//---------------------------------------------------------------------------
#ifndef classDataH
#define classDataH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.cpp"
#include "classCsv.h"
#include "classArray.h"
#include "classDerivate.h"
//---------------------------------------------------------------------------
/*
typedef struct sARRAYCHA //Charkterwerte eines Arrays
	{
	int			VonIdx;  //kleinster Index
	int			BisIdx;  //größter Index
	int			VonMsec; //kleinster Millisek.wert
	int			BisMsec; //größter Millisek.wert
	float		MinWert; //tiefster Wert (Ausschlag)
	float		MaxWert; //höchster Wert (Ausschlag)
	int			Number;  //Anzahl Datensätze im Array
	} sArrayCha;
//---------------------------------------------------------------------------
*/
class PACKAGE cData : public cBase
	{
public:
	cData();
	~cData();

	sArrayCha	farr_charac; //todo getter und setter machen
	bool		getFile(String file, String delim, int vonMsec, int bisMsec);
	bool		display(TImage* img);
	bool		roundAt(int nachkommastellen);
	bool		movingAv(int window, bool CalcBegin = true);
	int			cut(int vonMsec, int bisMsec);

	//------- mathematische Funktionen --------------------------------------
	bool		buildDerivates();

__property iarray_t   data_array = { read=get_array  };
__property cDerivate& derivate1  = { read=get_deriv1 };
__property cDerivate& derivate2  = { read=get_deriv2 };

private:
	cCsv*		fcsv;

	cDerivate*	fderiv1; //erste Ableitung
	cDerivate&	get_deriv1();

	cDerivate*	fderiv2; //zweite Ableitung
	cDerivate&	get_deriv2();

	cArray*		farray; //Klasse mit Grundfunktionalitäten

	iarray_t	farr;  //alle eingelesenen EKG-Werte
	iarray_t	get_array();

	void 		resetValues();


	};
//---------------------------------------------------------------------------
#endif
