#!/bin/bash

# created by Facundo Franchino

#####################################################################
#                                                                   #
#                        faust2clap generator                       #
#                (c) Grame & Facundo Franchino, 2025               #
#                                                                   #
#####################################################################

# wrapper for faust2clap.py
# runs the script from its actual location (not from /usr/local/bin)

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do
  DIR="$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)"
  SOURCE="$(readlink "$SOURCE")"
  [[ "$SOURCE" != /* ]] && SOURCE="$DIR/$SOURCE"
done
SCRIPT_DIR="$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)"
python3 "${SCRIPT_DIR}/faust2clap.py" "$@"
