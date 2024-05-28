INSTALLER FOR CHAOS STRATUS PEDAL EFFECTS
-----------------------------------------

This package contains a file of DSP code that you have designed in the Faust 
IDE, its corresponding c++ code ready for compiling for your pedal, an 
installer script, and some ubiquitous utilities that help to access your pedal.

You can use this installer from a standard computer, or directly on the pedal.

PROBABLY you will use your standard computer if you have a UNIX command line 
available in some way on that computer and you are comfortable with that. 
Linux, other UNIXs (e.g. BSD), Macs and even Windows with WSL offer the 
necessary features to permit running the installer.

If that is not the case you must still have access to your pedal from your 
computer, but you can use the pedal itself as your "UNIX" - see below for more.

TL;DR FOR INSTALLING FROM A STANDARD COMPUTER
---------------------------------------------
* Unzip this archive into a suitable folder on your computer
* Bring up a terminal/console whose working directory is that "suitable folder"
* Connect your pedal to your computer by USB
* Run "./install.sh" in the terminal/console
* Enter your pedal's root password when requested.

TL;DR FOR INSTALLING DIRECTLY ON THE PEDAL
------------------------------------------
* Ensure that you have "SCP" and "SSH" available on your standard computer
  This Quora response gives a good summary of the available tools that provide
  these features: https://qr.ae/pscvvo. There are even browser extensions that
  provide these features: e.g. https://chromewebstore.google.com/detail/secure-shell/iodihamcpbpeioajjeobimgagajmlibd

  When setting up sessions with your pedal:

  - The pedal "address" is PROBABLY "stratus.local"
  - The user ID is "root". BE VERY VERY CAREFUL - THIS USER CAN DO ANYTHING!
  - The password will have been communicated to you when you signed up to the 
    developer program

* Connect your pedal to your computer via USB
* Copy the installer zip file to the pedal using SCP or SFTP. Place it in the 
  folder "/root"
* Start an SSH terminal session with your pedal
* Run the following commands in that session:

  cd /root
  mkdir effect-installer
  cd effect-installer
  unzip ../<install-package-file-name>
  ./install.sh
  cd /root
  rm -rf effect-installer

NEXT STEPS
----------
If everything goes according to plan, your effect will be compiled suitably 
for your pedal, and it will be installed on your pedal IF the DSP file used 
to generate the c++ file has the effect's UUID declared as the "stratusId" 
metadata item.

Now test your effect without upsetting those who live with, or near, you!

SOME DETAIL
-----------

(Note that comments concerning docker do not apply to installations performed
directly on the pedal).

If you have "docker" installed, the build will occur in a docker container. 
If you don't want the installer to use docker, pass the '-nodocker' argument 
to the script - your effect will be built directly on your pedal - which is 
MUCH slower than the docker container, but that's your choice.

You can, in fact, use this installer to install ANY effect on your pedal!
You do that by running the install command as follows:

  ./install.sh <your DSP file> <your c++ file> <where you want the local copy of your SO file>

And, again, if you want to avoid using docker even if it is installed, then 
pass '-nodocker' as the first command line argument, followed by those three.

If you just want to BUILD your effect for the pedal, but not install it, then 
comment out the "${PEDAL_INSTALL}" command in the script.

And, finally, if you have the latest Faust installed, then forget this script 
for anything other than simply installing the package contents! Instead use 
'faust2stratus' for everything else - it's far more powerful. Discover its 
options by running 'faust2stratus -h'.