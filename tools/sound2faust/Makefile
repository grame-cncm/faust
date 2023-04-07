
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

USE_STATIC_SNDFILE ?= 0

ifeq ($(USE_STATIC_SNDFILE),1)
	LAME_PRIMARY_PREFIX ?= /usr/local/Cellar/lame
	LAME_BACKUP_PREFIX ?= /opt/homebrew/Cellar/lame
	LAME_STATIC_LIBS ?= $(shell find $(LAME_PRIMARY_PREFIX) -name libmp3lame.a 2>/dev/null || find $(LAME_BACKUP_PREFIX) -name libmp3lame.a 2>/dev/null)
	SNDFILE_STATIC_LIBS = $(shell pkg-config --libs sndfile | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libsndfile.a
	FLAC_STATIC_LIBS = $(shell pkg-config --libs flac | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libflac.a
	OGG_STATIC_LIBS = $(shell pkg-config --libs ogg | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libogg.a
	VORBIS_STATIC_LIBS = $(shell pkg-config --libs vorbis | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libvorbis.a
	VORBISFILE_STATIC_LIBS = $(shell pkg-config --libs vorbis | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libvorbisfile.a
	VORBISENC_STATIC_LIBS = $(shell pkg-config --libs vorbis | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libvorbisenc.a
	MPG123_STATIC_LIBS = $(shell pkg-config --libs libmpg123 | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libmpg123.a
	OPUS_STATIC_LIBS = $(shell pkg-config --libs opus | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libopus.a

	SNDFILE_LIBS = $(SNDFILE_STATIC_LIBS) $(FLAC_STATIC_LIBS) $(OGG_STATIC_LIBS) $(VORBIS_STATIC_LIBS) $(VORBISFILE_STATIC_LIBS) $(VORBISENC_STATIC_LIBS) $(MPG123_STATIC_LIBS) $(OPUS_STATIC_LIBS) $(LAME_STATIC_LIBS)
else
	SNDFILE_LIBS ?= `pkg-config --cflags --libs sndfile`
endif

all : sound2faust sound2file

sound2faust : sound2faust.cpp
	$(CXX) $(ARCHS) -O3 $(LDFLAGS) sound2faust.cpp -I../../architecture $(shell pkg-config --cflags sndfile) -o sound2faust $(LIBS) $(SNDFILE_LIBS)

sound2file : sound2file.cpp
	$(CXX) $(ARCHS) -O3 $(LDFLAGS) sound2file.cpp -I../../architecture $(shell pkg-config --cflags sndfile) -o sound2file $(LIBS) $(SNDFILE_LIBS)

install :
	([ -e sound2faust ]) && install sound2faust $(prefix)/bin/ || echo sound2faust not found
	([ -e sound2file ]) && install sound2file $(prefix)/bin/ || echo sound2file not found
	([ -e sound2reader ]) && install sound2reader $(prefix)/bin/ || echo sound2reader not found

clean :
	rm -f sound2faust$(EXE) sound2file$(EXE)


	
