/* Feature-Extraction nach Choi 2016
 * Todo: Beschreibung einfügen
 */
//---------------------------------------------------------------------------
#pragma hdrstop

#include "classFeaturesChoi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cFeaturesChoi::cFeaturesChoi()
	{
	fAlgIdent = 1;
	}
//---------------------------------------------------------------------------
cFeaturesChoi::~cFeaturesChoi()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   public functions   ***********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cFeaturesChoi::getFeatures(iarray_t curve, iarray_t rpeaks)
	{
	fFeatures.clear();

	if (curve.size() <= 0)  return fail(1, "Es wurde keine Kurve übergeben");
	if (rpeaks.size() <= 0)	return fail(1, "Es wurden keine R-Peaks gesetzt");

	//Sicherheitsabfrage: Maximale Anzahl Herzschläge (= R-Peaks) bei Puls 200
	double max_beats = (curve.size() / 1000) * 200/60;
	if (rpeaks.size() > max_beats)
		return fail(1, ftools.fmt("Zuviele R-Peaks gefunden: %d (max erlaubt %d)", rpeaks.size(), (int)max_beats));

	int round = 0;
	int zeit, prev, next;
	int rr_left, rr_rigt;
	int von, bis;

	double p_von, p_bis, q_von, q_bis, s_von, s_bis, t_von, t_bis;
	iarray_t features; features.clear();

	bool first  = true;
	bool fehler = false;
	for (iarray_itr itr = rpeaks.begin(); itr != rpeaks.end(); itr++)
		{
		ilist_t& v = itr->second;
		zeit = v[0];

		if (first)
			{
			prev = zeit;
			first = false;
			continue;
			}

		itr++;
		if (itr == rpeaks.end()) break;
		v = itr->second;
		next = v[0];
		itr--;

		if (!getSingleFeatures(curve, prev, zeit, next))
			{
			fehler = true;
			break;
			}

		features[round].push_back(fArray_Single_Features[0][0]);
		features[round].push_back(fArray_Single_Features[1][0]);
		features[round].push_back(fArray_Single_Features[2][0]);
		features[round].push_back(fArray_Single_Features[3][0]);
		features[round].push_back(fArray_Single_Features[4][0]);
		features[round].push_back(fArray_Single_Features[5][0]);
		features[round].push_back(fArray_Single_Features[6][0]);
		features[round].push_back(fArray_Single_Features[7][0]);
		round++;

		prev = zeit;
		}

	if (fehler)
		{
		//fail wurde von getSingleFeatures gesetzt
		return false;
		}

	int    i_pq = 0;   int    i_qs = 0; 	int    i_st = 0;
	double PAmp = 0.0; double QAmp = 0.0;	double RAmp = 0.0;
	double SAmp = 0.0; double TAmp = 0.0;

	for (iarray_itr itr = features.begin(); itr != features.end(); itr++)
		{
		ilist_t& v = itr->second;

		i_pq += v[0];
		i_qs += v[1];
		i_st += v[2];
		PAmp += v[3];
		QAmp += v[4];
		RAmp += v[5];
		SAmp += v[6];
		TAmp += v[7];
		}

	int anz = features.size();
	fFeatures[0].push_back(i_pq / anz);
	fFeatures[1].push_back(i_qs / anz);
	fFeatures[2].push_back(i_st / anz);
	fFeatures[3].push_back(PAmp / anz);
	fFeatures[4].push_back(QAmp / anz);
	fFeatures[5].push_back(RAmp / anz);
	fFeatures[6].push_back(SAmp / anz);
	fFeatures[7].push_back(TAmp / anz);

	//Features-String bilden
	fFeaturesStr = "";
	for (iarray_itr itr = fFeatures.begin(); itr != fFeatures.end(); itr++)
		{
		ilist_t& v = itr->second;
		if (fFeaturesStr == "")
			fFeaturesStr = String(v[0]);
		else
			fFeaturesStr += ";" + String(v[0]);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   private functions   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cFeaturesChoi::getSingleFeatures(iarray_t ecg, int prev_zeit, int curr_zeit, int next_zeit)
	{
	//in diesem Herzschlag die Features aus dem QRS-Bereich finden
	if (ecg.size() <= 0)
		return fail(2, "Es wurden keine EKG-Daten übergeben");

	if (prev_zeit < 0 || curr_zeit < 0 || next_zeit < 0)
		return fail(2, ftools.fmt("Es wurden keine R-Peak-Zeiten gesetzt: %d, %d, %d", prev_zeit, curr_zeit, next_zeit));

	if (prev_zeit >= curr_zeit)
		return fail(2, ftools.fmt("Die R-Peak-Zeiten stimmen nicht (prev): %d, %d, %d", prev_zeit, curr_zeit, next_zeit));

	if (curr_zeit >= next_zeit)
		return fail(2, ftools.fmt("Die R-Peak-Zeiten stimmen nicht (curr): %d, %d, %d", prev_zeit, curr_zeit, next_zeit));

	fArray_Single_Features.clear();
	double PAmp, QAmp, RAmp, SAmp, TAmp;
	int PLoc, QLoc, SLoc, TLoc;
	double p_von, p_bis, q_von, q_bis, s_von, s_bis, t_von, t_bis;

	iarray_itr itr_curve = ecg.find(curr_zeit);
	ilist_t& v = itr_curve->second;
	RAmp = v[1];

	//-- QRS-Bereich finden
	iarray_t qrs = farray.get(ecg, prev_zeit, next_zeit);
	if (qrs.size() <= 0)
		return fail(3, "Der QRS-Bereich konnte nicht gefunden werden");

	//RR-Intervalle feststellen
	int rr_left = curr_zeit - prev_zeit;
	int rr_rigt = next_zeit - curr_zeit;

	//-- Bereich und Minimun/Maximum feststellen
	//----- P-Welle
	p_von = (double)rr_left * 1/6; 		p_bis = (double)rr_left * 1/10;
	iarray_t arr = farray.get(qrs, (curr_zeit - p_von), (curr_zeit - p_bis));
	arr = fmath.resort(arr, false);
	iarray_itr itr = arr.begin();
	v = itr->second;
	PLoc = v[0];
	PAmp = v[1];

	//----- Q-Bereich
	q_von = (double)rr_left * 1/10;		q_bis = 0;
	arr = farray.get(qrs, (curr_zeit - q_von), (curr_zeit - q_bis));
	arr = fmath.resort(arr, true);
	itr = arr.begin();
	v = itr->second;
	QLoc = v[0];
	QAmp = v[1];

	//----- S-Bereich
	s_von = 0;							s_bis = (double)rr_rigt * 1/10;
	arr = farray.get(qrs, (curr_zeit + s_von), (curr_zeit + s_bis));
	arr = fmath.resort(arr, true);
	itr = arr.begin();
	v = itr->second;
	SLoc = v[0];
	SAmp = v[1];

	//----- T-Welle
	t_von = (double)rr_rigt * 1/10;		t_bis = (double)rr_rigt * 1/2;
	arr = farray.get(qrs, (curr_zeit + t_von), (curr_zeit + t_bis));
	arr = fmath.resort(arr, false);
	itr = arr.begin();
	v = itr->second;
	TLoc = v[0];
	TAmp = v[1];

	fArray_Single_Features[0].push_back(QLoc - PLoc); //intervall pq
	fArray_Single_Features[1].push_back(SLoc - QLoc); //intervall sq
	fArray_Single_Features[2].push_back(TLoc - SLoc); //intervall st

	fArray_Single_Features[3].push_back(PAmp);
	fArray_Single_Features[4].push_back(QAmp);
	fArray_Single_Features[5].push_back(RAmp);
	fArray_Single_Features[6].push_back(SAmp);
	fArray_Single_Features[7].push_back(TAmp);

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   getter und setter   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cFeaturesChoi::get_alg_ident()
	{
	return fAlgIdent;
	}
//---------------------------------------------------------------------------
iarray_t cFeaturesChoi::get_features()
	{
	return fFeatures;
	}
//---------------------------------------------------------------------------
String cFeaturesChoi::get_features_string()
	{
	return fFeaturesStr;
	}
//---------------------------------------------------------------------------
