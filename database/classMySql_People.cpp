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
bool cMySqlPeople::get(int person)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `Ident` = " + String(person);
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.vorname,  "%.127s", frow[1]);
	sprintf(fdata.nachname, "%.127s", frow[2]);

	return true;
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
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.vorname,  "%.127s", frow[1]);
	sprintf(fdata.nachname, "%.127s", frow[2]);

	//todo Erkrankungern laden
	//String test = getDiseasesOf(fdata.ident);

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::getLast()
	{
	String q = "SELECT * FROM " + String(TABLE) + " ORDER BY Ident DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.vorname,  "%.127s", frow[1]);
	sprintf(fdata.nachname, "%.127s", frow[2]);

	return true;
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
	q+= "(`Vorname`, `Nachname`) VALUES ";
	q+= "(";
	q+= "'" + String(data.vorname) + "', ";
	q+= "'" + String(data.nachname) + "'";
	q+= ")";

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten k�nnen (letzten Datensatz nach Ident laden)
		return getLast();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::update(sPeople data)
	{
	//UPDATE `ecg`.`subjects` SET `Vorname`='Otto', `Nachname`='Mustermann' WHERE  `Ident`=7;
	String q = "UPDATE " + String(TABLE) + " SET ";
	q+= "Vorname='"  + String(data.vorname)  + "',";
	q+= "Nachname='" + String(data.nachname) + "' ";
	q+= "WHERE Ident=" + String(data.ident);

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::addDisease(int person, int disease)
	{
	String q = "SELECT * FROM " + String(SUBDIS) + " WHERE";
	q+= " PersIdent = " + String(person) + " AND ";
	q+= " DisIdent = "  + String(disease);

	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);

	if (fwork->num_rows > 0)
		{
		//die Erkrankung ist bei der person bereits hinterlegt
		//nichts machen, einfach rausspringen
		return true;
		}
	else
		{
		//Erkrankung zur Person abspeichern
		//insert into subject_disease (PersIdent, DisIdent) VALUES (1, 7)
		q = "INSERT INTO " + String(SUBDIS) + "(PersIdent, DisIdent) ";
		q+= "VALUES (" + String(person) + "," + String(disease) + ")";

		if (!fwork->send(q))
			return fail(fwork->error_code, fwork->error_msg);
		}
		
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

	fres = res_old; //Position zur�cksetzen
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
		" GROUP BY DisIdent"; //zur Sicherheit, sollte nicht n�tig sein
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

	fres = res_old; //Position zur�cksetzen
	return arr;
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
/******************   Funktionen: l�schen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlPeople::deleteByIdent(int ident)
	{
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `Ident` = " + String(ident);
	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Evtl zugeh�rige Erkrankungen l�schen
		String q = "DELETE FROM " + String(SUBDIS);
		q+= " WHERE PersIdent = " + String(ident);
		if (!fwork->send(q))
			return fail(fwork->error_code, fwork->error_msg);
		}
		
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
