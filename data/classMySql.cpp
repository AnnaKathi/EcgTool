//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cMySql::cMySql()
	: fcsv(new cCsv)
	{
	}
//---------------------------------------------------------------------------
cMySql::~cMySql()
	{
	if (fcsv) delete fcsv;
	}
//---------------------------------------------------------------------------
bool cMySql::saveToDbase(String name, String pos, iarray_t array)
	{
	if (name == "") return fail(1, "Es wurde kein Name übergeben");
	if (pos  == "") return fail(1, "Es wurde keine Position übergeben");
	if (array.size() <= 0) return fail(1, "Das übergebene Datenarray ist leer");

	//todo, Datenarray in MySql-Datenbank speichern

	//todo, Name usw nicht auf Übergabeparameter auslegen, sondern via struct übergeben o.ä.
	
	return ok();
	}
//---------------------------------------------------------------------------
