//---------------------------------------------------------------------------
#ifndef Main_frmH
#define Main_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Registry.hpp>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include ".\\..\\..\\PACKAGES\\BARGRAPH.h"
#include ".\\..\\..\\PACKAGES\\SYSTRAY.h"
#include ".\\..\\..\\PACKAGES\\FRAMEPAN.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Core.h"
#include <ScktComp.hpp>
#include <Graphics.hpp>
#include "framepan.h"
#include "systray.h"
//---------------------------------------------------------------------------
class TMain_form : public TForm
{
__published:	// IDE-managed Components
        TPopupMenu *MainPopupMenu;
        TTimer *MainTimer;
        TSysTray *MainSysTray;
        TMenuItem *Pozycjakursora1;
        TMenuItem *MenuItemZwin;
        TMenuItem *SubMenuPrzeswit;
        TMenuItem *MenuItemTrans;
        TMenuItem *NOFF;
        TMenuItem *N801;
	TMenuItem *N701;
        TMenuItem *N601;
	TMenuItem *N501;
        TMenuItem *N401;
	TMenuItem *N301;
        TMenuItem *N201;
        TMenuItem *N101;
        TMenuItem *N5;
        TMenuItem *N4;
        TMenuItem *N3;
        TMenuItem *N2;
        TMenuItem *N1;
        TMenuItem *MenuItemInfo;
        TMenuItem *MenuItemClose;
        TMenuItem *SubMenuTools;
        TMenuItem *MenuItemLupa;
        TMenuItem *MenuItemBiurka;
        TTimer *Timer1;
        TMenuItem *EXPERIMENTALExpose1;
	TMenuItem *ShowtheClock1;
	TMenuItem *ShowZeus1;
	TMenuItem *ShowResolution1;
	TMenuItem *Alarm1;
    TPanel *Panel2;
    TSpeedButton *SpeedButtonDesk5;
    TSpeedButton *SpeedButtonDeskGrid;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton5;
    TBevel *Bevel3;
    TSpeedButton *SpeedButtonDesk1;
    TSpeedButton *SpeedButtonDesk2;
    TSpeedButton *SpeedButtonDesk3;
    TSpeedButton *SpeedButtonLupa;
    TSpeedButton *SpeedButtonMenu;
    TBevel *Bevel5;
    TBevel *Bevel1;
    TSpeedButton *SpeedButtonDesk4;
    TBevel *Bevel2;
    TPanel *Panel1;
    TImage *Image1;
    TPanel *Panel3;
		  void __fastcall MenuItemZwinClick(TObject *Sender);
		  void __fastcall SubMenuPrzeswitClick(TObject *Sender);
		  void __fastcall MenuItemTransClick(TObject *Sender);
		  void __fastcall NOFFClick(TObject *Sender);
		  void __fastcall N801Click(TObject *Sender);
		  void __fastcall N701Click(TObject *Sender);
		  void __fastcall N601Click(TObject *Sender);
		  void __fastcall N501Click(TObject *Sender);
		  void __fastcall N401Click(TObject *Sender);
		  void __fastcall N301Click(TObject *Sender);
		  void __fastcall N201Click(TObject *Sender);
                  void __fastcall N101Click(TObject *Sender);
		  void __fastcall MenuItemInfoClick(TObject *Sender);
		  void __fastcall MenuItemCloseClick(TObject *Sender);
		  void __fastcall SpeedButtonDesk1Click(TObject *Sender);
		  void __fastcall SpeedButtonDesk2Click(TObject *Sender);
		  void __fastcall SpeedButtonDesk3Click(TObject *Sender);
		  void __fastcall SpeedButtonDesk4Click(TObject *Sender);
		  void __fastcall SpeedButtonDesk5Click(TObject *Sender);
		  void __fastcall SpeedButtonDeskGridClick(TObject *Sender);
		  void __fastcall SpeedButtonLupaClick(TObject *Sender);
		  void __fastcall SpeedButtonLupaMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SpeedButton2XMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SpeedButtonMenuMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
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
        void __fastcall FormResize(TObject *Sender);
        void __fastcall MainTimerTimer(TObject *Sender);
        void __fastcall MenuItemBiurkaClick(TObject *Sender);
        void __fastcall MenuItemLupaClick(TObject *Sender);
        void __fastcall Pozycjakursora1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall EXPERIMENTALExpose1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall ShowtheClock1Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall ShowResolution1Click(TObject *Sender);
    void __fastcall SpeedButton7Click(TObject *Sender);
    void __fastcall SpeedButtonMinimalizeClick(TObject *Sender);
    void __fastcall Alarm1Click(TObject *Sender);
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
LONG alpha,clickthrough,zoomed,visible,zorder;
RECT clientrect;
} options;
//---------------------------------------------------------------------------
__fastcall TMain_form(TComponent* Owner);
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
};
//---------------------------------------------------------------------------
extern PACKAGE TMain_form *Main_form;
//---------------------------------------------------------------------------
#endif
