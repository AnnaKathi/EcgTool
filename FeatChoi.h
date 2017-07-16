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
#include "basics/classArray.h"
#include "basics/classMath.h"
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
	TMemo *mFeatO1;
	TMemo *mFeatO2;
	TImage *imgEcg2;
	TButton *btLoadEkg2;
	TComboBox *cbLead2;
	TButton *btFeat2;
	TLabel *laEcg2;
	TImage *iHeartEcg1;
	TLabel *Label2;
	TImage *iHeartEcg2;
	TLabel *Label3;
	TImage *iHeAblEcg1;
	TMemo *mFeatA1;
	TImage *iHeAblEcg2;
	TMemo *mFeatA2;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall btLoadEkg1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall cbLead1Change(TObject *Sender);
	void __fastcall btFeat1Click(TObject *Sender);
	void __fastcall btLoadEkg2Click(TObject *Sender);
	void __fastcall cbLead2Change(TObject *Sender);
	void __fastcall btFeat2Click(TObject *Sender);

private:
	cArray			farray;
	cMath			fmath;

	cEcg			fecg1;
	cEcg			fecg2;
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
