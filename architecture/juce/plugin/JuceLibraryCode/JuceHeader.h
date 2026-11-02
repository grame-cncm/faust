/*
 Written by faust2juce for the CMake build (CMakeLists.txt). The Faust JUCE architecture
 includes "JuceLibraryCode/JuceHeader.h", the header Projucer generates for the .jucer
 build: this one only includes the JUCE modules it uses. Saving the .jucer project with
 Projucer replaces it.
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

#if defined(OSCCTRL)
#include <juce_osc/juce_osc.h>
#endif

// -magic: the PluginGuiMagic module, and the GUI built into the plugin (FAUST_MAGIC_XML)
#if defined(PLUGIN_MAGIC)
#include <foleys_gui_magic/foleys_gui_magic.h>
#endif
#if defined(MAGIC_LOAD_BINARY)
#include "BinaryData.h"
#endif
