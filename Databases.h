//---------------------------------------------------------------------------
#ifndef DatabasesH
#define DatabasesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfmDatabases : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnBottom;
	TButton *Button1;
	TBevel *Bevel3;
	TPanel *pnTabellen;
	TLabel *Label1;
	TListView *lvData;
	TSplitter *Splitter1;
	TPanel *pnTabelle;
	TPanel *pnNoTab;
	TPanel *pnSelectDb;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall lvDataDblClick(TObject *Sender);

private:
	cTools		ftools;

	void 		ShowTabellen();
	void 		SelectTab(String tab);
	bool 		SelectTabDesc(String tab);
	bool 		createForm(cMySqlDescDb& desc);

public:
	__fastcall TfmDatabases(TComponent* Owner);
	__fastcall ~TfmDatabases();
	bool 		Execute();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmDatabases *fmDatabases;
bool DlgShowDatabases(TForm* Papa);
//---------------------------------------------------------------------------
#endif
