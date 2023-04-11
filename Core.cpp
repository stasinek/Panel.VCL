#include "core.h"
//---------------------------------------------------------------------------
ts::WindowsCOLLECTOR *Desktop;
ts::WindowsTILES *Tiles;
struct __KeyPressed KeyPressed;
//---------------------------------------------------------------------------

void __fastcall TForm_Helper::Load(String aform_Name)
{
if (!KluczRejestuSystemuWindows->OpenKey("Software\\TSoft\\Panel\\" + aform_Name,true))
    return;

if (KluczRejestuSystemuWindows->ValueExists("clientrect"))
   {KluczRejestuSystemuWindows->ReadBinaryData("clientrect",&Options.clientrect, sizeof(RECT));
    if (Options.clientrect.right-Options.clientrect.left % Default.clientrect.right || Options.clientrect.bottom-Options.clientrect.top % Default.clientrect.bottom)
        {Options.clientrect.right = Default.clientrect.right;
         Options.clientrect.left = 0;
         Options.clientrect.bottom = Default.clientrect.bottom;
         Options.clientrect.top = 0;
         }
   }
else
   {Options.clientrect.right = Default.clientrect.right;
    Options.clientrect.bottom = Default.clientrect.bottom;
   }
if (KluczRejestuSystemuWindows->ValueExists("rect"))
   {KluczRejestuSystemuWindows->ReadBinaryData("rect",&Options.rect, sizeof(RECT));
   }
else
   {Options.rect.left = 0;
    Options.rect.top = 0;
   }
if (KluczRejestuSystemuWindows->ValueExists("zoomed"))
   {Options.zoomed = KluczRejestuSystemuWindows->ReadBool("zoomed");
   }
else
   {Options.zoomed = false;
   }
if (KluczRejestuSystemuWindows->ValueExists("alpha"))
   {Options.alpha = KluczRejestuSystemuWindows->ReadInteger("alpha");
   }
else
   {Options.alpha = -1;
   }
if (KluczRejestuSystemuWindows->ValueExists("clickthrough"))
   {Options.clickthrough  = KluczRejestuSystemuWindows->ReadInteger("clickthrough");
   }
else
   {Options.clickthrough  = 0;
   }
if (KluczRejestuSystemuWindows->ValueExists("visible"))
   {Options.visible = KluczRejestuSystemuWindows->ReadBool("visible");
   }
else
   {Options.visible = false;
   }
if (KluczRejestuSystemuWindows->ValueExists("interval"))
	{Options.interval = KluczRejestuSystemuWindows->ReadInteger("interval");
	}
else
	{Options.interval = 44;
	}
if (KluczRejestuSystemuWindows->ValueExists("zorder"))
	{Options.zorder = KluczRejestuSystemuWindows->ReadInteger("zorder");
	}
else
	{Options.zorder = (long)HWND_TOPMOST;
	}
if (KluczRejestuSystemuWindows->ValueExists("sight"))
	{Options.sight = KluczRejestuSystemuWindows->ReadBool("sight");
	}
else
	{Options.sight = false;
	}
if (KluczRejestuSystemuWindows->ValueExists("zoom"))
	{Options.zoom = KluczRejestuSystemuWindows->ReadInteger("zoom");
	}
else
	{Options.zoom = 3;
	}
if (KluczRejestuSystemuWindows->ValueExists("central"))
	{Options.central = KluczRejestuSystemuWindows->ReadBool("central");
	}
else
	{Options.central = false;
	}
KluczRejestuSystemuWindows->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Helper::Save(String aform_Name)
{
if (!KluczRejestuSystemuWindows->OpenKey("Software\\TSoft\\Panel\\" + aform_Name,true))
    return;
if (Owner!=NULL && !Options.zoomed)
   {::GetClientRect(Owner->Handle,&Options.clientrect);
    ::GetWindowRect(Owner->Handle,&Options.rect);
    KluczRejestuSystemuWindows->WriteBinaryData("rect",&Options.rect,sizeof(RECT));
    KluczRejestuSystemuWindows->WriteBinaryData("clientrect",&Options.clientrect,sizeof(RECT));
   }
KluczRejestuSystemuWindows->WriteBool("zoomed",Options.zoomed);
KluczRejestuSystemuWindows->WriteInteger("alpha",Options.alpha);
KluczRejestuSystemuWindows->WriteInteger("clickthrough",Options.clickthrough);
KluczRejestuSystemuWindows->WriteBool("visible",Options.visible);
KluczRejestuSystemuWindows->WriteInteger("interval", Options.interval);
KluczRejestuSystemuWindows->WriteInteger("zorder",Options.zorder);
KluczRejestuSystemuWindows->WriteBool("sight",Options.sight);
KluczRejestuSystemuWindows->WriteInteger("zoom",Options.zoom);
KluczRejestuSystemuWindows->WriteBool("central",Options.central);

KluczRejestuSystemuWindows->CloseKey();
}

//---------------------------------------------------------------------------
