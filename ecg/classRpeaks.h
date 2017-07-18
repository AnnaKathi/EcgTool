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
	cRpeaks();  //!< Konstruktor f�r cRpeaks
	~cRpeaks(); //!< Destruktor f�r cRpeaks

	//! Die R-Peaks in einem Datenarray finden
	/*! In dem �bergebenen Datenarray werden die R-Peaks gesucht. Daf�r werden
	 *  die Daten absteigend sortiert; im vorderen Bereich liegen dann
	 *  (wahrscheinlich) die R-Peaks. Hier wird jeweils der gr��te Wert erfasst,
	 *  und diesem die umliegenden x Millisekunden zugeordnet (QRS-Bereich).
	 *  /param (std::map) Array mit EKG-Daten
	 *  /param <b>optional</b> (Image) Image in dem die umsortierten Werte zu Testzwecken angezeigt werden k�nnen. 
	 */
	iarray_t	find(const iarray_t& array, TImage* img1);

	bool		reset();
	int			next();
	int			prev_rpeak();
	int			next_rpeak();

__property iarray_t rpeaks = { read=get_rpeaks };

private:
	cMath*		fmath;
	cArray*		farray;

	sArrayCha	charac; //todo getter und setter machen

	int			findex;
	iarray_t	frpeaks;
	iarray_t	get_rpeaks();
	};
//---------------------------------------------------------------------------
#endif
