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
bool cData::display(TImage* img)
	{
	if (img == NULL)
		return fail(-1, "Es wurde keim Bild übergeben.");

	//--- Anzahl der x- und y-Werte ausrechnen
	float range_x = farr_charac.BisIdx  - farr_charac.VonIdx;
	float range_y = farr_charac.MaxWert - farr_charac.MinWert;

	if (range_x <= 0) return fail(-1, "Die Input-Werte (Index) stimmen nicht");
	if (range_y <= 0) return fail(-1, "Die Input-Werte (Value) stimmen nicht");

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
#define MAX_NO_STELLEN 20
bool cData::roundAt(int nachkommastellen)
	{
	/* Werte sind in float abgespeichert, z.B. 0,009816540195
	 * Beispiel: auf 0,000x runden:
	 * 		0,0098 16540195
	 *		0,000x ab hier ignorieren
	 */

	//TODO: ist das überhaupt sinnvoll????

	if (nachkommastellen < 0)
		return fail(-1, "Die Zahl der Nachkommastellen ist ungültig: " + String(nachkommastellen));

	if (nachkommastellen > MAX_NO_STELLEN)
		{
		String m =
			"Die ANzahl der Nachkommastellen ist größer als die maximal mögliche Anzahl. Stellen = "
			+ String(nachkommastellen) + ", Maximal möglich = " + String(MAX_NO_STELLEN);
		return fail(-1, m);
		}

	String temp, zahl, begin, middle, end;
	char nachkomma[MAX_NO_STELLEN+1];
	float wert;
	int pos, n;
	for (int i = 0; i < farr.size(); i++)
		{
		wert = farr[i][1]; //lead 1
		temp = String(wert);

		pos    = temp.Pos(",");
		zahl   = temp.SubString(0, pos-1);
		begin  = temp.SubString(pos+1, nachkommastellen-1);
		middle = temp.SubString(pos+1+nachkommastellen-1, 1);
		end    = temp.SubString(pos+1+nachkommastellen, 1);

		n = end.ToInt();
		if (n > 5) //aufrunden
			middle = String(middle.ToInt() + 1);

		temp = zahl + "," + begin + middle;
		wert = temp.ToDouble();

		farr[i][1] = wert;
		}

	resetValues();
	return ok();
	}
//---------------------------------------------------------------------------
#define MAX_NO_MOV_AV 250
bool cData::movingAv(int window, bool CalcBegin) //default CalcBegin=true
	{
	if (window <= 0)
		return fail(-1, "Das Fenster ist zu klein: " + String(window));

	else if (window > farr.size())
		{
		//Das Fenster ist größer als die Anzahl enthaltener Werte
		String m = "Das Fenster ist zu groß. Fenster = " + String(window) +
			", Anzahl Elemente im Array = " + String(farr.size());
		return fail(-1, m);
		}

	else if (window > MAX_NO_MOV_AV)
		{
		//Das Fenster ist größer als die maximal mögliche Anzahl
		String m =
			"Das Fenster ist größer als die maximal mögliche Breite. Fenster = "
			+ String(window) + ", Maximal möglich = " + String(MAX_NO_MOV_AV);
		return fail(-1, m);
		}

	float mov[MAX_NO_MOV_AV];
	for (int i = 0; i < MAX_NO_MOV_AV; i++)
		mov[i] = 0.0;

	iarray_t neu;
	iarray_itr ineu;
	neu.clear();

	float zeit, lead1;
	float summe, mittel;
	int new_index = 0;
	for (int i = 0; i < farr.size(); i++)
		{
		zeit  = farr[i][0];
		lead1 = farr[i][1];

		if (i < window)
			{
			//es sind noch nicht genug Werte im array vorhanden, Wert hinten anhängen
			mov[i] = lead1;

			//wenn keepBegin=true dann trotzdem Mittelwert ausrechnen,
			//sonst unveränderten Wert aus dem Array übernehmen
			if (CalcBegin)
				{
				summe = 0;
				for (int a = 0; a <= i; a++)
					summe += mov[a];
				mittel = summe / (i+1);

				neu[new_index].push_back(zeit);
				neu[new_index].push_back(mittel);
				new_index++;
				}
			else
				{
				//Anfangswerte dienen nur zur Berechnung, aus dem Array werden
				//sie aber entfernt, weil die Fensterbreite noch nicht
				//erreicht ist
				/* das hier nicht machen !
				neu[i].push_back(zeit);
				neu[i].push_back(lead1);
				*/
				}
			continue;
			}

		//genug Werte vorhanden, alle Werte eins nach vorn schieben
		for (int a = 0; a < (window-1); a++)
			mov[a] = mov[a+1];
		mov[window-1] = lead1;

		summe = 0;
		for (int a = 0; a < window; a++)
			summe += mov[a];
		mittel = summe / window;

		neu[new_index].push_back(zeit);
		neu[new_index].push_back(mittel);
		new_index++;
		}

	//Werte wieder zurückschreiben ins array
	farr.clear();
	int ix = 0;
	for (ineu = neu.begin(); ineu != neu.end(); ineu++)
		{
		ilist_t& v = ineu->second;
		farr[ix].push_back(v[0]);
		farr[ix].push_back(v[1]);
		ix++;
		}

	//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
	//inputMinWert und inputMaxWert müssen neu gesetzt werden
	resetValues();
	return ok();
	}
//---------------------------------------------------------------------------
