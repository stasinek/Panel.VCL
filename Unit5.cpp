//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Clock_frm.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CCALENDR"
#pragma resource "*.dfm"
TAlarm_form *Alarm_form;
//---------------------------------------------------------------------------
__fastcall TAlarm_form::TAlarm_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TAlarm_form::Button2Click(TObject *Sender)
{
Close();	
}
//---------------------------------------------------------------------------
void __fastcall TAlarm_form::Button1Click(TObject *Sender)
{
Close();	
}
//---------------------------------------------------------------------------






