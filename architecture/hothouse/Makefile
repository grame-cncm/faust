TARGET = ex_faust

USE_DAISYSP_LGPL=1

# Library Locations
HOTHOUSE_DIR ?= ../../HothouseExamples
LIBDAISY_DIR ?= $(HOTHOUSE_DIR)/libdaisy
DAISYSP_DIR ?= $(HOTHOUSE_DIR)/DaisySP

# Sources
CPP_SOURCES = $(TARGET).cpp $(HOTHOUSE_DIR)/src/hothouse.cpp
C_INCLUDES = -I$(HOTHOUSE_DIR)/src/

# Optimization Level (default: -Os for size optimization)
OPT ?= -Os

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

# Global includes
include $(HOTHOUSE_DIR)/src/Makefile
