//---------------------------------------------------------------------------
#ifndef classEcgH
#define classEcgH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classData.h"
//---------------------------------------------------------------------------
#include "classQrs.h"
#include "classHeartbeat.h"
//---------------------------------------------------------------------------
class PACKAGE cEcg : public cBase
	{
public:
	cEcg();
	~cEcg();

__property cData& data 		 = { read=get_data };
__property cQrs& qrs 		 = { read=get_qrs };
__property cHeartbeat& heart = { read=get_heart };

private:
	cData*		fdata;
	cData&		get_data();

	cQrs*		fqrs;
	cQrs&		get_qrs();

	cHeartbeat*	fheart;
	cHeartbeat&	get_heart();


	};
#endif
