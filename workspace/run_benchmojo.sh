MOJO_SRC="${MOJO_SRC:-test_benchmojo.mojo}"
MOJO_BIN="report/mojo/bench_bin"

run_case() {
  local dtype_label="$1"
  local dtype_define="$2"
  local opt="$3"
  local report="$4"
  local opt_level="${opt#O}"

  echo
  echo ">>>>>>>>>>>>>>>>>>>>>>> running benchmojo(${dtype_label}, ${opt})"
  (
    pixi run mojo build -O "${opt_level}" \
      -D FILL_INPUTS=True \
      -D FAUST_DTYPE="${dtype_define}" \
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
