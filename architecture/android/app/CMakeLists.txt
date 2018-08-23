cmake_minimum_required(VERSION 3.4.1)

# activate android code
add_definitions( -DANDROID_DRIVER )

# add other libs
add_library( dsp_faust SHARED src/main/cpp/java_interface_wrap.cpp src/main/cpp/DspFaust.cpp )
find_library( log-lib log )

# linking
target_link_libraries( dsp_faust ${log-lib} )
