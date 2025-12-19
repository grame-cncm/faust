// Minimal harness to generate an SVG from a synthetic Faust DSP layout.
// Builds a small UI with H/V/Tab groups and writes the SVG to /tmp/layoutui.svg (or argv[1]).

#include <fstream>
#include <iostream>
#include <string>

#include "faust/gui/SVGExport.h"
#include "faust/gui/HTMLExport.h"

// Smallest layout: button, check, knob slider
struct SimpleDSP {
    FAUSTFLOAT fGate = 0;
    FAUSTFLOAT fEnabled = 0;
    FAUSTFLOAT fGain = 0;

    void buildUserInterface(UI* ui)
    {
        ui->openVerticalBox("Root");
        ui->declare(&fGain, "style", "knob");
        ui->declare(&fGain, "unit", "dB");
        ui->addButton("gate", &fGate);
        ui->addCheckButton("enabled", &fEnabled);
        ui->addHorizontalSlider("gain", &fGain, 0.f, -60.f, 6.f, 0.1f);
        ui->closeBox();
    }
};

// Moderate layout: add vslider, numerical entry, bargraph
struct MediumDSP {
    FAUSTFLOAT fGate = 0;
    FAUSTFLOAT fEnabled = 0;
    FAUSTFLOAT fGain = 0;
    FAUSTFLOAT fFreq = 440;
    FAUSTFLOAT fMix = 50;
    FAUSTFLOAT fLevel = 0;

    void buildUserInterface(UI* ui)
    {
        ui->openVerticalBox("Root");
        ui->declare(&fGain, "style", "knob");
        ui->declare(&fGain, "unit", "dB");
        ui->addButton("gate", &fGate);
        ui->addCheckButton("enabled", &fEnabled);
        ui->addHorizontalSlider("gain", &fGain, 0.f, -60.f, 6.f, 0.1f);

        ui->openHorizontalBox("Row");
        ui->declare(&fFreq, "unit", "Hz");
        ui->declare(&fFreq, "scale", "log");
        ui->addVerticalSlider("freq", &fFreq, 440.f, 20.f, 20000.f, 1.f);
        ui->declare(&fMix, "unit", "%");
        ui->declare(&fMix, "style", "numerical");
        ui->addNumEntry("mix", &fMix, 50.f, 0.f, 100.f, 0.1f);
        ui->addHorizontalBargraph("level", &fLevel, -60.f, 0.f);
        ui->closeBox();

        ui->closeBox();  // Root
    }
};

// Pure vertical layout, menu metadata, exp scale, LED bargraph
struct VerticalDSP {
    FAUSTFLOAT fExp = 0;
    FAUSTFLOAT fMode = 0;
    FAUSTFLOAT fVBar = 0;

    void buildUserInterface(UI* ui)
    {
        ui->openVerticalBox("VerticalRoot");
        ui->declare(&fExp, "scale", "exp");
        ui->addVerticalSlider("exp", &fExp, 0.1f, 0.f, 1.f, 0.01f);
        ui->declare(&fMode, "style", "menu{'Slow':0; 'Medium':1; 'Fast':2}");
        ui->addVerticalSlider("mode", &fMode, 0.f, 0.f, 2.f, 1.f);
        ui->declare(&fVBar, "unit", "dB");
        ui->declare(&fVBar, "style", "led");
        ui->addVerticalBargraph("vbar", &fVBar, -60.f, 0.f);
        ui->closeBox();
    }
};

// Pure horizontal layout, radio metadata, bargraph
struct HorizontalDSP {
    FAUSTFLOAT fGate = 0;
    FAUSTFLOAT fCheck = 0;
    FAUSTFLOAT fRadio = 0;
    FAUSTFLOAT fHBar = 0;

    void buildUserInterface(UI* ui)
    {
        ui->openHorizontalBox("HorizontalRoot");
        ui->addButton("btn", &fGate);
        ui->addCheckButton("chk", &fCheck);
        ui->declare(&fRadio, "style", "radio{'A':0; 'B':1; 'C':2}");
        ui->addHorizontalSlider("mode", &fRadio, 0.f, 0.f, 2.f, 1.f);
        ui->addHorizontalBargraph("hbar[unit:%]", &fHBar, 0.f, 100.f);
        ui->closeBox();
    }
};

// Tabs and nested tabs, plus hidden metadata
struct TabbedDSP {
    FAUSTFLOAT fSlider1 = 0;
    FAUSTFLOAT fSlider2 = 0;
    FAUSTFLOAT fHidden = 0;

    void buildUserInterface(UI* ui)
    {
        ui->openTabBox("MainTabs");
        ui->openVerticalBox("TabA");
        ui->addHorizontalSlider("a-slider", &fSlider1, 0.f, 0.f, 1.f, 0.01f);
        ui->openTabBox("SubTabs");
        ui->openHorizontalBox("Sub1");
        ui->addHorizontalSlider("sub1-slider", &fSlider2, 0.f, 0.f, 1.f, 0.01f);
        ui->closeBox();
        ui->openHorizontalBox("Sub2");
        ui->declare(&fHidden, "hidden", "1");
        ui->addHorizontalSlider("hidden-slider", &fHidden, 0.f, 0.f, 1.f, 0.01f);
        ui->closeBox();
        ui->closeBox(); // SubTabs
        ui->closeBox(); // TabA
        ui->openVerticalBox("TabB");
        ui->addButton("tab-button", &fSlider1);
        ui->closeBox();
        ui->closeBox(); // MainTabs
    }
};

// Full layout mixing groups, metadata, and tabs
struct ComplexDSP {
    FAUSTFLOAT fGate = 0;
    FAUSTFLOAT fEnabled = 0;
    FAUSTFLOAT fGain = 0;
    FAUSTFLOAT fFreq = 440;
    FAUSTFLOAT fMix = 50;
    FAUSTFLOAT fLevel = 0;
    FAUSTFLOAT fMode = 0;
    FAUSTFLOAT fShape = 0;
    FAUSTFLOAT fPan = 0;
    FAUSTFLOAT fMeter = 0;

    void buildUserInterface(UI* ui)
    {
        ui->openVerticalBox("Root");
        ui->declare(&fGain, "style", "knob");
        ui->declare(&fGain, "unit", "dB");
        ui->addButton("gate", &fGate);
        ui->addCheckButton("enabled", &fEnabled);
        ui->addHorizontalSlider("gain", &fGain, 0.f, -60.f, 6.f, 0.1f);

        ui->openHorizontalBox("Row");
        ui->declare(&fFreq, "unit", "Hz");
        ui->declare(&fFreq, "scale", "log");
        ui->addVerticalSlider("freq", &fFreq, 440.f, 20.f, 20000.f, 1.f);
        ui->declare(&fMix, "unit", "%");
        ui->declare(&fMix, "style", "numerical");
        ui->addNumEntry("mix", &fMix, 50.f, 0.f, 100.f, 0.1f);
        ui->addHorizontalBargraph("level", &fLevel, -60.f, 0.f);
        ui->declare(&fMode, "style", "radio{'Off':0; 'On':1; 'Auto':2}");
        ui->addHorizontalSlider("mode", &fMode, 0.f, 0.f,
                                2.f, 1.f);
        ui->declare(&fShape, "style", "menu{'Sine':0; 'Square':1; 'Saw':2}");
        ui->addVerticalSlider("shape", &fShape, 0.f, 0.f,
                              2.f, 1.f);
        ui->closeBox();

        ui->openTabBox("tabs");
        ui->openVerticalBox("tab1");
        ui->addHorizontalSlider("pan", &fPan, 0.f, -1.f, 1.f, 0.01f);
        ui->closeBox();
        ui->openVerticalBox("tab2");
        ui->addVerticalBargraph("meter", &fMeter, -60.f, 0.f);
        ui->closeBox();
        ui->closeBox();  // tabs

        ui->closeBox();  // Root
    }
};

int main(int argc, char** argv)
{
    SimpleDSP   dsp_simple;
    MediumDSP   dsp_medium;
    VerticalDSP dsp_vertical;
    HorizontalDSP dsp_horizontal;
    TabbedDSP   dsp_tabs;
    ComplexDSP  dsp_complex;

    struct Job {
        std::string filename;
        std::string svg;
        std::string html;
    };

    Job jobs[] = {
        { "layoutui-simple",  toSVG(&dsp_simple, 300.f, 200.f, true),  toHTML(&dsp_simple, 300.f, 200.f, false) },
        { "layoutui-medium",  toSVG(&dsp_medium, 400.f, 250.f, true),  toHTML(&dsp_medium, 400.f, 250.f, false) },
        { "layoutui-vertical", toSVG(&dsp_vertical, 200.f, 320.f, true), toHTML(&dsp_vertical, 200.f, 320.f, false) },
        { "layoutui-horizontal", toSVG(&dsp_horizontal, 500.f, 200.f, true), toHTML(&dsp_horizontal, 500.f, 200.f, false) },
        { "layoutui-tabs", toSVG(&dsp_tabs, 400.f, 300.f, true), toHTML(&dsp_tabs, 400.f, 300.f, false) },
        { "layoutui-complex", toSVG(&dsp_complex, 400.f, 300.f, true), toHTML(&dsp_complex, 400.f, 300.f, false) }
    };

    for (const auto& job : jobs) {
        std::ofstream ofs(job.filename + ".svg");
        if (!ofs.is_open()) {
            std::cerr << "Cannot open output file: " << job.filename << ".svg" << std::endl;
            return 1;
        }
        ofs << job.svg;
        std::cout << "Wrote SVG to " << job.filename << ".svg" << std::endl;

        std::ofstream ofh(job.filename + ".html");
        if (!ofh.is_open()) {
            std::cerr << "Cannot open output file: " << job.filename << ".html" << std::endl;
            return 1;
        }
        ofh << job.html;
        std::cout << "Wrote HTML to " << job.filename << ".html" << std::endl;
    }

    return 0;
}
