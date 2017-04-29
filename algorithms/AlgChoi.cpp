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
void TfmChoi::GetBeats()
	{
	//todo: ersetzen durch Klassenaufruf Choi

	Print("----------------------------------------------");
	Print("...get heartbeats");
	if (fecg.data.data_array.size() <= 0)
		{
		Print("\t## Es wurde keine Datei eingelesen");
		return;
		}

	cHeartbeats& heart = fecg.heart;
	if (!heart.reset(fecg.data.data_array))
		{
		Print("\t## Fehler beim Zurücksetzen: %d, %s", heart.error_code, heart.error_msg);
		return;
		}

	farray.clearImg(imgBeat1);	farray.clearImg(imgBeat2);
	farray.clearImg(imgBeat3);	farray.clearImg(imgBeat4);
	farray.clearImg(imgBeat5);	farray.clearImg(imgBeat6);

	int count = 0;
	while (heart.next())
		{
		count++;
		switch (count)
			{
			case 1: farray.redisplay(heart.heartbeat, imgBeat1); break;
			case 2: farray.redisplay(heart.heartbeat, imgBeat2); break;
			case 3: farray.redisplay(heart.heartbeat, imgBeat3); break;
			case 4: farray.redisplay(heart.heartbeat, imgBeat4); break;
			case 5: farray.redisplay(heart.heartbeat, imgBeat5); break;
			case 6: farray.redisplay(heart.heartbeat, imgBeat6); break;
			default: break;
			}
		}

	Print("...heartbeats done");
	}
//---------------------------------------------------------------------------
void TfmChoi::GetRpeaks()
	{
	//todo: ersetzen durch Klassenaufruf Choi

	Print("----------------------------------------------");
	Print("...get r-peaks");
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

	farray.clearImg(imgPeak1);	farray.clearImg(imgPeak2);
	farray.clearImg(imgPeak3);	farray.clearImg(imgPeak4);
	farray.clearImg(imgPeak5);	farray.clearImg(imgPeak6);

	farray.redisplayPoints(fecg.data.data_array, rpeaks, imgEcg);
	iarray_t curve = fecg.data.data_array;
	iarray_t qrs;

	int zeit;
	double wert;
	int pic = 0;

	for (iarray_itr itr = rpeaks.begin(); itr != rpeaks.end(); itr++)
		{
		ilist_t& v = itr->second;
		zeit = v[0];

		//jetzt haben wir einen R-Peak, Test: darstellen mit +- 200 Werten
		qrs.clear();

		int von = zeit - 200;
		if (von < 0) von = 0;

		int bis = zeit + 200;
		if (zeit > curve.size())
			zeit = curve.size();

		qrs = farray.get(curve, von, bis);

		pic++;
		switch (pic)
			{
			case 1: farray.redisplay(qrs, imgPeak1); break;
			case 2: farray.redisplay(qrs, imgPeak2); break;
			case 3: farray.redisplay(qrs, imgPeak3); break;
			case 4: farray.redisplay(qrs, imgPeak4); break;
			case 5: farray.redisplay(qrs, imgPeak5); break;
			case 6: farray.redisplay(qrs, imgPeak6); break;
			default: break;
			}
		}

	Print("...R-Peaks done, %d R-Peaks found", rpeaks.size());
	}
//---------------------------------------------------------------------------
void TfmChoi::GetRpeaksNeu()
	{
	//todo: ersetzen durch Klassenaufruf Choi

	Print("----------------------------------------------");
	Print("...get r-peaks NEU");
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

	farray.clearImg(imgNeu1);	farray.clearImg(imgNeu2);
	farray.clearImg(imgNeu3);	farray.clearImg(imgNeu4);
	farray.clearImg(imgNeu5);	farray.clearImg(imgNeu6);

	farray.PointWidth = 5;
	farray.PointColor = clRed;
	farray.displayPoints(fecg.data.data_array, rpeaks, imgEcg);

	iarray_t curve = fecg.data.data_array;
	iarray_t qrs;

	if (!r.reset())
		{
		Print("\t## Fehler reset R-Peaks: %d, %s", r.error_code, r.error_msg);
		return;
		}

	int pic = 0;
	int zeit, prev, next;
	int rr_left, rr_rigt;
	int von, bis;

	double p_von, p_bis, q_von, q_bis, s_von, s_bis, t_von, t_bis;

	iarray_t points; points.clear();
	int pcount = 0;

	TImage* img;
	while ((zeit = r.next()) != -1)
		{
		if ((prev = r.prev_rpeak()) == -1) continue;
		if ((next = r.next_rpeak()) == -1) continue;

		pic++;
		switch (pic)
			{
			case 1: img = imgNeu1; break;
			case 2: img = imgNeu2; break;
			case 3: img = imgNeu3; break;
			case 4: img = imgNeu4; break;
			case 5: img = imgNeu5; break;
			case 6: img = imgNeu6; break;
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
		ilist_t& v = itr->second;
		int zz = v[0];
		double ww = v[1];
		points[pcount].push_back(zz);
		points[pcount].push_back(ww);
		pcount++;

		//----- Q-Bereich
		q_von = (double)rr_left * 1/10;		q_bis = 0;
		von = (zeit - q_von) - prev; 		bis = (zeit - q_bis) - prev;
		Color(img, clMoneyGreen, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit - q_von), (zeit - q_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		zz = v[0];
		ww = v[1];
		points[pcount].push_back(zz);
		points[pcount].push_back(ww);
		pcount++;

		//----- S-Bereich
		s_von = 0;							s_bis = (double)rr_rigt * 1/10;
		von = (zeit + s_von) - prev; 		bis = (zeit + s_bis) - prev;
		Color(img, clInfoBk, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit + s_von), (zeit + s_bis));
		arr = fmath.resort(arr, true);
		itr = arr.begin();
		v = itr->second;
		zz = v[0];
		ww = v[1];
		points[pcount].push_back(zz);
		points[pcount].push_back(ww);
		pcount++;

		//----- T-Welle
		t_von = (double)rr_rigt * 1/10;		t_bis = (double)rr_rigt * 1/2;
		von = (zeit + t_von) - prev; 		bis = (zeit + t_bis) - prev;
		Color(img, clMenuBar, von, bis, (next-prev));

		arr = farray.get(qrs, (zeit + t_von), (zeit + t_bis));
		arr = fmath.resort(arr, false);
		itr = arr.begin();
		v = itr->second;
		zz = v[0];
		ww = v[1];
		points[pcount].push_back(zz);
		points[pcount].push_back(ww);
		pcount++;

		}

	//farray.displayPoints(qrs, points, img);

	farray.PointWidth = 2;
	farray.PointColor = clBlue;
	farray.displayPoints(fecg.data.data_array, points, imgEcg);

	Print("...R-Peaks NEU done, %d R-Peaks found", rpeaks.size());
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

		farray.clearImg(imgBeat1);	farray.clearImg(imgBeat2);
		farray.clearImg(imgBeat3);	farray.clearImg(imgBeat4);
		farray.clearImg(imgBeat5);	farray.clearImg(imgBeat6);

		farray.clearImg(imgPeak1);	farray.clearImg(imgPeak2);
		farray.clearImg(imgPeak3);	farray.clearImg(imgPeak4);
		farray.clearImg(imgPeak5);	farray.clearImg(imgPeak6);

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
void __fastcall TfmChoi::btBeatsClick(TObject *Sender)
	{
	GetBeats();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button2Click(TObject *Sender)
	{
	GetRpeaks();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi::Button4Click(TObject *Sender)
	{
	GetRpeaksNeu();
	}
//---------------------------------------------------------------------------

