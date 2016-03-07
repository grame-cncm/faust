#!/bin/bash
set -e
echo "Updating packages..."
sudo apt-get -y update
echo "Installing Faust dependencies..."
sudo apt-get install -y build-essential pkg-config git libmicrohttpd-dev llvm-3.6 libssl-dev ncurses-dev libsndfile-dev
git clone git://git.code.sf.net/p/faudiostream/code faust
echo "Compiling Faust..."
cd faust
git checkout faust2
make world
echo "Installing Faust..."
sudo make install
echo "Done!"
