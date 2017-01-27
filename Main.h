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
class TForm1 : public TForm
{
__published:	// IDE-verwaltete Komponenten
	TButton *Button1;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall Button1Click(TObject *Sender);
private:	// Benutzer Deklarationen
	cAlg1		alg1;

public:		// Benutzer Deklarationen
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
