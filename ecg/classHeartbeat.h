//---------------------------------------------------------------------------
#ifndef classHeartbeatH
#define classHeartbeatH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classArray.h"
#include "classRpeaks.h"
//---------------------------------------------------------------------------
class PACKAGE cHeartbeats : public cBase
	{
public:
	cHeartbeats();
	~cHeartbeats();

	bool 		reset(iarray_t curve); //R-Peaks müssen noch gebildet werden
	bool 		first(iarray_t curve); //R-Peaks müssen noch gebildet werden
	bool		reset(iarray_t curve, iarray_t rpeaks); //Aufrufender hat RPeaks schon gebildet
	bool		first(iarray_t curve, iarray_t rpeaks); //Aufrufender hat RPeaks schon gebildet
	bool		next();
	bool		end();

__property iarray_t   heartbeat = { read=get_heartbeat  };

private:
	cArray		farray;
	iarray_t	fcurve;
	iarray_t	frpeaks;

	iarray_t	fheartbeat;
	iarray_t	get_heartbeat();

	sArrayCha	charac; //todo getter und setter machen

	int			findex;

    };
#endif

