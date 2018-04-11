//---------------------------------------------------------------------------

#ifndef Zeus_frmH
#define Zeus_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Registry.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
#include "Core.h"
#include "framepan.h"
#include <jpeg.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TZeus_form : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TBitBtn *BitBtn1;
        TMainMenu *MainMenu1;
        TMenuItem *Window1;
        TMenuItem *Hide1;
        TMenuItem *N1;
        TMenuItem *Cascade1;
        TMenuItem *Tile1;
        TMenuItem *Tile2;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *Kill1;
        TImage *Image2;
        TSpeedButton *SpeedButton1;
        TStatusBar *StatusBar1;
        TCheckListBox *CheckListBox1;
        THeaderControl *HeaderControl1;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Tile1Click(TObject *Sender);
        void __fastcall Cascade1Click(TObject *Sender);
        void __fastcall ArrangeAll1Click(TObject *Sender);
        void __fastcall Tile2Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall Window1Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall Kill1Click(TObject *Sender);
        void __fastcall Image2MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image2Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
ts::WindowsMover *Ruszacz;
TRegistry *KluczRejestuSystemuWindows;
//---------------------------------------------------------------------------
public:		// User declarations
HINSTANCE hInst; LONG updateing;
HWND HandleFromPoint;
        __fastcall TZeus_form(TComponent* Owner);
struct {
LONG sizeof_options;
RECT rect;
LONG alpha,clickthrough,zoomed,visible,zorder,interval,sight,zoom,central;
RECT clientrect;
} options;


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
extern PACKAGE TZeus_form *Zeus_form;
//---------------------------------------------------------------------------
#endif
