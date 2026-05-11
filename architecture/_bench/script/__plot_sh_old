#!/usr/bin/env bash

# Standard benchmark plots.
#
# This file may be executed directly or sourced through script/source.sh.
# It assumes the benchmark workspace layout initialized by source.sh.

bench_plot() {
  local csv_src="${1:-${BENCH_CSV}}"

  mkdir -p "${BENCH_PLOT_DIR}"

  pixi run python "${BENCH_SCRIPT_DIR}/plot.py" "${csv_src}" \
    --case buffer_sweep \
    --x buff_size \
    --y output_samples_per_s \
    --series language,precision,opt \
    --out "${BENCH_PLOT_DIR}/tput_bs.svg" \
    --title "Faust Benchmark"

  pixi run python "${BENCH_SCRIPT_DIR}/plot.py" "${csv_src}" \
    --case sample_rate_sweep \
    --x samp_rate \
    --y output_samples_per_s \
    --series language,precision,opt \
    --out "${BENCH_PLOT_DIR}/tput_sr.svg" \
    --title "Faust Benchmark"
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  # shellcheck source=/dev/null
  source "${SCRIPT_DIR}/source.sh"

  bench_plot "$@"
fi
