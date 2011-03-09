

all : liboscpack.a libOSCFaust.a

liboscpack.a :
	cd oscpack/cmake && cmake -G "Unix Makefiles"
	make -C oscpack/cmake

libOSCFaust.a :
	cd faust/cmake && cmake -G "Unix Makefiles"
	make -C faust/cmake

clean :
	make -C oscpack/cmake clean
	rm   -f oscpack/cmake/CMakeCache.txt
	make -C faust/cmake clean
	rm   -f faust/cmake/CMakeCache.txt

