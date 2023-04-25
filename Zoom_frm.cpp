//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Zoom_frm.h"
#include "Move_frm.h"
#include "Main_frm.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TZoom_form *Zoom_form;
//---------------------------------------------------------------------
__fastcall TZoom_form::TZoom_form(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------------

void __fastcall TZoom_form::FormShow(TObject *Sender)
{
RECT clientrect;
::GetClientRect(this->Handle,&clientrect);
 ::SetWindowPos(this->Handle,HWND_TOPMOST,
       		    (Desktop->Screen->Rect.right-clientrect.right)/2,(Desktop->Screen->Rect.bottom-clientrect.bottom)/2,0,0,
       		     SWP_NOSIZE|SWP_NOCOPYBITS|SWP_NOREDRAW|SWP_NOACTIVATE|SWP_NOSENDCHANGING);
}
//---------------------------------------------------------------------------

void __fastcall TZoom_form::FormHide(TObject*)
{
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------

long __fastcall TZoom_form::Execute(TObject *Sender)
{
this->Sender = Sender; return this->ShowModal();
}
//---------------------------------------------------------------------
void __fastcall TZoom_form::TrackBar1Change(TObject*)
{
GroupBox1->Caption = String(TrackBar1->Position) + " : 1";
}
//---------------------------------------------------------------------------

void __fastcall TZoom_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

