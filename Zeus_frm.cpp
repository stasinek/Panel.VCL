//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Zeus_frm.h"
#include "Lupa_frm.h"
#include "Desk_frm.h"
#include "Zoom_frm.h"
#include "Move_frm.h"
#include "Main_frm.h"
#include "Tips_frm.h"
#include "./../../FORM_TEMPLATES/About_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <winuser.h>

TZeus_form *Zeus_form;
//---------------------------------------------------------------------------
__fastcall TZeus_form::TZeus_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::tform_Align(void)
{

}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::tform_Resize()
{
options.rect.right  = options.rect.left + options.clientrect.right;
options.rect.bottom = options.rect.top  + options.clientrect.bottom;
AdjustWindowRectEx(&options.rect,
		GetWindowLong(this->Handle,GWL_STYLE),false,
		GetWindowLong(this->Handle,GWL_EXSTYLE));
SetWindowPos(this->Handle,NULL,
		0,0,(options.rect.right-options.rect.left),(options.rect.bottom-options.rect.top),
		SWP_NOCOPYBITS|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::tform_Move()
{
SetWindowPos(this->Handle,
		0,
		options.rect.left,options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::tform_Initialize(void)
{
tform_Load();
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
tform_Move(); tform_Resize();
SetClassLong(this->Handle,GCL_STYLE,GetClassLong(this->Handle,GCL_STYLE) | CS_SAVEBITS);
if (options.zoomed)
    SetWindowLong(this->Handle,GWL_STYLE,GetWindowLong(this->Handle,GWL_STYLE) | WS_MAXIMIZE);
if (options.visible) this->Show();
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::tform_Load(void)
{
KluczRejestuSystemuWindows->OpenKey("Software\\TSoft\\Panel\\Expose",true);


if (KluczRejestuSystemuWindows->ValueExists("rect"))
   {KluczRejestuSystemuWindows->ReadBinaryData("rect",&options.rect, sizeof(RECT));
   }
else
   {options.rect.left = 0;
    options.rect.top = 0;
   }
if (KluczRejestuSystemuWindows->ValueExists("clientrect"))
   {KluczRejestuSystemuWindows->ReadBinaryData("clientrect",&options.clientrect, sizeof(RECT));
    if (options.clientrect.right-options.clientrect.right < 512 || options.clientrect.bottom-options.clientrect.bottom < 462)
        {options.clientrect.right = 512;
         options.clientrect.bottom = 462;
         options.clientrect.left = 0;
         options.clientrect.top = 0;
        }
   }
else
   {options.clientrect.right = 512;
    options.clientrect.bottom = 462;
    options.clientrect.left = 0;
    options.clientrect.top = 0;
   }
if (KluczRejestuSystemuWindows->ValueExists("zoomed"))
   {options.zoomed = KluczRejestuSystemuWindows->ReadBool("zoomed");
   }
else
   {options.zoomed = false;
   }
if (KluczRejestuSystemuWindows->ValueExists("alpha"))
   {options.alpha = KluczRejestuSystemuWindows->ReadInteger("alpha");
   }
else
   {options.alpha = -1;
   }
if (KluczRejestuSystemuWindows->ValueExists("clickthrough"))
   {options.clickthrough  = KluczRejestuSystemuWindows->ReadInteger("clickthrough");
   }
else
   {options.clickthrough  = 0;
   }
if (KluczRejestuSystemuWindows->ValueExists("visible"))
   {options.visible = KluczRejestuSystemuWindows->ReadBool("visible");
   }
else
   {options.visible = false;
   }
KluczRejestuSystemuWindows->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::tform_Save(void)
{
if (!options.zoomed)
   {::GetClientRect(this->Handle,&options.clientrect);
    ::GetWindowRect(this->Handle,&options.rect);
   }
KluczRejestuSystemuWindows->OpenKey("Software\\TSoft_\\Panel\\Expose",true);

KluczRejestuSystemuWindows->WriteBinaryData("rect",&options.rect,sizeof(RECT));
KluczRejestuSystemuWindows->WriteBinaryData("clientrect",&options.clientrect,sizeof(RECT));
KluczRejestuSystemuWindows->WriteBool("zoomed",options.zoomed);
KluczRejestuSystemuWindows->WriteInteger("alpha",options.alpha);
KluczRejestuSystemuWindows->WriteInteger("clickthrough",options.clickthrough);
KluczRejestuSystemuWindows->WriteBool("visible",options.visible);

KluczRejestuSystemuWindows->CloseKey();
}

//---------------------------------------------------------------------------

void __fastcall TZeus_form::BitBtn1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TZeus_form::Tile1Click(TObject *Sender)
{
TileWindows(NULL,
    MDITILE_VERTICAL,NULL,NULL,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TZeus_form::Tile2Click(TObject *Sender)
{
TileWindows(NULL,
    MDITILE_HORIZONTAL,NULL,NULL,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TZeus_form::Cascade1Click(TObject *Sender)
{
CascadeWindows(NULL,
    MDITILE_SKIPDISABLED,NULL,NULL,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TZeus_form::ArrangeAll1Click(TObject *Sender)
{
ArrangeIconicWindows(GetDesktopWindow());
}
//---------------------------------------------------------------------------
void __fastcall TZeus_form::N2Click(TObject *Sender)
{
Timer1->Enabled=false;
About_form->ShowModal();
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::FormCreate(TObject *Sender)
{
updateing = 0;
hInst = (HINSTANCE)HInstance;
::SetStretchBltMode(this->Canvas->Handle,STRETCH_DELETESCANS);
Ruszacz = new ts::WindowsMover();
KluczRejestuSystemuWindows = new TRegistry;

//Image1->Picture->Icon->Handle = LoadIcon((HINSTANCE)HInstance,"ORDER");
//Image1->Update();

hInst = (HINSTANCE)HInstance;
::SetStretchBltMode(this->Canvas->Handle, STRETCH_DELETESCANS);

Image2->Picture->Bitmap = new Graphics::TBitmap;
Image2->Picture->Bitmap->Width = Image2->Width;
Image2->Picture->Bitmap->Height = Image2->Height;
Image2->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image2->Picture->Bitmap->Canvas->FillRect(Image2->ClientRect);

}
//---------------------------------------------------------------------------


void __fastcall TZeus_form::FormShow(TObject *Sender)
{
//if (Main_form!=NULL ? Main_form->SpeedButtonZeus!=NULL : false)
//	 Main_form->SpeedButtonZeus->Down = true;
options.visible = true;
tform_Align();

Desktop->Collect();
/*SetStretchBltMode(Image2->Picture->Bitmap->Canvas->Handle,HALFTONE);
StretchBlt(Image2->Picture->Bitmap->Canvas->Handle,
    	 0,0,Image2->Width,Image2->Height,
    	 Desktop->Screen->Context->Hdc,
    	 0,0,Desktop->Screen->Rect.right,Desktop->Screen->Rect.bottom,
    		 SRCCOPY);
  */
Desktop->Capture();
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::FormHide(TObject *Sender)
{
Timer1->Enabled = false;
// if (Main_form!=NULL ? Main_form->SpeedButtonZeus!=NULL : false)
//	 Main_form->SpeedButtonZeus->Down = false;
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::Window1Click(TObject *Sender)
{
Timer1->Enabled=!Timer1->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::SpeedButton1Click(TObject *Sender)
{
//Image1->Picture->Icon->Handle = LoadIcon((HINSTANCE)HInstance,"KILL");
SpeedButton1->Down = true;

while ((GetAsyncKeyState(2) & 0x8000)==0)
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
//Image1->Picture->Icon->Handle = LoadIcon((HINSTANCE)HInstance,"ORDER");

SpeedButton1->Caption = "Ups..";
Application->ProcessMessages();
Sleep(1000);
SpeedButton1->Caption = "Cheers!";
Application->ProcessMessages();
Sleep(800);
SpeedButton1->Caption = "I'm The GOD!";
Application->ProcessMessages();

SpeedButton1->Down = false;
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::Kill1Click(TObject *Sender)
{
 SpeedButton1Click(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TZeus_form::Image2MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
POINT cursorpoint;
cursorpoint.x = X;
cursorpoint.x = (cursorpoint.x * (Desktop->Screen->Rect.right -Desktop->Screen->Rect.left))/Image2->Width;
cursorpoint.y = Y;
cursorpoint.y = (cursorpoint.y * (Desktop->Screen->Rect.bottom-Desktop->Screen->Rect.top)) /Image2->Height;

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

bool LetPrintWindow = true;

SetWindowPos(Handle,HWND_TOPMOST,0,0,0,0,
             SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_NOSENDCHANGING);
POINT point_ofcursor;
//GetCursorPos(&point_ofcursor);
point_ofcursor = cursorpoint;
HWND hwnd_frompoint;
//hwnd_frompoint = WindowFromPoint(point_ofcursor);
hwnd_frompoint=curhwnd;
HWND hwnd_test = GetTopWindow(hwnd_frompoint);

DWORD dwProcessId;
GetWindowThreadProcessId(hwnd_frompoint,&dwProcessId);
 if (GetCurrentProcessId()==dwProcessId)
    {return;
    }

static HWND hwnd_frompoint_old;
if (hwnd_frompoint_old!=hwnd_frompoint) hwnd_frompoint_old = hwnd_frompoint;
else return;

if (hwnd_frompoint!=NULL)
{LPSTR title_text;
 title_text = (char*)LocalAlloc(LPTR,256);
 GetWindowText(hwnd_frompoint,title_text,256);
 LPSTR class_name;
 class_name = (char*)LocalAlloc(LPTR,256);
 GetClassName(hwnd_frompoint,class_name,256);
 LocalFree(class_name);
 LocalFree(title_text);
}

HWND hwnd_parent;
hwnd_parent = GetParent(hwnd_frompoint);
if (hwnd_parent==NULL) hwnd_parent=hwnd_frompoint;
static HWND hwnd_parent_old;
if (hwnd_parent_old!=hwnd_parent) hwnd_parent_old = hwnd_parent;
else return;
if (hwnd_parent!=NULL)
{LPSTR parent_title_text;
 parent_title_text = (char*)LocalAlloc(LPTR,256);
 GetWindowText(hwnd_parent,parent_title_text,256);
 LPSTR parent_class_name;
 parent_class_name = (char*)LocalAlloc(LPTR,256);
 GetClassName(hwnd_parent,parent_class_name,256);
 LocalFree(parent_class_name);
 LocalFree(parent_title_text);
}

HWND hwnd_top = 0;
for (HWND cur = hwnd_parent; cur!=NULL;cur = GetParent(cur))
    {hwnd_top = cur;
    }
if (hwnd_top==NULL) hwnd_top=hwnd_frompoint;
static HWND hwnd_top_old;
if (hwnd_top_old!=hwnd_top) hwnd_top_old = hwnd_top;
else return;

LPSTR top_title_text = (char*)LocalAlloc(LPTR,256);
LPSTR top_class_name;

if (hwnd_top!=NULL)
{
 GetWindowText(hwnd_top,top_title_text,256);
 top_class_name = (char*)LocalAlloc(LPTR,256);
 GetClassName(hwnd_top,top_class_name,256);
 LocalFree(top_class_name);

 LPSTR modulefilename_text;
 modulefilename_text = (char*)LocalAlloc(LPTR,256);
GetWindowModuleFileName(hwnd_top,modulefilename_text,256);
StatusBar1->SimpleText = modulefilename_text;
LocalFree(modulefilename_text);


if (top_title_text)
if (::strstr(top_title_text,"Program Manager"))
LetPrintWindow=false;
if (top_title_text)
if (::strstr(top_title_text,"Shell_TrayWnd"))
LetPrintWindow=false;
if (top_title_text)
if (::strstr(top_title_text,"Progman"))
LetPrintWindow=false;

LocalFree(top_title_text);

RECT temprect;
if (LetPrintWindow==true) {
   //     ::PrintWindow(hwnd_top,Desktop->Screen->Context->Hdc,0);
      ::GetWindowRect(hwnd_top,&temprect);
}
else {   temprect.left=0; temprect.top=0; temprect.bottom=Image2->Height;temprect.right=Image2->Width;
}
RECT sr, or;
double sw = temprect.right-temprect.left, sh = temprect.bottom-temprect.top;
if (sw==0 || sh ==0) {sw = 1; sh=1;}
double skalax = sw/sh, skalay = sh/sw;

double iw = Image2->Width, ih = Image2->Height;
double skalaimagex = iw/ih, skalaimagey = ih/iw;

double ow, oh;

if (skalax > skalaimagex)
{ow = iw;
 oh = (int)(iw*skalay);}
else
{ow = (int)(ih*skalax);
 oh = ih;}
//Label1->Caption = "sw="+FloatToStr(sw)+",sh="+FloatToStr(sh)+",ow="+FloatToStr(ow)+",oh="+FloatToStr(oh);
Image2->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image2->Picture->Bitmap->Canvas->FillRect(Image2->ClientRect);
if (LetPrintWindow==true) {
        ::SetStretchBltMode(Image2->Canvas->Handle, HALFTONE);
        RECT framerect;
        framerect.left = (int)((iw-ow)/2); framerect.top = (int)((ih-oh)/2);
        framerect.right = framerect.left+(int)ow; framerect.bottom = framerect.top+(int)oh;
        ::StretchBlt(Image2->Canvas->Handle,
			  framerect.left+1,framerect.top+1,framerect.right-framerect.left-2,framerect.bottom-framerect.top-2,
			  Desktop->Screen->Context->Hdc,
			  0,0,(int)sw,(int)sh,
			  SRCCOPY);
    }
else
    {
///alternatywna zawartoœæ
}
Image2->Repaint();
//HICON hicon =(HICON)GetClassLong(hwnd_top, GCL_HICON);//HICON hicon = (HICON)SendMessage(hwnd_top,WM_GETICON,ICON_BIG,0);
//Image1->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
//Image1->Picture->Bitmap->Canvas->FillRect(Image1->ClientRect);
//	  ::DrawIconEx(Image1->Canvas->Handle,0,0,
//hicon,32,32,0,Image1->Canvas->Brush->Handle,DI_NORMAL);
//if (hicon!=NULL) DeleteObject(hicon);
//Image1->Repaint();
   }
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::Image2Click(TObject *Sender)
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
EXIT_KILL:
}
//---------------------------------------------------------------------------


void __fastcall TZeus_form::FormResize(TObject *Sender)
{
::GetClientRect(this->Handle,&options.clientrect);
::GetWindowRect(this->Handle,&options.rect);
options.zoomed = IsZoomed(Handle);        
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::FormDestroy(TObject *Sender)
{
delete Ruszacz;
delete KluczRejestuSystemuWindows;
}
//---------------------------------------------------------------------------

void __fastcall TZeus_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

