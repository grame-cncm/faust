#!/bin/bash

FAUST=faust
CXX=g++
ARCHITECTURE=minimal.cpp

while true; do
    case "$1" in
      -c|--cxx) CXX=$2; shift 2;;
      -f|--faust) FAUST=$2; shift 2;;
      -a|--arch) ARCHITECTURE=$2; shift 2;;
      -m|--mode) MODE=$2; shift 2;;

      *)  break;;
    esac
done

FILE=$1

GENERATED=$(tempfile).cpp
$FAUST -a $ARCHITECTURE $MODE -o $GENERATED $FILE || exit $?

$CXX -c $GENERATED || exit $?
rm $GENERATED
rm -rf ${GENERATED/.cpp/.o}
