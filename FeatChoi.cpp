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
	laEcg2->Visible = false;
	cbLead1->ItemIndex = 1;
	cbLead2->ItemIndex = 1;
	mFeatO1->Lines->Clear(); mFeatA1->Lines->Clear();
	mFeatO2->Lines->Clear(); mFeatA2->Lines->Clear();
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

	if (!fecg1.data.getFile(laEcg1->Caption, formatADS, "\t", cbLead1->ItemIndex+1, 0, 3000))
		; //todo

	//Originaldaten
	fecg1.data.redisplay(imgEcg1);

	//Ableitungen
	if (!fecg1.data.buildDerivates()) ; //todo

	//Standardherzschlag normal
	iarray_t heart = fecg1.heart.calcAvBeat(fecg1.data.data_array);
	farray.redisplay(heart, iHeartEcg1);

	//Standardherzschlag auf 1. Ableitung
	iarray_t abl = fmath.calcDerivate(fecg1.data.data_array);
	iarray_t heartabl = fecg1.heart.calcAvBeat(abl);
	farray.redisplay(heartabl, iHeAblEcg1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btLoadEkg2Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	laEcg2->Caption = OpenDialog->FileName;

	if (!fecg2.data.getFile(laEcg2->Caption, formatADS, "\t", cbLead2->ItemIndex+2, 0, 3000))
		; //todo

	//Originaldaten
	fecg2.data.redisplay(imgEcg2);

	//Ableitungen
	if (!fecg2.data.buildDerivates()) ; //todo

	//Standardherzschlag normal
	iarray_t heart = fecg2.heart.calcAvBeat(fecg2.data.data_array);
	farray.redisplay(heart, iHeartEcg2);

	//Standardherzschlag auf 2. Ableitung
	iarray_t abl = fmath.calcDerivate(fecg2.data.data_array);
	iarray_t heartabl = fecg2.heart.calcAvBeat(abl);
	farray.redisplay(heartabl, iHeAblEcg2);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::cbLead1Change(TObject *Sender)
	{
	if (!fecg1.data.getFile(laEcg1->Caption, formatADS, "\t", cbLead1->ItemIndex+1, 0, 3000))
		; //todo

	fecg1.data.redisplay(imgEcg1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::cbLead2Change(TObject *Sender)
	{
	if (!fecg2.data.getFile(laEcg2->Caption, formatADS, "\t", cbLead2->ItemIndex+1, 0, 3000))
		; //todo

	fecg2.data.redisplay(imgEcg2);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btFeat1Click(TObject *Sender)
	{
	iarray_t ro = fecg1.rpeaks.find(fecg1.data.data_array, NULL);
	if (ro.size() <= 0) ; //todo
	if (!fFeatChoi.getFeatures(fecg1.data.data_array, ro))
		; //todo

	mFeatO1->Lines->Add(fFeatChoi.features_string);

	iarray_t ra = fecg1.rpeaks.find(fecg1.data.derivate1.deriv_array, NULL);
	if (ra.size() <= 0) ; //todo
	if (!fFeatChoi.getFeatures(fecg1.data.derivate1.deriv_array, ra))
		; //todo

	mFeatA1->Lines->Add(fFeatChoi.features_string);
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btFeat2Click(TObject *Sender)
	{
	iarray_t ro = fecg2.rpeaks.find(fecg2.data.data_array, NULL);
	if (ro.size() <= 0) ; //todo
	if (!fFeatChoi.getFeatures(fecg2.data.data_array, ro))
		; //todo

	mFeatO2->Lines->Add(fFeatChoi.features_string);

	iarray_t ra = fecg2.rpeaks.find(fecg2.data.derivate2.deriv_array, NULL);
	if (ra.size() <= 0) ; //todo
	if (!fFeatChoi.getFeatures(fecg2.data.derivate2.deriv_array, ra))
		; //todo

	mFeatA2->Lines->Add(fFeatChoi.features_string);
	}
//---------------------------------------------------------------------------

