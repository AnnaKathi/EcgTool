//---------------------------------------------------------------------------
#ifndef addPersonSessionH
#define addPersonSessionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
#include "..\..\basics\classTools.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfmAddPersonSession : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel4;
	TPanel *pnBottom;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel2;
	TPanel *pnPerson;
	TBevel *Bevel1;
	TLabel *Label1;
	TLabel *laPerson;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnAddState;
	TBitBtn *btAddLiegend;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TCheckBox *cxLead1;
	TCheckBox *cxLead2;
	TCheckBox *cxLead3;
	TCheckBox *cxLead4;
	TBevel *Bevel3;
	TListView *lvData;
	TAction *acAddZustand1;
	TAction *acAddZustand2;
	TAction *acAddZustand3;
	TAction *acAddZustand4;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acAddZustand1Execute(TObject *Sender);
	void __fastcall acAddZustand2Execute(TObject *Sender);
	void __fastcall acAddZustand3Execute(TObject *Sender);
	void __fastcall acAddZustand4Execute(TObject *Sender);

private:
	cTools	ftools;
	int		iPerson;

public:
	__fastcall TfmAddPersonSession(TComponent* Owner);
	bool 		Execute(int person);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmAddPersonSession *fmAddPersonSession;
bool DlgAddPersonSession(TForm* Papa, int person);
//---------------------------------------------------------------------------
#endif
