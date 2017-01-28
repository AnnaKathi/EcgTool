//---------------------------------------------------------------------------
#ifndef classDataH
#define classDataH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.cpp"
#include "classCsv.h"
//---------------------------------------------------------------------------
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
	bool		calcDerivates();

__property iarray_t data_array = { read=get_array };

private:
	cCsv*		fcsv;
	iarray_t	farr;  //alle eingelesenen EKG-Werte
	iarray_t	fderiv1; //erste Ableitung

	void 		resetValues();

	iarray_t	get_array();

	};
//---------------------------------------------------------------------------
#endif
