//---------------------------------------------------------------------------
#ifndef DetailsH
#define DetailsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "ecg/classEcg.h"
#include "basics/classArray.h"
#include "basics/classData.h"
#include "ecg/classHeartbeat.h"
#include "algorithms/features/classAC.h"
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
	cEcg*		ecg;
	cAC			fac;
	cArray		farray;
	cData		fdata;

	void		placeForm();

	inline void	StartJob();
	inline void	TickJob();
	inline void	EndJob();

	void		PaintCurves();
	void		DoCurves(iarray_t aDaten);

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TPanel *pnCombo;
	TLabel *Label1;
	TComboBox *cbKurve;
	TBevel *Bevel2;
	TPanel *pnHeader1;
	TLabel *Label2;
	TTimer *tCombo;
	TBevel *Bevel4;
	TImage *imgData;
	TPanel *Panel2;
	TLabel *Label4;
	TImage *imgBeats;
	TBevel *Bevel5;
	TPanel *Panel3;
	TLabel *Label5;
	TImage *imgHerz;
	TBevel *Bevel6;
	TProgressBar *pbJob;
	TPanel *Panel4;
	TLabel *Label6;
	TImage *imgAC;
	TBevel *Bevel7;
	TPanel *Panel1;
	TLabel *Label3;
	TImage *imgAcHerz;
	TBevel *Bevel3;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall cbKurveChange(TObject *Sender);
	void __fastcall tComboTimer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

public:
	__fastcall TfmDetails(TComponent* Owner);
	bool 		Execute(TForm* papa, cEcg& Ecg);
	bool		Renew(cEcg& Ecg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmDetails *fmDetails;
//---------------------------------------------------------------------------
#endif
