
DESTDIR ?= 
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

system	?= $(shell uname -s)

## On Windows (mingw32) we must link against the socket library.
ifneq ($(findstring MINGW32, $(system)),)
LIBS = -lwsock32
EXE = .exe
endif

sound2faust : sound2faust.cpp

	$(CXX) -O3 sound2faust.cpp -I../../architecture `pkg-config --cflags --static --libs sndfile` -o sound2faust $(LIBS)

static:

	$(CXX) -O3 sound2faust.cpp -I../../architecture `pkg-config --cflags  sndfile`  /usr/local/lib/libsndfile.a -o sound2faust

install :

	install sound2faust $(prefix)/bin/
	install sound2reader $(prefix)/bin/

clean :
	rm -f sound2faust$(EXE)


	
