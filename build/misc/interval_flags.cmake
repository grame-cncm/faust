# The interval library proves its bounds under IEEE binary arithmetic : its sources
# must be compiled without contraction nor reassociation, and with wrapping signed
# integers (the README of the interval library). Applied to its sources only.
file (GLOB INTERVAL_SRC ${SRCDIR}/interval/*.cpp)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set_source_files_properties (${INTERVAL_SRC} PROPERTIES COMPILE_FLAGS "-fno-fast-math -ffp-contract=off -fwrapv")
elseif (MSVC)
    set_source_files_properties (${INTERVAL_SRC} PROPERTIES COMPILE_FLAGS "/fp:strict")
endif ()
