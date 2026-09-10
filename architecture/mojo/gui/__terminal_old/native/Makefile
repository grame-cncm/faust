CC ?= cc
AR ?= ar
MOJO ?= mojo
FAUST ?= faust
PA_LINK ?= -Xlinker -lportaudio
DSP ?=
FAUST_FLAGS ?=
MOJO_FLAGS ?=
PROGRAM ?= build/terminal
SOURCE ?= build/program.mojo
SAMP_RATE ?= 96
BUFF_SIZE ?= 256
MODE ?= release
WARN = -Wall -Wextra -Wshadow -Wconversion -Werror -Wpedantic
BASE = -std=c11 $(WARN)
FLAGS_release = -O2 -DNDEBUG
FLAGS_debug = -O0 -g -DMJ_DEBUG=1
OBJ = build/$(MODE)/termgui.o
LIB = build/$(MODE)/libtermgui.a

.PHONY: all debug release clean check-import program link help FORCE
all: build/libtermgui.a

build/libtermgui.a: $(LIB) FORCE
	cp $(LIB) $@

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

$(OBJ): termgui.c termgui.h
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(BASE) $(FLAGS_$(MODE)) $(CFLAGS) -c $< -o $@

debug release:
	$(MAKE) MODE=$@ all

# The prototype rename belongs to the caller, never to a build recipe.
check-import:
	@test ! -f ../../terminal.mojo || { echo 'Rename gui/terminal.mojo to gui/proto.mojo first (prototype/package ambiguity).'; exit 1; }

# SAMP_RATE follows the architecture convention: kHz, not Hz. Build only, no playback.
program: check-import
	@test -f "$(DSP)" || { echo 'DSP file not found; pass DSP=/path/to/file.dsp'; exit 1; }
	mkdir -p build
	$(FAUST) -lang mojo $(FAUST_FLAGS) -a ../../../portaudio-terminal.mojo "$(DSP)" -o build/program.mojo
	$(MAKE) link SOURCE=build/program.mojo

link: all check-import
	@test -f "$(SOURCE)" || { echo 'Mojo source not found; pass SOURCE=/path/to/generated.mojo'; exit 1; }
	$(MOJO) build -I ../../.. -DSAMP_RATE=$(SAMP_RATE) -DBUFF_SIZE=$(BUFF_SIZE) $(MOJO_FLAGS) \
		"$(SOURCE)" -Xlinker "$(abspath build/libtermgui.a)" -Xlinker -lm $(PA_LINK) -o "$(PROGRAM)"

help:
	@echo 'make release                          build libtermgui.a'
	@echo 'make program DSP=/path/to/file.dsp     build your Faust DSP'
	@echo 'make link SOURCE=/path/to/file.mojo    link an already generated DSP'
	@echo 'SAMP_RATE=48 BUFF_SIZE=128             configure CPU audio'
	@echo 'Run ./build/terminal separately.'

clean:
	$(RM) build/libtermgui.a build/release/termgui.o build/release/libtermgui.a
	$(RM) build/debug/termgui.o build/debug/libtermgui.a
	$(RM) build/terminal build/program.mojo

FORCE:
