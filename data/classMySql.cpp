//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "inc/mysql/libmysql.lib"
//---------------------------------------------------------------------------
#define DATABASE "ecg"
#define ECGTABL  "ecgdata"
//---------------------------------------------------------------------------
cMySql::cMySql()
	: fcsv(new cCsv)
	{
	char path[MAX_PATH];
	strcpy(path, Application->ExeName.c_str());
	char* pt = strrchr(path, '\\');
	if (pt != 0)
		*pt = 0;

	String file = String(path) + "\\EcgTool.ini";
	Ini = new TIniFile(file);

	bMySqlConnected = false;
	}
//---------------------------------------------------------------------------
cMySql::~cMySql()
	{
	if (fcsv) delete fcsv;
	if (Ini)  delete Ini;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySql::saveToDbase()
	{
	//-- zu speichernde Daten �berpr�fen
	if (mysql_data.array.size() <= 0)
		return fail(1, "Das �bergebene Datenarray ist leer");

	if (mysql_data.name == "")
		return fail(1, "Es wurde kein Name �bergeben");

	if (mysql_data.pos <= 0)
		return fail(1, "Es wurde keine Position �bergeben");

	//-- MySql-Datenbank �ffnen
	if (!getLoginData())
		return fail(2, ferror.c_str());

	if (!OpenMysql())
		return fail(3, ferror.c_str());

	//-- Daten speichern
	if (!UpdateMysql())
		return fail(4, ferror.c_str());

	//-- MySql-Datenbank schlie�en
	CloseMysql();

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::loadData()
	{
	if (!getLoginData())
		return fail(2, ferror.c_str());

	if (!OpenMysql())
		return fail(3, ferror.c_str());

	String q = "select * from " + String(ECGTABL);
	if (mysql_real_query(fcon, q.c_str(), q.Length()) != 0)
		{
		ferror = "Fehler in SELECT * : " + String(mysql_error(fcon));
		return false;
		}

	if ((fres = mysql_store_result(fcon)) == NULL)
		{
		ferror = "Fehler in STORE_RESULT : " + String(mysql_error(fcon));
		return false;
		}

	if (mysql_num_rows(fres) == 0)
		{
		ferror = "keine Daten gefunden";
		return false;
		}
	else
		return true;
	}
//---------------------------------------------------------------------------
bool cMySql::nextRow()
	{
	if (!bMySqlConnected)
		return fail(9, "MySql-Verbindung wurde nicht initialisiert");

	if (fsql == NULL || fcon == NULL)
		return fail(9, "MySql-Verbindung ist nicht initialisiert");


	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fsqlrow.ident = atoi(frow[0]);
	sprintf(fsqlrow.name, "%.123s", frow[1]);
	fsqlrow.pos = (ePosition) atoi(frow[2]); //todo ePosition umwandeln in Text

	fsqlrow.werte[0] = atof(frow[3]);
	fsqlrow.werte[1] = atof(frow[4]);
	fsqlrow.werte[2] = atof(frow[5]);
	fsqlrow.werte[3] = atof(frow[6]);
	fsqlrow.werte[4] = atof(frow[7]);

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   private Funktionen   *******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySql::getLoginData()
	{
	//erst einmal als Klartext aus Ini-Datei lesen, todo: umstellen auf Dialog?
	serv = Ini->ReadString("MySql", "Server", "");
	user = Ini->ReadString("MySql", "User",   "");
	pass = Ini->ReadString("MySql", "Pwd",    "");
	data = Ini->ReadString("MySql", "Data",   "");

	//Passwort wird erst einmal im Klartext hinterlegt
	//todo verschl�sseln und dann hier decrypten
	port = Ini->ReadInteger("MySql", "Port", 0);

	//todo if...
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::OpenMysql()
	{
	if ((fsql = mysql_init(NULL)) == 0)
		{
		ferror = "Das MYSQL-System kann nicht initialisiert werden!";
		return false;
		}

	fcon = mysql_real_connect(
		fsql,
		serv.c_str(),
		user.c_str(),
		pass.c_str(),
		data.c_str(),
		port,
		NULL,
		0);

	if (fcon == NULL)
		{
		bMySqlConnected = false;
		ferror = "Fehler beim Verbindungsaufbau! MYSQL meldet: " + String(mysql_error(fsql));
		return false;
		}
	else
		{
		bMySqlConnected = true;
		return true;
		}
	}
//---------------------------------------------------------------------------
void cMySql::CloseMysql()
	{
	bMySqlConnected = false;
	mysql_close(fsql);
	}
//---------------------------------------------------------------------------
bool cMySql::UpdateMysql()
	{
	//todo: implementieren
	/*INSERT INTO `ecg`.`ecgdata`
		(`Name`, `Position`, `T1`, `T2`, `T3`, `T4`, `T5`)
	  VALUES
		('Manuela', '2', 0.146, 5.187, 1.999, 0.164, 1.976);
	*/

	char q[1024];
	sprintf(q, "INSERT INTO `%s`.`%s` "
		"(`Name`, `Position`, `T1`, `T2`, `T3`, `T4`, `T5`) "
		"VALUES ('%s', '%d', %.6f, %.6f, %.6f, %.6f, %.6f)",
		DATABASE, ECGTABL,
		mysql_data.name, mysql_data.pos,
		mysql_data.array[0][1],
		mysql_data.array[1][1],
		mysql_data.array[2][1],
		mysql_data.array[3][1],
		mysql_data.array[4][1]);

	String query = String(q);
	if (mysql_real_query(fcon, query.c_str(), query.Length()) != 0)
		{
		ferror = "Fehler in SELECT * : " + String(mysql_error(fcon));
		return false;
		}

	return true;
	}
//---------------------------------------------------------------------------
bool cMySql::deleteDataByIdent(int ident)
	{
	//DELETE FROM `ecg`.`ecgdata` WHERE  `Ident`=33;
	if (ident <= 0)
		return fail(1, "Es wurde kein Ident �bergeben");

	char q[1024];
	sprintf(q, "DELETE FROM `%s`.`%s` WHERE  `Ident`=%d", DATABASE, ECGTABL, ident);

	String query = String(q);
	if (mysql_real_query(fcon, query.c_str(), query.Length()) != 0)
		return fail(2, "Fehler in SELECT * : " + String(mysql_error(fcon)));

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sMySqlRow cMySql::get_row()
	{
	return fsqlrow;
	}
//---------------------------------------------------------------------------
int	cMySql::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
sMySqlData& cMySql::get_mysql_data()
	{
	return fsqldata;
	}
//---------------------------------------------------------------------------

