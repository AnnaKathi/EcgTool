//---------------------------------------------------------------------------
#pragma hdrstop

#include "classData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cData::cData()
	: fcsv(new cCsv)
	{
	}
//---------------------------------------------------------------------------
cData::~cData()
	{
	}
//---------------------------------------------------------------------------
bool cData::getFile(String file, String delim, int vonMsec, int bisMsec)
	{
	farr.clear();

	if (!fcsv->OpenFile(file, delim))
		return fail(fcsv->error_code, fcsv->error_msg);

	if (!fcsv->StartAt(vonMsec))
		return fail(fcsv->error_code, fcsv->error_msg);

	farr_charac.VonMsec = farr_charac.BisMsec = fcsv->getSample();
	farr_charac.MinWert = farr_charac.MaxWert = fcsv->getI();

	int zeit;
	float lead1;
	int ix = 0;
	do
		{
		zeit  = fcsv->getSample();
		lead1 = fcsv->getI();
		farr[ix].push_back((float)zeit);
		farr[ix].push_back(lead1);
		ix++;

		if (zeit < farr_charac.VonMsec) farr_charac.VonMsec = zeit;
		if (zeit > farr_charac.BisMsec) farr_charac.BisMsec = zeit;

		if (lead1 < farr_charac.MinWert) farr_charac.MinWert = lead1;
		if (lead1 > farr_charac.MaxWert) farr_charac.MaxWert = lead1;
		}
	while (fcsv->NextUntil(bisMsec));

	farr_charac.VonIdx = 0;
	farr_charac.BisIdx = ix-1;
	farr_charac.Number = farr.size();
	return ok();
	}
//---------------------------------------------------------------------------
bool cData::display(TImage* img)
	{
	if (img == NULL)
		return fail(-1, "Es wurde keim Bild übergeben.");

	//--- Anzahl der x- und y-Werte ausrechnen
	float range_x = farr_charac.BisIdx  - farr_charac.VonIdx;
	float range_y = farr_charac.MaxWert - farr_charac.MinWert;

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
