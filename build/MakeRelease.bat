echo off

IF [%1]==[]     GOTO USAGE
IF NOT EXIST %1 GOTO USAGE

SET VERSION=2.52.0
SET BUILD=%1
SET FAUSTGENVERSION=1.62
SET FAUSTLIVE=../../faustlive

echo "Building Faust version %VERSION%"
echo "Building Faustgen version %FAUSTGENVERSION%"
echo "Using build folder %BUILD%"
echo "Make sure that faust submodules are up-to-date"
set CONT="no"
set /p CONT=Type Y to continue... 
if /i NOT %CONT%==Y exit

echo "###################### Building Faust package ######################"
cd %BUILD%
cmake -C ..\backends\most.cmake -C ../targets/all-win64.cmake -DUSE_LLVM_CONFIG=on .. -G "Visual Studio 15 2017 Win64"
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
cmake -DFAUST="../../../build/%BUILD%/faust/bin/faust" -DUSE_LLVM_CONFIG=on -DMAXSDK="max-sdk-7.3.3/source/c74support" .. -G "Visual Studio 15 2017 Win64"
cmake --build . --config Release --  /maxcpucount:4
cmake --build . --config Release --target install
cd ../package
"C:\Program Files\7-Zip\7z.exe" a  -r faustgen-%FAUSTGENVERSION%-win64.zip -w faustgen-%FAUSTGENVERSION%-win64 -mem=AES256
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
GOTO END

:USAGE
echo "Usage: MakeRelease <builddir>
echo "       <builddir>   is the windows build folder"

:END
