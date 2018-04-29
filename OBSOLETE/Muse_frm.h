//---------------------------------------------------------------------------

#ifndef Muse_frmH
#define Muse_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Core.h"
#include "framepan.h"
#include <jpeg.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMuse_form : public TForm
{
__published:	// IDE-managed Components
       TButton *Button1;
        TImage *Image1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
         __fastcall TMuse_form(TComponent* Owner);
struct
	{ Graphics::TBitmap *Bitmap;
	  HDC  Hdc;
	  HWND Hwnd;
	  RECT Rect;
	} screen;

HINSTANCE hInst; LONG updateing;
HWND HandleFromPoint;
};
//---------------------------------------------------------------------------
extern PACKAGE TMuse_form *Muse_form;
//---------------------------------------------------------------------------
#endif
 