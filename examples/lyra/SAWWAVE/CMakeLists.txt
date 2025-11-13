cmake_minimum_required(VERSION 3.5)

include($ENV{ADF_PATH}/CMakeLists.txt)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(EXTRA_COMPONENT_DIRS
    $ENV{ADF_PATH}/components
    $ENV{ADF_PATH}/components/esp_peripherals)
project(faustcpp)
