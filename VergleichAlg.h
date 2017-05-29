//---------------------------------------------------------------------------
#ifndef VergleichAlgH
#define VergleichAlgH
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
#include "database/classMySql.h"
#include "database/baseforms/baseEcgData.h"
#include "algorithms/classifications/classChoiSVM.h"
#include "algorithms/features/classChoiFeatures.h"
#include "algorithms/features/classRandomPoints.h"
//---------------------------------------------------------------------------
class TfmVergleich : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TBevel *Bevel1;
	TBevel *Bevel2;
	TPanel *pnInfo;
	TMemo *mInfo;
	TPanel *Panel1;
	TButton *btClose;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TAction *acClassify;
	TPanel *pnAuswahl;
	TBevel *Bevel3;
	TPanel *pnAlg;
	TLabel *Label1;
	TCheckBox *cxChoi1;
	TCheckBox *cxRandom;
	TBevel *Bevel4;
	TPanel *pnEcg;
	TMemo *memo;
	TBevel *Bevel5;
	TPanel *pnClassify;
	TBevel *Bevel6;
	TLabel *Label2;
	TCheckBox *cxClassifySvm;
	TButton *btVergleich;
	TPanel *pnSvm;
	TLabel *Label3;
	TBevel *Bevel7;
	TLabel *Label4;
	TEdit *edTrainingVon;
	TLabel *Label6;
	TEdit *edTrainingBis;
	TLabel *Label7;
	TEdit *edClassifyVon;
	TLabel *Label9;
	TEdit *edClassifyBis;
	TProgressBar *pbJob;
	TCheckBox *cxChoi2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall cxClassifySvmClick(TObject *Sender);
	void __fastcall btVergleichClick(TObject *Sender);

private:
	cTools			ftools;
	cEcg			fecg;
	cChoiSVM		fChoiSvm;
	cChoiFeat		fChoiFeat;
	cRandomPoints	fRandomFeat;

	TfmBaseEcg*		TfmEcg;
	void 			Print(char* msg, ...);

	void 			JobStart(int max);
	void			JobEnd();
	void			JobTick(int tick = 1);

	double			Accuracy[2][2];  //zwei Klassifizierungen mal zwei Feature-Extracrtion
	void			DoVergleich();
	void 			DoVergleichNeu();

	bool			DoSvm();
	bool			DoXyz();


public:
	__fastcall TfmVergleich(TComponent* Owner);
	__fastcall ~TfmVergleich();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmVergleich *fmVergleich;
bool DlgAlgVergleich(TForm* Papa);
//---------------------------------------------------------------------------
#endif
