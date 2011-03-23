
all : oscpack/cmake/Makefile faust/cmake/Makefile
	make -C oscpack/cmake
	make -C faust/cmake

oscpack/cmake/Makefile:
	cd oscpack/cmake && cmake -G "Unix Makefiles"

faust/cmake/Makefile:
	cd faust/cmake && cmake -G "Unix Makefiles"
	
clean :
	make -C oscpack/cmake clean
	rm   -f oscpack/cmake/CMakeCache.txt
	make -C faust/cmake clean
	rm   -f faust/cmake/CMakeCache.txt

