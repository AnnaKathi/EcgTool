//---------------------------------------------------------------------------
#ifndef baseDescH
#define baseDescH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "../../basics/classTools.h"
#include "../classMySql_DescDb.h"
//---------------------------------------------------------------------------
struct sDescFilter
	{
	int			identVon;
	int			identBis;
	String		bez;
	};
//---------------------------------------------------------------------------
class TfmBaseDesc : public TForm
{
private:
	cTools				ftools;
	cMySqlDescDb*		fdesc;

	sDescFilter     	ffilter;

	void 				snapTo(TWinControl* container, TAlign align);
	void 				MsgBox(char* msg, ...);

	bool				bInShow;

	bool 				BuildFilter();
	bool 				CheckFilter();

__published:	// IDE-verwaltete Komponenten
	TBevel *Bevel4;
	TListView *lvData;
	TPanel *pnFilter;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edIdVon;
	TEdit *edIdBis;
	TEdit *edBez;
	TActionList *ActionList;
	TAction *acFilter;
	TAction *acAdd;
	TAction *acDel;
	TAction *acEdit;
	TPopupMenu *PopupMenu;
	TMenuItem *Erkrankunghinzufgen1;
	TMenuItem *Erkrankungndern1;
	TMenuItem *Erkrankunglschen1;
	TTimer *tStartup;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acFilterExecute(TObject *Sender);
	void __fastcall acAddExecute(TObject *Sender);
	void __fastcall acDelExecute(TObject *Sender);
	void __fastcall acEditExecute(TObject *Sender);
	void __fastcall lvDataClick(TObject *Sender);
	void __fastcall edIdVonExit(TObject *Sender);
	void __fastcall edBezChange(TObject *Sender);
	void __fastcall lvDataDblClick(TObject *Sender);

public:
	__fastcall TfmBaseDesc(TComponent* Owner, TWinControl* Container,cMySqlDescDb& desc);
	__fastcall ~TfmBaseDesc();

	void		LockFilter();
	void		DislockFilter();

	bool		ShowData();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmBaseDesc *fmBaseDesc;
TfmBaseDesc* CreateDescForm(TForm* caller, TWinControl* container, cMySqlDescDb& desc);
//---------------------------------------------------------------------------
#endif
