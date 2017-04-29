//---------------------------------------------------------------------------
#ifndef classDerivateH
#define classDerivateH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
#include "classArray.h"
#include "classMath.h"
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
//! erstellt und verwaltet eine Ableitung
/*! Die Klasse cDerivate bildet und verwaltet eine Ableitung �ber einem Datenarray (std::map)
 */
class PACKAGE cDerivate : public cBase
	{
public:
	cDerivate();  //!< Konstruktor von cDerivate
	~cDerivate(); //!< Destruktor von cDerivate

	sArrayCha	farr_charac; //todo getter und setter machen

	//! Erstellt eine ABleitung �ber einem Array
	/*! �ber dem �bergebenen Datenarray (std::map) wird die Ableitung erstellt.
	 *  Der Funktionsaufruf wird an cMath::calcDerivate weitergeleitet.
	 *  /param (std::map) Array �ber dem die Ableitung erstellt werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool		build(iarray_t array);

	//! Zeichnet das interne Ableitungs-Array in ein Image
	/*! Das interne Ableitungsarray wird in das �bergebene Image geziechnet.
	 *  Der Funktionsaufruf wird an cArray::redisplay weitergeleitet.
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		redisplay(TImage* img);

	//! Berechnet den gleitenden Durchschnitt �ber dem internen Ableitungsarray
	/*! �ber dem internen Ableitungsarray wird ein gleitender Durchschnitt berechnet.
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

	//! Daten aus dem internen Ableitungsarray entfernen
	/*! Der Bereich von-bis (Millisekunden) wird aus dem internen Ableitungsarray
	 *  entfernt. Der Funktionsaufruf wird an cArray::cut weitergeleitet.
	 *  /param (int) Millisekunden ab der die Daten entfernt werden sollen
	 *  /param (int) Millisekunden bis zu der die Daten entfernt werden sollen
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	int			cut(int vonMsec, int bisMsec);

__property iarray_t	deriv_array = { read=get_array }; //!< Internes Ableitungsarray

private:
	cMath*		fmath;
	cArray*		farray; //Grundfunktionalit�ten

	iarray_t	farr;
	iarray_t	get_array();
	};
//---------------------------------------------------------------------------
#endif
