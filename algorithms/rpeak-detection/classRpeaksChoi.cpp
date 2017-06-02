//---------------------------------------------------------------------------
#pragma hdrstop

#include "classRpeaksChoi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cRpeaksChoi::cRpeaksChoi()
	{
	fAlgIdent = 2;
	fParameter_Threshold    = 0.4;
	fParameter_Overlap_Time = 100;
	}
//---------------------------------------------------------------------------
cRpeaksChoi::~cRpeaksChoi()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   public functions   ***********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cRpeaksChoi::findRpeaks(iarray_t curve)
	{
	//Die R-Peaks anhand des Schwellenwerts finden und zurückgeben
	fRpeaks.clear();

	if (curve.size() <= 0) return fail(1, "Es wurde keine Kurve übergeben");

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
	iarray_t overlaps = findOverlaps(candidates);

	//overlaps aus candidates entfernen
	//-> in rpeaks (rloc) nur candidates übernehmen, die nicht in overlaps sind
	iarray_t rloc = farray.remove(candidates, overlaps, 0);

	if (rloc.size() <= 0)
		return fail(1, "Es konnten keine R-Peaks gefunden werden.");
	else
		{
		fRpeaks = rloc;
		return ok();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   private functions   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t cRpeaksChoi::findOverlaps(iarray_t candidates)
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
/******************   getter und setter   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cRpeaksChoi::get_alg_ident()
	{
	return fAlgIdent;
	}
//---------------------------------------------------------------------------
iarray_t cRpeaksChoi::get_rpeaks()
	{
	return fRpeaks;
	}
//---------------------------------------------------------------------------
