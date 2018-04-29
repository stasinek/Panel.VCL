//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <CheckLst.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAlarm_form : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    TPanel *Panel2;
    TLabel *Label2;
    TLabel *Label3;
    TCheckBox *CheckBox1;
    TComboBox *ComboBoxEx1;
    TSpeedButton *SpeedButton9;
    TSpeedButton *SpeedButton7;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton1;
    TStringGrid *StringGrid1;
    TCheckBox *CheckBox2;
    TLabel *Label1;
    TCheckListBox *CheckListBox1;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAlarm_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAlarm_form *Alarm_form;
//---------------------------------------------------------------------------
#endif
