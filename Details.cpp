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
/***************************************************************************/
/**************   Public Functions   ***************************************/
/***************************************************************************/
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
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
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
inline void TfmDetails::StartJob()
	{
	pbJob->Max 	   = 4;
	pbJob->Visible = true;
	Application->ProcessMessages();
	}
//---------------------------------------------------------------------------
inline void TfmDetails::TickJob()
	{
	pbJob->Position++;
	Application->ProcessMessages();
	}
//---------------------------------------------------------------------------
inline void TfmDetails::EndJob()
	{
	pbJob->Visible = false;
	Application->ProcessMessages();
	}
//---------------------------------------------------------------------------
void TfmDetails::PaintCurves()
	{
	StartJob();
	farray.clearImg(imgData);
	farray.clearImg(imgRpeaks);
	farray.clearImg(imgBeats);

	if (cbKurve->ItemIndex == cbEkgData)
		{
		//-- Originaldaten
		farray.redisplay(alg1->ecg.data.data_array, imgData);
		TickJob();

		//-- R-Peaks
		iarray_t rp = alg1->ecg.rpeaks.find(alg1->ecg.data.data_array, NULL);
		farray.displayPoints(alg1->ecg.data.data_array, rp, imgRpeaks);
		TickJob();

		//-- Herzschläge
		//die einzelnen Herzschläge müssen auf die gleiche Länge normalisiert werden
		//als Länge wird (erst einmal) die Länge zwischen den 1. RPeak und dem
		//2. verwendet, todo: über alle R-Peaks eine Länge berechnen
		int zeitges = 0;
		for (int i = 1; i < rp.size(); i++)
			zeitges += (rp[i][0] - rp[i-1][0]);
		int length;
		if (rp.size() > 1)
			length = zeitges / (rp.size()-1);
		else
        	length = 0;

		cHeartbeats& h = alg1->ecg.heart;
		h.reset(alg1->ecg.data.data_array);
		while (h.next())
			farray.display(fdata.normalize(h.heartbeat, length), imgBeats);
		TickJob();

		//-- Standardherzschlag
		h.calcAvBeat(alg1->ecg.data.data_array);
		farray.redisplay(h.avBeat, imgHerz);
		TickJob();
		}

	else if (cbKurve->ItemIndex == cbDerivate1)
		{
		//-- Originaldaten
		farray.redisplay(alg1->ecg.data.derivate1.deriv_array, imgData);
		TickJob();

		//-- R-Peaks
		iarray_t rp = alg1->ecg.rpeaks.find(alg1->ecg.data.derivate1.deriv_array, NULL);
		farray.displayPoints(alg1->ecg.data.derivate1.deriv_array, rp, imgRpeaks);
		TickJob();

		//-- Herzschläge
		//die einzelnen Herzschläge müssen auf die gleiche Länge normalisiert werden
		//als Länge wird (erst einmal) die Länge zwischen den 1. RPeak und dem
		//2. verwendet, todo: über alle R-Peaks eine Länge berechnen
		int zeitges = 0;
		for (int i = 1; i < rp.size(); i++)
			zeitges += (rp[i][0] - rp[i-1][0]);
		int length;
		if (rp.size() > 1)
			length = zeitges / (rp.size()-1);
		else
        	length = 0;

		cHeartbeats h = alg1->ecg.heart;
		h.reset(alg1->ecg.data.derivate1.deriv_array);
		while (h.next())
			farray.display(fdata.normalize(h.heartbeat, length), imgBeats);
		TickJob();

		//-- Standardherzschlag
		h.calcAvBeat(alg1->ecg.data.derivate1.deriv_array);
		farray.redisplay(h.avBeat, imgHerz);
		TickJob();
		}

	else if (cbKurve->ItemIndex == cbDerivate2)
		{
		//-- Originaldaten
		farray.redisplay(alg1->ecg.data.derivate2.deriv_array, imgData);
		TickJob();

		//-- R-Peaks
		iarray_t rp = alg1->ecg.rpeaks.find(alg1->ecg.data.derivate2.deriv_array, NULL);
		farray.displayPoints(alg1->ecg.data.derivate2.deriv_array, rp, imgRpeaks);
		TickJob();

		//-- Herzschläge
		//die einzelnen Herzschläge müssen auf die gleiche Länge normalisiert werden
		//als Länge wird (erst einmal) die Länge zwischen den 1. RPeak und dem
		//2. verwendet, todo: über alle R-Peaks eine Länge berechnen
		int zeitges = 0;
		for (int i = 1; i < rp.size(); i++)
			zeitges += (rp[i][0] - rp[i-1][0]);
		int length;
		if (rp.size() > 1)
			length = zeitges / (rp.size()-1);
		else
        	length = 0;

		cHeartbeats h = alg1->ecg.heart;
		h.reset(alg1->ecg.data.derivate2.deriv_array);
		while (h.next())
			farray.display(fdata.normalize(h.heartbeat, length), imgBeats);
		TickJob();

		//-- Standardherzschlag
		h.calcAvBeat(alg1->ecg.data.derivate2.deriv_array);
		farray.redisplay(h.avBeat, imgHerz);
		TickJob();
		}
	EndJob();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
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
void __fastcall TfmDetails::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
	{
	if (Shift.Contains(ssCtrl) && Shift.Contains(ssShift))
		{
		if (Key == 0x31) //"1" -> EKG-Daten aufrufen
			{
			cbKurve->ItemIndex = cbEkgData;
			cbKurveChange(Sender);
			}
		else if (Key == 0x32) //"2" -> Erste Ableitung aufrufen
			{
			cbKurve->ItemIndex = cbDerivate1;
			cbKurveChange(Sender);
			}
		else if (Key == 0x33) //"3" -> Zweite Ableitung aufrufen
			{
			cbKurve->ItemIndex = cbDerivate2;
			cbKurveChange(Sender);
			}
		else if (Key == 0x50) //"P" -> Papa fokussieren
			{
			Papa->BringToFront();
			}
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

