//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
#include "addDiseases.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmDis *fmDis;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgDiseaseAdd(TForm* Papa)
	{
	TfmDis* Form = new TfmDis(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(-1);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool DlgDiseaseChange(TForm* Papa, int ident)
	{
	TfmDis* Form = new TfmDis(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(ident);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmDis::Execute(int ident)
	{
	iDisease = ident;
	if (iDisease >= 0)
		bNewDisease = false;
	else
		bNewDisease = true;
		
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmDis::TfmDis(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmDis::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDis::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	if (bNewDisease)
		{
		edIdent->Text = "- noch nicht gesetzt -";
		edBez->Text = "";
		}

	else
		{
		edIdent->Text = String(iDisease);
		edBez->Text = fmysql.diseases.getNameOf(iDisease);
		}

	edBez->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmDis::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmDis::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmDis::acSaveExecute(TObject *Sender)
	{
	if (bNewDisease)
		{
		sDiseases data;
		data.ident = -1;
		sprintf(data.bez, "%.127s", edBez->Text.c_str());
		if (!fmysql.diseases.insert(data))
			{
			MsgBox("Der Datensatz konnte nicht gespeichert werden. "
				"Die Datenbank meldet: %s", fmysql.diseases.error_msg);
			return;
			}
		}

	else
		{
		sDiseases data;
		data.ident = iDisease;
		sprintf(data.bez, "%.127s", edBez->Text.c_str());
		if (!fmysql.diseases.update(data))
			{
			MsgBox("Der Datensatz konnte nicht geändert werden. "
				"Die Datenbank meldet: %s", fmysql.diseases.error_msg);
			return;
			}
		}

	acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void TfmDis::MsgBox(char* msg, ...)
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
void __fastcall TfmDis::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

