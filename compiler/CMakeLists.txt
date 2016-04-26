#file(GLOB SOURCES *cpp)
file(GLOB_RECURSE SOURCES */*cpp)
file(GLOB LOKI_SOURCES ../libraries/loki/*cpp)

include_directories(boxes documentator draw draw/device draw/schema errors evaluate extended generator normalize parallelize
    parser patternmatcher propagate signals tlib utils ../libraries . ../architecture)
find_package(OpenSSL REQUIRED)
find_program(LLVM_CONFIG llvm-config HINTS /usr/bin /usr/local/bin /usr/local/opt/llvm/bin)
if(NOT LLVM_CONFIG)
    message(FATAL_ERROR "Faust2 requires LLVM tooling to be present in the path")
endif()
exec_program(${LLVM_CONFIG} ARGS --includedir OUTPUT_VARIABLE LLVM_DIR)
exec_program(${LLVM_CONFIG} ARGS --libs OUTPUT_VARIABLE LLVM_LIBS)
exec_program(${LLVM_CONFIG} ARGS --version OUTPUT_VARIABLE LLVM_VERSION)
exec_program(${LLVM_CONFIG} ARGS --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS)


if(${LLVM_VERSION} VERSION_GREATER 3.5)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
set(LLVM_VERSION LLVM_${LLVM_VERSION_MAJOR}${LLVM_VERSION_MINOR})

include_directories(${LLVM_DIR})

set(FAUST2_UNIX_CXX_FLAGS "-Wall -Wuninitialized -Wno-parentheses -Wnon-virtual-dtor -Wno-logical-op-parentheses -Wno-overloaded-virtual")
if (${CMAKE_COMPILER_IS_GNUCXX})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FAUST2_UNIX_CXX_FLAGS}")
endif()
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FAUST2_UNIX_CXX_FLAGS}")
endif()

# STATIC LIBFAUST
add_library(libfaust-static STATIC libmain.cpp ${SOURCES} ${LOKI_SOURCES} global.cpp)
set_target_properties(libfaust-static PROPERTIES OUTPUT_NAME faust)
set_target_properties(libfaust-static PROPERTIES PREFIX "lib")
set_property(TARGET libfaust-static
    APPEND
    PROPERTY COMPILE_DEFINITIONS INSTALL_PREFIX="/usr/local" __STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS ${LLVM_VERSION} 
)
target_include_directories(libfaust-static PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/generator/asmjs 
    ${CMAKE_CURRENT_SOURCE_DIR}/generator/c
    ${CMAKE_CURRENT_SOURCE_DIR}/generator/cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generator/js
    ${CMAKE_CURRENT_SOURCE_DIR}/generator/java
    ${CMAKE_CURRENT_SOURCE_DIR}/generator/fir
    ${CMAKE_CURRENT_SOURCE_DIR}/generator/llvm
    ${OPENSSL_INCLUDE_DIR}
    )

# SHARED LIBFAUST
if(BUILD_FAUST_SHARED)
    add_library(libfaust SHARED libmain.cpp ${SOURCES} ${LOKI_SOURCES} global.cpp)
    set_target_properties(libfaust PROPERTIES OUTPUT_NAME faust)
    set_target_properties(libfaust PROPERTIES PREFIX "lib")

    set_property(TARGET libfaust
        APPEND
        PROPERTY COMPILE_DEFINITIONS INSTALL_PREFIX="/usr/local" __STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS ${LLVM_VERSION} 
    )

    target_link_libraries(libfaust pthread dl ${OPENSSL_LIBRARIES} curses z)
    target_link_libraries(libfaust ${LLVM_LDFLAGS} ${LLVM_LIBS})
    target_include_directories(libfaust PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/generator/asmjs 
        ${CMAKE_CURRENT_SOURCE_DIR}/generator/c
        ${CMAKE_CURRENT_SOURCE_DIR}/generator/cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generator/js
        ${CMAKE_CURRENT_SOURCE_DIR}/generator/java
        ${CMAKE_CURRENT_SOURCE_DIR}/generator/fir
        ${CMAKE_CURRENT_SOURCE_DIR}/generator/llvm
        ${OPENSSL_INCLUDE_DIR}
    )
endif()

# COMMANDLINE FAUST EXECUTABLE
if(BUILD_FAUST_CLI)
    add_executable(faust main.cpp libmain.cpp global.cpp)
    set_property(TARGET faust
        APPEND
        PROPERTY COMPILE_DEFINITIONS INSTALL_PREFIX="/usr/local" __STDC_LIMIT_MACROS __STDC_CONSTANT_MACROS ${LLVM_VERSION} 
    )

    target_link_libraries(faust libfaust-static)
    target_link_libraries(faust pthread dl ${OPENSSL_LIBRARIES}  curses z)
    target_link_libraries(faust ${LLVM_LDFLAGS} ${LLVM_LIBS})

    if (CTAGS AND NOT CMAKE_GENERATOR STREQUAL Xcode)
           add_custom_command (TARGET faust POST_BUILD COMMAND ctags ARGS -R .
                                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMENT "Creating tags" VERBATIM)
    endif()


    install(TARGETS faust
            DESTINATION "bin"
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endif()
