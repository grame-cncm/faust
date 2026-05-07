#!/usr/bin/env bash

# CSV helpers.
#
# This file is meant to be sourced by script/source.sh.
# It delegates CSV merge/update logic to script/csv.py.

bench_csv_merge() {
  local lang="$1"
  local dsp="$2"
  local bench_case="$3"

  local tmp_csv
  local name

  name="$(bench_dsp_name "${dsp}")"
  tmp_csv="$(bench_tmp_csv_path "${lang}" "${dsp}" "${bench_case}")"

  if [[ ! -f "${tmp_csv}" ]]; then
    echo "error: missing temporary CSV fragment: ${tmp_csv}"
    return 1
  fi

  pixi run python "${BENCH_SCRIPT_DIR}/csv.py" merge \
    --main "${BENCH_CSV}" \
    --tmp "${tmp_csv}" \
    --language "${lang}" \
    --dsp "${name}" \
    --case "${bench_case}"
}
