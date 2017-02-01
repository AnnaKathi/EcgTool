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
	void		ReadFile();
	void		Runden();
	void		MovingAv();
	void		CutCurve();
	void		FindRpeaks();

	void		Derivate1();
	void		Abl1Runden();
	void		Abl1MovingAv();
	void		Abl1CutCurve();

	void		Derivate2();
	void		Abl2Runden();
	void		Abl2MovingAv();
	void		Abl2CutCurve();

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
	TButton *btRpeaks;
	TButton *btDerivates;
	TBevel *Bevel2;
	TImage *img2;
	TImage *img3;
	TBevel *Bevel5;
	TButton *btAblRunden;
	TButton *btAblMovAv;
	TButton *btAblCut;
	TButton *btAblTurns;
	TButton *btAbl2;
	TButton *btAbl2Runden;
	TButton *btAbl2MovAv;
	TButton *btAbl2Cut;
	TButton *btAbl2Turns;
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
	void __fastcall btRpeaksClick(TObject *Sender);
	void __fastcall btDerivatesClick(TObject *Sender);
	void __fastcall btAblRundenClick(TObject *Sender);
	void __fastcall btAblMovAvClick(TObject *Sender);
	void __fastcall btAblCutClick(TObject *Sender);
	void __fastcall btAblTurnsClick(TObject *Sender);
	void __fastcall btAbl2Click(TObject *Sender);
	void __fastcall btAbl2RundenClick(TObject *Sender);
	void __fastcall btAbl2MovAvClick(TObject *Sender);
	void __fastcall btAbl2CutClick(TObject *Sender);
	void __fastcall btAbl2TurnsClick(TObject *Sender);


public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
