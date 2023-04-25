//---------------------------------------------------------------------------
#include <vcl.h>
#include <Winspool.h>
#include <Windows.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Size_frm.h"
#include "Main_frm.h"
#include "Lupa_frm.h"
//---------------------------------------------------------------------------
#include "Desk_frm.h"
//---------------------------------------------------------------------------
//#pragma link "..\\..\\Classes\\TSoft_DeskSwitcher.obj"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TDesk_form *Desk_form;
//---------------------------------------------------------------------------
__fastcall TDesk_form::TDesk_form(TComponent* Owner)
		  : TForm(Owner)
{
Helper = new TForm_Helper(this);
Helper->Default.clientrect.right = 4*96+12; Helper->Default.clientrect.bottom = 1*72+12;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::tform_Align(void)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
::GetWindowRect(Handle,&Helper->Options.rect);

if (Helper->Options.rect.left	 < Desktop->Screen->Rect.left)
   {Helper->Options.rect.left   = Desktop->Screen->Rect.left;
   }
if (Helper->Options.rect.right  >= Desktop->Screen->Rect.right)
   {Helper->Options.rect.left   = Desktop->Screen->Rect.right  - (Helper->Options.rect.right-Helper->Options.rect.left);
   }
if (Helper->Options.rect.top	 < Desktop->Screen->Rect.top)
   {Helper->Options.rect.top    = Desktop->Screen->Rect.top;
   }
if (Helper->Options.rect.bottom >= Desktop->Screen->Rect.bottom)
   {Helper->Options.rect.top    = Desktop->Screen->Rect.bottom - (Helper->Options.rect.bottom-Helper->Options.rect.top);
   }
SetWindowPos(this->Handle,NULL,
		Helper->Options.rect.left,Helper->Options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::tform_Resize()
{
Helper->Options.rect.right  = Helper->Options.rect.left + Helper->Options.clientrect.right;
Helper->Options.rect.bottom = Helper->Options.rect.top  + Helper->Options.clientrect.bottom;
AdjustWindowRectEx(&Helper->Options.rect,
		GetWindowLong(this->Handle,GWL_STYLE),false,
		GetWindowLong(this->Handle,GWL_EXSTYLE));
SetWindowPos(this->Handle,NULL,
		0,0,(Helper->Options.rect.right-Helper->Options.rect.left),(Helper->Options.rect.bottom-Helper->Options.rect.top),
		SWP_NOCOPYBITS|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Calculate_Rect(); tform_Align(); tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::tform_Move()
{
SetWindowPos(this->Handle,NULL,
		Helper->Options.rect.left,Helper->Options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::tform_Redraw()
{
static bool lock = 0;
if (lock==1)
        return;
lock = 1;

static HBRUSH btnbrush = GetSysColorBrush(COLOR_BTNFACE);
static HBRUSH redbrush = CreateSolidBrush(RGB(255,115,115)), greenbrush = CreateSolidBrush(RGB(115,255,115)), bluebrush = CreateSolidBrush(RGB(115,115,255));
HBRUSH brush;

tform_Calculate_Rect();

SetStretchBltMode(Desktop->Screen->Context->Hdc,COLORONCOLOR);
Desktop->Screen->Context->Resize(Helper->Options.clientrect.right,Helper->Options.clientrect.bottom);
::FillRect(Desktop->Screen->Context->Hdc,&Helper->Options.clientrect,btnbrush);
SetStretchBltMode(Desktop->Screen->Context->Hdc,HALFTONE);

for (int i = 1, x; i <= 4; i++)
    {
    if (Desktop->Virtual[i]->Printed==true) x = i;
	else x = 0;
    StretchBlt(Desktop->Screen->Context->Hdc,
    		 Helper->Options.deskrect[i].left, Helper->Options.deskrect[i].top, Helper->Options.deskrect[i].right-Helper->Options.deskrect[i].left, Helper->Options.deskrect[i].bottom-Helper->Options.deskrect[i].top,
    		 Desktop->Virtual[x]->Context->Hdc,
    		 0,0,Desktop->Virtual[x]->Rect.right,Desktop->Virtual[x]->Rect.bottom,
    		 SRCCOPY);
    }
for (int color, d = Desktop->Previous_Desktop_Index();;)
    {
     if (d==Desktop->Previous_Desktop_Index()) brush = bluebrush;
     else brush = redbrush;

     RECT temprect = Helper->Options.deskrect[d];
     temprect.left--;
     temprect.top--;
     temprect.right++;
     temprect.bottom++;
     ::FrameRect(Desktop->Screen->Context->Hdc,&temprect,brush);
     temprect.left--;
     temprect.top--;
     temprect.right++;
     temprect.bottom++;
     ::FrameRect(Desktop->Screen->Context->Hdc,&temprect,brush);

     if (d!=Desktop->Active_Desktop_Index()) d =Desktop->Active_Desktop_Index();
     else break;
    }
tform_Select();

BitBlt(this->Canvas->Handle,
     	 0,0,Helper->Options.clientrect.right,Helper->Options.clientrect.bottom,
     	 Desktop->Screen->Context->Hdc,
     	 0,0,
     	 SRCCOPY);
lock = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::tform_Select()
{
POINT cursorpoint;
::GetCursorPos(&cursorpoint);
::ScreenToClient(this->Handle,&cursorpoint);
static int  olddesk = 0, curdesk = 0, d;
static HWND oldhwnd = NULL, curhwnd = NULL;
static HBRUSH greenbrush = CreateSolidBrush(RGB(115,255,115));
HBRUSH brush;

for (d = 1; d <= 4; d++)
    {if (cursorpoint.x >= Helper->Options.deskrect[d].left && cursorpoint.x < Helper->Options.deskrect[d].right &&
	 cursorpoint.y >= Helper->Options.deskrect[d].top  && cursorpoint.y < Helper->Options.deskrect[d].bottom)
	{curdesk = d;
	 break;
	}
    }
if (curdesk!=0)
   {curhwnd = Desktop->Virtual[Desktop->Active_Desktop_Index()]->Handle_at_XY(
                (Desktop->Screen->Rect.right  * (cursorpoint.x-Helper->Options.deskrect[curdesk].left)) / (Helper->Options.deskrect[curdesk].right  - Helper->Options.deskrect[curdesk].left),
                (Desktop->Screen->Rect.bottom * (cursorpoint.y-Helper->Options.deskrect[curdesk].top))  / (Helper->Options.deskrect[curdesk].bottom - Helper->Options.deskrect[curdesk].top)
                );
   }
if (curdesk!=0 && curhwnd!=NULL)
   {
	 RECT temprect;
	 GetWindowRect(curhwnd,&temprect);

	 temprect.left = this->Helper->Options.deskrect[curdesk].left + (temprect.left   * (this->Helper->Options.deskrect[curdesk].right  - this->Helper->Options.deskrect[curdesk].left)) / Desktop->Screen->Rect.right;
	 if (temprect.left < this->Helper->Options.deskrect[curdesk].left)
	     temprect.left = this->Helper->Options.deskrect[curdesk].left;
	     temprect.right = this->Helper->Options.deskrect[curdesk].left + (temprect.right  * (this->Helper->Options.deskrect[curdesk].right  - this->Helper->Options.deskrect[curdesk].left)) / Desktop->Screen->Rect.right;
	 if (temprect.right > this->Helper->Options.deskrect[curdesk].right)
	     temprect.right = this->Helper->Options.deskrect[curdesk].right;
             temprect.top = this->Helper->Options.deskrect[curdesk].top  + (temprect.top    * (this->Helper->Options.deskrect[curdesk].bottom - this->Helper->Options.deskrect[curdesk].top))  / Desktop->Screen->Rect.bottom;
	 if (temprect.top < this->Helper->Options.deskrect[curdesk].top)
	     temprect.top = this->Helper->Options.deskrect[curdesk].top;
             temprect.bottom = this->Helper->Options.deskrect[curdesk].top  + (temprect.bottom * (this->Helper->Options.deskrect[curdesk].bottom - this->Helper->Options.deskrect[curdesk].top))  / Desktop->Screen->Rect.bottom;
	 if (temprect.bottom > this->Helper->Options.deskrect[curdesk].bottom)
	     temprect.bottom = this->Helper->Options.deskrect[curdesk].bottom;

	 InvertRect(Desktop->Screen->Context->Hdc,&this->Helper->Options.deskrect[curdesk]);
	 InvertRect(Desktop->Screen->Context->Hdc,&temprect);

	  brush = greenbrush;

	 temprect.left--;
	 temprect.top--;
	 temprect.right++;
         temprect.bottom++;
	 ::FrameRect(Desktop->Screen->Context->Hdc,&temprect,brush);
	 temprect.left--;
	 temprect.top--;
	 temprect.right++;
         temprect.bottom++;
	  ::FrameRect(Desktop->Screen->Context->Hdc,&temprect,brush);

	 char text[64];
	 GetWindowText(curhwnd,text,63);
	 if (GetWindowTextLength(curhwnd)>0)
	    {this->Caption = "Okno: " + (String)text;
	    }
	 else
	    {this->Caption = "Okno: NULL";
	    }
	 olddesk = curdesk; oldhwnd = curhwnd;
   }
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::tform_Calculate_Rect()
{
  Helper->Options.deskrect[0].left = 4;
 Helper->Options.deskrect[0].right = Helper->Options.clientrect.right   - 4;
   Helper->Options.deskrect[0].top = 4;
Helper->Options.deskrect[0].bottom = Helper->Options.clientrect.bottom  - 4;

  Helper->Options.deskrect[1].left = 4;
 Helper->Options.deskrect[1].right = Helper->Options.deskrect[1].left + (Helper->Options.clientrect.right  - 16)/4;
   Helper->Options.deskrect[1].top = 4;
Helper->Options.deskrect[1].bottom = Helper->Options.deskrect[1].top + Helper->Options.clientrect.bottom - 4;

  Helper->Options.deskrect[2].left = Helper->Options.deskrect[1].right  + 4;
 Helper->Options.deskrect[2].right = Helper->Options.deskrect[2].left + (Helper->Options.clientrect.right  - 16)/4;
   Helper->Options.deskrect[2].top = Helper->Options.deskrect[1].top;
Helper->Options.deskrect[2].bottom = Helper->Options.deskrect[1].bottom;

  Helper->Options.deskrect[3].left = Helper->Options.deskrect[2].right  + 4;
 Helper->Options.deskrect[3].right = Helper->Options.deskrect[3].left + (Helper->Options.clientrect.right  - 16)/4;
   Helper->Options.deskrect[3].top = Helper->Options.deskrect[1].top;
Helper->Options.deskrect[3].bottom = Helper->Options.deskrect[1].bottom;

  Helper->Options.deskrect[4].left = Helper->Options.deskrect[3].right  + 4;
 Helper->Options.deskrect[4].right = Helper->Options.deskrect[4].left + (Helper->Options.clientrect.right  - 16)/4;
   Helper->Options.deskrect[4].top = Helper->Options.deskrect[1].top;
Helper->Options.deskrect[4].bottom = Helper->Options.deskrect[1].bottom;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::tform_Initialize(void)
{
Helper->Load("Desk");
Timer1->Interval = Helper->Options.interval;
MenuItemTop->Checked = (Helper->Options.zorder==(long)HWND_TOPMOST);
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
tform_Move(); tform_Resize();
SetClassLong(this->Handle,GCL_STYLE,GetClassLong(this->Handle,GCL_STYLE) | CS_SAVEBITS);
if (Helper->Options.zoomed)
	SetWindowLong(this->Handle,GWL_STYLE,GetWindowLong(this->Handle,GWL_STYLE) | WS_MAXIMIZE);
if (Helper->Options.visible)
	this->Show();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormCreate(TObject *Sender)
{
hInst = (HINSTANCE)HInstance;
::SetStretchBltMode(this->Canvas->Handle, STRETCH_DELETESCANS);
Ruszacz = new ts::WindowsMover();
updateing = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormShow(TObject *Sender)
{
Timer1->Enabled = true;
if (Main_form!=NULL ? Main_form->SpeedButtonDeskGrid!=NULL : false)
    Main_form->SpeedButtonDeskGrid->Down = true;
MenuItemZwin->Caption = "&Hide";
Helper->Options.visible = true;
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormHide(TObject *Sender)
{
Timer1->Enabled = false;
if (Main_form!=NULL ? Main_form->SpeedButtonDeskGrid!=NULL : false)
    Main_form->SpeedButtonDeskGrid->Down = false;
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
MenuItemZwin->Caption = "&Show";
Helper->Options.visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormDestroy(TObject *Sender)
{
delete Ruszacz;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormResize(TObject *Sender)
{
Helper->Options.zoomed = IsZoomed(Handle);
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormPaint(TObject *Sender)
{
if (updateing) return;
updateing = true;
SetWindowPos(Handle,
	     (void*)Helper->Options.zorder,
	     0,0,0,0,
	     SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSENDCHANGING|SWP_NOREDRAW);
RECT temprect;
::GetClientRect(this->Handle,&temprect);
if (temprect.right!=Desktop->Screen->Context->Bitmap->Info->bmiHeader.biWidth || temprect.bottom!=Desktop->Screen->Context->Bitmap->Info->bmiHeader.biHeight)
   {tform_Redraw();
   }
else
   {::GetClipBox(this->Canvas->Handle,&temprect);
    ::BitBlt(this->Canvas->Handle,
		 temprect.left,temprect.top,temprect.right-temprect.left,temprect.bottom-temprect.top,
		 Desktop->Screen->Context->Hdc,
		 temprect.left,temprect.top,
		 SRCCOPY);
   }
updateing = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button==mbRight)
   {updateing = true;
    POINT point;
    GetCursorPos(&point);
    DeskPopupMenu->Popup(point.x,point.y);
    updateing = 0;
    return;
   }
if (Button==mbLeft)
   {for (int i = 4; i > 0; i--)
	{if (X >= Helper->Options.deskrect[i].left && X < Helper->Options.deskrect[i].right && Y >= Helper->Options.deskrect[i].top && Y < Helper->Options.deskrect[i].bottom)
	    {Desktop_Switch(i,true);
	     break;
            }
	}
   }
if (Button==mbMiddle)
   {tform_Redraw();
   }
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormMouseMove(TObject *Sender,
		TShiftState Shift, int X, int Y)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormMouseUp(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
/*if (Button!=mbMiddle)
	 return;
	for (int i = 4; i > 0; i--)
	{if (X >= Helper->Options.deskrect[i].left && X < Helper->Options.deskrect[i].right && Y >= Helper->Options.deskrect[i].top && Y < Helper->Options.deskrect[i].bottom)
		  {if (Desktop->Active_Desktop_Index()==i) Desktop_Switch(Desktop->Previous_Desktop_Index(),true);
			break;
		  }
	 }
*/
}
//---------------------------------------------------------------------------

int __fastcall TDesk_form::Desktop_Switch(int newDesk, bool redraw)
{
Desktop->Activate(newDesk);

switch (newDesk)
{
case 0: Main_form->SpeedButtonDesk5->Down = true;
break;
case 1: Main_form->SpeedButtonDesk1->Down = true;
break;
case 2: Main_form->SpeedButtonDesk2->Down = true;
break;
case 3: Main_form->SpeedButtonDesk3->Down = true;
break;
case 4: Main_form->SpeedButtonDesk4->Down = true;
break;
}
if (redraw) tform_Redraw();
return newDesk;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::FormKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
switch (Key) {
case '1':
	Desktop_Switch(1,true);
break;
case '2':
	Desktop_Switch(2,true);
break;
case '3':
	Desktop_Switch(3,true);
break;
case '4':
	Desktop_Switch(4,true);
break;
case '0':
	Desktop_Switch(0,true);
break;

case VK_ESCAPE: Hide();

break;
}
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::Timer1Timer(TObject *Sender)
{
if (updateing)
    return;
updateing = true;
Desktop->Collect(); Desktop->Capture();tform_Redraw();
updateing = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::Timer2Timer(TObject *Sender)
{
//if (updateing)
//    return;
//updateing = true;
if ((Lupa_form->Left+Lupa_form->Width < Desk_form->Left || Lupa_form->Top+Lupa_form->Height < Desk_form->Top) ||
    (Lupa_form->Left > Desk_form->Left + Desk_form->Width || Lupa_form->Top > Desk_form->Top + Desk_form->Height))
SetWindowPos(Handle,(void*)Helper->Options.zorder,
     		 0,0,0,0,
     		 SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOREDRAW|SWP_NOSENDCHANGING);
//updateing = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::SubMenuPrzeswitClick(TObject *Sender)
{
if (Helper->Options.clickthrough==true)
	 MenuItemTrans->Checked = true;

if (Helper->Options.alpha==0)
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

void __fastcall TDesk_form::MenuItemTransClick(TObject *Sender)
{
Helper->Options.clickthrough = !Helper->Options.clickthrough;
MenuItemTrans->Checked = Helper->Options.clickthrough;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::NOFFClick(TObject *Sender)
{
Helper->Options.alpha = -1;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
NOFF->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N101Click(TObject *Sender)
{
Helper->Options.alpha = 10;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N201Click(TObject *Sender)
{
Helper->Options.alpha = 20;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N301Click(TObject *Sender)
{
Helper->Options.alpha = 30;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N301->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N401Click(TObject *Sender)
{
Helper->Options.alpha = 40;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N401->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N501Click(TObject *Sender)
{
Helper->Options.alpha = 50;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N601Click(TObject *Sender)
{
Helper->Options.alpha = 60;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N601->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N701Click(TObject *Sender)
{
Helper->Options.alpha = 70;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N701->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::N801Click(TObject *Sender)
{
Helper->Options.alpha = 80;
Desktop->Action(SET_TRANSPARENCY,this->Handle,Helper->Options.alpha,Helper->Options.clickthrough);
N801->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::SubMenuSizeClick(TObject *Sender)
{
if (Helper->Options.clientrect.right==4*384+12 && Helper->Options.clientrect.bottom==1*256+12)
   {MenuItemSize384->Checked  = true;
   }
else
if (Helper->Options.clientrect.right==4*256+12 && Helper->Options.clientrect.bottom==1*192+12)
   {MenuItemSize256->Checked  = true;
   }
else
if (Helper->Options.clientrect.right==4*192+12 && Helper->Options.clientrect.bottom==1*144+12)
   {MenuItemSize192->Checked  = true;
   }
else
if (Helper->Options.clientrect.right==4*144+12 && Helper->Options.clientrect.bottom==1*108+12)
   {MenuItemSize144->Checked  = true;
   }
else
if (Helper->Options.clientrect.right==4*96+12 && Helper->Options.clientrect.bottom==1*72+12)
   {MenuItemSize96->Checked   = true;
   }
else
if (Helper->Options.clientrect.right==4*64+12 && Helper->Options.clientrect.bottom==1*48+12)
   {MenuItemSize64->Checked   = true;
   }
else
if (Helper->Options.clientrect.right==4*48+12 && Helper->Options.clientrect.bottom==1*36+12)
   {MenuItemSize48->Checked   = true;
   }
else
if (Helper->Options.clientrect.right==4*32+12 && Helper->Options.clientrect.bottom==1*24+12)
   {MenuItemSize32->Checked   = true;
   }
else
MenuItemSizeAdvanced->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSizeAdvancedClick(TObject *Sender)
{
Size_form->TrackBar1->Position = Helper->Options.clientrect.right;
Size_form->TrackBar2->Position = Helper->Options.clientrect.bottom;
Size_form->CheckBox1->Checked  = Helper->Options.clientrect.bottom*4==Helper->Options.clientrect.right*3;
long  acc = Helper->Options.zorder;
	    Helper->Options.zorder = (long)HWND_BOTTOM;
if (Size_form->Execute(this)==mrOk)
   {Helper->Options.clientrect.right = Size_form->TrackBar1->Position; Helper->Options.rect.bottom = Size_form->TrackBar2->Position;
    tform_Resize();
   }
Helper->Options.zorder = acc;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize32Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*24+16; Helper->Options.clientrect.bottom = 24+8;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize48Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*48+12; Helper->Options.clientrect.bottom = 48+8;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize64Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*64+12; Helper->Options.clientrect.bottom = 64+8;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize96Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*96+12; Helper->Options.clientrect.bottom = 96+8;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize144Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*144+12; Helper->Options.clientrect.bottom = 144+8;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize192Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*192+12; Helper->Options.clientrect.bottom = 192+8;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize256Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*256+12; Helper->Options.clientrect.bottom = 256+8;
tform_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemSize384Click(TObject *Sender)
{
Helper->Options.clientrect.right = 4*384+12; Helper->Options.clientrect.bottom = 384+8;
tform_Resize();
}
//---------------------------------------------------------------------------
void __fastcall TDesk_form::MenuItemBiurko0Click(TObject *Sender)
{
Desktop->Move(Desktop->Active_Desktop_Index(), 0);
Desktop->Capture();
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemBiurko1Click(TObject *Sender)
{
Desktop->Move(Desktop->Active_Desktop_Index(), 1);
Desktop->Capture();
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemBiurko2Click(TObject *Sender)
{
Desktop->Move(Desktop->Active_Desktop_Index(), 2);
Desktop->Capture();
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemBiurko3Click(TObject *Sender)
{
Desktop->Move(Desktop->Active_Desktop_Index(), 3);
Desktop->Capture();
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemBiurko4Click(TObject *Sender)
{
Desktop->Move(Desktop->Active_Desktop_Index(), 4);
Desktop->Capture();
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemZbierzClick(TObject *Sender)
{
for (int d = 1; d < 5; d++)
	{if (d!=Desktop->Active_Desktop_Index())
			Desktop->Move(d,Desktop->Active_Desktop_Index());
	}
Desktop->Capture();
tform_Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemPrzeniesClick(TObject *Sender)
{
MenuItemBiurko1->Enabled = Desktop->Active_Desktop_Index()!=1;
MenuItemBiurko2->Enabled = Desktop->Active_Desktop_Index()!=2;
MenuItemBiurko3->Enabled = Desktop->Active_Desktop_Index()!=3;
MenuItemBiurko4->Enabled = Desktop->Active_Desktop_Index()!=4;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::SubMenuOknaClick(TObject *Sender)
{
MenuItemBiurko0->Visible = Desktop->Active_Desktop_Index()!=0;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemZwinClick(TObject *Sender)
{
this->Visible=!this->Visible;
//SetForegroundWindow(Desk_form->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::MenuItemTopClick(TObject *Sender)
{
    Helper->Options.zorder^=(long)HWND_TOPMOST;
if (Helper->Options.zorder==(long)HWND_TOPMOST) MenuItemTop->Checked = true;
else
   {MenuItemTop->Checked = false;
   }
SetWindowPos(Handle,(void*)Helper->Options.zorder,0,0,0,0,SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOMOVE);
}
//---------------------------------------------------------------------------

/*
void __fastcall TDesk_form::SubMenuTimer1Click(TObject *Sender)
{
if (Helper->Options.interval==10000)
	U010->Checked = true;
else
if (Helper->Options.interval==20000)
	U020->Checked = true;
else
if (Helper->Options.interval==30000)
	U030->Checked = true;
else
if (Helper->Options.interval==60000)
	U060->Checked = true;
else
if (Helper->Options.interval==120000)
	U120->Checked = true;
else
if (Helper->Options.interval==3000000)
	U180->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::U010Click(TObject *Sender)
{
Helper->Options.interval = 10000;
Timer1->Interval = Helper->Options.interval;
U010->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::U020Click(TObject *Sender)
{
Helper->Options.interval = 20000;
Timer1->Interval = Helper->Options.interval;
U020->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::U030Click(TObject *Sender)
{
Helper->Options.interval = 30000;
Timer1->Interval = Helper->Options.interval;
U030->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::U060Click(TObject *Sender)
{
Helper->Options.interval = 60000;
Timer1->Interval = Helper->Options.interval;
U060->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::U120Click(TObject *Sender)
{
Helper->Options.interval = 120000;
Timer1->Interval = Helper->Options.interval;
U120->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDesk_form::U180Click(TObject *Sender)
{
Helper->Options.interval = 180000;
Timer1->Interval = Helper->Options.interval;
U180->Checked = true;
}
//---------------------------------------------------------------------------
*/



void __fastcall TDesk_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

