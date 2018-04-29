//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Muse_frm.h"
#include "Zeus_frm.h"
#include "Lupa_frm.h"
#include "Desk_frm.h"
#include "Zoom_frm.h"
#include "Move_frm.h"
#include "Main_frm.h"
#include "Info_frm.h"
#include "Tips_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMuse_form *Muse_form;
//---------------------------------------------------------------------------
__fastcall TMuse_form::TMuse_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMuse_form::FormCreate(TObject *Sender)
{

hInst = (HINSTANCE)HInstance;
screen.Hwnd = GetDesktopWindow();
screen.Hdc  = GetDC(0);
::GetWindowRect(screen.Hwnd,&screen.Rect);
screen.Bitmap = new Graphics::TBitmap();
screen.Bitmap->Height = (screen.Rect.bottom-screen.Rect.top)*2;
screen.Bitmap->Width  =  (screen.Rect.right-screen.Rect.left)*2;
::SetStretchBltMode(this->Canvas->Handle, STRETCH_DELETESCANS);

Image1->Picture->Bitmap = new Graphics::TBitmap;
Image1->Picture->Bitmap->Width = Image1->Width;
Image1->Picture->Bitmap->Height = Image1->Height;
Image1->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image1->Picture->Bitmap->Canvas->FillRect(Image1->ClientRect);

}
//---------------------------------------------------------------------------

void __fastcall TMuse_form::FormShow(TObject *Sender)
{
Desktop->Collect();
SetStretchBltMode(Image1->Picture->Bitmap->Canvas->Handle,HALFTONE);
StretchBlt(Image1->Picture->Bitmap->Canvas->Handle,
    	 0,0,Image1->Width,Image1->Height,
    	 screen.Hdc,
    	 0,0,screen.Rect.right,screen.Rect.bottom,
    		 SRCCOPY);

Desktop->Capture();
}
//---------------------------------------------------------------------------

void __fastcall TMuse_form::Button1Click(TObject *Sender)
{
Zeus_form->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMuse_form::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
POINT cursorpoint;
cursorpoint.x = X;
cursorpoint.x = (cursorpoint.x * (Desktop->Screen->Rect.right -Desktop->Screen->Rect.left))/Image1->Width;
cursorpoint.y = Y;
cursorpoint.y = (cursorpoint.y * (Desktop->Screen->Rect.bottom-Desktop->Screen->Rect.top))/Image1->Height;

HWND curhwnd = Desktop->Virtual[0]->Handle_at_XY(cursorpoint.x,cursorpoint.y);
HWND  parent = curhwnd;
while (GetParent(parent)!=NULL)
         {parent =  GetParent(parent);}
    char text[64];
GetWindowText(parent,text,63);
if (strlen(text)==0)
 GetClassName(parent,text,63);
if (strlen(text)==0)
strcpy(text,"Nic");
this->Caption = (AnsiString)cursorpoint.x+":"+(AnsiString)cursorpoint.y+" - "+(AnsiString)text;
if(IsWindow(parent))
        HandleFromPoint = parent;
}
//---------------------------------------------------------------------------

void __fastcall TMuse_form::Image1Click(TObject *Sender)
{
DWORD dwProcessId;
GetWindowThreadProcessId(HandleFromPoint,&dwProcessId);
 if (GetCurrentProcessId()==dwProcessId)
    {goto EXIT_KILL;
    }
HANDLE hProcess;
 if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwProcessId))!=NULL)
    {TerminateProcess(hProcess, -1);
    }
EXIT_KILL: return;

}
//---------------------------------------------------------------------------


