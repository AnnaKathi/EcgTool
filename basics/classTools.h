//---------------------------------------------------------------------------
#ifndef classToolsH
#define classToolsH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include "..\definitions.h"
//---------------------------------------------------------------------------
//! bietet verschiedene Grundfunktionalitäten an
/*! Die Klasse cTools bietet verschiedenen Grundfunktionalitäten an:\r\n
 * <ul><li>Datenkonverter 'Position' (String <-> enum ePosition)
 * <li>Positions-String in ComboBox laden
 * <li>Formular speichern und laden</ul> 
 */
class cTools
	{
public:
	//! Konstruktor für cTools
	cTools();

	//-------------------------------------------------------------------------
	//--- Datenkonverter ------------------------------------------------------
	//-------------------------------------------------------------------------
		//! Aus einem Positions-Enum den zugehörigen String erstellen
		/*! Aus dem übergebenen enum der Position (ePosition) wird der zugehörige
		 *  String generiert (z.B. posLiegend -> "liegend").
		 *  \param (ePosition) Auflistung der Position
		 *	\return (String) Bezeichnung der Position
		 */
		String		GetPosition(ePosition pos);

		//! Aus einem String den zugehörigen Positions-Enum erstellen
		/*! Aus dem übergebenen String der Position wird der zugehörige
		 *  enum-Wert generiert (z.B. "liegend" -> posLiegend).
		 *  \param (String) Bezeichnung der Position
		 *	\return (ePosition) Auflistung der Position
		 */
		ePosition   GetPosition(String pos);

	//-------------------------------------------------------------------------
	//--- Comboboxen ----------------------------------------------------------
	//-------------------------------------------------------------------------
		//! Die Strings der verfügbaren Positionen in eine ComboBox laden
		/*! Die Bezeichnungen aller verfügbaren Positionen (enum ePosition)
		 *  werden in die übergebene ComboBox geladen, der zugehörige enum-Wert
		 *  wird dabei jeweils als Object abgespeichert.
		 *  \param (TComboBox) ComboBox
		 */
		void 		PositionenToCombo(TComboBox* cb);

	//-------------------------------------------------------------------------
	//--- Formulare laden und speichern ---------------------------------------
	//-------------------------------------------------------------------------
		//! Dateiname der Projekt-Inifile erstellen
		/*! Gibt den Namen der Projekt-Inifile zurück. Diese liegt im gleichen
		 *  Verzeichnis wie die exe-Datei.
		 *  \return (String) Dateiname der Ini-File
		 */
		String		GetIniFile();

		//! Formular laden (Position, Ausdehnung, Felder, usw.)
		/*! Lädt die Daten des übergebenen Formular aus der Projekt-Inifile:\r\n
		 *  <ul><li>Position (Left und Top)
		 *  <li>Ausdehnung (Width und Height)
		 *  <li>Inhalte der Edit-Felder
		 *  <li>ItemIndex der ComboBoxen
		 *  <li>Status der Checkboxen (checked)
		 *  \param (TForm) Formular das gespeichert werden soll
		 */
		void 		FormLoad(TForm* fm);

		//! Formular speichern (Position, Ausdehnung, Felder, usw.)
		/*! Speichert die Daten des übergebenen Formular in die Projekt-Inifile:\r\n
		 *  <ul><li>Position (Left und Top)
		 *  <li>Ausdehnung (Width und Height)
		 *  <li>Inhalte der Edit-Felder
		 *  <li>ItemIndex der ComboBoxen
		 *  <li>Status der Checkboxen (checked)
		 *  \param (TForm) Formular das gespeichert werden soll
		 */
		void 		FormSave(TForm* fm);

	//-------------------------------------------------------------------------
	//--- Sonstige Funktionen -------------------------------------------------
	//-------------------------------------------------------------------------

		//! Feststellen ob das Programm auf einem Heimrechner ausgeführt wird (= im Debugmodus)
		/*! Überprüft ob der ausführende Rechner in der Liste der "HomeStations"
		 *  vorhanden ist. Falls ja, handelt es sich um einen "HeimRechner", d.h.
		 *  das Programm läuft im Debugmodus.\r\n
		 *  Kann verwendet werden um ggf. Testfunktionen o.ä. an oder aus zu schalten.
		 *  /return true wenn es sich beim ausführenden Rechner um einen Heimrechner
		 *		handelt, sonst false
		 */
    	bool		IsDebug();

private:

	};
//---------------------------------------------------------------------------
#endif
