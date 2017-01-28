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
#include "classAlg1.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
private:
	TIniFile*	Ini;
	cAlg1		alg1;

	bool		bRun;
	bool		bStop;

	void 		Print(char* msg, ...);
	void		Draw();
	void		ReadFile();
	void		Runden();
	void		MovingAv();
	void		CutCurve();
	void		Derivates();
	void		GetTurns();



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
	TLabel *Label2;
	TLabel *Label5;
	TLabel *Label3;
	TEdit *edInputfile;
	TEdit *edVonSample;
	TEdit *edBisSample;
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
	TButton *btRunden;
	TButton *btCut;
	TButton *btTurns;
	TButton *btDerivates;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall laClsClick(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall btReadClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btMovAvClick(TObject *Sender);
	void __fastcall btRundenClick(TObject *Sender);
	void __fastcall btCutClick(TObject *Sender);
	void __fastcall btTurnsClick(TObject *Sender);
	void __fastcall btDerivatesClick(TObject *Sender);


public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
