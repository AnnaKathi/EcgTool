//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "database/classMySql.h"

#include "addEcgMessungen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmAddMessung *fmAddMessung;
extern cMySql fmysql;
//---------------------------------------------------------------------------
__fastcall TfmAddMessung::TfmAddMessung(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmysql.people.listInCombo(cbPerson,  1);
	fmysql.states.listInCombo(cbZustand, 1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmAddMessung::SetCallbackTimer(TTimer* timer)
	{
	fCallbackTimer = timer;
	fCallbackTimer->Enabled = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddMessung::GetEcgHeader(int& person)
	{
	person = (int)cbPerson->Items->Objects[cbPerson->ItemIndex];
	fRow = -1;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddMessung::GetNextEcgRow(
	int& state, int& lage, int& anz,
	int& pos, String& file, int& format, String& delim)
	{
	fRow++;
	if (fRow >= lvData->Items->Count) return false;

	TListItem* item = lvData->Items->Item[fRow];
	lage = item->Caption.ToInt();
	if (lage <= 0) return false;

	state = item->SubItems->Strings[0].ToInt();
	if (state <= 0) return false;

	pos = item->SubItems->Strings[1].ToInt();
	if (pos <= 0)

	anz = item->SubItems->Strings[2].ToInt();
	if (anz <= 0) return false;

	file = item->SubItems->Strings[3];
	if (file == "") return false;

	format = cbFormat->ItemIndex;
	if (format < 0) return false;

	delim = cbDelim->ItemIndex;
	if (delim == "") return false;

	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddMessung::LoadFile(eLage lage)
	{
	int state = (int)cbZustand->Items->Objects[cbZustand->ItemIndex];
	if (!OpenDialog->Execute()) return false;

	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	eDatFormat format;
	if (cbFormat->ItemIndex == 1)
		format = formatADS;
	else
		format = formatNone;

	String file = OpenDialog->FileName;

	//TODO: getFile umstellen, sodass nicht eine bestimmte Spalte, sondern
	//ein bestimmter Lead eingelesen wird, z.B. V1-V2 = Brust eng
	if (cxLead1->Checked) //Brust weit
		{
		if (!fecg.data.getFile(file, format, delim, 1, 0, 3000))
			{
			; //todo Fehlermeludng
			return false;
			}

		int anz = fecg.data.data_array.size();
		AddLine(file, lage, (eState)state, posBrustNormal, anz);
		}

	if (cxLead2->Checked) //Brust eng
		{
		if (!fecg.data.getFile(file, format, delim, 3, 0, 3000))
			{
			; //todo Fehlermeludng
			return false;
			}

		int anz = fecg.data.data_array.size();
		AddLine(file, lage, (eState)state, posBrustEng, anz);
		}

	if (cxLead3->Checked) //Rücken
		{
		if (!fecg.data.getFile(file, format, delim, 5, 0, 3000))
			{
			; //todo Fehlermeludng
			return false;
			}

		int anz = fecg.data.data_array.size();
		AddLine(file, lage, (eState)state, posBack, anz);
		}

	if (cxLead4->Checked) //Hände
		{
		if (!fecg.data.getFile(file, format, delim, 7, 0, 3000))
			{
			; //todo Fehlermeludng
			return false;
			}

		int anz = fecg.data.data_array.size();
		AddLine(file, lage, (eState)state, posHandBack, anz);
		}

	return true;
	}
//---------------------------------------------------------------------------
void TfmAddMessung::AddLine(String file, eLage lage, eState state, ePosition pos, int anz)
	{
	TListItem* item = lvData->Items->Add();
	item->Caption = String(lage);
	item->SubItems->Add(String(state));
	item->SubItems->Add(String(pos)); //todo dynmaisch machen
	item->SubItems->Add(String(anz));
	item->SubItems->Add(file);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::addLiegendExecute(TObject *Sender)
	{
	LoadFile(lageLiegend);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::addSitzendExecute(TObject *Sender)
	{
	LoadFile(lageSitzend);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::addStehendExecute(TObject *Sender)
	{
	LoadFile(lageStehend);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::addGehendExecute(TObject *Sender)
	{
	LoadFile(lageGehend);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddMessung::Button2Click(TObject *Sender)
	{
	fCallbackTimer->Enabled = true;
	}
//---------------------------------------------------------------------------

