//---------------------------------------------------------------------------

#ifndef Lupa_frmH
#define Lupa_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Menus.hpp>
#include <Registry.hpp>
#include "framepan.h"
#include <ExtCtrls.hpp>
#include <Controls.hpp>
#include "exedlg.h"
#include "Core.h"
//---------------------------------------------------------------------------
class TLupa_form : public TForm
{
//---------------------------------------------------------------------------
__published:	// IDE-managed Components
//---------------------------------------------------------------------------
        TPopupMenu *LupaPopupMenu;
        TTimer *Timer1;
        TMenuItem *SubMenuZoom;
        TMenuItem *MenuItemZoomAdvanced;
        TMenuItem *N4;
        TMenuItem *MenuItemZoom02;
        TMenuItem *MenuItemZoom03;
        TMenuItem *MenuItemZoom04;
        TMenuItem *MenuItemZoom06;
        TMenuItem *MenuItemZoom08;
        TMenuItem *SubMenuSize;
        TMenuItem *MenuItemSizeAdvanced;
        TMenuItem *N3;
	TMenuItem *MenuItemSize180120;
	TMenuItem *MenuItemSize512384;
	TMenuItem *MenuItemSize384288;
	TMenuItem *MenuItemSize240180;
	TMenuItem *MenuItemSize320240;
        TMenuItem *N2;
        TMenuItem *SubMenuPrzeswit;
        TMenuItem *MenuItemTrans;
        TMenuItem *NOFF;
        TMenuItem *N1;
		  TMenuItem *N201;
		  TMenuItem *N301;
		  TMenuItem *N401;
		  TMenuItem *N501;
		  TMenuItem *N601;
		  TMenuItem *N701;
		  TMenuItem *N801;
		  TMenuItem *MenuItemCelownik;
		  TMenuItem *MenuItemZwin;
		  TMenuItem *N5;
        TMenuItem *Na1;
        TMenuItem *N101;
        TMenuItem *Natopie1;
        TMenuItem *N6;
		  void __fastcall Timer1Timer(TObject *Sender);
		  void __fastcall MenuItemZwinClick(TObject *Sender);
		  void __fastcall SubMenuZoomClick(TObject *Sender);
		  void __fastcall MenuItemZoomAdvancedClick(TObject *Sender);
		  void __fastcall MenuItemZoom02Click(TObject *Sender);
		  void __fastcall MenuItemZoom03Click(TObject *Sender);
		  void __fastcall MenuItemZoom04Click(TObject *Sender);
		  void __fastcall MenuItemZoom06Click(TObject *Sender);
		  void __fastcall MenuItemZoom08Click(TObject *Sender);
		  void __fastcall SubMenuSizeClick(TObject *Sender);
		  void __fastcall MenuItemSizeAdvancedClick(TObject *Sender);
		  void __fastcall MenuItemSize180120Click(TObject *Sender);
		  void __fastcall MenuItemSize512384Click(TObject *Sender);
		  void __fastcall MenuItemSize384288Click(TObject *Sender);
		  void __fastcall MenuItemSize240180Click(TObject *Sender);
		  void __fastcall MenuItemSize320240Click(TObject *Sender);
		  void __fastcall SubMenuPrzeswitClick(TObject *Sender);
		  void __fastcall MenuItemTransClick(TObject *Sender);
		  void __fastcall NOFFClick(TObject *Sender);
		  void __fastcall N201Click(TObject *Sender);
		  void __fastcall N301Click(TObject *Sender);
		  void __fastcall N401Click(TObject *Sender);
		  void __fastcall N501Click(TObject *Sender);
		  void __fastcall N601Click(TObject *Sender);
		  void __fastcall N701Click(TObject *Sender);
		  void __fastcall N801Click(TObject *Sender);
		  void __fastcall MenuItemCelownikClick(TObject *Sender);
		  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
			 TShiftState Shift, int X, int Y);
		  void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
			 int X, int Y);
		  void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
			 TShiftState Shift, int X, int Y);
		  void __fastcall FormCreate(TObject *Sender);
		  void __fastcall FormDestroy(TObject *Sender);
		  void __fastcall FormShow(TObject *Sender);
		  void __fastcall FormHide(TObject *Sender);
		  void __fastcall FormPaint(TObject *Sender);
		  void __fastcall FormActivate(TObject *Sender);
		  void __fastcall FormResize(TObject *Sender);
        void __fastcall Na1Click(TObject *Sender);
        void __fastcall N101Click(TObject *Sender);
        void __fastcall Natopie1Click(TObject *Sender);
    void __fastcall LupaPopupMenuPopup(TObject *Sender);
private:	// User declarations
//---------------------------------------------------------------------------
HINSTANCE hInst;
bool PopupMenuVisible;
//---------------------------------------------------------------------------
ts::WindowsMover *Ruszacz;
TRegistry *KluczRejestuSystemuWindows;
//---------------------------------------------------------------------------
public:		// User declarations
//---------------------------------------------------------------------------
struct {
LONG sizeof_options;
RECT rect;
LONG alpha,clickthrough,zoomed,visible,zorder,interval,sight,zoom,central;
RECT clientrect;
} options;
//---------------------------------------------------------------------------
      __fastcall TLupa_form(TComponent* Owner);
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
void  __fastcall tform_Redraw          (void);
};
//---------------------------------------------------------------------------
extern PACKAGE TLupa_form *Lupa_form;
//---------------------------------------------------------------------------
#endif
