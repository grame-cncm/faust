file(GLOB SOURCES *cpp)
file(GLOB SUB_SOURCES */*cpp)
file(GLOB SUB_SUB_SOURCES */*/*cpp)

include_directories(boxes documentator draw draw/device draw/schema errors evaluate extended generator normalize parallelize
    parser patternmatcher propagate signals tlib utils)

exec_program(llvm-config ARGS --includedir OUTPUT_VARIABLE LLVM_DIR)
exec_program(llvm-config ARGS --libs OUTPUT_VARIABLE LLVM_LIBS)

include_directories(${LLVM_DIR})


if (${CMAKE_COMPILER_IS_GNUCXX})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wuninitialized -Wno-parentheses -Wnon-virtual-dtor")
endif()

add_executable(faust ${SOURCES} ${SUB_SOURCES}  ${SUB_SUB_SOURCES})

set_property(TARGET faust
    APPEND
    PROPERTY COMPILE_DEFINITIONS INSTALL_PREFIX="/usr/local" __STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS
)

target_link_libraries(faust pthread dl)
target_link_libraries(faust ${LLVM_LIBS})
