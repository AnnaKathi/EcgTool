//---------------------------------------------------------------------------
#ifndef classFeaturesChoiH
#define classFeaturesChoiH
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
#include "../../basics/classTools.h"
#include "../../basics/classArray.h"
#include "../../basics/classMath.h"
//---------------------------------------------------------------------------
class PACKAGE cFeaturesChoi : public cBase
	{
public:
	cFeaturesChoi();
	~cFeaturesChoi();

	bool		getFeatures(iarray_t curve, iarray_t rpeaks);

__property int      AlgIdent = { read=get_alg_ident };
__property iarray_t features = { read=get_features  };
__property String	features_string = { read=get_features_string };

private:
	cTools		ftools;
	cArray		farray;
	cMath		fmath;

	iarray_t	fFeatures;
	iarray_t	get_features();

	String		fFeaturesStr;
	String		get_features_string();

	iarray_t	fArray_Single_Features;
	bool 		getSingleFeatures(iarray_t ecg, int prev_zeit, int curr_zeit, int next_zeit);

	int			fAlgIdent;
	int			get_alg_ident();
	};
//---------------------------------------------------------------------------
#endif
