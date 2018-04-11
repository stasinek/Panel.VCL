#ifndef Tips_frm_H
#define Tips_frm_H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "framepan.h"
#include "FRAMEPAN.h"
//#include "framepan.h"
//---------------------------------------------------------------------------
class TTips_form : public TForm
{
__published:	// IDE-managed Components
        	TRamka *Ramka1;
			void __fastcall FormPaint(TObject *Sender);
			void __fastcall FormHide(TObject *Sender);
        void __fastcall Ramka1Click(TObject *Sender);
        void __fastcall Ramka1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:	// User declarations
__fastcall TTips_form(TComponent* Owner);

void __fastcall Execute(String caption, bool timeout, bool flash);
TObject *Sender;

};
//---------------------------------------------------------------------------
extern PACKAGE TTips_form *Tips_form;
//---------------------------------------------------------------------------
#endif
