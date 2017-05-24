//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "VergleichAlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmVergleich *fmVergleich;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgAlgVergleich(TForm* Papa)
	{
	TfmVergleich* Form = new TfmVergleich(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmVergleich::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmVergleich::TfmVergleich(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmVergleich::~TfmVergleich()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmVergleich::FormShow(TObject *Sender)
	{
	ftools.FormLoad(this);
	TfmEcg = CreateEcgForm(this, pnEcg);
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmVergleich::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmVergleich::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	delete TfmEcg;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmVergleich::Print(char* msg, ...)
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
void TfmVergleich::JobStart(int max)
	{
	pbJob->Position = 0;
	pbJob->Max = max;
	pbJob->Visible = true;
	}
//---------------------------------------------------------------------------
void TfmVergleich::JobEnd()
	{
	pbJob->Visible = false;
	}
//---------------------------------------------------------------------------
void TfmVergleich::JobTick(int tick) //tick ist mit 1 vorbesetzt
	{
	pbJob->Position += tick;
	}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TfmVergleich::DoVergleich()
	{
	int t = 0;
	if (cxChoi->Checked)        t++;
	if (cxRandom->Checked)      t++;
	if (cxClassifySvm->Checked) t; //nur der Vollständigkeit halber aufgeführt

	Print("-----------------------------------------------------");

	if (!fmysql.ecg.loadTable())
		{
		Print("Die EKG-Datenbank kann nicht geladen werden");
		return;
		}

	JobStart(t * fmysql.ecg.getSize());

	if (!DoSvm()) return; //Fehlermeldung hat die Funktion schon ausgegeben
	if (!DoXyz()) return; //Fehlermeldung hat die Funktion schon ausgegeben

	Print("-----------------------------------------------------");
	Print("");
	Print("Auswertung Ergebnisse:");
	Print("Klassifizierung \t\t  SVM \t  xyz");
	Print("-----------------------------------------------------");
	if (cxChoi->Checked)
		Print("Feat. Choi \t\t\t%.2f \t%.2f ",  Accuracy[0][0], Accuracy[1][0]);
	if (cxRandom->Checked)
		Print("Feat. Random \t\t\t%.2f \t%.2f", Accuracy[0][1], Accuracy[1][1]);
	JobEnd();
	}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool TfmVergleich::DoSvm()
	{
	double accuracy;
	sChoiSvmData data;
	data.training_von = edTrainingVon->Text.ToIntDef(0);
	data.training_bis = edTrainingBis->Text.ToIntDef(0);
	data.classify_von = edClassifyVon->Text.ToIntDef(0);
	data.classify_bis = edClassifyBis->Text.ToIntDef(0);

	if (cxChoi->Checked)
		{
		//-- Do Svm für Choi-Features
		data.label = "choi";
		data.alg   = fChoiFeat.AlgNr;

		if (!fChoiSvm.SvmAccuracy(accuracy, data))
			{
			Print("## Fehler bei der SVM-Berechnung für die Choi-Features");
			return false;
			}

		Accuracy[0][0] = accuracy;
		}

	if (cxRandom->Checked)
		{
		//-- Do Svm für Random Features
		data.label = "random";
		data.alg   = fRandomFeat.AlgNr;

		if (!fChoiSvm.SvmAccuracy(accuracy, data))
			{
			Print("## Fehler bei der SVM-Berechnung für die Random-Features");
			return false;
			}

		Accuracy[0][1] = accuracy;
		}

	return true;
	}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool TfmVergleich::DoXyz()
	{
	if (cxChoi->Checked)
		{
		//-- Do Svm für Choi-Features
		Accuracy[1][0] = 45.45;
		}

	if (cxRandom->Checked)
		{
		//-- Do Svm für Random Features
		Accuracy[1][1] = 13.45;
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmVergleich::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmVergleich::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmVergleich::cxClassifySvmClick(TObject *Sender)
	{
	pnSvm->Enabled = cxClassifySvm->Checked;

	btVergleich->Enabled = (cxChoi->Checked || cxRandom->Checked) &&
							cxClassifySvm->Checked &&
							edTrainingVon->Text != "" &&
							edTrainingBis->Text != "" &&
							edClassifyVon->Text != "" &&
							edClassifyBis->Text != "";
	}
//---------------------------------------------------------------------------
void __fastcall TfmVergleich::btVergleichClick(TObject *Sender)
	{
    DoVergleich();
	}
//---------------------------------------------------------------------------

