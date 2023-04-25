//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Size_frm.h"
#include "Zoom_frm.h"
#include "Atab_frm.h"
#include "Tips_frm.h"
#include "Main_frm.h"
#include "Zeus_frm.h"
#include "Lupa_frm.h"
//---------------------------------------------------------------------------
#pragma link "framepan"
#pragma link "exedlg"
//#pragma link "..\\..\\Classes\\TSoft_DeskSwitcher.obj"
#pragma package(smart_init)
#pragma link "FRAMEPAN"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TLupa_form *Lupa_form;
//---------------------------------------------------------------------------
__fastcall TLupa_form::TLupa_form(TComponent* Owner)
		  : TForm(Owner) , PopupMenuVisible(false)
{
Helper = new TForm_Helper(this);
Helper->Default.clientrect.right = 320; Helper->Default.clientrect.bottom = 240;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Redraw(void)
{
static bool lock = 0;
if (lock==1)
{       return;
        }
lock = 1;

::GetClientRect(this->Handle,&Helper->Options.clientrect);
POINT halfsize, fullsize;
fullsize.x = (Helper->Options.clientrect.right-4)/Helper->Options.zoom; fullsize.y = (Helper->Options.clientrect.bottom-4)/Helper->Options.zoom;
halfsize.x =  fullsize.x/2; halfsize.y = fullsize.y/2;
Helper->Options.central = Helper->Options.clickthrough >0;

static CURSORINFO oldcursorinfo, curcursorinfo;
curcursorinfo.cbSize = sizeof(CURSORINFO);
GetCursorInfo(&curcursorinfo);
static POINT newformpoint;

static HBRUSH backgroundbrush = GetSysColorBrush(COLOR_BACKGROUND);
static HBRUSH crossbrush = GetSysColorBrush(COLOR_BTNFACE);
Desktop->Screen->Context->Resize(Helper->Options.clientrect.right,Helper->Options.clientrect.bottom);
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
//Helper->Options.sight
//
if (Helper->Options.sight==true && curcursorinfo.flags!=0)
   {
    ::MoveToEx(Desktop->Screen->Context->Hdc,halfsize.x - 4,halfsize.y,NULL);
      ::LineTo(Desktop->Screen->Context->Hdc,halfsize.x + 5,halfsize.y);
    ::MoveToEx(Desktop->Screen->Context->Hdc,halfsize.x,halfsize.y - 4,NULL);
      ::LineTo(Desktop->Screen->Context->Hdc,halfsize.x,halfsize.y + 5);
   }
// ustawienie pozycji okna i/lub umieszczenie TOPMOST
//
/* if (Helper->Options.follow==true && Helper->Options.zoomed==false)
if (oldcursorinfo.ptScreenPos.x!=curcursorinfo.ptScreenPos.x || oldcursorinfo.ptScreenPos.y!=curcursorinfo.ptScreenPos.y)
   {
	if (Helper->Options.central==true) {
        newformpoint.x = curcursorinfo.ptScreenPos.x - Helper->Options.clientrect.right/2;
	if (newformpoint.x > Desktop->Screen->Rect.right - Helper->Options.clientrect.right)
	   {newformpoint.x = Desktop->Screen->Rect.right - Helper->Options.clientrect.right;
		goto NEXT;
	   }
	    newformpoint.y = curcursorinfo.ptScreenPos.y - Helper->Options.clientrect.bottom/2;
	if (newformpoint.y > Desktop->Screen->Rect.bottom - Helper->Options.clientrect.bottom)
	   {newformpoint.y = Desktop->Screen->Rect.bottom - Helper->Options.clientrect.bottom;
	    goto NEXT;
	   }
    }
	else {
		newformpoint.x = curcursorinfo.ptScreenPos.x + (Helper->Options.clientrect.right)/2;
	if (newformpoint.x > Desktop->Screen->Rect.right - Helper->Options.clientrect.right)
	   {newformpoint.x = Desktop->Screen->Rect.right - Helper->Options.clientrect.right;
		if (Desktop->Screen->Rect.right - curcursorinfo.ptScreenPos.x >= Desktop->Screen->Rect.bottom - curcursorinfo.ptScreenPos.y)
		   {newformpoint.y = curcursorinfo.ptScreenPos.y - (Helper->Options.clientrect.bottom)/2 - Helper->Options.clientrect.bottom;
			goto NEXT;
		   }
	   }
		newformpoint.y = curcursorinfo.ptScreenPos.y + (Helper->Options.clientrect.bottom-Helper->Options.clientrect.top)/2;
	if (newformpoint.y > Desktop->Screen->Rect.bottom - Helper->Options.clientrect.bottom)
	   {newformpoint.y = Desktop->Screen->Rect.bottom - Helper->Options.clientrect.bottom;
		if (Desktop->Screen->Rect.right - curcursorinfo.ptScreenPos.x <= Desktop->Screen->Rect.bottom - curcursorinfo.ptScreenPos.y)
		   {newformpoint.x = curcursorinfo.ptScreenPos.x - (Helper->Options.clientrect.right)/2 - Helper->Options.clientrect.right;
			goto NEXT;
		   }
	   }
    }
	 NEXT:
	 SetWindowPos(Handle,
			 (void*)Helper->Options.zorder,
			 newformpoint.x,newformpoint.y,
			 0,0,
			 SWP_NOCOPYBITS|SWP_NOACTIVATE|SWP_NOSIZE);

	 oldcursorinfo.ptScreenPos = curcursorinfo.ptScreenPos;
	}
*/
    if(!Zeus_form->Visible && !Zoom_form->Visible && !Size_form->Visible && !Atab_form->Visible && !Tips_form->Visible && !PopupMenuVisible)
        {SetWindowPos(Handle,
			 (void*)Helper->Options.zorder,
			 0,0,
			 0,0,
        SWP_NOREDRAW|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);
        }
RECT framerect = Helper->Options.clientrect;
::FrameRect(this->Canvas->Handle,&framerect,crossbrush);
	 framerect.left++;
	 framerect.top++;
	 framerect.right--;
	 framerect.bottom--;
::FrameRect(this->Canvas->Handle,&framerect,crossbrush);

StretchBlt(this->Canvas->Handle,
	  2,2,Helper->Options.clientrect.right-4,Helper->Options.clientrect.bottom-4,
	  Desktop->Screen->Context->Hdc,
	  0,0,fullsize.x,fullsize.y,
	  SRCCOPY);

lock = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Align(void)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
::GetWindowRect(Handle,&Helper->Options.rect);

if (Helper->Options.rect.left	 < Desktop->Screen->Rect.left)
   {Helper->Options.rect.left    = Desktop->Screen->Rect.left;
   }
if (Helper->Options.rect.right  >= Desktop->Screen->Rect.right)
   {Helper->Options.rect.left    = Desktop->Screen->Rect.right  - (Helper->Options.rect.right-Helper->Options.rect.left);
   }
if (Helper->Options.rect.top	 < Desktop->Screen->Rect.top)
   {Helper->Options.rect.top     = Desktop->Screen->Rect.top;
   }
if (Helper->Options.rect.bottom >= Desktop->Screen->Rect.bottom)
   {Helper->Options.rect.top     = Desktop->Screen->Rect.bottom - (Helper->Options.rect.bottom-Helper->Options.rect.top);
   }

SetWindowPos(this->Handle,NULL,
		Helper->Options.rect.left,Helper->Options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Move()
{
SetWindowPos(this->Handle,NULL,
		Helper->Options.rect.left,Helper->Options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Resize(void)
{
Helper->Options.rect.right  = Helper->Options.rect.left + Helper->Options.clientrect.right;
Helper->Options.rect.bottom = Helper->Options.rect.top  + Helper->Options.clientrect.bottom;

AdjustWindowRectEx(&Helper->Options.rect,
		GetWindowLong(this->Handle,GWL_STYLE),false,
		GetWindowLong(this->Handle,GWL_EXSTYLE));
SetWindowPos(this->Handle,NULL,
		0,0,(Helper->Options.rect.right-Helper->Options.rect.left),(Helper->Options.rect.bottom-Helper->Options.rect.top),
		SWP_NOCOPYBITS|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::tform_Initialize(void)
{
Helper->Load("Lupa");
Timer1->Interval = Helper->Options.interval;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
tform_Move(); tform_Resize();
if (Helper->Options.zoomed)
	 SetWindowLong(this->Handle,GWL_STYLE,GetWindowLong(this->Handle,GWL_STYLE) | WS_MAXIMIZE);
if (Helper->Options.visible)
	 this->Show();
SetClassLong(this->Handle,GCL_STYLE,GetClassLong(this->Handle,GCL_STYLE) | CS_SAVEBITS);
MenuItemCelownik->Checked = Helper->Options.sight;
SubMenuZoomClick(this);
SubMenuPrzeswitClick(this);
SubMenuSizeClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormCreate(TObject *Sender)
{
hInst = (HINSTANCE)HInstance;
::SetStretchBltMode(this->Canvas->Handle,STRETCH_DELETESCANS);
Ruszacz = new ts::WindowsMover();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormShow(TObject *Sender)
{
Timer1->Enabled = true;
if (Main_form!=NULL ? Main_form->SpeedButtonLupa!=NULL : false)
	 Main_form->SpeedButtonLupa->Down = true;
MenuItemZwin->Caption = "&Hide";
Helper->Options.visible = true;
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
Helper->Options.visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormDestroy(TObject *Sender)
{
delete Ruszacz;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormResize(TObject *Sender)
{
::GetClientRect(this->Handle,&Helper->Options.clientrect);
::GetWindowRect(this->Handle,&Helper->Options.rect);
Helper->Options.zoomed = IsZoomed(Handle);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::FormPaint(TObject *Sender)
{
/*SetWindowPos(Handle,
	     (void*)Helper->Options.zorder,
	     0,0,0,0,
	     SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOSENDCHANGING);
RECT temprect;
 ::GetClipBox(this->Canvas->Handle,&temprect);
POINT halfsize, fullsize;
fullsize.x = (temprect.right-4)/Helper->Options.zoom; fullsize.y = (temprect.bottom-4)/Helper->Options.zoom;

if (temprect.right!=Desktop->Screen->Context->Bitmap.Info.bmiHeader.biWidth || temprect.bottom!=Desktop->Screen->Context->Bitmap.Info.bmiHeader.biHeight)
{tform_Redraw();
}
else
{
::GetClipBox(this->Canvas->Handle,&temprect);
StretchBlt(this->Canvas->Handle,
	  2,2,Helper->Options.clientrect.right-4,Helper->Options.clientrect.bottom-4,
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
if (Helper->Options.clickthrough==true)
	 MenuItemTrans->Checked = true;

if (Helper->Options.alpha==-1)
	 NOFF->Checked = true;
else
if (Helper->Options.alpha==20)
	 N201->Checked = true;
else
if (Helper->Options.alpha==30)
	 N301->Checked = true;
else
if (Helper->Options.alpha==40)
	 N401->Checked = true;
else
if (Helper->Options.alpha==50)
	 N501->Checked = true;
else
if (Helper->Options.alpha==60)
	 N601->Checked = true;
else
if (Helper->Options.alpha==70)
	 N701->Checked = true;
else
if (Helper->Options.alpha==80)
	 N801->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemTransClick(TObject *Sender)
{
Helper->Options.clickthrough = !Helper->Options.clickthrough;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
MenuItemTrans->Checked = Helper->Options.clickthrough;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::NOFFClick(TObject *Sender)
{
Helper->Options.alpha = -1;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
NOFF->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N101Click(TObject *Sender)
{
Helper->Options.alpha = 10;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N201Click(TObject *Sender)
{
Helper->Options.alpha = 20;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N301Click(TObject *Sender)
{
Helper->Options.alpha = 30;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N301->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N401Click(TObject *Sender)
{
Helper->Options.alpha = 40;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N401->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N501Click(TObject *Sender)
{
Helper->Options.alpha = 50;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N501->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N601Click(TObject *Sender)
{
Helper->Options.alpha = 60;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N601->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N701Click(TObject *Sender)
{
Helper->Options.alpha = 70;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N701->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::N801Click(TObject *Sender)
{
Helper->Options.alpha = 80;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N801->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::SubMenuSizeClick(TObject *Sender)
{
if ((Helper->Options.clientrect.right-Helper->Options.clientrect.left)-4==512)
	{MenuItemSize512384->Checked = true;
	}
else
if ((Helper->Options.clientrect.right-Helper->Options.clientrect.left)-4==384)
	{MenuItemSize384288->Checked = true;
	}
else
if ((Helper->Options.clientrect.right-Helper->Options.clientrect.left)-4==320)
	{MenuItemSize320240->Checked = true;
	}
else
if ((Helper->Options.clientrect.right-Helper->Options.clientrect.left)-4==240)
	{MenuItemSize240180->Checked = true;
	}
else
if ((Helper->Options.clientrect.right-Helper->Options.clientrect.left)-4==180)
	{MenuItemSize180120->Checked = true;
	}
else
MenuItemSizeAdvanced->Checked   = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSizeAdvancedClick(TObject *Sender)
{
Size_form->CheckBox1->Checked  = Helper->Options.clientrect.bottom*4==Helper->Options.clientrect.right*3;
Size_form->TrackBar1->Position = Helper->Options.clientrect.right;
Size_form->TrackBar2->Position = Helper->Options.clientrect.bottom;
long  acc = Helper->Options.zorder;
	    Helper->Options.zorder = (long)HWND_BOTTOM;
if (Size_form->Execute(this)==mrOk)
	{Helper->Options.clientrect.right = Size_form->TrackBar1->Position; Helper->Options.rect.bottom = Size_form->TrackBar2->Position;
	 tform_Resize();
	}
Helper->Options.zorder = acc;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize512384Click(TObject *Sender)
{
Helper->Options.clientrect.right = 512+4; Helper->Options.clientrect.bottom = 384+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize384288Click(TObject *Sender)
{
Helper->Options.clientrect.right = 384+4; Helper->Options.clientrect.bottom = 288+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize320240Click(TObject *Sender)
{
Helper->Options.clientrect.right = 320+4; Helper->Options.clientrect.bottom = 240+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize240180Click(TObject *Sender)
{
Helper->Options.clientrect.right = 240+4; Helper->Options.clientrect.bottom = 180+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemSize180120Click(TObject *Sender)
{
Helper->Options.clientrect.right = 180+4; Helper->Options.clientrect.bottom = 120+4;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::SubMenuZoomClick(TObject *Sender)
{
if (Helper->Options.zoom==8)
	{MenuItemZoom08->Checked   = true;
	}
else
if (Helper->Options.zoom==6)
	{MenuItemZoom06->Checked   = true;
	}
else
if (Helper->Options.zoom==4)
	{MenuItemZoom04->Checked   = true;
	}
else
if (Helper->Options.zoom==3)
	{MenuItemZoom03->Checked   = true;
	}
else
if (Helper->Options.zoom==2)
	{MenuItemZoom02->Checked   = true;
	}
else
MenuItemZoomAdvanced->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoomAdvancedClick(TObject *Sender)
{
long acc = Helper->Options.zorder;
	   Helper->Options.zorder = (long)HWND_BOTTOM;
Zoom_form->TrackBar1->Position = Helper->Options.zoom;
if (Zoom_form->Execute(this)==mrOk)
	 Helper->Options.zoom = Zoom_form->TrackBar1->Position;
Helper->Options.zorder = acc;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom02Click(TObject *Sender)
{
Helper->Options.zoom = 2;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom03Click(TObject *Sender)
{
Helper->Options.zoom = 3;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom04Click(TObject *Sender)
{
Helper->Options.zoom = 4;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom06Click(TObject *Sender)
{
Helper->Options.zoom = 6;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::MenuItemZoom08Click(TObject *Sender)
{
Helper->Options.zoom = 8;
}
//---------------------------------------------------------------------------
void __fastcall TLupa_form::MenuItemCelownikClick(TObject *Sender)
{
Helper->Options.sight = !Helper->Options.sight;
MenuItemCelownik->Checked = Helper->Options.sight;
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
    	 (void*)Helper->Options.zorder,
    	 (Desktop->Screen->Rect.right-Desktop->Screen->Rect.left)/2 - this->Width/2,(Desktop->Screen->Rect.bottom-Desktop->Screen->Rect.top)/2 - this->Height/2,
    	 0,0,
    	 SWP_NOCOPYBITS|SWP_NOACTIVATE|SWP_NOSIZE);
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::Natopie1Click(TObject *Sender)
{
Natopie1->Checked = !Natopie1->Checked;
if (Natopie1->Checked) Helper->Options.zorder = (long)HWND_TOPMOST;
else Helper->Options.zorder = NULL;
}
//---------------------------------------------------------------------------

/*
void __fastcall TLupa_form::SubMenuTimerClick(TObject *Sender)
{
if (Helper->Options.interval==20)
	U020->Checked = true;
else
if (Helper->Options.interval==25)
	U025->Checked = true;
else
if (Helper->Options.interval==30)
	U030->Checked = true;
else
if (Helper->Options.interval==40)
	U040->Checked = true;
else
if (Helper->Options.interval==50)
	U050->Checked = true;
else
if (Helper->Options.interval==100)
	U100->Checked = true;
else
if (Helper->Options.interval==200)
	U200->Checked = true;
else
if (Helper->Options.interval==250)
	U250->Checked = true;
else
if (Helper->Options.interval==500)
	U500->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U020Click(TObject *Sender)
{
Helper->Options.interval = 20;
Timer1->Interval = Helper->Options.interval;
U020->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U025Click(TObject *Sender)
{
Helper->Options.interval = 25;
Timer1->Interval = Helper->Options.interval;
U025->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U030Click(TObject *Sender)
{
Helper->Options.interval = 30;
Timer1->Interval = Helper->Options.interval;
U030->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U040Click(TObject *Sender)
{
Helper->Options.interval = 40;
Timer1->Interval = Helper->Options.interval;
U040->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U050Click(TObject *Sender)
{
Helper->Options.interval = 50;
Timer1->Interval = Helper->Options.interval;
U050->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U100Click(TObject *Sender)
{
Helper->Options.interval = 100;
Timer1->Interval = Helper->Options.interval;
U100->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U200Click(TObject *Sender)
{
Helper->Options.interval = 200;
Timer1->Interval = Helper->Options.interval;
U200->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U250Click(TObject *Sender)
{
Helper->Options.interval = 250;
Timer1->Interval = Helper->Options.interval;
U250->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TLupa_form::U500Click(TObject *Sender)
{
Helper->Options.interval = 500;
Timer1->Interval = Helper->Options.interval;
U500->Checked = true;
}
//---------------------------------------------------------------------------
*/



void __fastcall TLupa_form::LupaPopupMenuPopup(TObject *Sender)
{
PopupMenuVisible = true;    
}
//---------------------------------------------------------------------------

