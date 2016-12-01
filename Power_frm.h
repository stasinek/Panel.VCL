//---------------------------------------------------------------------------

#ifndef Power_frmH
#define Power_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TKillForm : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TEdit *Edit1;
        TEdit *Edit2;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TBitBtn *BitBtn1;
        TEdit *Edit3;
        TEdit *Edit4;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TMainMenu *MainMenu1;
        TMenuItem *Window1;
        TMenuItem *Show1;
        TMenuItem *Hide1;
        TMenuItem *N1;
        TMenuItem *Cascade1;
        TMenuItem *Tile1;
        TMenuItem *Tile2;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *Kill1;
        TImage *Image1;
        TStaticText *StaticText5;
        TStaticText *StaticText6;
        TEdit *Edit5;
        TEdit *Edit6;
        TImage *Image2;
        TButton *Button1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Tile1Click(TObject *Sender);
        void __fastcall Cascade1Click(TObject *Sender);
        void __fastcall ArrangeAll1Click(TObject *Sender);
        void __fastcall Tile2Click(TObject *Sender);
        void __fastcall Kill1Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
HWND HandleFromPoint;
        __fastcall TKillForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKillForm *KillForm;
//---------------------------------------------------------------------------
#endif
