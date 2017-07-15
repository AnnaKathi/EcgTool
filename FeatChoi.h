//---------------------------------------------------------------------------
#ifndef FeatChoiH
#define FeatChoiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "ecg/classEcg.h"
#include "algorithms/features/classFeaturesChoi.h"
//---------------------------------------------------------------------------
class TfmFeatChoi : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TButton *btLoadEkg1;
	TImage *imgEcg1;
	TOpenDialog *OpenDialog;
	TLabel *laEcg1;
	TComboBox *cbLead1;
	TButton *btFeat1;
	TMemo *mFeat1;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall btLoadEkg1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall cbLead1Change(TObject *Sender);
	void __fastcall btFeat1Click(TObject *Sender);

private:
	cEcg			fecg;
	cFeaturesChoi   fFeatChoi;

public:
	__fastcall TfmFeatChoi(TComponent* Owner);
	bool 	Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmFeatChoi *fmFeatChoi;
bool DlgShowVglChoi(TForm* Papa);
//---------------------------------------------------------------------------
#endif
