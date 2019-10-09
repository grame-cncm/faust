
echo off

IF [%2]==[]     GOTO USAGE
IF NOT EXIST %2 GOTO USAGE

SET VERSION=%1
SET BUILD=%2
SET FAUSTGENVERSION=1.39
SET FAUSTLIVE=../../faustlive

echo "###################### Building Faust package ######################"
cd %BUILD%
cmake -C ..\backends\most.cmake -C ../targets/all-win64.cmake ..
cmake --build . --config Release --  /maxcpucount:4
CALL ../MakePkg.bat
cmake -DCMAKE_INSTALL_PREFIX=faust ..
REM Install faust locally - to be used to build faustgen and faustlive
cmake --build . --config Release --target install
cd ..

echo "###################### Building faustgen package ######################"
cd ../embedded/faustgen/build
cmake -DFAUST=../../../build/%BUILD%/faust/bin/faust ..
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
echo "Usage: MakeRelease <version> <builddir>
echo "       <version>    is the release and faust version"
echo "       <builddir>   is the windows build folder"

:END
