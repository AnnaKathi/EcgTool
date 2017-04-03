//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <time.h>
#include <systdate.h>

#include "RequestBox.h"
#include "database/classMySql.h"
#include "database/Person.h"
#include "Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSession *fmSession;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgNewSession(TForm* Papa)
	{
	TfmSession* Form = new TfmSession(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
__fastcall TfmSession::TfmSession(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmSession::~TfmSession()
	{
	}
//---------------------------------------------------------------------------
bool TfmSession::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	edStamp->Text = getNow();
	fmysql.people.listInCombo(cbPerson, 1);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String TfmSession::getNow()
	{
	TDateTime dt;
	return dt.CurrentDateTime().DateTimeString();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSession::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acReAddExecute(TObject *Sender)
	{
	//todo: richtig l�sen, Researcher aus DB laden und anzeigen
	//jetzt erstmal quick and dirty
	String name = DlgRequest(this, "Name des Untersuchenden");
	if (name != "")
		{
		TListItem* item = lvResearchers->Items->Add();
		item->Caption = lvResearchers->Items->Count;
		item->SubItems->Add(name);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acReDelExecute(TObject *Sender)
	{
	if (lvResearchers->SelCount <= 0) return;
	TListItem* item = lvResearchers->Selected;
	item->Delete();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acSaveExecute(TObject *Sender)
	{
	//EKG-Daten zur Person abspeichern
	save(edL1); save(edL2); save(edL3);
	save(edS1); save(edS2); save(edS3);
	save(edT1); save(edT2); save(edT3);
	save(edG1); save(edG2); save(edG3);
	}
//---------------------------------------------------------------------------
bool TfmSession::save(TEdit* ed)
	{
	/*
	if (ed->Text == "") return true;
	if (!fdata.getFile(edL1->Hint, "\t", 0, 3000))
		; //todo

	fsql.mysql_data.array = fdata.data_array;
	sprintf(fsql.mysql_data.name, "%.63s", cbPerson->Text);

		 if (ed->Tag == 1) fsql.mysql_data.pos = posLiegend;
	else if (ed->Tag == 2) fsql.mysql_data.pos = posSitzend;
	else if (ed->Tag == 3) fsql.mysql_data.pos = posStehend;
	else if (ed->Tag == 2) fsql.mysql_data.pos = posGehend;
	else return false;

	if (!fsql.saveToDbase())
		; //todo

	*/
	return true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acResetExecute(TObject *Sender)
	{
	edL1->Text = ""; edL2->Text = ""; edL3->Text = "";
	edS1->Text = ""; edS2->Text = ""; edS3->Text = "";
	edT1->Text = ""; edT2->Text = ""; edT3->Text = "";
	edG1->Text = ""; edG2->Text = ""; edG3->Text = "";

	cbPerson->ItemIndex = 0;
	cbPerson->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::acPersonAddExecute(TObject *Sender)
	{
	if (DlgPersonNew(this))
    	fmysql.people.listInCombo(cbPerson, 1);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmSession::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::btNowClick(TObject *Sender)
	{
	edStamp->Text = getNow();
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::lvResearchersClick(TObject *Sender)
	{
	if (lvResearchers->SelCount <= 0)
		acReDel->Enabled = false;
	else
		acReDel->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::edL1DblClick(TObject *Sender)
	{
	TEdit* ed = (TEdit*)Sender;
	if (OpenECG->Execute())
		{
		ed->Hint  = OpenECG->FileName;
		ed->Text  = "geladen";
		ed->Color = clMoneyGreen;
		}
	else
		{
		ed->Hint  = "";
		ed->Text  = "";
		ed->Color = clWhite;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::edL1MouseDown(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y)
	{
	//beim Rechtsklick l�schen
	if (Button == mbRight)
		{
		TEdit* ed = (TEdit*)Sender;
		ed->Hint  = "";
		ed->Text  = "";
		ed->Color = clWhite;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmSession::edL1KeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
	{
	if (Key == VK_INSERT)
		{
		TEdit* ed = (TEdit*)Sender;
		if (OpenECG->Execute())
			{
			ed->Text  = "geladen";
			ed->Color = clMoneyGreen;
			}
		else
			{
			ed->Text  = "";
			ed->Color = clWhite;
			}
		ed->SetFocus();
		}
	else if (Key == VK_DELETE)
		{
		TEdit* ed = (TEdit*)Sender;
		ed->Hint  = "";
		ed->Text  = "";
		ed->Color = clWhite;
		}
	}
//---------------------------------------------------------------------------


