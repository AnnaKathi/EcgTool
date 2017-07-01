//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EcgLeadAnalysis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmEcgLeads *fmEcgLeads;
//---------------------------------------------------------------------------
bool DlgShowEcgLeads(TForm* Papa, String path, String name)
	{
	if (path == "") return false;
	if (!DirectoryExists(path)) return false;

	TfmEcgLeads* Form = new TfmEcgLeads(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(path, name);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmEcgLeads::Execute(String path, String name)
	{
	fPath = path;
	fName = name;
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
	laInfo->Caption = "ECG <" + fName + ">";

	String ecg1 = ftools.fmt("%s\\%s liegend.txt", fPath, fName);
	String ecg2 = ftools.fmt("%s\\%s sitzend.txt", fPath, fName);
	String ecg3 = ftools.fmt("%s\\%s stehend.txt", fPath, fName);
	String ecg4 = ftools.fmt("%s\\%s gehend.txt",  fPath, fName);

	fmLeads1 = CreateLeadForm(this, pnEcg1); fmLeads1->setEcg(ecg1, fName + " liegend");
	fmLeads2 = CreateLeadForm(this, pnEcg2); fmLeads2->setEcg(ecg2, fName + " sitzend");
	fmLeads3 = CreateLeadForm(this, pnEcg3); fmLeads3->setEcg(ecg3, fName + " stehend");
	fmLeads4 = CreateLeadForm(this, pnEcg4); fmLeads4->setEcg(ecg4, fName + " gehend");

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
