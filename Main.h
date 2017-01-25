//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <IniFiles.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "cCsv.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
private:
	TIniFile*		Ini;
	cCsv*			fcsv;

	bool			bRun;
	bool			bStop;

	void 			Print(char* msg, ...);
	void			ReadFile();

__published:	// IDE-verwaltete Komponenten
	TTimer *tStartup;
	TPanel *pnInfo;
	TMemo *mInfo;
	TOpenDialog *OpenDialog;
	TPanel *pnLeft;
	TPanel *Panel3;
	TLabel *Label1;
	TSpeedButton *btInputfile;
	TLabel *Label2;
	TLabel *Label5;
	TEdit *edInputfile;
	TEdit *edVonSample;
	TEdit *edBisSample;
	TBevel *Bevel1;
	TBevel *Bevel3;
	TMemo *memo;
	TProgressBar *pbJob;
	TBevel *Bevel4;
	TButton *btRead;
	TButton *btMaxMin;
	TLabel *laCls;
	TPanel *pnClient;
	TComboBox *cbDelim;
	TLabel *Label3;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall btReadClick(TObject *Sender);
	void __fastcall laClsClick(TObject *Sender);
	
public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
