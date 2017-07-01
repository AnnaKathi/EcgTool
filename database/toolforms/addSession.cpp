//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <time.h>
#include <systdate.h>

#include "RequestBox.h"
#include "database/classMySql.h"
#include "database/toolforms/selectDescDb.h"
#include "database/toolforms/addEcg.h"
#include "addSession.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSessionAdd *fmSessionAdd;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgNewSession(TForm* Papa)
	{
	TfmSessionAdd* Form = new TfmSessionAdd(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
__fastcall TfmSessionAdd::TfmSessionAdd(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmSessionAdd::~TfmSessionAdd()
	{
	}
//---------------------------------------------------------------------------
bool TfmSessionAdd::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	edStamp->Text = getNow();
	fmysql.places.listInCombo(cbOrte);
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String TfmSessionAdd::getNow()
	{
	TDateTime dt;
	return dt.CurrentDateTime().FormatString("yyyy-mm-dd hh-nn-ss");
	}
//---------------------------------------------------------------------------
void TfmSessionAdd::GetEcgData()
	{
	int person;
	if (!fmAddEcgMessung->GetEcgHeader(person)) return;

	int state; int lage; int anz; int pos; String file; int format; String delim;
	TListItem* item;
	while (fmAddEcgMessung->GetNextEcgRow(state, lage, anz, pos, file, format, delim))
		{
		item = lvEcg->Items->Add();
		item->Caption = String(lvEcg->Items->Count);
		item->SubItems->Add(String(anz));
		item->SubItems->Add(String(person));
		item->SubItems->Add(String(state));
		item->SubItems->Add(String(lage));
		item->SubItems->Add(String(pos));
		item->SubItems->Add(file);
		item->SubItems->Add(String(format));
		item->SubItems->Add(delim);
		}

	fmAddEcgMessung->Close();
	}
//---------------------------------------------------------------------------
bool TfmSessionAdd::CheckSession()
	{
	//Pflichtfelder prüfen
	if (edStamp->Text == "")   return false;
	if (cbOrte->ItemIndex < 0) return false;

	if (edTemp->Text == "") return false;
	if (edLuft->Text == "") return false;

	if (lvResearchers->Items->Count <= 0) return false;

	if (lvEcg->Items->Count <= 0) return false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmSessionAdd::SaveSession()
	{
	if (!CheckSession()) return false;

	//-- Session speichern
	sSession sdata;
	sdata.place = (int)cbOrte->Items->Objects[cbOrte->ItemIndex];
	sdata.temp  = edTemp->Text.ToDouble();
	sdata.luft  = edLuft->Text.ToDouble();
	sdata.stamp = edStamp->Text;
	sdata.note = mKommentar->Text;

	if (!fmysql.sessions.insert(sdata))
		{
		Application->MessageBox(
			ftools.fmt(
				"Die Session konnte nicht gespeichert werden. "
				"Die Datenbank meldet: %s", fmysql.sessions.error_msg).c_str(),
			"Fehler beim Speichern",
			MB_OK);
		return false;
		}

	//letzte Zeile wurde durch insert wieder reingeladen
	int session = fmysql.sessions.row.ident;

	//-- Researchers speichern
	TListItem* item; bool fehler = false;
	for (int i = 0; i < lvResearchers->Items->Count; i++)
		{
		item = lvResearchers->Items->Item[i];
		int rid = (int)item->Data;

		if (!fmysql.sessions.insertResearcher(session, rid))
			{
			fehler = true;
			Application->MessageBox(
				ftools.fmt(
					"Der Reseracher <%d, %s> konnte nicht gespeichert werden. "
					"Die Datenbank meldet: %s",
					rid, item->SubItems->Strings[0], fmysql.sessions.error_msg).c_str(),
				"Fehler beim Speichern",
				MB_OK);
			break;
			}
		}

	if (fehler) return false;

	//-- Ecg-Data speichern
	sEcgData edata;
	for (int i = 0; i < lvEcg->Items->Count; i++)
		{
		item = lvEcg->Items->Item[i];
		edata.person   = item->SubItems->Strings[1].ToInt();
		edata.state    = item->SubItems->Strings[2].ToInt();
		edata.posture  = item->SubItems->Strings[3].ToInt();
		edata.position = item->SubItems->Strings[4].ToInt();
		edata.session  = session;

		String file  = item->SubItems->Strings[5];
		int format   = item->SubItems->Strings[6].ToInt();
		String delim = item->SubItems->Strings[7];
		if (!GetArray(file, (eDatFormat)format, delim, edata))
			{
			fehler = true;
			//todo Fehlermeldung
			break;
			}

		if (!fmysql.ecg.save(edata))
			{
			fehler = true;
			Application->MessageBox(
				ftools.fmt(
					"Der EKG-Datensatz %s konnte nicht gespeichert werden. "
					"Die Datenbank meldet: %s",
					item->Caption, fmysql.ecg.error_msg).c_str(),
				"Fehler beim Speichern",
				MB_OK);
			break;
			}
		}

	if (fehler) return false;

	Application->MessageBox(
		"Die Session wurde erfolgreich gespeichert.", "Speichern erfolgreich", MB_OK);

	return true;
	}
//---------------------------------------------------------------------------
bool TfmSessionAdd::GetArray(String file, eDatFormat format, String delim, sEcgData& data)
	{
	if (!fecg.data.getFile(file, format, delim, 0, 0, 3000)) //TODO
		{
		//todo Fejlermeldung
		return false;
		}

	iarray_t array = fecg.data.data_array;

	double wert; int ix = 0;
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t& v = itr->second;
		wert = v[1];

		data.werte[ix] = wert;
		ix++;

		if (ix >= 3000) break;
		}
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::acReAddExecute(TObject *Sender)
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
void __fastcall TfmSessionAdd::acReDelExecute(TObject *Sender)
	{
	//einen Researcher löschen
	if (lvResearchers->SelCount <= 0) return;
	TListItem* item = lvResearchers->Selected;
	item->Delete();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::acSaveExecute(TObject *Sender)
	{
	if (SaveSession())
		acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::acEcgAddExecute(TObject *Sender)
	{
	/* OLD
	fmAddEcg = new TfmAddEcg(this);

	fmAddEcg->SetCallbackTimer(TimerCallback);
	fmAddEcg->ShowModal();

	delete fmAddEcg;
	*/

	fmAddEcgMessung = new TfmAddMessung(this);
	fmAddEcgMessung->SetCallbackTimer(TimerCallback);
    fmAddEcgMessung->ShowModal();
	
	delete fmAddEcgMessung;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::acEcgDelExecute(TObject *Sender)
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
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::btNowClick(TObject *Sender)
	{
	edStamp->Text = getNow();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::lvResearchersClick(TObject *Sender)
	{
	if (lvResearchers->SelCount > 0)
		acReDel->Enabled = true;
	else
		acReDel->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::lvEcgClick(TObject *Sender)
	{
	if (lvEcg->SelCount > 0)
		acEcgDel->Enabled = true;
	else
		acEcgDel->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::TimerCallbackTimer(TObject *Sender)
	{
	TimerCallback->Enabled = false;
	GetEcgData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::lvEcgChange(TObject *Sender, TListItem *Item,
	  TItemChange Change)
	{
	acSave->Enabled = CheckSession();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSessionAdd::edStampChange(TObject *Sender)
	{
	acSave->Enabled = CheckSession();
	}
//---------------------------------------------------------------------------

