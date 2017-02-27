//---------------------------------------------------------------------------
#ifndef classTurnsH
#define classTurnsH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
//---------------------------------------------------------------------------
class PACKAGE cTurns : public cBase
	{
public:
	cTurns();
	~cTurns();

	int			calcTurns(iarray_t array);

private:
	//iarray_t	farr; //die eigentliche Kurve
	//iarray_t	ftrn; //die Wendepunkte
	};
//---------------------------------------------------------------------------
#endif
