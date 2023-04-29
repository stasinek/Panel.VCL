//---------------------------------------------------------------------------
#ifndef __Expose_frm_H__
#define __Expose_frm_H__
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Core.h"
//---------------------------------------------------------------------------
class TExpose_form : public TForm
{
__published:	// IDE-managed Components
        TScrollBar *ScrollBar1;
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
HINSTANCE hInst; LONG updateing;
//---------------------------------------------------------------------------
ts::WindowsMover *Ruszacz;
TRegistry *KluczRejestuSystemuWindows;
public:		// User declarations
//---------------------------------------------------------------------------
      __fastcall TExpose_form(TComponent* Owner);
//---------------------------------------------------------------------------
struct {
RECT rect;
LONG alpha,clickthrough,zoomed,visible,zorder,interval,sight,zoom,central;
RECT clientrect;
} options;

bool Down; __int8 Index;

void  __fastcall tform_Resize          (void);
void  __fastcall tform_Align           (void);
void  __fastcall tform_Move            (void);
//---------------------------------------------------------------------------
void  __fastcall tform_Initialize      (void);
//---------------------------------------------------------------------------
void  __fastcall tform_Save            (void);
void  __fastcall tform_Load            (void);
//---------------------------------------------------------------------------
void  __fastcall tform_Redraw          (void);
};
//---------------------------------------------------------------------------
extern PACKAGE TExpose_form *Expose_form;
//---------------------------------------------------------------------------
#endif
