#!/usr/bin/env bash

function usage() {
	name=$1
	shift
	args=$*
	echo "Usage: $name $args"
}

function platform() {
	echo "Target platform: $*"
}

function require() {
	echo "Require: $*"
}

function options() {
	while [ "$1" ]
	do
		option $1
		shift
	done
}

function option() {
	if [ $# -ne 0 ] 
	then
		option=$1
		shift
		doc=$*
		if [ -z "$doc" ]
		then
			case $option in
				"-httpd") doc=" activates HTTP control";;
				"-osc") doc="   activates OSC control";;
				"-midi") doc="  activates MIDI control";;
				"-qrcode") doc="activates QR code generation";;
				"-poly") doc="  produces a polyphonic DSP, ready to be used with MIDI events";;
				"-nvoices <num>") doc="produces a polyphonic DSP with <num> voices, ready to be used with MIDI events";;
				"-soundfile") doc="when compiling a DSP using the 'soundfile' primitive, add required resources";;
				"-nodeploy") doc="skip self-contained application generation (using 'macdeployqt')";;
       			"-effect <effect.dsp>") doc="generates a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC";;
        		"-effect auto") doc="generates a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI or OSC";;
				"Faust options") doc="any faust option (e.g. -vec -vs 8...). See the faust compiler documentation.";;
			esac
		fi
		echo "   $option : $doc"
	else
#		echo
		echo "Options:"
	fi
}
