all : libFaustEngine.jnilib libFaust.jnilib TestFaust.class TestFaustEngine.class 

libFaustEngine.jnilib : FaustEngine.cpp faust-api.h 
	./faust2engine 

libFaust.jnilib : faust-api.h 
	./faust2engine 

TestFaustEngine.class : TestFaustEngine.java
	javac TestFaustEngine.java
	
TestFaust.class : TestFaust.java
	javac TestFaust.java

clean:
	rm -rf com FaustEngine_wrap.cxx Faust_wrap.cxx TestFaustEngine.class TestFaust.class libFaust.jnilib libFaustEngine.jnilib