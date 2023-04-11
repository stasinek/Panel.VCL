//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"
#include "./../../FORM_TEMPLATES/About_frm.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("./../../FORM_TEMPLATES/About_frm.cpp", About_form);
USEFORM("Unit1.cpp", Resizer_form);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Resizer.VCL";
                 Application->CreateForm(__classid(TResizer_form), &Resizer_form);
                 Application->CreateForm(__classid(TAbout_form), &About_form);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
