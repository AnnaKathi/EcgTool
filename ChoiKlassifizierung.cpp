//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "ChoiKlassifizierung.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmChoiClassification *fmChoiClassification;
extern cMySql fmysql;
//---------------------------------------------------------------------------
bool DlgChoiClassification(TForm* Papa)
	{
	TfmChoiClassification* Form = new TfmChoiClassification(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmChoiClassification::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoiClassification::TfmChoiClassification(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmChoiClassification::~TfmChoiClassification()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiClassification::FormShow(TObject *Sender)
	{
	ftools.FormLoad(this);
	TfmEcg = CreateEcgForm(this, pnEcg);
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiClassification::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiClassification::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	ftools.FormSave(this);
	delete TfmEcg;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmChoiClassification::Print(char* msg, ...)
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
bool TfmChoiClassification::WriteFile(bool bWriteTraining, String filename)
	{
	iarray_t array; array.clear();

	if (filename == "") return false;
	FILE* fp = fopen(filename.c_str(), "w");
	if (fp == NULL)
		return false;

	int ecgVon, ecgBis;
	if (bWriteTraining)
		{
		ecgVon = edTrainingVon->Text.ToIntDef(0);
		ecgBis = edTrainingBis->Text.ToIntDef(0);
		}
	else
		{
		ecgVon = edClassifyVon->Text.ToIntDef(0);
		ecgBis = edClassifyBis->Text.ToIntDef(0);
		}

	if (ecgVon <= 0 || ecgBis <= 0) return false;
	if (ecgVon > ecgBis) return false;

	int count = 0;
	for (int i = ecgVon; i <= ecgBis; i++)
		{
		//ECG reinladen
		if (!fmysql.ecg.loadByIdent(i)) continue;

		//Features laden
		if (!fmysql.features.select(i, 2)) continue;

		//Features in Array schreiben
		iarray_t feat = ftools.TextToArray(fmysql.features.row.features, ";");

		//Features zum Gesamt-Array hinzufügen
		array[count].push_back(fmysql.ecg.row.person);  //label = Person
		array[count].push_back(feat[0][1]);
		array[count].push_back(feat[1][1]);
		array[count].push_back(feat[2][1]);
		array[count].push_back(feat[3][1]);
		array[count].push_back(feat[4][1]);
		array[count].push_back(feat[5][1]);
		array[count].push_back(feat[6][1]);
		array[count].push_back(feat[7][1]);
		count++;
		}

	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		//<label> <index1>:<value1> <index2>:<value2> ...
		ilist_t& v = itr->second;
		fprintf(fp, "%d 1:%d 2:%d 3:%d 4:%.8f 5:%.8f 6:%.8f 7:%.8f 8:%.8f\n",
			(int)v[0], (int)v[1], (int)v[2], (int)v[3],
			v[4], v[5], v[6], v[7], v[8]);
		}

	fclose(fp);
	return true;
	}
//---------------------------------------------------------------------------
bool TfmChoiClassification::CompareResult(String testfile, String outfile)
	{
	FILE* fptest = fopen(testfile.c_str(), "r");
	if (fptest == NULL)
		{
		Print("# Fehler, Die Testfile konnte nicht geöffnet werden <%s>", testfile);
		return false;
		}

	FILE* fpout = fopen(outfile.c_str(), "r");
	if (fpout == NULL)
		{
		Print("# Fehler, Die Ausgabefile konnte nicht geöffnet werden <%s>", outfile);
		fclose(fptest);
		return false;
		}

	char rowbuf1[1024];  char rowbuf2[1024];
	int testlabel;		 int outlabel;
	bool fehler = false;

	int right = 0;
	int wrong = 0;
	int count = 0;
	while ((fgets(rowbuf1, sizeof(rowbuf1)-1, fptest)) != NULL)
		{
		char* pt = strchr(rowbuf1, ' ');
		if (pt == NULL)
			{
			fehler = true;
			break;
			}
		*pt = 0;
		testlabel = atoi(rowbuf1);

		if (fgets(rowbuf2, sizeof(rowbuf2)-1, fpout) == NULL)
			{
			fehler = true;
			break;
			}

		pt = strchr(rowbuf2, ' ');
		outlabel = atoi(rowbuf2);

		if (testlabel == outlabel)
			right++;
		else
			wrong++;

		count++;
		}

	fclose(fptest);
	fclose(fpout);

	if (fehler)
		{
		Print("# Fehler aufgetreten");
		return false;
		}

	double classification = (double)right / (double)count * 100;
	Print("Accuracy: %.2f", classification);
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoiClassification::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoiClassification::acClassifyExecute(TObject *Sender)
	{
	int training_von = edTrainingVon->Text.ToIntDef(0); if (training_von <= 0) return;
	int training_bis = edTrainingBis->Text.ToIntDef(0); if (training_bis <= 0) return;
	int classify_von = edClassifyVon->Text.ToIntDef(0); if (classify_von <= 0) return;
	int classify_bis = edClassifyBis->Text.ToIntDef(0); if (classify_bis <= 0) return;

	//todo: Sicherheitsprüfung Bereiche

	//-- Create Train + Test
	String path = ftools.GetPath();
	String trainfile = path + "\\libSVM\\choi.train";
	String testfile  = path + "\\libSVM\\choi.test";

	if (!WriteFile(true, trainfile))
		{
		Print("## Train: Fehler aufgetreten");
		return;
		}

	if (!WriteFile(false, testfile))
		{
		Print("## Test: Fehler aufgetreten");
		return;
		}

	Print("Trainings- und Testdateien erstellt");

	//-- Exe-Files aufrufen
	String svm_train  = path + "\\libSVM\\svm-train.exe";
	String choi_train = path + "\\libSVM\\choi.train";
	String choi_model = path + "\\libSVM\\choi.train.model";

	if (!FileExists(svm_train))
		{
		Print("# Die Train-Datei existiert nicht <%s>", svm_train);
		return;
		}

	 if (!FileExists(choi_train))
		{
		Print("# Die Trainings-Daten existieren nicht <%s>", choi_train);
		return;
		}

	//svm-train.exe a1a.train
	ShellExecute(
		this,    			//hwnd
		"open",     		//Operation
		svm_train.c_str(),	//File
		choi_train.c_str(),	//Parameters
		path.c_str(),		//Directory
		SW_SHOW);   		//Show-Command

	if (!FileExists(choi_model))
		{
		Print("# Das Modell konnte nicht erstellt werden <%s>", choi_model);
		return;
		}

	String svm_predict = path + "\\libSVM\\svm-predict.exe";
	String choi_test   = path + "\\libSVM\\choi.test";
	String choi_out    = path + "\\libSVM\\choi.out";

	if (!FileExists(svm_predict))
		{
		Print("# Die Predict-Datei existiert nicht <%s>", svm_predict);
		return;
		}

	if (!FileExists(choi_test))
		{
		Print("# Die Testdatei existiert nicht<%s>", choi_test);
		return;
		}

	//svm-predict.exe a1a.test a1a.train.model a1a.out
	String params = ftools.fmt("%s %s %s", choi_test, choi_model, choi_out);
	ShellExecute(
		this,    			//hwnd
		"open",     		//Operation
		svm_predict.c_str(),	//File
		params.c_str(),	//Parameters
		path.c_str(),		//Directory
		SW_SHOW);   		//Show-Command


	if (!FileExists(choi_out))
		{
		Print("# Die Ausgabedatei konnte nicht erstellt werden <%s>", choi_out);
		return;
		}

	Print("Dateien erfolgreich erstellt");

	//-- Ergebnisse vergleichen
	String outfile  = path + "\\libSVM\\choi.out";
	CompareResult(testfile, outfile);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoiClassification::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

