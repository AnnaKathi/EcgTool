//---------------------------------------------------------------------------
#pragma hdrstop

#include "classRpeaks.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cRpeaks::cRpeaks()
	: fmath(new cMath), farray(new cArray)
	{
	}
//---------------------------------------------------------------------------
cRpeaks::~cRpeaks()
	{
	}
//---------------------------------------------------------------------------
iarray_t cRpeaks::find(iarray_t array, TImage* img1)
	{
	iarray_t desc = fmath->resort(array, false);
	if (img1 != NULL)
		farray->redisplay(desc, img1);

	farray->resetValues(desc, charac);

	//Schwellenwert verwenden, der R-Peak macht vom Herzschlag ca. x% aus
	float anteil_qrs = 0.025;

	iarray_t peaks; peaks.clear();
	int last = desc.size() * anteil_qrs;
	for (int i = 0; i < last; i++)
		{
		peaks[i].push_back(desc[i][0]);
		peaks[i].push_back(desc[i][1]);
		}

	iarray_t rp; rp.clear();
	iarray_t arrneu;
	int msec_von, msec_bis;
	int rp_count = 0;

	int rpeakZeit;
	float rpeakWert;
	while (peaks.size() > 0)
		{
		rpeakZeit = peaks[0][0];
		rpeakWert = peaks[0][1];
		rp[rpeakZeit].push_back(rpeakZeit);
		rp[rpeakZeit].push_back(rpeakWert);
		rp_count++;

		msec_von = rpeakZeit - 100;
		if (msec_von < 0) msec_von = 0;

		msec_bis = rpeakZeit + 100;
		if (msec_bis > charac.BisMsec) msec_bis = charac.BisMsec;

		arrneu.clear();
		int zeit;
		int ix = 0;
		for (int n = 0; n < peaks.size(); n++)
			{
			zeit = peaks[n][0];
			if (zeit >= msec_von && zeit <= msec_bis) continue;

			arrneu[ix].push_back(zeit);
			arrneu[ix].push_back(peaks[n][1]);
			ix++;
			}
		peaks = arrneu;
		}

	//als Key wurde für rp der Zeitwert des R-Peaks verwendet, hier muss das
	//Array deswegen noch einmal umgeschrieben werden, sodass korrekte Indizes
	//vorhanden sind auf die sich aufbauende Funktionen beziehen können
	iarray_t rr; rr.clear();
	int key, zeit;
	float wert;
	int ix = 0;
	for (iarray_itr itr = rp.begin(); itr != rp.end(); itr++)
		{
		key = itr->first;
		ilist_t& v = itr->second;
		zeit = v[0];
		wert = v[1];

		rr[ix].push_back(zeit);
		rr[ix].push_back(wert);
		ix++;
		}

	return rr;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   private Funktionen   *************************************/
/***************************************************************************/
//---------------------------------------------------------------------------

