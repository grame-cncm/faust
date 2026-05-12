#!/usr/bin/env bash

# Benchmark primitives.
#
# This file is meant to be sourced by script/source.sh.
# It assumes that source.sh has already initialized BENCH_* paths and defaults.
#
# Public entrypoints:
#
#   bench_case <lang> <sample_rate> <buffer_size> <dsp...>
#   bench_full <lang> <dsp...>
#
# Both entrypoints are fresh runs: they clean the report, run the benchmark,
# regenerate the plot, and remove temporary generated files unless
# BENCH_KEEP_TMP=1.

# -----------------------------------------------------------------------------
# Generic validation/helpers
# -----------------------------------------------------------------------------

bench_require_lang() {
  local lang="$1"

  case "${lang}" in
    cpp|mojo|all)
      return 0
      ;;
    *)
      echo "error: unsupported benchmark language: ${lang}"
      echo "supported languages: cpp, mojo, all"
      return 1
      ;;
  esac
}

bench_require_precision() {
  local precision="$1"

  case "${precision}" in
    f32|f64)
      return 0
      ;;
    *)
      echo "error: unsupported precision: ${precision}"
      echo "supported precisions: f32, f64"
      return 1
      ;;
  esac
}

bench_require_dsp_count() {
  local count="$1"

  if (( count == 0 )); then
    echo "error: missing DSP input"
    return 1
  fi
}

bench_case_banner() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local precision="$4"
  local samp_rate="$5"
  local buff_size="$6"
  local write_csv="$7"

  local name
  name="$(bench_dsp_name "${dsp}")"

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running ${lang}:${bench_case}(${name}, ${precision}, sr=${samp_rate}, bs=${buff_size}, csv=${write_csv})"
}

# -----------------------------------------------------------------------------
# Cleanup
# -----------------------------------------------------------------------------

bench_clean_tabs() {
  local lang="$1"

  if [[ "${lang}" == "all" ]]; then
    local one_lang
    for one_lang in "${BENCH_LANGS[@]}"; do
      bench_clean_tabs "${one_lang}"
    done
    return 0
  fi

  find "${BENCH_REPORT_DIR}/${lang}" \
    -maxdepth 1 \
    -type f \
    -name "*.tab" \
    -delete 2>/dev/null || true
}

bench_clean_report() {
  rm -f "${BENCH_CSV}"

  find "${BENCH_TMP_DIR}" \
    -maxdepth 1 \
    -type f \
    -name "*.csv" \
    -delete 2>/dev/null || true

  bench_clean_tabs all

  find "${BENCH_PLOT_DIR}" \
    -maxdepth 1 \
    -type f \
    -name "*.svg" \
    -delete 2>/dev/null || true
}

# -----------------------------------------------------------------------------
# Source generation dispatch
# -----------------------------------------------------------------------------

bench_generate() {
  local lang="$1"
  local dsp="$2"

  bench_require_lang "${lang}" || return 1

  case "${lang}" in
    cpp)
      bench_generate_cpp "${dsp}"
      ;;
    mojo)
      bench_generate_mojo "${dsp}"
      ;;
    all)
      local one_lang
      for one_lang in "${BENCH_LANGS[@]}"; do
        bench_generate "${one_lang}" "${dsp}" || return 1
      done
      ;;
  esac
}

# -----------------------------------------------------------------------------
# C++ backend
# -----------------------------------------------------------------------------

bench_precision_cpp_macro() {
  local precision="$1"

  case "${precision}" in
    f32) echo "float" ;;
    f64) echo "double" ;;
    *)
      echo "error: unsupported C++ precision: ${precision}" >&2
      return 1
      ;;
  esac
}

bench_generate_cpp() {
  local dsp="$1"
  local dsp_path
  local cpp_src

  dsp_path="$(bench_dsp_path "${dsp}")"
  cpp_src="$(bench_cpp_src "${dsp}")"

  mkdir -p "$(dirname "${cpp_src}")"

  "${BENCH_FAUST_BIN}" \
    -lang cpp \
    -a "${BENCH_CPP_ARCH_DIR}/bench.cpp" \
    "${dsp_path}" \
    -o "${cpp_src}"
}

_bench_one_cpp() {
  local dsp="$1"
  local bench_case="$2"
  local precision="$3"
  local samp_rate="$4"
  local buff_size="$5"
  local write_csv="${6:-0}"
  shift 6 || true

  bench_require_precision "${precision}" || return 1

  local cpp_src
  local cpp_bin
  local report
  local csv_path
  local faust_float

  cpp_src="$(bench_cpp_src "${dsp}")"
  cpp_bin="$(bench_cpp_bin "${dsp}")"
  report="$(bench_tab_path cpp "${dsp}" "${bench_case}" "${precision}" "${samp_rate}" "${buff_size}")"
  csv_path="$(bench_tmp_csv_path cpp "${dsp}" "${bench_case}")"
  faust_float="$(bench_precision_cpp_macro "${precision}")"

  if [[ ! -f "${cpp_src}" ]]; then
    echo "error: missing C++ source: ${cpp_src}"
    return 1
  fi

  mkdir -p "$(dirname "${report}")" "$(dirname "${cpp_bin}")" "$(dirname "${csv_path}")"

  bench_case_banner cpp "${dsp}" "${bench_case}" "${precision}" "${samp_rate}" "${buff_size}" "${write_csv}"

  (
    clang++ -std=gnu++23 \
      -I"${BENCH_CPP_ARCH_DIR}" \
      "${BENCH_CPP_OPT[@]}" \
      "$@" \
      -DBENCH_LANG=\"cpp\" \
      -DBENCH_CASE=\"${bench_case}\" \
      -DFAUSTFLOAT="${faust_float}" \
      -DWRITE_CSV="${write_csv}" \
      -DCSV_PATH=\"${csv_path}\" \
      -DFILL_INPUTS=1 \
      -DSAMP_RATE="s32(${samp_rate})" \
      -DBUFF_SIZE="s32(${buff_size})" \
      -DWARMUP_ITERS="${BENCH_WARMUP_ITERS}" \
      -DCOMPUTE_ITERS="${BENCH_COMPUTE_ITERS}" \
      -Wall -Wextra -Wno-unused-parameter -pedantic \
      -o "${cpp_bin}" "${cpp_src}" \
      && "${cpp_bin}"
  ) &> "${report}"
  local case_status=$?

  cat "${report}"
  echo "------------------------------------"
  echo

  return "${case_status}"
}

# -----------------------------------------------------------------------------
# Mojo backend
# -----------------------------------------------------------------------------

bench_precision_mojo_dtype() {
  local precision="$1"

  case "${precision}" in
    f32) echo "DType.float32" ;;
    f64) echo "DType.float64" ;;
    *)
      echo "error: unsupported Mojo precision: ${precision}" >&2
      return 1
      ;;
  esac
}

bench_generate_mojo() {
  local dsp="$1"
  local dsp_path
  local mojo_src

  dsp_path="$(bench_dsp_path "${dsp}")"
  mojo_src="$(bench_mojo_src "${dsp}")"

  mkdir -p "$(dirname "${mojo_src}")"

  "${BENCH_FAUST_BIN}" \
    -lang mojo \
    -a "${BENCH_MOJO_ARCH_DIR}/bench.mojo" \
    "${dsp_path}" \
    -o "${mojo_src}"
}

_bench_one_mojo() {
  local dsp="$1"
  local bench_case="$2"
  local precision="$3"
  local samp_rate="$4"
  local buff_size="$5"
  local write_csv="${6:-0}"
  shift 6 || true

  bench_require_precision "${precision}" || return 1

  local mojo_src
  local mojo_bin
  local report
  local csv_path
  local dtype

  mojo_src="$(bench_mojo_src "${dsp}")"
  mojo_bin="$(bench_mojo_bin "${dsp}")"
  report="$(bench_tab_path mojo "${dsp}" "${bench_case}" "${precision}" "${samp_rate}" "${buff_size}")"
  csv_path="$(bench_tmp_csv_path mojo "${dsp}" "${bench_case}")"
  dtype="$(bench_precision_mojo_dtype "${precision}")"

  if [[ ! -f "${mojo_src}" ]]; then
    echo "error: missing Mojo source: ${mojo_src}"
    return 1
  fi

  mkdir -p "$(dirname "${report}")" "$(dirname "${mojo_bin}")" "$(dirname "${csv_path}")"

  bench_case_banner mojo "${dsp}" "${bench_case}" "${precision}" "${samp_rate}" "${buff_size}" "${write_csv}"

  (
    pixi run mojo build \
      "${BENCH_MOJO_OPT[@]}" \
      "$@" \
      -D BENCH_LANG=mojo \
      -D BENCH_CASE="${bench_case}" \
      -D FAUST_DTYPE="${dtype}" \
      -D WRITE_CSV="${write_csv}" \
      -D CSV_PATH="${csv_path}" \
      -D FILL_INPUTS=True \
      -D SAMP_RATE="${samp_rate}" \
      -D BUFF_SIZE="${buff_size}" \
      -D WARMUP_ITERS="${BENCH_WARMUP_ITERS}" \
      -D COMPUTE_ITERS="${BENCH_COMPUTE_ITERS}" \
      -o "${mojo_bin}" "${mojo_src}" \
      && "${mojo_bin}"
  ) &> "${report}"
  local case_status=$?

  cat "${report}"
  echo "------------------------------------"
  echo

  return "${case_status}"
}

# -----------------------------------------------------------------------------
# You can add a new backend above this line
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Atomic single-precision dispatch
# -----------------------------------------------------------------------------

bench_one() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local precision="$4"
  local samp_rate="$5"
  local buff_size="$6"
  local write_csv="${7:-0}"
  shift 7 || true

  bench_require_lang "${lang}" || return 1

  case "${lang}" in
    cpp)
      _bench_one_cpp "${dsp}" "${bench_case}" "${precision}" "${samp_rate}" "${buff_size}" "${write_csv}" "$@"
      ;;
    mojo)
      _bench_one_mojo "${dsp}" "${bench_case}" "${precision}" "${samp_rate}" "${buff_size}" "${write_csv}" "$@"
      ;;
    all)
      local one_lang
      for one_lang in "${BENCH_LANGS[@]}"; do
        bench_one "${one_lang}" "${dsp}" "${bench_case}" "${precision}" "${samp_rate}" "${buff_size}" "${write_csv}" "$@" || return 1
      done
      ;;
  esac
}

# -----------------------------------------------------------------------------
# Internal run helpers
# -----------------------------------------------------------------------------

_bench_prepare_csv() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"

  if [[ "${lang}" == "all" ]]; then
    local one_lang
    for one_lang in "${BENCH_LANGS[@]}"; do
      _bench_prepare_csv "${one_lang}" "${dsp}" "${bench_case}" || return 1
    done
    return 0
  fi

  local csv_path
  csv_path="$(bench_tmp_csv_path "${lang}" "${dsp}" "${bench_case}")"

  mkdir -p "$(dirname "${csv_path}")"
  rm -f "${csv_path}"
}

_bench_commit_csv() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"

  if [[ "${lang}" == "all" ]]; then
    local one_lang
    for one_lang in "${BENCH_LANGS[@]}"; do
      _bench_commit_csv "${one_lang}" "${dsp}" "${bench_case}" || return 1
    done
    return 0
  fi

  bench_csv_merge "${lang}" "${dsp}" "${bench_case}"
}

_bench_fixed_for_dsp() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local samp_rate="$4"
  local buff_size="$5"
  shift 5 || true

  bench_require_lang "${lang}" || return 1

  _bench_prepare_csv "${lang}" "${dsp}" "${bench_case}" || return 1

  local precision
  for precision in "${BENCH_PRECISIONS[@]}"; do
    bench_one \
      "${lang}" \
      "${dsp}" \
      "${bench_case}" \
      "${precision}" \
      "${samp_rate}" \
      "${buff_size}" \
      1 \
      "$@" || return 1
  done

  _bench_commit_csv "${lang}" "${dsp}" "${bench_case}"
}

_bench_grid_for_dsp() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  shift 3 || true

  bench_require_lang "${lang}" || return 1

  _bench_prepare_csv "${lang}" "${dsp}" "${bench_case}" || return 1

  local samp_rate
  local buff_size
  local precision

  for samp_rate in "${BENCH_SAMPLE_RATES[@]}"; do
    for buff_size in "${BENCH_BUFFER_SIZES[@]}"; do
      for precision in "${BENCH_PRECISIONS[@]}"; do
        bench_one \
          "${lang}" \
          "${dsp}" \
          "${bench_case}" \
          "${precision}" \
          "${samp_rate}" \
          "${buff_size}" \
          1 \
          "$@" || return 1
      done
    done
  done

  _bench_commit_csv "${lang}" "${dsp}" "${bench_case}"
}

# -----------------------------------------------------------------------------
# Public fresh entrypoints
# -----------------------------------------------------------------------------

bench_case() {
  local lang="$1"
  local samp_rate="$2"
  local buff_size="$3"
  shift 3 || true

  bench_require_lang "${lang}" || return 1
  bench_require_dsp_count "$#" || return 1

  local bench_case="full"

  bench_clean_report

  local dsp
  for dsp in "$@"; do
    bench_generate "${lang}" "${dsp}" || return 1
    _bench_fixed_for_dsp "${lang}" "${dsp}" "${bench_case}" "${samp_rate}" "${buff_size}" || return 1
    bench_clean_tmp_files "${dsp}"
  done

  bench_plot "${BENCH_CSV}"
}

bench_full() {
  local lang="$1"
  shift || true

  bench_require_lang "${lang}" || return 1
  bench_require_dsp_count "$#" || return 1

  local bench_case="full"

  bench_clean_report

  local dsp
  for dsp in "$@"; do
    bench_generate "${lang}" "${dsp}" || return 1
    _bench_grid_for_dsp "${lang}" "${dsp}" "${bench_case}" || return 1
    bench_clean_tmp_files "${dsp}"
  done

  bench_plot "${BENCH_CSV}"
}
