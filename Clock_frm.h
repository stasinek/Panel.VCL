//---------------------------------------------------------------------------

#ifndef Clock_frmH
#define Clock_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "CCALENDR.h"
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TClock_form : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPanel *Panel1;
	TPanel *Panel2;
        TCCalendar *CCalendar1;
        TPanel *Panel3;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
	void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TClock_form(TComponent* Owner);
        long current_time;

};
//---------------------------------------------------------------------------
extern PACKAGE TClock_form *Clock_form;
//---------------------------------------------------------------------------
#endif
