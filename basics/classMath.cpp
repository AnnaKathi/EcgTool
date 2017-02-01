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

