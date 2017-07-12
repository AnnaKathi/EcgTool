//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <System.hpp>

#include "EdanImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmEdan *fmEdan;
//---------------------------------------------------------------------------
bool DlgImportEdan(TForm* Papa)
	{
	TfmEdan* Form = new TfmEdan(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmEdan::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmEdan::TfmEdan(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmEdan::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEdan::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEdan::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmEdan::Tick(int pos) //pos ist mit 1 vorbesetzt
	{
	pbProgress->Position += pos;
	}
//---------------------------------------------------------------------------
bool TfmEdan::GetFile()
	{
	String path = edPath->Text;
	if (path == "" || !DirectoryExists(path)) return false;

	String file = edFile->Text;
	if (file == "") return false;
	String datei = ftools.fmt("%s\\%s.txt", path, file);
	if (FileExists(datei))
		{
		if (Application->MessageBox(
			ftools.fmt("Die Datei <%s> existiert bereits. Soll sie überschrieben werden?", datei).c_str(),
			"Datei existiert bereits",
			MB_YESNO) == IDNO)
			return false;
		}

	if (mLead1->Text == "") return false; if (mLead2->Text == "") return false;
	if (mLead3->Text == "") return false; if (mLead4->Text == "") return false;
	if (mLead5->Text == "") return false; if (mLead6->Text == "") return false;
	if (mLead7->Text == "") return false; if (mLead8->Text == "") return false;

	//Alle Werte aus den Memos einlesen und in eine ADS-Datei umlesen
	iarray_t lead1 = getMemo(mLead1); if (lead1.size() <= 0) return false;
	iarray_t lead2 = getMemo(mLead2); if (lead2.size() <= 0) return false;
	iarray_t lead3 = getMemo(mLead3); if (lead3.size() <= 0) return false;
	iarray_t lead4 = getMemo(mLead4); if (lead4.size() <= 0) return false;
	iarray_t lead5 = getMemo(mLead5); if (lead5.size() <= 0) return false;
	iarray_t lead6 = getMemo(mLead6); if (lead6.size() <= 0) return false;
	iarray_t lead7 = getMemo(mLead7); if (lead7.size() <= 0) return false;
	iarray_t lead8 = getMemo(mLead8); if (lead8.size() <= 0) return false;

	int max = 0;
	if (lead1.size() > max) max = lead1.size();
	if (lead2.size() > max) max = lead2.size();
	if (lead3.size() > max) max = lead3.size();
	if (lead4.size() > max) max = lead4.size();
	if (lead5.size() > max) max = lead5.size();
	if (lead6.size() > max) max = lead6.size();
	if (lead7.size() > max) max = lead7.size();
	if (lead8.size() > max) max = lead8.size();
	pbProgress->Max = max;

	FILE* fp = fopen(datei.c_str(), "w");
	for (int i = 0; i < 7; i++) //sieben Headerzeilen faken
		fprintf(fp, "Headerzeile %d\n", i);

	fprintf(fp, "CH1\tCH2\tCH3\tCH4\tCH5\tCH6\tCH7\tCH8\n");
	for (int i = 0; i < max; i++)
		{
		fprint(fp, lead1, i); fprintf(fp, "\t");
		fprint(fp, lead2, i); fprintf(fp, "\t");
		fprint(fp, lead3, i); fprintf(fp, "\t");
		fprint(fp, lead4, i); fprintf(fp, "\t");
		fprint(fp, lead5, i); fprintf(fp, "\t");
		fprint(fp, lead6, i); fprintf(fp, "\t");
		fprint(fp, lead7, i); fprintf(fp, "\t");
		fprint(fp, lead8, i); fprintf(fp, "\n");

		Tick();
		}

	fclose(fp);
	return true;
	}
//---------------------------------------------------------------------------
void TfmEdan::fprint(FILE* fp, iarray_t array, int ix)
	{
	if (ix >= array.size()) fprintf(fp, "%f", 0);
	else fprintf(fp, "%f", array[ix][1]);
	}
//---------------------------------------------------------------------------
iarray_t TfmEdan::getMemo(TMemo* memo)
	{
	iarray_t result; result.clear();
	int ix = 0; int pos; String number;

	String digits = memo->Text;
	while (digits.Length() > 0)
		{
		pos = digits.Pos(" ");
		if (pos <= 0) break;
		number = digits.SubString(0,     pos-1);
		digits = digits.SubString(pos+1, 9999);

		result[ix].push_back(ix);
		result[ix].push_back(number.ToDouble());
		ix++;
		}
	return result;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEdan::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEdan::acImportExecute(TObject *Sender)
	{
	pbProgress->Max = 100; //wird später angepasst
	pbProgress->Position = 0;
	pbProgress->Visible = true;

	if (!GetFile())
		; //Todo Fehlermeldung

	pbProgress->Visible = false;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEdan::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEdan::btTestClick(TObject *Sender)
	{
	fillMemo(mLead1);
	fillMemo(mLead2);
	fillMemo(mLead3);
	fillMemo(mLead4);
	fillMemo(mLead5);
	fillMemo(mLead6);
	fillMemo(mLead7);
	fillMemo(mLead8);
	}
//---------------------------------------------------------------------------
void TfmEdan::fillMemo(TMemo* memo)
	{
	Randomize(); double nr; String line = "";
	for (int i = 0; i < 1000; i++)
		{
		nr = Random(150);
		if (i == 0) line = String(nr);
    	else line += " " + String(nr);
		}
	memo->Text = line;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEdan::btLoadClick(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	String file = OpenDialog->FileName;

	iarray_t lead1; lead1.clear(); int ix1 = 0;

	char row[16384]; //Todo reicht das?
	FILE* fp = fopen(file.c_str(), "r");

	char number[32];

	String line;
	int test = 0;
	int InLead = 0;
	while (fgets(row, sizeof(row)-1, fp))
		{
		test++;
		if (test == 110)
			int bp = 0;

		line = String(row).Trim();
		if (InLead == 1) //Daten von Lead I einlesen
			{
			if (line.SubString(0, 8) != "<digits>") continue;
			//hier liegen jetzt die Zahlen vor, String kann nicht verwendet werden
			//da dieser in der Länge begrenzt ist !!
			char* pt = strchr(row, '>');
			if (pt)
				{
				*pt = 0;
				sprintf(row, "%s", pt+1);
				}

			mLead1->Text = String(row);

			pt = strchr(row, ' ');
			while (pt)
				{
				*pt = 0;
				sprintf(number, "%s", row);
				sprintf(row, "%s", pt+1);
				lead1[ix1].push_back(atof(number));
				ix1++;
				pt = strchr(row, ' ');
				}

			//TEST
			for (iarray_itr itr = lead1.begin(); itr != lead1.end(); itr++)
				{
				ilist_t& v = itr->second;
				mLead2->Text += " " + String(v[0]);
				}

			InLead = 0;
			continue;
			}

		else if (line.SubString(0, 27) == "<code code=\"MDC_ECG_LEAD_I\"" && lead1.size() == 0) //nur einmal machen
			{
			InLead = 1;
			}
		}

	fclose(fp);
	}
//---------------------------------------------------------------------------

