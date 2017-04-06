//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "../classMySql.h"
#include "addDiseases.h"
#include "baseDiseases.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmBaseDiseases *fmBaseDiseases;
extern cMySql fmysql;
//---------------------------------------------------------------------------
TfmBaseDiseases* CreateDiseaseForm(TForm* caller, TWinControl* container)
	{
	return new TfmBaseDiseases(caller, container, caller->Color);
	}
//---------------------------------------------------------------------------
__fastcall TfmBaseDiseases::TfmBaseDiseases(TComponent* Owner, TWinControl* Container, TColor color)
	: TForm(Owner)
	{
	if (Container)
		snapTo(Container, alClient);
	}
//---------------------------------------------------------------------------
void TfmBaseDiseases::snapTo(TWinControl* container, TAlign align)
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
void __fastcall TfmBaseDiseases::FormShow(TObject *Sender)
	{
	bInShow = false;
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ShowData();
	tStartup->Tag = 1; //signalisiert, dass der Init durchgef�hrt wurde
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: private   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmBaseDiseases::MsgBox(char* msg, ...)
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
bool TfmBaseDiseases::ShowData()
	{
	if (bInShow) return false; //verhindern, dass sich die Funktion selbst �berholt
	bInShow = true;
	lvDiseases->Items->Clear();
	lvDiseases->Items->BeginUpdate();

	if (!fmysql.diseases.loadTable("Bez ASC"))
		{
		MsgBox("Die Daten (Erkrankungen) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s", fmysql.diseases.error_msg);
		return false;
		}

	TListItem* item;
	while (fmysql.diseases.nextRow())
		{
		if (!CheckFilter()) continue;

		item = lvDiseases->Items->Add();
		item->Data = (void*) fmysql.diseases.row.ident;
		item->Caption = String(fmysql.diseases.row.ident);
		item->SubItems->Add(fmysql.diseases.row.bez);
		}

	lvDiseases->Items->EndUpdate();
	bInShow = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseDiseases::ShowDataOfPerson(int person)
	{
	if (bInShow) return false; //verhindern, dass sich die Funktion selbst �berholt
	bInShow = true;
	lvDiseases->Items->Clear();
	lvDiseases->Items->BeginUpdate();

	//Daten aus Datenbank anzeigen
	if (!fmysql.diseases.loadTable()) //todo loadByPerson einbauen
		{
		Application->MessageBox(fmysql.error_msg.c_str(), "Fehler aufgetreten", MB_OK);
		lvDiseases->Items->EndUpdate();
		return false;
		}

	sarray_t dis;
	dis = fmysql.people.getDiseasesOf(person);

	TListItem* item;
	while (fmysql.diseases.nextRow())
		{
		bool found = false;
		for (sarray_itr itr = dis.begin(); itr != dis.end(); itr++)
			{
			slist_t v = itr->second;
			if (fmysql.diseases.row.ident == v[0].ToInt())
				{
				found = true;
				break;
				}
			}

		if (!found) continue;
		if (!CheckFilter()) continue;

		item = lvDiseases->Items->Add();
		item->Data = (void*) fmysql.diseases.row.ident;
		item->Caption = String(fmysql.diseases.row.ident);
		item->SubItems->Add(fmysql.diseases.row.bez);
		}

	lvDiseases->Items->EndUpdate();
	bInShow = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseDiseases::BuildFilter()
	{
	ffilter.identVon = edDisIdVon->Text.ToIntDef(-1);
	ffilter.identBis = edDisIdBis->Text.ToIntDef(-1);

	ffilter.name = edDisName->Text;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBaseDiseases::CheckFilter()
	{
	int id = fmysql.diseases.row.ident;
	if (ffilter.identVon > 0 && id < ffilter.identVon) return false;
	if (ffilter.identBis > 0 && id > ffilter.identBis) return false;

	if (ffilter.name != "")
		{
		//enth�lt-Suche
		String nn = fmysql.diseases.getNameOf(id).LowerCase();
		if (nn.Pos(ffilter.name.LowerCase()) <= 0)
			return false;
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::acDisAddExecute(TObject *Sender)
	{
	if (DlgDiseaseAdd(this))
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::acDisChangeExecute(TObject *Sender)
	{
	if (lvDiseases->SelCount <= 0) return;
	TListItem* item = lvDiseases->Selected;
	int id = (int)item->Data;
	if (DlgDiseaseChange(this, id))
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::acDisDelExecute(TObject *Sender)
	{
	if (lvDiseases->SelCount <= 0) return;
	TListItem* item = lvDiseases->Selected;
	int id = (int)item->Data;
	if (!fmysql.diseases.deleteByIdent(id))
		{
		MsgBox("Die Erkrankung <%d> konnten nicht gel�scht werden. "
			"Die Datenbank  meldet: %s", id, fmysql.diseases.error_msg);
		}
	else
    	ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::acDisFilterExecute(TObject *Sender)
	{
	if (tStartup->Tag == 1) //Init wurde schon durchgef�hrt
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
void __fastcall TfmBaseDiseases::lvDiseasesClick(TObject *Sender)
	{
	TListItem* item = lvDiseases->Selected;
	if (item)
		{
		acDisDel->Enabled = true;
		acDisChange->Enabled = true;
		}
	else
		{
		acDisDel->Enabled = false;
		acDisChange->Enabled = false;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::edDisIdVonExit(TObject *Sender)
	{
	acDisFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::edDisNameChange(TObject *Sender)
	{
	acDisFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::lvDiseasesDblClick(TObject *Sender)
	{
	TListItem* item = lvDiseases->Selected;
	if (item)
		acDisChangeExecute(Sender);
	}
//---------------------------------------------------------------------------

