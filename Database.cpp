//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Database.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmData *fmData;
//---------------------------------------------------------------------------
bool DlgDatabase(TForm* Papa)
	{
	TfmData* Form = new TfmData(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
__fastcall TfmData::TfmData(TComponent* Owner)
	: TForm(Owner)
	{
	char path[MAX_PATH];
	strcpy(path, Application->ExeName.c_str());
	char* pt = strrchr(path, '\\');
	if (pt != 0)
		*pt = 0;

	String file = String(path) + "\\EcgTool.ini";
	Ini = new TIniFile(file);

	bFilter = false;
	bShowEcgData = false;
	}
//---------------------------------------------------------------------------
__fastcall TfmData::~TfmData()
	{
	delete Ini;
	}
//---------------------------------------------------------------------------
bool TfmData::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.PositionenToCombo(cbPosition);
	ftools.FormLoad(this);
	ShowEcgData();
	edIdVon->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
inline void TfmData::StartJob(int max)
	{
	pbJob->Max = max;
	pbJob->Position = 0;
	pbJob->Visible = true;
	}
//---------------------------------------------------------------------------
inline void TfmData::TickJob(int tick) //tick = 1
	{
	pbJob->Position += tick;
	}
//---------------------------------------------------------------------------
inline void TfmData::EndJob()
	{
	pbJob->Visible = false;
	}
//---------------------------------------------------------------------------
void TfmData::ShowEcgData()
	{
	if (bShowEcgData) return;

	bShowEcgData = true; // verhindern dass die Funktion mehrfach aufgerufen wird
	acRefresh->Enabled = false;

	lvData->Items->Clear();
	lvData->Items->BeginUpdate();

	//Daten aus Datenbank anzeigen
	if (!fmysql.LoadData())
		{
		Application->MessageBox(fmysql.error_msg.c_str(), "Fehler aufgetreten", MB_OK);
		lvData->Items->EndUpdate();
		return;
		}

	StartJob(fmysql.num_rows);

	sMySqlRow row;
	TListItem* item;
	while (fmysql.nextRow())
		{
		TickJob();
		row = fmysql.row;

		if (!CheckFilter(row)) continue;

		item = lvData->Items->Add();
		item->Data = (void*) row.ident;
		item->Caption = String(row.ident);
		item->SubItems->Add(row.name);
		item->SubItems->Add(ftools.GetPosition(row.pos));
		for (int i = 0; i < 5; i++)
			item->SubItems->Add(String(row.werte[i]));
		}

	lvData->Items->EndUpdate();
	bShowEcgData = false;
	acRefresh->Enabled = true;
	EndJob();
	}
//---------------------------------------------------------------------------
bool TfmData::BuildFilter()
	{
	if (bFilter) return false;
	bFilter = true;

	ffilter.identVon = edIdVon->Text.ToIntDef(-1);
	ffilter.identBis = edIdBis->Text.ToIntDef(-1);

	ffilter.name = edName->Text;
	ffilter.pos  = (ePosition)cbPosition->ItemIndex;
	//...todo

	bFilter = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmData::CheckFilter(sMySqlRow row)
	{
	if (ffilter.identVon > 0 && row.ident < ffilter.identVon) return false;
	if (ffilter.identBis > 0 && row.ident > ffilter.identBis) return false;

	if (ffilter.name != "")
		{
		//enthält-Suche
		String nn = String(row.name).LowerCase();
		if (nn.Pos(ffilter.name.LowerCase()) <= 0)
        	return false;
		}

	if (ffilter.pos > posNone)
		{
		if (row.pos != ffilter.pos)
			return false;
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmData::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acRefreshExecute(TObject *Sender)
	{
	ShowEcgData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acFilterExecute(TObject *Sender)
	{
	if (BuildFilter())
    	ShowEcgData();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmData::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::btCloseClick(TObject *Sender)
	{
	acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edIdVonKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_RETURN)
		{
		Key = 0;
		acFilterExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edIdVonExit(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edNameChange(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::cbPositionChange(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------

