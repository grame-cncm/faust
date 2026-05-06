#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo "usage: $0 <cpp-source> [extra-cpp-flags...]"
  exit 1
fi

CPP_SRC="$1"
shift

COMMON_FLAGS=("$@")
CPP_BIN="report/cpp/bench_bin"
CSV_OUT="report/cpp/report.csv"

WARMUP_ITERS=100
COMPUTE_ITERS=100000

BUFFER_SWEEP_SAMP_RATE=96000
BUFFER_SIZES=(
  16
  32
  64
  128
  256
  512
  1024
  2048
)

SAMPLE_RATE_SWEEP_BUFF_SIZE=128
SAMPLE_RATES=(
  44100
  48000
  96000
  192000
)

rm -f report/cpp/*.tab
rm -f "${CSV_OUT}"
rm -f "${CPP_BIN}"
mkdir -p report/cpp/

run_case() {
  local bench_case="$1"
  local precision="$2"
  local opt="$3"
  local samp_rate="$4"
  local buff_size="$5"
  local report="$6"
  shift 6

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running ${bench_case}(${precision}, ${opt}, sr=${samp_rate}, bs=${buff_size})"
  (
    clang++ -std=gnu++23 \
      "${COMMON_FLAGS[@]}" \
      "$@" \
      -DBENCH_LANG=\"cpp\" \
      -DBENCH_CASE=\"${bench_case}\" \
      -DBENCH_OPTIM=\"${opt}\" \
      -DCSV_PATH=\"${CSV_OUT}\" \
      -DFILL_INPUTS=1 \
      -DSAMP_RATE="s32(${samp_rate})" \
      -DBUFF_SIZE="s32(${buff_size})" \
      -DWARMUP_ITERS="${WARMUP_ITERS}" \
      -DCOMPUTE_ITERS="${COMPUTE_ITERS}" \
      -Wall -Wextra -Wno-unused-parameter -pedantic "-${opt}" \
      -o "${CPP_BIN}" "${CPP_SRC}" \
      && "./${CPP_BIN}"
  ) &> "${report}"

  cat "${report}"
  echo "------------------------------------"
  echo
}

run_matrix() {
  local bench_case="$1"
  local samp_rate="$2"
  local buff_size="$3"
  local suffix="$4"

  run_case "${bench_case}" "f32" "O0" "${samp_rate}" "${buff_size}" \
    "report/cpp/${suffix}_f32_O0.tab" \
    -DFAUSTFLOAT=r32

  run_case "${bench_case}" "f32" "O3" "${samp_rate}" "${buff_size}" \
    "report/cpp/${suffix}_f32_O3.tab" \
    -DFAUSTFLOAT=r32

  run_case "${bench_case}" "f64" "O0" "${samp_rate}" "${buff_size}" \
    "report/cpp/${suffix}_f64_O0.tab" \
    -DFAUSTFLOAT=r64

  run_case "${bench_case}" "f64" "O3" "${samp_rate}" "${buff_size}" \
    "report/cpp/${suffix}_f64_O3.tab" \
    -DFAUSTFLOAT=r64
}

for buff_size in "${BUFFER_SIZES[@]}"; do
  run_matrix \
    "buffer_sweep" \
    "${BUFFER_SWEEP_SAMP_RATE}" \
    "${buff_size}" \
    "buf_bs${buff_size}"
done

for samp_rate in "${SAMPLE_RATES[@]}"; do
  run_matrix \
    "sample_rate_sweep" \
    "${samp_rate}" \
    "${SAMPLE_RATE_SWEEP_BUFF_SIZE}" \
    "sr_sr${samp_rate}"
done

rm -f "${CPP_BIN}"
