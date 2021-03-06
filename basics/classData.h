//---------------------------------------------------------------------------
#ifndef classDataH
#define classDataH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.cpp"
#include "classCsv.h"
#include "classArray.h"
#include "classDerivate.h"
//---------------------------------------------------------------------------
/* todo: obsolete ?
typedef struct sARRAYCHA //Charkterwerte eines Arrays
	{
	int			VonIdx;  //kleinster Index
	int			BisIdx;  //gr��ter Index
	int			VonMsec; //kleinster Millisek.wert
	int			BisMsec; //gr��ter Millisek.wert
	float		MinWert; //tiefster Wert (Ausschlag)
	float		MaxWert; //h�chster Wert (Ausschlag)
	int			Number;  //Anzahl Datens�tze im Array
	} sArrayCha;
//---------------------------------------------------------------------------
*/
//! Grundfunktionalit�ten auf dem Daten-Array
/*! Die Klasse cData bietet Grundfunktionalit�ten aufd em array (std::map) an:\r\n
 *  <ul><li>Datei einlesen (Weiterleitung an cCsv)
 *  <li>Gleitenden Durchschnitt berechnen (Weiterleitung an cArray)
 *  <li>Werte entfernen (Weiterleitung an cArray)
 *  <li>Ableitungen berechnen (Weiterleitung an cMath)</ul>
 */
class PACKAGE cData : public cBase
	{
public:
	cData();  //!< Konstruktor von cData
	~cData(); //!< Destruktor von cData

	sArrayCha	farr_charac; //todo getter und setter machen

	//-----------------------------------------------------------------------
	//--- Grundfunktionen ---------------------------------------------------
	//-----------------------------------------------------------------------
		//! Datei einlesen
		/*! Die �bergebene Datei wird eingelesen. Dabei kann der einzulesende
		 *  Bereich nach Millisekunden eingeschr�nkt werden. Der Funktionsaufruf
		 *  wird an cCsv::OpenFile weitergeleitet.
		 *  /param (String) Datei die eingelesen werden soll
		 *  /param (String) Delimeter der f�r die Datei verwendet werden soll
		 *  /param (int) Millisekunde ab der eingelesen werden soll
		 *  /param (int) Millisekunde bis zu der eingelesen werden soll
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		getFile(String file, eDatFormat format, String delim, int vonMsec, int bisMsec);

		//! Daten des Array in einem Image anzeigen
		/*! Das interne Datenarray wird im �bergebenen Image eingezeichnet. Der
		 *  Funktionsaufruf wird an cArray::redisplay weitergeleitet.
		 *  /param (Image) Image in das gezeichnet werden soll
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		redisplay(TImage* img);

		//! Gleitenden Durchschnitt �ber dem internen Datenarray berechnen
		/*! �ber dem internen Datenarray wird ein gleitender Durchschnitt berechnet.
		 *  Dabei wird die zu verwendende Fenstergr��e �bergeben, sowie die
		 *  Information, ob die Anfangswerte (bevor das erste Fenster erreicht
		 *  wird) in die Berechnung einflie�en sollen, oder nicht.
		 *  Der Funktionsaufruf wird an cArray::movingAv weitergeleitet.
		 *  /param (int) window, die zu verwendende Fenstergr��e
		 *  /param (bool) CalcBegin, soll der Anfang, der vor dem ersten Fenster
		 *		liegt, mit in die Berechnung einflie�en? Ist mit true vorbesetzt
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		movingAv(int window, bool CalcBegin = true);

		//! Daten aus dem internen Datenarray entfernen
		/*! Der Bereich von-bis (Millisekunden) wird aus dem internen Datenarray
		 *  entfernt. Der Funktionsaufruf wird an cArray::cut weitergeleitet.
		 *  /param (int) Millisekunden ab der die Daten entfernt werden sollen
		 *  /param (int) Millisekunden bis zu der die Daten entfernt werden sollen
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		cut(int vonMsec, int bisMsec);

	//-----------------------------------------------------------------------
	//--- mathematische Funktionen ------------------------------------------
	//-----------------------------------------------------------------------
		//! 1. und 2. Ableitung �ber dme internen Datenarray bilden
		/*! Erstellt �ber dem internen Datenarray die erste und zweite Ableitung.
		 *  Der Funktionsaufruf wird an cDerivate::build weitergeleitet.
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		buildDerivates();

		//! EKG-Signal (array) auf die angegebene L�nge normalisieren
		/*! Das �bergebene Array wird auf die angegebene L�nge normalisiert.
		 *  Wenn das Array verk�rzt werden muss, werden in regelm��igen Abst�nden
		 *  Werte entfernt. Wenn es verl�ngert werden muss, werden in
		 *  regelm��igen Abst�nden Werte hinzugef�gt (Durchschnitt aus dem
		 *  vorangehenden und dem nachfolgenden Wert).
		 *  /param (std::map) array, EKG-Werte die normalisiert werden sollen
		 *  /param (int) length, L�nge auf die normliaisert werden soll
		 *  /return (bool) true wenn erfolgreich, sonst false
		 */
		iarray_t	normalize(iarray_t array, int length);

__property iarray_t   data_array = { read=get_array  }; //!< Internes Datenarray
__property cDerivate& derivate1  = { read=get_deriv1 }; //!< Erste Ableitung
__property cDerivate& derivate2  = { read=get_deriv2 }; //!< Zweite Ableitung

private:
	cCsv*		fcsv;

	cDerivate*	fderiv1; //erste Ableitung
	cDerivate&	get_deriv1();

	cDerivate*	fderiv2; //zweite Ableitung
	cDerivate&	get_deriv2();

	cArray*		farray; //Klasse mit Grundfunktionalit�ten

	iarray_t	farr;  //alle eingelesenen EKG-Werte
	iarray_t	get_array();

	void 		resetValues();
	};
//---------------------------------------------------------------------------
#endif
