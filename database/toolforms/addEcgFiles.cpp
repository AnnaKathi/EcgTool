//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "database/classMySql.h"

#include "addEcgFiles.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmEcgFiles *fmEcgFiles;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgAddEcgFiles(TForm* Papa)
	{
	TfmEcgFiles* Form = new TfmEcgFiles(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmEcgFiles::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmEcgFiles::TfmEcgFiles(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmysql.positions.listInCombo(cbPosition);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmEcgFiles::SetCallbackTimer(TTimer* timer)
	{
	fCallbackTimer = timer;
	fCallbackTimer->Enabled = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmEcgFiles::GetHeader(int& pos)
	{
	int id = (int)cbPosition->Items->Objects[cbPosition->ItemIndex];
	if (id <= 0) return false;
	pos = id;
	fRow = -1;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmEcgFiles::GetNextEcg(int& anz, String& file)
	{
	fRow++;
	if (fRow >= lvEcg->Items->Count) return false;

	TListItem* item = lvEcg->Items->Item[fRow];
	anz = item->SubItems->Strings[0].ToInt();
	if (anz <= 0) return false;

	file = item->SubItems->Strings[1];
	if (file == "") return false;

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::acAddExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;

	fDelim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		fDelim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		fDelim = "\t";

	if (cbFormat->ItemIndex == 1)
		fFormat = formatADS;
	else
		fFormat = formatNone;

	String file = OpenDialog->FileName;

	if (!fecg.data.getFile(file, fFormat, fDelim, 0, 3000))
		{
		; //todo Fehlermeludng
		return;
		}

	int anz = fecg.data.data_array.size();

	TListItem* item = lvEcg->Items->Add();
	item->Caption = lvEcg->Items->Count;
	item->SubItems->Add(String(anz));
	item->SubItems->Add(file);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::acDelExecute(TObject *Sender)
	{
	if (lvEcg->SelCount <= 0) return;
	TListItem* item;
	for (int i = lvEcg->Items->Count-1; i >= 0; i--)
		{
		item = lvEcg->Items->Item[i];
		if (!item->Selected) continue;
		item->Delete();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::acEndExecute(TObject *Sender)
	{
	fCallbackTimer->Enabled = true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEcgFiles::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

