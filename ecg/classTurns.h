//---------------------------------------------------------------------------
#ifndef classTurnsH
#define classTurnsH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
//---------------------------------------------------------------------------
//! Kapselt die Wendepunkte eines EKG
/*! Die Klasse cTurns findet und verwaltet die Wendepunkte eines EKG-Signals.
 */
class PACKAGE cTurns : public cBase
	{
public:
	cTurns();  //!< Konstruktor f�r cTurns
	~cTurns(); //!< Destruktor f�r cTurns

	//! (GEPLANT) Berechnet die Wendepunkte �ber einem Datenarray
	/*! �ber dem �bergebenen Datenarray werden die Wendepunkte berechnet.
	 *  /param (std::map) Datenarray
	 *  /return (int) Anzahl der gefundenen Wendepunkte
	 */
	int			calcTurns(iarray_t array);

private:
	//iarray_t	farr; //die eigentliche Kurve
	//iarray_t	ftrn; //die Wendepunkte
	};
//---------------------------------------------------------------------------
#endif
