//---------------------------------------------------------------------------
#ifndef classMySqlH
#define classMySqlH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classTools.h"
#include "classMySql_Work.h"
#include "classMySql_EcgData.h" //alte EKG-Klasse
#include "classMySql_Ecg.h"     //neue EKG-Klasse
#include "classMySql_People.h"
#include "classMySql_DescDb.h"
//---------------------------------------------------------------------------
class PACKAGE cMySql : public cBase
	{
public:
	cMySql();
	~cMySql();

	bool 	create();
	bool 	drop();
	bool	dbExists();
	bool	tabExists(String tabelle);

	bool 	open();
	bool 	openWithoutDb();
	bool	close();

__property cMySqlEcgData&  ecg      = { read=get_ecg };
__property cMySqlEcg&      ecgneu   = { read=get_ecg_neu  };
__property cMySqlPeople&   people   = { read=get_people   };

__property cMySqlDescDb&   diseases = { read=get_diseases };
__property cMySqlDescDb&   orte     = { read=get_orte };

private:
	cTools			ftools;
	cMySqlWork*		fwork;

	cMySqlEcgData*	fecg;
	cMySqlEcgData&  get_ecg();

	cMySqlEcg*		fecgneu;
	cMySqlEcg&		get_ecg_neu();

	cMySqlPeople*	fpeople;
	cMySqlPeople&	get_people();

	cMySqlDescDb*	fdiseases;
	cMySqlDescDb&	get_diseases();

	cMySqlDescDb*	forte;
	cMySqlDescDb&	get_orte();
	};
//---------------------------------------------------------------------------
#endif
