//---------------------------------------------------------------------------
#pragma hdrstop

#include "classEcg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cEcg::cEcg()
	: fqrs(new cQrs), fheart(new cHeartbeat)
	{


	}

cEcg::~cEcg()
	{
	if (fqrs) delete fqrs;
	if (fheart) delete fheart;
	}

cQrs& cEcg::get_qrs()
	{
	return *fqrs;
	}

cHeartbeat& cEcg::get_heart()
	{
	return *fheart;
	}
