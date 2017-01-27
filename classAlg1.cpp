//---------------------------------------------------------------------------
#pragma hdrstop

#include "classAlg1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
cAlg1::cAlg1()
	: fecg(new cEcg)
	{
	}
cAlg1::~cAlg1()
	{
	if (fecg) delete fecg;
	}

cEcg& cAlg1::get_ecg()
	{
	return *fecg;
	}


