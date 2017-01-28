//---------------------------------------------------------------------------
#pragma hdrstop

#include "classTurns.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cTurns::cTurns()
	{
	}
//---------------------------------------------------------------------------
cTurns::~cTurns()
	{
	}
//---------------------------------------------------------------------------
int	cTurns::calcTurns(cData data)
	{
	//auf einer Datenstruktur alle Wendepunkte feststellen, ein Wendepunkt
	//liegt vor, wenn der betrachtete Wert sich mehr als 'schwelle_proz' von den
	//Werten recht und links unterscheidet (Prozentwert!!)
	int count = 0;

	//todo in die Klasse verlagern, das erzeugt aber eine Fehlermeludng, warum?
	iarray_t arr = data.data_array;
	int bp = arr.size();

	if (arr.size() <= 0)
		{
		fail(1, "Das Daten-Array konnte nicht geladen werden oder ist leer");
		return -1;
		}

	iarray_t trn;
	trn.clear();

	int zeit;
	float lead1;
	for (iarray_itr itr = arr.begin(); itr != arr.end(); itr++)
		{
		zeit = itr->first;
		ilist_t& v = itr->second;
		lead1 = v[1];

		int bp = 0;
		}

	//Zugriff auf cBase nicht möglich, warum ?? ok();
	return count;
	}
//---------------------------------------------------------------------------
