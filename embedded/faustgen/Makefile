
.PHONY: package

# Get the absolute path to the Makefile
MAKEFILE_PATH := $(realpath $(lastword $(MAKEFILE_LIST)))
# Get the parent directory of the Makefile
PARENT_DIR := $(dir $(MAKEFILE_PATH))

ROOT   ?= $(shell pwd)
MAKE   ?= make
OUTDIR ?= build
FAUST  ?= faust
JOBS   ?= 
GENERATOR ?= 
CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Release
MAXSDK ?= $(PARENT_DIR)../../max-sdk/source/max-sdk-base/c74support
USE_STATIC_SNDFILE ?= 0
FAUST_PATH_IS_ABSOLUTE ?= 0

NCURSES_PRIMARY_PREFIX := /usr/local/Cellar/ncurses
NCURSES_BACKUP_PREFIX := /opt/homebrew/Cellar/ncurses
NCURSES_STATIC_LIB ?= $(shell find $(NCURSES_PRIMARY_PREFIX) -name libncurses.a 2>/dev/null || find $(NCURSES_BACKUP_PREFIX) -name libncurses.a 2>/dev/null)

all: 
	$(MAKE) cmake
	cmake --build $(OUTDIR) --config Release

package: 
	cmake --build $(OUTDIR) --config Release --target install

cmake: $(OUTDIR)
	cd $(OUTDIR) && cmake -Wno-dev -DFAUST_PATH_IS_ABSOLUTE=$(FAUST_PATH_IS_ABSOLUTE) -DFAUST="$(FAUST)" -DNCURSES_STATIC_LIB="$(NCURSES_STATIC_LIB)" -DMAXSDK="$(MAXSDK)" -DUSE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE) $(CMAKEOPT) .. $(GENERATOR)

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
