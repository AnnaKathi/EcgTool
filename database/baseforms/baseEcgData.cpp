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
	int anz = fmysql.ecg.getSize();
	laAuswahl->Caption = ftools.fmt("Auswahl: %d/%d EKG", anz, anz);

	fmysql.sessions.listInCombo(cbSession);
	fmysql.orte.listInCombo(cbOrt);
	fmysql.positions.listInCombo(cbPosition);
	fmysql.states.listInCombo(cbState);
	fmysql.lagen.listInCombo(cbLage);

	if (cbSession->Items->Count  > 0) cbSession->ItemIndex  = 0;
	if (cbOrt->Items->Count      > 0) cbOrt->ItemIndex      = 0;
	if (cbPosition->Items->Count > 0) cbPosition->ItemIndex = 0;
	if (cbState->Items->Count    > 0) cbState->ItemIndex    = 0;
	if (cbLage->Items->Count     > 0) cbLage->ItemIndex     = 0;

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
	int count = 0;
	int auswahl = 0;
	while (fmysql.ecg.nextRow())
		{
		count++;
		if (!CheckFilter()) continue;

		AddLine();
		auswahl++;
		}

	laAuswahl->Caption = ftools.fmt("Auswahl: %d/%d EKG", auswahl, count);
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
	item->SubItems->Add(fmysql.sessions.row.stamp);
	item->SubItems->Add(fmysql.orte.getNameOf(fmysql.sessions.row.ort));

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

	if (cbSession->ItemIndex < 0) ffilter.session = 0;
	else ffilter.session = (int)cbSession->Items->Objects[cbSession->ItemIndex];

	if (cbOrt->ItemIndex < 0) ffilter.ort = 0;
	else ffilter.ort = (int)cbOrt->Items->Objects[cbOrt->ItemIndex];

	if (cbPosition->ItemIndex < 0) ffilter.position = 0;
	else ffilter.position = (int)cbPosition->Items->Objects[cbPosition->ItemIndex];

	if (cbState->ItemIndex < 0) ffilter.state = 0;
	else ffilter.state = (int)cbState->Items->Objects[cbState->ItemIndex];

	if (cbLage->ItemIndex < 0) ffilter.lage = 0;
	else ffilter.lage = (int)cbLage->Items->Objects[cbLage->ItemIndex];

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

	if (ffilter.ort > 0)
		{
		if (!fmysql.sessions.get(fmysql.ecg.row.session)) return false;
		if (fmysql.sessions.row.ort != ffilter.ort) return false;
		}

	if (ffilter.session  > 0 && fmysql.ecg.row.session  != ffilter.session)  return false;
	if (ffilter.position > 0 && fmysql.ecg.row.position != ffilter.position) return false;
	if (ffilter.state    > 0 && fmysql.ecg.row.state    != ffilter.state)    return false;
	if (ffilter.lage     > 0 && fmysql.ecg.row.lage     != ffilter.lage)     return false;

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
String TfmBaseEcg::GetListedEcg()
	{
	//gibt die IDs aller Datensätze zurück, die gerade in der ListView
	//aufgeführt werden, d.h. Filter werden berücksichtigt
	String idents = "";
	TListItem* item; int id;
	for (int i = 0; i < lvData->Items->Count; i++)
		{
		item = lvData->Items->Item[i];
		id = (int)item->Data;

		if (idents == "")
			idents = String(id);
		else
        	idents += ";" + String(id);
		}
	return idents;
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

