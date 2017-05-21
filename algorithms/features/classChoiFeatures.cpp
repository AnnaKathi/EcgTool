//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classChoiFeatures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cChoiFeat::cChoiFeat()
	{
	fAlg_DbNr = 2;
	fParameter_Threshold    = 0.4;
	fParameter_Overlap_Time = 100;
	}
//---------------------------------------------------------------------------
cChoiFeat::~cChoiFeat()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   private functions   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cChoiFeat::FindMinMax(iarray_t array, double& min, double& max)
	{
	//TODO
	return true;
	}
//---------------------------------------------------------------------------
iarray_t cChoiFeat::FindOverlaps(iarray_t candidates)
	{
	/* Anmerkung Anna 30.04.17: Algorithmus funktioniert so nicht, weil jeder
	 * gefundene Kandidat min einen Nachbarn hat, weniger als overlap_time
	 * entfernt ist und deswegen entfernt wird -> alle Kandidaten werden als
	 * Overlap identifiziert
	 */
	iarray_t overlaps; overlaps.clear();
	if (candidates.size() <= 0) return overlaps;

	int zeit; 	   double wert;
	int next_zeit; double next_wert;
	int count = 0;

		//Änderung Anna ------------------------------------------------------
		//Wenn man die Kandidaten einfach von vorne durchläuft (nach der Zeit)
		//dann wird z.B. der erste direkt genommen
		//candidates = fmath.resort(candidates, false);

	for (iarray_itr itr = candidates.begin(); itr != candidates.end(); itr++)
		{
		ilist_t&v = itr->second;
		zeit = v[0];
		wert = v[1];

		itr++;
		if (itr == candidates.end()) break;
		v = itr->second;
		next_zeit = v[0];
		next_wert = v[1];
		itr--;

		if ((next_zeit - zeit) < fParameter_Overlap_Time) //beats are too close together
			{
			//add min-value of these two beats
			if (next_wert >= wert)
				{
				overlaps[count].push_back(zeit);
				overlaps[count].push_back(wert);
				}
			else
				{
				overlaps[count].push_back(next_zeit);
				overlaps[count].push_back(next_wert);
				}
			count++;
			}
		}
	return overlaps;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   function as described in paper   *********************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t cChoiFeat::getFeatures1(iarray_t curve)
	{
	fArray_Features.clear();
	if (!FindRPeaks1(curve))  return fArray_Features;
	if (!FindFeatures(curve)) return fArray_Features;
	return fArray_Features;
	}
//---------------------------------------------------------------------------
String cChoiFeat::getFeaturesStr1(iarray_t curve)
	{
	String features = "";
	if (!FindRPeaks1(curve))  return "";
	if (!FindFeatures(curve)) return "";

	for (iarray_itr itr = fArray_Features.begin(); itr != fArray_Features.end(); itr++)
		{
		ilist_t& v = itr->second;
		if (features == "")
			features = String(v[0]);
		else
			features += ";" + String(v[0]);
		}

	return features;
	}
//---------------------------------------------------------------------------
bool cChoiFeat::FindRPeaks1(iarray_t curve)
	{
	//Die R-Peaks anhand des Schwellenwerts finden und zurückgeben
	fArray_Rpeaks.clear();

	if (curve.size() <= 0)
		return fail(1, "Es wurde keine Kurve übergeben");


	//find max-Value in ECG-Array
	sArrayCha cha;
	farray.resetValues(curve, cha);

	//find potential candidates for R-Peaks through threshold
	/*GEÄNDERT: double max_threshold = fParameter_Threshold * max; */

		//Anpassung Anna ------------------------------------------------------
		//max * theshold ist so nicht richtig, weil 40% vom Max viel
		//weniger ist, als alle enthaltenen Wert -> 40% von der Differenz nehmen
		double max_threshold = cha.MinWert + ((cha.MaxWert - cha.MinWert) * fParameter_Threshold);
		//----------------------------------------------------------------------

	iarray_t candidates; candidates.clear();
	int count = 0;
	int zeit;
	double wert;
	for (iarray_itr itr = curve.begin(); itr != curve.end(); itr++)
		{
		ilist_t&v = itr->second;
		zeit = v[0];
		wert = v[1];

		if (wert >= max_threshold)
			{
			candidates[count].push_back(zeit);
			candidates[count].push_back(wert);
			count++;
			}
		}

	//find all overlaps
	iarray_t overlaps = FindOverlaps(candidates);

	//overlaps aus candidates entfernen
	//-> in rpeaks (rloc) nur candidates übernehmen, die nicht in overlaps sind
	iarray_t rloc = farray.remove(candidates, overlaps, 0);

	if (rloc.size() <= 0)
		return fail(1, "Es konnten keine R-Peaks gefunden werden.");
	else
		{
		fArray_Rpeaks = rloc;
		return ok();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   amendment: use Anna's R-Peak-class *******************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t cChoiFeat::getFeatures2(iarray_t curve)
	{
	fArray_Features.clear();
	if (!FindRPeaks2(curve))  return fArray_Features;
	if (!FindFeatures(curve)) return fArray_Features;
	return fArray_Features;
	}
//---------------------------------------------------------------------------
String cChoiFeat::getFeaturesStr2(iarray_t curve)
	{
	String features = "";
	if (!FindRPeaks2(curve))  return "";
	if (!FindFeatures(curve)) return "";

	for (iarray_itr itr = fArray_Features.begin(); itr != fArray_Features.end(); itr++)
		{
		ilist_t& v = itr->second;
		if (features == "")
			features = String(v[0]);
		else
			features += ";" + String(v[0]);
		}

	return features;
	}
//---------------------------------------------------------------------------
bool cChoiFeat::FindRPeaks2(iarray_t curve)
	{
	fArray_Rpeaks.clear();

	if (curve.size() <= 0)
		return fail(2, "Es wurde keine Kurve übergeben");

	iarray_t arr = fecg.rpeaks.find(curve, NULL);
	if (arr.size() <= 0)
		return fail(2, "Die R-Peaks konnten nicht gesetzt werden");

	fArray_Rpeaks = arr;
	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   find all features from curve   ***********************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cChoiFeat::FindFeatures(iarray_t curve)
	{
	fArray_Features.clear();

	if (curve.size() <= 0)
		return fail(2, "Es wurde keine Kurve übergeben");

	if (fArray_Rpeaks.size() <= 0)
		return fail(2, "Es wurden keine R-Peaks gesetzt");

	//Sicherheitsabfrage: Maximale Anzahl Herzschläge (= R-Peaks) bei Puls 200
	double max_beats = (curve.size() / 1000) * 200/60;
	if (fArray_Rpeaks.size() > max_beats)
		return fail(2, ftools.fmt("Zuviele R-Peaks gefunden: %d (max erlaubt %d)", fArray_Rpeaks.size(), (int)max_beats));

	int round = 0;
	int zeit, prev, next;
	int rr_left, rr_rigt;
	int von, bis;

	double p_von, p_bis, q_von, q_bis, s_von, s_bis, t_von, t_bis;
	iarray_t features; features.clear();

	bool first  = true;
	bool fehler = false;
	for (iarray_itr itr_rpeaks = fArray_Rpeaks.begin(); itr_rpeaks != fArray_Rpeaks.end(); itr_rpeaks++)
		{
		ilist_t& v = itr_rpeaks->second;
		zeit = v[0];

		if (first)
			{
			prev = zeit;
			first = false;
			continue;
			}

		itr_rpeaks++;
		if (itr_rpeaks == fArray_Rpeaks.end()) break;
		v = itr_rpeaks->second;
		next = v[0];
		itr_rpeaks--;

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
	fArray_Features[0].push_back(i_pq / anz);
	fArray_Features[1].push_back(i_qs / anz);
	fArray_Features[2].push_back(i_st / anz);
	fArray_Features[3].push_back(PAmp / anz);
	fArray_Features[4].push_back(QAmp / anz);
	fArray_Features[5].push_back(RAmp / anz);
	fArray_Features[6].push_back(SAmp / anz);
	fArray_Features[7].push_back(TAmp / anz);
	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   find one single feature-set   ************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cChoiFeat::getSingleFeatures(iarray_t ecg, int prev_zeit, int curr_zeit, int next_zeit)
	{
	//in diesem Herzschlag die Features aus dem QRS-Bereich finden
	if (ecg.size() <= 0)
		return fail(3, "Es wurden keine EKG-Daten übergeben");

	if (prev_zeit < 0 || curr_zeit < 0 || next_zeit < 0)
		return fail(3, ftools.fmt("Es wurden keine R-Peak-Zeiten gesetzt: %d, %d, %d", prev_zeit, curr_zeit, next_zeit));

	if (prev_zeit >= curr_zeit)
		return fail(3, ftools.fmt("Die R-Peak-Zeiten stimmen nicht (prev): %d, %d, %d", prev_zeit, curr_zeit, next_zeit));

	if (curr_zeit >= next_zeit)
		return fail(3, ftools.fmt("Die R-Peak-Zeiten stimmen nicht (curr): %d, %d, %d", prev_zeit, curr_zeit, next_zeit));

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
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void cChoiFeat::set_Threshold(double threshold)
	{
	if (threshold < 0 || threshold > 1) return;
	fParameter_Threshold = threshold;
	}
//---------------------------------------------------------------------------
double cChoiFeat::get_Threshold()
	{
	return fParameter_Threshold;
	}
//---------------------------------------------------------------------------
void cChoiFeat::set_Overlap(int time)
	{
	if (time <= 0) return;
	fParameter_Overlap_Time = time;
	}
//---------------------------------------------------------------------------
int cChoiFeat::get_Overlap()
	{
	return fParameter_Overlap_Time;
	}
//---------------------------------------------------------------------------
void cChoiFeat::set_Array_Rpeaks(iarray_t rpeaks)
	{
	fArray_Rpeaks = rpeaks;
	}
//---------------------------------------------------------------------------
iarray_t cChoiFeat::get_Array_Rpeaks()
	{
	return fArray_Rpeaks;
	}
//---------------------------------------------------------------------------
iarray_t cChoiFeat::get_Array_Features()
	{
	return fArray_Features;
	}
//---------------------------------------------------------------------------
iarray_t cChoiFeat::get_Array_Single_Features()
	{
	return fArray_Single_Features;
	}
//---------------------------------------------------------------------------
int cChoiFeat::get_algdbnr()
	{
	return fAlg_DbNr;
	}
//---------------------------------------------------------------------------
		/* obsolete: Berechnung der Features in FindFeatures()
		iarray_itr itr_curve = curve.find(zeit);
		v = itr_curve->second;
		RAmp = v[1];

		//-- QRS-Bereich finden
		qrs = farray.get(curve, prev, next);

		//RR-Intervalle feststellen
		rr_left = zeit - prev;
		rr_rigt = next - zeit;

		//-- Bereich und Minimun/Maximum feststellen
		//----- P-Welle
		p_von = (double)rr_left * 1/6; 		p_bis = (double)rr_left * 1/10;
		iarray_t arr = farray.get(qrs, (zeit - p_von), (zeit - p_bis));
		arr = fmath.resort(arr, false);
		iarray_itr itr = arr.begin();
		v = itr->second;
		PLoc = v[0];
		PAmp = v[1];
		points[pcount].push_back(PLoc);
		points[pcount].push_back(PAmp);
		pcount++;

		//----- Q-Bereich
		q_von = (double)rr_left * 1/10;		q_bis = 0;
		arr = farray.get(qrs, (zeit - q_von), (zeit - q_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		QLoc = v[0];
		QAmp = v[1];
		points[pcount].push_back(QLoc);
		points[pcount].push_back(QAmp);
		pcount++;

		//----- S-Bereich
		s_von = 0;							s_bis = (double)rr_rigt * 1/10;
		arr = farray.get(qrs, (zeit + s_von), (zeit + s_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		SLoc = v[0];
		SAmp = v[1];
		points[pcount].push_back(SLoc);
		points[pcount].push_back(SAmp);
		pcount++;

		//----- T-Welle
		t_von = (double)rr_rigt * 1/10;		t_bis = (double)rr_rigt * 1/2;
		arr = farray.get(qrs, (zeit + t_von), (zeit + t_bis));
		arr = fmath.resort(arr, false);
		itr = arr.begin();
		v = itr->second;
		TLoc = v[0];
		TAmp = v[1];
		points[pcount].push_back(TLoc);
		points[pcount].push_back(TAmp);
		pcount++;

		//Fiducial Points finden
		int int_pq = QLoc - PLoc; //PQ-Interval
		int int_qs = SLoc - QLoc; //QS-Interval
		int int_st = TLoc - SLoc; //ST-Interval
		*/
