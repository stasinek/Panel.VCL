#ifndef __Core_HDR__
#define __Core_HDR__
#include "windows.h"
#include "wingdi.h"
#include "winuser.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsMover.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsCollector.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsTile.h"
#include <Registry.hpp>
#include <vcl.h>
//---------------------------------------------------------------------------
// Definitions for Borland C++ 5 (it's older than Windows 2000 SP4, XP)
#ifndef WS_EX_COMPOSITED
#define WS_EX_COMPOSITED 0x02000000L
#endif
#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED  0x00080000L
#endif
#ifndef CS_DROPSHADOW
#define CS_DROPSHADOW  0x00002000L
#endif
//---------------------------------------------------------------------------
extern ts::WindowsCOLLECTOR *Desktop;
extern ts::WindowsTILES *Tiles;
//---------------------------------------------------------------------------
extern struct __KeyPressed
{ BOOL Ctrl, Alt, Tab;
  BOOL Locked;
  UINT Code;
} KeyPressed;
//---------------------------------------------------------------------------
typedef struct {
LONG sizeof_options;
LONG alpha,clickthrough,zoomed,visible,zorder,interval,sight,zoom,central;
RECT rect, clientrect, deskrect[5], deskhdcc;
} TForm_Options, *LPTForm_Options;
//---------------------------------------------------------------------------
class TForm_Helper {
private:
TForm *Owner;
TRegistry *KluczRejestuSystemuWindows;
public:
    __fastcall  TForm_Helper () : Owner(NULL) { this->KluczRejestuSystemuWindows = new TRegistry(KEY_WRITE|KEY_READ); this->KluczRejestuSystemuWindows->RootKey = HKEY_CURRENT_USER; }
    __fastcall  TForm_Helper (TForm *aform_Owner) : Owner(aform_Owner) { this->KluczRejestuSystemuWindows = new TRegistry(KEY_WRITE|KEY_READ); this->KluczRejestuSystemuWindows->RootKey = HKEY_CURRENT_USER; }
    __fastcall ~TForm_Helper () { delete KluczRejestuSystemuWindows; }
TForm_Options Options, Default;
//---------------------------------------------------------------------------
void  __fastcall Save            (String aform_Name);
void  __fastcall Load            (String aform_Name);
//---------------------------------------------------------------------------
};
#endif
