
DESTDIR ?= 
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

sound2faust : sound2faust.cpp

	g++ -O3 sound2faust.cpp `pkg-config  --cflags --libs sndfile` -o sound2faust


install :

	install sound2faust $(prefix)/bin/

	
clean :
	rm sound2faust

	