//----------------------------------------------------------------------------
#ifndef __Zoom_frm_H__
#define __Zoom_frm_H__
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <ComCtrls.hpp>
#pragma hdrstop
//----------------------------------------------------------------------------
class TZoom_form : public TForm
{
__published:        
			TButton *OKBtn;
			TButton *CancelBtn;
			TGroupBox *GroupBox1;
			TTrackBar *TrackBar1;
			void __fastcall FormHide(TObject *Sender);
			void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:
public:
virtual __fastcall TZoom_form(TComponent* AOwner);

long __fastcall Execute(TObject *Sender);
TObject *Sender;
};
//----------------------------------------------------------------------------
extern PACKAGE TZoom_form *Zoom_form;
//----------------------------------------------------------------------------
#endif    
