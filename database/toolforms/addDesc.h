//---------------------------------------------------------------------------
#ifndef addDescH
#define addDescH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "../classMySql_DescDb.h"
//---------------------------------------------------------------------------
class TfmDescAdd : public TForm
{
private:
	cMySqlDescDb*	fdesc;
	
	bool		bNewData;
	int			iData;

	void 		MsgBox(char* msg, ...);

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel2;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TAction *acSave;
	TLabel *Label1;
	TEdit *edIdent;
	TLabel *Label2;
	TEdit *edBez;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acSaveExecute(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall edBezKeyPress(TObject *Sender, char &Key);

public:
	__fastcall TfmDescAdd(TComponent* Owner);
	bool 	Execute(int ident, cMySqlDescDb& desc);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmDescAdd *fmDescAdd;
bool DlgDescDbAdd(TForm* Papa, cMySqlDescDb& desc);
bool DlgDescDbEdit(TForm* Papa, int ident, cMySqlDescDb& desc);
//---------------------------------------------------------------------------
#endif
