//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <time.h>
#include <systdate.h>

#include "RequestBox.h"
#include "database/classMySql.h"
#include "database/toolforms/selectDescDb.h"
#include "database/toolforms/addEcg.h"
#include "Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSession *fmSession;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgNewSession(TForm* Papa)
	{
	TfmSession* Form = new TfmSession(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
__fastcall TfmSession::TfmSession(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmSession::~TfmSession()
	{
	}
//---------------------------------------------------------------------------
bool TfmSession::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	edStamp->Text = getNow();
	fmysql.orte.listInCombo(cbOrte);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String TfmSession::getNow()
	{
	TDateTime dt;
	return dt.CurrentDateTime().DateTimeString();
	}
//---------------------------------------------------------------------------
void TfmSession::GetEcgData()
	{
	int person; int state; int lage;
	if (!fmAddEcg->GetEcgHeader(person, state, lage)) return;

	int anz; int pos; String file;
	TListItem* item;
	while (fmAddEcg->GetNextEcgRow(anz, pos, file))
		{
		item = lvEcg->Items->Add();
		item->Caption = String(lvEcg->Items->Count);
		item->SubItems->Add(String(anz));
		item->SubItems->Add(String(person));
		item->SubItems->Add(String(state));
		item->SubItems->Add(String(lage));
		item->SubItems->Add(String(pos));
		item->SubItems->Add(file);
		}

	fmAddEcg->Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSession::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acReAddExecute(TObject *Sender)
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
void __fastcall TfmSession::acReDelExecute(TObject *Sender)
	{
	//einen Researcher löschen
	if (lvResearchers->SelCount <= 0) return;
	TListItem* item = lvResearchers->Selected;
	item->Delete();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acEcgAddExecute(TObject *Sender)
	{
	fmAddEcg = new TfmAddEcg(this);

	fmAddEcg->SetCallbackTimer(TimerCallback);
	fmAddEcg->ShowModal();

	delete fmAddEcg;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acEcgDelExecute(TObject *Sender)
	{
	if (lvResearchers->SelCount <= 0) return;
	TListItem* item;
	for (int i = lvEcg->Items->Count-1; i >= 0; i--)
		{
		item = lvEcg->Items->Item[i];
		if (!item->Selected) continue;
		item->Delete();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acSaveExecute(TObject *Sender)
	{
	//todo: Daten speichern
	sSession data;
	data.ort = (int)cbOrte->Items->Objects[cbOrte->ItemIndex];
	data.stamp = edStamp->Text;
	data.kommentar = mKommentar->Text;

	if (!fmysql.sessions.insert(data))
		{
		Application->MessageBox(
			ftools.fmt(
				"Die Session konnte nicht gespeichert werden. "
				"Die Datenbank meldet: %s", fmysql.sessions.error_msg).c_str(),
			"Fehler beim Speichern",
			MB_OK);
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSession::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::btNowClick(TObject *Sender)
	{
	edStamp->Text = getNow();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::lvResearchersClick(TObject *Sender)
	{
	if (lvResearchers->SelCount > 0)
		acReDel->Enabled = true;
	else
		acReDel->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::lvEcgClick(TObject *Sender)
	{
	if (lvEcg->SelCount > 0)
		acEcgDel->Enabled = true;
	else
		acEcgDel->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::TimerCallbackTimer(TObject *Sender)
	{
	TimerCallback->Enabled = false;
	GetEcgData();
	}
//---------------------------------------------------------------------------

