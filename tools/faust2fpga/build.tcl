open_project -quiet faust_v4_project/faust_v4_project.xpr

set proj_dir [get_property directory [current_project]]

#generate_target all [get_files main.bd]
#export_ip_user_files -of_objects [get_files main.bd] -no_script -sync -force -quiet
#create_ip_run [get_files -of_objects [get_fileset sources_1] main.bd]
#synth_design
#opt_design
#place_design
#route_design

#synth_design -top main_wrapper -part xc7z010clg400-1
#synth_design -top [lindex [find_top] 0] -part xc7z010clg400-1
#opt_design
#place_design
#route_design

reset_run synth_1
launch_runs synth_1
wait_on_run synth_1

reset_run impl_1
launch_runs -to_step write_bitstream impl_1
wait_on_run impl_1

#write_bitstream -force master.bit
