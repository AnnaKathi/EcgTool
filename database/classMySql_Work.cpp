//---------------------------------------------------------------------------
#pragma hdrstop

#include "classMySql_Work.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "inc/mysql/libmysql.lib"
//---------------------------------------------------------------------------
cMySqlWork::cMySqlWork()
	{
	}
//---------------------------------------------------------------------------
cMySqlWork::~cMySqlWork()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlWork::open()
	{
	char path[MAX_PATH];
	strcpy(path, Application->ExeName.c_str());
	char* pt = strrchr(path, '\\');
	if (pt != 0)
		*pt = 0;

	String file = String(path) + "\\EcgTool.ini";
	TIniFile* Ini = new TIniFile(file);

	bMySqlConnected = false;

	//erst einmal als Klartext aus Ini-Datei lesen, todo: umstellen auf Dialog?
	String serv = Ini->ReadString("MySql", "Server", "");
	String user = Ini->ReadString("MySql", "User",   "");
	String pass = Ini->ReadString("MySql", "Pwd",    "");
	String data = Ini->ReadString("MySql", "Data",   "");

	int port = Ini->ReadInteger("MySql", "Port", 0);
	delete Ini;

	//Passwort wird erst einmal im Klartext hinterlegt
	//todo verschl�sseln und dann hier decrypten

	//todo Werte pr�fen.....

	if ((fsql = mysql_init(NULL)) == 0)
		return fail(1, "Das MYSQL-System kann nicht initialisiert werden!");

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
		return fail(1, "Fehler beim Verbindungsaufbau! MYSQL meldet: " + String(mysql_error(fsql)));
	else
		{
		bMySqlConnected = true;
		return ok();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlWork::close()
	{
	bMySqlConnected = false;
	mysql_close(fsql);
	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlWork::isReady()
	{
	if (!bMySqlConnected) return false;
	if (fsql == NULL || fcon == NULL) return false;
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Abfragen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlWork::query(String q)
	{
	if (!bMySqlConnected)
		return fail(2, "Datenbank wurde nicht initialisiert");

	if (mysql_real_query(fcon, q.c_str(), q.Length()) != 0)
		{
		String msg = "Fehler in QUERY : " + String(mysql_error(fcon));
		return fail(2, msg.c_str());
		}

	if ((fres = mysql_store_result(fcon)) == NULL)
		{
		String msg = "Fehler in STORE_RESULT : " + String(mysql_error(fcon));
		return fail(2, msg.c_str());
		}

	if (mysql_num_rows(fres) == 0)
		{
		String msg = "keine Daten gefunden";
		return ok(); //not: fail(2, msg.c_str());
		}
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlWork::send(String q)
	{
	if (!bMySqlConnected)
		return fail(3, "Datenbank wurde nicht initialisiert");

	if (mysql_real_query(fcon, q.c_str(), q.Length()) != 0)
		{
		String msg = "Fehler in QUERY : " + String(mysql_error(fcon));
		return fail(3, msg.c_str());
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Daten laden   ****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlWork::loadTable(String tab, String order) //order ist mit "" vorbesetzt
	{
	String q = "SELECT * FROM " + String(tab);
	if (order != "") q += " ORDER BY " + order;

	if (!query(q))
		return fail(error_code, error_msg);
	else
		{
		fres = getResult();
		return ok();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
MYSQL_RES* cMySqlWork::getResult()
	{
	return fres;
	}
//---------------------------------------------------------------------------
int cMySqlWork::get_num_rows()
	{
	 return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
