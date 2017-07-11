//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "..\classMySql.h"

#include "selectPeople.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSelectPerson *fmSelectPerson;
extern cMySql fmysql;
//---------------------------------------------------------------------------
int DlgSelectSinglePerson(TForm* Papa)
	{
	TfmSelectPerson* Form = new TfmSelectPerson(Papa);
	int ident = -1;

	if (Form)
		{
		ident = Form->Execute();
		delete Form;
		}
	return ident;
	}
//---------------------------------------------------------------------------
int TfmSelectPerson::Execute()
	{
	ShowModal();
	return iPerson;
	}
//---------------------------------------------------------------------------
__fastcall TfmSelectPerson::TfmSelectPerson(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectPerson::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectPerson::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmPeople = CreatePeopleForm(this, pnPeople, eSingleSelect);
	fmPeople->setCallback(*tCallback);
	fmPeople->ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectPerson::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	delete fmPeople;
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
void __fastcall TfmSelectPerson::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectPerson::acSelectExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSelectPerson::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectPerson::tCallbackTimer(TObject *Sender)
	{
	int person = fmPeople->iPerson;
	if (person <= 0) return;
	iPerson = person;
	acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------

