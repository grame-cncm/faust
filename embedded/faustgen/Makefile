
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
MAXSDK ?= $(ROOT)/max-sdk-7.3.3/source/c74support
USE_STATIC_SNDFILE ?= 0
FAUST_PATH_IS_ABSOLUTE ?= 0

all: 
	$(MAKE) cmake
	cmake --build $(OUTDIR) --config Release

package: 
	cmake --build $(OUTDIR) --config Release --target install

cmake: $(OUTDIR)
	cd $(OUTDIR) && cmake -Wno-dev -DFAUST_PATH_IS_ABSOLUTE=$(FAUST_PATH_IS_ABSOLUTE) -DFAUST="$(FAUST)" -DMAXSDK="$(MAXSDK)" -DUSE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE) $(CMAKEOPT) .. $(GENERATOR)

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
