//---------------------------------------------------------------------------
#ifndef basePeopleH
#define basePeopleH
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
struct sFilterPeople
	{
	int			identVon;
	int			identBis;
	String		name;
	};
//---------------------------------------------------------------------------
class TfmBasePeople : public TForm
{
private:
	TTimer*		tCallback;
	bool		bSelected;
	
	void 		snapTo(TWinControl* container, TAlign align);
	void 		MsgBox(char* msg, ...);

	bool		bInShow;

	sFilterPeople     ffilter;
	bool 		BuildFilter();
	bool 		CheckFilter();


__published:	// IDE-verwaltete Komponenten
	TBevel *Bevel4;
	TPanel *pnFilter;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edIdVon;
	TEdit *edIdBis;
	TEdit *edName;
	TActionList *ActionListDiseases;
	TAction *acFilter;
	TAction *acAdd;
	TAction *acDel;
	TPopupMenu *PopupMenu;
	TTimer *tStartup;
	TAction *acChange;
	TMenuItem *Erkrankunghinzufgen1;
	TMenuItem *Erkrankungndern1;
	TMenuItem *Erkrankunglschen1;
	TListView *lvPeople;
	TAction *acSelect;
	TMenuItem *N1;
	TMenuItem *Personauswhlen1;
	void __fastcall acAddExecute(TObject *Sender);
	void __fastcall acDelExecute(TObject *Sender);
	void __fastcall acFilterExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acChangeExecute(TObject *Sender);
	void __fastcall lvPeopleClick(TObject *Sender);
	void __fastcall edIdVonExit(TObject *Sender);
	void __fastcall edNameChange(TObject *Sender);
	void __fastcall lvPeopleDblClick(TObject *Sender);
	void __fastcall acSelectExecute(TObject *Sender);

public:
	__fastcall TfmBasePeople(TComponent* Owner, TWinControl* Container, TColor color);

	int			iPerson;
	bool		setCallback(TTimer& timer);
	
	bool		ShowData();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmBasePeople *fmBasePeople;
TfmBasePeople* CreatePeopleForm(TForm* caller, TWinControl* container);
//---------------------------------------------------------------------------
#endif
