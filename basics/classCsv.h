//---------------------------------------------------------------------------
#ifndef classCsvH
#define classCsvH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
class PACKAGE cCsv : public cBase
	{
public:
	cCsv();
	~cCsv();

	String		readFile(String file);
	
private:

	};
//---------------------------------------------------------------------------
#endif
