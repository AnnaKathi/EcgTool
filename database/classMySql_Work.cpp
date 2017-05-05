//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

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
	//todo verschlüsseln und dann hier decrypten

	//todo Werte prüfen.....

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
bool cMySqlWork::openWithoutDb()
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
	//String data = Ini->ReadString("MySql", "Data",   "");

	int port = Ini->ReadInteger("MySql", "Port", 0);
	delete Ini;

	//Passwort wird erst einmal im Klartext hinterlegt
	//todo verschlüsseln und dann hier decrypten

	//todo Werte prüfen.....

	if ((fsql = mysql_init(NULL)) == 0)
		return fail(1, "Das MYSQL-System kann nicht initialisiert werden!");

	fcon = mysql_real_connect(
		fsql,
		serv.c_str(),
		user.c_str(),
		pass.c_str(),
		NULL,
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
		return fail(2, ftools.fmt("Fehler in QUERY: %d", mysql_error(fcon)));

	if ((fres = mysql_store_result(fcon)) == NULL)
		return fail(2, ftools.fmt("Fehler in STORE_RESULT: %d", mysql_error(fcon)));

	if (mysql_num_rows(fres) == 0)
		return ok(); //not: fail(2, msg.c_str());
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlWork::send(String q)
	{
	if (!bMySqlConnected)
		return fail(3, "Datenbank wurde nicht initialisiert");

	if (mysql_real_query(fcon, q.c_str(), q.Length()) != 0)
		return fail(3, ftools.fmt("Fehler in QUERY: %s", mysql_error(fcon)));

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlWork::script(String script_name)
	{
	//Datei wird im Unterverzeichnis "script" erwartet!
	char script[MAX_PATH];
	sprintf(script, "%s\\mysql_scripts\\script_%s.sql", ftools.GetPath(), script_name);
	FILE* fp = fopen(script, "r");
	if (fp == NULL)
		return fail(4, ftools.fmt("Skript-Datei konnte nicht gefunden werden (%s)", script));

	String q = "";
	String line;
	char rowbuf[1024];
	bool fehler = false;
	while (fgets(rowbuf, sizeof(rowbuf)-1, fp) != NULL)
		{
		line = String(rowbuf);
		ftools.replace(line, "\n", "");
		line = line.Trim();
		if (line == "")
			{
			//Befehl zuende -> absenden
			if (!send(q))
				{
				fehler = true;
				break;
				}

			q = "";
			}
		else
			{
			//Befehl noch nicht vollständig
			q += line;
			}
		}

	fclose(fp);

	if (!fehler && q != "")
		{
		//es gibt noch einen nicht abgesendeten Befehl
		if (!send(q))
			fehler = true;
		}

	if (fehler)
		return fail(error_code, error_msg);

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
