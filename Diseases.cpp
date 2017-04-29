//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Diseases.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmDiseases *fmDiseases;
//---------------------------------------------------------------------------
bool DlgDiseases(TForm* Papa)
	{
	TfmDiseases* Form = new TfmDiseases(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmDiseases::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmDiseases::TfmDiseases(TComponent* Owner)
	: TForm(Owner)
	{
	fmDiseases = CreateDiseaseForm(this, pnDiseases);
	}
//---------------------------------------------------------------------------
__fastcall TfmDiseases::~TfmDiseases()
	{
	delete fmDiseases;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDiseases::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDiseases::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	fmDiseases->ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmDiseases::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmDiseases::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------

