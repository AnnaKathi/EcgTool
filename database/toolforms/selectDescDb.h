//---------------------------------------------------------------------------
#ifndef selectDescDbH
#define selectDescDbH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
#include "../classMySql_DescDb.h"
#include "database/baseforms/baseDesc.h"
//---------------------------------------------------------------------------
class TfmSelectDesc : public TForm
{
private:
	cMySqlDescDb*		fdesc;
	TfmBaseDesc*		fmDesc;
	String				fIdents;

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *Panel1;
	TButton *btClose;
	TBevel *Bevel2;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnListe;
	TTimer *TimerCallback;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall TimerCallbackTimer(TObject *Sender);

public:		
	__fastcall TfmSelectDesc(TComponent* Owner);
	
	String 		Execute(cMySqlDescDb& desc);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSelectDesc *fmSelectDesc;
String DlgSelectDesc(TForm* Papa, cMySqlDescDb& desc);
//---------------------------------------------------------------------------
#endif
