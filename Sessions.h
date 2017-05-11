//---------------------------------------------------------------------------
#ifndef SessionsH
#define SessionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "database/baseforms/baseSession.h"
//---------------------------------------------------------------------------
class TfmSessions : public TForm
{
private:
	TfmBaseSession*		fmSession;

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
	TPanel *pnSession;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);

public:
	__fastcall TfmSessions(TComponent* Owner);
	__fastcall ~TfmSessions();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSessions *fmSessions;
bool DlgShowSessions(TForm* Papa);
//---------------------------------------------------------------------------
#endif
