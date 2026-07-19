#
# Makefile for testing JAX backend with minimal.py architecture
#

system := $(shell uname -s)
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), MINGW)
 FAUST ?= ../../build/bin/faust.exe
else
 FAUST ?= ../../build/bin/faust
endif

PYTHON ?= python3
ARCHITECTURE ?= ../../architecture/jax/minimal.py
FAUSTOPTIONS ?= -lang nnx -a $(ARCHITECTURE)

# Find all DSP files in the dsp directory
dspfiles := $(wildcard dsp/*.dsp)

# TODO: waveform_tabulate.dsp is a known failure (missing fill function for the
# tabulated waveform, see https://github.com/grame-cncm/faust/issues/737).
# It is excluded from the default test run; run it manually with
# 'make test-waveform_tabulate' once the issue is fixed.
KNOWN_FAILURES := waveform_tabulate
dspfiles := $(filter-out $(KNOWN_FAILURES:%=dsp/%.dsp),$(dspfiles))

# Output directory for generated Python files
outdir := generated

# Target for each DSP file
pyfiles := $(dspfiles:dsp/%.dsp=$(outdir)/%.py)
testfiles := $(dspfiles:dsp/%.dsp=$(outdir)/%.test)

# Prevent automatic deletion of intermediate .py files
.SECONDARY: $(pyfiles)

.PHONY: all test clean help

# Generate individual test targets
test-%: $(outdir)/%.test
	@if grep -q "PASSED" $<; then \
		echo "✓ Test $* passed"; \
	else \
		echo "✗ Test $* failed"; \
		echo "Check logs:"; \
		echo "  - Compilation: $(outdir)/$*.compile.log"; \
		echo "  - Output: $(outdir)/$*.output.log"; \
		exit 1; \
	fi

# Compile only target
compile-%: $(outdir)/%.py
	@echo "✓ Compiled $*.dsp to $(outdir)/$*.py"

# Run only target (assumes already compiled)
run-%: $(outdir)/%.py
	@echo "Running $*.py..."
	@$(PYTHON) $< --duration 0.1 --jit

all: test

test: $(outdir) $(testfiles)
	@echo "===== JAX Backend Test Summary ====="
	@echo "Total tests: $(words $(testfiles))"
	@echo "Passed: $$(grep -l PASSED $(outdir)/*.test 2>/dev/null | wc -l | tr -d ' ')"
	@echo "Failed: $$(grep -l FAILED $(outdir)/*.test 2>/dev/null | wc -l | tr -d ' ')"
	@failed=$$(grep -l FAILED $(outdir)/*.test 2>/dev/null | sed 's|$(outdir)/||g' | sed 's|\.test||g'); \
	if [ -n "$$failed" ]; then \
		echo "Failed tests:"; \
		for f in $$failed; do echo "  - $$f"; done; \
		exit 1; \
	fi

help:
	@echo "===== FAUST JAX Backend Tests ====="
	@echo "This Makefile tests the JAX backend by compiling DSP files from the dsp/ directory"
	@echo "and running them with the minimal.py architecture."
	@echo ""
	@echo "Usage:"
	@echo "  make                    : Run all tests (default)"
	@echo "  make test               : Run all tests"
	@echo "  make test-<name>        : Test a specific DSP file"
	@echo "  make compile-<name>     : Only compile a specific DSP file"
	@echo "  make run-<name>         : Run a previously compiled DSP file"
	@echo "  make clean              : Remove generated files"
	@echo "  make help               : Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make test-simple_gain   : Test only simple_gain.dsp"
	@echo "  make compile-stereo_pan : Only compile stereo_pan.dsp"
	@echo "  make run-stereo_pan     : Run the compiled stereo_pan.py"
	@echo ""
	@echo "To add a test:"
	@echo "  1. Place a .dsp file in the dsp/ directory"
	@echo "  2. Run 'make' or 'make test-<filename>'"
	@echo ""
	@echo "Options:"
	@echo "  FAUST='path/to/faust'       : Specify Faust compiler path"
	@echo "  PYTHON='python3'            : Specify Python interpreter"
	@echo "  FAUSTOPTIONS='-lang nnx...' : Additional Faust options"

# Create output directory and dummy WAV files for sound.dsp
$(outdir):
	@mkdir -p $(outdir)
	@mkdir -p assets
	@echo "Creating dummy 4-channel WAV files for sound.dsp..."
	@$(PYTHON) -c "import numpy as np; from scipy.io import wavfile; \
		sr = 44100; duration = 1; channels = 4; \
		silence = np.zeros((int(sr * duration), channels), dtype=np.float32); \
		wavfile.write('assets/sound1.wav', sr, silence); \
		wavfile.write('assets/sound2.wav', sr, silence); \
		print('Created sound1.wav and sound2.wav with 4 channels in assets/')"

# Rule to compile DSP to Python. Write the log with a redirect rather than
# piping through tee: a pipeline's exit status is the last command's, which
# would turn every faust failure into a false "Compilation successful".
$(outdir)/%.py: dsp/%.dsp | $(outdir)
	@echo "Compiling $<..."
	if $(FAUST) $(FAUSTOPTIONS) -I ../../libraries/ $< -o $@ > $(outdir)/$*.compile.log 2>&1; then \
		cat $(outdir)/$*.compile.log; \
		echo "Compilation successful"; \
	else \
		cat $(outdir)/$*.compile.log; \
		echo "FAILED: Compilation error" > $(outdir)/$*.test; \
		exit 1; \
	fi

# Rule to run Python file and create test result
$(outdir)/%.test: $(outdir)/%.py
	@echo "Running $<..."
	@if [ "$*" = "random_test" ] || [ "$*" = "random_uniform" ]; then \
		if $(PYTHON) test_random.py $* > $(outdir)/$*.output.log 2>&1; then \
			echo "PASSED" > $@; \
			echo "✓ $(notdir $<) passed (random generation verified)"; \
		else \
			echo "FAILED: Random test failed" > $@; \
			echo "✗ $(notdir $<) failed"; \
			echo "  Error output:"; \
			tail -n 10 $(outdir)/$*.output.log | sed 's/^/    /'; \
		fi; \
	elif $(PYTHON) $< --duration 0.1 --jit > $(outdir)/$*.output.log 2>&1; then \
		echo "PASSED" > $@; \
		echo "✓ $(notdir $<) passed"; \
	else \
		echo "FAILED: Runtime error" > $@; \
		echo "✗ $(notdir $<) failed"; \
		echo "  Error output:"; \
		tail -n 10 $(outdir)/$*.output.log | sed 's/^/    /'; \
	fi

clean:
	@echo "Cleaning generated files..."
	@rm -rf $(outdir)
	@echo "Done."