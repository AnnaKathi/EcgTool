//---------------------------------------------------------------------------
#pragma hdrstop

#include "classDerivate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cDerivate::cDerivate()
	: fmath(new cMath), farray(new cArray)
	{
	}
//---------------------------------------------------------------------------
cDerivate::~cDerivate()
	{
	}
//---------------------------------------------------------------------------
bool cDerivate::build(iarray_t array)
	{
	farr = fmath->calcDerivate(array);
	return ok();
	}
//---------------------------------------------------------------------------
bool cDerivate::display(TImage* img)
	{
	return farray->display(farr, img);
	}
//---------------------------------------------------------------------------
bool cDerivate::roundAt(int nachkommastellen)
	{
	//TODO: ist das überhaupt sinnvoll????
	farr = farray->roundAt(farr, nachkommastellen);

	if (!farray->error)
		{
		//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
		//inputMinWert und inputMaxWert müssen neu gesetzt werden
		farray->resetValues(farr, farr_charac);
		}

	return !farray->error;
	}
//---------------------------------------------------------------------------
bool cDerivate::movingAv(int window, bool CalcBegin) //default CalcBegin=true
	{
	farr = farray->movingAv(farr, window, CalcBegin);

	if (!farray->error)
		{
		//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
		//inputMinWert und inputMaxWert müssen neu gesetzt werden
		farray->resetValues(farr, farr_charac);
		}

	return !farray->error;
	}
//---------------------------------------------------------------------------
int cDerivate::cut(int vonMsec, int bisMsec)
	{
	farr = farray->cut(farr, vonMsec, bisMsec);

	if (!farray->error)
		{
		//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
		//inputMinWert und inputMaxWert müssen neu gesetzt werden
		farray->resetValues(farr, farr_charac);
		}

	return !farray->error;
	}
//---------------------------------------------------------------------------
iarray_t cDerivate::get_array()
	{
	return farr;
	}
//---------------------------------------------------------------------------

