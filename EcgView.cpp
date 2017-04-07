//Todo: Position in Lage umbennen ?
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "algorithms/Alg1.h"
#include "algorithms/features/classAC.h"

#include "RequestBox.h"
#include "Details.h"
#include "EcgView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmEcg *fmEcg;
//---------------------------------------------------------------------------
__fastcall TfmEcg::TfmEcg(TComponent* Owner)
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
__fastcall TfmEcg::~TfmEcg()
	{
	delete fmDetails;
	delete Ini;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);

	btRead->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
bool TfmEcg::Execute()
	{
	//todo Formular ausrichten
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Grundfunktionen   ************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmEcg::Print(char* msg, ...)
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
/******************   EKG-Funktionen   *************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmEcg::ReadFile()
	{
	Print("start readFile...");
	String ecgFile = edInputfile->Text;
	if (ecgFile == "") return;

	//todo, über dyn Importschemata wählen lassen
	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	int vonSamp = edVonSample->Text.ToIntDef(-1);
	int bisSamp = edBisSample->Text.ToIntDef(-1);

	//-- EKG-Daten
	cData& data = ecg.data;
	if (!data.getFile(ecgFile, delim, vonSamp, bisSamp))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	data.redisplay(imgEcg);

	//-- Erste und zweite Ableitung
	if (!data.buildDerivates())
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	data.derivate1.redisplay(imgDeriv1);
	data.derivate2.redisplay(imgDeriv2);

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished readFile");

	//Detail-Werte anzeigen
	if (!bDisplayedDetails)
		{
		fmDetails->Execute(this, ecg);
		bDisplayedDetails = true;
		}
	else
		fmDetails->Renew(ecg);

	tDetails->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::tDetailsTimer(TObject *Sender)
	{
	tDetails->Enabled = false;
	fmDetails->BringToFront();
	}
//---------------------------------------------------------------------------
void TfmEcg::CutCurve()
	{
	Print("cut curve...");

	int von = edCutVon->Text.ToIntDef(-1);
	int bis = edCutBis->Text.ToIntDef(-1);
	if (von < 0 || bis < 0) return;
	if (bis < von) return;

	//-- EKG-Daten
	cData& data = ecg.data;
	if (!data.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	data.redisplay(imgEcg);

	//-- Erste Ableitung
	cDerivate& deriv1 = ecg.data.derivate1;
	if (!deriv1.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv1.error_code, deriv1.error_msg);
		return;
		}
	data.derivate1.redisplay(imgDeriv1);

	//-- Zweite Ableitung
	cDerivate& deriv2 = ecg.data.derivate2;
	if (!deriv2.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv2.error_code, deriv2.error_msg);
		return;
		}
	data.derivate2.redisplay(imgDeriv2);

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished cutting");

	//Detail-Werte aktuelisieren
	fmDetails->Renew(ecg);
	}
//---------------------------------------------------------------------------
void TfmEcg::MovingAv()
	{
	Print("build moving average...");

	int window1 = edGl1->Text.ToIntDef(-1);
	int window2 = edGl2->Text.ToIntDef(-1);
	int window3 = edGl3->Text.ToIntDef(-1);
	if (window1 <= 0 || window2 <= 0 || window3 <= 0) return;

	bool dropBegin = cxDropBegin->Checked;

	//-- EKG-Daten
	cData& data = ecg.data;
	if (!data.movingAv(window1, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return;
		}
	data.redisplay(imgEcg);

	//-- Erste Ableitung
	cDerivate& deriv1 = ecg.data.derivate1;
	if (!deriv1.movingAv(window2, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv1.error_code, deriv1.error_msg);
		return;
		}
	data.derivate1.redisplay(imgDeriv1);

	//-- Zweite Ableitung
	cDerivate& deriv2 = ecg.data.derivate2;
	if (!deriv2.movingAv(window3, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv2.error_code, deriv2.error_msg);
		return;
		}
	data.derivate2.redisplay(imgDeriv2);

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished moving average");

	//Detail-Werte aktuelisieren
	fmDetails->Renew(ecg);
	}
//---------------------------------------------------------------------------
void TfmEcg::Importschema()
	{
	//todo implementieren
	}
//---------------------------------------------------------------------------
void TfmEcg::MySqlSave()
	{
	/*
	if (ecg.data.data_array.size() <= 0)
		{
		Print("## Fehler aufgetreten: Es wurden noch keine EKG-Daten eingelesen");
		return;
		}

	//todo: über struct lösen, erstmal manuelle Testdaten verwenden
	String name = DlgRequest(this, "Personenname");
	String pos  = DlgRequest(this, "Position der Aufnahme");

	ePosition p = ftools.GetPosition(pos);

	fmysql.mysql_data.array = ecg.data.data_array;
	sprintf(fmysql.mysql_data.name, "%.63s", name.c_str());
	fmysql.mysql_data.pos   = (ePosition)p;

	if (!fmysql.saveToDbase())
		{
		Print("## Fehler aufgetreten: %d, %s", fmysql.error_code, fmysql.error_msg);
		return;
		}
	*/
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEcg::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
	{
	if (Shift.Contains(ssShift) && Key == VK_F11)
		{
		btInputfileClick(Sender);
		}

	if (Shift.Contains(ssCtrl) && Shift.Contains(ssShift) && Key == 0x44) //"D" -> Detailseite fokussieren
		{
		if (bDisplayedDetails)
			fmDetails->BringToFront();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::btInputfileClick(TObject *Sender)
	{
	if (OpenDialog->Execute())
    	edInputfile->Text = OpenDialog->FileName;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::laClsClick(TObject *Sender)
	{
	memo->Lines->Clear();
	}
//---------------------------------------------------------------------------
void TfmEcg::sendClick(TButton* bt)
	{
	String cap = bt->Caption;
	if (!bRun)
		{
		bt->Caption = "&ABBRECHEN";
		bStop = false;
		bRun  = true;

		switch (bt->Tag)
			{
			case  1: ReadFile(); break;
			case  2: CutCurve(); break;
			case  3: MovingAv(); break;
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
void __fastcall TfmEcg::btReadClick(TObject *Sender)
	{
	sendClick(btRead);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::btCutClick(TObject *Sender)
	{
	sendClick(btCut);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::btMovAvClick(TObject *Sender)
	{
	sendClick(btMovAv);
	}
//---------------------------------------------------------------------------
//------ Menuklicks --------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfmEcg::Importschemata2Click(TObject *Sender)
	{
	Importschema();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::DateninMySQLDatenbankspeichern1Click(TObject *Sender)
	{
	MySqlSave();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::Beenden1Click(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::Datenanzeigen1Click(TObject *Sender)
	{
	//todo ?? DlgDatabase(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::estenmitAlg11Click(TObject *Sender)
	{
	//todo DlgAlgorithmus1(this, ecg);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcg::GetValuefromAlg11Click(TObject *Sender)
	{
	double val = GetAlgorithmus1(this, ecg);
	Application->MessageBox(String(val).c_str(), "Erkennungswert", MB_OK);
	}
//---------------------------------------------------------------------------

