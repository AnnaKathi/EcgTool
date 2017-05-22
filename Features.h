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
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "ecg/classEcg.h"
#include "ecg/classHeartbeat.h"
#include "database/baseforms/baseEcgData.h"
//---------------------------------------------------------------------------
#include "algorithms/features/classChoiFeatures.h"
#include "algorithms/features/classRandomPoints.h"
#include <ComCtrls.hpp>
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
	TPanel *pnAlg;
	TBevel *Bevel3;
	TCheckBox *cxChoi;
	TLabel *Label1;
	TCheckBox *cxRandom;
	TBevel *Bevel4;
	TProgressBar *pbJob;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CallbackEcgTimer(TObject *Sender);
	void __fastcall btFeaturesClick(TObject *Sender);
	void __fastcall btBuildAllClick(TObject *Sender);

private:
	cTools			ftools;
	void 			Print(char* msg, ...);

	TfmBaseEcg*		TfmEcg;
	void			GetSelectedEcg();

	cHeartbeats		fHeartbeats;
	cChoiFeat		fChoi;
	cRandomPoints	fRandomPoints;

	int				Count_Neu;
	int				Count_Edit;
	
	void			GetFeatures();
	bool			InsertFeatures(String features, int alg);
	bool			UpdateFeatures(String features, int alg);
	String			BuildRandomFeatures(iarray_t array);

	void			GetAllFeatures();
	bool 			DoFeatures(sEcgData ecgdata, int alg, bool replace);

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
