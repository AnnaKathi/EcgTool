//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "database/classMySql.h"

#include "ChoiFeatures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmChoiFeatures *fmChoiFeatures;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgChoiFeatures(TForm* Papa)
	{
	TfmChoiFeatures* Form = new TfmChoiFeatures(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmChoiFeatures::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoiFeatures::TfmChoiFeatures(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::FormShow(TObject *Sender)
	{
	TfmEcg = CreateEcgForm(this, pnEcg);
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	TfmEcg->SelectEcg(CallbackEcg);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	delete TfmEcg;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmChoiFeatures::Print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
void TfmChoiFeatures::GetSelectedEcg()
	{
	int id = TfmEcg->GetSelectedEcg();
	if (id <= 0) return;

	if (!fmysql.ecg.loadByIdent(id))
		{
		ftools.ErrBox("Das EKG <%d> konnte nicht geladen werden. Die Datenbank meldet: %s",
			id, fmysql.ecg.error_msg);
		return;
		}

	iarray_t array; array.clear();
	for (int i = 0; i < 3000; i++)
		array[i].push_back(fmysql.ecg.row.werte[i]);

	Print("EKG geladen:");
	Print("\tSession: %d", fmysql.ecg.row.session);
	Print("\tPerson: %d", fmysql.ecg.row.person);
	Print("\tAnz. Werte: %d", array.size());
	}
//---------------------------------------------------------------------------
void TfmChoiFeatures::GetFeatures()
	{
	fChoi.
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::CallbackEcgTimer(TObject *Sender)
	{
	CallbackEcg->Enabled = false;
	GetSelectedEcg();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::btFeaturesClick(TObject *Sender)
	{
	GetFeatures();
	}
//---------------------------------------------------------------------------

