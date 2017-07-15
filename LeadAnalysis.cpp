//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LeadAnalysis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmLeads *fmLeads;
//---------------------------------------------------------------------------
bool DlgShowLeads(TForm* Papa, int ansicht)
	{
	TfmLeads* Form = new TfmLeads(Papa, NULL, ansicht);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(ansicht);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmLeads::Execute(int ansicht)
	{
	bLoaded  = false;
	iAnsicht = ansicht;
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TfmLeads* CreateLeadForm(TForm* caller, TWinControl* container, int ansicht)
	{
	return new TfmLeads(caller, container, ansicht);
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TfmLeads::TfmLeads(TComponent* Owner, TWinControl* Container, int ansicht)
	: TForm(Owner)
	{
	iAnsicht = ansicht;
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
	laInfo->Caption = "...Datei auswählen...";
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
void TfmLeads::RefreshView(int ansicht)
	{
	iAnsicht = ansicht;
	if (bLoaded)
    	ShowLeads();
	}
//---------------------------------------------------------------------------
bool TfmLeads::GetLeads(String file)
	{
	if (!fdata1.getFile(file, formatADS, "\t", 1, 0, 3000)) return false;
	if (!fdata1.buildDerivates()) return false;

	if (!fdata2.getFile(file, formatADS, "\t", 2, 0, 3000)) return false;
	if (!fdata2.buildDerivates()) return false;

	if (!fdata3.getFile(file, formatADS, "\t", 3, 0, 3000)) return false;
	if (!fdata3.buildDerivates()) return false;

	if (!fdata4.getFile(file, formatADS, "\t", 4, 0, 3000)) return false;
	if (!fdata4.buildDerivates()) return false;

	if (!fdata5.getFile(file, formatADS, "\t", 5, 0, 3000)) return false;
	if (!fdata5.buildDerivates()) return false;

	if (!fdata6.getFile(file, formatADS, "\t", 6, 0, 3000)) return false;
	if (!fdata6.buildDerivates()) return false;

	if (!fdata7.getFile(file, formatADS, "\t", 7, 0, 3000)) return false;
	if (!fdata7.buildDerivates()) return false;

	if (!fdata8.getFile(file, formatADS, "\t", 8, 0, 3000)) return false;
	if (!fdata8.buildDerivates()) return false;

	if (!fabl12.getFile(file, formatADS, "\t", 9, 0, 3000)) return false;
	if (!fabl12.buildDerivates()) return false;

	if (!fabl34.getFile(file, formatADS, "\t",10, 0, 3000)) return false;
	if (!fabl34.buildDerivates()) return false;

	if (!fabl56.getFile(file, formatADS, "\t",11, 0, 3000)) return false;
	if (!fabl56.buildDerivates()) return false;

	bLoaded = true;
	ShowLeads();
	return true;
	}
//---------------------------------------------------------------------------
bool TfmLeads::ShowLeads()
	{
	if (!ShowData(fdata1, iLead1)) return false;
	if (!ShowData(fdata2, iLead2)) return false;
	if (!ShowData(fdata3, iLead3)) return false;
	if (!ShowData(fdata4, iLead4)) return false;
	if (!ShowData(fdata5, iLead5)) return false;
	if (!ShowData(fdata6, iLead6)) return false;
	if (!ShowData(fdata7, iLead7)) return false;
	if (!ShowData(fdata8, iLead8)) return false;
	if (!ShowData(fabl12, iAbl12)) return false;
	if (!ShowData(fabl34, iAbl34)) return false;
	if (!ShowData(fabl56, iAbl56)) return false;
    return true;
	}
//---------------------------------------------------------------------------
bool TfmLeads::ShowData(cData data, TImage* img)
	{
	if (iAnsicht == 1) //Originaldaten
		{
		data.redisplay(img);
		return true;
		}
	else if (iAnsicht == 2) //1. Ableitung
		{
		//if (!data.buildDerivates()) return false;

		int n = data.derivate1.deriv_array.size();
		data.derivate1.redisplay(img);
		return true;
		}
	else if (iAnsicht == 3) //2. Ableitung
		{
		//if (!data.buildDerivates()) return false;
		data.derivate2.redisplay(img);
		return true;
		}
	else
		return false;
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
void __fastcall TfmLeads::laInfoClick(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	char file[MAX_PATH];
	sprintf(file, "%s", OpenDialog->FileName.c_str());
	char* pt = strrchr(file, '\\');
	if (pt) *pt = 0;
	sprintf(file, "%s", pt+1);
	laInfo->Caption = file;
	laInfo->Hint = OpenDialog->FileName;
	GetLeads(OpenDialog->FileName);
	}
//---------------------------------------------------------------------------

