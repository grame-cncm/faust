#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo "usage: $0 <mojo-source> [extra-mojo-flags...]"
  exit 1
fi

MOJO_SRC="$1"
shift

COMMON_FLAGS=("$@")
MOJO_BIN="report/mojo/bench_bin"

rm -f report/mojo/*report*
mkdir -p report/mojo/

run_case() {
  local precision="$1"
  local dtype="$2"
  local opt="$3"
  local report="$4"
  local opt_level="${opt#O}"
  shift 4

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running benchmojo(${precision}, ${opt})"
  (
    pixi run mojo build -O "${opt_level}" \
      "${COMMON_FLAGS[@]}" \
      "$@" \
      -D FAUST_DTYPE="${dtype}" \
      -o "${MOJO_BIN}" "${MOJO_SRC}" \
      && "./${MOJO_BIN}"
  ) &> "${report}"

  cat "${report}"
  echo "------------------------------------"
  echo
}

run_case "float"  "DType.float32" "O0" "report/mojo/report_float_O0"
run_case "float"  "DType.float32" "O3" "report/mojo/report_float_O3"
run_case "double" "DType.float64" "O0" "report/mojo/report_double_O0"
run_case "double" "DType.float64" "O3" "report/mojo/report_double_O3"

rm -f "${MOJO_BIN}"
