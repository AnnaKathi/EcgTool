//---------------------------------------------------------------------------
#ifndef classMySqlH
#define classMySqlH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include "definitions.h"
#include "../basics/classBase.h"
#include "../basics/classCsv.h"
#include "../inc/mysql/mysql.h"
//---------------------------------------------------------------------------
struct sMySqlData
	{
	iarray_t	array; //EKG-Stream
	char		name[64];
	ePosition	pos; //liegend, sitzend, stehend, gehend -> enum ePosition
	};
//---------------------------------------------------------------------------
struct sMySqlRow
	{
	int			ident;
	char		name[128];
	ePosition	pos;
	double		werte[5];
	};
//---------------------------------------------------------------------------
class PACKAGE cMySql : public cBase
	{
public:
	cMySql();
	~cMySql();

	bool 		loadData();
	bool		nextRow();

	bool		saveToDbase();

	bool		deleteDataByIdent(int ident);

__property int num_rows  = { read=get_num_rows };
__property sMySqlRow row = { read=get_row };  //eine Ergebniszeile aus einer Abfrage
__property sMySqlData& mysql_data = { read=get_mysql_data }; //die Daten die abgespeichert werden sollen

private:
	TIniFile*	Ini;
	cCsv*		fcsv;

	bool		bMySqlConnected;
	MYSQL*      fsql;
	MYSQL*      fcon;
	MYSQL_RES*  fres;
	MYSQL_ROW	frow;
	int			get_num_rows();

	//eine Ergeniszeile aus einer MySql-Abfrage, z.B. für nextRow()
	sMySqlRow	fsqlrow;
	sMySqlRow 	get_row();

	// MySql-Daten, die vom Aufrufenden übergeben werden (array mit Werten, Name, usw)
	sMySqlData	fsqldata;
	sMySqlData&	get_mysql_data();

	String		ferror;

	String		serv;
	String		user;
	String		pass;
	String		data;
	int         port;

	bool		getLoginData();
	bool 		OpenMysql();
	void 		CloseMysql();
	bool 		UpdateMysql();
	};
//---------------------------------------------------------------------------
#endif
