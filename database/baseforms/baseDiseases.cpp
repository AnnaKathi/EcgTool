//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "baseDiseases.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmBaseDiseases *fmBaseDiseases;
//---------------------------------------------------------------------------
bool CreateDiseaseForm(TForm* caller, TWinControl* container, cMySql& mysql)
	{
	return new TfmBaseDiseases(caller, container, mysql);
	}
//---------------------------------------------------------------------------
__fastcall TfmBaseDiseases::TfmBaseDiseases(TComponent* Owner, TWinControl* Container, cMySql& Mysql)
	: TForm(Owner)
	{
	fmysql = &Mysql;
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

	Height = realHeight;
	Width  = realWidth;
	Show();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ShowData();
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
	lvDiseases->Items->Clear();
	lvDiseases->Items->BeginUpdate();

	if (!fmysql->diseases.loadTable("Bez ASC"))
		{
		MsgBox("Die Daten (Erkrankungen) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s", fmysql->diseases.error_msg);
		return false;
		}

	TListItem* item;
	while (fmysql->diseases.nextRow())
		{
		//if (!CheckDiseaseFilter()) continue;

		item = lvDiseases->Items->Add();
		item->Data = (void*) fmysql->diseases.row.ident;
		item->Caption = String(fmysql->diseases.row.ident);
		item->SubItems->Add(fmysql->diseases.row.bez);
		}

	lvDiseases->Items->EndUpdate();
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::acDisAddExecute(TObject *Sender)
	{
    //
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::acDisDelExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmBaseDiseases::acDisFilterExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------

