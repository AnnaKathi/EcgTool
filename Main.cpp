//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "algorithms/EinzelAusw.h"
#include "database/classMySql.h"
#include "database/DbPersonen.h"
#include "algorithms/Alg1.h"
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
	setStatus("startup EcgTool...loading MySql-Database");
	if (!fmysql.open())
		{
		String msg =
			"Die MySql-Datenbank 'ecg' konnte nicht geöffnet werden."
			"Die Funktion meldet: " + fmysql.error_msg;
		Application->MessageBox(msg.c_str(), "Fehler beim Öffnen der Datenbank", MB_OK);
		Close();
		return;
		}

	//todo Anzahl der versch. Datensätze laden und anzeigen
	setStatus("startup EcgTool...reading MySql-Database");
	setDbInfo();

	setStatus("Startup finished - ready to go");
	pnMain->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
	{
	fmysql.close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmMain::setStatus(String status, int panel) //panel ist vorbesetzt mit 0
	{
	sbMain->Panels->Items[panel]->Text = status;
	}
//---------------------------------------------------------------------------
void TfmMain::setDbInfo()
	{
	String msg =
		String(fmysql.people.getSize()) + " Personen, " +
		String(fmysql.diseases.getSize()) + " Erkrankungen, " +
		String(fmysql.ecg.getSize()) + " EKG-Datensätze";
	setStatus(msg, 1);
	}
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
	setDbInfo();
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
	setDbInfo();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acDiseasesExecute(TObject *Sender)
	{
	DlgDiseases(this);
	setDbInfo();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acCreateSeesionExecute(TObject *Sender)
	{
	if (!DlgNewSession(this))
		;
	setDbInfo();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acSingleAuswExecute(TObject *Sender)
	{
	LoadAlgorithmus1(this);
	//todo später: DlgEinzelAuswertung(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acGesAuswExecute(TObject *Sender)
	{
	//
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

