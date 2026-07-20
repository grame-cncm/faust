#!/usr/bin/env bash
set -euo pipefail

src="$1"
out="${2:-$src}"

$HOME/Personal/dev/repo/faust/build/bin/faust \
    -double -vec -vs 4 -dfs -lang mojo \
    -a impulse.mojo \
    "src/$src.dsp" \
    -o "$out.mojo"
