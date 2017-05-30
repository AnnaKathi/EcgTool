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
	eShow = 0,  	//Datensätze anzeigen, DblClick = Datensatz ändern
	eSingleSelect,	//Datensätze anzeigen, DblClick = einen Datensatz auswählen
	eMultiSelect,	//Datensätze anzeigen, DblClick = mehrere Idents auswählen
	};
//---------------------------------------------------------------------------
#endif
