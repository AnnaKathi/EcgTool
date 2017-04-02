//---------------------------------------------------------------------------
#ifndef classMySqlH
#define classMySqlH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "classMySql_Work.h"
#include "classMySql_EcgData.h"
#include "classMySql_People.h"
#include "classMySql_Diseases.h"
//---------------------------------------------------------------------------
class PACKAGE cMySql : public cBase
	{
public:
	cMySql();
	~cMySql();

	bool 	open();
	bool	close();

__property cMySqlEcgData&  ecg      = { read=get_ecg };
__property cMySqlPeople&   people   = { read=get_people };
__property cMySqlDiseases& diseases = { read=get_diseases };

private:
	cMySqlWork*		fwork;

	cMySqlEcgData*	fecg;
	cMySqlEcgData&  get_ecg();

	cMySqlPeople*	fpeople;
	cMySqlPeople&	get_people();

	cMySqlDiseases*	fdiseases;
	cMySqlDiseases&	get_diseases();
	};
//---------------------------------------------------------------------------
#endif
