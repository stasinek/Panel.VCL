#include <windows.h>
#include <stdio.h>
#include "Dni_frm.h"
#include "Main_frm.h"

/*void x() {
struct _MEMORYSTATUS status;

GlobalMemoryStatus(&status);
static char HintChar[50];
static char AllocedPhysChar[12],AllocedPageChar[12];
sprintf(HintChar,"%d%%, tj. %s RAM, %s PAGE",
                  status.dwMemoryLoad,
                  BajtToChar(status.dwTotalPhys - status.dwAvailPhys, AllocedPhysChar),
                  BajtToChar(status.dwTotalPageFile - status.dwAvailPageFile, AllocedPageChar));
SysTray1->Hint = HintChar;
} */
//---------------------------------------------------------------------------

char *__fastcall TDni_form::BajtToChar(__int64 liczba, char* bufor)
{
if (liczba < 1024)
    return strcat(itoa(liczba,bufor,10), "B");
else
if (liczba < 1048576)
    return strcat(itoa(liczba/1024,bufor,10), "KB");
else
if (liczba < 1073741824)
    return strcat(itoa(liczba/1048576,bufor,10), "MB");
else
if (liczba >= 1073741824)
    return strcat(itoa(liczba/1073741824,bufor,10), "GB");
else
    return "?TB";
}
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Dni_frm.h"
#include "Main_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "bargraph"
#pragma link "framepan"
#pragma link "advbar"
#pragma link "advbar"
#pragma link "BARGRAPH"
#pragma link "ADVBAR"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TDni_form *Dni_form;
//---------------------------------------------------------------------------
__fastcall TDni_form::TDni_form(TComponent* Owner)
    : TForm(Owner)
{
hInst = (HINSTANCE)HInstance;
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::FormCreate(TObject *Sender)
{
Klucz = new TRegistry;
updateing = false;
Read();
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::FormShow(TObject *Sender)
{
static HWND  hwndDesk = GetDesktopWindow();
static RECT  deskRect;
::GetWindowRect(hwndDesk, &deskRect);
static POINT mousePoint;
GetCursorPos(&mousePoint);

/*if (Main_form->Left + this->Width < deskRect.right)
     Left = Main_form->Left;
else Left = Main_form->Left + Main_form->Width - this->Width;
if (Main_form->Top + Main_form->Height + this->Height < deskRect.bottom)
     Top = Main_form->Top + Main_form->Height;
else Top = Main_form->Top - this->Height;
*/
ShowWindow(Application->Handle,SW_SHOWNA);
//if (Main_form!=NULL ? Main_form->SpeedButton2!=NULL : false)
//	 Main_form->SpeedButton2->Down = true;
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::FormHide(TObject *Sender)
{
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::FormDestroy(TObject *Sender)
{
Post();
delete Klucz;
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::Read(void)
{
GetLocalTime(&LocalTime);
memmove(&LocalTimeOld,&LocalTime,sizeof(SYSTEMTIME));
setmem(&PassedTime,sizeof(SYSTEMTIME),0x00);
memmove(&LocalTimeDzien,&LocalTime,sizeof(SYSTEMTIME));
setmem(&PassedTimeDzien,sizeof(SYSTEMTIME),0x00);
//
//BarGraph1->BarCount = 0;
Klucz->OpenKey("Software\\TSoft\\Licznik\\Dni",true);
TStringList *DateNames = new TStringList;
Klucz->GetValueNames(DateNames);
DateNames->Sorted = true;

for (;DateNames->Count > 0;)
    {
     if (DateNames->Strings[DateNames->Count-1] <= LocalTimeToString(LocalTime))
         break;
     Klucz->DeleteValue(DateNames->Strings[DateNames->Count-1]);
      DateNames->Delete(DateNames->Count-1);
    }
 if (DateNames->Count==0)
    {DateNames->Add(LocalTimeToString(LocalTime)+" = __:__");
     ListBox1->Items->Add(DateNames->Strings[0]);
     //BarGraph1->AddBar();
     PassedTime.wDay = 1;
     return;
    }
SYSTEMTIME timeBgn = StringToLocalTime(DateNames->Strings[0]),
	   timeEnd = LocalTime,
           timeTmp;
if (Klucz->ValueExists(LocalTimeToString(timeEnd)))
   {PassedTimeDzien.wMinute = Klucz->ReadInteger(LocalTimeToString(timeEnd));
   }
LocalTimeDzien = timeEnd;

int  minutes,dni,index = 0;
for (timeTmp.wYear  = timeBgn.wYear;  timeTmp.wYear  <= timeEnd.wYear;  timeTmp.wYear++)
for (timeTmp.wMonth = timeBgn.wMonth; timeTmp.wMonth <= timeEnd.wMonth; timeTmp.wMonth++)
    {
     switch (timeBgn.wMonth)
       {
        case 1 : dni=31; break;
        case 2 : if (timeTmp.wYear%4==0) dni=29; else dni=28; break;
        case 3 : dni=31; break;
        case 4 : dni=30; break;
        case 5 : dni=31; break;
        case 6 : dni=30; break;
        case 7 : dni=31; break;
        case 8 : dni=31; break;
        case 9 : dni=30; break;
        case 10: dni=31; break;
        case 11: dni=30; break;
        case 12: dni=31; break;
        default:
                 dni=0;
       }
     for (timeTmp.wDay = timeBgn.wDay*(timeTmp.wMonth==timeBgn.wMonth) + (timeTmp.wMonth!=timeBgn.wMonth); timeTmp.wDay <= timeEnd.wDay*(timeTmp.wMonth==timeEnd.wMonth) + dni*(timeTmp.wMonth!=timeEnd.wMonth); timeTmp.wDay++)
         {
         if (index < DateNames->Count ? LocalTimeToString(timeTmp)==DateNames->Strings[index] : false)
            {minutes = Klucz->ReadInteger(DateNames->Strings[index]);
             //BarGraph1->AddData(clRed,minutes);
             //BarGraph1->AddBar();
             PassedTime.wMinute +=minutes;
             char tempChar[16];
             sprintf(tempChar," = %02d:%02d",minutes/60,minutes%60);
             ListBox1->Items->Add(DateNames->Strings[index]
                                  + (String)tempChar);
             index++;
            }
         else
            {//BarGraph1->AddData(clRed,0);
             //BarGraph1->AddBar();
             ListBox1->Items->Add(LocalTimeToString(timeTmp)
                                  + " = __:__");
            }
          PassedTime.wDay++;
         }
   }
delete DateNames;
Klucz->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::Post(void)
{
Klucz->OpenKey("Software\\TSoft\\Licznik\\Dni",true);
Klucz->WriteInteger(LocalTimeToString(LocalTimeDzien).c_str(),PassedTimeDzien.wMinute);
Klucz->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::Timer1Timer(TObject *Sender)
{
GetLocalTime(&LocalTime);
static char tempChar[64];

if (LocalTimeDzien.wDay!=LocalTime.wDay || LocalTimeDzien.wMonth!=LocalTime.wMonth || LocalTimeDzien.wYear!=LocalTime.wYear)
   {
    PassedTimeDzien.wMinute+=Timer1->Interval/60000;
    sprintf(tempChar," = %02d:%02d",PassedTimeDzien.wMinute/60,PassedTimeDzien.wMinute%60);
    ListBox1->Items->Strings[ListBox1->Items->Count-1] = LocalTimeToString(LocalTimeDzien)
                                                         + (String)tempChar;
    //BarGraph1->Data[BarGraph1->BarCount-1][clRed] = PassedTimeDzien.wMinute;
    Post();
    PassedTimeDzien.wMinute = 0;
    LocalTimeDzien = LocalTimeOld = LocalTime;
    //BarGraph1->AddBar();
    ListBox1->Items->Add(LocalTimeToString(LocalTime)
                         + " = __:__");
   }
if (LocalTime.wMinute >= LocalTimeOld.wMinute+1 || LocalTime.wHour!=LocalTimeOld.wHour)
   {
    int diff = (LocalTime.wMinute+60*LocalTime.wHour)-(LocalTimeOld.wMinute+60*LocalTimeOld.wHour);
    PassedTimeDzien.wMinute += diff;
    PassedTime.wMinute += diff;
    //BarGraph1->Data[BarGraph1->BarCount-1][clRed] = PassedTimeDzien.wMinute;
   }
if (LocalTime.wMinute >= LocalTimeOld.wMinute+5 || LocalTime.wHour!=LocalTimeOld.wHour)
   {
    sprintf(tempChar," = %02d:%02d",PassedTimeDzien.wMinute/60,PassedTimeDzien.wMinute%60);
    ListBox1->Items->Strings[ListBox1->Items->Count-1] = LocalTimeToString(LocalTime)
                                                         + (String)tempChar;
    //BarGraph1->Data[BarGraph1->BarCount-1][clRed] = PassedTimeDzien.wMinute;
    Post();
    LocalTimeOld = LocalTime;
   }
sprintf(tempChar,"DZIŒ=%02d:%02d, CA£OŒÆ=%02d godz %02d min",
        PassedTimeDzien.wMinute/60,
        PassedTimeDzien.wMinute%60,
        PassedTime.wMinute/60,
        PassedTime.wMinute%60);
//Main_form->SpeedButton2->Hint = tempChar;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TDni_form::LocalTimeToString(SYSTEMTIME time)
{
static char date[12];
static AnsiString text;
sprintf(date,"%04d-%02d-%02d", time.wYear, time.wMonth, time.wDay);
text = date;
return text;
}
//---------------------------------------------------------------------------

SYSTEMTIME __fastcall TDni_form::StringToLocalTime(AnsiString text)
{
static SYSTEMTIME time;
time.wYear  = text.SubString(1,4).ToIntDef(0);
time.wMonth = text.SubString(6,2).ToIntDef(0);
time.wDay   = text.SubString(9,2).ToIntDef(0);
return time;
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::MenuItem12Click(TObject *Sender)
{
/*Klucz->OpenKey("Software\\TSoft_\\Licznik\\Dni",false);
int margin,i;
for (margin = true, i = ListBox1->Items->Count-1; i >= 0; i--)
    {if (ListBox1->Selected[i] ? true : (BarGraph1->Data[i][clRed]==0 && margin==true))
        {if (i!=ListBox1->Items->Count-1)
            {ListBox1->Items->Strings[i] = ListBox1->Items->Strings[i].SubString(1,10)+" = __:__";
             BarGraph1->Data[i][clRed]=0;
            }
         else
            {ListBox1->Items->Delete(i);
             BarGraph1->DelBar(i);
             continue;
            }
        }
    else margin = false;
   }
for (margin = true, i = 0; i <= ListBox1->Items->Count-1; i++)
    {if (BarGraph1->Data[i][clRed]==0)
        {Klucz->DeleteValue(ListBox1->Items->Strings[i].SubString(1,10));
         if (margin==true)
            {ListBox1->Items->Delete(i);
             BarGraph1->DelBar(i);
             i--;
             continue;
            }
        }
    else margin = false;
   }
Klucz->CloseKey();
*/
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::MenuItem11Click(TObject *Sender)
{
if (MessageBox(NULL,"Masz ca³kowit¹ pewnoœæ?","PotwierdŸ zerowanie [T/N]",IDOK)!=IDOK)
    return;
Klucz->DeleteKey("Software\\TSoft_\\Licznik");
Post();
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::ListBox1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
AdvancedBar1->Max = ListBox1->Items->Count-1;
for (int p = 0; p <= AdvancedBar1->Max; p++)
    {if (ListBox1->Selected[p])
        {AdvancedBar1->Position = p;
         Application->ProcessMessages();
         return;
        }
    }
AdvancedBar1->Position = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDni_form::Button1Click(TObject *Sender)
{
Close();    
}
//---------------------------------------------------------------------------

