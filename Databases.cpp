//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "database/classMySql.h"

#include "database/baseforms/baseDesc.h"
#include "database/baseforms/baseEcgData.h"
#include "database/baseforms/baseSession.h"
#include "database/baseforms/basePeople.h"

#include "Databases.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmDatabases *fmDatabases;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgShowDatabases(TForm* Papa)
	{
	TfmDatabases* Form = new TfmDatabases(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmDatabases::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmDatabases::TfmDatabases(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmDatabases::~TfmDatabases()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmDatabases::FormShow(TObject *Sender)
	{
	ftools.FormLoad(this);
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDatabases::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled   = false;
	pnNoTab->Visible    = false;
	pnNoTab->Align      = alClient;
	pnNoTab->BevelOuter = bvNone;
	ShowTabellen();

	pnSelectDb->Align      = alClient;
	pnSelectDb->BevelOuter = bvNone;
	pnSelectDb->Visible    = true;
	pnSelectDb->BringToFront();
	}
//---------------------------------------------------------------------------
void __fastcall TfmDatabases::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmDatabases::ShowTabellen()
	{
	fmysql.listTabs(lvData);
	}
//---------------------------------------------------------------------------
void TfmDatabases::SelectTab(String tab)
	{
	if (tab == "") return;
	if (!fmysql.tabExists(tab))
		{
		ftools.ErrBox("Die Tabelle <%s> existiert nicht (mehr).", tab);
		return;
		}

	pnNoTab->Visible = false;
	pnSelectDb->Visible = false;
	if (SelectTabDesc(tab)) return; //Tabelle war DescDb und wurde angezeigt

	//restliche Tabellen von Hand prüfen
	if (tab == "ecgdata")
		{
		TfmBaseEcg* fm = CreateEcgForm(this, pnTabelle);
		fm->ShowData();
		}
	else if (tab == "sessions")
		{
		TfmBaseSession* fm = CreateSessionForm(this, pnTabelle);
		fm->ShowData();
		}
	else if (tab == "subjects")
		{
		TfmBasePeople* fm = CreatePeopleForm(this, pnTabelle, eShow);
		fm->ShowData();
		}
	else if (tab == "sessionresearchers")
		{
		pnNoTab->Visible = true;
		pnNoTab->BringToFront();
		}
	else if (tab == "subdiseases")
		{
		pnNoTab->Visible = true;
		pnNoTab->BringToFront();
		}
	else if (tab == "templates")
		{
		pnNoTab->Visible = true;
		pnNoTab->BringToFront();
		}
	else
		{
		//Datenbank wurde noch nicht berücksichtigt
		ftools.MsgBox("Die Datenbank <%s> wurde hier noch nicht berücksichtigt.", tab);
		}
	}
//---------------------------------------------------------------------------
bool TfmDatabases::SelectTabDesc(String tab)
	{
	//return true = Tabelle war eine Desc-Tabelle und wurde angezeigt
		 if (tab == "algfeatures") 		return createForm(fmysql.algfeatures);
	else if (tab == "algpreprocessing") return createForm(fmysql.algpreproc);
	else if (tab == "algrpeaks") 		return createForm(fmysql.algrpeaks);
	else if (tab == "diseases") 		return createForm(fmysql.diseases);
	else if (tab == "places") 			return createForm(fmysql.places);
	else if (tab == "positions") 		return createForm(fmysql.positions);
	else if (tab == "postures") 		return createForm(fmysql.postures);
	else if (tab == "researchers") 		return createForm(fmysql.researchers);
	else if (tab == "states") 			return createForm(fmysql.states);
	else return false;
	}
//---------------------------------------------------------------------------
bool TfmDatabases::createForm(cMySqlDescDb& desc)
	{
	TfmBaseDesc* fm = CreateDescForm(this, pnTabelle, desc, eShow);
	fm->ShowData();
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmDatabases::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmDatabases::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmDatabases::lvDataDblClick(TObject *Sender)
	{
	TListItem* item = lvData->Selected;
	if (!item)
		{
		pnSelectDb->Align = alClient;
		pnSelectDb->Visible = true;
		pnSelectDb->BringToFront();
		return;
		}

	String tab = item->Caption;
	SelectTab(tab); 
	}
//---------------------------------------------------------------------------

