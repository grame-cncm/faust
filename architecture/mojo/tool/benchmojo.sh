#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo "usage: $0 <mojo-source> [extra-mojo-flags...]"
  exit 1
fi

MOJO_SRC="$1"
shift

COMMON_FLAGS=("$@")
MOJO_BIN="report/mojo/bench_bin"
CSV_OUT="report/mojo/report.csv"

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

rm -f report/mojo/*.tab
rm -f "${CSV_OUT}"
rm -f "${MOJO_BIN}"
mkdir -p report/mojo/

run_case() {
  local bench_case="$1"
  local precision="$2"
  local dtype="$3"
  local opt="$4"
  local samp_rate="$5"
  local buff_size="$6"
  local report="$7"
  local opt_level="${opt#O}"
  shift 7

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running ${bench_case}(${precision}, ${opt}, sr=${samp_rate}, bs=${buff_size})"
  (
    pixi run mojo build -O "${opt_level}" \
      "${COMMON_FLAGS[@]}" \
      "$@" \
      -D BENCH_LANG=mojo \
      -D BENCH_CASE="${bench_case}" \
      -D BENCH_OPTIM="${opt}" \
      -D FAUST_DTYPE="${dtype}" \
      -D CSV_PATH="${CSV_OUT}" \
      -D FILL_INPUTS=True \
      -D SAMP_RATE="${samp_rate}" \
      -D BUFF_SIZE="${buff_size}" \
      -D WARMUP_ITERS="${WARMUP_ITERS}" \
      -D COMPUTE_ITERS="${COMPUTE_ITERS}" \
      -o "${MOJO_BIN}" "${MOJO_SRC}" \
      && "./${MOJO_BIN}"
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

  run_case "${bench_case}" "f32" "DType.float32" "O0" "${samp_rate}" "${buff_size}" \
    "report/mojo/${suffix}_f32_O0.tab"

  run_case "${bench_case}" "f32" "DType.float32" "O3" "${samp_rate}" "${buff_size}" \
    "report/mojo/${suffix}_f32_O3.tab"

  run_case "${bench_case}" "f64" "DType.float64" "O0" "${samp_rate}" "${buff_size}" \
    "report/mojo/${suffix}_f64_O0.tab"

  run_case "${bench_case}" "f64" "DType.float64" "O3" "${samp_rate}" "${buff_size}" \
    "report/mojo/${suffix}_f64_O3.tab"
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

rm -f "${MOJO_BIN}"
