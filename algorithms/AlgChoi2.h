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

	int			CountAnna;
	int			CountManni;
	int			CountManu;
	int			CountMartin;

	void 		Print(char* msg, ...);
	void		SetValues();
	String		GetFile(String dat);
	void		AddFile(String file, int count, int id);

	bool 		CheckEcg();
	void 		DoSvm();
	bool		BuildTrainingData();
	bool		BuildProblem();

	void		Test();
	bool 		outProblem(svm_problem& problem, String file);

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel4;
	TPanel *Panel1;
	TButton *Button1;
	TBevel *Bevel2;
	TTimer *tStartup;
	TOpenDialog *OpenDialog;
	TPanel *Panel3;
	TPanel *pnClassification;
	TBevel *Bevel5;
	TListView *lvData;
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
	TPanel *Panel2;
	TLabel *Label1;
	TButton *btAddAnna;
	TButton *btAddManni;
	TButton *btAddManu;
	TButton *btAddMartin;
	TComboBox *cbDelim;
	TLabel *Label3;
	TComboBox *cbFormat;
	TLabel *Label2;
	TButton *Button2;
	TAction *acCheckEcgs;
	TMemo *memo;
	TAction *acDoEcgs;
	TButton *Button3;
	TCheckBox *cxCrossvalidation;
	TLabel *laFold;
	TEdit *edFold;
	TButton *btAlt;
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
	void __fastcall acCheckEcgsExecute(TObject *Sender);
	void __fastcall acDoEcgsExecute(TObject *Sender);
	void __fastcall btAltClick(TObject *Sender);
	
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
