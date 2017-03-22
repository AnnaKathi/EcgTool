//---------------------------------------------------------------------------
#ifndef classAlg1H
#define classAlg1H
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
#include "../../ecg/classEcg.h"
#include "features/classRandomPoints.h"
//---------------------------------------------------------------------------
class PACKAGE cAlg1 : public cBase
	{
public:
	cAlg1();
	~cAlg1();

	bool	setupData(cEcg& ecg);
	bool 	buildRandomPoints(int anzahl);
	String	getRandomPoints();

__property cRandomPoints& randoms = { read=get_rp };

private:
	cEcg*			fecg;
	
	cRandomPoints*	frp;
	cRandomPoints&	get_rp();

	};
//---------------------------------------------------------------------------
#endif
