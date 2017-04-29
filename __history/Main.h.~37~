//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
private:
	cTools		ftools;

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TBitBtn *btLokkIntoEcg;
	TMainMenu *MainMenu;
	TMenuItem *ools1;
	TMenuItem *EKGuntersuchen1;
	TActionList *ActionList1;
	TAction *acLookIntoECG;
	TAction *acClose;
	TTimer *tStartup;
	TStatusBar *sbMain;
	TBitBtn *BitBtn1;
	TAction *acPeople;
	TBitBtn *BitBtn2;
	TAction *acDiseases;
	TBevel *Bevel2;
	TBitBtn *BitBtn3;
	TAction *acCreateTemp;
	TBitBtn *BitBtn4;
	TAction *acCreateSeesion;
	TBitBtn *BitBtn5;
	TAction *acShowData;
	void __fastcall acLookIntoECGExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acPeopleExecute(TObject *Sender);
	void __fastcall acDiseasesExecute(TObject *Sender);
	void __fastcall acCreateTempExecute(TObject *Sender);
	void __fastcall acCreateSeesionExecute(TObject *Sender);
	void __fastcall acShowDataExecute(TObject *Sender);

public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
