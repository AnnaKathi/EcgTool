//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_People.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define TABLE  "subjects"
#define SUBDIS "subdiseases"
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
bool cMySqlPeople::parse()
	{
	if (frow == NULL) return false;
	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.vorname,  "%.127s", frow[1]);
	sprintf(fdata.nachname, "%.127s", frow[2]);
	fdata.age = atoi(frow[3]);
	fdata.sex = atoi(frow[4]);
	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::get(int person)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `ID` = " + String(person);
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	return parse();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::loadTable(String order) //order ist vorbesetzt mit ""
	{
	if (!fwork->loadTable(TABLE, order))
		return fail(fwork->error_code, fwork->error_msg);

	fres = fwork->getResult();
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	return parse();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::getLast()
	{
	String q = "SELECT * FROM " + String(TABLE) + " ORDER BY ID DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	return parse();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlPeople::insert(sPeople data)
	{
	//INSERT INTO `ecg`.`subjects` (`Vorname`, `Nachname`) VALUES ('Otto', 'Mustermann');
	String q = "INSERT INTO " + String(TABLE) + " ";
	q+= "(`Vorname`, `Nachname`, `Age`, `Sex`) VALUES ";
	q+= "(";
	q+= "'" + String(data.vorname)  + "', ";
	q+= "'" + String(data.nachname) + "', ";
	q+= "'" + String(data.age)		+ "', ";
	q+= "'" + String(data.sex)		+ "'";
	q+= ")";

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können (letzten Datensatz nach Ident laden)
		return getLast();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::update(sPeople data)
	{
	//UPDATE `ecg`.`subjects` SET `Vorname`='Otto', `Nachname`='Mustermann' WHERE  `Ident`=7;
	String q = "UPDATE " + String(TABLE) + " SET ";
	q+= "Vorname='"  + String(data.vorname)  + "',";
	q+= "Nachname='" + String(data.nachname) + "',";
	q+= "Age='" + String(data.age) + "',";
	q+= "Sex='" + String(data.sex) + "'";
	q+= "WHERE ID=" + String(data.ident);

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
String cMySqlPeople::getNameOf(int person)
	{
	MYSQL_RES* res_old = fres; //aktuelle Position speichern

	String name = "";
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `ID` = " + String(person);
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
int cMySqlPeople::getSize()
	{
	if (!loadTable())
		{
		fail(fwork->error_code, fwork->error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Daten anzeigen   *************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlPeople::listInCombo(TComboBox* cb, int mode) //mode ist mit 0 vorbesetzt
	{
	//Alle Personen aus der DB in der ComboBox anzeigen, der mode bestimmt
	//was angezeigt wird
	if (!loadTable("Nachname ASC"))
		return fail(fwork->error_code, fwork->error_msg);

	cb->Items->Clear();
	String pers;
	while (nextRow())
		{
		if (mode == 1)  pers = String(fdata.nachname) + ", " + String(fdata.vorname);
		else 			pers = String(fdata.vorname) + " " + String(fdata.nachname);

		cb->Items->AddObject(pers, (TObject*)fdata.ident);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlPeople::deleteByIdent(int ident)
	{
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `ID` = " + String(ident);
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
