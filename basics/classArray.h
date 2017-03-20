//---------------------------------------------------------------------------
#ifndef classArrayH
#define classArrayH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
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
//! grundlegende Funktionen auf einem Array
/*! Die Klasse cArray bietet grundlagende Funktionen auf den Werten eines Array
 *  (std::map) an.
 */
class PACKAGE cArray : public cBase
	{
public:
	cArray();
	~cArray();

	sArrayCha	farr_charac; //todo getter und setter machen

	//! l�dt die Metadaten eines Array neu
	/*! Die Metadaten (z.B. Millisekunden-Bereich) des �bergebenen Arrays werden
	 *  neu geladen. Sollte aufgerufen werden, wenn das Array ver�ndert wird, z.B.
	 *  durch cut, weil andere Funktionen diese Metadaten verwenden k�nnten.
	 *  /param (std::map) Array das neu zu laden ist
	 *  /param (sArrayCha) Charakteristik-Struktur die gef�llt werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		resetValues(iarray_t array, sArrayCha& cha);

	//! Das �bergebene Image l�schen
	/*! Das �bergebene Image wird gel�scht (leer gezeichnet).
	 *  /param (Image) Image in das gel�scht werden soll
	 */
	void 		clearImg(TImage* img);

	//! Daten des �bergebenen Array in einem Image anzeigen
	/*! Das �bergebene Array wird im �bergebenen Image eingezeichnet. Das �bergebene
	 *  Image wird NICHT gel�scht, sondern nur neu gezeichnet. D.h. es k�nnen mehrere
	 *  Arrays in das gleiche Bild gezeichnet werden. Wenn das nicht gew�nscht
	 *  ist, kann redisplay() verwendet werden.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		display(iarray_t array, TImage* img);

	//! Daten des �bergebenen Array in einem Image anzeigen
	/*! Das �bergebene Array wird im �bergebenen Image eingezeichnet. Das �bergebene
	 *  Image wird zun�chst gel�scht und dann neu gezeichnet. Um mehrere Arrays
	 *  in das gleiche Bild zu zeichnen, kann display() verwendet werden.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		redisplay(iarray_t array, TImage* img); //ruft erst clear und dann display auf

	//! Punkte in eine Kurve einzeichnen
	/*! Das �bergebene Array 'curve' wird zun�chst im �bergebenen Image
	 *  eingezeichnet. Anschlie�end wird f�r jeden Punkt aus dem �bergebene
	 *  Array 'points' einPunkt in die Kurve eingezeichnet.
	 *  /param (std::map) Array das die Kurvenwerte enth�lt
	 *  /param (std::map) Array das die Punkte enth�lt
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		displayPoints(iarray_t curve, iarray_t points, TImage* img);

	//! Gleitenden Durchschnitt �ber dem �bergebenen Array berechnen
	/*! �ber dem �bergebenen Array wird ein gleitender Durchschnitt berechnet.
	 *  Dabei wird die zu verwendende Fenstergr��e �bergeben, sowie die
	 *  Information, ob die Anfangswerte (bevor das erste Fenster erreicht
	 *  wird) in die Berechnung einflie�en sollen, oder nicht.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /param (int) window, die zu verwendende Fenstergr��e
	 *  /param (bool) CalcBegin, soll der Anfang, der vor dem ersten Fenster
	 *		liegt, mit in die Berechnung einflie�en? Ist mit true vorbesetzt
	 *  /return (std::map) neues Array mit gleitendem Durchschnitt
	 */
	iarray_t 	movingAv(iarray_t array, int window, bool CalcBegin);

	//! Berechnet den Durchschnittswert des Arrays
	/*! Alle Werte des �bergebenen Arrays werden addiert und durch die Anzahl
	 *  der enthaltenen Werte geteilt.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /return (double) Durchschnittswert des Arrays 
	 */
	double		calcAvWert(iarray_t array);

	//! Daten aus dem �bergebenen Array entfernen
	/*! Der Bereich von-bis (Millisekunden) wird aus dem �bergebenen Array
	 *  entfernt.
	 *  /param (std::map) Array aus dem Werte entfernt werden sollen
	 *  /param (int) Millisekunden ab der die Daten entfernt werden sollen
	 *  /param (int) Millisekunden bis zu der die Daten entfernt werden sollen
	 *  /return (std::map) neues Array
	 */
	iarray_t 	cut(iarray_t array, int vonMsec, int bisMsec);

private:
	iarray_t	farr;

	bool 		resetValues(sArrayCha& cha);
	};
//---------------------------------------------------------------------------
#endif
