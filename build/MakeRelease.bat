@echo off

SET VERSION=2.76.0
SET FAUSTGENVERSION=1.72

SET MYPATH=%cd%
SET "MYPATH=%MYPATH:\=/%"
SET BUILD=%MYPATH%/build
SET FAUSTLIVE=../../faustlive
SET LLVM_CONFIG_A="%MYPATH%/../llvm/bin/llvm-config.exe"
SET LLVM_CONFIG_B="%MYPATH%/../../llvm/bin/llvm-config.exe"
SET MAXSDK_A="%MYPATH%/../max-sdk-base/c74support"
SET MAXSDK_B="%MYPATH%/../../max-sdk-base/c74support"
SET LIBSNDFILE_A="%MYPATH%/../libsndfile"
SET LIBSNDFILE_B="%MYPATH%/../../libsndfile"
SET VS_REDIST=%VCToolsRedistDir%vc_redist.x64.exe
SET "VS_REDIST=%VS_REDIST:\=/%"

IF EXIST %LLVM_CONFIG_A% (
    SET LLVM_CONFIG=%LLVM_CONFIG_A%
    echo llvm-config.exe found at %LLVM_CONFIG%
) ELSE (
    IF EXIST %LLVM_CONFIG_B% (
        SET LLVM_CONFIG=%LLVM_CONFIG_B%
        echo llvm-config.exe found at %LLVM_CONFIG%
    ) ELSE (
        echo llvm-config.exe not found at %LLVM_CONFIG_A% or %LLVM_CONFIG_B%
        EXIT /B
    )
)

IF EXIST %MAXSDK_A% (
    SET MAXSDK=%MAXSDK_A%
    echo max-sdk-base found at %MAXSDK%
) ELSE (
    IF EXIST %MAXSDK_B% (
        SET MAXSDK=%MAXSDK_B%
        echo max-sdk-base found at %MAXSDK%
    ) ELSE (
        echo max-sdk-base not found at %MAXSDK_A% or %MAXSDK_B%
        EXIT /B
    )
)

IF EXIST %LIBSNDFILE_A% (
    SET LIBSNDFILE=%LIBSNDFILE_A%
    echo libsndfile install found at %LIBSNDFILE%
) ELSE (
    IF EXIST %LIBSNDFILE_B% (
        SET LIBSNDFILE=%LIBSNDFILE_B%
        echo libsndfile install found at %LIBSNDFILE%
    ) ELSE (
        echo libsndfile install not found at %LIBSNDFILE_A% or %LIBSNDFILE_B%
        EXIT /B
    )
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
SET DEST=Release-%VERSION%
IF EXIST %DEST% ( 
    echo Warning ! %DEST% exist and may be non empty
    GOTO NEXT
)
mkdir %DEST%

:NEXT
COPY Faust-%VERSION%-win64.exe %DEST%
COPY ..\embedded\faustgen\package\faustgen-%FAUSTGENVERSION%-win64.zip %DEST%

echo DONE VERSION %VERSION%
