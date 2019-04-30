
.PHONY: package

ROOT   ?= $(shell pwd)
MAKE   ?= make
OUTDIR ?= build
FAUST  ?= faust
MAXSDK ?= $(ROOT)/max-sdk-7.3.3/source/c74support
JOBS   ?= 
GENERATOR ?= 

all: 
	$(MAKE) cmake
	cmake --build $(OUTDIR) --config Release -- $(JOBS)

package: 
	cmake --build $(OUTDIR) --config Release --target install

cmake: $(OUTDIR)
	cd $(OUTDIR) && cmake -Wno-dev -DFAUST=$(FAUST) -DMAXSDK=$(MAXSDK) .. $(GENERATOR)

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
