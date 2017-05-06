//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_Ecg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define TABLE "ecgdata"
//---------------------------------------------------------------------------
cMySqlEcg::cMySqlEcg(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlEcg::~cMySqlEcg()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlEcg::doQuery(String q)
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
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcg::save(sEcg data, TMemo* memo)
	{
	//Row muss vorher gesetzt sein
	String s = "";
	char feld[64]; double wert;
	for (int i = 0; i < 100; i++)
		{
		wert = data.werte[i];
		sprintf(feld, "%.8f", wert);
		if (i == 0)
			s = String(feld);
		else
			s += ";" + String(feld);
		}

	//INSERT INTO `ecg`.`ecgdata` (`Sessions_ID`, `Subjects_ID`, `Positions_ID`, `States_ID`, `Lagen_ID`, `Werte`) VALUES (1, 1, 1, 1, 1, '0,8723645897623');
	String q = ftools.fmt(
		"INSERT INTO `%s` "
		"(`Sessions_ID`, `Subjects_ID`, `Positions_ID`, `States_ID`, `Lagen_ID`, `Werte`) "
		"VALUES (%d, %d, %d, %d, %d, '%s')",
		String(TABLE),
		data.session, data.person, data.position, data.state, data.lage, s.c_str());

	memo->Lines->Add("");
	memo->Lines->Add(q);
	memo->Lines->Add("");

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können 
		return getLast();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: laden   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcg::loadTable()
	{
	String q = "SELECT * FROM " + String(TABLE);
	return doQuery(q);
	}
//---------------------------------------------------------------------------
bool cMySqlEcg::loadByIdent(int ident)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE Ident = " + String(ident);
	return doQuery(q);
	}
//---------------------------------------------------------------------------
bool cMySqlEcg::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	//frow[1] enthält die EKG-Daten

	//todo
	/*
	fdata.werte[0] = atof(frow[4]);
	fdata.werte[1] = atof(frow[5]);
	fdata.werte[2] = atof(frow[6]);
	fdata.werte[3] = atof(frow[7]);
	fdata.werte[4] = atof(frow[8]);
	*/

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlEcg::getLast()
	{
	String q = "SELECT * FROM " + String(TABLE) + " ORDER BY Ident DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident    = atoi(frow[0]);
	fdata.session  = atoi(frow[1]);
	fdata.person   = atoi(frow[2]);
	fdata.position = atoi(frow[3]);
	fdata.state    = atoi(frow[4]);
	fdata.lage     = atoi(frow[5]);
	//todo fdata.werte

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcg::deleteByIdent(int ident)
	{
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `Ident` = " + String(ident);
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
int cMySqlEcg::getSize()
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
/********************   getter und setter   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sEcg cMySqlEcg::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlEcg::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
