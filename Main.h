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
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
private:
	cTools		ftools;

	void		setStatus(String status, int panel=0);
	void		setDbInfo();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TMainMenu *MainMenu;
	TMenuItem *ools1;
	TMenuItem *EKGuntersuchen1;
	TActionList *ActionList1;
	TAction *acLookIntoECG;
	TAction *acClose;
	TTimer *tStartup;
	TStatusBar *sbMain;
	TAction *acPeople;
	TAction *acDiseases;
	TAction *acSingleAusw;
	TAction *acCreateSeesion;
	TAction *acShowData;
	TPanel *pnMain;
	TBitBtn *btLokkIntoEcg;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TBitBtn *BitBtn4;
	TBevel *Bevel2;
	TAction *acGesAusw;
	TBitBtn *BitBtn5;
	TBitBtn *BitBtn6;
	TAction *acLookIntoData;
	void __fastcall acLookIntoECGExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acPeopleExecute(TObject *Sender);
	void __fastcall acDiseasesExecute(TObject *Sender);
	void __fastcall acSingleAuswExecute(TObject *Sender);
	void __fastcall acCreateSeesionExecute(TObject *Sender);
	void __fastcall acShowDataExecute(TObject *Sender);
	void __fastcall acGesAuswExecute(TObject *Sender);
	void __fastcall acLookIntoDataExecute(TObject *Sender);

public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
