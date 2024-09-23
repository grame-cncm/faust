cmake_minimum_required(VERSION 3.6.0)
project (faustgen)
set (VERSION "1.72")

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

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
    set (MAXLIBS "-F${MAXSDK}/max-includes -F${MAXSDK}/msp-includes -framework MaxAudioAPI")
elseif (WIN32)
    file (GLOB MAPI ${MAXSDK}/max-includes/x64/MaxAPI.lib)
    file (GLOB MAUDIO ${MAXSDK}/msp-includes/x64/MaxAudio.lib)
    set (MAXLIBS ${MAPI} ${MAUDIO})
#   set (MAXLIBS ${MAXSDK}/max-includes/x64/MaxAPI  ${MAXSDK}/msp-includes/x64/MaxAudio)
endif()

#######################################
# Faust part
if(DEFINED FAUST_PATH_IS_ABSOLUTE AND FAUST_PATH_IS_ABSOLUTE MATCHES "1")
    # We can't execute an arm64 faust executable on a GitHub x86 runner,
    # so we make some strong assumptions about where the include and libs are.
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
string ( STRIP "${FINC}" FAUSTINC )
execute_process (COMMAND ${FAUST} --libdir OUTPUT_VARIABLE FLIB)
string ( STRIP "${FLIB}" FAUSTLIB )

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
    find_package(PkgConfig REQUIRED)
    if (DEFINED USE_STATIC_SNDFILE AND "${USE_STATIC_SNDFILE}" STREQUAL "1" )
        # We expect the user to have built libsndfile as a static lib
        # and for it to be accessible via `pkg-config --static libsndfile`
        set(SNDFILE_IS_STATIC 1)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
        list(APPEND PKG_CONFIG_EXECUTABLE "--static")  # append temporarily
        pkg_check_modules(SNDFILE REQUIRED IMPORTED_TARGET sndfile)
        pkg_check_modules(FLAC REQUIRED IMPORTED_TARGET flac)
        pkg_check_modules(VORBIS REQUIRED IMPORTED_TARGET vorbis)
        pkg_check_modules(OGG REQUIRED IMPORTED_TARGET ogg)
        pkg_check_modules(OPUS REQUIRED IMPORTED_TARGET opus)
        pkg_check_modules(MPG123 IMPORTED_TARGET libmpg123) # libmpg123 is not REQUIRED because it requires macos 12
        list(POP_BACK PKG_CONFIG_EXECUTABLE)  # undo the append above
    else()
        # We expect the user to have installed sndfile with
        # brew install libsndfile
        set(SNDFILE_IS_STATIC 1)
        pkg_check_modules(SNDFILE REQUIRED IMPORTED_TARGET sndfile)
        pkg_check_modules(FLAC REQUIRED IMPORTED_TARGET flac)
        pkg_check_modules(VORBIS REQUIRED IMPORTED_TARGET vorbis)
        pkg_check_modules(OGG REQUIRED IMPORTED_TARGET ogg)
        pkg_check_modules(OPUS REQUIRED IMPORTED_TARGET opus)
        pkg_check_modules(MPG123 IMPORTED_TARGET libmpg123) # libmpg123 is not REQUIRED because it requires macos 12
    endif()
endif()

#######################################
# faust libraries
file (GLOB DSPLIBS ${ROOT}/../../libraries/*.lib)

####################################
# compiler dependent settings
if (WIN32)
    set (FAUSTLIBS ${FAUSTLIB}/libfaustwithllvm.lib ${FAUSTLIB}/libOSCFaust.lib)
    set (WINSRC ${MAXSDK}/max-includes/common/dllmain_win.c ${MAXSDK}/max-includes/common/commonsyms.c)
else()

    set (MACLIBS "-framework CoreServices -framework IOKit")
    set (CMAKE_CXX_FLAGS_RELEASE "-O3")
    
    if(DEFINED FAUST_PATH_IS_ABSOLUTE AND FAUST_PATH_IS_ABSOLUTE MATCHES "1")
    set (FAUSTLIBS ${FAUSTLIB}/libfaustwithllvm.a ${FAUSTLIB}/libOSCFaust.a)
    else()
    execute_process( COMMAND faust-config --system-libs OUTPUT_VARIABLE FC_OUTPUT RESULT_VARIABLE FC_RESULT)
    string(REPLACE " " ";" FC_OUTPUT ${FC_OUTPUT})
    string(STRIP "${FC_OUTPUT}" FC_OUTPUT)
    set (FAUSTLIBS ${FAUSTLIB}/libfaustwithllvm.a ${FC_OUTPUT} -L/opt/local/lib ${FAUSTLIB}/libOSCFaust.a)
    endif()

endif()

####################################
# Add the faustgen target
####################################
add_library(faustgen MODULE ${ROOT}/src/faustgen~.cpp ${ROOT}/src/faustgen_factory.cpp ${WINSRC} ${DSPLIBS})
target_include_directories(faustgen PRIVATE ${ROOT}/src/ ${MAXINCL} ${FAUSTINC} ${SNDFILE_INCLUDE_DIRS})
if (DEFINED SNDFILE_IS_STATIC)
    target_link_libraries (faustgen ${FAUSTLIBS} ${MAXLIBS} PkgConfig::SNDFILE PkgConfig::FLAC PkgConfig::VORBIS PkgConfig::OGG PkgConfig::OPUS PkgConfig::MPG123)
else()
    target_link_libraries (faustgen ${FAUSTLIBS} ${MAXLIBS} ${SNDFILE_LIBRARIES})
endif()

if (APPLE)
    set_target_properties (faustgen PROPERTIES 
    # With Max 8.6, the MaxAPI framework is not linked anymore, so a bunch of symbols are undefined, are ignored with the -U flag and will be resolved at runtime.
    LINK_FLAGS "${MACLIBS} -Wl,-U,_outlet_new,-U,_object_new_imp,-U,_atom_getlong,-U,_atom_getobj,-U,_atom_getsym,-U,_atom_gettype,-U,_atom_setfloat,-U,_atom_setsym,-U,_class_addmethod,-U,_class_new,-U,_class_register,-U,_common_symbols_gettable,-U,_dictionary_appendlong,-U,_dictionary_appendstring,-U,_dictionary_getlong,-U,_dictionary_getstring,-U,_gensym,-U,_jbox_get_color,-U,_jbox_get_nextobject,-U,_jbox_get_object,-U,_jbox_get_varname,-U,_jbox_set_varname,-U,_jmouse_getposition_global,-U,_jpatcher_get_firstobject,-U,_jpatcher_set_dirty,-U,_jpopupmenu_additem,-U,_jpopupmenu_create,-U,_jpopupmenu_destroy,-U,_jpopupmenu_popup,-U,_jrgba_set,-U,_locatefile_extended,-U,_object_alloc,-U,_object_attr_setchar,-U,_object_attr_setsym,-U,_object_classname,-U,_object_classname_compare,-U,_object_error_obtrusive,-U,_object_free,-U,_object_method_imp,-U,_object_method_typed,-U,_object_obex_lookup,-U,_open_dialog,-U,_outlet_append,-U,_outlet_bang,-U,_outlet_delete,-U,_outlet_int,-U,_outlet_list,-U,_outlet_nth,-U,_path_createsysfile,-U,_path_opensysfile,-U,_path_setdefault,-U,_path_topathname,-U,_post,-U,_proxy_getinlet,-U,_saveas_dialog,-U,_strncpy_zero,-U,_sysfile_close,-U,_sysfile_readtextfile,-U,_sysfile_setpos,-U,_sysfile_writetextfile,-U,_sysmem_copyptr,-U,_sysmem_freehandle,-U,_sysmem_handlesize,-U,_sysmem_newhandle,-U,_sysmem_newhandleclear,-U,_jbox_set_color,-U,_path_getdefault"
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

