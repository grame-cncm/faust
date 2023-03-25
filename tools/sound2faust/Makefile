
DESTDIR ?= 
PREFIX ?= /usr/local

ARCHS   ?=
# ARCHS   ?= -arch x86_64

prefix := $(DESTDIR)$(PREFIX)

system	?= $(shell uname -s)

## On Windows (mingw32) we must link against the socket library.
ifneq ($(findstring MINGW32, $(system)),)
LIBS = -lwsock32
EXE = .exe
endif

SNDFILE_STATIC_LIBS = $(shell pkg-config --libs sndfile | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libsndfile.a

all : sound2faust sound2file

sound2faust : sound2faust.cpp
	$(CXX) $(ARCHS) -O3 $(LDFLAGS) sound2faust.cpp -I../../architecture $(shell pkg-config --cflags sndfile) -o sound2faust $(LIBS) $(SNDFILE_STATIC_LIBS)

sound2file : sound2file.cpp
	$(CXX) $(ARCHS) -O3 $(LDFLAGS) sound2file.cpp -I../../architecture $(shell pkg-config --cflags sndfile) -o sound2file $(LIBS) $(SNDFILE_STATIC_LIBS)

install :
	([ -e sound2faust ]) && install sound2faust $(prefix)/bin/ || echo sound2faust not found
	([ -e sound2file ]) && install sound2file $(prefix)/bin/ || echo sound2file not found
	([ -e sound2reader ]) && install sound2reader $(prefix)/bin/ || echo sound2reader not found

clean :
	rm -f sound2faust$(EXE) sound2file$(EXE)


	
