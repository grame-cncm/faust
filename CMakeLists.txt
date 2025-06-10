cmake_minimum_required(VERSION 3.10)
project(gainclap)

set(CMAKE_CXX_STANDARD 17)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../external/clap-helpers/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../../external/clap-helpers/clap/include
)

add_executable(gainclap ../../build/gain/gain_clap.cpp)

