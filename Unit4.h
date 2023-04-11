//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "FRAMEPAN.h"
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
