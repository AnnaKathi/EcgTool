//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "../classMySql.h"
#include "addPeople.h"
#include "basePeople.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmBasePeople *fmBasePeople;
extern cMySql fmysql;
//---------------------------------------------------------------------------
TfmBasePeople* CreatePeopleForm(TForm* caller, TWinControl* container)
	{
	return new TfmBasePeople(caller, container, caller->Color);
	}
//---------------------------------------------------------------------------
__fastcall TfmBasePeople::TfmBasePeople(TComponent* Owner, TWinControl* Container, TColor color)
	: TForm(Owner)
	{
	if (Container)
		snapTo(Container, alClient);
	}
//---------------------------------------------------------------------------
void TfmBasePeople::snapTo(TWinControl* container, TAlign align)
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
void __fastcall TfmBasePeople::FormShow(TObject *Sender)
	{
	bInShow = false;
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ShowData();
	tStartup->Tag = 1; //signalisiert, dass der Init durchgeführt wurde
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: private   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmBasePeople::MsgBox(char* msg, ...)
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
bool TfmBasePeople::ShowData()
	{
	if (bInShow) return false; //verhindern, dass sich die Funktion selbst überholt
	bInShow = true;
	lvPeople->Items->Clear();
	lvPeople->Items->BeginUpdate();

	if (!fmysql.people.loadTable(""))
		{
		MsgBox("Die Daten (Personen) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s", fmysql.diseases.error_msg);
		return false;
		}

	TListItem* item;
	String name;
	while (fmysql.people.nextRow())
		{
		if (!CheckFilter()) continue;

		item = lvPeople->Items->Add();
		int person = fmysql.people.row.ident;
		item->Data = (void*) person;
		item->Caption = String(person);
		name = String(fmysql.people.row.vorname) + " " + String(fmysql.people.row.nachname);
		item->SubItems->Add(name.c_str());

		sarray_t dis;
		dis = fmysql.people.getDiseasesOf(person);
		dis = fmysql.diseases.getNamesOf(dis);
		String liste = ""; 
		bool first = true;
		for (sarray_itr itr = dis.begin(); itr != dis.end(); itr++)
			{
			slist_t& v = itr->second;
			if (first)
				{
				first = false;
				liste = v[1];
				}
			else
				liste += ", " + v[1];
			}
		item->SubItems->Add(liste);
		}

	lvPeople->Items->EndUpdate();
	bInShow = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBasePeople::BuildFilter()
	{
	ffilter.identVon = edIdVon->Text.ToIntDef(-1);
	ffilter.identBis = edIdBis->Text.ToIntDef(-1);

	ffilter.name = edName->Text;

	return true;
	}
//---------------------------------------------------------------------------
bool TfmBasePeople::CheckFilter()
	{
	int id = fmysql.people.row.ident;
	if (ffilter.identVon > 0 && id < ffilter.identVon) return false;
	if (ffilter.identBis > 0 && id > ffilter.identBis) return false;

	if (ffilter.name != "")
		{
		//enthält-Suche
		String nn = fmysql.people.getNameOf(id).LowerCase();
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
void __fastcall TfmBasePeople::acAddExecute(TObject *Sender)
	{
	if (DlgPersonAdd(this))
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acChangeExecute(TObject *Sender)
	{
	if (lvPeople->SelCount <= 0) return;
	TListItem* item = lvPeople->Selected;
	int id = (int)item->Data;
	if (DlgPersonChange(this, id))
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acDelExecute(TObject *Sender)
	{
	if (lvPeople->SelCount <= 0) return;
	TListItem* item = lvPeople->Selected;
	int id = (int)item->Data;
	if (!fmysql.people.deleteByIdent(id))
		{
		MsgBox("Die Person <%d> konnten nicht gelöscht werden. "
			"Die Datenbank  meldet: %s", id, fmysql.diseases.error_msg);
		}
	else
    	ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acFilterExecute(TObject *Sender)
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
void __fastcall TfmBasePeople::lvPeopleClick(TObject *Sender)
	{
	TListItem* item = lvPeople->Selected;
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
void __fastcall TfmBasePeople::edIdVonExit(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::edNameChange(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::lvPeopleDblClick(TObject *Sender)
	{
	TListItem* item = lvPeople->Selected;
	if (item)
		acChangeExecute(Sender);
	}
//---------------------------------------------------------------------------

