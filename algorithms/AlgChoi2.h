//---------------------------------------------------------------------------
#ifndef AlgChoi2H
#define AlgChoi2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "../basics/classTools.h"
#include "../ecg/classEcg.h"
//---------------------------------------------------------------------------
#include "features/classChoiFeatures.h"
#include "classifications/classChoiSVM.h"
//---------------------------------------------------------------------------
class TfmChoi2 : public TForm
{
private:
	cTools		ftools;
	cEcg		fecg;

	cChoiFeat	fChoiFeat;
	cChoiSVM	fChoiSVM;

	int			Count1Anna;
	int			Count1Manni;
	int			Count1Manu;
	int			Count1Martin;

	int			Count2Anna;
	int			Count2Manni;
	int			Count2Manu;
	int			Count2Martin;

	void 		Print(char* msg, ...);
	void		SetValues();
	String		GetFile(String dat);
	void		AddFile(TListView* lv, String file, int count, int id);

	bool 		WriteFile(bool train, String filename);
	bool 		CompareResult(String testfile, String outfile);


__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel4;
	TPanel *Panel1;
	TButton *Button1;
	TTimer *tStartup;
	TOpenDialog *OpenDialog;
	TBevel *Bevel5;
	TButton *btReset;
	TActionList *ActionList1;
	TAction *acAddAnna;
	TAction *acAddManni;
	TAction *acAddManu;
	TAction *acAddMartin;
	TPopupMenu *PopupMenu;
	TAction *acDelAnna;
	TAction *acDelManni;
	TAction *acDelManu;
	TAction *acDelMartin;
	TAction *acClose;
	TAction *acReset;
	TAction *acCheckEcgs;
	TMemo *memo;
	TAction *acDoEcgs;
	TButton *btCreateFiles;
	TButton *btCompareFiles;
	TPanel *Panel6;
	TPanel *pnClassification;
	TPanel *Panel2;
	TLabel *Label1;
	TButton *btAddAnna;
	TButton *btAddManni;
	TButton *btAddManu;
	TButton *btAddMartin;
	TListView *lvData1;
	TPanel *Panel4;
	TPanel *Panel5;
	TLabel *Label4;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TListView *lvData2;
	TBevel *Bevel1;
	TButton *Button2;
	TComboBox *cbDelim;
	TLabel *Label3;
	TLabel *Label2;
	TComboBox *cbFormat;
	TButton *btExeFiles;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acAddAnnaExecute(TObject *Sender);
	void __fastcall acAddManniExecute(TObject *Sender);
	void __fastcall acAddManuExecute(TObject *Sender);
	void __fastcall acAddMartinExecute(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acResetExecute(TObject *Sender);
	void __fastcall btExeFilesClick(TObject *Sender);
	void __fastcall btCreateFilesClick(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall btCompareFilesClick(TObject *Sender);
	
public:
	__fastcall TfmChoi2(TComponent* Owner);
	__fastcall ~TfmChoi2();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmChoi2 *fmChoi2;
bool DlgAlgChoi2(TForm* Papa);
//---------------------------------------------------------------------------
#endif
