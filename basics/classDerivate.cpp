//---------------------------------------------------------------------------
#pragma hdrstop

#include "classDerivate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cDerivate::cDerivate()
	: fmath(new cMath)
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
void cDerivate::resetValues()
	{
	//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
	//inputMinWert und inputMaxWert müssen neu gesetzt werden
	iarray_itr itr = farr.begin();
	int key = itr->first;
	ilist_t& v = itr->second;
	float zeit = v[0];
	float wert = v[1];

	farr_charac.VonIdx  = 0;
	farr_charac.VonMsec = zeit;	farr_charac.BisMsec = zeit;
	farr_charac.MinWert = wert;	farr_charac.MaxWert = wert;

	//array umschreiben in ein neues array und dann zurückassoziieren
	iarray_t arrneu = farr; farr.clear();
	int ix = 0;
	for (itr = arrneu.begin(); itr != arrneu.end(); itr++)
		{
		key = itr->first;
		ilist_t& v = itr->second;
		zeit = v[0];
		wert = v[1];

		farr[ix].push_back(zeit);
		farr[ix].push_back(wert);
		ix++;

		if (key < farr_charac.VonIdx) farr_charac.VonIdx = key;
		if (key > farr_charac.BisIdx) farr_charac.BisIdx = key;

		if (zeit < farr_charac.VonMsec) farr_charac.VonMsec = zeit;
		if (zeit > farr_charac.BisMsec) farr_charac.BisMsec = zeit;

		if (wert < farr_charac.MinWert) farr_charac.MinWert = wert;
		if (wert > farr_charac.MaxWert) farr_charac.MaxWert = wert;
		}

	farr_charac.BisIdx = ix-1;
	}
//---------------------------------------------------------------------------
bool cDerivate::display(TImage* img)
	{
	if (img == NULL)
		return fail(1, "Es wurde keim Bild übergeben.");

	resetValues(); //TEST

	//--- Anzahl der x- und y-Werte ausrechnen
	float range_x = farr_charac.BisIdx  - farr_charac.VonIdx;
	float range_y = farr_charac.MaxWert - farr_charac.MinWert;

	if (range_x <= 0) return fail(1, "Die Input-Werte (Index) stimmen nicht");
	if (range_y <= 0) return fail(1, "Die Input-Werte (Value) stimmen nicht");

	//--- Anpassungfaktoren für x- und y-Achse ausrechnen
	float factor_x = (float)img->Width / range_x;
	float factor_y = (float)img->Height / range_y;

	//--- Bild vorbereiten
	img->Canvas->Brush->Color = clWhite;
	img->Canvas->FillRect(Rect(0, 0, img->Picture->Width, img->Picture->Height));
	img->Canvas->Pen->Color = clBlack;

	//--- Map-Werte einzeichnen
	int x, y1, y2;
	float val;
	bool first = true;
	int count = 0;
	for (iarray_itr itr = farr.begin(); itr != farr.end(); itr++)
		{
		count++;

		ilist_t& v = itr->second;
		val = v[1];
		if (val < 0) val *= -1; //auf positive Werte umrechnen ?

		val -= farr_charac.MinWert; //relativ ausrichten

		x  = count * factor_x;
		y1 = val * factor_y;

		//Y = 0 ist oben am Bildrand !
		y2 = img->Height - y1;

		if (first)
			{
			img->Canvas->MoveTo(x, y2);
			first = false;
			}
		else
			img->Canvas->LineTo(x, y2);
		}


	return ok();
	}
//---------------------------------------------------------------------------
iarray_t cDerivate::get_array()
	{
	return farr;
	}
//---------------------------------------------------------------------------

