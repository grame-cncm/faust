# Makefile to generate impulse responses `.ir` using Mojo

system := $(shell uname -s)
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), MINGW)
 FAUST ?= ../../build/bin/faust.exe
 COMPARE := ./filesCompare.exe
 EXEEXT := .exe
else
 FAUST ?= ../../build/bin/faust
 COMPARE := ./filesCompare
 EXEEXT :=
endif

MAKE ?= make
MOJO ?= pixi run mojo

outdir ?= mojo/double
lang ?= mojo
ext ?= mojo
arch ?= mojo/impulse.mojo
genout ?= archs/mojo
precision ?=
FAUSTOPTIONS ?= -I dsp -double
MOJOBUILDOPTIONS ?= -O3 -D DFAUST=DType.float32

.PHONY: all help test filesCompare clean
.DELETE_ON_ERROR:

dspfiles := $(wildcard dsp/*.dsp)

listfiles = $(dspfiles:dsp/%.dsp=ir/$1/%.ir)

all: filesCompare ir/$(outdir) $(call listfiles,$(outdir))

help:
	@echo "-------- FAUST impulse response tests (Mojo) --------"
	@echo "Available targets are:"
	@echo " 'all' (default): generate ir for all the dsp files using the given options"
	@echo
	@echo "Options:"
	@echo " 'outdir'           : define the output directory (default to '$(outdir)')"
	@echo " 'lang'             : used for faust -lang option (default to '$(lang)')"
	@echo " 'arch'             : used for faust -a option (default to '$(arch)')"
	@echo " 'FAUSTOPTIONS'     : define additional faust options (default to $(FAUSTOPTIONS))"
	@echo " 'MOJOBUILDOPTIONS' : additional options passed to 'mojo build'"
	@echo " 'precision'        : define filesCompare expected precision (empty by default)"

################################################################
# output directories
ir/$(outdir):
	mkdir -p ir/$(outdir)

filesCompare:
	$(MAKE) -f Makefile filesCompare

################################################################
# rules
ir/$(outdir)/%.ir: ir/$(outdir)/%$(EXEEXT) reference/%.ir | ir/$(outdir)
	$< -n 60000 > $@
	$(COMPARE) $@ reference/$(notdir $@) $(precision)

ir/$(outdir)/%$(EXEEXT): $(genout)/%.$(ext) | ir/$(outdir)
	$(MOJO) build $< -o $@ $(MOJOBUILDOPTIONS)
	rm -f $<

$(genout)/%.$(ext): dsp/%.dsp
	$(FAUST) -lang $(lang) $(FAUSTOPTIONS) -i -A ../../architecture -a archs/$(arch) $< -o $@

clean:
	rm -rf ir/$(outdir)
