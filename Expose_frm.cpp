//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 #include "Main_frm.h"
#include "Expose_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExpose_form *Expose_form;
//---------------------------------------------------------------------------
__fastcall TExpose_form::TExpose_form(TComponent* Owner)
        : TForm(Owner)
{
Index = 0;
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::tform_Align(void)
{
TShiftState shiftState;
this->FormMouseDown(this,mbLeft,shiftState,0,0);
this->FormMouseMove(this,shiftState,0,0);
  this->FormMouseUp(this,mbLeft,shiftState,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::tform_Resize()
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

void __fastcall TExpose_form::tform_Move()
{
SetWindowPos(this->Handle,
		0,
		options.rect.left,options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::tform_Initialize(void)
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

void __fastcall TExpose_form::tform_Load(void)
{
KluczRejestuSystemuWindows->OpenKey("Software\\TSoft_\\Panel\\Expose",true);

if (KluczRejestuSystemuWindows->ValueExists("rect"))
   {KluczRejestuSystemuWindows->ReadBinaryData("rect",&options.rect, sizeof(RECT));
   }
else
   {options.rect.left = 0;
    options.rect.top = 0;
   }
if (KluczRejestuSystemuWindows->ValueExists("clientrect"))
   {KluczRejestuSystemuWindows->ReadBinaryData("clientrect",&options.clientrect, sizeof(RECT));
    if (options.clientrect.right-options.clientrect.left != 385 || options.clientrect.bottom-options.clientrect.top != 30)
        {options.clientrect.right = 385;
         options.clientrect.bottom = 30;
         options.clientrect.left = 0;
         options.clientrect.top = 0;}
   }
else
   {options.clientrect.right = 385;
    options.clientrect.bottom = 30;
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

void __fastcall TExpose_form::tform_Save(void)
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
void __fastcall TExpose_form::FormHide(TObject *Sender)
{
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Down = 1;
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if (Down==false)
return;

tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (++Index>=32) Index = 0;
Down = 0;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TExpose_form::tform_Redraw(void)
{
static bool lock = 0;
if (lock==1)
{       return;
        }
lock = 1;

::GetClientRect(this->Handle,&options.clientrect);
static POINT oldcursorpoint, cursorpoint;
::GetCursorPos(&cursorpoint);
::ScreenToClient(this->Handle,&cursorpoint);

static HBRUSH backbrush = GetSysColorBrush(COLOR_BACKGROUND);
static HBRUSH brush = GetSysColorBrush(COLOR_BTNFACE);
static HBRUSH greenbrush = CreateSolidBrush(RGB(115,255,115));
static HPEN pen = CreatePen(PS_SOLID,1,GetSysColor(COLOR_WINDOWFRAME));
Desktop->Screen->Context->Resize(options.clientrect.right,options.clientrect.bottom);
SelectObject(Desktop->Screen->Context->Hdc,brush);
SelectObject(Desktop->Screen->Context->Hdc,pen);
FillRect(Desktop->Screen->Context->Hdc,&options.clientrect,backbrush);

    Tiles->Tile[Index]->Rect.left = cursorpoint.x - 32;
    Tiles->Tile[Index]->Rect.top = cursorpoint.y - 24;
    Tiles->Tile[Index]->Rect.right = cursorpoint.x + 32;
    Tiles->Tile[Index]->Rect.bottom = cursorpoint.y + 24;

for (int i = 0; i <= Index; i++) {
::Rectangle(Desktop->Screen->Context->Hdc,
    Tiles->Tile[i]->Rect.left,
    Tiles->Tile[i]->Rect.top,
    Tiles->Tile[i]->Rect.right,
    Tiles->Tile[i]->Rect.bottom
   );
/*StretchBlt(Desktop->Screen->Context->Hdc,
	  Tiles->Tile[i]->Rect.left,Tiles->Tile[i]->Rect.top,Tiles->Tile[i]->Rect.right-Tiles->Tile[i]->Rect.left,Tiles->Tile[i]->Rect.bottom-Tiles->Tile[i]->Rect.top,
	  Desktop->Screen->Context->Hdc,
	  0,0,options.clientrect.right,options.clientrect.bottom,
	  SRCCOPY); */
::InvertRect(Desktop->Screen->Context->Hdc,
    &Tiles->Tile[i]->Rect   );
          }

StretchBlt(this->Canvas->Handle,
	  0,0,options.clientrect.right,options.clientrect.bottom,
	  Desktop->Screen->Context->Hdc,
	  0,0,options.clientrect.right,options.clientrect.bottom,
	  SRCCOPY);

oldcursorpoint.x = cursorpoint.x;
oldcursorpoint.y = cursorpoint.y;
lock = 0;
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::FormCreate(TObject *Sender)
{
updateing = 0;
hInst = (HINSTANCE)HInstance;
::SetStretchBltMode(this->Canvas->Handle,STRETCH_DELETESCANS);
Ruszacz = new ts::WindowsMover();
KluczRejestuSystemuWindows = new TRegistry;
}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::FormDestroy(TObject *Sender)
{
delete Ruszacz;
delete KluczRejestuSystemuWindows;

}
//---------------------------------------------------------------------------

void __fastcall TExpose_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

