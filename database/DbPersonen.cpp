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

	bFilter = false;
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

	fmDiseases = CreateDiseaseForm(this, pnDiseases);

	ShowPeople();
	fmDiseases->ShowData();
	ShowEcgData();
	tStartup->Tag = 1; //Init beendet
	edIdVon->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::FormClose(TObject *Sender, TCloseAction &Action)
	{
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
void TfmData::ShowEcgData()
	{
	acRefresh->Enabled = false;

	lvData->Items->Clear();
	lvData->Items->BeginUpdate();

	//Daten aus Datenbank anzeigen
	if (!fmysql.ecg.loadTable())
		{
		Application->MessageBox(fmysql.error_msg.c_str(), "Fehler aufgetreten", MB_OK);
		lvData->Items->EndUpdate();
		return;
		}

	StartJob(fmysql.ecg.num_rows);

	TListItem* item;
	while (fmysql.ecg.nextRow())
		{
		TickJob();

		if (!CheckEcgFilter()) continue;

		item = lvData->Items->Add();
		item->Data = (void*) fmysql.ecg.row.ident;
		item->Caption = String(fmysql.ecg.row.ident);

		String name = fmysql.people.getNameOf(fmysql.ecg.row.person);
		item->SubItems->Add(name);

		item->SubItems->Add(fmysql.ecg.row.session);
		item->SubItems->Add(ftools.GetPosition(fmysql.ecg.row.pos));
		for (int i = 0; i < 5; i++)
			item->SubItems->Add(String(fmysql.ecg.row.werte[i]));
		}

	lvData->Items->EndUpdate();
	acRefresh->Enabled = true;
	EndJob();
	}
//---------------------------------------------------------------------------
void TfmData::ShowEcgOf(int person)
	{
	acRefresh->Enabled = false;

	lvData->Items->Clear();
	lvData->Items->BeginUpdate();

	//Daten aus Datenbank anzeigen
	if (!fmysql.ecg.loadByPerson(person))
		{
		Application->MessageBox(fmysql.error_msg.c_str(), "Fehler aufgetreten", MB_OK);
		lvData->Items->EndUpdate();
		return;
		}

	StartJob(fmysql.ecg.num_rows);

	TListItem* item;
	while (fmysql.ecg.nextRow())
		{
		TickJob();

		if (!CheckEcgFilter()) continue;

		item = lvData->Items->Add();
		item->Data = (void*) fmysql.ecg.row.ident;
		item->Caption = String(fmysql.ecg.row.ident);

		item->SubItems->Add(fmysql.people.getNameOf(fmysql.ecg.row.person));

		item->SubItems->Add(fmysql.ecg.row.session);
		item->SubItems->Add(ftools.GetPosition(fmysql.ecg.row.pos));
		for (int i = 0; i < 5; i++)
			item->SubItems->Add(String(fmysql.ecg.row.werte[i]));
		}

	lvData->Items->EndUpdate();
	acRefresh->Enabled = true;
	EndJob();
	}
//---------------------------------------------------------------------------
void TfmData::ShowPeople()
	{
	acRefresh->Enabled = false;

	lvPeople->Items->Clear();
	lvPeople->Items->BeginUpdate();

	//Daten aus Datenbank anzeigen
	if (!fmysql.people.loadTable())
		{
		Application->MessageBox(fmysql.error_msg.c_str(), "Fehler aufgetreten", MB_OK);
		lvPeople->Items->EndUpdate();
		return;
		}

	StartJob(fmysql.people.num_rows);

	TListItem* item;
	String name;
	while (fmysql.people.nextRow())
		{
		TickJob();

		if (!CheckPeopleFilter()) continue;

		item = lvPeople->Items->Add();
		int person = fmysql.people.row.ident;
		item->Data = (void*) person;
		item->Caption = String(person);
		name = String(fmysql.people.row.vorname) + " " + String(fmysql.people.row.nachname);
		item->SubItems->Add(name.c_str());

		sarray_t dis;
		dis = fmysql.people.getDiseasesOf(person);
		dis = fmysql.diseases.getNamesOf(dis);
		String liste = ""; 
		bool first = true;
		for (sarray_itr itr = dis.begin(); itr != dis.end(); itr++)
			{
			slist_t& v = itr->second;
			if (first)
				{
				first = false;
				liste = v[1];
				}
			else
				liste += ", " + v[1];
			}
		item->SubItems->Add(liste);
		}

	lvPeople->Items->EndUpdate();
	acRefresh->Enabled = true;
	EndJob();
	}
//---------------------------------------------------------------------------
//-- build filters ----------------------------------------------------------
//---------------------------------------------------------------------------
bool TfmData::BuildEcgFilter()
	{
	ffecg.identVon = edIdVon->Text.ToIntDef(-1);
	ffecg.identBis = edIdBis->Text.ToIntDef(-1);

	ffecg.name = edEcgName->Text;
	ffecg.pos  = (ePosition)cbPosition->ItemIndex;
	//...todo

	return true;
	}
//---------------------------------------------------------------------------
bool TfmData::BuildPeopleFilter()
	{
	ffpeople.identVon = edPeopleIdVon->Text.ToIntDef(-1);
	ffpeople.identBis = edPeopleIdBis->Text.ToIntDef(-1);

	ffpeople.name = edPeopleName->Text;
	//...todo

	return true;
	}
//---------------------------------------------------------------------------
//-- check filters ----------------------------------------------------------
//---------------------------------------------------------------------------
bool TfmData::CheckEcgFilter()
	{
	if (ffecg.identVon > 0 && fmysql.ecg.row.ident < ffecg.identVon) return false;
	if (ffecg.identBis > 0 && fmysql.ecg.row.ident > ffecg.identBis) return false;

	if (ffecg.name != "")
		{
		//enthält-Suche
		String nn = fmysql.people.getNameOf(fmysql.ecg.row.person).LowerCase();
		if (nn.Pos(ffecg.name.LowerCase()) <= 0)
			return false;
		}

	if (ffecg.pos > posNone)
		{
		if (fmysql.ecg.row.pos != ffecg.pos)
			return false;
		}
	return true;
	}
//---------------------------------------------------------------------------
bool TfmData::CheckPeopleFilter()
	{
	int id = fmysql.people.row.ident;
	if (ffpeople.identVon > 0 && id < ffpeople.identVon) return false;
	if (ffpeople.identBis > 0 && id > ffpeople.identBis) return false;

	if (ffpeople.name != "")
		{
		//enthält-Suche
		String nn = fmysql.people.getNameOf(id).LowerCase();
		if (nn.Pos(ffpeople.name.LowerCase()) <= 0)
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
	if (tStartup->Tag == 0) return; //Init noch nicht ausgeführt oder beendet

	//evtl bestehende Filter abschalten
	acPeopleDisselectExecute(Sender);

	ShowEcgData();
	fmDiseases->ShowData();
	ShowPeople();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acEcgFilterExecute(TObject *Sender)
	{
	if (tStartup->Tag == 0) return; //Init noch nicht ausgeführt oder beendet
	if (BuildEcgFilter())
		ShowEcgData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acPeopleFilterExecute(TObject *Sender)
	{
	if (tStartup->Tag == 0) return; //Init noch nicht ausgeführt oder beendet
	if (BuildPeopleFilter())
		ShowPeople();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acPeopleDelExecute(TObject *Sender)
	{
	if (lvPeople->SelCount < 0) return;
	else if (lvPeople->SelCount == 1)
		{
		int ident = (int)lvPeople->Selected->Data;
		if (ident <= 0) return;
		if (!fmysql.people.deleteByIdent(ident))
			; //todo
		}

	else //Multi-Select
		{
		for (int i = 0; i < lvPeople->Items->Count; i++)
			{
			TListItem* item = lvPeople->Items->Item[i];
			if (!item->Selected) continue;

			int ident = (int)item->Data;
			if (ident <= 0) continue;
			if (!fmysql.people.deleteByIdent(ident))
				; //todo
			}
		}

	acRefreshExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acPeopleAddExecute(TObject *Sender)
	{
	if (DlgPersonNew(this))
		acRefreshExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acPeopleChangeExecute(TObject *Sender)
	{
	if (lvPeople->SelCount <= 0) return;
	TListItem* item = lvPeople->Selected;
	int person = (int)item->Data;

	if (DlgPersonChange(this, person))
		acRefreshExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acPeopleSelectExecute(TObject *Sender)
	{
	if (lvPeople->SelCount <= 0) return;
	TListItem* item = lvPeople->Selected;
	int person = (int)item->Data;

	fmDiseases->ShowDataOfPerson(person);

	edEcgName->Text = fmysql.people.getNameOf(person);
	edEcgName->Enabled = false;
	ShowEcgOf(person);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acDisSelectExecute(TObject *Sender)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acPeopleDisselectExecute(TObject *Sender)
	{
	//Auswahl aufheben
	lvPeople->Selected = false;

	edEcgName->Text = "";
	edEcgName->Enabled = true;

	ShowEcgData();
	fmDiseases->ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acEcgDelExecute(TObject *Sender)
	{
	if (lvData->SelCount < 0) return;
	else if (lvData->SelCount == 1)
		{
		int ident = (int)lvData->Selected->Data;
		if (ident <= 0) return;
		if (!fmysql.ecg.deleteByIdent(ident))
        	; //todo
		}

	else //Multi-Select
		{
		for (int i = 0; i < lvData->Items->Count; i++)
			{
			TListItem* item = lvData->Items->Item[i];
			if (!item->Selected) continue;

			int ident = (int)item->Data;
			if (ident <= 0) continue;
			if (!fmysql.ecg.deleteByIdent(ident))
				; //todo
			}
		}

	acRefreshExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::acEcgAddExecute(TObject *Sender)
	{
	//
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
		acEcgFilterExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edIdVonExit(TObject *Sender)
	{
	acEcgFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edEcgNameChange(TObject *Sender)
	{
	acEcgFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::cbPositionChange(TObject *Sender)
	{
	acEcgFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::lvDataClick(TObject *Sender)
	{
	if (lvData->SelCount <= 0) acEcgDel->Enabled = false;
	else if (lvData->SelCount == 1)
		{
		acEcgDel->Caption = "&EKG-Datensatz löschen";
		acEcgDel->Enabled = true;
		}
	else //Multiselect
		{
		acEcgDel->Caption = "&EKG-Datensätze löschen";
		acEcgDel->Enabled = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::lvPeopleClick(TObject *Sender)
	{
	if (lvPeople->SelCount <= 0)
		{
		acPeopleDel->Enabled    = false;
		acPeopleSelect->Enabled = false;
		acPeopleChange->Enabled = false;
		}
	else
		{
		acPeopleDel->Enabled    = true;
		acPeopleSelect->Enabled = true;
		acPeopleChange->Enabled = true;

		if (lvPeople->SelCount == 1) //Single Select
			acPeopleDel->Caption = "&Personen-Datensatz löschen";
		else //Multiselect
			acPeopleDel->Caption = "&Personen-Datensätze löschen";
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::lvPeopleDblClick(TObject *Sender)
	{
	//nur die EKG-Daten der Person anzeigen
	acPeopleSelectExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edPeopleNameChange(TObject *Sender)
	{
	acPeopleFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edPeopleNameExit(TObject *Sender)
	{
	acPeopleFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmData::edPeopleNameKeyPress(TObject *Sender, char &Key)
	{
	acPeopleFilterExecute(Sender);
	}
//---------------------------------------------------------------------------

