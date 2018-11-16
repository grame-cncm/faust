/rem
/rem This simple script is intended to package faust without Makefile
/rem

echo "Warning, this script must be called from the build folder (e.g. faustdir)"
cmake -DUSE_LLVM_CONFIG=off -DPACK=on -C ../bakckends/most.cmake -C ../targets/most.cmake ..
cmake --build . --config Release --  /maxcpucount:4
cpack -G NSIS64
move Faust-*.exe ..