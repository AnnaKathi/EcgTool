//---------------------------------------------------------------------------
#ifndef TestformH
#define TestformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "database/classMySql.h"
#include "database/baseforms/baseDesc.h"
//---------------------------------------------------------------------------
class TfmTest : public TForm
{
private:
	cTools			ftools;

	TfmBaseDesc*	fmDiseases;
	TfmBaseDesc*	fmOrte;
	TfmBaseDesc*	fmLagen;

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TPanel *Panel1;
	TBevel *Bevel2;
	TButton *btClose;
	TPanel *pnDesc1;
	TPanel *pnDesc2;
	TPanel *pnDesc3;
	TTimer *TimerCallback;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall TimerCallbackTimer(TObject *Sender);

public:
	__fastcall TfmTest(TComponent* Owner);
	__fastcall ~TfmTest();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmTest *fmTest;
bool DlgTestform(TForm* Papa);
//---------------------------------------------------------------------------
#endif
