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
USEFORM("EdanImport.cpp", fmEdan);
USEFORM("database\DbPersonen.cpp", fmData);
USEFORM("database\baseforms\basePeople.cpp", fmBasePeople);
USEFORM("database\baseforms\baseEcgData.cpp", fmBaseEcg);
USEFORM("database\baseforms\baseSession.cpp", fmBaseSession);
USEFORM("database\baseforms\baseDesc.cpp", fmBaseDesc);
USEFORM("database\toolforms\addPeople.cpp", fmPerson);
USEFORM("database\toolforms\addDesc.cpp", fmDescAdd);
USEFORM("database\toolforms\addSession.cpp", fmSessionAdd);
USEFORM("database\toolforms\addPersonSession.cpp", fmAddPersonSession);
USEFORM("database\toolforms\addEcgMessungen.cpp", fmAddMessung);
USEFORM("database\toolforms\addEcg.cpp", fmAddEcg);
USEFORM("database\toolforms\addEcgFiles.cpp", fmEcgFiles);
USEFORM("database\toolforms\selectDescDb.cpp", fmSelectDesc);
USEFORM("database\toolforms\selectPeople.cpp", fmSelectPerson);
USEFORM("database\toolforms\wizardSession_Main.cpp", fmWizSession);
USEFORM("algorithms\EinzelAusw.cpp", fmSingle);
USEFORM("algorithms\AlgChoi.cpp", fmChoi);
USEFORM("algorithms\AlgChoi2.cpp", fmChoi2);
USEFORM("LeadAnalysis.cpp", fmLeads);
USEFORM("EcgLeadAnalysis.cpp", fmEcgLeads);
USEFORM("FeatChoi.cpp", fmFeatChoi);
//---------------------------------------------------------------------------
#pragma link "EcgBasics.lib"
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
		Application->CreateForm(__classid(TfmEcgLeads), &fmEcgLeads);
		Application->CreateForm(__classid(TfmFeatChoi), &fmFeatChoi);
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
