# Microsoft Developer Studio Project File - Name="faust" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=faust - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "faust.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "faust.mak" CFG="faust - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "faust - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "faust - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "faust - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "faust - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../compiler/boxes" /I "../compiler/errors" /I "../compiler/extended" /I "../compiler/generator" /I "../compiler/normalize" /I "../compiler/parallelize" /I "../compiler/parser" /I "../compiler/propagate" /I "../compiler/signals" /I "../compiler/tlib" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "faust - Win32 Release"
# Name "faust - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\compiler\extended\absprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\acosprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\asinprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\atan2prim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\atanprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\binop.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\blockSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\boxes\boxcomplexity.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\boxes\boxes.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\boxes\boxtype.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\cableSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\ceilprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\codegeneration.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\parallelize\colorize.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\compile.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\compile_scal.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\compile_vect.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\contextor.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\cosprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\cutSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\decorateSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\description.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\drawschema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\enlargedSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\enrobage.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\errors\errormsg.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\evaluate\eval.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\expprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\parser\faustlexer.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\parser\faustparser.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\floorprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\fmodprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\klass.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\tlib\list.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\log10prim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\logprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\main.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\maxprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\mergeSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\minprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\tlib\node.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\normalize\normalize.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\occurences.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\tlib\occurrences.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\parSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\powprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\boxes\ppbox.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\ppsig.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\prim2.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\normalize\privatise.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\propagate\propagate.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\device\PSDev.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\recSchema.cpp
# End Source File
# Begin Source File

SOURCE="..\compiler\tlib\recursive-tree.cpp"
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\recursivness.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\remainderprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\rintprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\seqSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\sharing.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\tlib\shlysis.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\signals.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\sigorderrules.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\sigprint.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\sigtype.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\sigtyperules.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\sigvisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\normalize\simplify.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\sinprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\parser\sourcereader.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\splitSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\sqrtprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\signals\subsignals.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\device\SVGDev.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\tlib\symbol.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\extended\tanprim.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\Text.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\schema\topSchema.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\tlib\tree.cpp
# End Source File
# Begin Source File

SOURCE=..\compiler\generator\uitree.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\compiler\boxes\boxcomplexity.h
# End Source File
# Begin Source File

SOURCE=..\compiler\parallelize\colorize.h
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\device\device.h
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\device\devLib.h
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\device\PSDev.h
# End Source File
# Begin Source File

SOURCE=..\compiler\draw\device\SVGDev.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
