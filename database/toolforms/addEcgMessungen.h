//---------------------------------------------------------------------------
#ifndef addEcgMessungenH
#define addEcgMessungenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "../../definitions.h"
#include "../../basics/classTools.h"
#include "../../ecg/classEcg.h"
//---------------------------------------------------------------------------
class TfmAddMessung : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TBevel *Bevel1;
	TPanel *pnInfo;
	TMemo *mInfo;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnBottom;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel2;
	TPanel *pnAddState;
	TBevel *Bevel3;
	TListView *lvData;
	TPanel *pnPerson;
	TBevel *Bevel4;
	TLabel *Label1;
	TComboBox *cbPerson;
	TBitBtn *btAddLiegend;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TAction *addLiegend;
	TAction *addSitzend;
	TAction *addStehend;
	TAction *addGehend;
	TOpenDialog *OpenDialog;
	TCheckBox *cxLead1;
	TCheckBox *cxLead2;
	TCheckBox *cxLead3;
	TCheckBox *cxLead4;
	TLabel *Label4;
	TLabel *Label2;
	TComboBox *cbFormat;
	TLabel *Label3;
	TComboBox *cbDelim;
	TLabel *Label5;
	TComboBox *cbZustand;
	TTimer *TimerCallback;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall addLiegendExecute(TObject *Sender);
	void __fastcall addSitzendExecute(TObject *Sender);
	void __fastcall addStehendExecute(TObject *Sender);
	void __fastcall addGehendExecute(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);

private:
	int				fRow;
	TTimer*			fCallbackTimer;

	cEcg		fecg;
	cTools		ftools;
	bool 		LoadFile(eLage lage);
	void 		AddLine(String file, eLage lage, eState state, ePosition pos, int anz);

public:
	__fastcall TfmAddMessung(TComponent* Owner);
	bool 		SetCallbackTimer(TTimer* timer);
	bool 		GetEcgHeader(int& person);
	bool 		GetNextEcgRow(int& state, int& lage, int& anz, int& pos, String& file, int& format, String& delim);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmAddMessung *fmAddMessung;
//---------------------------------------------------------------------------
#endif
