//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

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
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcgData::save(sEcgData data)
	{
	//Row muss vorher gesetzt sein
	String s = "";
	char feld[64]; double wert;
	for (int i = 0; i < 10; i++)
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
	if (!getRow())    return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::getLast()
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` ORDER BY Ident DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!getRow())    return false;

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
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
/******************   Funktionen: Datenfelder   ****************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cMySqlEcgData::getSize()
	{
	if (!loadTable())
		{
		fail(fwork->error_code, fwork->error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::getRow()
	{
	//aus row die fdata-Werte lesen
	if (frow == NULL) return false;

	fdata.ident    = atoi(frow[0]);
	fdata.session  = atoi(frow[1]);
	fdata.person   = atoi(frow[2]);
	fdata.position = atoi(frow[3]);
	fdata.state    = atoi(frow[4]);
	fdata.lage     = atoi(frow[5]);

	//Die EKG-Werte sind als semikolon-getrennter Longtext gespeichert
	String longwerte = String(frow[6]);
	int pos; String ww;
	int ix = 0;
	while ((pos = longwerte.Pos(";")) > 0)
		{
		ww = longwerte.SubString(0, pos-1);
		longwerte = longwerte.SubString(pos+1, 9999);

		fdata.werte[ix] = ww.ToDouble();
		ix++;
		}

	return true;
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