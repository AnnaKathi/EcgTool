//---------------------------------------------------------------------------
#ifndef classMathH
#define classMathH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
class PACKAGE cMath : public cBase
	{
public:
	cMath();
	~cMath();

	iarray_t	calcDerivate(iarray_t array);
	iarray_t	sortAsc(iarray_t  array, TProgressBar* job); //Werte aufsteigend sortieren
	iarray_t	sortDesc(iarray_t array, TProgressBar* job); //Werte absteigend sortieren

private:
	iarray_t	sort(iarray_t array, bool asc, TProgressBar* job);

	};
//---------------------------------------------------------------------------
#endif
