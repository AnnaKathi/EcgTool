//---------------------------------------------------------------------------
#pragma hdrstop

#include "classArray.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cArray::cArray()
	{
	}
//---------------------------------------------------------------------------
cArray::~cArray()
	{
	}
//---------------------------------------------------------------------------
bool cArray::resetValues(sArrayCha& cha)
	{
	return resetValues(farr, cha);
	}
//---------------------------------------------------------------------------
bool cArray::resetValues(iarray_t array, sArrayCha& cha)
	{
	if (array.size() <= 0)
		return fail(1, "Das Array ist leer oder nicht vorhanden.");

	//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
	//inputMinWert und inputMaxWert müssen neu gesetzt werden
	iarray_itr itr = array.begin();
	int key = itr->first;
	ilist_t& v = itr->second;
	float zeit = v[0];
	float wert = v[1];

	cha.VonIdx  = 0;
	cha.VonMsec = zeit;	cha.BisMsec = zeit;
	cha.MinWert = wert;	cha.MaxWert = wert;

	//array umschreiben in ein neues array und dann zurückassoziieren
	iarray_t arrneu = array; array.clear();
	int ix = 0;
	for (itr = arrneu.begin(); itr != arrneu.end(); itr++)
		{
		key = itr->first;
		ilist_t& v = itr->second;
		zeit = v[0];
		wert = v[1];

		array[ix].push_back(zeit);
		array[ix].push_back(wert);
		ix++;

		if (key < cha.VonIdx)   cha.VonIdx = key;
		if (key > cha.BisIdx)   cha.BisIdx = key;

		if (zeit < cha.VonMsec) cha.VonMsec = zeit;
		if (zeit > cha.BisMsec) cha.BisMsec = zeit;

		if (wert < cha.MinWert) cha.MinWert = wert;
		if (wert > cha.MaxWert) cha.MaxWert = wert;
		}

	cha.BisIdx = ix-1;
	return ok();
	}
//---------------------------------------------------------------------------
bool cArray::displayPoints(iarray_t curve, iarray_t points, TImage* img)
	{
	//erste Kurve zeichnen
	if (!display(curve, img)) return false;

	float range_x  = farr_charac.BisIdx  - farr_charac.VonIdx;
	float range_y  = farr_charac.MaxWert - farr_charac.MinWert;
	float factor_x = (float)img->Width / range_x;
	float factor_y = (float)img->Height / range_y;

	img->Canvas->Brush->Color = clBlue;

	float zeit, wert;
	int x, y;
	for (int i = 0; i < points.size(); i++)
		{
		zeit = points[i][0];
		wert = points[i][1];

		wert -= farr_charac.MinWert; //relativ ausrichten

		x  = zeit * factor_x;
		y = img->Height - (wert * factor_y);

		img->Canvas->FillRect(Rect(x-5, y-5, x+5, y+5));
		}

	img->Canvas->Brush->Color = clBlack;
	}
//---------------------------------------------------------------------------
bool cArray::display(iarray_t array, TImage* img)
	{
	if (img == NULL)
		return fail(1, "Es wurde kein Bild übergeben.");

	farr = array;
	if (!resetValues(farr_charac))
		return fail(1, "Reset-Values war nicht möglich.");

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
#define MAX_NO_STELLEN 20
iarray_t cArray::roundAt(iarray_t array, int nachkommastellen)
	{
	/* Werte sind in float abgespeichert, z.B. 0,009816540195
	 * Beispiel: auf 0,000x runden:
	 * 		0,0098 16540195
	 *		0,000x ab hier ignorieren
	 */

	//TODO: ist das überhaupt sinnvoll????

	farr.clear();
	if (nachkommastellen < 0)
		{
		fail(1, "Die Zahl der Nachkommastellen ist ungültig: " + String(nachkommastellen));
		return farr;
		}

	if (nachkommastellen > MAX_NO_STELLEN)
		{
		String m =
			"Die Anzahl der Nachkommastellen ist größer als die maximal mögliche Anzahl. Stellen = "
			+ String(nachkommastellen) + ", Maximal möglich = " + String(MAX_NO_STELLEN);
		fail(1, m);
		return farr;
		}

	farr = array;

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

		n = end.ToIntDef(0);
		if (n > 5) //aufrunden
			middle = String(middle.ToInt() + 1);

		temp = zahl + "," + begin + middle;
		wert = temp.ToDouble();

		farr[i][1] = wert;
		}

	ok();
	return farr;
	}
//---------------------------------------------------------------------------
#define MAX_NO_MOV_AV 250
iarray_t cArray::movingAv(iarray_t array, int window, bool CalcBegin)
	{
	farr.clear();
	if (window <= 0)
		{
		fail(1, "Das Fenster ist zu klein: " + String(window));
		return farr;
		}

	else if (window > array.size())
		{
		//Das Fenster ist größer als die Anzahl enthaltener Werte
		String m = "Das Fenster ist zu groß. Fenster = " + String(window) +
			", Anzahl Elemente im Array = " + String(farr.size());
		fail(1, m);
		return farr;
		}

	else if (window > MAX_NO_MOV_AV)
		{
		//Das Fenster ist größer als die maximal mögliche Anzahl
		String m =
			"Das Fenster ist größer als die maximal mögliche Breite. Fenster = "
			+ String(window) + ", Maximal möglich = " + String(MAX_NO_MOV_AV);
		fail(1, m);
		return farr;
		}

	farr = array;

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

	ok();
	return farr;
	}
//---------------------------------------------------------------------------
iarray_t cArray::cut(iarray_t array, int vonMsec, int bisMsec)
	{
	farr.clear();

	if (vonMsec < farr_charac.VonMsec)
		{
		String m = "Der übergebene Wert 'Von' ist kleiner als der "
			"Anfangswert der Kurve: " + String(farr_charac.VonMsec);
		fail(1, m);
		return farr;
		}

	if (bisMsec > farr_charac.BisMsec)
		{
		String m = "Der übergebene Wert 'Bis' ist größer als der "
			"Endwert der Kurve: " + String(farr_charac.BisMsec);
		fail(1, m);
		return farr;
		}

	farr = array;

	int key, zeit;
	int count = 0;

	//reverse Iterator, läuft von hinten nach vorne
	iarray_t::reverse_iterator itr_rev = farr.rbegin();

	while (itr_rev != farr.rend())
		{
		zeit = itr_rev->first;
		if (zeit < vonMsec) break;    //Wert liegt nach gewünschtem (reverse) Abschnitt
		if (zeit > bisMsec)
			{
			//Wert liegt vor gewünschtem (reverse) Abschnitt
			itr_rev++;
			continue;
			}

		farr.erase(zeit);
		count++;
		}

	ok();
	return farr;
	}
//---------------------------------------------------------------------------
