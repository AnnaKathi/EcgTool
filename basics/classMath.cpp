//---------------------------------------------------------------------------
#pragma hdrstop

#include "classMath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cMath::cMath()
	{
	}
//---------------------------------------------------------------------------
cMath::~cMath()
	{
	}
//---------------------------------------------------------------------------
iarray_t cMath::calcDerivate(iarray_t array)
	{
	iarray_t deriv;
	deriv.clear();

	//erste Ableitung = Steigung von farr
	int zeit;
	int ix = 0;
	float before, lead1, steigung;
	bool first = true;
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		zeit = itr->first;
		ilist_t& v = itr->second;
		lead1 = v[1];

		if (!first)
			{
			steigung = lead1 - before;
			deriv[ix].push_back(zeit);
			deriv[ix].push_back(steigung);
			ix++;
			}

		first = false;
		before = lead1;
		}

	return deriv;
	}
//---------------------------------------------------------------------------
iarray_t cMath::sortAscending(iarray_t array)
	{
	//Werte aufsteigend sortieren
	iarray_t asc;
	asc.clear();
	asc = array;

	//todo, eleganter und zeitsparender mit Quicksort o.ä.

	int n, i, zeit;
	float wert;
	for (n = asc.size(); n > 1; n--)
		{
		for (i = 0; i < n-1; i++)
			{
			if (asc[i][1] > asc[i+1][1])
				{
				//swap values
				zeit = asc[i][0];
				wert = asc[i][1];

				asc[i][0] = asc[i+1][0];
				asc[i][1] = asc[i+1][1];

				asc[i+1][0] = zeit;
				asc[i+1][0] = wert;
				}
			}
		}
	return asc;
	}
//---------------------------------------------------------------------------
iarray_t cMath::sortDescending(iarray_t array)
	{
	//Werte aufsteigend sortieren
	iarray_t desc;
	desc.clear();
	desc = array;

	//todo, eleganter und zeitsparender mit Quicksort o.ä.

	int n, i, zeit;
	float wert;
	for (n = desc.size(); n > 1; n--)
		{
		for (i = 0; i < n-1; i++)
			{
			if (desc[i][1] < desc[i+1][1])
				{
				//swap values
				zeit = desc[i][0];
				wert = desc[i][1];

				desc[i][0] = desc[i+1][0];
				desc[i][1] = desc[i+1][1];

				desc[i+1][0] = zeit;
				desc[i+1][0] = wert;
				}
			}
		}
	return desc;
	}
//---------------------------------------------------------------------------

