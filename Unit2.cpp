//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------

__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label1Click(TObject *Sender)
{
ShellExecute(
    this->Handle,	// handle to parent window
    "open",	// pointer to string that specifies operation to perform
    "http://www.facebook.com/sstsoft",	// pointer to filename or folder name string
    NULL,	// pointer to string that specifies executable-file parameters
    NULL,	// pointer to string that specifies default directory
    SW_SHOWNORMAL	// whether file is shown when opened
   );
for (int i = 0; i <= 20; i++){
ProgressBar1->Position = i;
Sleep(20);
Application->ProcessMessages();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image1Click(TObject *Sender)
{
Label1Click(Sender);
}
//---------------------------------------------------------------------------
