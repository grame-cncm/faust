set(OSCCTRL false)
cmake_minimum_required(VERSION 3.4.1)

# activate android code
if(OSCCTRL)
add_definitions(-DANDROID_DRIVER -DOSCCTRL)
elseif(NOT OSCCTRL)
add_definitions( -DANDROID_DRIVER )
endif(OSCCTRL)

# including OSClib
if(OSCCTRL)
add_library( libOSCFaust SHARED IMPORTED )
set_target_properties( libOSCFaust PROPERTIES IMPORTED_LOCATION /usr/local/share/faust/osclib/android/libs/${ANDROID_ABI}/libOSCFaust.so )
endif(OSCCTRL)


# add other libs
add_library( dsp_faust SHARED src/main/cpp/java_interface_wrap.cpp src/main/cpp/DspFaust.cpp )
find_library( log-lib log )

# linking
if(OSCCTRL)
target_link_libraries( dsp_faust libOSCFaust ${log-lib} )
elseif(NOT OSCCTRL)
target_link_libraries( dsp_faust ${log-lib} )
endif(OSCCTRL)
