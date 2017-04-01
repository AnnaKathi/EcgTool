//---------------------------------------------------------------------------
#ifndef classMySql_PeopleH
#define classMySql_PeopleH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "definitions.h"
#include "../basics/classBase.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sPeople
	{
	int			ident;
	char		vorname[128];
	char		nachname[128];
	int			diseases[16]; //Liste von Herzerkrankungen
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlPeople : public cBase
	{
public:
	cMySqlPeople(cMySqlWork& worker);
	~cMySqlPeople();

	//-- Daten laden
	bool	loadTable(); //lädt die gesamte Tabelle
	bool	nextRow();

	//-- Daten feststellen
	String	getNameOf(int person);
	String	getDiseasesOf(int person);

	//-- Daten löschen
	bool 	deleteByIdent(int ident);

__property sPeople row  = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	sPeople			fdata;
	sPeople			get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);
	};
//---------------------------------------------------------------------------
#endif
