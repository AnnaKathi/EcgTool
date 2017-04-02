//---------------------------------------------------------------------------
#pragma hdrstop

#include "classMySql.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cMySql::cMySql()
	{
	fwork     = new cMySqlWork();
	fecg      = new cMySqlEcgData(*fwork);
	fpeople   = new cMySqlPeople(*fwork);
	fdiseases = new cMySqlDiseases(*fwork);
	}
//---------------------------------------------------------------------------
cMySql::~cMySql()
	{
	if (fwork)     delete fwork;
	if (fecg)      delete fecg;
	if (fpeople)   delete fpeople;
	if (fdiseases) delete fdiseases;
	}
//---------------------------------------------------------------------------
bool cMySql::open()
	{
	if (!fwork->open())
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Unterklassen erstellen
		return ok();
		}
	}
//---------------------------------------------------------------------------
bool cMySql::close()
	{
	if (!fwork->close())
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
cMySqlEcgData& cMySql::get_ecg()
	{
	return *fecg;
	}
//---------------------------------------------------------------------------
cMySqlPeople& cMySql::get_people()
	{
	return *fpeople;
	}
//---------------------------------------------------------------------------
cMySqlDiseases& cMySql::get_diseases()
	{
	return *fdiseases;
	}
//---------------------------------------------------------------------------
