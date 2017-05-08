//---------------------------------------------------------------------------
#ifndef classChoiSVMH
#define classChoiSVMH
//---------------------------------------------------------------------------
#include "../inc/libsvm/svm.h"
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
#include "../../basics/classTools.h"
#include "../../ecg/classEcg.h"
#include "../../ecg/classRpeaks.h"
//---------------------------------------------------------------------------
#include "../features/classChoiFeatures.h"
//---------------------------------------------------------------------------
class PACKAGE cChoiSVM : public cBase
	{
public:
	cChoiSVM();
	~cChoiSVM();

	bool		startSvm(cEcg& ecg);
	bool		startSvm(); //für addTrainingData
	bool		doTrainingData(int label); //setzt fArray_Train_Data

	bool		clearTrainingData();
	bool		addTrainingData(cEcg& singleEcg, int label);

	svm_node* 	x_space;
	bool		doProblem(iarray_t training);
	bool		outProblem(String file);

	void		setParameterDefault();
	bool		doParameter(svm_problem problem);

	double		iMeanSquaredError;
	double		iSquredCorrCoeff;
	double		iAccuracy;
	bool		doCrossvalidation(svm_problem problem, svm_parameter param, int fold);

	bool		doModel(svm_problem problem, svm_parameter param);


__property int version = { read=get_LibSVM_Version };

__property iarray_t train_data = { read=get_train_data };
__property svm_problem problem = { read=get_problem };
__property svm_parameter param = { read=get_param };

private:
	cEcg*		fecg;
	cTools		ftools;
	cChoiFeat	fChoiFeat;

	bool		bStarted;

	iarray_t	fArray_Train_Data;
	iarray_t	get_train_data();

	svm_problem	fProblem;
	svm_problem	get_problem();

	svm_parameter	fParam;
	svm_parameter	get_param();

	svm_model*	fModel;

	int			libSVM_Version;
	int			get_LibSVM_Version();
	};
//---------------------------------------------------------------------------
#endif
