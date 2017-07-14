//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EcgLeadAnalysis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmEcgLeads *fmEcgLeads;
//---------------------------------------------------------------------------
bool DlgShowEcgLeads(TForm* Papa)
	{
	TfmEcgLeads* Form = new TfmEcgLeads(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmEcgLeads::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmEcgLeads::TfmEcgLeads(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgLeads::FormShow(TObject *Sender)
	{
    tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgLeads::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmLeads1 = CreateLeadForm(this, pnEcg1, 1);
	fmLeads2 = CreateLeadForm(this, pnEcg2, 1);
	fmLeads3 = CreateLeadForm(this, pnEcg3, 1);
	fmLeads4 = CreateLeadForm(this, pnEcg4, 1); 

	fmLeads1->Show();
	fmLeads2->Show();
	fmLeads3->Show();
	fmLeads4->Show();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgLeads::FormClose(TObject *Sender, TCloseAction &Action)
	{
	delete fmLeads1;
	delete fmLeads2;
	delete fmLeads3;
	delete fmLeads4;
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
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEcgLeads::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgLeads::cbAnsichtChange(TObject *Sender)
	{
	int ansicht = cbAnsicht->ItemIndex + 1;
	fmLeads1->RefreshView(ansicht);
	fmLeads2->RefreshView(ansicht);
	fmLeads3->RefreshView(ansicht);
	fmLeads4->RefreshView(ansicht);
	}
//---------------------------------------------------------------------------

