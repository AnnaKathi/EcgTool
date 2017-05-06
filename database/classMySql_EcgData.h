//---------------------------------------------------------------------------
#ifndef classMySql_EcgDataH
#define classMySql_EcgDataH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classTools.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sEcgData
	{
	int			ident;
	int			session;
	int			person;
	int			position;
	int			state;
	int			lage;
	double		werte[3000];
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlEcgData : public cBase
	{
public:
	cMySqlEcgData(cMySqlWork& worker);
	~cMySqlEcgData();

	bool 	save(sEcgData data);

	bool	loadTable(); //lädt die ganze Tabelle
	bool	loadByPerson(int person); //lädt nur die Daten von Person
	bool 	getLast();

	bool	nextRow();

	bool	deleteByIdent(int ident);

	//-- Datenfelder
	int 	getSize();
	bool 	getRow();


__property sEcgData row = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	cTools			ftools;
	sEcgData		fdata;
	sEcgData		get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);
	};
//---------------------------------------------------------------------------
#endif
