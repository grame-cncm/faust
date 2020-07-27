set(OSCCTRL false)
cmake_minimum_required(VERSION 3.4.1)

if(OSCCTRL)
    add_library( libOSCFaust SHARED IMPORTED )
    set_target_properties( libOSCFaust PROPERTIES IMPORTED_LOCATION /usr/local/share/faust/osclib/android/libs/${ANDROID_ABI}/libOSCFaust.so )
endif(OSCCTRL)

add_library( dsp_faust SHARED src/main/cpp/java_interface_wrap.cpp src/main/cpp/DspFaust.cpp )
find_library( log-lib log )

if(OSCCTRL)
    target_link_libraries( dsp_faust libOSCFaust oboe ${log-lib} )
elseif(NOT OSCCTRL)
    target_link_libraries( dsp_faust oboe ${log-lib} )
endif(OSCCTRL)

# Set the path to the Oboe directory.
set (OBOE_DIR oboe)

# Add the Oboe library as a subdirectory in your project.
add_subdirectory (${OBOE_DIR} ./oboe)

# Specify the path to the Oboe header files.
include_directories (${OBOE_DIR}/include)
