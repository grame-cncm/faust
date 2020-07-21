
@echo off

IF NOT EXIST faust.sln (
	echo "Warning, this script must be called from the build folder (e.g. faustdir)"
	GOTO END
)


cmake -DUSE_LLVM_CONFIG=on -DPACK=on -C ../backends/most.cmake -C ../targets/windows.cmake ..
cmake --build . --config Release --  /maxcpucount:4
cpack -G NSIS64
move Faust-*.exe ..

:END
