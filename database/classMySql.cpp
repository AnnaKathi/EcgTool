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
	fpeople   = new cMySqlPeople(*fwork);
	fsessions = new cMySqlSession(*fwork);

	fdiseases    = new cMySqlDescDb(*fwork, "diseases");
	forte        = new cMySqlDescDb(*fwork, "orte");
	fresearchers = new cMySqlDescDb(*fwork, "researchers");
	flagen       = new cMySqlDescDb(*fwork, "lagen");
	fstates      = new cMySqlDescDb(*fwork, "states");
	fpositions   = new cMySqlDescDb(*fwork, "positions");
	falgorithms  = new cMySqlDescDb(*fwork, "algorithms");
	}
//---------------------------------------------------------------------------
cMySql::~cMySql()
	{
	if (fwork)     delete fwork;
	if (fecg)      delete fecg;
	if (fpeople)   delete fpeople;
	if (fsessions) delete fsessions;

	if (fdiseases)    delete fdiseases; 		if (forte)	 delete forte;
	if (fresearchers) delete fresearchers;		if (flagen)  delete flagen;
	if (fpositions)   delete fpositions;		if (fstates) delete fstates;
	if (falgorithms)  delete (falgorithms);
	}
//---------------------------------------------------------------------------
bool cMySql::create()
	{
	//erstellt die komplette (leere) Datenbank
	if (!fwork->script("create_all_databases"))
		return fail(fwork->error_code, fwork->error_msg);

	if (Application->MessageBox(
		ftools.fmt(
			"M�chtest Du die Datenbank mit Dummy-Daten f�r die Grunddefinitionen "
			"f�llen lassen (Erkrankungen, Orte, Untersuchender, Lagen, Stati, "
			"Positionen und Algorithmen) ?").c_str(),
		"Datenbank f�llen ?",
		MB_YESNO) == IDYES)
		{
		//f�llt die Datenbank mit Dummy-Datens�tzen
		if (!fwork->script("insert_dummy_data_basic"))
			return fail(fwork->error_code, fwork->error_msg);
		}

	if (Application->MessageBox(
		ftools.fmt(
			"M�chtest Du die Datenbank mit Dummy-Daten f�r Sessions "
			"f�llen lassen (Personen, Seesions, EKG-Daten) ?").c_str(),
		"Datenbank f�llen ?",
		MB_YESNO) == IDYES)
		{
		//f�llt die Datenbank mit Dummy-Datens�tzen
		if (!fwork->script("insert_dummy_data_sessions"))
			return fail(fwork->error_code, fwork->error_msg);
		}

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::drop()
	{
	//falls noch eine ecg-Datenbank vorhanden ist -> l�schen
	if (dbExists())
		{
		if (Application->MessageBox(
			ftools.fmt(
				"Achtung: Die Datenbank 'ecg' wird mit allen zugeh�rigen "
				"Tabellen und Daten gel�scht. Dieser Prozess kann nicht "
				"zur�ckgenommen werden!\n\n"
				"Bist Du sicher, dass Du die Datenbank wirklich l�schen willst? ").c_str(),
			"DATENBANK L�SCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		if (Application->MessageBox(
			ftools.fmt("Bist Du wirklich, wirklich sicher?\n(Vermeidung PN-Fehler)").c_str(),
			"DATENBANK L�SCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		String q = "DROP DATABASE `ecg`";
		if (!fwork->send(q))
			return fail(error_code, error_msg);

		Application->MessageBox("Datenbank gel�scht", "Erfolgreich", MB_OK);
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
cMySqlPeople& cMySql::get_people()
	{
	return *fpeople;
	}
//---------------------------------------------------------------------------
cMySqlSession& cMySql::get_sessions()
	{
	return *fsessions;
	}
//---------------------------------------------------------------------------
//-- description databases --------------------------------------------------
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
cMySqlDescDb& cMySql::get_researchers()
	{
	return *fresearchers;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_lagen()
	{
	return *flagen;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_states()
	{
	return *fstates;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_positions()
	{
	return *fpositions;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_algorithms()
	{
	return *falgorithms;
	}
//---------------------------------------------------------------------------

