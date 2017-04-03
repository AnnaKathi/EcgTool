//---------------------------------------------------------------------------
#ifndef DiseasesH
#define DiseasesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "database/baseforms/baseDiseases.h"
//---------------------------------------------------------------------------
class TfmDiseases : public TForm
{
private:
	TfmBaseDiseases*	fmDiseases;


__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TPanel *pnDiseases;
	TTimer *tStartup;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);

public:
	__fastcall TfmDiseases(TComponent* Owner);
	__fastcall ~TfmDiseases();
	bool 	Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmDiseases *fmDiseases;
bool DlgDiseases(TForm* Papa);
//---------------------------------------------------------------------------
#endif
