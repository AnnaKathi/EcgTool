//---------------------------------------------------------------------------
#ifndef classToolsH
#define classToolsH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include "..\definitions.h"
//---------------------------------------------------------------------------
class cTools
	{
public:
	cTools();

	//-- Datenkonverter
	String		GetPosition(ePosition pos);
	ePosition   GetPosition(String pos);

	//-- Comboboxen
	void 		PositionenToCombo(TComboBox* cb);

	//-- Formularfelder laden und speichern
	String		GetIniFile();
	bool 		FormLoad(TForm* fm);
	bool 		FormSave(TForm* fm);


private:

	};
//---------------------------------------------------------------------------
#endif
