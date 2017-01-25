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
class TfmMain : public TForm
{
private:
	TIniFile*		Ini;

	void 			Print(char* msg, ...);

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
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *edInputfile;
	TEdit *edVonIdx;
	TEdit *edBisIdx;
	TEdit *edVonMsec;
	TEdit *edBisMsec;
	TEdit *edMinWert;
	TEdit *edMaxWert;
	TBevel *Bevel1;
	TBevel *Bevel3;
	TMemo *memo;
	TProgressBar *pbJob;
	TBevel *Bevel4;
	TButton *btRead;
	TButton *btMaxMin;
	TLabel *laCls;
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
