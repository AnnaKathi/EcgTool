/* LDA - Linear Discriminant Analysis (Klassifizierungsalg.)
 * ==================================
 * AKTUELL NUR SIMULATION !!
 */
//---------------------------------------------------------------------------
#pragma hdrstop

#include "classLDA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cLDA::cLDA()
	{
	}
//---------------------------------------------------------------------------
cLDA::~cLDA()
	{
	}
//---------------------------------------------------------------------------
double cLDA::singleCheck(iarray_t temp1, iarray_t temp2, int mode)
	{
	//SIMULATION
	Randomize();
	double conformity = 0.0;
	double range = Random();

	if (mode == 0) //intra
		{
		//gleichm��ige Wahrscheinlichkeit
			 if (range >= 0.66) conformity = Random(33) * 3.33;
		else if (range >= 0.33) conformity = Random(33) * 2.22;
		else                    conformity = Random(33) * 1.11;
		}
	else if (mode == 1) //inter
		{
		//mittlere Wahrscheinlichkeit
			 if (range >= 0.88) conformity = Random(33) * 3.33;
		else if (range >= 0.66) conformity = Random(33) * 2.22;
		else                    conformity = Random(33) * 1.11;
		}
	else //kreuz
		{
		//niedrige Wahrscheinlichkeit
			 if (range >= 0.99) conformity = Random(33) * 3.33;
		else if (range >= 0.88) conformity = Random(33) * 2.22;
		else                    conformity = Random(33) * 1.11;
		}

	return conformity;
	}
//---------------------------------------------------------------------------

