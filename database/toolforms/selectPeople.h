//---------------------------------------------------------------------------
#ifndef selectPeopleH
#define selectPeopleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "baseforms/basePeople.h"
//---------------------------------------------------------------------------
class TfmSelectPerson : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *pnBottom;
	TButton *Button1;
	TBevel *Bevel3;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnPeople;
	TAction *acSelect;
	TButton *btSelect;
	TTimer *tCallback;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tCallbackTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acSelectExecute(TObject *Sender);

private:
	int 			iPerson;

	TfmBasePeople*	fmPeople;
	void 			OnSelectPerson();

public:
	__fastcall TfmSelectPerson(TComponent* Owner);
	int 		Execute();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmSelectPerson *fmSelectPerson;
int DlgSelectSinglePerson(TForm* Papa);
//---------------------------------------------------------------------------
#endif
