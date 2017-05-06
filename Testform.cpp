//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <System.hpp>

#include "Testform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmTest *fmTest;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgTestform(TForm* Papa)
	{
	TfmTest* Form = new TfmTest(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmTest::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmTest::TfmTest(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmTest::~TfmTest()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmTest::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmTest::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmDiseases = CreateDescForm(this, pnDesc1, fmysql.diseases);
	fmOrte     = CreateDescForm(this, pnDesc2, fmysql.orte);
	fmLagen    = CreateDescForm(this, pnDesc3, fmysql.lagen);
	}
//---------------------------------------------------------------------------
void __fastcall TfmTest::FormClose(TObject *Sender, TCloseAction &Action)
	{
	delete fmDiseases;
	delete fmOrte;
	delete fmLagen;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmTest::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------

