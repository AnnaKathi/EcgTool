//---------------------------------------------------------------------------
#ifndef EinzelAuswH
#define EinzelAuswH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "baseforms/basePeople.h"
#include "baseforms/baseEcgData.h"
#include "../basics/classTools.h"
//---------------------------------------------------------------------------
class TfmSingle : public TForm
{
private:
	cTools			ftools;

	TfmBasePeople*	fmPeople;
	TfmBaseEcg*		fmEcgData;

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TPanel *Panel1;
	TButton *Button1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnAuswertung;
	TLabel *Label4;
	TMemo *Memo1;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TPanel *pnFilterEcg;
	TPanel *pnFilterPerson;
	TBevel *Bevel3;
	TBevel *Bevel4;
	TMemo *mAus;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);

public:
	__fastcall TfmSingle(TComponent* Owner);
	__fastcall ~TfmSingle();
	bool 	Execute();
	
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSingle *fmSingle;
bool DlgEinzelAuswertung(TForm* Papa);
//---------------------------------------------------------------------------
#endif
