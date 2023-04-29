//---------------------------------------------------------------------------
#ifndef Dni_frmH
#define Dni_frmH
//---------------------------------------------------------------------------
#include <checklst.hpp>
#include <Registry.hpp>
#include <Menus.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "../../../x86_win32_classes/tsoft_WindowsMover.h"
#include "BARGRAPH.h"
#include "ADVBAR.h"
#include "framepan.h"
//---------------------------------------------------------------------------
typedef struct __wpis
{ int session;
  SYSTEMTIME start, stop;
  int closed;
} wpis, *lpwpis;

class TDni_form : public TForm
{
__published:	// IDE-managed Components
    TTimer *Timer1;
    TPanel *Panel1;
    TButton *Button1;
    TPanel *Panel2;
    TListBox *ListBox1;
    TBarGraph *BarGraph1;
    TAdvancedBar *AdvancedBar1;
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall MenuItem11Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
	void __fastcall MenuItem12Click(TObject *Sender);
    void __fastcall ListBox1MouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall Button1Click(TObject *Sender);
    
private:	// User declarations
//---------------------------------------------------------------------------
int updateing;
TRegistry *Klucz;
ts::WindowsMover *Ruszacz;
HINSTANCE hInst;
//---------------------------------------------------------------------------
public:		// User declarations
//---------------------------------------------------------------------------
SYSTEMTIME PassedTime, PassedTimeDzien;
SYSTEMTIME LocalTime, LocalTimeOld, LocalTimeDzien;
//---------------------------------------------------------------------------
AnsiString __fastcall LocalTimeToString      (SYSTEMTIME time);
SYSTEMTIME __fastcall StringToLocalTime      (AnsiString text);
char *__fastcall BajtToChar(__int64 liczba, char* bufor);
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void  __fastcall Add                         (int index);
void  __fastcall Delete                      (int index);
void  __fastcall Clear                       (int index);
//---------------------------------------------------------------------------
void  __fastcall Post                        (void);
void  __fastcall Read                        (void);
//---------------------------------------------------------------------------
    __fastcall TDni_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDni_form *Dni_form;
//---------------------------------------------------------------------------
#endif
