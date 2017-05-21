//---------------------------------------------------------------------------
#ifndef ChoiKlassifizierungH
#define ChoiKlassifizierungH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "ecg/classEcg.h"
#include "database/classMySql.h"
#include "database/baseforms/baseEcgData.h"
//---------------------------------------------------------------------------
class TfmChoiClassification : public TForm
{
private:
	cTools			ftools;
	cEcg			fecg;
	void 			Print(char* msg, ...);

	TfmBaseEcg*		TfmEcg;

	bool 			WriteFile(bool bWriteTraining, String filename);


__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *Panel1;
	TButton *btClose;
	TBevel *Bevel2;
	TPanel *pnEcg;
	TMemo *memo;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edTrainingVon;
	TEdit *edTrainingBis;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edClassifyVon;
	TLabel *Label6;
	TEdit *edClassifyBis;
	TButton *Button1;
	TAction *acClassify;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acClassifyExecute(TObject *Sender);

public:
	__fastcall TfmChoiClassification(TComponent* Owner);
	__fastcall ~TfmChoiClassification();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmChoiClassification *fmChoiClassification;
bool DlgChoiClassification(TForm* Papa);
//---------------------------------------------------------------------------
#endif
