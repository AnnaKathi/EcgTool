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

	void		setImage(TImage* img);  //todo: wieder löschen
	iarray_t	calcDerivate(iarray_t array);

	iarray_t	resort(iarray_t array, bool asc);

private:

	};
//---------------------------------------------------------------------------
#endif
