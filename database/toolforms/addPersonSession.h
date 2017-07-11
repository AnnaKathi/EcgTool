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
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "..\..\basics\classTools.h"
#include "..\..\ecg\classEcg.h"
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
	TAction *acAddZustand1;
	TAction *acAddZustand2;
	TAction *acAddZustand3;
	TAction *acAddZustand4;
	TBitBtn *btAddLiegend;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TBitBtn *BitBtn4;
	TBitBtn *BitBtn5;
	TBitBtn *BitBtn6;
	TBitBtn *BitBtn7;
	TCheckBox *cxLead3;
	TCheckBox *cxLead4;
	TCheckBox *cxLead2;
	TCheckBox *cxLead1;
	TListView *lvData;
	TMemo *mZ1P1;
	TMemo *mZ2P1;
	TMemo *mZ3P1;
	TMemo *mZ4P1;
	TOpenDialog *OpenDialog;
	TMemo *mZ1P2;
	TMemo *mZ2P2;
	TMemo *mZ3P2;
	TMemo *mZ4P2;
	TMemo *mZ4P3;
	TMemo *mZ3P3;
	TMemo *mZ2P3;
	TMemo *mZ1P3;
	TMemo *mZ4P4;
	TMemo *mZ3P4;
	TMemo *mZ2P4;
	TMemo *mZ1P4;
	TLabel *Label2;
	TEdit *edZ1Puls;
	TEdit *edZ1BP;
	TLabel *Label3;
	TEdit *edZ2BP;
	TEdit *edZ2Puls;
	TEdit *edZ3BP;
	TEdit *edZ3Puls;
	TEdit *edZ4BP;
	TEdit *edZ4Puls;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acAddZustand1Execute(TObject *Sender);
	void __fastcall acAddZustand2Execute(TObject *Sender);
	void __fastcall acAddZustand3Execute(TObject *Sender);
	void __fastcall acAddZustand4Execute(TObject *Sender);
	void __fastcall mZ1P1DblClick(TObject *Sender);

private:
	cTools	ftools;
	cEcg	fecg;
	int		iPerson;

	bool 	getMemo(String name, int& state, int& lage);
	bool 	LoadFile(eState state, eLage lage, String bp, int puls, String file);
	void 	AddLine(String file, eLage lage, eState state, ePosition pos, int anz, String bp, int puls);

public:
	__fastcall TfmAddPersonSession(TComponent* Owner);
	bool 		Execute(int person);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmAddPersonSession *fmAddPersonSession;
bool DlgAddPersonSession(TForm* Papa, int person);
//---------------------------------------------------------------------------
#endif
