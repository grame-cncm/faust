# CMake project written by faust2juce for APPL_NAME, an alternative to APPL_NAME.jucer
# that needs no Projucer:
#
#   cmake -B build -DJUCE_DIR=/path/to/JUCE      (without JUCE_DIR, JUCE is downloaded)
#   cmake --build build --config Release
#
# The plugins are in build/APPL_NAME_artefacts/Release. JUCE only builds the AUv3 format
# with the Xcode generator (cmake -G Xcode). Options:
#
#   -DJUCE_DIR=<folder>                 a JUCE 7 or 8 checkout
#   -DJUCE_GIT_TAG=<tag>                the JUCE version downloaded when JUCE_DIR is empty
#   -DFAUST_CUSTOM_EDITOR=<file.h>      a header replacing the generic interface (see the
#                                       "Custom editor" section of the faust2juce README)
#   -DFAUST_EXTRA_SOURCES="<a.cpp;...>" more sources, e.g. the custom editor implementation
#                                       (absolute paths, or relative to this folder)
#   -DFAUST_COPY_PLUGINS=ON             copy the plugins to the user plug-in folders after
#                                       each build
#   -DFOLEYS_GUI_MAGIC_DIR=<folder>     with -magic (required): a checkout of
#                                       https://github.com/ffAudio/foleys_gui_magic, or its
#                                       modules/foleys_gui_magic folder
#   -DFAUST_MAGIC_XML=<file.xml>        with -magic: a GUI saved by the PluginGuiMagic editor,
#                                       built into the plugin (otherwise the default GUI is
#                                       generated from the parameter groups)
#
# Use either this file or the .jucer project in this folder: saving the .jucer project
# with Projucer replaces JuceLibraryCode/JuceHeader.h.

cmake_minimum_required(VERSION 3.22)
project(APPL_NAME VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum macOS version")

set(JUCE_DIR "" CACHE PATH "JUCE checkout; downloaded when empty")
set(JUCE_GIT_TAG "8.0.10" CACHE STRING "JUCE version downloaded when JUCE_DIR is empty")
set(FAUST_CUSTOM_EDITOR "" CACHE FILEPATH "Header replacing the generic Faust interface")
set(FAUST_EXTRA_SOURCES "" CACHE STRING "Additional source files")
option(FAUST_COPY_PLUGINS "Copy the plugins to the user plug-in folders after each build" OFF)
set(FOLEYS_GUI_MAGIC_DIR "" CACHE PATH "With -magic: foleys_gui_magic checkout or module folder")
set(FAUST_MAGIC_XML "" CACHE FILEPATH "With -magic: GUI saved by the PluginGuiMagic editor")

# Preprocessor definitions selected by the faust2juce options
set(FAUST_DEFINITIONS CMAKE_DEFINITIONS)

# -magic: the PluginGuiMagic module, from the repository root or the module folder itself
if("PLUGIN_MAGIC" IN_LIST FAUST_DEFINITIONS)
    if(EXISTS "${FOLEYS_GUI_MAGIC_DIR}/modules/foleys_gui_magic/foleys_gui_magic.h")
        set(FOLEYS_GUI_MAGIC_MODULE "${FOLEYS_GUI_MAGIC_DIR}/modules/foleys_gui_magic")
    elseif(EXISTS "${FOLEYS_GUI_MAGIC_DIR}/foleys_gui_magic.h")
        set(FOLEYS_GUI_MAGIC_MODULE "${FOLEYS_GUI_MAGIC_DIR}")
    else()
        message(FATAL_ERROR "-magic needs the foleys_gui_magic module "
                            "(https://github.com/ffAudio/foleys_gui_magic): pass -DFOLEYS_GUI_MAGIC_DIR=<checkout>")
    endif()
endif()

if(JUCE_DIR)
    add_subdirectory("${JUCE_DIR}" JUCE)
else()
    include(FetchContent)
    FetchContent_Declare(JUCE GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
                         GIT_TAG ${JUCE_GIT_TAG} GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(JUCE)
endif()

if(FOLEYS_GUI_MAGIC_MODULE)
    juce_add_module("${FOLEYS_GUI_MAGIC_MODULE}")
endif()

CMAKE_VST2_SDK

juce_add_plugin(APPL_NAME
    PRODUCT_NAME "APPL_NAME"
    COMPANY_NAME "GRAME"
    BUNDLE_ID com.grame.APPL_NAME
    PLUGIN_MANUFACTURER_CODE Manu
    PLUGIN_CODE SUB_TYPE
    FORMATS CMAKE_FORMATS
    IS_SYNTH CMAKE_IS_SYNTH
    NEEDS_MIDI_INPUT CMAKE_IS_MIDI
    NEEDS_MIDI_OUTPUT CMAKE_IS_MIDI
    COPY_PLUGIN_AFTER_BUILD ${FAUST_COPY_PLUGINS})

target_sources(APPL_NAME PRIVATE FaustPluginProcessor.cpp ${FAUST_EXTRA_SOURCES})

# This folder resolves "JuceLibraryCode/JuceHeader.h", JuceLibraryCode resolves the
# "../JuceLibraryCode/JuceHeader.h" of the architecture headers inlined by faust -i
target_include_directories(APPL_NAME PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode"
    "CMAKE_FAUST_INCLUDE")

target_compile_definitions(APPL_NAME PUBLIC
    ${FAUST_DEFINITIONS}
    FAUSTFLOAT=FAUST_FLOAT
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

# faust2juce -disable-splash-screen (which needs a JUCE 7 license; JUCE 8 has no splash screen)
if(NOT DISPLAY_SPLASH_SCREEN_DEFAULT)
    target_compile_definitions(APPL_NAME PUBLIC JUCE_DISPLAY_SPLASH_SCREEN=0)
endif()

if(FAUST_CUSTOM_EDITOR)
    get_filename_component(FAUST_EDITOR_DIR "${FAUST_CUSTOM_EDITOR}" DIRECTORY)
    get_filename_component(FAUST_EDITOR_NAME "${FAUST_CUSTOM_EDITOR}" NAME)
    target_include_directories(APPL_NAME PRIVATE "${FAUST_EDITOR_DIR}")
    target_compile_definitions(APPL_NAME PUBLIC "FAUST_CUSTOM_EDITOR=\"${FAUST_EDITOR_NAME}\"")
endif()

set(FAUST_JUCE_MODULES juce::juce_audio_utils)
if("OSCCTRL" IN_LIST FAUST_DEFINITIONS)
    list(APPEND FAUST_JUCE_MODULES juce::juce_osc)
endif()

if(FOLEYS_GUI_MAGIC_MODULE)
    list(APPEND FAUST_JUCE_MODULES foleys_gui_magic juce::juce_dsp juce::juce_cryptography)
    if(FAUST_MAGIC_XML)
        # Copied as magic.xml, so that the resource is BinaryData::magic_xml, the name the
        # architecture loads under MAGIC_LOAD_BINARY
        configure_file("${FAUST_MAGIC_XML}" "${CMAKE_CURRENT_BINARY_DIR}/magic.xml" COPYONLY)
        juce_add_binary_data(APPL_NAME_MagicGUI SOURCES "${CMAKE_CURRENT_BINARY_DIR}/magic.xml")
        list(APPEND FAUST_JUCE_MODULES APPL_NAME_MagicGUI)
        target_compile_definitions(APPL_NAME PUBLIC MAGIC_LOAD_BINARY)
    endif()
endif()

target_link_libraries(APPL_NAME
    PRIVATE
        ${FAUST_JUCE_MODULES}
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags)
