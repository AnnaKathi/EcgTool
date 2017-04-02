//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_Diseases.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define TABLE "diseases"
//---------------------------------------------------------------------------
cMySqlDiseases::cMySqlDiseases(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlDiseases::~cMySqlDiseases()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: laden   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlDiseases::loadTable()
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
bool cMySqlDiseases::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.bez, "%.127s", frow[1]);

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlDiseases::insert(sDiseases data)
	{
	String q = "INSERT INTO " + String(TABLE) + " ";
	q+= "(`Bez`) VALUES ";
	q+= "(";
	q+= "'" + String(data.bez) + "'";
	q+= ")";

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlDiseases::update(sDiseases data)
	{
	String q = "UPDATE " + String(TABLE) + " SET ";
	q+= "Bez='" + String(data.bez) + "' ";
	q+= "WHERE Ident=" + String(data.ident);

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Datenfelder   ****************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String cMySqlDiseases::getNameOf(int disease) //eine Bezeichnugn einer Erkrankung
	{
	MYSQL_RES* res_old = fres; //aktuelle Position speichern

	String name = "";
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `Ident` = " + String(disease);
	if (!fwork->query(q))
		name = "- nicht gefunden (" + String(disease) + ") -";
	else
		{
		fres = fwork->getResult();
		frow = mysql_fetch_row(fres);
		if (frow == NULL) return "";

		name = String(frow[1]);
		}

	fres = res_old; //Position zur�cksetzen
	return name;
	}
//---------------------------------------------------------------------------
sarray_t cMySqlDiseases::getNamesOf(sarray_t idents) //Liste mit Bez. auff�llen
	{
	sarray_t res; res.clear();
	int ix = 0;
	for (sarray_itr itr = idents.begin(); itr != idents.end(); itr++)
		{
		slist_t& v = itr->second;
		res[ix].push_back(v[0]);
		res[ix].push_back(getNameOf(v[0].ToInt()));
		ix++;
		}

	return res;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: l�schen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlDiseases::deleteByIdent(int ident)
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
sDiseases cMySqlDiseases::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlDiseases::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------