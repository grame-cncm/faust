open_hw
connect_hw_server -url localhost:3121
#current_hw_target
#get_hw_targets
open_hw_target
current_hw_device [lindex [get_hw_devices] 1]
set curr_directory  [exec pwd]
set bitstream_syfala build/faust_v4_project/faust_v4_project.runs/impl_1/main_wrapper.bit
puts "flashing: ${curr_directory}/${bitstream_syfala}"
set_property PROGRAM.FILE {build/faust_v4_project/faust_v4_project.runs/impl_1/main_wrapper.bit} [lindex [get_hw_devices] 1]
program_hw_devices [lindex [get_hw_devices] 1]

