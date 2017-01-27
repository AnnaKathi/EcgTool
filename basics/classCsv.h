//---------------------------------------------------------------------------
#ifndef classCsvH
#define classCsvH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <classes.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
enum CSV_ERROR_CODES
	{
	EC_OK,				// no error, all things done well
	EC_NOFILE,			// no file specified
	EC_FNF,				// file not found
	EC_FPSEEK,			// Filepointer konnte nicht zurückgesetzt werden
	EC_NOFP,			// Filepointer ist Null
	EC_NOROW,			// keien (weitere) Zeile vorhanden
	EC_NOFIELD,			// kein (weiteres) Feld vorhanden
	};
//---------------------------------------------------------------------------
struct cEcgLine
	{
	int 	lineno;
	int		sample;
	float	i;
	};
//---------------------------------------------------------------------------
class PACKAGE cCsv : public cBase
	{
public:
	cCsv();
	~cCsv();

	bool 		OpenFile(String file, String delim = ';');
	void 		CloseFile();
	bool 		Reset();

	bool 		StartAt(int sample);
	bool 		First();
	bool 		Next();
	bool 		NextUntil(int sample);

	int			getFileMax();
	int			getFilePos();

	int 		getLineNo();
	int 		getSample();
	float 		getI();

private:
	FILE*		fp;
	int         fpMax;

	int			LineCount;
	char		rowbuf[128];
	char		Delim[2];
	cEcgLine	EcgLine;

	bool 		Skip();
	bool 		ParseLine();

	};
//---------------------------------------------------------------------------
#endif
