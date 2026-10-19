# Links a JIT program against an installed LLVM package through its CMake
# exports, as a client of the package would (see build-llvm.yml).
cmake_minimum_required (VERSION 3.20)
# C is enabled for the find modules LLVMConfig.cmake runs.
project (llvm_smoke C CXX)

find_package (LLVM REQUIRED CONFIG)
message (STATUS "LLVM ${LLVM_PACKAGE_VERSION} from ${LLVM_DIR}")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)

add_executable (llvm-smoke llvm-smoke.cpp)
separate_arguments (LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
target_compile_options (llvm-smoke PRIVATE ${LLVM_DEFINITIONS_LIST})
target_include_directories (llvm-smoke PRIVATE ${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames (LLVM_SMOKE_LIBS orcjit native)
target_link_libraries (llvm-smoke PRIVATE ${LLVM_SMOKE_LIBS})
