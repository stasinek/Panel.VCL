//---------------------------------------------------------------------------
#ifndef Desk_frmH
#define Desk_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Registry.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include "Core.h"
//---------------------------------------------------------------------------
class TDesk_form : public TForm
{
//---------------------------------------------------------------------------
__published:	// IDE-managed Components
//---------------------------------------------------------------------------
        TPopupMenu *DeskPopupMenu;
		  TMenuItem *SubMenuPrzeswit;
		  TMenuItem *NOFF;
		  TMenuItem *N1;
		  TMenuItem *N201;
		  TMenuItem *N301;
		  TMenuItem *N401;
		  TMenuItem *N501;
		  TMenuItem *N601;
		  TMenuItem *N701;
		  TMenuItem *N801;
		  TMenuItem *N8;
		  TMenuItem *MenuItemTrans;
		  TMenuItem *MenuItemSize256;
		  TMenuItem *MenuItemSize192;
		  TMenuItem *MenuItemSize144;
		  TMenuItem *MenuItemSize96;
		  TMenuItem *MenuItemSize64;
		  TMenuItem *SubMenuSize;
		  TMenuItem *MenuItemSizeAdvanced;
		  TMenuItem *MenuItemSize48;
		  TMenuItem *MenuItemSize32;
		  TMenuItem *SubMenuOkna;
		  TMenuItem *MenuItemPrzenies;
		  TMenuItem *MenuItemBiurko2;
		  TMenuItem *MenuItemBiurko3;
		  TMenuItem *MenuItemBiurko4;
		  TMenuItem *MenuItemZbierz;
		  TMenuItem *MenuItemTop;
		  TMenuItem *MenuItemZwin;
        TMenuItem *N101;
        TMenuItem *N3;
        TMenuItem *MenuItemSize384;
    TTimer *Timer1;
    TMenuItem *MenuItemBiurko1;
    TMenuItem *MenuItemBiurko0;
		  void __fastcall MenuItemZwinClick(TObject *Sender);
		  void __fastcall SubMenuSizeClick(TObject *Sender);
		  void __fastcall MenuItemSize32Click(TObject *Sender);
		  void __fastcall MenuItemSize48Click(TObject *Sender);
		  void __fastcall MenuItemSize64Click(TObject *Sender);
		  void __fastcall MenuItemSize96Click(TObject *Sender);
		  void __fastcall MenuItemSize144Click(TObject *Sender);
		  void __fastcall MenuItemSize192Click(TObject *Sender);
		  void __fastcall MenuItemSize256Click(TObject *Sender);
		  void __fastcall MenuItemSizeAdvancedClick(TObject *Sender);
		  void __fastcall SubMenuPrzeswitClick(TObject *Sender);
		  void __fastcall NOFFClick(TObject *Sender);
		  void __fastcall N201Click(TObject *Sender);
		  void __fastcall N301Click(TObject *Sender);
		  void __fastcall N401Click(TObject *Sender);
		  void __fastcall N501Click(TObject *Sender);
		  void __fastcall N601Click(TObject *Sender);
		  void __fastcall N701Click(TObject *Sender);
		  void __fastcall N801Click(TObject *Sender);
		  void __fastcall MenuItemTransClick(TObject *Sender);
		  void __fastcall Timer1Timer(TObject *Sender);
		  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift);
		  void __fastcall FormPaint(TObject *Sender);
		  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
			 TShiftState Shift, int X, int Y);
		  void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
			 int X, int Y);
		  void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
			 TShiftState Shift, int X, int Y);
		  void __fastcall FormResize(TObject *Sender);
		  void __fastcall FormCreate(TObject *Sender);
		  void __fastcall FormDestroy(TObject *Sender);
		  void __fastcall FormShow(TObject *Sender);
		  void __fastcall FormHide(TObject *Sender);
		  void __fastcall SubMenuOknaClick(TObject *Sender);
		  void __fastcall MenuItemBiurko0Click(TObject *Sender);
		  void __fastcall MenuItemBiurko1Click(TObject *Sender);
		  void __fastcall MenuItemBiurko2Click(TObject *Sender);
		  void __fastcall MenuItemBiurko3Click(TObject *Sender);
		  void __fastcall MenuItemBiurko4Click(TObject *Sender);
		  void __fastcall MenuItemPrzeniesClick(TObject *Sender);
		  void __fastcall MenuItemZbierzClick(TObject *Sender);
		  void __fastcall MenuItemTopClick(TObject *Sender);
		  void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall N101Click(TObject *Sender);
        void __fastcall MenuItemSize384Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
//---------------------------------------------------------------------------
HINSTANCE hInst; LONG updateing;
//---------------------------------------------------------------------------
ts::WindowsMover *Ruszacz;
TRegistry *KluczRejestuSystemuWindows;
//---------------------------------------------------------------------------
public:		// User declarations
//---------------------------------------------------------------------------
struct {
RECT rect;
LONG alpha,clickthrough,zoomed,visible,zorder,interval;
RECT clientrect, deskrect[5], deskhdcc;
} options;
//---------------------------------------------------------------------------
        __fastcall TDesk_form(TComponent* Owner);
//---------------------------------------------------------------------------
int   __fastcall Desktop_Switch        (int newDesk, bool redraw);
//---------------------------------------------------------------------------
void  __fastcall tform_Resize          (void);
void  __fastcall tform_Align           (void);
void  __fastcall tform_Move            (void);
//---------------------------------------------------------------------------
void  __fastcall tform_Initialize      (void);
//---------------------------------------------------------------------------
void  __fastcall tform_Save            (void);
void  __fastcall tform_Load            (void);
//---------------------------------------------------------------------------
void  __fastcall tform_Calculate_Rect  (void);
void  __fastcall tform_Redraw          (void);
void  __fastcall tform_Select          (void);
};
//---------------------------------------------------------------------------
extern PACKAGE TDesk_form *Desk_form;
//---------------------------------------------------------------------------
#endif
