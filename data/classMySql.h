//---------------------------------------------------------------------------
#ifndef classMySqlH
#define classMySqlH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classCsv.h"
//---------------------------------------------------------------------------
class PACKAGE cMySql : public cBase
	{
public:
	cMySql();
	~cMySql();

	bool		saveToDbase(String name, String pos, iarray_t array);

private:
	cCsv*		fcsv;

	};
//---------------------------------------------------------------------------
#endif
