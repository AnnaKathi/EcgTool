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
	if (cxChoi->Checked)
		{
		//-- Do Svm für Choi-Features
		if (!SvmAccuracy(accuracy, "choi", fChoiFeat.AlgNr))
			{
			Print("## Fehler bei der SVM-Berechnung für die Choi-Features");
			return false;
			}

		double test;
		sChoiSvmData data;
		data.label = "choi";
		data.alg   = fChoiFeat.AlgNr;
		data.training_von = edTrainingVon->Text.ToIntDef(0);
		data.training_bis = edTrainingBis->Text.ToIntDef(0);
		data.classify_von = edClassifyVon->Text.ToIntDef(0);
		data.classify_bis = edClassifyBis->Text.ToIntDef(0);

		if (!fChoiSvm.SvmAccuracy(test, data))
			{
			Print("## Fehler bei der KLASSEN-SVM-Berechnung für die Choi-Features");
			return false;
			}

		int bp = 0;
		Accuracy[0][0] = accuracy;
		}

	if (cxRandom->Checked)
		{
		//-- Do Svm für Random Features
		if (!SvmAccuracy(accuracy, "random", fRandomFeat.AlgNr))
			{
			Print("## Fehler bei der SVM-Berechnung für die Random-Features");
			return false;
			}

		Accuracy[0][1] = accuracy;
		}

	return true;
	}
//---------------------------------------------------------------------------
bool TfmVergleich::SvmAccuracy(double& accuracy, String label, int alg)
	{
	int training_von = edTrainingVon->Text.ToIntDef(0); if (training_von <= 0) return false;
	int training_bis = edTrainingBis->Text.ToIntDef(0); if (training_bis <= 0) return false;
	int classify_von = edClassifyVon->Text.ToIntDef(0); if (classify_von <= 0) return false;
	int classify_bis = edClassifyBis->Text.ToIntDef(0); if (classify_bis <= 0) return false;

	//todo: Sicherheitsprüfung Bereiche

	//-- Used files
	String path = ftools.GetPath();
	String svm_train   = path + "\\libSVM\\svm-train.exe";
	String svm_predict = path + "\\libSVM\\svm-predict.exe";
	if (!FileExists(svm_train))
		{
		Print("# Die Train-Datei existiert nicht <%s>", svm_train);
		return false;
		}

	if (!FileExists(svm_predict))
		{
		Print("# Die Predict-Datei existiert nicht <%s>", svm_predict);
		return false;
		}

	String trainfile = ftools.fmt("%s\\libSVM\\%s.train",       path, label);
	String testfile  = ftools.fmt("%s\\libSVM\\%s.test",        path, label);
	String modelfile = ftools.fmt("%s\\libSVM\\%s.train.model", path, label);
	String outfile   = ftools.fmt("%s\\libSVM\\%s.out",         path, label);

	//-- Create Train + Test
	if (!SvmWriteFile(true, trainfile, alg, training_von, training_bis))
		{
		Print("## Train <%s>: Fehler aufgetreten", label);
		return false;
		}

	if (!SvmWriteFile(false, testfile, alg, classify_von, classify_bis))
		{
		Print("## Test <%s>: Fehler aufgetreten", label);
		return false;
		}

	//-- Exe-Files aufrufen
	 if (!FileExists(trainfile))
		{
		Print("# Die Trainings-Daten existieren nicht <%s>", trainfile);
		return false;
		}

	//svm-train.exe a1a.train
	ShellExecute(
		this,    			//hwnd
		"open",     		//Operation
		svm_train.c_str(),	//File
		trainfile.c_str(),	//Parameters
		path.c_str(),		//Directory
		SW_SHOW);   		//Show-Command

	if (!FileExists(modelfile))
		{
		Print("# Das Modell konnte nicht erstellt werden <%s>", modelfile);
		return false;
		}

	if (!FileExists(testfile))
		{
		Print("# Die Testdatei existiert nicht<%s>", testfile);
		return false;
		}

	//svm-predict.exe a1a.test a1a.train.model a1a.out
	String params = ftools.fmt("%s %s %s", testfile, modelfile, outfile);
	ShellExecute(
		this,    			//hwnd
		"open",     		//Operation
		svm_predict.c_str(),	//File
		params.c_str(),	//Parameters
		path.c_str(),		//Directory
		SW_SHOW);   		//Show-Command


	if (!FileExists(outfile))
		{
		Print("# Die Ausgabedatei konnte nicht erstellt werden <%s>", outfile);
		return false;
		}

	//-- Ergebnisse vergleichen
	if (!SvmCompareResult(accuracy, testfile, outfile))
		return false;
	else
		return true;
	}
//---------------------------------------------------------------------------
bool TfmVergleich::SvmWriteFile(bool bWriteTraining, String filename, int alg, int ecgvon, int ecgbis)
	{
	iarray_t array; array.clear();

	if (filename == "") return false;
	FILE* fp = fopen(filename.c_str(), "w");
	if (fp == NULL)
		return false;

	if (ecgvon <= 0 || ecgbis <= 0) return false;
	if (ecgvon > ecgbis) return false;

	int count = 0;
	int count_featmissing = 0;
	int count_datamissing = 0;
	for (int i = ecgvon; i <= ecgbis; i++)
		{
		//Features laden
		if (!fmysql.features.select(i, alg))
			{
			//keine Features für dieses EKG vorhanden
			count_featmissing++;
			continue;
			}

		//ECG reinladen
		if (!fmysql.ecg.loadByIdent(i))
			{
			//Original-EKG-Daten fehlen
			count_datamissing++;
			continue;
			}

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
bool TfmVergleich::SvmCompareResult(double& accuracy, String testfile, String outfile)
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

	accuracy = (double)right / (double)count * 100;
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

