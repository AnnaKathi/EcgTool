//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
private:
	cTools		ftools;

	bool		bNoMySql;
	bool		setupDatabase();
	
	void		setStatus(String status, int panel=0);
	void		setDbInfo();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TMainMenu *MainMenu;
	TMenuItem *ools1;
	TMenuItem *EKGuntersuchen1;
	TTimer *tStartup;
	TStatusBar *sbMain;
	TPanel *pnMain;
	TBitBtn *btAnalysis;
	TPopupMenu *PopupMenuAnalysis;
	TActionList *ActionListAnalysis;
	TAction *acAnalyseEcg;
	TMenuItem *EKGSignalanalysieren1;
	TBitBtn *btAnalysisSelect;
	TBitBtn *BitBtn8;
	TBitBtn *btDatabaseSelect;
	TActionList *ActionListDatabase;
	TAction *acDatabaseAll;
	TAction *acDatabasePeople;
	TPopupMenu *PopupMenuDatabase;
	TMenuItem *Allgbersicht1;
	TMenuItem *N1;
	TMenuItem *Personen1;
	TBitBtn *btSessions;
	TBitBtn *btSessionsSelect;
	TActionList *ActionList2;
	TAction *acSessionAdd;
	TPopupMenu *PopupMenuSessions;
	TMenuItem *Sessionanlegen1;
	TBitBtn *btFeatures;
	TBitBtn *btFeaturesSelect;
	TActionList *ActionListFeatures;
	TAction *acFeaturesShow;
	TAction *acFeaturesBuildAll;
	TAction *acFeaturesChoi;
	TAction *acFeaturesRandom;
	TPopupMenu *PopupMenuFeatures;
	TMenuItem *Featuresanzeigen1;
	TMenuItem *N2;
	TMenuItem *AllFeaturesbilden1;
	TMenuItem *N3;
	TMenuItem *FeaturesChoibilden1;
	TMenuItem *FeaturesRandomPointsbilden1;
	TBitBtn *btClassify;
	TBitBtn *btClassifySelect;
	TActionList *ActionListClassification;
	TAction *acClassifyAll;
	TAction *acClassifySvm;
	TPopupMenu *PopupMenuClassify;
	TMenuItem *VergleichallerKlassifizierungen1;
	TMenuItem *N4;
	TMenuItem *KlassifizierungChoiSVM1;
	TActionList *ActionListGeneral;
	TAction *acClose;
	TMenuItem *Datenanalyse1;
	TMenuItem *EKGSignalanalysieren2;
	TMenuItem *Datenbank1;
	TMenuItem *Allgbersicht2;
	TMenuItem *Personen2;
	TMenuItem *Session1;
	TMenuItem *Sessionanlegen2;
	TMenuItem *Features1;
	TMenuItem *Featuresanzeigen2;
	TMenuItem *AlleFeaturesbilden1;
	TMenuItem *FeaturesChoibilden2;
	TMenuItem *FeaturesRandomPointsbilden2;
	TMenuItem *N5;
	TMenuItem *Klassifizierung1;
	TMenuItem *VergleichallerKlassifizierungen2;
	TMenuItem *KlassifizierungChoiSVM2;
	TMenuItem *N6;
	TAction *acTest;
	TMenuItem *N7;
	TMenuItem *PreTestTool1;
	TAction *acSessionWizard;
	TMenuItem *SessionWizard1;
	TMenuItem *SessionWizard2;
	TButton *btLKeadAnalysis;
	TButton *btEcgAnalysis;
	TButton *btWavelib;
	TAction *acImportEdan;
	TMenuItem *EdanDatenstzeimportieren1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall btAnalysisSelectClick(TObject *Sender);
	void __fastcall acAnalyseEcgExecute(TObject *Sender);
	void __fastcall acDatabaseAllExecute(TObject *Sender);
	void __fastcall acDatabasePeopleExecute(TObject *Sender);
	void __fastcall acSessionAddExecute(TObject *Sender);
	void __fastcall acFeaturesShowExecute(TObject *Sender);
	void __fastcall acFeaturesBuildAllExecute(TObject *Sender);
	void __fastcall acFeaturesChoiExecute(TObject *Sender);
	void __fastcall acFeaturesRandomExecute(TObject *Sender);
	void __fastcall acClassifyAllExecute(TObject *Sender);
	void __fastcall acClassifySvmExecute(TObject *Sender);
	void __fastcall acTestExecute(TObject *Sender);
	void __fastcall acSessionWizardExecute(TObject *Sender);
	void __fastcall btLKeadAnalysisClick(TObject *Sender);
	void __fastcall btEcgAnalysisClick(TObject *Sender);
	void __fastcall btWavelibClick(TObject *Sender);
	void __fastcall acImportEdanExecute(TObject *Sender);

public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
