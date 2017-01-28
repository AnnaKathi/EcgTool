//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RequestBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmRequest *fmRequest;
//---------------------------------------------------------------------------
String DlgRequest(TForm* Papa, String msg)
	{
	TfmRequest* Form = new TfmRequest(Papa);
	String rc = "";

	if (Form)
		{
		rc = Form->Execute(msg);
		delete Form;
		}

	return rc;
	}
//---------------------------------------------------------------------------
String TfmRequest::Execute(String msg)
	{
	Answer = "";
	mRequest->Lines->Clear();
	mRequest->Text = msg;
	ShowModal();
	return Answer;
	}
//---------------------------------------------------------------------------
__fastcall TfmRequest::TfmRequest(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmRequest::FormShow(TObject *Sender)
	{
	edAnswer->Text = "";
	edAnswer->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmRequest::btAbortClick(TObject *Sender)
	{
	Answer = "";
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmRequest::btOkClick(TObject *Sender)
	{
	Answer = edAnswer->Text;
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmRequest::edAnswerKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_RETURN)
		{
		Key = 0;
		btOkClick(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmRequest::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		btAbortClick(Sender);
		}
	}
//---------------------------------------------------------------------------
