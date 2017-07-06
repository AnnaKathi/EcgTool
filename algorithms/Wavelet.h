//---------------------------------------------------------------------------
#ifndef WaveletH
#define WaveletH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "features/classWavelib.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmWavelet : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TMemo *mInfo;
	TButton *btPrint1;
	TButton *btPrint2;
	TButton *btDwt;
	TPanel *pnBottom;
	TBevel *Bevel1;
	TProgressBar *pbProgress;
	void __fastcall btPrint1Click(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall btPrint2Click(TObject *Sender);
	void __fastcall btDwtClick(TObject *Sender);

private:
	cWavelib		wavelib;
	wave_object		fWaveObj;
	wt_object		fWaveTransform;

	void print(char* msg, ...);

public:
	__fastcall TfmWavelet(TComponent* Owner);
	__fastcall ~TfmWavelet();
	bool Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmWavelet *fmWavelet;
bool DlgShowWavelet(TForm* Papa);
//---------------------------------------------------------------------------
#endif
