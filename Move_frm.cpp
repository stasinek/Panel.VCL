#include <vcl.h>
#include <Winspool.h>
#include <Windows.h>
#include "Size_frm.h"
#include "Main_frm.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Move_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMove_form *Move_form;
//---------------------------------------------------------------------------
__fastcall TMove_form::TMove_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::FormShow(TObject *Sender)
{
RECT clientrect;
::GetClientRect(this->Handle,&clientrect);
 ::SetWindowPos(this->Handle,HWND_TOPMOST,
       		    (Desktop->Screen->Rect.right-clientrect.right)/2,(Desktop->Screen->Rect.bottom-clientrect.bottom)/2,0,0,
       		     SWP_NOSIZE|SWP_NOCOPYBITS|SWP_NOREDRAW|SWP_NOACTIVATE|SWP_NOSENDCHANGING);

if (Desktop->Active_Desktop_Index()==1) Button1->Enabled=false;
else Button1->Enabled=true;
if (Desktop->Active_Desktop_Index()==2) Button2->Enabled=false;
else Button2->Enabled=true;
if (Desktop->Active_Desktop_Index()==3) Button3->Enabled=false;
else Button3->Enabled=true;
if (Desktop->Active_Desktop_Index()==4) Button4->Enabled=false;
else Button4->Enabled=true;
if (Desktop->Active_Desktop_Index()==0) Button5->Enabled=false;
else Button5->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::FormKeyDown(TObject *Sender, WORD &Key,
		TShiftState)
{
switch (Key) {
case '1':
	if (Button1->Enabled==true) {
	Button1Click(Sender);
	return;}
break;
case '2':
	if (Button2->Enabled==true) {
	Button2Click(Sender);
	return;}
break;
case '3':
	if (Button3->Enabled==true) {
	Button3Click(Sender);
	return;}
break;
case '4':
	if (Button4->Enabled==true) {
	Button4Click(Sender);
	return;}
break;
case '5':
	if (Button5->Enabled==true) {
	Button5Click(Sender);
	return;}
break;

case VK_ESCAPE: this->Hide();
return;
}
MessageBeep(MB_ICONEXCLAMATION);
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::Button1Click(TObject*)
{
this->Hide();
Desktop->Move(HwndToMove,Desktop->Active_Desktop_Index(),1);
ShowWindow(HwndToMove,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::Button2Click(TObject*)
{
this->Hide();
Desktop->Move(HwndToMove,Desktop->Active_Desktop_Index(),2);
ShowWindow(HwndToMove,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::Button3Click(TObject*)
{
this->Hide();
Desktop->Move(HwndToMove,Desktop->Active_Desktop_Index(),3);
ShowWindow(HwndToMove,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::Button4Click(TObject*)
{
this->Hide();
Desktop->Move(HwndToMove,Desktop->Active_Desktop_Index(),4);
ShowWindow(HwndToMove,SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::Button5Click(TObject*)
{
this->Hide();
Desktop->Move(HwndToMove,Desktop->Active_Desktop_Index(),0);
}
//---------------------------------------------------------------------------

void __fastcall TMove_form::FormHide(TObject *Sender)
{
ShowWindow(Application->Handle,SW_SHOWNA);
ShowWindow(Application->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------
void __fastcall TMove_form::FormClose(TObject*, TCloseAction&)
{
SetWindowPos(this->Handle,HWND_NOTOPMOST,
	      0,0,0,0,
	      SWP_NOCOPYBITS|SWP_NOSIZE|SWP_NOMOVE);
}

//---------------------------------------------------------------------------


