//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "database/classMySql.h"
#include "database/DbPersonen.h"
#include "Diseases.h"
#include "EcgView.h"
#include "Session.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
extern cMySql fmysql;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmMain::~TfmMain()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);

	if (!fmysql.open())
		{
		String msg =
			"Die MySql-Datenbank 'ecg' konnte nicht geöffnet werden."
			"Die Funktion meldet: " + fmysql.error_msg;
		Application->MessageBox(msg.c_str(), "Fehler beim Öffnen der Datenbank", MB_OK);
		Close();
		return;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	fmysql.close();
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
void __fastcall TfmMain::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acLookIntoECGExecute(TObject *Sender)
	{
	//Formular EcgView aufrufen, ein bestimmtes EKG untersuchen
	TfmEcg* formecg = new TfmEcg(this);
	if (!formecg->Execute())
		;
	delete formecg;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acShowDataExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acPeopleExecute(TObject *Sender)
	{
	DlgDatabasePersonen(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acDiseasesExecute(TObject *Sender)
	{
	DlgDiseases(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acCreateTempExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acCreateSeesionExecute(TObject *Sender)
	{
	if (!DlgNewSession(this))
		;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormKeyPress(TObject *Sender, char &Key)
	{
	acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------


