//---------------------------------------------------------------------------
#pragma hdrstop

#include "cCsv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cCsv::cCsv()
	{
	fp = NULL;
	ErrorMessage = "";
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
bool cCsv::OpenFile(String file, String delim)
	{
	if (file == "")
		{
		ErrorMessage = "keine Datei übergeben";
		return false;
		}

	fp = fopen(file.c_str(), "r");
	if (fp == NULL)
		{
		ErrorMessage = "Datei nicht gefunden: " + file;
		return false;
		}

	strcpy(Delim, delim.c_str());

	LineCount = -1;

	fseek(fp, 0, SEEK_END);
	fpMax = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return true;
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
		return true;
	else
		{
		ErrorMessage = "Filepointer konnte nicht zurückgesetzt werden";
		return false;
		}
	}
//---------------------------------------------------------------------------
bool cCsv::StartAt(int sample)
	{
	if (!Skip()) return false;
	if (sample == -1) //von Anfang an lesen
		return true;
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
	//erste Zeile überlesen (Überschriften)
	if (fp == NULL)
		{
		ErrorMessage = "(next) keine Datei vorhanden";
		return false;
		}

	if (fgets(rowbuf, sizeof(rowbuf)-1, fp) == NULL)
		{
		ErrorMessage = "(next) keine Zeile einzulesen";
		return false;
		}

	LineCount++;
	return true;
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
		{
		ErrorMessage = "(next) keine Datei vorhanden";
		return false;
		}

	do
		{
		if (fgets(rowbuf, sizeof(rowbuf)-1, fp) == NULL)
			{
			ErrorMessage = "(next) keine Zeile einzulesen";
			return false;
			}
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
	//die Werte werden Kommagetrennt aufgeführt
	char value[128];
	char* pt;
	float val;

	bool rc = true;
	for (int i = 0; i < 2; i++)
		{
		pt = strchr(rowbuf, Delim[0]);
		if (pt == NULL)
			{
			ErrorMessage = "(parse) Feld konnte nicht eingelesen werden";
			rc = false;
			break;
			}

		*pt = 0;
		String test = String(rowbuf);
		int n = test.Pos(",");
		if (n > 0)
			test = test.SubString(0, n-1) + "." + test.SubString(n+1, 9999);
		strcpy(value, test.c_str());

		//Komma durch PUnkt ersetzen, damit die Nachkommastellen richtig rauskommen

		val = atof(value);

		switch (i)
			{
			case 0: EcgLine.sample = val; break;
			case 1: EcgLine.i      = val; break;
			default: break;
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
String cCsv::getError()
	{
	return ErrorMessage;
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

