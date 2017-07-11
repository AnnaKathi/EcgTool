//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <string.h>

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

	ftools.FormLoad(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddPersonSession::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	ftools.FormSave(this);
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
void __fastcall TfmAddPersonSession::mZ1P1DblClick(TObject *Sender)
	{
	//hier landen alle Memo-Klicks
	int state, lage;
	TMemo* memo = (TMemo*) Sender;
	if (!getMemo(memo->Name, state, lage)) return;

	String bp; int puls;
	if (state == 1)
		{
		if (edZ1BP->Text == "" || edZ1Puls->Text == "") return;
		bp = edZ1BP->Text;
		puls = edZ1Puls->Text.ToIntDef(-1);
		}

	else if (state == 2)
		{
		if (edZ2BP->Text == "" || edZ2Puls->Text == "") return;
		bp = edZ2BP->Text;
		puls = edZ2Puls->Text.ToIntDef(-2);
		}

	else if (state == 3)
		{
		if (edZ3BP->Text == "" || edZ3Puls->Text == "") return;
		bp = edZ3BP->Text;
		puls = edZ3Puls->Text.ToIntDef(-3);
		}

	else if (state == 4)
		{
		if (edZ4BP->Text == "" || edZ4Puls->Text == "") return;
		bp = edZ4BP->Text;
		puls = edZ4Puls->Text.ToIntDef(-4);
		}

	if (!OpenDialog->Execute()) return;

	String file = OpenDialog->FileName;
	if (!LoadFile((eState)state, (eLage)lage, bp, puls, file)) return; //Todo, Fehlermeldung

	TStringList* liste = new TStringList();

	for (int i = 2; i < memo->Lines->Count; i++)
		liste->Add(memo->Lines->Strings[i]);

	memo->Lines->Clear();
	memo->Lines->Add(ftools.fmt("%d Datei(en)", liste->Count+1).c_str());
	memo->Lines->Add("-------------");

	char help[MAX_PATH];
	sprintf(help, "%s", file.c_str());
	char* pt = strrchr(help, '.');
	if (pt) *pt = 0;
	pt = strrchr(help, '\\');
	if (pt)
		{
		*pt = 0;
		sprintf(help, "%s", pt+1);
		}

	memo->Lines->Add(ftools.fmt("%.15s...", help));
	for (int i = liste->Count-1; i >= 0; i--)
		memo->Lines->Add(liste->Strings[i]);
		
	delete liste;
	}
//---------------------------------------------------------------------------
bool TfmAddPersonSession::getMemo(String name, int& state, int& lage)
	{
	state = name.SubString(3, 1).ToIntDef(-1);
	lage  = name.SubString(5, 1).ToIntDef(-1);
	if (state < 0 || lage < 0) return false;
	else return true;
	}
//---------------------------------------------------------------------------
bool TfmAddPersonSession::LoadFile(eState state, eLage lage, String bp, int puls, String file)
	{
	String delim = "\t"; // TODO
	eDatFormat format = formatADS; //Todo

	int gesamt = 0;

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
		AddLine(file, lage, (eState)state, posBrustNormal, anz, bp, puls);
		gesamt += anz;
		}

	if (cxLead2->Checked) //Brust eng
		{
		if (!fecg.data.getFile(file, format, delim, 3, 0, 3000))
			{
			; //todo Fehlermeludng
			return false;
			}

		int anz = fecg.data.data_array.size();
		AddLine(file, lage, (eState)state, posBrustEng, anz, bp, puls);
		gesamt += anz;
		}

	if (cxLead3->Checked) //Rücken
		{
		if (!fecg.data.getFile(file, format, delim, 5, 0, 3000))
			{
			; //todo Fehlermeludng
			return false;
			}

		int anz = fecg.data.data_array.size();
		AddLine(file, lage, (eState)state, posBack, anz, bp, puls);
		gesamt += anz;
		}

	if (cxLead4->Checked) //Hände
		{
		if (!fecg.data.getFile(file, format, delim, 7, 0, 3000))
			{
			; //todo Fehlermeludng
			return false;
			}

		int anz = fecg.data.data_array.size();
		AddLine(file, lage, (eState)state, posHandBack, anz, bp, puls);
		gesamt += anz;
		}

	if (gesamt > 0) return true;
	else return false;
	}
//---------------------------------------------------------------------------
void TfmAddPersonSession::AddLine(String file, eLage lage, eState state, ePosition pos, int anz, String bp, int puls)
	{
	TListItem* item = lvData->Items->Add();
	item->Caption = String(lage);
	item->SubItems->Add(String(state));
	item->SubItems->Add(String(pos)); //todo dynmaisch machen
	item->SubItems->Add(String(anz));
	item->SubItems->Add(bp);
	item->SubItems->Add(String(puls));
	item->SubItems->Add(file);
	}
//---------------------------------------------------------------------------

