//---------------------------------------------------------------------------
#ifndef classQrsH
#define classQrsH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include "../basics/classBase.h"
#include "classHeartbeat.h"
//---------------------------------------------------------------------------
class cHeartbeat; //wenn zirkelbezug ?
class PACKAGE cQrs : public cBase
	{
public:
	cQrs();

	void		run();
    int			calc();

private:

    };
#endif
