#!/bin/bash
set -euo pipefail

#####################################################################
#                                                                   #
#        install-faust2clap.sh - setup for global faust2clap        #
#       (c) Grame & Facundo Franchino                               #
#                                                                   #
#####################################################################

INSTALL_ROOT="/usr/local/share/faust2clap"
BIN_LINK="/usr/local/bin/faust2clap"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"  

# create install location
sudo mkdir -p "$INSTALL_ROOT"

# copy full required folders from REPO_ROOT
for dir in architecture external; do
  if [ -d "$REPO_ROOT/$dir" ]; then
    sudo cp -R "$REPO_ROOT/$dir" "$INSTALL_ROOT/"
  else
    echo "⚠️  Skipping missing directory: $dir"
  fi
done

# copy gui_stuff contents into architecture/clap/gui_stuff
GUI_ASSETS_SRC="$REPO_ROOT/architecture/clap/gui_stuff"
GUI_ASSETS_DEST="$INSTALL_ROOT/architecture/clap/gui_stuff"
if [ -d "$GUI_ASSETS_SRC" ]; then
  sudo mkdir -p "$GUI_ASSETS_DEST"
  sudo cp -R "$GUI_ASSETS_SRC/"* "$GUI_ASSETS_DEST/"
else
  echo "⚠️  gui_stuff folder not found at: $GUI_ASSETS_SRC"
fi

# copy core files from SCRIPT_DIR (tools/faust2clap)
for file in faust2clap.py faust2clap.sh CMakeLists.txt; do
  if [ -f "$SCRIPT_DIR/$file" ]; then
    sudo cp "$SCRIPT_DIR/$file" "$INSTALL_ROOT/"
  else
    echo "⚠️  Missing expected file: $file"
  fi
done

# copy Makefile.simple from architecture/clap instead
MAKEFILE_SRC="$REPO_ROOT/architecture/clap/Makefile.simple"
if [ -f "$MAKEFILE_SRC" ]; then
  sudo cp "$MAKEFILE_SRC" "$INSTALL_ROOT/"
else
  echo "⚠️  Missing Makefile.simple in architecture/clap"
fi

# patch Makefile.simple include paths to point to install location
MAKEFILE_INSTALLED="$INSTALL_ROOT/Makefile.simple"
if [ -f "$MAKEFILE_INSTALLED" ]; then
  sudo sed -i '' "s|../../architecture|$INSTALL_ROOT/architecture|g" "$MAKEFILE_INSTALLED"
  sudo sed -i '' "s|\$(FAUST2CLAP_ROOT)/external|$INSTALL_ROOT/external|g" "$MAKEFILE_INSTALLED"
fi

# copy GUI script from gui_stuff
GUI_SCRIPT_SRC="$REPO_ROOT/architecture/clap/faust-hot-reload.py"
if [ -f "$GUI_SCRIPT_SRC" ]; then
  sudo cp "$GUI_SCRIPT_SRC" "$INSTALL_ROOT/"
else
  echo "⚠️  GUI script not found at: $GUI_SCRIPT_SRC"
fi

# copy icon asset for desktop gui
ICON_SRC="$REPO_ROOT/architecture/clap/gui_stuff/grame.icns"
ICON_DEST="$INSTALL_ROOT/architecture/clap/gui_stuff/grame.icns"

if [ -f "$ICON_SRC" ]; then
  sudo mkdir -p "$(dirname "$ICON_DEST")"
  sudo cp "$ICON_SRC" "$ICON_DEST"
else
  echo "⚠️  grame.icns not found at: $ICON_SRC"
fi

# create CLI symlink
sudo ln -sf "$INSTALL_ROOT/faust2clap.sh" "$BIN_LINK"
sudo chmod +x "$INSTALL_ROOT/faust2clap.sh"

# optional: install libfaust.dylib
FAUST_LIB_SRC="$REPO_ROOT/build/lib/libfaust.dylib"
FAUST_LIB_DEST="/usr/local/lib/libfaust.dylib"

if [ -f "$FAUST_LIB_SRC" ]; then
  if [ ! -f "$FAUST_LIB_DEST" ]; then
    sudo cp "$FAUST_LIB_SRC" "$FAUST_LIB_DEST"
    echo "✅ libfaust.dylib installed."
  else
    echo "ℹ️  libfaust.dylib already exists in /usr/local/lib"
  fi
else
  echo "⚠️  libfaust.dylib not found in expected build location."
  echo "🔨 Attempting to build libfaust..."
  cd "$REPO_ROOT"
  make -j$(sysctl -n hw.ncpu || echo 4)

  if [ -f "$FAUST_LIB_SRC" ]; then
    sudo cp "$FAUST_LIB_SRC" "$FAUST_LIB_DEST"
    echo "✅ libfaust.dylib installed after build."
  else
    echo "❌ Still missing libfaust.dylib after build. Please verify Faust is built."
  fi
fi

echo "✅ faust2clap installed to: $INSTALL_ROOT"
echo "👉 Try: faust2clap --dynamic --install"
echo "👉 Try: faust2clap myeffect.dsp"