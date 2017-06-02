//---------------------------------------------------------------------------
#ifndef classRpeaksChoiH
#define classRpeaksChoiH
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
#include "../../basics/classTools.h"
#include "../../basics/classArray.h"
//---------------------------------------------------------------------------
class PACKAGE cRpeaksChoi : public cBase
	{
public:
	cRpeaksChoi();
	~cRpeaksChoi();

	bool 		findRpeaks(iarray_t curve);

__property int		AlgIdent = { read=get_alg_ident };
__property iarray_t Rpeaks   = { read=get_rpeaks    };

private:
	int			fAlgIdent;
	int			get_alg_ident();

	cTools		ftools;
	cArray		farray;

	iarray_t	fRpeaks;
	iarray_t	get_rpeaks();

	iarray_t 	findOverlaps(iarray_t candidates);

	double		fParameter_Threshold;
	int			fParameter_Overlap_Time;
	};
//---------------------------------------------------------------------------
#endif
