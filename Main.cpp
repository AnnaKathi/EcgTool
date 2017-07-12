/*
todo: Print-Funktionen aus allen Formularen in cTools verlagern
todo: include stdio.h aus allen Formularen in cTools verlagern
todo: extern cMySql fmysql in definitions.h verlagern?
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "algorithms/AlgChoi.h"
#include "algorithms/AlgChoi2.h"
#include "algorithms/EinzelAusw.h"

#include "database/classMySql.h"
#include "database/DbPersonen.h"
#include "database/toolforms/addSession.h"
#include "database/toolforms/wizardSession_Main.h"

#include "EcgView.h"
#include "Databases.h"
#include "DataAnalysis.h"
#include "Sessions.h"
#include "Testform.h"
#include "EdanImport.h"

#include "LeadAnalysis.h"
#include "EcgLeadAnalysis.h"

#include "Features.h"
#include "VergleichAlg.h"
#include "ChoiKlassifizierung.h"
#include "Main.h"

//TEST, Integration von wavelib.h
#include "algorithms/Wavelet.h"
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

	setStatus(ftools.GetComputer(), 2);
	/* TODO
	if (ftools.GetComputerProzessor() != "64Bit")
		{
		Application->MessageBox(
			ftools.fmt(
				"Es wurde der Systemtyp '%s' erkannt.\r\n\r\n"
				"Das Programm ist auf ein 64Bit-Windows-Betriebssystem ausgelegt. "
				"Einige Funktionen sind mit anderen Betriebssystemem unter Umständen "
				"nicht verfügbar, z.B. die Choi-SVM-Klassifizierung.\r\n\r\n",
				ftools.cpData.BSProzessor).c_str(),
			"Warnung 64Bit-System", MB_OK);
		setStatus("## 32Bit-System ggf. nicht ausreichend ##", 2);
		}
	else
		setStatus("64Bit-System  - ok", 2);
	*/

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
	if (bNoMySql)
		return true; //simulieren, die DB wär geöffnet worden

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

	setStatus("startup Database...checking existance, MySql found");
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
			fmysql.close();
			return false;
			}

		setStatus("startup Database...creating database");
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

	setStatus("startup Database...checking existance, DB found");
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
void __fastcall TfmMain::acTestExecute(TObject *Sender)
	{
	DlgTestform(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acImportEdanExecute(TObject *Sender)
	{
	DlgImportEdan(this);
	}
//---------------------------------------------------------------------------
//--- Analysis-Actions ------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmMain::acAnalyseEcgExecute(TObject *Sender)
	{
	//todo move
	//Formular EcgView aufrufen, ein bestimmtes EKG untersuchen
	TfmEcg* formecg = new TfmEcg(this);
	if (!formecg->Execute())
		;
	delete formecg;
	setDbInfo();
	}
//---------------------------------------------------------------------------
//--- Datenbank-Actions -----------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmMain::acDatabaseAllExecute(TObject *Sender)
	{
	DlgShowDatabases(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acDatabasePeopleExecute(TObject *Sender)
	{
	DlgDatabasePersonen(this);
	setDbInfo();
	}
//---------------------------------------------------------------------------
//--- Session-Actions -------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmMain::acSessionAddExecute(TObject *Sender)
	{
	DlgShowSessions(this);
	setDbInfo();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acSessionWizardExecute(TObject *Sender)
	{
	DlgWizardSession(this);
	}
//---------------------------------------------------------------------------
//--- Feature-Actions -------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmMain::acFeaturesShowExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acFeaturesBuildAllExecute(TObject *Sender)
	{
	DlgFeatures(this);
	setDbInfo();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acFeaturesChoiExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acFeaturesRandomExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
//--- Klassifizierungs-Actions ----------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmMain::acClassifyAllExecute(TObject *Sender)
	{
	DlgAlgVergleich(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acClassifySvmExecute(TObject *Sender)
	{
	DlgChoiClassification(this);
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
void __fastcall TfmMain::btAnalysisSelectClick(TObject *Sender)
	{
	String cl = Sender->ClassName();
	if (cl != "TBitBtn") return;
	TComponent* comp = (TComponent*)Sender;

	POINT pt;
	GetCursorPos(&pt);

		 if (comp->Name == "btAnalysisSelect") PopupMenuAnalysis->Popup(pt.x, pt.y);
	else if (comp->Name == "btDatabaseSelect") PopupMenuDatabase->Popup(pt.x, pt.y);
	else if (comp->Name == "btSessionsSelect") PopupMenuSessions->Popup(pt.x, pt.y);
	else if (comp->Name == "btFeaturesSelect") PopupMenuFeatures->Popup(pt.x, pt.y);
	else if (comp->Name == "btClassifySelect") PopupMenuClassify->Popup(pt.x, pt.y);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btLKeadAnalysisClick(TObject *Sender)
	{
	//TEST LEAD ANALYSIS
	String file = "D:\\ADS Tests - Transfer vom Laptop\\2017-06-24 - Durchgang 1\\Senta liegend.txt";
	DlgShowLeads(this, file, "Senta liegend");
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btEcgAnalysisClick(TObject *Sender)
	{
	String path = "D:\\ADS Tests - Transfer vom Laptop\\2017-06-24 - Durchgang 1";
	String name = "Senta";
	DlgShowEcgLeads(this, path, name);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btWavelibClick(TObject *Sender)
	{
	//TEST wavelib
	DlgShowWavelet(this);
	}
//---------------------------------------------------------------------------

