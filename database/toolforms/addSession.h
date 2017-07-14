//---------------------------------------------------------------------------
#ifndef addSessionH
#define addSessionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "basics/classData.h"
#include "ecg/classEcg.h"
#include "database/classMySql_Session.h"
#include "database/toolforms/addEcg.h" //OLD ??
#include "database/toolforms/addEcgMessungen.h"
//---------------------------------------------------------------------------
class TfmSessionAdd : public TForm
{
private:
	cTools		ftools;
	cEcg		fecg;
	cData		fdata;

	String		getNow();

	TfmAddEcg*	fmAddEcg;
	void		GetEcgData();

	TfmAddMessung*	fmAddEcgMessung;

	bool		CheckSession();
	bool		SaveSession();
	bool 		GetArray(String file, ePosition pos, eDatFormat format, String delim, sEcgData& data);

	void 		ShowPersonenData(int person);
	void 		addPersonRow(int person, char* buffer);


__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TAction *acReAdd;
	TAction *acReDel;
	TAction *acSave;
	TActionList *ActionList2;
	TAction *acEcgAdd;
	TAction *acEcgDel;
	TPopupMenu *PopupMenu;
	TMenuItem *EKGhinzufgen1;
	TMenuItem *EKGlschen1;
	TTimer *TimerCallback;
	TPanel *pnBottom;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel3;
	TPanel *pnBasics;
	TPanel *pnSession;
	TLabel *Label1;
	TSpeedButton *btNow;
	TLabel *Label2;
	TLabel *Label3;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TLabel *Label4;
	TEdit *edStamp;
	TComboBox *cbOrte;
	TListView *lvResearchers;
	TMemo *mKommentar;
	TListView *lvEcg;
	TBevel *Bevel2;
	TLabel *Label5;
	TEdit *edTemp;
	TLabel *Label6;
	TEdit *edLuft;
	TAction *acAddKnownPerson;
	TAction *acAddNewPerson;
	TButton *btNewPerson;
	TButton *btKnwonPerson;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall btNowClick(TObject *Sender);
	void __fastcall lvResearchersClick(TObject *Sender);
	void __fastcall lvEcgClick(TObject *Sender);
	void __fastcall TimerCallbackTimer(TObject *Sender);
	void __fastcall lvEcgChange(TObject *Sender, TListItem *Item,
          TItemChange Change);
	void __fastcall edStampChange(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acReAddExecute(TObject *Sender);
	void __fastcall acReDelExecute(TObject *Sender);
	void __fastcall acSaveExecute(TObject *Sender);
	void __fastcall acEcgAddExecute(TObject *Sender);
	void __fastcall acEcgDelExecute(TObject *Sender);
	void __fastcall acAddKnownPersonExecute(TObject *Sender);
	void __fastcall acAddNewPersonExecute(TObject *Sender);

public:		
	__fastcall TfmSessionAdd(TComponent* Owner);
	__fastcall ~TfmSessionAdd();
	bool	Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSessionAdd *fmSessionAdd;
bool DlgNewSession(TForm* Papa);
//---------------------------------------------------------------------------
#endif
