#ifndef __Core_HDR__
#define __Core_HDR__
#include "windows.h"
#include "wingdi.h"
#include "winuser.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsMover.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsCollector.h"
#include ".\\..\\..\\..\\x86_win32_classes\\tsoft_WindowsTile.h"
//---------------------------------------------------------------------------
extern ts::WindowsCOLLECTOR *Desktop;
extern ts::WindowsTILES *Tiles;
extern struct __KeyPressed
{ BOOL Ctrl, Alt, Tab;
  BOOL Locked;
  UINT Code;
} KeyPressed;
//---------------------------------------------------------------------------
#endif
