cmake_minimum_required (VERSION 2.6)
project (faust)

enable_testing()

# uninstall support
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")


add_subdirectory(compiler)

add_subdirectory(examples)
add_subdirectory(tests/codegen-tests)
add_subdirectory(tests/error-tests)
add_subdirectory(tests/warning-tests)
add_subdirectory(tests/pass-tests)
