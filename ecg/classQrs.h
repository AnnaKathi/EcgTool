//---------------------------------------------------------------------------
#ifndef classQrsH
#define classQrsH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classArray.h"
#include "../basics/classMath.h"
//---------------------------------------------------------------------------
struct qrsPoint
	{
	int		zeit;
	double	wert;
	};
//---------------------------------------------------------------------------
struct qrsArea
	{
	qrsPoint	Q;
	qrsPoint	R;
	qrsPoint	S;
	};
//---------------------------------------------------------------------------
//! Berechnet und kapselt die QRS-Bereiche des EKG-Signals
class PACKAGE cQrs : public cBase
	{
public:
	cQrs();  //! Konstruktor für cQRS
	~cQrs(); //! Destruktor für cQRS

	//findet die verschiedenen QRS-Bereiche um die R-Peaks herum
	bool		build(iarray_t curve, iarray_t rpeaks);

	bool		reset();
	bool		next();

__property qrsArea QRS = { read=fArea         };
__property int count   = { read=get_anz_turns };

private:
	cArray		farray;
	cMath		fmath;

	int			fIndex;
	iarray_t	fTurns;
	qrsArea		fArea;
	int			get_anz_turns();

	int			findTurn(iarray_t array, int von, int bis);
	};
//---------------------------------------------------------------------------
#endif
