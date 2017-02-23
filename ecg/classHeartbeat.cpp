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
bool cHeartbeats::reset(iarray_t curve)
	{
	//erst R-Peaks bilden
	cRpeaks rp;
	iarray_t rpeaks = rp.find(curve, NULL);

	return reset(curve, rpeaks);
	}
//---------------------------------------------------------------------------
bool cHeartbeats::reset(iarray_t curve, iarray_t rpeaks)
	{
	//von r-peak bis r-peak ist jeweils ein Herzschlag
	fcurve  = curve;
	frpeaks = rpeaks;

	if (!farray.resetValues(fcurve, charac))
		return fail(1, "Die Eigenschaftswerte konnten nicht gesetzt werden.");
	farray.farr_charac = charac;

	findex = 0;
	return ok();
	}
//---------------------------------------------------------------------------
bool cHeartbeats::first(iarray_t curve)
	{
	//erst R-Peaks bilden
	cRpeaks rp;
	iarray_t rpeaks = rp.find(curve, NULL);

	return first(curve, rpeaks);
	}
//---------------------------------------------------------------------------
bool cHeartbeats::first(iarray_t curve, iarray_t rpeaks)
	{
	if (!reset(curve, rpeaks))
		return fail(1, "Reset konnte nicht durchgeführt werden");

	return next();
	}
//---------------------------------------------------------------------------
bool cHeartbeats::next()
	{
	//den nächsten Herzschlag "rausschneiden" und in fheartbeat hinterlegen
	//den R-Peak[0] kann man überspringen, weil dieser den Anfang der Kurve,
	//und damit einen unvollständigen Herzschlag darstellt
	findex++;
	if (findex == frpeaks.size())
		return fail(0, "Ende der Kurve erreicht"); //letzter Abschnitt erreicht
	else if (findex >= frpeaks.size())
		return fail(2, "Index überschritten"); //das sollte eig nicht passieren

	int von = frpeaks[findex-1][0]; //Zeitwert vorangegangener R-Peak
	int bis = frpeaks[findex][0];	//Zeitwert aktueller R-Peak

	iarray_t rp = fcurve;
	rp = farray.cut(rp, charac.VonMsec, von-1);
	if (rp.size() <= 0)
		return fail(2, "Fehler beim Erstellen des Herzschlag-Arrays (von)");

	rp = farray.cut(rp, bis-1, charac.BisMsec);
	if (rp.size() <= 0)
		return fail(2, "Fehler beim Erstellen des Herzschlag-Arrays (bis)");

	fheartbeat = rp;
	return ok();
	}
//---------------------------------------------------------------------------
bool cHeartbeats::end()
	{
	if (findex >= frpeaks.size())
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   private Funktionen   *******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t cHeartbeats::get_heartbeat()
	{
	return fheartbeat;
	}
//---------------------------------------------------------------------------

