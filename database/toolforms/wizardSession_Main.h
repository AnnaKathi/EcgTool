//---------------------------------------------------------------------------
#ifndef wizardSession_MainH
#define wizardSession_MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "../../basics/classTools.h"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfmWizSession : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *pnBottom;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel3;
	TActionList *ActionList1;
	TAction *acNext;
	TAction *acBack;
	TTimer *tStartup;
	TAction *acClose;
	TPageControl *pcSession;
	TTabSheet *tbBasics;
	TLabel *Label1;
	TEdit *edStamp;
	TSpeedButton *btNow;
	TLabel *Label2;
	TComboBox *cbOrte;
	TLabel *Label3;
	TListView *lvResearchers;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TLabel *Label4;
	TMemo *mKommentar;
	TActionList *ActionListBasics;
	TAction *acAddResearcher;
	TAction *acDelResearcher;
	TTabSheet *tbPersonen;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acBackExecute(TObject *Sender);
	void __fastcall acNextExecute(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acAddResearcherExecute(TObject *Sender);
	void __fastcall acDelResearcherExecute(TObject *Sender);
	void __fastcall btNowClick(TObject *Sender);
	void __fastcall edStampChange(TObject *Sender);

private:
	cTools		ftools;
	void		CheckPage();

	//-- Definitionen tbBasics
	String 		getNow();


public:		
	__fastcall TfmWizSession(TComponent* Owner);
	__fastcall ~TfmWizSession();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmWizSession *fmWizSession;
bool DlgWizardSession(TForm* Papa);
//---------------------------------------------------------------------------
#endif
