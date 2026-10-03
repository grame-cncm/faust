#ifndef PLUGIN_STATE_H
#define PLUGIN_STATE_H

enum PluginState{
    ZERO_STATE,
    // IDDLE, // for when loading previously compiled plugins? i.e. when opening wwise?
    PENDING_CREATION,
    ERR_COMPILE_DSP,
    DSP_COMPILED,
    ERR_DSPUI_CREATION,
    DSPUI_CREATED,
    PENDING_CONFIGURATION,
    ERR_CONFIGURE_PLUGIN,
    PLUGIN_CONFIGURED,
    PLUGIN_SET,
    BUILT,
    READY,
    RESET,
    DESTROY
};

#endif