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

	bRun  = false;
	bStop = false;
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
	edInputfile->Text  = Ini->ReadString("EcgTool", "Inputfile", "");
	cbDelim->ItemIndex = Ini->ReadInteger("EcgTool", "ComboDelim", 0);

	edVonSample->Text = (String)Ini->ReadInteger("EcgTool", "edVonSample", 0);
	edBisSample->Text = (String)Ini->ReadInteger("EcgTool", "edBisSample", 0);

	btRead->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
	{
	Ini->WriteString("EcgTool", "Inputfile",   edInputfile->Text);
	Ini->WriteInteger("EcgTool", "ComboDelim", cbDelim->ItemIndex);

	Ini->WriteInteger("EcgTool", "edVonSample", edVonSample->Text.ToIntDef(0));
	Ini->WriteInteger("EcgTool", "edBisSample", edBisSample->Text.ToIntDef(0));

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
void TfmMain::Draw()
	{
	alg1.ecg.data.display(imgEcg);
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

	cData& data = alg1.ecg.data;
	if (!data.getFile(ecgFile, delim, vonSamp, bisSamp))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished readFile");
	Draw();
	}
//---------------------------------------------------------------------------
void TfmMain::Runden()
	{
	Print("rounding values...");
	int stellen = DlgRequest(this, "Anzahl Nachkommastellen").ToDouble();
	if (stellen <= 0) return;

	cData& data = alg1.ecg.data;
	if (!data.roundAt(stellen))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished rounding values");
	Draw();
	}
//---------------------------------------------------------------------------
void TfmMain::MovingAv()
	{
	Print("build moving average...");
	int window = DlgRequest(this, "Anzahl Werte im gleitenden Durchschnitt").ToIntDef(-1);
	if (window <= 0) return;

	bool calcBegin = true; //todo: abfragen

	cData& data = alg1.ecg.data;
	if (!data.movingAv(window, calcBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished moving average");
	Draw();
	}
//---------------------------------------------------------------------------
void TfmMain::CutCurve()
	{
	Print("cut curve...");
	int von = DlgRequest(this, "Werte löschen von Millisekunde").ToIntDef(-1);
	int bis = DlgRequest(this, "Werte löschen bis Millisekunde").ToIntDef(-1);
	if (von < 0 || bis < 0) return;
	if (bis < von) return;

	cData& data = alg1.ecg.data;
	int no = data.cut(von, bis);
	if (data.error)
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}

	Print("\tEs wurden %d Datensätze gelöscht", no);
	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished cutting");
	Draw();
	}
//---------------------------------------------------------------------------
void TfmMain::GetTurns()
	{
	Print("Wendepunkte berechnen...");
	float schwelle_proz = DlgRequest(this, "Schwellenwert für Wendepunkt-Berechnung").ToDouble();
	if (schwelle_proz < 0 || schwelle_proz > 1) return;

	cTurns& turns = alg1.ecg.turns;
	int no = turns.calcTurns(alg1.ecg.data, schwelle_proz);
	if (turns.error)
		{
		Print("## Fehler aufgetreten: %d, %s", turns.error_code, turns.error_msg);
		return;
		}

	Print("\tEs wurden %d Wendepunkte gefunden", no);
	Print("...finished turns");
	Draw();
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
void __fastcall TfmMain::btReadClick(TObject *Sender)
	{
	String cap = btRead->Caption;
	if (!bRun)
		{
		btRead->Caption = "&ABBRECHEN";
		bStop = false;
		bRun  = true;
		ReadFile();
		bRun = false;
		btRead->Caption = cap;
		}
	else
		{
		bStop = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btRundenClick(TObject *Sender)
	{
	String cap = btRunden->Caption;
	if (!bRun)
		{
		btRunden->Caption = "&ABBRECHEN";
		bStop = false;
		bRun  = true;
		Runden();
		bRun = false;
		btRunden->Caption = cap;
		}
	else
		{
		bStop = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btMovAvClick(TObject *Sender)
	{
	String cap = btMovAv->Caption;
	if (!bRun)
		{
		btMovAv->Caption = "&ABBRECHEN";
		bStop = false;
		bRun  = true;
		MovingAv();
		bRun = false;
		btMovAv->Caption = cap;
		}
	else
		{
		bStop = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btCutClick(TObject *Sender)
	{
	String cap = btCut->Caption;
	if (!bRun)
		{
		btCut->Caption = "&ABBRECHEN";
		bStop = false;
		bRun  = true;
		CutCurve();
		bRun = false;
		btCut->Caption = cap;
		}
	else
		{
		bStop = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btTurnsClick(TObject *Sender)
	{
	String cap = btTurns->Caption;
	if (!bRun)
		{
		btTurns->Caption = "&ABBRECHEN";
		bStop = false;
		bRun  = true;
		GetTurns();
		bRun = false;
		btTurns->Caption = cap;
		}
	else
		{
		bStop = true;
		}
	}
//---------------------------------------------------------------------------

