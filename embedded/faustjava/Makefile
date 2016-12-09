all : libFaustEngine.jnilib libFaust.jnilib TestFaust.class TestFaustEngine.class 

libFaustEngine.jnilib : ../../architecture/faust/dsp/faust-dynamic-engine.cpp ../../architecture/faust/dsp/faust-dynamic-engine.h FaustEngine.i
	./faust2engine 

libFaust.jnilib : libfaust_ext.cpp libfaust_ext.h Faust.i
	./faust2engine 

TestFaustEngine.class : TestFaustEngine.java
	javac TestFaustEngine.java
	
TestFaust.class : TestFaust.java
	javac TestFaust.java

clean:
	rm -rf com FaustEngine_wrap.cxx Faust_wrap.cxx TestFaustEngine.class TestFaust.class libFaust.jnilib libFaustEngine.jnilib