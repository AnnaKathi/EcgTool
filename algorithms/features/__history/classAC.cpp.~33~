//todo: check what's actual needed (in algorithmes to implement) and create class
//---------------------------------------------------------------------------
#pragma hdrstop

#include "classAC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cAC::cAC()
	{
	}
//---------------------------------------------------------------------------
cAC::~cAC()
	{
	}
//---------------------------------------------------------------------------
iarray_t cAC::buildACOld(iarray_t array)
	{
	// Calculate the (un-normalized) autocorrelation for a frame of a signal
	short order = array.size();

	ilist_t R(order);
	float sum;
	int i,j;

	for (i=0; i < order; i++)
		{
		sum = 0;
		for (j = 0; j < (order-i); j++)
			{
			sum += array[j][1] * array[j+i][1];
			}

		R[i] = sum;
		}

	iarray_t arr; arr.clear();
	int siz = R.size();
	double wert;
	for (int i = 0; i < siz; i++)
		{
		wert = R[i];
		arr[i].push_back(i);
		arr[i].push_back(wert);
		}

	return arr;
	}
//---------------------------------------------------------------------------
iarray_t cAC::buildAC(iarray_t array)
	{
	// Calculate the (un-normalized) autocorrelation for a frame of a signal
	short order = array.size();

	ilist_t R(order);
	float sum;
	int i,j;

	for (i = 1; i < order; i++)
		{
		R[i] = array[i][1] * array[i-1][1];
		}

	iarray_t arr; arr.clear();
	int siz = R.size();
	double wert;
	for (int i = 0; i < siz; i++)
		{
		wert = R[i];
		arr[i].push_back(i);
		arr[i].push_back(wert);
		}

	return arr;
	}
//---------------------------------------------------------------------------

