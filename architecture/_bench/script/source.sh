#!/usr/bin/env bash

# Benchmark framework initialization.
#
# This file is meant to be sourced from the benchmark root:
#
#   source script/source.sh
#
# It initializes paths, defaults, directories, and loads the benchmark API.

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  echo "source this file instead of executing it:"
  echo "  source script/source.sh"
  exit 1
fi

# ==========================================
# Root paths
# ==========================================

if [[ -n "${BASH_SOURCE[0]:-}" ]]; then
  BENCH_SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
else
  BENCH_SCRIPT_DIR="$(cd "$(dirname "${(%):-%x}")" && pwd)"
fi

if ! declare -p BENCH_FAUST_OPT >/dev/null 2>&1; then
  BENCH_FAUST_OPT=()
fi

BENCH_ROOT="$(cd "${BENCH_SCRIPT_DIR}/.." && pwd)"
BENCH_FAUST_ROOT="$(cd "${BENCH_ROOT}/../.." && pwd)"
BENCH_FAUST_BIN="${BENCH_FAUST_BIN:-${BENCH_FAUST_ROOT}/build/bin/faust}"

BENCH_SRC_DIR="${BENCH_ROOT}/src"
BENCH_ARCH_DIR="${BENCH_ROOT}/arch"

BENCH_REPORT_DIR="${BENCH_ROOT}/report"
BENCH_BIN_DIR="${BENCH_REPORT_DIR}/bin"
BENCH_TAB_DIR="${BENCH_REPORT_DIR}/tab"
BENCH_PLOT_DIR="${BENCH_REPORT_DIR}/plot"
BENCH_SNAP_DIR="${BENCH_REPORT_DIR}/snap"
BENCH_TMP_DIR="${BENCH_REPORT_DIR}/tmp"

BENCH_MOJO_ARCH_DIR="${BENCH_ARCH_DIR}/mojo"
BENCH_CPP_ARCH_DIR="${BENCH_ARCH_DIR}/cpp"

BENCH_CSV="${BENCH_REPORT_DIR}/report.csv"
BENCH_KEEP_TMP="${BENCH_KEEP_TMP:-0}"
BENCH_JOBS="${BENCH_JOBS:-10}"

# ==========================================
# Benchmark defaults
# ==========================================

BENCH_LANGS=(
  cpp
  mojo
)

BENCH_MODES=(
  scalar
  vec
)

# Fixed precision profile: internal DSP math is f64, architecture I/O is f32.
BENCH_INTERNAL_PRECISION="double"
BENCH_EXTERNAL_PRECISION="float32"
BENCH_CPP_FAUSTFLOAT="float"
BENCH_MOJO_FAUST_DTYPE="DType.float32"

BENCH_SAMPLE_RATES=(
  48000
  192000
)

BENCH_BUFFER_SIZES=(
  64
  512
)

if ! declare -p BENCH_FAUST_SCALAR_OPT >/dev/null 2>&1; then
  BENCH_FAUST_SCALAR_OPT=()
fi

if ! declare -p BENCH_FAUST_VEC_OPT >/dev/null 2>&1; then
  BENCH_FAUST_VEC_OPT=(
    -vec -vs 4 -dfs
  )
fi

BENCH_WARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}"
BENCH_COMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-1000000}"

BENCH_MIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}"
BENCH_MAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}"
BENCH_MAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}"

# ==========================================
# Compiler options
# ==========================================

BENCH_CPP_OPT=(
  -O3
  # -march=native
  # -mtune=native
  # -flto
  # -ffast-math
  # -fno-math-errno
  # -fstrict-aliasing
)

BENCH_MOJO_OPT=(
  -O3
  # --target-cpu apple-m4
)

# ==========================================
# Initialization helpers
# ==========================================

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
    "${BENCH_BIN_DIR}" \
    "${BENCH_BIN_DIR}/cpp" \
    "${BENCH_BIN_DIR}/mojo" \
    "${BENCH_TAB_DIR}" \
    "${BENCH_TAB_DIR}/cpp" \
    "${BENCH_TAB_DIR}/mojo" \
    "${BENCH_PLOT_DIR}" \
    "${BENCH_SNAP_DIR}" \
    "${BENCH_TMP_DIR}" \
    "${BENCH_REPORT_DIR}/llvm/cpp" \
    "${BENCH_REPORT_DIR}/llvm/mojo" \
    "${BENCH_REPORT_DIR}/asm/cpp" \
    "${BENCH_REPORT_DIR}/asm/mojo"
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

bench_load_api() {
  # shellcheck source=/dev/null
  source "${BENCH_SCRIPT_DIR}/bench.sh"
}

bench_init() {
  bench_require_pixi || return 1
  bench_make_dirs
  bench_ensure_mojo_link || return 1
  bench_load_api
}

# ==========================================
# Initialize
# ==========================================

bench_init || return 1

echo
echo "Faust benchmark framework initialized."
echo
echo "Main commands:"
echo
echo "  bench_clean"
echo "      Remove current CSV, temporary CSV fragments, tab reports, binaries, and plots."
echo "      Use this explicitly when you want a fresh benchmark report state."
echo
echo "  bench_run vec all all all all"
echo "      Incremental run over all configured languages, sample rates, buffer sizes, and DSP sources in vec mode."
echo "      Existing CSV rows are preserved unless the same benchmark identity is run again."
echo
echo "  bench_run scalar all 48 64 all"
echo "      Incremental run for all languages at 48 kHz / buffer size 64 in scalar mode."
echo
echo "  bench_run vec mojo 48 64 bells"
echo "      Incremental run for Mojo only on one DSP in vec mode."
echo
echo "  bench_run scalar cpp,mojo 48,192 64,512 carre_volterra"
echo "      Incremental run for selected languages, sample rates, buffer sizes, and one DSP in scalar mode."
echo
echo "  bench_plot compare_modes"
echo "      Generate report/plot/compare_modes.svg from report/report.csv."
echo
echo "  bench_snapshot after_changes"
echo "      Save the current report state under report/snap/."
echo
echo "  inspect_llvm scalar all carre_volterra"
echo "      Generate LLVM IR using the inspect architecture in scalar mode."
echo
echo "  inspect_asm vec all carre_volterra"
echo "      Generate target assembly using the inspect architecture in vec mode."
echo
echo "Argument notes:"
echo
echo "  modes:"
echo "      scalar or vec."
echo
echo "  languages:"
echo "      all or comma-separated entries from BENCH_LANGS."
echo
echo "  sample rates:"
echo "      passed in kHz; 48 means 48000 Hz, 192 means 192000 Hz."
echo "      use all for BENCH_SAMPLE_RATES."
echo
echo "  buffer sizes:"
echo "      integer values, comma-separated values, or all."
echo
echo "  sources:"
echo "      all, DSP names, DSP paths, or shell-expanded globs."
echo
echo "Fixed precision profile:"
echo "      internal Faust precision: ${BENCH_INTERNAL_PRECISION}."
echo "      external FAUSTFLOAT / dfaust: ${BENCH_EXTERNAL_PRECISION}."
echo
echo "Useful overrides:"
echo
echo "  BENCH_KEEP_TMP=1"
echo "  BENCH_JOBS=10"
echo "  BENCH_SAMPLE_RATES=(48000 192000)"
echo "  BENCH_BUFFER_SIZES=(64 512)"
echo "  BENCH_WARMUP_ITERS=50"
echo "  BENCH_COMPUTE_ITERS=1000000"
echo "  BENCH_MIN_RUNTIME_SECS=1"
echo "  BENCH_MAX_RUNTIME_SECS=60"
echo "  BENCH_MAX_BATCH_SIZE=10000"
echo "  BENCH_FAUST_SCALAR_OPT=(...)"
echo "  BENCH_FAUST_VEC_OPT=(...)"
