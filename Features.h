//---------------------------------------------------------------------------
#ifndef FeaturesH
#define FeaturesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "basics/classArray.h"
#include "ecg/classEcg.h"
#include "ecg/classHeartbeat.h"
#include "database/baseforms/baseEcgData.h"
//---------------------------------------------------------------------------
#include "algorithms/rpeak-detection/classRpeaksChoi.h"
//---------------------------------------------------------------------------
#include "algorithms/features/classChoiFeatures.h"
#include "algorithms/features/classRandomPoints.h"
#include "algorithms/features/classFeaturesChoi.h"
#include "algorithms/features/classFeaturesWaili3.h"
//---------------------------------------------------------------------------
class TfmFeatures : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *Panel1;
	TButton *btClose;
	TBevel *Bevel2;
	TPanel *pnEcg;
	TTimer *CallbackEcg;
	TPanel *pnAuswahl;
	TButton *btBuildAll;
	TPanel *pnFeatures;
	TBevel *Bevel3;
	TCheckBox *cxFeatChoi;
	TLabel *Label1;
	TCheckBox *cxFeatRandom;
	TBevel *Bevel4;
	TProgressBar *pbJob;
	TPanel *pnRPeaks;
	TBevel *Bevel5;
	TLabel *Label2;
	TCheckBox *cxRpeaksAnna;
	TCheckBox *cxRpeaksChoi;
	TBevel *Bevel6;
	TPanel *pnMemo;
	TMemo *memo;
	TPanel *pnPreprocessing;
	TBevel *Bevel7;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *cxPreFourier;
	TCheckBox *cxPreNone;
	TCheckBox *cxSmooth;
	TEdit *edSmooth;
	TRadioGroup *rgFehler;
	TCheckBox *cxFeatWaili;
	TButton *btArff;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CallbackEcgTimer(TObject *Sender);
	void __fastcall btBuildAllClick(TObject *Sender);
	void __fastcall cxSmoothClick(TObject *Sender);
	void __fastcall edSmoothExit(TObject *Sender);
	void __fastcall btArffClick(TObject *Sender);

private:
	cEcg			fecg;
	cArray			farray;
	cTools			ftools;
	void 			Print(char* msg, ...);

	TfmBaseEcg*		TfmEcg;
	void			GetSelectedEcg();

	cHeartbeats		fHeartbeats;
	cChoiFeat		fChoi;
	cRandomPoints	fRandomPoints;

	cRpeaksChoi		fRpeaksChoi;

	cFeaturesChoi	fFeatChoi;
	cFeaturesWaili3	fFeatWaili;

	int				Count_Neu;
	int				Count_Edit;
	
	bool			InsertFeatures(String features, int algPre, int algRpeaks, int algFeat);
	bool			UpdateFeatures(String features, int algPre, int algRpeaks, int algFeat);
	String			BuildRandomFeatures(iarray_t array);

	bool			fAbortOnError; //in Fehlerfall fortfahren
	iarray_t		fArray;  //Original-EKG-Werte
	iarray_t		fValues; //Ausgangswerte, ggf. durch Preprocessing bereinigt
	iarray_t		fRpeaks;
	String			fFeatures;

	void			GetFeatures();
	bool 			DoFeaturesBegin(sEcgData ecgdata, bool replace);
	bool			DoFeaturesPre(sEcgData ecgdata, bool replace, int algPre);
	bool			DoFeaturesRpeaks(sEcgData ecgdata, bool replace, int algPre, int algRpeaks);
	bool 			DoFeatures(sEcgData ecgdata, bool replace, int algPre, int algRpeaks, int algFeat);
	bool			doPre(int algPre);
	bool			doRpeaks(int algRpeaks);
	bool			doFeats(int algFeat);

	bool			StartJob(int anz_data);
	void			TickJob(int pos=1);
	void			EndJob();

	//TEST
	void CreateArff();

public:
	__fastcall TfmFeatures(TComponent* Owner);
	__fastcall ~TfmFeatures();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmFeatures *fmFeatures;
bool DlgFeatures(TForm* Papa);
//---------------------------------------------------------------------------
#endif
