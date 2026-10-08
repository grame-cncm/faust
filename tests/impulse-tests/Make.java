# Generate, compile, execute and compare Java double impulse responses.
.DEFAULT_GOAL := java
.DELETE_ON_ERROR:
.SECONDARY:

FAUST ?= ../../build/bin/faust
PYTHON ?= python3
JAVA ?=
JAVAC ?=
JAVAFLAGS ?=
JAVACFLAGS ?=
COMPARE ?= ./filesCompare
outdir ?= java/double
FAUSTOPTIONS ?= -I dsp -double
arch ?= archs/impulsearch.java
runner := tools/java-impulse.py
config := ir/$(outdir)/toolchain.json

# Java currently has no soundfile implementation. Keep the exclusion visible.
dspfiles ?= $(filter-out dsp/sound.dsp,$(wildcard dsp/*.dsp))
java_run_options :=
checks := $(patsubst dsp/%.dsp,check-java-%,$(dspfiles))

.PHONY: java java-preflight FORCE $(checks)
java: java-preflight $(checks)
	@test $(words $(checks)) -gt 0
	@echo "Java $(outdir): compared $(words $(checks)) programs in fixed mode, $(words $(filter-out check-java-bs,$(checks))) in fragmented mode, 15000 frames each"
	@echo "SKIP sound.dsp: Java soundfile support is not implemented"

java-preflight: filesCompare
	$(PYTHON) $(runner) prepare --config "$(config)" --faust "$(FAUST)" --java "$(JAVA)" --javac "$(JAVAC)" --javaflags="$(JAVAFLAGS)" --javacflags="$(JAVACFLAGS)" --compare "$(COMPARE)"

filesCompare:
	$(MAKE) filesCompare

# Fresh generation and compilation prevent a cached binary from hiding a change
# to Faust, its options or the JDK. Comparisons also run on every invocation.
FORCE:
ir/$(outdir)/%/mydsp.java: dsp/%.dsp $(arch) FORCE | java-preflight
	mkdir -p $(dir $@)
	$(FAUST) -lang java $(FAUSTOPTIONS) -a $(arch) $< -o $@

ir/$(outdir)/%/.compiled: ir/$(outdir)/%/mydsp.java
	$(PYTHON) $(runner) compile --config "$(config)" --source "$<"
	touch $@

# bs.dsp exposes the compute count; its signal intentionally depends on block size.
check-java-bs: java_run_options=--fixed-only

$(checks): check-java-%: ir/$(outdir)/%/.compiled reference/%.ir | java-preflight
	$(PYTHON) $(runner) run --config "$(config)" --classes "ir/$(outdir)/$*" --output "ir/$(outdir)/$*" --reference "reference/$*.ir" --compare "$(COMPARE)" $(java_run_options)
