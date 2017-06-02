/* Vorgehen SVM-Algorithmus von Choi
 * =================================
 *
 * entnommen der libSVM-readme-Datei, Abschnitt 'library usage'
 * see svm-train.c and svm-predict.c on how to use the library
 *
 * 1) get training data
 * 2) construct SVM model using training data, model can also be saved in a file for later use
 * 		a) construct the problem
 *		b) construct svm parameters
 *	3) use the model to classify new data
 */
//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classChoiSVM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "inc/libsvm/libsvm.lib"
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
extern cMySql fmysql;
//---------------------------------------------------------------------------
cChoiSVM::cChoiSVM()
	{
	fAlg_DbNr = 2; //Choi 2016
	bStarted = false;
	}
//---------------------------------------------------------------------------
cChoiSVM::~cChoiSVM()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   private functions   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   public functions   ***********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cChoiSVM::startSvm(cEcg& ecg)
	{
	fecg = &ecg;

	if (fecg->data.data_array.size() <= 0)
		return fail(1, "Es sind keine EKG-Daten enthalten");
		
	bStarted = true;
	return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::startSvm()
	{
	bStarted = true;
	return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::doTrainingData(int label)
	{
	if (!bStarted) return fail(2, "SVM ist nicht initialisiert");

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

	fArray_Train_Data.clear();

	//todo: Das Label des EKG soll nicht übergeben werden, sondern im EKG enthalten sein
	if (label <= 0)
		return fail(1, "Es wurde kein EKG-Label übergeben");

	iarray_t ecg = fecg->data.data_array;
	cRpeaks& r   = fecg->rpeaks;
	r.find(ecg, NULL);
	r.reset();

	int prev_zeit, curr_zeit, next_zeit;
	int count = 0;
	bool fehler = false;
	while ((curr_zeit = r.next()) != -1)
		{
		if ((prev_zeit = r.prev_rpeak()) == -1) continue;
		if ((next_zeit = r.next_rpeak()) == -1) continue;

		if (!fChoiFeat.getSingleFeatures(ecg, prev_zeit, curr_zeit, next_zeit))
			{
			fehler = true;
			break;
			}

		iarray_t features = fChoiFeat.SingleFeatures;
		fArray_Train_Data[count].push_back(label);
		fArray_Train_Data[count].push_back(features[0][0]);
		fArray_Train_Data[count].push_back(features[1][0]);
		fArray_Train_Data[count].push_back(features[2][0]);
		fArray_Train_Data[count].push_back(features[3][0]);
		fArray_Train_Data[count].push_back(features[4][0]);
		fArray_Train_Data[count].push_back(features[5][0]);
		fArray_Train_Data[count].push_back(features[6][0]);
		fArray_Train_Data[count].push_back(features[7][0]);
		count++;
		}

	if (fehler)
		return fail(2, ftools.fmt("SingleFeat meldet: %d, %s", fChoiFeat.error_code, fChoiFeat.error_msg));
	else if (fArray_Train_Data.size() <= 0)
    	return fail(2, "Es konnten keine Trainingsdaten gebildet werden");
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::clearTrainingData()
	{
	if (!bStarted) return fail(2, "SVM ist nicht initialisiert");

	fArray_Train_Data.clear();
	return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::addTrainingData(cEcg& singleEcg, int label)
	{
	if (!bStarted) return fail(2, "SVM ist nicht initialisiert");

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

	//todo: Das Label des EKG soll nicht übergeben werden, sondern im EKG enthalten sein
	fecg = &singleEcg;
	
	if (label < 0)
		return fail(1, "Es wurde kein EKG-Label übergeben");

	iarray_t ecg = fecg->data.data_array;
	cRpeaks& r   = fecg->rpeaks;
	r.find(ecg, NULL);
	r.reset();

	int prev_zeit, curr_zeit, next_zeit;
	int count = fArray_Train_Data.size();
	bool fehler = false;
	while ((curr_zeit = r.next()) != -1)
		{
		if ((prev_zeit = r.prev_rpeak()) == -1) continue;
		if ((next_zeit = r.next_rpeak()) == -1) continue;

		if (!fChoiFeat.getSingleFeatures(ecg, prev_zeit, curr_zeit, next_zeit))
			{
			fehler = true;
			break;
			}

		iarray_t features = fChoiFeat.SingleFeatures;
		fArray_Train_Data[count].push_back(label);
		fArray_Train_Data[count].push_back(features[0][0]);
		fArray_Train_Data[count].push_back(features[1][0]);
		fArray_Train_Data[count].push_back(features[2][0]);
		fArray_Train_Data[count].push_back(features[3][0]);
		fArray_Train_Data[count].push_back(features[4][0]);
		fArray_Train_Data[count].push_back(features[5][0]);
		fArray_Train_Data[count].push_back(features[6][0]);
		fArray_Train_Data[count].push_back(features[7][0]);
		count++;
		}

	if (fehler)
		return fail(2, ftools.fmt("SingleFeat meldet: %d, %s", fChoiFeat.error_code, fChoiFeat.error_msg));
	else if (fArray_Train_Data.size() <= 0)
		return fail(2, "Es konnten keine Trainingsdaten hinzugefügt werden");
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::doProblem(iarray_t training)
	{
	if (!bStarted) return fail(2, "SVM ist nicht initialisiert");
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
		return fail(3, "Es wurden keine Trainingdaten übergeben");

	//Speicherplatz allokieren
	fProblem.l = training.size();
	fProblem.y = Malloc(double, fProblem.l);
	fProblem.x = Malloc(struct svm_node*, fProblem.l);

	int elements = fProblem.l * 8; //8 features pro Herzschlag
	x_space = Malloc(struct svm_node, elements);

	int i = 0;
	int j = 0;
	for (iarray_itr itr = training.begin(); itr != training.end(); itr++)
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

	return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::outProblem(String file)
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
void cChoiSVM::setParameterDefault()
	{
	// default values lt. svm-train.c
	fParam.svm_type 	= C_SVC;
	fParam.kernel_type  = RBF;
	fParam.degree 		= 3;
	fParam.gamma 		= 0;
	fParam.coef0 		= 0;

	fParam.cache_size 	= 100;
	fParam.eps 		    = 1e-3;
	fParam.C 		    = 1;
	fParam.nr_weight    = 0;
	fParam.weight_label = NULL;
	fParam.weight 	    = NULL;
	fParam.nu 		    = 0.5;
	fParam.p 		    = 0.1;
	fParam.shrinking    = 1;
	fParam.probability  = 0;
	}
//---------------------------------------------------------------------------
bool cChoiSVM::doParameter(svm_problem problem)
	{
	if (!bStarted) return fail(2, "SVM ist nicht initialisiert");

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
		return fail(4, "Es wurde kein gültiges Problem übergeben");

	//setzen von außen ermöglichen, ersetzt den Aufruf der exe mit Optionen
	//aus Ini-Datei lesen
	TIniFile* ini = new TIniFile(ftools.GetIniFile());

	fParam.svm_type 	= ini->ReadInteger("SVM-Parameter", "SVM-Type", C_SVC);
	fParam.kernel_type 	= ini->ReadInteger("SVM-Parameter", "Kernel-Type", RBF);
	fParam.degree 		= ini->ReadInteger("SVM-Parameter", "Degree", 3);
	fParam.gamma 		= ini->ReadFloat("SVM-Parameter", "Gamma", 0.00);
	fParam.coef0 		= ini->ReadFloat("SVM-Parameter", "Coef0", 0.00);

	fParam.cache_size 	= ini->ReadFloat("SVM-Parameter", "Cache-Size", 100);
	fParam.eps 			= ini->ReadFloat("SVM-Parameter", "Eps", 1e-3);
	fParam.C 			= ini->ReadFloat("SVM-Parameter", "C", 1.00);
	fParam.nr_weight 	= ini->ReadInteger("SVM-Parameter", "Nr-Weight", 0);
	fParam.nu 			= ini->ReadFloat("SVM-Parameter", "Nu", 0.5);
	fParam.p 			= ini->ReadFloat("SVM-Parameter", "P", 0.1);
	fParam.shrinking 	= ini->ReadInteger("SVM-Parameter", "Shrinking", 1);
	fParam.probability 	= ini->ReadInteger("SVM-Parameter", "Probability", 0);


	fParam.weight_label = NULL; //todo, ist array: ini->ReadInteger("SVM-Parameter", "Weight-Label", NULL);
	fParam.weight 		= NULL; //todo, ist array: ini->ReadFloat("SVM-Parameter", "Weight", NULL);

	/* todo ?????
	case 'q':
		print_func = &print_null;
		i--;
		break;
	case 'v': --> wird über setCrossvalidation gesetzt
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

	return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::doCrossvalidation(svm_problem problem, svm_parameter param, int fold)
	{
	if (!bStarted) return fail(5, "SVM ist nicht initialisiert");

	if (fold < 2)
		return fail(5, "Der Crossvalidation-Fold muss min. 2 sein");

	int i;
	int total_correct = 0;
	double total_error = 0;
	double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;
	double *target = Malloc(double, problem.l);

	svm_cross_validation(&problem, &param, fold, target);
	if (param.svm_type == EPSILON_SVR || param.svm_type == NU_SVR)
		{
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

		iMeanSquaredError = total_error/problem.l;
		iSquredCorrCoeff  =
        	((problem.l*sumvy-sumv*sumy)*(problem.l*sumvy-sumv*sumy))/
			((problem.l*sumvv-sumv*sumv)*(problem.l*sumyy-sumy*sumy));

		/*
		Print("Cross Validation Mean squared error = %g\n",total_error/problem.l);
		Print("Cross Validation Squared correlation coefficient = %g\n",
			((problem.l*sumvy-sumv*sumy)*(problem.l*sumvy-sumv*sumy))/
			((problem.l*sumvv-sumv*sumv)*(problem.l*sumyy-sumy*sumy))
			);
		*/
		}
	else
		{
		for(i=0; i < problem.l; i++)
			{
			if(target[i] == problem.y[i])
				++total_correct;
			}
		iAccuracy = 100.0 * total_correct / problem.l;
		//Print("Cross Validation Accuracy = %g%%\n", 100.0 * total_correct / problem.l);
		}

	free(target);

	return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::doModel(svm_problem problem, svm_parameter param)
	{
	if (!bStarted) return fail(5, "SVM ist nicht initialisiert");

	fModel = svm_train(&problem, &param);

	char model_file_name[1024];
	sprintf(model_file_name, "D://TestAnna.model"); //todo übergeben lassen

	if(svm_save_model(model_file_name, fModel))
		return fail(6, "can't save model to file " + String(model_file_name));

	svm_free_and_destroy_model(&fModel);
	return ok();
	}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool cChoiSVM::SvmAccuracy(double& accuracy, sChoiSvmData data)
	{
	if (data.label == "") return fail(6, "Es wurde keine Algorithmus-Kennung übergeben");
	if (data.alg <= 0)    return fail(6, "Es wurde keine Algorithmus-Nummer übergeben");

	if (data.training_von <= 0) return fail(6, "Trainingdaten sind nicht korrekt (von)");
	if (data.training_bis <= 0) return fail(6, "Trainingdaten sind nicht korrekt (bis)");
	if (data.classify_von <= 0) return fail(6, "Classifydaten sind nicht korrekt (von)");
	if (data.classify_bis <= 0) return fail(6, "Classifydaten sind nicht korrekt (bis)");

	//todo: Sicherheitsprüfung Bereiche, auf Überlappung prüfen

	//-- Used files
	String path = ftools.GetPath();
	String svm_train   = path + "\\libSVM\\svm-train.exe";
	String svm_predict = path + "\\libSVM\\svm-predict.exe";
	if (!FileExists(svm_train))
		return fail(6, ftools.fmt("Die Train-Datei existiert nicht <%s>", svm_train).c_str());

	if (!FileExists(svm_predict))
		return fail(6, ftools.fmt("Die Predict-Datei existiert nicht <%s>", svm_train).c_str());

	String trainfile = ftools.fmt("%s\\libSVM\\%s.train",       path, data.label);
	String testfile  = ftools.fmt("%s\\libSVM\\%s.test",        path, data.label);
	String modelfile = ftools.fmt("%s\\libSVM\\%s.train.model", path, data.label);
	String outfile   = ftools.fmt("%s\\libSVM\\%s.out",         path, data.label);

	//-- Create Train + Test
	if (!SvmWriteFile(true, trainfile, data.alg, data.training_von, data.training_bis))
		return fail(6, ftools.fmt("Train <%s>: Fehler aufgetreten: %s", data.label, error_msg).c_str());

	if (!SvmWriteFile(false, testfile, data.alg, data.classify_von, data.classify_bis))
		return fail(6, ftools.fmt("Test <%s>: Fehler aufgetreten: %s", data.label, error_msg).c_str());

	//-- Exe-Files aufrufen
	 if (!FileExists(trainfile))
		return fail(6, ftools.fmt("Die Trainings-Daten existieren nicht <%s>", trainfile).c_str());

	//svm-train.exe a1a.train
	ShellExecute(
		this,    			//hwnd
		"open",     		//Operation
		svm_train.c_str(),	//File
		trainfile.c_str(),	//Parameters
		path.c_str(),		//Directory
		SW_SHOW);   		//Show-Command

	if (!FileExists(modelfile))
		return fail(6, ftools.fmt("Das Modell konnte nicht erstellt werden <%s>", modelfile).c_str());

	if (!FileExists(testfile))
		return fail(6, ftools.fmt("Die Testdatei existiert nicht<%s>", testfile).c_str());

	//svm-predict.exe a1a.test a1a.train.model a1a.out
	String params = ftools.fmt("%s %s %s", testfile, modelfile, outfile);
	ShellExecute(
		this,    			 //hwnd
		"open",     		 //Operation
		svm_predict.c_str(), //File
		params.c_str(),	     //Parameters
		path.c_str(),		 //Directory
		SW_SHOW);   		 //Show-Command


	if (!FileExists(outfile))
		return fail(6, ftools.fmt("Die Ausgabedatei konnte nicht erstellt werden <%s>", outfile).c_str());

	//-- Ergebnisse vergleichen
	if (!SvmCompareResult(accuracy, testfile, outfile))
		return fail(6, ftools.fmt("Ausgabevergleich konnte nicht durchgeführt werden: %s", error_msg).c_str());
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::SvmWriteFile(bool bWriteTraining, String filename, int alg, int ecgvon, int ecgbis)
	{
	iarray_t array; array.clear();

	if (filename == "") return fail(7, "Es wurde kein Dateiname übergeben");;
	FILE* fp = fopen(filename.c_str(), "w");
	if (fp == NULL)
		return fail(7, ftools.fmt("Die Datei konnte nicht geöffnet werden (%s)", filename).c_str());

	if (ecgvon <= 0 || ecgbis <= 0) return fail(7, ftools.fmt("Die Einschränkung stimmen nicht (%d-%d)", ecgvon, ecgbis).c_str());
	if (ecgvon > ecgbis) return fail(7, ftools.fmt("Die Einschränkung stimmen nicht (%d-%d)", ecgvon, ecgbis).c_str());

	int count = 0;
	int count_featmissing = 0;
	int count_datamissing = 0;
	for (int i = ecgvon; i <= ecgbis; i++)
		{
		//Features laden
		/* TODO if (!fmysql.features.select(i, alg))
			{
			//keine Features für dieses EKG vorhanden
			count_featmissing++;
			continue;
			}
		*/

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
	return ok();
	}
//---------------------------------------------------------------------------
bool cChoiSVM::SvmCompareResult(double& accuracy, String testfile, String outfile)
	{
	FILE* fptest = fopen(testfile.c_str(), "r");
	if (fptest == NULL)
		return fail(8, ftools.fmt("Fehler, Die Testfile konnte nicht geöffnet werden <%s>", testfile).c_str());

	FILE* fpout = fopen(outfile.c_str(), "r");
	if (fpout == NULL)
		{
		fclose(fptest);
		return fail(8, ftools.fmt("Fehler, Die Ausgabefile konnte nicht geöffnet werden <%s>", outfile).c_str());
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
		return fail(8, ftools.fmt("Fehler aufgetreten").c_str());

	if (count <= 0)
		accuracy = 0.0;
	else
		accuracy = (double)right / (double)count * 100;
	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int	cChoiSVM::get_LibSVM_Version()
	{
	return libsvm_version;
	}
//---------------------------------------------------------------------------
iarray_t cChoiSVM::get_train_data()
	{
	return fArray_Train_Data;
	}
//---------------------------------------------------------------------------
svm_problem cChoiSVM::get_problem()
	{
	return fProblem;
	}
//---------------------------------------------------------------------------
svm_parameter cChoiSVM::get_param()
	{
	return fParam;
	}
//---------------------------------------------------------------------------
int cChoiSVM::get_algdbnr()
	{
	return fAlg_DbNr;
	}
//---------------------------------------------------------------------------
