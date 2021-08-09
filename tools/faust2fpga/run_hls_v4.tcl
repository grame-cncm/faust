open_project -reset faust_v4_ip
set_top faust_v4
add_files faust_v4_ip/faust_v4.cpp
#add_files -tb faust_ip_hls/project_1/faust_bench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"

open_solution -reset "faust_v4"
set_part {xc7z010clg400-1}
create_clock -period 8

#csim_design
csynth_design
#cosim_design
export_design -rtl vhdl -format ip_catalog

exit
