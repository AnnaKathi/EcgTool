/* Testalgorithmus 1: Testet das grundlegende Prinzip mit simulierten AC/LDA
 * =================
 * Der Algorithmus soll Funktionen für die Template-Bildung und für die spätere
 * Klassifizerung anbieten:
 *
 * Funktionen
 * ----------
 * bool createTemplate(cEcg ecg), erstellt das AC-Template und speichert dieses in der Db ab
 * bool	singleCheck(temp1, temp2), vergleicht zwei Templates mit LDA
 * bool intraCheck(temp), erstellt über dem template einen Intraindividuellen Check
 * bool interCheck(temp), erstellt über dem template einen Interindividuellen Check
 * bool kreuzCheck(temp), erstellt über dem template einen Kreuz-Check
 */
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "Alg1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmAlg1 *fmAlg1;
//---------------------------------------------------------------------------
bool LoadAlgorithmus1(TForm* Papa)
	{
	TfmAlg1* Form = new TfmAlg1(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Startup();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool DlgAlgorithmus1(TForm* Papa, cEcg& ecg1, cEcg& ecg2)
	{
	TfmAlg1* Form = new TfmAlg1(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(ecg1, ecg2);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
double GetAlgorithmus1(TForm* Papa, cEcg& ecg)
	{
	TfmAlg1* Form = new TfmAlg1(Papa);
	double rc = 0.0;

	if (Form)
		{
		rc = Form->GetIdent(ecg);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmAlg1::Startup() //für den Aufruf mit Formular aber EKG selber laden
	{
	bPrintMsg = true;
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAlg1::Execute(cEcg& ecg1, cEcg& ecg2) //für den Aufruf mit Formular
	{
	bPrintMsg = true;
	fecg1 = &ecg1;
	fecg2 = &ecg2;
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
double TfmAlg1::GetIdent(cEcg& ecg) //für Direktaufruf von außen, ohne Formular
	{
	bPrintMsg = false;
	fecg1 = &ecg;
	FindBeat();
	//return CalcRange();
	}
//---------------------------------------------------------------------------
__fastcall TfmAlg1::TfmAlg1(TComponent* Owner)
	: TForm(Owner), fecg1 (new cEcg), fecg2 (new cEcg)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmAlg1::~TfmAlg1()
	{
	delete fecg1;
	delete fecg2;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	/*
	farray.redisplay(fecg1->data.data_array, img1);
	farray.redisplay(fecg2->data.data_array, img2);
	*/
	Print("Algorithmus 1 ist startbereit");
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmAlg1::Print(char* msg, ...)
	{
	if (!bPrintMsg) return;
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	Memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
bool TfmAlg1::GetEcgs() //Schritt 0
	{
	Print("--------------------------------------------");
	Print("0 - Lade EKG-Daten...");

	String delim = "\t";
	if (!fecg1->data.getFile(edInput1->Text, delim, -1, -1))
		{
		Print("\t...## Fehler aufgetreten: %d, %s", fecg1->data.error_code, fecg1->data.error_msg);
		return false;
		}

	if (!fecg2->data.getFile(edInput2->Text, delim, -1, -1))
		{
		Print("\t...## Fehler aufgetreten: %d, %s", fecg2->data.error_code, fecg2->data.error_msg);
		return false;
		}
	Print("\t...EKG-Daten eingelesen");

	if (!fecg1->data.buildDerivates())
		{
		Print("## Fehler aufgetreten: %d, %s", fecg1->data.error_code, fecg1->data.error_msg);
		return false;
		}

	if (!fecg2->data.buildDerivates())
		{
		Print("## Fehler aufgetreten: %d, %s", fecg2->data.error_code, fecg2->data.error_msg);
		return false;
		}
	Print("\t...Ableitungen gebildet");

	farray.redisplay(fecg1->data.data_array, img1);
	farray.redisplay(fecg2->data.data_array, img2);
	Print("\t...EKG-Daten dargestellt");

	Print("...EKG-Daten geladen");
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAlg1::FindBeat() //Schritt 1
	{
	Print("--------------------------------------------");
	Print("1 - Berechne Standardherzschläge auf 1. Ableitung...");

	fecg1->heart.calcAvBeat(fecg1->data.derivate1.deriv_array);
	fecg2->heart.calcAvBeat(fecg2->data.derivate1.deriv_array);
	Print("\t...durchschnittliche Herzschläge ermittelt");

	farray.redisplay(fecg1->heart.avBeat, imgBeat1);
	farray.redisplay(fecg2->heart.avBeat, imgBeat2);
	Print("\t...Herzschläge dargestellt");

	Print("...Standardherzschlag ermittelt.");
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAlg1::CreateTemplate() //Schritt 2
	{
	Print("--------------------------------------------");
	Print("2 - Erstelle AC-Templates auf Standardherzschlägen...");

	if (!fac1.createTemplate(fecg1->heart.avBeat))
		{
		Print("\t...## Fehler: Template 1 konnte nicht berechnet werden!");
		return false;
		}
	else
		Print("\t...Template 1 berechnet");

	if (!fac2.createTemplate(fecg2->heart.avBeat))
		{
		Print("\t...## Fehler: Template 2 konnte nicht berechnet werden!");
		return false;
		}
	else
		Print("\t...Template 2 berechnet");

	farray.redisplay(fac1.temp, imgTemplate1);
	farray.redisplay(fac2.temp, imgTemplate2);
	Print("\t...Templates dargestellt");

	Print("...AC-Template erstellt");
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAlg1::Klassifizierung() //Schritt 3
	{
	Print("--------------------------------------------");
	Print("3 - Klassifizierung durchführen...");

	double conformity = flda.singleCheck(fac1.temp, fac2.temp, cbMode->ItemIndex);
	Print("\t...Conformity berechnet");

	ed3->Text = String(conformity);
	Print("\t...Conformity = %.4f", conformity);

    Print("...Klassifizierung durchgeführt");
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::acCloseExecute(TObject *Sender)
	{
	Print("Goodbye...");
	Sleep(500);
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btStep0Click(TObject *Sender)
	{
	GetEcgs();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btStep1Click(TObject *Sender)
	{
	FindBeat();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btStep2Click(TObject *Sender)
	{
	CreateTemplate();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btStep3Click(TObject *Sender)
	{
	Klassifizierung();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btInputfile1Click(TObject *Sender)
	{
	if (OpenDialog->Execute())
		edInput1->Text = OpenDialog->FileName;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btInputfile2Click(TObject *Sender)
	{
	if (OpenDialog->Execute())
		edInput2->Text = OpenDialog->FileName;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btAlgLibClick(TObject *Sender)
	{
	flda.testAlgLib();
	}
//---------------------------------------------------------------------------

