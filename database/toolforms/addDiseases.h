//---------------------------------------------------------------------------
#ifndef addDiseasesH
#define addDiseasesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmDis : public TForm
{
private:
	bool		bNewDisease;
	int			iDisease;

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel2;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TAction *acSave;
	TLabel *Label1;
	TEdit *edIdent;
	TLabel *Label2;
	TEdit *edBez;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);

public:
	__fastcall TfmDis(TComponent* Owner);
	bool 	Execute(int ident);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmDis *fmDis;
bool DlgDiseaseAdd(TForm* Papa);
//---------------------------------------------------------------------------
#endif
