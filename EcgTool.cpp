//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", fmMain);
USEFORM("EcgView.cpp", fmEcg);
USEFORM("RequestBox.cpp", fmRequest);
USEFORM("Details.cpp", fmDetails);
USEFORM("Session.cpp", fmSession);
USEFORM("database\DbPersonen.cpp", fmData);
USEFORM("database\Person.cpp", fmPerson);
USEFORM("algorithms\Alg1.cpp", fmAlg1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		SetApplicationMainFormOnTaskBar(Application, true);
		Application->CreateForm(__classid(TfmMain), &fmMain);
		Application->CreateForm(__classid(TfmData), &fmData);
		Application->CreateForm(__classid(TfmPerson), &fmPerson);
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
