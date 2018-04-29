//---------------------------------------------------------------------------

#ifndef Move_frmH
#define Move_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMove_form : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *CheckBox1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button5;
	TPanel *Panel1;
	TButton *Button4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
private:	// User declarations                         
public:		// User declarations
		__fastcall TMove_form(TComponent* Owner);
HWND HwndToMove;
};
//---------------------------------------------------------------------------
extern PACKAGE TMove_form *Move_form;
//---------------------------------------------------------------------------
#endif

