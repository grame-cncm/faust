#file(GLOB SOURCES *cpp)
file(GLOB SUB_SOURCES */*cpp)
file(GLOB SUB_SUB_SOURCES */*/*cpp)
file(GLOB LOKI_SOURCES ../libraries/loki/*cpp)

include_directories(boxes documentator draw draw/device draw/schema errors evaluate extended generator normalize parallelize
    parser patternmatcher propagate signals tlib utils ../libraries)


exec_program(llvm-config ARGS --includedir OUTPUT_VARIABLE LLVM_DIR)
exec_program(llvm-config ARGS --libs OUTPUT_VARIABLE LLVM_LIBS)
exec_program(llvm-config ARGS --version OUTPUT_VARIABLE LLVM_VERSION)
exec_program(llvm-config ARGS --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS)

if (${LLVM_VERSION} STREQUAL 3.0)
    set(LLVM_VERSION LLVM_30)
elseif(${LLVM_VERSION} STREQUAL 2.9)
    set(LLVM_VERSION LLVM_29)
endif()

include_directories(${LLVM_DIR})

if (${CMAKE_COMPILER_IS_GNUCXX})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wuninitialized -Wno-parentheses -Wnon-virtual-dtor")
endif()

# STATIC LIBFAUST
add_library(libfaust-static STATIC libmain.cpp ${SUB_SOURCES}  ${SUB_SUB_SOURCES} ${LOKI_SOURCES})
set_target_properties(libfaust-static PROPERTIES OUTPUT_NAME faust)
set_target_properties(libfaust-static PROPERTIES PREFIX "lib")
set_property(TARGET libfaust-static
    APPEND
    PROPERTY COMPILE_DEFINITIONS INSTALL_PREFIX="/usr/local" __STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS ${LLVM_VERSION} 
)

# SHARED LIBFAUST
add_library(libfaust SHARED libmain.cpp ${SUB_SOURCES}
${SUB_SUB_SOURCES} ${LOKI_SOURCES})
set_target_properties(libfaust PROPERTIES OUTPUT_NAME faust)
set_target_properties(libfaust PROPERTIES PREFIX "lib")
set_property(TARGET libfaust
    APPEND
    PROPERTY LINK_FLAGS ${LLVM_LDFLAGS}
)
set_property(TARGET libfaust
    APPEND
    PROPERTY COMPILE_DEFINITIONS INSTALL_PREFIX="/usr/local" __STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS ${LLVM_VERSION} 
)
target_link_libraries(libfaust pthread dl)
target_link_libraries(libfaust ${LLVM_LIBS})

# COMMANDLINE FAUST EXECUTABLE
add_executable(faust main.cpp)
set_property(TARGET faust
    APPEND
    PROPERTY LINK_FLAGS ${LLVM_LDFLAGS}
)
set_property(TARGET faust
    APPEND
    PROPERTY COMPILE_DEFINITIONS INSTALL_PREFIX="/usr/local" __STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS ${LLVM_VERSION} 
)

target_link_libraries(faust libfaust-static)
target_link_libraries(faust pthread dl)
target_link_libraries(faust ${LLVM_LIBS})

if (CTAGS AND NOT CMAKE_GENERATOR STREQUAL Xcode)
       add_custom_command (TARGET faust POST_BUILD COMMAND ctags ARGS -R .
                                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMENT "Creating tags" VERBATIM)
endif()


install(TARGETS faust
        DESTINATION "bin"
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
