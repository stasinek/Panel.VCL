//---------------------------------------------------------------------------
#include <vcl.h>
#include <time.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Clock_frm.h"
#include "Main_frm.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CCALENDR"
#pragma resource "*.dfm"
TClock_form *Clock_form;
//---------------------------------------------------------------------------
__fastcall TClock_form::TClock_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TClock_form::Timer1Timer(TObject *Sender)
{
this->current_time = time(NULL);
struct tm *tm_struct = localtime(&current_time);

int hour = tm_struct->tm_hour;
int minute = tm_struct->tm_min;
int sec = tm_struct->tm_sec;

int day = tm_struct->tm_mday;
int month = tm_struct->tm_mon + 1;
int year = 1900 + tm_struct->tm_year;
int wday = tm_struct->tm_wday;

AnsiString TimeString = AnsiString::FormatFloat("0#",hour) + ":" + AnsiString::FormatFloat("0#",minute) + ":" + AnsiString::FormatFloat("0#",sec);
Clock_form->Panel1->Caption = TimeString;
Alarm_form->Label1->Caption = TimeString;

char days[7][10] = {"Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat." };
AnsiString WdayString(days[wday]);
AnsiString DateString = AnsiString::FormatFloat("0#",day) + "/" + AnsiString::FormatFloat("0#",month) + "/" + AnsiString::FormatFloat("0#",year);
Main_form->Panel1->Caption = WdayString + " " + DateString + " " + TimeString;
}
//---------------------------------------------------------------------------

void __fastcall TClock_form::SpeedButton2Click(TObject *Sender)
{
if (this->Panel2->Visible) this->Panel2->Show();
else this->Panel2->Hide();
SpeedButton2->Down = !SpeedButton2->Down;
}
//---------------------------------------------------------------------------

void __fastcall TClock_form::SpeedButton1Click(TObject *Sender)
{
 if (Clock_form->WindowState == wsMaximized) Clock_form->WindowState = wsNormal;
else Clock_form->WindowState == wsMaximized;

}
//---------------------------------------------------------------------------

