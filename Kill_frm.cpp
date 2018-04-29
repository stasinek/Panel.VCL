//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Kill_frm.h"
#include "Info_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TZeusForm *ZeusForm;
//---------------------------------------------------------------------------
__fastcall TZeusForm::TZeusForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TZeusForm::Timer1Timer(TObject *Sender)
{
SetWindowPos(Handle,HWND_TOPMOST,0,0,0,0,
             SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_NOSENDCHANGING);
POINT point_ofcursor;
GetCursorPos(&point_ofcursor);
HWND hwnd_frompoint;
hwnd_frompoint = WindowFromPoint(point_ofcursor);
if (hwnd_frompoint!=NULL)
{LPSTR title_text;
 title_text = (char*)LocalAlloc(LPTR,256);
 GetWindowText(hwnd_frompoint,title_text,256);
 LPSTR class_name;
 class_name = (char*)LocalAlloc(LPTR,256);
 GetClassName(hwnd_frompoint,class_name,256);
 Edit1->Text = class_name;
 Edit1->Enabled = Edit1->Text.Length()!=0;
 Edit2->Text = title_text;
 Edit2->Enabled = Edit2->Text.Length()!=0;
 LocalFree(class_name);
 LocalFree(title_text);


RECT temprect;
        ::PrintWindow(hwnd_frompoint,screen.Bitmap->Canvas->Handle,0);
      ::GetWindowRect(hwnd_frompoint,&temprect);

double sw = temprect.right-temprect.left, sh = temprect.bottom-temprect.top;
if (sw==0 || sh ==0) {sw = 1; sh=1;}
double iw, ih, mw = Image3->Width, mh = Image3->Height;
double skalax = sw/sh, skalay = sh/sw;
if (skalax > 1)
{iw = (int)((skalay*mw)*(mw/mh));
 ih = Image3->Height;}
else
{iw = Image3->Width;
 ih = (int)((skalax*mh)*(mh/mw)); }
         Label1->Caption = "sw="+FloatToStr(sw)+",sh="+FloatToStr(sh)+",iw="+FloatToStr(iw)+",ih="+FloatToStr(ih);
Image3->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image3->Picture->Bitmap->Canvas->FillRect(Image3->ClientRect);
::SetStretchBltMode(Image3->Canvas->Handle, HALFTONE);
StretchBlt(Image3->Canvas->Handle,
			  (int)(mw-iw)/2,(int)(mh-ih)/2,(int)iw,(int)ih,
			  screen.Bitmap->Canvas->Handle,
			  0,0,(int)sw,(int)sh,
			  SRCCOPY);
Image3->Repaint();
}
else
{Edit1->Text="";
 Edit1->Enabled=false;
 Edit2->Text="";
 Edit2->Enabled=false;
}

HWND hwnd_parent;
hwnd_parent = GetParent(hwnd_frompoint);
if (hwnd_parent!=NULL)
{LPSTR parent_title_text;
 parent_title_text = (char*)LocalAlloc(LPTR,256);
 GetWindowText(hwnd_parent,parent_title_text,256);
 LPSTR parent_class_name;
 parent_class_name = (char*)LocalAlloc(LPTR,256);
 GetClassName(hwnd_parent,parent_class_name,256);
 Edit3->Text = parent_class_name;
 Edit3->Enabled = Edit3->Text.Length()!=0;
 Edit4->Text = parent_title_text;
 Edit4->Enabled = Edit4->Text.Length()!=0;
 LocalFree(parent_class_name);
 LocalFree(parent_title_text);
}
else
{Edit3->Text="";
 Edit3->Enabled=false;
 Edit4->Text="";
 Edit4->Enabled=false;
}
HWND hwnd_top = 0;
for (HWND cur = hwnd_parent; cur!=NULL;cur = GetParent(cur))
    {hwnd_top = cur;
    }
if (hwnd_top!=NULL && hwnd_top!=hwnd_parent)
{LPSTR top_title_text;
 top_title_text = (char*)LocalAlloc(LPTR,256);
 GetWindowText(hwnd_top,top_title_text,256);
 LPSTR top_class_name;
 top_class_name = (char*)LocalAlloc(LPTR,256);
 GetClassName(hwnd_top,top_class_name,256);
 Edit5->Text = top_class_name;
 Edit5->Enabled = Edit5->Text.Length()!=0;
 Edit6->Text = top_title_text;
 Edit6->Enabled = Edit6->Text.Length()!=0;
 LocalFree(top_class_name);
 LocalFree(top_title_text);
}
else
{Edit5->Text="";
 Edit5->Enabled=false;
 Edit6->Text="";
 Edit6->Enabled=false;
}
}
//---------------------------------------------------------------------------
void __fastcall TZeusForm::BitBtn1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TZeusForm::Tile1Click(TObject *Sender)
{
TileWindows(NULL,
    MDITILE_VERTICAL,NULL,NULL,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TZeusForm::Tile2Click(TObject *Sender)
{
TileWindows(NULL,
    MDITILE_HORIZONTAL,NULL,NULL,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TZeusForm::Cascade1Click(TObject *Sender)
{
CascadeWindows(NULL,
    MDITILE_SKIPDISABLED,NULL,NULL,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TZeusForm::ArrangeAll1Click(TObject *Sender)
{
ArrangeIconicWindows(GetDesktopWindow());
}
//---------------------------------------------------------------------------
#include <winuser.h>

void __fastcall TZeusForm::Kill1Click(TObject *Sender)
{
Image1->Picture->Icon->Handle = LoadIcon((HINSTANCE)HInstance,"KILL");

while ((GetAsyncKeyState(1) & 0x8000)==0)
      {Sleep(50); Application->ProcessMessages();
      }
POINT point_ofcursor;
GetCursorPos(&point_ofcursor);
HWND hwnd_frompoint;
hwnd_frompoint = WindowFromPoint(point_ofcursor);
DWORD dwProcessId;
GetWindowThreadProcessId(hwnd_frompoint,&dwProcessId);
 if (GetCurrentProcessId()==dwProcessId)
    {goto EXIT_KILL;
     return;
    }
HANDLE hProcess;
 if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwProcessId))!=NULL)
    {TerminateProcess(hProcess, -1);
    }
EXIT_KILL:
Image1->Picture->Icon->Handle = LoadIcon((HINSTANCE)HInstance,"ORDER");

Button1->Caption = "A..psik..";
Application->ProcessMessages();
Sleep(1000);
Button1->Caption = "Na zdrowie!";
Application->ProcessMessages();
Sleep(800);
Button1->Caption = "JESTEM BOGIEM!";
Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TZeusForm::N2Click(TObject *Sender)
{
Timer1->Enabled=false;
InfoForm->ShowModal();
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TZeusForm::FormCreate(TObject *Sender)
{
Image1->Picture->Icon->Handle = LoadIcon((HINSTANCE)HInstance,"ORDER");
Image1->Update();

hInst = (HINSTANCE)HInstance;
screen.Hwnd = GetDesktopWindow();
screen.Hdc  = GetDC(0);
::GetWindowRect(screen.Hwnd,&screen.Rect);
screen.Bitmap = new Graphics::TBitmap();
screen.Bitmap->Height = (screen.Rect.bottom-screen.Rect.top);
screen.Bitmap->Width  =  (screen.Rect.right-screen.Rect.left);
::SetStretchBltMode(this->Canvas->Handle, STRETCH_DELETESCANS);
Image3->Picture->Bitmap = new Graphics::TBitmap;
Image3->Picture->Bitmap->Width = Image3->Width;
Image3->Picture->Bitmap->Height = Image3->Height;
Image3->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image3->Picture->Bitmap->Canvas->FillRect(Image3->ClientRect);

}
//---------------------------------------------------------------------------


void __fastcall TZeusForm::FormShow(TObject *Sender)
{
Timer1->Enabled=true;        
}
//---------------------------------------------------------------------------

void __fastcall TZeusForm::FormHide(TObject *Sender)
{
Timer1->Enabled = false;        
}
//---------------------------------------------------------------------------


