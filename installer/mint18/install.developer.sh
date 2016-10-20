#!/bin/bash
set -e

function installfaust {
	# Install 'Installation directory' if needed
	if [ ! -d ~/FaustInstall ]; then
		mkdir ~/FaustInstall
	fi
	cd ~/FaustInstall

	SUDO=`which sudo`

	echo "Updating packages..."
	$SUDO apt-get -y update
	echo "Installing Faust dependencies..."
	$SUDO apt-get install -y build-essential pkg-config git libmicrohttpd-dev llvm-3.6 llvm-3.6-dev libssl-dev ncurses-dev libsndfile-dev libedit-dev libcurl4-openssl-dev valgrind

	# Install all the needed SDK
	$SUDO apt-get install -y libgtk2.0-dev libasound2-dev jackd2 libjack-jackd2-dev libqrencode-dev qjackctl
	$SUDO apt-get install -y qt4-default libcsound64-dev dssi-dev lv2-dev puredata-dev supercollider-dev wget unzip libboost-dev
	$SUDO apt-get install -y inkscape graphviz

    # install QT5 for faust2faustvst
    $SUDO apt-get install -y qtbase5-dev qt5-qmake libqt5x11extras5-dev
	if [ ! -e /usr/bin/qmake-qt5 ]; then
    	$SUDO ln -s /usr/lib/x86_64-linux-gnu/qt5/bin/qmake /usr/bin/qmake-qt5
	fi

	# Install faust2pd from Albert Greaf Pure-lang PPA
	$SUDO apt-get install -y software-properties-common
	$SUDO add-apt-repository -y ppa:dr-graef/pure-lang.xenial
	$SUDO apt-get -y update
	$SUDO apt-get install -y faust2pd

	# Install pd.dll needed to cross compile pd externals for windows
    if [ ! -d /usr/include/pd/pd.dll ]; then
        wget http://faust.grame.fr/pd.dll
        $SUDO mv pd.dll /usr/include/pd/
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
	wget https://cycling74.com/download/max-sdk-7.1.0.zip
	unzip max-sdk-7.1.0.zip
	$SUDO cp -r max-sdk-7.1.0/source/c74support /usr/local/include/

	# Install ROS Jade
	#$SUDO sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
	#$SUDO apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 0xB01FA116
	#$SUDO apt-get -y update
	#$SUDO apt-get install -y ros-jade-ros-base


	# Install Bela
	$SUDO apt-get install -y gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
    if [ ! -d /usr/local/beaglert ]; then
        git clone https://github.com/BelaPlatform/Bela.git
        $SUDO mv Bela /usr/local/beaglert
    fi

    if [ ! -d /usr/arm-linux-gnueabihf/include/xenomai ]; then
        # install xenomia (should be downloaded from an official place)
        wget http://faust.grame.fr/xenomai.tgz
        tar xzf xenomai.tgz
        $SUDO mv xenomai /usr/arm-linux-gnueabihf/include/
    fi


	# Install Android development tools
	## install java 8
    $SUDO apt install -y openjdk-8-jdk

	## install android sdk
    if [ ! -d /opt/android ]; then
        $SUDO install -d /opt/android

        if [ ! -f android-sdk_r24.4.1-linux.tgz ]; then
            wget https://dl.google.com/android/android-sdk_r24.4.1-linux.tgz
        fi
        if [ ! -d /opt/android/sdk ]; then
            tar -xzf android-sdk_r24.4.1-linux.tgz
            $SUDO mv android-sdk-linux/ /opt/android/sdk
        fi

        ## install android ndk
        if [ ! -f android-ndk-r12-linux-x86_64.zip ]; then
            wget https://dl.google.com/android/repository/android-ndk-r12-linux-x86_64.zip
        fi

        if [ ! -d /opt/android/ndk ]; then
            unzip -q android-ndk-r12-linux-x86_64.zip
            $SUDO mv android-ndk-r12 /opt/android/ndk
        fi

        export PATH="/opt/android/sdk/tools:/opt/android/sdk/platform-tools:/opt/android/ndk:$PATH"
        echo y | android update sdk --no-ui -a --filter tools,platform-tools,android-24,build-tools-24.0.0
    fi

	# Install Latex
    $SUDO apt-get install -y texlive-full

	# Install Faust if needed
	if [ ! -d "faust" ]; then
		git clone http://git.code.sf.net/p/faudiostream/code faust
	fi

	# Update and compile Faust		
	cd faust
	git checkout faust2
	git pull
	make world
	$SUDO make install
	cd ..

	echo "Installation Done!"
}

installfaust


