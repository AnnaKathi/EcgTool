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
//! Kapselt verschiedene MySql-Funktionalitäten
/*! Die Klasse cMySql bietet verschiedene MySql-Funktionalitäten an.
 */
class PACKAGE cMySql : public cBase
	{
public:
	cMySql();  //!< Konstruktor für cMySql
	~cMySql(); //!< Destruktor für cMySql

	//! Lädt die Daten der Tabelle ecg.ecgdata
	/*! Lädt die Daten der Tabelle ecg.ecgdata
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool 		loadData();
	
	//! Lädt die nächste MySql-Zeile in den Speichern
	/*! Nach dem Ausführen von loadData() kann mit next() die nächste Datenzeile
	 *  der MySql-Tabelle cg.ecgdata in den Speicher geladen werden.
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		nextRow();

	//! Speichert einen vollständigen ECG-Datensatz ab (aktuell noch Testversion)
	/*! Eine ECG-Datenstruktur wird in die Tabelle ecg.ecgdata gespeichert. Die 
	 *  Datenstruktur muss vorab manuell gefüllt werden.
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		saveToDbase();

	//! Löscht einen Datensatz
	/*! Löscht den Datensatz 'ident'
	 *  /param (int) ident, ID des zu löschenden Datensatzes
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		deleteDataByIdent(int ident);

__property int num_rows  = { read=get_num_rows }; //!< Anzahl geladener Zeilen
__property sMySqlRow row = { read=get_row };  //!< Ergebniszeile aus einer Abfrage
__property sMySqlData& mysql_data = { read=get_mysql_data }; //!< Datenstruktur die abgespeichert werden soll

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
