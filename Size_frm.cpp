//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Lupa_frm.h"
#include "Size_frm.h"
#include "Move_frm.h"
#include "Main_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "Zoom_frm"

TSize_form *Size_form;
//---------------------------------------------------------------------------
__fastcall TSize_form::TSize_form(TComponent* Owner)
		  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSize_form::FormShow(TObject *Sender)
{
RECT clientrect;
::GetClientRect(this->Handle,&clientrect);
 ::SetWindowPos(this->Handle,HWND_TOPMOST,
       		    (Desktop->Screen->Rect.right-clientrect.right)/2,(Desktop->Screen->Rect.bottom-clientrect.bottom)/2,0,0,
       		     SWP_NOSIZE|SWP_NOCOPYBITS|SWP_NOREDRAW|SWP_NOACTIVATE|SWP_NOSENDCHANGING);
}
//---------------------------------------------------------------------------

void __fastcall TSize_form::FormHide(TObject*)
{
ShowWindow(Application->Handle, SW_SHOWNA);
ShowWindow(Application->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------

long __fastcall TSize_form::Execute(TObject *Sender)
{
this->Sender = Sender; return this->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TSize_form::TrackBar1Change(TObject*)
{
GroupBox1->Caption = "X : " + String(TrackBar1->Position) + " pixels";
if (CheckBox1!=NULL)
if (CheckBox1->Checked)
   {TrackBar2->Position = (3*TrackBar1->Position)/4;
   }
if (TrackBar2!=NULL && this->Sender!=NULL)
    SetWindowPos(((TForm*)(this->Sender))->Handle,0,
		0,0,TrackBar1->Position,TrackBar2->Position,
		SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
}
//---------------------------------------------------------------------------

void __fastcall TSize_form::TrackBar2Change(TObject*)
{
GroupBox2->Caption = "Y : " + String(TrackBar2->Position) + " pixels";
if (CheckBox1!=NULL)
if (CheckBox1->Checked)
   {TrackBar1->Position = (4*TrackBar2->Position)/3;
   }
if (TrackBar1!=NULL && this->Sender!=NULL)
    SetWindowPos(((TForm*)(this->Sender))->Handle,0,
		0,0,TrackBar1->Position,TrackBar2->Position,
		SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
}
//---------------------------------------------------------------------------

void __fastcall TSize_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

