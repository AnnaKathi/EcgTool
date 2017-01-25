//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
	{
	char path[MAX_PATH];
	strcpy(path, Application->ExeName.c_str());
	char* pt = strrchr(path, '\\');
	if (pt != 0)
		*pt = 0;

	String file = String(path) + "\\EcgTool.ini";
	Ini = new TIniFile(file);
	}
//---------------------------------------------------------------------------
__fastcall TfmMain::~TfmMain()
	{
	delete Ini;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	edInputfile->Text = Ini->ReadString("EcgTool", "Inputfile", "");

	edVonIdx->Text  = (String)Ini->ReadInteger("EcgTool", "VonIdx",  0);
	edBisIdx->Text  = (String)Ini->ReadInteger("EcgTool", "BisIdx",  0);
	edVonMsec->Text = (String)Ini->ReadInteger("EcgTool", "VonMsec", 0);
	edBisMsec->Text = (String)Ini->ReadInteger("EcgTool", "BisMsec", 0);
	edMinWert->Text = (String)Ini->ReadInteger("EcgTool", "MinWert", 0);
	edMaxWert->Text = (String)Ini->ReadInteger("EcgTool", "MaxWert", 0);

	Print("EcgTool gestartet");
	btRead->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
	{
	Ini->WriteString("EcgTool", "Inputfile", edInputfile->Text);

	Ini->WriteInteger("EcgTool", "VonIdx",  	 edVonIdx->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "BisIdx",  	 edBisIdx->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "VonMsec",  	 edVonMsec->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "BisMsec",  	 edBisMsec->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "MinWert",  	 edMinWert->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "MaxWert",  	 edMaxWert->Text.ToIntDef(0));

	Ini->UpdateFile();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmMain::Print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::laClsClick(TObject *Sender)
	{
	memo->Lines->Clear();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btInputfileClick(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	edInputfile->Text = OpenDialog->FileName;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btReadClick(TObject *Sender)
	{
	Print("pressed btRead...");
	}
//---------------------------------------------------------------------------

