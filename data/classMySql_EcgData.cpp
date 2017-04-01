//---------------------------------------------------------------------------
#pragma hdrstop

#include "classMySql_EcgData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define TABLE "ecgdata"
//---------------------------------------------------------------------------
cMySqlEcgData::cMySqlEcgData(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlEcgData::~cMySqlEcgData()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::doQuery(String q)
	{
	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		fres = fwork->getResult();
		return ok();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: laden   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcgData::loadTable()
	{
	String q = "SELECT * FROM " + String(TABLE);
	return doQuery(q);
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::loadByPerson(int person)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE PersIdent = " + String(person);
	return doQuery(q);
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	fdata.person  = atoi(frow[1]);
	fdata.session = atoi(frow[2]);
	fdata.pos = (ePosition) atoi(frow[3]); //todo ePosition umwandeln in Text

	fdata.werte[0] = atof(frow[4]);
	fdata.werte[1] = atof(frow[5]);
	fdata.werte[2] = atof(frow[6]);
	fdata.werte[3] = atof(frow[7]);
	fdata.werte[4] = atof(frow[8]);

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: l�schen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcgData::deleteByIdent(int ident)
	{
	//DELETE FROM `ecg`.`ecgdata` WHERE  `Ident`=51;
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `Ident` = " + String(ident);
	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   getter und setter   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sEcgData cMySqlEcgData::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlEcgData::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------