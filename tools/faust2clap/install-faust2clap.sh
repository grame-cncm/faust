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

# Copy lib from tool subdir instead
if [ -d "$SCRIPT_DIR/lib" ]; then
  sudo cp -R "$SCRIPT_DIR/lib" "$INSTALL_ROOT/"
else
  echo "⚠️  Missing lib directory in tools/faust2clap"
fi

# copy core files from SCRIPT_DIR (tools/faust2clap)
for file in faust2clap.py faust2clap.sh CMakeLists.txt; do
  if [ -f "$SCRIPT_DIR/$file" ]; then
    sudo cp "$SCRIPT_DIR/$file" "$INSTALL_ROOT/"
  else
    echo "⚠️  Missing expected file: $file"
  fi
done

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