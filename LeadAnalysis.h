//---------------------------------------------------------------------------
#ifndef LeadAnalysisH
#define LeadAnalysisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "basics/classTools.h"
#include "basics/classData.h"
#include "ecg/classEcg.h"
//---------------------------------------------------------------------------
class TfmLeads : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TBevel *Bevel1;
	TImage *iLead1;
	TImage *iLead2;
	TImage *iLead3;
	TImage *iLead4;
	TImage *iLead5;
	TImage *iLead6;
	TTimer *tStartup;
	TImage *iLead7;
	TImage *iLead8;
	TLabel *laInfo;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);

private:
	cTools		ftools;
	cEcg		fecg;
	cData		fdata1;
	cData		fdata2;
	cData		fdata3;
	cData		fdata4;
	cData		fdata5;
	cData		fdata6;
	cData		fdata7;
	cData		fdata8;

	String 		fEcgFile;
	String		fBez;

	void 		snapTo(TWinControl* container, TAlign align);
	bool 		GetLeads();

public:
	__fastcall TfmLeads(TComponent* Owner, TWinControl* Container);
	bool 		Execute(String ecgfile, String bez);
	bool		setEcg(String ecgfile, String bez);

};
//---------------------------------------------------------------------------
extern PACKAGE TfmLeads *fmLeads;
bool DlgShowLeads(TForm* Papa, String ecgfile, String bez);
TfmLeads* CreateLeadForm(TForm* caller, TWinControl* container);
//---------------------------------------------------------------------------
#endif
