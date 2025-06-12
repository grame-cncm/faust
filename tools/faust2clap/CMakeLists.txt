#min required version of cmake for compatibility
cmake_minimum_required(VERSION 3.15) 
#declaration of project and languages in use
project(faust2clap LANGUAGES C CXX)


#specify c++17 and macos deployment target
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "macOS target")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)



#avoid installing clap sdk during build
set(CLAP_NO_INSTALL ON CACHE BOOL "" FORCE)


#enable post-build copying of plugin to standard location
set(COPY_AFTER_BUILD ON CACHE BOOL "Copy the CLAP plugin to system folder after build")



#include required external libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/../../external/clap-sdk clap-sdk)
add_subdirectory(${CMAKE_SOURCE_DIR}/../../external/clap-helpers clap-helpers)


#define plugin name and generated source
set(GENERATED_NAME gain)
set(GENERATED_CPP ${CMAKE_SOURCE_DIR}/../../build/${GENERATED_NAME}/${GENERATED_NAME}_clap.cpp)


#declare the plugin module
add_library(${GENERATED_NAME} MODULE ${GENERATED_CPP})



#add plugin.cc to get full implementation of clap::helpers::Plugin<>
target_sources(${GENERATED_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/plugin.cc
)


#include necessary directories for compilation
target_include_directories(${GENERATED_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/../../
  ${CMAKE_SOURCE_DIR}/../../build
  ${CMAKE_SOURCE_DIR}/../../architecture
  ${CMAKE_SOURCE_DIR}/../../architecture/faust/dsp
  ${CMAKE_SOURCE_DIR}/../../external/clap-helpers/include
  ${CMAKE_SOURCE_DIR}/../../external/clap-sdk/include
)


#link against the clap core library and clap helpers
target_link_libraries(${GENERATED_NAME} PRIVATE
  clap
  clap-helpers
)


#generate info.plist from template
configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/${GENERATED_NAME}.plist.in
  ${CMAKE_CURRENT_BINARY_DIR}/${GENERATED_NAME}.plist @ONLY
)


#set bundle properties for macos
set_target_properties(${GENERATED_NAME} PROPERTIES
  OUTPUT_NAME ${GENERATED_NAME}
  BUNDLE TRUE
  BUNDLE_EXTENSION clap
  MACOSX_BUNDLE_GUI_IDENTIFIER org.faust.${GENERATED_NAME}
  MACOSX_BUNDLE_BUNDLE_NAME ${GENERATED_NAME}
  MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
  MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
  MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/${GENERATED_NAME}.plist
)


#ccopy bundle to user's plugin directory post-build
if (APPLE AND COPY_AFTER_BUILD)
  message(STATUS "Will copy plugin after every build")
  set(products_folder ${CMAKE_BINARY_DIR})
  add_custom_command(TARGET ${GENERATED_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Installing ${products_folder}/${GENERATED_NAME}.clap to ~/Library/Audio/Plug-Ins/CLAP/"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$ENV{HOME}/Library/Audio/Plug-Ins/CLAP"
    COMMAND ${CMAKE_COMMAND} -E rm -rf "$ENV{HOME}/Library/Audio/Plug-Ins/CLAP/${GENERATED_NAME}.clap"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${products_folder}/${GENERATED_NAME}.clap"
      "$ENV{HOME}/Library/Audio/Plug-Ins/CLAP/${GENERATED_NAME}.clap"
  )
endif()
