//---------------------------------------------------------------------------
#ifndef classMathH
#define classMathH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "classBase.h"
//---------------------------------------------------------------------------
//! bietet mathematische Grundfunktionen an
/*! Die Klasse cMath bietet verschiedenen mathematische Grundfunktionen an:\r\n
 *  <ul><li>Ableitung berechnen
 *  <li>Array sortieren</ul>
 */
class PACKAGE cMath : public cBase
	{
public:
	cMath();  //!< Konstruktor f�r cMath
	~cMath(); //!< Destruktor f�r cMath

	//! Ableitung �ber einem Array berechnen
	/*! Erstellt die Ableitung �ber dem �bergebenen Array
	 *  /param (std::map) Array mit float-Werten
	 *  /return (std::map) Array mit Steigungs-Werten = Ableitung
	 */
	iarray_t	calcDerivate(iarray_t array);

	//! Array sortieren (auf- oder absteigend)
	/*! Das �bergebene Array wird neu sortiert (auf- oder absteigend)
	 *  /param (std::map) Array das sortiert werden soll
	 *  /param (bool) asc, wenn true wird aufsteigend, sonst absteigend sortiert
	 *  /return (std::map) sortiertes Array
	 */
	iarray_t	resort(iarray_t array, bool asc);

private:

	};
//---------------------------------------------------------------------------
#endif
