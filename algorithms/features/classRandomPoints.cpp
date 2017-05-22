//---------------------------------------------------------------------------
#pragma hdrstop

#include "classRandomPoints.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cRandomPoints::cRandomPoints()
	{
	fAlg_DbNr = 3;
	}
//---------------------------------------------------------------------------
cRandomPoints::~cRandomPoints()
	{
	}
//---------------------------------------------------------------------------
bool cRandomPoints::getRandomPointsFromBeat(iarray_t beat, int anzahl)
	{
	if (beat.size() <= 0)
		return fail(1, "Es wurde ein leeres Array übergeben");

	if (anzahl <= 0)
		return fail(1, "Es wurde keine Anzahl von Werten übergeben");

	//todo: umstellen, Funktion bei cQRS einfügen, die den QRS-Bereich bestimmt

	//QRS-Komplex feststellen, der übergebene Herzschlag beginnt
	//am R-Peak und endet am R-Peak-1
	//ein QRS-Bereich ist ??? Millisekunden lang
	double ll = 100;

	iarray_t qrs; qrs.clear();
	iarray_t::reverse_iterator itr_rev = beat.rbegin();
	int count = 0;
	while (count < (ll/2))
		{
		if (itr_rev == beat.rend()) break;

		ilist_t& v = itr_rev->second;
		qrs[count].push_back(v[0]);
		qrs[count].push_back(v[1]);

		itr_rev++;
		count++;
		}

	iarray_itr itr = beat.begin();
	int ix = count;
	count = 0;
	while (count < (ll/2))
		{
		if (itr == beat.end()) break;

		ilist_t& v = itr->second;
		qrs[ix].push_back(v[0]);
		qrs[ix].push_back(v[1]);

		itr++;
		count++;
		ix++;
		}

	if (qrs.size() <= 0)
		return fail(1, "Es konnte kein QRS-Bereich gefunden werden");

	//Beispiel: 20 Werte gewünscht, 100 msek QRS-Bereich = jeden 5. Wert nehmen
	double block = ll / (double)(anzahl+1);

	randomValues.clear();

	int pos;
	double wert;
	for (int i = 1; i < (anzahl+1); i++)
		{
		pos = i * block;
		wert = qrs[pos][1];

		randomValues[i-1].push_back(wert);
		}

	if (randomValues.size() != anzahl)
		return fail(1, "Berechnung der Random-Points war fehlerhaft");
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cRandomPoints::resetBeatPoints()
	{
	rvIndex = -1;
	randomP = 0.0;
	return true;
	}
//---------------------------------------------------------------------------
bool cRandomPoints::nextPointInBeat()
	{
	rvIndex++;
	if (rvIndex >= randomValues.size())
		return false;

	randomP = randomValues[rvIndex][0];
	return true;
	}
//---------------------------------------------------------------------------
int cRandomPoints::get_algdbnr()
	{
	return fAlg_DbNr;
	}
//---------------------------------------------------------------------------

