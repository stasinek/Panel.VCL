#include <vcl.h>
#include "Tips_frm.h"
#include "Size_frm.h"
#include "Zoom_frm.h"
#include "Lupa_frm.h"
#include "Desk_frm.h"
#include "Zeus_frm.h"
#include "Expose_frm.h"
#include "Info_frm.h"
#include "Dni_frm.h"
#include "Clock_frm.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Main_frm.h"
//---------------------------------------------------------------------------
#pragma link "systray"
#pragma link "framepan"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

 TMain_form *Main_form;
__fastcall TMain_form::TMain_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::tform_Align(void)
{
TShiftState shiftState;
this->FormMouseDown(this,mbLeft,shiftState,0,0);
this->FormMouseMove(this,shiftState,0,0);
  this->FormMouseUp(this,mbLeft,shiftState,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::tform_Resize()
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

void __fastcall TMain_form::tform_Move()
{
SetWindowPos(this->Handle,
		0,
		options.rect.left,options.rect.top,0,0,
		SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::tform_Initialize(void)
{
tform_Load();
Desk_form->Desktop_Switch(1,true);
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
tform_Move(); tform_Resize();
SetClassLong(this->Handle,GCL_STYLE,GetClassLong(this->Handle,GCL_STYLE) | CS_SAVEBITS);
if (options.zoomed)
    SetWindowLong(this->Handle,GWL_STYLE,GetWindowLong(this->Handle,GWL_STYLE) | WS_MAXIMIZE);
if (options.visible)
    this->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::tform_Load(void)
{
KluczRejestuSystemuWindows->OpenKey("Software\\TSoft_\\Panel\\Main",true);

#define des_height 34
#define des_width 594

if (KluczRejestuSystemuWindows->ValueExists("clientrect"))
   {KluczRejestuSystemuWindows->ReadBinaryData("clientrect",&options.clientrect, sizeof(RECT));
    if (options.clientrect.right-options.clientrect.left != des_width || options.clientrect.bottom-options.clientrect.top != des_height)
        {options.clientrect.right = des_width;
         options.clientrect.bottom = des_height;
         options.clientrect.left = 0;
         options.clientrect.top = 0;}
   }
else
   {options.clientrect.right = des_width;
    options.clientrect.bottom = des_height;
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
KluczRejestuSystemuWindows->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::tform_Save(void)
{
if (!options.zoomed)
   {::GetClientRect(this->Handle,&options.clientrect);
    ::GetWindowRect(this->Handle,&options.rect);
   }
KluczRejestuSystemuWindows->OpenKey("Software\\TSoft_\\Panel\\Main",true);

KluczRejestuSystemuWindows->WriteBinaryData("rect",&options.rect,sizeof(RECT));
KluczRejestuSystemuWindows->WriteBinaryData("clientrect",&options.clientrect,sizeof(RECT));
KluczRejestuSystemuWindows->WriteBool("zoomed",options.zoomed);
KluczRejestuSystemuWindows->WriteInteger("alpha",options.alpha);
KluczRejestuSystemuWindows->WriteInteger("clickthrough",options.clickthrough);
KluczRejestuSystemuWindows->WriteBool("visible",options.visible);

KluczRejestuSystemuWindows->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormCreate(TObject*)
{
updateing = 0;
hInst = (HINSTANCE)HInstance;
::SetStretchBltMode(this->Canvas->Handle, STRETCH_DELETESCANS);
Ruszacz = new ts::WindowsMover();
KluczRejestuSystemuWindows = new TRegistry;
MainSysTray->Icon->Handle = LoadIcon(hInst,"MAINICON");
MainSysTray->AddIcon();
MainTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormShow(TObject*)
{
MenuItemZwin->Caption = "&Hide";
options.visible = true;
tform_Align();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormHide(TObject*)
{
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
MenuItemZwin->Caption = "&Show";
options.visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormDestroy(TObject*)
{
delete Ruszacz;
delete KluczRejestuSystemuWindows;
MainSysTray->RemoveIcon();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormResize(TObject*)
{
options.zoomed = IsZoomed(Handle);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormMouseDown(TObject*,
		TMouseButton Button, TShiftState, int X, int Y)
{
updateing = true;

if (Button==mbRight)
   {POINT point; GetCursorPos(&point);
    MainPopupMenu->Popup(point.x,point.y);
    updateing = false;
    return;
   }
else Ruszacz->MouseDown(this->Handle,X,Y,Button);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormMouseMove(TObject*,
		TShiftState, int X, int Y)
{
static RECT formRect;
static HWND taskHwnd = FindWindowEx(FindWindow("Progman",NULL),NULL,"SHELLDLL_DefView",NULL);
static RECT taskRect;
static HWND deskHwnd = GetDesktopWindow();
static RECT deskRect;

if (::GetWindowRect(deskHwnd ,&deskRect) ? ::GetWindowRect(taskHwnd,&taskRect) : false)
   {
   if (taskRect.bottom < deskRect.bottom) formRect.bottom = taskRect.bottom;
   else formRect.bottom = deskRect.bottom + 2;
   if (taskRect.right < deskRect.right) formRect.right = taskRect.right;
   else formRect.right = deskRect.right + 2;
   if (taskRect.left > deskRect.left) formRect.left = taskRect.left;
   else formRect.left = deskRect.left - 2;
   if (taskRect.top > deskRect.top) formRect.top = taskRect.top;
   else formRect.top = deskRect.top - 2;
   }
else
   {
   formRect.bottom = deskRect.bottom + 2;
   formRect.right = deskRect.right + 2;
   formRect.left = deskRect.left - 2;
   formRect.top = deskRect.top - 2;
   }
Ruszacz->MouseMove(this->Handle,X,Y,true,&formRect,50,(formRect.top+formRect.bottom)/2);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormMouseUp(TObject*,
		TMouseButton Button, TShiftState, int X, int Y)
{
Ruszacz->MouseUp(this->Handle,X,Y,Button);
updateing = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::MainTimerTimer(TObject*)
{
if ((GetAsyncKeyState(4) & 0x8000)==0 && (KeyPressed.Ctrl==true && KeyPressed.Alt==true)==0)
	return;

static POINT MousePoint; GetCursorPos(&MousePoint);
HWND fwh;

if (Desktop->Active_Desktop_Index()==1) {
if (MousePoint.x==Screen->Width-1)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(2,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,1,2);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(1,MousePoint.y);
    Desktop->Capture();
   }
else
if (MousePoint.y==Screen->Height-1)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(3,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,1,3);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(MousePoint.x,1);
    Desktop->Capture();
   }
}
else
if (Desktop->Active_Desktop_Index()==2) {
if (MousePoint.x==0)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(1,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,2,1);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(Screen->Width-2,MousePoint.y);
    Desktop->Capture();
   }
else
if (MousePoint.y==Screen->Height-1)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(4,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,2,4);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(MousePoint.x,1);
    Desktop->Capture();
   }
}
else
if (Desktop->Active_Desktop_Index()==3) {
if (MousePoint.x==Screen->Width-1)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(4,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,3,4);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(1,MousePoint.y);
    Desktop->Capture();
   }
else
if (MousePoint.y==0)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(1,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,3,1);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(MousePoint.x,Screen->Height-2);
    Desktop->Capture();
   }
}
else
if (Desktop->Active_Desktop_Index()==4) {
if (MousePoint.x==0)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(3,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,4,3);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(Screen->Width-2,MousePoint.y);
    Desktop->Capture();
   }
else
if (MousePoint.y==0)
   {fwh = GetForegroundWindow();
    ShowWindow(fwh,SW_HIDE);
    Desktop->Capture();
    Desk_form->Desktop_Switch(2,false);
    if (GetAsyncKeyState(1) & 0x8000)
   	Desktop->Move(fwh,4,2);
    ShowWindow(fwh,SW_SHOW);
    SetCursorPos(MousePoint.x,Screen->Height-2);
    Desktop->Capture();
   }
}
Desk_form->tform_Redraw();
updateing = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonMenuMouseUp(TObject*,
		TMouseButton Button, TShiftState, int X, int Y)
{
if (Button!=mbLeft)
	 return;
POINT point; GetCursorPos(&point);
Main_form->MainPopupMenu->Popup(point.x,point.y);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButton2XMouseUp(TObject*,
		TMouseButton Button, TShiftState, int X, int Y)
{
if (Button!=mbRight)
    return;
POINT point; GetCursorPos(&point);
Desk_form->DeskPopupMenu->Popup(point.x,point.y);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonLupaMouseUp(TObject*,
		TMouseButton Button, TShiftState, int X, int Y)
{
if (Button!=mbRight)
    return;
POINT point; GetCursorPos(&point);
Lupa_form->LupaPopupMenu->Popup(point.x,point.y);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonDesk1Click(TObject*)
{
Desk_form->Desktop_Switch(1,true);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonDesk2Click(TObject*)
{
Desk_form->Desktop_Switch(2,true);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonDesk3Click(TObject*)
{
Desk_form->Desktop_Switch(3,true);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonDesk4Click(TObject*)
{
Desk_form->Desktop_Switch(4,true);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonDesk5Click(TObject*)
{
Desk_form->Desktop_Switch(0,true);

}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonDeskGridClick(TObject*)
{
Desk_form->Visible = SpeedButtonDeskGrid->Down;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButtonLupaClick(TObject*)
{
Lupa_form->Visible = SpeedButtonLupa->Down;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SubMenuPrzeswitClick(TObject*)
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

void __fastcall TMain_form::MenuItemTransClick(TObject*)
{
MenuItemTrans->Checked = options.clickthrough = !MenuItemTrans->Checked;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::NOFFClick(TObject*)
{
options.alpha = -1;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
NOFF->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::N101Click(TObject *Sender)
{
options.alpha = 10;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TMain_form::N201Click(TObject*)
{
options.alpha = 20;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N201->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::N301Click(TObject*)
{
options.alpha = 30;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N301->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::N401Click(TObject*)
{
options.alpha = 40;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N401->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::N501Click(TObject*)
{
options.alpha = 50;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N501->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::N601Click(TObject*)
{
options.alpha = 60;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N601->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::N701Click(TObject*)
{
options.alpha = 70;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N701->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::N801Click(TObject*)
{
options.alpha = 80;
Desktop->Action(SET_TRANSPARENCY,this->Handle,options.alpha,options.clickthrough);
N801->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::MenuItemBiurkaClick(TObject*)
{
Desk_form->Visible = true;
SetForegroundWindow(Desk_form->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::MenuItemLupaClick(TObject*)
{
Lupa_form->Visible = true;
SetForegroundWindow(Lupa_form->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::MenuItemZwinClick(TObject*)
{
this->Visible=!this->Visible;
SetForegroundWindow(Main_form->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::MenuItemInfoClick(TObject*)
{
Info_form->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::MenuItemCloseClick(TObject*)
{
Main_form->tform_Save();
Desk_form->tform_Save();
Lupa_form->tform_Save();

//Desktop->Action(SET_TRANSPARENCY,FindWindow("Shell_TrayWnd",NULL),-1,false);
//Desktop->Action(SET_TRANSPARENCY,FindWindow("BaseBar",NULL),-1,false);
Application->Terminate();
}
//---------------------------------------------------------------------------

/*Zeus_form->Show();
return;

if (SpeedButtonKiller->Down) { Tips_form->Prompt("YOU HAVE GOT THE POWER! :]", false);
     for (int lbutton = 0, x = 0; x < 100; x++)
         {
          Sleep(200);
          if(GetSystemMetrics(SM_SWAPBUTTON)==TRUE) lbutton = GetAsyncKeyState(VK_RBUTTON);
          else lbutton = GetAsyncKeyState(VK_LBUTTON);
          if (x==0) lbutton = 0;
          else
          if (lbutton & 0x01){
                POINT point_ofcursor;
                GetCursorPos(&point_ofcursor);
                HWND hwnd_frompoint;
                hwnd_frompoint = WindowFromPoint(point_ofcursor);
                Desktop->Action(KILL_PROCESS,hwnd_frompoint,0,0);
                        break;
             }
         }
    }
else
   { return;
   }
SpeedButtonKiller->Down = false;
*/

void __fastcall TMain_form::Pozycjakursora1Click(TObject *Sender)
{
if (Tips_form->Visible) { Tips_form->Execute("HIDE",false, false); Timer1->Enabled = false; return; }
else Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::Timer1Timer(TObject *Sender)
{
POINT cursorpoint;
GetCursorPos(&cursorpoint);
Tips_form->Execute("X:" + (AnsiString)cursorpoint.x + " Y:" + (AnsiString)cursorpoint.y,false, false);

}
//---------------------------------------------------------------------------

void __fastcall TMain_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::EXPERIMENTALExpose1Click(TObject *Sender)
{
    Expose_form->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButton2Click(TObject *Sender)
{
Dni_form->Visible = SpeedButton2->Down;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::ShowtheClock1Click(TObject *Sender)
{
Clock_form->Visible = true;
SetForegroundWindow(Clock_form->Handle);

}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButton3Click(TObject *Sender)
{
Form1->Visible = SpeedButton3->Down;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButton5Click(TObject *Sender)
{
MenuItemCloseClick(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TMain_form::SpeedButton6Click(TObject *Sender)
{
Form3->Visible = SpeedButton6->Down;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::SpeedButton1Click(TObject *Sender)
{
Form5->Visible = SpeedButton1->Down;
}
//---------------------------------------------------------------------------

void __fastcall TMain_form::ShowResolution1Click(TObject *Sender)
{
Form1->Visible = true;	
}
//---------------------------------------------------------------------------

