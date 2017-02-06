cmake_minimum_required(VERSION 3.4.1)
add_library( dsp_faust SHARED src/main/cpp/java_interface_wrap.cpp src/main/cpp/DspFaust.cpp )
find_library( log-lib log )
target_link_libraries( dsp_faust ${log-lib} )