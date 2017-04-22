//---------------------------------------------------------------------------
#ifndef DataAnalysisH
#define DataAnalysisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "definitions.h"
#include "ecg/classEcg.h"
#include "basics/classTools.h"
//---------------------------------------------------------------------------
class TfmAnalysis : public TForm
{
private:
	cTools		ftools;
	cArray		farray;
	cEcg		fecg;

	String		Delim;
	eDatFormat	Format;
	bool		bFinished;

	bool		DoPath(String verz);
	bool 		DoFile(String file, String name);
	void		Values();
	void		Resort(bool asc);

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TPanel *Panel1;
	TButton *Button1;
	TBevel *Bevel2;
	TActionList *ActionList1;
	TAction *acClose;
	TBevel *Bevel3;
	TOpenDialog *OpenDialog;
	TAction *acLoadFile;
	TAction *acReadFile;
	TPanel *Panel3;
	TLabel *Label1;
	TSpeedButton *btInputfile;
	TLabel *Label3;
	TLabel *Label2;
	TEdit *edInput;
	TComboBox *cbDelim;
	TComboBox *cbFormat;
	TButton *btRead;
	TListView *lvData;
	TAction *acExport;
	TButton *Button2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall acLoadFileExecute(TObject *Sender);
	void __fastcall acReadFileExecute(TObject *Sender);
	void __fastcall acExportExecute(TObject *Sender);
	void __fastcall lvDataCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);

public:
	__fastcall TfmAnalysis(TComponent* Owner);
	__fastcall ~TfmAnalysis();

	bool 	Execute();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmAnalysis *fmAnalysis;
bool DlgAnalyseData(TForm* Papa);
//---------------------------------------------------------------------------
#endif
