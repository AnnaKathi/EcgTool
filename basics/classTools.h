//---------------------------------------------------------------------------
#ifndef classToolsH
#define classToolsH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include "../definitions.h"
#include "../basics/classBase.h"
//---------------------------------------------------------------------------
//! bietet verschiedene Grundfunktionalit�ten an
/*! Die Klasse cTools bietet verschiedenen Grundfunktionalit�ten an:\r\n
 * <ul><li>Datenkonverter 'Position' (String <-> enum ePosition)
 * <li>Positions-String in ComboBox laden
 * <li>Formular speichern und laden</ul> 
 */
class PACKAGE cTools
	{
public:
	//! Konstruktor f�r cTools
	cTools();

	//-------------------------------------------------------------------------
	//--- Formulare laden und speichern ---------------------------------------
	//-------------------------------------------------------------------------

		//! Dateipfad der Exe-Datei finden
		/*! Gibt den Pfad der Exe-Datei zur�ck.
		 *  \return (String) Pfad der Exe-Datei
		 */
		String		GetPath();

		//! Dateiname der Projekt-Inifile erstellen
		/*! Gibt den Namen der Projekt-Inifile zur�ck. Diese liegt im gleichen
		 *  Verzeichnis wie die exe-Datei.
		 *  \return (String) Dateiname der Ini-File
		 */
		String		GetIniFile();

		//! Formular laden (Position, Ausdehnung, Felder, usw.)
		/*! L�dt die Daten des �bergebenen Formular aus der Projekt-Inifile:\r\n
		 *  <ul><li>Position (Left und Top)
		 *  <li>Ausdehnung (Width und Height)
		 *  <li>Inhalte der Edit-Felder
		 *  <li>ItemIndex der ComboBoxen
		 *  <li>Status der Checkboxen (checked)
		 *  \param (TForm) Formular das gespeichert werden soll
		 */
		void 		FormLoad(TForm* fm);

		//! Formular speichern (Position, Ausdehnung, Felder, usw.)
		/*! Speichert die Daten des �bergebenen Formular in die Projekt-Inifile:\r\n
		 *  <ul><li>Position (Left und Top)
		 *  <li>Ausdehnung (Width und Height)
		 *  <li>Inhalte der Edit-Felder
		 *  <li>ItemIndex der ComboBoxen
		 *  <li>Status der Checkboxen (checked)
		 *  \param (TForm) Formular das gespeichert werden soll
		 */
		void 		FormSave(TForm* fm);

		void		ListViewLoad(TForm* fm, TListView* lv);
		void		ListViewSave(TForm* fm, TListView* lv);

	//-------------------------------------------------------------------------
	//--- Bildschirm- und Printmeldungen --------------------------------------
	//-------------------------------------------------------------------------

		void		ErrBox(char* msg, ...);
		void		MsgBox(char* msg, ...);

	//-------------------------------------------------------------------------
	//--- String-Funktionen ---------------------------------------------------
	//-------------------------------------------------------------------------

		String		fmt(char* msg, ...);
		int			replace(String& str, String old, String neu);
		iarray_t	TextToArray(String text, String delim);
		String		ArrayToText(iarray_t array, String delim);
	//-------------------------------------------------------------------------
	//--- Sonstige Funktionen -------------------------------------------------
	//-------------------------------------------------------------------------

		//! Feststellen ob das Programm auf einem Heimrechner ausgef�hrt wird (= im Debugmodus)
		/*! �berpr�ft ob der ausf�hrende Rechner in der Liste der "HomeStations"
		 *  vorhanden ist. Falls ja, handelt es sich um einen "HeimRechner", d.h.
		 *  das Programm l�uft im Debugmodus.\r\n
		 *  Kann verwendet werden um ggf. Testfunktionen o.�. an oder aus zu schalten.
		 *  /return true wenn es sich beim ausf�hrenden Rechner um einen Heimrechner
		 *		handelt, sonst false
		 */
		bool		IsDebug();

		String		GetComputer();
		String		GetComputerBS();
		String 		GetComputerProzessor();

		bool 		Log(String msg);

private:
	};
//---------------------------------------------------------------------------
#endif
