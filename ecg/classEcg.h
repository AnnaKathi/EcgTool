//---------------------------------------------------------------------------
#ifndef classEcgH
#define classEcgH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classCsv.h"
//---------------------------------------------------------------------------
#include "classQrs.h"
#include "classHeartbeat.h"
//---------------------------------------------------------------------------
class PACKAGE cEcg : public cBase
	{
public:
	cEcg();
	~cEcg();

__property cCsv& csv = { read=get_csv };
__property cQrs& qrs = { read=get_qrs };
__property cHeartbeat& heart = { read=get_heart };

private:
	cCsv*		fcsv;
	cCsv&		get_csv();

	cQrs*		fqrs;
	cQrs&		get_qrs();

	cHeartbeat*	fheart;
	cHeartbeat&	get_heart();


	};
#endif
