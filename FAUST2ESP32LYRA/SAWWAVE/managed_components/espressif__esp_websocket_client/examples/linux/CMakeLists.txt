cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(common_component_dir ../../../../common_components)
set(EXTRA_COMPONENT_DIRS
   ../..
  "${common_component_dir}/linux_compat/esp_timer"
  "${common_component_dir}/linux_compat/freertos"
   $ENV{IDF_PATH}/examples/protocols/linux_stubs/esp_stubs
   $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)

set(COMPONENTS main)
project(websocket)
