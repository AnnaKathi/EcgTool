//---------------------------------------------------------------------------
#ifndef classDerivateH
#define classDerivateH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
#include "classMath.h"
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
class PACKAGE cDerivate : public cBase
	{
public:
	cDerivate();
	~cDerivate();

	sArrayCha	farr_charac; //todo getter und setter machen

	bool		build(iarray_t array);
	void 		resetValues();
	bool 		display(TImage* img);

__property iarray_t	deriv_array = { read=get_array };

private:
	cMath*		fmath;

	iarray_t	farr;
	iarray_t	get_array();

	};
//---------------------------------------------------------------------------
#endif
