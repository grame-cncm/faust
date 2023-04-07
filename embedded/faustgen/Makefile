
.PHONY: package

ROOT   ?= $(shell pwd)
MAKE   ?= make
OUTDIR ?= build
FAUST  ?= faust
JOBS   ?= 
GENERATOR ?= 
LLVM_CONFIG ?= on
CMAKEOPT ?= 
LLVM_LIBS ?= 
LLVM_LD_FLAGS ?= 
MAXSDK ?= $(shell echo $(PWD)/../max-sdk/source/max-sdk-base/c74support)
USE_STATIC_SNDFILE ?= 0

all: 
	$(MAKE) cmake
	cmake --build $(OUTDIR) --config Release

package: 
	cmake --build $(OUTDIR) --config Release --target install

cmake: $(OUTDIR)
	cd $(OUTDIR) && cmake -Wno-dev -DFAUST="$(FAUST)" -DMAXSDK="$(MAXSDK)" -DUSE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE) -DUSE_LLVM_CONFIG=$(LLVM_CONFIG) -DLLVM_LIBS="$(LLVM_LIBS)" -DLLVM_LD_FLAGS="$(LLVM_LD_FLAGS)" $(CMAKEOPT) .. $(GENERATOR)

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
