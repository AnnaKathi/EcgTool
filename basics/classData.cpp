//---------------------------------------------------------------------------
#pragma hdrstop

#include "classData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cData::cData()
	: fcsv(new cCsv), farray(new cArray), fderiv1(new cDerivate), fderiv2(new cDerivate)
	{
	}
//---------------------------------------------------------------------------
cData::~cData()
	{
	}
//---------------------------------------------------------------------------
void cData::resetValues()
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
bool cData::getFile(String file, String delim, int vonMsec, int bisMsec)
	{
	farr.clear();

	if (!fcsv->OpenFile(file, delim))
		return fail(fcsv->error_code, fcsv->error_msg);

	if (!fcsv->StartAt(vonMsec))
		return fail(fcsv->error_code, fcsv->error_msg);

	farr_charac.VonMsec = farr_charac.BisMsec = fcsv->getSample();
	farr_charac.MinWert = farr_charac.MaxWert = fcsv->getI();

	float zeit;
	float lead1;
	int ix = 0;
	do
		{
		zeit  = fcsv->getLineNo(); //todo: fcsv->getSample(); ist in Datei nicht vorhanden
		lead1 = fcsv->getI();
		farr[ix].push_back(zeit);
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
bool cData::redisplay(TImage* img)
	{
    return farray->redisplay(farr, img);
	}
//---------------------------------------------------------------------------
bool cData::movingAv(int window, bool CalcBegin) //default CalcBegin=true
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
int cData::cut(int vonMsec, int bisMsec)
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
bool cData::buildDerivates()
	{
	if (farr.size() <= 0)
		return fail(1, "Das Daten-Array ist leer");

	if (!fderiv1->build(farr))
		; //todo

	if (!fderiv2->build(fderiv1->deriv_array))
		; //todo
		
	return ok();
	}
//---------------------------------------------------------------------------
iarray_t cData::get_array()
	{
	return farr;
	}
//---------------------------------------------------------------------------
cDerivate& cData::get_deriv1()
	{
	return *fderiv1;
	}
//---------------------------------------------------------------------------
cDerivate& cData::get_deriv2()
	{
	return *fderiv2;
	}
//---------------------------------------------------------------------------

