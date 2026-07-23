#!/usr/bin/env bash

# Benchmark framework.
#
# This file is meant to be sourced by script/source.sh.
# It assumes that source.sh has already initialized BENCH_* paths and defaults.

# ==========================================
# Public API
# ==========================================

bench_run() {
  if (( $# < 5 )); then
    echo "usage: bench_run <which,modes> <which,langs> <sample,rates,khz> <buffer,sizes> <dsp,sources>"
    return 1
  fi

  if [[ "${BENCH_RUN_IS_TRANSPILED:-0}" == "1" ]]; then
    BENCH_RUN_NAME="run"
  else
    BENCH_RUN_NAME="${BENCH_RUN_NAME:-run}"
  fi

  BENCH_RUN_IS_TRANSPILED=0
  unset BENCH_TRANSPILED_NAME
  unset BENCH_TRANSPILED_DSP
  unset BENCH_TRANSPILED_CASE
  unset BENCH_TRANSPILED_PATH
  unset BENCH_TRANSPILED_ORIGINAL_PATH

  BENCH_LAST_COMMAND="bench_run $*"
  _bench_resolve_args "$@" || return 1
  _bench_run_resolved
}

bench_run_transpiled() {
  if (( $# < 5 )); then
    echo "usage: bench_run_transpiled <mode> <lang> <sample-rate> <buffer-size> <transpiled-path>"
    return 1
  fi

  _bench_resolve_transpiled_args "$@" || return 1

  BENCH_RUN_IS_TRANSPILED=1
  BENCH_RUN_NAME="${BENCH_TRANSPILED_NAME}"
  BENCH_RUN_MODE="${BENCH_TRANSPILED_MODE}"
  BENCH_RUN_MODES=("${BENCH_TRANSPILED_MODE}")
  BENCH_RUN_LANGS=("${BENCH_TRANSPILED_LANG}")
  BENCH_RUN_SAMPLE_RATES=("${BENCH_TRANSPILED_SAMPLE_RATE}")
  BENCH_RUN_BUFFER_SIZES=("${BENCH_TRANSPILED_BUFFER_SIZE}")
  BENCH_RUN_SOURCES=("${BENCH_TRANSPILED_NAME}")
  BENCH_LAST_COMMAND="bench_run_transpiled $*"

  local run_status=0

  _bench_csv_prepare_fragment "${BENCH_TRANSPILED_LANG}" "${BENCH_TRANSPILED_DSP}" || run_status=1
  if (( run_status == 0 )); then
    _bench_build_transpiled_case \
      "${BENCH_TRANSPILED_LANG}" \
      "${BENCH_TRANSPILED_PATH}" \
      "${BENCH_TRANSPILED_DSP}" \
      "${BENCH_TRANSPILED_SAMPLE_RATE}" \
      "${BENCH_TRANSPILED_BUFFER_SIZE}" || run_status=1
  fi
  if (( run_status == 0 )); then
    _bench_exec_case \
      "${BENCH_TRANSPILED_DSP}" \
      "${BENCH_TRANSPILED_LANG}" \
      "${BENCH_TRANSPILED_SAMPLE_RATE}" \
      "${BENCH_TRANSPILED_BUFFER_SIZE}" || run_status=1
  fi
  if (( run_status == 0 )); then
    _bench_csv_commit_fragment "${BENCH_TRANSPILED_LANG}" "${BENCH_TRANSPILED_DSP}" || run_status=1
  fi

  _bench_clean_staged_transpiled
  return "${run_status}"
}

bench_clean() {
  _bench_clean_report || return 1
  echo "cleaned current benchmark reports."
}

bench_plot() {
  local plot_name="$1"
  local case_name="${2:-all}"
  _bench_plot_require_name "${plot_name}" || return 1
  _bench_plot_from_csv "${BENCH_CSV}" "$(_bench_plot_path "${plot_name}")" "${case_name}"
}

bench_snapshot() {
  local snapshot_name="$1"
  _bench_require_non_empty "${snapshot_name}" "snapshot name" || return 1
  local snapshot_path
  snapshot_path="$(_bench_snapshot_path "${snapshot_name}")"
  _bench_snapshot_copy_report "${snapshot_path}" || return 1
  _bench_snapshot_write_meta "${snapshot_path}" "${snapshot_name}"
}

inspect_llvm() {
  if (( $# < 3 )); then
    echo "usage: inspect_llvm <which,modes> <which,langs> <dsp,sources>"
    return 1
  fi
  BENCH_RUN_IS_TRANSPILED=0
  local modes="$1"
  local langs="$2"
  shift 2
  _bench_resolve_modes "${modes}" || return 1
  _bench_resolve_langs "${langs}" || return 1
  _bench_resolve_sources "$@" || return 1
  _inspect_llvm_gen
}

inspect_llvm_transpiled() {
  if (( $# < 5 )); then
    echo "usage: inspect_llvm_transpiled <mode> <lang> <sample-rate> <buffer-size> <transpiled-path>"
    return 1
  fi
  _inspect_transpiled_emit llvm "$@"
}

inspect_asm() {
  if (( $# < 3 )); then
    echo "usage: inspect_asm <which,modes> <which,langs> <dsp,sources>"
    return 1
  fi
  BENCH_RUN_IS_TRANSPILED=0
  local modes="$1"
  local langs="$2"
  shift 2
  _bench_resolve_modes "${modes}" || return 1
  _bench_resolve_langs "${langs}" || return 1
  _bench_resolve_sources "$@" || return 1
  _inspect_asm_gen
}

inspect_asm_transpiled() {
  if (( $# < 5 )); then
    echo "usage: inspect_asm_transpiled <mode> <lang> <sample-rate> <buffer-size> <transpiled-path>"
    return 1
  fi
  _inspect_transpiled_emit asm "$@"
}

# ==========================================
# Validation helpers
# ==========================================

_bench_require_mode() {
  local mode="$1"
  local supported
  for supported in "${BENCH_MODES[@]}"; do
    if [[ "${mode}" == "${supported}" ]]; then
      return 0
    fi
  done
  echo "error: unsupported benchmark mode: ${mode}"
  echo "supported modes: ${BENCH_MODES[*]}"
  return 1
}

_bench_require_lang() {
  local lang="$1"
  local supported
  for supported in "${BENCH_LANGS[@]}"; do
    if [[ "${lang}" == "${supported}" ]]; then
      return 0
    fi
  done
  echo "error: unsupported benchmark language: ${lang}"
  echo "supported languages: ${BENCH_LANGS[*]}"
  return 1
}

_bench_require_non_empty() {
  local value="$1"
  local what="$2"
  if [[ -z "${value}" ]]; then
    echo "error: missing ${what}"
    return 1
  fi
}

_bench_require_file() {
  local path="$1"
  if [[ ! -f "${path}" ]]; then
    echo "error: missing file: ${path}"
    return 1
  fi
}

_bench_normalize_sample_rate() {
  local item="$1"
  local value
  if ! [[ "${item}" =~ ^[0-9]+$ ]]; then
    echo "error: invalid sample rate: ${item}" >&2
    return 1
  fi
  if (( item < 1000 )); then
    value=$((item * 1000))
  else
    value="${item}"
  fi
  echo "${value}"
}

# ==========================================
# Argument resolution
# ==========================================

_bench_resolve_args() {
  local modes="$1"
  local langs="$2"
  local sample_rates="$3"
  local buffer_sizes="$4"
  shift 4

  _bench_resolve_modes "${modes}" || return 1
  _bench_resolve_langs "${langs}" || return 1
  _bench_resolve_sample_rates "${sample_rates}" || return 1
  _bench_resolve_buffer_sizes "${buffer_sizes}" || return 1
  _bench_resolve_sources "$@" || return 1
}

_bench_resolve_modes() {
  local spec="$1"
  local item
  BENCH_RUN_MODES=()

  if [[ "${spec}" == "all" ]]; then
    for item in "${BENCH_MODES[@]}"; do
      BENCH_RUN_MODES+=("${item}")
    done
    return 0
  fi

  for item in $(printf "%s" "${spec}" | tr ',' ' '); do
    _bench_require_mode "${item}" || return 1
    BENCH_RUN_MODES+=("${item}")
  done

  _bench_require_non_empty "${BENCH_RUN_MODES[*]}" "resolved modes"
}

_bench_resolve_langs() {
  local spec="$1"
  local item
  BENCH_RUN_LANGS=()

  if [[ "${spec}" == "all" ]]; then
    for item in "${BENCH_LANGS[@]}"; do
      BENCH_RUN_LANGS+=("${item}")
    done
    return 0
  fi

  for item in $(printf "%s" "${spec}" | tr ',' ' '); do
    _bench_require_lang "${item}" || return 1
    BENCH_RUN_LANGS+=("${item}")
  done

  _bench_require_non_empty "${BENCH_RUN_LANGS[*]}" "resolved languages"
}

_bench_resolve_sample_rates() {
  local spec="$1"
  local item
  local value
  BENCH_RUN_SAMPLE_RATES=()
  if [[ "${spec}" == "all" ]]; then
    for item in "${BENCH_SAMPLE_RATES[@]}"; do
      BENCH_RUN_SAMPLE_RATES+=("${item}")
    done
    return 0
  fi
  for item in $(printf "%s" "${spec}" | tr ',' ' '); do
    value="$(_bench_normalize_sample_rate "${item}")" || return 1
    BENCH_RUN_SAMPLE_RATES+=("${value}")
  done
  _bench_require_non_empty "${BENCH_RUN_SAMPLE_RATES[*]}" "resolved sample rates"
}

_bench_resolve_buffer_sizes() {
  local spec="$1"
  local item
  BENCH_RUN_BUFFER_SIZES=()
  if [[ "${spec}" == "all" ]]; then
    for item in "${BENCH_BUFFER_SIZES[@]}"; do
      BENCH_RUN_BUFFER_SIZES+=("${item}")
    done
    return 0
  fi
  for item in $(printf "%s" "${spec}" | tr ',' ' '); do
    if ! [[ "${item}" =~ ^[0-9]+$ ]]; then
      echo "error: invalid buffer size: ${item}"
      return 1
    fi
    BENCH_RUN_BUFFER_SIZES+=("${item}")
  done
  _bench_require_non_empty "${BENCH_RUN_BUFFER_SIZES[*]}" "resolved buffer sizes"
}

_bench_resolve_sources() {
  local source
  local item
  BENCH_RUN_SOURCES=()
  if (( $# == 1 )) && [[ "$1" == "all" ]]; then
    for source in "${BENCH_SRC_DIR}"/*.dsp; do
      if [[ -f "${source}" ]]; then
        BENCH_RUN_SOURCES+=("${source}")
      fi
    done
    return 0
  fi
  for source in "$@"; do
    if [[ "${source}" == "all" ]]; then
      for item in "${BENCH_SRC_DIR}"/*.dsp; do
        if [[ -f "${item}" ]]; then
          BENCH_RUN_SOURCES+=("${item}")
        fi
      done
      continue
    fi
    for item in $(printf "%s" "${source}" | tr ',' ' '); do
      BENCH_RUN_SOURCES+=("${item}")
    done
  done
  _bench_require_non_empty "${BENCH_RUN_SOURCES[*]}" "resolved sources"
}

# ==========================================
# Path helpers
# ==========================================

_bench_dsp_name() {
  local input="$1"
  local base
  base="$(basename "${input}")"
  echo "${base%.dsp}"
}

_bench_dsp_path() {
  local input="$1"
  local name
  if [[ -f "${input}" ]]; then
    echo "${input}"
    return 0
  fi
  name="$(_bench_dsp_name "${input}")"
  echo "${BENCH_SRC_DIR}/${name}.dsp"
}

_bench_current_mode() {
  echo "${BENCH_RUN_MODE:-scalar}"
}

_bench_case_stem() {
  local lang="$1"
  local dsp="$2"
  local samp_rate="$3"
  local buff_size="$4"
  local name
  local mode
  local sr_khz

  name="$(_bench_dsp_name "${dsp}")"
  mode="$(_bench_current_mode)"
  sr_khz="$((samp_rate / 1000))"

  if [[ "${BENCH_RUN_IS_TRANSPILED:-0}" == "1" ]]; then
    echo "${lang}_${BENCH_TRANSPILED_NAME}_${mode}_${sr_khz}_${buff_size}"
    return 0
  fi

  echo "${lang}_${name}_${BENCH_RUN_NAME}_${mode}_${sr_khz}_${buff_size}"
}

_bench_case_bin() {
  local lang="$1"
  local dsp="$2"
  local samp_rate="$3"
  local buff_size="$4"
  local stem
  stem="$(_bench_case_stem "${lang}" "${dsp}" "${samp_rate}" "${buff_size}")"

  case "${lang}" in
    cpp)
      echo "${BENCH_BIN_DIR}/cpp/${stem}_bin_cpp"
      ;;
    mojo)
      echo "${BENCH_BIN_DIR}/mojo/${stem}_bin_mojo"
      ;;
    *)
      echo "error: unsupported binary language: ${lang}" >&2
      return 1
      ;;
  esac
}

_bench_case_build_log() {
  local lang="$1"
  local dsp="$2"
  local samp_rate="$3"
  local buff_size="$4"
  local stem
  stem="$(_bench_case_stem "${lang}" "${dsp}" "${samp_rate}" "${buff_size}")"
  echo "${BENCH_TMP_DIR}/${stem}.build.log"
}

_bench_cpp_out() {
  local name
  local mode
  name="$(_bench_dsp_name "$1")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_CPP_ARCH_DIR}/${name}_${mode}_transpiled.cpp"
}

_bench_mojo_out() {
  local name
  local mode
  name="$(_bench_dsp_name "$1")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_MOJO_ARCH_DIR}/${name}_${mode}_transpiled.mojo"
}

_inspect_cpp_out() {
  local name
  local mode
  name="$(_bench_dsp_name "$1")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_CPP_ARCH_DIR}/${name}_${mode}_insp.cpp"
}

_inspect_mojo_out() {
  local name
  local mode
  name="$(_bench_dsp_name "$1")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_MOJO_ARCH_DIR}/${name}_${mode}_insp.mojo"
}

_inspect_cpp_llvm() {
  local name="$1"
  local mode
  name="$(_bench_dsp_name "${name}")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_REPORT_DIR}/llvm/cpp/${name}_${mode}.ll"
}

_inspect_mojo_llvm() {
  local name="$1"
  local mode
  name="$(_bench_dsp_name "${name}")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_REPORT_DIR}/llvm/mojo/${name}_${mode}.ll"
}

_inspect_cpp_asm() {
  local name="$1"
  local mode
  name="$(_bench_dsp_name "${name}")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_REPORT_DIR}/asm/cpp/${name}_${mode}.s"
}

_inspect_mojo_asm() {
  local name="$1"
  local mode
  name="$(_bench_dsp_name "${name}")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_REPORT_DIR}/asm/mojo/${name}_${mode}.s"
}

_bench_tab_path() {
  local lang="$1"
  local dsp="$2"
  local samp_rate="$3"
  local buff_size="$4"
  local name
  local mode
  local sr_khz

  name="$(_bench_dsp_name "${dsp}")"
  mode="$(_bench_current_mode)"
  sr_khz="$((samp_rate / 1000))"

  if [[ "${BENCH_RUN_IS_TRANSPILED:-0}" == "1" ]]; then
    echo "${BENCH_TAB_DIR}/${lang}/${lang}_${BENCH_TRANSPILED_NAME}_${mode}_${sr_khz}_${buff_size}.tab"
    return 0
  fi

  echo "${BENCH_TAB_DIR}/${lang}/${lang}_${name}_${BENCH_RUN_NAME}_${mode}_${sr_khz}_${buff_size}.tab"
}

_bench_tmp_csv_path() {
  local lang="$1"
  local dsp="$2"
  local name
  local mode

  if [[ "${BENCH_RUN_IS_TRANSPILED:-0}" == "1" ]]; then
    echo "${BENCH_TMP_DIR}/${BENCH_TRANSPILED_NAME}.csv"
    return 0
  fi

  name="$(_bench_dsp_name "${dsp}")"
  mode="$(_bench_current_mode)"
  echo "${BENCH_TMP_DIR}/${lang}_${name}_${BENCH_RUN_NAME}_${mode}.csv"
}

_bench_plot_path() {
  local name="$1"
  name="${name%.svg}"
  echo "${BENCH_PLOT_DIR}/${name}.svg"
}

_bench_snapshot_path() {
  local name="$1"
  local stamp
  local safe_name
  stamp="$(date "+%Y-%m-%d_%H%M")"
  safe_name="$(_bench_snapshot_name "${name}")"
  echo "${BENCH_SNAP_DIR}/${stamp}_${safe_name}"
}

# ==========================================
# Cleanup
# ==========================================

_bench_clean_report() {
  rm -f "${BENCH_CSV}"
  _bench_clean_tmp_csv
  _bench_clean_tabs all
  _bench_clean_bins
  _bench_clean_plots
  _bench_clean_inspect_artifacts
  _bench_clean_all_out_files
}

_bench_clean_tmp_csv() {
  find "${BENCH_TMP_DIR}" \
    -maxdepth 1 \
    -type f \
    -name "*.csv" \
    -delete 2>/dev/null || true
  find "${BENCH_TMP_DIR}" \
    -maxdepth 1 \
    -type f \
    -name "*.build.log" \
    -delete 2>/dev/null || true
}

_bench_clean_tabs() {
  local lang="$1"
  local one_lang
  if [[ "${lang}" == "all" ]]; then
    for one_lang in "${BENCH_LANGS[@]}"; do
      _bench_clean_tabs "${one_lang}"
    done
    return 0
  fi
  find "${BENCH_TAB_DIR}/${lang}" \
    -maxdepth 1 \
    -type f \
    -name "*.tab" \
    -delete 2>/dev/null || true
}

_bench_clean_bins() {
  find "${BENCH_BIN_DIR}" \
    -mindepth 1 \
    -type f \
    \( -name "*_bin_cpp" -o -name "*_bin_mojo" \) \
    -delete 2>/dev/null || true
}

_bench_clean_plots() {
  find "${BENCH_PLOT_DIR}" \
    -maxdepth 1 \
    -type f \
    -name "*.svg" \
    -delete 2>/dev/null || true
}

_bench_clean_inspect_artifacts() {
  find "${BENCH_REPORT_DIR}/llvm" \
    -mindepth 2 \
    -type f \
    -delete 2>/dev/null || true
  find "${BENCH_REPORT_DIR}/asm" \
    -mindepth 2 \
    -type f \
    -delete 2>/dev/null || true
}

_bench_clean_all_out_files() {
  if [[ "${BENCH_KEEP_TMP}" == "1" ]]; then
    return 0
  fi
  find "${BENCH_CPP_ARCH_DIR}" \
    -maxdepth 1 \
    -type f \
    \( -name "*_transpiled.cpp" -o -name "*_insp.cpp" \) \
    -delete 2>/dev/null || true
  find -H "${BENCH_MOJO_ARCH_DIR}" \
    -maxdepth 1 \
    -type f \
    \( -name "*_transpiled.mojo" -o -name "*_insp.mojo" \) \
    -delete 2>/dev/null || true
}

_bench_clean_generated_source() {
  local lang="$1"
  local source="$2"
  local name
  local mode

  if [[ "${BENCH_KEEP_TMP}" == "1" ]]; then
    return 0
  fi

  name="$(_bench_dsp_name "${source}")"
  mode="$(_bench_current_mode)"

  case "${lang}" in
    cpp)
      rm -f "${BENCH_CPP_ARCH_DIR}/${name}_${mode}_transpiled.cpp"
      ;;
    mojo)
      rm -f "${BENCH_MOJO_ARCH_DIR}/${name}_${mode}_transpiled.mojo"
      ;;
  esac
}

_inspect_clean_generated_source() {
  local lang="$1"
  local source="$2"
  local name
  local mode

  if [[ "${BENCH_KEEP_TMP}" == "1" ]]; then
    return 0
  fi

  name="$(_bench_dsp_name "${source}")"
  mode="$(_bench_current_mode)"

  case "${lang}" in
    cpp)
      rm -f "${BENCH_CPP_ARCH_DIR}/${name}_${mode}_insp.cpp"
      ;;
    mojo)
      rm -f "${BENCH_MOJO_ARCH_DIR}/${name}_${mode}_insp.mojo"
      ;;
  esac
}

# ==========================================
# CSV helpers
# ==========================================

_bench_csv_prepare_fragment() {
  local lang="$1"
  local source="$2"
  local csv_path
  csv_path="$(_bench_tmp_csv_path "${lang}" "${source}")"
  mkdir -p "$(dirname "${csv_path}")"
  rm -f "${csv_path}"
}

_bench_csv_commit_fragment() {
  local lang="$1"
  local source="$2"
  _bench_csv_merge_fragment "${lang}" "${source}"
}

_bench_csv_merge_fragment() {
  local lang="$1"
  local source="$2"
  local tmp_csv
  local name
  tmp_csv="$(_bench_tmp_csv_path "${lang}" "${source}")"
  name="$(_bench_dsp_name "${source}")"
  if [[ ! -f "${tmp_csv}" ]]; then
    echo "error: missing temporary CSV fragment: ${tmp_csv}"
    if [[ "${BENCH_RUN_IS_TRANSPILED:-0}" == "1" ]]; then
      echo "note: bench_run_transpiled expects the transpiled file to use the benchmark architecture and write CSV_PATH when WRITE_CSV=True."
      echo "note: use inspect_asm_transpiled or inspect_llvm_transpiled for inspect-only transpiled files."
    fi
    return 1
  fi
  pixi run python "${BENCH_SCRIPT_DIR}/csvmanip.py" merge \
    --main "${BENCH_CSV}" \
    --tmp "${tmp_csv}" \
    --language "${lang}" \
    --dsp "${name}" \
    --case "${BENCH_RUN_NAME}" \
    --mode "$(_bench_current_mode)"
}

# ==========================================
# Faust mode helpers
# ==========================================

_bench_set_faust_mode_opt() {
  local mode="$1"
  BENCH_FAUST_MODE_OPT=()
  case "${mode}" in
    scalar)
      BENCH_FAUST_MODE_OPT+=("${BENCH_FAUST_SCALAR_OPT[@]}")
      ;;
    vec)
      BENCH_FAUST_MODE_OPT+=("${BENCH_FAUST_VEC_OPT[@]}")
      ;;
    *)
      echo "error: no Faust options for benchmark mode: ${mode}"
      return 1
      ;;
  esac
}

# ==========================================
# Transpiled generation
# ==========================================

_bench_generate_source() {
  local lang="$1"
  local source="$2"
  case "${lang}" in
    cpp)
      _bench_generate_cpp "${source}"
      ;;
    mojo)
      _bench_generate_mojo "${source}"
      ;;
    *)
      echo "error: no source generator for language: ${lang}"
      return 1
      ;;
  esac
}

_bench_generate_cpp() {
  local source="$1"
  local dsp_path
  local cpp_out

  dsp_path="$(_bench_dsp_path "${source}")"
  cpp_out="$(_bench_cpp_out "${source}")"

  _bench_require_file "${dsp_path}" || return 1
  _bench_set_faust_mode_opt "$(_bench_current_mode)" || return 1

  mkdir -p "$(dirname "${cpp_out}")"
  rm -f "${cpp_out}"

  "${BENCH_FAUST_BIN}" \
    -lang cpp \
    -"${BENCH_INTERNAL_PRECISION}" \
    "${BENCH_FAUST_OPT[@]}" \
    "${BENCH_FAUST_MODE_OPT[@]}" \
    -a "${BENCH_CPP_ARCH_DIR}/bench.cpp" \
    "${dsp_path}" \
    -o "${cpp_out}"
}

_bench_generate_mojo() {
  local source="$1"
  local dsp_path
  local mojo_out

  dsp_path="$(_bench_dsp_path "${source}")"
  mojo_out="$(_bench_mojo_out "${source}")"

  _bench_require_file "${dsp_path}" || return 1
  _bench_set_faust_mode_opt "$(_bench_current_mode)" || return 1

  mkdir -p "$(dirname "${mojo_out}")"
  rm -f "${mojo_out}"

  "${BENCH_FAUST_BIN}" \
    -lang mojo \
    -"${BENCH_INTERNAL_PRECISION}" \
    "${BENCH_FAUST_OPT[@]}" \
    "${BENCH_FAUST_MODE_OPT[@]}" \
    -a "${BENCH_MOJO_ARCH_DIR}/bench.mojo" \
    "${dsp_path}" \
    -o "${mojo_out}"
}

_inspect_generate_cpp() {
  local source="$1"
  local dsp_path
  local cpp_out

  dsp_path="$(_bench_dsp_path "${source}")"
  cpp_out="$(_inspect_cpp_out "${source}")"

  _bench_require_file "${dsp_path}" || return 1
  _bench_set_faust_mode_opt "$(_bench_current_mode)" || return 1

  mkdir -p "$(dirname "${cpp_out}")"
  rm -f "${cpp_out}"

  "${BENCH_FAUST_BIN}" \
    -lang cpp \
    -"${BENCH_INTERNAL_PRECISION}" \
    "${BENCH_FAUST_OPT[@]}" \
    "${BENCH_FAUST_MODE_OPT[@]}" \
    -a "${BENCH_CPP_ARCH_DIR}/inspect.cpp" \
    "${dsp_path}" \
    -o "${cpp_out}"
}

_inspect_generate_mojo() {
  local source="$1"
  local dsp_path
  local mojo_out

  dsp_path="$(_bench_dsp_path "${source}")"
  mojo_out="$(_inspect_mojo_out "${source}")"

  _bench_require_file "${dsp_path}" || return 1
  _bench_set_faust_mode_opt "$(_bench_current_mode)" || return 1

  mkdir -p "$(dirname "${mojo_out}")"
  rm -f "${mojo_out}"

  "${BENCH_FAUST_BIN}" \
    -lang mojo \
    -"${BENCH_INTERNAL_PRECISION}" \
    "${BENCH_FAUST_OPT[@]}" \
    "${BENCH_FAUST_MODE_OPT[@]}" \
    -a "${BENCH_MOJO_ARCH_DIR}/inspect.mojo" \
    "${dsp_path}" \
    -o "${mojo_out}"
}

# ==========================================
# Transpiled file helpers
# ==========================================

_bench_resolve_transpiled_args() {
  local mode="$1"
  local lang="$2"
  local sample_rate="$3"
  local buffer_size="$4"
  local transpiled_path="$5"
  local norm_sample_rate

  _bench_require_mode "${mode}" || return 1
  _bench_require_lang "${lang}" || return 1
  _bench_require_file "${transpiled_path}" || return 1

  norm_sample_rate="$(_bench_normalize_sample_rate "${sample_rate}")" || return 1

  if ! [[ "${buffer_size}" =~ ^[0-9]+$ ]]; then
    echo "error: invalid buffer size: ${buffer_size}"
    return 1
  fi

  BENCH_TRANSPILED_MODE="${mode}"
  BENCH_TRANSPILED_LANG="${lang}"
  BENCH_TRANSPILED_SAMPLE_RATE="${norm_sample_rate}"
  BENCH_TRANSPILED_BUFFER_SIZE="${buffer_size}"
  BENCH_TRANSPILED_ORIGINAL_PATH="${transpiled_path}"

  _bench_split_transpiled_name "${transpiled_path}" || return 1
  BENCH_TRANSPILED_PATH="$(_bench_stage_transpiled_file "${lang}" "${transpiled_path}")" || return 1
}

_bench_split_transpiled_name() {
  local transpiled_path="$1"
  local base
  local stem

  base="${transpiled_path##*/}"
  stem="${base%.*}"

  BENCH_TRANSPILED_NAME="${stem}"
  BENCH_TRANSPILED_DSP="${stem}"
  BENCH_TRANSPILED_CASE="${stem}"

  _bench_require_non_empty "${BENCH_TRANSPILED_NAME}" "transpiled file name" || return 1
}

_bench_stage_transpiled_file() {
  local lang="$1"
  local transpiled_path="$2"
  local base
  local dest
  local arch_real
  local path_dir
  local path_dir_real

  case "${lang}" in
    mojo)
      base="${transpiled_path##*/}"
      dest="${BENCH_MOJO_ARCH_DIR}/${base}"
      path_dir="${transpiled_path%/*}"

      if [[ "${path_dir}" == "${transpiled_path}" ]]; then
        path_dir="."
      fi

      arch_real="$(cd "${BENCH_MOJO_ARCH_DIR}" && pwd -P)" || return 1
      path_dir_real="$(cd "${path_dir}" && pwd -P)" || return 1

      if [[ "${path_dir_real}" == "${arch_real}" ]]; then
        echo "${dest}"
        return 0
      fi

      mkdir -p "${BENCH_MOJO_ARCH_DIR}"
      cp "${transpiled_path}" "${dest}" || return 1
      echo "${dest}"
      ;;
    cpp)
      echo "${transpiled_path}"
      ;;
    *)
      echo "error: unsupported transpiled language: ${lang}" >&2
      return 1
      ;;
  esac
}

_bench_clean_staged_transpiled() {
  if [[ "${BENCH_KEEP_TMP}" == "1" || "${BENCH_TRANSPILED_LANG:-}" != "mojo" ]]; then
    return 0
  fi

  local original_dir
  local staged_dir
  original_dir="$(cd "$(dirname "${BENCH_TRANSPILED_ORIGINAL_PATH}")" && pwd -P)" || return 0
  staged_dir="$(cd "$(dirname "${BENCH_TRANSPILED_PATH}")" && pwd -P)" || return 0

  if [[ "${original_dir}/$(basename "${BENCH_TRANSPILED_ORIGINAL_PATH}")" != \
        "${staged_dir}/$(basename "${BENCH_TRANSPILED_PATH}")" ]]; then
    rm -f "${BENCH_TRANSPILED_PATH}"
  fi
}

_bench_build_required() {
  local transpiled_path="$1"
  local bin_path="$2"

  if [[ "${BENCH_FORCE_BUILD:-0}" == "1" ]]; then
    return 0
  fi

  if [[ ! -f "${bin_path}" ]]; then
    return 0
  fi

  if [[ "${transpiled_path}" -nt "${bin_path}" ]]; then
    return 0
  fi

  return 1
}

# ==========================================
# Transpiled inspect helpers
# ==========================================

_inspect_transpiled_emit() {
  local emit_kind="$1"
  shift

  _bench_resolve_transpiled_args "$@" || return 1

  BENCH_RUN_IS_TRANSPILED=1
  BENCH_RUN_NAME="${BENCH_TRANSPILED_NAME}"
  BENCH_RUN_MODE="${BENCH_TRANSPILED_MODE}"

  local emit_status=0

  case "${BENCH_TRANSPILED_LANG}" in
    cpp)
      _inspect_transpiled_emit_cpp \
        "${emit_kind}" \
        "${BENCH_TRANSPILED_PATH}" \
        "${BENCH_TRANSPILED_DSP}" \
        "${BENCH_TRANSPILED_CASE}" \
        "${BENCH_TRANSPILED_SAMPLE_RATE}" \
        "${BENCH_TRANSPILED_BUFFER_SIZE}" || emit_status=1
      ;;
    mojo)
      _inspect_transpiled_emit_mojo \
        "${emit_kind}" \
        "${BENCH_TRANSPILED_PATH}" \
        "${BENCH_TRANSPILED_DSP}" \
        "${BENCH_TRANSPILED_CASE}" \
        "${BENCH_TRANSPILED_SAMPLE_RATE}" \
        "${BENCH_TRANSPILED_BUFFER_SIZE}" || emit_status=1
      ;;
    *)
      echo "error: no transpiled inspect implementation for language: ${BENCH_TRANSPILED_LANG}"
      emit_status=1
      ;;
  esac

  _bench_clean_staged_transpiled
  return "${emit_status}"
}

_inspect_transpiled_path() {
  local emit_kind="$1"
  local lang="$2"
  local dsp="$3"
  local case_name="$4"
  local sample_rate="$5"
  local buffer_size="$6"
  local sr_khz
  local ext
  sr_khz="$((sample_rate / 1000))"

  case "${emit_kind}" in
    asm) ext="s" ;;
    llvm) ext="ll" ;;
    *)
      echo "error: unsupported inspect emit kind: ${emit_kind}" >&2
      return 1
      ;;
  esac

  if [[ "${BENCH_RUN_IS_TRANSPILED:-0}" == "1" ]]; then
    echo "${BENCH_REPORT_DIR}/${emit_kind}/${lang}/${BENCH_TRANSPILED_NAME}_${BENCH_RUN_MODE}_${sr_khz}_${buffer_size}.${ext}"
    return 0
  fi

  echo "${BENCH_REPORT_DIR}/${emit_kind}/${lang}/${dsp}__${case_name}_${BENCH_RUN_MODE}_${sr_khz}_${buffer_size}.${ext}"
}

_inspect_transpiled_emit_cpp() {
  local emit_kind="$1"
  local cpp_path="$2"
  local dsp="$3"
  local case_name="$4"
  local sample_rate="$5"
  local buffer_size="$6"
  local out_path
  local name
  local emit_args=()

  name="$(_bench_dsp_name "${dsp}")"
  out_path="$(_inspect_transpiled_path "${emit_kind}" cpp "${name}" "${case_name}" "${sample_rate}" "${buffer_size}")" || return 1
  mkdir -p "$(dirname "${out_path}")"

  case "${emit_kind}" in
    asm)
      emit_args=(-S)
      ;;
    llvm)
      emit_args=(-S -emit-llvm)
      ;;
  esac

  clang++ -std=gnu++23 \
    "${emit_args[@]}" \
    -I"${BENCH_CPP_ARCH_DIR}" \
    "${BENCH_CPP_OPT[@]}" \
    -DBENCH_LANG=\"cpp\" \
    -DBENCH_DSP=\"${name}\" \
    -DBENCH_CASE=\"${case_name}\" \
    -DBENCH_MODE=\"$(_bench_current_mode)\" \
    -DBENCH_OPTIM=\"${BENCH_OPTIM:-O3}\" \
    -DFAUSTFLOAT="${BENCH_CPP_FAUSTFLOAT}" \
    -DPRECISION=\"${BENCH_INTERNAL_PRECISION}\" \
    -DWRITE_CSV=0 \
    -DCSV_PATH=\"${BENCH_TMP_DIR}/${name}_${case_name}.csv\" \
    -DFILL_INPUTS=1 \
    -DSAMP_RATE="s32(${sample_rate})" \
    -DBUFF_SIZE="s32(${buffer_size})" \
    -DWARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
    -DCOMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-1000000}" \
    -DMIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
    -DMAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
    -DMAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
    -Wall -Wextra -Wno-unused-parameter -pedantic \
    -o "${out_path}" "${cpp_path}" || return 1

  echo "wrote ${out_path}"
}

_inspect_transpiled_emit_mojo() {
  local emit_kind="$1"
  local mojo_path="$2"
  local dsp="$3"
  local case_name="$4"
  local sample_rate="$5"
  local buffer_size="$6"
  local out_path
  local name
  local emit_arg

  name="$(_bench_dsp_name "${dsp}")"
  out_path="$(_inspect_transpiled_path "${emit_kind}" mojo "${name}" "${case_name}" "${sample_rate}" "${buffer_size}")" || return 1
  mkdir -p "$(dirname "${out_path}")"

  case "${emit_kind}" in
    asm) emit_arg="asm" ;;
    llvm) emit_arg="llvm" ;;
  esac

  pixi run mojo build \
    "${BENCH_MOJO_OPT[@]}" \
    -D BENCH_LANG=mojo \
    -D BENCH_DSP="${name}" \
    -D BENCH_CASE="${case_name}" \
    -D BENCH_MODE="$(_bench_current_mode)" \
    -D BENCH_OPTIM="${BENCH_OPTIM:-O3}" \
    -D FAUST_DTYPE="${BENCH_MOJO_FAUST_DTYPE}" \
    -D PRECISION="${BENCH_INTERNAL_PRECISION}" \
    -D WRITE_CSV=False \
    -D CSV_PATH="${BENCH_TMP_DIR}/${name}_${case_name}.csv" \
    -D FILL_INPUTS=True \
    -D SAMP_RATE="${sample_rate}" \
    -D BUFF_SIZE="${buffer_size}" \
    -D WARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
    -D COMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-1000000}" \
    -D MIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
    -D MAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
    -D MAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
    --emit "${emit_arg}" \
    -o "${out_path}" "${mojo_path}" || return 1

  echo "wrote ${out_path}"
}

# ==========================================
# Run engine
# ==========================================

_bench_run_resolved() {
  local run_status=0

  _bench_generate_all_transpiled_parallel || run_status=1

  if (( run_status == 0 )); then
    _bench_prepare_all_csv_fragments || run_status=1
  fi

  if (( run_status == 0 )); then
    _bench_build_all_cases_parallel || run_status=1
  fi

  if (( run_status == 0 )); then
    _bench_exec_all_cases_serial || run_status=1
  fi

  if (( run_status == 0 )); then
    _bench_commit_all_csv_fragments || run_status=1
  fi

  _bench_clean_all_tmp_files
  return "${run_status}"
}

_bench_disable_job_control_noise() {
  # Avoid interactive zsh job-control noise such as "[1] 12345" while still
  # running this file as a sourced shell API.
  if [[ -n "${ZSH_VERSION:-}" ]]; then
    unsetopt monitor 2>/dev/null || true
  else
    set +m 2>/dev/null || true
  fi
}

_bench_normalized_jobs() {
  local jobs="${BENCH_JOBS:-10}"
  if ! [[ "${jobs}" =~ ^[0-9]+$ ]] || (( jobs < 1 )); then
    jobs=1
  fi
  echo "${jobs}"
}

_bench_wait_parallel_batch() {
  local pid

  for pid in "$@"; do
    wait "${pid}" || true
  done
}

_bench_generate_all_transpiled_parallel() {
  local source
  local lang
  local mode
  local jobs
  local pids=()

  jobs="$(_bench_normalized_jobs)"
  _bench_disable_job_control_noise

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        _bench_generate_transpiled_with_mode \
          "${source}" \
          "${lang}" \
          "${mode}" &
        pids+=("$!")

        if (( ${#pids[@]} >= jobs )); then
          _bench_wait_parallel_batch "${pids[@]}" || return 1
          pids=()
        fi
      done
    done
  done

  if (( ${#pids[@]} > 0 )); then
    _bench_wait_parallel_batch "${pids[@]}" || return 1
  fi
}

_bench_generate_transpiled_with_mode() {
  local source="$1"
  local lang="$2"
  local mode="$3"
  local dsp_path

  BENCH_RUN_MODE="${mode}"

  if ! _bench_generate_source "${lang}" "${source}"; then
    dsp_path="$(_bench_dsp_path "${source}")"
    echo "${dsp_path##*/}" >&2
    return 1
  fi
}

_bench_prepare_all_csv_fragments() {
  local source
  local lang
  local mode

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        BENCH_RUN_MODE="${mode}"
        _bench_csv_prepare_fragment "${lang}" "${source}" || return 1
      done
    done
  done
}

_bench_commit_all_csv_fragments() {
  local source
  local lang
  local mode
  local csv_path

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        BENCH_RUN_MODE="${mode}"
        csv_path="$(_bench_tmp_csv_path "${lang}" "${source}")"

        if [[ -f "${csv_path}" ]]; then
          _bench_csv_commit_fragment "${lang}" "${source}" || true
        fi
      done
    done
  done
}

_bench_clean_all_tmp_files() {
  local source
  local lang
  local mode

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        BENCH_RUN_MODE="${mode}"
        _bench_clean_generated_source "${lang}" "${source}"
      done
    done
  done
}

_bench_build_all_cases_parallel() {
  local source
  local lang
  local mode
  local sample_rate
  local buffer_size
  local jobs
  local pids=()

  jobs="$(_bench_normalized_jobs)"
  _bench_disable_job_control_noise

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        for sample_rate in "${BENCH_RUN_SAMPLE_RATES[@]}"; do
          for buffer_size in "${BENCH_RUN_BUFFER_SIZES[@]}"; do
            _bench_build_case_with_mode \
              "${source}" \
              "${lang}" \
              "${mode}" \
              "${sample_rate}" \
              "${buffer_size}" &
            pids+=("$!")

            if (( ${#pids[@]} >= jobs )); then
              _bench_wait_parallel_batch "${pids[@]}" || return 1
              pids=()
            fi
          done
        done
      done
    done
  done

  if (( ${#pids[@]} > 0 )); then
    _bench_wait_parallel_batch "${pids[@]}" || return 1
  fi
}

_bench_exec_all_cases_serial() {
  local source
  local lang
  local mode
  local sample_rate
  local buffer_size

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        for sample_rate in "${BENCH_RUN_SAMPLE_RATES[@]}"; do
          for buffer_size in "${BENCH_RUN_BUFFER_SIZES[@]}"; do
            _bench_exec_case_with_mode \
              "${source}" \
              "${lang}" \
              "${mode}" \
              "${sample_rate}" \
              "${buffer_size}" || true
          done
        done
      done
    done
  done
}

_bench_build_case_with_mode() {
  local source="$1"
  local lang="$2"
  local mode="$3"
  local sample_rate="$4"
  local buffer_size="$5"
  local transpiled
  local bin

  BENCH_RUN_MODE="${mode}"

  case "${lang}" in
    cpp)
      transpiled="$(_bench_cpp_out "${source}")"
      ;;
    mojo)
      transpiled="$(_bench_mojo_out "${source}")"
      ;;
    *)
      return 1
      ;;
  esac

  if [[ ! -f "${transpiled}" ]]; then
    bin="$(_bench_case_bin "${lang}" "${source}" "${sample_rate}" "${buffer_size}")"
    rm -f "${bin}"
    return 0
  fi

  _bench_build_case "${source}" "${lang}" "${sample_rate}" "${buffer_size}"
}

_bench_exec_case_with_mode() {
  local source="$1"
  local lang="$2"
  local mode="$3"
  local sample_rate="$4"
  local buffer_size="$5"
  local bin

  BENCH_RUN_MODE="${mode}"
  bin="$(_bench_case_bin "${lang}" "${source}" "${sample_rate}" "${buffer_size}")"

  if [[ ! -f "${bin}" ]]; then
    return 0
  fi

  _bench_exec_case "${source}" "${lang}" "${sample_rate}" "${buffer_size}"
}

_bench_build_case() {
  local source="$1"
  local lang="$2"
  local sample_rate="$3"
  local buffer_size="$4"
  case "${lang}" in
    cpp)
      _bench_build_case_cpp "${source}" "${sample_rate}" "${buffer_size}"
      ;;
    mojo)
      _bench_build_case_mojo "${source}" "${sample_rate}" "${buffer_size}"
      ;;
    *)
      echo "error: no build case implementation for language: ${lang}"
      return 1
      ;;
  esac
}

_bench_build_transpiled_case() {
  local lang="$1"
  local transpiled_path="$2"
  local source="$3"
  local sample_rate="$4"
  local buffer_size="$5"
  case "${lang}" in
    cpp)
      _bench_build_transpiled_case_cpp "${transpiled_path}" "${source}" "${sample_rate}" "${buffer_size}"
      ;;
    mojo)
      _bench_build_transpiled_case_mojo "${transpiled_path}" "${source}" "${sample_rate}" "${buffer_size}"
      ;;
    *)
      echo "error: no build transpiled implementation for language: ${lang}"
      return 1
      ;;
  esac
}

_bench_exec_case() {
  local source="$1"
  local lang="$2"
  local sample_rate="$3"
  local buffer_size="$4"
  case "${lang}" in
    cpp)
      _bench_exec_case_cpp "${source}" "${sample_rate}" "${buffer_size}"
      ;;
    mojo)
      _bench_exec_case_mojo "${source}" "${sample_rate}" "${buffer_size}"
      ;;
    *)
      echo "error: no exec case implementation for language: ${lang}"
      return 1
      ;;
  esac
}

_bench_build_case_cpp() {
  local source="$1"
  local sample_rate="$2"
  local buffer_size="$3"
  local cpp_out
  cpp_out="$(_bench_cpp_out "${source}")"
  _bench_build_transpiled_case_cpp "${cpp_out}" "${source}" "${sample_rate}" "${buffer_size}"
}

_bench_build_transpiled_case_cpp() {
  local cpp_out="$1"
  local source="$2"
  local sample_rate="$3"
  local buffer_size="$4"
  local cpp_bin
  local csv_path
  local build_log
  local name
  cpp_bin="$(_bench_case_bin cpp "${source}" "${sample_rate}" "${buffer_size}")"
  csv_path="$(_bench_tmp_csv_path cpp "${source}")"
  build_log="$(_bench_case_build_log cpp "${source}" "${sample_rate}" "${buffer_size}")"
  name="$(_bench_dsp_name "${source}")"
  _bench_require_file "${cpp_out}" || return 1
  mkdir -p "$(dirname "${cpp_bin}")" "$(dirname "${csv_path}")" "$(dirname "${build_log}")"

  if ! _bench_build_required "${cpp_out}" "${cpp_bin}"; then
    echo "reusing cpp:${BENCH_RUN_NAME}/$(_bench_current_mode)(${name}, sr=${sample_rate}, bs=${buffer_size})"
    return 0
  fi

  rm -f "${cpp_bin}"

  echo "building cpp:${BENCH_RUN_NAME}/$(_bench_current_mode)(${name}, sr=${sample_rate}, bs=${buffer_size})"
  if ! clang++ -std=gnu++23 \
    -I"${BENCH_CPP_ARCH_DIR}" \
    "${BENCH_CPP_OPT[@]}" \
    -DBENCH_LANG=\"cpp\" \
    -DBENCH_DSP=\"${name}\" \
    -DBENCH_CASE=\"${BENCH_RUN_NAME}\" \
    -DBENCH_MODE=\"$(_bench_current_mode)\" \
    -DBENCH_OPTIM=\"${BENCH_OPTIM:-O3}\" \
    -DFAUSTFLOAT="${BENCH_CPP_FAUSTFLOAT}" \
    -DPRECISION=\"${BENCH_INTERNAL_PRECISION}\" \
    -DWRITE_CSV=1 \
    -DCSV_PATH=\"${csv_path}\" \
    -DFILL_INPUTS=1 \
    -DSAMP_RATE="s32(${sample_rate})" \
    -DBUFF_SIZE="s32(${buffer_size})" \
    -DWARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
    -DCOMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-1000000}" \
    -DMIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
    -DMAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
    -DMAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
    -Wall -Wextra -Wno-unused-parameter -pedantic \
    -o "${cpp_bin}" "${cpp_out}" \
    >"${build_log}" 2>&1; then
    cat "${build_log}"
    return 1
  fi
  rm -f "${build_log}"
}

_bench_build_case_mojo() {
  local source="$1"
  local sample_rate="$2"
  local buffer_size="$3"
  local mojo_out
  mojo_out="$(_bench_mojo_out "${source}")"
  _bench_build_transpiled_case_mojo "${mojo_out}" "${source}" "${sample_rate}" "${buffer_size}"
}

_bench_build_transpiled_case_mojo() {
  local mojo_out="$1"
  local source="$2"
  local sample_rate="$3"
  local buffer_size="$4"
  local mojo_bin
  local csv_path
  local build_log
  local name
  mojo_out="$(_bench_stage_transpiled_file mojo "${mojo_out}")" || return 1
  mojo_bin="$(_bench_case_bin mojo "${source}" "${sample_rate}" "${buffer_size}")"
  csv_path="$(_bench_tmp_csv_path mojo "${source}")"
  build_log="$(_bench_case_build_log mojo "${source}" "${sample_rate}" "${buffer_size}")"
  name="$(_bench_dsp_name "${source}")"
  _bench_require_file "${mojo_out}" || return 1
  mkdir -p "$(dirname "${mojo_bin}")" "$(dirname "${csv_path}")" "$(dirname "${build_log}")"

  if ! _bench_build_required "${mojo_out}" "${mojo_bin}"; then
    echo "reusing mojo:${BENCH_RUN_NAME}/$(_bench_current_mode)(${name}, sr=${sample_rate}, bs=${buffer_size})"
    return 0
  fi

  rm -f "${mojo_bin}"

  echo "building mojo:${BENCH_RUN_NAME}/$(_bench_current_mode)(${name}, sr=${sample_rate}, bs=${buffer_size})"
  if ! pixi run mojo build \
    "${BENCH_MOJO_OPT[@]}" \
    -D BENCH_LANG=mojo \
    -D BENCH_DSP="${name}" \
    -D BENCH_CASE="${BENCH_RUN_NAME}" \
    -D BENCH_MODE="$(_bench_current_mode)" \
    -D BENCH_OPTIM="${BENCH_OPTIM:-O3}" \
    -D FAUST_DTYPE="${BENCH_MOJO_FAUST_DTYPE}" \
    -D PRECISION="${BENCH_INTERNAL_PRECISION}" \
    -D WRITE_CSV=True \
    -D CSV_PATH="${csv_path}" \
    -D FILL_INPUTS=True \
    -D SAMP_RATE="${sample_rate}" \
    -D BUFF_SIZE="${buffer_size}" \
    -D WARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
    -D COMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-1000000}" \
    -D MIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
    -D MAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
    -D MAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
    -o "${mojo_bin}" "${mojo_out}" \
    >"${build_log}" 2>&1; then
    cat "${build_log}"
    return 1
  fi
  rm -f "${build_log}"
}

_bench_exec_case_cpp() {
  local source="$1"
  local sample_rate="$2"
  local buffer_size="$3"
  local cpp_bin
  local report
  local name
  cpp_bin="$(_bench_case_bin cpp "${source}" "${sample_rate}" "${buffer_size}")"
  report="$(_bench_tab_path cpp "${source}" "${sample_rate}" "${buffer_size}")"
  name="$(_bench_dsp_name "${source}")"
  _bench_require_file "${cpp_bin}" || return 1
  mkdir -p "$(dirname "${report}")"
  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running cpp:${BENCH_RUN_NAME}/$(_bench_current_mode)(${name}, sr=${sample_rate}, bs=${buffer_size}, csv=1)"
  ( "${cpp_bin}" ) &> "${report}"
  local case_status=$?
  cat "${report}"
  echo "------------------------------------"
  echo
  return "${case_status}"
}

_bench_exec_case_mojo() {
  local source="$1"
  local sample_rate="$2"
  local buffer_size="$3"
  local mojo_bin
  local report
  local name
  mojo_bin="$(_bench_case_bin mojo "${source}" "${sample_rate}" "${buffer_size}")"
  report="$(_bench_tab_path mojo "${source}" "${sample_rate}" "${buffer_size}")"
  name="$(_bench_dsp_name "${source}")"
  _bench_require_file "${mojo_bin}" || return 1
  mkdir -p "$(dirname "${report}")"
  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running mojo:${BENCH_RUN_NAME}/$(_bench_current_mode)(${name}, sr=${sample_rate}, bs=${buffer_size}, csv=1)"
  ( "${mojo_bin}" ) &> "${report}"
  local case_status=$?
  cat "${report}"
  echo "------------------------------------"
  echo
  return "${case_status}"
}

# ==========================================
# Plot helpers
# ==========================================

_bench_plot_require_name() {
  local plot_name="$1"
  if [[ -z "${plot_name}" ]]; then
    echo "usage: bench_plot <plot_name>"
    return 1
  fi
}

_bench_plot_from_csv() {
  local csv_out="$1"
  local plot_out="$2"
  local case_name="${3:-all}"
  local case_args=()

  if [[ "${case_name}" != "all" ]]; then
    case_args=(--case "${case_name}")
  fi

  _bench_require_file "${csv_out}" || return 1
  mkdir -p "$(dirname "${plot_out}")"
  pixi run python "${BENCH_SCRIPT_DIR}/plot.py" "${csv_out}" \
    "${case_args[@]}" \
    --x combo \
    --y out_samp_per_s \
    --series "${BENCH_PLOT_SERIES:-language,mode}" \
    --out "${plot_out}" \
    --title "Faust Benchmark"
}

# ==========================================
# Snapshot helpers
# ==========================================

_bench_snapshot_name() {
  local name="$1"
  printf "%s" "${name}" \
    | tr -cs 'A-Za-z0-9_.-' '_' \
    | sed 's/^_*//; s/_*$//'
}

_bench_snapshot_copy_report() {
  local snapshot_path="$1"
  mkdir -p "${snapshot_path}"
  if [[ -f "${BENCH_CSV}" ]]; then
    cp "${BENCH_CSV}" "${snapshot_path}/report.csv"
  fi
  if [[ -d "${BENCH_TAB_DIR}" ]]; then
    mkdir -p "${snapshot_path}/tab"
    cp -R "${BENCH_TAB_DIR}"/. "${snapshot_path}/tab/" 2>/dev/null || true
  fi
  if [[ -d "${BENCH_PLOT_DIR}" ]]; then
    mkdir -p "${snapshot_path}/plot"
    cp "${BENCH_PLOT_DIR}"/*.svg "${snapshot_path}/plot/" 2>/dev/null || true
  fi
  echo "saved snapshot: ${snapshot_path}"
}

_bench_snapshot_write_meta() {
  local snapshot_path="$1"
  local snapshot_name="$2"
  local meta_path="${snapshot_path}/meta.txt"
  {
    echo "snapshot: ${snapshot_name}"
    echo "created: $(date "+%Y-%m-%d %H:%M:%S")"
    echo "command: ${BENCH_LAST_COMMAND:-unknown}"
    echo "run_name: ${BENCH_RUN_NAME:-run}"
    echo "resolved_modes: ${BENCH_RUN_MODES[*]:-unknown}"
    echo "current_mode: ${BENCH_RUN_MODE:-unknown}"
    echo "workspace: ${BENCH_ROOT}"
    echo "git_branch: $(git -C "${BENCH_FAUST_ROOT}" branch --show-current 2>/dev/null || echo unknown)"
    echo "git_commit: $(git -C "${BENCH_FAUST_ROOT}" rev-parse --short HEAD 2>/dev/null || echo unknown)"
    echo "languages: ${BENCH_LANGS[*]}"
    echo "modes: ${BENCH_MODES[*]}"
    echo "sample_rates_hz: ${BENCH_SAMPLE_RATES[*]}"
    echo "buffer_sizes: ${BENCH_BUFFER_SIZES[*]}"
    echo "internal_precision: ${BENCH_INTERNAL_PRECISION}"
    echo "external_precision: ${BENCH_EXTERNAL_PRECISION}"
    echo "cpp_faustfloat: ${BENCH_CPP_FAUSTFLOAT}"
    echo "mojo_faust_dtype: ${BENCH_MOJO_FAUST_DTYPE}"
    echo "cpp_opt: ${BENCH_CPP_OPT[*]}"
    echo "mojo_opt: ${BENCH_MOJO_OPT[*]}"
    echo "faust_scalar_opt: ${BENCH_FAUST_SCALAR_OPT[*]}"
    echo "faust_vec_opt: ${BENCH_FAUST_VEC_OPT[*]}"
    echo "warmup_iters: ${BENCH_WARMUP_ITERS:-50}"
    echo "compute_iters: ${BENCH_COMPUTE_ITERS:-1000000}"
    echo "min_runtime_secs: ${BENCH_MIN_RUNTIME_SECS:-1}"
    echo "max_runtime_secs: ${BENCH_MAX_RUNTIME_SECS:-60}"
    echo "max_batch_size: ${BENCH_MAX_BATCH_SIZE:-10000}"
    echo "faust: $("${BENCH_FAUST_BIN}" --version 2>/dev/null || echo unknown)"
    echo "clang: $(clang++ --version 2>/dev/null | head -n 1 || echo unknown)"
    echo "mojo: $(pixi run mojo --version 2>/dev/null || echo unknown)"
  } > "${meta_path}"
}

# ==========================================
# Inspect helpers
# ==========================================

_inspect_sample_rate() {
  local value
  for value in "${BENCH_SAMPLE_RATES[@]}"; do
    echo "${value}"
    return 0
  done
}

_inspect_buffer_size() {
  local value
  for value in "${BENCH_BUFFER_SIZES[@]}"; do
    echo "${value}"
    return 0
  done
}

_inspect_compute_iters() {
  echo "${BENCH_INSPECT_COMPUTE_ITERS:-1}"
}

_inspect_supports_lang() {
  local lang="$1"
  case "${lang}" in
    cpp|mojo)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

_inspect_compile_common_cpp_args() {
  echo -I"${BENCH_CPP_ARCH_DIR}"
  echo "${BENCH_CPP_OPT[@]}"
  echo -DFAUSTFLOAT="${BENCH_CPP_FAUSTFLOAT}"
  echo -DPRECISION=\"${BENCH_INTERNAL_PRECISION}\"
  echo -DBENCH_MODE="$(_bench_current_mode)"
  echo -DSAMP_RATE="$(_inspect_sample_rate)"
  echo -DBUFF_SIZE="$(_inspect_buffer_size)"
  echo -DCOMPUTE_ITERS="$(_inspect_compute_iters)"
}

_inspect_compile_common_mojo_args() {
  echo "${BENCH_MOJO_OPT[@]}"
  echo -D FAUST_DTYPE="${BENCH_MOJO_FAUST_DTYPE}"
  echo -D PRECISION="${BENCH_INTERNAL_PRECISION}"
  echo -D BENCH_MODE="$(_bench_current_mode)"
  echo -D SAMP_RATE="$(_inspect_sample_rate)"
  echo -D BUFF_SIZE="$(_inspect_buffer_size)"
  echo -D COMPUTE_ITERS="$(_inspect_compute_iters)"
}

# ==========================================
# LLVM helpers
# ==========================================

_inspect_llvm_gen() {
  local source
  local lang
  local mode

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        BENCH_RUN_MODE="${mode}"

        if ! _inspect_supports_lang "${lang}"; then
          echo "skipped: language '${lang}' does not support LLVM IR generation in this framework"
          continue
        fi

        case "${lang}" in
          cpp)
            _inspect_llvm_gen_cpp "${source}" || return 1
            ;;
          mojo)
            _inspect_llvm_gen_mojo "${source}" || return 1
            ;;
        esac
      done
    done
  done
}

_inspect_llvm_gen_cpp() {
  local source="$1"
  local cpp_out
  local ir_path
  _inspect_generate_cpp "${source}" || return 1
  cpp_out="$(_inspect_cpp_out "${source}")"
  ir_path="$(_inspect_cpp_llvm "${source}")"
  mkdir -p "$(dirname "${ir_path}")"
  clang++ -std=gnu++23 \
    -S -emit-llvm \
    $(_inspect_compile_common_cpp_args) \
    -Wall -Wextra -Wno-unused-parameter -pedantic \
    -o "${ir_path}" "${cpp_out}" || return 1
  echo "wrote ${ir_path}"
  _inspect_clean_generated_source cpp "${source}"
}

_inspect_llvm_gen_mojo() {
  local source="$1"
  local mojo_out
  local ir_path
  _inspect_generate_mojo "${source}" || return 1
  mojo_out="$(_inspect_mojo_out "${source}")"
  ir_path="$(_inspect_mojo_llvm "${source}")"
  mkdir -p "$(dirname "${ir_path}")"
  pixi run mojo build \
    $(_inspect_compile_common_mojo_args) \
    --emit llvm \
    -o "${ir_path}" "${mojo_out}" || return 1
  echo "wrote ${ir_path}"
  _inspect_clean_generated_source mojo "${source}"
}

# ==========================================
# Assembly helpers
# ==========================================

_inspect_asm_gen() {
  local source
  local lang
  local mode

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      for mode in "${BENCH_RUN_MODES[@]}"; do
        BENCH_RUN_MODE="${mode}"

        if ! _inspect_supports_lang "${lang}"; then
          echo "skipped: language '${lang}' does not support assembly generation in this framework"
          continue
        fi

        case "${lang}" in
          cpp)
            _inspect_asm_gen_cpp "${source}" || return 1
            ;;
          mojo)
            _inspect_asm_gen_mojo "${source}" || return 1
            ;;
        esac
      done
    done
  done
}

_inspect_asm_gen_cpp() {
  local source="$1"
  local cpp_out
  local asm_path
  _inspect_generate_cpp "${source}" || return 1
  cpp_out="$(_inspect_cpp_out "${source}")"
  asm_path="$(_inspect_cpp_asm "${source}")"
  mkdir -p "$(dirname "${asm_path}")"
  clang++ -std=gnu++23 \
    -S \
    $(_inspect_compile_common_cpp_args) \
    -Wall -Wextra -Wno-unused-parameter -pedantic \
    -o "${asm_path}" "${cpp_out}" || return 1
  echo "wrote ${asm_path}"
  _inspect_clean_generated_source cpp "${source}"
}

_inspect_asm_gen_mojo() {
  local source="$1"
  local mojo_out
  local asm_path
  _inspect_generate_mojo "${source}" || return 1
  mojo_out="$(_inspect_mojo_out "${source}")"
  asm_path="$(_inspect_mojo_asm "${source}")"
  mkdir -p "$(dirname "${asm_path}")"
  pixi run mojo build \
    $(_inspect_compile_common_mojo_args) \
    --emit asm \
    -o "${asm_path}" "${mojo_out}" || return 1
  echo "wrote ${asm_path}"
  _inspect_clean_generated_source mojo "${source}"
}
