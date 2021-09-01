//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"
#include "./../../FORM_TEMPLATES/About_frm.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("./../../FORM_TEMPLATES/About_frm.cpp", AboutForm);
USEFORM("Unit1.cpp", ResizerForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Resizer.VCL";
                 Application->CreateForm(__classid(TResizerForm), &ResizerForm);
                 Application->CreateForm(__classid(TAboutForm), &AboutForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
