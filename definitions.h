//---------------------------------------------------------------------------
#ifndef definitionsH
#define definitionsH
//---------------------------------------------------------------------------
//----- Datenbank-Handling --------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/* Position in der ein EKG aufgenommen wurde, z.B. liegend oder stehend */
enum ePosition
	{
	posNone = 0,
	posLiegend,
	posSitzend,
	posStehend,
	posGehend
	};
//---------------------------------------------------------------------------
/* Format der einzulesenden Datei */
enum eDatFormat
	{
	formatNone = 0, //kein Format gesetzt, einfach zeilenweise parsen
	formatADS,		//Format ADS1298 von Texas Instruments
	};
//---------------------------------------------------------------------------
#endif
