cmake_minimum_required(VERSION 3.4.0)
project (faustgen)
set (VERSION "1.63")

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

option (USE_LLVM_CONFIG "Use llvm-config" on)

#######################################
set (CMAKE_CXX_STANDARD 11)

#######################################
# Max part
if (NOT DEFINED MAXSDK)
	message (FATAL_ERROR "MAXSDK path undefined ! Call cmake with -DMAXSDK=path/toMax/sdk")
else()
	message (STATUS "Using MAXSDK from ${MAXSDK}")
endif()
set (MAXINCL ${MAXSDK}/max-includes ${MAXSDK}/msp-includes)
if (APPLE)
	set (MAXLIBS "-F${MAXSDK}/max-includes -framework MaxAPI  -F${MAXSDK}/msp-includes -framework MaxAudioAPI")
elseif (WIN32)
	file (GLOB MAPI ${MAXSDK}/max-includes/x64/MaxAPI.lib)
	file (GLOB MAUDIO ${MAXSDK}/msp-includes/x64/MaxAudio.lib)
	set (MAXLIBS ${MAPI} ${MAUDIO})
#	set (MAXLIBS ${MAXSDK}/max-includes/x64/MaxAPI  ${MAXSDK}/msp-includes/x64/MaxAudio)
endif()

#######################################
# Faust part
if(APPLE AND CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
# We can't execute an arm64 faust executable on a GitHub x86 runner,
# so we may some strong assumptions about where the include/libs are.
cmake_path(GET FAUST PARENT_PATH FAUST_DIR)
cmake_path(GET FAUST_DIR PARENT_PATH FAUST_DIR)
set(FAUSTINC ${FAUST_DIR}/include)
set(FAUSTLIB ${FAUST_DIR}/lib)
string ( STRIP ${FAUSTINC} FAUSTINC )
message("USING FAUSTINC ${FAUSTINC}")
else()
if (NOT DEFINED FAUST)
	set (FAUST faust)
endif()
message (STATUS "Using Faust as ${FAUST}")
execute_process (COMMAND ${FAUST} --includedir OUTPUT_VARIABLE FINC)
string ( STRIP ${FINC} FAUSTINC )
execute_process (COMMAND ${FAUST} --libdir OUTPUT_VARIABLE FLIB)
string ( STRIP ${FLIB} FAUSTLIB )

message (STATUS "Using Faust libraries from ${FAUSTLIB}")
endif()

#######################################
# libsndfile
if (WIN32)
	if (NOT DEFINED LIBSNDFILE)
		set (LIBSNDFILE "C:/Program Files/Mega-Nerd/libsndfile")
	endif()
	set (SNDFILE_LIBRARIES ${LIBSNDFILE}/lib/sndfile.lib)
	set (SNDFILE_INCLUDE_DIRS ${LIBSNDFILE}/include)
else()
	# We expect the user to have built libsndfile as a static lib
	# and for it to be accessible via `pkg-config --static libsndfile`
	set(SNDFILE_IS_STATIC 1)
	find_package(PkgConfig REQUIRED)
	set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
	list(APPEND PKG_CONFIG_EXECUTABLE "--static")  # append temporarily
	pkg_check_modules(SNDFILE REQUIRED IMPORTED_TARGET sndfile)
	pkg_check_modules(FLAC REQUIRED IMPORTED_TARGET flac)
	pkg_check_modules(VORBIS REQUIRED IMPORTED_TARGET vorbis)
	pkg_check_modules(OGG REQUIRED IMPORTED_TARGET ogg)
	pkg_check_modules(OPUS REQUIRED IMPORTED_TARGET opus)
	pkg_check_modules(MPG123 REQUIRED IMPORTED_TARGET libmpg123)
	list(POP_BACK PKG_CONFIG_EXECUTABLE)  # undo the append above

	# need lame due to brew's lame not having a .pc file
	set(LAME_LIB_DIR ${LAME_DIR}/lib)

endif()

#######################################
# faust libraries
file (GLOB DSPLIBS ${ROOT}/../../libraries/*.lib)

####################################
# LLVM
if(NOT DEFINED LLVM_LD_FLAGS OR NOT DEFINED LLVM_LIBS)
include (../../build/misc/llvm.cmake)
if(USE_LLVM_CONFIG)
	llvm_config()
else()
	llvm_cmake()
endif()
endif()

####################################
# compiler dependent settings
if (WIN32)
	set (FAUSTLIBS ${FAUSTLIB}/libfaust.lib ${FAUSTLIB}/libOSCFaust.lib)
	set (WINSRC ${MAXSDK}/max-includes/common/dllmain_win.c ${MAXSDK}/max-includes/common/commonsyms.c)
else()
	set (MACLIBS "-framework CoreServices -framework IOKit")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set (FAUSTLIBS ${FAUSTLIB}/libfaust.a ${FAUSTLIB}/libOSCFaust.a)
endif()

####################################
# Add the faustgen target
####################################
add_library(faustgen MODULE ${ROOT}/src/faustgen~.cpp ${WINSRC} ${DSPLIBS})
target_include_directories(faustgen PRIVATE ${ROOT}/src/ ${MAXINCL} ${FAUSTINC} ${SNDFILE_INCLUDE_DIRS})
if (DEFINED SNDFILE_IS_STATIC)
target_link_directories(faustgen PRIVATE ${LAME_LIB_DIR})
target_link_libraries (faustgen ${FAUSTLIBS} ${MAXLIBS} PkgConfig::SNDFILE PkgConfig::FLAC PkgConfig::VORBIS PkgConfig::OGG PkgConfig::OPUS PkgConfig::MPG123 ${LLVM_LD_FLAGS} ${LLVM_LIBS} )
else()
target_link_libraries (faustgen ${FAUSTLIBS} ${MAXLIBS} ${SNDFILE_LIBRARIES} ${LLVM_LD_FLAGS} ${LLVM_LIBS})
endif()

if (APPLE)
set_target_properties (faustgen PROPERTIES 
	LINK_FLAGS "${MACLIBS} -Wl,-U,_object_new_imp -Wl,-U,_object_method_imp ${LLVM_LD_FLAGS}"
	BUNDLE TRUE
	BUNDLE_EXTENSION mxo
	MACOSX_BUNDLE_INFO_PLIST ${ROOT}/Info.plist
	RESOURCE "${DSPLIBS}"
	OUTPUT_NAME faustgen~)

elseif (WIN32)
set_target_properties (faustgen PROPERTIES 
	COMPILE_FLAGS "-DWIN_VERSION -DWIN_EXT_VERSION"
	LINK_FLAGS "winmm.lib ws2_32.lib"
	SUFFIX ".mxe64"
	OUTPUT_NAME faustgen~)
endif()


####################################
# Install - used for packaging
####################################
set (PACKDIR ${ROOT}/package)
set (DST faustgen-${VERSION})
if (WIN32)
set (DST ${DST}-win64)
endif()
set (FG ${DST}/faustgen)
install ( TARGETS faustgen
	RUNTIME DESTINATION ${PACKDIR}/${FG}/externals/msp
    LIBRARY DESTINATION ${PACKDIR}/${FG}/externals/msp
    ARCHIVE DESTINATION ${PACKDIR}/${FG}/externals/msp
)

####################################
# install folders
set (PACKCONTENT ${PACKDIR}/docs ${PACKDIR}/help ${PACKDIR}/init)
install (
    DIRECTORY ${PACKCONTENT} DESTINATION ${PACKDIR}/${FG}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)

if (WIN32)
####################################
# install lib files + misc
install (
    FILES     ${DSPLIBS} DESTINATION ${PACKDIR}/${FG}/externals/msp/faustgen-resources
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ  WORLD_READ
)
install (
    FILES    ${LIBSNDFILE}/bin/sndfile.dll DESTINATION ${PACKDIR}/${DST}
)
endif()


####################################
# install various files
set (MISC changelog.txt ${PACKDIR}/Install.html)
install (
    FILES     ${MISC} DESTINATION ${PACKDIR}/${DST}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ  WORLD_READ
)

####################################
# install VS redistributables
if (WIN32)
# Suppose VS_REDIST is
# C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Redist/MSVC/14.29.30133/vc_redist.x64.exe
install (
    FILES  ${VS_REDIST} DESTINATION ${PACKDIR}/${DST}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
endif()


####################################
# post install processing
if (APPLE)
install (
    # not sure this is the right place, but it works...
    CODE  "execute_process (COMMAND codesign --sign - --deep --force ${PACKDIR}/${DST}/faustgen/externals/msp/faustgen\~.mxo)"
    CODE  "execute_process (COMMAND hdiutil create ${PACKDIR}/${DST}-macosx.dmg -fs HFS+ -srcfolder ${PACKDIR}/${DST} -format UDBZ -ov)"
)
endif()

