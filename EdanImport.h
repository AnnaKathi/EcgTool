//---------------------------------------------------------------------------
#ifndef EdanImportH
#define EdanImportH
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
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfmEdan : public TForm
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
	TMemo *mLead1;
	TLabel *Label2;
	TEdit *edPath;
	TButton *Button2;
	TAction *acImport;
	TLabel *Label1;
	TMemo *mLead2;
	TLabel *Label3;
	TMemo *mLead3;
	TLabel *Label4;
	TMemo *mLead4;
	TLabel *Label5;
	TMemo *mLead5;
	TLabel *Label6;
	TMemo *mLead6;
	TLabel *Label7;
	TMemo *mLead7;
	TLabel *Label8;
	TMemo *mLead8;
	TLabel *Label9;
	TProgressBar *pbProgress;
	TLabel *Label10;
	TEdit *edFile;
	TButton *btTest;
	TOpenDialog *OpenDialog;
	TButton *btLoad;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acImportExecute(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall btTestClick(TObject *Sender);
	void __fastcall btLoadClick(TObject *Sender);

private:
	cTools		ftools;

	void		Tick(int pos = 1);
	bool 		GetFile();
	iarray_t 	getMemo(TMemo* memo);
	void 		fillMemo(TMemo* memo);
	void 		fprint(FILE* fp, iarray_t array, int ix);

public:
	__fastcall TfmEdan(TComponent* Owner);
	bool 		Execute();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmEdan *fmEdan;
bool DlgImportEdan(TForm* Papa);
//---------------------------------------------------------------------------
#endif
