#!/bin/bash
set -e
echo "Updating packages..."
sudo apt-get -y update
echo "Installing Faust dependencies..."
sudo apt-get install -y build-essential pkg-config git libmicrohttpd-dev llvm-3.6 libssl-dev ncurses-dev libsndfile-dev
sudo apt-get install -y libgtk2.0-dev libasound2-dev jackd2 libjack-jackd2-dev
git clone git://git.code.sf.net/p/faudiostream/code faust
echo "Compiling Faust..."
cd faust
git checkout faust2
make world
echo "Installing Faust..."
sudo make install
echo "Done!"
