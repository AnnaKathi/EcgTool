//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "database/classMySql.h"

#include "addEcg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmAddEcg *fmAddEcg;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgAddEcgs(TForm* Papa)
	{
	TfmAddEcg* Form = new TfmAddEcg(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmAddEcg::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmAddEcg::TfmAddEcg(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmysql.people.listInCombo(cbPerson);
	fmysql.states.listInCombo(cbState);
	fmysql.lagen.listInCombo(cbLage);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmAddEcg::SetCallbackTimer(TTimer* timer)
	{
	fCallbackTimer = timer;
	fCallbackTimer->Enabled = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddEcg::GetEcgHeader(int& person, int& state, int& lage)
	{
	int id = (int)cbPerson->Items->Objects[cbPerson->ItemIndex];
	if (id <= 0) return false;
	person = id;

	id = (int)cbState->Items->Objects[cbState->ItemIndex];
	if (id <= 0) return false;
	state = id;

	id = (int)cbLage->Items->Objects[cbLage->ItemIndex];
	if (id <= 0) return false;
	lage = id;

	fRow = -1;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddEcg::GetNextEcgRow(int& anz, int& pos, String& file)
	{
	fRow++;
	if (fRow >= lvEcg->Items->Count) return false;

	TListItem* item = lvEcg->Items->Item[fRow];
	anz = item->SubItems->Strings[0].ToInt();
	if (anz <= 0) return false;

	pos = item->SubItems->Strings[1].ToInt();
	if (pos <= 0) return false;

	file = item->SubItems->Strings[2];
	if (file == "") return false;

	return true;
	}
//---------------------------------------------------------------------------
void TfmAddEcg::GetEcgFiles()
	{
	int pos;
	if (!fmFiles->GetHeader(pos)) return;
	if (pos <= 0) return;

	int anz; String file;
	TListItem* item;
	while (fmFiles->GetNextEcg(anz, file))
		{
		item = lvEcg->Items->Add();
		item->Caption = lvEcg->Items->Count;
		item->SubItems->Add(String(anz));
		item->SubItems->Add(String(pos));
		item->SubItems->Add(file);
		}

	fmFiles->Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::acAddExecute(TObject *Sender)
	{
	fmFiles = new TfmEcgFiles(this);

	fmFiles->SetCallbackTimer(TimerCallback);
	fmFiles->ShowModal();

	delete fmFiles;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::acDelExecute(TObject *Sender)
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
void __fastcall TfmAddEcg::acSelectExecute(TObject *Sender)
	{
	fCallbackTimer->Enabled = true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::lvEcgClick(TObject *Sender)
	{
	if (lvEcg->SelCount >= 0)
		acDel->Enabled = true;
	else
		acDel->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddEcg::TimerCallbackTimer(TObject *Sender)
	{
	TimerCallback->Enabled = false;
	GetEcgFiles();
	}
//---------------------------------------------------------------------------


