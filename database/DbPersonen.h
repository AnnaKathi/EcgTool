//---------------------------------------------------------------------------
#ifndef DbPersonenH
#define DbPersonenH
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
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "baseforms/baseDiseases.h"
//---------------------------------------------------------------------------
struct sFilterEcg
	{
	int			identVon;
	int			identBis;
	String		name;
	ePosition   pos;
	double		wertVon;
	double		wertBis;
	};
//---------------------------------------------------------------------------
struct sFilterPeople
	{
	int			identVon;
	int			identBis;
	String		name;
	};
//---------------------------------------------------------------------------
class TfmData : public TForm
{
private:
	TIniFile*		Ini;
	cTools			ftools;

	sFilterEcg		ffecg;
	sFilterPeople 	ffpeople;

    TfmBaseDiseases*	fmDiseases;

	inline void StartJob(int max);
	inline void TickJob(int tick = 1);
	inline void EndJob();

	void		ShowPeople();

	void 		ShowEcgData();
	void		ShowEcgOf(int person);


	bool		bFilter;
	bool		BuildEcgFilter();
	bool		BuildPeopleFilter();
	bool		CheckEcgFilter();
	bool		CheckPeopleFilter();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TTimer *tStartup;
	TPanel *Panel1;
	TButton *btClose;
	TActionList *ActionList;
	TAction *acClose;
	TAction *acRefresh;
	TProgressBar *pbJob;
	TBevel *Bevel1;
	TPopupMenu *PopupMenuEcgData;
	TPanel *pnPeople;
	TSplitter *Splitter1;
	TPanel *pnEcgData;
	TPanel *pnFilter;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edIdVon;
	TEdit *edIdBis;
	TEdit *edEcgName;
	TComboBox *cbPosition;
	TBevel *Bevel2;
	TListView *lvData;
	TPanel *Panel2;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *edPeopleIdVon;
	TEdit *edPeopleIdBis;
	TEdit *edPeopleName;
	TBevel *Bevel3;
	TListView *lvPeople;
	TPopupMenu *PopupMenuPeople;
	TMenuItem *MenuItem1;
	TActionList *ActionListPeople;
	TAction *acPeopleDel;
	TAction *acPeopleAdd;
	TActionList *ActionListEcgData;
	TAction *acEcgAdd;
	TAction *acEcgDel;
	TMenuItem *Peronhinzufgen1;
	TAction *acPeopleSelect;
	TAction *acPeopleDisselect;
	TMenuItem *N1;
	TMenuItem *Personauswhlen1;
	TMenuItem *Auswahlaufheben1;
	TAction *acPeopleFilter;
	TAction *acEcgFilter;
	TPanel *pnDiseases;
	TSplitter *Splitter2;
	TLabel *Label14;
	TLabel *Label16;
	TAction *acPeopleChange;
	TMenuItem *Personndern1;
	TMenuItem *EkgDatensatzlschen1;
	TPanel *Panel5;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acRefreshExecute(TObject *Sender);
	void __fastcall edIdVonKeyPress(TObject *Sender, char &Key);
	void __fastcall edIdVonExit(TObject *Sender);
	void __fastcall edEcgNameChange(TObject *Sender);
	void __fastcall cbPositionChange(TObject *Sender);
	void __fastcall lvDataClick(TObject *Sender);
	void __fastcall lvPeopleClick(TObject *Sender);
	void __fastcall acPeopleDelExecute(TObject *Sender);
	void __fastcall acPeopleAddExecute(TObject *Sender);
	void __fastcall acEcgDelExecute(TObject *Sender);
	void __fastcall acEcgAddExecute(TObject *Sender);
	void __fastcall lvPeopleDblClick(TObject *Sender);
	void __fastcall acPeopleSelectExecute(TObject *Sender);
	void __fastcall acPeopleDisselectExecute(TObject *Sender);
	void __fastcall edPeopleNameChange(TObject *Sender);
	void __fastcall edPeopleNameExit(TObject *Sender);
	void __fastcall edPeopleNameKeyPress(TObject *Sender, char &Key);
	void __fastcall acPeopleFilterExecute(TObject *Sender);
	void __fastcall acEcgFilterExecute(TObject *Sender);
	void __fastcall acDisSelectExecute(TObject *Sender);
	void __fastcall acPeopleChangeExecute(TObject *Sender);

public:
	__fastcall TfmData(TComponent* Owner);
	__fastcall TfmData::~TfmData();
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmData *fmData;
bool DlgDatabasePersonen(TForm* Papa);
//---------------------------------------------------------------------------
#endif
