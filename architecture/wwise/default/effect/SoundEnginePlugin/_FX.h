TITLE:include the dsp header
BELOW: FXParams.h"
REPLACE: 0
CODE: #include "faustdsp.cpp"

TITLE:add mydsp private member variable
BELOW: AK::IAkEffectPluginContext* m_pContext;
REPLACE: 0
CODE:     mydsp m_dsp;