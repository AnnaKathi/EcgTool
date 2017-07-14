//---------------------------------------------------------------------------
#ifndef EcgLeadAnalysisH
#define EcgLeadAnalysisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "LeadAnalysis.h"
#include "basics/classTools.h"
//---------------------------------------------------------------------------
class TfmEcgLeads : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TBevel *Bevel1;
	TTimer *tStartup;
	TPanel *pnEcg1;
	TBevel *Bevel2;
	TPanel *pnEcg2;
	TBevel *Bevel3;
	TPanel *pnEcg3;
	TBevel *Bevel4;
	TPanel *pnEcg4;
	TBevel *Bevel5;
	TPanel *Panel1;
	TBevel *Bevel6;
	TLabel *Label1;
	TComboBox *cbAnsicht;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall cbAnsichtChange(TObject *Sender);

private:
	cTools		ftools;

	TfmLeads*	fmLeads1;
	TfmLeads*	fmLeads2;
	TfmLeads*	fmLeads3;
	TfmLeads*	fmLeads4;


public:
	__fastcall TfmEcgLeads(TComponent* Owner);
	bool 		Execute();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmEcgLeads *fmEcgLeads;
bool DlgShowEcgLeads(TForm* Papa);
//---------------------------------------------------------------------------
#endif
