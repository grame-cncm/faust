#!/bin/bash
set -e

function installfaust {
	SUDO=`which sudo`

	echo "Updating packages..."
	$SUDO apt-get -y update
	echo "Installing Faust dependencies..."
	$SUDO apt-get install -y build-essential pkg-config git libmicrohttpd-dev llvm-3.6 libssl-dev ncurses-dev libsndfile-dev valgrind

	# Install all the needed SDK
	$SUDO apt-get install -y libgtk2.0-dev libasound2-dev jackd2 libjack-jackd2-dev libqrencode-dev
	$SUDO apt-get install -y qt4-default libcsound64-dev dssi-dev lv2-dev puredata-dev supercollider-dev wget unzip libboost1.54-dev
	$SUDO apt-get install -y inkscape graphviz

    # install QT5 for faust2faustvst
    $SUDO apt-get install -y qtbase5-dev qt5-qmake libqt5x11extras5-dev
    $SUDO ln -s /usr/lib/x86_64-linux-gnu/qt5/bin/qmake /usr/bin/qmake-qt5

	# Install faust2pd from Albert Greaf Pure-lang PPA
	$SUDO apt-get install -y software-properties-common
	$SUDO add-apt-repository -y ppa:dr-graef/pure-lang.trusty
	$SUDO apt-get -y update
	$SUDO apt-get install -y faust2pd

	# Install pd.dll needed to cross compile pd externals for windows
	wget http://faust.grame.fr/pd.dll
	$SUDO mv pd.dll /usr/include/pd/

	# Install VST SDK
	wget http://www.steinberg.net/sdk_downloads/vstsdk365_12_11_2015_build_67.zip
	unzip vstsdk365_12_11_2015_build_67.zip
	$SUDO mv "VST3 SDK" /usr/local/include/vstsdk2.4

	# Install cross-compiler
	$SUDO apt-get install -y g++-mingw-w64

	# Install MaxMSP SDK
	wget https://cycling74.com/download/max-sdk-7.1.0.zip
	unzip max-sdk-7.1.0.zip
	$SUDO cp -r max-sdk-7.1.0/source/c74support /usr/local/include/

	# Install ROS Jade
	$SUDO sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
	$SUDO apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 0xB01FA116
	$SUDO apt-get -y update
	$SUDO apt-get install -y ros-jade-ros-base


	# Install Bela
	$SUDO apt-get install -y gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf mercurial
	$SUDO hg clone https://code.soundsoftware.ac.uk/hg/beaglert
	## currently needed for experimental midi stuff
	cd beaglert
	$SUDO hg checkout mergingClockSync
	$SUDO hg pull -u
	cd ..
	## end midi stuff
	$SUDO mv beaglert /usr/local/
	## install xenomia (should be downloaded from an official place)
	wget 192.168.1.3/xenomai.tgz
	tar xzf xenomai.tgz
	$SUDO mv xenomai /usr/arm-linux-gnueabihf/include/

	# Install Android development tools
	## install java 8
	echo y |sudo add-apt-repository ppa:webupd8team/java
	sudo apt-get update -y
	sudo apt-get install -y oracle-java8-installer

	## install android sdk
	install -d /opt/android
	cd /opt/android
	wget https://dl.google.com/android/android-sdk_r24.4.1-linux.tgz
	tar -xzf android-sdk_r24.4.1-linux.tgz
	mv android-sdk-linux/ sdk
	rm android-sdk_r24.4.1-linux.tgz

	## install android ndk
	wget https://dl.google.com/android/repository/android-ndk-r12-linux-x86_64.zip
	unzip -q android-ndk-r12-linux-x86_64.zip
	mv android-ndk-r12 ndk
	rm android-ndk-r12-linux-x86_64.zip

	export PATH="/opt/android/sdk/tools:/opt/android/sdk/platform-tools:/opt/android/ndk:$PATH"
	echo y | android update sdk --no-ui -a --filter tools,platform-tools,android-24,build-tools-24.0.0

	# Install Latex
	$SUDO apt-get install -y texlive-full

	# Install Faust
	git clone git://git.code.sf.net/p/faudiostream/code faust
	cd faust
	git checkout faust2
	make world
	$SUDO make install
	cd ..
	echo "Installation Done!"
}

function testscript {
	echo testing $@...
	($@ faust/examples/noise.dsp &>MYLOG)&&(echo $(tput smso) $@ OK $(tput rmso))||(echo $(tput smso) $@ FAILED $(tput rmso)); cat MYLOG;
}

function testfaust {
	echo "Test Faust Installation"
	testscript faust2alsa -httpd -osc -poly -midi
	testscript faust2alqt
	testscript faust2bela
	testscript faust2dssi
	testscript faust2jackinternal
	testscript faust2msp
	testscript faust2puredata
	testscript faust2svg
	testscript faust2alsa
	testscript faust2eps
	testscript faust2jackserver
	testscript faust2netjackconsole
	testscript faust2raqt
	testscript faust2alsaconsole
	testscript faust2faustvst
	testscript faust2faustvst -gui -qt4
	testscript faust2faustvst -gui -qt5
	testscript faust2jaqt
	testscript faust2netjackqt
	testscript faust2ros
	testscript faust2vsti
	testscript faust2android
	testscript faust2firefox
	testscript faust2ladspa
	testscript faust2octave
	testscript faust2rosgtk
	testscript faust2w32max6
	testscript faust2api
	testscript faust2gen
	testscript faust2lv2
	testscript faust2lv2 -gui -qt4
	testscript faust2lv2 -gui -qt4
	testscript faust2owl
	testscript faust2rpialsaconsole
	testscript faust2w32msp
	testscript faust2asmjs
	testscript faust2graph
	testscript faust2lv2synth
	testscript faust2paqt
	testscript faust2rpinetjackconsole
	testscript faust2w32puredata
	testscript faust2au
	testscript faust2graphviewer
	testscript faust2mathdoc
	testscript faust2pd
	testscript faust2sc
	testscript faust2w32vst
	testscript faust2caqt
	testscript faust2ios
	testscript faust2mathviewer
	testscript faust2pdf
	testscript faust2sig
	testscript faust2webaudioasm
	testscript faust2caqtios
	testscript faust2jack
	testscript faust2max6
	testscript faust2plot
	testscript faust2sigviewer
	testscript faust2csound
	testscript faust2jackconsole
	testscript faust2md
	testscript faust2png
	testscript faust2supercollider
}

installfaust
testfaust

