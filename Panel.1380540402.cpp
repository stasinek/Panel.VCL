
#include <vcl.h>
#include "Tips_frm.h"
#include "Atab_frm.h"
#include "Size_frm.h"
#include "Zoom_frm.h"
#include "Lupa_frm.h"
#include "Desk_frm.h"
#include "Main_frm.h"
#include "Move_frm.h"
#include "..\..\Forms\Info_frm.h"
#pragma link "..\\..\\Forms\\Info_Frm.obj"
#pragma hdrstop

//---------------------------------------------------------------------------
#include "Core.h"
//---------------------------------------------------------------------------
//USEFORM("Main_frm.cpp", MainForm);
USEFORM("Desk_frm.cpp", Desk_form);
USEFORM("Lupa_frm.cpp", Lupa_form);
USEFORM("Main_frm.cpp", Main_form);
USEFORM("Tips_frm.cpp", Tips_form);
USEFORM("Zoom_frm.cpp", Zoom_form);
USEFORM("Atab_frm.cpp", Atab_form);
USEFORM("Move_frm.cpp", Move_form);
USEFORM("Size_frm.cpp", Size_form);
USEFORM("Zeus_frm.cpp", Zeus_form);
USEFORM("Expose_frm.cpp", Expose_form);
//---------------------------------------------------------------------------
#pragma resource "manifest.res"
//---------------------------------------------------------------------------
LRESULT WindowSwitcherProc(INT aCode, INT aEdge) {
//------------------------------------
register __int8 ac = (Pressed.fCtrl==true) && (Pressed.fAlt==true);
register HANDLE h;

if (!ac) return 0;

if (aCode==VK_TAB && aEdge==WM_KEYDOWN) {

         if (IsWindowVisible(Atab_form->Handle)==false)
            {ShowWindow(Atab_form->Handle,SW_SHOW);
             Atab_form->tform_Start();
            }
         else
            {Atab_form->tform_Switch();
            }
         Pressed.fLocked = 1;
         return 1;
}
if (Pressed.fLocked==1)    {

         ShowWindow(Atab_form->Handle,SW_HIDE);
         if (Atab_form->curicon!=Atab_form->oldicon)
            {h = Atab_form->apps.Windows[Atab_form->oldicon];
             ShowWindow(h,SW_SHOW);
             BringWindowToTop(h);
            }
         Pressed.fLocked = 0;
         return 1;
}

return 0;
}
//---------------------------------------------------------------------------

LRESULT ShortcutProc(INT aCode, INT aEdge) {

static HWND lastwindow = NULL;
static HWND forewindow;
static LONG classstyle, wexstyle;

switch (aCode) {
//------------------------------------
case VK_END: // kill application on top
//------------------------------------
if (Desktop->Action(KILL_PROCESS,GetForegroundWindow(),0,0))
	 Tips_form->Execute("Proces: SPIEPRZAJ DZIADU!",true,false);
return true;
//------------------------------------
case VK_F5: // idle app
//------------------------------------
if (Desktop->Action(SET_PRIORITY,GetForegroundWindow(),IDLE_PRIORITY_CLASS,0))
	 Tips_form->Execute("Proces: IDLE",true,true);
return true;
//------------------------------------
case VK_F6: // normal app
//------------------------------------
if (Desktop->Action(SET_PRIORITY,GetForegroundWindow(),NORMAL_PRIORITY_CLASS,0))
	 Tips_form->Execute("Proces: NORMAL",true,true);
return true;
//------------------------------------
case VK_F7: // high app
//------------------------------------
if (Desktop->Action(SET_PRIORITY,GetForegroundWindow(),HIGH_PRIORITY_CLASS,0))
	 Tips_form->Execute("Proces: HIGH",true,true);
return true;
//------------------------------------
case VK_F8: // realtime app
//------------------------------------
if (Desktop->Action(SET_PRIORITY,GetForegroundWindow(),REALTIME_PRIORITY_CLASS,0))
	 Tips_form->Execute("Process: REALTIME",true,true);
return true;
//------------------------------------
case '1': // switch to desk 1
//------------------------------------
Desk_form->Desktop_Switch(1,true);
Tips_form->Execute("BIURKO: 1",true,false);
return true;
//------------------------------------
case '2': // switch to desk 2
//------------------------------------
Desk_form->Desktop_Switch(2,true);
Tips_form->Execute("BIURKO: 2",true,false);
return true;
//------------------------------------
case '3': // switch to desk 3
//------------------------------------
Desk_form->Desktop_Switch(3,true);
Tips_form->Execute("BIURKO: 3",true,false);
return true;
//------------------------------------
case '4': // switch to desk 4
//------------------------------------
Desk_form->Desktop_Switch(4,true);
Tips_form->Execute("BIURKO: 4",true,false);
return true;
//------------------------------------
case '5': // switch to desk share
//------------------------------------
Desk_form->Desktop_Switch(0,true);
Tips_form->Execute("BIURKO: *",true,false);
return true;
//------------------------------------
case VK_ADD: // increse zoom factor
//------------------------------------
if (Lupa_form->Visible==false)
    break;
    Lupa_form->SubMenuZoomClick(NULL);
if (Lupa_form->MenuItemZoom06->Checked && Lupa_form->MenuItemZoom08->Visible)
   {Lupa_form->MenuItemZoom08->Checked;
    Lupa_form->MenuItemZoom08Click(NULL);
    Tips_form->Execute("LUPA: zoom 8:1", true,false);
   }
if (Lupa_form->MenuItemZoom04->Checked && Lupa_form->MenuItemZoom06->Visible)
   {Lupa_form->MenuItemZoom06->Checked;
    Lupa_form->MenuItemZoom06Click(NULL);
    Tips_form->Execute("LUPA: zoom 6:1", true,false);
   }
if (Lupa_form->MenuItemZoom03->Checked && Lupa_form->MenuItemZoom04->Visible)
   {Lupa_form->MenuItemZoom04->Checked;
    Lupa_form->MenuItemZoom04Click(NULL);
    Tips_form->Execute("LUPA: zoom 4:1", true,false);
   }
if (Lupa_form->MenuItemZoom02->Checked && Lupa_form->MenuItemZoom03->Visible)
   {Lupa_form->MenuItemZoom03->Checked;
    Lupa_form->MenuItemZoom03Click(NULL);
    Tips_form->Execute("LUPA: zoom 3:1", true,false);
   }
return true;
//------------------------------------
case VK_SUBTRACT: // decrese zoom factor
//------------------------------------
if (Lupa_form->Visible==false)
    break;
    Lupa_form->SubMenuZoomClick(NULL);
if (Lupa_form->MenuItemZoom03->Checked && Lupa_form->MenuItemZoom02->Visible)
   {Lupa_form->MenuItemZoom02->Checked;
    Lupa_form->MenuItemZoom02Click(NULL);
    Tips_form->Execute("LUPA: zoom 2:1", true,false);
   }
if (Lupa_form->MenuItemZoom04->Checked && Lupa_form->MenuItemZoom03->Visible)
   {Lupa_form->MenuItemZoom03->Checked;
    Lupa_form->MenuItemZoom03Click(NULL);
    Tips_form->Execute("LUPA: zoom 3:1", true,false);
   }
if (Lupa_form->MenuItemZoom06->Checked && Lupa_form->MenuItemZoom04->Visible)
   {Lupa_form->MenuItemZoom04->Checked;
    Lupa_form->MenuItemZoom04Click(NULL);
    Tips_form->Execute("LUPA: zoom 4:1", true,false);
   }
if (Lupa_form->MenuItemZoom08->Checked && Lupa_form->MenuItemZoom06->Visible)
   {Lupa_form->MenuItemZoom06->Checked;
    Lupa_form->MenuItemZoom06Click(NULL);
    Tips_form->Execute("LUPA: zoom 6:1", true,false);
   }
return true;
//------------------------------------
case VK_MULTIPLY: // center lupa on screen
//------------------------------------
Lupa_form->Na1Click(NULL);
return true;
//------------------------------------
case 'P': // show main window
//------------------------------------
Main_form->tform_Align();
Main_form->Visible=!Main_form->Visible;
return true;
//------------------------------------
case 'L': // show zoom window
//------------------------------------
Lupa_form->tform_Align();
Main_form->SpeedButtonLupa->Down = !Main_form->SpeedButtonLupa->Down;
Main_form->SpeedButtonLupa->Click();
return true;
//------------------------------------
case 'G': // show desk window
//------------------------------------
Desk_form->tform_Align();
Main_form->SpeedButtonDesk5->Down = !Main_form->SpeedButtonDesk5->Down;
Main_form->SpeedButtonDesk5->Click();
return true;
//------------------------------------
case 'M': // show move window
//------------------------------------
Move_form->HwndToMove = GetForegroundWindow();
if (Move_form->HwndToMove==Main_form->Handle || Move_form->HwndToMove==Lupa_form->Handle || Move_form->HwndToMove==Desk_form->Handle)
   {MessageBeep(MB_ICONEXCLAMATION);
	 return false;
	}
Move_form->Visible =!Move_form->Visible;
return true;
case 'S': // set shadow
//------------------------------------
forewindow = GetForegroundWindow();
wexstyle = GetWindowLong(forewindow,GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_COMPOSITED;
if (!SetWindowLong(forewindow,GWL_EXSTYLE,wexstyle))
    Tips_form->Execute("Okno: COMPOSITED",true,false);
SetLayeredWindowAttributes(forewindow, 0x00000000, 255, LWA_COLORKEY);
                    Sleep(1);
classstyle = GetClassLong(forewindow,GCL_STYLE) | CS_DROPSHADOW;
if (!SetClassLong(forewindow,GCL_STYLE,classstyle))
    Tips_form->Execute("Okno: DROPSHADOW",true,false);
return true;
//------------------------------------
case 'T': // set transparency of application on top
//------------------------------------
forewindow = GetForegroundWindow();
if (Desktop->Action(GET_TRANSPARENCY,forewindow,NULL,NULL)<=0) {
        if (Desktop->Action(SET_TRANSPARENCY,forewindow,20,0))
                Tips_form->Execute("Okno: PRZEZROCZYSTE",true,false);
        }
else {
        if (Desktop->Action(SET_TRANSPARENCY,forewindow,-1,0))
                Tips_form->Execute("Okno: NORMALNE",true,false);
        }
return true;
//------------------------------------
case VK_LWIN: // ctose this app
//------------------------------------
//
Tips_form->Execute("Panel: ADIOS AMIGO!",true,true);
Main_form->tform_Save();
Desk_form->tform_Save();
Lupa_form->tform_Save();

Sleep(500);
Application->Terminate();
return true;
// nic nie znaleziono, koniec
default:
break;
}
return 0; // nic  nie znaleziono zwracam 0 ¿eby pozwoliæ na obs³uge innym programom.
}
//---------------------------------------------------------------------------

HHOOK cbthhook;
LRESULT CBTProc(INT nCode, WPARAM wParam, LPARAM lParam) {
return CallNextHookEx(cbthhook,nCode,wParam,lParam);
}
//---------------------------------------------------------------------------
//NISKOPOZIOMOWE PRZECHWYTYWANIE KLAWISZY, CTRL+ALT + TAB(WindowSwitcherProc) lub pozosta³e (ShortcutProc)
//

HHOOK llkbdhhook;
LRESULT LowLevelKeyboardProc(INT nCode, WPARAM wParam, LPARAM lParam) {
if (nCode!=HC_ACTION)
   {return CallNextHookEx(llkbdhhook,nCode,wParam,lParam);
   }
register BOOL fProcHandled;
register KBDLLHOOKSTRUCT *pkbdllhook = (KBDLLHOOKSTRUCT*)lParam;
//------------------------------------

// obs³uga naciœcienia klawisza, Ctrl, Alt, Tab i przekazanie dalej jeœli oba aktywne Ctrl+Alt
if (wParam==WM_KEYDOWN) {
switch (pkbdllhook->vkCode) {
case VK_LCONTROL:
Pressed.fCtrl =true;
goto KBRETURN;
break;
case VK_LMENU:
Pressed.fAlt  =true;
goto KBRETURN;
break;
case VK_TAB:
Pressed.fTab = true;

if (Pressed.fAlt==true && Pressed.fCtrl==true) goto CTALTTAB;
else goto KBRETURN;

default:

if (Pressed.fAlt==true && Pressed.fCtrl==true) goto SHORTCUT;
else goto KBRETURN;
break;
}}
else {
 // obs³uga zwolnienia klawisza Ctrl, Alt lub Tab i przekazanie dalej
if (wParam==WM_KEYUP)
switch (pkbdllhook->vkCode) {
case VK_LCONTROL:
Pressed.fCtrl=false;
if (Pressed.fLocked==true) goto CTALTTAB;
else goto KBRETURN;
case VK_LMENU:
Pressed.fAlt =false;
if (Pressed.fLocked==true) goto CTALTTAB;
else goto KBRETURN;
}}
// domyœlnie uznaj ¿e klawisz nie zosta³ ods³u¿ony przeka¿ akcje kolejnemu programowi.
//------------------------------------
KBRETURN:
return CallNextHookEx(llkbdhhook,nCode,wParam,lParam);
//------------------------------------
CTALTTAB:
fProcHandled = WindowSwitcherProc(pkbdllhook->vkCode,wParam);
if (fProcHandled) return true;
else CallNextHookEx(llkbdhhook,nCode,wParam,lParam);
//------------------------------------
SHORTCUT:
fProcHandled = ShortcutProc(pkbdllhook->vkCode,wParam);
if (fProcHandled)
{ Pressed.fCtrl== false; Pressed.fAlt = false;
return true;}
else CallNextHookEx(llkbdhhook,nCode,wParam,lParam);
}
//---------------------------------------------------------------------------

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
HANDLE hMutex = ::CreateMutex(NULL,TRUE,"TSoft_Panel_mutex");
if  (GetLastError()==ERROR_ALREADY_EXISTS)
    {return MessageBox(0,"Próbujesz uruchomiæ kilkakrotnie, to nie ma sensu",
                       "__ssTSoft_->Panel.exe",
      		       MB_OK|MB_ICONERROR|MB_SYSTEMMODAL);
	 }
//------------------------------------
Pressed.fCtrl = Pressed.fAlt = Pressed.fLocked = false;
llkbdhhook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)LowLevelKeyboardProc, (HINSTANCE)HInstance, 0);
//  cbthhook = SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTProc, (HINSTANCE)HInstance, 0);
//------------------------------------
Desktop = new ssTSoft_::WindowsCOLLECTOR();
Tiles = new ssTSoft_::WindowsTILES();
// 2 linijki ukrywaj¹ application z task bara
DWORD dwExStyle = GetWindowLong(Application->Handle,GWL_EXSTYLE);
SetWindowLong(Application->Handle, GWL_EXSTYLE, dwExStyle|=WS_EX_TOOLWINDOW);
SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
//------------------------------------
try
      {
      	Application->Title = "__ssTSoft_->Panel.exe";
        Application->HintPause = 300;
      	Application->HintHidePause = 30000;
                 Application->CreateForm(__classid(TTips_form), &Tips_form);
                 Application->CreateForm(__classid(TZoom_form), &Zoom_form);
                 Application->CreateForm(__classid(TSize_form), &Size_form);
                 Application->CreateForm(__classid(TLupa_form), &Lupa_form);
                 Application->CreateForm(__classid(TDesk_form), &Desk_form);
                 Application->CreateForm(__classid(TMain_form), &Main_form);
                 Application->CreateForm(__classid(TAtab_form), &Atab_form);
                 Application->CreateForm(__classid(TMove_form), &Move_form);
                 Application->CreateForm(__classid(TSize_form), &Size_form);
                 Application->CreateForm(__classid(TZeus_form), &Zeus_form);
                 Application->CreateForm(__classid(TInfo_form), &Info_form);
                 Application->CreateForm(__classid(TExpose_form), &Expose_form);
                 Application->ShowMainForm = false;
      	Main_form->tform_Initialize();
      	Lupa_form->tform_Initialize();
      	Desk_form->tform_Initialize();
//      	Zeus_form->tform_Initialize();

      	Application->Run();
      }
catch (Exception &exception)
      {
     	Application->ShowException(&exception);
      }
//------------------------------------
delete Desktop;
UnhookWindowsHookEx(llkbdhhook);
CloseHandle(hMutex);
//UnhookWindowsHookEx(cbthhook);
//------------------------------------
return 0;
}
//---------------------------------------------------------------------------
