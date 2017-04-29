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

	void 		Print(char* msg, ...);
	void		Color(TImage* img, TColor cl, int von, int bis, int max);
	void 		Line(TImage* img, int x, TColor cl);
	void		Dot(TImage* img, TColor cl, int zeit, int wert, int max);
	
	void		ShowEcg();
	void		GetBeats();
	void		GetRpeaks();
	void		GetRpeaksNeu();

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
	TPanel *pnBeats;
	TBevel *Bevel3;
	TImage *imgBeat1;
	TButton *btBeats;
	TImage *imgBeat2;
	TImage *imgBeat3;
	TImage *imgBeat4;
	TImage *imgBeat5;
	TImage *imgBeat6;
	TMemo *Memo;
	TPanel *Panel2;
	TImage *imgPeak1;
	TImage *imgPeak2;
	TImage *imgPeak3;
	TImage *imgPeak4;
	TImage *imgPeak5;
	TImage *imgPeak6;
	TButton *Button2;
	TBevel *Bevel5;
	TPanel *Panel5;
	TImage *imgNeu1;
	TImage *imgNeu2;
	TImage *imgNeu3;
	TImage *imgNeu4;
	TImage *imgNeu5;
	TImage *imgNeu6;
	TButton *Button4;
	TBevel *Bevel7;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall btReadClick(TObject *Sender);
	void __fastcall btBeatsClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
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
