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
class PACKAGE cRpeaks : public cBase
	{
public:
	cRpeaks();
	~cRpeaks();


	iarray_t	find(iarray_t array, TImage* img1);

private:
	cMath*		fmath;
	cArray*		farray;

	sArrayCha	charac; //todo getter und setter machen

	};
//---------------------------------------------------------------------------
#endif
