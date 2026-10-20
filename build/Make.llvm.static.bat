@ECHO OFF
SETLOCAL EnableDelayedExpansion

REM Build lib\libfaustwithllvm.lib from lib\libfaust.lib and the LLVM libraries.
REM The LLVM libraries come from the llvm-config CMake used to compile libfaust
REM (first argument, else the LLVM_CONFIG variable), or else from every LLVM*.lib
REM of the directory given as second argument. The import library of the
REM LLVM-C DLL is left out.

SET OUTLIB=lib\libfaustwithllvm.lib
SET RSP=lib\libfaustwithllvm.rsp
SET LLVMCONFIG=%~1
IF "!LLVMCONFIG!"=="" SET LLVMCONFIG=!LLVM_CONFIG!
IF NOT "!LLVMCONFIG!"=="" SET LLVMCONFIG=!LLVMCONFIG:"=!
SET LLVMDIR=%~2
SET libnames=

IF NOT "!LLVMCONFIG!"=="" (
    FOR /F "delims=" %%i IN ('call "!LLVMCONFIG!" --libdir') DO SET LLVMDIR=%%i
    FOR /F "delims=" %%i IN ('call "!LLVMCONFIG!" --libnames --link-static') DO SET libnames=%%i
    IF "!libnames!"=="" (
        ECHO "!LLVMCONFIG!" --libnames --link-static returned no library 1>&2
        EXIT /B 1
    )
)

REM A response file keeps the command below the length limit of cmd.exe.
> "%RSP%" ECHO "lib\libfaust.lib"
SET count=0
IF NOT "!libnames!"=="" (
    FOR %%n IN (!libnames!) DO (
        >> "%RSP%" ECHO "!LLVMDIR!\%%n"
        SET /A count+=1
    )
) ELSE IF NOT "!LLVMDIR!"=="" (
    FOR %%f IN ("!LLVMDIR!\LLVM*.lib") DO (
        IF /I NOT "%%~nxf"=="LLVM-C.lib" (
            >> "%RSP%" ECHO "%%~ff"
            SET /A count+=1
        )
    )
)
IF !count! EQU 0 (
    ECHO No LLVM library found: give llvm-config or the LLVM library directory 1>&2
    EXIT /B 1
)

@echo "Generating the library %OUTLIB% with !count! LLVM libraries from !LLVMDIR!"
lib.exe /OUT:%OUTLIB% /NOLOGO @"%RSP%"
IF ERRORLEVEL 1 EXIT /B 1
DEL "%RSP%"
