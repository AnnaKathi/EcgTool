//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LeadAnalysis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmLeads *fmLeads;
//---------------------------------------------------------------------------
bool DlgShowLeads(TForm* Papa, String ecgfile, String bez)
	{
	if (ecgfile == "") return false;
	if (!FileExists(ecgfile)) return false;

	TfmLeads* Form = new TfmLeads(Papa, NULL);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(ecgfile, bez);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmLeads::Execute(String ecgfile, String bez)
	{
	fEcgFile = ecgfile;
	fBez = bez;
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TfmLeads* CreateLeadForm(TForm* caller, TWinControl* container)
	{
	return new TfmLeads(caller, container);
	}
//---------------------------------------------------------------------------
void TfmLeads::snapTo(TWinControl* container, TAlign align)
	{
	int realHeight = ClientHeight;
	int realWidth  = ClientWidth;

	Parent  = container;
	Hint    = Caption;
	Caption = "";
	Left    = 0;
	Top     = 0;
	if (align != alNone) Align = align;
	BorderIcons = TBorderIcons();
	BorderStyle = bsNone;

	ParentFont  = true;
	ParentColor = true;

	Height = realHeight;
	Width  = realWidth;
	}
//---------------------------------------------------------------------------
bool TfmLeads::setEcg(String ecgfile, String bez)
	{
	if (ecgfile == "") return false;
	if (!FileExists(ecgfile)) return false;

	fEcgFile = ecgfile;
	fBez = bez;
	return true;
	}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TfmLeads::TfmLeads(TComponent* Owner, TWinControl* Container)
	: TForm(Owner)
	{
	if (Container)
		snapTo(Container, alClient);
	}
//---------------------------------------------------------------------------
void __fastcall TfmLeads::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmLeads::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	laInfo->Caption = ftools.fmt("EKG <%s>, Lead 1-8", fBez);
	
	GetLeads();
	}
//---------------------------------------------------------------------------
void __fastcall TfmLeads::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmLeads::GetLeads()
	{
	if (!fdata1.getFile(fEcgFile, formatADS, "\t", 0, 0, 3000)) return false;
	else fdata1.redisplay(iLead1);

	if (!fdata2.getFile(fEcgFile, formatADS, "\t", 1, 0, 3000)) return false;
	else fdata2.redisplay(iLead2);

	if (!fdata3.getFile(fEcgFile, formatADS, "\t", 2, 0, 3000)) return false;
	else fdata3.redisplay(iLead3);

	if (!fdata4.getFile(fEcgFile, formatADS, "\t", 3, 0, 3000)) return false;
	else fdata4.redisplay(iLead4);

	if (!fdata5.getFile(fEcgFile, formatADS, "\t", 4, 0, 3000)) return false;
	else fdata5.redisplay(iLead5);

	if (!fdata6.getFile(fEcgFile, formatADS, "\t", 5, 0, 3000)) return false;
	else fdata6.redisplay(iLead6);

	if (!fdata7.getFile(fEcgFile, formatADS, "\t", 6, 0, 3000)) return false;
	else fdata7.redisplay(iLead7);

	if (!fdata8.getFile(fEcgFile, formatADS, "\t", 7, 0, 3000)) return false;
	else fdata8.redisplay(iLead8);

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmLeads::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
