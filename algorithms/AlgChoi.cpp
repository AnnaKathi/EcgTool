//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "../inc/libsvm/svm.h"

#include "AlgChoi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "inc/libsvm/libsvm.lib"
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
	DoChoi();
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
	DoChoi();
	}
//---------------------------------------------------------------------------
void TfmChoi::DoChoi()
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

	Print("...features done");
	}
//---------------------------------------------------------------------------
void TfmChoi::DoSvm()
	{
	Print("libSVM-Version: %d", libsvm_version);

	//--> see readme, 'library usage' ------------------------------
	//see svm-train.c and svm-predict.c on how to use the library

	/*--> 1. get/construct training data */
	iarray_t train_data = getTrainingData(fecg.data.data_array);
	
	/*--> 2. construct SVM model (svm_model) using training data
			a model can also be saved in a file for later use.*/

			/*--> 2a. construct a problem */
			/*
			struct svm_problem describes the problem:
			struct svm_problem
				{
				int l;  //no. of training data (rows)
				double *y;  //array of target values (int in classification)
				struct svm_node **x; //array of pointers to one training vector each
				};

			where `l' is the number of training data, and `y' is an array containing
			their target values. (integers in classification, real numbers in
			regression) `x' is an array of pointers, each of which points to a sparse
			representation (array of svm_node) of one training vector.

			For example, if we have the following training data:

			LABEL    ATTR1    ATTR2    ATTR3    ATTR4    ATTR5
			-----    -----    -----    -----    -----    -----
			  1        0        0.1      0.2      0        0
			  2        0        0.1      0.3     -1.2      0
			  1        0.4      0        0        0        0
			  2        0        0.1      0        1.4      0.5
			  3       -0.1     -0.2      0.1      1.1      0.1

			then the components of svm_problem are:

				l = 5 //no of training data (rows)
				y -> 1 2 1 2 3 //array of target values (int in classification)
				x -> [ ] -> (2,0.1) (3,0.2) (-1,?) //array of pointers to one training vector each
					 [ ] -> (2,0.1) (3,0.3) (4,-1.2) (-1,?)
					 [ ] -> (1,0.4) (-1,?)
					 [ ] -> (2,0.1) (4,1.4) (5,0.5) (-1,?)
					 [ ] -> (1,-0.1) (2,-0.2) (3,0.1) (4,1.1) (5,0.1) (-1,?)

			where (index,value) is stored in the structure `svm_node':

			struct svm_node
			{
				int index;
				double value;
			};

			index = -1 indicates the end of one vector. Note that indices must
			be in ASCENDING order.
            */
			/*--> 2b. construct svm parameters */

	/*--> 3. use model to classify new data */
	}
//---------------------------------------------------------------------------
iarray_t TfmChoi::getTrainingData(iarray_t ecg)
	{
	/* aus dem ECG-Stream ein Array der folgenden Form erstellen:
	 *    LABEL    ATTR1    ATTR2    ATTR3    ATTR4    ATTR5
	 *    -----    -----    -----    -----    -----    -----
	 *      1        0        0.1      0.2      0        0
	 *      2        0        0.1      0.3     -1.2      0
	 *      1        0.4      0        0        0        0
	 *      2        0        0.1      0        1.4      0.5
	 *      3       -0.1     -0.2      0.1      1.1      0.1
	 *
	 * dabei wird für jeweils einen Herzschlag im EKG-Strom eine Zeile im
	 * Trainingsarray erzeugt mit den fiducial points nach Choi
	 */

	iarray_t training; training.clear();

	cRpeaks& r = fecg.rpeaks;
	r.find(ecg, NULL);
	r.reset();

	int prev_zeit, curr_zeit, next_zeit;
	while ((curr_zeit = r.next()) != -1)
		{
		if ((prev_zeit = r.prev_rpeak()) == -1) continue;
		if ((next_zeit = r.next_rpeak()) == -1) continue;

		if (!fChoiFeat.getSingleFeatures(ecg, prev_zeit, curr_zeit, next_zeit))
			{
			//todo Print...
			continue; //oder break???
			}

		iarray_t features = fChoiFeat.SingleFeatures;
		Print("\t------------------------------");
		Print("\t%d / %d / %d", (int)features[0][0], (int)features[1][0], (int)features[2][0]);
		Print("\t%.4f / %.4f", features[3][0], features[4][0]);
		Print("\t%.4f / %.4f", features[5][0], features[6][0]);
		Print("\t%.4f", features[7][0]);
		}

	return training;
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

