# Project Name
TARGET = ex_faust

# Sources
CPP_SOURCES = ex_faust.cpp

# Library Locations
LIBDAISY_DIR ?= ../../../libdaisy
DAISYSP_DIR ?= ../../../DaisySP

# Debug purposes, to remove
#LDFLAGS = -u _printf_float

# Linker Settings
APP_TYPE ?= BOOT_NONE

# Optimization Level (default: -Os for size optimization)
OPT ?= -Os

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

# Soundfile support: when a DSP uses soundfiles, the audio samples are inlined
# as 'const' into daisy_soundfile.hpp. Build with -qspi so they are placed in
# QSPI flash (they do not fit in the 128 KB internal flash). No extra build
# step is needed: the samples are part of the single program image.
