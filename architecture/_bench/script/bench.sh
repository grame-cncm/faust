#!/usr/bin/env bash

# Benchmark framework.
#
# This file is meant to be sourced by script/source.sh.
# It assumes that source.sh has already initialized BENCH_* paths and defaults.

# ------------------------------------------
# Public API
# ------------------------------------------

bench_run() {
  if (( $# < 4 )); then
    echo "usage: bench_run <langs> <sample_rates_khz> <buffer_sizes> <sources...>"
    return 1
  fi

  BENCH_RUN_NAME="${BENCH_RUN_NAME:-run}"
  BENCH_LAST_COMMAND="bench_run $*"

  _bench_resolve_args "$@" || return 1
  _bench_clean_report || return 1
  _bench_run_resolved
}

bench_plot() {
  local plot_name="$1"

  _bench_plot_require_name "${plot_name}" || return 1
  _bench_plot_from_csv "${BENCH_CSV}" "$(_bench_plot_path "${plot_name}")"
}

bench_snapshot() {
  local snapshot_name="$1"

  _bench_require_non_empty "${snapshot_name}" "snapshot name" || return 1

  local snapshot_path
  snapshot_path="$(_bench_snapshot_path "${snapshot_name}")"

  _bench_snapshot_copy_report "${snapshot_path}" || return 1
  _bench_snapshot_write_meta "${snapshot_path}" "${snapshot_name}"
}

bench_llvm_gen() {
  if (( $# < 2 )); then
    echo "usage: bench_llvm_gen <langs> <sources...>"
    return 1
  fi

  local langs="$1"
  shift

  _bench_resolve_langs "${langs}" || return 1
  _bench_resolve_sources "$@" || return 1
  _bench_llvm_gen
}

bench_asm_gen() {
  if (( $# < 2 )); then
    echo "usage: bench_asm_gen <langs> <sources...>"
    return 1
  fi
  local langs="$1"
  shift
  _bench_resolve_langs "${langs}" || return 1
  _bench_resolve_sources "$@" || return 1
  _bench_asm_gen
}

# ------------------------------------------
# Validation helpers
# ------------------------------------------

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

_bench_require_precision() {
  local precision="$1"
  local supported

  for supported in "${BENCH_PRECISIONS[@]}"; do
    if [[ "${precision}" == "${supported}" ]]; then
      return 0
    fi
  done

  echo "error: unsupported precision: ${precision}"
  echo "supported precisions: ${BENCH_PRECISIONS[*]}"
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

_bench_require_command() {
  local command="$1"

  if ! command -v "${command}" >/dev/null 2>&1; then
    echo "error: missing command: ${command}"
    return 1
  fi
}

# ------------------------------------------
# Argument resolution
# ------------------------------------------

_bench_resolve_args() {
  local langs="$1"
  local sample_rates="$2"
  local buffer_sizes="$3"
  shift 3

  _bench_resolve_langs "${langs}" || return 1
  _bench_resolve_sample_rates "${sample_rates}" || return 1
  _bench_resolve_buffer_sizes "${buffer_sizes}" || return 1
  _bench_resolve_sources "$@" || return 1
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
    if ! [[ "${item}" =~ ^[0-9]+$ ]]; then
      echo "error: invalid sample rate: ${item}"
      echo "sample rates are passed in kHz, for example: 48,192"
      return 1
    fi

    if (( item < 1000 )); then
      value=$((item * 1000))
    else
      value="${item}"
    fi

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

_bench_resolve_csv_list() {
  local spec="$1"
  local item

  BENCH_RESOLVED_CSV_LIST=()

  for item in $(printf "%s" "${spec}" | tr ',' ' '); do
    BENCH_RESOLVED_CSV_LIST+=("${item}")
  done

  _bench_require_non_empty "${BENCH_RESOLVED_CSV_LIST[*]}" "resolved CSV list"
}

# ------------------------------------------
# Path helpers
# ------------------------------------------

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

_bench_cpp_src() {
  local name
  name="$(_bench_dsp_name "$1")"
  echo "${BENCH_CPP_ARCH_DIR}/${name}.cpp"
}

_bench_cpp_bin() {
  local name
  name="$(_bench_dsp_name "$1")"
  echo "${BENCH_CPP_ARCH_DIR}/${name}_cpp"
}

_bench_cpp_llvm_ir() {
  local name="$1"
  local precision="$2"
  name="$(_bench_dsp_name "${name}")"
  echo "${BENCH_REPORT_DIR}/llvm/cpp/${name}_${precision}.ll"
}

_bench_mojo_src() {
  local name
  name="$(_bench_dsp_name "$1")"
  echo "${BENCH_MOJO_ARCH_DIR}/${name}.mojo"
}

_bench_mojo_bin() {
  local name
  name="$(_bench_dsp_name "$1")"
  echo "${BENCH_MOJO_ARCH_DIR}/${name}_mojo"
}

_bench_mojo_llvm_ir() {
  local name="$1"
  local precision="$2"
  name="$(_bench_dsp_name "${name}")"
  echo "${BENCH_REPORT_DIR}/llvm/mojo/${name}_${precision}.ll"
}

_bench_cpp_asm() {
  local name="$1"
  local precision="$2"
  name="$(_bench_dsp_name "${name}")"
  echo "${BENCH_REPORT_DIR}/asm/cpp/${name}_${precision}.s"
}

_bench_mojo_asm() {
  local name="$1"
  local precision="$2"
  name="$(_bench_dsp_name "${name}")"
  echo "${BENCH_REPORT_DIR}/asm/mojo/${name}_${precision}.s"
}

_bench_tab_path() {
  local lang="$1"
  local dsp="$2"
  local precision="$3"
  local samp_rate="$4"
  local buff_size="$5"

  local name
  local sr_khz

  name="$(_bench_dsp_name "${dsp}")"
  sr_khz="$((samp_rate / 1000))"

  echo "${BENCH_REPORT_DIR}/${lang}/${lang}_${name}_${BENCH_RUN_NAME}_${sr_khz}_${buff_size}_${precision}.tab"
}

_bench_tmp_csv_path() {
  local lang="$1"
  local dsp="$2"

  local name
  name="$(_bench_dsp_name "${dsp}")"

  echo "${BENCH_TMP_DIR}/${lang}_${name}_${BENCH_RUN_NAME}.csv"
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

  echo "${BENCH_REPORT_DIR}/snapshots/${stamp}_${safe_name}"
}

# ------------------------------------------
# Cleanup
# ------------------------------------------

_bench_clean_report() {
  rm -f "${BENCH_CSV}"

  _bench_clean_tmp_csv
  _bench_clean_tabs all
  _bench_clean_plots
}

_bench_clean_tmp_csv() {
  find "${BENCH_TMP_DIR}" \
    -maxdepth 1 \
    -type f \
    -name "*.csv" \
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

  find "${BENCH_REPORT_DIR}/${lang}" \
    -maxdepth 1 \
    -type f \
    -name "*.tab" \
    -delete 2>/dev/null || true
}

_bench_clean_plots() {
  find "${BENCH_PLOT_DIR}" \
    -maxdepth 1 \
    -type f \
    -name "*.svg" \
    -delete 2>/dev/null || true
}

_bench_clean_tmp_files() {
  local lang="$1"
  local source="$2"

  _bench_clean_generated_source "${lang}" "${source}"
  _bench_clean_generated_binary "${lang}" "${source}"
}

_bench_clean_generated_source() {
  local lang="$1"
  local source="$2"

  if [[ "${BENCH_KEEP_TMP}" == "1" ]]; then
    return 0
  fi

  case "${lang}" in
    cpp)
      rm -f "$(_bench_cpp_src "${source}")"
      ;;
    mojo)
      rm -f "$(_bench_mojo_src "${source}")"
      ;;
  esac
}

_bench_clean_generated_binary() {
  local lang="$1"
  local source="$2"

  if [[ "${BENCH_KEEP_TMP}" == "1" ]]; then
    return 0
  fi

  case "${lang}" in
    cpp)
      rm -f "$(_bench_cpp_bin "${source}")"
      ;;
    mojo)
      rm -f "$(_bench_mojo_bin "${source}")"
      ;;
  esac
}

# ------------------------------------------
# CSV helpers
# ------------------------------------------

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
    return 1
  fi

  pixi run python "${BENCH_SCRIPT_DIR}/csvmanip.py" merge \
    --main "${BENCH_CSV}" \
    --tmp "${tmp_csv}" \
    --language "${lang}" \
    --dsp "${name}" \
    --case "${BENCH_RUN_NAME}"
}

# ------------------------------------------
# Source generation
# ------------------------------------------

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
  local cpp_src

  dsp_path="$(_bench_dsp_path "${source}")"
  cpp_src="$(_bench_cpp_src "${source}")"

  _bench_require_file "${dsp_path}" || return 1
  mkdir -p "$(dirname "${cpp_src}")"

  "${BENCH_FAUST_BIN}" \
    -lang cpp \
    -a "${BENCH_CPP_ARCH_DIR}/bench.cpp" \
    "${dsp_path}" \
    -o "${cpp_src}"
}

_bench_generate_mojo() {
  local source="$1"
  local dsp_path
  local mojo_src

  dsp_path="$(_bench_dsp_path "${source}")"
  mojo_src="$(_bench_mojo_src "${source}")"

  _bench_require_file "${dsp_path}" || return 1
  mkdir -p "$(dirname "${mojo_src}")"

  "${BENCH_FAUST_BIN}" \
    -lang mojo \
    -a "${BENCH_MOJO_ARCH_DIR}/bench.mojo" \
    "${dsp_path}" \
    -o "${mojo_src}"
}

# ------------------------------------------
# Run engine
# ------------------------------------------

_bench_run_resolved() {
  local source
  local lang

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      _bench_run_source_lang "${source}" "${lang}" || return 1
    done
  done
}

_bench_run_source_lang() {
  local source="$1"
  local lang="$2"

  local sample_rate
  local buffer_size
  local precision

  _bench_generate_source "${lang}" "${source}" || return 1
  _bench_csv_prepare_fragment "${lang}" "${source}" || return 1

  for sample_rate in "${BENCH_RUN_SAMPLE_RATES[@]}"; do
    for buffer_size in "${BENCH_RUN_BUFFER_SIZES[@]}"; do
      for precision in "${BENCH_PRECISIONS[@]}"; do
        _bench_run_case \
          "${source}" \
          "${lang}" \
          "${precision}" \
          "${sample_rate}" \
          "${buffer_size}" || return 1
      done
    done
  done

  _bench_csv_commit_fragment "${lang}" "${source}" || return 1
  _bench_clean_tmp_files "${lang}" "${source}"
}

_bench_run_case() {
  local source="$1"
  local lang="$2"
  local precision="$3"
  local sample_rate="$4"
  local buffer_size="$5"

  case "${lang}" in
    cpp)
      _bench_run_case_cpp "${source}" "${precision}" "${sample_rate}" "${buffer_size}"
      ;;
    mojo)
      _bench_run_case_mojo "${source}" "${precision}" "${sample_rate}" "${buffer_size}"
      ;;
    *)
      echo "error: no run case implementation for language: ${lang}"
      return 1
      ;;
  esac
}

_bench_run_case_cpp() {
  local source="$1"
  local precision="$2"
  local sample_rate="$3"
  local buffer_size="$4"

  _bench_require_precision "${precision}" || return 1

  local cpp_src
  local cpp_bin
  local report
  local csv_path
  local faust_float
  local name

  cpp_src="$(_bench_cpp_src "${source}")"
  cpp_bin="$(_bench_cpp_bin "${source}")"
  report="$(_bench_tab_path cpp "${source}" "${precision}" "${sample_rate}" "${buffer_size}")"
  csv_path="$(_bench_tmp_csv_path cpp "${source}")"
  faust_float="$(_bench_precision_cpp_macro "${precision}")"
  name="$(_bench_dsp_name "${source}")"

  _bench_require_file "${cpp_src}" || return 1
  mkdir -p "$(dirname "${report}")" "$(dirname "${cpp_bin}")" "$(dirname "${csv_path}")"

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running cpp:${BENCH_RUN_NAME}(${name}, ${precision}, sr=${sample_rate}, bs=${buffer_size}, csv=1)"

  (
    clang++ -std=gnu++23 \
      -I"${BENCH_CPP_ARCH_DIR}" \
      "${BENCH_CPP_OPT[@]}" \
      -DBENCH_LANG=\"cpp\" \
      -DBENCH_DSP=\"${name}\" \
      -DBENCH_CASE=\"${BENCH_RUN_NAME}\" \
      -DBENCH_OPTIM=\"${BENCH_OPTIM:-O3}\" \
      -DFAUSTFLOAT="${faust_float}" \
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
      -o "${cpp_bin}" "${cpp_src}" \
      && "${cpp_bin}"
  ) &> "${report}"
  local case_status=$?

  cat "${report}"
  echo "------------------------------------"
  echo

  return "${case_status}"
}

_bench_run_case_mojo() {
  local source="$1"
  local precision="$2"
  local sample_rate="$3"
  local buffer_size="$4"

  _bench_require_precision "${precision}" || return 1

  local mojo_src
  local mojo_bin
  local report
  local csv_path
  local dtype
  local name

  mojo_src="$(_bench_mojo_src "${source}")"
  mojo_bin="$(_bench_mojo_bin "${source}")"
  report="$(_bench_tab_path mojo "${source}" "${precision}" "${sample_rate}" "${buffer_size}")"
  csv_path="$(_bench_tmp_csv_path mojo "${source}")"
  dtype="$(_bench_precision_mojo_dtype "${precision}")"
  name="$(_bench_dsp_name "${source}")"

  _bench_require_file "${mojo_src}" || return 1
  mkdir -p "$(dirname "${report}")" "$(dirname "${mojo_bin}")" "$(dirname "${csv_path}")"

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running mojo:${BENCH_RUN_NAME}(${name}, ${precision}, sr=${sample_rate}, bs=${buffer_size}, csv=1)"

  (
    pixi run mojo build \
      "${BENCH_MOJO_OPT[@]}" \
      -D BENCH_LANG=mojo \
      -D BENCH_DSP="${name}" \
      -D BENCH_CASE="${BENCH_RUN_NAME}" \
      -D BENCH_OPTIM="${BENCH_OPTIM:-O3}" \
      -D FAUST_DTYPE="${dtype}" \
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
      -o "${mojo_bin}" "${mojo_src}" \
      && "${mojo_bin}"
  ) &> "${report}"
  local case_status=$?

  cat "${report}"
  echo "------------------------------------"
  echo

  return "${case_status}"
}

# ------------------------------------------
# Plot helpers
# ------------------------------------------

_bench_plot_require_name() {
  local plot_name="$1"

  if [[ -z "${plot_name}" ]]; then
    echo "usage: bench_plot <plot_name>"
    return 1
  fi
}

_bench_plot_from_csv() {
  local csv_src="$1"
  local plot_out="$2"

  _bench_require_file "${csv_src}" || return 1
  mkdir -p "$(dirname "${plot_out}")"

  pixi run python "${BENCH_SCRIPT_DIR}/plot.py" "${csv_src}" \
    --case "${BENCH_RUN_NAME:-run}" \
    --x combo \
    --y out_samp_per_s \
    --series language,precision \
    --out "${plot_out}" \
    --title "Faust Benchmark"
}

# ------------------------------------------
# Snapshot helpers
# ------------------------------------------

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

  if [[ -d "${BENCH_REPORT_DIR}/cpp" ]]; then
    mkdir -p "${snapshot_path}/cpp"
    cp "${BENCH_REPORT_DIR}/cpp"/*.tab "${snapshot_path}/cpp/" 2>/dev/null || true
  fi

  if [[ -d "${BENCH_REPORT_DIR}/mojo" ]]; then
    mkdir -p "${snapshot_path}/mojo"
    cp "${BENCH_REPORT_DIR}/mojo"/*.tab "${snapshot_path}/mojo/" 2>/dev/null || true
  fi

  if [[ -d "${BENCH_PLOT_DIR}" ]]; then
    mkdir -p "${snapshot_path}/plots"
    cp "${BENCH_PLOT_DIR}"/*.svg "${snapshot_path}/plots/" 2>/dev/null || true
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
    echo "workspace: ${BENCH_ROOT}"
    echo "git_branch: $(git -C "${BENCH_FAUST_ROOT}" branch --show-current 2>/dev/null || echo unknown)"
    echo "git_commit: $(git -C "${BENCH_FAUST_ROOT}" rev-parse --short HEAD 2>/dev/null || echo unknown)"
    echo "languages: ${BENCH_LANGS[*]}"
    echo "sample_rates_hz: ${BENCH_SAMPLE_RATES[*]}"
    echo "buffer_sizes: ${BENCH_BUFFER_SIZES[*]}"
    echo "precisions: ${BENCH_PRECISIONS[*]}"
    echo "cpp_opt: ${BENCH_CPP_OPT[*]}"
    echo "mojo_opt: ${BENCH_MOJO_OPT[*]}"
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

# ------------------------------------------
# LLVM helpers
# ------------------------------------------

_bench_llvm_supports_lang() {
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

_bench_llvm_gen() {
  local source
  local lang

  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      if ! _bench_llvm_supports_lang "${lang}"; then
        echo "skipped: language '${lang}' does not support LLVM IR generation in this framework"
        continue
      fi

      case "${lang}" in
        cpp)
          _bench_llvm_gen_cpp "${source}" || return 1
          ;;
        mojo)
          _bench_llvm_gen_mojo "${source}" || return 1
          ;;
      esac
    done
  done
}

_bench_llvm_gen_cpp() {
  local source="$1"
  local precision
  local cpp_src
  local ir_path
  local faust_float
  local name

  _bench_generate_cpp "${source}" || return 1

  cpp_src="$(_bench_cpp_src "${source}")"
  name="$(_bench_dsp_name "${source}")"

  for precision in "${BENCH_PRECISIONS[@]}"; do
    faust_float="$(_bench_precision_cpp_macro "${precision}")"
    ir_path="$(_bench_cpp_llvm_ir "${source}" "${precision}")"

    mkdir -p "$(dirname "${ir_path}")"

    clang++ -std=gnu++23 \
      -S -emit-llvm \
      -I"${BENCH_CPP_ARCH_DIR}" \
      "${BENCH_CPP_OPT[@]}" \
      -DBENCH_LANG=\"cpp\" \
      -DBENCH_DSP=\"${name}\" \
      -DBENCH_CASE=\"llvm\" \
      -DBENCH_OPTIM=\"${BENCH_OPTIM:-O3}\" \
      -DFAUSTFLOAT="${faust_float}" \
      -DWRITE_CSV=0 \
      -DFILL_INPUTS=1 \
      -DSAMP_RATE="s32(${BENCH_LLVM_SAMPLE_RATE:-48000})" \
      -DBUFF_SIZE="s32(${BENCH_LLVM_BUFFER_SIZE:-64})" \
      -DWARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
      -DCOMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-1000000}" \
      -DMIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
      -DMAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
      -DMAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
      -Wall -Wextra -Wno-unused-parameter -pedantic \
      -o "${ir_path}" "${cpp_src}" || return 1

    echo "wrote ${ir_path}"
  done

  _bench_clean_tmp_files cpp "${source}"
}

_bench_llvm_gen_mojo() {
  local source="$1"
  local precision
  local mojo_src
  local ir_path
  local dtype
  local name
  _bench_generate_mojo "${source}" || return 1
  mojo_src="$(_bench_mojo_src "${source}")"
  name="$(_bench_dsp_name "${source}")"
  for precision in "${BENCH_PRECISIONS[@]}"; do
    dtype="$(_bench_precision_mojo_dtype "${precision}")"
    ir_path="$(_bench_mojo_llvm_ir "${source}" "${precision}")"
    mkdir -p "$(dirname "${ir_path}")"
    pixi run mojo build \
      "${BENCH_MOJO_OPT[@]}" \
      -D BENCH_LANG=mojo \
      -D BENCH_DSP="${name}" \
      -D BENCH_CASE=llvm \
      -D BENCH_OPTIM="${BENCH_OPTIM:-O3}" \
      -D FAUST_DTYPE="${dtype}" \
      -D WRITE_CSV=False \
      -D FILL_INPUTS=True \
      -D SAMP_RATE="${BENCH_LLVM_SAMPLE_RATE:-48000}" \
      -D BUFF_SIZE="${BENCH_LLVM_BUFFER_SIZE:-64}" \
      -D WARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
      -D COMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-100000}" \
      -D MIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
      -D MAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
      -D MAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
      --emit llvm \
      -o "${ir_path}" "${mojo_src}" || return 1
    echo "wrote ${ir_path}"
  done
  _bench_clean_tmp_files mojo "${source}"
}

# ------------------------------------------
# Assembly helpers
# ------------------------------------------

_bench_asm_supports_lang() {
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

_bench_asm_gen() {
  local source
  local lang
  for source in "${BENCH_RUN_SOURCES[@]}"; do
    for lang in "${BENCH_RUN_LANGS[@]}"; do
      if ! _bench_asm_supports_lang "${lang}"; then
        echo "skipped: language '${lang}' does not support assembly generation in this framework"
        continue
      fi
      case "${lang}" in
        cpp)
          _bench_asm_gen_cpp "${source}" || return 1
          ;;
        mojo)
          _bench_asm_gen_mojo "${source}" || return 1
          ;;
      esac
    done
  done
}

_bench_cpp_asm() {
  local name="$1"
  local precision="$2"
  name="$(_bench_dsp_name "${name}")"
  echo "${BENCH_REPORT_DIR}/asm/cpp/${name}_${precision}.s"
}

_bench_mojo_asm() {
  local name="$1"
  local precision="$2"
  name="$(_bench_dsp_name "${name}")"
  echo "${BENCH_REPORT_DIR}/asm/mojo/${name}_${precision}.s"
} 

_bench_asm_gen_cpp() {
  local source="$1"
  local precision
  local cpp_src
  local asm_path
  local faust_float
  local name
  _bench_generate_cpp "${source}" || return 1
  cpp_src="$(_bench_cpp_src "${source}")"
  name="$(_bench_dsp_name "${source}")"
  for precision in "${BENCH_PRECISIONS[@]}"; do
    faust_float="$(_bench_precision_cpp_macro "${precision}")"
    asm_path="$(_bench_cpp_asm "${source}" "${precision}")"
    mkdir -p "$(dirname "${asm_path}")"
    clang++ -std=gnu++23 \
      -S \
      -I"${BENCH_CPP_ARCH_DIR}" \
      "${BENCH_CPP_OPT[@]}" \
      -DBENCH_LANG=\"cpp\" \
      -DBENCH_DSP=\"${name}\" \
      -DBENCH_CASE=\"asm\" \
      -DBENCH_OPTIM=\"${BENCH_OPTIM:-O3}\" \
      -DFAUSTFLOAT="${faust_float}" \
      -DWRITE_CSV=0 \
      -DFILL_INPUTS=1 \
      -DSAMP_RATE="s32(${BENCH_ASM_SAMPLE_RATE:-${BENCH_LLVM_SAMPLE_RATE:-48000}})" \
      -DBUFF_SIZE="s32(${BENCH_ASM_BUFFER_SIZE:-${BENCH_LLVM_BUFFER_SIZE:-64}})" \
      -DWARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
      -DCOMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-100000}" \
      -DMIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
      -DMAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
      -DMAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
      -Wall -Wextra -Wno-unused-parameter -pedantic \
      -o "${asm_path}" "${cpp_src}" || return 1
    echo "wrote ${asm_path}"
  done
  _bench_clean_tmp_files cpp "${source}"
}

_bench_asm_gen_mojo() {
  local source="$1"
  local precision
  local mojo_src
  local asm_path
  local dtype
  local name
  _bench_generate_mojo "${source}" || return 1
  mojo_src="$(_bench_mojo_src "${source}")"
  name="$(_bench_dsp_name "${source}")"
  for precision in "${BENCH_PRECISIONS[@]}"; do
    dtype="$(_bench_precision_mojo_dtype "${precision}")"
    asm_path="$(_bench_mojo_asm "${source}" "${precision}")"
    mkdir -p "$(dirname "${asm_path}")"
    pixi run mojo build \
      "${BENCH_MOJO_OPT[@]}" \
      -D BENCH_LANG=mojo \
      -D BENCH_DSP="${name}" \
      -D BENCH_CASE=asm \
      -D BENCH_OPTIM="${BENCH_OPTIM:-O3}" \
      -D FAUST_DTYPE="${dtype}" \
      -D WRITE_CSV=False \
      -D FILL_INPUTS=True \
      -D SAMP_RATE="${BENCH_ASM_SAMPLE_RATE:-${BENCH_LLVM_SAMPLE_RATE:-48000}}" \
      -D BUFF_SIZE="${BENCH_ASM_BUFFER_SIZE:-${BENCH_LLVM_BUFFER_SIZE:-64}}" \
      -D WARMUP_ITERS="${BENCH_WARMUP_ITERS:-50}" \
      -D COMPUTE_ITERS="${BENCH_COMPUTE_ITERS:-100000}" \
      -D MIN_RUNTIME_SECS="${BENCH_MIN_RUNTIME_SECS:-1}" \
      -D MAX_RUNTIME_SECS="${BENCH_MAX_RUNTIME_SECS:-60}" \
      -D MAX_BATCH_SIZE="${BENCH_MAX_BATCH_SIZE:-10000}" \
      --emit asm \
      -o "${asm_path}" "${mojo_src}" || return 1
    echo "wrote ${asm_path}"
  done
  _bench_clean_tmp_files mojo "${source}"
}

# ------------------------------------------
# Type helpers
# ------------------------------------------

_bench_precision_cpp_macro() {
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

_bench_precision_mojo_dtype() {
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
