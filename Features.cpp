//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "database/classMySql.h"

#include "Features.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmFeatures *fmFeatures;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgFeatures(TForm* Papa)
	{
	TfmFeatures* Form = new TfmFeatures(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmFeatures::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmFeatures::TfmFeatures(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmFeatures::~TfmFeatures()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::FormShow(TObject *Sender)
	{
	ftools.FormLoad(this);
	TfmEcg = CreateEcgForm(this, pnEcg);
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	TfmEcg->SelectEcg(CallbackEcg);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	delete TfmEcg;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmFeatures::Print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
void TfmFeatures::GetSelectedEcg()
	{
	int id = TfmEcg->GetSelectedEcg();
	if (id <= 0) return;

	if (!fmysql.ecg.loadByIdent(id))
		{
		ftools.ErrBox("Das EKG <%d> konnte nicht geladen werden. Die Datenbank meldet: %s",
			id, fmysql.ecg.error_msg);
		return;
		}

	iarray_t array = fmysql.ecg.row.array_werte;

	Print("EKG geladen:");
	Print("\tSession: %d", fmysql.ecg.row.session);
	Print("\tPerson: %d", fmysql.ecg.row.person);
	Print("\tAnz. Werte: %d", array.size());
	}
//---------------------------------------------------------------------------
String TfmFeatures::BuildRandomFeatures(iarray_t array)
	{
	//todo Stringbildung nach classRandomPoints verlagern
	//Standardherzschlag berechnen und für diesen dann die Random Points
	//berechnen lassen
	iarray_t beat = fHeartbeats.calcAvBeat(array);
	if (beat.size() <= 0)
		{
		Print("## Fehler beim Berechnen des Standardherzschlags. Die Klasse "
			"cHeartbeats meldet: %s", fHeartbeats.error_msg);
		return "";
		}
	//Print("Standardherzschlag berechnet");

	if (!fRandomPoints.getRandomPointsFromBeat(beat, 20))
		{
		Print("## Fehler beim Berechnen der Random Points. Die Klasse "
			"cRandomPoints meldet: %s", fRandomPoints.error_msg);
		return "";
		}
	//Print("Random Points berechnet");

	if (!fRandomPoints.resetBeatPoints())
		{
		Print("## Fehler beim Zurücksetzen der Random Points. Die Klasse "
			"cRandomPoints meldet: %s", fRandomPoints.error_msg);
		return "";
		}

	String features = "";
	while (fRandomPoints.nextPointInBeat())
		{
		if (features == "")
			features = String(fRandomPoints.randomPoint);
		else
			features += ";" + String(fRandomPoints.randomPoint);
		}
	return features;
	}
//---------------------------------------------------------------------------
void TfmFeatures::GetFeatures()
	{
	//fmysql-ecg umlesen in fecg
	sEcgData data = fmysql.ecg.row;
	Print("-------------------------------------------------------");
	Print("Features bilden für EKG <%d> %s",
		data.ident, fmysql.people.getNameOf(data.person));

	if (cxChoi->Checked)
		{
		if (!DoFeatures(fmysql.ecg.row, fChoi.AlgNr, true))
			return;
		}

	if (cxRandom->Checked)
		{
		if (!DoFeatures(fmysql.ecg.row, fRandomPoints.AlgNr, true))
			return;
		}

	Print("Features erstellt");
	}
//---------------------------------------------------------------------------
bool TfmFeatures::InsertFeatures(String features, int alg)
	{
	sFeature data;
	data.ecgId    = fmysql.ecg.row.ident;
	data.algId    = alg;
	data.features = features;

	if (!fmysql.features.insert(data))
		{
		ftools.ErrBox("Die Features konnten nicht gespeichert werden. "
			"Die Datenbank meldet: %s", fmysql.features.error_msg);
		Print("## Fehler beim Speichern: %s", fmysql.features.error_msg);
		return false;
		}
	//Print("Datensatz gespeichert, neue ID = %d", fmysql.features.row.ident);
	return true;
	}
//---------------------------------------------------------------------------
bool TfmFeatures::UpdateFeatures(String features, int alg)
	{
	sFeature data;
	data.ident    = fmysql.features.row.ident;
	data.ecgId    = fmysql.ecg.row.ident;
	data.algId    = alg;
	data.features = features;

	if (!fmysql.features.update(data))
		{
		ftools.ErrBox("Die Features konnten nicht geändert werden. "
			"Die Datenbank meldet: %s", fmysql.features.error_msg);
		Print("## Fehler beim Speichern: %s", fmysql.features.error_msg);
		return false;
		}
	//Print("Datensatz gespeichert, ID = %d", fmysql.features.row.ident);
	return true;
	}
//---------------------------------------------------------------------------
bool TfmFeatures::DoFeatures(sEcgData ecgdata, int alg, bool replace)
	{
	iarray_t array = ecgdata.array_werte;
	if (array.size() <= 0) return false;
	if (alg < 0) 		   return false;

	String features;
		 if (alg == fChoi.AlgNr) 		 features = fChoi.getFeaturesStr2(array);
	else if (alg == fRandomPoints.AlgNr) features = BuildRandomFeatures(array);
	else return false;

	if (features == "")
		{
		Print("## Fehler beim Erstellen der Features");
		return false;
		}

	bool vorhanden = false;
	if (fmysql.features.select(ecgdata.ident, alg))
		{
		//Print("\tDatensatz bereits vorhanden...");
		vorhanden = true;
		if (!replace)
			{
			Print("Datensatz <%d> bereits vorhanden -> wird übersprungen", ecgdata.ident);
			return true;
			}
		}

	if (vorhanden)
		{
		if (!UpdateFeatures(features, alg))
			return false;
		Count_Edit++;
		}
	else
		{
		if (!InsertFeatures(features, alg))
			return false;
		Count_Neu++;
		}
		
	return true;
	}
//---------------------------------------------------------------------------
void TfmFeatures::GetAllFeatures()
	{
	bool bReplace = false;
	if (Application->MessageBox(
		"Es werden Features für alle in der Datenbank "
		"vorhandenen EKG-Daten gebildet.\r\n"
		"Sollen bestehende Feature-Sets dabei überschrieben werden ?",
		"RandomPoint-Features für alle EKG bilden",
		MB_YESNO) == ID_YES)
		bReplace = true;

	Print("--------------------------------------------------");
	Print("--- Feature-Sets bilden --------------------------");
	if (bReplace)
		Print("--- bestehende Datensätze überschreiben ----------");
	else
		Print("--- bestehende Datensätze bestehen lassen --------");
	Print("--------------------------------------------------");

	if (!fmysql.ecg.loadTable())
		{
		Print("## Die EKG-Tabelle konnte nicht geladen werden.");
		Print("## Die Datenbank meldet: %s", fmysql.ecg.error_msg);
		return;
		}
	//Print("Datenbank ecgdata geladen, %d Datensätze", fmysql.ecg.getSize());

	int max = 0;
	if (cxChoi->Checked)   max += fmysql.ecg.getSize();
	if (cxRandom->Checked) max += fmysql.ecg.getSize();
	pbJob->Max = max;
	pbJob->Position = 0;
	pbJob->Visible = true;

	Count_Neu  = 0;
	Count_Edit = 0;

	sEcgData data;
	while (fmysql.ecg.nextRow())
		{
		pbJob->Position++;
		data = fmysql.ecg.row;
		Print("EKG %d (%s)", data.ident, fmysql.people.getNameOf(data.person));

		if (cxChoi->Checked)
			{
			if (!DoFeatures(data, fChoi.AlgNr, bReplace))
				break;
			}

		if (cxRandom->Checked)
			{
			if (!DoFeatures(data, fRandomPoints.AlgNr, bReplace))
				break;
			}
		}
		
	pbJob->Visible = false;
	Print("--------------------------------------------------");
	Print("Es wurden %d EKG-Datensätze bearbeitet", fmysql.ecg.getSize());
	Print("\tDatensätze neu anleget\t: %d", Count_Neu);
	Print("\tDatensätze geändert\t: %d", Count_Edit);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::CallbackEcgTimer(TObject *Sender)
	{
	CallbackEcg->Enabled = false;
	GetSelectedEcg();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::btFeaturesClick(TObject *Sender)
	{
	GetFeatures();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatures::btBuildAllClick(TObject *Sender)
	{
    GetAllFeatures();
	}
//---------------------------------------------------------------------------
