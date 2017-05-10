//---------------------------------------------------------------------------
#ifndef SessionH
#define SessionH
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
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "basics/classData.h"
#include "database/classMySql_Session.h"
#include "database/toolforms/addEcg.h"
//---------------------------------------------------------------------------
class TfmSession : public TForm
{
private:
	cTools		ftools;
	cData		fdata;

	String		getNow();

	TfmAddEcg*	fmAddEcg;
	void		GetEcgData();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TAction *acReAdd;
	TAction *acReDel;
	TPanel *pnSession;
	TLabel *Label1;
	TSpeedButton *btNow;
	TEdit *edStamp;
	TLabel *Label2;
	TComboBox *cbOrte;
	TLabel *Label3;
	TListView *lvResearchers;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TBevel *Bevel2;
	TListView *lvEcg;
	TPopupMenu *PopupMenu;
	TActionList *ActionList2;
	TAction *acEcgAdd;
	TAction *acEcgDel;
	TMenuItem *EKGhinzufgen1;
	TMenuItem *EKGlschen1;
	TTimer *TimerCallback;
	TPanel *pnBottom;
	TButton *Button1;
	TBevel *Bevel3;
	TButton *Button2;
	TAction *acSave;
	TMemo *mKommentar;
	TLabel *Label4;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall btNowClick(TObject *Sender);
	void __fastcall acReAddExecute(TObject *Sender);
	void __fastcall acReDelExecute(TObject *Sender);
	void __fastcall lvResearchersClick(TObject *Sender);
	void __fastcall acEcgAddExecute(TObject *Sender);
	void __fastcall acEcgDelExecute(TObject *Sender);
	void __fastcall lvEcgClick(TObject *Sender);
	void __fastcall TimerCallbackTimer(TObject *Sender);
	void __fastcall acSaveExecute(TObject *Sender);

public:
	__fastcall TfmSession(TComponent* Owner);
	__fastcall ~TfmSession();
	bool	Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSession *fmSession;
bool DlgNewSession(TForm* Papa);
//---------------------------------------------------------------------------
#endif
