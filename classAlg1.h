//---------------------------------------------------------------------------
#ifndef classAlg1H
#define classAlg1H
//---------------------------------------------------------------------------
#include <classes.hpp>
#include "basics/classBase.h"
#include "ecg/classEcg.h"
//---------------------------------------------------------------------------
class PACKAGE cAlg1 : public cBase
	{
public:
	cAlg1();
	~cAlg1();

__property cEcg& ecg = { read=get_ecg };

private:
	cEcg*	fecg;
	cEcg&	get_ecg();


    };
#endif
