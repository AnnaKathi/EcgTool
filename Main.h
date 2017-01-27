//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "classAlg1.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// IDE-verwaltete Komponenten
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// Benutzer Deklarationen
	cAlg1		alg1;

public:		// Benutzer Deklarationen
	__fastcall TfmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
