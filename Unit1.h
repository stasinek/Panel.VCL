//---------------------------------------------------------------------------
#ifndef __Unit1_H__
#define __Unit1_H__
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
class TResizer_form : public TForm
{
__published:	// IDE-managed Components
        TComboBox *ComboBox1;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TPanel *Panel1;
        TButton *Button2;
        TButton *Button3;
        TPanel *Panel2;
        TSpeedButton *SpeedButton1;
        TImage *Image1;
        TLabel *Label2;
        TComboBox *ComboBox2;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TResizer_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResizer_form *Resizer_form;
//---------------------------------------------------------------------------
#endif
