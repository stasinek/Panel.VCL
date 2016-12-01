//---------------------------------------------------------------------------

#ifndef Runer_frmH
#define Runer_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TRunerForm : public TForm
{
__published:	// IDE-managed Components
        TPopupMenu *PopupMenu1;
        TMenuItem *MenuItem11;
        TMenuItem *Execution1;
private:	// User declarations
public:		// User declarations
        __fastcall TRunerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRunerForm *RunerForm;
//---------------------------------------------------------------------------
#endif
