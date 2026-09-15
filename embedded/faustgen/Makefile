
.PHONY: all package cmake clean test help

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

test:
	python3 -m unittest discover -s tests -v

help:
	@echo "faustgen build targets:"
	@echo "  make all      Configure and build the faustgen external (default)"
	@echo "  make cmake    Configure the build directory"
	@echo "  make test     Run the unit and regression test suite"
	@echo "  make package  Build and install the distributable package"
	@echo "  make clean    Remove the build directory"
	@echo "  make help     Display this help"
	@echo ""
	@echo "Common variables:"
	@echo "  MAXSDK=<path>       Max SDK c74support directory"
	@echo "  FAUST=<command>     Faust compiler executable (default: faust)"
	@echo "  OUTDIR=<directory>  Build directory (default: build)"
	@echo "  CMAKEOPT=<options>  Additional CMake options"
	@echo "  GENERATOR=<option>  CMake generator option, for example -G Ninja"
