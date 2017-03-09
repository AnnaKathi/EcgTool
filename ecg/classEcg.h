//---------------------------------------------------------------------------
#ifndef classEcgH
#define classEcgH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classData.h"
//---------------------------------------------------------------------------
#include "classRpeaks.h"
#include "classTurns.h"
#include "classQrs.h"
#include "classHeartbeat.h"
//---------------------------------------------------------------------------
//! Kapselt ein EKG
/*! Die Klasse cEcg kapselt die Daten und Funktionalitäten eines EKGs (welches
 *  zu einer bestimmten Person in einer bestimmten Lage (Position) gehört.
 *  Ein EKG hat:\r\n
 *  <ul><li>Daten (cData), die elektrischen Ausschläge
 *  <li>R-Peaks (cRpeaks) und QRS-Bereiche (cQrs)
 *  <li>einen Standardherzschlag
 */
class PACKAGE cEcg : public cBase
	{
public:
	cEcg();  //!< Konstruktor für cEcg
	~cEcg(); //!< Destruktor für cEcg

__property cData& data 		  = { read=get_data };  //!< Daten des EKGs (Ausschläge der leads)
__property cRpeaks& rpeaks	  = { read=get_rpeaks };//!< R-Peaks des EKG
__property cTurns& turns	  = { read=get_turns }; //!< Wendepunkte des EKG
__property cQrs& qrs 		  = { read=get_qrs };   //!< QRS-Bereiche des EKG
__property cHeartbeats& heart = { read=get_heart }; //!< Standardherzschlag des EKG

private:
	cData*		fdata;
	cData&		get_data();

	cRpeaks*	frpeaks;
	cRpeaks&	get_rpeaks();

	cTurns*		fturns;
	cTurns&		get_turns();

	cQrs*		fqrs;
	cQrs&		get_qrs();

	cHeartbeats*	fheart;
	cHeartbeats&	get_heart();
	};
//---------------------------------------------------------------------------
#endif
