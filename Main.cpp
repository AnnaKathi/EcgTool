//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
	{
	cQrs& q = alg1.ecg.qrs;  //wenn nur eins verwendet wird
	q.run();

	cQrs q1 = alg1.ecg.qrs; //das ist eine Kopie !
	// q.data = q1.data

	alg1.ecg.qrs.run();
	alg1.ecg.heart.run();

	int no = q.calc();
	Label1->Caption = "QRS hat ausgerechnet: " + String(no);

	no = alg1.ecg.heart.calc();
	Label2->Caption = "Heartbeat meldet: " + String(no);
	}
//---------------------------------------------------------------------------
