//---------------------------------------------------------------------------
#ifndef DbPersonenH
#define DbPersonenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <IniFiles.hpp>
#include <System.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "baseforms/basePeople.h"
#include "baseforms/baseEcgData.h"
#include "baseforms/baseDesc.h"
//---------------------------------------------------------------------------
class TfmData : public TForm
{
private:
	TIniFile*		Ini;
	cTools			ftools;

	bool	   			bSelected;
	TfmBasePeople*		fmPeople;
	TfmBaseDesc*		fmDiseases;
	TfmBaseEcg*			fmEcg;

	inline void StartJob(int max);
	inline void TickJob(int tick = 1);
	inline void EndJob();

	void 	OnSelectPerson();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TTimer *tStartup;
	TPanel *Panel1;
	TButton *btClose;
	TActionList *ActionList;
	TAction *acClose;
	TAction *acRefresh;
	TProgressBar *pbJob;
	TBevel *Bevel1;
	TPanel *pnPeople;
	TSplitter *Splitter1;
	TPanel *pnEcgData;
	TPanel *pnDiseases;
	TSplitter *Splitter2;
	TPanel *Panel5;
	TTimer *tCallback;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acRefreshExecute(TObject *Sender);
	void __fastcall tCallbackTimer(TObject *Sender);

public:
	__fastcall TfmData(TComponent* Owner);
	__fastcall TfmData::~TfmData();
	bool 		Execute();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmData *fmData;
bool DlgDatabasePersonen(TForm* Papa);
//---------------------------------------------------------------------------
#endif
