//---------------------------------------------------------------------------
#ifndef classHeartbeatH
#define classHeartbeatH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classArray.h"
#include "classRpeaks.h"
//---------------------------------------------------------------------------
//! Erstellt und verwaltet den Standardherzschlag eines EKG
/*! Die Klasse cHeartbeat berechnet und verwaltet den Standardherzschlag eines
 *  EKG-Signals. Daf�r werden alle einzelnen Herzschl�ge (von R-Peak bis R-Peak)
 *  �bereinander gelegt und aus allen Werten der Durchschnitt gebildet. 
 */
class PACKAGE cHeartbeats : public cBase
	{
public:
	cHeartbeats();  //!< Konstruktor f�r cHeartbeat
	~cHeartbeats(); //!< Destruktor f�r cHeartbeat

	//! Metadaten der Kurve zur�cksetzen
	/*! Die Metadaten der Kurvendaten werden zur�ckgesetzt, damit sich die
	 *  nachfolgenden Funktionen auf diese beziehen k�nnen. Dieser Aufruf erstellt
	 *  die R-Peaks selbstst�ndig, wenn bereits eine R-Peak-Berechnung vorliegt,
	 *  kann stattdessen reset(curve, rpeaks) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool 		reset(iarray_t curve); //R-Peaks m�ssen noch gebildet werden

	//! Gibt den ersten R-Peak des Signals zur�ck
	/*! Auf der �bergebenen Kurve wird der erste R-Peak berechnet und zur�ckgeben.
	 *  Intern wird der Funktionsaufruf auf next() weitergeleitet, first() kann
	 *  f�r Aufrufe innerhalb einer for-Schleife verwendet werden. Dieser Aufruf
	 *  erstellt die R-Peaks selbstst�ndig, wenn bereits eine R-Peak-Berechnung
	 *  vorliegt, kann stattdessen first(curve, rpeaks) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool 		first(iarray_t curve); //R-Peaks m�ssen noch gebildet werden

	//! Metadaten der Kurve zur�cksetzen
	/*! Die Metadaten der Kurvendaten werden zur�ckgesetzt, damit sich die
	 *  nachfolgenden Funktionen auf diese beziehen k�nnen. Dieser Aufruf erstellt
	 *  die R-Peaks NICHT selbstst�ndig, wenn noch keine R-Peak-Berechnung vorliegt,
	 *  kann stattdessen reset(curve) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /param (std::map) R-Peaks der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		reset(iarray_t curve, iarray_t rpeaks); //Aufrufender hat RPeaks schon gebildet

	//! Gibt den ersten R-Peak des Signals zur�ck
	/*! Auf der �bergebenen Kurve wird der erste R-Peak berechnet und zur�ckgeben.
	 *  Intern wird der Funktionsaufruf auf next() weitergeleitet, first() kann
	 *  f�r Aufrufe innerhalb einer for-Schleife verwendet werden. Dieser Aufruf
	 *  erstellt die R-Peaks NICHT selbstst�ndig, wenn noch keine R-Peak-Berechnung
	 *  vorliegt, kann stattdessen first(curve) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /param (std::map) R-Peaks der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		first(iarray_t curve, iarray_t rpeaks); //Aufrufender hat RPeaks schon gebildet

	//! Gibt den n�chsten R-Peak des Signals zur�ck
	/*! Auf der �bergebenen Kurve wird der n�chste R-Peak berechnet und zur�ckgeben.
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		next();

	//! Pr�ft ob der letzte R-Peak erreicht wurde
	/*! Pr�ft, ob noch Kurvendaten zur Verf�gung stehen ober ob der letzte R-Peak
	 *  erreicht wurde. Kann z.B. f�r for-Schleifen verwendet werden.
	 *  /return (bool) true wenn keine R-Peaks mehr vorhanden sind, sonst false
	 */
	bool		end();

	//! Berechnet den Standardherzschlag �ber einem Datenarray
	/*! �ber dem �bergebenem Datenarray wird der Standardherzschlag berechnet.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /return (bool) Array mit den Werten des Standardherzschlags
	 */
	iarray_t	calcAvBeat(iarray_t curve);
	bool		rf_calcAvBeat(iarray_t curve);

__property iarray_t   heartbeat = { read=get_heartbeat  }; //!< jeweils ein einzelner Herzschlag, f�r for-Schleifen z.B.
__property iarray_t   avBeat	= { read=get_AvBeat		}; //!< Standardherzschlag, Durchschnitt aller Herzschl�ge

private:
	cArray		farray;
	iarray_t	fcurve;
	iarray_t	frpeaks;

	iarray_t	fheartbeat; //jeweils ein einzelner Herzschlag, f�r first-next
	iarray_t	get_heartbeat();

	iarray_t	fAvBeat; //Standardherzschlag
	iarray_t	get_AvBeat();

	sArrayCha	charac; //todo getter und setter machen

	int			findex;
	};
//---------------------------------------------------------------------------
#endif

