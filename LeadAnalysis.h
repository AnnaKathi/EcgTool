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
#include <Dialogs.hpp>
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
	TImage *iAbl12;
	TImage *iAbl34;
	TImage *iAbl56;
	TOpenDialog *OpenDialog;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall laInfoClick(TObject *Sender);

private:
	int			iAnsicht;
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

	cData		fabl12;
	cData		fabl34;
	cData		fabl56;

	bool		bLoaded;

	void 		snapTo(TWinControl* container, TAlign align);
	bool 		GetLeads(String file);
	bool 		ShowLeads();
	bool 		ShowData(cData data, TImage* img);

public:
	__fastcall TfmLeads(TComponent* Owner, TWinControl* Container, int ansicht);
	bool 		Execute(int ansicht);
	void		RefreshView(int ansicht);

};
//---------------------------------------------------------------------------
extern PACKAGE TfmLeads *fmLeads;
bool DlgShowLeads(TForm* Papa, int ansicht);
TfmLeads* CreateLeadForm(TForm* caller, TWinControl* container, int ansicht);
//---------------------------------------------------------------------------
#endif
