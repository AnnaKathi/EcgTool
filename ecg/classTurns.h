//---------------------------------------------------------------------------
#ifndef classTurnsH
#define classTurnsH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classData.h"
//---------------------------------------------------------------------------
class PACKAGE cTurns : public cBase
	{
public:
	cTurns();
	~cTurns();

	int			calcTurns(cData data);

private:
	//warum geht das nicht ?? iarray_t	farr; //die eigentliche Kurve
	//warum geht das nicht ?? iarray_t	ftrn; //die Wendepunkte
	};
//---------------------------------------------------------------------------
#endif
