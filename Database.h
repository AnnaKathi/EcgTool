//---------------------------------------------------------------------------
#ifndef DatabaseH
#define DatabaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <IniFiles.hpp>
#include <System.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "data/classMySql.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
struct sFilter
	{
	int			identVon;
	int			identBis;
	String		name;
	ePosition   pos;
	double		wertVon;
	double		wertBis;
	};
//---------------------------------------------------------------------------
class TfmData : public TForm
{
private:
	TIniFile*	Ini;
	cTools		ftools;
	cMySql		fmysql;
	sFilter		ffilter;

	inline void StartJob(int max);
	inline void TickJob(int tick = 1);
	inline void EndJob();

	bool		bShowEcgData;
	void 		ShowEcgData();

	bool		bFilter;
	bool		BuildFilter();
	bool		CheckFilter(sMySqlRow row);

	void		CreateTestdata();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TTimer *tStartup;
	TPanel *Panel1;
	TButton *btClose;
	TListView *lvData;
	TButton *Button1;
	TActionList *ActionList;
	TAction *acClose;
	TAction *acRefresh;
	TProgressBar *pbJob;
	TPanel *pnFilter;
	TBevel *Bevel1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edIdVon;
	TLabel *Label3;
	TEdit *edIdBis;
	TAction *acFilter;
	TLabel *Label4;
	TEdit *edName;
	TLabel *Label5;
	TComboBox *cbPosition;
	TButton *btCreateTestData;
	TPopupMenu *PopupMenu;
	TAction *acDelete;
	TMenuItem *Datensatzlschen1;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acRefreshExecute(TObject *Sender);
	void __fastcall edIdVonKeyPress(TObject *Sender, char &Key);
	void __fastcall acFilterExecute(TObject *Sender);
	void __fastcall edIdVonExit(TObject *Sender);
	void __fastcall edNameChange(TObject *Sender);
	void __fastcall cbPositionChange(TObject *Sender);
	void __fastcall btCreateTestDataClick(TObject *Sender);
	void __fastcall acDeleteExecute(TObject *Sender);
	void __fastcall lvDataClick(TObject *Sender);

public:
	__fastcall TfmData(TComponent* Owner);
	__fastcall TfmData::~TfmData();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmData *fmData;
bool DlgDatabase(TForm* Papa);
//---------------------------------------------------------------------------
#endif
