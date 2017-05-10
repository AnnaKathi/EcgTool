//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "selectDescDb.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSelectDesc *fmSelectDesc;
//---------------------------------------------------------------------------
String DlgSelectDesc(TForm* Papa, cMySqlDescDb& desc)
	{
	TfmSelectDesc* Form = new TfmSelectDesc(Papa);
	String res = "";

	if (Form)
		{
		res = Form->Execute(desc);
		delete Form;
		}
	return res;
	}
//---------------------------------------------------------------------------
String TfmSelectDesc::Execute(cMySqlDescDb& desc)
	{
	fdesc = &desc;
	ShowModal();
	return fIdents;
	}
//---------------------------------------------------------------------------
__fastcall TfmSelectDesc::TfmSelectDesc(TComponent* Owner)
	: TForm(Owner)
	{
	fIdents = "";
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectDesc::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectDesc::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	Caption = "select " + fdesc->myName;
	fmDesc= CreateDescForm(this, pnListe, *fdesc, eSelect);
	fmDesc->SetCallbackTimer(TimerCallback);
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectDesc::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TfmSelectDesc::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSelectDesc::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmSelectDesc::TimerCallbackTimer(TObject *Sender)
	{
	TimerCallback->Enabled = false;
	fIdents = fmDesc->GetSelectedIdents();
	acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------

