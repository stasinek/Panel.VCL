//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Atab_frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "framepan"
#pragma resource "*.dfm"
TAtab_form *Atab_form;
//---------------------------------------------------------------------------
__fastcall TAtab_form::TAtab_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void  __fastcall TAtab_form::tform_Resize(void)
{}
//---------------------------------------------------------------------------
void  __fastcall TAtab_form::tform_Redraw(void)
{}
//---------------------------------------------------------------------------

void  __fastcall TAtab_form::tform_Move(void)
{
RECT screenrect,clientrect;
::GetClientRect(GetDesktopWindow(),&screenrect);
::GetClientRect(this->Handle,&clientrect);
 ::SetWindowPos(this->Handle,HWND_TOPMOST,
			    (screenrect.right-clientrect.right)/2,(screenrect.bottom-clientrect.bottom)/2,0,0,
			     SWP_NOSIZE|SWP_NOCOPYBITS|SWP_NOREDRAW|SWP_NOACTIVATE|SWP_NOSENDCHANGING);
}
//---------------------------------------------------------------------------

void __fastcall TAtab_form::tform_Initialize(void)
{
Desktop->Action(SET_TRANSPARENCY,this->Handle,przeswit,noclick);
tform_Move(); tform_Resize();
}
//---------------------------------------------------------------------------
void __fastcall TAtab_form::FormCreate(TObject*)
{
updateing = false;
hInst = (HINSTANCE)HInstance;
screen.Hwnd = GetDesktopWindow();
screen.Hdc  = GetDC(0);
::GetWindowRect(screen.Hwnd,&screen.Rect);
screen.Bitmap = new Graphics::TBitmap();
screen.Bitmap->Height = (screen.Rect.bottom-screen.Rect.top)*2;
screen.Bitmap->Width  =  (screen.Rect.right-screen.Rect.left)*2;
::SetStretchBltMode(this->Canvas->Handle, STRETCH_DELETESCANS);

Image1->Picture->Bitmap = new Graphics::TBitmap;
Image1->Picture->Bitmap->Width = Image1->Width;
Image1->Picture->Bitmap->Height = Image1->Height;
Image1->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image1->Picture->Bitmap->Canvas->FillRect(Image1->ClientRect);

Image2->Picture->Bitmap = new Graphics::TBitmap;
Image2->Picture->Bitmap->Width = Image2->Width;
Image2->Picture->Bitmap->Height = Image2->Height;
Image2->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image2->Picture->Bitmap->Canvas->FillRect(Image2->ClientRect);

for (int i = 0; i < MAXOPENAPPS; i++)
	 {apps.Hicon[i] = NULL;
		apps.Text[i] = NULL;
	 }
curicon = 0; oldicon = 0;
}
//---------------------------------------------------------------------------

void  __fastcall TAtab_form::tform_Start(void)
{
Desktop->Collect();
apps.Count = 0;
for (int desk = Desktop->Active_Desktop_Index();;)
	 {
	  for (int i = 0, cnt = Desktop->Virtual[desk]->Windows_Count(), toadd, length; i < cnt; i++, toadd=true)
			{
			for (int s = 0; s < apps.Count; s++)
				 {if (apps.Windows[s]==Desktop->Virtual[desk]->Window[i]->Hwnd)
					  {toadd = false;
						break;
					  }
				 }
			 if (toadd==false)
				 {continue;
				 }
			 if (Desktop->Virtual[desk]->Window[i]->Visible==false)
				 {continue;
				 }
/*          if (GetParent(Desktop->Virtual[desk]->Window[i]->Hwnd)!=NULL)
				 {continue;
				 }       */
			 length=GetWindowTextLength(Desktop->Virtual[desk]->Window[i]->Hwnd);
/*          if ((length=GetWindowTextLength(Desktop->Virtual[desk]->Window[i]->Hwnd))==0)
				 {continue;
				 }    */
			 if (FindWindow("Shell_TrayWnd",NULL)==Desktop->Virtual[desk]->Window[i]->Hwnd)
				 {continue;
				 }
			 if (FindWindow("Progman",NULL)==Desktop->Virtual[desk]->Window[i]->Hwnd)
				 {continue;
				 }
			 apps.Windows[apps.Count] = Desktop->Virtual[desk]->Window[i]->Hwnd;
			 apps.Text[apps.Count] = (char*)realloc((void*)apps.Text[apps.Count],length+1);
			 GetWindowText(apps.Windows[apps.Count],apps.Text[apps.Count],length+1);
			 apps.Count++;
			}
		if (desk!=0) desk = 0;
		else
			 break;
	 }

for (int i = 0, x = 0; i < apps.Count; i++)
	 {
	  if (apps.Hicon[i]!=NULL)
			DeleteObject(apps.Hicon[i]);
	  apps.Hicon[i] = (HICON)SendMessage(apps.Windows[i],WM_GETICON,ICON_BIG,0);
	  ::DrawIconEx(Image1->Canvas->Handle,x+5,5,apps.Hicon[i],32,32,0,Image1->Canvas->Brush->Handle,DI_NORMAL);
	  x+=42;
	 }
tform_Switch();
}
//---------------------------------------------------------------------------

void  __fastcall TAtab_form::tform_Switch(void)
{
RECT temprect, framerect;

Image1->Canvas->Brush->Color = clBtnFace;
temprect.left = 42*oldicon;
temprect.top = 0;
temprect.right = 42*oldicon+10+32;
temprect.bottom = 10+32;
::FrameRect(Image1->Canvas->Handle,&temprect,Image1->Canvas->Brush->Handle);
temprect.left++;
temprect.top++;
temprect.right--;
temprect.bottom--;
::FrameRect(Image1->Canvas->Handle,&temprect,Image1->Canvas->Brush->Handle);

Image1->Canvas->Brush->Color = clHighlight;
temprect.left = 42*curicon;
temprect.top = 0;
temprect.right = 42*curicon+10+32;
temprect.bottom = 10+32;
::FrameRect(Image1->Canvas->Handle,&temprect,Image1->Canvas->Brush->Handle);
temprect.left++;
temprect.top++;
temprect.right--;
temprect.bottom--;
::FrameRect(Image1->Canvas->Handle,&temprect,Image1->Canvas->Brush->Handle);

Panel1->Caption = apps.Text[curicon];
bool LetPrintWindow = true;
if (Panel1->Caption=="Program Manager") LetPrintWindow=false;
Image1->Canvas->Brush->Color = clBtnFace;
Image1->Repaint();
      //skalowanie okna aby zmieœcilo sie w obrazku
if (LetPrintWindow==true) {
      //  ::PrintWindow(apps.Windows[curicon],screen.Bitmap->Canvas->Handle,0);
      ::GetWindowRect(apps.Windows[curicon],&temprect);
}
else {temprect.left=0; temprect.top=0; temprect.bottom=Image2->Height;temprect.right=Image2->Width;
}

double sw = temprect.right-temprect.left, sh = temprect.bottom-temprect.top;
if (sw==0 || sh ==0) {sw = 1; sh=1;}
double skalax = sw/sh, skalay = sh/sw;
double iw = Image2->Width, ih = Image2->Height;
double skalaimagex = iw/ih, skalaimagey = ih/iw;
double ow, oh;
if (skalax > skalaimagex)
{ow = iw;
 oh = (int)(iw*skalay);}
else
{ow = (int)(ih*skalax);
 oh = ih;}
Image2->Picture->Bitmap->Canvas->Brush->Color = clBtnFace;
Image2->Picture->Bitmap->Canvas->FillRect(Image2->ClientRect);
if (LetPrintWindow==true) {
        ::SetStretchBltMode(Image2->Canvas->Handle, HALFTONE);
        framerect.left = (int)((iw-ow)/2); framerect.top = (int)((ih-oh)/2);
        framerect.right = (int)ow; framerect.bottom = (int)oh;
        ::StretchBlt(Image2->Canvas->Handle,
			  framerect.left,framerect.top,framerect.right,framerect.bottom,
			  screen.Bitmap->Canvas->Handle,
			  0,0,(int)sw,(int)sh,
			  SRCCOPY);
}
Image2->Repaint();

oldicon = curicon; curicon = (curicon+1) % apps.Count;
}
//---------------------------------------------------------------------------

void __fastcall TAtab_form::FormDestroy(TObject*)
{
for (int i = 0; i < MAXOPENAPPS; i++)
    {if (apps.Hicon[i]!=NULL)
         DeleteObject(apps.Hicon[i]);
      if (apps.Text[i]!=NULL)
          free(apps.Text[i]);
    }
}
//---------------------------------------------------------------------------

void __fastcall TAtab_form::FormActivate(TObject *Sender)
{
::GetWindowRect(Desktop->Screen->Hwnd,&Desktop->Screen->Rect);
}
//---------------------------------------------------------------------------

