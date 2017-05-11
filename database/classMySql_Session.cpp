//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define TABLE "sessions"
#define SESRE "sessionresearchers"
//---------------------------------------------------------------------------
cMySqlSession::cMySqlSession(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlSession::~cMySqlSession()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlSession::doQuery(String q)
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
bool cMySqlSession::get(int session)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `ID` = " + String(session);
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlSession::loadTable(String order) //order ist vorbesetzt mit ""
	{
	if (!fwork->loadTable(TABLE, order))
		return fail(fwork->error_code, fwork->error_msg);

	fres = fwork->getResult();
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlSession::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlSession::getLast()
	{
	String q = "SELECT * FROM " + String(TABLE) + " ORDER BY ID DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlSession::insert(sSession data)
	{
	String q = "INSERT INTO " + String(TABLE) + " ";
	q+= "(`Orte_ID`, `Stamp`, `Kommentar`) VALUES ";
	q+= "(";
	q+= "'" + String(data.ort) + "', ";
	q+= "'" + data.stamp     + "', ";
	q+= "'" + data.kommentar + "'";
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
bool cMySqlSession::update(sSession data)
	{
	//UPDATE `ecg`.`subjects` SET `Vorname`='Otto', `Nachname`='Mustermann' WHERE  `Ident`=7;
	String q = "UPDATE " + String(TABLE) + " SET ";
	q+= "Orte_ID='"    + String(data.ort)       + "',";
	q+= "Stamp='"     + data.stamp     + "',";
	q+= "Kommentar='" + data.kommentar + "' ";
	q+= "WHERE ID="   + String(data.ident);

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlSession::insertResearcher(int session, int researcher)
	{
	if (session <= 0 || researcher <= 0) return false;

	String q = "INSERT INTO `" + String(SESRE) + "` ";
	q += "(`Sessions_ID`, `Researchers_ID`) VALUES ";
	q += "(";
	q += "'" + String(session)    + "', ";
	q += "'" + String(researcher) + "'";
	q += ")";

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
int cMySqlSession::getSize()
	{
	if (!loadTable())
		{
		fail(fwork->error_code, fwork->error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
bool cMySqlSession::ParseRow()
	{
	fdata.ident     = atoi(frow[0]);
	fdata.ort       = atoi(frow[1]);
	fdata.stamp     = String(frow[2]);
	fdata.kommentar = String(frow[3]);
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Daten anzeigen   *************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlSession::listInCombo(TComboBox* cb, int mode) //mode ist mit 0 vorbesetzt
	{
	//Alle Personen aus der DB in der ComboBox anzeigen, der mode bestimmt
	//was angezeigt wird
	if (!loadTable(""))
		return fail(fwork->error_code, fwork->error_msg);

	cb->Items->Clear();
	String str;
	while (nextRow())
		{
		if (mode == 1)  str = ""; //String(fdata.nachname) + ", " + String(fdata.vorname);
		else 			str = ""; //pers = String(fdata.vorname) + " " + String(fdata.nachname);

		cb->Items->AddObject(str, (TObject*)fdata.ident);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlSession::deleteByIdent(int ident)
	{
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `ID` = " + String(ident);
	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Evtl zugehörige Tabellen löschen??
		}
		
	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   getter und setter   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sSession cMySqlSession::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlSession::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
