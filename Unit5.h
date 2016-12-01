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
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TCheckBox *CheckBox1;
	TLabel *Label1;
	TLabel *Label2;
	TComboBoxEx *ComboBoxEx1;
	TStringGrid *StringGrid1;
	TCheckListBox *CheckListBox1;
	TButton *Button1;
	TButton *Button2;
	TCheckBox *CheckBox2;
	TLabel *Label3;
private:	// User declarations
public:		// User declarations
	__fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
