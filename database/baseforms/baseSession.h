//---------------------------------------------------------------------------
#ifndef baseSessionH
#define baseSessionH
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
//---------------------------------------------------------------------------
struct sFilterSession
	{
	int			identVon;
	int			identBis;
	int			ort;
	String		kommentar;
	};
//---------------------------------------------------------------------------
class TfmBaseSession : public TForm
{
private:
	cTools		ftools;
	TTimer*		tCallback;
	bool		bSelected;
	
	void 		snapTo(TWinControl* container, TAlign align);

	bool		bInShow;

	sFilterSession ffilter;
	bool 		BuildFilter();
	bool 		CheckFilter();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnFilter;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edIdVon;
	TEdit *edIdBis;
	TEdit *edKommentar;
	TBevel *Bevel4;
	TActionList *ActionListDiseases;
	TAction *acFilter;
	TAction *acAdd;
	TAction *acDel;
	TAction *acChange;
	TAction *acSelect;
	TPopupMenu *PopupMenu;
	TMenuItem *Erkrankunghinzufgen1;
	TMenuItem *Erkrankungndern1;
	TMenuItem *Erkrankunglschen1;
	TMenuItem *N1;
	TMenuItem *Personauswhlen1;
	TTimer *tStartup;
	TListView *lvSession;
	TLabel *Label1;
	TComboBox *cbOrt;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall acFilterExecute(TObject *Sender);
	void __fastcall acAddExecute(TObject *Sender);
	void __fastcall acDelExecute(TObject *Sender);
	void __fastcall acChangeExecute(TObject *Sender);
	void __fastcall acSelectExecute(TObject *Sender);
	void __fastcall lvSessionClick(TObject *Sender);
	void __fastcall edIdVonExit(TObject *Sender);
	void __fastcall lvSessionDblClick(TObject *Sender);

public:
	__fastcall TfmBaseSession(TComponent* Owner, TWinControl* Container);

	int			iSession;
	bool		setCallback(TTimer& timer);
	bool		ShowData();

};
//---------------------------------------------------------------------------
extern PACKAGE TfmBaseSession *fmBaseSession;
TfmBaseSession* CreateSessionForm(TForm* caller, TWinControl* container);
//---------------------------------------------------------------------------
#endif
