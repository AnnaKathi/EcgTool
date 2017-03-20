//---------------------------------------------------------------------------
#ifndef Alg1H
#define Alg1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
#include "classAlg1.h"
#include "../ecg/classEcg.h"
#include "../basics/classArray.h"
//---------------------------------------------------------------------------
class TfmAlg1 : public TForm
{
private:
	cAlg1		falg;
	cEcg*		fecg;
	cArray		farray;

	bool		bPrintMsg;
	void 		Print(char* msg, ...);

	double		Range;
	bool		FindBeat();
	double		CalcRange();


__published:	// IDE-verwaltete Komponenten
	TTimer *tStartup;
	TPanel *pnInfo;
	TMemo *mInfo;
	TPanel *Panel1;
	TActionList *ActionList1;
	TAction *acClose;
	TButton *Button1;
	TImage *img;
	TMemo *Memo;
	TButton *btStep1;
	TImage *imgBeat;
	TButton *btStep2;
	TEdit *edRange;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall btStep1Click(TObject *Sender);
	void __fastcall btStep2Click(TObject *Sender);

public:
	__fastcall TfmAlg1(TComponent* Owner);
	__fastcall ~TfmAlg1();
	bool 		Execute(cEcg& ecg);
	double		GetIdent(cEcg& ecg); //für Direktaufruf von außen
};
//---------------------------------------------------------------------------
extern PACKAGE TfmAlg1 *fmAlg1;
bool DlgAlgorithmus1(TForm* Papa, cEcg& ecg);
double GetAlgorithmus1(TForm* Papa, cEcg& ecg);
//---------------------------------------------------------------------------
#endif
