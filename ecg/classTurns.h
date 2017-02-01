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
	//warum geht das nicht ?? iarray_t	farr; //die eigentliche Kurve
	//warum geht das nicht ?? iarray_t	ftrn; //die Wendepunkte
	};
//---------------------------------------------------------------------------
#endif
