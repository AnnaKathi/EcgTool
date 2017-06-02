//---------------------------------------------------------------------------
#ifndef classRandomPointsH
#define classRandomPointsH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
//---------------------------------------------------------------------------
//! Die Klasse cRandomPoints wählt x zufällige Punkte im QRS-Bereich
class PACKAGE cRandomPoints : public cBase
	{
public:
	cRandomPoints();
	~cRandomPoints();

	//! Sucht x zufällige Punkte aus dem QRS-Komplex des übergebenen Herzschlags raus
	/*! Aus dem QRS-Komplex des übergebenen Herzschlags werden x zufällige Punkte
	 *  ausgewählt. Diese können danach über next() abgefragt werden.
	 *  /param (std::map) Array des Herzschlags
	 *  /param (int) Anzahl der gewünschten Werte
	 *  /return (bbol) true wenn erfolgreich, sonst false
	 */
	bool		getRandomPointsFromBeat(iarray_t beat, int anzahl);
	bool		resetBeatPoints();
	bool		nextPointInBeat();

__property int	  AlgIdent    = { read=get_alg_ident };
__property double randomPoint = { read=randomP };

private:
	int			fAlgIdent;
	int			get_alg_ident();

	int			rvIndex;
	iarray_t	randomValues;

	double		randomP;
	};
//---------------------------------------------------------------------------
#endif
