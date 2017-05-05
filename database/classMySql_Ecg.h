//---------------------------------------------------------------------------
#ifndef classMySql_EcgH
#define classMySql_EcgH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classTools.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sEcg
	{
	int			ident;
	double		werte[3000];
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlEcg : public cBase
	{
public:
	cMySqlEcg(cMySqlWork& worker);
	~cMySqlEcg();

	bool	loadTable(); //lädt die ganze Tabelle
	bool	loadByIdent(int ident); //lädt nur einen Datensatz

	bool	nextRow();

	bool	deleteByIdent(int ident);

	bool	save(sEcg data, TMemo* meo);

	//-- Datenfelder
	int 	getSize();

__property sEcg row = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	cTools			ftools;
	sEcg			fdata;
	sEcg			get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);

	};
//---------------------------------------------------------------------------
#endif
