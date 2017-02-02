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
iarray_t cMath::sortAsc(iarray_t array, TProgressBar* job)
	{
	return sort(array, true, job);
	}
//---------------------------------------------------------------------------
iarray_t cMath::sortDesc(iarray_t array, TProgressBar* job)
	{
	return sort(array, false, job);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   private Funktionen   *************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t cMath::sort(iarray_t array, bool asc, TProgressBar* job)
	{
	//Werte sortieren
	iarray_t arr;
	arr.clear();
	arr = array;

	//todo: progressBar, anders lösen
	//todo, eleganter und zeitsparender mit Quicksort o.ä.

	int n, i, zeit1, zeit2;
	float wert1, wert2;

	int last = arr.size();
	bool swapped, swap;
	job->Max = last;
	job->Position = 0;
	while (last > 0)
		{
		swapped = false;
		for (i = 0; i < last-1; i++) //vom ersten bis zum letzten Wert im Restfenster
			{
			zeit1 = arr[i][0];
			wert1 = arr[i][1];

			zeit2 = arr[i+1][0];
			wert2 = arr[i+1][1];

				 if ( asc && (wert1 > wert2)) swap = true;
			else if (!asc && (wert1 < wert2)) swap = true;
			else swap = false;

			if (swap)
				{
				//swap values
				arr[i][0] = zeit2;
				arr[i][1] = wert2;

				arr[i+1][0] = zeit1;
				arr[i+1][1] = wert1;

				swapped = true;
				}
			}

		if (!swapped)
			{
			//es wurden keine Werte mehr geswappt, dann können wir aufhören
			break;
			}

		last--;
		job->Position++;
		}

	job->Position = 0;
	return arr;
	}
//---------------------------------------------------------------------------

