//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "algorithms/AlgChoi.h"
#include "algorithms/AlgChoi2.h"
#include "algorithms/EinzelAusw.h"

#include "database/classMySql.h"
#include "database/DbPersonen.h"
#include "database/toolforms/addSession.h"

#include "EcgView.h"
#include "DataAnalysis.h"
#include "Sessions.h"
#include "Testform.h"
#include "ChoiFeatures.h"
#include "ChoiKlassifizierung.h"
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

	//Testschalter NoMySql berücksichtigen, ermöglichst einen Testbetrieb ohne MySql
	TIniFile* Ini = new TIniFile(ftools.GetIniFile());
	bNoMySql = Ini->ReadBool("MySql", "NoMySql", false);
	delete Ini;

	setStatus("startup EcgTool...loading MySql-Database");

	if (ftools.GetComputerBS() != "Windows")
		{
		if (Application->MessageBox(
			ftools.fmt(
				"Es wurde das Betriebssystem '%s' erkannt.\r\n\r\n"
				"Das Programm ist (vorläufig) auf ein Windows-Betriebssystem ausgelegt. "
				"Einige Funktionen sind mit anderen Betriebssystemem unter Umständen "
				"nicht verfügbar.\r\n\r\n"
				"Soll das EcgTool-Programm abgebrochen werden?",
				ftools.GetComputerBS()).c_str(),
			"Falsches Betriebssystem", MB_YESNO) == ID_YES)
			{
			Close();
			return;
			}
		}

	if (ftools.GetComputerProzessor() != "64Bit")
		{
		/*
		Application->MessageBox(
			ftools.fmt(
				"Es wurde der Systemtyp '%s' erkannt.\r\n\r\n"
				"Das Programm ist auf ein 64Bit-Windows-Betriebssystem ausgelegt. "
				"Einige Funktionen sind mit anderen Betriebssystemem unter Umständen "
				"nicht verfügbar, z.B. die Choi-SVM-Klassifizierung.\r\n\r\n",
				ftools.cpData.BSProzessor).c_str(),
			"Warnung 64Bit-System", MB_OK);
		*/
		setStatus("## 32Bit-System ggf. nicht ausreichend ##", 2);
		}
	else
		setStatus("64Bit-System  - ok", 2);

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
	if (bNoMySql) return true; //simulieren, die DB wär geöffnet worden

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
	if (bNoMySql)
		setStatus("### MySql-Datenbank wird nicht verwendet ###", 1);
	else
		setStatus(
		ftools.fmt("%d Personen, %d Sessions, %d EKG-Datensätze, %d Features",
		fmysql.people.getSize(),
		fmysql.sessions.getSize(),
		fmysql.ecg.getSize(),
		fmysql.features.getSize()), 1);
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
	DlgShowSessions(this);
	setDbInfo();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acSingleAuswExecute(TObject *Sender)
	{
	DlgChoiFeatures(this);
	setDbInfo();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acGesAuswExecute(TObject *Sender)
	{
	DlgChoiClassification(this);
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

