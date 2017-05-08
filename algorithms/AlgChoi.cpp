//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "AlgChoi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmChoi *fmChoi;
//---------------------------------------------------------------------------
bool DlgAlgChoi(TForm* Papa)
	{
	TfmChoi* Form = new TfmChoi(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmChoi::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi::TfmChoi(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi::~TfmChoi()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::FormClose(TObject *Sender, TCloseAction &Action)
	{
    ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String TfmChoi::fmt(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	va_end(argptr);
	return (String)buffer;
	}
//---------------------------------------------------------------------------
void TfmChoi::Print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	Memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
void TfmChoi::Line(TImage* img, int x, TColor cl)
	{
	//diese X-Pos in der angegebenen Farbe anmalen ohne dass die Kurve übermalt wird
	for (int y = 0; y < img->Height; y++)
		{
		if (img->Canvas->Pixels[x][y] == clBlack)
			continue;
		else
			img->Canvas->Pixels[x][y] = cl;
		}
	}
//---------------------------------------------------------------------------
void TfmChoi::Color(TImage* img, TColor cl, int von, int bis, int max)
	{
	//wird aufgerufen mit einem Zeitbereich -> umrechnen auf x-Positionen
	double faktor = (double)img->Width / (double)max;
	int x_von = (double)von * (double)faktor;
	int x_bis = (double)bis * (double)faktor;

	for (int x = x_von; x <= x_bis; x++)
		Line(img, x, cl);
	}
//---------------------------------------------------------------------------
void TfmChoi::ShowEcg()
	{
	farray.clearImg(imgEcg);
	
	Print("----------------------------------------------");
	Print("...read ecg-file...");
	String ecgFile = edInputfile->Text;
	if (ecgFile == "") return;

	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	eDatFormat format;
	if (cbFormat->ItemIndex == 1)
		format = formatADS;
	else
		format = formatNone;

	//-- EKG-Daten
	if (!fecg.data.getFile(ecgFile, format, delim, 1, 3000))
		{
		Print("\t## Fehler aufgetreten: %d, %s", fecg.data.error_code, fecg.data.error_msg);
		return;
		}

	fecg.data.redisplay(imgEcg);
	Print("...ecg-file ready");
	}
//---------------------------------------------------------------------------
void TfmChoi::GetRpeaksAnna()
	{
	//todo: ersetzen durch Klassenaufruf Choi

	Print("----------------------------------------------");
	Print("...get r-peaks Anna");
	if (fecg.data.data_array.size() <= 0)
		{
		Print("\t## Es wurde keine Datei eingelesen");
		return;
		}

	cRpeaks& r = fecg.rpeaks;
	iarray_t rpeaks = r.find(fecg.data.data_array, NULL);
	if (rpeaks.size() <= 0)
		{
		Print("\t## Fehler set R-Peaks: %d, %s", r.error_code, r.error_msg);
		return;
		}

	farray.PointWidth = 5;
	farray.PointColor = clRed;
	farray.displayPoints(fecg.data.data_array, rpeaks, imgEcg);

	Print("\tR-Peaks done");

	fChoiFeat.Rpeaks = rpeaks;
	DoFeat();
	}
//---------------------------------------------------------------------------
void TfmChoi::GetRpeaksChoi()
	{
	Print("----------------------------------------------");
	Print("...get r-peaks Choi");
	if (fecg.data.data_array.size() <= 0)
		{
		Print("\t## Es wurde keine Datei eingelesen");
		return;
		}

	fChoiFeat.Threshold = edThreshold->Text.ToDouble();
	fChoiFeat.Overlap   = edOverlap->Text.ToInt();

	if (!fChoiFeat.FindRPeaks(fecg.data.data_array))
		{
		Print("\t## Fehler aufgetreten: %d - %s", fChoiFeat.error_code, fChoiFeat.error_msg);
		return;
		}

	iarray_t rloc = fChoiFeat.Rpeaks;

	farray.PointWidth = 5;
	farray.PointColor = clRed;
	farray.displayPoints(fecg.data.data_array, rloc, imgEcg);

	Print("\t...R-Peaks done");
	DoFeat();
	}
//---------------------------------------------------------------------------
void TfmChoi::DoFeat()
	{
	Print("...get features Choi");
	if (!fChoiFeat.FindFeatures(fecg.data.data_array))
		{
		Print("\t## Fehler aufgetreten: %d - %s", fChoiFeat.error_code, fChoiFeat.error_msg);
		return;
		}

	iarray_t features = fChoiFeat.Features;

	mFid->Lines->Add(fmt("%d / %d / %d", (int)features[0][0], (int)features[1][0], (int)features[2][0]));
	mFid->Lines->Add("");
	mFid->Lines->Add(fmt("%.5f - %.5f", features[3][0], features[4][0]));
	mFid->Lines->Add(fmt("%.5f", features[5][0]));
	mFid->Lines->Add(fmt("%.5f - %.5f", features[6][0], features[7][0]));

	String s = "";
	for (int i = 0; i < 8; i++)
		{
		if (i == 0)
			s = String(features[i][0]);
		else
			s += ";" + String(features[i][0]);
		}
	Print("");
	Print("%s", s);
	Print("");

	Print("...features done");
	}
//---------------------------------------------------------------------------
void TfmChoi::DoSvm()
	{
	Print("\n------- Startup SVM Choi -----------------------------------");
	Print("libSVM-Version: %d", fChoiSVM.version);
	if (!fChoiSVM.startSvm(fecg))
		{
		Print("# Fehler, SVM konnte nicht gestartet werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return;
		}

	Print("\n------- Trainingsdata --------------------------------------");
	if (!fChoiSVM.doTrainingData(56))
		{
		Print("# Fehler, Trainingdaten konnten nicht gebildet werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return;
		}

	iarray_t train_data = fChoiSVM.train_data;
	for (iarray_itr itr = train_data.begin(); itr != train_data.end(); itr++)
		{
		ilist_t& v = itr->second;
		Print("%d: %d / %d / %d / %.4f / %.4f / %.4f / %.4f / %.4f",
			(int)v[0], (int)v[1], (int)v[2], (int)v[3], v[4], v[5], v[6], v[7], v[8]);
		}

	Print("\n------- Problem --------------------------------------------");
	if (!fChoiSVM.doProblem(train_data))
		{
		Print("# Fehler, Trainingdaten konnten nicht gebildet werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return;
		}

	svm_problem problem = fChoiSVM.problem;

	int max = problem.l;
	Print("l = %d", max);

	String line = "";
	int label;
	for (int i = 0; i < max; i++)
		{
		label = problem.y[i];
		line = line + String(label) + " ";
		}
	Print("y -> %s", line.c_str());

	int idx; double wert;
	for (int i = 0; i < max; i++)
		{
		line = ftools.fmt("x -> [%d] -> ", i);
		svm_node* node = problem.x[i];
		for (int j = 0; j < 8; j++)
			{
			idx  = node[j].index;
			wert = node[j].value;
			line = line + ftools.fmt("(%d,%.4f) ", idx, wert);
			}
		Print("%s", line.c_str());
		}

fChoiSVM.outProblem("d:\\problem_alt.txt");

	Print("\n------- Parameter ------------------------------------------");
	if (!fChoiSVM.doParameter(problem))
		{
		Print("# Fehler, Parameter konnten nicht gesetzt werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return;
		}

	svm_parameter param = fChoiSVM.param;
	Print("okay");

	if (cxCrossvalidation->Checked)
		{
		Print("\n------- Crossvalidation ------------------------------------");
		if (!fChoiSVM.doCrossvalidation(problem, param, edFold->Text.ToInt()))
			{
			Print("# Fehler, Crossvalidation konnte nicht durchgeführt werden");
			Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
			return;
			}

		if (param.svm_type == EPSILON_SVR || param.svm_type == NU_SVR)
			{
			Print("Mean Sqaured Error: %.4f", fChoiSVM.iMeanSquaredError);
			Print("Squared Corr. Coeff.: %.4f", fChoiSVM.iSquredCorrCoeff);
			}
		else
			Print("Crossvalidation accuracy: %.2f %", fChoiSVM.iAccuracy);
		}
	else
		{
		Print("\n------- Save Model -----------------------------------------");
		if (!fChoiSVM.doModel(problem, param))
			{
			Print("# Fehler, Model konnte nicht gespeichert werden");
			Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
			return;
			}
		Print("okay");
		}

	Print("\n------- SVM-Train beendet ----------------------------------");
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::btInputfileClick(TObject *Sender)
	{
	if (OpenDialog->Execute())
		{
		edInputfile->Text = OpenDialog->FileName;
		farray.clearImg(imgEcg);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::btReadClick(TObject *Sender)
	{
	ShowEcg();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button4Click(TObject *Sender)
	{
	farray.redisplay(fecg.data.data_array, imgEcg);
	GetRpeaksAnna();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button2Click(TObject *Sender)
	{
	farray.redisplay(fecg.data.data_array, imgEcg);
	GetRpeaksChoi();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button3Click(TObject *Sender)
	{
	farray.redisplay(fecg.data.data_array, imgEcg);

	fChoiFeat.Threshold = edThreshold->Text.ToDouble();
	fChoiFeat.Overlap   = edOverlap->Text.ToInt();
	iarray_t features = fChoiFeat.getFeatures(fecg.data.data_array);

	Print("");
	Print("FEATURES");
	Print("---------------");
	double feat;
	for (iarray_itr itr = features.begin(); itr != features.end(); itr++)
		{
		ilist_t& v = itr->second;
		feat = v[0];

		Print("\t%.6f", feat);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::btTestSVMClick(TObject *Sender)
	{
	DoSvm();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button5Click(TObject *Sender)
	{
    //
	}
//---------------------------------------------------------------------------

