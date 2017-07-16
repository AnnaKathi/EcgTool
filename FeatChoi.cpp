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
	laEcg3->Visible = false;
	cbLead1->ItemIndex = 1;
	cbLead2->ItemIndex = 1;
	cbLead3->ItemIndex = 1;
	mFeatO1->Lines->Clear(); mFeatA1->Lines->Clear();
	mFeatO2->Lines->Clear(); mFeatA2->Lines->Clear();
	mFeatO3->Lines->Clear(); mFeatA3->Lines->Clear();
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
bool TfmFeatChoi::LoadEcg(cEcg& ecg, TImage* img, TImage* iheart, TImage* iabl)
	{
	//Originaldaten
	ecg.data.redisplay(img);

	//Ableitungen
	if (!ecg.data.buildDerivates()) return false;

	//Standardherzschlag normal
	iarray_t heart = ecg.heart.calcAvBeat(ecg.data.data_array);
	farray.redisplay(heart, iheart);

	//Standardherzschlag auf 1. Ableitung
	iarray_t abl = fmath.calcDerivate(ecg.data.data_array);
	iarray_t heartabl = ecg.heart.calcAvBeat(abl);
	farray.redisplay(heartabl, iabl);

	return true;
	}
//---------------------------------------------------------------------------
bool TfmFeatChoi::GetFeat(cEcg& ecg, TMemo* memo, TMemo* mema)
	{
	memo->Lines->Clear(); mema->Lines->Clear();

	iarray_t ro = ecg.rpeaks.find(ecg.data.data_array, NULL);
	if (ro.size() <= 0) return false;
	if (!fFeatChoi.getFeatures(ecg.data.data_array, ro)) return false;
	memo->Lines->Add(fFeatChoi.features_string);

	iarray_t ra = ecg.rpeaks.find(ecg.data.derivate1.deriv_array, NULL);
	if (ra.size() <= 0) return false;
	if (!fFeatChoi.getFeatures(ecg.data.derivate1.deriv_array, ra)) return false;
	mema->Lines->Add(fFeatChoi.features_string);

	return true;
	}
//---------------------------------------------------------------------------
void TfmFeatChoi::Tick(int pos)
	{
	pbJob->Position += pos;
	}
//---------------------------------------------------------------------------
void TfmFeatChoi::Start()
	{
	Cursor = crHourGlass;
	Application->ProcessMessages();
	}
//---------------------------------------------------------------------------
void TfmFeatChoi::End()
	{
	Cursor = crDefault;
	Application->ProcessMessages();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btLoadEkg1Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Start();
	laEcg1->Caption = OpenDialog->FileName;
	if (!fecg1.data.getFile(OpenDialog->FileName, formatADS, "\t", cbLead1->ItemIndex+1, 0, 3000))
		; //todo

	if (!LoadEcg(fecg1, imgEcg1, iHeartEcg1, iHeAblEcg1))
		; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btLoadEkg2Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Start();
	laEcg2->Caption = OpenDialog->FileName;
	if (!fecg2.data.getFile(OpenDialog->FileName, formatADS, "\t", cbLead2->ItemIndex+1, 0, 3000))
		; //todo

	if (!LoadEcg(fecg2, imgEcg2, iHeartEcg2, iHeAblEcg2))
		; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btLoadEcg3Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Start();
	laEcg3->Caption = OpenDialog->FileName;
	if (!fecg3.data.getFile(OpenDialog->FileName, formatADS, "\t", cbLead3->ItemIndex+1, 0, 3000))
		; //todo

	if (!LoadEcg(fecg3, imgEcg3, iHeartEcg3, iHeAblEcg3))
		; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::cbLead1Change(TObject *Sender)
	{
	Start();
	if (!fecg1.data.getFile(laEcg1->Caption, formatADS, "\t", cbLead1->ItemIndex+1, 0, 3000))
		; //todo

	if (!LoadEcg(fecg1, imgEcg1, iHeartEcg1, iHeAblEcg1)) ; //todo
	if (!GetFeat(fecg1, mFeatO1, mFeatA1)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::cbLead2Change(TObject *Sender)
	{
	Start();
	if (!fecg2.data.getFile(laEcg2->Caption, formatADS, "\t", cbLead2->ItemIndex+1, 0, 3000))
		; //todo

	if (!LoadEcg(fecg2, imgEcg2, iHeartEcg2, iHeAblEcg2)) ; //todo
	if (!GetFeat(fecg2, mFeatO2, mFeatA2)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::cbLead3Change(TObject *Sender)
	{
	Start();
	if (!fecg3.data.getFile(laEcg3->Caption, formatADS, "\t", cbLead3->ItemIndex+1, 0, 3000))
		; //todo

	if (!LoadEcg(fecg3, imgEcg3, iHeartEcg3, iHeAblEcg3)) ; //todo
	if (!GetFeat(fecg3, mFeatO3, mFeatA3)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btFeat1Click(TObject *Sender)
	{
	Start();
	if (!GetFeat(fecg1, mFeatO1, mFeatA1)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btFeat2Click(TObject *Sender)
	{
	Start();
	if (!GetFeat(fecg2, mFeatO2, mFeatA2)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btFeat3Click(TObject *Sender)
	{
	Start();
	if (!GetFeat(fecg3, mFeatO3, mFeatA3)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btGlatt1Click(TObject *Sender)
	{
	Start();
	if (!fecg1.data.movingAv(10, true)) ; //todo
	if (!LoadEcg(fecg1, imgEcg1, iHeartEcg1, iHeAblEcg1)) ; //todo
	if (!GetFeat(fecg1, mFeatO1, mFeatA1)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btGlatt2Click(TObject *Sender)
	{
	Start();
	if (!fecg2.data.movingAv(10, true)) ; //todo
	if (!LoadEcg(fecg2, imgEcg2, iHeartEcg2, iHeAblEcg2)) ; //todo
	if (!GetFeat(fecg2, mFeatO2, mFeatA2)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::btGlatt3Click(TObject *Sender)
	{
	Start();
	if (!fecg3.data.movingAv(10, true)) ; //todo
	if (!LoadEcg(fecg3, imgEcg3, iHeartEcg3, iHeAblEcg3)) ; //todo
	if (!GetFeat(fecg3, mFeatO3, mFeatA3)) ; //todo
	End();
	}
//---------------------------------------------------------------------------
void __fastcall TfmFeatChoi::laElkeClick(TObject *Sender)
	{
	//Daten Elke laden und anzeigen
	Start();
	pbJob->Visible = true;
	pbJob->Max = 17;
	pbJob->Position = 0;

	Tick(); String file1 = "D:\\ADS Tests - Transfer vom Laptop\\2017-06-24 - Durchgang 1\\Elke liegend.txt";
	Tick(); laEcg1->Caption = file1;
	Tick(); if (!fecg1.data.getFile(file1, formatADS, "\t", cbLead1->ItemIndex+1, 0, 3000)) ; //todo
	Tick(); if (!LoadEcg(fecg1, imgEcg1, iHeartEcg1, iHeAblEcg1)) ; //todo
	Tick(); if (!GetFeat(fecg1, mFeatO1, mFeatA1)) ; //todo

	Tick(); String file2 = "D:\\ADS Tests - Transfer vom Laptop\\2017-06-24 - Durchgang 2\\Elke liegend.txt";
	Tick(); laEcg2->Caption = file2;
	Tick(); if (!fecg2.data.getFile(file2, formatADS, "\t", cbLead2->ItemIndex+1, 0, 3000)) ; //todo
	Tick(); if (!LoadEcg(fecg2, imgEcg2, iHeartEcg2, iHeAblEcg2)) ; //todo
	Tick(); if (!GetFeat(fecg2, mFeatO2, mFeatA2)) ; //todo

	Tick(); String file3 = "D:\\ADS Tests - Transfer vom Laptop\\2017-06-24 - Durchgang 3\\Elke liegend.txt";
	Tick(); laEcg3->Caption = file3;
	Tick(); if (!fecg3.data.getFile(file3, formatADS, "\t", cbLead3->ItemIndex+1, 0, 3000)) ; //todo
	Tick(); if (!LoadEcg(fecg3, imgEcg3, iHeartEcg3, iHeAblEcg3)) ; //todo
	Tick(); if (!GetFeat(fecg3, mFeatO3, mFeatA3)) ; //todo

	pbJob->Visible = false;
	End();
	}
//---------------------------------------------------------------------------

