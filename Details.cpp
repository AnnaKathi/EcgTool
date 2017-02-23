//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Details.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmDetails *fmDetails;
//---------------------------------------------------------------------------
bool DlgShowDetails(TForm* Papa, cAlg1& alg)
	{
	TfmDetails* Form = new TfmDetails(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute(alg);
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
__fastcall TfmDetails::TfmDetails(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
bool TfmDetails::Execute(cAlg1& alg)
	{
	alg1 = &alg;
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDetails::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDetails::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	cbKurveChange(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmDetails::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
void __fastcall TfmDetails::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmDetails::cbKurveChange(TObject *Sender)
	{
	tCombo->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmDetails::tComboTimer(TObject *Sender)
	{
	tCombo->Enabled  = false;
	cbKurve->Enabled = false; //damit die Funktion sich nicht überholt

	PaintCurves();

	cbKurve->Enabled = true;
	}
//---------------------------------------------------------------------------
void TfmDetails::PaintCurves()
	{
	farray.clearImg(imgData);
	farray.clearImg(imgRpeaks);
	farray.clearImg(imgBeats);
	
	if (cbKurve->ItemIndex == cbEkgData)
		{
		//-- Originaldaten
		farray.redisplay(alg1->ecg.data.data_array, imgData);

		//-- R-Peaks
		iarray_t rp = alg1->ecg.rpeaks.find(alg1->ecg.data.data_array, NULL);
		farray.displayPoints(alg1->ecg.data.data_array, rp, imgRpeaks);

		//-- Herzschläge
		cHeartbeats h = alg1->ecg.heart;
		h.reset(alg1->ecg.data.data_array);
		while (h.next())
			farray.display(h.heartbeat, imgBeats);

		//-- Standardherzschlag
		//TODO h.calcStandard()
		}

	else if (cbKurve->ItemIndex == cbDerivate1)
		{
		//-- Originaldaten
		farray.redisplay(alg1->ecg.data.derivate1.deriv_array, imgData);

		//-- R-Peaks
		iarray_t rp = alg1->ecg.rpeaks.find(alg1->ecg.data.derivate1.deriv_array, NULL);
		farray.displayPoints(alg1->ecg.data.derivate1.deriv_array, rp, imgRpeaks);

		//-- Herzschläge
		cHeartbeats h = alg1->ecg.heart;
		h.reset(alg1->ecg.data.derivate1.deriv_array);
		while (h.next())
			farray.display(h.heartbeat, imgBeats);

		//-- Standardherzschlag
		//TODO h.calcStandard()
		}

	else if (cbKurve->ItemIndex == cbDerivate2)
		{
		//-- Originaldaten
		farray.redisplay(alg1->ecg.data.derivate2.deriv_array, imgData);

		//-- R-Peaks
		iarray_t rp = alg1->ecg.rpeaks.find(alg1->ecg.data.derivate2.deriv_array, NULL);
		farray.displayPoints(alg1->ecg.data.derivate2.deriv_array, rp, imgRpeaks);

		//-- Herzschläge
		cHeartbeats h = alg1->ecg.heart;
		h.reset(alg1->ecg.data.derivate2.deriv_array);
		while (h.next())
			farray.display(h.heartbeat, imgBeats);

		//-- Standardherzschlag
		//TODO h.calcStandard()
		}
	}
//---------------------------------------------------------------------------
