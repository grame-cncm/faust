#!/bin/sh

usage() {
    name=$1
    shift
    args=$*
    echo "Usage: $name $args"
}

platform() {
    echo "Target platform: $*"
}

require() {
    echo "Require: $*"
}

options() {
    while [ "$1" ]
    do
        option "$1"
        shift
    done
}

option() {
    if [ $# -ne 0 ]
    then
        option="$1"
        shift
        doc=$*
        if [ -z "$doc" ]
        then
            case $option in
                "-dyn") doc="create libfaust + LLVM backend dynamic version";;
                "-httpd") doc="activates HTTP control";;
                "-osc") doc="activates OSC control";;
                "-midi") doc="activates MIDI control";;
                "-qrcode") doc="activates QR code generation";;
                "-poly") doc="produces a polyphonic DSP, ready to be used with MIDI events";;
                "-nvoices <num>") doc="produces a polyphonic DSP with <num> voices, ready to be used with MIDI events";;
                "-sr <num>") doc="to specify sample rate";;
                "-bs <num>") doc="to specify buffer size";;
                "-us <factor>") doc="upsample the DSP by a factor";;
                "-ds <factor>") doc="downsample the DSP by a factor";;
                "-filter <filter>") doc="use a filter for upsampling or downsampling [0..4]";;
                "-cpp_path <path>") doc="to set C++ export folder";;
                "-cpp_filename <filename>") doc="to set C++ export filename";;
                "-source") doc="to only create the source folder";;
                "-soundfile") doc="when compiling a DSP using the 'soundfile' primitive, add required resources";;
                "-nodeploy") doc="skip self-contained application generation (using 'macdeployqt')";;
                "-effect <effect.dsp>") doc="generates a polyphonic DSP connected to a global output effect, ready to be used with MIDI or OSC";;
                "-effect auto") doc="generates a polyphonic DSP connected to a global output effect defined as 'effect' in <file.dsp>, ready to be used with MIDI or OSC";;
                "Faust options") doc="any option (e.g. -vec -vs 8...). See the Faust compiler documentation.";;
            esac
        fi
        echo "   $option : $doc"
    else
        echo "Options:"
    fi
}

# Check if a DSP has MIDI control, looking for the [midi:on] option in the JSON file
hasMidi() {
    cat $1 | jq -r '.meta[] | select(.options?) | .options | contains("[midi:on]")'
}

# Get the number of voices of a polyphonic DSP, looking for the [nvoices:<num>] option in the JSON file
getNvoices() {
    cat $1 | jq -r '.meta[] | select(.options?) | .options | capture("\\[nvoices:(?<nvoices>\\d+)\\]") | .nvoices'
}
