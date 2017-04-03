//---------------------------------------------------------------------------
#ifndef baseDiseasesH
#define baseDiseasesH
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
#include "../classMySql.h"
//---------------------------------------------------------------------------
class TfmBaseDiseases : public TForm
{
private:
	void 		snapTo(TWinControl* container, TAlign align);

	cMySql*		fmysql;

	void 		MsgBox(char* msg, ...);


__published:	// IDE-verwaltete Komponenten
	TListView *lvDiseases;
	TBevel *Bevel4;
	TPanel *Panel4;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edDisIdVon;
	TEdit *edDisIdBis;
	TEdit *edDisName;
	TActionList *ActionListDiseases;
	TAction *acDisFilter;
	TAction *acDisAdd;
	TAction *acDisDel;
	TPopupMenu *PopupMenuDiseases;
	TTimer *tStartup;
	void __fastcall acDisAddExecute(TObject *Sender);
	void __fastcall acDisDelExecute(TObject *Sender);
	void __fastcall acDisFilterExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);

public:
	__fastcall TfmBaseDiseases(TComponent* Owner, TWinControl* Container, cMySql& Mysql);

	bool		ShowData();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmBaseDiseases *fmBaseDiseases;
bool CreateDiseaseForm(TForm* caller, TWinControl* container, cMySql& mysql);
//---------------------------------------------------------------------------
#endif
