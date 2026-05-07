#!/usr/bin/env bash
set -euo pipefail

# Run the full benchmark pipeline for one DSP.
#
# Usage:
#   script/run_all.sh [dsp-name] [language]
#
# Examples:
#   script/run_all.sh
#   script/run_all.sh hello_sine
#   script/run_all.sh hello_sine cpp
#   script/run_all.sh hello_sine mojo
#   script/run_all.sh hello_sine all

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=/dev/null
source "${SCRIPT_DIR}/source.sh"

DSP="${1:-hello_sine}"
LANG="${2:-all}"

bench_require_lang "${LANG}"

bench_all "${LANG}" "${DSP}"
bench_plot "${BENCH_CSV}"
