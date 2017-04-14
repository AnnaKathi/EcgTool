//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DataAnalysis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmAnalysis *fmAnalysis;
//---------------------------------------------------------------------------
bool DlgAnalyseData(TForm* Papa)
	{
	TfmAnalysis* Form = new TfmAnalysis(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmAnalysis::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmAnalysis::TfmAnalysis(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmAnalysis::~TfmAnalysis()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::acLoadFileExecute(TObject *Sender)
	{
	if (OpenDialog->Execute())
		edInputfile->Text = OpenDialog->FileName;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::acReadFileExecute(TObject *Sender)
	{
	String ecgFile = edInputfile->Text;
	if (ecgFile == "") return;

	//todo, über dyn Importschemata wählen lassen
	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	int vonSamp = 1;
	int bisSamp = 3000;

	//-- EKG-Daten
	cData& data = fecg.data;
	if (!data.getFile(ecgFile, delim, vonSamp, bisSamp))
		{
		//Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		int bp = 0;
		return;
		}

	data.redisplay(imgData);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmAnalysis::btInputfileClick(TObject *Sender)
	{
	acLoadFileExecute(Sender);
	}
//---------------------------------------------------------------------------

