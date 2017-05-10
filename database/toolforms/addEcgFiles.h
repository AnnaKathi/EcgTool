//---------------------------------------------------------------------------
#ifndef addEcgFilesH
#define addEcgFilesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "../../definitions.h"
#include "../../ecg/classEcg.h"
//---------------------------------------------------------------------------
class TfmEcgFiles : public TForm
{
private:
	cEcg			fecg;

	int				fRow;
	TTimer*			fCallbackTimer;

	eDatFormat 		fFormat;
	String			fDelim;

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *pnBottom;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel2;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TAction *acAdd;
	TAction *acDel;
	TPanel *pnData;
	TLabel *Label2;
	TComboBox *cbPosition;
	TBevel *Bevel3;
	TListView *lvEcg;
	TPopupMenu *PopupMenu;
	TMenuItem *EKGhinzufgen1;
	TMenuItem *EKGlschen1;
	TAction *acEnd;
	TOpenDialog *OpenDialog;
	TLabel *Label1;
	TComboBox *cbFormat;
	TComboBox *cbDelim;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acAddExecute(TObject *Sender);
	void __fastcall acDelExecute(TObject *Sender);
	void __fastcall acEndExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	
public:
	__fastcall TfmEcgFiles(TComponent* Owner);
	bool 		Execute();

	bool		SetCallbackTimer(TTimer* timer);
	bool		GetHeader(int& pos);
	bool		GetNextEcg(int& anz, String& file);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmEcgFiles *fmEcgFiles;
bool DlgAddEcgFiles(TForm* Papa);
//---------------------------------------------------------------------------
#endif
