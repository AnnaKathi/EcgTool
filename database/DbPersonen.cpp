//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "database/classMySql.h"
#include "Person.h"
#include "DbPersonen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmData *fmData;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgDatabasePersonen(TForm* Papa)
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

	bSelected = false;
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
	ftools.FormLoad(this);

	fmDiseases = CreateDescForm(this, pnDiseases, fmysql.diseases);
	fmPeople   = CreatePeopleForm(this, pnPeople);
	fmPeople->setCallback(*tCallback);

	fmEcg      = CreateEcgForm(this, pnEcgData);

	fmPeople->ShowData();
	fmDiseases->ShowData();
	fmEcg->ShowData();

	tStartup->Tag = 1; //Init beendet
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::FormClose(TObject *Sender, TCloseAction &Action)
	{
	delete fmEcg;
	delete fmPeople;
	delete fmDiseases;
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
	if (tStartup->Tag == 0) return; //Init noch nicht ausgeführt oder beendet

	//evtl bestehende Filter abschalten
	//acPeopleDisselectExecute(Sender);

	fmDiseases->ShowData();
	fmPeople->ShowData();
	fmEcg->ShowData();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/*******   Callback-Funktionen für die baseListen   ************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmData::OnSelectPerson()
	{
	//todo
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
void __fastcall TfmData::tCallbackTimer(TObject *Sender)
	{
	//TEST
	tCallback->Enabled = false;
	if (!bSelected)
		{
		int person = fmPeople->iPerson;
		if (person <= 0) return;

		//Diseases und EKG-Daten anpassen
		fmDiseases->LockFilter();
		//fmDiseases->ShowDataOfPerson(person);

		fmEcg->LockFilter();
		fmEcg->ShowEcgOf(person);
		bSelected = true;
		}
	else
		{
		//Auswahl wieder aufheben
		fmDiseases->DislockFilter();
		fmDiseases->ShowData();

		fmEcg->DislockFilter();
		fmEcg->ShowData();
		bSelected = false;
		}
	}
//---------------------------------------------------------------------------

