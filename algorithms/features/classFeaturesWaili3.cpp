//---------------------------------------------------------------------------
#pragma hdrstop

#include "classFeaturesWaili3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cFeaturesWaili3::cFeaturesWaili3()
	{
	fAlgIdent = 3;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   public functions   ***********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cFeaturesWaili3::getFeatures(iarray_t curve, iarray_t rpeaks)
	{
	cQrs& q = fecg.qrs;
	if (!q.build(curve, rpeaks))
		return fail(1, ftools.fmt("Die QRS-Bereiche konnten nicht gebildet werden. cQRS meldet: %s", q.error_msg));

	if (!q.reset())
		return fail(1, ftools.fmt("Die QRS-Wendepunkte konnten nicht zurückgesetzt werden. cQRS meldet: %s", q.error_msg));

	int diff1 = 0;
	int diff2 = 0;
	double w1 = 0;
	double w2 = 0;
	double w3 = 0;
	while (q.next())
		{
		//Annahme: Gespeichert werden die zeitlichen Unterschiede zwischen den
		//Punkten plus die Amplituden
		diff1 += q.QRS.R.zeit - q.QRS.Q.zeit;
		diff2 += q.QRS.S.zeit - q.QRS.R.zeit;

		w1 += q.QRS.Q.wert;
		w2 += q.QRS.Q.wert;
		w3 += q.QRS.Q.wert;
		}

	//Features speichern
	fFeatures[0].push_back(diff1 / q.count);
	fFeatures[1].push_back(diff2 / q.count);
	fFeatures[2].push_back(w1 / q.count);
	fFeatures[3].push_back(w2 / q.count);
	fFeatures[4].push_back(w3 / q.count);

	//Features-String bilden
	fFeaturesStr = "";
	for (iarray_itr itr = fFeatures.begin(); itr != fFeatures.end(); itr++)
		{
		ilist_t& v = itr->second;
		if (fFeaturesStr == "")
			fFeaturesStr = String(v[0]);
		else
			fFeaturesStr += ";" + String(v[0]);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   private functions   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   getter und setter   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cFeaturesWaili3::get_alg_ident()
	{
	return fAlgIdent;
	}
//---------------------------------------------------------------------------
iarray_t cFeaturesWaili3::get_features()
	{
	return fFeatures;
	}
//---------------------------------------------------------------------------
String cFeaturesWaili3::get_features_string()
	{
	return fFeaturesStr;
	}
//---------------------------------------------------------------------------
