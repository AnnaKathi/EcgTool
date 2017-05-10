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
#include "database/classMySql.h"
//---------------------------------------------------------------------------
class TfmEcg : public TForm
{
private:
	TIniFile*	Ini;
	cTools		ftools;
	cEcg		ecg;
	cArray		farray;
	cMath		fmath;
	TfmDetails*	fmDetails;

	bool		bDisplayedDetails;
	bool		bRun;
	bool		bStop;

	bool		bMausMarking;
	int			MausPosBegin;
	int			MausCurrPos;
	int			MausPosEnde;
	void		Line(int x, TColor cl);

	void 		Print(char* msg, ...);
	
	void		ReadFile();
	void		CutCurve();
	void		MovingAv();
	void		SaveData();
	bool		SaveDataHeader(FILE* fp);

	void		Importschema();
	void		MySqlSave();
	void 		BuildData(sEcgData& data);

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
	TLabel *Label2;
	TComboBox *cbFormat;
	TButton *btSave;
	TSaveDialog *SaveDialog;
	TButton *btSave2;
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
	void __fastcall btSaveClick(TObject *Sender);
	void __fastcall imgEcgMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall imgEcgMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall imgEcgMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall btSave2Click(TObject *Sender);


public:
	__fastcall TfmEcg(TComponent* Owner);
	__fastcall ~TfmEcg();

	bool Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmEcg *fmEcg;
//---------------------------------------------------------------------------
#endif
