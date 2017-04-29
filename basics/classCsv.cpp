//todo: anpassen auf dyn Formate
//---------------------------------------------------------------------------
#pragma hdrstop

#include "classCsv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cCsv::cCsv()
	{
	fp = NULL;
	}
//---------------------------------------------------------------------------
cCsv::~cCsv()
	{
	CloseFile();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cCsv::OpenFile(String file, eDatFormat format, String delim) //delim wurde vorbesetzt mit ;
	{
	if (file == "")
		{
		return fail(EC_NOFILE, "keine Datei �bergeben");
		}

	fp = fopen(file.c_str(), "r");
	if (fp == NULL)
		{
		return fail(EC_FNF, "Datei nicht gefunden: " + file);
		}

	strcpy(Delim, delim.c_str());
	Format = format;

	LineCount = -1;

	fseek(fp, 0, SEEK_END);
	fpMax = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return ok();
	}
//---------------------------------------------------------------------------
void cCsv::CloseFile()
	{
	if (fp != NULL)
		{
		fclose(fp);
		fp = NULL;
		}
	}
//---------------------------------------------------------------------------
bool cCsv::Reset()
	{
	if (fseek(fp, 0, SEEK_SET) == 0)
		return ok();
	else
		return fail(EC_FPSEEK, "Filepointer konnte nicht zur�ckgesetzt werden");
	}
//---------------------------------------------------------------------------
bool cCsv::StartAt(int sample)
	{
	if (!Skip()) return false;
	if (sample == -1) //von Anfang an lesen
		return ok();
	else
		{
		int rc = false;
		while (Next())
			{
			if (EcgLine.sample >= sample)
				{
				//genauen Wert oder den n�chsten gefunden, EKG-Werte stehen durch
				//Next() bereits in EcgLine
				rc = true;
				break;
				}
			}

		return rc;
		}
	}
//---------------------------------------------------------------------------
bool cCsv::Skip()
	{
	//erste(n) Zeilen ggf. �berlesen (�berschriften usw.)
	if (fp == NULL)
		return fail(EC_NOFP, "(skip) keine Datei vorhanden");

	bool fehler = false;
	if (Format == formatNone)
		{
		if (!SkipRow())
			fehler = true;
		}

	else if (Format == formatADS)
		{
		//im ADS-Format sind 12 Zeilen zu �berlesen
		//(elf f�r allg Infos und eine f�r �berschriften)
		for (int i = 0; i < 12; i++)
			{
			if (!SkipRow())
				{
				fehler = true;
				break;
				}
			LineCount++;
			}
		}

	return !fehler;
	}
//---------------------------------------------------------------------------
bool cCsv::SkipRow()
	{
	//eine Zeile �berspringen
	if (fgets(rowbuf, sizeof(rowbuf)-1, fp) == NULL)
		return fail(EC_NOROW, "(skip) keine Zeile einzulesen");
	LineCount++;
	return ok();
	}
//---------------------------------------------------------------------------
bool cCsv::First()
	{
	return Next();
	}
//---------------------------------------------------------------------------
bool cCsv::Next()
	{
	if (fp == NULL)
		return fail(EC_NOFP, "(next) keine Datei vorhanden");

	do
		{
		if (fgets(rowbuf, sizeof(rowbuf)-1, fp) == NULL)
			return fail(EC_NOROW, "(skip) keine Zeile einzulesen");

		} while (String(rowbuf) == "\n");

	LineCount++;
	return ParseLine();
	}
//---------------------------------------------------------------------------
bool cCsv::NextUntil(int sample)
	{
	if (!Next()) return false;
	if (sample > 0 && EcgLine.sample > sample)
		{
		//hier aufh�ren
		return false;
		}
	return true;
	}
//---------------------------------------------------------------------------
bool cCsv::ParseLine()
	{
	//die Werte werden Semikolon- oder Tabgetrennt aufgef�hrt
	char value[128];
	char* pt;
	float val;

	bool rc = true;
	for (int i = 0; i < 2; i++)
		{
		pt = strchr(rowbuf, Delim[0]);
		if (pt == NULL)
			{
			fail(EC_NOFIELD, "(parse) Feld konnte nicht eingelesen werden");
			rc = false;
			break;
			}

		*pt = 0;
		String test = String(rowbuf);
		int n = test.Pos(",");
		if (n > 0)
			test = test.SubString(0, n-1) + "." + test.SubString(n+1, 9999);
		strcpy(value, test.c_str());

		//Komma durch Punkt ersetzen, damit die Nachkommastellen richtig rauskommen

		val = atof(value);

		if (Format == formatNone)
			{
			//1. Spalte = SampleNo, 2. Spalte = LeadI usw.
			switch (i)
				{
				case 0: EcgLine.sample = LineCount; break;
				case 1: EcgLine.i      = val;		break;
				case 2: /*EcgLine.ii = val;*/ 		break;
				default: break;
				}
			}

		else if (Format == formatADS)
			{
			//1. Spalte = LeadI, 2. Spalte = LeadII, usw.
			switch (i)
				{
				case 0: EcgLine.sample = LineCount;
						EcgLine.i      = val;
						break;
				case 1: /*EcgLine.ii = val;*/ break;
				default: break;
				}
			}

		strcpy(rowbuf, pt+1);
		}

	EcgLine.lineno = LineCount;
	return rc;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   getter und setter   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int	cCsv::getFileMax()
	{
	return fpMax;
	}
//---------------------------------------------------------------------------
int	cCsv::getFilePos()
	{
	return ftell(fp);
	}
//---------------------------------------------------------------------------
int cCsv::getLineNo()
	{
	return EcgLine.lineno;
	}
//---------------------------------------------------------------------------
int cCsv::getSample()
	{
	return EcgLine.sample;
	}
//---------------------------------------------------------------------------
float cCsv::getI()
	{
	return EcgLine.i;
	}
//---------------------------------------------------------------------------
