//---------------------------------------------------------------------------
#ifndef EcgViewH
#define EcgViewH
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
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "basics/classArray.h"
#include "basics/classMath.h"
#include "ecg/classEcg.h"
#include "definitions.h"
#include "Details.h"
//---------------------------------------------------------------------------
class TfmEcg : public TForm
{
private:
	TIniFile*	Ini;
	cTools		ftools;
	cEcg		ecg;
//todo	cMySql		fmysql;
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

	void		Importschema();
	void		MySqlSave();

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
	TTimer *tDetails;
	TMainMenu *MainMenu;
	TMenuItem *Importschemata1;
	TMenuItem *Importschemata2;
	TMenuItem *DateninMySQLDatenbankspeichern1;
	TMenuItem *N1;
	TMenuItem *Beenden1;
	TMenuItem *Datenbank1;
	TMenuItem *Datenanzeigen1;
	TMenuItem *Algorithmen1;
	TMenuItem *estenmitAlg11;
	TMenuItem *GetValuefromAlg11;
	TButton *btAC;
	TButton *btNeu;
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
	void __fastcall tDetailsTimer(TObject *Sender);
	void __fastcall Beenden1Click(TObject *Sender);
	void __fastcall Importschemata2Click(TObject *Sender);
	void __fastcall DateninMySQLDatenbankspeichern1Click(TObject *Sender);
	void __fastcall Datenanzeigen1Click(TObject *Sender);
	void __fastcall estenmitAlg11Click(TObject *Sender);
	void __fastcall GetValuefromAlg11Click(TObject *Sender);
	void __fastcall btACClick(TObject *Sender);
	void __fastcall btNeuClick(TObject *Sender);


public:
	__fastcall TfmEcg(TComponent* Owner);
	__fastcall ~TfmEcg();

	bool Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmEcg *fmEcg;
//---------------------------------------------------------------------------
#endif
