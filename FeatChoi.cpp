//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FeatChoi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmFeatChoi *fmFeatChoi;
//---------------------------------------------------------------------------
bool DlgShowVglChoi(TForm* Papa)
	{
	TfmFeatChoi* Form = new TfmFeatChoi(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmFeatChoi::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmFeatChoi::TfmFeatChoi(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::FormShow(TObject *Sender)
	{
	laEcg1->Visible = false;
	cbLead1->ItemIndex = 1;
	mFeat1->Lines->Clear();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btLoadEkg1Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	laEcg1->Caption = OpenDialog->FileName;

	if (!fecg.data.getFile(laEcg1->Caption, formatADS, "\t", cbLead1->ItemIndex+1, 0, 3000))
		; //todo

	fecg.data.redisplay(imgEcg1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::cbLead1Change(TObject *Sender)
	{
	if (!fecg.data.getFile(laEcg1->Caption, formatADS, "\t", cbLead1->ItemIndex+1, 0, 3000))
		; //todo

	fecg.data.redisplay(imgEcg1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btFeat1Click(TObject *Sender)
	{
	iarray_t rr = fecg.rpeaks.find(fecg.data.data_array, NULL);
	int n = rr.size();

	if (!fFeatChoi.getFeatures(fecg.data.data_array, fecg.rpeaks.rpeaks))
		; //todo

	mFeat1->Lines->Add(fFeatChoi.features_string);
	}
//---------------------------------------------------------------------------

