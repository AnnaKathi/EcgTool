//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "algorithms/AlgChoi.h"
#include "algorithms/AlgChoi2.h"
#include "algorithms/EinzelAusw.h"
#include "algorithms/Alg1.h"
#include "database/classMySql.h"
#include "database/DbPersonen.h"
#include "EcgView.h"
#include "DataAnalysis.h"
#include "Session.h"
#include "Testform.h"
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
	pnMain->Enabled = false;
	Cursor = crHourGlass;

	setStatus("startup EcgTool...loading MySql-Database");

	if (!setupDatabase())
		{
		Close();
		return;
		}

	setStatus("startup EcgTool...reading MySql-Database");
	setDbInfo();

	setStatus("Startup finished - ready to go");
	Cursor = crDefault;
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
bool TfmMain::setupDatabase()
	{
	//falls die Datenbank nicht vorhanden ist, anlegen
	setStatus("startup Database...checking existance");
	if (!fmysql.openWithoutDb())
		{
		Application->MessageBox(
			ftools.fmt(
				"Die MySql-Datenbankverbindung konnte nicht initialisiert werden. "
				"Die Funktion meldet: %s", fmysql.error_msg).c_str(),
			"Fehler beim Öffnen der Datenbank",
			MB_OK);
		return false;
		}

	if (!fmysql.dbExists())
		{
		if (Application->MessageBox(
			ftools.fmt(
				"Die MySql-Datenbank 'ecg' ist nicht vorhanden. "
				"Soll sie nun vom Programm erstellt werden ?\n\n"
				"Ansonsten wird das Programm abgebrochen.").c_str(),
			"Datenbank erstellen ?",
			MB_YESNO) == IDNO)
			{
			//todo?? fmysql.close();
			return false;
			}

		setStatus("startup Database...creating databse");
		if (!fmysql.create())
			{
			Application->MessageBox(
				ftools.fmt(
					"Die MySql-Datenbank 'ecg' konnte nicht initialisiert werden. "
					"Die Funktion meldet: %s", fmysql.error_msg).c_str(),
				"Fehler beim Öffnen der Datenbank",
				MB_OK);
			return false;
			}
		}

	if (!fmysql.close())
		;

	//Datenbank öffnen
	setStatus("startup Database...opening database");
	if (!fmysql.open())
		{
		Application->MessageBox(
			ftools.fmt(
				"Die MySql-Datenbank 'ecg' konnte nicht geöffnet werden. "
				"Die Funktion meldet: %s", fmysql.error_msg).c_str(),
			"Fehler beim Öffnen der Datenbank",
			MB_OK);
		return false;
		}

	setStatus("startup Database...ready");
	return true;
	}
//---------------------------------------------------------------------------
void TfmMain::setStatus(String status, int panel) //panel ist vorbesetzt mit 0
	{
	sbMain->Panels->Items[panel]->Text = status;
	}
//---------------------------------------------------------------------------
void TfmMain::setDbInfo()
	{
	setStatus(
		ftools.fmt("%d Personen, %d Erkrankenungen, %d EKG-Datensätze",
		fmysql.people.getSize(),
		fmysql.diseases.getSize(),
		fmysql.ecg.getSize()), 1);
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
void __fastcall TfmMain::acLookIntoDataExecute(TObject *Sender)
	{
	DlgAnalyseData(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acChoi2016Execute(TObject *Sender)
	{
	//DlgAlgChoi(this);
	DlgAlgChoi2(this);
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
void __fastcall TfmMain::btMySqlTestClick(TObject *Sender)
	{
	DlgTestform(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::BitBtn7Click(TObject *Sender)
	{
	DlgAlgChoi(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::BitBtn8Click(TObject *Sender)
	{
	DlgAlgChoi2(this);
	}
//---------------------------------------------------------------------------

