//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", fmMain);
USEFORM("EcgView.cpp", fmEcg);
USEFORM("RequestBox.cpp", fmRequest);
USEFORM("Details.cpp", fmDetails);
USEFORM("Diseases.cpp", fmDiseases);
USEFORM("Session.cpp", fmSession);
USEFORM("database\DbPersonen.cpp", fmData);
USEFORM("database\baseforms\baseDiseases.cpp", fmBaseDiseases);
USEFORM("database\baseforms\baseEcgData.cpp", fmBaseEcg);
USEFORM("database\toolforms\addPeople.cpp", fmPerson);
USEFORM("database\toolforms\addDiseases.cpp", fmDis);
USEFORM("algorithms\EinzelAusw.cpp", fmSingle);
USEFORM("algorithms\Alg1.cpp", fmAlg1);
USEFORM("database\baseforms\basePeople.cpp", fmBasePeople);
//---------------------------------------------------------------------------
#include "database/classMySql.h"
cMySql fmysql;
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		SetApplicationMainFormOnTaskBar(Application, true);
		Application->CreateForm(__classid(TfmMain), &fmMain);
		Application->CreateForm(__classid(TfmSingle), &fmSingle);
		Application->CreateForm(__classid(TfmBaseDiseases), &fmBaseDiseases);
		Application->CreateForm(__classid(TfmDis), &fmDis);
		Application->CreateForm(__classid(TfmBasePeople), &fmBasePeople);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
