//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_frm.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
//Main_form->SpeedButton6->Down = false;
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
if (ListBox1->ItemIndex > -1) ListBox1->Items->Delete(ListBox1->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton4Click(TObject *Sender)
{
if (ListBox2->ItemIndex > -1) ListBox2->Items->Delete(ListBox2->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton6Click(TObject *Sender)
{
if (ListBox1->ItemIndex > -1) ListBox1->Items->Delete(ListBox1->ItemIndex);
}
//---------------------------------------------------------------------------


