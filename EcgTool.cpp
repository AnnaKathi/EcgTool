//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", fmMain);
USEFORM("EcgView.cpp", fmEcg);
USEFORM("Databases.cpp", fmDatabases);
USEFORM("Sessions.cpp", fmSessions);
USEFORM("DataAnalysis.cpp", fmAnalysis);
USEFORM("RequestBox.cpp", fmRequest);
USEFORM("Details.cpp", fmDetails);
USEFORM("Features.cpp", fmFeatures);
USEFORM("ChoiKlassifizierung.cpp", fmChoiClassification);
USEFORM("VergleichAlg.cpp", fmVergleich);
USEFORM("Testform.cpp", fmTest);
USEFORM("database\DbPersonen.cpp", fmData);
USEFORM("database\baseforms\basePeople.cpp", fmBasePeople);
USEFORM("database\baseforms\baseEcgData.cpp", fmBaseEcg);
USEFORM("database\baseforms\baseSession.cpp", fmBaseSession);
USEFORM("database\baseforms\baseDesc.cpp", fmBaseDesc);
USEFORM("database\toolforms\addPeople.cpp", fmPerson);
USEFORM("database\toolforms\addDesc.cpp", fmDescAdd);
USEFORM("database\toolforms\addSession.cpp", fmSessionAdd);
USEFORM("database\toolforms\addEcg.cpp", fmAddEcg);
USEFORM("database\toolforms\addEcgFiles.cpp", fmEcgFiles);
USEFORM("database\toolforms\selectDescDb.cpp", fmSelectDesc);
USEFORM("database\toolforms\wizardSession_Main.cpp", fmWizSession);
USEFORM("algorithms\EinzelAusw.cpp", fmSingle);
USEFORM("algorithms\AlgChoi.cpp", fmChoi);
USEFORM("algorithms\AlgChoi2.cpp", fmChoi2);
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
		Application->CreateForm(__classid(TfmDescAdd), &fmDescAdd);
		Application->CreateForm(__classid(TfmBasePeople), &fmBasePeople);
		Application->CreateForm(__classid(TfmAnalysis), &fmAnalysis);
		Application->CreateForm(__classid(TfmChoi), &fmChoi);
		Application->CreateForm(__classid(TfmTest), &fmTest);
		Application->CreateForm(__classid(TfmBaseDesc), &fmBaseDesc);
		Application->CreateForm(__classid(TfmChoi2), &fmChoi2);
		Application->CreateForm(__classid(TfmSelectDesc), &fmSelectDesc);
		Application->CreateForm(__classid(TfmAddEcg), &fmAddEcg);
		Application->CreateForm(__classid(TfmEcgFiles), &fmEcgFiles);
		Application->CreateForm(__classid(TfmSessionAdd), &fmSessionAdd);
		Application->CreateForm(__classid(TfmSessions), &fmSessions);
		Application->CreateForm(__classid(TfmBaseSession), &fmBaseSession);
		Application->CreateForm(__classid(TfmChoiClassification), &fmChoiClassification);
		Application->CreateForm(__classid(TfmFeatures), &fmFeatures);
		Application->CreateForm(__classid(TfmVergleich), &fmVergleich);
		Application->CreateForm(__classid(TfmWizSession), &fmWizSession);
		Application->CreateForm(__classid(TfmDatabases), &fmDatabases);
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
