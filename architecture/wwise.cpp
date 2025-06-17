#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

<<includeIntrinsic>>
<<includeclass>>

static mydsp m_dsp;
static MapUI map_ui;

void initDSP(int sampleRate) {
    m_dsp.init(sampleRate);
    m_dsp.buildUserInterface(&map_ui);
}

template <typename T> // for the shake of proper usage and to supress a probable warning
void setParameter(const char* name, T value) {
    map_ui.setParamValue(std::string(name), static_cast<FAUSTFLOAT>(value)); 
}
