//---------------------------------------------------------------------------
#ifndef classMySql_DiseasesH
#define classMySql_DiseasesH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sDiseases
	{
	int			ident;
	char		bez[128];
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlDiseases : public cBase
	{
public:
	cMySqlDiseases(cMySqlWork& worker);
	~cMySqlDiseases();

	//-- Daten laden
	bool	loadTable(String order = ""); //lädt die ganze Tabelle
	bool	nextRow();

	//-- Daten speichern
	bool 	insert(sDiseases data);
	bool 	update(sDiseases data);

	//-- Daten feststellen
	String 	getNameOf(int disease); //eine Bezeichnugn einer Erkrankung feststellen
	sarray_t getNamesOf(sarray_t idents); //Liste mit Bez. auffüllen
	int 	getSize();

	//-- Daten anzeigen
	bool	listInCombo(TComboBox* cb, int mode = 0);

	//-- Daten löschen
	bool	deleteByIdent(int ident);

__property sDiseases row = { read=get_data };
__property int num_rows  = { read=get_num_rows };

private:
	sDiseases		fdata;
	sDiseases   	get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	};
//---------------------------------------------------------------------------
#endif
