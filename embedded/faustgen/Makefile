
.PHONY: package

ROOT   ?= $(shell pwd)
MAKE   ?= make
OUTDIR ?= build
FAUST  ?= faust
MAXSDK ?= $(ROOT)/max-sdk-7.3.3/source/c74support
JOBS   ?= 
GENERATOR ?= 
LLVM_CONFIG ?= on

all: 
	$(MAKE) cmake
	cmake --build $(OUTDIR) --config Release -- $(JOBS)

package: 
	cmake --build $(OUTDIR) --config Release --target install

cmake: $(OUTDIR)
	cd $(OUTDIR) && cmake -Wno-dev -DFAUST=$(FAUST) -DMAXSDK=$(MAXSDK) -DUSE_LLVM_CONFIG=$(LLVM_CONFIG) .. $(GENERATOR)

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
