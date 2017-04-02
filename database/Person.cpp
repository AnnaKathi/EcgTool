//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "Person.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmPerson *fmPerson;
//---------------------------------------------------------------------------
bool DlgPersonNew(TForm* Papa)
	{
	TfmPerson* Form = new TfmPerson(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(-1);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool DlgPersonChange(TForm* Papa, int person)
	{
	TfmPerson* Form = new TfmPerson(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(person);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmPerson::Execute(int person)
	{
	iPerson = person;
	person < 0 ? bNewPerson = true : bNewPerson = false;
	
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmPerson::TfmPerson(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmPerson::~TfmPerson()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	if (!fmysql.open())
		{
		String msg =
			"Die MySql-Datenbank 'ecg' konnte nicht ge�ffnet werden."
			"Die Funktion meldet: " + fmysql.error_msg;
		Application->MessageBox(msg.c_str(), "Fehler beim �ffnen der Datenbank", MB_OK);
		Close();
		return;
		}

	lvDiseases->Items->Clear();
	if (bNewPerson)
		{
		edVorname->Text  = "";
		edNachname->Text = "";
		}
	else
		{
		if (!fmysql.people.get(iPerson))
			{
			String msg = "Die Person <" + String(iPerson) + "> konnte nicht gefunden werden.";
			Application->MessageBox(msg.c_str(), "Fehler beim Laden", MB_OK);
			Close();
			return;
			}
		else
			{
			edVorname->Text  = fmysql.people.row.vorname;
			edNachname->Text = fmysql.people.row.nachname;

			sarray_t dis;
			dis = fmysql.people.getDiseasesOf(iPerson);
			dis = fmysql.diseases.getNamesOf(dis);

			TListItem* item;
			for (sarray_itr itr = dis.begin(); itr != dis.end(); itr++)
				{
				slist_t& v = itr->second;
				item = lvDiseases->Items->Add();
				item->Data = (void*) v[0].ToInt();
				item->Caption = v[0];
				item->SubItems->Add(v[1]);
				}
			}
		}

	if (bNewPerson) Caption = "Person anlegen";
	else Caption = "Person �ndern";
	edVorname->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::FormClose(TObject *Sender, TCloseAction &Action)
	{
	fmysql.close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmPerson::SaveData()
	{
	if (edVorname->Text == "" || edNachname->Text == "") return false;

	sPeople data;
	data.ident = iPerson;
	sprintf(data.vorname,  "%.127s", edVorname->Text.c_str());
	sprintf(data.nachname, "%.127s", edNachname->Text.c_str());

	if (bNewPerson && !fmysql.people.insert(data))
		{
		//todo Fehlermeldung
		return false;
		}

	else if (!bNewPerson && !fmysql.people.update(data))
		{
		//todo Fehlermeldung
		return false;
		}

	else
		return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acSaveExecute(TObject *Sender)
	{
	if (SaveData())
		acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acDisAddExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acDisDelExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmPerson::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

