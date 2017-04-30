//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classChoiFeatures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cChoiFeat::cChoiFeat()
	{
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

		//�nderung Anna ------------------------------------------------------
		//Wenn man die Kandidaten einfach von vorne durchl�uft (nach der Zeit)
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
/******************   public functions   ***********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t cChoiFeat::getFeatures(iarray_t curve)
	{
	fArray_Features.clear();
	if (!FindRPeaks(curve))   return fArray_Features;
	if (!FindFeatures(curve)) return fArray_Features;
	return fArray_Features;
	}
//---------------------------------------------------------------------------
bool cChoiFeat::FindRPeaks(iarray_t curve)
	{
	//Die R-Peaks anhand des Schwellenwerts finden und zur�ckgeben
	fArray_Rpeaks.clear();

	if (curve.size() <= 0)
		return fail(1, "Es wurde keine Kurve �bergeben");


	//find max-Value in ECG-Array
	sArrayCha cha;
	farray.resetValues(curve, cha);

	//find potential candidates for R-Peaks through threshold
	/*GE�NDERT: double max_threshold = fParameter_Threshold * max; */

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
	//-> in rpeaks (rloc) nur candidates �bernehmen, die nicht in overlaps sind
	iarray_t rloc = farray.remove(candidates, overlaps, 0);

	if (rloc.size() <= 0)
		return fail(2, "Es konnten keine R-Peaks gefunden werden.");
	else
		{
		fArray_Rpeaks = rloc;
		return ok();
		}
	}
//---------------------------------------------------------------------------
bool cChoiFeat::FindFeatures(iarray_t curve)
	{
	fArray_Features.clear();

	if (curve.size() <= 0)
		return fail(1, "Es wurde keine Kurve �bergeben");

	if (fArray_Rpeaks.size() <= 0)
		return fail(3, "Es wurden keine R-Peaks gesetzt");

	//Sicherheitsabfrage: Maximale Anzahl Herzschl�ge (= R-Peaks) bei Puls 200
	double max_beats = (curve.size() / 1000) * 200/60;
	if (fArray_Rpeaks.size() > max_beats)
		{
		String msg = ftools.fmt("Zuviele R-Peaks gefunden: %d (max erlaubt %d)", fArray_Rpeaks.size(), (int)max_beats);
		return fail(4, msg.c_str());
		}

	iarray_t qrs;

	int round = -1;
	int zeit, prev, next;
	int rr_left, rr_rigt;
	int von, bis;

	double p_von, p_bis, q_von, q_bis, s_von, s_bis, t_von, t_bis;

	iarray_t points; points.clear();
	int pcount = 0;

	int PLoc, QLoc, SLoc, TLoc; 
	int int_pq, int_qs, int_st;
	double PAmp, QAmp, RAmp, SAmp, TAmp; 

	bool first = true;
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

    	round++;
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

		if (round < 128) //alle weiteren Werte ignorieren
			{
			FidPQInt[round] = int_pq;
			FidQSInt[round] = int_qs;
			FidSTInt[round] = int_st;
			FidPAmp[round]  = PAmp;
			FidQAmp[round]  = QAmp;
			FidRAmp[round]  = RAmp;
			FidSAmp[round]  = SAmp;
			FidTAmp[round]  = TAmp;
			}

		prev = zeit;
		}

	int_pq = int_qs = int_st = 0;
	PAmp = QAmp = RAmp = SAmp = TAmp = 0.00;
	for (int i = 0; i < round; i++)
		{
		int_pq += FidPQInt[i];
		int_qs += FidQSInt[i];
		int_st += FidSTInt[i];
		PAmp += FidPAmp[i];
		QAmp += FidQAmp[i];
		RAmp += FidRAmp[i];
		SAmp += FidSAmp[i];
		TAmp += FidTAmp[i];
		}

	int_pq = int_pq / (round);
	int_qs = int_qs / (round);
	int_st = int_st / (round);
	PAmp = PAmp / (round);
	QAmp = QAmp / (round);
	RAmp = RAmp / (round);
	SAmp = SAmp / (round);
	TAmp = TAmp / (round);

	fArray_Features[0].push_back(int_pq);
	fArray_Features[1].push_back(int_qs);
	fArray_Features[2].push_back(int_st);

	fArray_Features[3].push_back(PAmp);
	fArray_Features[4].push_back(QAmp);
	fArray_Features[5].push_back(RAmp);
	fArray_Features[6].push_back(SAmp);
	fArray_Features[7].push_back(TAmp);
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