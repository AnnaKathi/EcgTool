//---------------------------------------------------------------------------
#ifndef AlgChoiH
#define AlgChoiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "../ecg/classEcg.h"
#include "../ecg/classHeartbeat.h"
#include "../ecg/classRpeaks.h"
#include "../basics/classTools.h"
#include "../basics/classArray.h"
#include "../basics/classMath.h"
//---------------------------------------------------------------------------
class TfmChoi : public TForm
{
private:
	cEcg		fecg;
	cTools		ftools;
	cArray		farray;
	cMath		fmath;

	String		fmt(char* msg, ...);
	void 		Print(char* msg, ...);
	void		Color(TImage* img, TColor cl, int von, int bis, int max);
	void 		Line(TImage* img, int x, TColor cl);
	void		Dot(TImage* img, TColor cl, int zeit, int wert, int max);
	
	void		ShowEcg();
	void		GetRpeaks();

	int			FidPQInt[12];
	int			FidQSInt[12];
	int			FidSTInt[12];
	double 		FidPAmp[12];
	double 		FidQAmp[12];
	double 		FidRAmp[12];
	double 		FidSAmp[12];
	double 		FidTAmp[12];

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *Panel1;
	TButton *Button1;
	TBevel *Bevel2;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TOpenDialog *OpenDialog;
	TPanel *Panel3;
	TLabel *Label1;
	TSpeedButton *btInputfile;
	TLabel *Label3;
	TLabel *Label2;
	TEdit *edInputfile;
	TComboBox *cbDelim;
	TComboBox *cbFormat;
	TBevel *Bevel4;
	TPanel *pnMain;
	TPanel *pnEcgGes;
	TImage *imgEcg;
	TButton *btRead;
	TBevel *Bevel6;
	TMemo *Memo;
	TPanel *Panel5;
	TImage *imgNeu1;
	TImage *imgNeu2;
	TImage *imgNeu3;
	TImage *imgNeu4;
	TImage *imgNeu5;
	TImage *imgNeu6;
	TButton *Button4;
	TBevel *Bevel7;
	TPanel *pnFid;
	TBevel *Bevel3;
	TMemo *m1;
	TMemo *m2;
	TMemo *m3;
	TMemo *m4;
	TMemo *m5;
	TMemo *m6;
	TLabel *Label4;
	TImage *imgBeat;
	TLabel *Label5;
	TMemo *mFid;
	TLabel *Label6;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall btReadClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);

public:		
	__fastcall TfmChoi(TComponent* Owner);
	__fastcall ~TfmChoi();

	bool 		Execute();
	
};
//---------------------------------------------------------------------------
extern PACKAGE TfmChoi *fmChoi;
bool DlgAlgChoi(TForm* Papa);
//---------------------------------------------------------------------------
#endif
