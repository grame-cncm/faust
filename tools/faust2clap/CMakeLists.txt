cmake_minimum_required(VERSION 3.15)
project(faust2clap LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "macOS target")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CLAP_NO_INSTALL ON CACHE BOOL "" FORCE)
set(COPY_AFTER_BUILD ON CACHE BOOL "Copy the CLAP plugin to system folder after build")

# Define root for local install
set(FAUST2CLAP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})


# --------------------------------------------------
# Locate Faust headers for global builds
# --------------------------------------------------
execute_process(COMMAND faust --includedir
                OUTPUT_VARIABLE FAUST_INCLUDE_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "Faust include dir: ${FAUST_INCLUDE_DIR}")


# -------------------------------
# External Dependencies
# -------------------------------

# Clap SDK
add_subdirectory(${FAUST2CLAP_ROOT}/external/clap-sdk clap-sdk)
add_subdirectory(${FAUST2CLAP_ROOT}/external/clap-helpers clap-helpers)

# GUI glue lib
add_library(faust_gui_glue STATIC ${FAUST2CLAP_ROOT}/architecture/clap/faust_gui_glue.cpp)

target_include_directories(faust_gui_glue PRIVATE
  ${FAUST2CLAP_ROOT}/architecture
  ${FAUST2CLAP_ROOT}/architecture/faust/gui
  ${FAUST_INCLUDE_DIR} 
)

# RtMidi (hardcoded Homebrew path)
set(RTMIDI_LIBRARY /opt/homebrew/Cellar/rtmidi/6.0.0/lib/librtmidi.dylib CACHE FILEPATH "RtMidi lib")
set(RTMIDI_INCLUDE_DIR /opt/homebrew/Cellar/rtmidi/6.0.0/include CACHE PATH "RtMidi include")
message(STATUS "Using hardcoded RtMidi:")
message(STATUS "  Library: ${RTMIDI_LIBRARY}")
message(STATUS "  Include: ${RTMIDI_INCLUDE_DIR}")





# -------------------------------
# Discover and Build Plugins
# -------------------------------

# This assumes that faust2clap.py puts sources in: <working_dir>/build/<plugin>/
file(GLOB_RECURSE FAUST_SOURCES "${CMAKE_BINARY_DIR}/*_clap.cpp")

foreach(FAUST_CPP ${FAUST_SOURCES})
  get_filename_component(FILENAME ${FAUST_CPP} NAME_WE)
  string(REPLACE "_clap" "" PLUGIN_NAME ${FILENAME})

  add_library(${PLUGIN_NAME} MODULE ${FAUST_CPP})

  target_sources(${PLUGIN_NAME} PRIVATE ${FAUST2CLAP_ROOT}/architecture/clap/plugin.cc)

  target_include_directories(${PLUGIN_NAME} PRIVATE
    ${CMAKE_BINARY_DIR}
    ${FAUST2CLAP_ROOT}/architecture
    ${FAUST2CLAP_ROOT}/architecture/faust/gui
    ${FAUST_INCLUDE_DIR}
    ${FAUST2CLAP_ROOT}/architecture/faust/midi
    ${FAUST2CLAP_ROOT}/architecture/faust/dsp
    ${FAUST2CLAP_ROOT}/external/clap-helpers/include
    ${FAUST2CLAP_ROOT}/external/clap-sdk/include
    ${RTMIDI_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/${PLUGIN_NAME}
  )

  target_link_libraries(${PLUGIN_NAME} PRIVATE
    clap
    clap-helpers
    faust_gui_glue
    ${RTMIDI_LIBRARY}
  )

  configure_file(
    ${FAUST2CLAP_ROOT}/cmake/generic.plist.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_NAME}.plist @ONLY
  )

  set_target_properties(${PLUGIN_NAME} PROPERTIES
    OUTPUT_NAME ${PLUGIN_NAME}
    BUNDLE TRUE
    BUNDLE_EXTENSION clap
    MACOSX_BUNDLE_GUI_IDENTIFIER org.faust.${PLUGIN_NAME}
    MACOSX_BUNDLE_BUNDLE_NAME ${PLUGIN_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_NAME}.plist
  )

  if (APPLE AND COPY_AFTER_BUILD)
    message(STATUS "Will copy plugin '${PLUGIN_NAME}' after build")
    set(products_folder ${CMAKE_BINARY_DIR})
    add_custom_command(TARGET ${PLUGIN_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E echo "Installing ${products_folder}/${PLUGIN_NAME}.clap to ~/Library/Audio/Plug-Ins/CLAP/"
      COMMAND ${CMAKE_COMMAND} -E make_directory "$ENV{HOME}/Library/Audio/Plug-Ins/CLAP"
      COMMAND ${CMAKE_COMMAND} -E rm -rf "$ENV{HOME}/Library/Audio/Plug-Ins/CLAP/${PLUGIN_NAME}.clap"
      COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${products_folder}/${PLUGIN_NAME}.clap"
        "$ENV{HOME}/Library/Audio/Plug-Ins/CLAP/${PLUGIN_NAME}.clap"
    )
  endif()
endforeach()

# Optional: install the faust2clap CLI
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/faust2clap.sh
        DESTINATION bin
        RENAME faust2clap)