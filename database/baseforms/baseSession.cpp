//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "../classMySql.h"
#include "../toolforms/addSession.h"
#include "baseSession.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmBaseSession *fmBaseSession;
extern cMySql fmysql;
//---------------------------------------------------------------------------
TfmBaseSession* CreateSessionForm(TForm* caller, TWinControl* container)
	{
	return new TfmBaseSession(caller, container);
	}
//---------------------------------------------------------------------------
__fastcall TfmBaseSession::TfmBaseSession(TComponent* Owner, TWinControl* Container)
	: TForm(Owner)
	{
	tCallback = NULL;
	bSelected = false;
	if (Container)
		snapTo(Container, alClient);
	}
//---------------------------------------------------------------------------
void TfmBaseSession::snapTo(TWinControl* container, TAlign align)
	{
	int realHeight = ClientHeight;
	int realWidth  = ClientWidth;

	Parent  = container;
	Hint    = Caption;
	Caption = "";
	Left    = 0;
	Top     = 0;
	if (align != alNone) Align = align;
	BorderIcons = TBorderIcons();
	BorderStyle = bsNone;

	ParentFont  = true;
	ParentColor = true;

	Height = realHeight;
	Width  = realWidth;
	Show();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::FormShow(TObject *Sender)
	{
	bInShow = false;
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmysql.places.listInCombo(cbOrt);
	if (cbOrt->Items->Count > 0) cbOrt->ItemIndex = 0;

	ShowData();
	tStartup->Tag = 1; //signalisiert, dass der Init durchgeführt wurde
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: public   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmBaseSession::setCallback(TTimer& timer)
	{
	tCallback = &timer;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseSession::ShowData()
	{
	if (bInShow) return false; //verhindern, dass sich die Funktion selbst überholt
	bInShow = true;
	lvSession->Items->Clear();
	lvSession->Items->BeginUpdate();

	if (!fmysql.sessions.loadTable(""))
		{
		ftools.ErrBox("Die Daten (Sessions) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s", fmysql.sessions.error_msg);
		return false;
		}

	TListItem* item;
	String name;
	while (fmysql.sessions.nextRow())
		{
		if (!CheckFilter()) continue;

		item = lvSession->Items->Add();
		int ident = fmysql.sessions.row.ident;
		item->Data = (void*) ident;
		item->Caption = String(ident);

		item->SubItems->Add(fmysql.sessions.row.stamp);
		item->SubItems->Add(fmysql.places.getNameOf(fmysql.sessions.row.place));
		item->SubItems->Add(fmysql.sessions.row.note);

		if (fmysql.ecg.loadBySession(ident))
			item->SubItems->Add(fmysql.ecg.num_rows);
		else
			item->SubItems->Add("# FEHLER #");
		}

	lvSession->Items->EndUpdate();
	bInShow = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseSession::BuildFilter()
	{
	ffilter.identVon = edIdVon->Text.ToIntDef(-1);
	ffilter.identBis = edIdBis->Text.ToIntDef(-1);

	ffilter.ort = (int)cbOrt->Items->Objects[cbOrt->ItemIndex];
	ffilter.kommentar = edKommentar->Text;

	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseSession::CheckFilter()
	{
	int id = fmysql.sessions.row.ident;
	if (ffilter.identVon > 0 && id < ffilter.identVon) return false;
	if (ffilter.identBis > 0 && id > ffilter.identBis) return false;

	if (ffilter.ort > 0 && ffilter.ort != fmysql.sessions.row.place) return false;

	if (ffilter.kommentar != "")
		{
		//enthält-Suche durchführen
		String db = fmysql.sessions.row.note.LowerCase();
		String kk = ffilter.kommentar.LowerCase();

		if (db.Pos(kk) <= 0) return false;
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::acFilterExecute(TObject *Sender)
	{
	if (tStartup->Tag == 1) //Init wurde schon durchgeführt
		{
		BuildFilter();
		ShowData();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::acAddExecute(TObject *Sender)
	{
	if (DlgNewSession(this))
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::acDelExecute(TObject *Sender)
	{
	if (lvSession->SelCount <= 0) return;
	TListItem* item = lvSession->Selected;
	int id = (int)item->Data;
	if (!fmysql.sessions.deleteByIdent(id))
		{
		ftools.ErrBox("Die Session <%d> konnten nicht gelöscht werden. "
			"Die Datenbank  meldet: %s", id, fmysql.sessions.error_msg);
		}
	else
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::acChangeExecute(TObject *Sender)
	{
	if (lvSession->SelCount <= 0) return;
	TListItem* item = lvSession->Selected;
	int id = (int)item->Data;
	/* todo
	if (DlgPersonChange(this, id))
		ShowData();
	*/
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::acSelectExecute(TObject *Sender)
	{
	//den Ident der ausgewählten Person an das aufrufende Formular zurückgeben
	//todo: als Callback auslegen
	if (!tStartup->Tag == 1) return;
	if (lvSession->SelCount <= 0) return;
	if (tCallback == NULL) return;

	TListItem* item = lvSession->Selected;
	int id = (int)item->Data;
	if (id <= 0) return;

	bSelected = true;
	iSession = id;
	tCallback->Enabled = true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::lvSessionClick(TObject *Sender)
	{
	TListItem* item = lvSession->Selected;
	if (item)
		{
		acDel->Enabled    = true;
		acChange->Enabled = true;
		acSelect->Enabled = true;
		}
	else
		{
		acDel->Enabled    = false;
		acChange->Enabled = false;
		acSelect->Enabled = false;
		}

	//ggf. getroffene Auswahl wieder aufheben
	if (bSelected)
		{
		bSelected = false;
		ShowData();
		tCallback->Enabled = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::lvSessionDblClick(TObject *Sender)
	{
	TListItem* item = lvSession->Selected;
	if (item)
		acSelectExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseSession::edIdVonExit(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------

