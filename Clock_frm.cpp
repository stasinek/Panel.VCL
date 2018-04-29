//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Clock_frm.h"
#include "Unit5.h"
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
long current_time = time(NULL);
struct tm *tm_struct = localtime(&current_time);
int hour = tm_struct->tm_hour;
int minute = tm_struct->tm_min;
int sec = tm_struct->tm_sec;

Clock_form->Panel1->Caption = (AnsiString)hour + ":" + (AnsiString)minute + ":" + (AnsiString)sec;
Alarm_form->Label1->Caption = (AnsiString)hour + ":" + (AnsiString)minute + ":" + (AnsiString)sec;
}
//---------------------------------------------------------------------------

