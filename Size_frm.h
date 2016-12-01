//---------------------------------------------------------------------------
#ifndef Size_frmH
#define Size_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "Zoom_frm.h"
//---------------------------------------------------------------------------
class TSize_form : public TForm
{
__published:	// IDE-managed Components
		  TButton *OKBtn;
		  TButton *CancelBtn;
        TGroupBox *GroupBox1;
        TTrackBar *TrackBar1;
		  TGroupBox *GroupBox2;
		  TTrackBar *TrackBar2;
		  TCheckBox *CheckBox1;
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
__fastcall TSize_form(TComponent* Owner);

long __fastcall Execute(TObject *Sender);
TObject *Sender;
};
//---------------------------------------------------------------------------
extern PACKAGE TSize_form *Size_form;
//---------------------------------------------------------------------------
#endif
