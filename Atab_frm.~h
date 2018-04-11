//---------------------------------------------------------------------------

#ifndef Atab_frmH
#define Atab_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "framepan.h"
#include <ExtCtrls.hpp>
#include "Core.h"

#define MAXOPENAPPS 128
//---------------------------------------------------------------------------
class TAtab_form : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TImage *Image2;
        TImage *Image1;
        TPanel *Panel1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
//---------------------------------------------------------------------------
HINSTANCE hInst; LONG updateing;
//---------------------------------------------------------------------------
struct
	{ Graphics::TBitmap *Bitmap;
	  HDC  Hdc;
	  HWND Hwnd;
	  RECT Rect;
	} screen;
//---------------------------------------------------------------------------
public:		// User declarations
//---------------------------------------------------------------------------
LONG przeswit, noclick;
//---------------------------------------------------------------------------
        __fastcall TAtab_form(TComponent* Owner);
//---------------------------------------------------------------------------
void  __fastcall tform_Resize          (void);
void  __fastcall tform_Move            (void);
void  __fastcall tform_Redraw          (void);
//---------------------------------------------------------------------------
void  __fastcall tform_Initialize      (void);
void  __fastcall tform_Start           (void);
void  __fastcall tform_Switch          (void);
//---------------------------------------------------------------------------
struct tagAPPS
   { HWND Windows[MAXOPENAPPS]; HICON Hicon[MAXOPENAPPS]; char *Text[MAXOPENAPPS];
     LONG Count;
	} apps;
LONG curicon,oldicon;
};
//---------------------------------------------------------------------------
extern PACKAGE TAtab_form *Atab_form;
//---------------------------------------------------------------------------
#endif
