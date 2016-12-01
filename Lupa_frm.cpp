#include <vcl.h>
#include "Size_frm.h"
#include "Zoom_frm.h"
#include "Atab_frm.h"
#include "Tips_frm.h"
#include "Main_frm.h"
#include "Zeus_frm.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Lupa_frm.h"
//---------------------------------------------------------------------------
#pragma link "framepan"
#pragma link "exedlg"
//#pragma link "..\\..\\Classes\\TSoft_DeskSwitcher.obj"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TLupa_form *Lupa_form;
//---------------------------------------------------------------------------
__fastcall TLupa_form::TLupa_form(TComponent* Owner)
		  : TForm(Owner) , PopupMenuVisible(false)
{
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Redraw(void)
{
static bool lock = 0;
if (lock==1)
{       return;
        }
lock = 1;

::GetClientRect(this->Handle,&options.clientrect);
POINT halfsize, fullsize;
fullsize.x = (options.clientrect.right-4)/options.zoom; fullsize.y = (options.clientrect.bottom-4)/options.zoom;
halfsize.x =  fullsize.x/2; halfsize.y = fullsize.y/2;
options.central = options.clickthrough >0;

static CURSORINFO oldcursorinfo, curcursorinfo;
curcursorinfo.cbSize = sizeof(CURSORINFO);
GetCursorInfo(&curcursorinfo);
static POINT newformpoint;

static HBRUSH backgroundbrush = GetSysColorBrush(COLOR_BACKGROUND);
static HBRUSH crossbrush = GetSysColorBrush(COLOR_BTNFACE);
Desktop->Screen->Context->Resize(options.clientrect.right,options.clientrect.bottom);
// zamalowanie poza ekranem X
//
RECT grabrect, destrect, fillrect;
	 destrect.left  = 0;
	 fillrect.left  = 0; fillrect.right  = 0;
	 fillrect.top   = 0; fillrect.bottom = fullsize.y;
	 grabrect.left  = curcursorinfo.ptScreenPos.x - halfsize.x;
	 grabrect.right = grabrect.left + fullsize.x;
 if (curcursorinfo.ptScreenPos.x < halfsize.x)
	{destrect.left = halfsize.x - curcursorinfo.ptScreenPos.x;
	 fillrect.right = destrect.left;
	 grabrect.left = 0;
	}
 else
 if (curcursorinfo.ptScreenPos.x + halfsize.x >= Desktop->Screen->Rect.right)
	{grabrect.right = Desktop->Screen->Rect.right;
	 fillrect.left = grabrect.right-grabrect.left; fillrect.right = fullsize.x;
	}
 if (fillrect.right - fillrect.left!=0)
	{::FillRect(Desktop->Screen->Context->Hdc,&fillrect,backgroundbrush);
	}
// zamalowanie poza ekranem Y
//
	 destrect.top    = 0;
	 fillrect.top    = 0; fillrect.bottom = 0;
	 fillrect.left   = 0; fillrect.right  = fullsize.x;
	 grabrect.top    = curcursorinfo.ptScreenPos.y - halfsize.y;
	 grabrect.bottom = grabrect.top + fullsize.y;
 if (curcursorinfo.ptScreenPos.y < halfsize.y)
	{destrect.top = halfsize.y - curcursorinfo.ptScreenPos.y;
	 fillrect.bottom = destrect.top;
	 grabrect.top = 0;
	}
 else
 if (curcursorinfo.ptScreenPos.y + halfsize.y >= Desktop->Screen->Rect.bottom)
	{grabrect.bottom = Desktop->Screen->Rect.bottom;
	 fillrect.top = grabrect.bottom-grabrect.top; fillrect.bottom = fullsize.y;
	}
 if (fillrect.top - fillrect.bottom!=0)
	{FillRect(Desktop->Screen->Context->Hdc,&fillrect,backgroundbrush);
	}
// zrzut ekranu
//
::BitBlt(Desktop->Screen->Context->Hdc,
		destrect.left,destrect.top,grabrect.right-grabrect.left,grabrect.bottom-grabrect.top,
		Desktop->Screen->Hdc,
		grabrect.left,grabrect.top,
		SRCCOPY);
//options.sight
//
if (options.sight==true && curcursorinfo.flags!=0)
   {
    ::MoveToEx(Desktop->Screen->Context->Hdc,halfsize.x - 4,halfsize.y,NULL);
      ::LineTo(Desktop->Screen->Context->Hdc,halfsize.x + 5,halfsize.y);
    ::MoveToEx(Desktop->Screen->Context->Hdc,halfsize.x,halfsize.y - 4,NULL);
      ::LineTo(Desktop->Screen->Context->Hdc,halfsize.x,halfsize.y + 5);
   }
// ustawienie pozycji okna i/lub umieszczenie TOPMOST
//
/* if (options.follow==true && options.zoomed==false)
if (oldcursorinfo.ptScreenPos.x!=curcursorinfo.ptScreenPos.x || oldcursorinfo.ptScreenPos.y!=curcursorinfo.ptScreenPos.y)
   {
	if (options.central==true) {
        newformpoint.x = curcursorinfo.ptScreenPos.x - options.clientrect.right/2;
	if (newformpoint.x > Desktop->Screen->Rect.right - options.clientrect.right)
	   {newformpoint.x = Desktop->Screen->Rect.right - options.clientrect.right;
		goto NEXT;
	   }
	    newformpoint.y = curcursorinfo.ptScreenPos.y - options.clientrect.bottom/2;
	if (newformpoint.y > Desktop->Screen->Rect.bottom - options.clientrect.bottom)
	   {newformpoint.y = Desktop->Screen->Rect.bottom - options.clientrect.bottom;
	    goto NEXT;
	   }
    }
	else {
		newformpoint.x = curcursorinfo.ptScreenPos.x + (options.clientrect.right)/2;
	if (newformpoint.x > Desktop->Screen->Rect.right - options.clientrect.right)
	   {newformpoint.x = Desktop->Screen->Rect.right - options.clientrect.right;
		if (Desktop->Screen->Rect.right - curcursorinfo.ptScreenPos.x >= Desktop->Screen->Rect.bottom - curcursorinfo.ptScreenPos.y)
		   {newformpoint.y = curcursorinfo.ptScreenPos.y - (options.clientrect.bottom)/2 - options.clientrect.bottom;
			goto NEXT;
		   }
	   }
		newformpoint.y = curcursorinfo.ptScreenPos.y + (options.clientrect.bottom-options.clientrect.top)/2;
	if (newformpoint.y > Desktop->Screen->Rect.bottom - options.clientrect.bottom)
	   {newformpoint.y = Desktop->Screen->Rect.bottom - options.clientrect.bottom;
		if (Desktop->Screen->Rect.right - curcursorinfo.ptScreenPos.x <= Desktop->Screen->Rect.bottom - curcursorinfo.ptScreenPos.y)
		   {newformpoint.x = curcursorinfo.ptScreenPos.x - (options.clientrect.right)/2 - options.clientrect.right;
			goto NEXT;
		   }
	   }
    }
	 NEXT:
	 SetWindowPos(Handle,
			 (void*)options.zorder,
			 newformpoint.x,newformpoint.y,
			 0,0,
			 SWP_NOCOPYBITS|SWP_NOACTIVATE|SWP_NOSIZE);

	 oldcursorinfo.ptScreenPos = curcursorinfo.ptScreenPos;
	}
*/
    if(!Zeus_form->Visible && !Zoom_form->Visible && !Size_form->Visible && !Atab_form->Visible && !Tips_form->Visible && !PopupMenuVisible)
        {SetWindowPos(Handle,
			 (void*)options.zorder,
			 0,0,
			 0,0,
        SWP_NOREDRAW|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);
        }
RECT framerect = options.clientrect;
::FrameRect(this->Canvas->Handle,&framerect,crossbrush);
	 framerect.left++;
	 framerect.top++;
	 framerect.right--;
	 framerect.bottom--;
::FrameRect(this->Canvas->Handle,&framerect,crossbrush);

StretchBlt(this->Canvas->Handle,
	  2,2,options.clientrect.right-4,options.clientrect.bottom-4,
	  Desktop->Screen->Context->Hdc,
	  0,0,fullsize.x,fullsize.y,
	  SRCCOPY);

lock = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Align(void)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
::GetWindowRect(Handle,&options.rect);

if (options.rect.left	 < Desktop->Screen->Rect.left)
   {options.rect.left    = Desktop->Screen->Rect.left;
   }
if (options.rect.right  >= Desktop->Screen->Rect.right)
   {options.rect.left    = Desktop->Screen->Rect.right  - (options.rect.right-options.rect.left);
   }
if (options.rect.top	 < Desktop->Screen->Rect.top)
   {options.rect.top     = Desktop->Screen->Rect.top;
   }
if (options.rect.bottom >= Desktop->Screen->Rect.bottom)
   {options.rect.top     = Desktop->Screen->Rect.bottom - (options.rect.bottom-options.rect.top);
   }

SetWindowPos(this->Handle,NULL,
		options.rect.left,options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Move()
{
SetWindowPos(this->Handle,NULL,
		options.rect.left,options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Resize(void)
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

void __fastcall TLupa_form::tform_Initialize(void)
{
tform_Load();
Timer1->Interval = options.interval;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
tform_Move(); tform_Resize();
if (options.zoomed)
	 SetWindowLong(this->Handle,GWL_STYLE,GetWindowLong(this->Handle,GWL_STYLE) | WS_MAXIMIZE);
if (options.visible)
	 this->Show();
SetClassLong(this->Handle,GCL_STYLE,GetClassLong(this->Handle,GCL_STYLE) | CS_SAVEBITS);
MenuItemCelownik->Checked = options.sight;
SubMenuZoomClick(this);
SubMenuPrzeswitClick(this);
SubMenuSizeClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Load(void)
{
KluczRejestuSystemuWindows->OpenKey("Software\\TSoft_\\Panel\\Lupa",true);

if (KluczRejestuSystemuWindows->ValueExists("clientrect"))
	{KluczRejestuSystemuWindows->ReadBinaryData("clientrect",&options.clientrect, sizeof(RECT));
	}
else
	{options.clientrect.right = 320;
	 options.clientrect.bottom = 240;
	}
if (KluczRejestuSystemuWindows->ValueExists("rect"))
	{KluczRejestuSystemuWindows->ReadBinaryData("rect",&options.rect, sizeof(RECT));
	}
else
	{options.rect.left = 0; 
	 options.rect.top = 0;
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
if (KluczRejestuSystemuWindows->ValueExists("interval"))
	{options.interval = KluczRejestuSystemuWindows->ReadInteger("interval");
	}
else
	{options.interval = 44;
	}
if (KluczRejestuSystemuWindows->ValueExists("zorder"))
	{options.zorder = KluczRejestuSystemuWindows->ReadInteger("zorder");
	}
else
	{options.zorder = (long)HWND_TOPMOST;
	}
if (KluczRejestuSystemuWindows->ValueExists("sight"))
	{options.sight = KluczRejestuSystemuWindows->ReadBool("sight");
	}
else
	{options.sight = false;
	}
if (KluczRejestuSystemuWindows->ValueExists("zoom"))
	{options.zoom = KluczRejestuSystemuWindows->ReadInteger("zoom");
	}
else
	{options.zoom = 3;
	}
if (KluczRejestuSystemuWindows->ValueExists("central"))
	{options.central = KluczRejestuSystemuWindows->ReadBool("central");
	}
else
	{options.central = false;
	}
KluczRejestuSystemuWindows->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Save(void)
{
if (!options.zoomed)
	{::GetClientRect(this->Handle,&options.clientrect);
	 ::GetWindowRect(this->Handle,&options.rect);
	}
KluczRejestuSystemuWindows->OpenKey("Software\\TSoft_\\Panel\\Lupa",true);

KluczRejestuSystemuWindows->WriteBinaryData("rect",&options.rect,sizeof(RECT));
KluczRejestuSystemuWindows->WriteBinaryData("clientrect",&options.clientrect,sizeof(RECT));
KluczRejestuSystemuWindows->WriteBool("zoomed",options.zoomed);
KluczRejestuSystemuWindows->WriteInteger("alpha",options.alpha);
KluczRejestuSystemuWindows->WriteInteger("clickthrough",options.clickthrough);
KluczRejestuSystemuWindows->WriteBool("visible",options.visible);
KluczRejestuSystemuWindows->WriteInteger("interval", options.interval);
KluczRejestuSystemuWindows->WriteInteger("zorder",options.zorder);
KluczRejestuSystemuWindows->WriteBool("sight",options.sight);
KluczRejestuSystemuWindows->WriteInteger("zoom",options.zoom);
KluczRejestuSystemuWindows->WriteBool("central",options.central);

KluczRejestuSystemuWindows->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormCreate(TObject *Sender)
{
hInst = (HINSTANCE)HInstance;
::SetStretchBltMode(this->Canvas->Handle,STRETCH_DELETESCANS);
Ruszacz = new ts::WindowsMover();
KluczRejestuSystemuWindows = new TRegistry;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormShow(TObject *Sender)
{
Timer1->Enabled = true;
if (Main_form!=NULL ? Main_form->SpeedButtonLupa!=NULL : false)
	 Main_form->SpeedButtonLupa->Down = true;
MenuItemZwin->Caption = "&Hide";
options.visible = true;
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormHide(TObject *Sender)
{
Timer1->Enabled = false;
if (Main_form!=NULL ? Main_form->SpeedButtonLupa!=NULL : false)
	 Main_form->SpeedButtonLupa->Down = false;
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
MenuItemZwin->Caption = "&Show";
options.visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormDestroy(TObject *Sender)
{
delete Ruszacz;
delete KluczRejestuSystemuWindows;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormResize(TObject *Sender)
{
::GetClientRect(this->Handle,&options.clientrect);
::GetWindowRect(this->Handle,&options.rect);
options.zoomed = IsZoomed(Handle);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormPaint(TObject *Sender)
{
/*SetWindowPos(Handle,
	     (void*)options.zorder,
	     0,0,0,0,
	     SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOSENDCHANGING);
RECT temprect;
 ::GetClipBox(this->Canvas->Handle,&temprect);
POINT halfsize, fullsize;
fullsize.x = (temprect.right-4)/options.zoom; fullsize.y = (temprect.bottom-4)/options.zoom;

if (temprect.right!=Desktop->Screen->Context->Bitmap.Info.bmiHeader.biWidth || temprect.bottom!=Desktop->Screen->Context->Bitmap.Info.bmiHeader.biHeight)
{tform_Redraw();
}
else
{
::GetClipBox(this->Canvas->Handle,&temprect);
StretchBlt(this->Canvas->Handle,
	  2,2,options.clientrect.right-4,options.clientrect.bottom-4,
	  Desktop->Screen->Context->Hdc,
	  0,0,fullsize.x,fullsize.y,
	  SRCCOPY);
}*/

}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
PopupMenuVisible = false;

if (Button==mbRight)
	{POINT point;
	 GetCursorPos(&point);
	 LupaPopupMenu->Popup(point.x,point.y);
	 return;
	}
SendMessage(Handle, WM_LBUTTONUP, 0, 0);
SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
//Ruszacz->MouseDown(this->Handle,X,Y,Button);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormMouseMove(TObject *Sender,
		TShiftState Shift, int X, int Y)
{
//Ruszacz->MouseMove(this->Handle,X,Y,true,&Desktop->Screen->Rect,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormMouseUp(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
//Ruszacz->MouseUp(this->Handle,X,Y,Button);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::Timer1Timer(TObject *Sender)
{
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::SubMenuPrzeswitClick(TObject *Sender)
{
if (options.clickthrough==true)
	 MenuItemTrans->Checked = true;

if (options.alpha==-1)
	 NOFF->Checked = true;
else
if (options.alpha==20)
	 N201->Checked = true;
else
if (options.alpha==30)
	 N301->Checked = true;
else
if (options.alpha==40)
	 N401->Checked = true;
else
if (options.alpha==50)
	 N501->Checked = true;
else
if (options.alpha==60)
	 N601->Checked = true;
else
if (options.alpha==70)
	 N701->Checked = true;
else
if (options.alpha==80)
	 N801->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemTransClick(TObject *Sender)
{
options.clickthrough = !options.clickthrough;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
MenuItemTrans->Checked = options.clickthrough;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::NOFFClick(TObject *Sender)
{
options.alpha = -1;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
NOFF->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N101Click(TObject *Sender)
{
options.alpha = 10;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N201Click(TObject *Sender)
{
options.alpha = 20;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N301Click(TObject *Sender)
{
options.alpha = 30;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N301->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N401Click(TObject *Sender)
{
options.alpha = 40;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N401->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N501Click(TObject *Sender)
{
options.alpha = 50;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N501->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N601Click(TObject *Sender)
{
options.alpha = 60;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N601->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N701Click(TObject *Sender)
{
options.alpha = 70;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N701->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N801Click(TObject *Sender)
{
options.alpha = 80;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N801->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::SubMenuSizeClick(TObject *Sender)
{
if ((options.clientrect.right-options.clientrect.left)-4==512)
	{MenuItemSize512384->Checked = true;
	}
else
if ((options.clientrect.right-options.clientrect.left)-4==384)
	{MenuItemSize384288->Checked = true;
	}
else
if ((options.clientrect.right-options.clientrect.left)-4==320)
	{MenuItemSize320240->Checked = true;
	}
else
if ((options.clientrect.right-options.clientrect.left)-4==240)
	{MenuItemSize240180->Checked = true;
	}
else
if ((options.clientrect.right-options.clientrect.left)-4==180)
	{MenuItemSize180120->Checked = true;
	}
else
MenuItemSizeAdvanced->Checked   = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSizeAdvancedClick(TObject *Sender)
{
Size_form->CheckBox1->Checked  = options.clientrect.bottom*4==options.clientrect.right*3;
Size_form->TrackBar1->Position = options.clientrect.right;
Size_form->TrackBar2->Position = options.clientrect.bottom;
long  acc = options.zorder;
	    options.zorder = (long)HWND_BOTTOM;
if (Size_form->Execute(this)==mrOk)
	{options.clientrect.right = Size_form->TrackBar1->Position; options.rect.bottom = Size_form->TrackBar2->Position;
	 tform_Resize();
	}
options.zorder = acc;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize512384Click(TObject *Sender)
{
options.clientrect.right = 512+4; options.clientrect.bottom = 384+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize384288Click(TObject *Sender)
{
options.clientrect.right = 384+4; options.clientrect.bottom = 288+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize320240Click(TObject *Sender)
{
options.clientrect.right = 320+4; options.clientrect.bottom = 240+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize240180Click(TObject *Sender)
{
options.clientrect.right = 240+4; options.clientrect.bottom = 180+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize180120Click(TObject *Sender)
{
options.clientrect.right = 180+4; options.clientrect.bottom = 120+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::SubMenuZoomClick(TObject *Sender)
{
if (options.zoom==8)
	{MenuItemZoom08->Checked   = true;
	}
else
if (options.zoom==6)
	{MenuItemZoom06->Checked   = true;
	}
else
if (options.zoom==4)
	{MenuItemZoom04->Checked   = true;
	}
else
if (options.zoom==3)
	{MenuItemZoom03->Checked   = true;
	}
else
if (options.zoom==2)
	{MenuItemZoom02->Checked   = true;
	}
else
MenuItemZoomAdvanced->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoomAdvancedClick(TObject *Sender)
{
long acc = options.zorder;
	   options.zorder = (long)HWND_BOTTOM;
Zoom_form->TrackBar1->Position = options.zoom;
if (Zoom_form->Execute(this)==mrOk)
	 options.zoom = Zoom_form->TrackBar1->Position;
options.zorder = acc;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom02Click(TObject *Sender)
{
options.zoom = 2;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom03Click(TObject *Sender)
{
options.zoom = 3;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom04Click(TObject *Sender)
{
options.zoom = 4;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom06Click(TObject *Sender)
{
options.zoom = 6;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom08Click(TObject *Sender)
{
options.zoom = 8;
}
//---------------------------------------------------------------------------
void __fastcall TLupa_form::MenuItemCelownikClick(TObject *Sender)
{
options.sight = !options.sight;
MenuItemCelownik->Checked = options.sight;
tform_Align();
}

//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZwinClick(TObject *Sender)
{
this->Visible = !this->Visible;
SetForegroundWindow(Lupa_form->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::Na1Click(TObject *Sender)
{
SetWindowPos(Handle,
    	 (void*)options.zorder,
    	 (Desktop->Screen->Rect.right-Desktop->Screen->Rect.left)/2 - this->Width/2,(Desktop->Screen->Rect.bottom-Desktop->Screen->Rect.top)/2 - this->Height/2,
    	 0,0,
    	 SWP_NOCOPYBITS|SWP_NOACTIVATE|SWP_NOSIZE);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::Natopie1Click(TObject *Sender)
{
Natopie1->Checked = !Natopie1->Checked;
if (Natopie1->Checked) options.zorder = (long)HWND_TOPMOST;
else options.zorder = NULL;
}
//---------------------------------------------------------------------------

/*
void __fastcall TLupa_form::SubMenuTimerClick(TObject *Sender)
{
if (options.interval==20)
	U020->Checked = true;
else
if (options.interval==25)
	U025->Checked = true;
else
if (options.interval==30)
	U030->Checked = true;
else
if (options.interval==40)
	U040->Checked = true;
else
if (options.interval==50)
	U050->Checked = true;
else
if (options.interval==100)
	U100->Checked = true;
else
if (options.interval==200)
	U200->Checked = true;
else
if (options.interval==250)
	U250->Checked = true;
else
if (options.interval==500)
	U500->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U020Click(TObject *Sender)
{
options.interval = 20;
Timer1->Interval = options.interval;
U020->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U025Click(TObject *Sender)
{
options.interval = 25;
Timer1->Interval = options.interval;
U025->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U030Click(TObject *Sender)
{
options.interval = 30;
Timer1->Interval = options.interval;
U030->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U040Click(TObject *Sender)
{
options.interval = 40;
Timer1->Interval = options.interval;
U040->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U050Click(TObject *Sender)
{
options.interval = 50;
Timer1->Interval = options.interval;
U050->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U100Click(TObject *Sender)
{
options.interval = 100;
Timer1->Interval = options.interval;
U100->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U200Click(TObject *Sender)
{
options.interval = 200;
Timer1->Interval = options.interval;
U200->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U250Click(TObject *Sender)
{
options.interval = 250;
Timer1->Interval = options.interval;
U250->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U500Click(TObject *Sender)
{
options.interval = 500;
Timer1->Interval = options.interval;
U500->Checked = true;
}
//---------------------------------------------------------------------------
*/



void __fastcall TLupa_form::LupaPopupMenuPopup(TObject *Sender)
{
PopupMenuVisible = true;    
}
//---------------------------------------------------------------------------

