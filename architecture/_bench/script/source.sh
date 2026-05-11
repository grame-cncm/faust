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

if [[ -n "${BASH_SOURCE[0]:-}" ]]; then
  BENCH_SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
else
  BENCH_SCRIPT_DIR="$(cd "$(dirname "${(%):-%x}")" && pwd)"
fi

BENCH_ROOT="$(cd "${BENCH_SCRIPT_DIR}/.." && pwd)"
BENCH_FAUST_ROOT="$(cd "${BENCH_ROOT}/../.." && pwd)"
BENCH_FAUST_BIN="${BENCH_FAUST_BIN:-${BENCH_FAUST_ROOT}/build/bin/faust}"

BENCH_SRC_DIR="${BENCH_ROOT}/src"
BENCH_ARCH_DIR="${BENCH_ROOT}/arch"

BENCH_REPORT_DIR="${BENCH_ROOT}/report"
BENCH_PLOT_DIR="${BENCH_REPORT_DIR}/plots"
BENCH_TMP_DIR="${BENCH_REPORT_DIR}/tmp"

BENCH_MOJO_ARCH_DIR="${BENCH_ARCH_DIR}/mojo"
BENCH_MOJO_REPORT_DIR="${BENCH_REPORT_DIR}/mojo"

BENCH_CPP_ARCH_DIR="${BENCH_ARCH_DIR}/cpp"
BENCH_CPP_REPORT_DIR="${BENCH_REPORT_DIR}/cpp"

BENCH_CSV="${BENCH_REPORT_DIR}/report.csv"

BENCH_KEEP_TMP="${BENCH_KEEP_TMP:-0}"

# -----------------------------------------------------------------------------
# Benchmark defaults
# -----------------------------------------------------------------------------

BENCH_WARMUP_ITERS="${BENCH_WARMUP_ITERS:-100}"
BENCH_COMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-100000}"

BENCH_BUFFER_SIZES=(
  64
  512
)

BENCH_SAMPLE_RATES=(
  48000
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

BENCH_CPP_OPT=(
  -O3
  -march=native
  -mtune=native
  -flto
  -ffast-math
  -fno-math-errno
  -fstrict-aliasing
)

BENCH_MOJO_OPT=(
  -O 3
  # --target-cpu apple-m4
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
    "${BENCH_REPORT_DIR}" \
    "${BENCH_CPP_REPORT_DIR}" \
    "${BENCH_MOJO_REPORT_DIR}" \
    "${BENCH_PLOT_DIR}" \
    "${BENCH_TMP_DIR}"
}

bench_ensure_mojo_link() {
  local expected_target="../../mojo"

  if [[ -L "${BENCH_MOJO_ARCH_DIR}" ]]; then
    local actual_target
    actual_target="$(readlink "${BENCH_MOJO_ARCH_DIR}")"

    if [[ "${actual_target}" != "${expected_target}" ]]; then
      echo "error: ${BENCH_MOJO_ARCH_DIR} points to ${actual_target}, expected ${expected_target}"
      return 1
    fi

    return 0
  fi

  if [[ -e "${BENCH_MOJO_ARCH_DIR}" ]]; then
    echo "error: ${BENCH_MOJO_ARCH_DIR} exists but is not a symlink"
    return 1
  fi

  ln -s "${expected_target}" "${BENCH_MOJO_ARCH_DIR}"
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
  echo "${BENCH_CPP_ARCH_DIR}/${name}.cpp"
}

bench_cpp_bin() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_CPP_ARCH_DIR}/${name}_cpp"
}

bench_mojo_src() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_MOJO_ARCH_DIR}/${name}.mojo"
}

bench_mojo_bin() {
  local name
  name="$(bench_dsp_name "$1")"
  echo "${BENCH_MOJO_ARCH_DIR}/${name}_mojo"
}

bench_clean_tmp_files() {
  if [[ "${BENCH_KEEP_TMP}" == "1" ]]; then
    return 0
  fi
  local name
  name="$(bench_dsp_name "$1")"
  rm -f "${BENCH_CPP_ARCH_DIR}/${name}.cpp"
  rm -f "${BENCH_CPP_ARCH_DIR}/${name}_cpp"
  rm -f "${BENCH_MOJO_ARCH_DIR}/${name}.mojo"
  rm -f "${BENCH_MOJO_ARCH_DIR}/${name}_mojo"
}

bench_tab_path() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local precision="$4"
  local samp_rate="$5"
  local buff_size="$6"

  local sr_khz
  sr_khz="$((samp_rate / 1000))"

  echo "${BENCH_REPORT_DIR}/${lang}/${lang}_${bench_case}_${sr_khz}_${buff_size}_${precision}.tab"
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
  bench_source_optional "${BENCH_SCRIPT_DIR}/csvmanip.sh"
  bench_source_optional "${BENCH_SCRIPT_DIR}/bench.sh"
  bench_source_optional "${BENCH_SCRIPT_DIR}/plot.sh"
  bench_source_optional "${BENCH_SCRIPT_DIR}/clean.sh"
}

bench_init || return 1
bench_load_scripts

echo
echo "Faust benchmark framework initialized."
echo
echo "Main commands:"
echo
echo "  bench_full all hello_sine"
echo "      Run the full benchmark suite for all backends."
echo
echo "  bench_full cpp hello_sine"
echo "      Run the full benchmark suite only for C++."
echo
echo "  bench_full mojo hello_sine"
echo "      Run the full benchmark suite only for Mojo."
echo
echo "  bench_plot"
echo "      Regenerate plots from report/report.csv."
echo
echo "Environment:"
echo
echo "  BENCH_KEEP_TMP=1"
echo "      Keep generated temporary sources and binaries."
echo
echo "See spec.md for the full framework specification."
echo
