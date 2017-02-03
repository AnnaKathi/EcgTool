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
iarray_t cRpeaks::find(iarray_t array, TImage* img1, TImage* img2, TProgressBar* job)
	{
	iarray_t desc = fmath->resort(array, false);
	//iarray_t desc = fmath->bubbleSortDesc(array, job);
	farray->display(desc, img1);

	farray->resetValues(desc, charac);

	//Schwellenwert verwenden, der R-Peak macht vom Herzschlag ca. 5% aus
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
		rp[rp_count].push_back(rpeakZeit);
		rp[rp_count].push_back(rpeakWert);
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

	return rp;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   private Funktionen   *************************************/
/***************************************************************************/
//---------------------------------------------------------------------------

