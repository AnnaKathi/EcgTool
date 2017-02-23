//---------------------------------------------------------------------------
#ifndef classDerivateH
#define classDerivateH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
#include "classArray.h"
#include "classMath.h"
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
class PACKAGE cDerivate : public cBase
	{
public:
	cDerivate();
	~cDerivate();

	sArrayCha	farr_charac; //todo getter und setter machen

	bool		build(iarray_t array);
	bool 		redisplay(TImage* img);

	bool		movingAv(int window, bool CalcBegin = true);
	int			cut(int vonMsec, int bisMsec);
	
__property iarray_t	deriv_array = { read=get_array };

private:
	cMath*		fmath;
	cArray*		farray; //Grundfunktionalitäten

	iarray_t	farr;
	iarray_t	get_array();

	};
//---------------------------------------------------------------------------
#endif
