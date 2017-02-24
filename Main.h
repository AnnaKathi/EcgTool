//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <IniFiles.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "basics/classArray.h"
#include "basics/classMath.h"
#include "classAlg1.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
private:
	TIniFile*	Ini;
	cAlg1		alg1;
	cArray		farray;
	cMath		fmath;
	TfmDetails*	fmDetails;

	bool		bDisplayedDetails;
	bool		bRun;
	bool		bStop;

	void 		Print(char* msg, ...);
	void		ReadFile();
	void		CutCurve();
	void		MovingAv();

	void		sendClick(TButton* bt);

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *pnLeft;
	TBevel *Bevel4;
	TLabel *laCls;
	TPanel *Panel3;
	TLabel *Label1;
	TSpeedButton *btInputfile;
	TLabel *Label3;
	TEdit *edInputfile;
	TComboBox *cbDelim;
	TMemo *memo;
	TProgressBar *pbJob;
	TButton *btRead;
	TPanel *pnClient;
	TImage *imgEcg;
	TBevel *Bevel3;
	TTimer *tStartup;
	TOpenDialog *OpenDialog;
	TButton *btMovAv;
	TButton *btCut;
	TBevel *Bevel2;
	TImage *imgDeriv1;
	TImage *imgDeriv2;
	TBevel *Bevel5;
	TBevel *Bevel6;
	TEdit *edGl1;
	TEdit *edGl2;
	TEdit *edGl3;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label9;
	TEdit *edCutVon;
	TEdit *edCutBis;
	TLabel *Label10;
	TLabel *Label8;
	TEdit *edVonSample;
	TLabel *Label11;
	TEdit *edBisSample;
	TCheckBox *cxDropBegin;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall laClsClick(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall btReadClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btMovAvClick(TObject *Sender);
	void __fastcall btCutClick(TObject *Sender);


public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
