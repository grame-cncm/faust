# Dynamic Faust CLAP plugin: one binary that compiles .dsp programs at runtime
# with the libfaust interpreter backend and hot-reloads them while the host
# plays.
#
#   make           build FaustDynamic.clap
#   make install   install it for the current user
#   make clean     remove the build output
#   make help      show the configuration and the options

UNAME := $(shell uname -s)

CXX       ?= c++
CXXFLAGS  ?= -O2 -Wall -Wextra
LDFLAGS   ?=
ARCHFLAGS ?=

# A libfaust built with `make interp` needs nothing else. One that also carries
# the LLVM backend does; pass it in:
#   make LLVM_LIBS="$$(llvm-config --ldflags --libs --system-libs)"
LLVM_LIBS ?=

# Ask the installed compiler where its files are; fall back to this checkout.
FAUST_INCLUDE ?= $(shell faust --includedir 2>/dev/null)
FAUST_LIBDIR  ?= $(shell faust --libdir 2>/dev/null)

PLUGIN  = FaustDynamic.clap
SOURCES = dynamic-faust.cpp clap-dsp-bundle.cpp clap-plugin-impl.cpp clap-gui-glue.cpp
OBJECTS = $(SOURCES:.cpp=.o)

INCLUDES = -std=c++17 \
           -I../../architecture \
           -I../../external/clap-sdk/include \
           -I../../external/clap-helpers/include \
           $(if $(FAUST_INCLUDE),-I$(FAUST_INCLUDE))

LIBS = $(if $(FAUST_LIBDIR),-L$(FAUST_LIBDIR)) -lfaust $(LLVM_LIBS)

# Platform differences, all guarded so the Makefile is not macOS-only.
ifeq ($(UNAME),Darwin)
  BINARY      = $(PLUGIN)/Contents/MacOS/FaustDynamic
  LINKFLAGS   = -dynamiclib
  LIBS       += -framework CoreFoundation -framework CoreServices
  INSTALL_DIR = $(HOME)/Library/Audio/Plug-Ins/CLAP
else
  BINARY      = $(PLUGIN)
  LINKFLAGS   = -shared
  LIBS       += -ldl -lpthread
  # The CLAP specification says ~/.clap, not ~/.clap/plugins.
  INSTALL_DIR = $(HOME)/.clap
endif

# A .clap is a bundle on macOS. CFBundlePackageType must be BNDL: a host
# inspects the bundle before loading anything and refuses APPL, which is what a
# plain shared library copied into place looks like.
define INFO_PLIST
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0"><dict>
  <key>CFBundleExecutable</key><string>FaustDynamic</string>
  <key>CFBundleIdentifier</key><string>org.grame.faust.dynamic</string>
  <key>CFBundleName</key><string>FaustDynamic</string>
  <key>CFBundlePackageType</key><string>BNDL</string>
  <key>CFBundleSignature</key><string>????</string>
  <key>CFBundleShortVersionString</key><string>1.0.0</string>
  <key>CFBundleVersion</key><string>1.0.0</string>
</dict></plist>
endef
export INFO_PLIST

all: $(PLUGIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(ARCHFLAGS) -fPIC $(INCLUDES) -c $< -o $@

$(PLUGIN): $(OBJECTS)
ifeq ($(UNAME),Darwin)
	@mkdir -p $(PLUGIN)/Contents/MacOS
	@echo "$$INFO_PLIST" > $(PLUGIN)/Contents/Info.plist
	@printf 'BNDL????' > $(PLUGIN)/Contents/PkgInfo
endif
	$(CXX) $(LINKFLAGS) $(ARCHFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS) -o $(BINARY)
	@echo "built $(PLUGIN)"

install: $(PLUGIN)
	@mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(PLUGIN)
	cp -R $(PLUGIN) $(INSTALL_DIR)/
	@echo "installed $(PLUGIN) in $(INSTALL_DIR)"

clean:
	rm -rf $(OBJECTS) $(PLUGIN)

help:
	@echo "targets:"
	@echo "  make           build $(PLUGIN)"
	@echo "  make install   copy it into $(INSTALL_DIR)"
	@echo "  make clean     remove the build output"
	@echo ""
	@echo "configuration:"
	@echo "  CXX           = $(CXX)"
	@echo "  CXXFLAGS      = $(CXXFLAGS)"
	@echo "  ARCHFLAGS     = $(ARCHFLAGS)"
	@echo "  FAUST_INCLUDE = $(FAUST_INCLUDE)"
	@echo "  FAUST_LIBDIR  = $(FAUST_LIBDIR)"
	@echo "  LLVM_LIBS     = $(LLVM_LIBS)"
	@echo ""
	@echo "notes:"
	@echo "  needs a libfaust with the interpreter backend:"
	@echo "    make interp && sudo make install   (from the root of the Faust tree)"
	@echo "  LLVM_LIBS is only needed if that libfaust also carries the LLVM backend"
	@echo "  macOS builds native only; for a universal plugin, with a universal"
	@echo "  libfaust: make ARCHFLAGS=\"-arch arm64 -arch x86_64\""

.PHONY: all install clean help
