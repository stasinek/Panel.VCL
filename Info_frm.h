//----------------------------------------------------------------------------
#ifndef About_frm_H
#define About_frm_H
//----------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "..\Packages\exeinfo.h"
#include "..\Packages\framepan.h"
//----------------------------------------------------------------------------
class TInfo_form : public TForm
{
__published:
		TImage *Image1;
		TExeInformation *ExeInformation1;
		TLabel *Label2;
		TLabel *Label3;
		TLabel *Label4;
        TLabel *Label5;
        TButton *Button1;
        TMemo *Memo1;
        TLabel *Label1;
		void __fastcall FormCreate(TObject *Sender);
		void __fastcall FormHide(TObject *Sender);
		void __fastcall FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
		void __fastcall Label5Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:
    HINSTANCE hInst;
public:
    virtual __fastcall TInfo_form(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TInfo_form *Info_form;
//----------------------------------------------------------------------------
#endif
