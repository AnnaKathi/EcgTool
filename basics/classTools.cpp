//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cTools::cTools()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Datenkonverter   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String cTools::GetLage(eLage lage)
	{
		 if (lage == lageLiegend) return "liegend";
	else if (lage == lageSitzend) return "sitzend";
	else if (lage == lageStehend) return "stehend";
	else if (lage == lageGehend)  return "gehend";
	else return "";
	}
//---------------------------------------------------------------------------
eLage cTools::GetLage(String lage)
	{
		 if (lage == "liegend") return lageLiegend;
	else if (lage == "sitzend") return lageSitzend;
	else if (lage == "stehend") return lageStehend;
	else if (lage == "gehend")  return lageGehend;
	else return lageNone;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Comboboxen   *********************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void cTools::LagenToCombo(TComboBox* cb)
	{
	cb->Items->Clear();
	cb->Items->AddObject("- alle Positionen -"  , (TObject*)lageNone);
	cb->Items->AddObject(GetLage(lageLiegend), (TObject*)lageLiegend);
	cb->Items->AddObject(GetLage(lageSitzend), (TObject*)lageSitzend);
	cb->Items->AddObject(GetLage(lageStehend), (TObject*)lageStehend);
	cb->Items->AddObject(GetLage(lageGehend) , (TObject*)lageGehend);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Formulardaten laden und speichern   **********************/
/***************************************************************************/
//---------------------------------------------------------------------------
String cTools::GetPath()
	{
	char path[MAX_PATH];
	strcpy(path, Application->ExeName.c_str());
	char* pt = strrchr(path, '\\');
	if (pt != 0)
		*pt = 0;

	return String(path);
	}
//---------------------------------------------------------------------------
String cTools::GetIniFile()
	{
	String dat = GetPath() + "\\EcgTool.ini";
	return dat;
	}
//---------------------------------------------------------------------------
void cTools::FormLoad(TForm* fm)
	{
	TIniFile* Ini = new TIniFile(GetIniFile());

	for (int i = 0; i < fm->ComponentCount; i++)
		{
		TComponent* comp = fm->Components[i];
		if (String(comp->ClassName()) == "TEdit")
			{
			TEdit* ed = (TEdit*) comp;
			String key = fm->Name + "." + ed->Name;
			ed->Text = Ini->ReadString("FormEdits", key, "");
			}

		else if (String(comp->ClassName()) == "TComboBox")
			{
			TComboBox* cb = (TComboBox*) comp;
			String key = fm->Name + "." + cb->Name;
			cb->ItemIndex = Ini->ReadInteger("FormCombos", key, 0);
			}

		else if (String(comp->ClassName()) == "TCheckBox")
			{
			TCheckBox* cx = (TCheckBox*) comp;
			String key = fm->Name + "." + cx->Name;
			cx->Checked = Ini->ReadBool("FormChecks", key, false);
			}
		}

	//Formularpositionen laden
	int left = Ini->ReadInteger("FormPos", fm->Name + ".Left", -1);
	if (left < 0) //kein Wert gespeichert
		left = (Screen->DesktopWidth - fm->Width)/2;  //mittig ausrichten
	else if ((left + fm->Width) > Screen->DesktopWidth)
		left = Screen->DesktopWidth - fm->Width; //rechts ausrichten
	fm->Left = left;

	int top = Ini->ReadInteger("FormPos", fm->Name + ".Top", -1);
	if (top < 0) //kein Wert gespeichert
		top = (Screen->DesktopHeight - fm->Height)/2;  //mittig ausrichten
	else if ((top + fm->Height) > Screen->DesktopHeight)
		top = Screen->DesktopHeight - fm->Height; //unten ausrichten
	fm->Top = top;

	//Formulardimensionen laden
	//diese Width ist evtl anders als die vordesignte fm->Width
	int width = Ini->ReadInteger("FormPos", fm->Name + ".Width", -1);
	if (width > 0 && ((fm->Left + width) <= Screen->DesktopWidth))
		fm->Width = width;

	int height = Ini->ReadInteger("FormPos", fm->Name + ".Height", -1);
	if (height > 0 && ((fm->Top + height) <= Screen->DesktopHeight))
		fm->Height = height;

	delete Ini;
	}
//---------------------------------------------------------------------------
void cTools::FormSave(TForm* fm)
	{
	TIniFile* Ini = new TIniFile(GetIniFile());

	for (int i = 0; i < fm->ComponentCount; i++)
		{
		TComponent* comp = fm->Components[i];
		if (String(comp->ClassName()) == "TEdit")
			{
			TEdit* ed = (TEdit*) comp;
			String key = fm->Name + "." + ed->Name;
			Ini->WriteString("FormEdits", key, ed->Text);
			}

		else if (String(comp->ClassName()) == "TComboBox")
			{
			TComboBox* cb = (TComboBox*) comp;
			String key = fm->Name + "." + cb->Name;
			Ini->WriteInteger("FormCombos", key, cb->ItemIndex);
			}

		else if (String(comp->ClassName()) == "TCheckBox")
			{
			TCheckBox* cx = (TCheckBox*) comp;
			String key = fm->Name + "." + cx->Name;
			Ini->WriteBool("FormChecks", key, cx->Checked);
			}
		}

	//Formularposition speichern
	Ini->WriteInteger("FormPos", fm->Name + ".Left", fm->Left);
	Ini->WriteInteger("FormPos", fm->Name + ".Top",  fm->Top);

	//Formulardimensionen speichern
	Ini->WriteInteger("FormPos", fm->Name + ".Width",  fm->Width);
	Ini->WriteInteger("FormPos", fm->Name + ".Height", fm->Height);

	Ini->UpdateFile();
	delete Ini;
	}
//---------------------------------------------------------------------------
void cTools::ListViewLoad(TForm* fm, TListView* lv)
	{
	if (lv == NULL) return;
	TIniFile* Ini = new TIniFile(GetIniFile());
	String sec = "FormListView." + fm->Name + "." + lv->Name;
	if (!Ini->SectionExists(sec))
		{
		delete Ini;
		return;
		}

	String rowkey; String key;
	TListItem* item;
	int row = 0;
	while (row < 9999)
		{
		rowkey = String(row) + ".";
		if (!Ini->ValueExists(sec, rowkey + "caption"))
			break;

		item = lv->Items->Add();
		item->Data    = (void*)Ini->ReadInteger(sec, rowkey + "data", 0);
		item->Caption = Ini->ReadString(sec, rowkey + "caption", "");

		for (int col = 0; col < (lv->Columns->Count-1); col++)
			{
			key = rowkey + "col" + String(col);
			item->SubItems->Add(Ini->ReadString(sec, key, ""));
			}

		row++;
		}

	Ini->UpdateFile();
	delete Ini;
	}
//---------------------------------------------------------------------------
void cTools::ListViewSave(TForm* fm, TListView* lv)
	{
	if (lv == NULL) return;
	TIniFile* Ini = new TIniFile(GetIniFile());

	String sec = "FormListView." + fm->Name + "." + lv->Name;
	Ini->EraseSection(sec);

	String rowkey; String key;
	for (int row = 0; row < lv->Items->Count; row++)
		{
		TListItem* item = lv->Items->Item[row];
		rowkey = String(row) + ".";

		Ini->WriteInteger(sec, rowkey + "data",    (int)item->Data);
		Ini->WriteString(sec, rowkey + "caption", item->Caption);

		for (int col = 0; col < (lv->Columns->Count-1); col++)
			{
			key = rowkey + "col" + String(col);
			Ini->WriteString(sec, key, item->SubItems->Strings[col]);
			}
		}

	Ini->UpdateFile();
	delete Ini;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Sonstige Funktionen   ************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cTools::IsDebug()
	{
	TIniFile* Ini = new TIniFile(GetIniFile());
	char comp[64];
	DWORD nSize = sizeof(comp);
	GetComputerName(comp, &nSize);
	int found = Ini->ReadInteger("HomeStations", comp, 0);
	delete Ini;
	return found == 1 ? true : false;
	}
//---------------------------------------------------------------------------
String cTools::fmt(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;
	va_end(argptr);

	return String(buffer);
	}
//---------------------------------------------------------------------------
int cTools::replace(String& str, String old, String neu)
	{
	if (str == "") return 0;
	int count = 0;

	int pos;
	String left, right;
	while ((pos = str.Pos(old)) > 0)
		{
		left  = str.SubString(0, pos-1);
		right = str.SubString(pos + old.Length(), 999);

		str = left + neu + right;
		count++;

		if (count > 100) //sicherheitsabfrage
			break;
		}

	return count;
	}
//---------------------------------------------------------------------------

