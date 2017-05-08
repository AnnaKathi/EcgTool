//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "AlgChoi2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmChoi2 *fmChoi2;
//---------------------------------------------------------------------------
bool DlgAlgChoi2(TForm* Papa)
	{
	TfmChoi2* Form = new TfmChoi2(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmChoi2::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi2::TfmChoi2(TComponent* Owner)
	: TForm(Owner)
	{
	CountAnna = CountManni = CountManu = CountMartin = 0;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi2::~TfmChoi2()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	ftools.FormLoad(this);
	ftools.ListViewLoad(this, lvData);
	SetValues();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	ftools.ListViewSave(this, lvData);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmChoi2::Print(char* msg, ...)
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
void TfmChoi2::SetValues()
	{
	CountAnna = CountManni = CountManu = CountMartin = 0;

	TListItem* item;
	for (int i = 0; i < lvData->Items->Count; i++)
		{
		item = lvData->Items->Item[i];
		if (item->SubItems->Strings[0] != "") CountAnna++;
		if (item->SubItems->Strings[1] != "") CountManni++;
		if (item->SubItems->Strings[2] != "") CountManu++;
		if (item->SubItems->Strings[3] != "") CountMartin++;
		}
	}
//---------------------------------------------------------------------------
String TfmChoi2::GetFile(String dat)
	{
	char help[MAX_PATH];
	sprintf(help, "%s", dat.c_str());
	char* pt = strrchr(help, '\\');
	if (pt)
		{
		*pt = 0;
		sprintf(help, "%s", pt+1);
		return String(help);
		}
	else
    	return dat;
	}
//---------------------------------------------------------------------------
void TfmChoi2::AddFile(String file, int count, int id)
	{
	if (count > lvData->Items->Count)
		{
		TListItem* item = lvData->Items->Add();
		item->Caption = String(lvData->Items->Count);
		item->Data = (void*)lvData->Items->Count;

		for (int i = 0; i < 4; i++)
			item->SubItems->Add("");
		}

	TListItem* item = lvData->Items->Item[count-1];
	item->SubItems->Strings[id] = file;

	Print("+ %s", GetFile(file));
	}
//---------------------------------------------------------------------------
bool TfmChoi2::CheckEcg()
	{
	//prüfen ob alle Daten eingelsen werden können und ob keine Datei doppelt vorhanden ist
	TStringList* files = new TStringList();

	Print("-----------------------------------------------");
	Print("-- EKGs prüfen --------------------------------");
	Print("-----------------------------------------------");
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

	String file;
	TListItem* item;
	bool fehler = false;
	for (int row = 0; row < lvData->Items->Count; row++)
		{
		item = lvData->Items->Item[row];
		for (int col = 0; col < (lvData->Columns->Count-1); col++)
			{
			file = item->SubItems->Strings[col];
			if (file == "") continue;

			if (files->IndexOf(file) > -1) //file ist bereits enthalten
				{
				fehler = true;
				Print("Eine Datei ist mehrfach enthalten: %s", file);
				break;
				}

			files->Add(file);

			if (!fecg.data.getFile(file, format, delim, 1, 3000))
				{
				fehler = true;
				Print("# Eine Datei kann nicht eingelesen werden: %s", file);
				Print("# ECG meldet: %s", fecg.data.error_msg);
				break;
				}

			Print("- %s", GetFile(file));
			}

		if (fehler) break;
		}

	if (fehler) Print("# Fehler aufgetreten, Vorgang abgebrochen");
	else Print("done sucessfully");
	Print("-----------------------------------------------");
	delete files;
	return !fehler;
	}
//---------------------------------------------------------------------------
void TfmChoi2::DoSvm()
	{
	Print("-----------------------------------------------");
	Print("-- SVM erstellen ------------------------------");
	Print("-----------------------------------------------");
	Print("");
	Print("---- Startup SVM Choi");
	Print("\tlibSVM-Version: %d", fChoiSVM.version);
	if (!fChoiSVM.startSvm())
		{
		Print("# Fehler, SVM konnte nicht gestartet werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return;
		}
	Print("\tokay");

	Print("---- Build Trainingsdata");
	if (!BuildTrainingData()) return;
	Print("\tokay");

	Print("---- Build Problem");
	if (!fChoiSVM.doProblem(fChoiSVM.train_data))
		{
		Print("# Fehler, Trainingdaten konnten nicht gebildet werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return;
		}
	Print("\tokay");

svm_problem problem = fChoiSVM.problem;
int max = problem.l;
int idx; double wert;
for (int i = 0; i < max; i++)
{
//line = ftools.fmt("x -> [%d] -> ", i);
svm_node* node = problem.x[i];
for (int j = 0; j < 8; j++)
{
idx  = node[j].index;
wert = node[j].value;
//line = line + ftools.fmt("(%d,%.4f) ", idx, wert);
}
//Print("%s", line.c_str());
}

fChoiSVM.outProblem("d:\\problem_neu.txt");

	Print("---- Build Parameter");
	if (!fChoiSVM.doParameter(fChoiSVM.problem))
		{
		Print("# Fehler, Parameter konnten nicht gesetzt werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return;
		}
	Print("\tokay");
svm_parameter param = fChoiSVM.param;

	if (cxCrossvalidation->Checked)
		{

		int no = edFold->Text.ToInt();
		Print("---- Crossvalidation");
		if (!fChoiSVM.doCrossvalidation(problem, param, no))
			{
			Print("# Fehler, Crossvalidation konnte nicht durchgeführt werden");
			Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
			return;
			}

		if (param.svm_type == EPSILON_SVR || param.svm_type == NU_SVR)
			{
			Print("\tMean Sqaured Error: %.4f", fChoiSVM.iMeanSquaredError);
			Print("\tSquared Corr. Coeff.: %.4f", fChoiSVM.iSquredCorrCoeff);
			}
		else
			Print("\tCrossvalidation accuracy: %.2f %", fChoiSVM.iAccuracy);
		}
	else
		{
		Print("---- Save Model");
		if (!fChoiSVM.doModel(fChoiSVM.problem, fChoiSVM.param))
			{
			Print("# Fehler, Model konnte nicht gespeichert werden");
			Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
			return;
			}
		Print("\tsaved to d:\\TestAnna.model");
		}
	Print("\tokay");

	Print("\n-- SVM-Train beendet ---------------------------");
	}
//---------------------------------------------------------------------------
bool TfmChoi2::BuildTrainingData()
	{
	if (!fChoiSVM.clearTrainingData())
		{
		Print("# Fehler, Trainingdaten konnten nicht gelöscht werden");
		Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
		return false;
		}

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

	String file;
	TListItem* item;
	for (int row = 0; row < lvData->Items->Count; row++)
		{
		item = lvData->Items->Item[row];
		for (int col = 0; col < (lvData->Columns->Count-1); col++)
			{
			file = item->SubItems->Strings[col];
			if (file == "") continue;

			if (!fecg.data.getFile(file, format, delim, 1, 3000))
				{
				Print("# Eine Datei kann nicht eingelesen werden: %s", file);
				Print("# ECG meldet: %s", fecg.data.error_msg);
				break;
				}

			int label = 56;
			if (!fChoiSVM.addTrainingData(fecg, label))
				{
				Print("# Fehler, Trainingdaten konnten nicht hinzugefügt werden");
				Print("# ChoiSVM meldet: %d, %s", fChoiSVM.error_code, fChoiSVM.error_msg);
				return false;
				}
			}
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Actions   ********************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acResetExecute(TObject *Sender)
	{
	if (Application->MessageBox(
		"Bist Du sicher, dass Du alle Daten zurücksetzen möchtest?",
		"Daten zurücksetzen",
		MB_YESNO) == IDNO) return;

	lvData->Items->Clear();
	SetValues();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddAnnaExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	CountAnna++;
	AddFile(OpenDialog->FileName, CountAnna, 0);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddManniExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	CountManni++;
	AddFile(OpenDialog->FileName, CountManni, 1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddManuExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	CountManu++;
	AddFile(OpenDialog->FileName, CountManu, 2);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddMartinExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	CountMartin++;
	AddFile(OpenDialog->FileName, CountMartin, 3);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acCheckEcgsExecute(TObject *Sender)
	{
	CheckEcg();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acDoEcgsExecute(TObject *Sender)
	{
	DoSvm();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::btAltClick(TObject *Sender)
	{
	Test();
	}
//---------------------------------------------------------------------------
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
void TfmChoi2::Test()
	{
	//--- Trainingdaten bilden
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

	int label = 56;
	iarray_t TrainingsDaten; TrainingsDaten.clear();

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

	bool fehler = false;

	String file;
	TListItem* item;
	int count = 0;
	for (int row = 0; row < lvData->Items->Count; row++)
		{
		item = lvData->Items->Item[row];
		for (int col = 0; col < (lvData->Columns->Count-1); col++)
			{
			file = item->SubItems->Strings[col];
			if (file == "") continue;

			//Datei einlesen
			if (!fecg.data.getFile(file, format, delim, 1, 3000))
				{
				fehler = true;
				Print("# Eine Datei kann nicht eingelesen werden: %s", file);
				Print("# ECG meldet: %s", fecg.data.error_msg);
				break;
				}

			//R-Peak feststellen
			iarray_t ecg = fecg.data.data_array;
			cRpeaks& r   = fecg.rpeaks;
			r.find(ecg, NULL);
			r.reset();

			//R-Peaks durchlaufen und zu den Trainingsdaten hinzufügen
			int prev_zeit, curr_zeit, next_zeit;
			while ((curr_zeit = r.next()) != -1)
				{
				if ((prev_zeit = r.prev_rpeak()) == -1) continue;
				if ((next_zeit = r.next_rpeak()) == -1) continue;

				if (!fChoiFeat.getSingleFeatures(ecg, prev_zeit, curr_zeit, next_zeit))
					{
					fehler = true;
					Print("# Fehler, SingleFeat meldet: %d, %s", fChoiFeat.error_code, fChoiFeat.error_msg);
					break;
					}

				iarray_t features = fChoiFeat.SingleFeatures;
				TrainingsDaten[count].push_back(label);
				TrainingsDaten[count].push_back(features[0][0]);
				TrainingsDaten[count].push_back(features[1][0]);
				TrainingsDaten[count].push_back(features[2][0]);
				TrainingsDaten[count].push_back(features[3][0]);
				TrainingsDaten[count].push_back(features[4][0]);
				TrainingsDaten[count].push_back(features[5][0]);
				TrainingsDaten[count].push_back(features[6][0]);
				TrainingsDaten[count].push_back(features[7][0]);
				count++;
				}
			}
		}

	int sz = TrainingsDaten.size();
	if (fehler) return;

	//--- Problem erstellen
	/* aus den Trainingsdaten ein SVM-Problem forumlieren:
	 *	struct svm_problem
	 *		{
	 *		int l;  //no. of training data (rows)
	 *		double *y;  //array of target values (int in classification)
	 *		struct svm_node **x; //array of pointers to one training vector each
	 *		};
	 *
	 *	For example, if we have the following training data:
	 *
	 *	LABEL    ATTR1    ATTR2    ATTR3    ATTR4    ATTR5
	 *	-----    -----    -----    -----    -----    -----
	 *	  1        0        0.1      0.2      0        0
	 *	  2        0        0.1      0.3     -1.2      0
	 *	  1        0.4      0        0        0        0
	 *	  2        0        0.1      0        1.4      0.5
	 *	  3       -0.1     -0.2      0.1      1.1      0.1
	 *
	 *	then the components of svm_problem are:
	 *
	 *		l = 5 //no of training data (rows)
	 *		y -> 1 2 1 2 3 //array of target values (int in classification)
	 *		x -> [ ] -> (2,0.1) (3,0.2) (-1,?) //array of pointers to one training vector each
	 *			 [ ] -> (2,0.1) (3,0.3) (4,-1.2) (-1,?)
	 *			 [ ] -> (1,0.4) (-1,?)
	 *			 [ ] -> (2,0.1) (4,1.4) (5,0.5) (-1,?)
	 *			 [ ] -> (1,-0.1) (2,-0.2) (3,0.1) (4,1.1) (5,0.1) (-1,?)
	 *
	 *	where (index,value) is stored in the structure `svm_node':
	 *
	 *	struct svm_node
	 *		{
	 *		int index;
	 *		double value;
	 *		};
	 *
	 *  index = -1 indicates the end of one vector. Note that indices must
	 *	be in ASCENDING order.
	 */


	//Speicherplatz allokieren
	svm_problem	fProblem;
	fProblem.l = TrainingsDaten.size();
	fProblem.y = Malloc(double, fProblem.l);
	fProblem.x = Malloc(struct svm_node*, fProblem.l);

	svm_node* 	x_space;
	int elements = fProblem.l * 8; //8 features pro Herzschlag
	x_space = Malloc(struct svm_node, elements);

	int i = 0;
	int j = 0;
	for (iarray_itr itr = TrainingsDaten.begin(); itr != TrainingsDaten.end(); itr++)
		{
		ilist_t& v = itr->second;

		fProblem.y[i] = v[0]; //Label
		fProblem.x[i] = &x_space[j];

		x_space[j].index =  1; 	x_space[j].value = v[1]; 	j++;
		x_space[j].index =  2; 	x_space[j].value = v[2]; 	j++;
		x_space[j].index =  3; 	x_space[j].value = v[3]; 	j++;
		x_space[j].index =  4; 	x_space[j].value = v[4]; 	j++;
		x_space[j].index =  5; 	x_space[j].value = v[5]; 	j++;
		x_space[j].index =  6; 	x_space[j].value = v[6]; 	j++;
		x_space[j].index =  7; 	x_space[j].value = v[7]; 	j++;
		x_space[j].index =  8; 	x_space[j].value = v[8]; 	j++;
		x_space[j].index = -1;  x_space[j].value = 0.00; 	j++; //end of vector

		i++;
		}

	outProblem(fProblem, "D:\\Problem_080517.txt");

	//--- Parameter setzen
	/* struct svm_parameter describes the parameters of an SVM model:
	 *
	 *	struct svm_parameter
	 *		{
	 *		int svm_type;
	 *		int kernel_type;
	 *		int degree;	   // for poly
	 *		double gamma;  // for poly/rbf/sigmoid
	 *		double coef0;  // for poly/sigmoid
	 *
	 *		// these are for training only
	 *		double cache_size;  // in MB
	 *		double eps;			// stopping criteria
	 *		double C;			// for C_SVC, EPSILON_SVR, and NU_SVR
	 *		int nr_weight;		// for C_SVC
	 *		int *weight_label;	// for C_SVC
	 *		double* weight;		// for C_SVC
	 *		double nu;			// for NU_SVC, ONE_CLASS, and NU_SVR
	 *		double p;			// for EPSILON_SVR
	 *		int shrinking;		// use the shrinking heuristics
	 *		int probability; 	// do probability estimates
	 *		};
	 *
	 * Die gesetzten Eigenschaften wurden aus svm-train.c übernommen, die aus-
	 * drücklich zur Nachahmung empfohlen wurde.
	 */
	svm_parameter	fParam;

	fParam.svm_type 	= C_SVC;
	fParam.kernel_type  = RBF;
	fParam.degree 		= 3;
	fParam.gamma 		= 0;
	fParam.coef0 		= 0;

	fParam.cache_size 	= 500; //default ist 100
	fParam.eps 		    = 1e-3;
	fParam.C 		    = 1;
	fParam.nr_weight    = 0;
	fParam.weight_label = NULL;
	fParam.weight 	    = NULL;
	fParam.nu 		    = 0.5;
	fParam.p 		    = 0.1;
	fParam.shrinking    = 1;
	fParam.probability  = 0;

	//--- Crossvalidation
	int fold = 2;

	int total_correct = 0;
	double total_error = 0;
	double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;
	double *target = Malloc(double, fProblem.l);

	svm_cross_validation(&fProblem, &fParam, fold, target);
	for(int i = 0; i < fProblem.l; i++) //SVM-Type !=  EPSILON_SVR || NU_SVR
		{
		if(target[i] == fProblem.y[i])
			++total_correct;
		}
	double Accuracy = 100.0 * total_correct / fProblem.l;
	free(target);

	Application->MessageBox(ftools.fmt("Result Crossvalidation: %.2f Accuracy", Accuracy).c_str(), "Crossvalidation", MB_OK);
	}
//---------------------------------------------------------------------------
bool TfmChoi2::outProblem(svm_problem& problem, String file)
	{
	//das problem in die übergebene Datei schreiben
	if (file == "") return false;
	FILE* fp = fopen(file.c_str(), "w");
	if (fp == NULL) return false;

	int max = problem.l;
	fprintf(fp, "l = %d\n\n", max);

	String line = "";
	int label;
	for (int i = 0; i < max; i++)
		{
		label = problem.y[i];
		fprintf(fp, "\t%d\n", label);
		//line = line + String(label) + " ";
		}
	//fprintf(fp, "y -> %s\n\n", line.c_str());
	fprintf(fp, "\n");

	int idx; double wert;
	for (int i = 0; i < max; i++)
		{
		line = ftools.fmt("x -> [%d] -> ", i);
		svm_node* node = problem.x[i];
		for (int j = 0; j < 9; j++)
			{
			idx  = node[j].index;
			wert = node[j].value;
			//line = line + ftools.fmt("(%d,%.4f) ", idx, wert);
			fprintf(fp, "(%d,%.4f) ", idx, wert);
			}
		fprintf(fp, "\n");
		//fprintf(fp, "%s\n", line.c_str());
		}

	fclose(fp);
	return true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::btExeFilesClick(TObject *Sender)
	{
	//EXE-Dateien mit a1a-Daten aufrufen

	String path = ftools.GetPath();

	String svm_train   = path + "\\libSVM\\svm-train.exe";
	String svm_predict = path + "\\libSVM\\svm-predict.exe";
	String a1a_train   = path + "\\libSVM\\a1a.train";
	String a1a_test    = path + "\\libSVM\\a1a.test";

	String a1a_model   = path + "\\libSVM\\a1a.train.model";
	String a1a_out     = path + "\\libSVM\\a1a.out";

	if (!FileExists(svm_train) || !FileExists(svm_predict) ||
		!FileExists(a1a_train) || !FileExists(a1a_test))
		{
		; //todo Fehlermeldung
		return;
		}

	//svm-train.exe a1a.train
	ShellExecute(
		this,    			//hwnd
		"open",     		//Operation
		svm_train.c_str(),	//File
		a1a_train.c_str(),	//Parameters
		path.c_str(),		//Directory
		SW_SHOW);   		//Show-Command



	}
//---------------------------------------------------------------------------

