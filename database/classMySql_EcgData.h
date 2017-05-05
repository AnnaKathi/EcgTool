//---------------------------------------------------------------------------
#ifndef classMySql_EcgDataH
#define classMySql_EcgDataH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sEcgData
	{
	int			ident;
	int			session;
	int			person;
	int			platzierung;
	int			state;
	ePosition	pos;
	double		werte[3000];
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlEcgData : public cBase
	{
public:
	cMySqlEcgData(cMySqlWork& worker);
	~cMySqlEcgData();

	bool	loadTable(); //lädt die ganze Tabelle
	bool	loadByPerson(int person); //lädt nur die Daten von Person

	bool	nextRow();

	bool	deleteByIdent(int ident);

	//-- Datenfelder
	int 	getSize();


__property sEcgData row = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
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
