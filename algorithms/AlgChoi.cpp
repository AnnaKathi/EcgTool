//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

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

	svm_destroy_param(&param);
	free(problem.y);
	free(problem.x);
	free(x_space);
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
	int label = edLabel->Text.ToInt();
	if (label <= 0)
    	return training; //todo Fehlermeldung usw

	cRpeaks& r = fecg.rpeaks;
	r.find(ecg, NULL);
	r.reset();

	int prev_zeit, curr_zeit, next_zeit;
	int count = 0;
	while ((curr_zeit = r.next()) != -1)
		{
		if ((prev_zeit = r.prev_rpeak()) == -1) continue;
		if ((next_zeit = r.next_rpeak()) == -1) continue;

		if (!fChoiFeat.getSingleFeatures(ecg, prev_zeit, curr_zeit, next_zeit))
			{
			Print("## Fehler, SingleFeat meldet: %d, %s", fChoiFeat.error_code, fChoiFeat.error_msg);
			break;
			}

		iarray_t features = fChoiFeat.SingleFeatures;
		Print("\t------------------------------");
		Print("\t%d / %d / %d", (int)features[0][0], (int)features[1][0], (int)features[2][0]);
		Print("\t%.4f / %.4f", features[3][0], features[4][0]);
		Print("\t%.4f / %.4f", features[5][0], features[6][0]);
		Print("\t%.4f", features[7][0]);

		training[count].push_back(label);
		training[count].push_back(features[0][0]);
		training[count].push_back(features[1][0]);
		training[count].push_back(features[2][0]);
		training[count].push_back(features[3][0]);
		training[count].push_back(features[4][0]);
		training[count].push_back(features[5][0]);
		training[count].push_back(features[6][0]);
		training[count].push_back(features[7][0]);
		count++;
		}

	return training;
	}
//---------------------------------------------------------------------------
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
bool TfmChoi::getProblem(iarray_t training, svm_problem& problem)
	{
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

	if (training.size() <= 0)
		{
		Print("# Fehler, es wurden keine Trainingdaten übergeben");
		return false;
		}

	//Speicherplatz allokieren
	problem.l = training.size();
	problem.y = Malloc(double, problem.l);
	problem.x = Malloc(struct svm_node*, problem.l);

	int elements = problem.l * 8; //8 features pro Herzschlag
	x_space = Malloc(struct svm_node, elements);

	int i = 0;
	int j = 0;
	for (iarray_itr itr = training.begin(); itr != training.end(); itr++)
		{
		ilist_t& v = itr->second;

		problem.y[i] = v[0]; //Label
		problem.x[i] = &x_space[j];

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

	return true;
	}
//---------------------------------------------------------------------------
bool TfmChoi::getParameter(svm_problem problem, svm_parameter& param)
	{
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
	if (problem.l <= 0)
		{
		//todo Fehlermeldung
		return false;
		}

	//nein: setParameterDefault(param);

	//setzen von außen ermöglichen, ersetzt den Aufruf der exe mit Optionen
	//aus Ini-Datei lesen
	TIniFile* ini = new TIniFile(ftools.GetIniFile());

	param.svm_type 		= ini->ReadInteger("SVM-Parameter", "SVM-Type", C_SVC);
	param.kernel_type 	= ini->ReadInteger("SVM-Parameter", "Kernel-Type", RBF);
	param.degree 		= ini->ReadInteger("SVM-Parameter", "Degree", 3);
	param.gamma 		= ini->ReadFloat("SVM-Parameter", "Gamma", 0.00);
	param.coef0 		= ini->ReadFloat("SVM-Parameter", "Coef0", 0.00);

	param.cache_size 	= ini->ReadFloat("SVM-Parameter", "Cache-Size", 100);
	param.eps 			= ini->ReadFloat("SVM-Parameter", "Eps", 1e-3);
	param.C 			= ini->ReadFloat("SVM-Parameter", "C", 1.00);
	param.nr_weight 	= ini->ReadInteger("SVM-Parameter", "Nr-Weight", 0);
	param.nu 			= ini->ReadFloat("SVM-Parameter", "Nu", 0.5);
	param.p 			= ini->ReadFloat("SVM-Parameter", "P", 0.1);
	param.shrinking 	= ini->ReadInteger("SVM-Parameter", "Shrinking", 1);
	param.probability 	= ini->ReadInteger("SVM-Parameter", "Probability", 0);


	param.weight_label 	= NULL; //todo, ist array: ini->ReadInteger("SVM-Parameter", "Weight-Label", NULL);
	param.weight 		= NULL; //todo, ist array: ini->ReadFloat("SVM-Parameter", "Weight", NULL);

	bCrossvalidation    = cxCrossvalidation->Checked;
	if (bCrossvalidation)
		{
		iCrossvalidation_NrFold = edFold->Text.ToInt();
		if (iCrossvalidation_NrFold < 2)
			{
			Print("#Fehler, Crossvalidation-Fold muss min. 2 sein!");
			return false;
			}
		}

	/* todo ?????
	case 'q':
		print_func = &print_null;
		i--;
		break;
	case 'v': --> wurde über CheckBox geregelt
		cross_validation = 1;
		nr_fold = atoi(argv[i]);
		if(nr_fold < 2)
		{
			fprintf(stderr,"n-fold cross validation: n must >= 2\n");
			exit_with_help();
		}
		break;
	case 'w':
		++param.nr_weight;
		param.weight_label = (int *)realloc(param.weight_label,sizeof(int)*param.nr_weight);
		param.weight = (double *)realloc(param.weight,sizeof(double)*param.nr_weight);
		param.weight_label[param.nr_weight-1] = atoi(&argv[i-1][2]);
		param.weight[param.nr_weight-1] = atof(argv[i]);
		break;
	 */
	delete ini;
	return true;
	}
//---------------------------------------------------------------------------
void TfmChoi::setParameterDefault(svm_parameter& param)
	{
	// default values lt. svm-train.c
	param.svm_type 		= C_SVC;
	param.kernel_type 	= RBF;
	param.degree 		= 3;
	param.gamma 		= 0;
	param.coef0 		= 0;

	param.cache_size 	= 100;
	param.eps 			= 1e-3;
	param.C 			= 1;
	param.nr_weight 	= 0;
	param.weight_label  = NULL;
	param.weight 		= NULL;
	param.nu 			= 0.5;
	param.p 			= 0.1;
	param.shrinking 	= 1;
	param.probability 	= 0;
	}
//---------------------------------------------------------------------------
bool TfmChoi::doCrossvalidation(svm_problem problem, svm_parameter param, int nr_fold)
	{
	Print("\n------- Crossvalidation ------------------------------------");
	int i;
	int total_correct = 0;
	double total_error = 0;
	double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;
	double *target = Malloc(double, problem.l);

	svm_cross_validation(&problem, &param, nr_fold, target);
	if (param.svm_type == EPSILON_SVR || param.svm_type == NU_SVR)
		{
		Print("\tsvm-type == epsilon/nu");

		for(i=0; i < problem.l; i++)
			{
			double y = problem.y[i];
			double v = target[i];
			total_error += (v-y)*(v-y);
			sumv  += v;
			sumy  += y;
			sumvv += v*v;
			sumyy += y*y;
			sumvy += v*y;
			}

		Print("Cross Validation Mean squared error = %g\n",total_error/problem.l);
		Print("Cross Validation Squared correlation coefficient = %g\n",
			((problem.l*sumvy-sumv*sumy)*(problem.l*sumvy-sumv*sumy))/
			((problem.l*sumvv-sumv*sumv)*(problem.l*sumyy-sumy*sumy))
			);
		}
	else
		{
		Print("\tsvm-type != epsilon/nu");
		for(i=0; i < problem.l; i++)
			{
			if(target[i] == problem.y[i])
				++total_correct;
			}
		Print("Cross Validation Accuracy = %g%%\n", 100.0 * total_correct / problem.l);
		}

	free(target);
	return true;
	}
//---------------------------------------------------------------------------
bool TfmChoi::getModel(svm_problem problem, svm_parameter param, svm_model* model)
	{
	Print("\n------- Train Model ----------------------------------------");
	model = svm_train(&problem, &param);

	char model_file_name[1024];
	sprintf(model_file_name, "D://TestAnna.model");
	if(svm_save_model(model_file_name, model))
		{
		Print("#Fehler, can't save model to file %s", model_file_name);
		return false;
		}

	svm_free_and_destroy_model(&model);
	return true;
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

