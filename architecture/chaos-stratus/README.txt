INSTALLER FOR CHAOS STRATUS PEDAL EFFECTS
-----------------------------------------

This package contains a file of DSP code that you have designed in the Faust IDE, 
its corresponding c++ code ready for compiling for your pedal, an installer script
and some ubiquitous utilities that help to access your pedal.

TL;DR - DO THE FOLLOWING:

* Unzip this archive in a suitable folder on your computer
* Bring up a terminal/console who's working directory
  is that "suitable folder"
* Connect your pedal to your computer by USB
* Run "./install.sh" in the terminal/console
* Enter you pedal's root password when requested.

If everything goes according to plan, your effect will be compiled suitably for
your pedal, and it will be installed on your pedal IF the DSP file used to generate
the CPP file has the effect's UUID declared as the "stratusId" metadata item.

Now test your effect without upsetting those who live with, or near, you!

SOME DETAIL
-----------

If you have "docker" installed, the build will occur in a docker container. If
you don't want the installer to use docker, pass the '-nodocker' argument to
the script - your effect will be built directly on your pedal - which is MUCH 
slower than the docker container, but that's your choice.

You can, in fact, use this installer to install ANY effect on your pedal!
You do that by running the install command as follows:

    ./install.sh <your DSP file> <your CPP file> <where you want the local copy of your SO file>

And, again, if you want to avoid using docker even if it is installed, then pass '-nodocker'
as the first command line argument, followed by those three.

If you just want to BUILD you effect for the pedal, but not install it, then comment out
the "installOnStratus" command in the script.

And, finally, if you have the latest Faust installed, then forget this script for anything
other than simply installing the package contents! Instead use 'faust2stratus' for everything
else - it's far more powerful. Find out its options by running 'faust2stratus -h'.