	/* Testcode
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

	String m = alg1.ecg.csv.readFile("test");
	Label3->Caption = m;
	*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "RequestBox.h"
#include "Details.h"
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

	fmDetails = new TfmDetails(this);
	fmDetails->Hide();
	bDisplayedDetails = false;

	bRun  = false;
	bStop = false;
	}
//---------------------------------------------------------------------------
__fastcall TfmMain::~TfmMain()
	{
	delete fmDetails;
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
	edInputfile->Text  = Ini->ReadString("EcgTool", "Inputfile", "");
	cbDelim->ItemIndex = Ini->ReadInteger("EcgTool", "ComboDelim", 0);

	edVonSample->Text = (String)Ini->ReadInteger("EcgTool", "edVonSample", 0);
	edBisSample->Text = (String)Ini->ReadInteger("EcgTool", "edBisSample", 0);

	edCutVon->Text = (String)Ini->ReadInteger("EcgTool", "edCutVon", 0);
	edCutBis->Text = (String)Ini->ReadInteger("EcgTool", "edCutBis", 0);

	edGl1->Text = (String)Ini->ReadInteger("EcgTool", "edGl1", 0);
	edGl2->Text = (String)Ini->ReadInteger("EcgTool", "edGl2", 0);
	edGl3->Text = (String)Ini->ReadInteger("EcgTool", "edGl3", 0);

	cxDropBegin->Checked = Ini->ReadBool("EcgTool", "cxDropBegin", false);

	Left = Ini->ReadInteger("EcgTool", "Left", -1);
	if (Left <= 0) 	Left = (Screen->DesktopWidth - Width)/2;  //mittig ausrichten

	Top  = Ini->ReadInteger("EcgTool", "Top",  -1);
	if (Top <= 0) 	Top = (Screen->DesktopHeight - Height)/2; //mittig ausrichten

	btRead->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
	{
	Ini->WriteString("EcgTool", "Inputfile",   edInputfile->Text);
	Ini->WriteInteger("EcgTool", "ComboDelim", cbDelim->ItemIndex);

	Ini->WriteInteger("EcgTool", "edVonSample", edVonSample->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "edBisSample", edBisSample->Text.ToIntDef(0));

	Ini->WriteInteger("EcgTool", "edCutVon", edCutVon->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "edCutBis", edCutBis->Text.ToIntDef(0));

	Ini->WriteInteger("EcgTool", "edGl1", edGl1->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "edGl2", edGl2->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "edGl3", edGl3->Text.ToIntDef(0));

	Ini->WriteBool("EcgTool", "cxDropBegin", cxDropBegin->Checked);

	Ini->WriteInteger("EcgTool", "Left", Left);
	Ini->WriteInteger("EcgTool", "Top",  Top);

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
void TfmMain::ReadFile()
	{
	Print("start readFile...");
	String ecgFile = edInputfile->Text;
	if (ecgFile == "") return;

	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	int vonSamp = edVonSample->Text.ToIntDef(-1);
	int bisSamp = edBisSample->Text.ToIntDef(-1);

	//-- EKG-Daten
	cData& data = alg1.ecg.data;
	if (!data.getFile(ecgFile, delim, vonSamp, bisSamp))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	alg1.ecg.data.redisplay(imgEcg);

	//-- Erste und zweite Ableitung
	if (!data.buildDerivates())
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	alg1.ecg.data.derivate1.redisplay(imgDeriv1);
	alg1.ecg.data.derivate2.redisplay(imgDeriv2);

	Print("\tDatens�tze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished readFile");

	//Detail-Werte anzeigen
	if (!bDisplayedDetails)
		{
		fmDetails->Execute(fmMain, alg1);
		bDisplayedDetails = true;
		}
	else
		fmDetails->Renew(alg1);
	}
//---------------------------------------------------------------------------
void TfmMain::CutCurve()
	{
	Print("cut curve...");
	/* obsolete, Bereich wird nun �ber das Formular angegeben
	int von = DlgRequest(this, "Werte l�schen von Millisekunde").ToIntDef(-1);
	int bis = DlgRequest(this, "Werte l�schen bis Millisekunde").ToIntDef(-1);
	*/

	int von = edCutVon->Text.ToIntDef(-1);
	int bis = edCutBis->Text.ToIntDef(-1);
	if (von < 0 || bis < 0) return;
	if (bis < von) return;

	//-- EKG-Daten
	cData& data = alg1.ecg.data;
	if (!data.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	alg1.ecg.data.redisplay(imgEcg);

	//-- Erste Ableitung
	cDerivate& deriv1 = alg1.ecg.data.derivate1;
	if (!deriv1.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv1.error_code, deriv1.error_msg);
		return;
		}
	alg1.ecg.data.derivate1.redisplay(imgDeriv1);

	//-- Zweite Ableitung
	cDerivate& deriv2 = alg1.ecg.data.derivate2;
	if (!deriv2.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv2.error_code, deriv2.error_msg);
		return;
		}
	alg1.ecg.data.derivate2.redisplay(imgDeriv2);

	Print("\tDatens�tze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished cutting");

	//Detail-Werte aktuelisieren
	fmDetails->Renew(alg1);
	}
//---------------------------------------------------------------------------
void TfmMain::MovingAv()
	{
	Print("build moving average...");
	/* obsolete, Werte werden �ber das Formular angegeben
	int window = DlgRequest(this, "Anzahl Werte im gleitenden Durchschnitt").ToIntDef(-1);
	*/

	int window1 = edGl1->Text.ToIntDef(-1);
	int window2 = edGl2->Text.ToIntDef(-1);
	int window3 = edGl3->Text.ToIntDef(-1);
	if (window1 <= 0 || window2 <= 0 || window3 <= 0) return;

	bool dropBegin = cxDropBegin->Checked;

	//-- EKG-Daten
	cData& data = alg1.ecg.data;
	if (!data.movingAv(window1, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	alg1.ecg.data.redisplay(imgEcg);

	//-- Erste Ableitung
	cDerivate& deriv1 = alg1.ecg.data.derivate1;
	if (!deriv1.movingAv(window2, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv1.error_code, deriv1.error_msg);
		return;
		}
	alg1.ecg.data.derivate1.redisplay(imgDeriv1);

	//-- Zweite Ableitung
	cDerivate& deriv2 = alg1.ecg.data.derivate2;
	if (!deriv2.movingAv(window3, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv2.error_code, deriv2.error_msg);
		return;
		}
	alg1.ecg.data.derivate2.redisplay(imgDeriv2);

	Print("\tDatens�tze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished moving average");

	//Detail-Werte aktuelisieren
	fmDetails->Renew(alg1);
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
	else if (Key == VK_F12)
		{
		Key = 0;
		btInputfileClick(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
	{
	if (Shift.Contains(ssShift) && Key == VK_F11)
		{
		btInputfileClick(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btInputfileClick(TObject *Sender)
	{
	if (OpenDialog->Execute())
    	edInputfile->Text = OpenDialog->FileName;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::laClsClick(TObject *Sender)
	{
	memo->Lines->Clear();
	}
//---------------------------------------------------------------------------
void TfmMain::sendClick(TButton* bt)
	{
	String cap = bt->Caption;
	if (!bRun)
		{
		bt->Caption = "&ABBRECHEN";
		bStop = false;
		bRun  = true;

		switch (bt->Tag)
			{
			case  1: ReadFile(); 		break;
			case  2: CutCurve();		break;
			case  3: MovingAv();		break;
			//default, nicht n�tig
			}

		bRun = false;
		bt->Caption = cap;
		}
	else
		{
		bStop = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btReadClick(TObject *Sender)
	{
	sendClick(btRead);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btCutClick(TObject *Sender)
	{
	sendClick(btCut);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btMovAvClick(TObject *Sender)
	{
	sendClick(btMovAv);
	}
//---------------------------------------------------------------------------

