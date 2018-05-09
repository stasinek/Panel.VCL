//---------------------------------------------------------------------------

#ifndef Numpad_frmH
#define Numpad_frmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TNumpad : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TButton *Button2;
    TButton *Button1;
    TPanel *Panel2;
    TPanel *Panel3;
    TGroupBox *GroupBox1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TSpeedButton *SpeedButton8;
    TSpeedButton *SpeedButton9;
    TSpeedButton *SpeedButton10;
    TSpeedButton *SpeedButton11;
    TSpeedButton *SpeedButton12;
    TSpeedButton *SpeedButton13;
    TSpeedButton *SpeedButton14;
    TSpeedButton *SpeedButton15;
    TSpeedButton *SpeedButton16;
private:	// User declarations
public:		// User declarations
int ADres, Rtol;
int Rcd;
int Rs1,Rs2,Rs3,Rs4,Rs5,Rs6,Rs7,Rs8,Rs9,Rs0,RsA,RsB,RsC,RsD,RsHash,RsStar;
int Rx1,Rx2,Rx3;
int Ry1,Ry2,Ry3;
int U1,U2,U3,U4,U5,U6,U7,U8,U9,U0,UA,UB,UC,UD,UHash,UStar;

	__fastcall TNumpad(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNumpad *Numpad;
//---------------------------------------------------------------------------
#endif
