//---------------------------------------------------------------------------
#ifndef classMySqlH
#define classMySqlH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classCsv.h"
#include "../inc/mysql/mysql.h"
//---------------------------------------------------------------------------
enum ePosition
	{
	posNone = 0,
	posLiegend,
	posSitzend,
	posStehend,
	posGehend
	};
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

	sMySqlData	mysql_data; //todo getter und setter machen

	bool 		LoadData();
	bool		nextRow();

	bool		saveToDbase();

__property sMySqlRow row = { read=get_row };
__property int num_rows  = { read=get_num_rows };

private:
	TIniFile*	Ini;
	cCsv*		fcsv;

	bool		bMySqlConnected;
	MYSQL*      fsql;
	MYSQL*      fcon;
	MYSQL_RES*  fres;
	MYSQL_ROW	frow;
	sMySqlRow	fsqlrow;
	sMySqlRow 	get_row();
	int			get_num_rows();

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
