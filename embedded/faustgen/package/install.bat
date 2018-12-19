
@echo off

SET CYCLING="C:\Program Files\Cycling '74\Max 8"

IF EXIST %CYCLING% (\resources\externals\msp
  echo Max found in %CYCLING%
  @echo on
  xcopy /y libsndfile-1.dll  %CYCLING%
  xcopy /s /y external\msp\* %CYCLING%\resources\externals\msp\
  xcopy /s /y docs\refpage\* %CYCLING%\resources\docs\refpages\msp-ref\
  xcopy /s /y help\* %CYCLING%\resources\help\msp\
  xcopy /s /y init\* %CYCLING%\resources\init\

) ELSE (
  echo Max not found. Proceed manually or edit this script.
)