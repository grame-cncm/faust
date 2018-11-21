cmake_minimum_required(VERSION 3.0)


option ( USE_LLVM_CONFIG 	"Use llvm-config"	on )

set (FAUSTROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set (SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (C74_MAX_API_DIR ${MAX_SDK_DIR}source/max-api)

if (NOT DEFINED MAX_SDK_DIR)
message (FATAL_ERROR "MAX_SDK_DIR is undefined. Call cmake with -DMAX_SDK_DIR=max_sdk_path")
endif()

include (${MAX_SDK_DIR}/source/max-api/script/max-pretarget.cmake)

####################################
# LLVM
include (${FAUSTROOT}/build/misc/llvm.cmake)
if(USE_LLVM_CONFIG)
	llvm_config()
else()
	llvm_cmake()
endif()

#set( LIBS -L${FAUSTROOT}/build/lib -lfaust ${LLVM_LD_FLAGS} ${LLVM_LIBS})
set( LIBS -lfaust -L/usr/local/Cellar/libsndfile/1.0.28/lib -lsndfile ${LLVM_LD_FLAGS} ${LLVM_LIBS})

message( "C74_INCLUDES ${C74_INCLUDES}" )

include_directories( "${C74_INCLUDES}"  /usr/local/include /usr/local/Cellar/libsndfile/1.0.28/include)
add_library ( ${PROJECT_NAME}  MODULE ${SRC}/faustgen.cpp )
target_link_libraries ( ${PROJECT_NAME} PUBLIC ${LIBS} )


include(${MAX_SDK_DIR}/source/max-api/script/max-posttarget.cmake)
