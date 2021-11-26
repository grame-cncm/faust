@ECHO OFF
SETLOCAL EnableDelayedExpansion

SET OUTLIB=lib\libfaustwithllvm.lib
FOR /F "delims=" %%i IN ('llvm-config --libdir') DO SET LLVMDIR=%%i
FOR /F "delims=" %%i IN ('llvm-config --libnames  --link-static') DO SET libnames=%%i

set in=%libnames: =" "!LLVMDIR!\%
set inputlibs=lib/libfaust.lib "!LLVMDIR!\!in!"

@echo "Generating the library %OUTLIB%"
lib.exe /OUT:%OUTLIB% /NOLOGO !inputlibs!
