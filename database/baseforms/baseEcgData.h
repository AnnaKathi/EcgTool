//---------------------------------------------------------------------------
#ifndef baseEcgDataH
#define baseEcgDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "../../basics/classTools.h"
//---------------------------------------------------------------------------
struct sFilterEcg
	{
	int			identVon;
	int			identBis;
	int			session;
	int			ort;
	String		name;
	ePosition	position;
	eState		state;
	eLage   	lage;
	double		wertVon;
	double		wertBis;
	};
//---------------------------------------------------------------------------
class TfmBaseEcg : public TForm
{
private:
	cTools		ftools;
	void 		snapTo(TWinControl* container, TAlign align);

	bool		bInShow;

	sFilterEcg  ffilter;
	void 		AddLine();
	bool 		BuildFilter();
	bool 		CheckFilter();

	bool		bSelectEcg;
	int			iSelectedEcg;
	TTimer*		CallbackSelected;


__published:	// IDE-verwaltete Komponenten
	TActionList *ActionListDiseases;
	TAction *acFilter;
	TAction *acAdd;
	TAction *acDel;
	TPopupMenu *PopupMenuDiseases;
	TTimer *tStartup;
	TAction *acChange;
	TMenuItem *Erkrankunghinzufgen1;
	TMenuItem *Erkrankungndern1;
	TMenuItem *Erkrankunglschen1;
	TListView *lvData;
	TPanel *pnFilter;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edIdVon;
	TEdit *edIdBis;
	TEdit *edName;
	TComboBox *cbLage;
	TBevel *Bevel1;
	TLabel *laTabelle;
	TComboBox *cbPosition;
	TLabel *Label1;
	TComboBox *cbState;
	TLabel *Label2;
	TComboBox *cbSession;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *cbOrt;
	TLabel *laAuswahl;
	void __fastcall acAddExecute(TObject *Sender);
	void __fastcall acDelExecute(TObject *Sender);
	void __fastcall acFilterExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acChangeExecute(TObject *Sender);
	void __fastcall lvDataClick(TObject *Sender);
	void __fastcall edIdVonExit(TObject *Sender);
	void __fastcall edNameChange(TObject *Sender);
	void __fastcall lvDataDblClick(TObject *Sender);
	void __fastcall cbLageChange(TObject *Sender);

public:
	__fastcall TfmBaseEcg(TComponent* Owner, TWinControl* Container, TColor color);

	void		LockFilter();
	void		DislockFilter();
	bool		ShowData();
	bool		ShowEcgOf(int person);
	void		SelectEcg(TTimer* timer);
	int			GetSelectedEcg();
	String		GetListedEcg();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmBaseEcg *fmBaseEcg;
TfmBaseEcg* CreateEcgForm(TForm* caller, TWinControl* container);
//---------------------------------------------------------------------------
#endif
