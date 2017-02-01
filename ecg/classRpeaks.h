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

	iarray_t	find(iarray_t array, TImage* img1, TImage* img2);

private:
	cMath*		fmath;
	cArray*		farray;

	iarray_t	fdesc; //absteigende Array-Werte

	};
//---------------------------------------------------------------------------
#endif
