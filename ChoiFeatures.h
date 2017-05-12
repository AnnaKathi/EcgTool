//---------------------------------------------------------------------------
#ifndef ChoiFeaturesH
#define ChoiFeaturesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "database/baseforms/baseEcgData.h"
#include "algorithms/features/classChoiFeatures.h"
//---------------------------------------------------------------------------
class TfmChoiFeatures : public TForm
{
private:
	cTools			ftools;
	void 			Print(char* msg, ...);

	TfmBaseEcg*		TfmEcg;
	void			GetSelectedEcg();

	cChoiFeat		fChoi;
	void			GetFeatures();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *Panel1;
	TButton *btClose;
	TBevel *Bevel2;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnEcg;
	TTimer *CallbackEcg;
	TMemo *memo;
	TButton *btFeatures;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall CallbackEcgTimer(TObject *Sender);
	void __fastcall btFeaturesClick(TObject *Sender);

public:		
	__fastcall TfmChoiFeatures(TComponent* Owner);
	bool 		Execute();

	
};
extern PACKAGE TfmChoiFeatures *fmChoiFeatures;
bool DlgChoiFeatures(TForm* Papa);
//---------------------------------------------------------------------------
#endif
