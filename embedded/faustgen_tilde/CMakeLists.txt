cmake_minimum_required(VERSION 3.0)


option ( USE_LLVM_CONFIG 	"Use llvm-config"	on )

set (FAUSTROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set (SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (C74_MAX_API_DIR ${MAX_SDK_DIR}/source/max-api)

if (NOT DEFINED MAX_SDK_DIR)
message (FATAL_ERROR "MAX_SDK_DIR is undefined. Call cmake with -DMAX_SDK_DIR=max_sdk_path")
endif()

####################################
# Max stuff before
include (${MAX_SDK_DIR}/source/max-api/script/max-pretarget.cmake)

####################################
# LLVM
include (${FAUSTROOT}/build/misc/llvm.cmake)
if(USE_LLVM_CONFIG)
	llvm_config()
else()
	llvm_cmake()
endif()

####################################
execute_process (COMMAND faust --includedir          OUTPUT_VARIABLE FAUST_INCLUDE_TMP)
string ( STRIP ${FAUST_INCLUDE_TMP} FAUST_INCLUDE )
execute_process (COMMAND faust --libdir 	         OUTPUT_VARIABLE FAUST_LIB_TMP)
string ( STRIP ${FAUST_LIB_TMP} FAUST_LIB )
execute_process (COMMAND pkg-config --cflags sndfile OUTPUT_VARIABLE SNDF_CFLAGS_TMP)
string ( STRIP ${SNDF_CFLAGS_TMP} SNDF_CFLAGS )
execute_process (COMMAND pkg-config --libs sndfile   OUTPUT_VARIABLE SNDF_LDFLAGS_TMP)
string ( STRIP ${SNDF_LDFLAGS_TMP} SNDF_LDFLAGS )

set( INC ${C74_INCLUDES}  /usr/local/include ${SNDF_CFLAGS})
set( LIBS ${FAUST_LIB}/libfaust.a ${SNDF_LDFLAGS} ${LLVM_LD_FLAGS} ${LLVM_LIBS})

include_directories( ${INC} )
add_library ( ${PROJECT_NAME}  MODULE ${SRC}/faustgen.cpp )
target_link_libraries ( ${PROJECT_NAME} PUBLIC ${LIBS} )

####################################
# Max stuff before
include(${MAX_SDK_DIR}/source/max-api/script/max-posttarget.cmake)

