//---------------------------------------------------------------------------
#ifndef DetailsH
#define DetailsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classArray.h"
#include "classAlg1.h"
//---------------------------------------------------------------------------
enum {
	cbEkgData,
	cbDerivate1,
	cbDerivate2
	};
//---------------------------------------------------------------------------
class TfmDetails : public TForm
{
private:
	TForm*		Papa;
	cAlg1*		alg1;
	cArray		farray;

	void		placeForm();

	void		PaintCurves();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TPanel *pnCombo;
	TLabel *Label1;
	TComboBox *cbKurve;
	TBevel *Bevel2;
	TImage *imgRpeaks;
	TPanel *pnHeader1;
	TLabel *Label2;
	TBevel *Bevel3;
	TTimer *tCombo;
	TBevel *Bevel4;
	TImage *imgData;
	TPanel *Panel1;
	TLabel *Label3;
	TPanel *Panel2;
	TLabel *Label4;
	TImage *imgBeats;
	TBevel *Bevel5;
	TPanel *Panel3;
	TLabel *Label5;
	TImage *imgHerz;
	TBevel *Bevel6;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall cbKurveChange(TObject *Sender);
	void __fastcall tComboTimer(TObject *Sender);

public:
	__fastcall TfmDetails(TComponent* Owner);
	bool 		Execute(TForm* papa, cAlg1& alg);
	bool		Renew(cAlg1& alg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmDetails *fmDetails;
//---------------------------------------------------------------------------
#endif
