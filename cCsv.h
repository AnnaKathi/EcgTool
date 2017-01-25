//---------------------------------------------------------------------------
#ifndef cCsvH
#define cCsvH
//---------------------------------------------------------------------------
#include <StdCtrls.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
struct cEcgLine
	{
	int 	lineno;
	int		sample;
	float	i;
	};
//---------------------------------------------------------------------------
class cCsv
	{
private:
	FILE*		fp;
	String		ErrorMessage;
	int         fpMax;

	int			LineCount;
	char		rowbuf[128];
	char		Delim[2];
	cEcgLine	EcgLine;

	bool 		Skip();
	bool 		ParseLine();


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

	String 		getError();
	int 		getLineNo();
	int 		getSample();
	float 		getI();
	};
//---------------------------------------------------------------------------
#endif
