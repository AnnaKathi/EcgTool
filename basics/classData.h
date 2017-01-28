//---------------------------------------------------------------------------
#ifndef classDataH
#define classDataH
//---------------------------------------------------------------------------
#include <map>
#include <vector>
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.cpp"
#include "classCsv.h"
//---------------------------------------------------------------------------
typedef std::vector<float> ilist_t;
typedef std::map<float,ilist_t> iarray_t;
typedef iarray_t::iterator iarray_itr;
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

private:
	cCsv*		fcsv;
	iarray_t	farr;  //alle eingelesenen EKG-Werte

	void 		resetValues();

	};
//---------------------------------------------------------------------------
#endif
