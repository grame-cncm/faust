#!/bin/bash

# For additional installations uncomment the following lines
#INSTALL_LATEX=1
#INSTALL_ANDROID=1
#INSTALL_BELA=1
#INSTALL_ROS=1

function installfaust {
	# Install 'Installation directory' if needed
	if [ ! -d ~/FaustInstall ]; then
		mkdir ~/FaustInstall
	fi
	cd ~/FaustInstall

	# for some reason which sudo doesn't work with Docker Ubuntu 16.04
	#SUDO=`which sudo`
	if [ -e /usr/bin/sudo ]; then
		SUDO=/usr/bin/sudo
	fi

	echo "Updating packages..."
	$SUDO apt-get -y update
	echo "Installing Faust dependencies..."
	echo yes | $SUDO apt install -y jackd2
	$SUDO apt-get install -y build-essential g++-multilib pkg-config git libmicrohttpd-dev llvm-3.9 llvm-3.9-dev libssl-dev ncurses-dev libsndfile-dev libedit-dev libcurl4-openssl-dev vim-common

	# Install all the needed SDK
	$SUDO apt-get install -y libgtk2.0-dev libasound2-dev libqrencode-dev portaudio19-dev
	$SUDO apt-get install -y libjack-jackd2-dev qjackctl qt4-default libcsound64-dev dssi-dev lv2-dev puredata-dev supercollider-dev wget unzip libboost-dev
	$SUDO apt-get install -y inkscape graphviz octave

    # install QT5 for faust2faustvst
    $SUDO apt-get install -y qtbase5-dev qt5-qmake libqt5x11extras5-dev
	if [ ! -e /usr/bin/qmake-qt5 ]; then
    	$SUDO ln -s /usr/lib/x86_64-linux-gnu/qt5/bin/qmake /usr/bin/qmake-qt5
	fi

	# Install faust2pd from Albert Greaf Pure-lang PPA
	$SUDO apt-get install -y software-properties-common
	$SUDO add-apt-repository -y ppa:dr-graef/pure-lang.zesty
	$SUDO apt-get -y update
	$SUDO apt-get install -y faust2pd faust2pd-extra

	# Install pd.dll needed to cross compile pd externals for windows
	PDW32BINDIR=/usr/lib/i686-w64-mingw32/pd

    if [ ! -e $PDW32BINDIR/pd.dll ]; then
        wget http://faust.grame.fr/pd.dll || wget http://ifaust.grame.fr/pd.dll
		$SUDO install -d $PDW32BINDIR
        $SUDO mv pd.dll $PDW32BINDIR
    fi


	# Install VST SDK
    if [ ! -d /usr/local/include/vstsdk2.4 ]; then
        wget http://www.steinberg.net/sdk_downloads/vstsdk365_12_11_2015_build_67.zip
        unzip vstsdk365_12_11_2015_build_67.zip
        $SUDO mv "VST3 SDK" /usr/local/include/vstsdk2.4
    fi

	# Install cross-compiler
	$SUDO apt-get install -y g++-mingw-w64

	# Install MaxMSP SDK
	if [ ! -d /usr/local/include/c74support ]; then
		if [ ! -f max-sdk-7.1.0.zip ]; then
			wget https://cycling74.com/download/max-sdk-7.1.0.zip
		fi
		unzip max-sdk-7.1.0.zip
		$SUDO cp -r max-sdk-7.1.0/source/c74support /usr/local/include/
	fi

	if [ -n "$INSTALL_ROS" ]; then
		# Install ROS Jade, see $(lsb_release -sc) instead of xenial
		echo "INSTALL ROS"
		$SUDO sh -c 'echo "deb http://packages.ros.org/ros/ubuntu  $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
		$SUDO apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
		$SUDO apt-get -y update
		$SUDO apt-get install -y ros-lunar-ros-base
	fi

	if [ -n "$INSTALL_BELA" ]; then
		# Install Bela
		echo "INSTALL BELA"
		$SUDO apt-get install -y gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
		if [ ! -d /usr/local/beaglert ]; then
		    git clone https://github.com/BelaPlatform/Bela.git
		    $SUDO mv Bela /usr/local/beaglert
		fi

		if [ ! -d /usr/arm-linux-gnueabihf/include/xenomai ]; then
		    # install xenomia (should be downloaded from an official place)
		    wget http://faust.grame.fr/xenomai.tgz || wget http://ifaust.grame.fr/xenomai.tgz
		    tar xzf xenomai.tgz
		    $SUDO mv xenomai /usr/arm-linux-gnueabihf/include/
		fi
	fi

	if [ -n "$INSTALL_ANDROID" ]; then
		# Install Android development tools
		## install java 8
		echo "INSTALL ANDROID SDK AND NDK"
		$SUDO apt install -y openjdk-8-jdk

		## install android sdk
		if [ ! -d /opt/android/sdk ]; then
		    	$SUDO install -d /opt/android/sdk
			if [ ! -e sdk-tools-linux-3859397.zip ]; then
				wget https://dl.google.com/android/repository/sdk-tools-linux-3859397.zip
			fi
			if [ ! -d tools ]; then
				unzip sdk-tools-linux-3859397.zip
			fi
		   	$SUDO ./tools/bin/sdkmanager --sdk_root=/opt/android/sdk "build-tools;25.0.3" "cmake;3.6.4111459" "platforms;android-25" "tools" "ndk-bundle" "extras;android;m2repository"		
			export ANDROID_HOME=/opt/android/sdk
			export ANDROID_NDK_HOME=$ANDROID_HOME/ndk-bundle
			export PATH=$ANDROID_HOME/tools:$ANDROID_HOME/platform-tools:$PATH
			$SUDO ln -s $ANDROID_NDK_HOME /opt/android/ndk
		fi
	fi

	if [ -n "$INSTALL_LATEX" ]; then
		# Install Latex
		echo "INSTALL LATEX"
		$SUDO apt-get install -y texlive-full
	fi

	# Install Faust if needed
	if [ ! -d "faust" ]; then
		git clone https://github.com/grame-cncm/faust.git
	fi
	

	# Update and compile Faust
	cd faust
	git checkout faust2
	git pull
	make world
	$SUDO make install

	echo "Installation Done!"
	echo "Now testing the installation..."
	cd ./tests/architecture-tests
	./testsuccess linux
	echo "Testing Done!"
	cd ..
}

installfaust
