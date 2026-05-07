#!/usr/bin/env bash

# This file is meant to be sourced from the benchmark root:
#
#   source script/source.sh
#
# It initializes paths, benchmark defaults, required directories, and helper
# functions. It does not run benchmarks and does not modify report data.

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  echo "source this file instead of executing it:"
  echo "  source script/source.sh"
  exit 1
fi

# -----------------------------------------------------------------------------
# Root paths
# -----------------------------------------------------------------------------

BENCH_SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BENCH_ROOT="$(cd "${BENCH_SCRIPT_DIR}/.." && pwd)"

BENCH_SRC_DIR="${BENCH_ROOT}/src"
BENCH_ARCH_DIR="${BENCH_ROOT}/arch"
BENCH_CPP_ARCH_DIR="${BENCH_ARCH_DIR}/cpp"
BENCH_MOJO_ARCH_LINK="${BENCH_ARCH_DIR}/mojo"

BENCH_OUT_DIR="${BENCH_ROOT}/out"
BENCH_CPP_OUT_DIR="${BENCH_OUT_DIR}/cpp"
BENCH_MOJO_OUT_DIR="${BENCH_OUT_DIR}/mojo"

BENCH_BIN_DIR="${BENCH_ROOT}/bin"

BENCH_REPORT_DIR="${BENCH_ROOT}/report"
BENCH_CPP_REPORT_DIR="${BENCH_REPORT_DIR}/cpp"
BENCH_MOJO_REPORT_DIR="${BENCH_REPORT_DIR}/mojo"
BENCH_PLOT_DIR="${BENCH_REPORT_DIR}/plots"
BENCH_TMP_DIR="${BENCH_REPORT_DIR}/tmp"

BENCH_CSV="${BENCH_REPORT_DIR}/report.csv"

# -----------------------------------------------------------------------------
# Tool paths
# -----------------------------------------------------------------------------

BENCH_FAUST_BIN="${BENCH_FAUST_BIN:-${BENCH_ROOT}/../../build/bin/faust}"

# -----------------------------------------------------------------------------
# Benchmark defaults
# -----------------------------------------------------------------------------

BENCH_WARMUP_ITERS="${BENCH_WARMUP_ITERS:-100}"
BENCH_COMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-100000}"

BENCH_BUFFER_SWEEP_SAMP_RATE="${BENCH_BUFFER_SWEEP_SAMP_RATE:-96000}"
BENCH_SAMPLE_RATE_SWEEP_BUFF_SIZE="${BENCH_SAMPLE_RATE_SWEEP_BUFF_SIZE:-128}"

BENCH_BUFFER_SIZES=(
  16
  32
  64
  128
  256
  512
  1024
  2048
)

BENCH_SAMPLE_RATES=(
  44100
  48000
  96000
  192000
)

BENCH_LANGS=(
  cpp
  mojo
)

BENCH_PRECISIONS=(
  f32
  f64
)

BENCH_OPT_LEVELS=(
  O0
  O3
)

# -----------------------------------------------------------------------------
# Initialization
# -----------------------------------------------------------------------------

bench_require_pixi() {
  if [[ -z "${PIXI_ENVIRONMENT_NAME:-}" ]]; then
    echo "error: pixi environment is not active."
    echo "run first:"
    echo "  pixi shell"
    return 1
  fi
}

bench_make_dirs() {
  mkdir -p \
    "${BENCH_SRC_DIR}" \
    "${BENCH_CPP_ARCH_DIR}" \
    "${BENCH_OUT_DIR}" \
    "${BENCH_CPP_OUT_DIR}" \
    "${BENCH_BIN_DIR}" \
    "${BENCH_REPORT_DIR}" \
    "${BENCH_CPP_REPORT_DIR}" \
    "${BENCH_MOJO_REPORT_DIR}" \
    "${BENCH_PLOT_DIR}" \
    "${BENCH_TMP_DIR}"
}

bench_ensure_mojo_link() {
  local expected_target="../../mojo"

  if [[ -L "${BENCH_MOJO_ARCH_LINK}" ]]; then
    local actual_target
    actual_target="$(readlink "${BENCH_MOJO_ARCH_LINK}")"

    if [[ "${actual_target}" != "${expected_target}" ]]; then
      echo "error: ${BENCH_MOJO_ARCH_LINK} points to ${actual_target}, expected ${expected_target}"
      return 1
    fi

    return 0
  fi

  if [[ -e "${BENCH_MOJO_ARCH_LINK}" ]]; then
    echo "error: ${BENCH_MOJO_ARCH_LINK} exists but is not a symlink"
    return 1
  fi

  ln -s "${expected_target}" "${BENCH_MOJO_ARCH_LINK}"
}

bench_init() {
  bench_require_pixi || return 1
  bench_make_dirs
  bench_ensure_mojo_link || return 1
}

# -----------------------------------------------------------------------------
# Path helpers
# -----------------------------------------------------------------------------

bench_dsp_name() {
  local input="$1"
  local base
  base="$(basename "${input}")"
  echo "${base%.dsp}"
}

bench_dsp_path() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_SRC_DIR}/${name}.dsp"
}

bench_cpp_src() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_CPP_OUT_DIR}/${name}.cpp"
}

bench_mojo_src() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_MOJO_OUT_DIR}/${name}.mojo"
}

bench_cpp_bin() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_BIN_DIR}/${name}_cpp"
}

bench_mojo_bin() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_BIN_DIR}/${name}_mojo"
}

bench_tab_path() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local precision="$4"
  local opt="$5"
  local samp_rate="$6"
  local buff_size="$7"

  local name
  name="$(bench_dsp_name "${dsp}")"

  echo "${BENCH_REPORT_DIR}/${lang}/${bench_case}_${name}_${precision}_${opt}_sr${samp_rate}_bs${buff_size}.tab"
}

bench_tmp_csv_path() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"

  local name
  name="$(bench_dsp_name "${dsp}")"

  echo "${BENCH_TMP_DIR}/${lang}_${name}_${bench_case}.csv"
}

# -----------------------------------------------------------------------------
# Script loading
# -----------------------------------------------------------------------------

bench_source_optional() {
  local file="$1"

  if [[ -f "${file}" ]]; then
    # shellcheck source=/dev/null
    source "${file}"
  fi
}

bench_load_scripts() {
  bench_source_optional "${BENCH_SCRIPT_DIR}/csv.sh"
  bench_source_optional "${BENCH_SCRIPT_DIR}/bench.sh"
  bench_source_optional "${BENCH_SCRIPT_DIR}/plot.sh"
  bench_source_optional "${BENCH_SCRIPT_DIR}/clean.sh"
}

bench_init
bench_load_scripts
