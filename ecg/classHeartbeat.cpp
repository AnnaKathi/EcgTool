//---------------------------------------------------------------------------
#pragma hdrstop

#include "classHeartbeat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cHeartbeats::cHeartbeats()
	{
	}
//---------------------------------------------------------------------------
cHeartbeats::~cHeartbeats()
	{
	}
//---------------------------------------------------------------------------
bool cHeartbeats::build(iarray_t curve, iarray_t rpeaks)
	{
	//von r-peak bis r-peak ist jeweils ein Herzschlag
	fheartbeats.clear();
	int von, bis;
	bool first = true;
	int ix = 0;
	iarray_t beat;
	for (iarray_itr itr = rpeaks.begin(); itr != rpeaks.end(); itr++)
		{
		ilist_t& v = itr->second;
		bis = v[0]; //Zeitwert aktueller R-Peak
		if (first)
			{
			//Anfang bis zum 1. R-Peak wegschneiden
			curve = farray.cut(curve, 0, bis);
			von   = bis;
			first = false;
			continue;
			}

		beat = farray.cut(curve, von, bis);
		for (int n = 0; n < beat.size(); n++)
			{
			fheartbeats[ix].push_back(v[0]);
			fheartbeats[ix].push_back(v[1]);
			}

		ix++;
		von = bis;
		}

	if (ix > 0)
		return true;
	else
    	return false;
	}
//---------------------------------------------------------------------------
iarray_t cHeartbeats::first()
	{
	findex = -1; //next setzt das eins hoch
	return next();
	}
//---------------------------------------------------------------------------
iarray_t cHeartbeats::next()
	{
	findex++;

	iarray_t beat; beat.clear();
	int key;
	int ix = 0;
	for (iarray_itr itr = fheartbeats.begin(); itr != fheartbeats.end(); itr++)
		{
		key = itr->first;
		if (key != findex) continue;

		ilist_t& v = itr->second;
		beat[ix].push_back(v[0]);
		beat[ix].push_back(v[1]);
		ix++;
		}

	return beat;
	}
//---------------------------------------------------------------------------

