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

option(EXTENSIVE_TESTSUITE "run extensive testsuite (can take some time)")
option(CTAGS "Generate ctags." ON)
option(OSX_FAT_BINARIES "Enable fat binaries on OS X" ON)
option(BUILD_FAUST_SHARED "Build shared library version of faust" ON)
option(BUILD_FAUST_CLI "Build faust CLI" ON)

add_subdirectory(compiler)

add_subdirectory(examples)
add_subdirectory(tests/codegen-tests)
add_subdirectory(tests/error-tests)
add_subdirectory(tests/warning-tests)
add_subdirectory(tests/pass-tests)


install(DIRECTORY architecture
  DESTINATION lib/faust
)

install(DIRECTORY examples
  DESTINATION share/doc/faust/examples
)

if(APPLE AND OSX_FAT_BINARIES)
 set(CMAKE_OSX_ARCHITECTURES i386;x86_64 CACHE STRING "Build
architectures for OSX" FORCE)
endif()
