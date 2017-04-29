//---------------------------------------------------------------------------
#ifndef classRpeaksH
#define classRpeaksH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classMath.h"
#include "../basics/classArray.h"
//---------------------------------------------------------------------------
//! Die R-Peaks eines EKG-Signals
/*! Die Klasse cRpeaks kapselt die R-Peaks eines EKG-Signals.
 */
class PACKAGE cRpeaks : public cBase
	{
public:
	cRpeaks();  //!< Konstruktor für cRpeaks
	~cRpeaks(); //!< Destruktor für cRpeaks

	//! Die R-Peaks in einem Datenarray finden
	/*! In dem übergebenen Datenarray werden die R-Peaks gesucht. Dafür werden
	 *  die Daten absteigend sortiert; im vorderen Bereich liegen dann
	 *  (wahrscheinlich) die R-Peaks. Hier wird jeweils der größte Wert erfasst,
	 *  und diesem die umliegenden x Millisekunden zugeordnet (QRS-Bereich).
	 *  /param (std::map) Array mit EKG-Daten
	 *  /param <b>optional</b> (Image) Image in dem die umsortierten Werte zu Testzwecken angezeigt werden können. 
	 */
	iarray_t	find(iarray_t array, TImage* img1);

private:
	cMath*		fmath;
	cArray*		farray;

	sArrayCha	charac; //todo getter und setter machen
	};
//---------------------------------------------------------------------------
#endif
