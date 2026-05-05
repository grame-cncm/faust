#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo "usage: $0 <cpp-source> [extra-cpp-flags...]"
  exit 1
fi

CPP_SRC="$1"
shift

COMMON_FLAGS=("$@")
CPP_BIN="report/cpp/bench_bin"

rm -f report/cpp/*report*
mkdir -p report/cpp/

run_case() {
  local precision="$1"
  local opt="$2"
  local report="$3"
  shift 3

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running benchcpp(${precision}, ${opt})"
  (
    clang++ -std=gnu++23 "${COMMON_FLAGS[@]}" "$@" \
      -Wall -Wextra -Wno-unused-parameter -pedantic "-${opt}" \
      -o "${CPP_BIN}" "${CPP_SRC}" \
      && "./${CPP_BIN}"
  ) &> "${report}"

  cat "${report}"
  echo "------------------------------------"
  echo
}

run_case "float"  "O0" "report/cpp/report_float_O0"
run_case "float"  "O3" "report/cpp/report_float_O3"
run_case "double" "O0" "report/cpp/report_double_O0" -DFAUSTFLOAT=double
run_case "double" "O3" "report/cpp/report_double_O3" -DFAUSTFLOAT=double

rm -f "${CPP_BIN}"
