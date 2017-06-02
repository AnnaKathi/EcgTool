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
#include "ecg/classEcg.h"
#include "ecg/classHeartbeat.h"
#include "database/baseforms/baseEcgData.h"
//---------------------------------------------------------------------------
#include "algorithms/rpeak-detection/classRpeaksChoi.h"
//---------------------------------------------------------------------------
#include "algorithms/features/classFeaturesChoi.h"
#include "algorithms/features/classChoiFeatures.h"
#include "algorithms/features/classRandomPoints.h"
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
	TMemo *memo;
	TButton *btFeatures;
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
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CallbackEcgTimer(TObject *Sender);
	void __fastcall btFeaturesClick(TObject *Sender);
	void __fastcall btBuildAllClick(TObject *Sender);

private:
	cEcg			fecg;
	cTools			ftools;
	void 			Print(char* msg, ...);

	TfmBaseEcg*		TfmEcg;
	void			GetSelectedEcg();

	cHeartbeats		fHeartbeats;
	cChoiFeat		fChoi;
	cRandomPoints	fRandomPoints;

	cRpeaksChoi		fRpeaksChoi;

	cFeaturesChoi	fFeatChoi;

	int				Count_Neu;
	int				Count_Edit;
	
	void			GetFeatures();
	bool			InsertFeatures(String features, int algRpeaks, int algFeat);
	bool			UpdateFeatures(String features, int algRpeaks, int algFeat);
	String			BuildRandomFeatures(iarray_t array);

	void			GetAllFeatures();
	bool 			DoFeatures(sEcgData ecgdata, int algRpeaks, int algFeat, bool replace);

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
