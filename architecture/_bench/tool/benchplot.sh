#!/bin/bash

CSV_SRC="${1:-report/mojo/report.csv}"

mkdir -p report/plots

pixi run python tool/benchplot.py "${CSV_SRC}" \
  --case buffer_sweep \
  --x buff_size \
  --y ns_per_frame \
  --series language,precision,opt \
  --out report/plots/buff_size_ns_per_frame.svg \
  --title "Faust benchmark: ns/frame by buffer size"

pixi run python tool/benchplot.py "${CSV_SRC}" \
  --case sample_rate_sweep \
  --x samp_rate \
  --y ns_per_frame \
  --series language,precision,opt \
  --out report/plots/samp_rate_ns_per_frame.svg \
  --title "Faust benchmark: ns/frame by sample rate"
