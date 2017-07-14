//---------------------------------------------------------------------------
#ifndef classCsvH
#define classCsvH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <classes.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
/* spezielle Fehlercodes von cCsv */
enum CSV_ERROR_CODES
	{
	EC_OK,		  // no error, all things done well
	EC_NOFILE,	  // no file specified
	EC_FNF,		  // file not found
	EC_FPSEEK,	  // Filepointer konnte nicht zur�ckgesetzt werden
	EC_NOFP,	  // Filepointer ist Null
	EC_NOROW,	  // keien (weitere) Zeile vorhanden
	EC_NOFIELD,	  // kein (weiteres) Feld vorhanden
	};
//---------------------------------------------------------------------------
/* Struktur f�r die auszulesenden EKG-Daten */
struct cEcgLine
	{
	int 	lineno;
	int		sample;
	double	ch1; //die acht Kan�le der Datei, siehe auch unten
	double	ch2;
	double	ch3;
	double	ch4;
	double	ch5;
	double	ch6;
	double	ch7;
	double	ch8;

	double  v12; //C1 zu C2 --> (V1-WCT) - (V2-WCT) = V1 - V2 = Ch.8 - Ch.4
	double  v34; //C3 zu C4 --> (V3-WCT) - (V4-WCT) = V3 - V4 = Ch.5 - Ch.6
	double  v56; //C5 zu C6 --> (V5-WCT) - (V6-WCT) = V5 - V6 = Ch.7 - Ch.1

	double	min[12]; //kleinster Wert aller Spalten
	double  max[12]; //gr��ter Wert aller Spalten
	};
//---------------------------------------------------------------------------
/* Lead-Derivation ADS1298
Channel 1 = V6 = V6 - WCT
Channel 2 = Lead I  = LA - RA
Channel 3 = Lead II = LL - RA
Channel 4 = V2 = V2 - WCT
Channel 5 = V3 = V3 - WCT
Channel 6 = V4 = V4 - WCT
Channel 7 = V5 = V5 - WCT
Channel 8 = V1 = V1 - WCT
*/
//---------------------------------------------------------------------------
//! liest eine CSV-Datei ein
/*! Die Klasse cCsv liest eine csv-Datei (bzw. eine txt-Datei) ein und f�llt
 *  f�r jede (g�ltige) Zeile die Struktur EcgLine.
 */
class PACKAGE cCsv : public cBase
	{
public:
	cCsv();  //!< Konstruktor f�r CCsv
	~cCsv(); //!< Destruktor f�r cCsv

	//-----------------------------------------------------------------------
	//--- Dateihandling -----------------------------------------------------
	//-----------------------------------------------------------------------
		//! Datei �ffnen
		/*! �ffnet die �bergebene Datei und stellt den zu verwendenden Delimeter
		 *  (Semikolon oder Tab) ein. Als Standard Delimeter wird ';' verwendet.
		 *  /param (String) file, Datei die ge�ffnet werden soll
		 *  /param (String) delim, Delimeter der verwendet werden soll, Standard
		 *		ist ';'
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool 		OpenFile(String file, eDatFormat format, String delim, int lead);

		//! Datei schlie�en
		/*! Schlie�t die Datei und gibt den FilePointer frei, sofern gesetzt.
		 */
		void 		CloseFile();

		//! FilePointer zum Anfang der Datei zur�cksetzen
		/*! Der FilePointer wird zum Anfang der Datei zur�ckgesetzt (fseek SEEK_SET)
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool 		Reset();

	//-----------------------------------------------------------------------
	//--- Datei einlesen ----------------------------------------------------
	//-----------------------------------------------------------------------
		//! Beginnt das Einlesen, ggf. ab einer bestimmten Millisekunde
		/*! Beginnt das  Einlesen der ge�ffneten Datei. Daf�r werden zun�chst
		 *  Leerzeielen am Anfang, sowie die Spaltenk�pfe �bersprungen.
		 *  Dar�ber hinaus kann man eine Millisekunde �bergeben, ab der das
		 *  Einlesen beginnen soll. In diesem Fall werden alle Datens�tze bis zu
		 *  diesem Wert (exklusiv) �bersprungen.
		 *  /param (int) sample, Startwert ab dem die Datei eingelsen werden soll
		 *  /return (bool) true wenn der Startpunkt f�r das Einlesen gefunden
		 *		werden konnte, sonst false
		 */
		bool 		StartAt(int sample);

		//! ersten Datensatz lesen
		/*! Liest den ersten Datensatz aus der Datei nach dem Startpunkt (siehe
		 *  StartAt(...)). Intern wird der Aufruf auf Next() weitergeleitet. Die
		 *  Funktion dient nur dem Aufruf in einer for-Schleife
		 *  (for (rc = First(), rc != false; rc = Next()).
		 *  /return (bool) true wenn ein Datensatz eingelesen werden konnte,
		 *		sonst false (z.B. wenn die Datei zu Ende ist)
		 */
		bool 		First();

		//! n�chsten Datensatz lesen
		/*! Liest den n�chsten Datensatz aus der Datei (bis zum n�chsten \n).
		 *  /return (bool) true wenn ein Datensatz eingelesen werden konnte,
		 *		sonst false (z.B. wenn die Datei zu Ende ist)
		 */
		bool 		Next();

		//! n�chsten Datensatz lesen, Alternative zu First/Next
		/*! Liest den n�chsten Datensatz aus der Datei bis zum �bergebenen
		 *  Millisekunden-Wert (inklusive).
		 *  /param (int) sample, Millisekunde bis zu der gelesen werden soll
		 *  /return (bool) true wenn ein Datensatz eingelesen werden konnte,
		 *		sonst false (z.B. wenn die Datei zu Ende ist oder der eingelesene
		 *		Datensatz hinter dem �bergebenen Millisekundenwert liegt)
		 */
		bool 		NextUntil(int sample);

	//-----------------------------------------------------------------------
	//--- allgemeine getter -------------------------------------------------
	//-----------------------------------------------------------------------
		//! Gr��e der Datei
		/*! Gibt die Gr��e der einzulesenden Datei in Bytes zur�ck (ftell).
		 *  Kann z.B. f�r Fortschrittsanzeigen verwendet werden.
		 *  /return (int) Gr��e der Datei
		 */
		int			getFileMax();

		//! aktuelle Position in der Datei
		/*! Gibt die aktuelle Position in der Datei in Bytes zur�ck (ftell).
		 *  Kann z.B. f�r Fortschrittsanzeigen verwendet werden.
		 *  /return (int) Position in der Datei
		 */
		int			getFilePos();

	//-----------------------------------------------------------------------
	//--- getter zur EKG-Struktur -------------------------------------------
	//-----------------------------------------------------------------------
		//! aktuelle Zeilennummer
		/*! Gibt nach First/Next/NextUntil die aktuelle Zeilennummer zur�ck
		 *  /return (int) Zeilennummer
		 */
		int 		getLineNo();

		//! aktuelles Sample (= Millisekunde)
		/*! Gibt nach First/Next/NextUntil die aktuelle Samplenummer
		 *  (= Millisekunde) zur�ck
		 *  /return (int) Sample
		 */
		int 		getSample();

		double		getVal(); //gibt den gew�nschten Lead zur�ck (1-8 = Channels, 9-11 Ableitungen)
		double		getChannel(int channel);
		double		getC12();
		double		getC34();
		double		getC56();

private:
	FILE*		fp;
	int         fpMax;

	int			LineCount;
	char		rowbuf[128];
	char		Delim[2];
	eDatFormat	Format;
	cEcgLine	EcgLine;
	int			iLead;

	bool 		Skip();
	bool		SkipRow();
	bool 		ParseLineObsolete();
	bool 		ParseLineOld();
	bool		ParseLine();
	bool		bFirstParse;
	};
//---------------------------------------------------------------------------
#endif
