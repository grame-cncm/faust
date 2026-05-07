#!/usr/bin/env bash

# Benchmark primitives.
#
# This file is meant to be sourced by script/source.sh.
# It assumes that source.sh has already initialized BENCH_* paths and defaults.

# -----------------------------------------------------------------------------
# Internal helpers
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

bench_require_opt() {
  local opt="$1"

  case "${opt}" in
    O0|O1|O2|O3)
      return 0
      ;;
    *)
      echo "error: unsupported optimization level: ${opt}"
      echo "supported optimization levels: O0, O1, O2, O3"
      return 1
      ;;
  esac
}

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

bench_case_banner() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local precision="$4"
  local opt="$5"
  local samp_rate="$6"
  local buff_size="$7"
  local write_csv="$8"

  local name
  name="$(bench_dsp_name "${dsp}")"

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running ${lang}:${bench_case}(${name}, ${precision}, ${opt}, sr=${samp_rate}, bs=${buff_size}, csv=${write_csv})"
}

# -----------------------------------------------------------------------------
# Single-case implementations
# -----------------------------------------------------------------------------

_bench_case_cpp() {
  local dsp="$1"
  local bench_case="$2"
  local precision="$3"
  local opt="$4"
  local samp_rate="$5"
  local buff_size="$6"
  local write_csv="${7:-0}"
  shift 7 || true

  bench_require_precision "${precision}" || return 1
  bench_require_opt "${opt}" || return 1

  local cpp_src
  local cpp_bin
  local report
  local csv_path
  local faust_float

  cpp_src="$(bench_cpp_src "${dsp}")"
  cpp_bin="$(bench_cpp_bin "${dsp}")"
  report="$(bench_tab_path cpp "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}")"
  csv_path="$(bench_tmp_csv_path cpp "${dsp}" "${bench_case}")"
  faust_float="$(bench_precision_cpp_macro "${precision}")"

  if [[ ! -f "${cpp_src}" ]]; then
    echo "error: missing C++ source: ${cpp_src}"
    return 1
  fi

  mkdir -p "$(dirname "${report}")" "$(dirname "${cpp_bin}")" "$(dirname "${csv_path}")"

  bench_case_banner cpp "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}" "${write_csv}"

  (
    clang++ -std=gnu++23 \
      -I"${BENCH_CPP_ARCH_DIR}" \
      "$@" \
      -DBENCH_LANG=\"cpp\" \
      -DBENCH_CASE=\"${bench_case}\" \
      -DBENCH_OPTIM=\"${opt}\" \
      -DFAUSTFLOAT="${faust_float}" \
      -DWRITE_CSV="${write_csv}" \
      -DCSV_PATH=\"${csv_path}\" \
      -DFILL_INPUTS=1 \
      -DSAMP_RATE="s32(${samp_rate})" \
      -DBUFF_SIZE="s32(${buff_size})" \
      -DWARMUP_ITERS="${BENCH_WARMUP_ITERS}" \
      -DCOMPUTE_ITERS="${BENCH_COMPUTE_ITERS}" \
      -Wall -Wextra -Wno-unused-parameter -pedantic "-${opt}" \
      -o "${cpp_bin}" "${cpp_src}" \
      && "${cpp_bin}"
  ) &> "${report}"

  cat "${report}"
  echo "------------------------------------"
  echo
}

_bench_case_mojo() {
  local dsp="$1"
  local bench_case="$2"
  local precision="$3"
  local opt="$4"
  local samp_rate="$5"
  local buff_size="$6"
  local write_csv="${7:-0}"
  shift 7 || true

  bench_require_precision "${precision}" || return 1
  bench_require_opt "${opt}" || return 1

  local mojo_src
  local mojo_bin
  local report
  local csv_path
  local dtype
  local opt_level

  mojo_src="$(bench_mojo_src "${dsp}")"
  mojo_bin="$(bench_mojo_bin "${dsp}")"
  report="$(bench_tab_path mojo "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}")"
  csv_path="$(bench_tmp_csv_path mojo "${dsp}" "${bench_case}")"
  dtype="$(bench_precision_mojo_dtype "${precision}")"
  opt_level="${opt#O}"

  if [[ ! -f "${mojo_src}" ]]; then
    echo "error: missing Mojo source: ${mojo_src}"
    return 1
  fi

  mkdir -p "$(dirname "${report}")" "$(dirname "${mojo_bin}")" "$(dirname "${csv_path}")"

  bench_case_banner mojo "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}" "${write_csv}"

  (
    pixi run mojo build -O "${opt_level}" \
      "$@" \
      -D BENCH_LANG=mojo \
      -D BENCH_CASE="${bench_case}" \
      -D BENCH_OPTIM="${opt}" \
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

  cat "${report}"
  echo "------------------------------------"
  echo
}

# -----------------------------------------------------------------------------
# Public single-case primitive
# -----------------------------------------------------------------------------

bench_case() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local precision="$4"
  local opt="$5"
  local samp_rate="$6"
  local buff_size="$7"
  local write_csv="${8:-0}"
  shift 8 || true

  bench_require_lang "${lang}" || return 1

  case "${lang}" in
    cpp)
      _bench_case_cpp "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}" "${write_csv}" "$@"
      ;;
    mojo)
      _bench_case_mojo "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}" "${write_csv}" "$@"
      ;;
    all)
      _bench_case_cpp "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}" "${write_csv}" "$@"
      _bench_case_mojo "${dsp}" "${bench_case}" "${precision}" "${opt}" "${samp_rate}" "${buff_size}" "${write_csv}" "$@"
      ;;
  esac
}

# -----------------------------------------------------------------------------
# Matrix and sweeps
# -----------------------------------------------------------------------------

bench_matrix() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"
  local samp_rate="$4"
  local buff_size="$5"
  local write_csv="${6:-0}"
  shift 6 || true

  bench_require_lang "${lang}" || return 1

  local precision
  local opt

  for precision in "${BENCH_PRECISIONS[@]}"; do
    for opt in "${BENCH_OPT_LEVELS[@]}"; do
      bench_case \
        "${lang}" \
        "${dsp}" \
        "${bench_case}" \
        "${precision}" \
        "${opt}" \
        "${samp_rate}" \
        "${buff_size}" \
        "${write_csv}" \
        "$@"
    done
  done
}

bench_bs_sweep() {
  local lang="$1"
  local dsp="$2"
  shift 2 || true

  bench_require_lang "${lang}" || return 1

  local bench_case="buffer_sweep"
  local buff_size

  bench_prepare_sweep_csv "${lang}" "${dsp}" "${bench_case}"

  for buff_size in "${BENCH_BUFFER_SIZES[@]}"; do
    bench_matrix \
      "${lang}" \
      "${dsp}" \
      "${bench_case}" \
      "${BENCH_BUFFER_SWEEP_SAMP_RATE}" \
      "${buff_size}" \
      1 \
      "$@"
  done

  bench_commit_sweep_csv "${lang}" "${dsp}" "${bench_case}"
}

bench_sr_sweep() {
  local lang="$1"
  local dsp="$2"
  shift 2 || true

  bench_require_lang "${lang}" || return 1

  local bench_case="sample_rate_sweep"
  local samp_rate

  bench_prepare_sweep_csv "${lang}" "${dsp}" "${bench_case}"

  for samp_rate in "${BENCH_SAMPLE_RATES[@]}"; do
    bench_matrix \
      "${lang}" \
      "${dsp}" \
      "${bench_case}" \
      "${samp_rate}" \
      "${BENCH_SAMPLE_RATE_SWEEP_BUFF_SIZE}" \
      1 \
      "$@"
  done

  bench_merge_sweep_csv "${lang}" "${dsp}" "${bench_case}"
}

bench_all() {
  local lang="$1"
  local dsp="$2"
  shift 2 || true

  bench_require_lang "${lang}" || return 1

  bench_bs_sweep "${lang}" "${dsp}" "$@"
  bench_sr_sweep "${lang}" "${dsp}" "$@"
}

# -----------------------------------------------------------------------------
# CSV hooks
# -----------------------------------------------------------------------------

bench_prepare_sweep_csv() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"

  if [[ "${lang}" == "all" ]]; then
    local one_lang
    for one_lang in "${BENCH_LANGS[@]}"; do
      bench_prepare_sweep_csv "${one_lang}" "${dsp}" "${bench_case}"
    done
    return 0
  fi

  local csv_path
  csv_path="$(bench_tmp_csv_path "${lang}" "${dsp}" "${bench_case}")"

  mkdir -p "$(dirname "${csv_path}")"
  rm -f "${csv_path}"
}

bench_commit_sweep_csv() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"

  if declare -F bench_csv_merge >/dev/null; then
    bench_csv_merge "${lang}" "${dsp}" "${bench_case}"
    return $?
  fi

  echo "error: bench_csv_merge is not available"
  return 1
}
