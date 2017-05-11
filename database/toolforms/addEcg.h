//---------------------------------------------------------------------------
#ifndef addEcgH
#define addEcgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "addEcgFiles.h"
//---------------------------------------------------------------------------
class TfmAddEcg : public TForm
{
private:
	int				fRow;
	TTimer*			fCallbackTimer;

	TfmEcgFiles*	fmFiles;
	void			GetEcgFiles();

	bool			CheckForm();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *pnBottom;
	TBevel *Bevel2;
	TPanel *pnData;
	TLabel *Label2;
	TComboBox *cbPerson;
	TBevel *Bevel3;
	TListView *lvEcg;
	TPopupMenu *PopupMenu;
	TMenuItem *EKGhinzufgen1;
	TMenuItem *EKGlschen1;
	TLabel *Label1;
	TComboBox *cbState;
	TLabel *Label3;
	TComboBox *cbLage;
	TButton *Button1;
	TAction *acAdd;
	TAction *acDel;
	TAction *acSelect;
	TButton *Button2;
	TTimer *TimerCallback;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acAddExecute(TObject *Sender);
	void __fastcall acDelExecute(TObject *Sender);
	void __fastcall lvEcgClick(TObject *Sender);
	void __fastcall acSelectExecute(TObject *Sender);
	void __fastcall TimerCallbackTimer(TObject *Sender);
	void __fastcall cbPersonChange(TObject *Sender);
	void __fastcall lvEcgChange(TObject *Sender, TListItem *Item,
          TItemChange Change);

public:	   
	__fastcall TfmAddEcg(TComponent* Owner);
	bool 		Execute();

	bool		SetCallbackTimer(TTimer* timer);
	bool		GetEcgHeader(int& person, int& state, int& lage);
	bool		GetNextEcgRow(int& anz, int& pos, String& file, int& format, String& delim);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmAddEcg *fmAddEcg;
bool DlgAddEcgs(TForm* Papa);
//---------------------------------------------------------------------------
#endif
