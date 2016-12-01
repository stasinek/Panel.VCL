//---------------------------------------------------------------------------

#ifndef Clock_frmH
#define Clock_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TClock_form : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPanel *Panel1;
	TPanel *Panel2;
private:	// User declarations
public:		// User declarations
	__fastcall TClock_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClock_form *Clock_form;
//---------------------------------------------------------------------------
#endif
