//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_People.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define TABLE  "subjects"
#define SUBDIS "subject_disease"
//---------------------------------------------------------------------------
cMySqlPeople::cMySqlPeople(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlPeople::~cMySqlPeople()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::doQuery(String q)
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
bool cMySqlPeople::loadTable()
	{
	String q = "SELECT * FROM " + String(TABLE);
	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		fres = fwork->getResult();
		return ok();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.vorname,  "%.127s", frow[1]);
	sprintf(fdata.nachname, "%.127s", frow[2]);

	//todo Erkrankungern laden
	//String test = getDiseasesOf(fdata.ident);

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Datenfelder   ****************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String cMySqlPeople::getNameOf(int person)
	{
	MYSQL_RES* res_old = fres; //aktuelle Position speichern

	String name = "";
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `Ident` = " + String(person);
	if (!fwork->query(q))
		name = "- nicht gefunden (" + String(person) + ") -";
	else
		{
		fres = fwork->getResult();
		frow = mysql_fetch_row(fres);
		if (frow == NULL) return "";

		name = String(frow[1]) + " " + String(frow[2]);
		}

	fres = res_old; //Position zurücksetzen
	return name;
	}
//---------------------------------------------------------------------------
sarray_t cMySqlPeople::getDiseasesOf(int person)
	{
	MYSQL_RES* res_old = fres; //aktuelle Position speichern

	sarray_t arr; arr.clear();
	String q =
		"SELECT * FROM `" + String(SUBDIS) +
		"` WHERE `PersIdent` = " + String(person) +
		" GROUP BY DisIdent"; //zur Sicherheit, sollte nicht nötig sein
	if (!fwork->query(q))
		; //keine Erkankungen vorhanden
	else
		{
		fres = fwork->getResult();
		int ix = 0;
		while ((frow = mysql_fetch_row(fres)) != NULL)
			{
			arr[ix].push_back(frow[2]); //DisIdent
			ix++;
			}
		}

	fres = res_old; //Position zurücksetzen
	return arr;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlPeople::deleteByIdent(int ident)
	{
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
sPeople cMySqlPeople::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlPeople::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
