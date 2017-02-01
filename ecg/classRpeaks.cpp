//---------------------------------------------------------------------------
#pragma hdrstop

#include "classRpeaks.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cRpeaks::cRpeaks()
	: fmath(new cMath), farray(new cArray)
	{
	}
//---------------------------------------------------------------------------
cRpeaks::~cRpeaks()
	{
	}
//---------------------------------------------------------------------------
iarray_t cRpeaks::find(iarray_t array, TImage* img1, TImage* img2)
	{
	iarray_t asc  = fmath->sortAscending(array);
	iarray_t desc = fmath->sortDescending(array);

	farray->display(asc,  img1);
	farray->display(desc, img2);
	
	return asc;
	}
//---------------------------------------------------------------------------

