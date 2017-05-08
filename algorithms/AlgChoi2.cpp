//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "AlgChoi2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmChoi2 *fmChoi2;
//---------------------------------------------------------------------------
bool DlgAlgChoi2(TForm* Papa)
	{
	TfmChoi2* Form = new TfmChoi2(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmChoi2::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi2::TfmChoi2(TComponent* Owner)
	: TForm(Owner)
	{
	Count1Anna = Count1Manni = Count1Manu = Count1Martin = 0;
	Count2Anna = Count2Manni = Count2Manu = Count2Martin = 0;
	}
//---------------------------------------------------------------------------
__fastcall TfmChoi2::~TfmChoi2()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	ftools.FormLoad(this);
	ftools.ListViewLoad(this, lvData1);
	ftools.ListViewLoad(this, lvData2);
	SetValues();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	ftools.ListViewSave(this, lvData1);
	ftools.ListViewSave(this, lvData2);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmChoi2::Print(char* msg, ...)
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
void TfmChoi2::SetValues()
	{
	Count1Anna = Count1Manni = Count1Manu = Count1Martin = 0;
	Count2Anna = Count2Manni = Count2Manu = Count2Martin = 0;

	TListItem* item;
	for (int i = 0; i < lvData1->Items->Count; i++)
		{
		item = lvData1->Items->Item[i];
		if (item->SubItems->Strings[0] != "") Count1Anna++;
		if (item->SubItems->Strings[1] != "") Count1Manni++;
		if (item->SubItems->Strings[2] != "") Count1Manu++;
		if (item->SubItems->Strings[3] != "") Count1Martin++;
		}

	for (int i = 0; i < lvData2->Items->Count; i++)
		{
		item = lvData2->Items->Item[i];
		if (item->SubItems->Strings[0] != "") Count2Anna++;
		if (item->SubItems->Strings[2] != "") Count2Manni++;
		if (item->SubItems->Strings[2] != "") Count2Manu++;
		if (item->SubItems->Strings[3] != "") Count2Martin++;
		}
	}
//---------------------------------------------------------------------------
String TfmChoi2::GetFile(String dat)
	{
	char help[MAX_PATH];
	sprintf(help, "%s", dat.c_str());
	char* pt = strrchr(help, '\\');
	if (pt)
		{
		*pt = 0;
		sprintf(help, "%s", pt+1);
		return String(help);
		}
	else
    	return dat;
	}
//---------------------------------------------------------------------------
void TfmChoi2::AddFile(TListView* lv, String file, int count, int id)
	{
	if (count > lv->Items->Count)
		{
		TListItem* item = lv->Items->Add();
		item->Caption = String(lv->Items->Count);
		item->Data = (void*)lv->Items->Count;

		for (int i = 0; i < 4; i++)
			item->SubItems->Add("");
		}

	TListItem* item = lv->Items->Item[count-1];
	item->SubItems->Strings[id] = file;

	Print("+ %s", GetFile(file));
	}
//---------------------------------------------------------------------------
bool TfmChoi2::CompareResult(String testfile, String outfile)
	{
	FILE* fptest = fopen(testfile.c_str(), "r");
	if (fptest == NULL) return false;

	FILE* fpout = fopen(outfile.c_str(), "r");
	if (fpout == NULL)
		{
		fclose(fptest);
		return false;
		}

	char rowbuf1[1024];  char rowbuf2[1024];
	int testlabel;		 int outlabel;
	bool fehler = false;

	int right = 0;
	int wrong = 0;
	int count = 0;
	while ((fgets(rowbuf1, sizeof(rowbuf1)-1, fptest)) != NULL)
		{
		char* pt = strchr(rowbuf1, ' ');
		if (pt == NULL)
			{
			fehler = true;
			break;
			}
		*pt = 0;
		testlabel = atoi(rowbuf1);

		if (fgets(rowbuf2, sizeof(rowbuf2)-1, fpout) == NULL)
			{
			fehler = true;
			break;
			}

		pt = strchr(rowbuf2, ' ');
		outlabel = atoi(rowbuf2);

		if (testlabel == outlabel)
			right++;
		else
			wrong++;

		count++;
		}

	fclose(fptest);
	fclose(fpout);

	if (fehler) return false;

	double classification = (double)right / (double)count * 100;
	Print("Accuracy: %.2f", classification);
    return true;
	}
//---------------------------------------------------------------------------
bool TfmChoi2::WriteFile(bool train, String filename)
	{
	iarray_t array; array.clear();

	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	eDatFormat format;
	if (cbFormat->ItemIndex == 1)
		format = formatADS;
	else
		format = formatNone;

	TListView* lv;
	if (train)
		lv = lvData1;
	else
		lv = lvData2;

	String lvData1; String lvData2; //TEST

	bool fehler = false;
	String datei;
	TListItem* item;
	int count = 0;
	for (int row = 0; row < lv->Items->Count; row++)
		{
		item = lv->Items->Item[row];
		for (int col = 0; col < (lv->Columns->Count-1); col++)
			{
			datei = item->SubItems->Strings[col];
			if (datei == "") continue;

			//Datei einlesen
			if (!fecg.data.getFile(datei, format, delim, 1, 3000))
				{
				fehler = true;
				Print("# Eine Datei kann nicht eingelesen werden: %s", datei);
				Print("# ECG meldet: %s", fecg.data.error_msg);
				break;
				}

			//R-Peak feststellen
			iarray_t ecg = fecg.data.data_array;
			cRpeaks& r   = fecg.rpeaks;
			r.find(ecg, NULL);
			r.reset();

			//R-Peaks durchlaufen und zu den Trainingsdaten hinzufügen
			int prev_zeit, curr_zeit, next_zeit;
			while ((curr_zeit = r.next()) != -1)
				{
				if ((prev_zeit = r.prev_rpeak()) == -1) continue;
				if ((next_zeit = r.next_rpeak()) == -1) continue;

				if (!fChoiFeat.getSingleFeatures(ecg, prev_zeit, curr_zeit, next_zeit))
					{
					fehler = true;
					Print("# Fehler, SingleFeat meldet: %d, %s", fChoiFeat.error_code, fChoiFeat.error_msg);
					break;
					}

				iarray_t features = fChoiFeat.SingleFeatures;
				array[count].push_back(col+1);  //label
				array[count].push_back(features[0][0]);
				array[count].push_back(features[1][0]);
				array[count].push_back(features[2][0]);
				array[count].push_back(features[3][0]);
				array[count].push_back(features[4][0]);
				array[count].push_back(features[5][0]);
				array[count].push_back(features[6][0]);
				array[count].push_back(features[7][0]);
				count++;
				}
			}
		}

	int sz = array.size();
	if (fehler) return false;

	FILE* fp = fopen(filename.c_str(), "w");
	if (fp == NULL)
		return false;

	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		//<label> <index1>:<value1> <index2>:<value2> ...
		ilist_t& v = itr->second;
		fprintf(fp, "%d 1:%d 2:%d 3:%d 4:%.8f 5:%.8f 6:%.8f 7:%.8f 8:%.8f\n",
			(int)v[0], (int)v[1], (int)v[2], (int)v[3],
			v[4], v[5], v[6], v[7], v[8]);
		}

	fclose(fp);
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Actions   ********************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acResetExecute(TObject *Sender)
	{
	if (Application->MessageBox(
		"Bist Du sicher, dass Du alle Daten zurücksetzen möchtest?",
		"Daten zurücksetzen",
		MB_YESNO) == IDNO) return;

	lvData1->Items->Clear();
	lvData2->Items->Clear();
	SetValues();
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddAnnaExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count1Anna++;
	AddFile(lvData1, OpenDialog->FileName, Count1Anna, 0);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddManniExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count1Manni++;
	AddFile(lvData1, OpenDialog->FileName, Count1Manni, 1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddManuExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count1Manu++;
	AddFile(lvData1, OpenDialog->FileName, Count1Manu, 2);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::acAddMartinExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count1Martin++;
	AddFile(lvData1, OpenDialog->FileName, Count1Martin, 3);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::Button6Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count2Anna++;
	AddFile(lvData2, OpenDialog->FileName, Count2Anna, 0);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::Button7Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count2Manni++;
	AddFile(lvData2, OpenDialog->FileName, Count2Manni, 1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::Button8Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count2Manu++;
	AddFile(lvData2, OpenDialog->FileName, Count2Manu, 2);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::Button9Click(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	Count2Martin++;
	AddFile(lvData2, OpenDialog->FileName, Count2Martin, 3);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::btExeFilesClick(TObject *Sender)
	{
	//EXE-Dateien mit a1a-Daten aufrufen

	String path = ftools.GetPath();

	String svm_train   = path + "\\libSVM\\svm-train.exe";
	String a1a_train   = path + "\\libSVM\\a1a.train";
	String a1a_model   = path + "\\libSVM\\a1a.train.model";

	if (!FileExists(svm_train) || !FileExists(a1a_train))
		{
		; //todo Fehlermeldung
		return;
		}

	//svm-train.exe a1a.train
	ShellExecute(
		this,    			//hwnd
		"open",     		//Operation
		svm_train.c_str(),	//File
		a1a_train.c_str(),	//Parameters
		path.c_str(),		//Directory
		SW_SHOW);   		//Show-Command

	if (!FileExists(a1a_model))
		{
		; //todo Fehlermeldung
		return;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::btCreateFilesClick(TObject *Sender)
	{
	if (!WriteFile(true, "d:\\anna.train"))
		{
		Application->MessageBox("Train: Fehler aufgetreten", "Fehler", MB_OK);
		return;
		}

	if (!WriteFile(false, "d:\\anna.test"))
		{
		Application->MessageBox("Test: Fehler aufgetreten", "Fehler", MB_OK);
		return;
		}

	Application->MessageBox("Dateien erzeugt", "ok", MB_OK);
	}
//---------------------------------------------------------------------------
void __fastcall TfmChoi2::btCompareFilesClick(TObject *Sender)
	{
	String testfile = "d:\\anna.test";
	String outfile  = "d:\\anna.out";

	CompareResult(testfile, outfile);
	}
//---------------------------------------------------------------------------

