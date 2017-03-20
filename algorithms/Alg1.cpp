/* Testalgorithmus 1: Testet das grundlegende Prinzip
 * =================
 * Aus den eingelesenen EKG-Werten wird ein Erkennungs-Wert berechnet, um die
 * grundlegende Funktionsweise des Systems zu validieren. Dazu werden die
 * folgenden Schritte durchgeführt:
 *
 * 1) Auf der ersten Ableitung den Standardherzschlag feststellen
 * 2) Aus dem Standardherzschlag die Differenz zwischen dem höchsten und dem
 *		niedrigsten Wert feststellen (= Erkennungswert)
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
bool DlgAlgorithmus1(TForm* Papa, cEcg& ecg)
	{
	TfmAlg1* Form = new TfmAlg1(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(ecg);
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
bool TfmAlg1::Execute(cEcg& ecg) //für den Aufruf mit Formular
	{
	bPrintMsg = true;
	fecg = &ecg;
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
double TfmAlg1::GetIdent(cEcg& ecg) //für Direktaufruf von außen, ohne Formular
	{
	bPrintMsg = false;
	fecg = &ecg;
	FindBeat();
	return CalcRange();
	}
//---------------------------------------------------------------------------
__fastcall TfmAlg1::TfmAlg1(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmAlg1::~TfmAlg1()
	{
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

	farray.redisplay(fecg->data.data_array, img);
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
bool TfmAlg1::FindBeat() //Schritt 1
	{
	Print("--------------------------------------------");
	Print("1 - Berechne Standardherzschlag auf 1. Ableitung...");

	fecg->heart.calcAvBeat(fecg->data.derivate1.deriv_array);
	Print("\t...durchschnittlichen Herzschlag ermittelt");

	farray.redisplay(fecg->heart.avBeat, imgBeat);
	Print("\t...Herzschlag dargestellt");

	Print("...Standardherzschlag ermittelt.");
	return true;
	}
//---------------------------------------------------------------------------
double TfmAlg1::CalcRange() //Schritt 2
	{
	Print("--------------------------------------------");
	Print("2 - Berechne Maximalausschlag...");

	sArrayCha	fc;
	farray.resetValues(fecg->heart.avBeat, fc);
	double range = (fc.MaxWert - fc.MinWert) * 1000;
	Print("\t...Wert berechnet: %.6f", range);

	edRange->Text = String(range);
	Print("...Maximalausschlag ermittelt.");
	return range;
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
void __fastcall TfmAlg1::btStep1Click(TObject *Sender)
	{
	FindBeat();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAlg1::btStep2Click(TObject *Sender)
	{
	Range = CalcRange();
	}
//---------------------------------------------------------------------------

