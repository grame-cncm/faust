======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("virtual_analog_oscillators")
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "See Faust's oscillator.lib for documentation and references")
	OpenVerticalBox("VIRTUAL ANALOG OSCILLATORS")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("Signal Levels")
	AddMetaDeclareInst(fVslider1, "0", "")
	AddMetaDeclareInst(fVslider1, "style", "vslider")
	AddVerticalSlider("Sawtooth", fVslider1, 1.0f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("Pulse Train")
	AddMetaDeclareInst(fCheckbox2, "0", "")
	AddMetaDeclareInst(fCheckbox2, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)      See if you can hear a difference with the freq high and swept")
	AddCheckButtonInst("Order 3"fCheckbox2)
	AddMetaDeclareInst(fVslider7, "1", "")
	AddMetaDeclareInst(fVslider7, "style", "vslider")
	AddVerticalSlider("0x00", fVslider7, 0.0f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fVslider8, "2", "")
	AddMetaDeclareInst(fVslider8, "style", "knob")
	AddVerticalSlider("Duty Cycle", fVslider8, 0.5f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
	AddMetaDeclareInst(fVslider5, "2", "")
	AddMetaDeclareInst(fVslider5, "style", "vslider")
	AddVerticalSlider("Square", fVslider5, 0.0f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fVslider6, "3", "")
	AddMetaDeclareInst(fVslider6, "style", "vslider")
	AddVerticalSlider("Triangle", fVslider6, 0.0f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fVslider9, "4", "")
	AddMetaDeclareInst(fVslider9, "style", "vslider")
	AddMetaDeclareInst(fVslider9, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the same total power in every octave (uses only amplitude controls)")
	AddVerticalSlider("Pink Noise", fVslider9, 0.0f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fVslider0, "5", "")
	AddMetaDeclareInst(fVslider0, "style", "vslider")
	AddVerticalSlider("Ext Input", fVslider0, 0.0f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("Signal Parameters")
	AddMetaDeclareInst(0, "0", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(fHslider4, "1", "")
	AddMetaDeclareInst(fHslider4, "style", "hslider")
	AddMetaDeclareInst(fHslider4, "tooltip", "Sawtooth waveform amplitude")
	AddMetaDeclareInst(fHslider4, "unit", "dB")
	AddHorizontalSlider("Mix Amplitude", fHslider4, -2e+01f, -1.2e+02f, 1e+01f, 0.1f)
	AddMetaDeclareInst(fHslider5, "2", "")
	AddMetaDeclareInst(fHslider5, "style", "hslider")
	AddMetaDeclareInst(fHslider5, "tooltip", "Sawtooth frequency as a Piano Key (PK) number (A440 = key 49)")
	AddMetaDeclareInst(fHslider5, "unit", "PK")
	AddHorizontalSlider("Frequency", fHslider5, 49.0f, 1.0f, 88.0f, 0.01f)
	CloseboxInst
	AddMetaDeclareInst(fVslider3, "3", "")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Percentage frequency-shift up or down for second oscillator")
	AddMetaDeclareInst(fVslider3, "unit", "%%")
	AddVerticalSlider("Detuning 1", fVslider3, -0.1f, -1e+01f, 1e+01f, 0.01f)
	AddMetaDeclareInst(fVslider4, "4", "")
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddMetaDeclareInst(fVslider4, "tooltip", "Percentage frequency-shift up or down for third detuned oscillator")
	AddMetaDeclareInst(fVslider4, "unit", "%%")
	AddVerticalSlider("Detuning 2", fVslider4, 0.1f, -1e+01f, 1e+01f, 0.01f)
	AddMetaDeclareInst(fVslider2, "5", "")
	AddMetaDeclareInst(fVslider2, "scale", "log")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds")
	AddMetaDeclareInst(fVslider2, "unit", "sec")
	AddVerticalSlider("Portamento", fVslider2, 0.1f, 0.001f, 1e+01f, 0.001f)
	AddMetaDeclareInst(fEntry0, "6", "")
	AddMetaDeclareInst(fEntry0, "tooltip", "Order of sawtooth aliasing suppression")
	AddNumEntry"Saw Order", fEntry0, 2.0f, 1.0f, 4.0f, 1.0f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(0, "tooltip", "See Faust's effect.lib for info and references")
	OpenHorizontalBox("MOOG VCF (Voltage Controlled Filter)")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the Moog VCF has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fCheckbox1, "1", "")
	AddMetaDeclareInst(fCheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad) implementation, instead of the default moog_vcf (analog style) implementation")
	AddCheckButtonInst("Use Biquads"fCheckbox1)
	AddMetaDeclareInst(fCheckbox3, "2", "")
	AddMetaDeclareInst(fCheckbox3, "tooltip", "If using biquads, make them normalized ladders (moog_vcf_2bn)")
	AddCheckButtonInst("Normalized Ladders"fCheckbox3)
	CloseboxInst
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "tooltip", "The VCF resonates at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).  The VCF response is flat below the corner frequency, and rolls off -24 dB per octave above.")
	AddMetaDeclareInst(fHslider3, "unit", "PK")
	AddHorizontalSlider("Corner Frequency", fHslider3, 25.0f, 1.0f, 88.0f, 0.01f)
	AddMetaDeclareInst(fHslider6, "2", "")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddMetaDeclareInst(fHslider6, "tooltip", "Amount of resonance near VCF corner frequency (specified between 0 and 1)")
	AddHorizontalSlider("Corner Resonance", fHslider6, 0.9f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fHslider2, "3", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "tooltip", "output level in decibels")
	AddMetaDeclareInst(fHslider2, "unit", "dB")
	AddHorizontalSlider("VCF Output Level", fHslider2, 5.0f, -6e+01f, 2e+01f, 0.1f)
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "See Faust's filter.lib for documentation and references")
	OpenHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP")
	AddMetaDeclareInst(fVbargraph14, "0", "")
	AddMetaDeclareInst(fVbargraph14, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph14, "unit", "dB")
	AddVerticalBargraph("vbargraph0", fVbargraph14, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph13, "1", "")
	AddMetaDeclareInst(fVbargraph13, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph13, "unit", "dB")
	AddVerticalBargraph("vbargraph1", fVbargraph13, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph12, "2", "")
	AddMetaDeclareInst(fVbargraph12, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph12, "unit", "dB")
	AddVerticalBargraph("vbargraph2", fVbargraph12, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph11, "3", "")
	AddMetaDeclareInst(fVbargraph11, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph11, "unit", "dB")
	AddVerticalBargraph("vbargraph3", fVbargraph11, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph10, "4", "")
	AddMetaDeclareInst(fVbargraph10, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph10, "unit", "dB")
	AddVerticalBargraph("vbargraph4", fVbargraph10, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph9, "5", "")
	AddMetaDeclareInst(fVbargraph9, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph9, "unit", "dB")
	AddVerticalBargraph("vbargraph5", fVbargraph9, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph8, "6", "")
	AddMetaDeclareInst(fVbargraph8, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph8, "unit", "dB")
	AddVerticalBargraph("vbargraph6", fVbargraph8, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph7, "7", "")
	AddMetaDeclareInst(fVbargraph7, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph7, "unit", "dB")
	AddVerticalBargraph("vbargraph7", fVbargraph7, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph6, "8", "")
	AddMetaDeclareInst(fVbargraph6, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("vbargraph8", fVbargraph6, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph5, "9", "")
	AddMetaDeclareInst(fVbargraph5, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("vbargraph9", fVbargraph5, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph4, "10", "")
	AddMetaDeclareInst(fVbargraph4, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("vbargraph10", fVbargraph4, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph3, "11", "")
	AddMetaDeclareInst(fVbargraph3, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("vbargraph11", fVbargraph3, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph2, "12", "")
	AddMetaDeclareInst(fVbargraph2, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("vbargraph12", fVbargraph2, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph1, "13", "")
	AddMetaDeclareInst(fVbargraph1, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("vbargraph13", fVbargraph1, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph0, "14", "")
	AddMetaDeclareInst(fVbargraph0, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("vbargraph14", fVbargraph0, -5e+01f, 1e+01f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("SPECTRUM ANALYZER CONTROLS")
	AddMetaDeclareInst(fHslider1, "0", "")
	AddMetaDeclareInst(fHslider1, "scale", "log")
	AddMetaDeclareInst(fHslider1, "tooltip", "band-level averaging time in milliseconds")
	AddMetaDeclareInst(fHslider1, "unit", "ms")
	AddHorizontalSlider("Level Averaging Time", fHslider1, 1e+02f, 1.0f, 1e+04f, 1.0f)
	AddMetaDeclareInst(fHslider0, "1", "")
	AddMetaDeclareInst(fHslider0, "tooltip", "Level offset in decibels")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Level dB Offset", fHslider0, 5e+01f, 0.0f, 1e+02f, 1.0f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("int[4]", iVec0)("FAUSTFLOAT", fHslider1)("int", fSampleRate)("float", fConst0)("float", fConst1)("float", fConst2)("float", fConst3)("float", fConst4)("float", fConst5)("float", fConst6)("float", fConst7)("float", fConst8)("float", fConst9)("float", fConst10)("float", fConst11)("float", fConst12)("float", fConst13)("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fHslider2)("float[2]", fRec4)("FAUSTFLOAT", fCheckbox1)("float", fConst14)("FAUSTFLOAT", fHslider3)("float[2]", fRec10)("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fHslider4)("float[2]", fRec11)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fEntry0)("float", fConst15)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fHslider5)("float[2]", fRec13)("float[2]", fRec12)("float", fConst16)("float[2]", fVec1)("float", fConst17)("float[2]", fVec2)("float[2]", fVec3)("float", fConst18)("float[2]", fVec4)("float[2]", fVec5)("float[2]", fVec6)("FAUSTFLOAT", fVslider3)("float[2]", fRec14)("float[2]", fVec7)("float[2]", fVec8)("float[2]", fVec9)("float[2]", fVec10)("float[2]", fVec11)("float[2]", fVec12)("FAUSTFLOAT", fVslider4)("float[2]", fRec15)("float[2]", fVec13)("float[2]", fVec14)("float[2]", fVec15)("float[2]", fVec16)("float[2]", fVec17)("float[2]", fVec18)("float", fConst19)("FAUSTFLOAT", fVslider5)("float[2]", fRec16)("float[2]", fVec19)("int", IOTA0)("float[4096]", fVec20)("float", fConst20)("float[2]", fRec17)("float[2]", fVec21)("float[4096]", fVec22)("float[2]", fRec18)("float[2]", fVec23)("float[4096]", fVec24)("float", fConst21)("FAUSTFLOAT", fVslider6)("float[2]", fRec19)("float[2]", fRec20)("float[2]", fRec21)("FAUSTFLOAT", fVslider7)("float", fConst22)("FAUSTFLOAT", fCheckbox2)("float[2]", fVec25)("float[2]", fVec26)("float[4096]", fVec27)("FAUSTFLOAT", fVslider8)("float[2]", fRec22)("float[2]", fVec28)("float[2]", fVec29)("float[4096]", fVec30)("float[2]", fVec31)("float[2]", fVec32)("float[4096]", fVec33)("FAUSTFLOAT", fVslider9)("int[2]", iRec24)("float[4]", fRec23)("FAUSTFLOAT", fHslider6)("float[2]", fRec9)("float[2]", fRec8)("float[2]", fRec7)("float[2]", fRec6)("float[2]", fRec5)("FAUSTFLOAT", fCheckbox3)("float", fConst23)("float[3]", fRec26)("float[3]", fRec25)("float[2]", fRec29)("float[2]", fRec27)("float[2]", fRec32)("float[2]", fRec30)("float", fConst24)("float", fConst25)("float", fConst26)("float[3]", fRec3)("float", fConst27)("float", fConst28)("float", fConst29)("float[3]", fRec2)("float", fConst30)("float", fConst31)("float", fConst32)("float[3]", fRec1)("float", fConst33)("float[2]", fRec0)("FAUSTFLOAT", fVbargraph0)("float", fConst34)("float", fConst35)("float", fConst36)("float", fConst37)("float", fConst38)("float", fConst39)("float", fConst40)("float", fConst41)("float", fConst42)("float", fConst43)("float", fConst44)("float", fConst45)("float", fConst46)("float", fConst47)("float", fConst48)("float", fConst49)("float", fConst50)("float", fConst51)("float", fConst52)("float", fConst53)("float", fConst54)("float[3]", fRec39)("float", fConst55)("float", fConst56)("float", fConst57)("float[3]", fRec38)("float", fConst58)("float", fConst59)("float", fConst60)("float[3]", fRec37)("float", fConst61)("float", fConst62)("float", fConst63)("float", fConst64)("float[3]", fRec36)("float", fConst65)("float", fConst66)("float", fConst67)("float[3]", fRec35)("float", fConst68)("float", fConst69)("float", fConst70)("float[3]", fRec34)("float", fConst71)("float[2]", fRec33)("FAUSTFLOAT", fVbargraph1)("float", fConst72)("float", fConst73)("float", fConst74)("float", fConst75)("float", fConst76)("float", fConst77)("float", fConst78)("float", fConst79)("float", fConst80)("float", fConst81)("float", fConst82)("float", fConst83)("float", fConst84)("float", fConst85)("float", fConst86)("float", fConst87)("float", fConst88)("float", fConst89)("float", fConst90)("float", fConst91)("float", fConst92)("float[3]", fRec46)("float", fConst93)("float", fConst94)("float", fConst95)("float[3]", fRec45)("float", fConst96)("float", fConst97)("float", fConst98)("float[3]", fRec44)("float", fConst99)("float", fConst100)("float", fConst101)("float", fConst102)("float[3]", fRec43)("float", fConst103)("float", fConst104)("float", fConst105)("float[3]", fRec42)("float", fConst106)("float", fConst107)("float", fConst108)("float[3]", fRec41)("float", fConst109)("float[2]", fRec40)("FAUSTFLOAT", fVbargraph2)("float", fConst110)("float", fConst111)("float", fConst112)("float", fConst113)("float", fConst114)("float", fConst115)("float", fConst116)("float", fConst117)("float", fConst118)("float", fConst119)("float", fConst120)("float", fConst121)("float", fConst122)("float", fConst123)("float", fConst124)("float", fConst125)("float", fConst126)("float", fConst127)("float", fConst128)("float", fConst129)("float", fConst130)("float[3]", fRec53)("float", fConst131)("float", fConst132)("float", fConst133)("float[3]", fRec52)("float", fConst134)("float", fConst135)("float", fConst136)("float[3]", fRec51)("float", fConst137)("float", fConst138)("float", fConst139)("float", fConst140)("float[3]", fRec50)("float", fConst141)("float", fConst142)("float", fConst143)("float[3]", fRec49)("float", fConst144)("float", fConst145)("float", fConst146)("float[3]", fRec48)("float", fConst147)("float[2]", fRec47)("FAUSTFLOAT", fVbargraph3)("float", fConst148)("float", fConst149)("float", fConst150)("float", fConst151)("float", fConst152)("float", fConst153)("float", fConst154)("float", fConst155)("float", fConst156)("float", fConst157)("float", fConst158)("float", fConst159)("float", fConst160)("float", fConst161)("float", fConst162)("float", fConst163)("float", fConst164)("float", fConst165)("float", fConst166)("float", fConst167)("float", fConst168)("float[3]", fRec60)("float", fConst169)("float", fConst170)("float", fConst171)("float[3]", fRec59)("float", fConst172)("float", fConst173)("float", fConst174)("float[3]", fRec58)("float", fConst175)("float", fConst176)("float", fConst177)("float", fConst178)("float[3]", fRec57)("float", fConst179)("float", fConst180)("float", fConst181)("float[3]", fRec56)("float", fConst182)("float", fConst183)("float", fConst184)("float[3]", fRec55)("float", fConst185)("float[2]", fRec54)("FAUSTFLOAT", fVbargraph4)("float", fConst186)("float", fConst187)("float", fConst188)("float", fConst189)("float", fConst190)("float", fConst191)("float", fConst192)("float", fConst193)("float", fConst194)("float", fConst195)("float", fConst196)("float", fConst197)("float", fConst198)("float", fConst199)("float", fConst200)("float", fConst201)("float", fConst202)("float", fConst203)("float", fConst204)("float", fConst205)("float", fConst206)("float[3]", fRec67)("float", fConst207)("float", fConst208)("float", fConst209)("float[3]", fRec66)("float", fConst210)("float", fConst211)("float", fConst212)("float[3]", fRec65)("float", fConst213)("float", fConst214)("float", fConst215)("float", fConst216)("float[3]", fRec64)("float", fConst217)("float", fConst218)("float", fConst219)("float[3]", fRec63)("float", fConst220)("float", fConst221)("float", fConst222)("float[3]", fRec62)("float", fConst223)("float[2]", fRec61)("FAUSTFLOAT", fVbargraph5)("float", fConst224)("float", fConst225)("float", fConst226)("float", fConst227)("float", fConst228)("float", fConst229)("float", fConst230)("float", fConst231)("float", fConst232)("float", fConst233)("float", fConst234)("float", fConst235)("float", fConst236)("float", fConst237)("float", fConst238)("float", fConst239)("float", fConst240)("float", fConst241)("float", fConst242)("float", fConst243)("float", fConst244)("float[3]", fRec74)("float", fConst245)("float", fConst246)("float", fConst247)("float[3]", fRec73)("float", fConst248)("float", fConst249)("float", fConst250)("float[3]", fRec72)("float", fConst251)("float", fConst252)("float", fConst253)("float", fConst254)("float[3]", fRec71)("float", fConst255)("float", fConst256)("float", fConst257)("float[3]", fRec70)("float", fConst258)("float", fConst259)("float", fConst260)("float[3]", fRec69)("float", fConst261)("float[2]", fRec68)("FAUSTFLOAT", fVbargraph6)("float", fConst262)("float", fConst263)("float", fConst264)("float", fConst265)("float", fConst266)("float", fConst267)("float", fConst268)("float", fConst269)("float", fConst270)("float", fConst271)("float", fConst272)("float", fConst273)("float", fConst274)("float", fConst275)("float", fConst276)("float", fConst277)("float", fConst278)("float", fConst279)("float", fConst280)("float", fConst281)("float", fConst282)("float[3]", fRec81)("float", fConst283)("float", fConst284)("float", fConst285)("float[3]", fRec80)("float", fConst286)("float", fConst287)("float", fConst288)("float[3]", fRec79)("float", fConst289)("float", fConst290)("float", fConst291)("float", fConst292)("float[3]", fRec78)("float", fConst293)("float", fConst294)("float", fConst295)("float[3]", fRec77)("float", fConst296)("float", fConst297)("float", fConst298)("float[3]", fRec76)("float", fConst299)("float[2]", fRec75)("FAUSTFLOAT", fVbargraph7)("float", fConst300)("float", fConst301)("float", fConst302)("float", fConst303)("float", fConst304)("float", fConst305)("float", fConst306)("float", fConst307)("float", fConst308)("float", fConst309)("float", fConst310)("float", fConst311)("float", fConst312)("float", fConst313)("float", fConst314)("float", fConst315)("float", fConst316)("float", fConst317)("float", fConst318)("float", fConst319)("float", fConst320)("float[3]", fRec88)("float", fConst321)("float", fConst322)("float", fConst323)("float[3]", fRec87)("float", fConst324)("float", fConst325)("float", fConst326)("float[3]", fRec86)("float", fConst327)("float", fConst328)("float", fConst329)("float", fConst330)("float[3]", fRec85)("float", fConst331)("float", fConst332)("float", fConst333)("float[3]", fRec84)("float", fConst334)("float", fConst335)("float", fConst336)("float[3]", fRec83)("float", fConst337)("float[2]", fRec82)("FAUSTFLOAT", fVbargraph8)("float", fConst338)("float", fConst339)("float", fConst340)("float", fConst341)("float", fConst342)("float", fConst343)("float", fConst344)("float", fConst345)("float", fConst346)("float", fConst347)("float", fConst348)("float", fConst349)("float", fConst350)("float", fConst351)("float", fConst352)("float", fConst353)("float", fConst354)("float", fConst355)("float", fConst356)("float", fConst357)("float", fConst358)("float[3]", fRec95)("float", fConst359)("float", fConst360)("float", fConst361)("float[3]", fRec94)("float", fConst362)("float", fConst363)("float", fConst364)("float[3]", fRec93)("float", fConst365)("float", fConst366)("float", fConst367)("float", fConst368)("float[3]", fRec92)("float", fConst369)("float", fConst370)("float", fConst371)("float[3]", fRec91)("float", fConst372)("float", fConst373)("float", fConst374)("float[3]", fRec90)("float", fConst375)("float[2]", fRec89)("FAUSTFLOAT", fVbargraph9)("float", fConst376)("float", fConst377)("float", fConst378)("float", fConst379)("float", fConst380)("float", fConst381)("float", fConst382)("float", fConst383)("float", fConst384)("float", fConst385)("float", fConst386)("float", fConst387)("float", fConst388)("float", fConst389)("float", fConst390)("float", fConst391)("float", fConst392)("float", fConst393)("float", fConst394)("float", fConst395)("float", fConst396)("float[3]", fRec102)("float", fConst397)("float", fConst398)("float", fConst399)("float[3]", fRec101)("float", fConst400)("float", fConst401)("float", fConst402)("float[3]", fRec100)("float", fConst403)("float", fConst404)("float", fConst405)("float", fConst406)("float[3]", fRec99)("float", fConst407)("float", fConst408)("float", fConst409)("float[3]", fRec98)("float", fConst410)("float", fConst411)("float", fConst412)("float[3]", fRec97)("float", fConst413)("float[2]", fRec96)("FAUSTFLOAT", fVbargraph10)("float", fConst414)("float", fConst415)("float", fConst416)("float", fConst417)("float", fConst418)("float", fConst419)("float", fConst420)("float", fConst421)("float", fConst422)("float", fConst423)("float", fConst424)("float", fConst425)("float", fConst426)("float", fConst427)("float", fConst428)("float", fConst429)("float", fConst430)("float", fConst431)("float", fConst432)("float", fConst433)("float", fConst434)("float[3]", fRec109)("float", fConst435)("float", fConst436)("float", fConst437)("float[3]", fRec108)("float", fConst438)("float", fConst439)("float", fConst440)("float[3]", fRec107)("float", fConst441)("float", fConst442)("float", fConst443)("float", fConst444)("float[3]", fRec106)("float", fConst445)("float", fConst446)("float", fConst447)("float[3]", fRec105)("float", fConst448)("float", fConst449)("float", fConst450)("float[3]", fRec104)("float", fConst451)("float[2]", fRec103)("FAUSTFLOAT", fVbargraph11)("float", fConst452)("float", fConst453)("float", fConst454)("float", fConst455)("float", fConst456)("float", fConst457)("float", fConst458)("float", fConst459)("float", fConst460)("float", fConst461)("float", fConst462)("float", fConst463)("float", fConst464)("float", fConst465)("float", fConst466)("float", fConst467)("float", fConst468)("float", fConst469)("float", fConst470)("float", fConst471)("float", fConst472)("float[3]", fRec116)("float", fConst473)("float", fConst474)("float", fConst475)("float[3]", fRec115)("float", fConst476)("float", fConst477)("float", fConst478)("float[3]", fRec114)("float", fConst479)("float", fConst480)("float", fConst481)("float", fConst482)("float[3]", fRec113)("float", fConst483)("float", fConst484)("float", fConst485)("float[3]", fRec112)("float", fConst486)("float", fConst487)("float", fConst488)("float[3]", fRec111)("float", fConst489)("float[2]", fRec110)("FAUSTFLOAT", fVbargraph12)("float", fConst490)("float", fConst491)("float", fConst492)("float", fConst493)("float", fConst494)("float", fConst495)("float", fConst496)("float", fConst497)("float", fConst498)("float", fConst499)("float", fConst500)("float", fConst501)("float", fConst502)("float", fConst503)("float", fConst504)("float", fConst505)("float", fConst506)("float", fConst507)("float", fConst508)("float", fConst509)("float", fConst510)("float[3]", fRec123)("float", fConst511)("float", fConst512)("float", fConst513)("float[3]", fRec122)("float", fConst514)("float", fConst515)("float", fConst516)("float[3]", fRec121)("float", fConst517)("float", fConst518)("float", fConst519)("float", fConst520)("float[3]", fRec120)("float", fConst521)("float", fConst522)("float", fConst523)("float[3]", fRec119)("float", fConst524)("float", fConst525)("float", fConst526)("float[3]", fRec118)("float", fConst527)("float[2]", fRec117)("FAUSTFLOAT", fVbargraph13)("float", fConst528)("float", fConst529)("float", fConst530)("float", fConst531)("float", fConst532)("float", fConst533)("float", fConst534)("float", fConst535)("float", fConst536)("float[3]", fRec127)("float", fConst537)("float", fConst538)("float", fConst539)("float[3]", fRec126)("float", fConst540)("float", fConst541)("float", fConst542)("float[3]", fRec125)("float", fConst543)("float[2]", fRec124)("FAUSTFLOAT", fVbargraph14)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("tanf", BinopInst("/", Float(50265.484f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst5, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("+", LoadVarInst(Address(fConst6, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst9, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("+", LoadVarInst(Address(fConst9, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst2, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("*", Float(0.041666668f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("*", Float(0.0052083335f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("*", Float(0.083333336f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("/", Float(1.3333334f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("*", Float(0.013888889f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst24, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst2, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst26, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst27, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst12, kStruct)))))
	StoreVarInst(Address(fConst28, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst9, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst32, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst33, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst6, kStruct)))))
	StoreVarInst(Address(fConst34, kStruct), FunCallInst("tanf", BinopInst("/", Float(31665.27f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst34, kStruct))))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst37, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst34, kStruct))))
	StoreVarInst(Address(fConst38, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst39, kStruct), BinopInst("+", LoadVarInst(Address(fConst38, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst41, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst42, kStruct), BinopInst("+", LoadVarInst(Address(fConst41, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst43, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst34, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst45, kStruct), BinopInst("+", LoadVarInst(Address(fConst44, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst46, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst47, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst48, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst49, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst50, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst51, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst52, kStruct), BinopInst("+", LoadVarInst(Address(fConst51, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst53, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst54, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst55, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst51, kStruct)))))
	StoreVarInst(Address(fConst56, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst57, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst58, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst59, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst60, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst61, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst62, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst34, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst63, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst64, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst65, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst44, kStruct)))))
	StoreVarInst(Address(fConst66, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst67, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst68, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst41, kStruct)))))
	StoreVarInst(Address(fConst69, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst70, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst71, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst38, kStruct)))))
	StoreVarInst(Address(fConst72, kStruct), FunCallInst("tanf", BinopInst("/", Float(19947.87f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst73, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst72, kStruct))))
	StoreVarInst(Address(fConst74, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst75, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst72, kStruct))))
	StoreVarInst(Address(fConst76, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst77, kStruct), BinopInst("+", LoadVarInst(Address(fConst76, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst78, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst79, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst80, kStruct), BinopInst("+", LoadVarInst(Address(fConst79, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst81, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst72, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst82, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst83, kStruct), BinopInst("+", LoadVarInst(Address(fConst82, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst84, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst85, kStruct), BinopInst("+", LoadVarInst(Address(fConst63, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst86, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst87, kStruct), BinopInst("+", LoadVarInst(Address(fConst63, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst88, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst89, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst90, kStruct), BinopInst("+", LoadVarInst(Address(fConst89, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst91, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst92, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst93, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst89, kStruct)))))
	StoreVarInst(Address(fConst94, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst95, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst96, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst97, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst98, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst99, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst100, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst72, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst101, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst102, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst103, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst82, kStruct)))))
	StoreVarInst(Address(fConst104, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst105, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst106, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst79, kStruct)))))
	StoreVarInst(Address(fConst107, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst108, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst109, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst76, kStruct)))))
	StoreVarInst(Address(fConst110, kStruct), FunCallInst("tanf", BinopInst("/", Float(12566.371f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst111, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst110, kStruct))))
	StoreVarInst(Address(fConst112, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst113, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst110, kStruct))))
	StoreVarInst(Address(fConst114, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst115, kStruct), BinopInst("+", LoadVarInst(Address(fConst114, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst116, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst117, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst118, kStruct), BinopInst("+", LoadVarInst(Address(fConst117, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst119, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst110, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst120, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst121, kStruct), BinopInst("+", LoadVarInst(Address(fConst120, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst122, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst123, kStruct), BinopInst("+", LoadVarInst(Address(fConst101, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst124, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst125, kStruct), BinopInst("+", LoadVarInst(Address(fConst101, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst126, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst127, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst128, kStruct), BinopInst("+", LoadVarInst(Address(fConst127, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst129, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst130, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst131, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst127, kStruct)))))
	StoreVarInst(Address(fConst132, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst133, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst134, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst135, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst136, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst137, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst138, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst110, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst139, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst140, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst141, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst120, kStruct)))))
	StoreVarInst(Address(fConst142, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst143, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst144, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst117, kStruct)))))
	StoreVarInst(Address(fConst145, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst146, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst147, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst114, kStruct)))))
	StoreVarInst(Address(fConst148, kStruct), FunCallInst("tanf", BinopInst("/", Float(7916.3174f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst149, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst150, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst151, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst152, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst153, kStruct), BinopInst("+", LoadVarInst(Address(fConst152, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst154, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst155, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst156, kStruct), BinopInst("+", LoadVarInst(Address(fConst155, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst157, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst148, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst158, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst159, kStruct), BinopInst("+", LoadVarInst(Address(fConst158, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst160, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst161, kStruct), BinopInst("+", LoadVarInst(Address(fConst139, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst162, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst163, kStruct), BinopInst("+", LoadVarInst(Address(fConst139, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst164, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst165, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst166, kStruct), BinopInst("+", LoadVarInst(Address(fConst165, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst167, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst168, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst169, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst165, kStruct)))))
	StoreVarInst(Address(fConst170, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst171, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst172, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst173, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst174, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst175, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst176, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst148, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst177, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst178, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst179, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst158, kStruct)))))
	StoreVarInst(Address(fConst180, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst181, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst182, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst155, kStruct)))))
	StoreVarInst(Address(fConst183, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst184, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst185, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst152, kStruct)))))
	StoreVarInst(Address(fConst186, kStruct), FunCallInst("tanf", BinopInst("/", Float(4986.9673f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst187, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst186, kStruct))))
	StoreVarInst(Address(fConst188, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst189, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst186, kStruct))))
	StoreVarInst(Address(fConst190, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst191, kStruct), BinopInst("+", LoadVarInst(Address(fConst190, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst192, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst193, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst194, kStruct), BinopInst("+", LoadVarInst(Address(fConst193, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst195, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst186, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst196, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst197, kStruct), BinopInst("+", LoadVarInst(Address(fConst196, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst198, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst199, kStruct), BinopInst("+", LoadVarInst(Address(fConst177, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst200, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst201, kStruct), BinopInst("+", LoadVarInst(Address(fConst177, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst202, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst203, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst204, kStruct), BinopInst("+", LoadVarInst(Address(fConst203, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst205, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst206, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst207, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst203, kStruct)))))
	StoreVarInst(Address(fConst208, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst209, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst210, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst211, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst212, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst213, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst214, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst186, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst215, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst216, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst217, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst196, kStruct)))))
	StoreVarInst(Address(fConst218, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst219, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst220, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst193, kStruct)))))
	StoreVarInst(Address(fConst221, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst222, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst223, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst190, kStruct)))))
	StoreVarInst(Address(fConst224, kStruct), FunCallInst("tanf", BinopInst("/", Float(3141.5928f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst225, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst226, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst227, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst228, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst229, kStruct), BinopInst("+", LoadVarInst(Address(fConst228, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst230, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst231, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst232, kStruct), BinopInst("+", LoadVarInst(Address(fConst231, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst233, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst224, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst234, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst235, kStruct), BinopInst("+", LoadVarInst(Address(fConst234, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst236, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst237, kStruct), BinopInst("+", LoadVarInst(Address(fConst215, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst238, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst239, kStruct), BinopInst("+", LoadVarInst(Address(fConst215, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst240, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst241, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst242, kStruct), BinopInst("+", LoadVarInst(Address(fConst241, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst243, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst244, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst245, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst241, kStruct)))))
	StoreVarInst(Address(fConst246, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst247, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst248, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst249, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst250, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst251, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst252, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst224, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst253, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst254, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst255, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst234, kStruct)))))
	StoreVarInst(Address(fConst256, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst257, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst258, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst231, kStruct)))))
	StoreVarInst(Address(fConst259, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst260, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst261, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst228, kStruct)))))
	StoreVarInst(Address(fConst262, kStruct), FunCallInst("tanf", BinopInst("/", Float(1979.0793f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst263, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst262, kStruct))))
	StoreVarInst(Address(fConst264, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst265, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst262, kStruct))))
	StoreVarInst(Address(fConst266, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst267, kStruct), BinopInst("+", LoadVarInst(Address(fConst266, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst268, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst269, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst270, kStruct), BinopInst("+", LoadVarInst(Address(fConst269, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst271, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst262, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst272, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst273, kStruct), BinopInst("+", LoadVarInst(Address(fConst272, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst274, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst275, kStruct), BinopInst("+", LoadVarInst(Address(fConst253, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst276, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst277, kStruct), BinopInst("+", LoadVarInst(Address(fConst253, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst278, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst279, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst280, kStruct), BinopInst("+", LoadVarInst(Address(fConst279, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst281, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst282, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst283, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst279, kStruct)))))
	StoreVarInst(Address(fConst284, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst285, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst286, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst287, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst288, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst289, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst290, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst262, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst291, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst292, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst293, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst272, kStruct)))))
	StoreVarInst(Address(fConst294, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst295, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst296, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst269, kStruct)))))
	StoreVarInst(Address(fConst297, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst298, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst299, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst266, kStruct)))))
	StoreVarInst(Address(fConst300, kStruct), FunCallInst("tanf", BinopInst("/", Float(1246.7418f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst301, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst300, kStruct))))
	StoreVarInst(Address(fConst302, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst303, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst300, kStruct))))
	StoreVarInst(Address(fConst304, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst305, kStruct), BinopInst("+", LoadVarInst(Address(fConst304, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst306, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst307, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst308, kStruct), BinopInst("+", LoadVarInst(Address(fConst307, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst309, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst300, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst310, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst311, kStruct), BinopInst("+", LoadVarInst(Address(fConst310, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst312, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst313, kStruct), BinopInst("+", LoadVarInst(Address(fConst291, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst314, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst315, kStruct), BinopInst("+", LoadVarInst(Address(fConst291, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst316, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst317, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst318, kStruct), BinopInst("+", LoadVarInst(Address(fConst317, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst319, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst320, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst321, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst317, kStruct)))))
	StoreVarInst(Address(fConst322, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst323, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst324, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst325, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst326, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst327, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst328, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst300, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst329, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst330, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst331, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst310, kStruct)))))
	StoreVarInst(Address(fConst332, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst333, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst334, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst307, kStruct)))))
	StoreVarInst(Address(fConst335, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst336, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst337, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst304, kStruct)))))
	StoreVarInst(Address(fConst338, kStruct), FunCallInst("tanf", BinopInst("/", Float(785.3982f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst339, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst338, kStruct))))
	StoreVarInst(Address(fConst340, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst341, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst338, kStruct))))
	StoreVarInst(Address(fConst342, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst343, kStruct), BinopInst("+", LoadVarInst(Address(fConst342, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst344, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst345, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst346, kStruct), BinopInst("+", LoadVarInst(Address(fConst345, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst347, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst338, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst348, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst349, kStruct), BinopInst("+", LoadVarInst(Address(fConst348, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst350, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst351, kStruct), BinopInst("+", LoadVarInst(Address(fConst329, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst352, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst353, kStruct), BinopInst("+", LoadVarInst(Address(fConst329, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst354, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst355, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst356, kStruct), BinopInst("+", LoadVarInst(Address(fConst355, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst357, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst358, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst359, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst355, kStruct)))))
	StoreVarInst(Address(fConst360, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst361, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst362, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst363, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst364, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst365, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst366, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst338, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst367, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst368, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst369, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst348, kStruct)))))
	StoreVarInst(Address(fConst370, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst371, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst372, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst345, kStruct)))))
	StoreVarInst(Address(fConst373, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst374, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst375, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst342, kStruct)))))
	StoreVarInst(Address(fConst376, kStruct), FunCallInst("tanf", BinopInst("/", Float(494.76984f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst377, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst378, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst379, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst380, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst381, kStruct), BinopInst("+", LoadVarInst(Address(fConst380, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst382, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst383, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst384, kStruct), BinopInst("+", LoadVarInst(Address(fConst383, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst385, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst376, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst386, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst387, kStruct), BinopInst("+", LoadVarInst(Address(fConst386, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst388, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst389, kStruct), BinopInst("+", LoadVarInst(Address(fConst367, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst390, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst391, kStruct), BinopInst("+", LoadVarInst(Address(fConst367, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst392, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst393, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst394, kStruct), BinopInst("+", LoadVarInst(Address(fConst393, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst395, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst396, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst397, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst393, kStruct)))))
	StoreVarInst(Address(fConst398, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst399, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst400, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst401, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst402, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst403, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst404, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst376, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst405, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst406, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst407, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst386, kStruct)))))
	StoreVarInst(Address(fConst408, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst409, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst410, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst383, kStruct)))))
	StoreVarInst(Address(fConst411, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst412, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst413, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst380, kStruct)))))
	StoreVarInst(Address(fConst414, kStruct), FunCallInst("tanf", BinopInst("/", Float(311.68546f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst415, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst414, kStruct))))
	StoreVarInst(Address(fConst416, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst417, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst414, kStruct))))
	StoreVarInst(Address(fConst418, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst419, kStruct), BinopInst("+", LoadVarInst(Address(fConst418, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst420, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst421, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst422, kStruct), BinopInst("+", LoadVarInst(Address(fConst421, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst423, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst414, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst424, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst425, kStruct), BinopInst("+", LoadVarInst(Address(fConst424, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst426, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst427, kStruct), BinopInst("+", LoadVarInst(Address(fConst405, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst428, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst429, kStruct), BinopInst("+", LoadVarInst(Address(fConst405, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst430, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst431, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst432, kStruct), BinopInst("+", LoadVarInst(Address(fConst431, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst433, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst434, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst435, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst431, kStruct)))))
	StoreVarInst(Address(fConst436, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst437, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst438, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst439, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst440, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst441, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst442, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst414, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst443, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst444, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst445, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst424, kStruct)))))
	StoreVarInst(Address(fConst446, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst447, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst448, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst421, kStruct)))))
	StoreVarInst(Address(fConst449, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst450, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst451, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst418, kStruct)))))
	StoreVarInst(Address(fConst452, kStruct), FunCallInst("tanf", BinopInst("/", Float(196.34955f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst453, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst452, kStruct))))
	StoreVarInst(Address(fConst454, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst455, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst452, kStruct))))
	StoreVarInst(Address(fConst456, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst457, kStruct), BinopInst("+", LoadVarInst(Address(fConst456, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst458, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst459, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst460, kStruct), BinopInst("+", LoadVarInst(Address(fConst459, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst461, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst452, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst462, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst463, kStruct), BinopInst("+", LoadVarInst(Address(fConst462, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst464, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst465, kStruct), BinopInst("+", LoadVarInst(Address(fConst443, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst466, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst467, kStruct), BinopInst("+", LoadVarInst(Address(fConst443, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst468, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst469, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst470, kStruct), BinopInst("+", LoadVarInst(Address(fConst469, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst471, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst472, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst473, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst469, kStruct)))))
	StoreVarInst(Address(fConst474, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst475, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst476, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst477, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst478, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst479, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst480, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst452, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst481, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst482, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst483, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst462, kStruct)))))
	StoreVarInst(Address(fConst484, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst485, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst486, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst459, kStruct)))))
	StoreVarInst(Address(fConst487, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst488, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst489, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst456, kStruct)))))
	StoreVarInst(Address(fConst490, kStruct), FunCallInst("tanf", BinopInst("/", Float(123.69246f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst491, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst490, kStruct))))
	StoreVarInst(Address(fConst492, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst493, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst490, kStruct))))
	StoreVarInst(Address(fConst494, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst495, kStruct), BinopInst("+", LoadVarInst(Address(fConst494, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst496, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst497, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst498, kStruct), BinopInst("+", LoadVarInst(Address(fConst497, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst499, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst490, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst500, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst501, kStruct), BinopInst("+", LoadVarInst(Address(fConst500, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst502, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst503, kStruct), BinopInst("+", LoadVarInst(Address(fConst481, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst504, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst505, kStruct), BinopInst("+", LoadVarInst(Address(fConst481, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst506, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst507, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst508, kStruct), BinopInst("+", LoadVarInst(Address(fConst507, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst509, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst510, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst511, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst507, kStruct)))))
	StoreVarInst(Address(fConst512, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst513, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst514, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst515, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst516, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst517, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst518, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst490, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst519, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst520, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst521, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst500, kStruct)))))
	StoreVarInst(Address(fConst522, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst523, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst524, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst497, kStruct)))))
	StoreVarInst(Address(fConst525, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst526, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst527, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst494, kStruct)))))
	StoreVarInst(Address(fConst528, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst529, kStruct), BinopInst("+", LoadVarInst(Address(fConst519, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst530, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst531, kStruct), BinopInst("+", LoadVarInst(Address(fConst519, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst532, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst533, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst534, kStruct), BinopInst("+", LoadVarInst(Address(fConst533, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst535, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst536, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst537, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst533, kStruct)))))
	StoreVarInst(Address(fConst538, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst539, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst540, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst541, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst542, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst543, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst519, kStruct)))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(25.0f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(-2e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.1f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(-0.1f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.1f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.9f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(4))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(4096))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(4096))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(4096))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(4096))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(4096))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4096))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec24, kStruct)[LoadVarInst(Address(l48, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(3))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(3))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(3))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(3))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(3))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(3))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(3))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(3))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(3))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(3))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(2))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(3))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec46, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(3))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(3))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(3))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(3))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(3))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(2))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(3))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec53, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(3))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec52, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(3))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec51, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(3))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec50, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(3))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec49, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(3))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec48, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec47, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(3))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec60, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(3))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec59, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(3))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec58, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(3))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec57, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(3))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec56, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(3))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec55, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(2))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec54, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(3))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec67, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(3))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec66, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(3))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec65, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(3))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec64, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(3))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec63, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(3))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec62, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l99, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l99, kLoop)), Int32(2))
		StoreVarInst(Address(l99, kLoop), BinopInst("+", LoadVarInst(Address(l99, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec61, kStruct)[LoadVarInst(Address(l99, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l100, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l100, kLoop)), Int32(3))
		StoreVarInst(Address(l100, kLoop), BinopInst("+", LoadVarInst(Address(l100, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec74, kStruct)[LoadVarInst(Address(l100, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l101, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l101, kLoop)), Int32(3))
		StoreVarInst(Address(l101, kLoop), BinopInst("+", LoadVarInst(Address(l101, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec73, kStruct)[LoadVarInst(Address(l101, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l102, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l102, kLoop)), Int32(3))
		StoreVarInst(Address(l102, kLoop), BinopInst("+", LoadVarInst(Address(l102, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec72, kStruct)[LoadVarInst(Address(l102, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l103, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l103, kLoop)), Int32(3))
		StoreVarInst(Address(l103, kLoop), BinopInst("+", LoadVarInst(Address(l103, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec71, kStruct)[LoadVarInst(Address(l103, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l104, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l104, kLoop)), Int32(3))
		StoreVarInst(Address(l104, kLoop), BinopInst("+", LoadVarInst(Address(l104, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec70, kStruct)[LoadVarInst(Address(l104, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l105, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l105, kLoop)), Int32(3))
		StoreVarInst(Address(l105, kLoop), BinopInst("+", LoadVarInst(Address(l105, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec69, kStruct)[LoadVarInst(Address(l105, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l106, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l106, kLoop)), Int32(2))
		StoreVarInst(Address(l106, kLoop), BinopInst("+", LoadVarInst(Address(l106, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec68, kStruct)[LoadVarInst(Address(l106, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l107, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l107, kLoop)), Int32(3))
		StoreVarInst(Address(l107, kLoop), BinopInst("+", LoadVarInst(Address(l107, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec81, kStruct)[LoadVarInst(Address(l107, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l108, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l108, kLoop)), Int32(3))
		StoreVarInst(Address(l108, kLoop), BinopInst("+", LoadVarInst(Address(l108, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec80, kStruct)[LoadVarInst(Address(l108, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l109, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l109, kLoop)), Int32(3))
		StoreVarInst(Address(l109, kLoop), BinopInst("+", LoadVarInst(Address(l109, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec79, kStruct)[LoadVarInst(Address(l109, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l110, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l110, kLoop)), Int32(3))
		StoreVarInst(Address(l110, kLoop), BinopInst("+", LoadVarInst(Address(l110, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec78, kStruct)[LoadVarInst(Address(l110, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l111, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l111, kLoop)), Int32(3))
		StoreVarInst(Address(l111, kLoop), BinopInst("+", LoadVarInst(Address(l111, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec77, kStruct)[LoadVarInst(Address(l111, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l112, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l112, kLoop)), Int32(3))
		StoreVarInst(Address(l112, kLoop), BinopInst("+", LoadVarInst(Address(l112, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec76, kStruct)[LoadVarInst(Address(l112, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l113, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l113, kLoop)), Int32(2))
		StoreVarInst(Address(l113, kLoop), BinopInst("+", LoadVarInst(Address(l113, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec75, kStruct)[LoadVarInst(Address(l113, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l114, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l114, kLoop)), Int32(3))
		StoreVarInst(Address(l114, kLoop), BinopInst("+", LoadVarInst(Address(l114, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec88, kStruct)[LoadVarInst(Address(l114, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l115, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l115, kLoop)), Int32(3))
		StoreVarInst(Address(l115, kLoop), BinopInst("+", LoadVarInst(Address(l115, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec87, kStruct)[LoadVarInst(Address(l115, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l116, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l116, kLoop)), Int32(3))
		StoreVarInst(Address(l116, kLoop), BinopInst("+", LoadVarInst(Address(l116, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec86, kStruct)[LoadVarInst(Address(l116, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l117, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l117, kLoop)), Int32(3))
		StoreVarInst(Address(l117, kLoop), BinopInst("+", LoadVarInst(Address(l117, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec85, kStruct)[LoadVarInst(Address(l117, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l118, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l118, kLoop)), Int32(3))
		StoreVarInst(Address(l118, kLoop), BinopInst("+", LoadVarInst(Address(l118, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec84, kStruct)[LoadVarInst(Address(l118, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l119, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l119, kLoop)), Int32(3))
		StoreVarInst(Address(l119, kLoop), BinopInst("+", LoadVarInst(Address(l119, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec83, kStruct)[LoadVarInst(Address(l119, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l120, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l120, kLoop)), Int32(2))
		StoreVarInst(Address(l120, kLoop), BinopInst("+", LoadVarInst(Address(l120, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec82, kStruct)[LoadVarInst(Address(l120, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l121, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l121, kLoop)), Int32(3))
		StoreVarInst(Address(l121, kLoop), BinopInst("+", LoadVarInst(Address(l121, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec95, kStruct)[LoadVarInst(Address(l121, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l122, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l122, kLoop)), Int32(3))
		StoreVarInst(Address(l122, kLoop), BinopInst("+", LoadVarInst(Address(l122, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec94, kStruct)[LoadVarInst(Address(l122, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l123, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l123, kLoop)), Int32(3))
		StoreVarInst(Address(l123, kLoop), BinopInst("+", LoadVarInst(Address(l123, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec93, kStruct)[LoadVarInst(Address(l123, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l124, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l124, kLoop)), Int32(3))
		StoreVarInst(Address(l124, kLoop), BinopInst("+", LoadVarInst(Address(l124, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec92, kStruct)[LoadVarInst(Address(l124, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l125, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l125, kLoop)), Int32(3))
		StoreVarInst(Address(l125, kLoop), BinopInst("+", LoadVarInst(Address(l125, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec91, kStruct)[LoadVarInst(Address(l125, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l126, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l126, kLoop)), Int32(3))
		StoreVarInst(Address(l126, kLoop), BinopInst("+", LoadVarInst(Address(l126, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec90, kStruct)[LoadVarInst(Address(l126, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l127, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l127, kLoop)), Int32(2))
		StoreVarInst(Address(l127, kLoop), BinopInst("+", LoadVarInst(Address(l127, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec89, kStruct)[LoadVarInst(Address(l127, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l128, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l128, kLoop)), Int32(3))
		StoreVarInst(Address(l128, kLoop), BinopInst("+", LoadVarInst(Address(l128, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec102, kStruct)[LoadVarInst(Address(l128, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l129, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l129, kLoop)), Int32(3))
		StoreVarInst(Address(l129, kLoop), BinopInst("+", LoadVarInst(Address(l129, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec101, kStruct)[LoadVarInst(Address(l129, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l130, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l130, kLoop)), Int32(3))
		StoreVarInst(Address(l130, kLoop), BinopInst("+", LoadVarInst(Address(l130, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec100, kStruct)[LoadVarInst(Address(l130, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l131, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l131, kLoop)), Int32(3))
		StoreVarInst(Address(l131, kLoop), BinopInst("+", LoadVarInst(Address(l131, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec99, kStruct)[LoadVarInst(Address(l131, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l132, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l132, kLoop)), Int32(3))
		StoreVarInst(Address(l132, kLoop), BinopInst("+", LoadVarInst(Address(l132, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec98, kStruct)[LoadVarInst(Address(l132, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l133, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l133, kLoop)), Int32(3))
		StoreVarInst(Address(l133, kLoop), BinopInst("+", LoadVarInst(Address(l133, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec97, kStruct)[LoadVarInst(Address(l133, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l134, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l134, kLoop)), Int32(2))
		StoreVarInst(Address(l134, kLoop), BinopInst("+", LoadVarInst(Address(l134, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec96, kStruct)[LoadVarInst(Address(l134, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l135, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l135, kLoop)), Int32(3))
		StoreVarInst(Address(l135, kLoop), BinopInst("+", LoadVarInst(Address(l135, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec109, kStruct)[LoadVarInst(Address(l135, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l136, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l136, kLoop)), Int32(3))
		StoreVarInst(Address(l136, kLoop), BinopInst("+", LoadVarInst(Address(l136, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec108, kStruct)[LoadVarInst(Address(l136, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l137, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l137, kLoop)), Int32(3))
		StoreVarInst(Address(l137, kLoop), BinopInst("+", LoadVarInst(Address(l137, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec107, kStruct)[LoadVarInst(Address(l137, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l138, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l138, kLoop)), Int32(3))
		StoreVarInst(Address(l138, kLoop), BinopInst("+", LoadVarInst(Address(l138, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec106, kStruct)[LoadVarInst(Address(l138, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l139, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l139, kLoop)), Int32(3))
		StoreVarInst(Address(l139, kLoop), BinopInst("+", LoadVarInst(Address(l139, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec105, kStruct)[LoadVarInst(Address(l139, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l140, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l140, kLoop)), Int32(3))
		StoreVarInst(Address(l140, kLoop), BinopInst("+", LoadVarInst(Address(l140, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec104, kStruct)[LoadVarInst(Address(l140, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l141, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l141, kLoop)), Int32(2))
		StoreVarInst(Address(l141, kLoop), BinopInst("+", LoadVarInst(Address(l141, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec103, kStruct)[LoadVarInst(Address(l141, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l142, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l142, kLoop)), Int32(3))
		StoreVarInst(Address(l142, kLoop), BinopInst("+", LoadVarInst(Address(l142, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec116, kStruct)[LoadVarInst(Address(l142, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l143, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l143, kLoop)), Int32(3))
		StoreVarInst(Address(l143, kLoop), BinopInst("+", LoadVarInst(Address(l143, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec115, kStruct)[LoadVarInst(Address(l143, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l144, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l144, kLoop)), Int32(3))
		StoreVarInst(Address(l144, kLoop), BinopInst("+", LoadVarInst(Address(l144, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec114, kStruct)[LoadVarInst(Address(l144, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l145, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l145, kLoop)), Int32(3))
		StoreVarInst(Address(l145, kLoop), BinopInst("+", LoadVarInst(Address(l145, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec113, kStruct)[LoadVarInst(Address(l145, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l146, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l146, kLoop)), Int32(3))
		StoreVarInst(Address(l146, kLoop), BinopInst("+", LoadVarInst(Address(l146, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec112, kStruct)[LoadVarInst(Address(l146, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l147, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l147, kLoop)), Int32(3))
		StoreVarInst(Address(l147, kLoop), BinopInst("+", LoadVarInst(Address(l147, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec111, kStruct)[LoadVarInst(Address(l147, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l148, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l148, kLoop)), Int32(2))
		StoreVarInst(Address(l148, kLoop), BinopInst("+", LoadVarInst(Address(l148, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec110, kStruct)[LoadVarInst(Address(l148, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l149, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l149, kLoop)), Int32(3))
		StoreVarInst(Address(l149, kLoop), BinopInst("+", LoadVarInst(Address(l149, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec123, kStruct)[LoadVarInst(Address(l149, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l150, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l150, kLoop)), Int32(3))
		StoreVarInst(Address(l150, kLoop), BinopInst("+", LoadVarInst(Address(l150, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec122, kStruct)[LoadVarInst(Address(l150, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l151, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l151, kLoop)), Int32(3))
		StoreVarInst(Address(l151, kLoop), BinopInst("+", LoadVarInst(Address(l151, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec121, kStruct)[LoadVarInst(Address(l151, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l152, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l152, kLoop)), Int32(3))
		StoreVarInst(Address(l152, kLoop), BinopInst("+", LoadVarInst(Address(l152, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec120, kStruct)[LoadVarInst(Address(l152, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l153, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l153, kLoop)), Int32(3))
		StoreVarInst(Address(l153, kLoop), BinopInst("+", LoadVarInst(Address(l153, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec119, kStruct)[LoadVarInst(Address(l153, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l154, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l154, kLoop)), Int32(3))
		StoreVarInst(Address(l154, kLoop), BinopInst("+", LoadVarInst(Address(l154, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec118, kStruct)[LoadVarInst(Address(l154, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l155, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l155, kLoop)), Int32(2))
		StoreVarInst(Address(l155, kLoop), BinopInst("+", LoadVarInst(Address(l155, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec117, kStruct)[LoadVarInst(Address(l155, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l156, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l156, kLoop)), Int32(3))
		StoreVarInst(Address(l156, kLoop), BinopInst("+", LoadVarInst(Address(l156, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec127, kStruct)[LoadVarInst(Address(l156, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l157, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l157, kLoop)), Int32(3))
		StoreVarInst(Address(l157, kLoop), BinopInst("+", LoadVarInst(Address(l157, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec126, kStruct)[LoadVarInst(Address(l157, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l158, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l158, kLoop)), Int32(3))
		StoreVarInst(Address(l158, kLoop), BinopInst("+", LoadVarInst(Address(l158, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec125, kStruct)[LoadVarInst(Address(l158, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l159, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l159, kLoop)), Int32(2))
		StoreVarInst(Address(l159, kLoop), BinopInst("+", LoadVarInst(Address(l159, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec124, kStruct)[LoadVarInst(Address(l159, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 56 Store = 0 Binop = 45 [ { Int(>=) = 3 } { Real(*) = 24 } { Real(+) = 8 } { Real(-) = 6 } { Real(/) = 2 } { Real(>) = 2 } ] Mathop = 12 [ { expf = 2 } { max_f = 1 } { min_f = 2 } { mydsp_faustpower2_f = 2 } { mydsp_faustpower4_f = 1 } { powf = 4 } ] Numbers = 48 Declare = 45 Cast = 26 Select = 2 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, Select2Inst(BinopInst(">", BinopInst("*", Float(0.001f), LoadVarInst(Address(fSlow1, kStack))), Float(0.0f)) FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow1, kStack))))) Float(0.0f)))
	DeclareVarInst("int", iSlow3, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	DeclareVarInst("int", iSlow5, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(0.44f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider3, kStruct))), Float(-49.0f))))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(0.33333334f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))
	DeclareVarInst("int", iSlow10, kStack, CastInst("int", BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry0, kStruct))), Float(-1.0f))))
	DeclareVarInst("int", iSlow11, kStack, BinopInst(">=", LoadVarInst(Address(iSlow10, kStack)), Int32(2)))
	DeclareVarInst("int", iSlow12, kStack, BinopInst(">=", LoadVarInst(Address(iSlow10, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, Select2Inst(BinopInst(">", LoadVarInst(Address(fSlow13, kStack)), Float(0.0f)) FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow13, kStack))))) Float(0.0f)))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", BinopInst("*", Float(4.4e+02f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider5, kStruct))), Float(-49.0f))))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow14, kStack)))))
	DeclareVarInst("int", iSlow16, kStack, BinopInst(">=", LoadVarInst(Address(iSlow10, kStack)), Int32(3)))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("+", BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))), Float(1.0f)))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.083333336f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow22, kStack)))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(4.0f), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fSlow27, kStack))), Float(0.999999f)))))
	DeclareVarInst("int", iSlow29, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct)))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("min_f", Float(1.4127994f), BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow30, kStack))))
	DeclareVarInst("float", fSlow32, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow30, kStack))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("+", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fSlow32, kStack))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("+", LoadVarInst(Address(fSlow31, kStack)), Float(2.0f)))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.4127994f), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("*", Float(1.998f), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("+", LoadVarInst(Address(fSlow37, kStack)), Float(2.0f)))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 1965 Store = 421 Binop = 1475 [ { Int(&) = 24 } { Int(*) = 1 } { Int(+) = 9 } { Int(-) = 22 } { Int(<) = 1 } { Int(>) = 2 } { Real(*) = 776 } { Real(+) = 392 } { Real(-) = 186 } { Real(/) = 62 } ] Mathop = 107 [ { fabsf = 21 } { floorf = 6 } { log10f = 15 } { max_f = 25 } { min_f = 11 } { mydsp_faustpower2_f = 12 } { mydsp_faustpower3_f = 6 } { mydsp_faustpower4_f = 1 } { sqrtf = 8 } { tanf = 2 } ] Numbers = 1366 Declare = 152 Cast = 34 Select = 13 Loop = 3

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp0, kStack))))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow14, kStack))), LoadVarInst(Address(fSlow15, kStack))))
		DeclareVarInst("float", fTemp2, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp3, kStack)))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec12, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), Float(-1.0f)))
		DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp7, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp5, kStack))))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
		DeclareVarInst("float", fTemp8, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(2)])))
		DeclareVarInst("float", fTemp9, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp5, kStack))))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp4, kStack)))))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp2, kStack))))
		StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
		DeclareVarInst("float", fTemp11, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(3)])))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("*", LoadVarInst(Address(fTemp7, kStack)), BinopInst("+", LoadVarInst(Address(fTemp7, kStack)), Float(-2.0f))))
		StoreVarInst(Address(fVec4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp2, kStack))))
		StoreVarInst(Address(fVec5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp13, kStack)))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp13, kStack)), LoadVarInst(Address(fVec5, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp2, kStack))))
		StoreVarInst(Address(fVec6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp14, kStack)))
		DeclareVarInst("float", fTemp15, kStack, BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp16, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp15, kStack)))))
		DeclareVarInst("float", fTemp17, kStack, BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp16, kStack)))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp17, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp17, kStack)))))
		DeclareVarInst("float", fTemp18, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp19, kStack, BinopInst("+", LoadVarInst(Address(fTemp18, kStack)), Float(-1.0f)))
		DeclareVarInst("float", fTemp20, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp19, kStack))))
		StoreVarInst(Address(fVec7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp20, kStack)))
		DeclareVarInst("float", fTemp21, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp19, kStack))))
		StoreVarInst(Address(fVec8, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp21, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp18, kStack)))))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp21, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fVec8, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp16, kStack))))
		StoreVarInst(Address(fVec9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp22, kStack)))
		DeclareVarInst("float", fTemp23, kStack, BinopInst("*", LoadVarInst(Address(fTemp20, kStack)), BinopInst("+", LoadVarInst(Address(fTemp20, kStack)), Float(-2.0f))))
		StoreVarInst(Address(fVec10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp23, kStack)))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp23, kStack)), LoadVarInst(Address(fVec10, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp16, kStack))))
		StoreVarInst(Address(fVec11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fVec11, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp16, kStack))))
		StoreVarInst(Address(fVec12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
		DeclareVarInst("float", fTemp26, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp27, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp26, kStack)))))
		DeclareVarInst("float", fTemp28, kStack, BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp27, kStack)))))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp28, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp28, kStack)))))
		DeclareVarInst("float", fTemp29, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp30, kStack, BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), Float(-1.0f)))
		DeclareVarInst("float", fTemp31, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp30, kStack))))
		StoreVarInst(Address(fVec13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp31, kStack)))
		DeclareVarInst("float", fTemp32, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp30, kStack))))
		StoreVarInst(Address(fVec14, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp29, kStack)))))
		DeclareVarInst("float", fTemp33, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fVec14, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp27, kStack))))
		StoreVarInst(Address(fVec15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp33, kStack)))
		DeclareVarInst("float", fTemp34, kStack, BinopInst("*", LoadVarInst(Address(fTemp31, kStack)), BinopInst("+", LoadVarInst(Address(fTemp31, kStack)), Float(-2.0f))))
		StoreVarInst(Address(fVec16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp34, kStack)))
		DeclareVarInst("float", fTemp35, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fVec16, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp27, kStack))))
		StoreVarInst(Address(fVec17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp35, kStack)))
		DeclareVarInst("float", fTemp36, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp35, kStack)), LoadVarInst(Address(fVec17, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp27, kStack))))
		StoreVarInst(Address(fVec18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp36, kStack)))
		DeclareVarInst("float", fTemp37, kStack, FunCallInst("max_f", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), Float(23.44895f)))
		DeclareVarInst("float", fTemp38, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp37, kStack)))))
		DeclareVarInst("float", fTemp39, kStack, BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp38, kStack)))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp39, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp39, kStack)))))
		DeclareVarInst("float", fTemp40, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp41, kStack, BinopInst("+", LoadVarInst(Address(fTemp40, kStack)), Float(-1.0f)))
		DeclareVarInst("float", fTemp42, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp41, kStack))))
		StoreVarInst(Address(fVec19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp42, kStack)))
		DeclareVarInst("float", fTemp43, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp38, kStack))))
		StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp43, kStack)))
		DeclareVarInst("float", fTemp44, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fTemp37, kStack))))))
		DeclareVarInst("int", iTemp45, kStack, CastInst("int", LoadVarInst(Address(fTemp44, kStack))))
		DeclareVarInst("float", fTemp46, kStack, CastInst("float", LoadVarInst(Address(iTemp45, kStack))))
		DeclareVarInst("float", fTemp47, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp43, kStack)), BinopInst("*", LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp45, kStack))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp44, kStack)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp44, kStack)), LoadVarInst(Address(fTemp46, kStack))), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", LoadVarInst(Address(iTemp45, kStack)), Int32(1))), Int32(4095))]))))
		DeclareVarInst("float", fTemp48, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp15, kStack)), Float(23.44895f)))
		DeclareVarInst("float", fTemp49, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp48, kStack)))))
		DeclareVarInst("float", fTemp50, kStack, BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp49, kStack)))))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp50, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp50, kStack)))))
		DeclareVarInst("float", fTemp51, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp52, kStack, BinopInst("+", LoadVarInst(Address(fTemp51, kStack)), Float(-1.0f)))
		DeclareVarInst("float", fTemp53, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp52, kStack))))
		StoreVarInst(Address(fVec21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp53, kStack)))
		DeclareVarInst("float", fTemp54, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
		StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp54, kStack)))
		DeclareVarInst("float", fTemp55, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fTemp48, kStack))))))
		DeclareVarInst("int", iTemp56, kStack, CastInst("int", LoadVarInst(Address(fTemp55, kStack))))
		DeclareVarInst("float", fTemp57, kStack, CastInst("float", LoadVarInst(Address(iTemp56, kStack))))
		DeclareVarInst("float", fTemp58, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp56, kStack))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp57, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp55, kStack)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp55, kStack)), LoadVarInst(Address(fTemp57, kStack))), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", LoadVarInst(Address(iTemp56, kStack)), Int32(1))), Int32(4095))]))))
		DeclareVarInst("float", fTemp59, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp26, kStack)), Float(23.44895f)))
		DeclareVarInst("float", fTemp60, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp59, kStack)))))
		DeclareVarInst("float", fTemp61, kStack, BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp60, kStack)))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp61, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp61, kStack)))))
		DeclareVarInst("float", fTemp62, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp63, kStack, BinopInst("+", LoadVarInst(Address(fTemp62, kStack)), Float(-1.0f)))
		DeclareVarInst("float", fTemp64, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp63, kStack))))
		StoreVarInst(Address(fVec23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp64, kStack)))
		DeclareVarInst("float", fTemp65, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp64, kStack)), LoadVarInst(Address(fVec23, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
		StoreVarInst(Address(fVec24, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp65, kStack)))
		DeclareVarInst("float", fTemp66, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fTemp59, kStack))))))
		DeclareVarInst("int", iTemp67, kStack, CastInst("int", LoadVarInst(Address(fTemp66, kStack))))
		DeclareVarInst("float", fTemp68, kStack, CastInst("float", LoadVarInst(Address(iTemp67, kStack))))
		DeclareVarInst("float", fTemp69, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp67, kStack))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp68, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp66, kStack)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp66, kStack)), LoadVarInst(Address(fTemp68, kStack))), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", LoadVarInst(Address(iTemp67, kStack)), Int32(1))), Int32(4095))]))))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fTemp47, kStack))), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fTemp58, kStack))), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fTemp69, kStack))), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp70, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp41, kStack))))
		StoreVarInst(Address(fVec25, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp70, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp40, kStack)))))
		DeclareVarInst("float", fTemp71, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp70, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp40, kStack)), LoadVarInst(Address(fVec25, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp38, kStack))))
		StoreVarInst(Address(fVec26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp71, kStack)))
		DeclareVarInst("float", fTemp72, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp71, kStack)), LoadVarInst(Address(fVec26, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp38, kStack))))
		StoreVarInst(Address(fVec27, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp72, kStack)))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", Float(0.99f), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp73, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp37, kStack)))))))
		DeclareVarInst("int", iTemp74, kStack, CastInst("int", LoadVarInst(Address(fTemp73, kStack))))
		DeclareVarInst("float", fTemp75, kStack, CastInst("float", LoadVarInst(Address(iTemp74, kStack))))
		DeclareVarInst("float", fTemp76, kStack, BinopInst("+", LoadVarInst(Address(fTemp75, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp73, kStack)))))
		DeclareVarInst("float", fTemp77, kStack, BinopInst("-", LoadVarInst(Address(fTemp73, kStack)), LoadVarInst(Address(fTemp75, kStack))))
		DeclareVarInst("int", iTemp78, kStack, BinopInst("+", LoadVarInst(Address(iTemp74, kStack)), Int32(1)))
		DeclareVarInst("float", fTemp79, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp52, kStack))))
		StoreVarInst(Address(fVec28, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp79, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp51, kStack)))))
		DeclareVarInst("float", fTemp80, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp79, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp51, kStack)), LoadVarInst(Address(fVec28, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp49, kStack))))
		StoreVarInst(Address(fVec29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp80, kStack)))
		DeclareVarInst("float", fTemp81, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp80, kStack)), LoadVarInst(Address(fVec29, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
		StoreVarInst(Address(fVec30, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp81, kStack)))
		DeclareVarInst("float", fTemp82, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp48, kStack)))))))
		DeclareVarInst("int", iTemp83, kStack, CastInst("int", LoadVarInst(Address(fTemp82, kStack))))
		DeclareVarInst("float", fTemp84, kStack, CastInst("float", LoadVarInst(Address(iTemp83, kStack))))
		DeclareVarInst("float", fTemp85, kStack, BinopInst("+", LoadVarInst(Address(fTemp84, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp82, kStack)))))
		DeclareVarInst("float", fTemp86, kStack, BinopInst("-", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp84, kStack))))
		DeclareVarInst("int", iTemp87, kStack, BinopInst("+", LoadVarInst(Address(iTemp83, kStack)), Int32(1)))
		DeclareVarInst("float", fTemp88, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp63, kStack))))
		StoreVarInst(Address(fVec31, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp88, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp62, kStack)))))
		DeclareVarInst("float", fTemp89, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp88, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp62, kStack)), LoadVarInst(Address(fVec31, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp60, kStack))))
		StoreVarInst(Address(fVec32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp89, kStack)))
		DeclareVarInst("float", fTemp90, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp89, kStack)), LoadVarInst(Address(fVec32, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
		StoreVarInst(Address(fVec33, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp90, kStack)))
		DeclareVarInst("float", fTemp91, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp59, kStack)))))))
		DeclareVarInst("int", iTemp92, kStack, CastInst("int", LoadVarInst(Address(fTemp91, kStack))))
		DeclareVarInst("float", fTemp93, kStack, CastInst("float", LoadVarInst(Address(iTemp92, kStack))))
		DeclareVarInst("float", fTemp94, kStack, BinopInst("+", LoadVarInst(Address(fTemp93, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp91, kStack)))))
		DeclareVarInst("float", fTemp95, kStack, BinopInst("-", LoadVarInst(Address(fTemp91, kStack)), LoadVarInst(Address(fTemp93, kStack))))
		DeclareVarInst("int", iTemp96, kStack, BinopInst("+", LoadVarInst(Address(iTemp92, kStack)), Int32(1)))
		StoreVarInst(Address(iRec24, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec24, kStruct)[Int32(1)])), Int32(12345)))
		StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fRec23, kStruct)[Int32(3)])), BinopInst("+", BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iRec24, kStruct)[Int32(0)]))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(Address(fRec23, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp97, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", LoadVarInst(Address(fRec11, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(Address(iSlow11, kStack)) Select2Inst(LoadVarInst(Address(iSlow16, kStack)) BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fVec6, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp2, kStack)))) BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp2, kStack))))) Select2Inst(LoadVarInst(Address(iSlow12, kStack)) BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp2, kStack)))) LoadVarInst(Address(fTemp5, kStack)))), Select2Inst(LoadVarInst(Address(iSlow11, kStack)) Select2Inst(LoadVarInst(Address(iSlow16, kStack)) BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fVec12, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp16, kStack)))) BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fVec9, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp16, kStack))))) Select2Inst(LoadVarInst(Address(iSlow12, kStack)) BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fVec7, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp16, kStack)))) LoadVarInst(Address(fTemp19, kStack))))), Select2Inst(LoadVarInst(Address(iSlow11, kStack)) Select2Inst(LoadVarInst(Address(iSlow16, kStack)) BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp27, kStack)))) BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp33, kStack)), LoadVarInst(Address(fVec15, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp27, kStack))))) Select2Inst(LoadVarInst(Address(iSlow12, kStack)) BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fVec13, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp27, kStack)))) LoadVarInst(Address(fTemp30, kStack)))))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp47, kStack)), LoadVarInst(Address(fTemp58, kStack))), LoadVarInst(Address(fTemp69, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)])))))), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp72, kStack)), BinopInst("*", LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp74, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp76, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp77, kStack)), LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp78, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp81, kStack)), BinopInst("*", LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp83, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp85, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp87, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp90, kStack)), BinopInst("*", LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp92, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp94, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp95, kStack)), LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp96, kStack))), Int32(4095))]))))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp43, kStack)), BinopInst("*", LoadVarInst(Address(fTemp76, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp74, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp77, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp78, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fTemp85, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp83, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp87, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fTemp94, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp92, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp95, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp96, kStack))), Int32(4095))])))))))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("-", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fRec23, kStruct)[Int32(0)])), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fRec23, kStruct)[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.095993534f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])), BinopInst("*", Float(0.004408786f), LoadVarInst(Address(fRec23, kStruct)[Int32(3)])))))))))
		DeclareVarInst("float", fTemp98, kStack, Select2Inst(LoadVarInst(Address(iSlow3, kStack)) Float(0.0f) LoadVarInst(Address(fTemp97, kStack))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp98, kStack))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp1, kStack)))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fTemp0, kStack)))))
		DeclareVarInst("float", fTemp99, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1e+04f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp100, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp99, kStack))))
		DeclareVarInst("float", fTemp101, kStack, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp99, kStack))))))
		DeclareVarInst("float", fTemp102, kStack, BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp100, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f))))
		StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp98, kStack)), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec26, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp100, kStack)), LoadVarInst(Address(fSlow34, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f)))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fTemp101, kStack)))))), LoadVarInst(Address(fTemp102, kStack)))))
		DeclareVarInst("float", fTemp103, kStack, BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fTemp100, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow31, kStack)))))
		StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("-", BinopInst("/", BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp102, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec25, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp100, kStack)), LoadVarInst(Address(fSlow35, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow31, kStack))))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec25, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("-", LoadVarInst(Address(fTemp101, kStack)), LoadVarInst(Address(fSlow31, kStack))))))), LoadVarInst(Address(fTemp103, kStack)))))
		DeclareVarInst("float", fTemp104, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), FunCallInst("max_f", LoadVarInst(Address(fRec10, kStruct)[Int32(0)]), Float(2e+01f)))))
		DeclareVarInst("float", fTemp105, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp104, kStack))))
		DeclareVarInst("float", fTemp106, kStack, BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp105, kStack))), LoadVarInst(Address(fTemp104, kStack))), Float(1.0f))))
		DeclareVarInst("float", fTemp107, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), BinopInst("-", Float(1.0f), BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp105, kStack))), LoadVarInst(Address(fTemp104, kStack))))), LoadVarInst(Address(fTemp106, kStack))))
		DeclareVarInst("float", fTemp108, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp107, kStack)))))
		DeclareVarInst("float", fTemp109, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp108, kStack)))))
		DeclareVarInst("float", fTemp110, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp109, kStack)))))
		DeclareVarInst("float", fTemp111, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp98, kStack)), LoadVarInst(Address(fTemp110, kStack))), BinopInst("*", LoadVarInst(Address(fTemp108, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp112, kStack, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp104, kStack))))))
		DeclareVarInst("float", fTemp113, kStack, BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp112, kStack))))
		DeclareVarInst("float", fTemp114, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp113, kStack)), BinopInst("*", LoadVarInst(Address(fTemp106, kStack)), BinopInst("+", LoadVarInst(Address(fTemp107, kStack)), Float(1.0f))))))))
		DeclareVarInst("float", fTemp115, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp114, kStack)))))
		DeclareVarInst("float", fTemp116, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp115, kStack)))))
		StoreVarInst(Address(fRec29, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp111, kStack)), LoadVarInst(Address(fTemp116, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114, kStack)), LoadVarInst(Address(fRec29, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec27, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111, kStack)), LoadVarInst(Address(fTemp114, kStack))), BinopInst("*", LoadVarInst(Address(fRec29, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp116, kStack)))))
		DeclareVarInst("float", fRec28, kStack, LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
		DeclareVarInst("float", fTemp117, kStack, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(Address(fTemp113, kStack)), LoadVarInst(Address(fTemp106, kStack)))))
		DeclareVarInst("float", fTemp118, kStack, FunCallInst("sqrtf", LoadVarInst(Address(fTemp109, kStack))))
		DeclareVarInst("float", fTemp119, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp98, kStack)), LoadVarInst(Address(fTemp108, kStack))), BinopInst("*", LoadVarInst(Address(fRec27, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp110, kStack)))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec27, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp117, kStack))), LoadVarInst(Address(fTemp118, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec28, kStack)), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp107, kStack))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fTemp114, kStack)), LoadVarInst(Address(fTemp117, kStack)))))), BinopInst("*", LoadVarInst(Address(fTemp118, kStack)), FunCallInst("sqrtf", LoadVarInst(Address(fTemp115, kStack)))))))
		DeclareVarInst("float", fTemp120, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp105, kStack))), LoadVarInst(Address(fTemp104, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow37, kStack)))))
		DeclareVarInst("float", fTemp121, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp105, kStack)), LoadVarInst(Address(fSlow40, kStack))), LoadVarInst(Address(fTemp104, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow37, kStack)))), LoadVarInst(Address(fTemp120, kStack))))
		DeclareVarInst("float", fTemp122, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp121, kStack)))))
		DeclareVarInst("float", fTemp123, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp122, kStack)))))
		DeclareVarInst("float", fTemp124, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp123, kStack)))))
		DeclareVarInst("float", fTemp125, kStack, BinopInst("-", BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp119, kStack)), LoadVarInst(Address(fTemp124, kStack))), LoadVarInst(Address(fTemp106, kStack))), BinopInst("*", LoadVarInst(Address(fTemp122, kStack)), LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp126, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), BinopInst("-", LoadVarInst(Address(fTemp112, kStack)), LoadVarInst(Address(fSlow37, kStack)))))
		DeclareVarInst("float", fTemp127, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp126, kStack)), BinopInst("*", LoadVarInst(Address(fTemp120, kStack)), BinopInst("+", LoadVarInst(Address(fTemp121, kStack)), Float(1.0f))))))))
		DeclareVarInst("float", fTemp128, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp127, kStack)))))
		DeclareVarInst("float", fTemp129, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp128, kStack)))))
		StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp125, kStack)), LoadVarInst(Address(fTemp129, kStack))), BinopInst("*", LoadVarInst(Address(fTemp127, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec30, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp125, kStack)), LoadVarInst(Address(fTemp127, kStack))), BinopInst("*", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp129, kStack)))))
		DeclareVarInst("float", fRec31, kStack, LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		DeclareVarInst("float", fTemp130, kStack, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(Address(fTemp126, kStack)), LoadVarInst(Address(fTemp120, kStack)))))
		DeclareVarInst("float", fTemp131, kStack, FunCallInst("sqrtf", LoadVarInst(Address(fTemp123, kStack))))
		DeclareVarInst("float", fTemp132, kStack, Select2Inst(LoadVarInst(Address(iSlow3, kStack)) LoadVarInst(Address(fTemp97, kStack)) BinopInst("*", LoadVarInst(Address(fRec4, kStruct)[Int32(0)]), Select2Inst(LoadVarInst(Address(iSlow5, kStack)) Select2Inst(LoadVarInst(Address(iSlow29, kStack)) BinopInst("/", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp119, kStack)), LoadVarInst(Address(fTemp122, kStack))), LoadVarInst(Address(fTemp106, kStack))), BinopInst("*", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp124, kStack)))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec30, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp130, kStack))), LoadVarInst(Address(fTemp131, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec31, kStack)), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp121, kStack))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fTemp127, kStack)), LoadVarInst(Address(fTemp130, kStack)))))), BinopInst("*", LoadVarInst(Address(fTemp131, kStack)), FunCallInst("sqrtf", LoadVarInst(Address(fTemp128, kStack)))))), LoadVarInst(Address(fTemp120, kStack))) BinopInst("/", BinopInst("+", LoadVarInst(Address(fRec25, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec25, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec25, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp103, kStack)))) LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp132, kStack)), BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst26, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst31, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack))), BinopInst("*", FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst33, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)]))))), LoadVarInst(Address(fSlow41, kStack)))))
		StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp132, kStack)), BinopInst("*", LoadVarInst(Address(fConst50, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst53, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst54, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst50, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst55, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst56, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst57, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst58, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst46, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst59, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst60, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp133, kStack, BinopInst("*", LoadVarInst(Address(fConst46, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst47, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst61, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst47, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp133, kStack)), BinopInst("*", LoadVarInst(Address(fConst43, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst62, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst64, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst43, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst65, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst66, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst67, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst68, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst36, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst69, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst70, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst36, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst71, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec46, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp133, kStack)), BinopInst("*", LoadVarInst(Address(fConst88, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst91, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst92, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst88, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst90, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst93, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst90, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst86, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst94, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst95, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec44, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst86, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst87, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst96, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst87, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst84, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst97, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst98, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp134, kStack, BinopInst("*", LoadVarInst(Address(fConst84, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst85, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst99, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst85, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec43, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp134, kStack)), BinopInst("*", LoadVarInst(Address(fConst81, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst100, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst102, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst81, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst83, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst103, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst83, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst78, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst104, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst105, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst78, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst80, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst106, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst80, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst74, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst107, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst108, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec40, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec40, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst74, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst77, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst109, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst77, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec53, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp134, kStack)), BinopInst("*", LoadVarInst(Address(fConst126, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst129, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst130, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec52, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst126, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst128, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst131, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst128, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst124, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst132, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst133, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec51, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst124, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst125, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst134, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst125, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst122, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst135, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst136, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp135, kStack, BinopInst("*", LoadVarInst(Address(fConst122, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst123, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst137, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst123, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec50, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp135, kStack)), BinopInst("*", LoadVarInst(Address(fConst119, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst138, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst140, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec49, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst119, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst141, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst116, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst142, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst143, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec48, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst116, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst118, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst144, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst118, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst112, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst145, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst146, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec47, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec47, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst112, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst115, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst147, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst115, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec60, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp135, kStack)), BinopInst("*", LoadVarInst(Address(fConst164, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst167, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst168, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec59, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst164, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst166, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst169, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst166, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst162, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst170, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst171, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec58, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst162, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst163, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst172, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst163, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst160, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst173, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst174, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp136, kStack, BinopInst("*", LoadVarInst(Address(fConst160, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst161, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst175, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst161, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec57, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp136, kStack)), BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst176, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst178, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec56, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst159, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst179, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst159, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst154, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst180, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst181, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec55, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst154, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst156, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst182, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst156, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst150, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst183, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst184, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec54, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec54, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst150, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst153, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst185, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst153, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec54, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec67, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp136, kStack)), BinopInst("*", LoadVarInst(Address(fConst202, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst205, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst206, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec66, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst202, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst204, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst207, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst204, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst200, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst208, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst209, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec65, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst200, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst201, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst210, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst201, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst198, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst211, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst212, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp137, kStack, BinopInst("*", LoadVarInst(Address(fConst198, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst199, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst213, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst199, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec64, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp137, kStack)), BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst214, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst216, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec63, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst197, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst217, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst197, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst192, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst218, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst219, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec62, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst192, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst194, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst220, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst194, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst221, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst222, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec61, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec61, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst191, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst223, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst191, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec74, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp137, kStack)), BinopInst("*", LoadVarInst(Address(fConst240, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst243, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst244, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec73, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst240, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst242, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst245, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst242, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst246, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst247, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec72, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst239, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst248, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst239, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst236, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst249, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst250, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp138, kStack, BinopInst("*", LoadVarInst(Address(fConst236, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst237, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst251, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst237, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec71, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp138, kStack)), BinopInst("*", LoadVarInst(Address(fConst233, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst252, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst254, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec70, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst233, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst235, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst255, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst235, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst230, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst256, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst257, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec69, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst230, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst232, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst258, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst232, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst226, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst259, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst260, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec68, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec68, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst226, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst229, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst261, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst229, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec68, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec81, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp138, kStack)), BinopInst("*", LoadVarInst(Address(fConst278, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst281, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst282, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec80, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst278, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst280, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst283, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst280, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst276, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst284, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst285, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec79, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst276, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst277, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst286, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst277, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst274, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst287, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst288, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp139, kStack, BinopInst("*", LoadVarInst(Address(fConst274, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst275, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst289, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst275, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec78, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp139, kStack)), BinopInst("*", LoadVarInst(Address(fConst271, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst290, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst292, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec77, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst271, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst273, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst293, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst273, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst268, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst294, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst295, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec76, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst268, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst296, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst264, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst297, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst298, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec75, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec75, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst264, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst267, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst299, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst267, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec75, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec88, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp139, kStack)), BinopInst("*", LoadVarInst(Address(fConst316, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst319, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst320, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec87, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst316, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst318, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst321, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst318, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst314, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst322, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst323, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec86, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst314, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst315, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst324, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst315, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst325, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst326, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp140, kStack, BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst313, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst327, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst313, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec85, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp140, kStack)), BinopInst("*", LoadVarInst(Address(fConst309, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst328, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst330, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec84, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst309, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst311, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst331, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst311, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst306, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst332, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst333, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec83, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst306, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst308, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst334, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst308, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst302, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst335, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst336, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec82, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec82, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst302, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst337, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec82, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec95, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp140, kStack)), BinopInst("*", LoadVarInst(Address(fConst354, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst357, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst358, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec94, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst354, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst356, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst359, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst356, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst352, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst360, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst361, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec93, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst352, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst353, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst362, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst353, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst350, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst363, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst364, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp141, kStack, BinopInst("*", LoadVarInst(Address(fConst350, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst351, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst365, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst351, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec92, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp141, kStack)), BinopInst("*", LoadVarInst(Address(fConst347, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst366, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst368, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec91, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst347, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst349, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst369, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst349, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst370, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst371, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec90, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst346, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst372, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst346, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst340, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst373, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst374, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec89, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec89, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst340, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst343, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst375, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst343, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec89, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec102, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp141, kStack)), BinopInst("*", LoadVarInst(Address(fConst392, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst395, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst396, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec101, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst392, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst397, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst390, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst398, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst399, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec100, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst390, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst391, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst400, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst391, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst388, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst401, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst402, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp142, kStack, BinopInst("*", LoadVarInst(Address(fConst388, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst389, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst403, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst389, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec99, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp142, kStack)), BinopInst("*", LoadVarInst(Address(fConst385, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst404, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst406, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec98, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst385, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst407, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst382, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst408, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst409, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec97, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst382, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst384, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst410, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst384, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst378, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst411, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst412, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec96, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec96, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst378, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst381, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst413, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst381, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph10, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec96, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec109, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp142, kStack)), BinopInst("*", LoadVarInst(Address(fConst430, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst433, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst434, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec108, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst430, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst432, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst435, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst432, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst428, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst436, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst437, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec107, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst428, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst438, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst426, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst439, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst440, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp143, kStack, BinopInst("*", LoadVarInst(Address(fConst426, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst427, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst441, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst427, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec106, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp143, kStack)), BinopInst("*", LoadVarInst(Address(fConst423, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst442, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst444, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec105, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst423, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst425, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst445, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst425, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst420, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst446, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst447, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec104, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst420, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst422, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst448, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst422, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst416, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst449, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst450, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec103, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec103, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst416, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst419, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst451, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst419, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph11, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec103, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec116, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp143, kStack)), BinopInst("*", LoadVarInst(Address(fConst468, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst471, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst472, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec115, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst468, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst470, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst473, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst470, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst466, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst474, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst475, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec114, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst466, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst467, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst476, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst467, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst464, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst477, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst478, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp144, kStack, BinopInst("*", LoadVarInst(Address(fConst464, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst465, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst479, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst465, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec113, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp144, kStack)), BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst480, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst482, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec112, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst463, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst483, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst463, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst458, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst484, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst485, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec111, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst458, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst460, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst486, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst460, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst454, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst487, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst488, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec110, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec110, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst454, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst457, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst489, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst457, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph12, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec110, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec123, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp144, kStack)), BinopInst("*", LoadVarInst(Address(fConst506, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst509, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst510, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec122, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst506, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst511, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst504, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst512, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst513, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec121, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst504, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst505, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst514, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst505, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst502, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst515, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst516, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp145, kStack, BinopInst("*", LoadVarInst(Address(fConst502, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst503, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst517, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst503, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec120, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp145, kStack)), BinopInst("*", LoadVarInst(Address(fConst499, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst518, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst520, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec119, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst499, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst521, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst496, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst522, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst523, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec118, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst496, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst498, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst524, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst498, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst492, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst525, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst526, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec117, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec117, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst492, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst495, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst527, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst495, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph13, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec117, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fRec127, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp145, kStack)), BinopInst("*", LoadVarInst(Address(fConst532, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst535, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst536, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec126, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst532, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst537, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst530, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst538, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst539, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec125, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst530, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst531, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst540, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst531, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst528, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst541, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst542, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec124, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec124, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst528, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst529, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst543, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst529, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(2)]))))))))
		StoreVarInst(Address(fVbargraph14, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec124, kStruct)[Int32(0)]))))))
		DeclareVarInst("float", fTemp146, kStack, LoadVarInst(Address(fTemp132, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp146, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp146, kStack))))
		ForLoopInst 
			DeclareVarInst("int", j0, kLoop, Int32(3))
			BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
			StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(iVec0, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec4, kStruct)[Int32(1)], LoadVarInst(Address(fVec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec5, kStruct)[Int32(1)], LoadVarInst(Address(fVec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec6, kStruct)[Int32(1)], LoadVarInst(Address(fVec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec7, kStruct)[Int32(1)], LoadVarInst(Address(fVec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec8, kStruct)[Int32(1)], LoadVarInst(Address(fVec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec9, kStruct)[Int32(1)], LoadVarInst(Address(fVec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec10, kStruct)[Int32(1)], LoadVarInst(Address(fVec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec11, kStruct)[Int32(1)], LoadVarInst(Address(fVec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec12, kStruct)[Int32(1)], LoadVarInst(Address(fVec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec13, kStruct)[Int32(1)], LoadVarInst(Address(fVec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec14, kStruct)[Int32(1)], LoadVarInst(Address(fVec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec15, kStruct)[Int32(1)], LoadVarInst(Address(fVec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec16, kStruct)[Int32(1)], LoadVarInst(Address(fVec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec17, kStruct)[Int32(1)], LoadVarInst(Address(fVec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec18, kStruct)[Int32(1)], LoadVarInst(Address(fVec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec19, kStruct)[Int32(1)], LoadVarInst(Address(fVec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec21, kStruct)[Int32(1)], LoadVarInst(Address(fVec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec23, kStruct)[Int32(1)], LoadVarInst(Address(fVec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec25, kStruct)[Int32(1)], LoadVarInst(Address(fVec25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec26, kStruct)[Int32(1)], LoadVarInst(Address(fVec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec28, kStruct)[Int32(1)], LoadVarInst(Address(fVec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec29, kStruct)[Int32(1)], LoadVarInst(Address(fVec29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec31, kStruct)[Int32(1)], LoadVarInst(Address(fVec31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec32, kStruct)[Int32(1)], LoadVarInst(Address(fVec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec24, kStruct)[Int32(1)], LoadVarInst(Address(iRec24, kStruct)[Int32(0)]))
		ForLoopInst 
			DeclareVarInst("int", j1, kLoop, Int32(3))
			BinopInst(">", LoadVarInst(Address(j1, kLoop)), Int32(0))
			StoreVarInst(Address(j1, kLoop), BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fRec23, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(2)], LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec25, kStruct)[Int32(2)], LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(2)], LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(2)], LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(2)], LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(2)], LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(2)], LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(2)], LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec46, kStruct)[Int32(2)], LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec46, kStruct)[Int32(1)], LoadVarInst(Address(fRec46, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec45, kStruct)[Int32(2)], LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec44, kStruct)[Int32(2)], LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec43, kStruct)[Int32(2)], LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec42, kStruct)[Int32(2)], LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec41, kStruct)[Int32(2)], LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec53, kStruct)[Int32(2)], LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec53, kStruct)[Int32(1)], LoadVarInst(Address(fRec53, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec52, kStruct)[Int32(2)], LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec52, kStruct)[Int32(1)], LoadVarInst(Address(fRec52, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec51, kStruct)[Int32(2)], LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec51, kStruct)[Int32(1)], LoadVarInst(Address(fRec51, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec50, kStruct)[Int32(2)], LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec50, kStruct)[Int32(1)], LoadVarInst(Address(fRec50, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec49, kStruct)[Int32(2)], LoadVarInst(Address(fRec49, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec49, kStruct)[Int32(1)], LoadVarInst(Address(fRec49, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec48, kStruct)[Int32(2)], LoadVarInst(Address(fRec48, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec48, kStruct)[Int32(1)], LoadVarInst(Address(fRec48, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec47, kStruct)[Int32(1)], LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec60, kStruct)[Int32(2)], LoadVarInst(Address(fRec60, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec60, kStruct)[Int32(1)], LoadVarInst(Address(fRec60, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec59, kStruct)[Int32(2)], LoadVarInst(Address(fRec59, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec59, kStruct)[Int32(1)], LoadVarInst(Address(fRec59, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec58, kStruct)[Int32(2)], LoadVarInst(Address(fRec58, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec58, kStruct)[Int32(1)], LoadVarInst(Address(fRec58, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec57, kStruct)[Int32(2)], LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec57, kStruct)[Int32(1)], LoadVarInst(Address(fRec57, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec56, kStruct)[Int32(2)], LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec56, kStruct)[Int32(1)], LoadVarInst(Address(fRec56, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec55, kStruct)[Int32(2)], LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec55, kStruct)[Int32(1)], LoadVarInst(Address(fRec55, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec54, kStruct)[Int32(1)], LoadVarInst(Address(fRec54, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec67, kStruct)[Int32(2)], LoadVarInst(Address(fRec67, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec67, kStruct)[Int32(1)], LoadVarInst(Address(fRec67, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec66, kStruct)[Int32(2)], LoadVarInst(Address(fRec66, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec66, kStruct)[Int32(1)], LoadVarInst(Address(fRec66, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec65, kStruct)[Int32(2)], LoadVarInst(Address(fRec65, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec65, kStruct)[Int32(1)], LoadVarInst(Address(fRec65, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec64, kStruct)[Int32(2)], LoadVarInst(Address(fRec64, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec64, kStruct)[Int32(1)], LoadVarInst(Address(fRec64, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec63, kStruct)[Int32(2)], LoadVarInst(Address(fRec63, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec63, kStruct)[Int32(1)], LoadVarInst(Address(fRec63, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec62, kStruct)[Int32(2)], LoadVarInst(Address(fRec62, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec62, kStruct)[Int32(1)], LoadVarInst(Address(fRec62, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec61, kStruct)[Int32(1)], LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec74, kStruct)[Int32(2)], LoadVarInst(Address(fRec74, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec74, kStruct)[Int32(1)], LoadVarInst(Address(fRec74, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec73, kStruct)[Int32(2)], LoadVarInst(Address(fRec73, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec73, kStruct)[Int32(1)], LoadVarInst(Address(fRec73, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec72, kStruct)[Int32(2)], LoadVarInst(Address(fRec72, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec72, kStruct)[Int32(1)], LoadVarInst(Address(fRec72, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec71, kStruct)[Int32(2)], LoadVarInst(Address(fRec71, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec71, kStruct)[Int32(1)], LoadVarInst(Address(fRec71, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec70, kStruct)[Int32(2)], LoadVarInst(Address(fRec70, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec70, kStruct)[Int32(1)], LoadVarInst(Address(fRec70, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec69, kStruct)[Int32(2)], LoadVarInst(Address(fRec69, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec69, kStruct)[Int32(1)], LoadVarInst(Address(fRec69, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec68, kStruct)[Int32(1)], LoadVarInst(Address(fRec68, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec81, kStruct)[Int32(2)], LoadVarInst(Address(fRec81, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec81, kStruct)[Int32(1)], LoadVarInst(Address(fRec81, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec80, kStruct)[Int32(2)], LoadVarInst(Address(fRec80, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec80, kStruct)[Int32(1)], LoadVarInst(Address(fRec80, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec79, kStruct)[Int32(2)], LoadVarInst(Address(fRec79, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec79, kStruct)[Int32(1)], LoadVarInst(Address(fRec79, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec78, kStruct)[Int32(2)], LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec78, kStruct)[Int32(1)], LoadVarInst(Address(fRec78, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec77, kStruct)[Int32(2)], LoadVarInst(Address(fRec77, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec77, kStruct)[Int32(1)], LoadVarInst(Address(fRec77, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec76, kStruct)[Int32(2)], LoadVarInst(Address(fRec76, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec76, kStruct)[Int32(1)], LoadVarInst(Address(fRec76, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec75, kStruct)[Int32(1)], LoadVarInst(Address(fRec75, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec88, kStruct)[Int32(2)], LoadVarInst(Address(fRec88, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec88, kStruct)[Int32(1)], LoadVarInst(Address(fRec88, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec87, kStruct)[Int32(2)], LoadVarInst(Address(fRec87, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec87, kStruct)[Int32(1)], LoadVarInst(Address(fRec87, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec86, kStruct)[Int32(2)], LoadVarInst(Address(fRec86, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec86, kStruct)[Int32(1)], LoadVarInst(Address(fRec86, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec85, kStruct)[Int32(2)], LoadVarInst(Address(fRec85, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec85, kStruct)[Int32(1)], LoadVarInst(Address(fRec85, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec84, kStruct)[Int32(2)], LoadVarInst(Address(fRec84, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec84, kStruct)[Int32(1)], LoadVarInst(Address(fRec84, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec83, kStruct)[Int32(2)], LoadVarInst(Address(fRec83, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec83, kStruct)[Int32(1)], LoadVarInst(Address(fRec83, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec82, kStruct)[Int32(1)], LoadVarInst(Address(fRec82, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec95, kStruct)[Int32(2)], LoadVarInst(Address(fRec95, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec95, kStruct)[Int32(1)], LoadVarInst(Address(fRec95, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec94, kStruct)[Int32(2)], LoadVarInst(Address(fRec94, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec94, kStruct)[Int32(1)], LoadVarInst(Address(fRec94, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec93, kStruct)[Int32(2)], LoadVarInst(Address(fRec93, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec93, kStruct)[Int32(1)], LoadVarInst(Address(fRec93, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec92, kStruct)[Int32(2)], LoadVarInst(Address(fRec92, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec92, kStruct)[Int32(1)], LoadVarInst(Address(fRec92, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec91, kStruct)[Int32(2)], LoadVarInst(Address(fRec91, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec91, kStruct)[Int32(1)], LoadVarInst(Address(fRec91, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec90, kStruct)[Int32(2)], LoadVarInst(Address(fRec90, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec90, kStruct)[Int32(1)], LoadVarInst(Address(fRec90, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec89, kStruct)[Int32(1)], LoadVarInst(Address(fRec89, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec102, kStruct)[Int32(2)], LoadVarInst(Address(fRec102, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec102, kStruct)[Int32(1)], LoadVarInst(Address(fRec102, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec101, kStruct)[Int32(2)], LoadVarInst(Address(fRec101, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec101, kStruct)[Int32(1)], LoadVarInst(Address(fRec101, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec100, kStruct)[Int32(2)], LoadVarInst(Address(fRec100, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec100, kStruct)[Int32(1)], LoadVarInst(Address(fRec100, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec99, kStruct)[Int32(2)], LoadVarInst(Address(fRec99, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec99, kStruct)[Int32(1)], LoadVarInst(Address(fRec99, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec98, kStruct)[Int32(2)], LoadVarInst(Address(fRec98, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec98, kStruct)[Int32(1)], LoadVarInst(Address(fRec98, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec97, kStruct)[Int32(2)], LoadVarInst(Address(fRec97, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec97, kStruct)[Int32(1)], LoadVarInst(Address(fRec97, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec96, kStruct)[Int32(1)], LoadVarInst(Address(fRec96, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec109, kStruct)[Int32(2)], LoadVarInst(Address(fRec109, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec109, kStruct)[Int32(1)], LoadVarInst(Address(fRec109, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec108, kStruct)[Int32(2)], LoadVarInst(Address(fRec108, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec108, kStruct)[Int32(1)], LoadVarInst(Address(fRec108, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec107, kStruct)[Int32(2)], LoadVarInst(Address(fRec107, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec107, kStruct)[Int32(1)], LoadVarInst(Address(fRec107, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec106, kStruct)[Int32(2)], LoadVarInst(Address(fRec106, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec106, kStruct)[Int32(1)], LoadVarInst(Address(fRec106, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec105, kStruct)[Int32(2)], LoadVarInst(Address(fRec105, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec105, kStruct)[Int32(1)], LoadVarInst(Address(fRec105, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec104, kStruct)[Int32(2)], LoadVarInst(Address(fRec104, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec104, kStruct)[Int32(1)], LoadVarInst(Address(fRec104, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec103, kStruct)[Int32(1)], LoadVarInst(Address(fRec103, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec116, kStruct)[Int32(2)], LoadVarInst(Address(fRec116, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec116, kStruct)[Int32(1)], LoadVarInst(Address(fRec116, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec115, kStruct)[Int32(2)], LoadVarInst(Address(fRec115, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec115, kStruct)[Int32(1)], LoadVarInst(Address(fRec115, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec114, kStruct)[Int32(2)], LoadVarInst(Address(fRec114, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec114, kStruct)[Int32(1)], LoadVarInst(Address(fRec114, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec113, kStruct)[Int32(2)], LoadVarInst(Address(fRec113, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec113, kStruct)[Int32(1)], LoadVarInst(Address(fRec113, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec112, kStruct)[Int32(2)], LoadVarInst(Address(fRec112, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec112, kStruct)[Int32(1)], LoadVarInst(Address(fRec112, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec111, kStruct)[Int32(2)], LoadVarInst(Address(fRec111, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec111, kStruct)[Int32(1)], LoadVarInst(Address(fRec111, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec110, kStruct)[Int32(1)], LoadVarInst(Address(fRec110, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec123, kStruct)[Int32(2)], LoadVarInst(Address(fRec123, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec123, kStruct)[Int32(1)], LoadVarInst(Address(fRec123, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec122, kStruct)[Int32(2)], LoadVarInst(Address(fRec122, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec122, kStruct)[Int32(1)], LoadVarInst(Address(fRec122, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec121, kStruct)[Int32(2)], LoadVarInst(Address(fRec121, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec121, kStruct)[Int32(1)], LoadVarInst(Address(fRec121, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec120, kStruct)[Int32(2)], LoadVarInst(Address(fRec120, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec120, kStruct)[Int32(1)], LoadVarInst(Address(fRec120, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec119, kStruct)[Int32(2)], LoadVarInst(Address(fRec119, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec119, kStruct)[Int32(1)], LoadVarInst(Address(fRec119, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec118, kStruct)[Int32(2)], LoadVarInst(Address(fRec118, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec118, kStruct)[Int32(1)], LoadVarInst(Address(fRec118, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec117, kStruct)[Int32(1)], LoadVarInst(Address(fRec117, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec127, kStruct)[Int32(2)], LoadVarInst(Address(fRec127, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec127, kStruct)[Int32(1)], LoadVarInst(Address(fRec127, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec126, kStruct)[Int32(2)], LoadVarInst(Address(fRec126, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec126, kStruct)[Int32(1)], LoadVarInst(Address(fRec126, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec125, kStruct)[Int32(2)], LoadVarInst(Address(fRec125, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec125, kStruct)[Int32(1)], LoadVarInst(Address(fRec125, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec124, kStruct)[Int32(1)], LoadVarInst(Address(fRec124, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Post compute DSP begin ==========

BlockInst 
EndBlockInst

======= Post compute DSP end ==========

======= Flatten FIR begin ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", iVec0[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("float", fConst6, kStruct)
	DeclareVarInst("float", fConst7, kStruct)
	DeclareVarInst("float", fConst8, kStruct)
	DeclareVarInst("float", fConst9, kStruct)
	DeclareVarInst("float", fConst10, kStruct)
	DeclareVarInst("float", fConst11, kStruct)
	DeclareVarInst("float", fConst12, kStruct)
	DeclareVarInst("float", fConst13, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("float", fConst14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fRec10[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("float", fRec11[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("float", fConst15, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("float", fConst16, kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("float", fConst17, kStruct)
	DeclareVarInst("float", fVec2[2], kStruct)
	DeclareVarInst("float", fVec3[2], kStruct)
	DeclareVarInst("float", fConst18, kStruct)
	DeclareVarInst("float", fVec4[2], kStruct)
	DeclareVarInst("float", fVec5[2], kStruct)
	DeclareVarInst("float", fVec6[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("float", fVec7[2], kStruct)
	DeclareVarInst("float", fVec8[2], kStruct)
	DeclareVarInst("float", fVec9[2], kStruct)
	DeclareVarInst("float", fVec10[2], kStruct)
	DeclareVarInst("float", fVec11[2], kStruct)
	DeclareVarInst("float", fVec12[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fVec13[2], kStruct)
	DeclareVarInst("float", fVec14[2], kStruct)
	DeclareVarInst("float", fVec15[2], kStruct)
	DeclareVarInst("float", fVec16[2], kStruct)
	DeclareVarInst("float", fVec17[2], kStruct)
	DeclareVarInst("float", fVec18[2], kStruct)
	DeclareVarInst("float", fConst19, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("float", fVec19[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec20[4096], kStruct)
	DeclareVarInst("float", fConst20, kStruct)
	DeclareVarInst("float", fRec17[2], kStruct)
	DeclareVarInst("float", fVec21[2], kStruct)
	DeclareVarInst("float", fVec22[4096], kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("float", fVec23[2], kStruct)
	DeclareVarInst("float", fVec24[4096], kStruct)
	DeclareVarInst("float", fConst21, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("float", fRec19[2], kStruct)
	DeclareVarInst("float", fRec20[2], kStruct)
	DeclareVarInst("float", fRec21[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("float", fConst22, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox2, kStruct)
	DeclareVarInst("float", fVec25[2], kStruct)
	DeclareVarInst("float", fVec26[2], kStruct)
	DeclareVarInst("float", fVec27[4096], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("float", fRec22[2], kStruct)
	DeclareVarInst("float", fVec28[2], kStruct)
	DeclareVarInst("float", fVec29[2], kStruct)
	DeclareVarInst("float", fVec30[4096], kStruct)
	DeclareVarInst("float", fVec31[2], kStruct)
	DeclareVarInst("float", fVec32[2], kStruct)
	DeclareVarInst("float", fVec33[4096], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("int", iRec24[2], kStruct)
	DeclareVarInst("float", fRec23[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox3, kStruct)
	DeclareVarInst("float", fConst23, kStruct)
	DeclareVarInst("float", fRec26[3], kStruct)
	DeclareVarInst("float", fRec25[3], kStruct)
	DeclareVarInst("float", fRec29[2], kStruct)
	DeclareVarInst("float", fRec27[2], kStruct)
	DeclareVarInst("float", fRec32[2], kStruct)
	DeclareVarInst("float", fRec30[2], kStruct)
	DeclareVarInst("float", fConst24, kStruct)
	DeclareVarInst("float", fConst25, kStruct)
	DeclareVarInst("float", fConst26, kStruct)
	DeclareVarInst("float", fRec3[3], kStruct)
	DeclareVarInst("float", fConst27, kStruct)
	DeclareVarInst("float", fConst28, kStruct)
	DeclareVarInst("float", fConst29, kStruct)
	DeclareVarInst("float", fRec2[3], kStruct)
	DeclareVarInst("float", fConst30, kStruct)
	DeclareVarInst("float", fConst31, kStruct)
	DeclareVarInst("float", fConst32, kStruct)
	DeclareVarInst("float", fRec1[3], kStruct)
	DeclareVarInst("float", fConst33, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("float", fConst34, kStruct)
	DeclareVarInst("float", fConst35, kStruct)
	DeclareVarInst("float", fConst36, kStruct)
	DeclareVarInst("float", fConst37, kStruct)
	DeclareVarInst("float", fConst38, kStruct)
	DeclareVarInst("float", fConst39, kStruct)
	DeclareVarInst("float", fConst40, kStruct)
	DeclareVarInst("float", fConst41, kStruct)
	DeclareVarInst("float", fConst42, kStruct)
	DeclareVarInst("float", fConst43, kStruct)
	DeclareVarInst("float", fConst44, kStruct)
	DeclareVarInst("float", fConst45, kStruct)
	DeclareVarInst("float", fConst46, kStruct)
	DeclareVarInst("float", fConst47, kStruct)
	DeclareVarInst("float", fConst48, kStruct)
	DeclareVarInst("float", fConst49, kStruct)
	DeclareVarInst("float", fConst50, kStruct)
	DeclareVarInst("float", fConst51, kStruct)
	DeclareVarInst("float", fConst52, kStruct)
	DeclareVarInst("float", fConst53, kStruct)
	DeclareVarInst("float", fConst54, kStruct)
	DeclareVarInst("float", fRec39[3], kStruct)
	DeclareVarInst("float", fConst55, kStruct)
	DeclareVarInst("float", fConst56, kStruct)
	DeclareVarInst("float", fConst57, kStruct)
	DeclareVarInst("float", fRec38[3], kStruct)
	DeclareVarInst("float", fConst58, kStruct)
	DeclareVarInst("float", fConst59, kStruct)
	DeclareVarInst("float", fConst60, kStruct)
	DeclareVarInst("float", fRec37[3], kStruct)
	DeclareVarInst("float", fConst61, kStruct)
	DeclareVarInst("float", fConst62, kStruct)
	DeclareVarInst("float", fConst63, kStruct)
	DeclareVarInst("float", fConst64, kStruct)
	DeclareVarInst("float", fRec36[3], kStruct)
	DeclareVarInst("float", fConst65, kStruct)
	DeclareVarInst("float", fConst66, kStruct)
	DeclareVarInst("float", fConst67, kStruct)
	DeclareVarInst("float", fRec35[3], kStruct)
	DeclareVarInst("float", fConst68, kStruct)
	DeclareVarInst("float", fConst69, kStruct)
	DeclareVarInst("float", fConst70, kStruct)
	DeclareVarInst("float", fRec34[3], kStruct)
	DeclareVarInst("float", fConst71, kStruct)
	DeclareVarInst("float", fRec33[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("float", fConst72, kStruct)
	DeclareVarInst("float", fConst73, kStruct)
	DeclareVarInst("float", fConst74, kStruct)
	DeclareVarInst("float", fConst75, kStruct)
	DeclareVarInst("float", fConst76, kStruct)
	DeclareVarInst("float", fConst77, kStruct)
	DeclareVarInst("float", fConst78, kStruct)
	DeclareVarInst("float", fConst79, kStruct)
	DeclareVarInst("float", fConst80, kStruct)
	DeclareVarInst("float", fConst81, kStruct)
	DeclareVarInst("float", fConst82, kStruct)
	DeclareVarInst("float", fConst83, kStruct)
	DeclareVarInst("float", fConst84, kStruct)
	DeclareVarInst("float", fConst85, kStruct)
	DeclareVarInst("float", fConst86, kStruct)
	DeclareVarInst("float", fConst87, kStruct)
	DeclareVarInst("float", fConst88, kStruct)
	DeclareVarInst("float", fConst89, kStruct)
	DeclareVarInst("float", fConst90, kStruct)
	DeclareVarInst("float", fConst91, kStruct)
	DeclareVarInst("float", fConst92, kStruct)
	DeclareVarInst("float", fRec46[3], kStruct)
	DeclareVarInst("float", fConst93, kStruct)
	DeclareVarInst("float", fConst94, kStruct)
	DeclareVarInst("float", fConst95, kStruct)
	DeclareVarInst("float", fRec45[3], kStruct)
	DeclareVarInst("float", fConst96, kStruct)
	DeclareVarInst("float", fConst97, kStruct)
	DeclareVarInst("float", fConst98, kStruct)
	DeclareVarInst("float", fRec44[3], kStruct)
	DeclareVarInst("float", fConst99, kStruct)
	DeclareVarInst("float", fConst100, kStruct)
	DeclareVarInst("float", fConst101, kStruct)
	DeclareVarInst("float", fConst102, kStruct)
	DeclareVarInst("float", fRec43[3], kStruct)
	DeclareVarInst("float", fConst103, kStruct)
	DeclareVarInst("float", fConst104, kStruct)
	DeclareVarInst("float", fConst105, kStruct)
	DeclareVarInst("float", fRec42[3], kStruct)
	DeclareVarInst("float", fConst106, kStruct)
	DeclareVarInst("float", fConst107, kStruct)
	DeclareVarInst("float", fConst108, kStruct)
	DeclareVarInst("float", fRec41[3], kStruct)
	DeclareVarInst("float", fConst109, kStruct)
	DeclareVarInst("float", fRec40[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("float", fConst110, kStruct)
	DeclareVarInst("float", fConst111, kStruct)
	DeclareVarInst("float", fConst112, kStruct)
	DeclareVarInst("float", fConst113, kStruct)
	DeclareVarInst("float", fConst114, kStruct)
	DeclareVarInst("float", fConst115, kStruct)
	DeclareVarInst("float", fConst116, kStruct)
	DeclareVarInst("float", fConst117, kStruct)
	DeclareVarInst("float", fConst118, kStruct)
	DeclareVarInst("float", fConst119, kStruct)
	DeclareVarInst("float", fConst120, kStruct)
	DeclareVarInst("float", fConst121, kStruct)
	DeclareVarInst("float", fConst122, kStruct)
	DeclareVarInst("float", fConst123, kStruct)
	DeclareVarInst("float", fConst124, kStruct)
	DeclareVarInst("float", fConst125, kStruct)
	DeclareVarInst("float", fConst126, kStruct)
	DeclareVarInst("float", fConst127, kStruct)
	DeclareVarInst("float", fConst128, kStruct)
	DeclareVarInst("float", fConst129, kStruct)
	DeclareVarInst("float", fConst130, kStruct)
	DeclareVarInst("float", fRec53[3], kStruct)
	DeclareVarInst("float", fConst131, kStruct)
	DeclareVarInst("float", fConst132, kStruct)
	DeclareVarInst("float", fConst133, kStruct)
	DeclareVarInst("float", fRec52[3], kStruct)
	DeclareVarInst("float", fConst134, kStruct)
	DeclareVarInst("float", fConst135, kStruct)
	DeclareVarInst("float", fConst136, kStruct)
	DeclareVarInst("float", fRec51[3], kStruct)
	DeclareVarInst("float", fConst137, kStruct)
	DeclareVarInst("float", fConst138, kStruct)
	DeclareVarInst("float", fConst139, kStruct)
	DeclareVarInst("float", fConst140, kStruct)
	DeclareVarInst("float", fRec50[3], kStruct)
	DeclareVarInst("float", fConst141, kStruct)
	DeclareVarInst("float", fConst142, kStruct)
	DeclareVarInst("float", fConst143, kStruct)
	DeclareVarInst("float", fRec49[3], kStruct)
	DeclareVarInst("float", fConst144, kStruct)
	DeclareVarInst("float", fConst145, kStruct)
	DeclareVarInst("float", fConst146, kStruct)
	DeclareVarInst("float", fRec48[3], kStruct)
	DeclareVarInst("float", fConst147, kStruct)
	DeclareVarInst("float", fRec47[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("float", fConst148, kStruct)
	DeclareVarInst("float", fConst149, kStruct)
	DeclareVarInst("float", fConst150, kStruct)
	DeclareVarInst("float", fConst151, kStruct)
	DeclareVarInst("float", fConst152, kStruct)
	DeclareVarInst("float", fConst153, kStruct)
	DeclareVarInst("float", fConst154, kStruct)
	DeclareVarInst("float", fConst155, kStruct)
	DeclareVarInst("float", fConst156, kStruct)
	DeclareVarInst("float", fConst157, kStruct)
	DeclareVarInst("float", fConst158, kStruct)
	DeclareVarInst("float", fConst159, kStruct)
	DeclareVarInst("float", fConst160, kStruct)
	DeclareVarInst("float", fConst161, kStruct)
	DeclareVarInst("float", fConst162, kStruct)
	DeclareVarInst("float", fConst163, kStruct)
	DeclareVarInst("float", fConst164, kStruct)
	DeclareVarInst("float", fConst165, kStruct)
	DeclareVarInst("float", fConst166, kStruct)
	DeclareVarInst("float", fConst167, kStruct)
	DeclareVarInst("float", fConst168, kStruct)
	DeclareVarInst("float", fRec60[3], kStruct)
	DeclareVarInst("float", fConst169, kStruct)
	DeclareVarInst("float", fConst170, kStruct)
	DeclareVarInst("float", fConst171, kStruct)
	DeclareVarInst("float", fRec59[3], kStruct)
	DeclareVarInst("float", fConst172, kStruct)
	DeclareVarInst("float", fConst173, kStruct)
	DeclareVarInst("float", fConst174, kStruct)
	DeclareVarInst("float", fRec58[3], kStruct)
	DeclareVarInst("float", fConst175, kStruct)
	DeclareVarInst("float", fConst176, kStruct)
	DeclareVarInst("float", fConst177, kStruct)
	DeclareVarInst("float", fConst178, kStruct)
	DeclareVarInst("float", fRec57[3], kStruct)
	DeclareVarInst("float", fConst179, kStruct)
	DeclareVarInst("float", fConst180, kStruct)
	DeclareVarInst("float", fConst181, kStruct)
	DeclareVarInst("float", fRec56[3], kStruct)
	DeclareVarInst("float", fConst182, kStruct)
	DeclareVarInst("float", fConst183, kStruct)
	DeclareVarInst("float", fConst184, kStruct)
	DeclareVarInst("float", fRec55[3], kStruct)
	DeclareVarInst("float", fConst185, kStruct)
	DeclareVarInst("float", fRec54[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph4, kStruct)
	DeclareVarInst("float", fConst186, kStruct)
	DeclareVarInst("float", fConst187, kStruct)
	DeclareVarInst("float", fConst188, kStruct)
	DeclareVarInst("float", fConst189, kStruct)
	DeclareVarInst("float", fConst190, kStruct)
	DeclareVarInst("float", fConst191, kStruct)
	DeclareVarInst("float", fConst192, kStruct)
	DeclareVarInst("float", fConst193, kStruct)
	DeclareVarInst("float", fConst194, kStruct)
	DeclareVarInst("float", fConst195, kStruct)
	DeclareVarInst("float", fConst196, kStruct)
	DeclareVarInst("float", fConst197, kStruct)
	DeclareVarInst("float", fConst198, kStruct)
	DeclareVarInst("float", fConst199, kStruct)
	DeclareVarInst("float", fConst200, kStruct)
	DeclareVarInst("float", fConst201, kStruct)
	DeclareVarInst("float", fConst202, kStruct)
	DeclareVarInst("float", fConst203, kStruct)
	DeclareVarInst("float", fConst204, kStruct)
	DeclareVarInst("float", fConst205, kStruct)
	DeclareVarInst("float", fConst206, kStruct)
	DeclareVarInst("float", fRec67[3], kStruct)
	DeclareVarInst("float", fConst207, kStruct)
	DeclareVarInst("float", fConst208, kStruct)
	DeclareVarInst("float", fConst209, kStruct)
	DeclareVarInst("float", fRec66[3], kStruct)
	DeclareVarInst("float", fConst210, kStruct)
	DeclareVarInst("float", fConst211, kStruct)
	DeclareVarInst("float", fConst212, kStruct)
	DeclareVarInst("float", fRec65[3], kStruct)
	DeclareVarInst("float", fConst213, kStruct)
	DeclareVarInst("float", fConst214, kStruct)
	DeclareVarInst("float", fConst215, kStruct)
	DeclareVarInst("float", fConst216, kStruct)
	DeclareVarInst("float", fRec64[3], kStruct)
	DeclareVarInst("float", fConst217, kStruct)
	DeclareVarInst("float", fConst218, kStruct)
	DeclareVarInst("float", fConst219, kStruct)
	DeclareVarInst("float", fRec63[3], kStruct)
	DeclareVarInst("float", fConst220, kStruct)
	DeclareVarInst("float", fConst221, kStruct)
	DeclareVarInst("float", fConst222, kStruct)
	DeclareVarInst("float", fRec62[3], kStruct)
	DeclareVarInst("float", fConst223, kStruct)
	DeclareVarInst("float", fRec61[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph5, kStruct)
	DeclareVarInst("float", fConst224, kStruct)
	DeclareVarInst("float", fConst225, kStruct)
	DeclareVarInst("float", fConst226, kStruct)
	DeclareVarInst("float", fConst227, kStruct)
	DeclareVarInst("float", fConst228, kStruct)
	DeclareVarInst("float", fConst229, kStruct)
	DeclareVarInst("float", fConst230, kStruct)
	DeclareVarInst("float", fConst231, kStruct)
	DeclareVarInst("float", fConst232, kStruct)
	DeclareVarInst("float", fConst233, kStruct)
	DeclareVarInst("float", fConst234, kStruct)
	DeclareVarInst("float", fConst235, kStruct)
	DeclareVarInst("float", fConst236, kStruct)
	DeclareVarInst("float", fConst237, kStruct)
	DeclareVarInst("float", fConst238, kStruct)
	DeclareVarInst("float", fConst239, kStruct)
	DeclareVarInst("float", fConst240, kStruct)
	DeclareVarInst("float", fConst241, kStruct)
	DeclareVarInst("float", fConst242, kStruct)
	DeclareVarInst("float", fConst243, kStruct)
	DeclareVarInst("float", fConst244, kStruct)
	DeclareVarInst("float", fRec74[3], kStruct)
	DeclareVarInst("float", fConst245, kStruct)
	DeclareVarInst("float", fConst246, kStruct)
	DeclareVarInst("float", fConst247, kStruct)
	DeclareVarInst("float", fRec73[3], kStruct)
	DeclareVarInst("float", fConst248, kStruct)
	DeclareVarInst("float", fConst249, kStruct)
	DeclareVarInst("float", fConst250, kStruct)
	DeclareVarInst("float", fRec72[3], kStruct)
	DeclareVarInst("float", fConst251, kStruct)
	DeclareVarInst("float", fConst252, kStruct)
	DeclareVarInst("float", fConst253, kStruct)
	DeclareVarInst("float", fConst254, kStruct)
	DeclareVarInst("float", fRec71[3], kStruct)
	DeclareVarInst("float", fConst255, kStruct)
	DeclareVarInst("float", fConst256, kStruct)
	DeclareVarInst("float", fConst257, kStruct)
	DeclareVarInst("float", fRec70[3], kStruct)
	DeclareVarInst("float", fConst258, kStruct)
	DeclareVarInst("float", fConst259, kStruct)
	DeclareVarInst("float", fConst260, kStruct)
	DeclareVarInst("float", fRec69[3], kStruct)
	DeclareVarInst("float", fConst261, kStruct)
	DeclareVarInst("float", fRec68[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph6, kStruct)
	DeclareVarInst("float", fConst262, kStruct)
	DeclareVarInst("float", fConst263, kStruct)
	DeclareVarInst("float", fConst264, kStruct)
	DeclareVarInst("float", fConst265, kStruct)
	DeclareVarInst("float", fConst266, kStruct)
	DeclareVarInst("float", fConst267, kStruct)
	DeclareVarInst("float", fConst268, kStruct)
	DeclareVarInst("float", fConst269, kStruct)
	DeclareVarInst("float", fConst270, kStruct)
	DeclareVarInst("float", fConst271, kStruct)
	DeclareVarInst("float", fConst272, kStruct)
	DeclareVarInst("float", fConst273, kStruct)
	DeclareVarInst("float", fConst274, kStruct)
	DeclareVarInst("float", fConst275, kStruct)
	DeclareVarInst("float", fConst276, kStruct)
	DeclareVarInst("float", fConst277, kStruct)
	DeclareVarInst("float", fConst278, kStruct)
	DeclareVarInst("float", fConst279, kStruct)
	DeclareVarInst("float", fConst280, kStruct)
	DeclareVarInst("float", fConst281, kStruct)
	DeclareVarInst("float", fConst282, kStruct)
	DeclareVarInst("float", fRec81[3], kStruct)
	DeclareVarInst("float", fConst283, kStruct)
	DeclareVarInst("float", fConst284, kStruct)
	DeclareVarInst("float", fConst285, kStruct)
	DeclareVarInst("float", fRec80[3], kStruct)
	DeclareVarInst("float", fConst286, kStruct)
	DeclareVarInst("float", fConst287, kStruct)
	DeclareVarInst("float", fConst288, kStruct)
	DeclareVarInst("float", fRec79[3], kStruct)
	DeclareVarInst("float", fConst289, kStruct)
	DeclareVarInst("float", fConst290, kStruct)
	DeclareVarInst("float", fConst291, kStruct)
	DeclareVarInst("float", fConst292, kStruct)
	DeclareVarInst("float", fRec78[3], kStruct)
	DeclareVarInst("float", fConst293, kStruct)
	DeclareVarInst("float", fConst294, kStruct)
	DeclareVarInst("float", fConst295, kStruct)
	DeclareVarInst("float", fRec77[3], kStruct)
	DeclareVarInst("float", fConst296, kStruct)
	DeclareVarInst("float", fConst297, kStruct)
	DeclareVarInst("float", fConst298, kStruct)
	DeclareVarInst("float", fRec76[3], kStruct)
	DeclareVarInst("float", fConst299, kStruct)
	DeclareVarInst("float", fRec75[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph7, kStruct)
	DeclareVarInst("float", fConst300, kStruct)
	DeclareVarInst("float", fConst301, kStruct)
	DeclareVarInst("float", fConst302, kStruct)
	DeclareVarInst("float", fConst303, kStruct)
	DeclareVarInst("float", fConst304, kStruct)
	DeclareVarInst("float", fConst305, kStruct)
	DeclareVarInst("float", fConst306, kStruct)
	DeclareVarInst("float", fConst307, kStruct)
	DeclareVarInst("float", fConst308, kStruct)
	DeclareVarInst("float", fConst309, kStruct)
	DeclareVarInst("float", fConst310, kStruct)
	DeclareVarInst("float", fConst311, kStruct)
	DeclareVarInst("float", fConst312, kStruct)
	DeclareVarInst("float", fConst313, kStruct)
	DeclareVarInst("float", fConst314, kStruct)
	DeclareVarInst("float", fConst315, kStruct)
	DeclareVarInst("float", fConst316, kStruct)
	DeclareVarInst("float", fConst317, kStruct)
	DeclareVarInst("float", fConst318, kStruct)
	DeclareVarInst("float", fConst319, kStruct)
	DeclareVarInst("float", fConst320, kStruct)
	DeclareVarInst("float", fRec88[3], kStruct)
	DeclareVarInst("float", fConst321, kStruct)
	DeclareVarInst("float", fConst322, kStruct)
	DeclareVarInst("float", fConst323, kStruct)
	DeclareVarInst("float", fRec87[3], kStruct)
	DeclareVarInst("float", fConst324, kStruct)
	DeclareVarInst("float", fConst325, kStruct)
	DeclareVarInst("float", fConst326, kStruct)
	DeclareVarInst("float", fRec86[3], kStruct)
	DeclareVarInst("float", fConst327, kStruct)
	DeclareVarInst("float", fConst328, kStruct)
	DeclareVarInst("float", fConst329, kStruct)
	DeclareVarInst("float", fConst330, kStruct)
	DeclareVarInst("float", fRec85[3], kStruct)
	DeclareVarInst("float", fConst331, kStruct)
	DeclareVarInst("float", fConst332, kStruct)
	DeclareVarInst("float", fConst333, kStruct)
	DeclareVarInst("float", fRec84[3], kStruct)
	DeclareVarInst("float", fConst334, kStruct)
	DeclareVarInst("float", fConst335, kStruct)
	DeclareVarInst("float", fConst336, kStruct)
	DeclareVarInst("float", fRec83[3], kStruct)
	DeclareVarInst("float", fConst337, kStruct)
	DeclareVarInst("float", fRec82[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph8, kStruct)
	DeclareVarInst("float", fConst338, kStruct)
	DeclareVarInst("float", fConst339, kStruct)
	DeclareVarInst("float", fConst340, kStruct)
	DeclareVarInst("float", fConst341, kStruct)
	DeclareVarInst("float", fConst342, kStruct)
	DeclareVarInst("float", fConst343, kStruct)
	DeclareVarInst("float", fConst344, kStruct)
	DeclareVarInst("float", fConst345, kStruct)
	DeclareVarInst("float", fConst346, kStruct)
	DeclareVarInst("float", fConst347, kStruct)
	DeclareVarInst("float", fConst348, kStruct)
	DeclareVarInst("float", fConst349, kStruct)
	DeclareVarInst("float", fConst350, kStruct)
	DeclareVarInst("float", fConst351, kStruct)
	DeclareVarInst("float", fConst352, kStruct)
	DeclareVarInst("float", fConst353, kStruct)
	DeclareVarInst("float", fConst354, kStruct)
	DeclareVarInst("float", fConst355, kStruct)
	DeclareVarInst("float", fConst356, kStruct)
	DeclareVarInst("float", fConst357, kStruct)
	DeclareVarInst("float", fConst358, kStruct)
	DeclareVarInst("float", fRec95[3], kStruct)
	DeclareVarInst("float", fConst359, kStruct)
	DeclareVarInst("float", fConst360, kStruct)
	DeclareVarInst("float", fConst361, kStruct)
	DeclareVarInst("float", fRec94[3], kStruct)
	DeclareVarInst("float", fConst362, kStruct)
	DeclareVarInst("float", fConst363, kStruct)
	DeclareVarInst("float", fConst364, kStruct)
	DeclareVarInst("float", fRec93[3], kStruct)
	DeclareVarInst("float", fConst365, kStruct)
	DeclareVarInst("float", fConst366, kStruct)
	DeclareVarInst("float", fConst367, kStruct)
	DeclareVarInst("float", fConst368, kStruct)
	DeclareVarInst("float", fRec92[3], kStruct)
	DeclareVarInst("float", fConst369, kStruct)
	DeclareVarInst("float", fConst370, kStruct)
	DeclareVarInst("float", fConst371, kStruct)
	DeclareVarInst("float", fRec91[3], kStruct)
	DeclareVarInst("float", fConst372, kStruct)
	DeclareVarInst("float", fConst373, kStruct)
	DeclareVarInst("float", fConst374, kStruct)
	DeclareVarInst("float", fRec90[3], kStruct)
	DeclareVarInst("float", fConst375, kStruct)
	DeclareVarInst("float", fRec89[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph9, kStruct)
	DeclareVarInst("float", fConst376, kStruct)
	DeclareVarInst("float", fConst377, kStruct)
	DeclareVarInst("float", fConst378, kStruct)
	DeclareVarInst("float", fConst379, kStruct)
	DeclareVarInst("float", fConst380, kStruct)
	DeclareVarInst("float", fConst381, kStruct)
	DeclareVarInst("float", fConst382, kStruct)
	DeclareVarInst("float", fConst383, kStruct)
	DeclareVarInst("float", fConst384, kStruct)
	DeclareVarInst("float", fConst385, kStruct)
	DeclareVarInst("float", fConst386, kStruct)
	DeclareVarInst("float", fConst387, kStruct)
	DeclareVarInst("float", fConst388, kStruct)
	DeclareVarInst("float", fConst389, kStruct)
	DeclareVarInst("float", fConst390, kStruct)
	DeclareVarInst("float", fConst391, kStruct)
	DeclareVarInst("float", fConst392, kStruct)
	DeclareVarInst("float", fConst393, kStruct)
	DeclareVarInst("float", fConst394, kStruct)
	DeclareVarInst("float", fConst395, kStruct)
	DeclareVarInst("float", fConst396, kStruct)
	DeclareVarInst("float", fRec102[3], kStruct)
	DeclareVarInst("float", fConst397, kStruct)
	DeclareVarInst("float", fConst398, kStruct)
	DeclareVarInst("float", fConst399, kStruct)
	DeclareVarInst("float", fRec101[3], kStruct)
	DeclareVarInst("float", fConst400, kStruct)
	DeclareVarInst("float", fConst401, kStruct)
	DeclareVarInst("float", fConst402, kStruct)
	DeclareVarInst("float", fRec100[3], kStruct)
	DeclareVarInst("float", fConst403, kStruct)
	DeclareVarInst("float", fConst404, kStruct)
	DeclareVarInst("float", fConst405, kStruct)
	DeclareVarInst("float", fConst406, kStruct)
	DeclareVarInst("float", fRec99[3], kStruct)
	DeclareVarInst("float", fConst407, kStruct)
	DeclareVarInst("float", fConst408, kStruct)
	DeclareVarInst("float", fConst409, kStruct)
	DeclareVarInst("float", fRec98[3], kStruct)
	DeclareVarInst("float", fConst410, kStruct)
	DeclareVarInst("float", fConst411, kStruct)
	DeclareVarInst("float", fConst412, kStruct)
	DeclareVarInst("float", fRec97[3], kStruct)
	DeclareVarInst("float", fConst413, kStruct)
	DeclareVarInst("float", fRec96[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph10, kStruct)
	DeclareVarInst("float", fConst414, kStruct)
	DeclareVarInst("float", fConst415, kStruct)
	DeclareVarInst("float", fConst416, kStruct)
	DeclareVarInst("float", fConst417, kStruct)
	DeclareVarInst("float", fConst418, kStruct)
	DeclareVarInst("float", fConst419, kStruct)
	DeclareVarInst("float", fConst420, kStruct)
	DeclareVarInst("float", fConst421, kStruct)
	DeclareVarInst("float", fConst422, kStruct)
	DeclareVarInst("float", fConst423, kStruct)
	DeclareVarInst("float", fConst424, kStruct)
	DeclareVarInst("float", fConst425, kStruct)
	DeclareVarInst("float", fConst426, kStruct)
	DeclareVarInst("float", fConst427, kStruct)
	DeclareVarInst("float", fConst428, kStruct)
	DeclareVarInst("float", fConst429, kStruct)
	DeclareVarInst("float", fConst430, kStruct)
	DeclareVarInst("float", fConst431, kStruct)
	DeclareVarInst("float", fConst432, kStruct)
	DeclareVarInst("float", fConst433, kStruct)
	DeclareVarInst("float", fConst434, kStruct)
	DeclareVarInst("float", fRec109[3], kStruct)
	DeclareVarInst("float", fConst435, kStruct)
	DeclareVarInst("float", fConst436, kStruct)
	DeclareVarInst("float", fConst437, kStruct)
	DeclareVarInst("float", fRec108[3], kStruct)
	DeclareVarInst("float", fConst438, kStruct)
	DeclareVarInst("float", fConst439, kStruct)
	DeclareVarInst("float", fConst440, kStruct)
	DeclareVarInst("float", fRec107[3], kStruct)
	DeclareVarInst("float", fConst441, kStruct)
	DeclareVarInst("float", fConst442, kStruct)
	DeclareVarInst("float", fConst443, kStruct)
	DeclareVarInst("float", fConst444, kStruct)
	DeclareVarInst("float", fRec106[3], kStruct)
	DeclareVarInst("float", fConst445, kStruct)
	DeclareVarInst("float", fConst446, kStruct)
	DeclareVarInst("float", fConst447, kStruct)
	DeclareVarInst("float", fRec105[3], kStruct)
	DeclareVarInst("float", fConst448, kStruct)
	DeclareVarInst("float", fConst449, kStruct)
	DeclareVarInst("float", fConst450, kStruct)
	DeclareVarInst("float", fRec104[3], kStruct)
	DeclareVarInst("float", fConst451, kStruct)
	DeclareVarInst("float", fRec103[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph11, kStruct)
	DeclareVarInst("float", fConst452, kStruct)
	DeclareVarInst("float", fConst453, kStruct)
	DeclareVarInst("float", fConst454, kStruct)
	DeclareVarInst("float", fConst455, kStruct)
	DeclareVarInst("float", fConst456, kStruct)
	DeclareVarInst("float", fConst457, kStruct)
	DeclareVarInst("float", fConst458, kStruct)
	DeclareVarInst("float", fConst459, kStruct)
	DeclareVarInst("float", fConst460, kStruct)
	DeclareVarInst("float", fConst461, kStruct)
	DeclareVarInst("float", fConst462, kStruct)
	DeclareVarInst("float", fConst463, kStruct)
	DeclareVarInst("float", fConst464, kStruct)
	DeclareVarInst("float", fConst465, kStruct)
	DeclareVarInst("float", fConst466, kStruct)
	DeclareVarInst("float", fConst467, kStruct)
	DeclareVarInst("float", fConst468, kStruct)
	DeclareVarInst("float", fConst469, kStruct)
	DeclareVarInst("float", fConst470, kStruct)
	DeclareVarInst("float", fConst471, kStruct)
	DeclareVarInst("float", fConst472, kStruct)
	DeclareVarInst("float", fRec116[3], kStruct)
	DeclareVarInst("float", fConst473, kStruct)
	DeclareVarInst("float", fConst474, kStruct)
	DeclareVarInst("float", fConst475, kStruct)
	DeclareVarInst("float", fRec115[3], kStruct)
	DeclareVarInst("float", fConst476, kStruct)
	DeclareVarInst("float", fConst477, kStruct)
	DeclareVarInst("float", fConst478, kStruct)
	DeclareVarInst("float", fRec114[3], kStruct)
	DeclareVarInst("float", fConst479, kStruct)
	DeclareVarInst("float", fConst480, kStruct)
	DeclareVarInst("float", fConst481, kStruct)
	DeclareVarInst("float", fConst482, kStruct)
	DeclareVarInst("float", fRec113[3], kStruct)
	DeclareVarInst("float", fConst483, kStruct)
	DeclareVarInst("float", fConst484, kStruct)
	DeclareVarInst("float", fConst485, kStruct)
	DeclareVarInst("float", fRec112[3], kStruct)
	DeclareVarInst("float", fConst486, kStruct)
	DeclareVarInst("float", fConst487, kStruct)
	DeclareVarInst("float", fConst488, kStruct)
	DeclareVarInst("float", fRec111[3], kStruct)
	DeclareVarInst("float", fConst489, kStruct)
	DeclareVarInst("float", fRec110[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph12, kStruct)
	DeclareVarInst("float", fConst490, kStruct)
	DeclareVarInst("float", fConst491, kStruct)
	DeclareVarInst("float", fConst492, kStruct)
	DeclareVarInst("float", fConst493, kStruct)
	DeclareVarInst("float", fConst494, kStruct)
	DeclareVarInst("float", fConst495, kStruct)
	DeclareVarInst("float", fConst496, kStruct)
	DeclareVarInst("float", fConst497, kStruct)
	DeclareVarInst("float", fConst498, kStruct)
	DeclareVarInst("float", fConst499, kStruct)
	DeclareVarInst("float", fConst500, kStruct)
	DeclareVarInst("float", fConst501, kStruct)
	DeclareVarInst("float", fConst502, kStruct)
	DeclareVarInst("float", fConst503, kStruct)
	DeclareVarInst("float", fConst504, kStruct)
	DeclareVarInst("float", fConst505, kStruct)
	DeclareVarInst("float", fConst506, kStruct)
	DeclareVarInst("float", fConst507, kStruct)
	DeclareVarInst("float", fConst508, kStruct)
	DeclareVarInst("float", fConst509, kStruct)
	DeclareVarInst("float", fConst510, kStruct)
	DeclareVarInst("float", fRec123[3], kStruct)
	DeclareVarInst("float", fConst511, kStruct)
	DeclareVarInst("float", fConst512, kStruct)
	DeclareVarInst("float", fConst513, kStruct)
	DeclareVarInst("float", fRec122[3], kStruct)
	DeclareVarInst("float", fConst514, kStruct)
	DeclareVarInst("float", fConst515, kStruct)
	DeclareVarInst("float", fConst516, kStruct)
	DeclareVarInst("float", fRec121[3], kStruct)
	DeclareVarInst("float", fConst517, kStruct)
	DeclareVarInst("float", fConst518, kStruct)
	DeclareVarInst("float", fConst519, kStruct)
	DeclareVarInst("float", fConst520, kStruct)
	DeclareVarInst("float", fRec120[3], kStruct)
	DeclareVarInst("float", fConst521, kStruct)
	DeclareVarInst("float", fConst522, kStruct)
	DeclareVarInst("float", fConst523, kStruct)
	DeclareVarInst("float", fRec119[3], kStruct)
	DeclareVarInst("float", fConst524, kStruct)
	DeclareVarInst("float", fConst525, kStruct)
	DeclareVarInst("float", fConst526, kStruct)
	DeclareVarInst("float", fRec118[3], kStruct)
	DeclareVarInst("float", fConst527, kStruct)
	DeclareVarInst("float", fRec117[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph13, kStruct)
	DeclareVarInst("float", fConst528, kStruct)
	DeclareVarInst("float", fConst529, kStruct)
	DeclareVarInst("float", fConst530, kStruct)
	DeclareVarInst("float", fConst531, kStruct)
	DeclareVarInst("float", fConst532, kStruct)
	DeclareVarInst("float", fConst533, kStruct)
	DeclareVarInst("float", fConst534, kStruct)
	DeclareVarInst("float", fConst535, kStruct)
	DeclareVarInst("float", fConst536, kStruct)
	DeclareVarInst("float", fRec127[3], kStruct)
	DeclareVarInst("float", fConst537, kStruct)
	DeclareVarInst("float", fConst538, kStruct)
	DeclareVarInst("float", fConst539, kStruct)
	DeclareVarInst("float", fRec126[3], kStruct)
	DeclareVarInst("float", fConst540, kStruct)
	DeclareVarInst("float", fConst541, kStruct)
	DeclareVarInst("float", fConst542, kStruct)
	DeclareVarInst("float", fRec125[3], kStruct)
	DeclareVarInst("float", fConst543, kStruct)
	DeclareVarInst("float", fRec124[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph14, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("tanf", BinopInst("/", Float(50265.484f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst5, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("+", LoadVarInst(Address(fConst6, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst9, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("+", LoadVarInst(Address(fConst9, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst2, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("*", Float(0.041666668f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("*", Float(0.0052083335f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("*", Float(0.083333336f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("/", Float(1.3333334f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("*", Float(0.013888889f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst24, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst2, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst26, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst27, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst12, kStruct)))))
	StoreVarInst(Address(fConst28, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst9, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst32, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst33, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst6, kStruct)))))
	StoreVarInst(Address(fConst34, kStruct), FunCallInst("tanf", BinopInst("/", Float(31665.27f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst34, kStruct))))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst37, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst34, kStruct))))
	StoreVarInst(Address(fConst38, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst39, kStruct), BinopInst("+", LoadVarInst(Address(fConst38, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst41, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst42, kStruct), BinopInst("+", LoadVarInst(Address(fConst41, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst43, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst34, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst45, kStruct), BinopInst("+", LoadVarInst(Address(fConst44, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst46, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst47, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst48, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst49, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst50, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst51, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst52, kStruct), BinopInst("+", LoadVarInst(Address(fConst51, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst53, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst54, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst55, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst51, kStruct)))))
	StoreVarInst(Address(fConst56, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst2, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst57, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst58, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst59, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst2, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst60, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst61, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst25, kStruct)))))
	StoreVarInst(Address(fConst62, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst34, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst63, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst64, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst65, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst44, kStruct)))))
	StoreVarInst(Address(fConst66, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst67, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst68, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst41, kStruct)))))
	StoreVarInst(Address(fConst69, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst70, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst71, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst38, kStruct)))))
	StoreVarInst(Address(fConst72, kStruct), FunCallInst("tanf", BinopInst("/", Float(19947.87f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst73, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst72, kStruct))))
	StoreVarInst(Address(fConst74, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst75, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst72, kStruct))))
	StoreVarInst(Address(fConst76, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst77, kStruct), BinopInst("+", LoadVarInst(Address(fConst76, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst78, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst79, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst80, kStruct), BinopInst("+", LoadVarInst(Address(fConst79, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst81, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst72, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst82, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst83, kStruct), BinopInst("+", LoadVarInst(Address(fConst82, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst84, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst85, kStruct), BinopInst("+", LoadVarInst(Address(fConst63, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst86, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst87, kStruct), BinopInst("+", LoadVarInst(Address(fConst63, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst88, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst89, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst37, kStruct))))
	StoreVarInst(Address(fConst90, kStruct), BinopInst("+", LoadVarInst(Address(fConst89, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst91, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst92, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst93, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst89, kStruct)))))
	StoreVarInst(Address(fConst94, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst34, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst95, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst96, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst97, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst35, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst34, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst98, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst99, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst63, kStruct)))))
	StoreVarInst(Address(fConst100, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst72, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst101, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst102, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst103, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst82, kStruct)))))
	StoreVarInst(Address(fConst104, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst105, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst106, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst79, kStruct)))))
	StoreVarInst(Address(fConst107, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst108, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst109, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst76, kStruct)))))
	StoreVarInst(Address(fConst110, kStruct), FunCallInst("tanf", BinopInst("/", Float(12566.371f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst111, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst110, kStruct))))
	StoreVarInst(Address(fConst112, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst113, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst110, kStruct))))
	StoreVarInst(Address(fConst114, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst115, kStruct), BinopInst("+", LoadVarInst(Address(fConst114, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst116, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst117, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst118, kStruct), BinopInst("+", LoadVarInst(Address(fConst117, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst119, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst110, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst120, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst121, kStruct), BinopInst("+", LoadVarInst(Address(fConst120, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst122, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst123, kStruct), BinopInst("+", LoadVarInst(Address(fConst101, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst124, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst125, kStruct), BinopInst("+", LoadVarInst(Address(fConst101, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst126, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst127, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst128, kStruct), BinopInst("+", LoadVarInst(Address(fConst127, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst129, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst130, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst131, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst127, kStruct)))))
	StoreVarInst(Address(fConst132, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst72, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst133, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst134, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst135, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst73, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst72, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst136, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst137, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst101, kStruct)))))
	StoreVarInst(Address(fConst138, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst110, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst139, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst140, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst141, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst120, kStruct)))))
	StoreVarInst(Address(fConst142, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst143, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst144, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst117, kStruct)))))
	StoreVarInst(Address(fConst145, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst146, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst147, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst114, kStruct)))))
	StoreVarInst(Address(fConst148, kStruct), FunCallInst("tanf", BinopInst("/", Float(7916.3174f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst149, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst150, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst151, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst152, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst153, kStruct), BinopInst("+", LoadVarInst(Address(fConst152, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst154, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst155, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst156, kStruct), BinopInst("+", LoadVarInst(Address(fConst155, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst157, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst148, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst158, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst159, kStruct), BinopInst("+", LoadVarInst(Address(fConst158, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst160, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst161, kStruct), BinopInst("+", LoadVarInst(Address(fConst139, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst162, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst163, kStruct), BinopInst("+", LoadVarInst(Address(fConst139, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst164, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst165, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst113, kStruct))))
	StoreVarInst(Address(fConst166, kStruct), BinopInst("+", LoadVarInst(Address(fConst165, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst167, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst168, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst169, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst165, kStruct)))))
	StoreVarInst(Address(fConst170, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst110, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst171, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst172, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst173, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst111, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst110, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst174, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst175, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst139, kStruct)))))
	StoreVarInst(Address(fConst176, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst148, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst177, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst178, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst179, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst158, kStruct)))))
	StoreVarInst(Address(fConst180, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst181, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst182, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst155, kStruct)))))
	StoreVarInst(Address(fConst183, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst184, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst185, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst152, kStruct)))))
	StoreVarInst(Address(fConst186, kStruct), FunCallInst("tanf", BinopInst("/", Float(4986.9673f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst187, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst186, kStruct))))
	StoreVarInst(Address(fConst188, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst189, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst186, kStruct))))
	StoreVarInst(Address(fConst190, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst191, kStruct), BinopInst("+", LoadVarInst(Address(fConst190, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst192, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst193, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst194, kStruct), BinopInst("+", LoadVarInst(Address(fConst193, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst195, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst186, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst196, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst197, kStruct), BinopInst("+", LoadVarInst(Address(fConst196, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst198, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst199, kStruct), BinopInst("+", LoadVarInst(Address(fConst177, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst200, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst201, kStruct), BinopInst("+", LoadVarInst(Address(fConst177, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst202, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst203, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst151, kStruct))))
	StoreVarInst(Address(fConst204, kStruct), BinopInst("+", LoadVarInst(Address(fConst203, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst205, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst206, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst207, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst203, kStruct)))))
	StoreVarInst(Address(fConst208, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst148, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst209, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst210, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst211, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst149, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst148, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst212, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst213, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst214, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst186, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst215, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst216, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst217, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst196, kStruct)))))
	StoreVarInst(Address(fConst218, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst219, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst220, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst193, kStruct)))))
	StoreVarInst(Address(fConst221, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst222, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst223, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst190, kStruct)))))
	StoreVarInst(Address(fConst224, kStruct), FunCallInst("tanf", BinopInst("/", Float(3141.5928f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst225, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst226, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst227, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst228, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst229, kStruct), BinopInst("+", LoadVarInst(Address(fConst228, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst230, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst231, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst232, kStruct), BinopInst("+", LoadVarInst(Address(fConst231, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst233, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst224, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst234, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst235, kStruct), BinopInst("+", LoadVarInst(Address(fConst234, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst236, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst237, kStruct), BinopInst("+", LoadVarInst(Address(fConst215, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst238, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst239, kStruct), BinopInst("+", LoadVarInst(Address(fConst215, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst240, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst241, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst189, kStruct))))
	StoreVarInst(Address(fConst242, kStruct), BinopInst("+", LoadVarInst(Address(fConst241, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst243, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst244, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst245, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst241, kStruct)))))
	StoreVarInst(Address(fConst246, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst186, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst247, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst248, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst249, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst187, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst186, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst250, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst251, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst215, kStruct)))))
	StoreVarInst(Address(fConst252, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst224, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst253, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst254, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst255, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst234, kStruct)))))
	StoreVarInst(Address(fConst256, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst257, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst258, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst231, kStruct)))))
	StoreVarInst(Address(fConst259, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst260, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst261, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst228, kStruct)))))
	StoreVarInst(Address(fConst262, kStruct), FunCallInst("tanf", BinopInst("/", Float(1979.0793f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst263, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst262, kStruct))))
	StoreVarInst(Address(fConst264, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst265, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst262, kStruct))))
	StoreVarInst(Address(fConst266, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst267, kStruct), BinopInst("+", LoadVarInst(Address(fConst266, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst268, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst269, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst270, kStruct), BinopInst("+", LoadVarInst(Address(fConst269, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst271, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst262, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst272, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst273, kStruct), BinopInst("+", LoadVarInst(Address(fConst272, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst274, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst275, kStruct), BinopInst("+", LoadVarInst(Address(fConst253, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst276, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst277, kStruct), BinopInst("+", LoadVarInst(Address(fConst253, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst278, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst279, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst280, kStruct), BinopInst("+", LoadVarInst(Address(fConst279, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst281, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst282, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst283, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst279, kStruct)))))
	StoreVarInst(Address(fConst284, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst224, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst285, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst286, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst287, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst224, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst288, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst289, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst253, kStruct)))))
	StoreVarInst(Address(fConst290, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst262, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst291, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst292, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst293, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst272, kStruct)))))
	StoreVarInst(Address(fConst294, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst295, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst296, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst269, kStruct)))))
	StoreVarInst(Address(fConst297, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst298, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst299, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst266, kStruct)))))
	StoreVarInst(Address(fConst300, kStruct), FunCallInst("tanf", BinopInst("/", Float(1246.7418f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst301, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst300, kStruct))))
	StoreVarInst(Address(fConst302, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst303, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst300, kStruct))))
	StoreVarInst(Address(fConst304, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst305, kStruct), BinopInst("+", LoadVarInst(Address(fConst304, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst306, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst307, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst308, kStruct), BinopInst("+", LoadVarInst(Address(fConst307, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst309, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst300, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst310, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst311, kStruct), BinopInst("+", LoadVarInst(Address(fConst310, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst312, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst313, kStruct), BinopInst("+", LoadVarInst(Address(fConst291, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst314, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst315, kStruct), BinopInst("+", LoadVarInst(Address(fConst291, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst316, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst317, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst265, kStruct))))
	StoreVarInst(Address(fConst318, kStruct), BinopInst("+", LoadVarInst(Address(fConst317, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst319, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst320, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst321, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst317, kStruct)))))
	StoreVarInst(Address(fConst322, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst262, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst323, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst324, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst325, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst263, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst262, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst326, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst327, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst291, kStruct)))))
	StoreVarInst(Address(fConst328, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst300, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst329, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst330, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst331, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst310, kStruct)))))
	StoreVarInst(Address(fConst332, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst333, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst334, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst307, kStruct)))))
	StoreVarInst(Address(fConst335, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst336, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst337, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst304, kStruct)))))
	StoreVarInst(Address(fConst338, kStruct), FunCallInst("tanf", BinopInst("/", Float(785.3982f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst339, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst338, kStruct))))
	StoreVarInst(Address(fConst340, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst341, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst338, kStruct))))
	StoreVarInst(Address(fConst342, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst343, kStruct), BinopInst("+", LoadVarInst(Address(fConst342, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst344, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst345, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst346, kStruct), BinopInst("+", LoadVarInst(Address(fConst345, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst347, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst338, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst348, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst349, kStruct), BinopInst("+", LoadVarInst(Address(fConst348, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst350, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst351, kStruct), BinopInst("+", LoadVarInst(Address(fConst329, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst352, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst353, kStruct), BinopInst("+", LoadVarInst(Address(fConst329, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst354, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst355, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst303, kStruct))))
	StoreVarInst(Address(fConst356, kStruct), BinopInst("+", LoadVarInst(Address(fConst355, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst357, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst358, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst359, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst355, kStruct)))))
	StoreVarInst(Address(fConst360, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst300, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst361, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst362, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst363, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst301, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst300, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst364, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst365, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst329, kStruct)))))
	StoreVarInst(Address(fConst366, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst338, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst367, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst368, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst369, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst348, kStruct)))))
	StoreVarInst(Address(fConst370, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst371, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst372, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst345, kStruct)))))
	StoreVarInst(Address(fConst373, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst374, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst375, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst342, kStruct)))))
	StoreVarInst(Address(fConst376, kStruct), FunCallInst("tanf", BinopInst("/", Float(494.76984f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst377, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst378, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst379, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst380, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst381, kStruct), BinopInst("+", LoadVarInst(Address(fConst380, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst382, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst383, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst384, kStruct), BinopInst("+", LoadVarInst(Address(fConst383, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst385, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst376, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst386, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst387, kStruct), BinopInst("+", LoadVarInst(Address(fConst386, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst388, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst389, kStruct), BinopInst("+", LoadVarInst(Address(fConst367, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst390, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst391, kStruct), BinopInst("+", LoadVarInst(Address(fConst367, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst392, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst393, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst394, kStruct), BinopInst("+", LoadVarInst(Address(fConst393, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst395, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst396, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst397, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst393, kStruct)))))
	StoreVarInst(Address(fConst398, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst338, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst399, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst400, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst401, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst338, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst402, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst403, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst367, kStruct)))))
	StoreVarInst(Address(fConst404, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst376, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst405, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst406, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst407, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst386, kStruct)))))
	StoreVarInst(Address(fConst408, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst409, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst410, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst383, kStruct)))))
	StoreVarInst(Address(fConst411, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst412, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst413, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst380, kStruct)))))
	StoreVarInst(Address(fConst414, kStruct), FunCallInst("tanf", BinopInst("/", Float(311.68546f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst415, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst414, kStruct))))
	StoreVarInst(Address(fConst416, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst417, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst414, kStruct))))
	StoreVarInst(Address(fConst418, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst419, kStruct), BinopInst("+", LoadVarInst(Address(fConst418, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst420, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst421, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst422, kStruct), BinopInst("+", LoadVarInst(Address(fConst421, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst423, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst414, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst424, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst425, kStruct), BinopInst("+", LoadVarInst(Address(fConst424, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst426, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst427, kStruct), BinopInst("+", LoadVarInst(Address(fConst405, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst428, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst429, kStruct), BinopInst("+", LoadVarInst(Address(fConst405, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst430, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst431, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst379, kStruct))))
	StoreVarInst(Address(fConst432, kStruct), BinopInst("+", LoadVarInst(Address(fConst431, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst433, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst434, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst435, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst431, kStruct)))))
	StoreVarInst(Address(fConst436, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst376, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst437, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst438, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst439, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst377, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst376, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst440, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst441, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst405, kStruct)))))
	StoreVarInst(Address(fConst442, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst414, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst443, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst444, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst445, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst424, kStruct)))))
	StoreVarInst(Address(fConst446, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst447, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst448, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst421, kStruct)))))
	StoreVarInst(Address(fConst449, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst450, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst451, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst418, kStruct)))))
	StoreVarInst(Address(fConst452, kStruct), FunCallInst("tanf", BinopInst("/", Float(196.34955f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst453, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst452, kStruct))))
	StoreVarInst(Address(fConst454, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst455, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst452, kStruct))))
	StoreVarInst(Address(fConst456, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst457, kStruct), BinopInst("+", LoadVarInst(Address(fConst456, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst458, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst459, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst460, kStruct), BinopInst("+", LoadVarInst(Address(fConst459, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst461, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst452, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst462, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst463, kStruct), BinopInst("+", LoadVarInst(Address(fConst462, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst464, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst465, kStruct), BinopInst("+", LoadVarInst(Address(fConst443, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst466, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst467, kStruct), BinopInst("+", LoadVarInst(Address(fConst443, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst468, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst469, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst470, kStruct), BinopInst("+", LoadVarInst(Address(fConst469, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst471, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst472, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst473, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst469, kStruct)))))
	StoreVarInst(Address(fConst474, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst414, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst475, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst476, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst477, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst414, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst478, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst479, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst443, kStruct)))))
	StoreVarInst(Address(fConst480, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst452, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst481, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst482, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst483, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst462, kStruct)))))
	StoreVarInst(Address(fConst484, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst485, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst486, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst459, kStruct)))))
	StoreVarInst(Address(fConst487, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst488, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst489, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst456, kStruct)))))
	StoreVarInst(Address(fConst490, kStruct), FunCallInst("tanf", BinopInst("/", Float(123.69246f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst491, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst490, kStruct))))
	StoreVarInst(Address(fConst492, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.15748216f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.9351402f))))
	StoreVarInst(Address(fConst493, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst490, kStruct))))
	StoreVarInst(Address(fConst494, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst495, kStruct), BinopInst("+", LoadVarInst(Address(fConst494, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst496, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.74313045f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.4500711f))))
	StoreVarInst(Address(fConst497, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst498, kStruct), BinopInst("+", LoadVarInst(Address(fConst497, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst499, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(3.1897273f)), LoadVarInst(Address(fConst490, kStruct))), Float(4.0767817f))))
	StoreVarInst(Address(fConst500, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst501, kStruct), BinopInst("+", LoadVarInst(Address(fConst500, kStruct)), Float(0.0004076782f)))
	StoreVarInst(Address(fConst502, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst503, kStruct), BinopInst("+", LoadVarInst(Address(fConst481, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst504, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst505, kStruct), BinopInst("+", LoadVarInst(Address(fConst481, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst506, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst507, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst455, kStruct))))
	StoreVarInst(Address(fConst508, kStruct), BinopInst("+", LoadVarInst(Address(fConst507, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst509, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst510, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst511, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst507, kStruct)))))
	StoreVarInst(Address(fConst512, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst452, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst513, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst514, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst515, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst453, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst452, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst516, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst517, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst518, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-3.1897273f)), LoadVarInst(Address(fConst490, kStruct))), Float(4.0767817f)))
	StoreVarInst(Address(fConst519, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst520, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst521, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst500, kStruct)))))
	StoreVarInst(Address(fConst522, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.74313045f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.4500711f)))
	StoreVarInst(Address(fConst523, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst524, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst497, kStruct)))))
	StoreVarInst(Address(fConst525, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.15748216f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.9351402f)))
	StoreVarInst(Address(fConst526, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst527, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst494, kStruct)))))
	StoreVarInst(Address(fConst528, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.16840488f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.0693583f))))
	StoreVarInst(Address(fConst529, kStruct), BinopInst("+", LoadVarInst(Address(fConst519, kStruct)), Float(53.53615f)))
	StoreVarInst(Address(fConst530, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.51247865f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.6896214f))))
	StoreVarInst(Address(fConst531, kStruct), BinopInst("+", LoadVarInst(Address(fConst519, kStruct)), Float(7.6217313f)))
	StoreVarInst(Address(fConst532, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(0.78241307f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.2452915f))))
	StoreVarInst(Address(fConst533, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst493, kStruct))))
	StoreVarInst(Address(fConst534, kStruct), BinopInst("+", LoadVarInst(Address(fConst533, kStruct)), Float(0.0004332272f)))
	StoreVarInst(Address(fConst535, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.78241307f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.2452915f)))
	StoreVarInst(Address(fConst536, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst537, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst533, kStruct)))))
	StoreVarInst(Address(fConst538, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.51247865f)), LoadVarInst(Address(fConst490, kStruct))), Float(0.6896214f)))
	StoreVarInst(Address(fConst539, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst540, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst541, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst491, kStruct)), Float(-0.16840488f)), LoadVarInst(Address(fConst490, kStruct))), Float(1.0693583f)))
	StoreVarInst(Address(fConst542, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fConst543, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst519, kStruct)))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(5e+01f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(25.0f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(-2e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.1f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(-0.1f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.1f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.9f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(4))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(4096))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(4096))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(4096))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(4096))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(4096))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4096))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec24, kStruct)[LoadVarInst(Address(l48, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(3))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(3))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(3))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(3))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(3))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(3))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(3))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(3))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(3))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(3))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(2))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(3))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec46, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(3))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(3))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(3))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(3))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(3))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(2))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(3))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec53, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(3))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec52, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(3))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec51, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(3))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec50, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(3))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec49, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(3))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec48, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec47, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(3))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec60, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(3))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec59, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(3))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec58, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(3))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec57, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(3))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec56, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(3))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec55, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(2))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec54, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(3))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec67, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(3))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec66, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(3))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec65, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(3))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec64, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(3))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec63, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(3))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec62, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l99, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l99, kLoop)), Int32(2))
		StoreVarInst(Address(l99, kLoop), BinopInst("+", LoadVarInst(Address(l99, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec61, kStruct)[LoadVarInst(Address(l99, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l100, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l100, kLoop)), Int32(3))
		StoreVarInst(Address(l100, kLoop), BinopInst("+", LoadVarInst(Address(l100, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec74, kStruct)[LoadVarInst(Address(l100, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l101, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l101, kLoop)), Int32(3))
		StoreVarInst(Address(l101, kLoop), BinopInst("+", LoadVarInst(Address(l101, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec73, kStruct)[LoadVarInst(Address(l101, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l102, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l102, kLoop)), Int32(3))
		StoreVarInst(Address(l102, kLoop), BinopInst("+", LoadVarInst(Address(l102, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec72, kStruct)[LoadVarInst(Address(l102, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l103, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l103, kLoop)), Int32(3))
		StoreVarInst(Address(l103, kLoop), BinopInst("+", LoadVarInst(Address(l103, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec71, kStruct)[LoadVarInst(Address(l103, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l104, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l104, kLoop)), Int32(3))
		StoreVarInst(Address(l104, kLoop), BinopInst("+", LoadVarInst(Address(l104, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec70, kStruct)[LoadVarInst(Address(l104, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l105, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l105, kLoop)), Int32(3))
		StoreVarInst(Address(l105, kLoop), BinopInst("+", LoadVarInst(Address(l105, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec69, kStruct)[LoadVarInst(Address(l105, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l106, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l106, kLoop)), Int32(2))
		StoreVarInst(Address(l106, kLoop), BinopInst("+", LoadVarInst(Address(l106, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec68, kStruct)[LoadVarInst(Address(l106, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l107, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l107, kLoop)), Int32(3))
		StoreVarInst(Address(l107, kLoop), BinopInst("+", LoadVarInst(Address(l107, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec81, kStruct)[LoadVarInst(Address(l107, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l108, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l108, kLoop)), Int32(3))
		StoreVarInst(Address(l108, kLoop), BinopInst("+", LoadVarInst(Address(l108, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec80, kStruct)[LoadVarInst(Address(l108, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l109, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l109, kLoop)), Int32(3))
		StoreVarInst(Address(l109, kLoop), BinopInst("+", LoadVarInst(Address(l109, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec79, kStruct)[LoadVarInst(Address(l109, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l110, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l110, kLoop)), Int32(3))
		StoreVarInst(Address(l110, kLoop), BinopInst("+", LoadVarInst(Address(l110, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec78, kStruct)[LoadVarInst(Address(l110, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l111, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l111, kLoop)), Int32(3))
		StoreVarInst(Address(l111, kLoop), BinopInst("+", LoadVarInst(Address(l111, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec77, kStruct)[LoadVarInst(Address(l111, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l112, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l112, kLoop)), Int32(3))
		StoreVarInst(Address(l112, kLoop), BinopInst("+", LoadVarInst(Address(l112, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec76, kStruct)[LoadVarInst(Address(l112, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l113, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l113, kLoop)), Int32(2))
		StoreVarInst(Address(l113, kLoop), BinopInst("+", LoadVarInst(Address(l113, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec75, kStruct)[LoadVarInst(Address(l113, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l114, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l114, kLoop)), Int32(3))
		StoreVarInst(Address(l114, kLoop), BinopInst("+", LoadVarInst(Address(l114, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec88, kStruct)[LoadVarInst(Address(l114, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l115, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l115, kLoop)), Int32(3))
		StoreVarInst(Address(l115, kLoop), BinopInst("+", LoadVarInst(Address(l115, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec87, kStruct)[LoadVarInst(Address(l115, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l116, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l116, kLoop)), Int32(3))
		StoreVarInst(Address(l116, kLoop), BinopInst("+", LoadVarInst(Address(l116, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec86, kStruct)[LoadVarInst(Address(l116, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l117, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l117, kLoop)), Int32(3))
		StoreVarInst(Address(l117, kLoop), BinopInst("+", LoadVarInst(Address(l117, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec85, kStruct)[LoadVarInst(Address(l117, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l118, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l118, kLoop)), Int32(3))
		StoreVarInst(Address(l118, kLoop), BinopInst("+", LoadVarInst(Address(l118, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec84, kStruct)[LoadVarInst(Address(l118, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l119, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l119, kLoop)), Int32(3))
		StoreVarInst(Address(l119, kLoop), BinopInst("+", LoadVarInst(Address(l119, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec83, kStruct)[LoadVarInst(Address(l119, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l120, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l120, kLoop)), Int32(2))
		StoreVarInst(Address(l120, kLoop), BinopInst("+", LoadVarInst(Address(l120, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec82, kStruct)[LoadVarInst(Address(l120, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l121, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l121, kLoop)), Int32(3))
		StoreVarInst(Address(l121, kLoop), BinopInst("+", LoadVarInst(Address(l121, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec95, kStruct)[LoadVarInst(Address(l121, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l122, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l122, kLoop)), Int32(3))
		StoreVarInst(Address(l122, kLoop), BinopInst("+", LoadVarInst(Address(l122, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec94, kStruct)[LoadVarInst(Address(l122, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l123, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l123, kLoop)), Int32(3))
		StoreVarInst(Address(l123, kLoop), BinopInst("+", LoadVarInst(Address(l123, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec93, kStruct)[LoadVarInst(Address(l123, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l124, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l124, kLoop)), Int32(3))
		StoreVarInst(Address(l124, kLoop), BinopInst("+", LoadVarInst(Address(l124, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec92, kStruct)[LoadVarInst(Address(l124, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l125, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l125, kLoop)), Int32(3))
		StoreVarInst(Address(l125, kLoop), BinopInst("+", LoadVarInst(Address(l125, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec91, kStruct)[LoadVarInst(Address(l125, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l126, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l126, kLoop)), Int32(3))
		StoreVarInst(Address(l126, kLoop), BinopInst("+", LoadVarInst(Address(l126, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec90, kStruct)[LoadVarInst(Address(l126, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l127, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l127, kLoop)), Int32(2))
		StoreVarInst(Address(l127, kLoop), BinopInst("+", LoadVarInst(Address(l127, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec89, kStruct)[LoadVarInst(Address(l127, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l128, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l128, kLoop)), Int32(3))
		StoreVarInst(Address(l128, kLoop), BinopInst("+", LoadVarInst(Address(l128, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec102, kStruct)[LoadVarInst(Address(l128, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l129, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l129, kLoop)), Int32(3))
		StoreVarInst(Address(l129, kLoop), BinopInst("+", LoadVarInst(Address(l129, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec101, kStruct)[LoadVarInst(Address(l129, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l130, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l130, kLoop)), Int32(3))
		StoreVarInst(Address(l130, kLoop), BinopInst("+", LoadVarInst(Address(l130, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec100, kStruct)[LoadVarInst(Address(l130, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l131, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l131, kLoop)), Int32(3))
		StoreVarInst(Address(l131, kLoop), BinopInst("+", LoadVarInst(Address(l131, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec99, kStruct)[LoadVarInst(Address(l131, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l132, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l132, kLoop)), Int32(3))
		StoreVarInst(Address(l132, kLoop), BinopInst("+", LoadVarInst(Address(l132, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec98, kStruct)[LoadVarInst(Address(l132, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l133, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l133, kLoop)), Int32(3))
		StoreVarInst(Address(l133, kLoop), BinopInst("+", LoadVarInst(Address(l133, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec97, kStruct)[LoadVarInst(Address(l133, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l134, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l134, kLoop)), Int32(2))
		StoreVarInst(Address(l134, kLoop), BinopInst("+", LoadVarInst(Address(l134, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec96, kStruct)[LoadVarInst(Address(l134, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l135, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l135, kLoop)), Int32(3))
		StoreVarInst(Address(l135, kLoop), BinopInst("+", LoadVarInst(Address(l135, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec109, kStruct)[LoadVarInst(Address(l135, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l136, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l136, kLoop)), Int32(3))
		StoreVarInst(Address(l136, kLoop), BinopInst("+", LoadVarInst(Address(l136, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec108, kStruct)[LoadVarInst(Address(l136, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l137, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l137, kLoop)), Int32(3))
		StoreVarInst(Address(l137, kLoop), BinopInst("+", LoadVarInst(Address(l137, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec107, kStruct)[LoadVarInst(Address(l137, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l138, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l138, kLoop)), Int32(3))
		StoreVarInst(Address(l138, kLoop), BinopInst("+", LoadVarInst(Address(l138, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec106, kStruct)[LoadVarInst(Address(l138, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l139, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l139, kLoop)), Int32(3))
		StoreVarInst(Address(l139, kLoop), BinopInst("+", LoadVarInst(Address(l139, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec105, kStruct)[LoadVarInst(Address(l139, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l140, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l140, kLoop)), Int32(3))
		StoreVarInst(Address(l140, kLoop), BinopInst("+", LoadVarInst(Address(l140, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec104, kStruct)[LoadVarInst(Address(l140, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l141, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l141, kLoop)), Int32(2))
		StoreVarInst(Address(l141, kLoop), BinopInst("+", LoadVarInst(Address(l141, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec103, kStruct)[LoadVarInst(Address(l141, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l142, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l142, kLoop)), Int32(3))
		StoreVarInst(Address(l142, kLoop), BinopInst("+", LoadVarInst(Address(l142, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec116, kStruct)[LoadVarInst(Address(l142, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l143, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l143, kLoop)), Int32(3))
		StoreVarInst(Address(l143, kLoop), BinopInst("+", LoadVarInst(Address(l143, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec115, kStruct)[LoadVarInst(Address(l143, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l144, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l144, kLoop)), Int32(3))
		StoreVarInst(Address(l144, kLoop), BinopInst("+", LoadVarInst(Address(l144, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec114, kStruct)[LoadVarInst(Address(l144, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l145, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l145, kLoop)), Int32(3))
		StoreVarInst(Address(l145, kLoop), BinopInst("+", LoadVarInst(Address(l145, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec113, kStruct)[LoadVarInst(Address(l145, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l146, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l146, kLoop)), Int32(3))
		StoreVarInst(Address(l146, kLoop), BinopInst("+", LoadVarInst(Address(l146, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec112, kStruct)[LoadVarInst(Address(l146, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l147, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l147, kLoop)), Int32(3))
		StoreVarInst(Address(l147, kLoop), BinopInst("+", LoadVarInst(Address(l147, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec111, kStruct)[LoadVarInst(Address(l147, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l148, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l148, kLoop)), Int32(2))
		StoreVarInst(Address(l148, kLoop), BinopInst("+", LoadVarInst(Address(l148, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec110, kStruct)[LoadVarInst(Address(l148, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l149, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l149, kLoop)), Int32(3))
		StoreVarInst(Address(l149, kLoop), BinopInst("+", LoadVarInst(Address(l149, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec123, kStruct)[LoadVarInst(Address(l149, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l150, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l150, kLoop)), Int32(3))
		StoreVarInst(Address(l150, kLoop), BinopInst("+", LoadVarInst(Address(l150, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec122, kStruct)[LoadVarInst(Address(l150, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l151, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l151, kLoop)), Int32(3))
		StoreVarInst(Address(l151, kLoop), BinopInst("+", LoadVarInst(Address(l151, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec121, kStruct)[LoadVarInst(Address(l151, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l152, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l152, kLoop)), Int32(3))
		StoreVarInst(Address(l152, kLoop), BinopInst("+", LoadVarInst(Address(l152, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec120, kStruct)[LoadVarInst(Address(l152, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l153, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l153, kLoop)), Int32(3))
		StoreVarInst(Address(l153, kLoop), BinopInst("+", LoadVarInst(Address(l153, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec119, kStruct)[LoadVarInst(Address(l153, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l154, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l154, kLoop)), Int32(3))
		StoreVarInst(Address(l154, kLoop), BinopInst("+", LoadVarInst(Address(l154, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec118, kStruct)[LoadVarInst(Address(l154, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l155, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l155, kLoop)), Int32(2))
		StoreVarInst(Address(l155, kLoop), BinopInst("+", LoadVarInst(Address(l155, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec117, kStruct)[LoadVarInst(Address(l155, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l156, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l156, kLoop)), Int32(3))
		StoreVarInst(Address(l156, kLoop), BinopInst("+", LoadVarInst(Address(l156, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec127, kStruct)[LoadVarInst(Address(l156, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l157, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l157, kLoop)), Int32(3))
		StoreVarInst(Address(l157, kLoop), BinopInst("+", LoadVarInst(Address(l157, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec126, kStruct)[LoadVarInst(Address(l157, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l158, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l158, kLoop)), Int32(3))
		StoreVarInst(Address(l158, kLoop), BinopInst("+", LoadVarInst(Address(l158, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec125, kStruct)[LoadVarInst(Address(l158, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l159, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l159, kLoop)), Int32(2))
		StoreVarInst(Address(l159, kLoop), BinopInst("+", LoadVarInst(Address(l159, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec124, kStruct)[LoadVarInst(Address(l159, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, Select2Inst(BinopInst(">", BinopInst("*", Float(0.001f), LoadVarInst(Address(fSlow1, kStack))), Float(0.0f)) FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow1, kStack))))) Float(0.0f)))
	DeclareVarInst("int", iSlow3, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	DeclareVarInst("int", iSlow5, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(0.44f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider3, kStruct))), Float(-49.0f))))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(0.33333334f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))
	DeclareVarInst("int", iSlow10, kStack, CastInst("int", BinopInst("+", CastInst("float", LoadVarInst(Address(fEntry0, kStruct))), Float(-1.0f))))
	DeclareVarInst("int", iSlow11, kStack, BinopInst(">=", LoadVarInst(Address(iSlow10, kStack)), Int32(2)))
	DeclareVarInst("int", iSlow12, kStack, BinopInst(">=", LoadVarInst(Address(iSlow10, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, Select2Inst(BinopInst(">", LoadVarInst(Address(fSlow13, kStack)), Float(0.0f)) FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow13, kStack))))) Float(0.0f)))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", BinopInst("*", Float(4.4e+02f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider5, kStruct))), Float(-49.0f))))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow14, kStack)))))
	DeclareVarInst("int", iSlow16, kStack, BinopInst(">=", LoadVarInst(Address(iSlow10, kStack)), Int32(3)))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("+", BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct)))), Float(1.0f)))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), CastInst("float", LoadVarInst(Address(fVslider5, kStruct)))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), CastInst("float", LoadVarInst(Address(fVslider6, kStruct)))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider7, kStruct)))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct)))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.083333336f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow22, kStack)))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(4.0f), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fSlow27, kStack))), Float(0.999999f)))))
	DeclareVarInst("int", iSlow29, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct)))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("min_f", Float(1.4127994f), BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow30, kStack))))
	DeclareVarInst("float", fSlow32, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow30, kStack))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("+", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fSlow32, kStack))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("+", LoadVarInst(Address(fSlow31, kStack)), Float(2.0f)))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.4127994f), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("*", Float(1.998f), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("+", LoadVarInst(Address(fSlow37, kStack)), Float(2.0f)))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow37, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp0, kStack))))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow14, kStack))), LoadVarInst(Address(fSlow15, kStack))))
			DeclareVarInst("float", fTemp2, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp3, kStack)))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec12, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), Float(-1.0f)))
			DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp7, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp5, kStack))))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
			DeclareVarInst("float", fTemp8, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(2)])))
			DeclareVarInst("float", fTemp9, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp5, kStack))))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp4, kStack)))))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp2, kStack))))
			StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
			DeclareVarInst("float", fTemp11, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(3)])))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("*", LoadVarInst(Address(fTemp7, kStack)), BinopInst("+", LoadVarInst(Address(fTemp7, kStack)), Float(-2.0f))))
			StoreVarInst(Address(fVec4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp2, kStack))))
			StoreVarInst(Address(fVec5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp13, kStack)))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp13, kStack)), LoadVarInst(Address(fVec5, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp2, kStack))))
			StoreVarInst(Address(fVec6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp14, kStack)))
			DeclareVarInst("float", fTemp15, kStack, BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp16, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp15, kStack)))))
			DeclareVarInst("float", fTemp17, kStack, BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp16, kStack)))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp17, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp17, kStack)))))
			DeclareVarInst("float", fTemp18, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp19, kStack, BinopInst("+", LoadVarInst(Address(fTemp18, kStack)), Float(-1.0f)))
			DeclareVarInst("float", fTemp20, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp19, kStack))))
			StoreVarInst(Address(fVec7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp20, kStack)))
			DeclareVarInst("float", fTemp21, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp19, kStack))))
			StoreVarInst(Address(fVec8, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp21, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp18, kStack)))))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp21, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fVec8, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp16, kStack))))
			StoreVarInst(Address(fVec9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp22, kStack)))
			DeclareVarInst("float", fTemp23, kStack, BinopInst("*", LoadVarInst(Address(fTemp20, kStack)), BinopInst("+", LoadVarInst(Address(fTemp20, kStack)), Float(-2.0f))))
			StoreVarInst(Address(fVec10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp23, kStack)))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp23, kStack)), LoadVarInst(Address(fVec10, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp16, kStack))))
			StoreVarInst(Address(fVec11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fVec11, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp16, kStack))))
			StoreVarInst(Address(fVec12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
			DeclareVarInst("float", fTemp26, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp27, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp26, kStack)))))
			DeclareVarInst("float", fTemp28, kStack, BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp27, kStack)))))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp28, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp28, kStack)))))
			DeclareVarInst("float", fTemp29, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp30, kStack, BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), Float(-1.0f)))
			DeclareVarInst("float", fTemp31, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp30, kStack))))
			StoreVarInst(Address(fVec13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp31, kStack)))
			DeclareVarInst("float", fTemp32, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp30, kStack))))
			StoreVarInst(Address(fVec14, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp29, kStack)))))
			DeclareVarInst("float", fTemp33, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fVec14, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp27, kStack))))
			StoreVarInst(Address(fVec15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp33, kStack)))
			DeclareVarInst("float", fTemp34, kStack, BinopInst("*", LoadVarInst(Address(fTemp31, kStack)), BinopInst("+", LoadVarInst(Address(fTemp31, kStack)), Float(-2.0f))))
			StoreVarInst(Address(fVec16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp34, kStack)))
			DeclareVarInst("float", fTemp35, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fVec16, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp27, kStack))))
			StoreVarInst(Address(fVec17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp35, kStack)))
			DeclareVarInst("float", fTemp36, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp35, kStack)), LoadVarInst(Address(fVec17, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp27, kStack))))
			StoreVarInst(Address(fVec18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp36, kStack)))
			DeclareVarInst("float", fTemp37, kStack, FunCallInst("max_f", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), Float(23.44895f)))
			DeclareVarInst("float", fTemp38, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp37, kStack)))))
			DeclareVarInst("float", fTemp39, kStack, BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp38, kStack)))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp39, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp39, kStack)))))
			DeclareVarInst("float", fTemp40, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp41, kStack, BinopInst("+", LoadVarInst(Address(fTemp40, kStack)), Float(-1.0f)))
			DeclareVarInst("float", fTemp42, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp41, kStack))))
			StoreVarInst(Address(fVec19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp42, kStack)))
			DeclareVarInst("float", fTemp43, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp38, kStack))))
			StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp43, kStack)))
			DeclareVarInst("float", fTemp44, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fTemp37, kStack))))))
			DeclareVarInst("int", iTemp45, kStack, CastInst("int", LoadVarInst(Address(fTemp44, kStack))))
			DeclareVarInst("float", fTemp46, kStack, CastInst("float", LoadVarInst(Address(iTemp45, kStack))))
			DeclareVarInst("float", fTemp47, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp43, kStack)), BinopInst("*", LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp45, kStack))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp44, kStack)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp44, kStack)), LoadVarInst(Address(fTemp46, kStack))), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", LoadVarInst(Address(iTemp45, kStack)), Int32(1))), Int32(4095))]))))
			DeclareVarInst("float", fTemp48, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp15, kStack)), Float(23.44895f)))
			DeclareVarInst("float", fTemp49, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp48, kStack)))))
			DeclareVarInst("float", fTemp50, kStack, BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp49, kStack)))))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp50, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp50, kStack)))))
			DeclareVarInst("float", fTemp51, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp52, kStack, BinopInst("+", LoadVarInst(Address(fTemp51, kStack)), Float(-1.0f)))
			DeclareVarInst("float", fTemp53, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp52, kStack))))
			StoreVarInst(Address(fVec21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp53, kStack)))
			DeclareVarInst("float", fTemp54, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
			StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp54, kStack)))
			DeclareVarInst("float", fTemp55, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fTemp48, kStack))))))
			DeclareVarInst("int", iTemp56, kStack, CastInst("int", LoadVarInst(Address(fTemp55, kStack))))
			DeclareVarInst("float", fTemp57, kStack, CastInst("float", LoadVarInst(Address(iTemp56, kStack))))
			DeclareVarInst("float", fTemp58, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp56, kStack))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp57, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp55, kStack)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp55, kStack)), LoadVarInst(Address(fTemp57, kStack))), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", LoadVarInst(Address(iTemp56, kStack)), Int32(1))), Int32(4095))]))))
			DeclareVarInst("float", fTemp59, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp26, kStack)), Float(23.44895f)))
			DeclareVarInst("float", fTemp60, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp59, kStack)))))
			DeclareVarInst("float", fTemp61, kStack, BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp60, kStack)))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp61, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp61, kStack)))))
			DeclareVarInst("float", fTemp62, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp63, kStack, BinopInst("+", LoadVarInst(Address(fTemp62, kStack)), Float(-1.0f)))
			DeclareVarInst("float", fTemp64, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp63, kStack))))
			StoreVarInst(Address(fVec23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp64, kStack)))
			DeclareVarInst("float", fTemp65, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp64, kStack)), LoadVarInst(Address(fVec23, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
			StoreVarInst(Address(fVec24, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp65, kStack)))
			DeclareVarInst("float", fTemp66, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fTemp59, kStack))))))
			DeclareVarInst("int", iTemp67, kStack, CastInst("int", LoadVarInst(Address(fTemp66, kStack))))
			DeclareVarInst("float", fTemp68, kStack, CastInst("float", LoadVarInst(Address(iTemp67, kStack))))
			DeclareVarInst("float", fTemp69, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp67, kStack))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp68, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp66, kStack)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp66, kStack)), LoadVarInst(Address(fTemp68, kStack))), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", LoadVarInst(Address(iTemp67, kStack)), Int32(1))), Int32(4095))]))))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fTemp47, kStack))), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fTemp58, kStack))), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fTemp69, kStack))), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp70, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp41, kStack))))
			StoreVarInst(Address(fVec25, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp70, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp40, kStack)))))
			DeclareVarInst("float", fTemp71, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp70, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp40, kStack)), LoadVarInst(Address(fVec25, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp38, kStack))))
			StoreVarInst(Address(fVec26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp71, kStack)))
			DeclareVarInst("float", fTemp72, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp71, kStack)), LoadVarInst(Address(fVec26, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp38, kStack))))
			StoreVarInst(Address(fVec27, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp72, kStack)))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", Float(0.99f), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp73, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp37, kStack)))))))
			DeclareVarInst("int", iTemp74, kStack, CastInst("int", LoadVarInst(Address(fTemp73, kStack))))
			DeclareVarInst("float", fTemp75, kStack, CastInst("float", LoadVarInst(Address(iTemp74, kStack))))
			DeclareVarInst("float", fTemp76, kStack, BinopInst("+", LoadVarInst(Address(fTemp75, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp73, kStack)))))
			DeclareVarInst("float", fTemp77, kStack, BinopInst("-", LoadVarInst(Address(fTemp73, kStack)), LoadVarInst(Address(fTemp75, kStack))))
			DeclareVarInst("int", iTemp78, kStack, BinopInst("+", LoadVarInst(Address(iTemp74, kStack)), Int32(1)))
			DeclareVarInst("float", fTemp79, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp52, kStack))))
			StoreVarInst(Address(fVec28, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp79, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp51, kStack)))))
			DeclareVarInst("float", fTemp80, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp79, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp51, kStack)), LoadVarInst(Address(fVec28, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp49, kStack))))
			StoreVarInst(Address(fVec29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp80, kStack)))
			DeclareVarInst("float", fTemp81, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp80, kStack)), LoadVarInst(Address(fVec29, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
			StoreVarInst(Address(fVec30, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp81, kStack)))
			DeclareVarInst("float", fTemp82, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp48, kStack)))))))
			DeclareVarInst("int", iTemp83, kStack, CastInst("int", LoadVarInst(Address(fTemp82, kStack))))
			DeclareVarInst("float", fTemp84, kStack, CastInst("float", LoadVarInst(Address(iTemp83, kStack))))
			DeclareVarInst("float", fTemp85, kStack, BinopInst("+", LoadVarInst(Address(fTemp84, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp82, kStack)))))
			DeclareVarInst("float", fTemp86, kStack, BinopInst("-", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp84, kStack))))
			DeclareVarInst("int", iTemp87, kStack, BinopInst("+", LoadVarInst(Address(iTemp83, kStack)), Int32(1)))
			DeclareVarInst("float", fTemp88, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp63, kStack))))
			StoreVarInst(Address(fVec31, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp88, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp62, kStack)))))
			DeclareVarInst("float", fTemp89, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fTemp88, kStack)), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp62, kStack)), LoadVarInst(Address(fVec31, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp60, kStack))))
			StoreVarInst(Address(fVec32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp89, kStack)))
			DeclareVarInst("float", fTemp90, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp89, kStack)), LoadVarInst(Address(fVec32, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
			StoreVarInst(Address(fVec33, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp90, kStack)))
			DeclareVarInst("float", fTemp91, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp59, kStack)))))))
			DeclareVarInst("int", iTemp92, kStack, CastInst("int", LoadVarInst(Address(fTemp91, kStack))))
			DeclareVarInst("float", fTemp93, kStack, CastInst("float", LoadVarInst(Address(iTemp92, kStack))))
			DeclareVarInst("float", fTemp94, kStack, BinopInst("+", LoadVarInst(Address(fTemp93, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp91, kStack)))))
			DeclareVarInst("float", fTemp95, kStack, BinopInst("-", LoadVarInst(Address(fTemp91, kStack)), LoadVarInst(Address(fTemp93, kStack))))
			DeclareVarInst("int", iTemp96, kStack, BinopInst("+", LoadVarInst(Address(iTemp92, kStack)), Int32(1)))
			StoreVarInst(Address(iRec24, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec24, kStruct)[Int32(1)])), Int32(12345)))
			StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fRec23, kStruct)[Int32(3)])), BinopInst("+", BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iRec24, kStruct)[Int32(0)]))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(Address(fRec23, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp97, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", LoadVarInst(Address(fRec11, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(Address(iSlow11, kStack)) Select2Inst(LoadVarInst(Address(iSlow16, kStack)) BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fVec6, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp2, kStack)))) BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp2, kStack))))) Select2Inst(LoadVarInst(Address(iSlow12, kStack)) BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp2, kStack)))) LoadVarInst(Address(fTemp5, kStack)))), Select2Inst(LoadVarInst(Address(iSlow11, kStack)) Select2Inst(LoadVarInst(Address(iSlow16, kStack)) BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fVec12, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp16, kStack)))) BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fVec9, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp16, kStack))))) Select2Inst(LoadVarInst(Address(iSlow12, kStack)) BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fVec7, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp16, kStack)))) LoadVarInst(Address(fTemp19, kStack))))), Select2Inst(LoadVarInst(Address(iSlow11, kStack)) Select2Inst(LoadVarInst(Address(iSlow16, kStack)) BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp27, kStack)))) BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp8, kStack)), BinopInst("-", LoadVarInst(Address(fTemp33, kStack)), LoadVarInst(Address(fVec15, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp27, kStack))))) Select2Inst(LoadVarInst(Address(iSlow12, kStack)) BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fVec13, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp27, kStack)))) LoadVarInst(Address(fTemp30, kStack)))))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp47, kStack)), LoadVarInst(Address(fTemp58, kStack))), LoadVarInst(Address(fTemp69, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)])))))), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp72, kStack)), BinopInst("*", LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp74, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp76, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp77, kStack)), LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp78, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp81, kStack)), BinopInst("*", LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp83, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp85, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp87, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp90, kStack)), BinopInst("*", LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp92, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp94, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp95, kStack)), LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp96, kStack))), Int32(4095))]))))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp43, kStack)), BinopInst("*", LoadVarInst(Address(fTemp76, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp74, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp77, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp78, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fTemp85, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp83, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp87, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fTemp94, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp92, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp95, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp96, kStack))), Int32(4095))])))))))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("-", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fRec23, kStruct)[Int32(0)])), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fRec23, kStruct)[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.095993534f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])), BinopInst("*", Float(0.004408786f), LoadVarInst(Address(fRec23, kStruct)[Int32(3)])))))))))
			DeclareVarInst("float", fTemp98, kStack, Select2Inst(LoadVarInst(Address(iSlow3, kStack)) Float(0.0f) LoadVarInst(Address(fTemp97, kStack))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp98, kStack))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp1, kStack)))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fTemp0, kStack)))))
			DeclareVarInst("float", fTemp99, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1e+04f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp100, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp99, kStack))))
			DeclareVarInst("float", fTemp101, kStack, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp99, kStack))))))
			DeclareVarInst("float", fTemp102, kStack, BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp100, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f))))
			StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp98, kStack)), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec26, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp100, kStack)), LoadVarInst(Address(fSlow34, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f)))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fTemp101, kStack)))))), LoadVarInst(Address(fTemp102, kStack)))))
			DeclareVarInst("float", fTemp103, kStack, BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fTemp100, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow31, kStack)))))
			StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("-", BinopInst("/", BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp102, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec25, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp100, kStack)), LoadVarInst(Address(fSlow35, kStack))), LoadVarInst(Address(fTemp99, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow31, kStack))))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec25, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fSlow32, kStack)), BinopInst("-", LoadVarInst(Address(fTemp101, kStack)), LoadVarInst(Address(fSlow31, kStack))))))), LoadVarInst(Address(fTemp103, kStack)))))
			DeclareVarInst("float", fTemp104, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), FunCallInst("max_f", LoadVarInst(Address(fRec10, kStruct)[Int32(0)]), Float(2e+01f)))))
			DeclareVarInst("float", fTemp105, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp104, kStack))))
			DeclareVarInst("float", fTemp106, kStack, BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp105, kStack))), LoadVarInst(Address(fTemp104, kStack))), Float(1.0f))))
			DeclareVarInst("float", fTemp107, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), BinopInst("-", Float(1.0f), BinopInst("/", BinopInst("-", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp105, kStack))), LoadVarInst(Address(fTemp104, kStack))))), LoadVarInst(Address(fTemp106, kStack))))
			DeclareVarInst("float", fTemp108, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp107, kStack)))))
			DeclareVarInst("float", fTemp109, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp108, kStack)))))
			DeclareVarInst("float", fTemp110, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp109, kStack)))))
			DeclareVarInst("float", fTemp111, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp98, kStack)), LoadVarInst(Address(fTemp110, kStack))), BinopInst("*", LoadVarInst(Address(fTemp108, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp112, kStack, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp104, kStack))))))
			DeclareVarInst("float", fTemp113, kStack, BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp112, kStack))))
			DeclareVarInst("float", fTemp114, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp113, kStack)), BinopInst("*", LoadVarInst(Address(fTemp106, kStack)), BinopInst("+", LoadVarInst(Address(fTemp107, kStack)), Float(1.0f))))))))
			DeclareVarInst("float", fTemp115, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp114, kStack)))))
			DeclareVarInst("float", fTemp116, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp115, kStack)))))
			StoreVarInst(Address(fRec29, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp111, kStack)), LoadVarInst(Address(fTemp116, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114, kStack)), LoadVarInst(Address(fRec29, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec27, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111, kStack)), LoadVarInst(Address(fTemp114, kStack))), BinopInst("*", LoadVarInst(Address(fRec29, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp116, kStack)))))
			DeclareVarInst("float", fRec28, kStack, LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
			DeclareVarInst("float", fTemp117, kStack, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(Address(fTemp113, kStack)), LoadVarInst(Address(fTemp106, kStack)))))
			DeclareVarInst("float", fTemp118, kStack, FunCallInst("sqrtf", LoadVarInst(Address(fTemp109, kStack))))
			DeclareVarInst("float", fTemp119, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp98, kStack)), LoadVarInst(Address(fTemp108, kStack))), BinopInst("*", LoadVarInst(Address(fRec27, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp110, kStack)))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec27, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp117, kStack))), LoadVarInst(Address(fTemp118, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec28, kStack)), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp107, kStack))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fTemp114, kStack)), LoadVarInst(Address(fTemp117, kStack)))))), BinopInst("*", LoadVarInst(Address(fTemp118, kStack)), FunCallInst("sqrtf", LoadVarInst(Address(fTemp115, kStack)))))))
			DeclareVarInst("float", fTemp120, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp105, kStack))), LoadVarInst(Address(fTemp104, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow37, kStack)))))
			DeclareVarInst("float", fTemp121, kStack, BinopInst("/", BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp105, kStack)), LoadVarInst(Address(fSlow40, kStack))), LoadVarInst(Address(fTemp104, kStack))), Float(1.0f)), LoadVarInst(Address(fSlow37, kStack)))), LoadVarInst(Address(fTemp120, kStack))))
			DeclareVarInst("float", fTemp122, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp121, kStack)))))
			DeclareVarInst("float", fTemp123, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp122, kStack)))))
			DeclareVarInst("float", fTemp124, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp123, kStack)))))
			DeclareVarInst("float", fTemp125, kStack, BinopInst("-", BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp119, kStack)), LoadVarInst(Address(fTemp124, kStack))), LoadVarInst(Address(fTemp106, kStack))), BinopInst("*", LoadVarInst(Address(fTemp122, kStack)), LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp126, kStack, BinopInst("+", LoadVarInst(Address(fSlow36, kStack)), BinopInst("-", LoadVarInst(Address(fTemp112, kStack)), LoadVarInst(Address(fSlow37, kStack)))))
			DeclareVarInst("float", fTemp127, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp126, kStack)), BinopInst("*", LoadVarInst(Address(fTemp120, kStack)), BinopInst("+", LoadVarInst(Address(fTemp121, kStack)), Float(1.0f))))))))
			DeclareVarInst("float", fTemp128, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp127, kStack)))))
			DeclareVarInst("float", fTemp129, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp128, kStack)))))
			StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp125, kStack)), LoadVarInst(Address(fTemp129, kStack))), BinopInst("*", LoadVarInst(Address(fTemp127, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec30, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp125, kStack)), LoadVarInst(Address(fTemp127, kStack))), BinopInst("*", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp129, kStack)))))
			DeclareVarInst("float", fRec31, kStack, LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			DeclareVarInst("float", fTemp130, kStack, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(Address(fTemp126, kStack)), LoadVarInst(Address(fTemp120, kStack)))))
			DeclareVarInst("float", fTemp131, kStack, FunCallInst("sqrtf", LoadVarInst(Address(fTemp123, kStack))))
			DeclareVarInst("float", fTemp132, kStack, Select2Inst(LoadVarInst(Address(iSlow3, kStack)) LoadVarInst(Address(fTemp97, kStack)) BinopInst("*", LoadVarInst(Address(fRec4, kStruct)[Int32(0)]), Select2Inst(LoadVarInst(Address(iSlow5, kStack)) Select2Inst(LoadVarInst(Address(iSlow29, kStack)) BinopInst("/", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp119, kStack)), LoadVarInst(Address(fTemp122, kStack))), LoadVarInst(Address(fTemp106, kStack))), BinopInst("*", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp124, kStack)))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec30, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp130, kStack))), LoadVarInst(Address(fTemp131, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec31, kStack)), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp121, kStack))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fTemp127, kStack)), LoadVarInst(Address(fTemp130, kStack)))))), BinopInst("*", LoadVarInst(Address(fTemp131, kStack)), FunCallInst("sqrtf", LoadVarInst(Address(fTemp128, kStack)))))), LoadVarInst(Address(fTemp120, kStack))) BinopInst("/", BinopInst("+", LoadVarInst(Address(fRec25, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec25, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec25, kStruct)[Int32(1)])))), LoadVarInst(Address(fTemp103, kStack)))) LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp132, kStack)), BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst26, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst31, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack))), BinopInst("*", FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst33, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)]))))), LoadVarInst(Address(fSlow41, kStack)))))
			StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp132, kStack)), BinopInst("*", LoadVarInst(Address(fConst50, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst53, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst54, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst50, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst55, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fRec39, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst56, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst57, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst58, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst46, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst59, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst60, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp133, kStack, BinopInst("*", LoadVarInst(Address(fConst46, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst47, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst61, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst47, kStruct)), LoadVarInst(Address(fRec37, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp133, kStack)), BinopInst("*", LoadVarInst(Address(fConst43, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst62, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst64, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst43, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst65, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fRec36, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst66, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst67, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst68, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fRec35, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst36, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst69, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst70, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst36, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst71, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fRec34, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec46, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp133, kStack)), BinopInst("*", LoadVarInst(Address(fConst88, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst91, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst92, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst88, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst90, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst93, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst90, kStruct)), LoadVarInst(Address(fRec46, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst86, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst94, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst95, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec44, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst86, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst87, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst96, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst87, kStruct)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst84, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst97, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst98, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp134, kStack, BinopInst("*", LoadVarInst(Address(fConst84, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst85, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst99, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst85, kStruct)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec43, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp134, kStack)), BinopInst("*", LoadVarInst(Address(fConst81, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst100, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst102, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst81, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst83, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst103, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst83, kStruct)), LoadVarInst(Address(fRec43, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst78, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst104, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst105, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst78, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst80, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst106, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst80, kStruct)), LoadVarInst(Address(fRec42, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst74, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst107, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst108, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec40, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec40, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst74, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst77, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst109, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst77, kStruct)), LoadVarInst(Address(fRec41, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec53, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp134, kStack)), BinopInst("*", LoadVarInst(Address(fConst126, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst129, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst130, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec52, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst126, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst128, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst131, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst128, kStruct)), LoadVarInst(Address(fRec53, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst124, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst132, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst133, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec51, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst124, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst125, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst134, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst125, kStruct)), LoadVarInst(Address(fRec52, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst122, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst135, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst136, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp135, kStack, BinopInst("*", LoadVarInst(Address(fConst122, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst123, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst137, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst123, kStruct)), LoadVarInst(Address(fRec51, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec50, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp135, kStack)), BinopInst("*", LoadVarInst(Address(fConst119, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst138, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst140, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec49, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst119, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst141, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fRec50, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst116, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst142, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst143, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec48, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst116, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst118, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst144, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst118, kStruct)), LoadVarInst(Address(fRec49, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst112, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst145, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst146, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec47, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec47, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst112, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst115, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst147, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst115, kStruct)), LoadVarInst(Address(fRec48, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec60, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp135, kStack)), BinopInst("*", LoadVarInst(Address(fConst164, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst167, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst168, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec59, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst164, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst166, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst169, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst166, kStruct)), LoadVarInst(Address(fRec60, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst162, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst170, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst171, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec58, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst162, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst163, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst172, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst163, kStruct)), LoadVarInst(Address(fRec59, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst160, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst173, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst174, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp136, kStack, BinopInst("*", LoadVarInst(Address(fConst160, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst161, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst175, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst161, kStruct)), LoadVarInst(Address(fRec58, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec57, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp136, kStack)), BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst176, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst178, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec56, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst159, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst179, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst159, kStruct)), LoadVarInst(Address(fRec57, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst154, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst180, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst181, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec55, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst154, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst156, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst182, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst156, kStruct)), LoadVarInst(Address(fRec56, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst150, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst183, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst184, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec54, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec54, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst150, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst153, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst185, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst153, kStruct)), LoadVarInst(Address(fRec55, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec54, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec67, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp136, kStack)), BinopInst("*", LoadVarInst(Address(fConst202, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst205, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst206, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec66, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst202, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst204, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst207, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst204, kStruct)), LoadVarInst(Address(fRec67, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst200, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst208, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst209, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec65, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst200, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst201, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst210, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst201, kStruct)), LoadVarInst(Address(fRec66, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst198, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst211, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst212, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp137, kStack, BinopInst("*", LoadVarInst(Address(fConst198, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst199, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst213, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst199, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec64, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp137, kStack)), BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst214, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst216, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec63, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst197, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst217, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst197, kStruct)), LoadVarInst(Address(fRec64, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst192, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst218, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst219, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec62, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst192, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst194, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst220, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst194, kStruct)), LoadVarInst(Address(fRec63, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst221, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst222, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec61, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec61, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst191, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst223, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst191, kStruct)), LoadVarInst(Address(fRec62, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec74, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp137, kStack)), BinopInst("*", LoadVarInst(Address(fConst240, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst243, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst244, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec73, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst240, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst242, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst245, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst242, kStruct)), LoadVarInst(Address(fRec74, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst246, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst247, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec72, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst239, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst248, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst239, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst236, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst249, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst250, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp138, kStack, BinopInst("*", LoadVarInst(Address(fConst236, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst237, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst251, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst237, kStruct)), LoadVarInst(Address(fRec72, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec71, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp138, kStack)), BinopInst("*", LoadVarInst(Address(fConst233, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst252, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst254, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec70, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst233, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst235, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst255, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst235, kStruct)), LoadVarInst(Address(fRec71, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst230, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst256, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst257, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec69, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst230, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst232, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst258, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst232, kStruct)), LoadVarInst(Address(fRec70, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst226, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst259, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst260, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec68, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec68, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst226, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst229, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst261, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst229, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec68, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec81, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp138, kStack)), BinopInst("*", LoadVarInst(Address(fConst278, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst281, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst282, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec80, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst278, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst280, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst283, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst280, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst276, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst284, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst285, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec79, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst276, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst277, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst286, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst277, kStruct)), LoadVarInst(Address(fRec80, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst274, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst287, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst288, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp139, kStack, BinopInst("*", LoadVarInst(Address(fConst274, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst275, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst289, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst275, kStruct)), LoadVarInst(Address(fRec79, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec78, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp139, kStack)), BinopInst("*", LoadVarInst(Address(fConst271, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst290, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst292, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec77, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst271, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst273, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst293, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst273, kStruct)), LoadVarInst(Address(fRec78, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst268, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst294, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst295, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec76, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst268, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst296, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst264, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst297, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst298, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec75, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec75, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst264, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst267, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst299, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst267, kStruct)), LoadVarInst(Address(fRec76, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec75, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec88, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp139, kStack)), BinopInst("*", LoadVarInst(Address(fConst316, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst319, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst320, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec87, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst316, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst318, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst321, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst318, kStruct)), LoadVarInst(Address(fRec88, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst314, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst322, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst323, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec86, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst314, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst315, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst324, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst315, kStruct)), LoadVarInst(Address(fRec87, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst325, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst326, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp140, kStack, BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst313, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst327, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst313, kStruct)), LoadVarInst(Address(fRec86, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec85, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp140, kStack)), BinopInst("*", LoadVarInst(Address(fConst309, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst328, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst330, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec84, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst309, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst311, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst331, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst311, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst306, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst332, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst333, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec83, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst306, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst308, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst334, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst308, kStruct)), LoadVarInst(Address(fRec84, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst302, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst335, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst336, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec82, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec82, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst302, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst337, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fRec83, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec82, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec95, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp140, kStack)), BinopInst("*", LoadVarInst(Address(fConst354, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst357, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst358, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec94, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst354, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst356, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst359, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst356, kStruct)), LoadVarInst(Address(fRec95, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst352, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst360, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst361, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec93, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst352, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst353, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst362, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst353, kStruct)), LoadVarInst(Address(fRec94, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst350, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst363, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst364, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp141, kStack, BinopInst("*", LoadVarInst(Address(fConst350, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst351, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst365, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst351, kStruct)), LoadVarInst(Address(fRec93, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec92, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp141, kStack)), BinopInst("*", LoadVarInst(Address(fConst347, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst366, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst368, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec91, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst347, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst349, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst369, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst349, kStruct)), LoadVarInst(Address(fRec92, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst370, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst371, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec90, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst346, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst372, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst346, kStruct)), LoadVarInst(Address(fRec91, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst340, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst373, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst374, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec89, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec89, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst340, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst343, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst375, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst343, kStruct)), LoadVarInst(Address(fRec90, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec89, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec102, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp141, kStack)), BinopInst("*", LoadVarInst(Address(fConst392, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst395, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst396, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec101, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst392, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst397, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fRec102, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst390, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst398, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst399, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec100, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst390, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst391, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst400, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst391, kStruct)), LoadVarInst(Address(fRec101, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst388, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst401, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst402, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp142, kStack, BinopInst("*", LoadVarInst(Address(fConst388, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst389, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst403, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst389, kStruct)), LoadVarInst(Address(fRec100, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec99, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp142, kStack)), BinopInst("*", LoadVarInst(Address(fConst385, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst404, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst406, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec98, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst385, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst407, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fRec99, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst382, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst408, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst409, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec97, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst382, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst384, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst410, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst384, kStruct)), LoadVarInst(Address(fRec98, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst378, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst411, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst412, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec96, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec96, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst378, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst381, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst413, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst381, kStruct)), LoadVarInst(Address(fRec97, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph10, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec96, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec109, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp142, kStack)), BinopInst("*", LoadVarInst(Address(fConst430, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst433, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst434, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec108, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst430, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst432, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst435, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst432, kStruct)), LoadVarInst(Address(fRec109, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst428, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst436, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst437, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec107, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst428, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst438, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fRec108, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst426, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst439, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst440, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp143, kStack, BinopInst("*", LoadVarInst(Address(fConst426, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst427, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst441, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst427, kStruct)), LoadVarInst(Address(fRec107, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec106, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp143, kStack)), BinopInst("*", LoadVarInst(Address(fConst423, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst442, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst444, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec105, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst423, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst425, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst445, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst425, kStruct)), LoadVarInst(Address(fRec106, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst420, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst446, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst447, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec104, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst420, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst422, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst448, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst422, kStruct)), LoadVarInst(Address(fRec105, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst416, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst449, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst450, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec103, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec103, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst416, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst419, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst451, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst419, kStruct)), LoadVarInst(Address(fRec104, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph11, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec103, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec116, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp143, kStack)), BinopInst("*", LoadVarInst(Address(fConst468, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst471, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst472, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec115, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst468, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst470, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst473, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst470, kStruct)), LoadVarInst(Address(fRec116, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst466, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst474, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst475, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec114, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst466, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst467, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst476, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst467, kStruct)), LoadVarInst(Address(fRec115, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst464, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst477, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst478, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp144, kStack, BinopInst("*", LoadVarInst(Address(fConst464, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst465, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst479, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst465, kStruct)), LoadVarInst(Address(fRec114, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec113, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp144, kStack)), BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst480, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst482, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec112, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst463, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst483, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst463, kStruct)), LoadVarInst(Address(fRec113, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst458, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst484, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst485, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec111, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst458, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst460, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst486, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst460, kStruct)), LoadVarInst(Address(fRec112, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst454, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst487, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst488, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec110, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec110, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst454, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst457, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst489, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst457, kStruct)), LoadVarInst(Address(fRec111, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph12, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec110, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec123, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp144, kStack)), BinopInst("*", LoadVarInst(Address(fConst506, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst509, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst510, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec122, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst506, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst511, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fRec123, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst504, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst512, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst513, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec121, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst504, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst505, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst514, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst505, kStruct)), LoadVarInst(Address(fRec122, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst502, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst515, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst516, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp145, kStack, BinopInst("*", LoadVarInst(Address(fConst502, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst503, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst517, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst503, kStruct)), LoadVarInst(Address(fRec121, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec120, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp145, kStack)), BinopInst("*", LoadVarInst(Address(fConst499, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst518, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst520, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec119, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst499, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst521, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fRec120, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst496, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst522, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst523, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec118, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst496, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst498, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst524, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst498, kStruct)), LoadVarInst(Address(fRec119, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst492, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst525, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst526, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec117, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec117, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst492, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst495, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst527, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst495, kStruct)), LoadVarInst(Address(fRec118, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph13, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec117, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fRec127, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp145, kStack)), BinopInst("*", LoadVarInst(Address(fConst532, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst535, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst536, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec126, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst532, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst537, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fRec127, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst530, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst538, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst539, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec125, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst530, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst531, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst540, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst531, kStruct)), LoadVarInst(Address(fRec126, kStruct)[Int32(2)])))), BinopInst("*", LoadVarInst(Address(fConst528, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst541, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst542, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec124, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec124, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), FunCallInst("fabsf", BinopInst("*", LoadVarInst(Address(fConst528, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst529, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst543, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst529, kStruct)), LoadVarInst(Address(fRec125, kStruct)[Int32(2)]))))))))
			StoreVarInst(Address(fVbargraph14, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fRec124, kStruct)[Int32(0)]))))))
			DeclareVarInst("float", fTemp146, kStack, LoadVarInst(Address(fTemp132, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp146, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp146, kStack))))
			ForLoopInst 
				DeclareVarInst("int", j0, kLoop, Int32(3))
				BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
				StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(iVec0, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec4, kStruct)[Int32(1)], LoadVarInst(Address(fVec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec5, kStruct)[Int32(1)], LoadVarInst(Address(fVec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec6, kStruct)[Int32(1)], LoadVarInst(Address(fVec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec7, kStruct)[Int32(1)], LoadVarInst(Address(fVec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec8, kStruct)[Int32(1)], LoadVarInst(Address(fVec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec9, kStruct)[Int32(1)], LoadVarInst(Address(fVec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec10, kStruct)[Int32(1)], LoadVarInst(Address(fVec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec11, kStruct)[Int32(1)], LoadVarInst(Address(fVec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec12, kStruct)[Int32(1)], LoadVarInst(Address(fVec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec13, kStruct)[Int32(1)], LoadVarInst(Address(fVec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec14, kStruct)[Int32(1)], LoadVarInst(Address(fVec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec15, kStruct)[Int32(1)], LoadVarInst(Address(fVec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec16, kStruct)[Int32(1)], LoadVarInst(Address(fVec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec17, kStruct)[Int32(1)], LoadVarInst(Address(fVec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec18, kStruct)[Int32(1)], LoadVarInst(Address(fVec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec19, kStruct)[Int32(1)], LoadVarInst(Address(fVec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec21, kStruct)[Int32(1)], LoadVarInst(Address(fVec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec23, kStruct)[Int32(1)], LoadVarInst(Address(fVec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec25, kStruct)[Int32(1)], LoadVarInst(Address(fVec25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec26, kStruct)[Int32(1)], LoadVarInst(Address(fVec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec28, kStruct)[Int32(1)], LoadVarInst(Address(fVec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec29, kStruct)[Int32(1)], LoadVarInst(Address(fVec29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec31, kStruct)[Int32(1)], LoadVarInst(Address(fVec31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec32, kStruct)[Int32(1)], LoadVarInst(Address(fVec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec24, kStruct)[Int32(1)], LoadVarInst(Address(iRec24, kStruct)[Int32(0)]))
			ForLoopInst 
				DeclareVarInst("int", j1, kLoop, Int32(3))
				BinopInst(">", LoadVarInst(Address(j1, kLoop)), Int32(0))
				StoreVarInst(Address(j1, kLoop), BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fRec23, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(2)], LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec25, kStruct)[Int32(2)], LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(2)], LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(2)], LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(2)], LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(2)], LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(2)], LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(2)], LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec46, kStruct)[Int32(2)], LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec46, kStruct)[Int32(1)], LoadVarInst(Address(fRec46, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec45, kStruct)[Int32(2)], LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec44, kStruct)[Int32(2)], LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec43, kStruct)[Int32(2)], LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec42, kStruct)[Int32(2)], LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec41, kStruct)[Int32(2)], LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec53, kStruct)[Int32(2)], LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec53, kStruct)[Int32(1)], LoadVarInst(Address(fRec53, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec52, kStruct)[Int32(2)], LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec52, kStruct)[Int32(1)], LoadVarInst(Address(fRec52, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec51, kStruct)[Int32(2)], LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec51, kStruct)[Int32(1)], LoadVarInst(Address(fRec51, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec50, kStruct)[Int32(2)], LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec50, kStruct)[Int32(1)], LoadVarInst(Address(fRec50, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec49, kStruct)[Int32(2)], LoadVarInst(Address(fRec49, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec49, kStruct)[Int32(1)], LoadVarInst(Address(fRec49, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec48, kStruct)[Int32(2)], LoadVarInst(Address(fRec48, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec48, kStruct)[Int32(1)], LoadVarInst(Address(fRec48, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec47, kStruct)[Int32(1)], LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec60, kStruct)[Int32(2)], LoadVarInst(Address(fRec60, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec60, kStruct)[Int32(1)], LoadVarInst(Address(fRec60, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec59, kStruct)[Int32(2)], LoadVarInst(Address(fRec59, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec59, kStruct)[Int32(1)], LoadVarInst(Address(fRec59, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec58, kStruct)[Int32(2)], LoadVarInst(Address(fRec58, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec58, kStruct)[Int32(1)], LoadVarInst(Address(fRec58, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec57, kStruct)[Int32(2)], LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec57, kStruct)[Int32(1)], LoadVarInst(Address(fRec57, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec56, kStruct)[Int32(2)], LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec56, kStruct)[Int32(1)], LoadVarInst(Address(fRec56, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec55, kStruct)[Int32(2)], LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec55, kStruct)[Int32(1)], LoadVarInst(Address(fRec55, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec54, kStruct)[Int32(1)], LoadVarInst(Address(fRec54, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec67, kStruct)[Int32(2)], LoadVarInst(Address(fRec67, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec67, kStruct)[Int32(1)], LoadVarInst(Address(fRec67, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec66, kStruct)[Int32(2)], LoadVarInst(Address(fRec66, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec66, kStruct)[Int32(1)], LoadVarInst(Address(fRec66, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec65, kStruct)[Int32(2)], LoadVarInst(Address(fRec65, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec65, kStruct)[Int32(1)], LoadVarInst(Address(fRec65, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec64, kStruct)[Int32(2)], LoadVarInst(Address(fRec64, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec64, kStruct)[Int32(1)], LoadVarInst(Address(fRec64, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec63, kStruct)[Int32(2)], LoadVarInst(Address(fRec63, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec63, kStruct)[Int32(1)], LoadVarInst(Address(fRec63, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec62, kStruct)[Int32(2)], LoadVarInst(Address(fRec62, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec62, kStruct)[Int32(1)], LoadVarInst(Address(fRec62, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec61, kStruct)[Int32(1)], LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec74, kStruct)[Int32(2)], LoadVarInst(Address(fRec74, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec74, kStruct)[Int32(1)], LoadVarInst(Address(fRec74, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec73, kStruct)[Int32(2)], LoadVarInst(Address(fRec73, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec73, kStruct)[Int32(1)], LoadVarInst(Address(fRec73, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec72, kStruct)[Int32(2)], LoadVarInst(Address(fRec72, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec72, kStruct)[Int32(1)], LoadVarInst(Address(fRec72, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec71, kStruct)[Int32(2)], LoadVarInst(Address(fRec71, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec71, kStruct)[Int32(1)], LoadVarInst(Address(fRec71, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec70, kStruct)[Int32(2)], LoadVarInst(Address(fRec70, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec70, kStruct)[Int32(1)], LoadVarInst(Address(fRec70, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec69, kStruct)[Int32(2)], LoadVarInst(Address(fRec69, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec69, kStruct)[Int32(1)], LoadVarInst(Address(fRec69, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec68, kStruct)[Int32(1)], LoadVarInst(Address(fRec68, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec81, kStruct)[Int32(2)], LoadVarInst(Address(fRec81, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec81, kStruct)[Int32(1)], LoadVarInst(Address(fRec81, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec80, kStruct)[Int32(2)], LoadVarInst(Address(fRec80, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec80, kStruct)[Int32(1)], LoadVarInst(Address(fRec80, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec79, kStruct)[Int32(2)], LoadVarInst(Address(fRec79, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec79, kStruct)[Int32(1)], LoadVarInst(Address(fRec79, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec78, kStruct)[Int32(2)], LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec78, kStruct)[Int32(1)], LoadVarInst(Address(fRec78, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec77, kStruct)[Int32(2)], LoadVarInst(Address(fRec77, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec77, kStruct)[Int32(1)], LoadVarInst(Address(fRec77, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec76, kStruct)[Int32(2)], LoadVarInst(Address(fRec76, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec76, kStruct)[Int32(1)], LoadVarInst(Address(fRec76, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec75, kStruct)[Int32(1)], LoadVarInst(Address(fRec75, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec88, kStruct)[Int32(2)], LoadVarInst(Address(fRec88, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec88, kStruct)[Int32(1)], LoadVarInst(Address(fRec88, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec87, kStruct)[Int32(2)], LoadVarInst(Address(fRec87, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec87, kStruct)[Int32(1)], LoadVarInst(Address(fRec87, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec86, kStruct)[Int32(2)], LoadVarInst(Address(fRec86, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec86, kStruct)[Int32(1)], LoadVarInst(Address(fRec86, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec85, kStruct)[Int32(2)], LoadVarInst(Address(fRec85, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec85, kStruct)[Int32(1)], LoadVarInst(Address(fRec85, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec84, kStruct)[Int32(2)], LoadVarInst(Address(fRec84, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec84, kStruct)[Int32(1)], LoadVarInst(Address(fRec84, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec83, kStruct)[Int32(2)], LoadVarInst(Address(fRec83, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec83, kStruct)[Int32(1)], LoadVarInst(Address(fRec83, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec82, kStruct)[Int32(1)], LoadVarInst(Address(fRec82, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec95, kStruct)[Int32(2)], LoadVarInst(Address(fRec95, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec95, kStruct)[Int32(1)], LoadVarInst(Address(fRec95, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec94, kStruct)[Int32(2)], LoadVarInst(Address(fRec94, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec94, kStruct)[Int32(1)], LoadVarInst(Address(fRec94, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec93, kStruct)[Int32(2)], LoadVarInst(Address(fRec93, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec93, kStruct)[Int32(1)], LoadVarInst(Address(fRec93, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec92, kStruct)[Int32(2)], LoadVarInst(Address(fRec92, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec92, kStruct)[Int32(1)], LoadVarInst(Address(fRec92, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec91, kStruct)[Int32(2)], LoadVarInst(Address(fRec91, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec91, kStruct)[Int32(1)], LoadVarInst(Address(fRec91, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec90, kStruct)[Int32(2)], LoadVarInst(Address(fRec90, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec90, kStruct)[Int32(1)], LoadVarInst(Address(fRec90, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec89, kStruct)[Int32(1)], LoadVarInst(Address(fRec89, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec102, kStruct)[Int32(2)], LoadVarInst(Address(fRec102, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec102, kStruct)[Int32(1)], LoadVarInst(Address(fRec102, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec101, kStruct)[Int32(2)], LoadVarInst(Address(fRec101, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec101, kStruct)[Int32(1)], LoadVarInst(Address(fRec101, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec100, kStruct)[Int32(2)], LoadVarInst(Address(fRec100, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec100, kStruct)[Int32(1)], LoadVarInst(Address(fRec100, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec99, kStruct)[Int32(2)], LoadVarInst(Address(fRec99, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec99, kStruct)[Int32(1)], LoadVarInst(Address(fRec99, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec98, kStruct)[Int32(2)], LoadVarInst(Address(fRec98, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec98, kStruct)[Int32(1)], LoadVarInst(Address(fRec98, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec97, kStruct)[Int32(2)], LoadVarInst(Address(fRec97, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec97, kStruct)[Int32(1)], LoadVarInst(Address(fRec97, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec96, kStruct)[Int32(1)], LoadVarInst(Address(fRec96, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec109, kStruct)[Int32(2)], LoadVarInst(Address(fRec109, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec109, kStruct)[Int32(1)], LoadVarInst(Address(fRec109, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec108, kStruct)[Int32(2)], LoadVarInst(Address(fRec108, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec108, kStruct)[Int32(1)], LoadVarInst(Address(fRec108, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec107, kStruct)[Int32(2)], LoadVarInst(Address(fRec107, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec107, kStruct)[Int32(1)], LoadVarInst(Address(fRec107, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec106, kStruct)[Int32(2)], LoadVarInst(Address(fRec106, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec106, kStruct)[Int32(1)], LoadVarInst(Address(fRec106, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec105, kStruct)[Int32(2)], LoadVarInst(Address(fRec105, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec105, kStruct)[Int32(1)], LoadVarInst(Address(fRec105, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec104, kStruct)[Int32(2)], LoadVarInst(Address(fRec104, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec104, kStruct)[Int32(1)], LoadVarInst(Address(fRec104, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec103, kStruct)[Int32(1)], LoadVarInst(Address(fRec103, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec116, kStruct)[Int32(2)], LoadVarInst(Address(fRec116, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec116, kStruct)[Int32(1)], LoadVarInst(Address(fRec116, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec115, kStruct)[Int32(2)], LoadVarInst(Address(fRec115, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec115, kStruct)[Int32(1)], LoadVarInst(Address(fRec115, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec114, kStruct)[Int32(2)], LoadVarInst(Address(fRec114, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec114, kStruct)[Int32(1)], LoadVarInst(Address(fRec114, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec113, kStruct)[Int32(2)], LoadVarInst(Address(fRec113, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec113, kStruct)[Int32(1)], LoadVarInst(Address(fRec113, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec112, kStruct)[Int32(2)], LoadVarInst(Address(fRec112, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec112, kStruct)[Int32(1)], LoadVarInst(Address(fRec112, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec111, kStruct)[Int32(2)], LoadVarInst(Address(fRec111, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec111, kStruct)[Int32(1)], LoadVarInst(Address(fRec111, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec110, kStruct)[Int32(1)], LoadVarInst(Address(fRec110, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec123, kStruct)[Int32(2)], LoadVarInst(Address(fRec123, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec123, kStruct)[Int32(1)], LoadVarInst(Address(fRec123, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec122, kStruct)[Int32(2)], LoadVarInst(Address(fRec122, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec122, kStruct)[Int32(1)], LoadVarInst(Address(fRec122, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec121, kStruct)[Int32(2)], LoadVarInst(Address(fRec121, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec121, kStruct)[Int32(1)], LoadVarInst(Address(fRec121, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec120, kStruct)[Int32(2)], LoadVarInst(Address(fRec120, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec120, kStruct)[Int32(1)], LoadVarInst(Address(fRec120, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec119, kStruct)[Int32(2)], LoadVarInst(Address(fRec119, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec119, kStruct)[Int32(1)], LoadVarInst(Address(fRec119, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec118, kStruct)[Int32(2)], LoadVarInst(Address(fRec118, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec118, kStruct)[Int32(1)], LoadVarInst(Address(fRec118, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec117, kStruct)[Int32(1)], LoadVarInst(Address(fRec117, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec127, kStruct)[Int32(2)], LoadVarInst(Address(fRec127, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec127, kStruct)[Int32(1)], LoadVarInst(Address(fRec127, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec126, kStruct)[Int32(2)], LoadVarInst(Address(fRec126, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec126, kStruct)[Int32(1)], LoadVarInst(Address(fRec126, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec125, kStruct)[Int32(2)], LoadVarInst(Address(fRec125, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec125, kStruct)[Int32(1)], LoadVarInst(Address(fRec125, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec124, kStruct)[Int32(1)], LoadVarInst(Address(fRec124, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 24 bytes
Heap size real = 102196 bytes
Total heap size = 102228 bytes
Stack size in compute = 192 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec20 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec26 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec25 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec39 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec38 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec37 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec36 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec35 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst70 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec34 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst71 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst78 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst79 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst80 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst81 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst82 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst83 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst84 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst85 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst86 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst87 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst88 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst89 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst90 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst91 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst92 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec46 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst93 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst94 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst95 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec45 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst96 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst97 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst98 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec44 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst99 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst100 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst101 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst102 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec43 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst103 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst104 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst105 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec42 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst106 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst107 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst108 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec41 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst109 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst110 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst111 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst112 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst113 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst114 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst115 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst116 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst117 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst118 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst119 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst120 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst121 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst122 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst123 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst124 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst125 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst126 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst127 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst128 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst129 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst130 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec53 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst131 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst132 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst133 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec52 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst134 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst135 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst136 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec51 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst137 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst138 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst139 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst140 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec50 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst141 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst142 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst143 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec49 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst144 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst145 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst146 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec48 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst147 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec47 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst148 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst149 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst150 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst151 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst152 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst153 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst154 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst155 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst156 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst157 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst158 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst159 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst160 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst161 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst162 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst163 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst164 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst165 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst166 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst167 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst168 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec60 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst169 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst170 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst171 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec59 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst172 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst173 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst174 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec58 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst175 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst176 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst177 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst178 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec57 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst179 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst180 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst181 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec56 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst182 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst183 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst184 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec55 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst185 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec54 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst186 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst187 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst188 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst189 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst190 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst191 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst192 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst193 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst194 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst195 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst196 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst197 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst198 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst199 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst200 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst201 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst202 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst203 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst204 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst205 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst206 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec67 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst207 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst208 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst209 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec66 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst210 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst211 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst212 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec65 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst213 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst214 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst215 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst216 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec64 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst217 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst218 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst219 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec63 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst220 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst221 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst222 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec62 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst223 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec61 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst224 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst225 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst226 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst227 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst228 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst229 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst230 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst231 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst232 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst233 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst234 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst235 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst236 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst237 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst238 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst239 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst240 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst241 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst242 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst243 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst244 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec74 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst245 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst246 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst247 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec73 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst248 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst249 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst250 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec72 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst251 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst252 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst253 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst254 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec71 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst255 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst256 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst257 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec70 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst258 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst259 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst260 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec69 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst261 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec68 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst262 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst263 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst264 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst265 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst266 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst267 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst268 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst269 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst270 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst271 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst272 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst273 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst274 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst275 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst276 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst277 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst278 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst279 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst280 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst281 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst282 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec81 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst283 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst284 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst285 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec80 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst286 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst287 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst288 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec79 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst289 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst290 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst291 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst292 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec78 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst293 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst294 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst295 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec77 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst296 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst297 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst298 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec76 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst299 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec75 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst300 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst301 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst302 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst303 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst304 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst305 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst306 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst307 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst308 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst309 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst310 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst311 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst312 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst313 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst314 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst315 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst316 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst317 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst318 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst319 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst320 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec88 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst321 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst322 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst323 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec87 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst324 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst325 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst326 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec86 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst327 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst328 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst329 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst330 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec85 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst331 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst332 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst333 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec84 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst334 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst335 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst336 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec83 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst337 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec82 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst338 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst339 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst340 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst341 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst342 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst343 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst344 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst345 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst346 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst347 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst348 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst349 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst350 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst351 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst352 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst353 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst354 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst355 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst356 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst357 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst358 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec95 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst359 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst360 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst361 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec94 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst362 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst363 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst364 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec93 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst365 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst366 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst367 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst368 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec92 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst369 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst370 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst371 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec91 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst372 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst373 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst374 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec90 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst375 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec89 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst376 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst377 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst378 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst379 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst380 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst381 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst382 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst383 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst384 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst385 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst386 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst387 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst388 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst389 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst390 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst391 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst392 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst393 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst394 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst395 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst396 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec102 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst397 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst398 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst399 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec101 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst400 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst401 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst402 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec100 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst403 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst404 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst405 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst406 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec99 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst407 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst408 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst409 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec98 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst410 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst411 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst412 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec97 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst413 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec96 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst414 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst415 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst416 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst417 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst418 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst419 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst420 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst421 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst422 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst423 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst424 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst425 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst426 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst427 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst428 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst429 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst430 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst431 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst432 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst433 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst434 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec109 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst435 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst436 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst437 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec108 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst438 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst439 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst440 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec107 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst441 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst442 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst443 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst444 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec106 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst445 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst446 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst447 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec105 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst448 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst449 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst450 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec104 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst451 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec103 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst452 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst453 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst454 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst455 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst456 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst457 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst458 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst459 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst460 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst461 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst462 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst463 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst464 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst465 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst466 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst467 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst468 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst469 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst470 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst471 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst472 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec116 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst473 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst474 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst475 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec115 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst476 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst477 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst478 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec114 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst479 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst480 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst481 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst482 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec113 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst483 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst484 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst485 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec112 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst486 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst487 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst488 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec111 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst489 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec110 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst490 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst491 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst492 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst493 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst494 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst495 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst496 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst497 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst498 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst499 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst500 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst501 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst502 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst503 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst504 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst505 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst506 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst507 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst508 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst509 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst510 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec123 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst511 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst512 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst513 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec122 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst514 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst515 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst516 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec121 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst517 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst518 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst519 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst520 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec120 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst521 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst522 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst523 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec119 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst524 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst525 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst526 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec118 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst527 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec117 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst528 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst529 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst530 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst531 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst532 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst533 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst534 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst535 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst536 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec127 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst537 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst538 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst539 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec126 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst540 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst541 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst542 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec125 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst543 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec124 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec0 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec20 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst22 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec26 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec25 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec39 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec38 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec37 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec36 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec35 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst70 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec34 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst71 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst78 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst79 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst80 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst81 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst82 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst83 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst84 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst85 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst86 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst87 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst88 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst89 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst90 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst91 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst92 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec46 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst93 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst94 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst95 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec45 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst96 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst97 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst98 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec44 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst99 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst100 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst101 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst102 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec43 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst103 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst104 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst105 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec42 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst106 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst107 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst108 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec41 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst109 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst110 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst111 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst112 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst113 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst114 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst115 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst116 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst117 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst118 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst119 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst120 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst121 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst122 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst123 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst124 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst125 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst126 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst127 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst128 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst129 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst130 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec53 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst131 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst132 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst133 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec52 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst134 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst135 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst136 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec51 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst137 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst138 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst139 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst140 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec50 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst141 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst142 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst143 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec49 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst144 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst145 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst146 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec48 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst147 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec47 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst148 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst149 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst150 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst151 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst152 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst153 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst154 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst155 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst156 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst157 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst158 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst159 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst160 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst161 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst162 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst163 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst164 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst165 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst166 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst167 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst168 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec60 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst169 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst170 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst171 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec59 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst172 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst173 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst174 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec58 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst175 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst176 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst177 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst178 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec57 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst179 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst180 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst181 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec56 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst182 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst183 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst184 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec55 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst185 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec54 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst186 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst187 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst188 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst189 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst190 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst191 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst192 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst193 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst194 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst195 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst196 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst197 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst198 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst199 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst200 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst201 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst202 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst203 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst204 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst205 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst206 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec67 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst207 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst208 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst209 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec66 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst210 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst211 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst212 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec65 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst213 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst214 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst215 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst216 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec64 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst217 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst218 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst219 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec63 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst220 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst221 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst222 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec62 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst223 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec61 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst224 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst225 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst226 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst227 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst228 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst229 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst230 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst231 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst232 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst233 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst234 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst235 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst236 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst237 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst238 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst239 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst240 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst241 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst242 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst243 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst244 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec74 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst245 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst246 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst247 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec73 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst248 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst249 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst250 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec72 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst251 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst252 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst253 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst254 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec71 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst255 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst256 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst257 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec70 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst258 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst259 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst260 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec69 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst261 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec68 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst262 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst263 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst264 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst265 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst266 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst267 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst268 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst269 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst270 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst271 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst272 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst273 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst274 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst275 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst276 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst277 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst278 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst279 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst280 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst281 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst282 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec81 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst283 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst284 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst285 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec80 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst286 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst287 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst288 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec79 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst289 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst290 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst291 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst292 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec78 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst293 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst294 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst295 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec77 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst296 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst297 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst298 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec76 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst299 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec75 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst300 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst301 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst302 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst303 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst304 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst305 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst306 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst307 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst308 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst309 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst310 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst311 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst312 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst313 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst314 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst315 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst316 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst317 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst318 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst319 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst320 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec88 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst321 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst322 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst323 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec87 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst324 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst325 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst326 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec86 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst327 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst328 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst329 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst330 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec85 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst331 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst332 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst333 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec84 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst334 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst335 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst336 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec83 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst337 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec82 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst338 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst339 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst340 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst341 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst342 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst343 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst344 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst345 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst346 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst347 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst348 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst349 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst350 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst351 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst352 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst353 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst354 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst355 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst356 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst357 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst358 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec95 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst359 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst360 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst361 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec94 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst362 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst363 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst364 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec93 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst365 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst366 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst367 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst368 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec92 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst369 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst370 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst371 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec91 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst372 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst373 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst374 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec90 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst375 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec89 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst376 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst377 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst378 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst379 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst380 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst381 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst382 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst383 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst384 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst385 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst386 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst387 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst388 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst389 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst390 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst391 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst392 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst393 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst394 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst395 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst396 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec102 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst397 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst398 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst399 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec101 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst400 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst401 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst402 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec100 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst403 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst404 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst405 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst406 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec99 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst407 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst408 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst409 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec98 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst410 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst411 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst412 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec97 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst413 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec96 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst414 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst415 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst416 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst417 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst418 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst419 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst420 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst421 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst422 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst423 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst424 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst425 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst426 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst427 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst428 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst429 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst430 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst431 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst432 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst433 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst434 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec109 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst435 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst436 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst437 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec108 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst438 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst439 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst440 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec107 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst441 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst442 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst443 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst444 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec106 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst445 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst446 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst447 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec105 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst448 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst449 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst450 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec104 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst451 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec103 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst452 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst453 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst454 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst455 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst456 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst457 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst458 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst459 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst460 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst461 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst462 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst463 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst464 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst465 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst466 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst467 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst468 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst469 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst470 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst471 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst472 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec116 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst473 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst474 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst475 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec115 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst476 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst477 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst478 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec114 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst479 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst480 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst481 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst482 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec113 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst483 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst484 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst485 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec112 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst486 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst487 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst488 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec111 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst489 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec110 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst490 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst491 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst492 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst493 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst494 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst495 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst496 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst497 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst498 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst499 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst500 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst501 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst502 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst503 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst504 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst505 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst506 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst507 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst508 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst509 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst510 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec123 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst511 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst512 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst513 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec122 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst514 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst515 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst516 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec121 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst517 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst518 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst519 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst520 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec120 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst521 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst522 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst523 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec119 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst524 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst525 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst526 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec118 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst527 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec117 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst528 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst529 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst530 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst531 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst532 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst533 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst534 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst535 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst536 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec127 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst537 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst538 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst539 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec126 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst540 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst541 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst542 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec125 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst543 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec124 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 4 size_bytes = 16 read = 4 write = 2 ratio = 1.5
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst8 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst11 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 6 write = 0 ratio = 6
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 7 write = 2 ratio = 4.5
Field = fRec12 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst16 size = 1 size_bytes = 4 read = 6 write = 0 ratio = 6
Field = fVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst17 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst18 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fVec4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec8 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec9 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec10 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec11 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec12 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec13 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec14 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec15 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec16 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec17 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec18 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec19 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = IOTA0 size = 1 size_bytes = 4 read = 25 write = 1 ratio = 26
Field = fVec20 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fConst20 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fRec17 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec21 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec22 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fRec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec23 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec24 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec20 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec21 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec25 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec26 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec27 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fVec28 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec29 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec30 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVec31 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec32 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec33 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec24 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec23 size = 4 size_bytes = 16 read = 8 write = 2 ratio = 2.5
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec26 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec25 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec29 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec27 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec32 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec30 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fConst24 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst27 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst28 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst29 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec2 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst30 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst31 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst32 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst40 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst42 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst43 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst46 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst47 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst48 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst49 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst50 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst53 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst54 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec39 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst55 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst56 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst57 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec38 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst58 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst59 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst60 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec37 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst61 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst62 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec36 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst65 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst66 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst67 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec35 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst68 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst69 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst70 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec34 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst71 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec33 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst74 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst77 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst78 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst79 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst80 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst81 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst82 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst83 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst84 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst85 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst86 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst87 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst88 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst89 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst90 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst91 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst92 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec46 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst93 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst94 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst95 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec45 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst96 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst97 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst98 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec44 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst99 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst100 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst101 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst102 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec43 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst103 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst104 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst105 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec42 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst106 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst107 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst108 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec41 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst109 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec40 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst110 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst111 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst112 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst113 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst114 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst115 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst116 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst117 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst118 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst119 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst120 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst121 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst122 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst123 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst124 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst125 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst126 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst127 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst128 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst129 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst130 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec53 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst131 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst132 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst133 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec52 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst134 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst135 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst136 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec51 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst137 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst138 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst139 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst140 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec50 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst141 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst142 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst143 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec49 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst144 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst145 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst146 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec48 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst147 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec47 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst148 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst149 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst150 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst151 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst152 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst153 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst154 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst155 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst156 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst157 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst158 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst159 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst160 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst161 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst162 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst163 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst164 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst165 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst166 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst167 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst168 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec60 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst169 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst170 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst171 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec59 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst172 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst173 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst174 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec58 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst175 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst176 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst177 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst178 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec57 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst179 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst180 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst181 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec56 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst182 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst183 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst184 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec55 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst185 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec54 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst186 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst187 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst188 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst189 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst190 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst191 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst192 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst193 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst194 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst195 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst196 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst197 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst198 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst199 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst200 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst201 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst202 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst203 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst204 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst205 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst206 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec67 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst207 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst208 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst209 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec66 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst210 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst211 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst212 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec65 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst213 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst214 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst215 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst216 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec64 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst217 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst218 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst219 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec63 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst220 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst221 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst222 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec62 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst223 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec61 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst224 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst225 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst226 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst227 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst228 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst229 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst230 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst231 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst232 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst233 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst234 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst235 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst236 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst237 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst238 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst239 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst240 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst241 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst242 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst243 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst244 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec74 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst245 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst246 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst247 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec73 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst248 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst249 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst250 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec72 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst251 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst252 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst253 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst254 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec71 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst255 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst256 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst257 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec70 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst258 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst259 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst260 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec69 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst261 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec68 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst262 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst263 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst264 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst265 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst266 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst267 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst268 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst269 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst270 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst271 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst272 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst273 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst274 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst275 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst276 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst277 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst278 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst279 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst280 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst281 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst282 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec81 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst283 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst284 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst285 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec80 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst286 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst287 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst288 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec79 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst289 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst290 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst291 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst292 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec78 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst293 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst294 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst295 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec77 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst296 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst297 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst298 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec76 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst299 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec75 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst300 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst301 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst302 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst303 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst304 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst305 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst306 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst307 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst308 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst309 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst310 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst311 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst312 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst313 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst314 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst315 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst316 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst317 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst318 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst319 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst320 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec88 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst321 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst322 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst323 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec87 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst324 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst325 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst326 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec86 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst327 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst328 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst329 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst330 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec85 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst331 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst332 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst333 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec84 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst334 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst335 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst336 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec83 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst337 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec82 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst338 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst339 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst340 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst341 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst342 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst343 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst344 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst345 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst346 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst347 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst348 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst349 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst350 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst351 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst352 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst353 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst354 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst355 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst356 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst357 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst358 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec95 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst359 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst360 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst361 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec94 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst362 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst363 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst364 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec93 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst365 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst366 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst367 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst368 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec92 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst369 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst370 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst371 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec91 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst372 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst373 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst374 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec90 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst375 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec89 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst376 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst377 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst378 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst379 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst380 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst381 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst382 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst383 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst384 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst385 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst386 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst387 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst388 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst389 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst390 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst391 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst392 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst393 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst394 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst395 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst396 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec102 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst397 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst398 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst399 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec101 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst400 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst401 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst402 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec100 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst403 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst404 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst405 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst406 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec99 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst407 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst408 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst409 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec98 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst410 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst411 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst412 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec97 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst413 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec96 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph10 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst414 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst415 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst416 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst417 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst418 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst419 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst420 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst421 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst422 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst423 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst424 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst425 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst426 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst427 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst428 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst429 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst430 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst431 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst432 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst433 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst434 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec109 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst435 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst436 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst437 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec108 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst438 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst439 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst440 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec107 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst441 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst442 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst443 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst444 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec106 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst445 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst446 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst447 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec105 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst448 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst449 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst450 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec104 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst451 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec103 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph11 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst452 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst453 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst454 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst455 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst456 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst457 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst458 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst459 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst460 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst461 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst462 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst463 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst464 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst465 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst466 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst467 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst468 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst469 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst470 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst471 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst472 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec116 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst473 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst474 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst475 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec115 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst476 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst477 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst478 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec114 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst479 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst480 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst481 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst482 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec113 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst483 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst484 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst485 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec112 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst486 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst487 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst488 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec111 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst489 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec110 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph12 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst490 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst491 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst492 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst493 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst494 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst495 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst496 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst497 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst498 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst499 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst500 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst501 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst502 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst503 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst504 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst505 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst506 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst507 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst508 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst509 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst510 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec123 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst511 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst512 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst513 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec122 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst514 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst515 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst516 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec121 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst517 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst518 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst519 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst520 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec120 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst521 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst522 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst523 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec119 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst524 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst525 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst526 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec118 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst527 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec117 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph13 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst528 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst529 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst530 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst531 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst532 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst533 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst534 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst535 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst536 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec127 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst537 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst538 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst539 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec126 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst540 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst541 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst542 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec125 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst543 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec124 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVbargraph14 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
