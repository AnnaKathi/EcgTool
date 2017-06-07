//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "database/classMySql.h"
#include "database/toolforms/selectDescDb.h"

#include "wizardSession_Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmWizSession *fmWizSession;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgWizardSession(TForm* Papa)
	{
	TfmWizSession* Form = new TfmWizSession(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmWizSession::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmWizSession::TfmWizSession(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmWizSession::~TfmWizSession()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);

	pcSession->ActivePage = tbBasics;
	edStamp->Text = getNow();
	fmysql.places.listInCombo(cbOrte);
	}
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmWizSession::CheckPage()
	{
	//Prüfen, ob Weiter- und Zurück-Buttons freigeschaltet werden können
	if (pcSession->ActivePage == tbBasics)
		{
		acBack->Enabled = false;

		if (edStamp->Text == ""   ||
			cbOrte->ItemIndex < 0 ||
			lvResearchers->Items->Count <= 0)
			acNext->Enabled = false;
		else
			acNext->Enabled = true;
		}
	else
		{
		//undefinierter Tab
		acBack->Enabled = false;
		acNext->Enabled = false;
		}
	}
//---------------------------------------------------------------------------
String TfmWizSession::getNow()
	{
	TDateTime dt;
	return dt.CurrentDateTime().FormatString("yyyy-mm-dd hh-nn-ss");
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
//--  allgemeine Actions  ---------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::acCloseExecute(TObject *Sender)
	{
	if (Application->MessageBox(
		ftools.fmt(
			"Es wurden bereits Session-Daten erfasst. Diese Daten gehen bei "
			"einem Abbruch des Wizards verloren. Soll der Vorgang trotzdem "
			"abgebrochen werden?").c_str(),
		"Session-Wizard abbrechen", MB_YESNO) == IDYES)
		Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::acBackExecute(TObject *Sender)
	{
	//todo vorherige Seite anziegen
	}
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::acNextExecute(TObject *Sender)
	{
	//todo nächste Seite anzeigen

	CheckPage();
	}
//---------------------------------------------------------------------------
//--  Actions Basics  -------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::acAddResearcherExecute(TObject *Sender)
	{
	//Reseracher laden
	String idents = DlgSelectDesc(this, fmysql.researchers);
	if (idents == "") return;

	int pos; int id; String name; TListItem* item;
	while ((pos = idents.Pos(";")) > 0)
		{
		id = idents.SubString(0, pos-1).ToInt();
		name = fmysql.researchers.getNameOf(id);
		idents = idents.SubString(pos+1, 9999);

		item = lvResearchers->Items->Add();
		item->Data = (void*)id;
		item->Caption = String(id);
		item->SubItems->Add(name);
		}

	if (idents != "")
		{
		id = idents.ToInt();
		name = fmysql.researchers.getNameOf(id);

		item = lvResearchers->Items->Add();
		item->Data = (void*)id;
		item->Caption = String(id);
		item->SubItems->Add(name);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::acDelResearcherExecute(TObject *Sender)
	{
	//einen Researcher löschen
	if (lvResearchers->SelCount <= 0) return;
	TListItem* item = lvResearchers->Selected;
	item->Delete();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
//--  Meldungen Hauptformular  ----------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
//--  Meldungen tbBasics  ---------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::btNowClick(TObject *Sender)
	{
	edStamp->Text = getNow();
	}
//---------------------------------------------------------------------------
void __fastcall TfmWizSession::edStampChange(TObject *Sender)
	{
	CheckPage();
	}
//---------------------------------------------------------------------------

