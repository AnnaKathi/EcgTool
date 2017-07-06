//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <System.hpp>

#include "Wavelet.h"
//---------------------------------------------------------------------------
#define DecompLevel 3
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmWavelet *fmWavelet;
//---------------------------------------------------------------------------
bool DlgShowWavelet(TForm* Papa)
	{
	TfmWavelet* Form = new TfmWavelet(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmWavelet::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmWavelet::TfmWavelet(TComponent* Owner)
	: TForm(Owner)
	{
	wavelib.setMemo(mInfo);
	fWaveObj = wavelib.wave_init("db4");
	fWaveTransform = wavelib.wt_init(fWaveObj, "dwt", 3000, DecompLevel);
	}
//---------------------------------------------------------------------------
__fastcall TfmWavelet::~TfmWavelet()
	{
	wavelib.wt_free(fWaveTransform);
	wavelib.wave_free(fWaveObj);
	}
//---------------------------------------------------------------------------
void TfmWavelet::print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	mInfo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
void __fastcall TfmWavelet::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmWavelet::btPrint1Click(TObject *Sender)
	{
	mInfo->Lines->Clear();
	wavelib.wave_summary(fWaveObj);
	}
//---------------------------------------------------------------------------
void __fastcall TfmWavelet::btPrint2Click(TObject *Sender)
	{
	mInfo->Lines->Clear();
	wavelib.wt_summary(fWaveTransform);
	}
//---------------------------------------------------------------------------
void __fastcall TfmWavelet::btDwtClick(TObject *Sender)
	{
	Randomize();
	double input[3000];
	char help[8];
	for (int i = 0; i < 3000; i++)
		{
		sprintf(help, "%d,%d%d%d%d", Random(10), Random(10), Random(10), Random(10));
		input[i] = atof(help);
		}

	wavelib.dwt(fWaveTransform, input);

	pbProgress->Max = fWaveTransform->outlength;
	pbProgress->Position = 0;
	pbProgress->Visible = true;

	print("");
	print("--- Output -------------------");
	for (int i = 0; i < fWaveTransform->outlength; i++)
		{
		print("%03d: %.4f", i, fWaveTransform->output[i]);
		pbProgress->Position++;
		}

	print("");
	print("fertig!");
	}
//---------------------------------------------------------------------------

