//---------------------------------------------------------------------------
#ifndef classACH
#define classACH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
//---------------------------------------------------------------------------
//typedef std::vector<float> float_vec_t; -> ist das gleiche wie: typedef std::vector<float> ilist_t;
//---------------------------------------------------------------------------
//! Die Klasse cAC bietet Funktionalit�ten an, um eine Autokorrelation erstellen zu k�nnen
class PACKAGE cAC : public cBase
	{
public:
	cAC(); //! Konstruktor f�r cAC
	~cAC(); //! Destruktor f�r cAC

	//! Erstellt �ber dem �bergebenen Array eine AC
	/*! �ber dem �bergebenen Array wird eine AC erstellt.
	 *  /param (std::map) array
	 *  /raturn (std::map) AC-Array
	 */
	iarray_t	buildAC(iarray_t array);

	//! Erstellt das AC-Template
	/*! Aus dem �bergebenen Standardherzschlag wird eine AC gebildet und
	 *  zur�ckgegeben. Der aufrufende Algorithmus k�mmert sich um Auswertung
	 *  und Speicherung usw.\r\n
	 *  Intern ruft createTemplate() die Funktion buildAC() auf.
	 *  /param (std::map) Standardherzschlag
	 *  /return (boll) true wenn erfolgreich, sonst false
	 */
	bool		createTemplate(iarray_t herzschlag);

__property iarray_t temp = { read=get_template };
private:
	iarray_t	ftemplate;
	iarray_t	get_template();

	iarray_t	buildACOld(iarray_t array);
	};
//---------------------------------------------------------------------------
#endif
