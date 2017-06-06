//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
#include "addDesc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmDescAdd *fmDescAdd;
//---------------------------------------------------------------------------
bool DlgDescDbAdd(TForm* Papa, cMySqlDescDb& desc)
	{
	TfmDescAdd* Form = new TfmDescAdd(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(-1, desc);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool DlgDescDbEdit(TForm* Papa, int ident, cMySqlDescDb& desc)
	{
	TfmDescAdd* Form = new TfmDescAdd(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(ident, desc);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmDescAdd::Execute(int ident, cMySqlDescDb& desc)
	{
	fdesc = &desc;
	iData = ident;
	if (iData >= 0)
		bNewData = false;
	else
		bNewData = true;
		
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmDescAdd::TfmDescAdd(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmDescAdd::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDescAdd::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	String db =
		fdesc->myName.SubString(1,1).UpperCase() +
		fdesc->myName.SubString(2, 999).LowerCase();

	if (bNewData)
		{
		Caption = "Datensatz anlegen: " + db;
		edIdent->Text = "- noch nicht gesetzt -";
		edBez->Text = "";
		}

	else
		{
		Caption = "Datensatz ändern: " + db;
		edIdent->Text = String(iData);
		edBez->Text = fdesc->getNameOf(iData);
		}

	edBez->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmDescAdd::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmDescAdd::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmDescAdd::acSaveExecute(TObject *Sender)
	{
	if (bNewData)
		{
		sDescData data;
		data.ident = -1;
		sprintf(data.name, "%.127s", edBez->Text.c_str());
		if (!fdesc->insert(data))
			{
			MsgBox("Der Datensatz konnte nicht gespeichert werden. "
				"Die Datenbank meldet: %s", fdesc->error_msg);
			return;
			}
		}

	else
		{
		sDescData data;
		data.ident = iData;
		sprintf(data.name, "%.127s", edBez->Text.c_str());
		if (!fdesc->update(data))
			{
			MsgBox("Der Datensatz konnte nicht geändert werden. "
				"Die Datenbank meldet: %s", fdesc->error_msg);
			return;
			}
		}

	acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void TfmDescAdd::MsgBox(char* msg, ...)
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
void __fastcall TfmDescAdd::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmDescAdd::edBezKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_RETURN)
		{
		Key = 0;
		acSaveExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

