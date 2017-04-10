//---------------------------------------------------------------------------
#ifndef classLDAH
#define classLDAH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <System.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
//---------------------------------------------------------------------------
class PACKAGE cLDA : public cBase
	{
public:
	cLDA();
	~cLDA();

	double		singleCheck(iarray_t temp1, iarray_t temp2, int mode);
	bool		testAlgLib();

private:

	};
//---------------------------------------------------------------------------
#endif
