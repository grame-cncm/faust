echo off

SET VERSION=2.59.5
SET FAUSTGENVERSION=1.64

SET MYPATH=%cd%
set "MYPATH=%MYPATH:\=/%"
SET BUILD=%MYPATH%/build
SET FAUSTLIVE=../../faustlive

set LLVM_CONFIG="%MYPATH%/../llvm/bin/llvm-config.exe"
set MAXSDK="%MYPATH%/../max-sdk/source/max-sdk-base/c74support"
set LIBSNDFILE="%MYPATH%/../libsndfile"
set VS_REDIST=%VCToolsRedistDir%vc_redist.x64.exe
set "VS_REDIST=%VS_REDIST:\=/%"

if not exist "%LLVM_CONFIG%" (
    echo "llvm-config.exe was not found at location: %LLVM_CONFIG%"
    EXIT /B 1
)

if not exist "%MAXSDK%" (
    echo "The Max SDK was not found at location: %MAXSDK%"
    EXIT /B 1
)

if not exist "%LIBSNDFILE%" (
    echo "libsndfile was not found at location: %LIBSNDFILE%"
    EXIT /B 1
)

if not exist "%VS_REDIST%" (
    echo "Windows Redistributables were not found at location: %VS_REDIST%"
    EXIT /B 1
)

echo "Building Faust version: %VERSION%"
echo "Building Faustgen version: %FAUSTGENVERSION%"
echo "VS_REDIST is %VS_REDIST%"
echo "Using build folder %BUILD%"
echo "Make sure that faust submodules are up-to-date"

echo "###################### Building Faust package ######################"
mkdir build
cd build
cmake -C ..\backends\most.cmake -C ../targets/all-win64.cmake -DUSE_LLVM_CONFIG=ON -DLLVM_CONFIG="%LLVM_CONFIG%" -Ax64 ..
cmake --build . --config Release --  /maxcpucount:4
CALL ../MakePkg.bat
cmake -DCMAKE_INSTALL_PREFIX=faust -DPACK=off ..
REM Install faust locally - to be used to build faustgen and faustlive
cmake --build . --config Release --target install
cd ..

:FAUSTGEN
echo "###################### Building faustgen package ######################"
cd ../embedded/faustgen
IF NOT exist build ( mkdir build)
cd build
cmake -DFAUST="%BUILD%/faust/bin/faust.exe" -DUSE_LLVM_CONFIG=ON -DLLVM_CONFIG="%LLVM_CONFIG%" -DMAXSDK="%MAXSDK%" -DLIBSNDFILE="%LIBSNDFILE%" -DVS_REDIST="%VS_REDIST%" -Ax64 ..
cmake --build . --config Release --  /maxcpucount:4
cmake --build . --config Release --target install
cd ../package
"C:\Program Files\7-Zip\7z.exe" a -r faustgen-%FAUSTGENVERSION%-win64.zip -w faustgen-%FAUSTGENVERSION%-win64 -mem=AES256
cd ../../../build

echo "####################### Creating release folder #######################"
set DEST=Release-%VERSION%
IF EXIST %DEST% ( 
    echo Warning ! %DEST% exist and may be non empty
    GOTO NEXT
)
mkdir %DEST%

:NEXT
COPY Faust-%VERSION%-win64.exe %DEST%
COPY ..\embedded\faustgen\package\faustgen-%FAUSTGENVERSION%-win64.zip %DEST%

echo DONE VERSION %VERSION%
