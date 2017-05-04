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
//---------------------------------------------------------------------------
cChoiSVM::cChoiSVM()
	{
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

	//todo: Das Label des EKG soll nciht übergeben werden, sondern im EKG enthalten sein
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

