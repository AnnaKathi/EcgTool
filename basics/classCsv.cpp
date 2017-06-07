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
bool cCsv::OpenFile(String file, eDatFormat format, String delim, int lead)
	{
	if (file == "")
		{
		return fail(EC_NOFILE, "keine Datei übergeben");
		}

	fp = fopen(file.c_str(), "r");
	if (fp == NULL)
		{
		return fail(EC_FNF, "Datei nicht gefunden: " + file);
		}

	strcpy(Delim, delim.c_str());
	Format = format;
	Lead = lead;

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
		return fail(EC_FPSEEK, "Filepointer konnte nicht zurückgesetzt werden");
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
				//genauen Wert oder den nächsten gefunden, EKG-Werte stehen durch
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
	//erste(n) Zeilen ggf. überlesen (Überschriften usw.)
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
		//im ADS-Format sind 12 Zeilen zu überlesen
		//(elf für allg Infos und eine für Überschriften)
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
	//eine Zeile überspringen
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
		//hier aufhören
		return false;
		}
	return true;
	}
//---------------------------------------------------------------------------
bool cCsv::ParseLine()
	{
	//die Werte werden Semikolon- oder Tabgetrennt aufgeführt
	char value[128];
	char* pt;
	float val;

	for (int i = 0; i < Lead; i++)
		{
		//Felder überspringen
		pt = strchr(rowbuf, Delim[0]);
		*pt = 0;
		strcpy(rowbuf, pt+1);
		}

	//jetzt kommt das gewünschte Feld
	String feld;
	pt = strchr(rowbuf, Delim[0]);
	if (pt == NULL)
		{
		//Feld ist das letzte Feld
		feld = String(rowbuf);
		}
	else
		{
		//Feld ist nicht das letzte Feld
		*pt = 0;
		feld = String(rowbuf);
		}

	//Komma durch Punkt ersetzen, damit die Nachkommastellen richtig rauskommen
	int n = feld.Pos(",");
	if (n > 0)
		feld = feld.SubString(0, n-1) + "." + feld.SubString(n+1, 9999);
	strcpy(value, feld.c_str());

	val = atof(value);

	EcgLine.sample = LineCount;
	EcgLine.lineno = LineCount;
	EcgLine.i = val;
	return ok();
	}
//---------------------------------------------------------------------------
bool cCsv::ParseLineOld()
	{
	//die Werte werden Semikolon- oder Tabgetrennt aufgeführt
	char value[128];
	char* pt;
	float val;

	bool rc = true;
	int max;
	if (Format == formatNone) max = 8;
	else if (Format == formatADS) max = 7;

	String feld;
	for (int i = 0; i <= max; i++)
		{
		pt = strchr(rowbuf, Delim[0]);
		if (pt == NULL && i < max)
			{
			fail(EC_NOFIELD, "(parse) Feld " + String(i) + " konnte nicht eingelesen werden");
			rc = false;
			break;
			}
		else if (pt == NULL)
			{
			//letztes Feld erreicht
			feld = String(rowbuf);
			}
		else
			{
			*pt = 0;
			feld = String(rowbuf);
			strcpy(rowbuf, pt+1);
			}

		//Komma durch Punkt ersetzen, damit die Nachkommastellen richtig rauskommen
		int n = feld.Pos(",");
		if (n > 0)
			feld = feld.SubString(0, n-1) + "." + feld.SubString(n+1, 9999);
		strcpy(value, feld.c_str());

		val = atof(value);

		if (Format == formatNone)
			{
			//1. Spalte = SampleNo, 2. Spalte = LeadI usw.
			switch (i)
				{
				case 0: EcgLine.sample = LineCount; break;
				case 1: EcgLine.i      = val;		break;
				case 2: EcgLine.ii     = val; 		break;
				case 3: EcgLine.v1     = val; 		break;
				case 4: EcgLine.v2     = val; 		break;
				case 5: EcgLine.v3     = val; 		break;
				case 6: EcgLine.v4     = val; 		break;
				case 7: EcgLine.v5     = val; 		break;
				case 8: EcgLine.v6     = val; 		break;
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
				case 1: EcgLine.ii     = val; 		break;
				case 2: EcgLine.v1     = val; 		break;
				case 3: EcgLine.v2     = val; 		break;
				case 4: EcgLine.v3     = val; 		break;
				case 5: EcgLine.v4     = val; 		break;
				case 6: EcgLine.v5     = val; 		break;
				case 7: EcgLine.v6     = val; 		break;
				default: break;
				}
			}
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

