//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "../classMySql.h"
// todo #include "addEcgData.h"
#include "baseEcgData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmBaseEcg *fmBaseEcg;
extern cMySql fmysql;
//---------------------------------------------------------------------------
TfmBaseEcg* CreateEcgForm(TForm* caller, TWinControl* container)
	{
	return new TfmBaseEcg(caller, container, caller->Color);
	}
//---------------------------------------------------------------------------
__fastcall TfmBaseEcg::TfmBaseEcg(TComponent* Owner, TWinControl* Container, TColor color)
	: TForm(Owner)
	{
	bSelectEcg = false;

	if (Container)
		snapTo(Container, alClient);
	}
//---------------------------------------------------------------------------
void TfmBaseEcg::snapTo(TWinControl* container, TAlign align)
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
void __fastcall TfmBaseEcg::FormShow(TObject *Sender)
	{
	bInShow = false;
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	laTabelle->Caption = "EKG-Daten (ecgdata)";
	fmysql.lagen.listInCombo(cbLage);
	ShowData();
	tStartup->Tag = 1; //signalisiert, dass der Init durchgeführt wurde
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: private   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: public   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmBaseEcg::LockFilter()
	{
	pnFilter->Enabled = false;
	}
//---------------------------------------------------------------------------
void TfmBaseEcg::DislockFilter()
	{
	pnFilter->Enabled = true;
	}
//---------------------------------------------------------------------------
bool TfmBaseEcg::ShowData()
	{
	if (bInShow) return false; //verhindern, dass sich die Funktion selbst überholt
	bInShow = true;
	lvData->Items->Clear();
	lvData->Items->BeginUpdate();

	//Daten aus Datenbank anzeigen
	if (!fmysql.ecg.loadTable())
		{
		ftools.ErrBox("Die Daten (EKG) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s", fmysql.diseases.error_msg);
		return false;
		}

	TListItem* item;
	while (fmysql.ecg.nextRow())
		{
		if (!CheckFilter()) continue;
		AddLine();
		}

	lvData->Items->EndUpdate();
	bInShow = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseEcg::ShowEcgOf(int person)
	{
	lvData->Items->Clear();
	lvData->Items->BeginUpdate();

	//Daten aus Datenbank anzeigen
	if (!fmysql.ecg.loadByPerson(person))
		{
		ftools.ErrBox("Die Daten (EKG) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s", fmysql.ecg.error_msg);
		return false;
		}

	TListItem* item;
	while (fmysql.ecg.nextRow())
		{
		if (!CheckFilter()) continue;
		AddLine();
		}

	lvData->Items->EndUpdate();
	return true;
	}
//---------------------------------------------------------------------------
void TfmBaseEcg::AddLine()
	{
	TListItem* item = lvData->Items->Add();
	item->Data = (void*) fmysql.ecg.row.ident;
	item->Caption = String(fmysql.ecg.row.ident);

	fmysql.sessions.get(fmysql.ecg.row.session);
	String s = ftools.fmt("%s - %s",
		fmysql.sessions.row.stamp,
		fmysql.orte.getNameOf(fmysql.sessions.row.ort));

	item->SubItems->Add(s);

	String name = fmysql.people.getNameOf(fmysql.ecg.row.person);
	item->SubItems->Add(name);

	item->SubItems->Add(fmysql.positions.getNameOf(fmysql.ecg.row.position));
	item->SubItems->Add(fmysql.states.getNameOf(fmysql.ecg.row.state));
	item->SubItems->Add(fmysql.lagen.getNameOf(fmysql.ecg.row.lage));
	}
//---------------------------------------------------------------------------
bool TfmBaseEcg::BuildFilter()
	{
	ffilter.identVon = edIdVon->Text.ToIntDef(-1);
	ffilter.identBis = edIdBis->Text.ToIntDef(-1);

	ffilter.name = edName->Text;
	ffilter.lage = (int)cbLage->Items->Objects[cbLage->ItemIndex];

	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseEcg::CheckFilter()
	{
	if (ffilter.identVon > 0 && fmysql.ecg.row.ident < ffilter.identVon) return false;
	if (ffilter.identBis > 0 && fmysql.ecg.row.ident > ffilter.identBis) return false;

	if (ffilter.name != "")
		{
		//enthält-Suche
		String nn = fmysql.people.getNameOf(fmysql.ecg.row.person).LowerCase();
		if (nn.Pos(ffilter.name.LowerCase()) <= 0)
			return false;
		}

	if (ffilter.lage > 0)
		{
		if (fmysql.ecg.row.lage != ffilter.lage)
			return false;
		}

	return true;
	}
//---------------------------------------------------------------------------
void TfmBaseEcg::SelectEcg(TTimer* timer)
	{
	bSelectEcg = true;
	CallbackSelected = timer;
	}
//---------------------------------------------------------------------------
int TfmBaseEcg::GetSelectedEcg()
	{
	return iSelectedEcg;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::acAddExecute(TObject *Sender)
	{
	/* todo
	if (DlgEcgAdd(this))
		ShowData();
	*/
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::acChangeExecute(TObject *Sender)
	{
	if (lvData->SelCount <= 0) return;
	TListItem* item = lvData->Selected;
	int id = (int)item->Data;
	/* todo
	if (DlgEcgChange(this, id))
		ShowData();
	*/
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::acDelExecute(TObject *Sender)
	{
	if (lvData->SelCount <= 0) return;
	TListItem* item = lvData->Selected;
	int id = (int)item->Data;
	if (!fmysql.ecg.deleteByIdent(id))
		{
		ftools.ErrBox("Das EKG <%d> konnte nicht gelöscht werden. "
			"Die Datenbank  meldet: %s", id, fmysql.diseases.error_msg);
		}
	else
    	ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::acFilterExecute(TObject *Sender)
	{
	if (tStartup->Tag == 1) //Init wurde schon durchgeführt
		{
		BuildFilter();
		ShowData();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::lvDataClick(TObject *Sender)
	{
	TListItem* item = lvData->Selected;
	if (item)
		{
		acDel->Enabled = true;
		acChange->Enabled = true;
		}
	else
		{
		acDel->Enabled = false;
		acChange->Enabled = false;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::edIdVonExit(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::edNameChange(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::lvDataDblClick(TObject *Sender)
	{
	TListItem* item = lvData->Selected;
	if (!item) return;

	if (bSelectEcg)
		{
		iSelectedEcg = (int)item->Data;
		CallbackSelected->Enabled = true;
		}
	else
		acChangeExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseEcg::cbLageChange(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------

