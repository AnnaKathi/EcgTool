//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "database/classMySql.h"

#include "ChoiFeatures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmChoiFeatures *fmChoiFeatures;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgChoiFeatures(TForm* Papa)
	{
	TfmChoiFeatures* Form = new TfmChoiFeatures(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmChoiFeatures::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoiFeatures::TfmChoiFeatures(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::FormShow(TObject *Sender)
	{
	TfmEcg = CreateEcgForm(this, pnEcg);
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	TfmEcg->SelectEcg(CallbackEcg);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	delete TfmEcg;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmChoiFeatures::Print(char* msg, ...)
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
void TfmChoiFeatures::GetSelectedEcg()
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
void TfmChoiFeatures::GetFeatures()
	{
	//fmysql-ecg umlesen in fecg
	Print("-------------------------------------------------------");
	iarray_t array = fmysql.ecg.row.array_werte;
	int bp = array.size();

	String features = fChoi.getFeaturesStr2(array);
	if (features == "")
		{
		ftools.ErrBox("Die Features konnten nicht berechnet werden. "
			"Die Choi-Klasse meldet: %s", fChoi.error_msg);
		Print("## Fehler beim Erstellen der Features: %s", fChoi.error_msg);
		return;
		}
	Print("Features berechnet");

	sFeature data;
	data.ecgId = fmysql.ecg.row.ident;
	data.algId = 2; //todo
	data.features = features;

	if (!fmysql.features.insert(data))
		{
		ftools.ErrBox("Die Features konnten nicht gespeichert werden. "
			"Die Datenbank meldet: %s", fmysql.features.error_msg);
		Print("## Fehler beim Speichern: %s", fmysql.features.error_msg);
		return;
		}
	Print("Datensatz gespeichert, neue ID = %d", fmysql.features.row.ident);
	}
//---------------------------------------------------------------------------
void TfmChoiFeatures::GetAllFeatures()
	{
	bool bReplace = false;
	if (Application->MessageBox(
		"Es werden Choi-Features für alle in der Datenbank "
		"vorhandenen EKG-Daten gebildet.\r\n"
		"Sollen bestehende Feature-Sets dabei überschrieben werden ?",
		"Choi-Features für alle EKG bilden",
		MB_YESNO) == ID_YES)
		bReplace = true;

	Print("--------------------------------------------------");
	Print("--- Choi-Feature-Sets bilden ---------------------");
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
	Print("Datenbank ecgdata geladen, %d Datensätze", fmysql.ecg.getSize());
	Print("");

	sEcgData data;
	while (fmysql.ecg.nextRow())
		{
		data = fmysql.ecg.row;
		Print("EKG %d (%s)", data.ident, fmysql.people.getNameOf(data.person));

		bool vorhanden = false;
		if (!fmysql.features.select(data.ident, 2))
			{
			Print("\# Fehler in Feature-Select, DB meldet: %s", fmysql.features.error_msg);
			break;
			}

		if (fmysql.features.num_rows > 0)
			{
			Print("\tDatensatz bereits vorhanden...");
			if (!bReplace)
				{
				Print("\t> wird übersprungen");
				continue;
				}
			else
				{
				vorhanden = true;
				Print("\t> wird ersetzt");
				}
			}


		iarray_t array = data.array_werte;
		String features = fChoi.getFeaturesStr2(array);
		if (features == "")
			{
			Print("\t# Fehler beim Erstellen der Features: %s", fChoi.error_msg);
			continue;
			}
		Print("\t- Features berechnet");

		sFeature featdata;
		if (vorhanden)
			{
			fmysql.features.nextRow();
			featdata.ident = fmysql.features.row.ident;
			}

		featdata.ecgId = data.ident;
		featdata.algId = 2; //todo
		featdata.features = features;

		if (vorhanden)
			{
			if (!fmysql.features.update(featdata))
				Print("\t# Fehler beim Ändern: %s", fmysql.features.error_msg);
			else
				Print("\t- Datensatz geändert, ID = %d", fmysql.features.row.ident);
			}
		else
			{
			if (!fmysql.features.insert(featdata))
				Print("\t# Fehler beim Speichern: %s", fmysql.features.error_msg);
			else
				Print("\t- Datensatz gespeichert, neue ID = %d", fmysql.features.row.ident);
			}

		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::CallbackEcgTimer(TObject *Sender)
	{
	CallbackEcg->Enabled = false;
	GetSelectedEcg();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::btFeaturesClick(TObject *Sender)
	{
	GetFeatures();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiFeatures::btBuildAllClick(TObject *Sender)
	{
	GetAllFeatures();
	}
//---------------------------------------------------------------------------

