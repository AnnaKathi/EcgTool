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
	iarray_t	array_werte;
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlEcgData : public cBase
	{
public:
	cMySqlEcgData(cMySqlWork& worker);
	~cMySqlEcgData();

	bool 	save(sEcgData data);

	bool	loadTable(); //l�dt die ganze Tabelle
	bool	loadByIdent(int ecg);
	bool	loadByPerson(int person); //l�dt nur die Daten von Person
	bool	loadBySession(int session);

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

	bool			LongstrToData(String str, sEcgData& data);
	String 			DataToLongtext(sEcgData data);

	bool			load(String condition);

	//-- MySql-Variablen und -Funktionen
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
