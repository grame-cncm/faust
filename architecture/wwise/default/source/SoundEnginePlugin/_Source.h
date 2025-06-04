TITLE:include the dsp header
BELOW: #include <AK/Plugin/PluginServices/AkFXDurationHandler.h>
REPLACE: 0
CODE:#include "faustdsp.cpp"

TITLE:add mydsp private member variable
BELOW: AkFXDurationHandler m_durationHandler;
REPLACE: 0
CODE:    mydsp m_dsp;
