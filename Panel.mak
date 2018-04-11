# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.06.00
# ---------------------------------------------------------------------------
PROJECT = Panel.exe
OBJFILES = Panel.obj Dni_frm.obj Desk_frm.obj Lupa_frm.obj Main_frm.obj Tips_frm.obj \
    Zoom_frm.obj Atab_frm.obj Move_frm.obj Size_frm.obj Expose_frm.obj \
    Info_frm.obj Zeus_frm.obj Clock_frm.obj Unit2.obj Unit1.obj Unit3.obj \
    Unit4.obj Unit5.obj Idle_frm.obj Idlecheck_frm.obj
RESFILES = 
MAINSOURCE = Panel.cpp
RESDEPEN = $(RESFILES) Dni_frm.dfm Desk_frm.dfm Lupa_frm.dfm Main_frm.dfm \
    Tips_frm.dfm Zoom_frm.dfm Atab_frm.dfm Move_frm.dfm Size_frm.dfm \
    Expose_frm.dfm Info_frm.dfm Zeus_frm.dfm Clock_frm.dfm Unit2.dfm Unit1.dfm \
    Unit3.dfm Unit4.dfm Unit5.dfm Idle_frm.dfm Idlecheck_frm.dfm
LIBFILES = 
IDLFILES = 
IDLGENFILES = 
LIBRARIES = vclx.lib USRPKG.lib vcl.lib rtl.lib
PACKAGES = vcl.bpi rtl.bpi vclx.bpi qrpt.bpi teeui.bpi teedb.bpi tee.bpi teeqr.bpi \
    ibxpress.bpi
SPARELIBS = rtl.lib vcl.lib USRPKG.lib vclx.lib
DEFFILE = 
OTHERFILES = 
# ---------------------------------------------------------------------------
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = _DEBUG
SYSDEFINES = NO_STRICT
INCLUDEPATH = ..\Rozdz;..\..\..\x86_win32_classes;..\..\Classes;modul_licznika;"C:\Program Files\Borland\CBuilder6\Projects";$(BCB)\include;$(BCB)\include\vcl;..\..\PACKAGES;..\..\Libraries;..\..\FORM_TEMPLATES
LIBPATH = ..\Rozdz;..\..\..\x86_win32_classes;modul_licznika;"C:\Program Files\Borland\CBuilder6\Projects";$(BCB)\Projects\Lib;$(BCB)\lib\obj;$(BCB)\lib;..\..\Packages;..\..\Libraries;..\..\Forms
WARNINGS= -w-par
PATHCPP = .;
PATHASM = .;
PATHPAS = .;
PATHRC = .;
PATHOBJ = .;$(LIBPATH)
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -H=$(BCB)\lib\vcl60.csm -Hc -Q -w -Jgx -Vmd -P -Vx -Ve -xf -xp -Vmp -C \
    -fp -ff -X- -ps -a8 -6 -b -d -k -y -v -vi- -c -tW -tWM
IDLCFLAGS = 
PFLAGS = -$Y+ -$W -$U -$T -$R -$Q -$B -$A8 -v -JPHNE -M
RFLAGS = 
AFLAGS = /mu /w0 /zi
LFLAGS = -D"" -V5.1 -Rr -Gz -c- -aa -Tpe -GD -s -Gn -M -v
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif

!if $d(PATHOBJ)
.PATH.OBJ  = $(PATHOBJ)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(OTHERFILES) $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) -i$(INCLUDEPATH:;= -i) $(AUSERDEFINES) -d$(SYSDEFINES:;= -d) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<



# ---------------------------------------------------------------------------




