#ifndef __Core_HDR__
#define __Core_HDR__
#include "windows.h"
#include "wingdi.h"
#include "winuser.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsMover.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsCollector.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsTile.h"
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


extern ts::WindowsCOLLECTOR *Desktop;
extern ts::WindowsTILES *Tiles;
extern struct __KeyPressed
{ BOOL Ctrl, Alt, Tab;
  BOOL Locked;
  UINT Code;
} KeyPressed;
//---------------------------------------------------------------------------
#endif
