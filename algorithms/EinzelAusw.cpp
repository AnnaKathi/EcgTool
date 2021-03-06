//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EinzelAusw.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSingle *fmSingle;
//---------------------------------------------------------------------------
bool DlgEinzelAuswertung(TForm* Papa)
	{
	TfmSingle* Form = new TfmSingle(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmSingle::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmSingle::TfmSingle(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmSingle::~TfmSingle()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmSingle::FormShow(TObject *Sender)
	{
    tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSingle::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);
	pnFilterPerson->Caption = "";
	pnFilterEcg->Caption    = "";

	fmPeople  = CreatePeopleForm(this, pnFilterPerson);
	fmEcgData = CreateEcgForm(this,    pnFilterEcg);

	fmPeople->ShowData();
	fmEcgData->ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSingle::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	delete fmPeople;
	delete fmEcgData;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSingle::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSingle::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

