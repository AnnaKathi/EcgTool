//---------------------------------------------------------------------------
#ifndef classMathH
#define classMathH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
class PACKAGE cMath : public cBase
	{
public:
	cMath();
	~cMath();

	iarray_t	calcDerivate(iarray_t array);
	iarray_t	sortAscending(iarray_t array); //Werte aufsteigend sortieren
	iarray_t	sortDescending(iarray_t array); //Werte absteigend sortieren

private:

	};
//---------------------------------------------------------------------------
#endif
