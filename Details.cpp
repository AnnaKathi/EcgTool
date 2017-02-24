//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Details.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmDetails *fmDetails;
//---------------------------------------------------------------------------
__fastcall TfmDetails::TfmDetails(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
bool TfmDetails::Execute(TForm* papa, cAlg1& alg)
	{
	Papa = papa;
	alg1 = &alg;
	Show();
	return true;
	}
//---------------------------------------------------------------------------
bool TfmDetails::Renew(cAlg1& alg)
	{
	alg1 = &alg;
	cbKurveChange(this);
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
	placeForm();
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
void TfmDetails::placeForm()
	{
	//Formular rechts ausrichten wenn es geht
	int left  = Papa->Left + Papa->Width + 25;
	int right = left + Width;
	if (right > Screen->DesktopWidth)
		{
		//passt es vllt links daneben ?
		left = Papa->Left - Width - 25;
		if (left < 0)
			{
			//passt weder rechts noch links daneben, mittig anzeigen
			left = (Screen->DesktopWidth - Width)/2;
			}
		}
	Left = left;

	//Formular vertikal mittig zum Hauptformular ausrichten wenn es geht
	int mitte = Papa->Top + (Papa->Height/2);
	int top   = mitte - (Height/2);
	if (top < 0)
		{
		//Formular oben am Hauptformular ausrichten
		top = Papa->Top;
		}
	Top = top;
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
		h.calcAvBeat(alg1->ecg.data.data_array);
		farray.redisplay(h.avBeat, imgHerz);
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
		h.calcAvBeat(alg1->ecg.data.derivate1.deriv_array);
		farray.redisplay(h.avBeat, imgHerz);
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
		h.calcAvBeat(alg1->ecg.data.derivate2.deriv_array);
		farray.redisplay(h.avBeat, imgHerz);
		}
	}
//---------------------------------------------------------------------------
