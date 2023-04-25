//---------------------------------------------------------------------------
#include <vcl.h>
#include <commctrl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Tips_frm.h"
#include "Main_frm.h"
//---------------------------------------------------------------------------
#pragma link "framepan"
#pragma link "framepan"
#pragma link "framepan"
#pragma link "framepan"
#pragma link "framepan"
#pragma link "framepan"
#pragma link "FRAMEPAN"
#pragma resource "*.dfm"
TTips_form *Tips_form;
//---------------------------------------------------------------------------
__fastcall TTips_form::TTips_form(TComponent* Owner)
		  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TTips_form::Execute(String caption, bool timeout, bool flash)
{
register HWND hwnd = GetForegroundWindow();
register int p;

this->Caption = caption;
this->Repaint();

POINT cursorpoint;
GetCursorPos(&cursorpoint);
RECT clientrect;
::GetClientRect(this->Handle,&clientrect);
 ::SetWindowPos(this->Handle,HWND_TOPMOST,
       		    (Desktop->Screen->Rect.right-clientrect.right)/2,(Desktop->Screen->Rect.bottom-clientrect.bottom)/2,0,0,
       		     SWP_NOSIZE|SWP_NOCOPYBITS|SWP_NOREDRAW|SWP_NOACTIVATE|SWP_NOSENDCHANGING);
ShowWindow(this->Handle,SW_SHOW);

 if (timeout)
for (p = 1; p <= 5; p++) { Application->ProcessMessages();
      if (flash==true) {
      FlashWindow(hwnd, (p & 0x01));
      Sleep(200);
      FlashWindow(hwnd,!(p & 0x01));
      Sleep(200);
      }
      else Sleep(400);
    }
if (timeout) ShowWindow(this->Handle,SW_HIDE);
SetForegroundWindow(hwnd);
}
//---------------------------------------------------------------------------

void __fastcall TTips_form::FormPaint(TObject*)
{
RECT clientrect;
::GetClientRect(this->Handle,&clientrect);
DrawText(Canvas->Handle,Caption.c_str(),Caption.Length(),
     		&clientrect,
     		DT_CENTER|DT_SINGLELINE|DT_VCENTER);
}
//---------------------------------------------------------------------------

void __fastcall TTips_form::FormHide(TObject*)
{
ShowWindow(Application->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------
void __fastcall TTips_form::Ramka1Click(TObject *Sender)
{
if (Main_form->Timer1->Enabled) Main_form->Timer1->Enabled = false;
ShowWindow(Application->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TTips_form::Ramka1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
SendMessage(Handle, WM_LBUTTONUP, 0, 0);
SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
}
//---------------------------------------------------------------------------

void __fastcall TTips_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
SetClassLong(this->Handle,GCL_STYLE,GetClassLong(this->Handle,GCL_STYLE) | CS_SAVEBITS);
}
//---------------------------------------------------------------------------

