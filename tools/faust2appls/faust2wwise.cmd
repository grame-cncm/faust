@REM #####################################################################
@REM #                                                                   #
@REM #                        faust2wwise generator                      #
@REM #                          (c) Grame, 2025                          #
@REM #                                                                   #
@REM #####################################################################    

@echo off
set SCRIPT_DIR=%~dp0
python "%SCRIPT_DIR%\faust2wwise.py" %*