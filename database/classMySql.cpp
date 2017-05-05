//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cMySql::cMySql()
	{
	fwork     = new cMySqlWork();
	fecg      = new cMySqlEcgData(*fwork);
	fecgneu	  = new cMySqlEcg(*fwork);
	fpeople   = new cMySqlPeople(*fwork);

	fdiseases = new cMySqlDescDb(*fwork, "diseases");
	forte     = new cMySqlDescDb(*fwork, "orte");

	//old: fdiseases = new cMySqlDiseases(*fwork);
	}
//---------------------------------------------------------------------------
cMySql::~cMySql()
	{
	if (fwork)     delete fwork;
	if (fecg)      delete fecg;
	if (fecgneu)   delete fecgneu;
	if (fpeople)   delete fpeople;
	if (fdiseases) delete fdiseases;
	if (forte)	   delete forte;
	}
//---------------------------------------------------------------------------
bool cMySql::create()
	{
	//erstellt die komplette Datenbank
	if (!fwork->script("create_all_databases"))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::drop()
	{
	//falls noch eine ecg-Datenbank vorhanden ist -> löschen
	if (dbExists())
		{
		if (Application->MessageBox(
			ftools.fmt(
				"Achtung: Die Datenbank 'ecg' wird mit allen zugehörigen "
				"Tabellen und Daten gelöscht. Dieser Prozess kann nicht "
				"zurückgenommen werden!\n\n"
				"Bist Du sicher, dass Du die Datenbank wirklich löschen willst? ").c_str(),
			"DATENBANK LÖSCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		if (Application->MessageBox(
			ftools.fmt("Bist Du wirklich, wirklich sicher?\n(Vermeidung PN-Fehler)").c_str(),
			"DATENBANK LÖSCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		String q = "DROP DATABASE `ecg`";
		if (!fwork->send(q))
			return fail(error_code, error_msg);

		Application->MessageBox("Datenbank gelöscht", "Erfolgreich", MB_OK);
		}

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::dbExists()
	{
	String q = "SHOW DATABASES like 'ecg'";
	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);

	if (fwork->num_rows > 0) //Datenbank gibt es
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
bool cMySql::tabExists(String tabelle)
	{
	String q = ftools.fmt("SHOW TABLE like '%s'", tabelle);

	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);

	if (fwork->num_rows > 0) //Tabelle gibt es
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
bool cMySql::open()
	{
	if (!fwork->open())
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::openWithoutDb()
	{
	if (!fwork->openWithoutDb())
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
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
cMySqlEcg& cMySql::get_ecg_neu()
	{
	return *fecgneu;
	}
//---------------------------------------------------------------------------
cMySqlPeople& cMySql::get_people()
	{
	return *fpeople;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_diseases()
	{
	return *fdiseases;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_orte()
	{
	return *forte;
	}
//---------------------------------------------------------------------------

