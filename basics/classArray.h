//---------------------------------------------------------------------------
#ifndef classArrayH
#define classArrayH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
typedef struct sARRAYCHA //Charkterwerte eines Arrays
	{
	int			VonIdx;  //kleinster Index
	int			BisIdx;  //gr��ter Index
	int			VonMsec; //kleinster Millisek.wert
	int			BisMsec; //gr��ter Millisek.wert
	float		MinWert; //tiefster Wert (Ausschlag)
	float		MaxWert; //h�chster Wert (Ausschlag)
	int			Number;  //Anzahl Datens�tze im Array
	} sArrayCha;
//---------------------------------------------------------------------------
class PACKAGE cArray : public cBase
	{
public:
	cArray();
	~cArray();

	sArrayCha	farr_charac; //todo getter und setter machen

	bool 		resetValues(sArrayCha& cha);
	bool 		display(iarray_t array, TImage* img);

	iarray_t 	roundAt(iarray_t array, int nachkommastellen);
	iarray_t 	movingAv(iarray_t array, int window, bool CalcBegin);
	iarray_t 	cut(iarray_t array, int vonMsec, int bisMsec);

private:
	iarray_t	farr;


	};
//---------------------------------------------------------------------------
#endif
