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
	cTurns();  //!< Konstruktor für cTurns
	~cTurns(); //!< Destruktor für cTurns

	//! (GEPLANT) Berechnet die Wendepunkte über einem Datenarray
	/*! Über dem übergebenen Datenarray werden die Wendepunkte berechnet.
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
