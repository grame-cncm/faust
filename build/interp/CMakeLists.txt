# CMAKE faust interpreter
project(FaustMachine)
cmake_minimum_required(VERSION 3.4.0)

#######################################
# versions management
set (VERSION 1.0.0)
set (SOVERS 0)

#######################################
# options
option ( ITPDYNAMIC 	"Include Faust Interpreter dynamic library"	off )

#######################################
# check for variables that are normally set at upper level
if (NOT DEFINED LIBDIR)
	set (LIBDIR lib)
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
FILE(GLOB SRC ${FAUSTITP}/interpreter_dsp_aux.cpp ${FAUSTGEN}/export.cpp)
FILE(GLOB SRCH  ${FAUSTITP}/*.h ${FAUSTGEN}/dsp_aux.h ${FAUSTGEN}/export.h)

set( INCLUDE
	${FAUSTROOT}
	${FAUSTROOT}/errors
	${FAUSTROOT}/tlib
	${FAUSTGEN}/  
	${FAUSTITP}/)

#######################################
# add libraries
if (INCLUDE_ITP)
	add_library( faustmachinestatic STATIC ${SRC} ${SRCH})
	target_include_directories (faustmachinestatic PRIVATE ${INCLUDE} )
	set_target_properties(faustmachinestatic PROPERTIES OUTPUT_NAME faustmachine)
	target_compile_definitions (faustmachinestatic PRIVATE -DMACHINE)
	set (TARGETS ${TARGETS} faustmachinestatic)
endif()

if (NOT IOS AND ITPDYNAMIC)
	add_library( faustmachinedynamic SHARED ${SRC} ${SRCH} )
	target_include_directories (faustmachinedynamic PRIVATE ${INCLUDE} )
	set_target_properties(faustmachinedynamic PROPERTIES 
		VERSION ${VERSION}
		SOVERSION ${SOVERS}
		OUTPUT_NAME faustmachine)
	set (TARGETS ${TARGETS} faustmachinedynamic)
	target_compile_definitions (faustmachinedynamic PRIVATE -DMACHINE)
endif()


file (GLOB HEADERS ${ROOT}/architecture/faust/dsp/interpreter-machine-dsp.h)
set_target_properties(${TARGETS} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBDIR})

# public headers are similar for both static and dynamic libs but only attached to the static one
if (INCLUDE_OSC)
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
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/faust/dsp
)

