//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TResizerForm : public TForm
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
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TComboBox *ComboBox2;
        TSpeedButton *SpeedButton4;
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
        __fastcall TResizerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResizerForm *ResizerForm;
//---------------------------------------------------------------------------
#endif
