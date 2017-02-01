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
	alg1.ecg.data.display(imgEcg);

	img2->Canvas->Brush->Color = clWhite;
	img2->Canvas->FillRect(Rect(0, 0, img2->Picture->Width, img2->Picture->Height));
	img2->Canvas->Pen->Color = clBlack;

	img3->Canvas->Brush->Color = clWhite;
	img3->Canvas->FillRect(Rect(0, 0, img3->Picture->Width, img3->Picture->Height));
	img3->Canvas->Pen->Color = clBlack;
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
	alg1.ecg.data.display(imgEcg);
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
	alg1.ecg.data.display(imgEcg);
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
	alg1.ecg.data.display(imgEcg);
	}
//---------------------------------------------------------------------------
void TfmMain::FindRpeaks()
	{
	Print("R-Peaks finden...");

	cRpeaks& rpeaks = alg1.ecg.rpeaks;
	iarray_t asc = rpeaks.find(alg1.ecg.data.data_array, img2, img3);

	Print("...finished r-peaks");
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Funktionen auf erster Ableitung   ************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmMain::Derivate1()
	{
	Print("Erste Ableitung berechnen...");

	cData& data = alg1.ecg.data;
	if (!data.buildDerivates())
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}

	alg1.ecg.data.derivate1.display(img2);

	Print("...Berechnung der Ableitungen abgeschlossen");
	}
//---------------------------------------------------------------------------
void TfmMain::Abl1Runden()
	{
	Print("ERSTE ABLEITUNG rounding values...");
	int stellen = DlgRequest(this, "Anzahl Nachkommastellen").ToDouble();
	if (stellen <= 0) return;

	cDerivate& deriv = alg1.ecg.data.derivate1;
	if (!deriv.roundAt(stellen))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv.error_code, deriv.error_msg);
		return;
		}

	Print("\tDatensätze im Array: %d", deriv.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", deriv.farr_charac.VonIdx, deriv.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", deriv.farr_charac.VonMsec, deriv.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", deriv.farr_charac.MinWert, deriv.farr_charac.MaxWert);

	Print("...finished rounding values");
	alg1.ecg.data.derivate1.display(img2);
	}
//---------------------------------------------------------------------------
void TfmMain::Abl1MovingAv()
	{
	Print("ERSTE ABLEITUNG build moving average...");
	int window = DlgRequest(this, "Anzahl Werte im gleitenden Durchschnitt").ToIntDef(-1);
	if (window <= 0) return;

	bool calcBegin = true; //todo: abfragen

	cDerivate& deriv = alg1.ecg.data.derivate1;
	if (!deriv.movingAv(window, calcBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv.error_code, deriv.error_msg);
		return;
		}

	Print("\tDatensätze im Array: %d", deriv.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", deriv.farr_charac.VonIdx, deriv.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", deriv.farr_charac.VonMsec, deriv.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", deriv.farr_charac.MinWert, deriv.farr_charac.MaxWert);

	Print("...finished moving average");
	alg1.ecg.data.derivate1.display(img2);
	}
//---------------------------------------------------------------------------
void TfmMain::Abl1CutCurve()
	{
	Print("ERSTE ABLEITUNG cut curve...");
	int von = DlgRequest(this, "Werte löschen von Millisekunde").ToIntDef(-1);
	int bis = DlgRequest(this, "Werte löschen bis Millisekunde").ToIntDef(-1);
	if (von < 0 || bis < 0) return;
	if (bis < von) return;

	cDerivate& deriv = alg1.ecg.data.derivate1;
	int no = deriv.cut(von, bis);
	if (deriv.error)
		{
		Print("## Fehler aufgetreten: %d, %s", deriv.error_code, deriv.error_msg);
		return;
		}

	Print("\tEs wurden %d Datensätze gelöscht", no);
	Print("\tDatensätze im Array: %d", deriv.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", deriv.farr_charac.VonIdx, deriv.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", deriv.farr_charac.VonMsec, deriv.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", deriv.farr_charac.MinWert, deriv.farr_charac.MaxWert);

	Print("...finished cutting");
	alg1.ecg.data.derivate1.display(img2);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Funktionen auf zweiter Ableitung   ***********************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmMain::Derivate2()
	{
	Print("Zweite Ableitung berechnen...");

	cData& data = alg1.ecg.data;
	if (!data.buildDerivates())
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}

	alg1.ecg.data.derivate2.display(img3);

	Print("...Berechnung der Ableitungen abgeschlossen");
	}
//---------------------------------------------------------------------------
void TfmMain::Abl2Runden()
	{
	Print("ZWEITE ABLEITUNG rounding values...");
	int stellen = DlgRequest(this, "Anzahl Nachkommastellen").ToDouble();
	if (stellen <= 0) return;

	cDerivate& deriv = alg1.ecg.data.derivate2;
	if (!deriv.roundAt(stellen))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv.error_code, deriv.error_msg);
		return;
		}

	Print("\tDatensätze im Array: %d", deriv.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", deriv.farr_charac.VonIdx, deriv.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", deriv.farr_charac.VonMsec, deriv.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", deriv.farr_charac.MinWert, deriv.farr_charac.MaxWert);

	Print("...finished rounding values");
	alg1.ecg.data.derivate2.display(img3);
	}
//---------------------------------------------------------------------------
void TfmMain::Abl2MovingAv()
	{
	Print("ZWEITE ABLEITUNG build moving average...");
	int window = DlgRequest(this, "Anzahl Werte im gleitenden Durchschnitt").ToIntDef(-1);
	if (window <= 0) return;

	bool calcBegin = true; //todo: abfragen

	cDerivate& deriv = alg1.ecg.data.derivate2;
	if (!deriv.movingAv(window, calcBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv.error_code, deriv.error_msg);
		return;
		}

	Print("\tDatensätze im Array: %d", deriv.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", deriv.farr_charac.VonIdx, deriv.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", deriv.farr_charac.VonMsec, deriv.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", deriv.farr_charac.MinWert, deriv.farr_charac.MaxWert);

	Print("...finished moving average");
	alg1.ecg.data.derivate2.display(img3);
	}
//---------------------------------------------------------------------------
void TfmMain::Abl2CutCurve()
	{
	Print("ZWEITE ABLEITUNG cut curve...");
	int von = DlgRequest(this, "Werte löschen von Millisekunde").ToIntDef(-1);
	int bis = DlgRequest(this, "Werte löschen bis Millisekunde").ToIntDef(-1);
	if (von < 0 || bis < 0) return;
	if (bis < von) return;

	cDerivate& deriv = alg1.ecg.data.derivate2;
	int no = deriv.cut(von, bis);
	if (deriv.error)
		{
		Print("## Fehler aufgetreten: %d, %s", deriv.error_code, deriv.error_msg);
		return;
		}

	Print("\tEs wurden %d Datensätze gelöscht", no);
	Print("\tDatensätze im Array: %d", deriv.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", deriv.farr_charac.VonIdx, deriv.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", deriv.farr_charac.VonMsec, deriv.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", deriv.farr_charac.MinWert, deriv.farr_charac.MaxWert);

	Print("...finished cutting");
	alg1.ecg.data.derivate2.display(img3);
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
			case  2: Runden();			break;
			case  3: MovingAv();		break;
			case  4: CutCurve();		break;
			case  5: FindRpeaks();		break;
			case  6: Derivate1();		break;
			case  7: Abl1Runden();		break;
			case  8: Abl1MovingAv();	break;
			case  9: Abl1CutCurve();	break;
			case 10: break;
			case 11: Derivate2();		break;
			case 12: Abl2Runden();		break;
			case 13: Abl2MovingAv();	break;
			case 14: Abl2CutCurve();	break;
			case 15: break;
			//default, nicht nötig
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
void __fastcall TfmMain::btRundenClick(TObject *Sender)
	{
	sendClick(btRunden);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btMovAvClick(TObject *Sender)
	{
	sendClick(btMovAv);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btCutClick(TObject *Sender)
	{
	sendClick(btCut);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btRpeaksClick(TObject *Sender)
	{
	sendClick(btRpeaks);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btDerivatesClick(TObject *Sender)
	{
	sendClick(btDerivates);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAblRundenClick(TObject *Sender)
	{
	sendClick(btAblRunden);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAblMovAvClick(TObject *Sender)
	{
	sendClick(btAblMovAv);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAblCutClick(TObject *Sender)
	{
	sendClick(btAblCut);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAblTurnsClick(TObject *Sender)
	{
	sendClick(btAblTurns);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAbl2Click(TObject *Sender)
	{
    sendClick(btAbl2);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAbl2RundenClick(TObject *Sender)
	{
	sendClick(btAbl2Runden);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAbl2MovAvClick(TObject *Sender)
	{
	sendClick(btAbl2MovAv);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAbl2CutClick(TObject *Sender)
	{
    sendClick(btAbl2Cut);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btAbl2TurnsClick(TObject *Sender)
	{
	sendClick(btAbl2Turns);
	}
//---------------------------------------------------------------------------

