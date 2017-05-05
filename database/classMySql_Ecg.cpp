//---------------------------------------------------------------------------
#pragma hdrstop

#include "classMySql_Ecg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define TABLE "ecg"
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
	for (int i = 0; i < 10; i++)
		{
		double wert = data.werte[i];
		if (i == 0)
			s = String(wert);
		else
			s += ";" + String(wert);
		}

	//INSERT INTO `ecg`.`ecg` (`Ident`, `Werte`) VALUES (1, 0x557074696D6500006500630074006500);
	String q = ftools.fmt(
		"INSERT INTO `%s` "
		"(`Ident`, `Werte`) "
		"VALUES (%d, '%s')",
		String(TABLE), data.ident, s.c_str());

	memo->Lines->Add("");
	memo->Lines->Add(q);
	memo->Lines->Add("");

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können 
		return loadByIdent(data.ident);
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
