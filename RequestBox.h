//---------------------------------------------------------------------------
#ifndef RequestBoxH
#define RequestBoxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmRequest : public TForm
{
private:
	String	Answer;

__published:	// IDE-verwaltete Komponenten
	TMemo *mRequest;
	TEdit *edAnswer;
	TPanel *Panel1;
	TButton *btOk;
	TButton *btAbort;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btAbortClick(TObject *Sender);
	void __fastcall btOkClick(TObject *Sender);
	void __fastcall edAnswerKeyPress(TObject *Sender, char &Key);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);

public:
	__fastcall TfmRequest(TComponent* Owner);

	String	Execute(String msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmRequest *fmRequest;
String DlgRequest(TForm* Papa, String msg);
//---------------------------------------------------------------------------
#endif
