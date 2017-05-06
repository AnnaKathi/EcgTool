//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "../toolforms/addDesc.h"
#include "baseDesc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmBaseDesc *fmBaseDesc;
//---------------------------------------------------------------------------
TfmBaseDesc* CreateDescForm(TForm* caller, TWinControl* container, cMySqlDescDb& desc)
	{
	return new TfmBaseDesc(caller, container, desc);
	}
//---------------------------------------------------------------------------
__fastcall TfmBaseDesc::TfmBaseDesc(TComponent* Owner, TWinControl* Container, cMySqlDescDb& desc)
	: TForm(Owner)
	{
	fdesc = &desc;
	if (Container)
		snapTo(Container, alClient);
	}
//---------------------------------------------------------------------------
void TfmBaseDesc::snapTo(TWinControl* container, TAlign align)
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
__fastcall TfmBaseDesc::~TfmBaseDesc()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	laTabelle->Caption =
		fdesc->myName.SubString(1,1).UpperCase() +
		fdesc->myName.SubString(2, 999).LowerCase();
		
	ShowData();
	tStartup->Tag = 1; //signalisiert, dass der Init durchgeführt wurde
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: private   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmBaseDesc::MsgBox(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	Application->MessageBox(String(buffer).c_str(), "Fehler", MB_OK);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: public   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmBaseDesc::LockFilter()
	{
	pnFilter->Enabled = false;
	}
//---------------------------------------------------------------------------
void TfmBaseDesc::DislockFilter()
	{
	pnFilter->Enabled = true;
	}
//---------------------------------------------------------------------------
bool TfmBaseDesc::ShowData()
	{
	if (bInShow) return false; //verhindern, dass sich die Funktion selbst überholt
	bInShow = true;
	lvData->Items->Clear();
	lvData->Items->BeginUpdate();

	if (!fdesc->loadTable("Bez ASC"))
		{
		MsgBox(ftools.fmt(
			"Die Daten (%s) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s",
			fdesc->myName, fdesc->error_msg).c_str());
		return false;
		}

	TListItem* item;
	while (fdesc->nextRow())
		{
		if (!CheckFilter()) continue;

		item = lvData->Items->Add();
		item->Data = (void*) fdesc->row.ident;
		item->Caption = String(fdesc->row.ident);
		item->SubItems->Add(fdesc->row.bez);
		}

	lvData->Items->EndUpdate();
	bInShow = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseDesc::BuildFilter()
	{
	ffilter.identVon = edIdVon->Text.ToIntDef(-1);
	ffilter.identBis = edIdBis->Text.ToIntDef(-1);

	ffilter.bez = edBez->Text;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseDesc::CheckFilter()
	{
	int id = fdesc->row.ident;
	if (ffilter.identVon > 0 && id < ffilter.identVon) return false;
	if (ffilter.identBis > 0 && id > ffilter.identBis) return false;

	if (ffilter.bez != "")
		{
		//enthält-Suche
		String bezeichnung = fdesc->getNameOf(id).LowerCase();
		if (bezeichnung.Pos(ffilter.bez.LowerCase()) <= 0)
			return false;
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::acFilterExecute(TObject *Sender)
	{
	if (tStartup->Tag == 1) //Init wurde schon durchgeführt
		{
		BuildFilter();
		ShowData();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::acAddExecute(TObject *Sender)
	{
	if (DlgDescDbAdd(this, *fdesc))
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::acDelExecute(TObject *Sender)
	{
	if (lvData->SelCount <= 0) return;
	TListItem* item = lvData->Selected;
	int id = (int)item->Data;
	if (!fdesc->deleteByIdent(id))
		{
		MsgBox("Der Datensatz <%d> konnten nicht gelöscht werden. "
			"Die Datenbank  meldet: %s", id, fdesc->error_msg);
		}
	else
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::acEditExecute(TObject *Sender)
	{
	if (lvData->SelCount <= 0) return;
	TListItem* item = lvData->Selected;
	int id = (int)item->Data;
	if (DlgDescDbEdit(this, id, *fdesc))
		ShowData();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::lvDataClick(TObject *Sender)
	{
	TListItem* item = lvData->Selected;
	if (item)
		{
		acDel->Enabled  = true;
		acEdit->Enabled = true;
		}
	else
		{
		acDel->Enabled  = false;
		acEdit->Enabled = false;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::edIdVonExit(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::edBezChange(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDesc::lvDataDblClick(TObject *Sender)
	{
	TListItem* item = lvData->Selected;
	if (item)
		acEditExecute(Sender);
	}
//---------------------------------------------------------------------------

