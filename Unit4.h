//---------------------------------------------------------------------------
#ifndef __Unit4_H__
#define __Unit4_H__
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "FRAMEPAN.h"
#pragma hdrstop
//---------------------------------------------------------------------------
class TUruchom : public TForm
{
__published:	// IDE-managed Components
    TRamka *Ramka1;
    TTabControl *TabControl1;
private:	// User declarations
public:		// User declarations
	__fastcall TUruchom(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUruchom *Uruchom;
//---------------------------------------------------------------------------
#endif
