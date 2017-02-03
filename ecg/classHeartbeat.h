//---------------------------------------------------------------------------
#ifndef classHeartbeatH
#define classHeartbeatH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classArray.h"
//---------------------------------------------------------------------------
class PACKAGE cHeartbeats : public cBase
	{
public:
	cHeartbeats();
	~cHeartbeats();

	bool		build(iarray_t curve, iarray_t rpeaks);

	iarray_t	first();
	iarray_t	next();

private:
	cArray		farray;
	iarray_t	fheartbeats;

	int			findex;

    };
#endif

