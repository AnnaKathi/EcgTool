//---------------------------------------------------------------------------
#ifndef classFeaturesWaili3H
#define classFeaturesWaili3H
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
//---------------------------------------------------------------------------
class PACKAGE cFeaturesWaili3 : public cBase
	{
public:
	cFeaturesWaili3();

	bool		getFeatures(iarray_t curve, iarray_t rpeaks);
	
__property int  AlgIdent = { read=get_alg_ident };
__property iarray_t features = { read=get_features  };
__property String	features_string = { read=get_features_string };

private:

	iarray_t	fFeatures;
	iarray_t	get_features();

	String		fFeaturesStr;
	String		get_features_string();

	int			fAlgIdent;
	int			get_alg_ident();
	};
//---------------------------------------------------------------------------
#endif
