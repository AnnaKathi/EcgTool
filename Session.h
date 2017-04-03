//---------------------------------------------------------------------------
#ifndef SessionH
#define SessionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "basics/classData.h"
//---------------------------------------------------------------------------
class TfmSession : public TForm
{
private:
	cTools		ftools;
	cData		fdata;

	String		getNow();
	bool		save(TEdit* ed);

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TLabel *Label1;
	TEdit *edStamp;
	TSpeedButton *btNow;
	TLabel *Label2;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TListView *lvResearchers;
	TAction *acReAdd;
	TAction *acReDel;
	TLabel *Label3;
	TComboBox *cbPerson;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edL1;
	TEdit *edL2;
	TEdit *edL3;
	TEdit *edS1;
	TEdit *edS2;
	TEdit *edS3;
	TEdit *edT1;
	TEdit *edT2;
	TEdit *edT3;
	TEdit *edG1;
	TEdit *edG2;
	TEdit *edG3;
	TOpenDialog *OpenECG;
	TAction *acEcgAdd;
	TAction *acEcgDel;
	TBevel *Bevel2;
	TButton *Button1;
	TAction *acSave;
	TAction *acReset;
	TButton *Button2;
	TSpeedButton *SpeedButton3;
	TAction *acPersonAdd;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall btNowClick(TObject *Sender);
	void __fastcall acReAddExecute(TObject *Sender);
	void __fastcall acReDelExecute(TObject *Sender);
	void __fastcall lvResearchersClick(TObject *Sender);
	void __fastcall edL1DblClick(TObject *Sender);
	void __fastcall edL1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall edL1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall acSaveExecute(TObject *Sender);
	void __fastcall acResetExecute(TObject *Sender);
	void __fastcall acPersonAddExecute(TObject *Sender);

public:
	__fastcall TfmSession(TComponent* Owner);
	__fastcall ~TfmSession();
	bool	Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSession *fmSession;
bool DlgNewSession(TForm* Papa);
//---------------------------------------------------------------------------
#endif
