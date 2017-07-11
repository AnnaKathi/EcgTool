//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "..\classMySql.h"

#include "addPersonSession.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmAddPersonSession *fmAddPersonSession;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgAddPersonSession(TForm* Papa, int person)
	{
	TfmAddPersonSession* Form = new TfmAddPersonSession(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(person);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmAddPersonSession::Execute(int person)
	{
	iPerson = person;
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmAddPersonSession::TfmAddPersonSession(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	laPerson->Caption = ftools.fmt("%d - %s", iPerson, fmysql.people.getNameOf(iPerson));
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::acAddZustand1Execute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::acAddZustand2Execute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::acAddZustand3Execute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::acAddZustand4Execute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

