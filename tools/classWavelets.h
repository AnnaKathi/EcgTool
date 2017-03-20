//---------------------------------------------------------------------------
#ifndef classWaveletsH
#define classWaveletsH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
//---------------------------------------------------------------------------
//! Die Klasse cWavelet bietet Funktionen zur Wavelet-Analyse und - Synthese
/*! Wavelet-Transformation = lineare Zeit-Frequenz-Fransformation, Wavelet-Analyse
 *  und -Synthese. Die zeitliche lokalisierten "Wellchen" dienen als Basis zur
 *  Transformation. \r\n
 *  \r\n
 *  <u>Haar-Wavelet</u>\r\n
 *  Die einfachste Ausführung eines Wavelets ist das sogenannte Haar-Wavelet.
 */
class PACKAGE cWavelets : public cBase
	{
public:
	cWavelets();
	~cWavelets();

private:
	};
//---------------------------------------------------------------------------
#endif
