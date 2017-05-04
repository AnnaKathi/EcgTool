//---------------------------------------------------------------------------
#ifndef classChoiFeaturesH
#define classChoiFeaturesH
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
#include "../../basics/classArray.h"
#include "../../basics/classTools.h"
#include "../../basics/classMath.h"
//---------------------------------------------------------------------------
class PACKAGE cChoiFeat : public cBase
	{
public:
	cChoiFeat();
	~cChoiFeat();

	iarray_t	getFeatures(iarray_t curve); //ruft FindRPeaks und FindFeatures auf, setzt die �bergreifenden Durchschnittssfeatures
	bool		FindRPeaks(iarray_t curve);
	bool		FindFeatures(iarray_t curve);

	bool		getSingleFeatures(iarray_t ecg, int prev_zeit, int curr_zeit, int next_zeit);

__property double   Threshold = { read=get_Threshold, write=set_Threshold };
__property int	    Overlap   = { read=get_Overlap,   write=set_Overlap   };

__property iarray_t Rpeaks    = { read=get_Array_Rpeaks, write=set_Array_Rpeaks   };
__property iarray_t Features  = { read=get_Array_Features }; //Durchschnittsfeatures des ges. EKG-Streams
__property iarray_t SingleFeatures = { read=get_Array_Single_Features }; //Features eines Herzschlags

private:
	cArray		farray;
	cTools		ftools;
	cMath		fmath;

	double		fParameter_Threshold;
	void		set_Threshold(double threshold);
	double		get_Threshold();

	int			fParameter_Overlap_Time;
	void		set_Overlap(int time);
	int			get_Overlap();

	iarray_t	fArray_Rpeaks;
	void		set_Array_Rpeaks(iarray_t rpeaks); //falls man sich R-Peaks selber setzen will
	iarray_t	get_Array_Rpeaks();

	iarray_t 	fArray_Features;  //enth�lt die Durchschnittsfeatures des ges. EKG-Streams, gesetzt von getFeatures()
	iarray_t	get_Array_Features();

	iarray_t	fArray_Single_Features; //enth�lt die Features eines Herzschlags, gesetzt von getSingleFeatures()
	iarray_t	get_Array_Single_Features();

	int			FidPQInt[128];
	int			FidQSInt[128];
	int			FidSTInt[128];
	double 		FidPAmp[128];
	double 		FidQAmp[128];
	double 		FidRAmp[128];
	double 		FidSAmp[128];
	double 		FidTAmp[128];

	bool 		FindMinMax(iarray_t array, double& min, double& max);
	iarray_t 	FindOverlaps(iarray_t candidates);
	};
//---------------------------------------------------------------------------
#endif