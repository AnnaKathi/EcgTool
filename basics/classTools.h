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
//! bietet verschiedene Grundfunktionalit�ten an
/*! Die Klasse cTools bietet verschiedenen Grundfunktionalit�ten an:\r\n
 * <ul><li>Datenkonverter 'Position' (String <-> enum ePosition)
 * <li>Positions-String in ComboBox laden
 * <li>Formular speichern und laden</ul> 
 */
class cTools
	{
public:
	//! Konstruktor f�r cTools
	cTools();

	//-------------------------------------------------------------------------
	//--- Datenkonverter ------------------------------------------------------
	//-------------------------------------------------------------------------
		//! Aus einem Positions-Enum den zugeh�rigen String erstellen
		/*! Aus dem �bergebenen enum der Position (ePosition) wird der zugeh�rige
		 *  String generiert (z.B. posLiegend -> "liegend").
		 *  \param (ePosition) Auflistung der Position
		 *	\return (String) Bezeichnung der Position
		 */
		String		GetPosition(ePosition pos);

		//! Aus einem String den zugeh�rigen Positions-Enum erstellen
		/*! Aus dem �bergebenen String der Position wird der zugeh�rige
		 *  enum-Wert generiert (z.B. "liegend" -> posLiegend).
		 *  \param (String) Bezeichnung der Position
		 *	\return (ePosition) Auflistung der Position
		 */
		ePosition   GetPosition(String pos);

	//-------------------------------------------------------------------------
	//--- Comboboxen ----------------------------------------------------------
	//-------------------------------------------------------------------------
		//! Die Strings der verf�gbaren Positionen in eine ComboBox laden
		/*! Die Bezeichnungen aller verf�gbaren Positionen (enum ePosition)
		 *  werden in die �bergebene ComboBox geladen, der zugeh�rige enum-Wert
		 *  wird dabei jeweils als Object abgespeichert.
		 *  \param (TComboBox) ComboBox
		 */
		void 		PositionenToCombo(TComboBox* cb);

	//-------------------------------------------------------------------------
	//--- Formulare laden und speichern ---------------------------------------
	//-------------------------------------------------------------------------
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

private:

	};
//---------------------------------------------------------------------------
#endif
