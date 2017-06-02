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

	if (cxRpeaksAnna->Checked)
		{
		if (cxFeatChoi->Checked) 	DoFeatures(fmysql.ecg.row, 1, fFeatChoi.AlgIdent, true);
		if (cxFeatRandom->Checked)  DoFeatures(fmysql.ecg.row, 1, fRandomPoints.AlgIdent, true);
		}

	if (cxRpeaksChoi->Checked)
		{
		if (cxFeatChoi->Checked) 	DoFeatures(fmysql.ecg.row, fRpeaksChoi.AlgIdent, fFeatChoi.AlgIdent, true);
		if (cxFeatRandom->Checked)  DoFeatures(fmysql.ecg.row, fRpeaksChoi.AlgIdent, fRandomPoints.AlgIdent, true);
		}

	Print("Features erstellt");
	}
//---------------------------------------------------------------------------
bool TfmFeatures::InsertFeatures(String features, int algRpeaks, int algFeat)
	{
	sFeature data;
	data.ecgId    = fmysql.ecg.row.ident;
	data.algIdRpeaks = algRpeaks;
	data.algIdFeatures = algFeat;
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
bool TfmFeatures::UpdateFeatures(String features, int algRpeaks, int algFeat)
	{
	sFeature data;
	data.ident    = fmysql.features.row.ident;
	data.ecgId    = fmysql.ecg.row.ident;
	data.algIdRpeaks = algRpeaks;
	data.algIdFeatures = algFeat;
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
bool TfmFeatures::DoFeatures(sEcgData ecgdata, int algRpeaks, int algFeat, bool replace)
	{
	iarray_t array = ecgdata.array_werte;
	if (array.size() <= 0) return false;
	if (algRpeaks <= 0) return false;
	if (algFeat   <= 0) return false;

	iarray_t rpeaks;
	if (algRpeaks == 1) //Anna
		{
		rpeaks = fecg.rpeaks.find(array, NULL);
		if (rpeaks.size() <= 0)
			{
			Print("## Fehler beim Erstellen der Anna-RPeaks");
			Print("## Meldung: %s", fecg.rpeaks.error_msg);
			return false;
			}
		}
	else if (algRpeaks == 2) //Choi
		{
		if (!fRpeaksChoi.findRpeaks(array))
			{
			Print("## Fehler beim Erstellen der Choi-RPeaks");
			Print("## Meldung: %s", fRpeaksChoi.error_msg);
			return false;
			}

		rpeaks = fRpeaksChoi.Rpeaks;
		if (rpeaks.size() <= 0)
			{
			Print("## Fehler beim Erstellen der Choi-RPeaks");
			Print("## Meldung: %s", fRpeaksChoi.error_msg);
			return false;
			}
		}

	String features;
	if (algFeat == 1) //Choi
		{
		if (!fFeatChoi.getFeatures(array, rpeaks))
			; //todo Fehlermeludng

		features = fFeatChoi.features_string;
		if (features == "")
			{
			Print("## Fehler beim Erstellen der Choi-Features");
			Print("## Meldung: %s", fFeatChoi.error_msg);
			return false;
			}
		}
	else if (algFeat == 2) //Random
		{
		//todo: in Klasse bringen
		features = BuildRandomFeatures(array);
		if (features == "")
			{
			Print("## Fehler beim Erstellen der Random-Features");
			Print("## Meldung: %s", fRandomPoints.error_msg);
			return false;
			}
		}

	bool vorhanden = false;
	if (fmysql.features.select(ecgdata.ident, algRpeaks, algFeat))
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
		if (!UpdateFeatures(features, algRpeaks, algFeat))
			return false;
		Count_Edit++;
		}
	else
		{
		if (!InsertFeatures(features, algRpeaks, algFeat))
			return false;
		Count_Neu++;
		}

	return true;
	}
//---------------------------------------------------------------------------
void TfmFeatures::GetAllFeatures()
	{
	String EcgIdents = TfmEcg->GetListedEcg();
	if (EcgIdents == "")
		{
		ftools.ErrBox("Es wurden keine EKG-Daten ausgewählt.");
		return;
		}

	iarray_t idents = ftools.TextToArray(EcgIdents, ";");
	if (idents.size() <= 0)
		{
		ftools.ErrBox("Die ausgewählten EKG-Datensätze konnten nicht umgesetzt werden.");
		return;
		}

	bool bReplace = false;
	if (Application->MessageBox(
		"Es werden Features für die ausgewählten EKG-Datensätze gebildet.\r\n"
		"Sollen eventuell bestehende Feature-Sets dabei überschrieben werden ?",
		"Features für EKG bilden",
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

	int anz_rpeaks = 0;
	if (cxRpeaksAnna->Checked) anz_rpeaks++;
	if (cxRpeaksChoi->Checked) anz_rpeaks++;

	int anz_feat = 0;
	if (cxFeatChoi->Checked)   anz_feat++;
	if (cxFeatRandom->Checked) anz_feat++;

	pbJob->Max = idents.size() * (anz_rpeaks * anz_feat);
	pbJob->Position = 0;
	pbJob->Visible = true;

	Count_Neu  = 0;
	Count_Edit = 0;

	sEcgData data;
	int count = 0;
	for (iarray_itr itr = idents.begin(); itr != idents.end(); itr++)
		{
		pbJob->Position++;
		ilist_t& v = itr->second;
		int id = v[1];
		if (!fmysql.ecg.loadByIdent(id))
			{
			Print("## EKG <%d> nicht gefunden", id);
			continue;
			}

		count++;
		data = fmysql.ecg.row;
		Print("EKG %d (%s)", data.ident, fmysql.people.getNameOf(data.person));

		if (cxRpeaksAnna->Checked)
			{
			if (cxFeatChoi->Checked) 	DoFeatures(fmysql.ecg.row, 1, fFeatChoi.AlgIdent, true);
			pbJob->Position++;
			if (cxFeatRandom->Checked)  DoFeatures(fmysql.ecg.row, 1, fRandomPoints.AlgIdent, true);
			pbJob->Position++;
			}

		if (cxRpeaksChoi->Checked)
			{
			if (cxFeatChoi->Checked) 	DoFeatures(fmysql.ecg.row, fRpeaksChoi.AlgIdent, fFeatChoi.AlgIdent, true);
			pbJob->Position++;
			if (cxFeatRandom->Checked)  DoFeatures(fmysql.ecg.row, fRpeaksChoi.AlgIdent, fRandomPoints.AlgIdent, true);
			pbJob->Position++;
			}
		}
		
	pbJob->Visible = false;
	Print("--------------------------------------------------");
	Print("Es wurden %d EKG-Datensätze bearbeitet", count);
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
