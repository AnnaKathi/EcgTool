//---------------------------------------------------------------------------
#ifndef DataAnalysisH
#define DataAnalysisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "ecg/classEcg.h"
#include "basics/classTools.h"
//---------------------------------------------------------------------------
class TfmAnalysis : public TForm
{
private:
	cTools		ftools;
	cEcg		fecg;

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TPanel *Panel1;
	TButton *Button1;
	TBevel *Bevel2;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *Panel3;
	TLabel *Label1;
	TSpeedButton *btInputfile;
	TLabel *Label3;
	TEdit *edInputfile;
	TComboBox *cbDelim;
	TBevel *Bevel3;
	TOpenDialog *OpenDialog;
	TAction *acLoadFile;
	TAction *acReadFile;
	TButton *Button2;
	TImage *imgData;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall acLoadFileExecute(TObject *Sender);
	void __fastcall acReadFileExecute(TObject *Sender);

public:
	__fastcall TfmAnalysis(TComponent* Owner);
	__fastcall ~TfmAnalysis();

	bool 	Execute();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmAnalysis *fmAnalysis;
bool DlgAnalyseData(TForm* Papa);
//---------------------------------------------------------------------------
#endif
