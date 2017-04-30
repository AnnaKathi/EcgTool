//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "AlgChoi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmChoi *fmChoi;
//---------------------------------------------------------------------------
bool DlgAlgChoi(TForm* Papa)
	{
	TfmChoi* Form = new TfmChoi(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmChoi::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi::TfmChoi(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi::~TfmChoi()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::FormClose(TObject *Sender, TCloseAction &Action)
	{
    ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String TfmChoi::fmt(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	va_end(argptr);
	return (String)buffer;
	}
//---------------------------------------------------------------------------
void TfmChoi::Print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	Memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
void TfmChoi::Line(TImage* img, int x, TColor cl)
	{
	//diese X-Pos in der angegebenen Farbe anmalen ohne dass die Kurve übermalt wird
	for (int y = 0; y < img->Height; y++)
		{
		if (img->Canvas->Pixels[x][y] == clBlack)
			continue;
		else
			img->Canvas->Pixels[x][y] = cl;
		}
	}
//---------------------------------------------------------------------------
void TfmChoi::Color(TImage* img, TColor cl, int von, int bis, int max)
	{
	//wird aufgerufen mit einem Zeitbereich -> umrechnen auf x-Positionen
	double faktor = (double)img->Width / (double)max;
	int x_von = (double)von * (double)faktor;
	int x_bis = (double)bis * (double)faktor;

	for (int x = x_von; x <= x_bis; x++)
		Line(img, x, cl);
	}
//---------------------------------------------------------------------------
void TfmChoi::ShowEcg()
	{
	farray.clearImg(imgEcg);
	
	Print("----------------------------------------------");
	Print("...read ecg-file...");
	String ecgFile = edInputfile->Text;
	if (ecgFile == "") return;

	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	eDatFormat format;
	if (cbFormat->ItemIndex == 1)
		format = formatADS;
	else
		format = formatNone;

	//-- EKG-Daten
	if (!fecg.data.getFile(ecgFile, format, delim, 1, 3000))
		{
		Print("\t## Fehler aufgetreten: %d, %s", fecg.data.error_code, fecg.data.error_msg);
		return;
		}

	fecg.data.redisplay(imgEcg);
	Print("...ecg-file ready");
	}
//---------------------------------------------------------------------------
void TfmChoi::GetRpeaksAnna()
	{
	//todo: ersetzen durch Klassenaufruf Choi

	Print("----------------------------------------------");
	Print("...get r-peaks Anna");
	if (fecg.data.data_array.size() <= 0)
		{
		Print("\t## Es wurde keine Datei eingelesen");
		return;
		}

	cRpeaks& r = fecg.rpeaks;
	iarray_t rpeaks = r.find(fecg.data.data_array, NULL);
	if (rpeaks.size() <= 0)
		{
		Print("\t## Fehler set R-Peaks: %d, %s", r.error_code, r.error_msg);
		return;
		}

	farray.PointWidth = 5;
	farray.PointColor = clRed;
	farray.displayPoints(fecg.data.data_array, rpeaks, imgEcg);

	Print("\tR-Peaks done");
	DoChoi(r);
	}
//---------------------------------------------------------------------------
void TfmChoi::GetRpeaksChoi()
	{
	//todo: ersetzen durch Klassenaufruf Choi

	Print("----------------------------------------------");
	Print("...get r-peaks Choi");
	if (fecg.data.data_array.size() <= 0)
		{
		Print("\t## Es wurde keine Datei eingelesen");
		return;
		}

	//Parameter Choi: minimum amplitude of R-Peak
	double threshold = edThreshold->Text.ToDouble(); //Paper says 0.4;
	iarray_t ecg = fecg.data.data_array;

	//find max-Value in ECG-Array
	double max = ecg[0][1];
	double min = ecg[0][1];
	double wert; int zeit;
	for (iarray_itr itr = ecg.begin(); itr != ecg.end(); itr++)
		{
		ilist_t&v = itr->second;
		wert = v[1];
		if (wert > max) max = wert;
		if (wert < min) min = wert;
		}

	//find potential candidates for R-Peaks through threshold
	double max_threshold = threshold * max;

		//Anpassung Anna ------------------------------------------------------
		//max * theshold ist so nicht richtig, weil 40% vom Max viel
		//weniger ist, als alle enthaltenen Wert -> 40% von der Differenz nehmen
		double diff   = max - min;
		double anteil = diff * threshold;
		max_threshold = min + anteil;
		//----------------------------------------------------------------------

	iarray_t candidates; candidates.clear();
	int count = 0;
	for (iarray_itr itr = ecg.begin(); itr != ecg.end(); itr++)
		{
		ilist_t&v = itr->second;
		zeit = v[0];
		wert = v[1];

		if (wert >= max_threshold)
			{
			candidates[count].push_back(zeit);
			candidates[count].push_back(wert);
			count++;
			}
		}

	//find all overlaps
	int overlap_time = edOverlap->Text.ToInt(); //Paper says 100; //0,1 Sekunde = 100 ms
	iarray_t overlaps = FindOverlapsChoi(candidates, overlap_time);
int bp1 = overlaps.size();

	//overlaps aus candidates entfernen
	//-> in rpeaks (rloc) nur candidates übernehmen, die nicht in overlaps sind
	iarray_t rloc = farray.remove(candidates, overlaps, 0);
int bp2 = rloc.size();

	farray.PointWidth = 5;
	farray.PointColor = clRed;
	farray.displayPoints(fecg.data.data_array, rloc, imgEcg);

	Print("\tR-Peaks done");
	DoChoi2(rloc);
	}
//---------------------------------------------------------------------------
iarray_t TfmChoi::FindOverlapsChoi(iarray_t candidates, int overlap_time)
	{
	/* Anmerkung Anna 30.04.17: Algorithmus funktioniert so nicht, weil jeder
	 * gefundene Kandidat min einen Nachbarn hat, weniger als overlap_time
	 * entfernt ist und deswegen entfernt wird -> alle Kandidaten werden als
	 * Overlap identifiziert
	 */
	iarray_t overlaps; overlaps.clear();
	if (candidates.size() <= 0) return overlaps;

	int zeit; 	   double wert;
	int next_zeit; double next_wert;
	int count = 0;

		//Änderung Anna ------------------------------------------------------
		//Wenn man die Kandidaten einfach von vorne durchläuft (nach der Zeit)
		//dann wird z.B. der erste direkt genommen
		//candidates = fmath.resort(candidates, false);

	for (iarray_itr itr = candidates.begin(); itr != candidates.end(); itr++)
		{
		ilist_t&v = itr->second;
		zeit = v[0];
		wert = v[1];

		itr++;
		if (itr == candidates.end()) break;
		v = itr->second;
		next_zeit = v[0];
		next_wert = v[1];
		itr--;

		if ((next_zeit - zeit) < overlap_time) //beats are too close together
			{
			//add min-value of these two beats
			if (next_wert >= wert)
				{
				overlaps[count].push_back(zeit);
				overlaps[count].push_back(wert);
				}
			else
				{
				overlaps[count].push_back(next_zeit);
				overlaps[count].push_back(next_wert);
				}
			count++;
			}
		}
	return overlaps;
	}
//---------------------------------------------------------------------------
iarray_t TfmChoi::FindOverlapsAnna(iarray_t candidates, int overlap_time)
	{
	iarray_t overlaps; overlaps.clear();
	if (candidates.size() <= 0) return overlaps;

	int zeit; 	   double wert;
	int next_zeit; double next_wert;
	int count = 0;
	for (iarray_itr itr = candidates.begin(); itr != candidates.end(); itr++)
		{
		ilist_t&v = itr->second;
		zeit = v[0];
		wert = v[1];

		itr++;
		if (itr == candidates.end()) break;
		v = itr->second;
		next_zeit = v[0];
		next_wert = v[1];
		itr--;

		if ((next_zeit - zeit) < overlap_time) //beats are too close together
			{
			//add max-value of these two beats
			if (next_wert >= wert)
				{
				overlaps[count].push_back(next_zeit);
				overlaps[count].push_back(next_wert);
				}
			else
				{
				overlaps[count].push_back(zeit);
				overlaps[count].push_back(wert);
				}
			count++;
			}
		}
	return overlaps;
	}
//---------------------------------------------------------------------------
void TfmChoi::DoChoi(cRpeaks& r)
	{
	iarray_t rpeaks = r.rpeaks;

	farray.clearImg(imgNeu1);	farray.clearImg(imgNeu2);
	farray.clearImg(imgNeu3);	farray.clearImg(imgNeu4);
	farray.clearImg(imgNeu5);	farray.clearImg(imgNeu6);
	farray.clearImg(imgBeat);

	m1->Lines->Clear();		m2->Lines->Clear();
	m3->Lines->Clear();		m4->Lines->Clear();
	m5->Lines->Clear();		m6->Lines->Clear();
	mFid->Lines->Clear();

	iarray_t curve = fecg.data.data_array;
	iarray_t qrs;

	if (!r.reset())
		{
		Print("\t## Fehler reset R-Peaks: %d, %s", r.error_code, r.error_msg);
		return;
		}

	int round = -1;
	int zeit, prev, next;
	int rr_left, rr_rigt;
	int von, bis;

	double p_von, p_bis, q_von, q_bis, s_von, s_bis, t_von, t_bis;

	iarray_t points; points.clear();
	int pcount = 0;

	int PLoc, QLoc, RLoc, SLoc, TLoc; 
	int int_pq, int_qs, int_st;
	double PAmp, QAmp, RAmp, SAmp, TAmp; 

	TImage* img; TMemo* memo;
	while ((zeit = r.next()) != -1)
		{
		if ((prev = r.prev_rpeak()) == -1) continue;
		if ((next = r.next_rpeak()) == -1) continue;

		iarray_itr itr = curve.find(zeit);
		ilist_t& v = itr->second;
		RLoc = zeit; RAmp = v[1];

		round++;
		switch (round)
			{
			case 0: img = imgNeu1; memo = m1; break;
			case 1: img = imgNeu2; memo = m2; break;
			case 2: img = imgNeu3; memo = m3; break;
			case 3: img = imgNeu4; memo = m4; break;
			case 4: img = imgNeu5; memo = m5; break;
			case 5: img = imgNeu6; memo = m6; break;
			default: break;
			}

		//-- QRS-Bereich finden
		qrs = farray.get(curve, prev, next);
		farray.redisplay(qrs, img);

		//RR-Intervalle feststellen
		rr_left = zeit - prev;
		rr_rigt = next - zeit;

		//-- Bereich und Minimun/Maximum feststellen
		//----- P-Welle
		p_von = (double)rr_left * 1/6; 		p_bis = (double)rr_left * 1/10;
		von = (zeit - p_von) - prev; 		bis = (zeit - p_bis) - prev;
		Color(img, clGradientInactiveCaption, von, bis, (next-prev));

		iarray_t arr = farray.get(qrs, (zeit - p_von), (zeit - p_bis));
		arr = fmath.resort(arr, false);
		itr = arr.begin();
		v = itr->second;
		PLoc = v[0];
		PAmp = v[1];
		points[pcount].push_back(PLoc);
		points[pcount].push_back(PAmp);
		pcount++;

		//----- Q-Bereich
		q_von = (double)rr_left * 1/10;		q_bis = 0;
		von = (zeit - q_von) - prev; 		bis = (zeit - q_bis) - prev;
		Color(img, clMoneyGreen, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit - q_von), (zeit - q_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		QLoc = v[0];
		QAmp = v[1];
		points[pcount].push_back(QLoc);
		points[pcount].push_back(QAmp);
		pcount++;

		//----- S-Bereich
		s_von = 0;							s_bis = (double)rr_rigt * 1/10;
		von = (zeit + s_von) - prev; 		bis = (zeit + s_bis) - prev;
		Color(img, clInfoBk, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit + s_von), (zeit + s_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		SLoc = v[0];
		SAmp = v[1];
		points[pcount].push_back(SLoc);
		points[pcount].push_back(SAmp);
		pcount++;

		//----- T-Welle
		t_von = (double)rr_rigt * 1/10;		t_bis = (double)rr_rigt * 1/2;
		von = (zeit + t_von) - prev; 		bis = (zeit + t_bis) - prev;
		Color(img, clMenuBar, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit + t_von), (zeit + t_bis));
		arr = fmath.resort(arr, false);
		itr = arr.begin();
		v = itr->second;
		TLoc = v[0];
		TAmp = v[1];
		points[pcount].push_back(TLoc);
		points[pcount].push_back(TAmp);
		pcount++;

		//Fiducial Points finden
		int int_pq = QLoc - PLoc; //PQ-Interval
		int int_qs = SLoc - QLoc; //QS-Interval
		int int_st = TLoc - SLoc; //ST-Interval

		char val[16];
		sprintf(val, "%.8f", PAmp); double amp_p = atof(val);
		sprintf(val, "%.8f", QAmp); double amp_q = atof(val);
		sprintf(val, "%.8f", RAmp); double amp_r = atof(val);
		sprintf(val, "%.8f", SAmp); double amp_s = atof(val);
		sprintf(val, "%.8f", TAmp); double amp_t = atof(val);

		memo->Lines->Add(fmt("%d / %d / %d", int_pq, int_qs, int_st));
		memo->Lines->Add("");
		memo->Lines->Add(fmt("%.5f - %.5f", PAmp, QAmp));
		memo->Lines->Add(fmt("%.5f", RAmp));
		memo->Lines->Add(fmt("%.5f - %.5f", SAmp, TAmp));

		FidPQInt[round] = int_pq;
		FidQSInt[round] = int_qs;
		FidSTInt[round] = int_st;
		FidPAmp[round]  = PAmp;
		FidQAmp[round]  = QAmp;
		FidRAmp[round]  = RAmp;
		FidSAmp[round]  = SAmp;
		FidTAmp[round]  = TAmp;
		}

	//todo farray.displayPoints(qrs, points, img); funktioniert nicht..?

	farray.PointWidth = 2;
	farray.PointColor = clBlue;
	farray.displayPoints(fecg.data.data_array, points, imgEcg);

	fecg.heart.calcAvBeat(fecg.data.data_array);
	farray.redisplay(fecg.heart.avBeat, imgBeat);

	int_pq = int_qs = int_st = 0;
	PAmp = QAmp = RAmp = SAmp = TAmp = 0.00;
	for (int i = 0; i < round; i++)
		{
		int_pq += FidPQInt[i];
		int_qs += FidQSInt[i];
		int_st += FidSTInt[i];
		PAmp += FidPAmp[i];
		QAmp += FidQAmp[i];
		RAmp += FidRAmp[i];
		SAmp += FidSAmp[i];
		TAmp += FidTAmp[i];
		}

	int_pq = int_pq / (round);
	int_qs = int_qs / (round);
	int_st = int_st / (round);
	PAmp = PAmp / (round);
	QAmp = QAmp / (round);
	RAmp = RAmp / (round);
	SAmp = SAmp / (round);
	TAmp = TAmp / (round);

	mFid->Lines->Add(fmt("%d / %d / %d", int_pq, int_qs, int_st));
	mFid->Lines->Add("");
	mFid->Lines->Add(fmt("%.5f - %.5f", PAmp, QAmp));
	mFid->Lines->Add(fmt("%.5f", RAmp));
	mFid->Lines->Add(fmt("%.5f - %.5f", SAmp, TAmp));

	Print("...R-Peaks done, %d R-Peaks found", rpeaks.size());
	}
//---------------------------------------------------------------------------
void TfmChoi::DoChoi2(iarray_t rpeaks)
	{
	//Choi-Algorithmus ausführen ohne Zugriff auf cRpeaks
	int peaks = rpeaks.size();
	if (peaks <= 0)
		{
		Print("\t## Fehler R-Peaks nicht gesetzt");
		return;
		}

	farray.clearImg(imgNeu1);	farray.clearImg(imgNeu2);
	farray.clearImg(imgNeu3);	farray.clearImg(imgNeu4);
	farray.clearImg(imgNeu5);	farray.clearImg(imgNeu6);
	farray.clearImg(imgBeat);

	m1->Lines->Clear();		m2->Lines->Clear();
	m3->Lines->Clear();		m4->Lines->Clear();
	m5->Lines->Clear();		m6->Lines->Clear();
	mFid->Lines->Clear();

	//Sicherheitsabfrage: Maximale Anzahl Herzschläge (= R-Peaks) bei Puls 200
	double max_beats = (fecg.data.data_array.size() / 1000) * 200/60;
	if (peaks > max_beats)
		{
		Print("\t >> zuviele R-Peaks gefunden: %d", peaks);
		Print("\t >> EKG kann max. %2.f Herschläge enthalten", max_beats);
		return;
		}

	iarray_t curve = fecg.data.data_array;
	iarray_t qrs;

	int round = -1;
	int zeit, prev, next;
	int rr_left, rr_rigt;
	int von, bis;

	double p_von, p_bis, q_von, q_bis, s_von, s_bis, t_von, t_bis;

	iarray_t points; points.clear();
	int pcount = 0;

	int PLoc, QLoc, RLoc, SLoc, TLoc; 
	int int_pq, int_qs, int_st;
	double PAmp, QAmp, RAmp, SAmp, TAmp; 

	TImage* img; TMemo* memo;

	bool first = true;
	for (iarray_itr itr_rpeaks = rpeaks.begin(); itr_rpeaks != rpeaks.end(); itr_rpeaks++)
		{
		ilist_t& v = itr_rpeaks->second;
		zeit = v[0];

		if (first)
			{
			prev = zeit;
			first = false;
			continue;
			}

		itr_rpeaks++;
		if (itr_rpeaks == rpeaks.end()) break;
		v = itr_rpeaks->second;
		next = v[0];
		itr_rpeaks--;

		iarray_itr itr_curve = curve.find(zeit);
		v = itr_curve->second;
		RLoc = zeit; RAmp = v[1];

		round++;
		switch (round)
			{
			case 0: img = imgNeu1; memo = m1; break;
			case 1: img = imgNeu2; memo = m2; break;
			case 2: img = imgNeu3; memo = m3; break;
			case 3: img = imgNeu4; memo = m4; break;
			case 4: img = imgNeu5; memo = m5; break;
			case 5: img = imgNeu6; memo = m6; break;
			default: break;
			}

		//-- QRS-Bereich finden
		qrs = farray.get(curve, prev, next);
		farray.redisplay(qrs, img);

		//RR-Intervalle feststellen
		rr_left = zeit - prev;
		rr_rigt = next - zeit;

		//-- Bereich und Minimun/Maximum feststellen
		//----- P-Welle
		p_von = (double)rr_left * 1/6; 		p_bis = (double)rr_left * 1/10;
		von = (zeit - p_von) - prev; 		bis = (zeit - p_bis) - prev;
		Color(img, clGradientInactiveCaption, von, bis, (next-prev));

		iarray_t arr = farray.get(qrs, (zeit - p_von), (zeit - p_bis));
		arr = fmath.resort(arr, false);
		iarray_itr itr = arr.begin();
		v = itr->second;
		PLoc = v[0];
		PAmp = v[1];
		points[pcount].push_back(PLoc);
		points[pcount].push_back(PAmp);
		pcount++;

		//----- Q-Bereich
		q_von = (double)rr_left * 1/10;		q_bis = 0;
		von = (zeit - q_von) - prev; 		bis = (zeit - q_bis) - prev;
		Color(img, clMoneyGreen, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit - q_von), (zeit - q_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		QLoc = v[0];
		QAmp = v[1];
		points[pcount].push_back(QLoc);
		points[pcount].push_back(QAmp);
		pcount++;

		//----- S-Bereich
		s_von = 0;							s_bis = (double)rr_rigt * 1/10;
		von = (zeit + s_von) - prev; 		bis = (zeit + s_bis) - prev;
		Color(img, clInfoBk, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit + s_von), (zeit + s_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		SLoc = v[0];
		SAmp = v[1];
		points[pcount].push_back(SLoc);
		points[pcount].push_back(SAmp);
		pcount++;

		//----- T-Welle
		t_von = (double)rr_rigt * 1/10;		t_bis = (double)rr_rigt * 1/2;
		von = (zeit + t_von) - prev; 		bis = (zeit + t_bis) - prev;
		Color(img, clMenuBar, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit + t_von), (zeit + t_bis));
		arr = fmath.resort(arr, false);
		itr = arr.begin();
		v = itr->second;
		TLoc = v[0];
		TAmp = v[1];
		points[pcount].push_back(TLoc);
		points[pcount].push_back(TAmp);
		pcount++;

		//Fiducial Points finden
		int int_pq = QLoc - PLoc; //PQ-Interval
		int int_qs = SLoc - QLoc; //QS-Interval
		int int_st = TLoc - SLoc; //ST-Interval

		char val[16];
		sprintf(val, "%.8f", PAmp); double amp_p = atof(val);
		sprintf(val, "%.8f", QAmp); double amp_q = atof(val);
		sprintf(val, "%.8f", RAmp); double amp_r = atof(val);
		sprintf(val, "%.8f", SAmp); double amp_s = atof(val);
		sprintf(val, "%.8f", TAmp); double amp_t = atof(val);

		memo->Lines->Add(fmt("%d / %d / %d", int_pq, int_qs, int_st));
		memo->Lines->Add("");
		memo->Lines->Add(fmt("%.5f - %.5f", PAmp, QAmp));
		memo->Lines->Add(fmt("%.5f", RAmp));
		memo->Lines->Add(fmt("%.5f - %.5f", SAmp, TAmp));

		FidPQInt[round] = int_pq;
		FidQSInt[round] = int_qs;
		FidSTInt[round] = int_st;
		FidPAmp[round]  = PAmp;
		FidQAmp[round]  = QAmp;
		FidRAmp[round]  = RAmp;
		FidSAmp[round]  = SAmp;
		FidTAmp[round]  = TAmp;

		prev = zeit;
		}

	//todo farray.displayPoints(qrs, points, img); funktioniert nicht..?

	farray.PointWidth = 2;
	farray.PointColor = clBlue;
	farray.displayPoints(fecg.data.data_array, points, imgEcg);

	fecg.heart.calcAvBeat(fecg.data.data_array);
	farray.redisplay(fecg.heart.avBeat, imgBeat);

	int_pq = int_qs = int_st = 0;
	PAmp = QAmp = RAmp = SAmp = TAmp = 0.00;
	for (int i = 0; i < round; i++)
		{
		int_pq += FidPQInt[i];
		int_qs += FidQSInt[i];
		int_st += FidSTInt[i];
		PAmp += FidPAmp[i];
		QAmp += FidQAmp[i];
		RAmp += FidRAmp[i];
		SAmp += FidSAmp[i];
		TAmp += FidTAmp[i];
		}

	int_pq = int_pq / (round);
	int_qs = int_qs / (round);
	int_st = int_st / (round);
	PAmp = PAmp / (round);
	QAmp = QAmp / (round);
	RAmp = RAmp / (round);
	SAmp = SAmp / (round);
	TAmp = TAmp / (round);

	mFid->Lines->Add(fmt("%d / %d / %d", int_pq, int_qs, int_st));
	mFid->Lines->Add("");
	mFid->Lines->Add(fmt("%.5f - %.5f", PAmp, QAmp));
	mFid->Lines->Add(fmt("%.5f", RAmp));
	mFid->Lines->Add(fmt("%.5f - %.5f", SAmp, TAmp));

	Print("...R-Peaks done, %d R-Peaks found", rpeaks.size());
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::btInputfileClick(TObject *Sender)
	{
	if (OpenDialog->Execute())
		{
		edInputfile->Text = OpenDialog->FileName;

		farray.clearImg(imgEcg);

		farray.clearImg(imgNeu1);	farray.clearImg(imgNeu2);
		farray.clearImg(imgNeu3);	farray.clearImg(imgNeu4);
		farray.clearImg(imgNeu5);	farray.clearImg(imgNeu6);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::btReadClick(TObject *Sender)
	{
	ShowEcg();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button4Click(TObject *Sender)
	{
	farray.redisplay(fecg.data.data_array, imgEcg);
	GetRpeaksAnna();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button2Click(TObject *Sender)
	{
	farray.redisplay(fecg.data.data_array, imgEcg);
	GetRpeaksChoi();
	}
//---------------------------------------------------------------------------

