//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include "./../../FORM_TEMPLATES/About_frm.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Resizer_form);
USEFORM("..\..\FORM_TEMPLATES\About_frm.cpp", About_form);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
                 Application->Title = "Resizer.VCL";
                 Application->CreateForm(__classid(TAbout_form), &About_form);
		Application->CreateForm(__classid(TResizer_form), &Resizer_form);
		Application->CreateForm(__classid(TAbout_form), &About_form);
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
