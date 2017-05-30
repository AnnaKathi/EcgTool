//---------------------------------------------------------------------------
#ifndef definitionsH
#define definitionsH
//---------------------------------------------------------------------------
//----- Datenbank-Handling --------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/* Lage in der ein EKG aufgenommen wurde, z.B. liegend oder stehend */
enum eLage
	{
	lageNone = 0,
	lageLiegend,
	lageSitzend,
	lageStehend,
	lageGehend
	};
//---------------------------------------------------------------------------
/* State (Zustand) in dem ein EKG erfasst wurde, z.B. 'in Ruhe' */
enum eState
	{
	stateNone = 0,
	stateInRuhe,         //keine Bewegung vor der Messung, bis Puls 80 ??
	stateNachWenigBew,	 //leichte Bewegung vor der Messung, ab Puls 80 ??
	stateNachMittelBew,  //m‰ﬂige Bewegung vor der Messung, ab Puls 120 ??
	stateNachVielBew,    //viel Bewegung vor der Messung, ab Puls 160 ??
	stateInBew           //w‰hrend der Bewegung
	};
//---------------------------------------------------------------------------
/* Format der einzulesenden Datei */
enum eDatFormat
	{
	formatNone = 0, //kein Format gesetzt, einfach zeilenweise parsen
	formatADS,		//Format ADS1298 von Texas Instruments
	};
//---------------------------------------------------------------------------
/* Modus der baseForms */
enum eListMode
	{
	eShow = 0,  	//Datens‰tze anzeigen, DblClick = Datensatz ‰ndern
	eSingleSelect,	//Datens‰tze anzeigen, DblClick = einen Datensatz ausw‰hlen
	eMultiSelect,	//Datens‰tze anzeigen, DblClick = mehrere Idents ausw‰hlen
	};
//---------------------------------------------------------------------------
#endif
