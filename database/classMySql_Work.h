//---------------------------------------------------------------------------
#ifndef classMySql_WorkH
#define classMySql_WorkH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <IniFiles.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classTools.h"
#include "../inc/mysql/mysql.h"
//---------------------------------------------------------------------------
class PACKAGE cMySqlWork : public cBase
	{
public:
	cMySqlWork();
	~cMySqlWork();

	bool 		open();
	bool 		openWithoutDb();
	bool		close();

	bool		isReady();       //wurde open() erfolgreich durchgef�hrt?
	bool		query(String q); //f�hrt ein store_result durch
	bool		send(String q);  //f�hrt nur das Kommando aus (z.B. delete) ohne store_result
	bool 		script(String script_name); //f�hrt eine sql-Datei aus
	MYSQL_RES*  getResult();     //Resultate zur�ckgeben

	//-- Daten laden
	bool		loadTable(String tab, String order = "");

	bool		listIn(TListView* lv);

__property int num_rows = { read=get_num_rows };

private:
	cTools			ftools;

	//SQL-Daten
	MYSQL*      	fsql;
	MYSQL*      	fcon;
	MYSQL_RES*  	fres;
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			bMySqlConnected;

	};
//---------------------------------------------------------------------------
#endif
