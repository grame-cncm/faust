# CMAKE faust interpreter
project(FaustMachine)
cmake_minimum_required(VERSION 3.4.0)

#######################################
# versions management
set (VERSION 1.0.0)
set (SOVERS 0)

#######################################
# options
option ( ITPDYNAMIC         "Include Faust Interpreter dynamic library" off )
option ( USE_LLVM_CONFIG    "Force use off llvm-config" on )


#######################################
# check for variables that are normally set at upper level
if (NOT DEFINED LIBDIR)
	set (LIBDIR lib)
endif()
if (NOT DEFINED LIBSDIR)
	set (LIBSDIR lib)
endif()
if (NOT DEFINED ROOT)
	set (ROOT ../..)
endif()

#######################################
# SET MAIN DIRECTORY.
set (FAUSTROOT ${ROOT}/compiler)
set (FAUSTGEN ${FAUSTROOT}/generator)
set (FAUSTITP ${FAUSTGEN}/interpreter)
set (CMAKE_BUILD_TYPE Release)

#######################################
# collect source files
FILE(GLOB SRC ${FAUSTITP}/interpreter_dsp_aux.cpp ${FAUSTGEN}/export.cpp ${FAUSTROOT}/lock_api.cpp)
FILE(GLOB SRCH ${FAUSTITP}/*.h ${FAUSTGEN}/dsp_aux.h ${FAUSTGEN}/export.h)

set( INCLUDE
	${FAUSTROOT}
	${FAUSTROOT}/errors
	${FAUSTROOT}/tlib
	${FAUSTROOT}/utils
	${ROOT}/architecture
	${FAUSTGEN}/  
	${FAUSTITP}/
	/usr/local/include)

set( MACHINEDEFS -DMACHINE -D${LLVM_VERSION})
if (WIN32 OR MSYS)
else()
	set( MACHINE_DYN_LIBS ${MACHINE_DYN_LIBS} -lpthread)
endif()


####################################
# LLVM
include (../misc/llvm.cmake)
# if LLVM_PACKAGE_VERSION is defined, LLVM has already been set at upper level
if (INCLUDE_LLVM AND NOT DEFINED LLVM_PACKAGE_VERSION)
	if(USE_LLVM_CONFIG)
		llvm_config()
	else()
		llvm_cmake()
	endif()
	string (REGEX REPLACE "([0-9])\\.([0-9]).*" "LLVM_\\1\\2" LLVM_VERSION ${LLVM_PACKAGE_VERSION})
	set (FAUST_LIBS ${FAUST_LIBS} ${LLVM_LD_FLAGS} ${LLVM_LIBS})
endif()

#######################################
# add libraries
#message ("target_link_libraries (faustmachinestatic PRIVATE ${LLVM_LD_FLAGS} ${LLVM_LIBS}")
if (INCLUDE_ITP)
	add_library( faustmachinestatic STATIC ${SRC} ${SRCH})
	set_target_properties(faustmachinestatic PROPERTIES OUTPUT_NAME faustmachine)
	target_include_directories (faustmachinestatic PRIVATE ${INCLUDE} ${LLVM_INCLUDE_DIRS} )
	target_link_libraries (faustmachinestatic PRIVATE ${LLVM_LD_FLAGS} ${LLVM_LIBS})
	target_compile_definitions (faustmachinestatic PRIVATE ${MACHINEDEFS})
	set (TARGETS ${TARGETS} faustmachinestatic)
endif()

if (NOT IOS AND ITPDYNAMIC)
	add_library( faustmachinedynamic SHARED ${SRC} ${SRCH} )
	target_include_directories (faustmachinedynamic PRIVATE ${INCLUDE} ${LLVM_INCLUDE_DIRS})
	target_link_libraries (faustmachinedynamic PRIVATE ${LLVM_LD_FLAGS} ${LLVM_LIBS} ${MACHINE_DYN_LIBS})
	target_compile_definitions (faustmachinedynamic PRIVATE ${MACHINEDEFS})
	set_target_properties(faustmachinedynamic PROPERTIES 
		VERSION ${VERSION}
		SOVERSION ${SOVERS}
		OUTPUT_NAME faustmachine)
	set (TARGETS ${TARGETS} faustmachinedynamic)
endif()


file (GLOB HEADERS ${ROOT}/architecture/faust/dsp/interpreter-machine-dsp.h)
set_target_properties(${TARGETS} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})

# public headers are similar for both static and dynamic libs but only attached to the static one
if (INCLUDE_ITP)
	set_target_properties(faustmachinestatic PROPERTIES PUBLIC_HEADER "${HEADERS}")
else()
	set_target_properties(faustmachinedynamic PROPERTIES PUBLIC_HEADER "${HEADERS}")
endif()	

if (IOS)
	set_target_properties(faustmachinestatic PROPERTIES OUTPUT_NAME FaustMachine.ios)
endif()	

####################################
# install section
####################################
if (PACK)
	set (CMAKE_INSTALL_PREFIX .)
endif()

install ( TARGETS ${TARGETS}
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBSDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBSDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBSDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/dsp
)

