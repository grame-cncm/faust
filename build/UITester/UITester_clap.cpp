/* ------------------------------------------------------------
author: "O. Guillerminet"
copyright: "(c) O. Guillerminet 2012"
license: "BSD"
name: "UITester"
version: "1.0"
Code generated with Faust 2.81.0 (https://faust.grame.fr)
Compilation options: -a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

//dummy clap architecture file
//this file will translate faust's mydsp c++ class into the clap plugin interface
//it should include plugin lifecycle, audio block processing calls, parameter registration and ui integration using buildUserInterface () and CLAP API
//core of the plugin backend

//includes for faust dsp and ui
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

//include for cpp logging
#include <iostream>

//includes for the clap helpers glue
#include <clap/helpers/plugin.hh>
#include <clap/helpers/host-proxy.hh>
#include <clap/events.h>

//guarded MapUI subclass to prevent accidental param writes
struct GuardedUI : public MapUI {
    bool allowWrite = false;
    void setParamValue(const std::string& path, FAUSTFLOAT val) {
        if (!allowWrite) {
            std::abort(); //catch unintended writes early
        }
        MapUI::setParamValue(path, val);
    }

    void setParamValue(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }

    void guardedSetByIndex(int index, FAUSTFLOAT val) {
        std::string addr = getParamAddress(index);

        if (!allowWrite) {
            return;
        }
        MapUI::setParamValue(addr, val);
    }
};


struct GuardedScope {
    GuardedUI& ui;
    const char* tag;

    GuardedScope(GuardedUI& ui, const char* src = "unknown") : ui(ui), tag(src) {
        ui.allowWrite = true;
    }

    ~GuardedScope() {
        ui.allowWrite = false;
    }
};

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fButton1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fHbargraph1;
	int fSampleRate;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "O. Guillerminet");
		m->declare("compile_options", "-a /Users/cucu/Documents/GitHub/faust/architecture/clap/clap-arch.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("copyright", "(c) O. Guillerminet 2012");
		m->declare("filename", "UITester.dsp");
		m->declare("license", "BSD");
		m->declare("name", "UITester");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 6;
	}
	virtual int getNumOutputs() {
		return 34;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(6e+01f);
		fVslider0 = FAUSTFLOAT(6e+01f);
		fVslider1 = FAUSTFLOAT(6e+01f);
		fVslider2 = FAUSTFLOAT(6e+01f);
		fVslider3 = FAUSTFLOAT(6e+01f);
		fVslider4 = FAUSTFLOAT(6e+01f);
		fVslider5 = FAUSTFLOAT(6e+01f);
		fVslider6 = FAUSTFLOAT(6e+01f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(6e+01f);
		fVslider7 = FAUSTFLOAT(6e+01f);
		fVslider8 = FAUSTFLOAT(6e+01f);
		fVslider9 = FAUSTFLOAT(6e+01f);
		fEntry1 = FAUSTFLOAT(6e+01f);
		fVslider10 = FAUSTFLOAT(6e+01f);
		fVslider11 = FAUSTFLOAT(6e+01f);
		fVslider12 = FAUSTFLOAT(6e+01f);
		fEntry2 = FAUSTFLOAT(6e+01f);
		fVslider13 = FAUSTFLOAT(6e+01f);
		fVslider14 = FAUSTFLOAT(6e+01f);
		fVslider15 = FAUSTFLOAT(6e+01f);
		fEntry3 = FAUSTFLOAT(6e+01f);
		fVslider16 = FAUSTFLOAT(6e+01f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(6e+01f);
		fEntry4 = FAUSTFLOAT(6e+01f);
	}
	
	virtual void instanceClear() {
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openTabBox("grp 1");
		ui_interface->openHorizontalBox("hmisc");
		ui_interface->addButton("button", &fButton1);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph1, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->addHorizontalSlider("hslider", &fHslider1, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fEntry4, "unit", "f");
		ui_interface->addNumEntry("num", &fEntry4, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->addVerticalBargraph("vbar", &fVbargraph3, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->declare(&fVslider16, "unit", "f");
		ui_interface->addVerticalSlider("vslider4", &fVslider16, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("knobs");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->addVerticalSlider("knob1", &fVslider3, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->addVerticalSlider("knob2", &fVslider4, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->addVerticalSlider("knob3", &fVslider5, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sliders");
		ui_interface->addVerticalSlider("vslider1", &fVslider0, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->addVerticalSlider("vslider2", &fVslider1, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->addVerticalSlider("vslider3", &fVslider2, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vbox");
		ui_interface->addCheckButton("check1", &fCheckbox0);
		ui_interface->addCheckButton("check2", &fCheckbox1);
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->addNumEntry("knob0", &fEntry0, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("vmisc");
		ui_interface->addButton("button", &fButton0);
		ui_interface->addHorizontalBargraph("hbar", &fHbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("hslider", &fHslider0, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->openHorizontalBox("small box 1");
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->addVerticalSlider("knob4", &fVslider9, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fEntry1, "unit", "f");
		ui_interface->addNumEntry("num1", &fEntry1, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->addVerticalBargraph("vbar1", &fVbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->declare(&fVslider7, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider5", &fVslider7, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider8, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider6", &fVslider8, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("sub box 1");
		ui_interface->openHorizontalBox("small box 2");
		ui_interface->declare(&fVslider12, "style", "knob");
		ui_interface->addVerticalSlider("knob5", &fVslider12, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fEntry2, "unit", "f");
		ui_interface->addNumEntry("num2", &fEntry2, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->addVerticalBargraph("vbar2", &fVbargraph1, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->declare(&fVslider10, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider7", &fVslider10, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider11, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider8", &fVslider11, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("small box 3");
		ui_interface->declare(&fVslider15, "style", "knob");
		ui_interface->addVerticalSlider("knob6", &fVslider15, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fEntry3, "unit", "f");
		ui_interface->addNumEntry("num3", &fEntry3, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->addVerticalBargraph("vbar3", &fVbargraph2, FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f));
		ui_interface->declare(&fVslider14, "unit", "m");
		ui_interface->addVerticalSlider("vslider10", &fVslider14, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider13, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider9", &fVslider13, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fVslider6, "unit", "Hz");
		ui_interface->addVerticalSlider("vslider4", &fVslider6, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		FAUSTFLOAT* output8 = outputs[8];
		FAUSTFLOAT* output9 = outputs[9];
		FAUSTFLOAT* output10 = outputs[10];
		FAUSTFLOAT* output11 = outputs[11];
		FAUSTFLOAT* output12 = outputs[12];
		FAUSTFLOAT* output13 = outputs[13];
		FAUSTFLOAT* output14 = outputs[14];
		FAUSTFLOAT* output15 = outputs[15];
		FAUSTFLOAT* output16 = outputs[16];
		FAUSTFLOAT* output17 = outputs[17];
		FAUSTFLOAT* output18 = outputs[18];
		FAUSTFLOAT* output19 = outputs[19];
		FAUSTFLOAT* output20 = outputs[20];
		FAUSTFLOAT* output21 = outputs[21];
		FAUSTFLOAT* output22 = outputs[22];
		FAUSTFLOAT* output23 = outputs[23];
		FAUSTFLOAT* output24 = outputs[24];
		FAUSTFLOAT* output25 = outputs[25];
		FAUSTFLOAT* output26 = outputs[26];
		FAUSTFLOAT* output27 = outputs[27];
		FAUSTFLOAT* output28 = outputs[28];
		FAUSTFLOAT* output29 = outputs[29];
		FAUSTFLOAT* output30 = outputs[30];
		FAUSTFLOAT* output31 = outputs[31];
		FAUSTFLOAT* output32 = outputs[32];
		FAUSTFLOAT* output33 = outputs[33];
		float fSlow0 = float(fCheckbox0);
		float fSlow1 = float(fCheckbox1);
		float fSlow2 = float(fEntry0);
		float fSlow3 = float(fVslider0);
		float fSlow4 = float(fVslider1);
		float fSlow5 = float(fVslider2);
		float fSlow6 = float(fVslider3);
		float fSlow7 = float(fVslider4);
		float fSlow8 = float(fVslider5);
		float fSlow9 = float(fVslider6);
		float fSlow10 = float(fButton0);
		float fSlow11 = float(fHslider0);
		float fSlow12 = float(fVslider7);
		float fSlow13 = float(fVslider8);
		float fSlow14 = float(fVslider9);
		float fSlow15 = float(fEntry1);
		float fSlow16 = float(fVslider10);
		float fSlow17 = float(fVslider11);
		float fSlow18 = float(fVslider12);
		float fSlow19 = float(fEntry2);
		float fSlow20 = float(fVslider13);
		float fSlow21 = float(fVslider14);
		float fSlow22 = float(fVslider15);
		float fSlow23 = float(fEntry3);
		float fSlow24 = float(fVslider16);
		float fSlow25 = float(fButton1);
		float fSlow26 = float(fHslider1);
		float fSlow27 = float(fEntry4);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			output0[i0] = FAUSTFLOAT(fSlow0);
			output1[i0] = FAUSTFLOAT(fSlow1);
			output2[i0] = FAUSTFLOAT(fSlow2);
			output3[i0] = FAUSTFLOAT(fSlow3);
			output4[i0] = FAUSTFLOAT(fSlow4);
			output5[i0] = FAUSTFLOAT(fSlow5);
			output6[i0] = FAUSTFLOAT(fSlow6);
			output7[i0] = FAUSTFLOAT(fSlow7);
			output8[i0] = FAUSTFLOAT(fSlow8);
			output9[i0] = FAUSTFLOAT(fSlow9);
			output10[i0] = FAUSTFLOAT(fSlow10);
			output11[i0] = FAUSTFLOAT(fSlow11);
			output12[i0] = FAUSTFLOAT(fSlow12);
			output13[i0] = FAUSTFLOAT(fSlow13);
			output14[i0] = FAUSTFLOAT(fSlow14);
			output15[i0] = FAUSTFLOAT(fSlow15);
			fVbargraph0 = FAUSTFLOAT(float(input0[i0]));
			output16[i0] = FAUSTFLOAT(fVbargraph0);
			output17[i0] = FAUSTFLOAT(fSlow16);
			output18[i0] = FAUSTFLOAT(fSlow17);
			output19[i0] = FAUSTFLOAT(fSlow18);
			output20[i0] = FAUSTFLOAT(fSlow19);
			fVbargraph1 = FAUSTFLOAT(float(input1[i0]));
			output21[i0] = FAUSTFLOAT(fVbargraph1);
			output22[i0] = FAUSTFLOAT(fSlow20);
			output23[i0] = FAUSTFLOAT(fSlow21);
			output24[i0] = FAUSTFLOAT(fSlow22);
			output25[i0] = FAUSTFLOAT(fSlow23);
			fVbargraph2 = FAUSTFLOAT(float(input2[i0]));
			output26[i0] = FAUSTFLOAT(fVbargraph2);
			fHbargraph0 = FAUSTFLOAT(float(input3[i0]));
			output27[i0] = FAUSTFLOAT(fHbargraph0);
			output28[i0] = FAUSTFLOAT(fSlow24);
			output29[i0] = FAUSTFLOAT(fSlow25);
			output30[i0] = FAUSTFLOAT(fSlow26);
			output31[i0] = FAUSTFLOAT(fSlow27);
			fVbargraph3 = FAUSTFLOAT(float(input4[i0]));
			output32[i0] = FAUSTFLOAT(fVbargraph3);
			fHbargraph1 = FAUSTFLOAT(float(input5[i0]));
			output33[i0] = FAUSTFLOAT(fHbargraph1);
		}
	}

};

using Base = clap::helpers::Plugin<
    clap::helpers::MisbehaviourHandler::Terminate,
    clap::helpers::CheckingLevel::Minimal>;

static const clap_plugin_descriptor_t gain_desc = {
    .clap_version = CLAP_VERSION_INIT,
    .id = "org.faust.gain",
    .name = "Faust Gain",
    .vendor = "faust",
    .url = "https://faust.grame.fr",
    .manual_url = "",
    .support_url = "",
    .version = "1.0.0",
    .description = "Simple gain plugin generated from Faust",
    .features = (const char*[]) { CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr }
};

class GainPlugin final : public Base {
public:
    int fNumInputs = 0;
    int fNumOutputs = 0;
    mydsp fDSP;
    GuardedUI fUI;
    std::vector<std::string> fParamAddresses;
    std::vector<float> fExpectedValues;
    bool fHasFlushed = false;

    GainPlugin(const clap_plugin_descriptor_t* desc, const clap_host_t* host)
    : Base(desc, host) {}

    bool init() noexcept override {
        fDSP.buildUserInterface(&fUI);
        fParamAddresses.clear();
        for (int i = 0; i < fUI.getParamsCount(); ++i) {
            auto shortname = fUI.getParamShortname(i);
            fParamAddresses.push_back(shortname);
            float actual = fUI.getParamValue(shortname);
            fExpectedValues.push_back(actual);
        }
        return true;
    }

    bool startProcessing() noexcept override {
        return Base::startProcessing(); //set status to processing
    }

    void stopProcessing() noexcept override {
        Base::stopProcessing(); //resets status to activated
    }

    bool activate(double sampleRate, uint32_t, uint32_t) noexcept override {
        fDSP.init(sampleRate);
        fNumInputs = fDSP.getNumInputs();
        fNumOutputs = fDSP.getNumOutputs();
        std::cerr << "[activate] Sample rate: " << sampleRate << std::endl;
        std::cerr << "[activate] Input channels: " << fNumInputs << ", Output channels: " << fNumOutputs << std::endl;
        return true;
    }


    bool applyParamEventIfValid(const clap_event_header_t* hdr) {
        if (hdr->space_id != CLAP_CORE_EVENT_SPACE_ID) {
            return false;
        }

        if (hdr->type != CLAP_EVENT_PARAM_VALUE) return false;

        const auto* evParam = reinterpret_cast<const clap_event_param_value_t*>(hdr);
        if (evParam->param_id >= fParamAddresses.size()) return false;

        GuardedScope guard(fUI, "applyParamEventIfValid");
        fUI.setParamValue(fParamAddresses[evParam->param_id], evParam->value);
        fExpectedValues[evParam->param_id] = evParam->value;

        return true;
    }



    clap_process_status process(const clap_process_t* process) noexcept override {
        if (!process || process->audio_inputs_count < 1 || process->audio_outputs_count < 1)
            return CLAP_PROCESS_ERROR;

        const auto& inBuffer  = process->audio_inputs[0];
        const auto& outBuffer = process->audio_outputs[0];

        //skip processing gracefully if no audio channels are connected
        if (inBuffer.channel_count == 0 || outBuffer.channel_count == 0)
            return CLAP_PROCESS_CONTINUE;

        if (inBuffer.channel_count < fNumInputs ||
            outBuffer.channel_count < fNumOutputs) {
            std::cerr << "[error] Channel count mismatch: in="
                      << inBuffer.channel_count << ", expected="
                      << fNumInputs << " / out=" << outBuffer.channel_count
                      << ", expected=" << fNumOutputs << "\n";
            return CLAP_PROCESS_ERROR;
            }

        //apply param events
        if (auto events = process->in_events) {
            for (uint32_t i = 0, N = events->size(events); i < N; ++i) {
                applyParamEventIfValid(events->get(events, i));
            }
        }

        //prepare pointers
        FAUSTFLOAT* inputs[fNumInputs];
        FAUSTFLOAT* outputs[fNumOutputs];
        for (int i = 0; i < fNumInputs; ++i)
            inputs[i] = inBuffer.data32[i];
        for (int i = 0; i < fNumOutputs; ++i)
            outputs[i] = outBuffer.data32[i];

        //process audio
        GuardedScope guard(fUI, "full-buffer");
        fDSP.compute(process->frames_count, inputs, outputs);

        return CLAP_PROCESS_CONTINUE;
    }


    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return static_cast<uint32_t>(fParamAddresses.size()); }

    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override {
        return 1; //still 1 port, but could change if faust generates multiple ports
    }
    bool audioPortsInfo(uint32_t index, bool isInput, clap_audio_port_info_t* info) const noexcept override {
        if (index != 0) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        snprintf(info->name, sizeof(info->name), "%s", isInput ? "Input" : "Output");
        info->channel_count = isInput ? fNumInputs : fNumOutputs;
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->port_type = nullptr;
        return true;
    }

    bool paramsInfo(uint32_t index, clap_param_info_t* info) const noexcept override {
        if (index >= fParamAddresses.size()) return false;
        std::memset(info, 0, sizeof(*info));
        info->id = index;
        const char* addr = fParamAddresses[index].c_str();
        if (addr[0] == '/') addr += 1;
        snprintf(info->name, sizeof(info->name), "%s", addr);
        info->min_value = 0.f;
        info->max_value = 1.f;
        info->default_value = 0.5f;
        info->flags = CLAP_PARAM_IS_AUTOMATABLE;
        return true;
    }

    bool paramsValue(clap_id id, double* value) noexcept override {
        if (id >= fExpectedValues.size()) return false;
        *value = fExpectedValues[id];
        return true;
    }

    bool paramsTextToValue(clap_id, const char*, double*) noexcept override { return false; }
    bool paramsValueToText(clap_id, double, char*, uint32_t) noexcept override { return false; }

    void paramsFlush(const clap_input_events_t* in, const clap_output_events_t*) noexcept override {
        if (!in) return;
        fHasFlushed = true;

        for (uint32_t i = 0; i < in->size(in); ++i) {
            const clap_event_header_t* hdr = in->get(in, i);
            if (!applyParamEventIfValid(hdr)) {
            }
        }
    }
    using Base::clapPlugin;
    static const clap_plugin_t* create(const clap_host_t* host) {
        return (new GainPlugin(&gain_desc, host))->clapPlugin();
    }
};
static uint32_t plugin_count(const clap_plugin_factory_t*) { return 1; }
static const clap_plugin_descriptor_t* plugin_desc(const clap_plugin_factory_t*, uint32_t index) {
    return (index == 0) ? &gain_desc : nullptr;
}
static const clap_plugin_t* plugin_create(const clap_plugin_factory_t*, const clap_host_t* host, const char* plugin_id) {
    if (std::strcmp(plugin_id, gain_desc.id) == 0) {
        return GainPlugin::create(host);
    }
    return nullptr;
}
static const clap_plugin_factory_t gain_factory = {
    .get_plugin_count = plugin_count,
    .get_plugin_descriptor = plugin_desc,
    .create_plugin = plugin_create
};
static bool entry_init(const char* path) { return true; }
static void entry_deinit() {}

extern "C" {
CLAP_EXPORT const void* clap_get_factory(const char* factory_id) {
    if (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
        return &gain_factory;
    return nullptr;
}
CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
    CLAP_VERSION_INIT,
    entry_init,
    entry_deinit,
    clap_get_factory
};
}

#endif
