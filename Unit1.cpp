//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
//#include "Main_frm.h"
#include "Unit1.h"
#include "./../../FORM_TEMPLATES/About_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResizer_form *Resizer_form;
//---------------------------------------------------------------------------
__fastcall TResizer_form::TResizer_form(TComponent* Owner)
        : TForm(Owner)
{
Application->Title = Resizer_form->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::SpeedButton1Click(TObject *Sender)
{
static bool down = false;

if (down==true)
{
this->ClientHeight = Panel1->Height + Panel2->Height;
}
else
{
this->ClientHeight = Panel1->Height;
}
down = !down;
}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::Button2Click(TObject *Sender)
{
if (ComboBox1->ItemIndex > 0)
ComboBox1->ItemIndex = ComboBox1->ItemIndex-1;
this->FormPaint(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::Button3Click(TObject *Sender)
{
if (ComboBox1->ItemIndex < ComboBox1->Items->Count-1)
ComboBox1->ItemIndex = ComboBox1->ItemIndex+1;
this->FormPaint(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TResizer_form::FormPaint(TObject *Sender)
{
static __int32 w = 1, h = 1;
__int32 l, p, s;
l = ComboBox1->Text.Length();
if (l >=7) {
p = ComboBox1->Text.Pos("x");
if (p >=4) {
 w = ComboBox1->Text.SubString(1,p - 1).ToInt();
 h = ComboBox1->Text.SubString(p + 1,l).ToInt();
}}

if (w*Image1->Height>=h*Image1->Width) { s = (1000 * (Image1->Width - 50))  / w;
}
else {
s = (1000 * (Image1->Height - 30)) / h;
}
w = (w * s) / 1000;
h = (h * s) / 1000;

TRect r; r.left = (Image1->Width - w) / 2; r.top = (Image1->Height - h) / 2; r.right = r.left + w;
r.bottom = h + r.top;
Image1->Canvas->Pen->Style = psSolid;
Image1->Canvas->Pen->Mode  = pmCopy;
Image1->Canvas->Pen->Color = clBlack;
Image1->Canvas->Pen->Width = 1;
Image1->Canvas->Brush->Color = clBtnFace;
Image1->Canvas->FillRect(Rect(0,0,Image1->Width, Image1->Height));
Image1->Canvas->RoundRect(0,0,Image1->Width, Image1->Height,0,0);
Image1->Canvas->Pen->Style = psDot;
Image1->Canvas->Pen->Mode  = pmCopy;
Image1->Canvas->Pen->Color = clRed;
Image1->Canvas->Pen->Width = 2;
Image1->Canvas->Brush->Color = clWindow;
Image1->Canvas->Rectangle(r);

TSize ts = Image1->Canvas->TextExtent(ComboBox1->Text);
Image1->Canvas->TextOutA((Image1->Width - ts.cx)/2, (Image1->Height - ts.cy)/2, ComboBox1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::SpeedButton2Click(TObject *Sender)
{
DEVMODE DevMode; // >>
DevMode.dmSize = sizeof (DEVMODE);
static char dev[MAX_PATH];
strcpy(dev,"\\\\.\\DISPLAY");
static char helper[MAX_PATH];
#if __BORLANDC__ > 0x551
wcstombs(helper, ComboBox2->Text.c_str(),ComboBox2->Text.Length());
#else
memmove(helper,ComboBox2->Text.c_str(),ComboBox2->Text.Length()+1);
#endif
strcat(dev,helper);

if (EnumDisplaySettingsEx(dev,ENUM_CURRENT_SETTINGS,&DevMode,EDS_RAWMODE)==0) ShowMessage("Nie mo�na pobrac ustawien");
//
DevMode.dmPelsWidth        = ComboBox1->Text.SubString(1,ComboBox1->Text.Pos("x") - 1).ToInt();
DevMode.dmPelsHeight       = ComboBox1->Text.SubString(ComboBox1->Text.Pos("x") + 1,ComboBox1->Text.Length()).ToInt();
DevMode.dmDisplayFrequency = ComboBox4->Text.ToInt();
DevMode.dmBitsPerPel       = ComboBox3->Text.ToInt();
DevMode.dmFields           = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;
//
if (ChangeDisplaySettingsEx(dev,&DevMode,NULL,CDS_TEST,NULL)==DISP_CHANGE_SUCCESSFUL) ChangeDisplaySettingsEx(dev,&DevMode,NULL,0,NULL);
                                                             else ShowMessage("Z�E USTAWIENIA, Twoja karta graficzna ich nie akceptuje\n\r");

}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::SpeedButton3Click(TObject *Sender)
{
About_form->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::ComboBox2Change(TObject *Sender)
{
DEVMODE DevMode; // >>
DevMode.dmSize = sizeof (DEVMODE);

/*BOOL EnumDisplayDevices(
  _In_   LPCTSTR lpDevice,
  _In_   DWORD iDevNum,
  _Out_  PDISPLAY_DEVICE lpDisplayDevice,
  _In_   DWORD dwFlags
);*/

static char dev[MAX_PATH];
strcpy(dev,"\\\\.\\DISPLAY");
static char helper[MAX_PATH];
#if __BORLANDC__ <= 0x551
strcpy(helper,ComboBox2->Text.c_str());
#else
wcstombs(helper, ComboBox2->Text.c_str(),ComboBox2->Text.Length());
#endif
strcat(dev,helper);

if (EnumDisplaySettingsEx(dev,ENUM_CURRENT_SETTINGS,&DevMode,EDS_RAWMODE)==0) {
    ShowMessage("Nie mo�na pobrac ustawien");
    }
ComboBox1->Text = AnsiString(DevMode.dmPelsWidth) + "x" + AnsiString(DevMode.dmPelsHeight);
ComboBox4->Text = DevMode.dmDisplayFrequency;
ComboBox3->Text = DevMode.dmBitsPerPel;

for (int i = 0; i < ComboBox1->Items->Count;i++) {
     if (ComboBox1->Text==ComboBox1->Items->Strings[i]) { ComboBox1->ItemIndex=i; break;}
    }
}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::FormShow(TObject *Sender)
{
ComboBox2Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TResizer_form::FormClose(TObject *Sender, TCloseAction &Action)
{
this->SpeedButton3->Down = false;
}
//---------------------------------------------------------------------------

