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
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "style", "hslider")
	AddMetaDeclareInst(fHslider3, "tooltip", "Sawtooth waveform amplitude")
	AddMetaDeclareInst(fHslider3, "unit", "dB")
	AddHorizontalSlider("Mix Amplitude", fHslider3, -2e+01f, -1.2e+02f, 1e+01f, 0.1f)
	AddMetaDeclareInst(fHslider4, "2", "")
	AddMetaDeclareInst(fHslider4, "style", "hslider")
	AddMetaDeclareInst(fHslider4, "tooltip", "Sawtooth frequency as a Piano Key (PK) number (A440 = key 49)")
	AddMetaDeclareInst(fHslider4, "unit", "PK")
	AddHorizontalSlider("Frequency", fHslider4, 49.0f, 1.0f, 88.0f, 0.01f)
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
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "tooltip", "The VCF resonates at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).  The VCF response is flat below the corner frequency, and rolls off -24 dB per octave above.")
	AddMetaDeclareInst(fHslider2, "unit", "PK")
	AddHorizontalSlider("Corner Frequency", fHslider2, 25.0f, 1.0f, 88.0f, 0.01f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "tooltip", "Amount of resonance near VCF corner frequency (specified between 0 and 1)")
	AddHorizontalSlider("Corner Resonance", fHslider1, 0.9f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fHslider5, "3", "")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddMetaDeclareInst(fHslider5, "tooltip", "output level in decibels")
	AddMetaDeclareInst(fHslider5, "unit", "dB")
	AddHorizontalSlider("VCF Output Level", fHslider5, 5.0f, -6e+01f, 2e+01f, 0.1f)
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "See Faust's filter.lib for documentation and references")
	OpenHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP")
	AddMetaDeclareInst(fVbargraph11, "0", "")
	AddMetaDeclareInst(fVbargraph11, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph11, "unit", "dB")
	AddVerticalBargraph("vbargraph0", fVbargraph11, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph7, "1", "")
	AddMetaDeclareInst(fVbargraph7, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph7, "unit", "dB")
	AddVerticalBargraph("vbargraph1", fVbargraph7, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph3, "2", "")
	AddMetaDeclareInst(fVbargraph3, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("vbargraph2", fVbargraph3, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph14, "3", "")
	AddMetaDeclareInst(fVbargraph14, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph14, "unit", "dB")
	AddVerticalBargraph("vbargraph3", fVbargraph14, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph10, "4", "")
	AddMetaDeclareInst(fVbargraph10, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph10, "unit", "dB")
	AddVerticalBargraph("vbargraph4", fVbargraph10, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph6, "5", "")
	AddMetaDeclareInst(fVbargraph6, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("vbargraph5", fVbargraph6, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph2, "6", "")
	AddMetaDeclareInst(fVbargraph2, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("vbargraph6", fVbargraph2, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph13, "7", "")
	AddMetaDeclareInst(fVbargraph13, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph13, "unit", "dB")
	AddVerticalBargraph("vbargraph7", fVbargraph13, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph9, "8", "")
	AddMetaDeclareInst(fVbargraph9, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph9, "unit", "dB")
	AddVerticalBargraph("vbargraph8", fVbargraph9, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph5, "9", "")
	AddMetaDeclareInst(fVbargraph5, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("vbargraph9", fVbargraph5, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph1, "10", "")
	AddMetaDeclareInst(fVbargraph1, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("vbargraph10", fVbargraph1, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph12, "11", "")
	AddMetaDeclareInst(fVbargraph12, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph12, "unit", "dB")
	AddVerticalBargraph("vbargraph11", fVbargraph12, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph8, "12", "")
	AddMetaDeclareInst(fVbargraph8, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph8, "unit", "dB")
	AddVerticalBargraph("vbargraph12", fVbargraph8, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph4, "13", "")
	AddMetaDeclareInst(fVbargraph4, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("vbargraph13", fVbargraph4, -5e+01f, 1e+01f)
	AddMetaDeclareInst(fVbargraph0, "14", "")
	AddMetaDeclareInst(fVbargraph0, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("vbargraph14", fVbargraph0, -5e+01f, 1e+01f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("SPECTRUM ANALYZER CONTROLS")
	AddMetaDeclareInst(fHslider6, "0", "")
	AddMetaDeclareInst(fHslider6, "scale", "log")
	AddMetaDeclareInst(fHslider6, "tooltip", "band-level averaging time in milliseconds")
	AddMetaDeclareInst(fHslider6, "unit", "ms")
	AddHorizontalSlider("Level Averaging Time", fHslider6, 1e+02f, 1.0f, 1e+04f, 1.0f)
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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fCheckbox1)("FAUSTFLOAT", fHslider1)("int[4]", iVec0)("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fHslider2)("float[2]", fIIR3)("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fHslider3)("float[2]", fIIR4)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fEntry0)("float", fConst2)("FAUSTFLOAT", fHslider4)("FAUSTFLOAT", fVslider2)("float[2]", fIRM1)("float[2]", fRec5)("float", fConst3)("float[2]", fVec1)("float", fConst4)("float", fConst5)("float[2]", fVec2)("float[2]", fVec3)("float", fConst6)("float", fConst7)("float[2]", fVec4)("float[2]", fVec5)("float[2]", fVec6)("FAUSTFLOAT", fVslider3)("float[2]", fRec6)("float", fConst8)("float[2]", fVec7)("float", fConst9)("float[2]", fVec8)("float[2]", fVec9)("float", fConst10)("float[2]", fVec10)("float[2]", fVec11)("float[2]", fVec12)("FAUSTFLOAT", fVslider4)("float[2]", fRec7)("float", fConst11)("float[2]", fVec13)("float", fConst12)("float[2]", fVec14)("float[2]", fVec15)("float", fConst13)("float[2]", fVec16)("float[2]", fVec17)("float[2]", fVec18)("float", fConst14)("FAUSTFLOAT", fVslider5)("float", fConst15)("float[2]", fRec8)("float[2]", fVec19)("int", IOTA0)("float[4096]", fVec20)("float[2]", fRec9)("float[2]", fVec21)("float[4096]", fVec22)("float[2]", fRec10)("float[2]", fVec23)("float[4096]", fVec24)("float", fConst16)("FAUSTFLOAT", fVslider6)("float", fConst17)("float[2]", fIIR5)("float", fConst18)("float[2]", fIIR6)("float", fConst19)("float[2]", fIIR7)("FAUSTFLOAT", fVslider7)("float", fConst20)("FAUSTFLOAT", fCheckbox2)("FAUSTFLOAT", fVslider8)("float[2]", fIIR8)("float[2]", fVec25)("float[2]", fVec26)("float[4096]", fVec27)("float[2]", fVec28)("float[2]", fVec29)("float[4096]", fVec30)("float[2]", fVec31)("float[2]", fVec32)("float[4096]", fVec33)("float", fConst21)("FAUSTFLOAT", fVslider9)("int[2]", iIIR10)("float[4]", fIIR9)("float[4]", fVec34)("float[2]", fRec0)("float[2]", fRec1)("float[2]", fRec2)("float[2]", fRec3)("float[2]", fRec4)("FAUSTFLOAT", fCheckbox3)("float", fConst22)("float[3]", fRec12)("float[3]", fRec11)("float[2]", fRec13)("float[2]", fRec14)("float[2]", fRec15)("float[2]", fRec16)("FAUSTFLOAT", fHslider5)("float[2]", fIIR11)("float", fConst23)("float", fConst24)("float", fConst25)("float", fConst26)("float", fConst27)("float", fConst28)("float", fConst29)("float", fConst30)("float[3]", fIIR2)("float", fConst31)("float", fConst32)("float", fConst33)("float", fConst34)("float", fConst35)("float", fConst36)("float", fConst37)("float", fConst38)("float[3]", fIIR1)("float", fConst39)("float", fConst40)("float", fConst41)("float", fConst42)("float", fConst43)("float", fConst44)("float", fConst45)("float", fConst46)("float[3]", fIIR0)("float", fConst47)("float", fConst48)("float", fConst49)("float", fConst50)("FAUSTFLOAT", fHslider6)("float[2]", fIRM0)("FAUSTFLOAT", fVbargraph0)("float", fConst51)("float", fConst52)("float", fConst53)("float", fConst54)("float", fConst55)("float[3]", fIIR26)("float", fConst56)("float", fConst57)("float", fConst58)("float", fConst59)("float", fConst60)("float", fConst61)("float", fConst62)("float", fConst63)("float[3]", fIIR25)("float", fConst64)("float", fConst65)("float", fConst66)("float", fConst67)("float", fConst68)("float", fConst69)("float", fConst70)("float[3]", fIIR24)("float", fConst71)("float", fConst72)("float", fConst73)("float", fConst74)("float", fConst75)("float", fConst76)("float", fConst77)("float", fConst78)("float", fConst79)("float", fConst80)("float[3]", fIIR23)("float", fConst81)("float", fConst82)("float", fConst83)("float", fConst84)("float", fConst85)("float", fConst86)("float", fConst87)("float", fConst88)("float[3]", fIIR22)("float", fConst89)("float", fConst90)("float", fConst91)("float", fConst92)("float", fConst93)("float", fConst94)("float", fConst95)("float[3]", fIIR21)("float", fConst96)("float", fConst97)("float", fConst98)("float", fConst99)("float", fConst100)("float", fConst101)("float", fConst102)("float", fConst103)("float", fConst104)("float", fConst105)("float[3]", fIIR20)("float", fConst106)("float", fConst107)("float", fConst108)("float", fConst109)("float", fConst110)("float", fConst111)("float", fConst112)("float", fConst113)("float[3]", fIIR19)("float", fConst114)("float", fConst115)("float", fConst116)("float", fConst117)("float", fConst118)("float", fConst119)("float", fConst120)("float[3]", fIIR18)("float", fConst121)("float", fConst122)("float", fConst123)("float", fConst124)("float", fConst125)("float", fConst126)("float", fConst127)("float", fConst128)("float", fConst129)("float", fConst130)("float[3]", fIIR17)("float", fConst131)("float", fConst132)("float", fConst133)("float", fConst134)("float", fConst135)("float", fConst136)("float", fConst137)("float", fConst138)("float[3]", fIIR16)("float", fConst139)("float", fConst140)("float", fConst141)("float", fConst142)("float", fConst143)("float", fConst144)("float", fConst145)("float[3]", fIIR15)("float", fConst146)("float", fConst147)("float", fConst148)("float", fConst149)("float", fConst150)("float", fConst151)("float", fConst152)("float", fConst153)("float", fConst154)("float", fConst155)("float[3]", fIIR14)("float", fConst156)("float", fConst157)("float", fConst158)("float", fConst159)("float", fConst160)("float", fConst161)("float", fConst162)("float", fConst163)("float[3]", fIIR13)("float", fConst164)("float", fConst165)("float", fConst166)("float", fConst167)("float", fConst168)("float", fConst169)("float", fConst170)("float", fConst171)("float[3]", fIIR12)("float", fConst172)("float", fConst173)("float", fConst174)("float[2]", fIRM2)("FAUSTFLOAT", fVbargraph1)("float", fConst175)("float", fConst176)("float", fConst177)("float", fConst178)("float", fConst179)("float[3]", fIIR41)("float", fConst180)("float", fConst181)("float", fConst182)("float", fConst183)("float", fConst184)("float", fConst185)("float", fConst186)("float", fConst187)("float[3]", fIIR40)("float", fConst188)("float", fConst189)("float", fConst190)("float", fConst191)("float", fConst192)("float", fConst193)("float", fConst194)("float[3]", fIIR39)("float", fConst195)("float", fConst196)("float", fConst197)("float", fConst198)("float", fConst199)("float", fConst200)("float", fConst201)("float", fConst202)("float", fConst203)("float", fConst204)("float[3]", fIIR38)("float", fConst205)("float", fConst206)("float", fConst207)("float", fConst208)("float", fConst209)("float", fConst210)("float", fConst211)("float", fConst212)("float[3]", fIIR37)("float", fConst213)("float", fConst214)("float", fConst215)("float", fConst216)("float", fConst217)("float", fConst218)("float", fConst219)("float[3]", fIIR36)("float", fConst220)("float", fConst221)("float", fConst222)("float", fConst223)("float", fConst224)("float", fConst225)("float", fConst226)("float", fConst227)("float", fConst228)("float", fConst229)("float[3]", fIIR35)("float", fConst230)("float", fConst231)("float", fConst232)("float", fConst233)("float", fConst234)("float", fConst235)("float", fConst236)("float", fConst237)("float[3]", fIIR34)("float", fConst238)("float", fConst239)("float", fConst240)("float", fConst241)("float", fConst242)("float", fConst243)("float", fConst244)("float[3]", fIIR33)("float", fConst245)("float", fConst246)("float", fConst247)("float", fConst248)("float", fConst249)("float", fConst250)("float", fConst251)("float", fConst252)("float", fConst253)("float", fConst254)("float[3]", fIIR32)("float", fConst255)("float", fConst256)("float", fConst257)("float", fConst258)("float", fConst259)("float", fConst260)("float", fConst261)("float", fConst262)("float[3]", fIIR31)("float", fConst263)("float", fConst264)("float", fConst265)("float", fConst266)("float", fConst267)("float", fConst268)("float", fConst269)("float[3]", fIIR30)("float", fConst270)("float", fConst271)("float", fConst272)("float", fConst273)("float", fConst274)("float", fConst275)("float", fConst276)("float", fConst277)("float", fConst278)("float", fConst279)("float[3]", fIIR29)("float", fConst280)("float", fConst281)("float", fConst282)("float", fConst283)("float", fConst284)("float", fConst285)("float", fConst286)("float", fConst287)("float[3]", fIIR28)("float", fConst288)("float", fConst289)("float", fConst290)("float", fConst291)("float", fConst292)("float", fConst293)("float", fConst294)("float", fConst295)("float[3]", fIIR27)("float", fConst296)("float", fConst297)("float", fConst298)("float[2]", fIRM3)("FAUSTFLOAT", fVbargraph2)("float", fConst299)("float", fConst300)("float", fConst301)("float", fConst302)("float", fConst303)("float[3]", fIIR56)("float", fConst304)("float", fConst305)("float", fConst306)("float", fConst307)("float", fConst308)("float", fConst309)("float", fConst310)("float", fConst311)("float[3]", fIIR55)("float", fConst312)("float", fConst313)("float", fConst314)("float", fConst315)("float", fConst316)("float", fConst317)("float", fConst318)("float[3]", fIIR54)("float", fConst319)("float", fConst320)("float", fConst321)("float", fConst322)("float", fConst323)("float", fConst324)("float", fConst325)("float", fConst326)("float", fConst327)("float", fConst328)("float[3]", fIIR53)("float", fConst329)("float", fConst330)("float", fConst331)("float", fConst332)("float", fConst333)("float", fConst334)("float", fConst335)("float", fConst336)("float[3]", fIIR52)("float", fConst337)("float", fConst338)("float", fConst339)("float", fConst340)("float", fConst341)("float", fConst342)("float", fConst343)("float[3]", fIIR51)("float", fConst344)("float", fConst345)("float", fConst346)("float", fConst347)("float", fConst348)("float", fConst349)("float", fConst350)("float", fConst351)("float", fConst352)("float", fConst353)("float[3]", fIIR50)("float", fConst354)("float", fConst355)("float", fConst356)("float", fConst357)("float", fConst358)("float", fConst359)("float", fConst360)("float", fConst361)("float[3]", fIIR49)("float", fConst362)("float", fConst363)("float", fConst364)("float", fConst365)("float", fConst366)("float", fConst367)("float", fConst368)("float[3]", fIIR48)("float", fConst369)("float", fConst370)("float", fConst371)("float", fConst372)("float", fConst373)("float", fConst374)("float", fConst375)("float", fConst376)("float", fConst377)("float", fConst378)("float[3]", fIIR47)("float", fConst379)("float", fConst380)("float", fConst381)("float", fConst382)("float", fConst383)("float", fConst384)("float", fConst385)("float", fConst386)("float[3]", fIIR46)("float", fConst387)("float", fConst388)("float", fConst389)("float", fConst390)("float", fConst391)("float", fConst392)("float", fConst393)("float[3]", fIIR45)("float", fConst394)("float", fConst395)("float", fConst396)("float", fConst397)("float", fConst398)("float", fConst399)("float", fConst400)("float", fConst401)("float", fConst402)("float", fConst403)("float[3]", fIIR44)("float", fConst404)("float", fConst405)("float", fConst406)("float", fConst407)("float", fConst408)("float", fConst409)("float", fConst410)("float", fConst411)("float[3]", fIIR43)("float", fConst412)("float", fConst413)("float", fConst414)("float", fConst415)("float", fConst416)("float", fConst417)("float", fConst418)("float", fConst419)("float[3]", fIIR42)("float", fConst420)("float", fConst421)("float", fConst422)("float[2]", fIRM4)("FAUSTFLOAT", fVbargraph3)("float", fConst423)("float", fConst424)("float", fConst425)("float", fConst426)("float", fConst427)("float[3]", fIIR59)("float", fConst428)("float", fConst429)("float", fConst430)("float", fConst431)("float", fConst432)("float", fConst433)("float", fConst434)("float", fConst435)("float[3]", fIIR58)("float", fConst436)("float", fConst437)("float", fConst438)("float", fConst439)("float", fConst440)("float", fConst441)("float", fConst442)("float", fConst443)("float[3]", fIIR57)("float", fConst444)("float", fConst445)("float", fConst446)("float[2]", fIRM5)("FAUSTFLOAT", fVbargraph4)("float", fConst447)("float", fConst448)("float", fConst449)("float", fConst450)("float", fConst451)("float[3]", fIIR62)("float", fConst452)("float", fConst453)("float", fConst454)("float", fConst455)("float", fConst456)("float", fConst457)("float", fConst458)("float", fConst459)("float[3]", fIIR61)("float", fConst460)("float", fConst461)("float", fConst462)("float", fConst463)("float", fConst464)("float", fConst465)("float", fConst466)("float", fConst467)("float[3]", fIIR60)("float", fConst468)("float", fConst469)("float", fConst470)("float[2]", fIRM6)("FAUSTFLOAT", fVbargraph5)("float", fConst471)("float", fConst472)("float", fConst473)("float", fConst474)("float", fConst475)("float[3]", fIIR65)("float", fConst476)("float", fConst477)("float", fConst478)("float", fConst479)("float", fConst480)("float", fConst481)("float", fConst482)("float", fConst483)("float[3]", fIIR64)("float", fConst484)("float", fConst485)("float", fConst486)("float", fConst487)("float", fConst488)("float", fConst489)("float", fConst490)("float", fConst491)("float[3]", fIIR63)("float", fConst492)("float", fConst493)("float", fConst494)("float[2]", fIRM7)("FAUSTFLOAT", fVbargraph6)("float", fConst495)("float", fConst496)("float", fConst497)("float", fConst498)("float", fConst499)("float[3]", fIIR71)("float", fConst500)("float", fConst501)("float", fConst502)("float", fConst503)("float", fConst504)("float", fConst505)("float", fConst506)("float", fConst507)("float[3]", fIIR70)("float", fConst508)("float", fConst509)("float", fConst510)("float", fConst511)("float", fConst512)("float", fConst513)("float", fConst514)("float[3]", fIIR69)("float", fConst515)("float", fConst516)("float", fConst517)("float", fConst518)("float", fConst519)("float", fConst520)("float", fConst521)("float", fConst522)("float", fConst523)("float", fConst524)("float[3]", fIIR68)("float", fConst525)("float", fConst526)("float", fConst527)("float", fConst528)("float", fConst529)("float", fConst530)("float", fConst531)("float", fConst532)("float[3]", fIIR67)("float", fConst533)("float", fConst534)("float", fConst535)("float", fConst536)("float", fConst537)("float", fConst538)("float", fConst539)("float", fConst540)("float[3]", fIIR66)("float", fConst541)("float", fConst542)("float", fConst543)("float[2]", fIRM8)("FAUSTFLOAT", fVbargraph7)("float", fConst544)("float", fConst545)("float", fConst546)("float", fConst547)("float", fConst548)("float[3]", fIIR74)("float", fConst549)("float", fConst550)("float", fConst551)("float", fConst552)("float", fConst553)("float", fConst554)("float", fConst555)("float", fConst556)("float[3]", fIIR73)("float", fConst557)("float", fConst558)("float", fConst559)("float", fConst560)("float", fConst561)("float", fConst562)("float", fConst563)("float", fConst564)("float[3]", fIIR72)("float", fConst565)("float", fConst566)("float", fConst567)("float[2]", fIRM9)("FAUSTFLOAT", fVbargraph8)("float", fConst568)("float", fConst569)("float", fConst570)("float", fConst571)("float", fConst572)("float[3]", fIIR77)("float", fConst573)("float", fConst574)("float", fConst575)("float", fConst576)("float", fConst577)("float", fConst578)("float", fConst579)("float", fConst580)("float[3]", fIIR76)("float", fConst581)("float", fConst582)("float", fConst583)("float", fConst584)("float", fConst585)("float", fConst586)("float", fConst587)("float", fConst588)("float[3]", fIIR75)("float", fConst589)("float", fConst590)("float", fConst591)("float[2]", fIRM10)("FAUSTFLOAT", fVbargraph9)("float", fConst592)("float", fConst593)("float", fConst594)("float", fConst595)("float", fConst596)("float[3]", fIIR80)("float", fConst597)("float", fConst598)("float", fConst599)("float", fConst600)("float", fConst601)("float", fConst602)("float", fConst603)("float", fConst604)("float[3]", fIIR79)("float", fConst605)("float", fConst606)("float", fConst607)("float", fConst608)("float", fConst609)("float", fConst610)("float", fConst611)("float", fConst612)("float[3]", fIIR78)("float", fConst613)("float", fConst614)("float", fConst615)("float[2]", fIRM11)("FAUSTFLOAT", fVbargraph10)("float", fConst616)("float", fConst617)("float", fConst618)("float", fConst619)("float", fConst620)("float[3]", fIIR83)("float", fConst621)("float", fConst622)("float", fConst623)("float", fConst624)("float", fConst625)("float", fConst626)("float", fConst627)("float", fConst628)("float[3]", fIIR82)("float", fConst629)("float", fConst630)("float", fConst631)("float", fConst632)("float", fConst633)("float", fConst634)("float", fConst635)("float[3]", fIIR81)("float", fConst636)("float", fConst637)("float[2]", fIRM12)("FAUSTFLOAT", fVbargraph11)("float", fConst638)("float", fConst639)("float", fConst640)("float", fConst641)("float", fConst642)("float[3]", fIIR86)("float", fConst643)("float", fConst644)("float", fConst645)("float", fConst646)("float", fConst647)("float", fConst648)("float", fConst649)("float", fConst650)("float[3]", fIIR85)("float", fConst651)("float", fConst652)("float", fConst653)("float", fConst654)("float", fConst655)("float", fConst656)("float", fConst657)("float", fConst658)("float[3]", fIIR84)("float", fConst659)("float", fConst660)("float", fConst661)("float[2]", fIRM13)("FAUSTFLOAT", fVbargraph12)("float", fConst662)("float", fConst663)("float", fConst664)("float", fConst665)("float", fConst666)("float[3]", fIIR89)("float", fConst667)("float", fConst668)("float", fConst669)("float", fConst670)("float", fConst671)("float", fConst672)("float", fConst673)("float", fConst674)("float[3]", fIIR88)("float", fConst675)("float", fConst676)("float", fConst677)("float", fConst678)("float", fConst679)("float", fConst680)("float", fConst681)("float", fConst682)("float[3]", fIIR87)("float", fConst683)("float", fConst684)("float", fConst685)("float[2]", fIRM14)("FAUSTFLOAT", fVbargraph13)("float", fConst686)("float", fConst687)("float", fConst688)("float", fConst689)("float", fConst690)("float[3]", fIIR92)("float", fConst691)("float", fConst692)("float", fConst693)("float", fConst694)("float", fConst695)("float", fConst696)("float", fConst697)("float", fConst698)("float[3]", fIIR91)("float", fConst699)("float", fConst700)("float", fConst701)("float", fConst702)("float", fConst703)("float", fConst704)("float", fConst705)("float", fConst706)("float[3]", fIIR90)("float", fConst707)("float", fConst708)("float", fConst709)("float[2]", fIRM15)("FAUSTFLOAT", fVbargraph14)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.041666668f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.0052083335f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), BinopInst("*", Float(0.041666668f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(0.0052083335f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("*", Float(0.041666668f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("*", Float(0.0052083335f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("*", Float(0.083333336f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("/", Float(1.3333334f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(0.013888889f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("*", Float(0.083333336f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), FunCallInst("tanf", BinopInst("/", Float(50265.484f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst24, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst26, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst27, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst25, kStruct))))
	StoreVarInst(Address(fConst28, kStruct), BinopInst("+", LoadVarInst(Address(fConst26, kStruct)), LoadVarInst(Address(fConst27, kStruct))))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst28, kStruct)))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fConst26, kStruct))), LoadVarInst(Address(fConst28, kStruct))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst32, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst31, kStruct))), LoadVarInst(Address(fConst28, kStruct))))
	StoreVarInst(Address(fConst33, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst31, kStruct))), LoadVarInst(Address(fConst28, kStruct)))))
	StoreVarInst(Address(fConst34, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("+", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst35, kStruct))))
	StoreVarInst(Address(fConst37, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst36, kStruct)))))
	StoreVarInst(Address(fConst38, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fConst34, kStruct))), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst39, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst39, kStruct))), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst41, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst39, kStruct))), LoadVarInst(Address(fConst36, kStruct)))))
	StoreVarInst(Address(fConst42, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst43, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("+", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fConst43, kStruct))))
	StoreVarInst(Address(fConst45, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst44, kStruct)))))
	StoreVarInst(Address(fConst46, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst43, kStruct)), LoadVarInst(Address(fConst42, kStruct))), LoadVarInst(Address(fConst44, kStruct))))
	StoreVarInst(Address(fConst47, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst48, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst47, kStruct))), LoadVarInst(Address(fConst44, kStruct))))
	StoreVarInst(Address(fConst49, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst47, kStruct))), LoadVarInst(Address(fConst44, kStruct)))))
	StoreVarInst(Address(fConst50, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst51, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst52, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(0.2452915f)))
	StoreVarInst(Address(fConst53, kStruct), BinopInst("+", LoadVarInst(Address(fConst51, kStruct)), LoadVarInst(Address(fConst52, kStruct))))
	StoreVarInst(Address(fConst54, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst53, kStruct)))))
	StoreVarInst(Address(fConst55, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fConst51, kStruct))), LoadVarInst(Address(fConst53, kStruct))))
	StoreVarInst(Address(fConst56, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst57, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst56, kStruct))), LoadVarInst(Address(fConst53, kStruct))))
	StoreVarInst(Address(fConst58, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst56, kStruct))), LoadVarInst(Address(fConst53, kStruct)))))
	StoreVarInst(Address(fConst59, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst60, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(0.6896214f)))
	StoreVarInst(Address(fConst61, kStruct), BinopInst("+", LoadVarInst(Address(fConst59, kStruct)), LoadVarInst(Address(fConst60, kStruct))))
	StoreVarInst(Address(fConst62, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst61, kStruct)))))
	StoreVarInst(Address(fConst63, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst60, kStruct)), LoadVarInst(Address(fConst59, kStruct))), LoadVarInst(Address(fConst61, kStruct))))
	StoreVarInst(Address(fConst64, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst61, kStruct))))
	StoreVarInst(Address(fConst65, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst61, kStruct)))))
	StoreVarInst(Address(fConst66, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst67, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(1.0693583f)))
	StoreVarInst(Address(fConst68, kStruct), BinopInst("+", LoadVarInst(Address(fConst66, kStruct)), LoadVarInst(Address(fConst67, kStruct))))
	StoreVarInst(Address(fConst69, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst68, kStruct)))))
	StoreVarInst(Address(fConst70, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst67, kStruct)), LoadVarInst(Address(fConst66, kStruct))), LoadVarInst(Address(fConst68, kStruct))))
	StoreVarInst(Address(fConst71, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst68, kStruct))))
	StoreVarInst(Address(fConst72, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst68, kStruct)))))
	StoreVarInst(Address(fConst73, kStruct), FunCallInst("tanf", BinopInst("/", Float(31665.27f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst74, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst75, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst76, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst77, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst78, kStruct), BinopInst("+", LoadVarInst(Address(fConst76, kStruct)), LoadVarInst(Address(fConst77, kStruct))))
	StoreVarInst(Address(fConst79, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst78, kStruct)))))
	StoreVarInst(Address(fConst80, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst77, kStruct)), LoadVarInst(Address(fConst76, kStruct))), LoadVarInst(Address(fConst78, kStruct))))
	StoreVarInst(Address(fConst81, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst82, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst81, kStruct))), LoadVarInst(Address(fConst78, kStruct))))
	StoreVarInst(Address(fConst83, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst81, kStruct))), LoadVarInst(Address(fConst78, kStruct)))))
	StoreVarInst(Address(fConst84, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst85, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst86, kStruct), BinopInst("+", LoadVarInst(Address(fConst84, kStruct)), LoadVarInst(Address(fConst85, kStruct))))
	StoreVarInst(Address(fConst87, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst86, kStruct)))))
	StoreVarInst(Address(fConst88, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst85, kStruct)), LoadVarInst(Address(fConst84, kStruct))), LoadVarInst(Address(fConst86, kStruct))))
	StoreVarInst(Address(fConst89, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst86, kStruct))))
	StoreVarInst(Address(fConst90, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst86, kStruct)))))
	StoreVarInst(Address(fConst91, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst92, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst93, kStruct), BinopInst("+", LoadVarInst(Address(fConst91, kStruct)), LoadVarInst(Address(fConst92, kStruct))))
	StoreVarInst(Address(fConst94, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst93, kStruct)))))
	StoreVarInst(Address(fConst95, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst92, kStruct)), LoadVarInst(Address(fConst91, kStruct))), LoadVarInst(Address(fConst93, kStruct))))
	StoreVarInst(Address(fConst96, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst93, kStruct))))
	StoreVarInst(Address(fConst97, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst93, kStruct)))))
	StoreVarInst(Address(fConst98, kStruct), FunCallInst("tanf", BinopInst("/", Float(19947.87f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst99, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst100, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst101, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst102, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst103, kStruct), BinopInst("+", LoadVarInst(Address(fConst101, kStruct)), LoadVarInst(Address(fConst102, kStruct))))
	StoreVarInst(Address(fConst104, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst103, kStruct)))))
	StoreVarInst(Address(fConst105, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst102, kStruct)), LoadVarInst(Address(fConst101, kStruct))), LoadVarInst(Address(fConst103, kStruct))))
	StoreVarInst(Address(fConst106, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst107, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst106, kStruct))), LoadVarInst(Address(fConst103, kStruct))))
	StoreVarInst(Address(fConst108, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst106, kStruct))), LoadVarInst(Address(fConst103, kStruct)))))
	StoreVarInst(Address(fConst109, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst110, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst111, kStruct), BinopInst("+", LoadVarInst(Address(fConst109, kStruct)), LoadVarInst(Address(fConst110, kStruct))))
	StoreVarInst(Address(fConst112, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst111, kStruct)))))
	StoreVarInst(Address(fConst113, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst110, kStruct)), LoadVarInst(Address(fConst109, kStruct))), LoadVarInst(Address(fConst111, kStruct))))
	StoreVarInst(Address(fConst114, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst111, kStruct))))
	StoreVarInst(Address(fConst115, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst111, kStruct)))))
	StoreVarInst(Address(fConst116, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst117, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst118, kStruct), BinopInst("+", LoadVarInst(Address(fConst116, kStruct)), LoadVarInst(Address(fConst117, kStruct))))
	StoreVarInst(Address(fConst119, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst118, kStruct)))))
	StoreVarInst(Address(fConst120, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst117, kStruct)), LoadVarInst(Address(fConst116, kStruct))), LoadVarInst(Address(fConst118, kStruct))))
	StoreVarInst(Address(fConst121, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst118, kStruct))))
	StoreVarInst(Address(fConst122, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst118, kStruct)))))
	StoreVarInst(Address(fConst123, kStruct), FunCallInst("tanf", BinopInst("/", Float(12566.371f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst124, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst125, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst126, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst127, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst128, kStruct), BinopInst("+", LoadVarInst(Address(fConst126, kStruct)), LoadVarInst(Address(fConst127, kStruct))))
	StoreVarInst(Address(fConst129, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst128, kStruct)))))
	StoreVarInst(Address(fConst130, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst127, kStruct)), LoadVarInst(Address(fConst126, kStruct))), LoadVarInst(Address(fConst128, kStruct))))
	StoreVarInst(Address(fConst131, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst132, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst131, kStruct))), LoadVarInst(Address(fConst128, kStruct))))
	StoreVarInst(Address(fConst133, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst131, kStruct))), LoadVarInst(Address(fConst128, kStruct)))))
	StoreVarInst(Address(fConst134, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst135, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst136, kStruct), BinopInst("+", LoadVarInst(Address(fConst134, kStruct)), LoadVarInst(Address(fConst135, kStruct))))
	StoreVarInst(Address(fConst137, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst136, kStruct)))))
	StoreVarInst(Address(fConst138, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst135, kStruct)), LoadVarInst(Address(fConst134, kStruct))), LoadVarInst(Address(fConst136, kStruct))))
	StoreVarInst(Address(fConst139, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst136, kStruct))))
	StoreVarInst(Address(fConst140, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst136, kStruct)))))
	StoreVarInst(Address(fConst141, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst142, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst143, kStruct), BinopInst("+", LoadVarInst(Address(fConst141, kStruct)), LoadVarInst(Address(fConst142, kStruct))))
	StoreVarInst(Address(fConst144, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst143, kStruct)))))
	StoreVarInst(Address(fConst145, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst142, kStruct)), LoadVarInst(Address(fConst141, kStruct))), LoadVarInst(Address(fConst143, kStruct))))
	StoreVarInst(Address(fConst146, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst143, kStruct))))
	StoreVarInst(Address(fConst147, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst143, kStruct)))))
	StoreVarInst(Address(fConst148, kStruct), FunCallInst("tanf", BinopInst("/", Float(7916.3174f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst149, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst150, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst151, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst152, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst153, kStruct), BinopInst("+", LoadVarInst(Address(fConst151, kStruct)), LoadVarInst(Address(fConst152, kStruct))))
	StoreVarInst(Address(fConst154, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst153, kStruct)))))
	StoreVarInst(Address(fConst155, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst152, kStruct)), LoadVarInst(Address(fConst151, kStruct))), LoadVarInst(Address(fConst153, kStruct))))
	StoreVarInst(Address(fConst156, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst157, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst156, kStruct))), LoadVarInst(Address(fConst153, kStruct))))
	StoreVarInst(Address(fConst158, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst156, kStruct))), LoadVarInst(Address(fConst153, kStruct)))))
	StoreVarInst(Address(fConst159, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst160, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst161, kStruct), BinopInst("+", LoadVarInst(Address(fConst159, kStruct)), LoadVarInst(Address(fConst160, kStruct))))
	StoreVarInst(Address(fConst162, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst161, kStruct)))))
	StoreVarInst(Address(fConst163, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst160, kStruct)), LoadVarInst(Address(fConst159, kStruct))), LoadVarInst(Address(fConst161, kStruct))))
	StoreVarInst(Address(fConst164, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst165, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst164, kStruct))), LoadVarInst(Address(fConst161, kStruct))))
	StoreVarInst(Address(fConst166, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst164, kStruct))), LoadVarInst(Address(fConst161, kStruct)))))
	StoreVarInst(Address(fConst167, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst168, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst169, kStruct), BinopInst("+", LoadVarInst(Address(fConst167, kStruct)), LoadVarInst(Address(fConst168, kStruct))))
	StoreVarInst(Address(fConst170, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst169, kStruct)))))
	StoreVarInst(Address(fConst171, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst168, kStruct)), LoadVarInst(Address(fConst167, kStruct))), LoadVarInst(Address(fConst169, kStruct))))
	StoreVarInst(Address(fConst172, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst173, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst172, kStruct))), LoadVarInst(Address(fConst169, kStruct))))
	StoreVarInst(Address(fConst174, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst172, kStruct))), LoadVarInst(Address(fConst169, kStruct)))))
	StoreVarInst(Address(fConst175, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst176, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst177, kStruct), BinopInst("+", LoadVarInst(Address(fConst175, kStruct)), LoadVarInst(Address(fConst176, kStruct))))
	StoreVarInst(Address(fConst178, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst179, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst176, kStruct)), LoadVarInst(Address(fConst175, kStruct))), LoadVarInst(Address(fConst177, kStruct))))
	StoreVarInst(Address(fConst180, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst181, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst180, kStruct))), LoadVarInst(Address(fConst177, kStruct))))
	StoreVarInst(Address(fConst182, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst180, kStruct))), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst183, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst184, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst185, kStruct), BinopInst("+", LoadVarInst(Address(fConst183, kStruct)), LoadVarInst(Address(fConst184, kStruct))))
	StoreVarInst(Address(fConst186, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst185, kStruct)))))
	StoreVarInst(Address(fConst187, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst184, kStruct)), LoadVarInst(Address(fConst183, kStruct))), LoadVarInst(Address(fConst185, kStruct))))
	StoreVarInst(Address(fConst188, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst185, kStruct))))
	StoreVarInst(Address(fConst189, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst185, kStruct)))))
	StoreVarInst(Address(fConst190, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst191, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst192, kStruct), BinopInst("+", LoadVarInst(Address(fConst190, kStruct)), LoadVarInst(Address(fConst191, kStruct))))
	StoreVarInst(Address(fConst193, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst192, kStruct)))))
	StoreVarInst(Address(fConst194, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst191, kStruct)), LoadVarInst(Address(fConst190, kStruct))), LoadVarInst(Address(fConst192, kStruct))))
	StoreVarInst(Address(fConst195, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst192, kStruct))))
	StoreVarInst(Address(fConst196, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst192, kStruct)))))
	StoreVarInst(Address(fConst197, kStruct), FunCallInst("tanf", BinopInst("/", Float(4986.9673f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst198, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst199, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst200, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst201, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst202, kStruct), BinopInst("+", LoadVarInst(Address(fConst200, kStruct)), LoadVarInst(Address(fConst201, kStruct))))
	StoreVarInst(Address(fConst203, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst202, kStruct)))))
	StoreVarInst(Address(fConst204, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst201, kStruct)), LoadVarInst(Address(fConst200, kStruct))), LoadVarInst(Address(fConst202, kStruct))))
	StoreVarInst(Address(fConst205, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst206, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst205, kStruct))), LoadVarInst(Address(fConst202, kStruct))))
	StoreVarInst(Address(fConst207, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst205, kStruct))), LoadVarInst(Address(fConst202, kStruct)))))
	StoreVarInst(Address(fConst208, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst209, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst210, kStruct), BinopInst("+", LoadVarInst(Address(fConst208, kStruct)), LoadVarInst(Address(fConst209, kStruct))))
	StoreVarInst(Address(fConst211, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst210, kStruct)))))
	StoreVarInst(Address(fConst212, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst209, kStruct)), LoadVarInst(Address(fConst208, kStruct))), LoadVarInst(Address(fConst210, kStruct))))
	StoreVarInst(Address(fConst213, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst210, kStruct))))
	StoreVarInst(Address(fConst214, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst210, kStruct)))))
	StoreVarInst(Address(fConst215, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst216, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst217, kStruct), BinopInst("+", LoadVarInst(Address(fConst215, kStruct)), LoadVarInst(Address(fConst216, kStruct))))
	StoreVarInst(Address(fConst218, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst217, kStruct)))))
	StoreVarInst(Address(fConst219, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst216, kStruct)), LoadVarInst(Address(fConst215, kStruct))), LoadVarInst(Address(fConst217, kStruct))))
	StoreVarInst(Address(fConst220, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst217, kStruct))))
	StoreVarInst(Address(fConst221, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst217, kStruct)))))
	StoreVarInst(Address(fConst222, kStruct), FunCallInst("tanf", BinopInst("/", Float(3141.5928f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst223, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst224, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst225, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst226, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst227, kStruct), BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), LoadVarInst(Address(fConst226, kStruct))))
	StoreVarInst(Address(fConst228, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst227, kStruct)))))
	StoreVarInst(Address(fConst229, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst226, kStruct)), LoadVarInst(Address(fConst225, kStruct))), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst230, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst231, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst230, kStruct))), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst232, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst230, kStruct))), LoadVarInst(Address(fConst227, kStruct)))))
	StoreVarInst(Address(fConst233, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst234, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst235, kStruct), BinopInst("+", LoadVarInst(Address(fConst233, kStruct)), LoadVarInst(Address(fConst234, kStruct))))
	StoreVarInst(Address(fConst236, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst235, kStruct)))))
	StoreVarInst(Address(fConst237, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst234, kStruct)), LoadVarInst(Address(fConst233, kStruct))), LoadVarInst(Address(fConst235, kStruct))))
	StoreVarInst(Address(fConst238, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst235, kStruct))))
	StoreVarInst(Address(fConst239, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst235, kStruct)))))
	StoreVarInst(Address(fConst240, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst241, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst242, kStruct), BinopInst("+", LoadVarInst(Address(fConst240, kStruct)), LoadVarInst(Address(fConst241, kStruct))))
	StoreVarInst(Address(fConst243, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst242, kStruct)))))
	StoreVarInst(Address(fConst244, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst241, kStruct)), LoadVarInst(Address(fConst240, kStruct))), LoadVarInst(Address(fConst242, kStruct))))
	StoreVarInst(Address(fConst245, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst242, kStruct))))
	StoreVarInst(Address(fConst246, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst242, kStruct)))))
	StoreVarInst(Address(fConst247, kStruct), FunCallInst("tanf", BinopInst("/", Float(1979.0793f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst248, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst249, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst250, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst251, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst252, kStruct), BinopInst("+", LoadVarInst(Address(fConst250, kStruct)), LoadVarInst(Address(fConst251, kStruct))))
	StoreVarInst(Address(fConst253, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst252, kStruct)))))
	StoreVarInst(Address(fConst254, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst251, kStruct)), LoadVarInst(Address(fConst250, kStruct))), LoadVarInst(Address(fConst252, kStruct))))
	StoreVarInst(Address(fConst255, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst256, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst255, kStruct))), LoadVarInst(Address(fConst252, kStruct))))
	StoreVarInst(Address(fConst257, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst255, kStruct))), LoadVarInst(Address(fConst252, kStruct)))))
	StoreVarInst(Address(fConst258, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst259, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst260, kStruct), BinopInst("+", LoadVarInst(Address(fConst258, kStruct)), LoadVarInst(Address(fConst259, kStruct))))
	StoreVarInst(Address(fConst261, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst260, kStruct)))))
	StoreVarInst(Address(fConst262, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst259, kStruct)), LoadVarInst(Address(fConst258, kStruct))), LoadVarInst(Address(fConst260, kStruct))))
	StoreVarInst(Address(fConst263, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst260, kStruct))))
	StoreVarInst(Address(fConst264, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst260, kStruct)))))
	StoreVarInst(Address(fConst265, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst266, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst267, kStruct), BinopInst("+", LoadVarInst(Address(fConst265, kStruct)), LoadVarInst(Address(fConst266, kStruct))))
	StoreVarInst(Address(fConst268, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst267, kStruct)))))
	StoreVarInst(Address(fConst269, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst266, kStruct)), LoadVarInst(Address(fConst265, kStruct))), LoadVarInst(Address(fConst267, kStruct))))
	StoreVarInst(Address(fConst270, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst267, kStruct))))
	StoreVarInst(Address(fConst271, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst267, kStruct)))))
	StoreVarInst(Address(fConst272, kStruct), FunCallInst("tanf", BinopInst("/", Float(1246.7418f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst273, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst274, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst275, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst276, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst277, kStruct), BinopInst("+", LoadVarInst(Address(fConst275, kStruct)), LoadVarInst(Address(fConst276, kStruct))))
	StoreVarInst(Address(fConst278, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst277, kStruct)))))
	StoreVarInst(Address(fConst279, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst276, kStruct)), LoadVarInst(Address(fConst275, kStruct))), LoadVarInst(Address(fConst277, kStruct))))
	StoreVarInst(Address(fConst280, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst281, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst280, kStruct))), LoadVarInst(Address(fConst277, kStruct))))
	StoreVarInst(Address(fConst282, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst280, kStruct))), LoadVarInst(Address(fConst277, kStruct)))))
	StoreVarInst(Address(fConst283, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst284, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst285, kStruct), BinopInst("+", LoadVarInst(Address(fConst283, kStruct)), LoadVarInst(Address(fConst284, kStruct))))
	StoreVarInst(Address(fConst286, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst285, kStruct)))))
	StoreVarInst(Address(fConst287, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst284, kStruct)), LoadVarInst(Address(fConst283, kStruct))), LoadVarInst(Address(fConst285, kStruct))))
	StoreVarInst(Address(fConst288, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst289, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst288, kStruct))), LoadVarInst(Address(fConst285, kStruct))))
	StoreVarInst(Address(fConst290, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst288, kStruct))), LoadVarInst(Address(fConst285, kStruct)))))
	StoreVarInst(Address(fConst291, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst292, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst293, kStruct), BinopInst("+", LoadVarInst(Address(fConst291, kStruct)), LoadVarInst(Address(fConst292, kStruct))))
	StoreVarInst(Address(fConst294, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst293, kStruct)))))
	StoreVarInst(Address(fConst295, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst292, kStruct)), LoadVarInst(Address(fConst291, kStruct))), LoadVarInst(Address(fConst293, kStruct))))
	StoreVarInst(Address(fConst296, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst297, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst296, kStruct))), LoadVarInst(Address(fConst293, kStruct))))
	StoreVarInst(Address(fConst298, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst296, kStruct))), LoadVarInst(Address(fConst293, kStruct)))))
	StoreVarInst(Address(fConst299, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst300, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst301, kStruct), BinopInst("+", LoadVarInst(Address(fConst299, kStruct)), LoadVarInst(Address(fConst300, kStruct))))
	StoreVarInst(Address(fConst302, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst301, kStruct)))))
	StoreVarInst(Address(fConst303, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst300, kStruct)), LoadVarInst(Address(fConst299, kStruct))), LoadVarInst(Address(fConst301, kStruct))))
	StoreVarInst(Address(fConst304, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst305, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst304, kStruct))), LoadVarInst(Address(fConst301, kStruct))))
	StoreVarInst(Address(fConst306, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst304, kStruct))), LoadVarInst(Address(fConst301, kStruct)))))
	StoreVarInst(Address(fConst307, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst308, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst309, kStruct), BinopInst("+", LoadVarInst(Address(fConst307, kStruct)), LoadVarInst(Address(fConst308, kStruct))))
	StoreVarInst(Address(fConst310, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst309, kStruct)))))
	StoreVarInst(Address(fConst311, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst308, kStruct)), LoadVarInst(Address(fConst307, kStruct))), LoadVarInst(Address(fConst309, kStruct))))
	StoreVarInst(Address(fConst312, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst309, kStruct))))
	StoreVarInst(Address(fConst313, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst309, kStruct)))))
	StoreVarInst(Address(fConst314, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst315, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst316, kStruct), BinopInst("+", LoadVarInst(Address(fConst314, kStruct)), LoadVarInst(Address(fConst315, kStruct))))
	StoreVarInst(Address(fConst317, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst316, kStruct)))))
	StoreVarInst(Address(fConst318, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst315, kStruct)), LoadVarInst(Address(fConst314, kStruct))), LoadVarInst(Address(fConst316, kStruct))))
	StoreVarInst(Address(fConst319, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst316, kStruct))))
	StoreVarInst(Address(fConst320, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst316, kStruct)))))
	StoreVarInst(Address(fConst321, kStruct), FunCallInst("tanf", BinopInst("/", Float(785.3982f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst322, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst323, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst324, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst325, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst326, kStruct), BinopInst("+", LoadVarInst(Address(fConst324, kStruct)), LoadVarInst(Address(fConst325, kStruct))))
	StoreVarInst(Address(fConst327, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst326, kStruct)))))
	StoreVarInst(Address(fConst328, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst325, kStruct)), LoadVarInst(Address(fConst324, kStruct))), LoadVarInst(Address(fConst326, kStruct))))
	StoreVarInst(Address(fConst329, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst330, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst329, kStruct))), LoadVarInst(Address(fConst326, kStruct))))
	StoreVarInst(Address(fConst331, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst329, kStruct))), LoadVarInst(Address(fConst326, kStruct)))))
	StoreVarInst(Address(fConst332, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst333, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst334, kStruct), BinopInst("+", LoadVarInst(Address(fConst332, kStruct)), LoadVarInst(Address(fConst333, kStruct))))
	StoreVarInst(Address(fConst335, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst334, kStruct)))))
	StoreVarInst(Address(fConst336, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst333, kStruct)), LoadVarInst(Address(fConst332, kStruct))), LoadVarInst(Address(fConst334, kStruct))))
	StoreVarInst(Address(fConst337, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst334, kStruct))))
	StoreVarInst(Address(fConst338, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst334, kStruct)))))
	StoreVarInst(Address(fConst339, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst340, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst341, kStruct), BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), LoadVarInst(Address(fConst340, kStruct))))
	StoreVarInst(Address(fConst342, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst341, kStruct)))))
	StoreVarInst(Address(fConst343, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst340, kStruct)), LoadVarInst(Address(fConst339, kStruct))), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst344, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst345, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst341, kStruct)))))
	StoreVarInst(Address(fConst346, kStruct), FunCallInst("tanf", BinopInst("/", Float(494.76984f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst347, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst348, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst349, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst350, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst351, kStruct), BinopInst("+", LoadVarInst(Address(fConst349, kStruct)), LoadVarInst(Address(fConst350, kStruct))))
	StoreVarInst(Address(fConst352, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst351, kStruct)))))
	StoreVarInst(Address(fConst353, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst350, kStruct)), LoadVarInst(Address(fConst349, kStruct))), LoadVarInst(Address(fConst351, kStruct))))
	StoreVarInst(Address(fConst354, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst355, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst354, kStruct))), LoadVarInst(Address(fConst351, kStruct))))
	StoreVarInst(Address(fConst356, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst354, kStruct))), LoadVarInst(Address(fConst351, kStruct)))))
	StoreVarInst(Address(fConst357, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst358, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst359, kStruct), BinopInst("+", LoadVarInst(Address(fConst357, kStruct)), LoadVarInst(Address(fConst358, kStruct))))
	StoreVarInst(Address(fConst360, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst359, kStruct)))))
	StoreVarInst(Address(fConst361, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst358, kStruct)), LoadVarInst(Address(fConst357, kStruct))), LoadVarInst(Address(fConst359, kStruct))))
	StoreVarInst(Address(fConst362, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst359, kStruct))))
	StoreVarInst(Address(fConst363, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst359, kStruct)))))
	StoreVarInst(Address(fConst364, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst365, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst366, kStruct), BinopInst("+", LoadVarInst(Address(fConst364, kStruct)), LoadVarInst(Address(fConst365, kStruct))))
	StoreVarInst(Address(fConst367, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst366, kStruct)))))
	StoreVarInst(Address(fConst368, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst365, kStruct)), LoadVarInst(Address(fConst364, kStruct))), LoadVarInst(Address(fConst366, kStruct))))
	StoreVarInst(Address(fConst369, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst366, kStruct))))
	StoreVarInst(Address(fConst370, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst366, kStruct)))))
	StoreVarInst(Address(fConst371, kStruct), FunCallInst("tanf", BinopInst("/", Float(311.68546f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst372, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst373, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst374, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst375, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst376, kStruct), BinopInst("+", LoadVarInst(Address(fConst374, kStruct)), LoadVarInst(Address(fConst375, kStruct))))
	StoreVarInst(Address(fConst377, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst376, kStruct)))))
	StoreVarInst(Address(fConst378, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst375, kStruct)), LoadVarInst(Address(fConst374, kStruct))), LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst379, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst380, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst379, kStruct))), LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst381, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst379, kStruct))), LoadVarInst(Address(fConst376, kStruct)))))
	StoreVarInst(Address(fConst382, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst383, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst384, kStruct), BinopInst("+", LoadVarInst(Address(fConst382, kStruct)), LoadVarInst(Address(fConst383, kStruct))))
	StoreVarInst(Address(fConst385, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst384, kStruct)))))
	StoreVarInst(Address(fConst386, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst383, kStruct)), LoadVarInst(Address(fConst382, kStruct))), LoadVarInst(Address(fConst384, kStruct))))
	StoreVarInst(Address(fConst387, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst384, kStruct))))
	StoreVarInst(Address(fConst388, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst384, kStruct)))))
	StoreVarInst(Address(fConst389, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst390, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst391, kStruct), BinopInst("+", LoadVarInst(Address(fConst389, kStruct)), LoadVarInst(Address(fConst390, kStruct))))
	StoreVarInst(Address(fConst392, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst391, kStruct)))))
	StoreVarInst(Address(fConst393, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst390, kStruct)), LoadVarInst(Address(fConst389, kStruct))), LoadVarInst(Address(fConst391, kStruct))))
	StoreVarInst(Address(fConst394, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst391, kStruct))))
	StoreVarInst(Address(fConst395, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst391, kStruct)))))
	StoreVarInst(Address(fConst396, kStruct), FunCallInst("tanf", BinopInst("/", Float(196.34955f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst397, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst398, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst399, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst400, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst401, kStruct), BinopInst("+", LoadVarInst(Address(fConst399, kStruct)), LoadVarInst(Address(fConst400, kStruct))))
	StoreVarInst(Address(fConst402, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst401, kStruct)))))
	StoreVarInst(Address(fConst403, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst400, kStruct)), LoadVarInst(Address(fConst399, kStruct))), LoadVarInst(Address(fConst401, kStruct))))
	StoreVarInst(Address(fConst404, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst405, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst404, kStruct))), LoadVarInst(Address(fConst401, kStruct))))
	StoreVarInst(Address(fConst406, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst404, kStruct))), LoadVarInst(Address(fConst401, kStruct)))))
	StoreVarInst(Address(fConst407, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst408, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst409, kStruct), BinopInst("+", LoadVarInst(Address(fConst407, kStruct)), LoadVarInst(Address(fConst408, kStruct))))
	StoreVarInst(Address(fConst410, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst409, kStruct)))))
	StoreVarInst(Address(fConst411, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst408, kStruct)), LoadVarInst(Address(fConst407, kStruct))), LoadVarInst(Address(fConst409, kStruct))))
	StoreVarInst(Address(fConst412, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst413, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst412, kStruct))), LoadVarInst(Address(fConst409, kStruct))))
	StoreVarInst(Address(fConst414, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst412, kStruct))), LoadVarInst(Address(fConst409, kStruct)))))
	StoreVarInst(Address(fConst415, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst416, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst417, kStruct), BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), LoadVarInst(Address(fConst416, kStruct))))
	StoreVarInst(Address(fConst418, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst417, kStruct)))))
	StoreVarInst(Address(fConst419, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst416, kStruct)), LoadVarInst(Address(fConst415, kStruct))), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst420, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst421, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst420, kStruct))), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst422, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst420, kStruct))), LoadVarInst(Address(fConst417, kStruct)))))
	StoreVarInst(Address(fConst423, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst424, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst425, kStruct), BinopInst("+", LoadVarInst(Address(fConst423, kStruct)), LoadVarInst(Address(fConst424, kStruct))))
	StoreVarInst(Address(fConst426, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst425, kStruct)))))
	StoreVarInst(Address(fConst427, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst424, kStruct)), LoadVarInst(Address(fConst423, kStruct))), LoadVarInst(Address(fConst425, kStruct))))
	StoreVarInst(Address(fConst428, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst429, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst428, kStruct))), LoadVarInst(Address(fConst425, kStruct))))
	StoreVarInst(Address(fConst430, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst428, kStruct))), LoadVarInst(Address(fConst425, kStruct)))))
	StoreVarInst(Address(fConst431, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst432, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst433, kStruct), BinopInst("+", LoadVarInst(Address(fConst431, kStruct)), LoadVarInst(Address(fConst432, kStruct))))
	StoreVarInst(Address(fConst434, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst433, kStruct)))))
	StoreVarInst(Address(fConst435, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst432, kStruct)), LoadVarInst(Address(fConst431, kStruct))), LoadVarInst(Address(fConst433, kStruct))))
	StoreVarInst(Address(fConst436, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst437, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst436, kStruct))), LoadVarInst(Address(fConst433, kStruct))))
	StoreVarInst(Address(fConst438, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst436, kStruct))), LoadVarInst(Address(fConst433, kStruct)))))
	StoreVarInst(Address(fConst439, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst440, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst441, kStruct), BinopInst("+", LoadVarInst(Address(fConst439, kStruct)), LoadVarInst(Address(fConst440, kStruct))))
	StoreVarInst(Address(fConst442, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst441, kStruct)))))
	StoreVarInst(Address(fConst443, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst440, kStruct)), LoadVarInst(Address(fConst439, kStruct))), LoadVarInst(Address(fConst441, kStruct))))
	StoreVarInst(Address(fConst444, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst445, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst444, kStruct))), LoadVarInst(Address(fConst441, kStruct))))
	StoreVarInst(Address(fConst446, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst444, kStruct))), LoadVarInst(Address(fConst441, kStruct)))))
	StoreVarInst(Address(fConst447, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst448, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst449, kStruct), BinopInst("+", LoadVarInst(Address(fConst447, kStruct)), LoadVarInst(Address(fConst448, kStruct))))
	StoreVarInst(Address(fConst450, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst449, kStruct)))))
	StoreVarInst(Address(fConst451, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst448, kStruct)), LoadVarInst(Address(fConst447, kStruct))), LoadVarInst(Address(fConst449, kStruct))))
	StoreVarInst(Address(fConst452, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst453, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst452, kStruct))), LoadVarInst(Address(fConst449, kStruct))))
	StoreVarInst(Address(fConst454, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst452, kStruct))), LoadVarInst(Address(fConst449, kStruct)))))
	StoreVarInst(Address(fConst455, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst456, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst457, kStruct), BinopInst("+", LoadVarInst(Address(fConst455, kStruct)), LoadVarInst(Address(fConst456, kStruct))))
	StoreVarInst(Address(fConst458, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst457, kStruct)))))
	StoreVarInst(Address(fConst459, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst456, kStruct)), LoadVarInst(Address(fConst455, kStruct))), LoadVarInst(Address(fConst457, kStruct))))
	StoreVarInst(Address(fConst460, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst461, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst460, kStruct))), LoadVarInst(Address(fConst457, kStruct))))
	StoreVarInst(Address(fConst462, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst460, kStruct))), LoadVarInst(Address(fConst457, kStruct)))))
	StoreVarInst(Address(fConst463, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst464, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst465, kStruct), BinopInst("+", LoadVarInst(Address(fConst463, kStruct)), LoadVarInst(Address(fConst464, kStruct))))
	StoreVarInst(Address(fConst466, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst465, kStruct)))))
	StoreVarInst(Address(fConst467, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst464, kStruct)), LoadVarInst(Address(fConst463, kStruct))), LoadVarInst(Address(fConst465, kStruct))))
	StoreVarInst(Address(fConst468, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst469, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst468, kStruct))), LoadVarInst(Address(fConst465, kStruct))))
	StoreVarInst(Address(fConst470, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst468, kStruct))), LoadVarInst(Address(fConst465, kStruct)))))
	StoreVarInst(Address(fConst471, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst472, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst473, kStruct), BinopInst("+", LoadVarInst(Address(fConst471, kStruct)), LoadVarInst(Address(fConst472, kStruct))))
	StoreVarInst(Address(fConst474, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst473, kStruct)))))
	StoreVarInst(Address(fConst475, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst472, kStruct)), LoadVarInst(Address(fConst471, kStruct))), LoadVarInst(Address(fConst473, kStruct))))
	StoreVarInst(Address(fConst476, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst477, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst476, kStruct))), LoadVarInst(Address(fConst473, kStruct))))
	StoreVarInst(Address(fConst478, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst476, kStruct))), LoadVarInst(Address(fConst473, kStruct)))))
	StoreVarInst(Address(fConst479, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst480, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst481, kStruct), BinopInst("+", LoadVarInst(Address(fConst479, kStruct)), LoadVarInst(Address(fConst480, kStruct))))
	StoreVarInst(Address(fConst482, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst483, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst480, kStruct)), LoadVarInst(Address(fConst479, kStruct))), LoadVarInst(Address(fConst481, kStruct))))
	StoreVarInst(Address(fConst484, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst485, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst484, kStruct))), LoadVarInst(Address(fConst481, kStruct))))
	StoreVarInst(Address(fConst486, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst484, kStruct))), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst487, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst488, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst489, kStruct), BinopInst("+", LoadVarInst(Address(fConst487, kStruct)), LoadVarInst(Address(fConst488, kStruct))))
	StoreVarInst(Address(fConst490, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst489, kStruct)))))
	StoreVarInst(Address(fConst491, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst488, kStruct)), LoadVarInst(Address(fConst487, kStruct))), LoadVarInst(Address(fConst489, kStruct))))
	StoreVarInst(Address(fConst492, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst493, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst492, kStruct))), LoadVarInst(Address(fConst489, kStruct))))
	StoreVarInst(Address(fConst494, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst492, kStruct))), LoadVarInst(Address(fConst489, kStruct)))))
	StoreVarInst(Address(fConst495, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst496, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst497, kStruct), BinopInst("+", LoadVarInst(Address(fConst495, kStruct)), LoadVarInst(Address(fConst496, kStruct))))
	StoreVarInst(Address(fConst498, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst497, kStruct)))))
	StoreVarInst(Address(fConst499, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst496, kStruct)), LoadVarInst(Address(fConst495, kStruct))), LoadVarInst(Address(fConst497, kStruct))))
	StoreVarInst(Address(fConst500, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst501, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst500, kStruct))), LoadVarInst(Address(fConst497, kStruct))))
	StoreVarInst(Address(fConst502, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst500, kStruct))), LoadVarInst(Address(fConst497, kStruct)))))
	StoreVarInst(Address(fConst503, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst504, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst505, kStruct), BinopInst("+", LoadVarInst(Address(fConst503, kStruct)), LoadVarInst(Address(fConst504, kStruct))))
	StoreVarInst(Address(fConst506, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst505, kStruct)))))
	StoreVarInst(Address(fConst507, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst504, kStruct)), LoadVarInst(Address(fConst503, kStruct))), LoadVarInst(Address(fConst505, kStruct))))
	StoreVarInst(Address(fConst508, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst505, kStruct))))
	StoreVarInst(Address(fConst509, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst505, kStruct)))))
	StoreVarInst(Address(fConst510, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst511, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst512, kStruct), BinopInst("+", LoadVarInst(Address(fConst510, kStruct)), LoadVarInst(Address(fConst511, kStruct))))
	StoreVarInst(Address(fConst513, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst512, kStruct)))))
	StoreVarInst(Address(fConst514, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst511, kStruct)), LoadVarInst(Address(fConst510, kStruct))), LoadVarInst(Address(fConst512, kStruct))))
	StoreVarInst(Address(fConst515, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst512, kStruct))))
	StoreVarInst(Address(fConst516, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst512, kStruct)))))
	StoreVarInst(Address(fConst517, kStruct), FunCallInst("tanf", BinopInst("/", Float(123.69246f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst518, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst519, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst520, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst521, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst522, kStruct), BinopInst("+", LoadVarInst(Address(fConst520, kStruct)), LoadVarInst(Address(fConst521, kStruct))))
	StoreVarInst(Address(fConst523, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst522, kStruct)))))
	StoreVarInst(Address(fConst524, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst521, kStruct)), LoadVarInst(Address(fConst520, kStruct))), LoadVarInst(Address(fConst522, kStruct))))
	StoreVarInst(Address(fConst525, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst526, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst525, kStruct))), LoadVarInst(Address(fConst522, kStruct))))
	StoreVarInst(Address(fConst527, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst525, kStruct))), LoadVarInst(Address(fConst522, kStruct)))))
	StoreVarInst(Address(fConst528, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst529, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst530, kStruct), BinopInst("+", LoadVarInst(Address(fConst528, kStruct)), LoadVarInst(Address(fConst529, kStruct))))
	StoreVarInst(Address(fConst531, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst530, kStruct)))))
	StoreVarInst(Address(fConst532, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst529, kStruct)), LoadVarInst(Address(fConst528, kStruct))), LoadVarInst(Address(fConst530, kStruct))))
	StoreVarInst(Address(fConst533, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst534, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst533, kStruct))), LoadVarInst(Address(fConst530, kStruct))))
	StoreVarInst(Address(fConst535, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst533, kStruct))), LoadVarInst(Address(fConst530, kStruct)))))
	StoreVarInst(Address(fConst536, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst537, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst538, kStruct), BinopInst("+", LoadVarInst(Address(fConst536, kStruct)), LoadVarInst(Address(fConst537, kStruct))))
	StoreVarInst(Address(fConst539, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst538, kStruct)))))
	StoreVarInst(Address(fConst540, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst537, kStruct)), LoadVarInst(Address(fConst536, kStruct))), LoadVarInst(Address(fConst538, kStruct))))
	StoreVarInst(Address(fConst541, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst542, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst541, kStruct))), LoadVarInst(Address(fConst538, kStruct))))
	StoreVarInst(Address(fConst543, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst541, kStruct))), LoadVarInst(Address(fConst538, kStruct)))))
	StoreVarInst(Address(fConst544, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst545, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst546, kStruct), BinopInst("+", LoadVarInst(Address(fConst544, kStruct)), LoadVarInst(Address(fConst545, kStruct))))
	StoreVarInst(Address(fConst547, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst546, kStruct)))))
	StoreVarInst(Address(fConst548, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst545, kStruct)), LoadVarInst(Address(fConst544, kStruct))), LoadVarInst(Address(fConst546, kStruct))))
	StoreVarInst(Address(fConst549, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst550, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst549, kStruct))), LoadVarInst(Address(fConst546, kStruct))))
	StoreVarInst(Address(fConst551, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst549, kStruct))), LoadVarInst(Address(fConst546, kStruct)))))
	StoreVarInst(Address(fConst552, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst553, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst554, kStruct), BinopInst("+", LoadVarInst(Address(fConst552, kStruct)), LoadVarInst(Address(fConst553, kStruct))))
	StoreVarInst(Address(fConst555, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst554, kStruct)))))
	StoreVarInst(Address(fConst556, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst553, kStruct)), LoadVarInst(Address(fConst552, kStruct))), LoadVarInst(Address(fConst554, kStruct))))
	StoreVarInst(Address(fConst557, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst558, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst557, kStruct))), LoadVarInst(Address(fConst554, kStruct))))
	StoreVarInst(Address(fConst559, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst557, kStruct))), LoadVarInst(Address(fConst554, kStruct)))))
	StoreVarInst(Address(fConst560, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst561, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst562, kStruct), BinopInst("+", LoadVarInst(Address(fConst560, kStruct)), LoadVarInst(Address(fConst561, kStruct))))
	StoreVarInst(Address(fConst563, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst562, kStruct)))))
	StoreVarInst(Address(fConst564, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst561, kStruct)), LoadVarInst(Address(fConst560, kStruct))), LoadVarInst(Address(fConst562, kStruct))))
	StoreVarInst(Address(fConst565, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst566, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst565, kStruct))), LoadVarInst(Address(fConst562, kStruct))))
	StoreVarInst(Address(fConst567, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst565, kStruct))), LoadVarInst(Address(fConst562, kStruct)))))
	StoreVarInst(Address(fConst568, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst569, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst570, kStruct), BinopInst("+", LoadVarInst(Address(fConst568, kStruct)), LoadVarInst(Address(fConst569, kStruct))))
	StoreVarInst(Address(fConst571, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst570, kStruct)))))
	StoreVarInst(Address(fConst572, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst569, kStruct)), LoadVarInst(Address(fConst568, kStruct))), LoadVarInst(Address(fConst570, kStruct))))
	StoreVarInst(Address(fConst573, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst574, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst573, kStruct))), LoadVarInst(Address(fConst570, kStruct))))
	StoreVarInst(Address(fConst575, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst573, kStruct))), LoadVarInst(Address(fConst570, kStruct)))))
	StoreVarInst(Address(fConst576, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst577, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst578, kStruct), BinopInst("+", LoadVarInst(Address(fConst576, kStruct)), LoadVarInst(Address(fConst577, kStruct))))
	StoreVarInst(Address(fConst579, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst578, kStruct)))))
	StoreVarInst(Address(fConst580, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst577, kStruct)), LoadVarInst(Address(fConst576, kStruct))), LoadVarInst(Address(fConst578, kStruct))))
	StoreVarInst(Address(fConst581, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst582, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst581, kStruct))), LoadVarInst(Address(fConst578, kStruct))))
	StoreVarInst(Address(fConst583, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst581, kStruct))), LoadVarInst(Address(fConst578, kStruct)))))
	StoreVarInst(Address(fConst584, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst585, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst586, kStruct), BinopInst("+", LoadVarInst(Address(fConst584, kStruct)), LoadVarInst(Address(fConst585, kStruct))))
	StoreVarInst(Address(fConst587, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst586, kStruct)))))
	StoreVarInst(Address(fConst588, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst585, kStruct)), LoadVarInst(Address(fConst584, kStruct))), LoadVarInst(Address(fConst586, kStruct))))
	StoreVarInst(Address(fConst589, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst590, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst589, kStruct))), LoadVarInst(Address(fConst586, kStruct))))
	StoreVarInst(Address(fConst591, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst589, kStruct))), LoadVarInst(Address(fConst586, kStruct)))))
	StoreVarInst(Address(fConst592, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst593, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst594, kStruct), BinopInst("+", LoadVarInst(Address(fConst592, kStruct)), LoadVarInst(Address(fConst593, kStruct))))
	StoreVarInst(Address(fConst595, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst594, kStruct)))))
	StoreVarInst(Address(fConst596, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst593, kStruct)), LoadVarInst(Address(fConst592, kStruct))), LoadVarInst(Address(fConst594, kStruct))))
	StoreVarInst(Address(fConst597, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst598, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst597, kStruct))), LoadVarInst(Address(fConst594, kStruct))))
	StoreVarInst(Address(fConst599, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst597, kStruct))), LoadVarInst(Address(fConst594, kStruct)))))
	StoreVarInst(Address(fConst600, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst601, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst602, kStruct), BinopInst("+", LoadVarInst(Address(fConst600, kStruct)), LoadVarInst(Address(fConst601, kStruct))))
	StoreVarInst(Address(fConst603, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst602, kStruct)))))
	StoreVarInst(Address(fConst604, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst601, kStruct)), LoadVarInst(Address(fConst600, kStruct))), LoadVarInst(Address(fConst602, kStruct))))
	StoreVarInst(Address(fConst605, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst606, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst605, kStruct))), LoadVarInst(Address(fConst602, kStruct))))
	StoreVarInst(Address(fConst607, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst605, kStruct))), LoadVarInst(Address(fConst602, kStruct)))))
	StoreVarInst(Address(fConst608, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst609, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst610, kStruct), BinopInst("+", LoadVarInst(Address(fConst608, kStruct)), LoadVarInst(Address(fConst609, kStruct))))
	StoreVarInst(Address(fConst611, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst610, kStruct)))))
	StoreVarInst(Address(fConst612, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst609, kStruct)), LoadVarInst(Address(fConst608, kStruct))), LoadVarInst(Address(fConst610, kStruct))))
	StoreVarInst(Address(fConst613, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst614, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst613, kStruct))), LoadVarInst(Address(fConst610, kStruct))))
	StoreVarInst(Address(fConst615, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst613, kStruct))), LoadVarInst(Address(fConst610, kStruct)))))
	StoreVarInst(Address(fConst616, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst617, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst618, kStruct), BinopInst("+", LoadVarInst(Address(fConst616, kStruct)), LoadVarInst(Address(fConst617, kStruct))))
	StoreVarInst(Address(fConst619, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst618, kStruct)))))
	StoreVarInst(Address(fConst620, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst617, kStruct)), LoadVarInst(Address(fConst616, kStruct))), LoadVarInst(Address(fConst618, kStruct))))
	StoreVarInst(Address(fConst621, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst622, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst621, kStruct))), LoadVarInst(Address(fConst618, kStruct))))
	StoreVarInst(Address(fConst623, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst621, kStruct))), LoadVarInst(Address(fConst618, kStruct)))))
	StoreVarInst(Address(fConst624, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst625, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst626, kStruct), BinopInst("+", LoadVarInst(Address(fConst624, kStruct)), LoadVarInst(Address(fConst625, kStruct))))
	StoreVarInst(Address(fConst627, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst626, kStruct)))))
	StoreVarInst(Address(fConst628, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst625, kStruct)), LoadVarInst(Address(fConst624, kStruct))), LoadVarInst(Address(fConst626, kStruct))))
	StoreVarInst(Address(fConst629, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst626, kStruct))))
	StoreVarInst(Address(fConst630, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst626, kStruct)))))
	StoreVarInst(Address(fConst631, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst632, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst633, kStruct), BinopInst("+", LoadVarInst(Address(fConst631, kStruct)), LoadVarInst(Address(fConst632, kStruct))))
	StoreVarInst(Address(fConst634, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst633, kStruct)))))
	StoreVarInst(Address(fConst635, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst632, kStruct)), LoadVarInst(Address(fConst631, kStruct))), LoadVarInst(Address(fConst633, kStruct))))
	StoreVarInst(Address(fConst636, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst633, kStruct))))
	StoreVarInst(Address(fConst637, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst633, kStruct)))))
	StoreVarInst(Address(fConst638, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst639, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst640, kStruct), BinopInst("+", LoadVarInst(Address(fConst638, kStruct)), LoadVarInst(Address(fConst639, kStruct))))
	StoreVarInst(Address(fConst641, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst640, kStruct)))))
	StoreVarInst(Address(fConst642, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst639, kStruct)), LoadVarInst(Address(fConst638, kStruct))), LoadVarInst(Address(fConst640, kStruct))))
	StoreVarInst(Address(fConst643, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst644, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst643, kStruct))), LoadVarInst(Address(fConst640, kStruct))))
	StoreVarInst(Address(fConst645, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst643, kStruct))), LoadVarInst(Address(fConst640, kStruct)))))
	StoreVarInst(Address(fConst646, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst647, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst648, kStruct), BinopInst("+", LoadVarInst(Address(fConst646, kStruct)), LoadVarInst(Address(fConst647, kStruct))))
	StoreVarInst(Address(fConst649, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst648, kStruct)))))
	StoreVarInst(Address(fConst650, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst647, kStruct)), LoadVarInst(Address(fConst646, kStruct))), LoadVarInst(Address(fConst648, kStruct))))
	StoreVarInst(Address(fConst651, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst652, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst651, kStruct))), LoadVarInst(Address(fConst648, kStruct))))
	StoreVarInst(Address(fConst653, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst651, kStruct))), LoadVarInst(Address(fConst648, kStruct)))))
	StoreVarInst(Address(fConst654, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst655, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst656, kStruct), BinopInst("+", LoadVarInst(Address(fConst654, kStruct)), LoadVarInst(Address(fConst655, kStruct))))
	StoreVarInst(Address(fConst657, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst656, kStruct)))))
	StoreVarInst(Address(fConst658, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst655, kStruct)), LoadVarInst(Address(fConst654, kStruct))), LoadVarInst(Address(fConst656, kStruct))))
	StoreVarInst(Address(fConst659, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst660, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst659, kStruct))), LoadVarInst(Address(fConst656, kStruct))))
	StoreVarInst(Address(fConst661, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst659, kStruct))), LoadVarInst(Address(fConst656, kStruct)))))
	StoreVarInst(Address(fConst662, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst663, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst664, kStruct), BinopInst("+", LoadVarInst(Address(fConst662, kStruct)), LoadVarInst(Address(fConst663, kStruct))))
	StoreVarInst(Address(fConst665, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst664, kStruct)))))
	StoreVarInst(Address(fConst666, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst663, kStruct)), LoadVarInst(Address(fConst662, kStruct))), LoadVarInst(Address(fConst664, kStruct))))
	StoreVarInst(Address(fConst667, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst668, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst667, kStruct))), LoadVarInst(Address(fConst664, kStruct))))
	StoreVarInst(Address(fConst669, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst667, kStruct))), LoadVarInst(Address(fConst664, kStruct)))))
	StoreVarInst(Address(fConst670, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst671, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst672, kStruct), BinopInst("+", LoadVarInst(Address(fConst670, kStruct)), LoadVarInst(Address(fConst671, kStruct))))
	StoreVarInst(Address(fConst673, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst672, kStruct)))))
	StoreVarInst(Address(fConst674, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst671, kStruct)), LoadVarInst(Address(fConst670, kStruct))), LoadVarInst(Address(fConst672, kStruct))))
	StoreVarInst(Address(fConst675, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst676, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst675, kStruct))), LoadVarInst(Address(fConst672, kStruct))))
	StoreVarInst(Address(fConst677, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst675, kStruct))), LoadVarInst(Address(fConst672, kStruct)))))
	StoreVarInst(Address(fConst678, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst679, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst680, kStruct), BinopInst("+", LoadVarInst(Address(fConst678, kStruct)), LoadVarInst(Address(fConst679, kStruct))))
	StoreVarInst(Address(fConst681, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst680, kStruct)))))
	StoreVarInst(Address(fConst682, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst679, kStruct)), LoadVarInst(Address(fConst678, kStruct))), LoadVarInst(Address(fConst680, kStruct))))
	StoreVarInst(Address(fConst683, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst684, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst683, kStruct))), LoadVarInst(Address(fConst680, kStruct))))
	StoreVarInst(Address(fConst685, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst683, kStruct))), LoadVarInst(Address(fConst680, kStruct)))))
	StoreVarInst(Address(fConst686, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst687, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst688, kStruct), BinopInst("+", LoadVarInst(Address(fConst686, kStruct)), LoadVarInst(Address(fConst687, kStruct))))
	StoreVarInst(Address(fConst689, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst688, kStruct)))))
	StoreVarInst(Address(fConst690, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst687, kStruct)), LoadVarInst(Address(fConst686, kStruct))), LoadVarInst(Address(fConst688, kStruct))))
	StoreVarInst(Address(fConst691, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst692, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst691, kStruct))), LoadVarInst(Address(fConst688, kStruct))))
	StoreVarInst(Address(fConst693, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst691, kStruct))), LoadVarInst(Address(fConst688, kStruct)))))
	StoreVarInst(Address(fConst694, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst695, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst696, kStruct), BinopInst("+", LoadVarInst(Address(fConst694, kStruct)), LoadVarInst(Address(fConst695, kStruct))))
	StoreVarInst(Address(fConst697, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst696, kStruct)))))
	StoreVarInst(Address(fConst698, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst695, kStruct)), LoadVarInst(Address(fConst694, kStruct))), LoadVarInst(Address(fConst696, kStruct))))
	StoreVarInst(Address(fConst699, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst700, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst699, kStruct))), LoadVarInst(Address(fConst696, kStruct))))
	StoreVarInst(Address(fConst701, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst699, kStruct))), LoadVarInst(Address(fConst696, kStruct)))))
	StoreVarInst(Address(fConst702, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst703, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst704, kStruct), BinopInst("+", LoadVarInst(Address(fConst702, kStruct)), LoadVarInst(Address(fConst703, kStruct))))
	StoreVarInst(Address(fConst705, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst704, kStruct)))))
	StoreVarInst(Address(fConst706, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst703, kStruct)), LoadVarInst(Address(fConst702, kStruct))), LoadVarInst(Address(fConst704, kStruct))))
	StoreVarInst(Address(fConst707, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst708, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst707, kStruct))), LoadVarInst(Address(fConst704, kStruct))))
	StoreVarInst(Address(fConst709, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst707, kStruct))), LoadVarInst(Address(fConst704, kStruct)))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.9f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(25.0f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(-2e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(1.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(2.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Float(49.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.1f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(-0.1f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(0.1f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Float(5.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Float(1e+02f)))
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
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4096))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(4096))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(4096))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fVec28, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(4096))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(4096))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR10, kStruct)[LoadVarInst(Address(l47, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(4))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(3))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR11, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(3))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(3))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(3))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM0, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(3))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR26, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(3))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR25, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(3))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR24, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(3))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR23, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(3))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR22, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(3))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR21, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(3))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR20, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(3))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR19, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(3))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR18, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(3))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR17, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(3))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR16, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(3))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR15, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(3))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR14, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(3))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR13, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(3))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR12, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(2))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM2, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(3))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR41, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(3))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR40, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(3))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR39, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(3))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR38, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(3))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR37, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(3))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR36, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(3))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR35, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(3))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR34, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(3))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR33, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(3))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR32, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(3))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR31, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(3))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR30, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(3))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR29, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(3))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR28, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(3))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR27, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(2))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM3, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(3))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR56, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l99, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l99, kLoop)), Int32(3))
		StoreVarInst(Address(l99, kLoop), BinopInst("+", LoadVarInst(Address(l99, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR55, kStruct)[LoadVarInst(Address(l99, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l100, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l100, kLoop)), Int32(3))
		StoreVarInst(Address(l100, kLoop), BinopInst("+", LoadVarInst(Address(l100, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR54, kStruct)[LoadVarInst(Address(l100, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l101, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l101, kLoop)), Int32(3))
		StoreVarInst(Address(l101, kLoop), BinopInst("+", LoadVarInst(Address(l101, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR53, kStruct)[LoadVarInst(Address(l101, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l102, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l102, kLoop)), Int32(3))
		StoreVarInst(Address(l102, kLoop), BinopInst("+", LoadVarInst(Address(l102, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR52, kStruct)[LoadVarInst(Address(l102, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l103, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l103, kLoop)), Int32(3))
		StoreVarInst(Address(l103, kLoop), BinopInst("+", LoadVarInst(Address(l103, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR51, kStruct)[LoadVarInst(Address(l103, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l104, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l104, kLoop)), Int32(3))
		StoreVarInst(Address(l104, kLoop), BinopInst("+", LoadVarInst(Address(l104, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR50, kStruct)[LoadVarInst(Address(l104, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l105, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l105, kLoop)), Int32(3))
		StoreVarInst(Address(l105, kLoop), BinopInst("+", LoadVarInst(Address(l105, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR49, kStruct)[LoadVarInst(Address(l105, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l106, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l106, kLoop)), Int32(3))
		StoreVarInst(Address(l106, kLoop), BinopInst("+", LoadVarInst(Address(l106, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR48, kStruct)[LoadVarInst(Address(l106, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l107, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l107, kLoop)), Int32(3))
		StoreVarInst(Address(l107, kLoop), BinopInst("+", LoadVarInst(Address(l107, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR47, kStruct)[LoadVarInst(Address(l107, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l108, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l108, kLoop)), Int32(3))
		StoreVarInst(Address(l108, kLoop), BinopInst("+", LoadVarInst(Address(l108, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR46, kStruct)[LoadVarInst(Address(l108, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l109, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l109, kLoop)), Int32(3))
		StoreVarInst(Address(l109, kLoop), BinopInst("+", LoadVarInst(Address(l109, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR45, kStruct)[LoadVarInst(Address(l109, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l110, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l110, kLoop)), Int32(3))
		StoreVarInst(Address(l110, kLoop), BinopInst("+", LoadVarInst(Address(l110, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR44, kStruct)[LoadVarInst(Address(l110, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l111, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l111, kLoop)), Int32(3))
		StoreVarInst(Address(l111, kLoop), BinopInst("+", LoadVarInst(Address(l111, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR43, kStruct)[LoadVarInst(Address(l111, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l112, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l112, kLoop)), Int32(3))
		StoreVarInst(Address(l112, kLoop), BinopInst("+", LoadVarInst(Address(l112, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR42, kStruct)[LoadVarInst(Address(l112, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l113, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l113, kLoop)), Int32(2))
		StoreVarInst(Address(l113, kLoop), BinopInst("+", LoadVarInst(Address(l113, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM4, kStruct)[LoadVarInst(Address(l113, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l114, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l114, kLoop)), Int32(3))
		StoreVarInst(Address(l114, kLoop), BinopInst("+", LoadVarInst(Address(l114, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR59, kStruct)[LoadVarInst(Address(l114, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l115, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l115, kLoop)), Int32(3))
		StoreVarInst(Address(l115, kLoop), BinopInst("+", LoadVarInst(Address(l115, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR58, kStruct)[LoadVarInst(Address(l115, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l116, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l116, kLoop)), Int32(3))
		StoreVarInst(Address(l116, kLoop), BinopInst("+", LoadVarInst(Address(l116, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR57, kStruct)[LoadVarInst(Address(l116, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l117, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l117, kLoop)), Int32(2))
		StoreVarInst(Address(l117, kLoop), BinopInst("+", LoadVarInst(Address(l117, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM5, kStruct)[LoadVarInst(Address(l117, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l118, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l118, kLoop)), Int32(3))
		StoreVarInst(Address(l118, kLoop), BinopInst("+", LoadVarInst(Address(l118, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR62, kStruct)[LoadVarInst(Address(l118, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l119, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l119, kLoop)), Int32(3))
		StoreVarInst(Address(l119, kLoop), BinopInst("+", LoadVarInst(Address(l119, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR61, kStruct)[LoadVarInst(Address(l119, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l120, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l120, kLoop)), Int32(3))
		StoreVarInst(Address(l120, kLoop), BinopInst("+", LoadVarInst(Address(l120, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR60, kStruct)[LoadVarInst(Address(l120, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l121, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l121, kLoop)), Int32(2))
		StoreVarInst(Address(l121, kLoop), BinopInst("+", LoadVarInst(Address(l121, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM6, kStruct)[LoadVarInst(Address(l121, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l122, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l122, kLoop)), Int32(3))
		StoreVarInst(Address(l122, kLoop), BinopInst("+", LoadVarInst(Address(l122, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR65, kStruct)[LoadVarInst(Address(l122, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l123, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l123, kLoop)), Int32(3))
		StoreVarInst(Address(l123, kLoop), BinopInst("+", LoadVarInst(Address(l123, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR64, kStruct)[LoadVarInst(Address(l123, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l124, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l124, kLoop)), Int32(3))
		StoreVarInst(Address(l124, kLoop), BinopInst("+", LoadVarInst(Address(l124, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR63, kStruct)[LoadVarInst(Address(l124, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l125, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l125, kLoop)), Int32(2))
		StoreVarInst(Address(l125, kLoop), BinopInst("+", LoadVarInst(Address(l125, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM7, kStruct)[LoadVarInst(Address(l125, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l126, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l126, kLoop)), Int32(3))
		StoreVarInst(Address(l126, kLoop), BinopInst("+", LoadVarInst(Address(l126, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR71, kStruct)[LoadVarInst(Address(l126, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l127, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l127, kLoop)), Int32(3))
		StoreVarInst(Address(l127, kLoop), BinopInst("+", LoadVarInst(Address(l127, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR70, kStruct)[LoadVarInst(Address(l127, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l128, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l128, kLoop)), Int32(3))
		StoreVarInst(Address(l128, kLoop), BinopInst("+", LoadVarInst(Address(l128, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR69, kStruct)[LoadVarInst(Address(l128, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l129, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l129, kLoop)), Int32(3))
		StoreVarInst(Address(l129, kLoop), BinopInst("+", LoadVarInst(Address(l129, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR68, kStruct)[LoadVarInst(Address(l129, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l130, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l130, kLoop)), Int32(3))
		StoreVarInst(Address(l130, kLoop), BinopInst("+", LoadVarInst(Address(l130, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR67, kStruct)[LoadVarInst(Address(l130, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l131, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l131, kLoop)), Int32(3))
		StoreVarInst(Address(l131, kLoop), BinopInst("+", LoadVarInst(Address(l131, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR66, kStruct)[LoadVarInst(Address(l131, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l132, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l132, kLoop)), Int32(2))
		StoreVarInst(Address(l132, kLoop), BinopInst("+", LoadVarInst(Address(l132, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM8, kStruct)[LoadVarInst(Address(l132, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l133, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l133, kLoop)), Int32(3))
		StoreVarInst(Address(l133, kLoop), BinopInst("+", LoadVarInst(Address(l133, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR74, kStruct)[LoadVarInst(Address(l133, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l134, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l134, kLoop)), Int32(3))
		StoreVarInst(Address(l134, kLoop), BinopInst("+", LoadVarInst(Address(l134, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR73, kStruct)[LoadVarInst(Address(l134, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l135, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l135, kLoop)), Int32(3))
		StoreVarInst(Address(l135, kLoop), BinopInst("+", LoadVarInst(Address(l135, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR72, kStruct)[LoadVarInst(Address(l135, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l136, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l136, kLoop)), Int32(2))
		StoreVarInst(Address(l136, kLoop), BinopInst("+", LoadVarInst(Address(l136, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM9, kStruct)[LoadVarInst(Address(l136, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l137, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l137, kLoop)), Int32(3))
		StoreVarInst(Address(l137, kLoop), BinopInst("+", LoadVarInst(Address(l137, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR77, kStruct)[LoadVarInst(Address(l137, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l138, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l138, kLoop)), Int32(3))
		StoreVarInst(Address(l138, kLoop), BinopInst("+", LoadVarInst(Address(l138, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR76, kStruct)[LoadVarInst(Address(l138, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l139, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l139, kLoop)), Int32(3))
		StoreVarInst(Address(l139, kLoop), BinopInst("+", LoadVarInst(Address(l139, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR75, kStruct)[LoadVarInst(Address(l139, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l140, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l140, kLoop)), Int32(2))
		StoreVarInst(Address(l140, kLoop), BinopInst("+", LoadVarInst(Address(l140, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM10, kStruct)[LoadVarInst(Address(l140, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l141, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l141, kLoop)), Int32(3))
		StoreVarInst(Address(l141, kLoop), BinopInst("+", LoadVarInst(Address(l141, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR80, kStruct)[LoadVarInst(Address(l141, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l142, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l142, kLoop)), Int32(3))
		StoreVarInst(Address(l142, kLoop), BinopInst("+", LoadVarInst(Address(l142, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR79, kStruct)[LoadVarInst(Address(l142, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l143, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l143, kLoop)), Int32(3))
		StoreVarInst(Address(l143, kLoop), BinopInst("+", LoadVarInst(Address(l143, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR78, kStruct)[LoadVarInst(Address(l143, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l144, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l144, kLoop)), Int32(2))
		StoreVarInst(Address(l144, kLoop), BinopInst("+", LoadVarInst(Address(l144, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM11, kStruct)[LoadVarInst(Address(l144, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l145, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l145, kLoop)), Int32(3))
		StoreVarInst(Address(l145, kLoop), BinopInst("+", LoadVarInst(Address(l145, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR83, kStruct)[LoadVarInst(Address(l145, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l146, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l146, kLoop)), Int32(3))
		StoreVarInst(Address(l146, kLoop), BinopInst("+", LoadVarInst(Address(l146, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR82, kStruct)[LoadVarInst(Address(l146, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l147, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l147, kLoop)), Int32(3))
		StoreVarInst(Address(l147, kLoop), BinopInst("+", LoadVarInst(Address(l147, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR81, kStruct)[LoadVarInst(Address(l147, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l148, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l148, kLoop)), Int32(2))
		StoreVarInst(Address(l148, kLoop), BinopInst("+", LoadVarInst(Address(l148, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM12, kStruct)[LoadVarInst(Address(l148, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l149, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l149, kLoop)), Int32(3))
		StoreVarInst(Address(l149, kLoop), BinopInst("+", LoadVarInst(Address(l149, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR86, kStruct)[LoadVarInst(Address(l149, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l150, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l150, kLoop)), Int32(3))
		StoreVarInst(Address(l150, kLoop), BinopInst("+", LoadVarInst(Address(l150, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR85, kStruct)[LoadVarInst(Address(l150, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l151, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l151, kLoop)), Int32(3))
		StoreVarInst(Address(l151, kLoop), BinopInst("+", LoadVarInst(Address(l151, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR84, kStruct)[LoadVarInst(Address(l151, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l152, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l152, kLoop)), Int32(2))
		StoreVarInst(Address(l152, kLoop), BinopInst("+", LoadVarInst(Address(l152, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM13, kStruct)[LoadVarInst(Address(l152, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l153, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l153, kLoop)), Int32(3))
		StoreVarInst(Address(l153, kLoop), BinopInst("+", LoadVarInst(Address(l153, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR89, kStruct)[LoadVarInst(Address(l153, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l154, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l154, kLoop)), Int32(3))
		StoreVarInst(Address(l154, kLoop), BinopInst("+", LoadVarInst(Address(l154, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR88, kStruct)[LoadVarInst(Address(l154, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l155, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l155, kLoop)), Int32(3))
		StoreVarInst(Address(l155, kLoop), BinopInst("+", LoadVarInst(Address(l155, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR87, kStruct)[LoadVarInst(Address(l155, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l156, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l156, kLoop)), Int32(2))
		StoreVarInst(Address(l156, kLoop), BinopInst("+", LoadVarInst(Address(l156, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM14, kStruct)[LoadVarInst(Address(l156, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l157, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l157, kLoop)), Int32(3))
		StoreVarInst(Address(l157, kLoop), BinopInst("+", LoadVarInst(Address(l157, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR92, kStruct)[LoadVarInst(Address(l157, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l158, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l158, kLoop)), Int32(3))
		StoreVarInst(Address(l158, kLoop), BinopInst("+", LoadVarInst(Address(l158, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR91, kStruct)[LoadVarInst(Address(l158, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l159, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l159, kLoop)), Int32(3))
		StoreVarInst(Address(l159, kLoop), BinopInst("+", LoadVarInst(Address(l159, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR90, kStruct)[LoadVarInst(Address(l159, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l160, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l160, kLoop)), Int32(2))
		StoreVarInst(Address(l160, kLoop), BinopInst("+", LoadVarInst(Address(l160, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM15, kStruct)[LoadVarInst(Address(l160, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 54 Store = 0 Binop = 39 [ { Int(>=) = 3 } { Real(*) = 17 } { Real(+) = 8 } { Real(-) = 5 } { Real(/) = 2 } { Real(>) = 4 } ] Mathop = 48 [ { expf = 2 } { max_f = 19 } { min_f = 20 } { mydsp_faustpower2_f = 2 } { mydsp_faustpower4_f = 1 } { powf = 4 } ] Numbers = 78 Declare = 47 Cast = 30 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("int", iSlow1, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f)))))
	DeclareVarInst("int", iSlow2, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))), Float(0.0f)))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fSlow3, kStack))), Float(0.999999f))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(4.0f), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", Float(-49.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(88.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-1.2e+02f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))))))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(0.33333334f), LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("int", iSlow11, kStack, CastInst("int", BinopInst("+", Float(-1.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("int", iSlow12, kStack, BinopInst(">=", LoadVarInst(Address(iSlow11, kStack)), Int32(2)))
	DeclareVarInst("int", iSlow13, kStack, BinopInst(">=", LoadVarInst(Address(iSlow11, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", Float(-49.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(88.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), FunCallInst("max_f", Float(0.001f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow15, kStack))), LoadVarInst(Address(fSlow14, kStack))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst(">=", LoadVarInst(Address(iSlow11, kStack)), Int32(3)))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", Float(0.01f), FunCallInst("max_f", Float(-1e+01f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow18, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("+", Float(1.0f), BinopInst("*", Float(0.01f), FunCallInst("max_f", Float(-1e+01f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))
	DeclareVarInst("int", iSlow32, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct))), Float(0.0f)))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("min_f", Float(1.4127994f), BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow3, kStack)))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow33, kStack))))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow33, kStack)))))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow34, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("+", Float(2.0f), LoadVarInst(Address(fSlow34, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("*", Float(1.998f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("+", Float(2.0f), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.4127994f), LoadVarInst(Address(fSlow3, kStack))))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow42, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-6e+01f), FunCallInst("min_f", Float(2e+01f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst50, kStruct)), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 1939 Store = 424 Binop = 1284 [ { Int(&) = 24 } { Int(*) = 1 } { Int(+) = 9 } { Int(-) = 24 } { Int(<) = 1 } { Int(>) = 3 } { Real(*) = 596 } { Real(+) = 293 } { Real(-) = 274 } { Real(/) = 59 } ] Mathop = 109 [ { fabsf = 21 } { floorf = 6 } { log10f = 15 } { max_f = 25 } { min_f = 11 } { mydsp_faustpower2_f = 14 } { mydsp_faustpower3_f = 6 } { mydsp_faustpower4_f = 1 } { sqrtf = 8 } { tanf = 2 } ] Numbers = 1324 Declare = 300 Cast = 34 Select = 13 Loop = 4

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("*", Float(0.44f), LoadVarInst(Address(fTemp0, kStack))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp1, kStack))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp2, kStack))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fIRM1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIRM1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(4.4e+02f), LoadVarInst(Address(fTemp5, kStack))))
		DeclareVarInst("float", fTemp7, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp6, kStack)))))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp7, kStack)))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp8, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp8, kStack)))))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp9, kStack))))
		DeclareVarInst("float", fTemp11, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp12, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp10, kStack))))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
		DeclareVarInst("float", fTemp13, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(2)])))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("-", LoadVarInst(Address(fTemp9, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp10, kStack))))))
		DeclareVarInst("float", fTemp15, kStack, NegInst(LoadVarInst(Address(fTemp14, kStack))))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp15, kStack)))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec2, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp14, kStack)))), LoadVarInst(Address(fTemp7, kStack))))
		StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp16, kStack)))
		DeclareVarInst("float", fTemp17, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(3)])))
		DeclareVarInst("float", fTemp18, kStack, BinopInst("*", LoadVarInst(Address(fTemp12, kStack)), BinopInst("+", Float(-2.0f), LoadVarInst(Address(fTemp12, kStack)))))
		StoreVarInst(Address(fVec4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp18, kStack)))
		DeclareVarInst("float", fTemp19, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp7, kStack))))
		StoreVarInst(Address(fVec5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp19, kStack)))
		DeclareVarInst("float", fTemp20, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fVec5, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp7, kStack))))
		StoreVarInst(Address(fVec6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp20, kStack)))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fTemp6, kStack))))
		DeclareVarInst("float", fTemp22, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp21, kStack)))))
		DeclareVarInst("float", fTemp23, kStack, BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp22, kStack)))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp23, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp23, kStack)))))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp24, kStack))))
		DeclareVarInst("float", fTemp26, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp25, kStack))))
		StoreVarInst(Address(fVec7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp26, kStack)))
		DeclareVarInst("float", fTemp27, kStack, BinopInst("-", LoadVarInst(Address(fTemp24, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp25, kStack))))))
		DeclareVarInst("float", fTemp28, kStack, NegInst(LoadVarInst(Address(fTemp27, kStack))))
		StoreVarInst(Address(fVec8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp28, kStack)))
		DeclareVarInst("float", fTemp29, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec8, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp27, kStack)))), LoadVarInst(Address(fTemp22, kStack))))
		StoreVarInst(Address(fVec9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp29, kStack)))
		DeclareVarInst("float", fTemp30, kStack, BinopInst("*", LoadVarInst(Address(fTemp26, kStack)), BinopInst("+", Float(-2.0f), LoadVarInst(Address(fTemp26, kStack)))))
		StoreVarInst(Address(fVec10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp30, kStack)))
		DeclareVarInst("float", fTemp31, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fVec10, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp22, kStack))))
		StoreVarInst(Address(fVec11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp31, kStack)))
		DeclareVarInst("float", fTemp32, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fVec11, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp22, kStack))))
		StoreVarInst(Address(fVec12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp32, kStack)))
		DeclareVarInst("float", fTemp33, kStack, BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fTemp6, kStack))))
		DeclareVarInst("float", fTemp34, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp33, kStack)))))
		DeclareVarInst("float", fTemp35, kStack, BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp34, kStack)))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp35, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp35, kStack)))))
		DeclareVarInst("float", fTemp36, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp37, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp36, kStack))))
		DeclareVarInst("float", fTemp38, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp37, kStack))))
		StoreVarInst(Address(fVec13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp38, kStack)))
		DeclareVarInst("float", fTemp39, kStack, BinopInst("-", LoadVarInst(Address(fTemp36, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp37, kStack))))))
		DeclareVarInst("float", fTemp40, kStack, NegInst(LoadVarInst(Address(fTemp39, kStack))))
		StoreVarInst(Address(fVec14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp40, kStack)))
		DeclareVarInst("float", fTemp41, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp39, kStack)))), LoadVarInst(Address(fTemp34, kStack))))
		StoreVarInst(Address(fVec15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp41, kStack)))
		DeclareVarInst("float", fTemp42, kStack, BinopInst("*", LoadVarInst(Address(fTemp38, kStack)), BinopInst("+", Float(-2.0f), LoadVarInst(Address(fTemp38, kStack)))))
		StoreVarInst(Address(fVec16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp42, kStack)))
		DeclareVarInst("float", fTemp43, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fVec16, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp34, kStack))))
		StoreVarInst(Address(fVec17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp43, kStack)))
		DeclareVarInst("float", fTemp44, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp43, kStack)), LoadVarInst(Address(fVec17, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp34, kStack))))
		StoreVarInst(Address(fVec18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp44, kStack)))
		DeclareVarInst("float", fTemp45, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp6, kStack)), Float(23.44895f)))
		DeclareVarInst("float", fTemp46, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp45, kStack))))))
		DeclareVarInst("int", iTemp47, kStack, CastInst("int", LoadVarInst(Address(fTemp46, kStack))))
		DeclareVarInst("float", fTemp48, kStack, CastInst("float", LoadVarInst(Address(iTemp47, kStack))))
		DeclareVarInst("float", fTemp49, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp45, kStack)))))
		DeclareVarInst("float", fTemp50, kStack, BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp49, kStack)))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp50, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp50, kStack)))))
		DeclareVarInst("float", fTemp51, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp52, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp51, kStack))))
		DeclareVarInst("float", fTemp53, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp52, kStack))))
		StoreVarInst(Address(fVec19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp53, kStack)))
		DeclareVarInst("float", fTemp54, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
		StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp54, kStack)))
		DeclareVarInst("float", fTemp55, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp47, kStack))), Int32(4095))]), BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp46, kStack))), LoadVarInst(Address(fTemp48, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fTemp48, kStack))), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp47, kStack)))), Int32(4095))]))))
		DeclareVarInst("float", fTemp56, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp21, kStack)), Float(23.44895f)))
		DeclareVarInst("float", fTemp57, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp56, kStack))))))
		DeclareVarInst("int", iTemp58, kStack, CastInst("int", LoadVarInst(Address(fTemp57, kStack))))
		DeclareVarInst("float", fTemp59, kStack, CastInst("float", LoadVarInst(Address(iTemp58, kStack))))
		DeclareVarInst("float", fTemp60, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp56, kStack)))))
		DeclareVarInst("float", fTemp61, kStack, BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp60, kStack)))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp61, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp61, kStack)))))
		DeclareVarInst("float", fTemp62, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp63, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp62, kStack))))
		DeclareVarInst("float", fTemp64, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp63, kStack))))
		StoreVarInst(Address(fVec21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp64, kStack)))
		DeclareVarInst("float", fTemp65, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp64, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
		StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp65, kStack)))
		DeclareVarInst("float", fTemp66, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp58, kStack))), Int32(4095))]), BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp57, kStack))), LoadVarInst(Address(fTemp59, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp57, kStack)), LoadVarInst(Address(fTemp59, kStack))), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp58, kStack)))), Int32(4095))]))))
		DeclareVarInst("float", fTemp67, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp33, kStack)), Float(23.44895f)))
		DeclareVarInst("float", fTemp68, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp67, kStack))))))
		DeclareVarInst("int", iTemp69, kStack, CastInst("int", LoadVarInst(Address(fTemp68, kStack))))
		DeclareVarInst("float", fTemp70, kStack, CastInst("float", LoadVarInst(Address(iTemp69, kStack))))
		DeclareVarInst("float", fTemp71, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp67, kStack)))))
		DeclareVarInst("float", fTemp72, kStack, BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp71, kStack)))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp72, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp72, kStack)))))
		DeclareVarInst("float", fTemp73, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp74, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp73, kStack))))
		DeclareVarInst("float", fTemp75, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp74, kStack))))
		StoreVarInst(Address(fVec23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp75, kStack)))
		DeclareVarInst("float", fTemp76, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp75, kStack)), LoadVarInst(Address(fVec23, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp71, kStack))))
		StoreVarInst(Address(fVec24, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp76, kStack)))
		DeclareVarInst("float", fTemp77, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp76, kStack)), BinopInst("*", LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp69, kStack))), Int32(4095))]), BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp68, kStack))), LoadVarInst(Address(fTemp70, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp68, kStack)), LoadVarInst(Address(fTemp70, kStack))), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp69, kStack)))), Int32(4095))]))))
		DeclareVarInst("float", fTemp78, kStack, BinopInst("+", LoadVarInst(Address(fTemp55, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp78, kStack)))
		DeclareVarInst("float", fTemp79, kStack, BinopInst("+", LoadVarInst(Address(fTemp66, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp79, kStack)))
		DeclareVarInst("float", fTemp80, kStack, BinopInst("+", LoadVarInst(Address(fTemp77, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp80, kStack)))
		DeclareVarInst("float", fTemp81, kStack, BinopInst("+", LoadVarInst(Address(fSlow28, kStack)), BinopInst("*", Float(0.99f), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp81, kStack)))
		DeclareVarInst("float", fTemp82, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fTemp81, kStack))))
		DeclareVarInst("float", fTemp83, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp45, kStack)))))))
		DeclareVarInst("int", iTemp84, kStack, CastInst("int", LoadVarInst(Address(fTemp83, kStack))))
		DeclareVarInst("float", fTemp85, kStack, CastInst("float", LoadVarInst(Address(iTemp84, kStack))))
		DeclareVarInst("float", fTemp86, kStack, BinopInst("-", LoadVarInst(Address(fTemp83, kStack)), LoadVarInst(Address(fTemp85, kStack))))
		DeclareVarInst("float", fTemp87, kStack, BinopInst("-", LoadVarInst(Address(fTemp51, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp52, kStack))))))
		DeclareVarInst("float", fTemp88, kStack, NegInst(LoadVarInst(Address(fTemp87, kStack))))
		StoreVarInst(Address(fVec25, kStruct)[Int32(0)], LoadVarInst(Address(fTemp88, kStack)))
		DeclareVarInst("float", fTemp89, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec25, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp87, kStack)))), LoadVarInst(Address(fTemp49, kStack))))
		StoreVarInst(Address(fVec26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp89, kStack)))
		DeclareVarInst("float", fTemp90, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp89, kStack)), LoadVarInst(Address(fVec26, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
		StoreVarInst(Address(fVec27, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp90, kStack)))
		DeclareVarInst("int", iTemp91, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iTemp84, kStack))))
		DeclareVarInst("float", fTemp92, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp83, kStack))), LoadVarInst(Address(fTemp85, kStack))))
		DeclareVarInst("float", fTemp93, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp56, kStack)))))))
		DeclareVarInst("int", iTemp94, kStack, CastInst("int", LoadVarInst(Address(fTemp93, kStack))))
		DeclareVarInst("float", fTemp95, kStack, CastInst("float", LoadVarInst(Address(iTemp94, kStack))))
		DeclareVarInst("float", fTemp96, kStack, BinopInst("-", LoadVarInst(Address(fTemp93, kStack)), LoadVarInst(Address(fTemp95, kStack))))
		DeclareVarInst("float", fTemp97, kStack, BinopInst("-", LoadVarInst(Address(fTemp62, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp63, kStack))))))
		DeclareVarInst("float", fTemp98, kStack, NegInst(LoadVarInst(Address(fTemp97, kStack))))
		StoreVarInst(Address(fVec28, kStruct)[Int32(0)], LoadVarInst(Address(fTemp98, kStack)))
		DeclareVarInst("float", fTemp99, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec28, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp97, kStack)))), LoadVarInst(Address(fTemp60, kStack))))
		StoreVarInst(Address(fVec29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp99, kStack)))
		DeclareVarInst("float", fTemp100, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp99, kStack)), LoadVarInst(Address(fVec29, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
		StoreVarInst(Address(fVec30, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp100, kStack)))
		DeclareVarInst("int", iTemp101, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iTemp94, kStack))))
		DeclareVarInst("float", fTemp102, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp93, kStack))), LoadVarInst(Address(fTemp95, kStack))))
		DeclareVarInst("float", fTemp103, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp67, kStack)))))))
		DeclareVarInst("int", iTemp104, kStack, CastInst("int", LoadVarInst(Address(fTemp103, kStack))))
		DeclareVarInst("float", fTemp105, kStack, CastInst("float", LoadVarInst(Address(iTemp104, kStack))))
		DeclareVarInst("float", fTemp106, kStack, BinopInst("-", LoadVarInst(Address(fTemp103, kStack)), LoadVarInst(Address(fTemp105, kStack))))
		DeclareVarInst("float", fTemp107, kStack, BinopInst("-", LoadVarInst(Address(fTemp73, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp74, kStack))))))
		DeclareVarInst("float", fTemp108, kStack, NegInst(LoadVarInst(Address(fTemp107, kStack))))
		StoreVarInst(Address(fVec31, kStruct)[Int32(0)], LoadVarInst(Address(fTemp108, kStack)))
		DeclareVarInst("float", fTemp109, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec31, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp107, kStack)))), LoadVarInst(Address(fTemp71, kStack))))
		StoreVarInst(Address(fVec32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp109, kStack)))
		DeclareVarInst("float", fTemp110, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp109, kStack)), LoadVarInst(Address(fVec32, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp71, kStack))))
		StoreVarInst(Address(fVec33, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp110, kStack)))
		DeclareVarInst("int", iTemp111, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iTemp104, kStack))))
		DeclareVarInst("float", fTemp112, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp103, kStack))), LoadVarInst(Address(fTemp105, kStack))))
		DeclareVarInst("int", iTemp113, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR10, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR10, kStruct)[Int32(0)], LoadVarInst(Address(iTemp113, kStack)))
		DeclareVarInst("float", fTemp114, kStack, BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(iTemp113, kStack))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fIIR9, kStruct)[Int32(2)]))), BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fIIR9, kStruct)[Int32(3)]))))
		StoreVarInst(Address(fIIR9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp114, kStack)))
		StoreVarInst(Address(fVec34, kStruct)[Int32(0)], BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp114, kStack))))
		DeclareVarInst("float", fTemp115, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp4, kStack))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(Address(iSlow12, kStack)) Select2Inst(LoadVarInst(Address(iSlow17, kStack)) BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fVec6, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp7, kStack)))) BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp16, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp7, kStack))))) Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp7, kStack)))) LoadVarInst(Address(fTemp10, kStack)))), Select2Inst(LoadVarInst(Address(iSlow12, kStack)) Select2Inst(LoadVarInst(Address(iSlow17, kStack)) BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp32, kStack)), LoadVarInst(Address(fVec12, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp22, kStack)))) BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fVec9, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp22, kStack))))) Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), LoadVarInst(Address(fVec7, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp22, kStack)))) LoadVarInst(Address(fTemp25, kStack))))), Select2Inst(LoadVarInst(Address(iSlow12, kStack)) Select2Inst(LoadVarInst(Address(iSlow17, kStack)) BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp44, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp34, kStack)))) BinopInst("*", LoadVarInst(Address(fConst12, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp41, kStack)), LoadVarInst(Address(fVec15, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp34, kStack))))) Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp38, kStack)), LoadVarInst(Address(fVec13, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp34, kStack)))) LoadVarInst(Address(fTemp37, kStack)))))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp55, kStack)), LoadVarInst(Address(fTemp66, kStack))), LoadVarInst(Address(fTemp77, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fTemp78, kStack))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fTemp79, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fTemp80, kStack)))))))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp90, kStack)), BinopInst("*", LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp84, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp92, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp91, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp100, kStack)), BinopInst("*", LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp94, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp102, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp96, kStack)), LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp101, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp110, kStack)), BinopInst("*", LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp104, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp112, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp106, kStack)), LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp111, kStack))), Int32(4095))]))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fTemp92, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp84, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp91, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fTemp102, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp94, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp96, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp101, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp76, kStack)), BinopInst("*", LoadVarInst(Address(fTemp112, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp104, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp106, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp111, kStack))), Int32(4095))])))))))), BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec34, kStruct)[Int32(0)])), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec34, kStruct)[Int32(1)]))), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fVec34, kStruct)[Int32(2)]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fVec34, kStruct)[Int32(3)]))))))))
		DeclareVarInst("float", fTemp116, kStack, Select2Inst(LoadVarInst(Address(iSlow1, kStack)) Float(0.0f) LoadVarInst(Address(fTemp115, kStack))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp3, kStack))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp116, kStack))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("*", FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fTemp2, kStack))), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp117, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1e+04f), LoadVarInst(Address(fTemp1, kStack)))))))
		DeclareVarInst("float", fTemp118, kStack, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp117, kStack)))))
		DeclareVarInst("float", fTemp119, kStack, BinopInst("-", LoadVarInst(Address(fTemp118, kStack)), LoadVarInst(Address(fSlow35, kStack))))
		DeclareVarInst("float", fTemp120, kStack, BinopInst("/", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp117, kStack))))
		DeclareVarInst("float", fTemp121, kStack, BinopInst("+", LoadVarInst(Address(fTemp118, kStack)), LoadVarInst(Address(fSlow35, kStack))))
		DeclareVarInst("float", fTemp122, kStack, BinopInst("-", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp121, kStack))))
		DeclareVarInst("float", fTemp123, kStack, BinopInst("-", LoadVarInst(Address(fTemp120, kStack)), LoadVarInst(Address(fTemp122, kStack))))
		DeclareVarInst("float", fTemp124, kStack, BinopInst("/", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fTemp117, kStack))))
		DeclareVarInst("float", fTemp125, kStack, BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp121, kStack))))
		DeclareVarInst("float", fTemp126, kStack, BinopInst("+", LoadVarInst(Address(fTemp124, kStack)), LoadVarInst(Address(fTemp125, kStack))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp116, kStack)), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("-", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp119, kStack))))), BinopInst("*", LoadVarInst(Address(fRec12, kStruct)[Int32(2)]), BinopInst("-", LoadVarInst(Address(fTemp125, kStack)), LoadVarInst(Address(fTemp124, kStack))))), LoadVarInst(Address(fTemp126, kStack)))))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("-", BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))), LoadVarInst(Address(fRec12, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp126, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), NegInst(BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp119, kStack)))))), BinopInst("*", LoadVarInst(Address(fRec11, kStruct)[Int32(2)]), NegInst(BinopInst("+", LoadVarInst(Address(fTemp120, kStack)), LoadVarInst(Address(fTemp122, kStack)))))), LoadVarInst(Address(fTemp123, kStack)))))
		DeclareVarInst("float", fTemp127, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), FunCallInst("max_f", LoadVarInst(Address(fTemp1, kStack)), Float(2e+01f)))))
		DeclareVarInst("float", fTemp128, kStack, BinopInst("/", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp127, kStack))))
		DeclareVarInst("float", fTemp129, kStack, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp127, kStack)))))
		DeclareVarInst("float", fTemp130, kStack, BinopInst("+", LoadVarInst(Address(fTemp129, kStack)), LoadVarInst(Address(fSlow40, kStack))))
		DeclareVarInst("float", fTemp131, kStack, BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp130, kStack))))
		DeclareVarInst("float", fTemp132, kStack, BinopInst("-", LoadVarInst(Address(fTemp131, kStack)), LoadVarInst(Address(fTemp128, kStack))))
		DeclareVarInst("float", fTemp133, kStack, BinopInst("+", LoadVarInst(Address(fTemp128, kStack)), LoadVarInst(Address(fTemp131, kStack))))
		DeclareVarInst("float", fTemp134, kStack, BinopInst("/", LoadVarInst(Address(fTemp132, kStack)), LoadVarInst(Address(fTemp133, kStack))))
		DeclareVarInst("float", fTemp135, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp134, kStack)))))
		DeclareVarInst("float", fTemp136, kStack, BinopInst("-", LoadVarInst(Address(fTemp129, kStack)), LoadVarInst(Address(fSlow40, kStack))))
		DeclareVarInst("float", fTemp137, kStack, BinopInst("-", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp136, kStack))))
		DeclareVarInst("float", fTemp138, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp137, kStack)), BinopInst("*", LoadVarInst(Address(fTemp133, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp134, kStack)))))))))
		DeclareVarInst("float", fTemp139, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp135, kStack)))))
		DeclareVarInst("float", fTemp140, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp139, kStack)))))
		DeclareVarInst("float", fTemp141, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp116, kStack)), LoadVarInst(Address(fTemp140, kStack))), BinopInst("*", LoadVarInst(Address(fTemp135, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp142, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp138, kStack)))))
		DeclareVarInst("float", fTemp143, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp142, kStack)))))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp141, kStack)), LoadVarInst(Address(fTemp143, kStack))), BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp138, kStack)))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp138, kStack)), LoadVarInst(Address(fTemp141, kStack))), BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp143, kStack)))))
		DeclareVarInst("float", fTemp144, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp133, kStack))))
		DeclareVarInst("float", fTemp145, kStack, BinopInst("/", LoadVarInst(Address(fTemp137, kStack)), LoadVarInst(Address(fTemp144, kStack))))
		DeclareVarInst("float", fTemp146, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp133, kStack))))
		DeclareVarInst("float", fTemp147, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fTemp138, kStack))))
		DeclareVarInst("float", fTemp148, kStack, BinopInst("+", BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp116, kStack)), LoadVarInst(Address(fTemp135, kStack))), BinopInst("*", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp140, kStack)))), LoadVarInst(Address(fTemp133, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec14, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fTemp146, kStack)), LoadVarInst(Address(fTemp145, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp146, kStack)), BinopInst("*", LoadVarInst(Address(fTemp147, kStack)), BinopInst("-", LoadVarInst(Address(fTemp145, kStack)), LoadVarInst(Address(fTemp146, kStack))))), BinopInst("/", LoadVarInst(Address(fTemp132, kStack)), LoadVarInst(Address(fTemp144, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp142, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp139, kStack))))))
		DeclareVarInst("float", fTemp149, kStack, BinopInst("/", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fTemp127, kStack))))
		DeclareVarInst("float", fTemp150, kStack, BinopInst("-", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp130, kStack))))
		DeclareVarInst("float", fTemp151, kStack, NegInst(BinopInst("+", LoadVarInst(Address(fTemp149, kStack)), LoadVarInst(Address(fTemp150, kStack)))))
		DeclareVarInst("float", fTemp152, kStack, BinopInst("-", LoadVarInst(Address(fTemp149, kStack)), LoadVarInst(Address(fTemp150, kStack))))
		DeclareVarInst("float", fTemp153, kStack, BinopInst("/", LoadVarInst(Address(fTemp151, kStack)), LoadVarInst(Address(fTemp152, kStack))))
		DeclareVarInst("float", fTemp154, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp153, kStack)))))
		DeclareVarInst("float", fTemp155, kStack, NegInst(BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp136, kStack)))))
		DeclareVarInst("float", fTemp156, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp155, kStack)), BinopInst("*", LoadVarInst(Address(fTemp152, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp153, kStack)))))))))
		DeclareVarInst("float", fTemp157, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp154, kStack)))))
		DeclareVarInst("float", fTemp158, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp157, kStack)))))
		DeclareVarInst("float", fTemp159, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp148, kStack)), LoadVarInst(Address(fTemp158, kStack))), BinopInst("*", LoadVarInst(Address(fTemp154, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp160, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp156, kStack)))))
		DeclareVarInst("float", fTemp161, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp160, kStack)))))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp159, kStack)), LoadVarInst(Address(fTemp161, kStack))), BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp156, kStack)))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp156, kStack)), LoadVarInst(Address(fTemp159, kStack))), BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp161, kStack)))))
		DeclareVarInst("float", fTemp162, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp152, kStack))))
		DeclareVarInst("float", fTemp163, kStack, BinopInst("/", LoadVarInst(Address(fTemp155, kStack)), LoadVarInst(Address(fTemp162, kStack))))
		DeclareVarInst("float", fTemp164, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp152, kStack))))
		DeclareVarInst("float", fTemp165, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fTemp156, kStack))))
		DeclareVarInst("float", fTemp166, kStack, BinopInst("+", LoadVarInst(Address(fSlow42, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR11, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp166, kStack)))
		DeclareVarInst("float", fTemp167, kStack, Select2Inst(LoadVarInst(Address(iSlow1, kStack)) LoadVarInst(Address(fTemp115, kStack)) BinopInst("*", Select2Inst(LoadVarInst(Address(iSlow2, kStack)) Select2Inst(LoadVarInst(Address(iSlow32, kStack)) BinopInst("+", BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp148, kStack)), LoadVarInst(Address(fTemp154, kStack))), BinopInst("*", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp158, kStack)))), LoadVarInst(Address(fTemp152, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec16, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fTemp164, kStack)), LoadVarInst(Address(fTemp163, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp164, kStack)), BinopInst("*", LoadVarInst(Address(fTemp165, kStack)), BinopInst("-", LoadVarInst(Address(fTemp163, kStack)), LoadVarInst(Address(fTemp164, kStack))))), BinopInst("/", LoadVarInst(Address(fTemp151, kStack)), LoadVarInst(Address(fTemp162, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp160, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp157, kStack))))) BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))), LoadVarInst(Address(fRec11, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp123, kStack)))) LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp166, kStack))))))
		DeclareVarInst("float", fTemp168, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp167, kStack)), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp168, kStack)))
		DeclareVarInst("float", fTemp169, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst33, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst37, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst38, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp169, kStack)))
		DeclareVarInst("float", fTemp170, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst41, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst46, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp170, kStack)))
		DeclareVarInst("float", fTemp171, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp172, kStack, BinopInst("+", LoadVarInst(Address(fTemp171, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM0, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp171, kStack))))))
		StoreVarInst(Address(fIRM0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp172, kStack)))
		StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp172, kStack)))))))
		DeclareVarInst("float", fTemp173, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp167, kStack)), BinopInst("*", LoadVarInst(Address(fConst54, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst55, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp173, kStack)))
		DeclareVarInst("float", fTemp174, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst57, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst58, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst57, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst62, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst63, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR25, kStruct)[Int32(0)], LoadVarInst(Address(fTemp174, kStack)))
		DeclareVarInst("float", fTemp175, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst64, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst65, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst64, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst69, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst70, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR24, kStruct)[Int32(0)], LoadVarInst(Address(fTemp175, kStack)))
		DeclareVarInst("float", fTemp176, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst71, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst72, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst71, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp177, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp176, kStack)), BinopInst("*", LoadVarInst(Address(fConst79, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst80, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp177, kStack)))
		DeclareVarInst("float", fTemp178, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst82, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst83, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst82, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst87, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst88, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR22, kStruct)[Int32(0)], LoadVarInst(Address(fTemp178, kStack)))
		DeclareVarInst("float", fTemp179, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst89, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst90, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst89, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst94, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst95, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp179, kStack)))
		DeclareVarInst("float", fTemp180, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst96, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst97, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst96, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp181, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp180, kStack)), BinopInst("*", LoadVarInst(Address(fConst104, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst105, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR20, kStruct)[Int32(0)], LoadVarInst(Address(fTemp181, kStack)))
		DeclareVarInst("float", fTemp182, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst107, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst108, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst107, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst112, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst113, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp182, kStack)))
		DeclareVarInst("float", fTemp183, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst114, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst115, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst114, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst119, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst120, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp183, kStack)))
		DeclareVarInst("float", fTemp184, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst122, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp185, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp184, kStack)), BinopInst("*", LoadVarInst(Address(fConst129, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst130, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp185, kStack)))
		DeclareVarInst("float", fTemp186, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst132, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst133, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst132, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst137, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst138, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp186, kStack)))
		DeclareVarInst("float", fTemp187, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst139, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst140, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst139, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst144, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst145, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp187, kStack)))
		DeclareVarInst("float", fTemp188, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst146, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst147, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst146, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp189, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp188, kStack)), BinopInst("*", LoadVarInst(Address(fConst154, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst155, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp189, kStack)))
		DeclareVarInst("float", fTemp190, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst158, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst162, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst163, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp190, kStack)))
		DeclareVarInst("float", fTemp191, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst165, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst166, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst165, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst170, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst171, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp191, kStack)))
		DeclareVarInst("float", fTemp192, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst173, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst174, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst173, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp193, kStack, BinopInst("+", LoadVarInst(Address(fTemp192, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM2, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp192, kStack))))))
		StoreVarInst(Address(fIRM2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp193, kStack)))
		StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp193, kStack)))))))
		DeclareVarInst("float", fTemp194, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp188, kStack)), BinopInst("*", LoadVarInst(Address(fConst178, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst179, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR41, kStruct)[Int32(0)], LoadVarInst(Address(fTemp194, kStack)))
		DeclareVarInst("float", fTemp195, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst181, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst182, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst181, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst186, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst187, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR40, kStruct)[Int32(0)], LoadVarInst(Address(fTemp195, kStack)))
		DeclareVarInst("float", fTemp196, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst189, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst193, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst194, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR39, kStruct)[Int32(0)], LoadVarInst(Address(fTemp196, kStack)))
		DeclareVarInst("float", fTemp197, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst196, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp198, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp197, kStack)), BinopInst("*", LoadVarInst(Address(fConst203, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst204, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR38, kStruct)[Int32(0)], LoadVarInst(Address(fTemp198, kStack)))
		DeclareVarInst("float", fTemp199, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst206, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst207, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst206, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst211, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst212, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR37, kStruct)[Int32(0)], LoadVarInst(Address(fTemp199, kStack)))
		DeclareVarInst("float", fTemp200, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst213, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst214, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst213, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst218, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst219, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR36, kStruct)[Int32(0)], LoadVarInst(Address(fTemp200, kStack)))
		DeclareVarInst("float", fTemp201, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst220, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst221, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst220, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp202, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp201, kStack)), BinopInst("*", LoadVarInst(Address(fConst228, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst229, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR35, kStruct)[Int32(0)], LoadVarInst(Address(fTemp202, kStack)))
		DeclareVarInst("float", fTemp203, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst231, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst232, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst231, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst236, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst237, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR34, kStruct)[Int32(0)], LoadVarInst(Address(fTemp203, kStack)))
		DeclareVarInst("float", fTemp204, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst239, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst243, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst244, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR33, kStruct)[Int32(0)], LoadVarInst(Address(fTemp204, kStack)))
		DeclareVarInst("float", fTemp205, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst245, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst246, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst245, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp206, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp205, kStack)), BinopInst("*", LoadVarInst(Address(fConst253, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst254, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp206, kStack)))
		DeclareVarInst("float", fTemp207, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst256, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst257, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst256, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst261, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst262, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR31, kStruct)[Int32(0)], LoadVarInst(Address(fTemp207, kStack)))
		DeclareVarInst("float", fTemp208, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst263, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst264, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst263, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst268, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst269, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR30, kStruct)[Int32(0)], LoadVarInst(Address(fTemp208, kStack)))
		DeclareVarInst("float", fTemp209, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst271, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp210, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp209, kStack)), BinopInst("*", LoadVarInst(Address(fConst278, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst279, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp210, kStack)))
		DeclareVarInst("float", fTemp211, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst281, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst282, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst281, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst286, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst287, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR28, kStruct)[Int32(0)], LoadVarInst(Address(fTemp211, kStack)))
		DeclareVarInst("float", fTemp212, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst289, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst290, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst289, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst294, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst295, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR27, kStruct)[Int32(0)], LoadVarInst(Address(fTemp212, kStack)))
		DeclareVarInst("float", fTemp213, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst297, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst298, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst297, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp214, kStack, BinopInst("+", LoadVarInst(Address(fTemp213, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM3, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp213, kStack))))))
		StoreVarInst(Address(fIRM3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp214, kStack)))
		StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp214, kStack)))))))
		DeclareVarInst("float", fTemp215, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp209, kStack)), BinopInst("*", LoadVarInst(Address(fConst302, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst303, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR56, kStruct)[Int32(0)], LoadVarInst(Address(fTemp215, kStack)))
		DeclareVarInst("float", fTemp216, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst306, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst310, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst311, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR55, kStruct)[Int32(0)], LoadVarInst(Address(fTemp216, kStack)))
		DeclareVarInst("float", fTemp217, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst313, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst317, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst318, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR54, kStruct)[Int32(0)], LoadVarInst(Address(fTemp217, kStack)))
		DeclareVarInst("float", fTemp218, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst319, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst320, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst319, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp219, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp218, kStack)), BinopInst("*", LoadVarInst(Address(fConst327, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst328, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR53, kStruct)[Int32(0)], LoadVarInst(Address(fTemp219, kStack)))
		DeclareVarInst("float", fTemp220, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst330, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst331, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst330, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst335, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst336, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR52, kStruct)[Int32(0)], LoadVarInst(Address(fTemp220, kStack)))
		DeclareVarInst("float", fTemp221, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst337, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst338, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst337, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst342, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst343, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR51, kStruct)[Int32(0)], LoadVarInst(Address(fTemp221, kStack)))
		DeclareVarInst("float", fTemp222, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst345, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp223, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp222, kStack)), BinopInst("*", LoadVarInst(Address(fConst352, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst353, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR50, kStruct)[Int32(0)], LoadVarInst(Address(fTemp223, kStack)))
		DeclareVarInst("float", fTemp224, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst355, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst356, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst355, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst360, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst361, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR49, kStruct)[Int32(0)], LoadVarInst(Address(fTemp224, kStack)))
		DeclareVarInst("float", fTemp225, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst362, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst363, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst362, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst367, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst368, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR48, kStruct)[Int32(0)], LoadVarInst(Address(fTemp225, kStack)))
		DeclareVarInst("float", fTemp226, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst369, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst370, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst369, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp227, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp226, kStack)), BinopInst("*", LoadVarInst(Address(fConst377, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst378, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR47, kStruct)[Int32(0)], LoadVarInst(Address(fTemp227, kStack)))
		DeclareVarInst("float", fTemp228, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst380, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst381, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst380, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst385, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst386, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR46, kStruct)[Int32(0)], LoadVarInst(Address(fTemp228, kStack)))
		DeclareVarInst("float", fTemp229, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst388, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst392, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst393, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR45, kStruct)[Int32(0)], LoadVarInst(Address(fTemp229, kStack)))
		DeclareVarInst("float", fTemp230, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst395, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp231, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp230, kStack)), BinopInst("*", LoadVarInst(Address(fConst402, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst403, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR44, kStruct)[Int32(0)], LoadVarInst(Address(fTemp231, kStack)))
		DeclareVarInst("float", fTemp232, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst405, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst406, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst405, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst410, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst411, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR43, kStruct)[Int32(0)], LoadVarInst(Address(fTemp232, kStack)))
		DeclareVarInst("float", fTemp233, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst413, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst414, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst413, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst418, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst419, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR42, kStruct)[Int32(0)], LoadVarInst(Address(fTemp233, kStack)))
		DeclareVarInst("float", fTemp234, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst421, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst422, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst421, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp235, kStack, BinopInst("+", LoadVarInst(Address(fTemp234, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM4, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp234, kStack))))))
		StoreVarInst(Address(fIRM4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp235, kStack)))
		StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp235, kStack)))))))
		DeclareVarInst("float", fTemp236, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp176, kStack)), BinopInst("*", LoadVarInst(Address(fConst426, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst427, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR59, kStruct)[Int32(0)], LoadVarInst(Address(fTemp236, kStack)))
		DeclareVarInst("float", fTemp237, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst430, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst434, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst435, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR58, kStruct)[Int32(0)], LoadVarInst(Address(fTemp237, kStack)))
		DeclareVarInst("float", fTemp238, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst437, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst438, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst437, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst442, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst443, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR57, kStruct)[Int32(0)], LoadVarInst(Address(fTemp238, kStack)))
		DeclareVarInst("float", fTemp239, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst445, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst446, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst445, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp240, kStack, BinopInst("+", LoadVarInst(Address(fTemp239, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM5, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp239, kStack))))))
		StoreVarInst(Address(fIRM5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp240, kStack)))
		StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp240, kStack)))))))
		DeclareVarInst("float", fTemp241, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp197, kStack)), BinopInst("*", LoadVarInst(Address(fConst450, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst451, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR62, kStruct)[Int32(0)], LoadVarInst(Address(fTemp241, kStack)))
		DeclareVarInst("float", fTemp242, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst453, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst454, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst453, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst458, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst459, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR61, kStruct)[Int32(0)], LoadVarInst(Address(fTemp242, kStack)))
		DeclareVarInst("float", fTemp243, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst462, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst466, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst467, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR60, kStruct)[Int32(0)], LoadVarInst(Address(fTemp243, kStack)))
		DeclareVarInst("float", fTemp244, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst469, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst470, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst469, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp245, kStack, BinopInst("+", LoadVarInst(Address(fTemp244, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM6, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp244, kStack))))))
		StoreVarInst(Address(fIRM6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp245, kStack)))
		StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp245, kStack)))))))
		DeclareVarInst("float", fTemp246, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp218, kStack)), BinopInst("*", LoadVarInst(Address(fConst474, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst475, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR65, kStruct)[Int32(0)], LoadVarInst(Address(fTemp246, kStack)))
		DeclareVarInst("float", fTemp247, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst477, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst478, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst477, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst482, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst483, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR64, kStruct)[Int32(0)], LoadVarInst(Address(fTemp247, kStack)))
		DeclareVarInst("float", fTemp248, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst485, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst486, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst485, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst490, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst491, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR63, kStruct)[Int32(0)], LoadVarInst(Address(fTemp248, kStack)))
		DeclareVarInst("float", fTemp249, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst493, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst494, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst493, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp250, kStack, BinopInst("+", LoadVarInst(Address(fTemp249, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM7, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp249, kStack))))))
		StoreVarInst(Address(fIRM7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp250, kStack)))
		StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp250, kStack)))))))
		DeclareVarInst("float", fTemp251, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp230, kStack)), BinopInst("*", LoadVarInst(Address(fConst498, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst499, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR71, kStruct)[Int32(0)], LoadVarInst(Address(fTemp251, kStack)))
		DeclareVarInst("float", fTemp252, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst502, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst506, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst507, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR70, kStruct)[Int32(0)], LoadVarInst(Address(fTemp252, kStack)))
		DeclareVarInst("float", fTemp253, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst509, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst513, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst514, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR69, kStruct)[Int32(0)], LoadVarInst(Address(fTemp253, kStack)))
		DeclareVarInst("float", fTemp254, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst515, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst516, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst515, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp255, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp254, kStack)), BinopInst("*", LoadVarInst(Address(fConst523, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst524, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR68, kStruct)[Int32(0)], LoadVarInst(Address(fTemp255, kStack)))
		DeclareVarInst("float", fTemp256, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst526, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst527, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst526, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst531, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst532, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR67, kStruct)[Int32(0)], LoadVarInst(Address(fTemp256, kStack)))
		DeclareVarInst("float", fTemp257, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst535, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst539, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst540, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR66, kStruct)[Int32(0)], LoadVarInst(Address(fTemp257, kStack)))
		DeclareVarInst("float", fTemp258, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst542, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst543, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst542, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp259, kStack, BinopInst("+", LoadVarInst(Address(fTemp258, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM8, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp258, kStack))))))
		StoreVarInst(Address(fIRM8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp259, kStack)))
		StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp259, kStack)))))))
		DeclareVarInst("float", fTemp260, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp180, kStack)), BinopInst("*", LoadVarInst(Address(fConst547, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst548, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR74, kStruct)[Int32(0)], LoadVarInst(Address(fTemp260, kStack)))
		DeclareVarInst("float", fTemp261, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst550, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst551, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst550, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst555, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst556, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR73, kStruct)[Int32(0)], LoadVarInst(Address(fTemp261, kStack)))
		DeclareVarInst("float", fTemp262, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst558, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst559, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst558, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst563, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst564, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR72, kStruct)[Int32(0)], LoadVarInst(Address(fTemp262, kStack)))
		DeclareVarInst("float", fTemp263, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst566, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst567, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst566, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp264, kStack, BinopInst("+", LoadVarInst(Address(fTemp263, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM9, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp263, kStack))))))
		StoreVarInst(Address(fIRM9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp264, kStack)))
		StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp264, kStack)))))))
		DeclareVarInst("float", fTemp265, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp201, kStack)), BinopInst("*", LoadVarInst(Address(fConst571, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst572, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR77, kStruct)[Int32(0)], LoadVarInst(Address(fTemp265, kStack)))
		DeclareVarInst("float", fTemp266, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst574, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst575, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst574, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst579, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst580, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR76, kStruct)[Int32(0)], LoadVarInst(Address(fTemp266, kStack)))
		DeclareVarInst("float", fTemp267, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst582, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst583, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst582, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst587, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst588, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR75, kStruct)[Int32(0)], LoadVarInst(Address(fTemp267, kStack)))
		DeclareVarInst("float", fTemp268, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst590, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst591, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst590, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp269, kStack, BinopInst("+", LoadVarInst(Address(fTemp268, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM10, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp268, kStack))))))
		StoreVarInst(Address(fIRM10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp269, kStack)))
		StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp269, kStack)))))))
		DeclareVarInst("float", fTemp270, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp222, kStack)), BinopInst("*", LoadVarInst(Address(fConst595, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst596, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR80, kStruct)[Int32(0)], LoadVarInst(Address(fTemp270, kStack)))
		DeclareVarInst("float", fTemp271, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst598, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst599, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst598, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst603, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst604, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR79, kStruct)[Int32(0)], LoadVarInst(Address(fTemp271, kStack)))
		DeclareVarInst("float", fTemp272, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst606, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst607, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst606, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst611, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst612, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR78, kStruct)[Int32(0)], LoadVarInst(Address(fTemp272, kStack)))
		DeclareVarInst("float", fTemp273, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst614, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst615, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst614, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp274, kStack, BinopInst("+", LoadVarInst(Address(fTemp273, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM11, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp273, kStack))))))
		StoreVarInst(Address(fIRM11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp274, kStack)))
		StoreVarInst(Address(fVbargraph10, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp274, kStack)))))))
		DeclareVarInst("float", fTemp275, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp254, kStack)), BinopInst("*", LoadVarInst(Address(fConst619, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst620, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR83, kStruct)[Int32(0)], LoadVarInst(Address(fTemp275, kStack)))
		DeclareVarInst("float", fTemp276, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst622, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst623, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst622, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst627, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst628, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR82, kStruct)[Int32(0)], LoadVarInst(Address(fTemp276, kStack)))
		DeclareVarInst("float", fTemp277, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst629, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst630, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst629, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst634, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst635, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR81, kStruct)[Int32(0)], LoadVarInst(Address(fTemp277, kStack)))
		DeclareVarInst("float", fTemp278, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst636, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst637, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst636, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp279, kStack, BinopInst("+", LoadVarInst(Address(fTemp278, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM12, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp278, kStack))))))
		StoreVarInst(Address(fIRM12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp279, kStack)))
		StoreVarInst(Address(fVbargraph11, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp279, kStack)))))))
		DeclareVarInst("float", fTemp280, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp184, kStack)), BinopInst("*", LoadVarInst(Address(fConst641, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst642, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR86, kStruct)[Int32(0)], LoadVarInst(Address(fTemp280, kStack)))
		DeclareVarInst("float", fTemp281, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst644, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst645, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst644, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst649, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst650, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR85, kStruct)[Int32(0)], LoadVarInst(Address(fTemp281, kStack)))
		DeclareVarInst("float", fTemp282, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst652, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst653, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst652, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst657, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst658, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR84, kStruct)[Int32(0)], LoadVarInst(Address(fTemp282, kStack)))
		DeclareVarInst("float", fTemp283, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst660, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst661, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst660, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp284, kStack, BinopInst("+", LoadVarInst(Address(fTemp283, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM13, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp283, kStack))))))
		StoreVarInst(Address(fIRM13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp284, kStack)))
		StoreVarInst(Address(fVbargraph12, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp284, kStack)))))))
		DeclareVarInst("float", fTemp285, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp205, kStack)), BinopInst("*", LoadVarInst(Address(fConst665, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst666, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR89, kStruct)[Int32(0)], LoadVarInst(Address(fTemp285, kStack)))
		DeclareVarInst("float", fTemp286, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst668, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst669, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst668, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst673, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst674, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR88, kStruct)[Int32(0)], LoadVarInst(Address(fTemp286, kStack)))
		DeclareVarInst("float", fTemp287, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst676, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst677, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst676, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst681, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst682, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR87, kStruct)[Int32(0)], LoadVarInst(Address(fTemp287, kStack)))
		DeclareVarInst("float", fTemp288, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst684, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst685, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst684, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp289, kStack, BinopInst("+", LoadVarInst(Address(fTemp288, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp288, kStack))))))
		StoreVarInst(Address(fIRM14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp289, kStack)))
		StoreVarInst(Address(fVbargraph13, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp289, kStack)))))))
		DeclareVarInst("float", fTemp290, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp226, kStack)), BinopInst("*", LoadVarInst(Address(fConst689, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst690, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR92, kStruct)[Int32(0)], LoadVarInst(Address(fTemp290, kStack)))
		DeclareVarInst("float", fTemp291, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst692, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst693, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst692, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst697, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst698, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR91, kStruct)[Int32(0)], LoadVarInst(Address(fTemp291, kStack)))
		DeclareVarInst("float", fTemp292, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst700, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst701, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst700, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst705, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst706, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR90, kStruct)[Int32(0)], LoadVarInst(Address(fTemp292, kStack)))
		DeclareVarInst("float", fTemp293, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst708, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst709, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst708, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(2)])))))
		DeclareVarInst("float", fTemp294, kStack, BinopInst("+", LoadVarInst(Address(fTemp293, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM15, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp293, kStack))))))
		StoreVarInst(Address(fIRM15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp294, kStack)))
		StoreVarInst(Address(fVbargraph14, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp294, kStack)))))))
		DeclareVarInst("float", fTemp295, kStack, LoadVarInst(Address(fTemp167, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp295, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp295, kStack))))
		ForLoopInst 
			DeclareVarInst("int", j0, kLoop, Int32(3))
			BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
			StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(iVec0, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM1, kStruct)[Int32(1)], LoadVarInst(Address(fIRM1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec4, kStruct)[Int32(1)], LoadVarInst(Address(fVec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec5, kStruct)[Int32(1)], LoadVarInst(Address(fVec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec6, kStruct)[Int32(1)], LoadVarInst(Address(fVec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec7, kStruct)[Int32(1)], LoadVarInst(Address(fVec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec8, kStruct)[Int32(1)], LoadVarInst(Address(fVec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec9, kStruct)[Int32(1)], LoadVarInst(Address(fVec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec10, kStruct)[Int32(1)], LoadVarInst(Address(fVec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec11, kStruct)[Int32(1)], LoadVarInst(Address(fVec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec12, kStruct)[Int32(1)], LoadVarInst(Address(fVec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec13, kStruct)[Int32(1)], LoadVarInst(Address(fVec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec14, kStruct)[Int32(1)], LoadVarInst(Address(fVec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec15, kStruct)[Int32(1)], LoadVarInst(Address(fVec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec16, kStruct)[Int32(1)], LoadVarInst(Address(fVec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec17, kStruct)[Int32(1)], LoadVarInst(Address(fVec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec18, kStruct)[Int32(1)], LoadVarInst(Address(fVec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec19, kStruct)[Int32(1)], LoadVarInst(Address(fVec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec21, kStruct)[Int32(1)], LoadVarInst(Address(fVec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec23, kStruct)[Int32(1)], LoadVarInst(Address(fVec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec25, kStruct)[Int32(1)], LoadVarInst(Address(fVec25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec26, kStruct)[Int32(1)], LoadVarInst(Address(fVec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec28, kStruct)[Int32(1)], LoadVarInst(Address(fVec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec29, kStruct)[Int32(1)], LoadVarInst(Address(fVec29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec31, kStruct)[Int32(1)], LoadVarInst(Address(fVec31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec32, kStruct)[Int32(1)], LoadVarInst(Address(fVec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(iIIR10, kStruct)[Int32(1)], LoadVarInst(Address(iIIR10, kStruct)[Int32(0)]))
		ForLoopInst 
			DeclareVarInst("int", j1, kLoop, Int32(3))
			BinopInst(">", LoadVarInst(Address(j1, kLoop)), Int32(0))
			StoreVarInst(Address(j1, kLoop), BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fIIR9, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
		ForLoopInst 
			DeclareVarInst("int", j2, kLoop, Int32(3))
			BinopInst(">", LoadVarInst(Address(j2, kLoop)), Int32(0))
			StoreVarInst(Address(j2, kLoop), BinopInst("-", LoadVarInst(Address(j2, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(fVec34, kStruct)[LoadVarInst(Address(j2, kLoop))], LoadVarInst(Address(fVec34, kStruct)[BinopInst("-", LoadVarInst(Address(j2, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(2)], LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR11, kStruct)[Int32(1)], LoadVarInst(Address(fIIR11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(2)], LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(2)], LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM0, kStruct)[Int32(1)], LoadVarInst(Address(fIRM0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR26, kStruct)[Int32(2)], LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR26, kStruct)[Int32(1)], LoadVarInst(Address(fIIR26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR25, kStruct)[Int32(2)], LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR25, kStruct)[Int32(1)], LoadVarInst(Address(fIIR25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR24, kStruct)[Int32(2)], LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR24, kStruct)[Int32(1)], LoadVarInst(Address(fIIR24, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR23, kStruct)[Int32(2)], LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR23, kStruct)[Int32(1)], LoadVarInst(Address(fIIR23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR22, kStruct)[Int32(2)], LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR22, kStruct)[Int32(1)], LoadVarInst(Address(fIIR22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR21, kStruct)[Int32(2)], LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR21, kStruct)[Int32(1)], LoadVarInst(Address(fIIR21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR20, kStruct)[Int32(2)], LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR20, kStruct)[Int32(1)], LoadVarInst(Address(fIIR20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR19, kStruct)[Int32(2)], LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR19, kStruct)[Int32(1)], LoadVarInst(Address(fIIR19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR18, kStruct)[Int32(2)], LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR18, kStruct)[Int32(1)], LoadVarInst(Address(fIIR18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR17, kStruct)[Int32(2)], LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR17, kStruct)[Int32(1)], LoadVarInst(Address(fIIR17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR16, kStruct)[Int32(2)], LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR16, kStruct)[Int32(1)], LoadVarInst(Address(fIIR16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR15, kStruct)[Int32(2)], LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR15, kStruct)[Int32(1)], LoadVarInst(Address(fIIR15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR14, kStruct)[Int32(2)], LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR14, kStruct)[Int32(1)], LoadVarInst(Address(fIIR14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR13, kStruct)[Int32(2)], LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR13, kStruct)[Int32(1)], LoadVarInst(Address(fIIR13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR12, kStruct)[Int32(2)], LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR12, kStruct)[Int32(1)], LoadVarInst(Address(fIIR12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM2, kStruct)[Int32(1)], LoadVarInst(Address(fIRM2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR41, kStruct)[Int32(2)], LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR41, kStruct)[Int32(1)], LoadVarInst(Address(fIIR41, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR40, kStruct)[Int32(2)], LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR40, kStruct)[Int32(1)], LoadVarInst(Address(fIIR40, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR39, kStruct)[Int32(2)], LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR39, kStruct)[Int32(1)], LoadVarInst(Address(fIIR39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR38, kStruct)[Int32(2)], LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR38, kStruct)[Int32(1)], LoadVarInst(Address(fIIR38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR37, kStruct)[Int32(2)], LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR37, kStruct)[Int32(1)], LoadVarInst(Address(fIIR37, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR36, kStruct)[Int32(2)], LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR36, kStruct)[Int32(1)], LoadVarInst(Address(fIIR36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR35, kStruct)[Int32(2)], LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR35, kStruct)[Int32(1)], LoadVarInst(Address(fIIR35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR34, kStruct)[Int32(2)], LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR34, kStruct)[Int32(1)], LoadVarInst(Address(fIIR34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR33, kStruct)[Int32(2)], LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR33, kStruct)[Int32(1)], LoadVarInst(Address(fIIR33, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR32, kStruct)[Int32(2)], LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR32, kStruct)[Int32(1)], LoadVarInst(Address(fIIR32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR31, kStruct)[Int32(2)], LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR31, kStruct)[Int32(1)], LoadVarInst(Address(fIIR31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR30, kStruct)[Int32(2)], LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR30, kStruct)[Int32(1)], LoadVarInst(Address(fIIR30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR29, kStruct)[Int32(2)], LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR29, kStruct)[Int32(1)], LoadVarInst(Address(fIIR29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR28, kStruct)[Int32(2)], LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR28, kStruct)[Int32(1)], LoadVarInst(Address(fIIR28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR27, kStruct)[Int32(2)], LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR27, kStruct)[Int32(1)], LoadVarInst(Address(fIIR27, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM3, kStruct)[Int32(1)], LoadVarInst(Address(fIRM3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR56, kStruct)[Int32(2)], LoadVarInst(Address(fIIR56, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR56, kStruct)[Int32(1)], LoadVarInst(Address(fIIR56, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR55, kStruct)[Int32(2)], LoadVarInst(Address(fIIR55, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR55, kStruct)[Int32(1)], LoadVarInst(Address(fIIR55, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR54, kStruct)[Int32(2)], LoadVarInst(Address(fIIR54, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR54, kStruct)[Int32(1)], LoadVarInst(Address(fIIR54, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR53, kStruct)[Int32(2)], LoadVarInst(Address(fIIR53, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR53, kStruct)[Int32(1)], LoadVarInst(Address(fIIR53, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR52, kStruct)[Int32(2)], LoadVarInst(Address(fIIR52, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR52, kStruct)[Int32(1)], LoadVarInst(Address(fIIR52, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR51, kStruct)[Int32(2)], LoadVarInst(Address(fIIR51, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR51, kStruct)[Int32(1)], LoadVarInst(Address(fIIR51, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR50, kStruct)[Int32(2)], LoadVarInst(Address(fIIR50, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR50, kStruct)[Int32(1)], LoadVarInst(Address(fIIR50, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR49, kStruct)[Int32(2)], LoadVarInst(Address(fIIR49, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR49, kStruct)[Int32(1)], LoadVarInst(Address(fIIR49, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR48, kStruct)[Int32(2)], LoadVarInst(Address(fIIR48, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR48, kStruct)[Int32(1)], LoadVarInst(Address(fIIR48, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR47, kStruct)[Int32(2)], LoadVarInst(Address(fIIR47, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR47, kStruct)[Int32(1)], LoadVarInst(Address(fIIR47, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR46, kStruct)[Int32(2)], LoadVarInst(Address(fIIR46, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR46, kStruct)[Int32(1)], LoadVarInst(Address(fIIR46, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR45, kStruct)[Int32(2)], LoadVarInst(Address(fIIR45, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR45, kStruct)[Int32(1)], LoadVarInst(Address(fIIR45, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR44, kStruct)[Int32(2)], LoadVarInst(Address(fIIR44, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR44, kStruct)[Int32(1)], LoadVarInst(Address(fIIR44, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR43, kStruct)[Int32(2)], LoadVarInst(Address(fIIR43, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR43, kStruct)[Int32(1)], LoadVarInst(Address(fIIR43, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR42, kStruct)[Int32(2)], LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR42, kStruct)[Int32(1)], LoadVarInst(Address(fIIR42, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM4, kStruct)[Int32(1)], LoadVarInst(Address(fIRM4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR59, kStruct)[Int32(2)], LoadVarInst(Address(fIIR59, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR59, kStruct)[Int32(1)], LoadVarInst(Address(fIIR59, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR58, kStruct)[Int32(2)], LoadVarInst(Address(fIIR58, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR58, kStruct)[Int32(1)], LoadVarInst(Address(fIIR58, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR57, kStruct)[Int32(2)], LoadVarInst(Address(fIIR57, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR57, kStruct)[Int32(1)], LoadVarInst(Address(fIIR57, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM5, kStruct)[Int32(1)], LoadVarInst(Address(fIRM5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR62, kStruct)[Int32(2)], LoadVarInst(Address(fIIR62, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR62, kStruct)[Int32(1)], LoadVarInst(Address(fIIR62, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR61, kStruct)[Int32(2)], LoadVarInst(Address(fIIR61, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR61, kStruct)[Int32(1)], LoadVarInst(Address(fIIR61, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR60, kStruct)[Int32(2)], LoadVarInst(Address(fIIR60, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR60, kStruct)[Int32(1)], LoadVarInst(Address(fIIR60, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM6, kStruct)[Int32(1)], LoadVarInst(Address(fIRM6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR65, kStruct)[Int32(2)], LoadVarInst(Address(fIIR65, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR65, kStruct)[Int32(1)], LoadVarInst(Address(fIIR65, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR64, kStruct)[Int32(2)], LoadVarInst(Address(fIIR64, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR64, kStruct)[Int32(1)], LoadVarInst(Address(fIIR64, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR63, kStruct)[Int32(2)], LoadVarInst(Address(fIIR63, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR63, kStruct)[Int32(1)], LoadVarInst(Address(fIIR63, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM7, kStruct)[Int32(1)], LoadVarInst(Address(fIRM7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR71, kStruct)[Int32(2)], LoadVarInst(Address(fIIR71, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR71, kStruct)[Int32(1)], LoadVarInst(Address(fIIR71, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR70, kStruct)[Int32(2)], LoadVarInst(Address(fIIR70, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR70, kStruct)[Int32(1)], LoadVarInst(Address(fIIR70, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR69, kStruct)[Int32(2)], LoadVarInst(Address(fIIR69, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR69, kStruct)[Int32(1)], LoadVarInst(Address(fIIR69, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR68, kStruct)[Int32(2)], LoadVarInst(Address(fIIR68, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR68, kStruct)[Int32(1)], LoadVarInst(Address(fIIR68, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR67, kStruct)[Int32(2)], LoadVarInst(Address(fIIR67, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR67, kStruct)[Int32(1)], LoadVarInst(Address(fIIR67, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR66, kStruct)[Int32(2)], LoadVarInst(Address(fIIR66, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR66, kStruct)[Int32(1)], LoadVarInst(Address(fIIR66, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM8, kStruct)[Int32(1)], LoadVarInst(Address(fIRM8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR74, kStruct)[Int32(2)], LoadVarInst(Address(fIIR74, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR74, kStruct)[Int32(1)], LoadVarInst(Address(fIIR74, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR73, kStruct)[Int32(2)], LoadVarInst(Address(fIIR73, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR73, kStruct)[Int32(1)], LoadVarInst(Address(fIIR73, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR72, kStruct)[Int32(2)], LoadVarInst(Address(fIIR72, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR72, kStruct)[Int32(1)], LoadVarInst(Address(fIIR72, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM9, kStruct)[Int32(1)], LoadVarInst(Address(fIRM9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR77, kStruct)[Int32(2)], LoadVarInst(Address(fIIR77, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR77, kStruct)[Int32(1)], LoadVarInst(Address(fIIR77, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR76, kStruct)[Int32(2)], LoadVarInst(Address(fIIR76, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR76, kStruct)[Int32(1)], LoadVarInst(Address(fIIR76, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR75, kStruct)[Int32(2)], LoadVarInst(Address(fIIR75, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR75, kStruct)[Int32(1)], LoadVarInst(Address(fIIR75, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM10, kStruct)[Int32(1)], LoadVarInst(Address(fIRM10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR80, kStruct)[Int32(2)], LoadVarInst(Address(fIIR80, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR80, kStruct)[Int32(1)], LoadVarInst(Address(fIIR80, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR79, kStruct)[Int32(2)], LoadVarInst(Address(fIIR79, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR79, kStruct)[Int32(1)], LoadVarInst(Address(fIIR79, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR78, kStruct)[Int32(2)], LoadVarInst(Address(fIIR78, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR78, kStruct)[Int32(1)], LoadVarInst(Address(fIIR78, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM11, kStruct)[Int32(1)], LoadVarInst(Address(fIRM11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR83, kStruct)[Int32(2)], LoadVarInst(Address(fIIR83, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR83, kStruct)[Int32(1)], LoadVarInst(Address(fIIR83, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR82, kStruct)[Int32(2)], LoadVarInst(Address(fIIR82, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR82, kStruct)[Int32(1)], LoadVarInst(Address(fIIR82, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR81, kStruct)[Int32(2)], LoadVarInst(Address(fIIR81, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR81, kStruct)[Int32(1)], LoadVarInst(Address(fIIR81, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM12, kStruct)[Int32(1)], LoadVarInst(Address(fIRM12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR86, kStruct)[Int32(2)], LoadVarInst(Address(fIIR86, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR86, kStruct)[Int32(1)], LoadVarInst(Address(fIIR86, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR85, kStruct)[Int32(2)], LoadVarInst(Address(fIIR85, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR85, kStruct)[Int32(1)], LoadVarInst(Address(fIIR85, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR84, kStruct)[Int32(2)], LoadVarInst(Address(fIIR84, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR84, kStruct)[Int32(1)], LoadVarInst(Address(fIIR84, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM13, kStruct)[Int32(1)], LoadVarInst(Address(fIRM13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR89, kStruct)[Int32(2)], LoadVarInst(Address(fIIR89, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR89, kStruct)[Int32(1)], LoadVarInst(Address(fIIR89, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR88, kStruct)[Int32(2)], LoadVarInst(Address(fIIR88, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR88, kStruct)[Int32(1)], LoadVarInst(Address(fIIR88, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR87, kStruct)[Int32(2)], LoadVarInst(Address(fIIR87, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR87, kStruct)[Int32(1)], LoadVarInst(Address(fIIR87, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM14, kStruct)[Int32(1)], LoadVarInst(Address(fIRM14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR92, kStruct)[Int32(2)], LoadVarInst(Address(fIIR92, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR92, kStruct)[Int32(1)], LoadVarInst(Address(fIIR92, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR91, kStruct)[Int32(2)], LoadVarInst(Address(fIIR91, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR91, kStruct)[Int32(1)], LoadVarInst(Address(fIIR91, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR90, kStruct)[Int32(2)], LoadVarInst(Address(fIIR90, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR90, kStruct)[Int32(1)], LoadVarInst(Address(fIIR90, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIRM15, kStruct)[Int32(1)], LoadVarInst(Address(fIRM15, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", iVec0[4], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fIIR4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("float", fIRM1[2], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("float", fVec2[2], kStruct)
	DeclareVarInst("float", fVec3[2], kStruct)
	DeclareVarInst("float", fConst6, kStruct)
	DeclareVarInst("float", fConst7, kStruct)
	DeclareVarInst("float", fVec4[2], kStruct)
	DeclareVarInst("float", fVec5[2], kStruct)
	DeclareVarInst("float", fVec6[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fConst8, kStruct)
	DeclareVarInst("float", fVec7[2], kStruct)
	DeclareVarInst("float", fConst9, kStruct)
	DeclareVarInst("float", fVec8[2], kStruct)
	DeclareVarInst("float", fVec9[2], kStruct)
	DeclareVarInst("float", fConst10, kStruct)
	DeclareVarInst("float", fVec10[2], kStruct)
	DeclareVarInst("float", fVec11[2], kStruct)
	DeclareVarInst("float", fVec12[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("float", fConst11, kStruct)
	DeclareVarInst("float", fVec13[2], kStruct)
	DeclareVarInst("float", fConst12, kStruct)
	DeclareVarInst("float", fVec14[2], kStruct)
	DeclareVarInst("float", fVec15[2], kStruct)
	DeclareVarInst("float", fConst13, kStruct)
	DeclareVarInst("float", fVec16[2], kStruct)
	DeclareVarInst("float", fVec17[2], kStruct)
	DeclareVarInst("float", fVec18[2], kStruct)
	DeclareVarInst("float", fConst14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("float", fConst15, kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fVec19[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec20[4096], kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fVec21[2], kStruct)
	DeclareVarInst("float", fVec22[4096], kStruct)
	DeclareVarInst("float", fRec10[2], kStruct)
	DeclareVarInst("float", fVec23[2], kStruct)
	DeclareVarInst("float", fVec24[4096], kStruct)
	DeclareVarInst("float", fConst16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("float", fConst17, kStruct)
	DeclareVarInst("float", fIIR5[2], kStruct)
	DeclareVarInst("float", fConst18, kStruct)
	DeclareVarInst("float", fIIR6[2], kStruct)
	DeclareVarInst("float", fConst19, kStruct)
	DeclareVarInst("float", fIIR7[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("float", fConst20, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("float", fIIR8[2], kStruct)
	DeclareVarInst("float", fVec25[2], kStruct)
	DeclareVarInst("float", fVec26[2], kStruct)
	DeclareVarInst("float", fVec27[4096], kStruct)
	DeclareVarInst("float", fVec28[2], kStruct)
	DeclareVarInst("float", fVec29[2], kStruct)
	DeclareVarInst("float", fVec30[4096], kStruct)
	DeclareVarInst("float", fVec31[2], kStruct)
	DeclareVarInst("float", fVec32[2], kStruct)
	DeclareVarInst("float", fVec33[4096], kStruct)
	DeclareVarInst("float", fConst21, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("int", iIIR10[2], kStruct)
	DeclareVarInst("float", fIIR9[4], kStruct)
	DeclareVarInst("float", fVec34[4], kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox3, kStruct)
	DeclareVarInst("float", fConst22, kStruct)
	DeclareVarInst("float", fRec12[3], kStruct)
	DeclareVarInst("float", fRec11[3], kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("float", fIIR11[2], kStruct)
	DeclareVarInst("float", fConst23, kStruct)
	DeclareVarInst("float", fConst24, kStruct)
	DeclareVarInst("float", fConst25, kStruct)
	DeclareVarInst("float", fConst26, kStruct)
	DeclareVarInst("float", fConst27, kStruct)
	DeclareVarInst("float", fConst28, kStruct)
	DeclareVarInst("float", fConst29, kStruct)
	DeclareVarInst("float", fConst30, kStruct)
	DeclareVarInst("float", fIIR2[3], kStruct)
	DeclareVarInst("float", fConst31, kStruct)
	DeclareVarInst("float", fConst32, kStruct)
	DeclareVarInst("float", fConst33, kStruct)
	DeclareVarInst("float", fConst34, kStruct)
	DeclareVarInst("float", fConst35, kStruct)
	DeclareVarInst("float", fConst36, kStruct)
	DeclareVarInst("float", fConst37, kStruct)
	DeclareVarInst("float", fConst38, kStruct)
	DeclareVarInst("float", fIIR1[3], kStruct)
	DeclareVarInst("float", fConst39, kStruct)
	DeclareVarInst("float", fConst40, kStruct)
	DeclareVarInst("float", fConst41, kStruct)
	DeclareVarInst("float", fConst42, kStruct)
	DeclareVarInst("float", fConst43, kStruct)
	DeclareVarInst("float", fConst44, kStruct)
	DeclareVarInst("float", fConst45, kStruct)
	DeclareVarInst("float", fConst46, kStruct)
	DeclareVarInst("float", fIIR0[3], kStruct)
	DeclareVarInst("float", fConst47, kStruct)
	DeclareVarInst("float", fConst48, kStruct)
	DeclareVarInst("float", fConst49, kStruct)
	DeclareVarInst("float", fConst50, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("float", fIRM0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph0, kStruct)
	DeclareVarInst("float", fConst51, kStruct)
	DeclareVarInst("float", fConst52, kStruct)
	DeclareVarInst("float", fConst53, kStruct)
	DeclareVarInst("float", fConst54, kStruct)
	DeclareVarInst("float", fConst55, kStruct)
	DeclareVarInst("float", fIIR26[3], kStruct)
	DeclareVarInst("float", fConst56, kStruct)
	DeclareVarInst("float", fConst57, kStruct)
	DeclareVarInst("float", fConst58, kStruct)
	DeclareVarInst("float", fConst59, kStruct)
	DeclareVarInst("float", fConst60, kStruct)
	DeclareVarInst("float", fConst61, kStruct)
	DeclareVarInst("float", fConst62, kStruct)
	DeclareVarInst("float", fConst63, kStruct)
	DeclareVarInst("float", fIIR25[3], kStruct)
	DeclareVarInst("float", fConst64, kStruct)
	DeclareVarInst("float", fConst65, kStruct)
	DeclareVarInst("float", fConst66, kStruct)
	DeclareVarInst("float", fConst67, kStruct)
	DeclareVarInst("float", fConst68, kStruct)
	DeclareVarInst("float", fConst69, kStruct)
	DeclareVarInst("float", fConst70, kStruct)
	DeclareVarInst("float", fIIR24[3], kStruct)
	DeclareVarInst("float", fConst71, kStruct)
	DeclareVarInst("float", fConst72, kStruct)
	DeclareVarInst("float", fConst73, kStruct)
	DeclareVarInst("float", fConst74, kStruct)
	DeclareVarInst("float", fConst75, kStruct)
	DeclareVarInst("float", fConst76, kStruct)
	DeclareVarInst("float", fConst77, kStruct)
	DeclareVarInst("float", fConst78, kStruct)
	DeclareVarInst("float", fConst79, kStruct)
	DeclareVarInst("float", fConst80, kStruct)
	DeclareVarInst("float", fIIR23[3], kStruct)
	DeclareVarInst("float", fConst81, kStruct)
	DeclareVarInst("float", fConst82, kStruct)
	DeclareVarInst("float", fConst83, kStruct)
	DeclareVarInst("float", fConst84, kStruct)
	DeclareVarInst("float", fConst85, kStruct)
	DeclareVarInst("float", fConst86, kStruct)
	DeclareVarInst("float", fConst87, kStruct)
	DeclareVarInst("float", fConst88, kStruct)
	DeclareVarInst("float", fIIR22[3], kStruct)
	DeclareVarInst("float", fConst89, kStruct)
	DeclareVarInst("float", fConst90, kStruct)
	DeclareVarInst("float", fConst91, kStruct)
	DeclareVarInst("float", fConst92, kStruct)
	DeclareVarInst("float", fConst93, kStruct)
	DeclareVarInst("float", fConst94, kStruct)
	DeclareVarInst("float", fConst95, kStruct)
	DeclareVarInst("float", fIIR21[3], kStruct)
	DeclareVarInst("float", fConst96, kStruct)
	DeclareVarInst("float", fConst97, kStruct)
	DeclareVarInst("float", fConst98, kStruct)
	DeclareVarInst("float", fConst99, kStruct)
	DeclareVarInst("float", fConst100, kStruct)
	DeclareVarInst("float", fConst101, kStruct)
	DeclareVarInst("float", fConst102, kStruct)
	DeclareVarInst("float", fConst103, kStruct)
	DeclareVarInst("float", fConst104, kStruct)
	DeclareVarInst("float", fConst105, kStruct)
	DeclareVarInst("float", fIIR20[3], kStruct)
	DeclareVarInst("float", fConst106, kStruct)
	DeclareVarInst("float", fConst107, kStruct)
	DeclareVarInst("float", fConst108, kStruct)
	DeclareVarInst("float", fConst109, kStruct)
	DeclareVarInst("float", fConst110, kStruct)
	DeclareVarInst("float", fConst111, kStruct)
	DeclareVarInst("float", fConst112, kStruct)
	DeclareVarInst("float", fConst113, kStruct)
	DeclareVarInst("float", fIIR19[3], kStruct)
	DeclareVarInst("float", fConst114, kStruct)
	DeclareVarInst("float", fConst115, kStruct)
	DeclareVarInst("float", fConst116, kStruct)
	DeclareVarInst("float", fConst117, kStruct)
	DeclareVarInst("float", fConst118, kStruct)
	DeclareVarInst("float", fConst119, kStruct)
	DeclareVarInst("float", fConst120, kStruct)
	DeclareVarInst("float", fIIR18[3], kStruct)
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
	DeclareVarInst("float", fIIR17[3], kStruct)
	DeclareVarInst("float", fConst131, kStruct)
	DeclareVarInst("float", fConst132, kStruct)
	DeclareVarInst("float", fConst133, kStruct)
	DeclareVarInst("float", fConst134, kStruct)
	DeclareVarInst("float", fConst135, kStruct)
	DeclareVarInst("float", fConst136, kStruct)
	DeclareVarInst("float", fConst137, kStruct)
	DeclareVarInst("float", fConst138, kStruct)
	DeclareVarInst("float", fIIR16[3], kStruct)
	DeclareVarInst("float", fConst139, kStruct)
	DeclareVarInst("float", fConst140, kStruct)
	DeclareVarInst("float", fConst141, kStruct)
	DeclareVarInst("float", fConst142, kStruct)
	DeclareVarInst("float", fConst143, kStruct)
	DeclareVarInst("float", fConst144, kStruct)
	DeclareVarInst("float", fConst145, kStruct)
	DeclareVarInst("float", fIIR15[3], kStruct)
	DeclareVarInst("float", fConst146, kStruct)
	DeclareVarInst("float", fConst147, kStruct)
	DeclareVarInst("float", fConst148, kStruct)
	DeclareVarInst("float", fConst149, kStruct)
	DeclareVarInst("float", fConst150, kStruct)
	DeclareVarInst("float", fConst151, kStruct)
	DeclareVarInst("float", fConst152, kStruct)
	DeclareVarInst("float", fConst153, kStruct)
	DeclareVarInst("float", fConst154, kStruct)
	DeclareVarInst("float", fConst155, kStruct)
	DeclareVarInst("float", fIIR14[3], kStruct)
	DeclareVarInst("float", fConst156, kStruct)
	DeclareVarInst("float", fConst157, kStruct)
	DeclareVarInst("float", fConst158, kStruct)
	DeclareVarInst("float", fConst159, kStruct)
	DeclareVarInst("float", fConst160, kStruct)
	DeclareVarInst("float", fConst161, kStruct)
	DeclareVarInst("float", fConst162, kStruct)
	DeclareVarInst("float", fConst163, kStruct)
	DeclareVarInst("float", fIIR13[3], kStruct)
	DeclareVarInst("float", fConst164, kStruct)
	DeclareVarInst("float", fConst165, kStruct)
	DeclareVarInst("float", fConst166, kStruct)
	DeclareVarInst("float", fConst167, kStruct)
	DeclareVarInst("float", fConst168, kStruct)
	DeclareVarInst("float", fConst169, kStruct)
	DeclareVarInst("float", fConst170, kStruct)
	DeclareVarInst("float", fConst171, kStruct)
	DeclareVarInst("float", fIIR12[3], kStruct)
	DeclareVarInst("float", fConst172, kStruct)
	DeclareVarInst("float", fConst173, kStruct)
	DeclareVarInst("float", fConst174, kStruct)
	DeclareVarInst("float", fIRM2[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph1, kStruct)
	DeclareVarInst("float", fConst175, kStruct)
	DeclareVarInst("float", fConst176, kStruct)
	DeclareVarInst("float", fConst177, kStruct)
	DeclareVarInst("float", fConst178, kStruct)
	DeclareVarInst("float", fConst179, kStruct)
	DeclareVarInst("float", fIIR41[3], kStruct)
	DeclareVarInst("float", fConst180, kStruct)
	DeclareVarInst("float", fConst181, kStruct)
	DeclareVarInst("float", fConst182, kStruct)
	DeclareVarInst("float", fConst183, kStruct)
	DeclareVarInst("float", fConst184, kStruct)
	DeclareVarInst("float", fConst185, kStruct)
	DeclareVarInst("float", fConst186, kStruct)
	DeclareVarInst("float", fConst187, kStruct)
	DeclareVarInst("float", fIIR40[3], kStruct)
	DeclareVarInst("float", fConst188, kStruct)
	DeclareVarInst("float", fConst189, kStruct)
	DeclareVarInst("float", fConst190, kStruct)
	DeclareVarInst("float", fConst191, kStruct)
	DeclareVarInst("float", fConst192, kStruct)
	DeclareVarInst("float", fConst193, kStruct)
	DeclareVarInst("float", fConst194, kStruct)
	DeclareVarInst("float", fIIR39[3], kStruct)
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
	DeclareVarInst("float", fIIR38[3], kStruct)
	DeclareVarInst("float", fConst205, kStruct)
	DeclareVarInst("float", fConst206, kStruct)
	DeclareVarInst("float", fConst207, kStruct)
	DeclareVarInst("float", fConst208, kStruct)
	DeclareVarInst("float", fConst209, kStruct)
	DeclareVarInst("float", fConst210, kStruct)
	DeclareVarInst("float", fConst211, kStruct)
	DeclareVarInst("float", fConst212, kStruct)
	DeclareVarInst("float", fIIR37[3], kStruct)
	DeclareVarInst("float", fConst213, kStruct)
	DeclareVarInst("float", fConst214, kStruct)
	DeclareVarInst("float", fConst215, kStruct)
	DeclareVarInst("float", fConst216, kStruct)
	DeclareVarInst("float", fConst217, kStruct)
	DeclareVarInst("float", fConst218, kStruct)
	DeclareVarInst("float", fConst219, kStruct)
	DeclareVarInst("float", fIIR36[3], kStruct)
	DeclareVarInst("float", fConst220, kStruct)
	DeclareVarInst("float", fConst221, kStruct)
	DeclareVarInst("float", fConst222, kStruct)
	DeclareVarInst("float", fConst223, kStruct)
	DeclareVarInst("float", fConst224, kStruct)
	DeclareVarInst("float", fConst225, kStruct)
	DeclareVarInst("float", fConst226, kStruct)
	DeclareVarInst("float", fConst227, kStruct)
	DeclareVarInst("float", fConst228, kStruct)
	DeclareVarInst("float", fConst229, kStruct)
	DeclareVarInst("float", fIIR35[3], kStruct)
	DeclareVarInst("float", fConst230, kStruct)
	DeclareVarInst("float", fConst231, kStruct)
	DeclareVarInst("float", fConst232, kStruct)
	DeclareVarInst("float", fConst233, kStruct)
	DeclareVarInst("float", fConst234, kStruct)
	DeclareVarInst("float", fConst235, kStruct)
	DeclareVarInst("float", fConst236, kStruct)
	DeclareVarInst("float", fConst237, kStruct)
	DeclareVarInst("float", fIIR34[3], kStruct)
	DeclareVarInst("float", fConst238, kStruct)
	DeclareVarInst("float", fConst239, kStruct)
	DeclareVarInst("float", fConst240, kStruct)
	DeclareVarInst("float", fConst241, kStruct)
	DeclareVarInst("float", fConst242, kStruct)
	DeclareVarInst("float", fConst243, kStruct)
	DeclareVarInst("float", fConst244, kStruct)
	DeclareVarInst("float", fIIR33[3], kStruct)
	DeclareVarInst("float", fConst245, kStruct)
	DeclareVarInst("float", fConst246, kStruct)
	DeclareVarInst("float", fConst247, kStruct)
	DeclareVarInst("float", fConst248, kStruct)
	DeclareVarInst("float", fConst249, kStruct)
	DeclareVarInst("float", fConst250, kStruct)
	DeclareVarInst("float", fConst251, kStruct)
	DeclareVarInst("float", fConst252, kStruct)
	DeclareVarInst("float", fConst253, kStruct)
	DeclareVarInst("float", fConst254, kStruct)
	DeclareVarInst("float", fIIR32[3], kStruct)
	DeclareVarInst("float", fConst255, kStruct)
	DeclareVarInst("float", fConst256, kStruct)
	DeclareVarInst("float", fConst257, kStruct)
	DeclareVarInst("float", fConst258, kStruct)
	DeclareVarInst("float", fConst259, kStruct)
	DeclareVarInst("float", fConst260, kStruct)
	DeclareVarInst("float", fConst261, kStruct)
	DeclareVarInst("float", fConst262, kStruct)
	DeclareVarInst("float", fIIR31[3], kStruct)
	DeclareVarInst("float", fConst263, kStruct)
	DeclareVarInst("float", fConst264, kStruct)
	DeclareVarInst("float", fConst265, kStruct)
	DeclareVarInst("float", fConst266, kStruct)
	DeclareVarInst("float", fConst267, kStruct)
	DeclareVarInst("float", fConst268, kStruct)
	DeclareVarInst("float", fConst269, kStruct)
	DeclareVarInst("float", fIIR30[3], kStruct)
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
	DeclareVarInst("float", fIIR29[3], kStruct)
	DeclareVarInst("float", fConst280, kStruct)
	DeclareVarInst("float", fConst281, kStruct)
	DeclareVarInst("float", fConst282, kStruct)
	DeclareVarInst("float", fConst283, kStruct)
	DeclareVarInst("float", fConst284, kStruct)
	DeclareVarInst("float", fConst285, kStruct)
	DeclareVarInst("float", fConst286, kStruct)
	DeclareVarInst("float", fConst287, kStruct)
	DeclareVarInst("float", fIIR28[3], kStruct)
	DeclareVarInst("float", fConst288, kStruct)
	DeclareVarInst("float", fConst289, kStruct)
	DeclareVarInst("float", fConst290, kStruct)
	DeclareVarInst("float", fConst291, kStruct)
	DeclareVarInst("float", fConst292, kStruct)
	DeclareVarInst("float", fConst293, kStruct)
	DeclareVarInst("float", fConst294, kStruct)
	DeclareVarInst("float", fConst295, kStruct)
	DeclareVarInst("float", fIIR27[3], kStruct)
	DeclareVarInst("float", fConst296, kStruct)
	DeclareVarInst("float", fConst297, kStruct)
	DeclareVarInst("float", fConst298, kStruct)
	DeclareVarInst("float", fIRM3[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph2, kStruct)
	DeclareVarInst("float", fConst299, kStruct)
	DeclareVarInst("float", fConst300, kStruct)
	DeclareVarInst("float", fConst301, kStruct)
	DeclareVarInst("float", fConst302, kStruct)
	DeclareVarInst("float", fConst303, kStruct)
	DeclareVarInst("float", fIIR56[3], kStruct)
	DeclareVarInst("float", fConst304, kStruct)
	DeclareVarInst("float", fConst305, kStruct)
	DeclareVarInst("float", fConst306, kStruct)
	DeclareVarInst("float", fConst307, kStruct)
	DeclareVarInst("float", fConst308, kStruct)
	DeclareVarInst("float", fConst309, kStruct)
	DeclareVarInst("float", fConst310, kStruct)
	DeclareVarInst("float", fConst311, kStruct)
	DeclareVarInst("float", fIIR55[3], kStruct)
	DeclareVarInst("float", fConst312, kStruct)
	DeclareVarInst("float", fConst313, kStruct)
	DeclareVarInst("float", fConst314, kStruct)
	DeclareVarInst("float", fConst315, kStruct)
	DeclareVarInst("float", fConst316, kStruct)
	DeclareVarInst("float", fConst317, kStruct)
	DeclareVarInst("float", fConst318, kStruct)
	DeclareVarInst("float", fIIR54[3], kStruct)
	DeclareVarInst("float", fConst319, kStruct)
	DeclareVarInst("float", fConst320, kStruct)
	DeclareVarInst("float", fConst321, kStruct)
	DeclareVarInst("float", fConst322, kStruct)
	DeclareVarInst("float", fConst323, kStruct)
	DeclareVarInst("float", fConst324, kStruct)
	DeclareVarInst("float", fConst325, kStruct)
	DeclareVarInst("float", fConst326, kStruct)
	DeclareVarInst("float", fConst327, kStruct)
	DeclareVarInst("float", fConst328, kStruct)
	DeclareVarInst("float", fIIR53[3], kStruct)
	DeclareVarInst("float", fConst329, kStruct)
	DeclareVarInst("float", fConst330, kStruct)
	DeclareVarInst("float", fConst331, kStruct)
	DeclareVarInst("float", fConst332, kStruct)
	DeclareVarInst("float", fConst333, kStruct)
	DeclareVarInst("float", fConst334, kStruct)
	DeclareVarInst("float", fConst335, kStruct)
	DeclareVarInst("float", fConst336, kStruct)
	DeclareVarInst("float", fIIR52[3], kStruct)
	DeclareVarInst("float", fConst337, kStruct)
	DeclareVarInst("float", fConst338, kStruct)
	DeclareVarInst("float", fConst339, kStruct)
	DeclareVarInst("float", fConst340, kStruct)
	DeclareVarInst("float", fConst341, kStruct)
	DeclareVarInst("float", fConst342, kStruct)
	DeclareVarInst("float", fConst343, kStruct)
	DeclareVarInst("float", fIIR51[3], kStruct)
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
	DeclareVarInst("float", fIIR50[3], kStruct)
	DeclareVarInst("float", fConst354, kStruct)
	DeclareVarInst("float", fConst355, kStruct)
	DeclareVarInst("float", fConst356, kStruct)
	DeclareVarInst("float", fConst357, kStruct)
	DeclareVarInst("float", fConst358, kStruct)
	DeclareVarInst("float", fConst359, kStruct)
	DeclareVarInst("float", fConst360, kStruct)
	DeclareVarInst("float", fConst361, kStruct)
	DeclareVarInst("float", fIIR49[3], kStruct)
	DeclareVarInst("float", fConst362, kStruct)
	DeclareVarInst("float", fConst363, kStruct)
	DeclareVarInst("float", fConst364, kStruct)
	DeclareVarInst("float", fConst365, kStruct)
	DeclareVarInst("float", fConst366, kStruct)
	DeclareVarInst("float", fConst367, kStruct)
	DeclareVarInst("float", fConst368, kStruct)
	DeclareVarInst("float", fIIR48[3], kStruct)
	DeclareVarInst("float", fConst369, kStruct)
	DeclareVarInst("float", fConst370, kStruct)
	DeclareVarInst("float", fConst371, kStruct)
	DeclareVarInst("float", fConst372, kStruct)
	DeclareVarInst("float", fConst373, kStruct)
	DeclareVarInst("float", fConst374, kStruct)
	DeclareVarInst("float", fConst375, kStruct)
	DeclareVarInst("float", fConst376, kStruct)
	DeclareVarInst("float", fConst377, kStruct)
	DeclareVarInst("float", fConst378, kStruct)
	DeclareVarInst("float", fIIR47[3], kStruct)
	DeclareVarInst("float", fConst379, kStruct)
	DeclareVarInst("float", fConst380, kStruct)
	DeclareVarInst("float", fConst381, kStruct)
	DeclareVarInst("float", fConst382, kStruct)
	DeclareVarInst("float", fConst383, kStruct)
	DeclareVarInst("float", fConst384, kStruct)
	DeclareVarInst("float", fConst385, kStruct)
	DeclareVarInst("float", fConst386, kStruct)
	DeclareVarInst("float", fIIR46[3], kStruct)
	DeclareVarInst("float", fConst387, kStruct)
	DeclareVarInst("float", fConst388, kStruct)
	DeclareVarInst("float", fConst389, kStruct)
	DeclareVarInst("float", fConst390, kStruct)
	DeclareVarInst("float", fConst391, kStruct)
	DeclareVarInst("float", fConst392, kStruct)
	DeclareVarInst("float", fConst393, kStruct)
	DeclareVarInst("float", fIIR45[3], kStruct)
	DeclareVarInst("float", fConst394, kStruct)
	DeclareVarInst("float", fConst395, kStruct)
	DeclareVarInst("float", fConst396, kStruct)
	DeclareVarInst("float", fConst397, kStruct)
	DeclareVarInst("float", fConst398, kStruct)
	DeclareVarInst("float", fConst399, kStruct)
	DeclareVarInst("float", fConst400, kStruct)
	DeclareVarInst("float", fConst401, kStruct)
	DeclareVarInst("float", fConst402, kStruct)
	DeclareVarInst("float", fConst403, kStruct)
	DeclareVarInst("float", fIIR44[3], kStruct)
	DeclareVarInst("float", fConst404, kStruct)
	DeclareVarInst("float", fConst405, kStruct)
	DeclareVarInst("float", fConst406, kStruct)
	DeclareVarInst("float", fConst407, kStruct)
	DeclareVarInst("float", fConst408, kStruct)
	DeclareVarInst("float", fConst409, kStruct)
	DeclareVarInst("float", fConst410, kStruct)
	DeclareVarInst("float", fConst411, kStruct)
	DeclareVarInst("float", fIIR43[3], kStruct)
	DeclareVarInst("float", fConst412, kStruct)
	DeclareVarInst("float", fConst413, kStruct)
	DeclareVarInst("float", fConst414, kStruct)
	DeclareVarInst("float", fConst415, kStruct)
	DeclareVarInst("float", fConst416, kStruct)
	DeclareVarInst("float", fConst417, kStruct)
	DeclareVarInst("float", fConst418, kStruct)
	DeclareVarInst("float", fConst419, kStruct)
	DeclareVarInst("float", fIIR42[3], kStruct)
	DeclareVarInst("float", fConst420, kStruct)
	DeclareVarInst("float", fConst421, kStruct)
	DeclareVarInst("float", fConst422, kStruct)
	DeclareVarInst("float", fIRM4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph3, kStruct)
	DeclareVarInst("float", fConst423, kStruct)
	DeclareVarInst("float", fConst424, kStruct)
	DeclareVarInst("float", fConst425, kStruct)
	DeclareVarInst("float", fConst426, kStruct)
	DeclareVarInst("float", fConst427, kStruct)
	DeclareVarInst("float", fIIR59[3], kStruct)
	DeclareVarInst("float", fConst428, kStruct)
	DeclareVarInst("float", fConst429, kStruct)
	DeclareVarInst("float", fConst430, kStruct)
	DeclareVarInst("float", fConst431, kStruct)
	DeclareVarInst("float", fConst432, kStruct)
	DeclareVarInst("float", fConst433, kStruct)
	DeclareVarInst("float", fConst434, kStruct)
	DeclareVarInst("float", fConst435, kStruct)
	DeclareVarInst("float", fIIR58[3], kStruct)
	DeclareVarInst("float", fConst436, kStruct)
	DeclareVarInst("float", fConst437, kStruct)
	DeclareVarInst("float", fConst438, kStruct)
	DeclareVarInst("float", fConst439, kStruct)
	DeclareVarInst("float", fConst440, kStruct)
	DeclareVarInst("float", fConst441, kStruct)
	DeclareVarInst("float", fConst442, kStruct)
	DeclareVarInst("float", fConst443, kStruct)
	DeclareVarInst("float", fIIR57[3], kStruct)
	DeclareVarInst("float", fConst444, kStruct)
	DeclareVarInst("float", fConst445, kStruct)
	DeclareVarInst("float", fConst446, kStruct)
	DeclareVarInst("float", fIRM5[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph4, kStruct)
	DeclareVarInst("float", fConst447, kStruct)
	DeclareVarInst("float", fConst448, kStruct)
	DeclareVarInst("float", fConst449, kStruct)
	DeclareVarInst("float", fConst450, kStruct)
	DeclareVarInst("float", fConst451, kStruct)
	DeclareVarInst("float", fIIR62[3], kStruct)
	DeclareVarInst("float", fConst452, kStruct)
	DeclareVarInst("float", fConst453, kStruct)
	DeclareVarInst("float", fConst454, kStruct)
	DeclareVarInst("float", fConst455, kStruct)
	DeclareVarInst("float", fConst456, kStruct)
	DeclareVarInst("float", fConst457, kStruct)
	DeclareVarInst("float", fConst458, kStruct)
	DeclareVarInst("float", fConst459, kStruct)
	DeclareVarInst("float", fIIR61[3], kStruct)
	DeclareVarInst("float", fConst460, kStruct)
	DeclareVarInst("float", fConst461, kStruct)
	DeclareVarInst("float", fConst462, kStruct)
	DeclareVarInst("float", fConst463, kStruct)
	DeclareVarInst("float", fConst464, kStruct)
	DeclareVarInst("float", fConst465, kStruct)
	DeclareVarInst("float", fConst466, kStruct)
	DeclareVarInst("float", fConst467, kStruct)
	DeclareVarInst("float", fIIR60[3], kStruct)
	DeclareVarInst("float", fConst468, kStruct)
	DeclareVarInst("float", fConst469, kStruct)
	DeclareVarInst("float", fConst470, kStruct)
	DeclareVarInst("float", fIRM6[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph5, kStruct)
	DeclareVarInst("float", fConst471, kStruct)
	DeclareVarInst("float", fConst472, kStruct)
	DeclareVarInst("float", fConst473, kStruct)
	DeclareVarInst("float", fConst474, kStruct)
	DeclareVarInst("float", fConst475, kStruct)
	DeclareVarInst("float", fIIR65[3], kStruct)
	DeclareVarInst("float", fConst476, kStruct)
	DeclareVarInst("float", fConst477, kStruct)
	DeclareVarInst("float", fConst478, kStruct)
	DeclareVarInst("float", fConst479, kStruct)
	DeclareVarInst("float", fConst480, kStruct)
	DeclareVarInst("float", fConst481, kStruct)
	DeclareVarInst("float", fConst482, kStruct)
	DeclareVarInst("float", fConst483, kStruct)
	DeclareVarInst("float", fIIR64[3], kStruct)
	DeclareVarInst("float", fConst484, kStruct)
	DeclareVarInst("float", fConst485, kStruct)
	DeclareVarInst("float", fConst486, kStruct)
	DeclareVarInst("float", fConst487, kStruct)
	DeclareVarInst("float", fConst488, kStruct)
	DeclareVarInst("float", fConst489, kStruct)
	DeclareVarInst("float", fConst490, kStruct)
	DeclareVarInst("float", fConst491, kStruct)
	DeclareVarInst("float", fIIR63[3], kStruct)
	DeclareVarInst("float", fConst492, kStruct)
	DeclareVarInst("float", fConst493, kStruct)
	DeclareVarInst("float", fConst494, kStruct)
	DeclareVarInst("float", fIRM7[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph6, kStruct)
	DeclareVarInst("float", fConst495, kStruct)
	DeclareVarInst("float", fConst496, kStruct)
	DeclareVarInst("float", fConst497, kStruct)
	DeclareVarInst("float", fConst498, kStruct)
	DeclareVarInst("float", fConst499, kStruct)
	DeclareVarInst("float", fIIR71[3], kStruct)
	DeclareVarInst("float", fConst500, kStruct)
	DeclareVarInst("float", fConst501, kStruct)
	DeclareVarInst("float", fConst502, kStruct)
	DeclareVarInst("float", fConst503, kStruct)
	DeclareVarInst("float", fConst504, kStruct)
	DeclareVarInst("float", fConst505, kStruct)
	DeclareVarInst("float", fConst506, kStruct)
	DeclareVarInst("float", fConst507, kStruct)
	DeclareVarInst("float", fIIR70[3], kStruct)
	DeclareVarInst("float", fConst508, kStruct)
	DeclareVarInst("float", fConst509, kStruct)
	DeclareVarInst("float", fConst510, kStruct)
	DeclareVarInst("float", fConst511, kStruct)
	DeclareVarInst("float", fConst512, kStruct)
	DeclareVarInst("float", fConst513, kStruct)
	DeclareVarInst("float", fConst514, kStruct)
	DeclareVarInst("float", fIIR69[3], kStruct)
	DeclareVarInst("float", fConst515, kStruct)
	DeclareVarInst("float", fConst516, kStruct)
	DeclareVarInst("float", fConst517, kStruct)
	DeclareVarInst("float", fConst518, kStruct)
	DeclareVarInst("float", fConst519, kStruct)
	DeclareVarInst("float", fConst520, kStruct)
	DeclareVarInst("float", fConst521, kStruct)
	DeclareVarInst("float", fConst522, kStruct)
	DeclareVarInst("float", fConst523, kStruct)
	DeclareVarInst("float", fConst524, kStruct)
	DeclareVarInst("float", fIIR68[3], kStruct)
	DeclareVarInst("float", fConst525, kStruct)
	DeclareVarInst("float", fConst526, kStruct)
	DeclareVarInst("float", fConst527, kStruct)
	DeclareVarInst("float", fConst528, kStruct)
	DeclareVarInst("float", fConst529, kStruct)
	DeclareVarInst("float", fConst530, kStruct)
	DeclareVarInst("float", fConst531, kStruct)
	DeclareVarInst("float", fConst532, kStruct)
	DeclareVarInst("float", fIIR67[3], kStruct)
	DeclareVarInst("float", fConst533, kStruct)
	DeclareVarInst("float", fConst534, kStruct)
	DeclareVarInst("float", fConst535, kStruct)
	DeclareVarInst("float", fConst536, kStruct)
	DeclareVarInst("float", fConst537, kStruct)
	DeclareVarInst("float", fConst538, kStruct)
	DeclareVarInst("float", fConst539, kStruct)
	DeclareVarInst("float", fConst540, kStruct)
	DeclareVarInst("float", fIIR66[3], kStruct)
	DeclareVarInst("float", fConst541, kStruct)
	DeclareVarInst("float", fConst542, kStruct)
	DeclareVarInst("float", fConst543, kStruct)
	DeclareVarInst("float", fIRM8[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph7, kStruct)
	DeclareVarInst("float", fConst544, kStruct)
	DeclareVarInst("float", fConst545, kStruct)
	DeclareVarInst("float", fConst546, kStruct)
	DeclareVarInst("float", fConst547, kStruct)
	DeclareVarInst("float", fConst548, kStruct)
	DeclareVarInst("float", fIIR74[3], kStruct)
	DeclareVarInst("float", fConst549, kStruct)
	DeclareVarInst("float", fConst550, kStruct)
	DeclareVarInst("float", fConst551, kStruct)
	DeclareVarInst("float", fConst552, kStruct)
	DeclareVarInst("float", fConst553, kStruct)
	DeclareVarInst("float", fConst554, kStruct)
	DeclareVarInst("float", fConst555, kStruct)
	DeclareVarInst("float", fConst556, kStruct)
	DeclareVarInst("float", fIIR73[3], kStruct)
	DeclareVarInst("float", fConst557, kStruct)
	DeclareVarInst("float", fConst558, kStruct)
	DeclareVarInst("float", fConst559, kStruct)
	DeclareVarInst("float", fConst560, kStruct)
	DeclareVarInst("float", fConst561, kStruct)
	DeclareVarInst("float", fConst562, kStruct)
	DeclareVarInst("float", fConst563, kStruct)
	DeclareVarInst("float", fConst564, kStruct)
	DeclareVarInst("float", fIIR72[3], kStruct)
	DeclareVarInst("float", fConst565, kStruct)
	DeclareVarInst("float", fConst566, kStruct)
	DeclareVarInst("float", fConst567, kStruct)
	DeclareVarInst("float", fIRM9[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph8, kStruct)
	DeclareVarInst("float", fConst568, kStruct)
	DeclareVarInst("float", fConst569, kStruct)
	DeclareVarInst("float", fConst570, kStruct)
	DeclareVarInst("float", fConst571, kStruct)
	DeclareVarInst("float", fConst572, kStruct)
	DeclareVarInst("float", fIIR77[3], kStruct)
	DeclareVarInst("float", fConst573, kStruct)
	DeclareVarInst("float", fConst574, kStruct)
	DeclareVarInst("float", fConst575, kStruct)
	DeclareVarInst("float", fConst576, kStruct)
	DeclareVarInst("float", fConst577, kStruct)
	DeclareVarInst("float", fConst578, kStruct)
	DeclareVarInst("float", fConst579, kStruct)
	DeclareVarInst("float", fConst580, kStruct)
	DeclareVarInst("float", fIIR76[3], kStruct)
	DeclareVarInst("float", fConst581, kStruct)
	DeclareVarInst("float", fConst582, kStruct)
	DeclareVarInst("float", fConst583, kStruct)
	DeclareVarInst("float", fConst584, kStruct)
	DeclareVarInst("float", fConst585, kStruct)
	DeclareVarInst("float", fConst586, kStruct)
	DeclareVarInst("float", fConst587, kStruct)
	DeclareVarInst("float", fConst588, kStruct)
	DeclareVarInst("float", fIIR75[3], kStruct)
	DeclareVarInst("float", fConst589, kStruct)
	DeclareVarInst("float", fConst590, kStruct)
	DeclareVarInst("float", fConst591, kStruct)
	DeclareVarInst("float", fIRM10[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph9, kStruct)
	DeclareVarInst("float", fConst592, kStruct)
	DeclareVarInst("float", fConst593, kStruct)
	DeclareVarInst("float", fConst594, kStruct)
	DeclareVarInst("float", fConst595, kStruct)
	DeclareVarInst("float", fConst596, kStruct)
	DeclareVarInst("float", fIIR80[3], kStruct)
	DeclareVarInst("float", fConst597, kStruct)
	DeclareVarInst("float", fConst598, kStruct)
	DeclareVarInst("float", fConst599, kStruct)
	DeclareVarInst("float", fConst600, kStruct)
	DeclareVarInst("float", fConst601, kStruct)
	DeclareVarInst("float", fConst602, kStruct)
	DeclareVarInst("float", fConst603, kStruct)
	DeclareVarInst("float", fConst604, kStruct)
	DeclareVarInst("float", fIIR79[3], kStruct)
	DeclareVarInst("float", fConst605, kStruct)
	DeclareVarInst("float", fConst606, kStruct)
	DeclareVarInst("float", fConst607, kStruct)
	DeclareVarInst("float", fConst608, kStruct)
	DeclareVarInst("float", fConst609, kStruct)
	DeclareVarInst("float", fConst610, kStruct)
	DeclareVarInst("float", fConst611, kStruct)
	DeclareVarInst("float", fConst612, kStruct)
	DeclareVarInst("float", fIIR78[3], kStruct)
	DeclareVarInst("float", fConst613, kStruct)
	DeclareVarInst("float", fConst614, kStruct)
	DeclareVarInst("float", fConst615, kStruct)
	DeclareVarInst("float", fIRM11[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph10, kStruct)
	DeclareVarInst("float", fConst616, kStruct)
	DeclareVarInst("float", fConst617, kStruct)
	DeclareVarInst("float", fConst618, kStruct)
	DeclareVarInst("float", fConst619, kStruct)
	DeclareVarInst("float", fConst620, kStruct)
	DeclareVarInst("float", fIIR83[3], kStruct)
	DeclareVarInst("float", fConst621, kStruct)
	DeclareVarInst("float", fConst622, kStruct)
	DeclareVarInst("float", fConst623, kStruct)
	DeclareVarInst("float", fConst624, kStruct)
	DeclareVarInst("float", fConst625, kStruct)
	DeclareVarInst("float", fConst626, kStruct)
	DeclareVarInst("float", fConst627, kStruct)
	DeclareVarInst("float", fConst628, kStruct)
	DeclareVarInst("float", fIIR82[3], kStruct)
	DeclareVarInst("float", fConst629, kStruct)
	DeclareVarInst("float", fConst630, kStruct)
	DeclareVarInst("float", fConst631, kStruct)
	DeclareVarInst("float", fConst632, kStruct)
	DeclareVarInst("float", fConst633, kStruct)
	DeclareVarInst("float", fConst634, kStruct)
	DeclareVarInst("float", fConst635, kStruct)
	DeclareVarInst("float", fIIR81[3], kStruct)
	DeclareVarInst("float", fConst636, kStruct)
	DeclareVarInst("float", fConst637, kStruct)
	DeclareVarInst("float", fIRM12[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph11, kStruct)
	DeclareVarInst("float", fConst638, kStruct)
	DeclareVarInst("float", fConst639, kStruct)
	DeclareVarInst("float", fConst640, kStruct)
	DeclareVarInst("float", fConst641, kStruct)
	DeclareVarInst("float", fConst642, kStruct)
	DeclareVarInst("float", fIIR86[3], kStruct)
	DeclareVarInst("float", fConst643, kStruct)
	DeclareVarInst("float", fConst644, kStruct)
	DeclareVarInst("float", fConst645, kStruct)
	DeclareVarInst("float", fConst646, kStruct)
	DeclareVarInst("float", fConst647, kStruct)
	DeclareVarInst("float", fConst648, kStruct)
	DeclareVarInst("float", fConst649, kStruct)
	DeclareVarInst("float", fConst650, kStruct)
	DeclareVarInst("float", fIIR85[3], kStruct)
	DeclareVarInst("float", fConst651, kStruct)
	DeclareVarInst("float", fConst652, kStruct)
	DeclareVarInst("float", fConst653, kStruct)
	DeclareVarInst("float", fConst654, kStruct)
	DeclareVarInst("float", fConst655, kStruct)
	DeclareVarInst("float", fConst656, kStruct)
	DeclareVarInst("float", fConst657, kStruct)
	DeclareVarInst("float", fConst658, kStruct)
	DeclareVarInst("float", fIIR84[3], kStruct)
	DeclareVarInst("float", fConst659, kStruct)
	DeclareVarInst("float", fConst660, kStruct)
	DeclareVarInst("float", fConst661, kStruct)
	DeclareVarInst("float", fIRM13[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph12, kStruct)
	DeclareVarInst("float", fConst662, kStruct)
	DeclareVarInst("float", fConst663, kStruct)
	DeclareVarInst("float", fConst664, kStruct)
	DeclareVarInst("float", fConst665, kStruct)
	DeclareVarInst("float", fConst666, kStruct)
	DeclareVarInst("float", fIIR89[3], kStruct)
	DeclareVarInst("float", fConst667, kStruct)
	DeclareVarInst("float", fConst668, kStruct)
	DeclareVarInst("float", fConst669, kStruct)
	DeclareVarInst("float", fConst670, kStruct)
	DeclareVarInst("float", fConst671, kStruct)
	DeclareVarInst("float", fConst672, kStruct)
	DeclareVarInst("float", fConst673, kStruct)
	DeclareVarInst("float", fConst674, kStruct)
	DeclareVarInst("float", fIIR88[3], kStruct)
	DeclareVarInst("float", fConst675, kStruct)
	DeclareVarInst("float", fConst676, kStruct)
	DeclareVarInst("float", fConst677, kStruct)
	DeclareVarInst("float", fConst678, kStruct)
	DeclareVarInst("float", fConst679, kStruct)
	DeclareVarInst("float", fConst680, kStruct)
	DeclareVarInst("float", fConst681, kStruct)
	DeclareVarInst("float", fConst682, kStruct)
	DeclareVarInst("float", fIIR87[3], kStruct)
	DeclareVarInst("float", fConst683, kStruct)
	DeclareVarInst("float", fConst684, kStruct)
	DeclareVarInst("float", fConst685, kStruct)
	DeclareVarInst("float", fIRM14[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph13, kStruct)
	DeclareVarInst("float", fConst686, kStruct)
	DeclareVarInst("float", fConst687, kStruct)
	DeclareVarInst("float", fConst688, kStruct)
	DeclareVarInst("float", fConst689, kStruct)
	DeclareVarInst("float", fConst690, kStruct)
	DeclareVarInst("float", fIIR92[3], kStruct)
	DeclareVarInst("float", fConst691, kStruct)
	DeclareVarInst("float", fConst692, kStruct)
	DeclareVarInst("float", fConst693, kStruct)
	DeclareVarInst("float", fConst694, kStruct)
	DeclareVarInst("float", fConst695, kStruct)
	DeclareVarInst("float", fConst696, kStruct)
	DeclareVarInst("float", fConst697, kStruct)
	DeclareVarInst("float", fConst698, kStruct)
	DeclareVarInst("float", fIIR91[3], kStruct)
	DeclareVarInst("float", fConst699, kStruct)
	DeclareVarInst("float", fConst700, kStruct)
	DeclareVarInst("float", fConst701, kStruct)
	DeclareVarInst("float", fConst702, kStruct)
	DeclareVarInst("float", fConst703, kStruct)
	DeclareVarInst("float", fConst704, kStruct)
	DeclareVarInst("float", fConst705, kStruct)
	DeclareVarInst("float", fConst706, kStruct)
	DeclareVarInst("float", fIIR90[3], kStruct)
	DeclareVarInst("float", fConst707, kStruct)
	DeclareVarInst("float", fConst708, kStruct)
	DeclareVarInst("float", fConst709, kStruct)
	DeclareVarInst("float", fIRM15[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVbargraph14, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.041666668f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.0052083335f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), BinopInst("*", Float(0.041666668f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(0.0052083335f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("*", Float(0.041666668f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("*", Float(0.0052083335f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("*", Float(0.083333336f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("/", Float(1.3333334f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(0.013888889f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("*", Float(0.083333336f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), FunCallInst("tanf", BinopInst("/", Float(50265.484f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst24, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst26, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst27, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst25, kStruct))))
	StoreVarInst(Address(fConst28, kStruct), BinopInst("+", LoadVarInst(Address(fConst26, kStruct)), LoadVarInst(Address(fConst27, kStruct))))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst28, kStruct)))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fConst26, kStruct))), LoadVarInst(Address(fConst28, kStruct))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst32, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst31, kStruct))), LoadVarInst(Address(fConst28, kStruct))))
	StoreVarInst(Address(fConst33, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst31, kStruct))), LoadVarInst(Address(fConst28, kStruct)))))
	StoreVarInst(Address(fConst34, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(1.4500711f)))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("+", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst35, kStruct))))
	StoreVarInst(Address(fConst37, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst36, kStruct)))))
	StoreVarInst(Address(fConst38, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fConst34, kStruct))), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst39, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst39, kStruct))), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst41, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst39, kStruct))), LoadVarInst(Address(fConst36, kStruct)))))
	StoreVarInst(Address(fConst42, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst43, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(0.9351402f)))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("+", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fConst43, kStruct))))
	StoreVarInst(Address(fConst45, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst44, kStruct)))))
	StoreVarInst(Address(fConst46, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst43, kStruct)), LoadVarInst(Address(fConst42, kStruct))), LoadVarInst(Address(fConst44, kStruct))))
	StoreVarInst(Address(fConst47, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst48, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst47, kStruct))), LoadVarInst(Address(fConst44, kStruct))))
	StoreVarInst(Address(fConst49, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst47, kStruct))), LoadVarInst(Address(fConst44, kStruct)))))
	StoreVarInst(Address(fConst50, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst51, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst52, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(0.2452915f)))
	StoreVarInst(Address(fConst53, kStruct), BinopInst("+", LoadVarInst(Address(fConst51, kStruct)), LoadVarInst(Address(fConst52, kStruct))))
	StoreVarInst(Address(fConst54, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst53, kStruct)))))
	StoreVarInst(Address(fConst55, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fConst51, kStruct))), LoadVarInst(Address(fConst53, kStruct))))
	StoreVarInst(Address(fConst56, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst57, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst56, kStruct))), LoadVarInst(Address(fConst53, kStruct))))
	StoreVarInst(Address(fConst58, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst56, kStruct))), LoadVarInst(Address(fConst53, kStruct)))))
	StoreVarInst(Address(fConst59, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst60, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(0.6896214f)))
	StoreVarInst(Address(fConst61, kStruct), BinopInst("+", LoadVarInst(Address(fConst59, kStruct)), LoadVarInst(Address(fConst60, kStruct))))
	StoreVarInst(Address(fConst62, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst61, kStruct)))))
	StoreVarInst(Address(fConst63, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst60, kStruct)), LoadVarInst(Address(fConst59, kStruct))), LoadVarInst(Address(fConst61, kStruct))))
	StoreVarInst(Address(fConst64, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst61, kStruct))))
	StoreVarInst(Address(fConst65, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst61, kStruct)))))
	StoreVarInst(Address(fConst66, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst23, kStruct))))
	StoreVarInst(Address(fConst67, kStruct), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(1.0693583f)))
	StoreVarInst(Address(fConst68, kStruct), BinopInst("+", LoadVarInst(Address(fConst66, kStruct)), LoadVarInst(Address(fConst67, kStruct))))
	StoreVarInst(Address(fConst69, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst68, kStruct)))))
	StoreVarInst(Address(fConst70, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst67, kStruct)), LoadVarInst(Address(fConst66, kStruct))), LoadVarInst(Address(fConst68, kStruct))))
	StoreVarInst(Address(fConst71, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst68, kStruct))))
	StoreVarInst(Address(fConst72, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst25, kStruct))), LoadVarInst(Address(fConst68, kStruct)))))
	StoreVarInst(Address(fConst73, kStruct), FunCallInst("tanf", BinopInst("/", Float(31665.27f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst74, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst75, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst76, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst77, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst78, kStruct), BinopInst("+", LoadVarInst(Address(fConst76, kStruct)), LoadVarInst(Address(fConst77, kStruct))))
	StoreVarInst(Address(fConst79, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst78, kStruct)))))
	StoreVarInst(Address(fConst80, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst77, kStruct)), LoadVarInst(Address(fConst76, kStruct))), LoadVarInst(Address(fConst78, kStruct))))
	StoreVarInst(Address(fConst81, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst82, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst81, kStruct))), LoadVarInst(Address(fConst78, kStruct))))
	StoreVarInst(Address(fConst83, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst81, kStruct))), LoadVarInst(Address(fConst78, kStruct)))))
	StoreVarInst(Address(fConst84, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst85, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst86, kStruct), BinopInst("+", LoadVarInst(Address(fConst84, kStruct)), LoadVarInst(Address(fConst85, kStruct))))
	StoreVarInst(Address(fConst87, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst86, kStruct)))))
	StoreVarInst(Address(fConst88, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst85, kStruct)), LoadVarInst(Address(fConst84, kStruct))), LoadVarInst(Address(fConst86, kStruct))))
	StoreVarInst(Address(fConst89, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst86, kStruct))))
	StoreVarInst(Address(fConst90, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst86, kStruct)))))
	StoreVarInst(Address(fConst91, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst92, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst93, kStruct), BinopInst("+", LoadVarInst(Address(fConst91, kStruct)), LoadVarInst(Address(fConst92, kStruct))))
	StoreVarInst(Address(fConst94, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst93, kStruct)))))
	StoreVarInst(Address(fConst95, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst92, kStruct)), LoadVarInst(Address(fConst91, kStruct))), LoadVarInst(Address(fConst93, kStruct))))
	StoreVarInst(Address(fConst96, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst93, kStruct))))
	StoreVarInst(Address(fConst97, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst93, kStruct)))))
	StoreVarInst(Address(fConst98, kStruct), FunCallInst("tanf", BinopInst("/", Float(19947.87f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst99, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst100, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst101, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst102, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst103, kStruct), BinopInst("+", LoadVarInst(Address(fConst101, kStruct)), LoadVarInst(Address(fConst102, kStruct))))
	StoreVarInst(Address(fConst104, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst103, kStruct)))))
	StoreVarInst(Address(fConst105, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst102, kStruct)), LoadVarInst(Address(fConst101, kStruct))), LoadVarInst(Address(fConst103, kStruct))))
	StoreVarInst(Address(fConst106, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst107, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst106, kStruct))), LoadVarInst(Address(fConst103, kStruct))))
	StoreVarInst(Address(fConst108, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst106, kStruct))), LoadVarInst(Address(fConst103, kStruct)))))
	StoreVarInst(Address(fConst109, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst110, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst111, kStruct), BinopInst("+", LoadVarInst(Address(fConst109, kStruct)), LoadVarInst(Address(fConst110, kStruct))))
	StoreVarInst(Address(fConst112, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst111, kStruct)))))
	StoreVarInst(Address(fConst113, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst110, kStruct)), LoadVarInst(Address(fConst109, kStruct))), LoadVarInst(Address(fConst111, kStruct))))
	StoreVarInst(Address(fConst114, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst111, kStruct))))
	StoreVarInst(Address(fConst115, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst111, kStruct)))))
	StoreVarInst(Address(fConst116, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst117, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst118, kStruct), BinopInst("+", LoadVarInst(Address(fConst116, kStruct)), LoadVarInst(Address(fConst117, kStruct))))
	StoreVarInst(Address(fConst119, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst118, kStruct)))))
	StoreVarInst(Address(fConst120, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst117, kStruct)), LoadVarInst(Address(fConst116, kStruct))), LoadVarInst(Address(fConst118, kStruct))))
	StoreVarInst(Address(fConst121, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst118, kStruct))))
	StoreVarInst(Address(fConst122, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst118, kStruct)))))
	StoreVarInst(Address(fConst123, kStruct), FunCallInst("tanf", BinopInst("/", Float(12566.371f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst124, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst125, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst126, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst127, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst128, kStruct), BinopInst("+", LoadVarInst(Address(fConst126, kStruct)), LoadVarInst(Address(fConst127, kStruct))))
	StoreVarInst(Address(fConst129, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst128, kStruct)))))
	StoreVarInst(Address(fConst130, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst127, kStruct)), LoadVarInst(Address(fConst126, kStruct))), LoadVarInst(Address(fConst128, kStruct))))
	StoreVarInst(Address(fConst131, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst132, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst131, kStruct))), LoadVarInst(Address(fConst128, kStruct))))
	StoreVarInst(Address(fConst133, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst131, kStruct))), LoadVarInst(Address(fConst128, kStruct)))))
	StoreVarInst(Address(fConst134, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst135, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst136, kStruct), BinopInst("+", LoadVarInst(Address(fConst134, kStruct)), LoadVarInst(Address(fConst135, kStruct))))
	StoreVarInst(Address(fConst137, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst136, kStruct)))))
	StoreVarInst(Address(fConst138, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst135, kStruct)), LoadVarInst(Address(fConst134, kStruct))), LoadVarInst(Address(fConst136, kStruct))))
	StoreVarInst(Address(fConst139, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst136, kStruct))))
	StoreVarInst(Address(fConst140, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst136, kStruct)))))
	StoreVarInst(Address(fConst141, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst142, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst143, kStruct), BinopInst("+", LoadVarInst(Address(fConst141, kStruct)), LoadVarInst(Address(fConst142, kStruct))))
	StoreVarInst(Address(fConst144, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst143, kStruct)))))
	StoreVarInst(Address(fConst145, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst142, kStruct)), LoadVarInst(Address(fConst141, kStruct))), LoadVarInst(Address(fConst143, kStruct))))
	StoreVarInst(Address(fConst146, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst143, kStruct))))
	StoreVarInst(Address(fConst147, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst143, kStruct)))))
	StoreVarInst(Address(fConst148, kStruct), FunCallInst("tanf", BinopInst("/", Float(7916.3174f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst149, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst150, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst151, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst152, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst153, kStruct), BinopInst("+", LoadVarInst(Address(fConst151, kStruct)), LoadVarInst(Address(fConst152, kStruct))))
	StoreVarInst(Address(fConst154, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst153, kStruct)))))
	StoreVarInst(Address(fConst155, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst152, kStruct)), LoadVarInst(Address(fConst151, kStruct))), LoadVarInst(Address(fConst153, kStruct))))
	StoreVarInst(Address(fConst156, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst157, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst156, kStruct))), LoadVarInst(Address(fConst153, kStruct))))
	StoreVarInst(Address(fConst158, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst156, kStruct))), LoadVarInst(Address(fConst153, kStruct)))))
	StoreVarInst(Address(fConst159, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst160, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst161, kStruct), BinopInst("+", LoadVarInst(Address(fConst159, kStruct)), LoadVarInst(Address(fConst160, kStruct))))
	StoreVarInst(Address(fConst162, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst161, kStruct)))))
	StoreVarInst(Address(fConst163, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst160, kStruct)), LoadVarInst(Address(fConst159, kStruct))), LoadVarInst(Address(fConst161, kStruct))))
	StoreVarInst(Address(fConst164, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst165, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst164, kStruct))), LoadVarInst(Address(fConst161, kStruct))))
	StoreVarInst(Address(fConst166, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst164, kStruct))), LoadVarInst(Address(fConst161, kStruct)))))
	StoreVarInst(Address(fConst167, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst168, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst169, kStruct), BinopInst("+", LoadVarInst(Address(fConst167, kStruct)), LoadVarInst(Address(fConst168, kStruct))))
	StoreVarInst(Address(fConst170, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst169, kStruct)))))
	StoreVarInst(Address(fConst171, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst168, kStruct)), LoadVarInst(Address(fConst167, kStruct))), LoadVarInst(Address(fConst169, kStruct))))
	StoreVarInst(Address(fConst172, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst173, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst172, kStruct))), LoadVarInst(Address(fConst169, kStruct))))
	StoreVarInst(Address(fConst174, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst172, kStruct))), LoadVarInst(Address(fConst169, kStruct)))))
	StoreVarInst(Address(fConst175, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst176, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst177, kStruct), BinopInst("+", LoadVarInst(Address(fConst175, kStruct)), LoadVarInst(Address(fConst176, kStruct))))
	StoreVarInst(Address(fConst178, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst179, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst176, kStruct)), LoadVarInst(Address(fConst175, kStruct))), LoadVarInst(Address(fConst177, kStruct))))
	StoreVarInst(Address(fConst180, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst149, kStruct))))
	StoreVarInst(Address(fConst181, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst180, kStruct))), LoadVarInst(Address(fConst177, kStruct))))
	StoreVarInst(Address(fConst182, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst180, kStruct))), LoadVarInst(Address(fConst177, kStruct)))))
	StoreVarInst(Address(fConst183, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst184, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst185, kStruct), BinopInst("+", LoadVarInst(Address(fConst183, kStruct)), LoadVarInst(Address(fConst184, kStruct))))
	StoreVarInst(Address(fConst186, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst185, kStruct)))))
	StoreVarInst(Address(fConst187, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst184, kStruct)), LoadVarInst(Address(fConst183, kStruct))), LoadVarInst(Address(fConst185, kStruct))))
	StoreVarInst(Address(fConst188, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst185, kStruct))))
	StoreVarInst(Address(fConst189, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst185, kStruct)))))
	StoreVarInst(Address(fConst190, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst148, kStruct))))
	StoreVarInst(Address(fConst191, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst150, kStruct))))
	StoreVarInst(Address(fConst192, kStruct), BinopInst("+", LoadVarInst(Address(fConst190, kStruct)), LoadVarInst(Address(fConst191, kStruct))))
	StoreVarInst(Address(fConst193, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst192, kStruct)))))
	StoreVarInst(Address(fConst194, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst191, kStruct)), LoadVarInst(Address(fConst190, kStruct))), LoadVarInst(Address(fConst192, kStruct))))
	StoreVarInst(Address(fConst195, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst192, kStruct))))
	StoreVarInst(Address(fConst196, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst150, kStruct))), LoadVarInst(Address(fConst192, kStruct)))))
	StoreVarInst(Address(fConst197, kStruct), FunCallInst("tanf", BinopInst("/", Float(4986.9673f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst198, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst199, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst200, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst201, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst202, kStruct), BinopInst("+", LoadVarInst(Address(fConst200, kStruct)), LoadVarInst(Address(fConst201, kStruct))))
	StoreVarInst(Address(fConst203, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst202, kStruct)))))
	StoreVarInst(Address(fConst204, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst201, kStruct)), LoadVarInst(Address(fConst200, kStruct))), LoadVarInst(Address(fConst202, kStruct))))
	StoreVarInst(Address(fConst205, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst206, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst205, kStruct))), LoadVarInst(Address(fConst202, kStruct))))
	StoreVarInst(Address(fConst207, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst205, kStruct))), LoadVarInst(Address(fConst202, kStruct)))))
	StoreVarInst(Address(fConst208, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst209, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst210, kStruct), BinopInst("+", LoadVarInst(Address(fConst208, kStruct)), LoadVarInst(Address(fConst209, kStruct))))
	StoreVarInst(Address(fConst211, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst210, kStruct)))))
	StoreVarInst(Address(fConst212, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst209, kStruct)), LoadVarInst(Address(fConst208, kStruct))), LoadVarInst(Address(fConst210, kStruct))))
	StoreVarInst(Address(fConst213, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst210, kStruct))))
	StoreVarInst(Address(fConst214, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst210, kStruct)))))
	StoreVarInst(Address(fConst215, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst216, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst217, kStruct), BinopInst("+", LoadVarInst(Address(fConst215, kStruct)), LoadVarInst(Address(fConst216, kStruct))))
	StoreVarInst(Address(fConst218, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst217, kStruct)))))
	StoreVarInst(Address(fConst219, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst216, kStruct)), LoadVarInst(Address(fConst215, kStruct))), LoadVarInst(Address(fConst217, kStruct))))
	StoreVarInst(Address(fConst220, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst217, kStruct))))
	StoreVarInst(Address(fConst221, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst217, kStruct)))))
	StoreVarInst(Address(fConst222, kStruct), FunCallInst("tanf", BinopInst("/", Float(3141.5928f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst223, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst224, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst225, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst226, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst227, kStruct), BinopInst("+", LoadVarInst(Address(fConst225, kStruct)), LoadVarInst(Address(fConst226, kStruct))))
	StoreVarInst(Address(fConst228, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst227, kStruct)))))
	StoreVarInst(Address(fConst229, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst226, kStruct)), LoadVarInst(Address(fConst225, kStruct))), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst230, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst231, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst230, kStruct))), LoadVarInst(Address(fConst227, kStruct))))
	StoreVarInst(Address(fConst232, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst230, kStruct))), LoadVarInst(Address(fConst227, kStruct)))))
	StoreVarInst(Address(fConst233, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst234, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst235, kStruct), BinopInst("+", LoadVarInst(Address(fConst233, kStruct)), LoadVarInst(Address(fConst234, kStruct))))
	StoreVarInst(Address(fConst236, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst235, kStruct)))))
	StoreVarInst(Address(fConst237, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst234, kStruct)), LoadVarInst(Address(fConst233, kStruct))), LoadVarInst(Address(fConst235, kStruct))))
	StoreVarInst(Address(fConst238, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst235, kStruct))))
	StoreVarInst(Address(fConst239, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst235, kStruct)))))
	StoreVarInst(Address(fConst240, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst241, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst242, kStruct), BinopInst("+", LoadVarInst(Address(fConst240, kStruct)), LoadVarInst(Address(fConst241, kStruct))))
	StoreVarInst(Address(fConst243, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst242, kStruct)))))
	StoreVarInst(Address(fConst244, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst241, kStruct)), LoadVarInst(Address(fConst240, kStruct))), LoadVarInst(Address(fConst242, kStruct))))
	StoreVarInst(Address(fConst245, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst242, kStruct))))
	StoreVarInst(Address(fConst246, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst242, kStruct)))))
	StoreVarInst(Address(fConst247, kStruct), FunCallInst("tanf", BinopInst("/", Float(1979.0793f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst248, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst249, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst250, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst251, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst252, kStruct), BinopInst("+", LoadVarInst(Address(fConst250, kStruct)), LoadVarInst(Address(fConst251, kStruct))))
	StoreVarInst(Address(fConst253, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst252, kStruct)))))
	StoreVarInst(Address(fConst254, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst251, kStruct)), LoadVarInst(Address(fConst250, kStruct))), LoadVarInst(Address(fConst252, kStruct))))
	StoreVarInst(Address(fConst255, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst256, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst255, kStruct))), LoadVarInst(Address(fConst252, kStruct))))
	StoreVarInst(Address(fConst257, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst255, kStruct))), LoadVarInst(Address(fConst252, kStruct)))))
	StoreVarInst(Address(fConst258, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst259, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst260, kStruct), BinopInst("+", LoadVarInst(Address(fConst258, kStruct)), LoadVarInst(Address(fConst259, kStruct))))
	StoreVarInst(Address(fConst261, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst260, kStruct)))))
	StoreVarInst(Address(fConst262, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst259, kStruct)), LoadVarInst(Address(fConst258, kStruct))), LoadVarInst(Address(fConst260, kStruct))))
	StoreVarInst(Address(fConst263, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst260, kStruct))))
	StoreVarInst(Address(fConst264, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst260, kStruct)))))
	StoreVarInst(Address(fConst265, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst266, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst267, kStruct), BinopInst("+", LoadVarInst(Address(fConst265, kStruct)), LoadVarInst(Address(fConst266, kStruct))))
	StoreVarInst(Address(fConst268, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst267, kStruct)))))
	StoreVarInst(Address(fConst269, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst266, kStruct)), LoadVarInst(Address(fConst265, kStruct))), LoadVarInst(Address(fConst267, kStruct))))
	StoreVarInst(Address(fConst270, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst267, kStruct))))
	StoreVarInst(Address(fConst271, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst267, kStruct)))))
	StoreVarInst(Address(fConst272, kStruct), FunCallInst("tanf", BinopInst("/", Float(1246.7418f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst273, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst274, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst275, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst276, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst277, kStruct), BinopInst("+", LoadVarInst(Address(fConst275, kStruct)), LoadVarInst(Address(fConst276, kStruct))))
	StoreVarInst(Address(fConst278, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst277, kStruct)))))
	StoreVarInst(Address(fConst279, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst276, kStruct)), LoadVarInst(Address(fConst275, kStruct))), LoadVarInst(Address(fConst277, kStruct))))
	StoreVarInst(Address(fConst280, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst281, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst280, kStruct))), LoadVarInst(Address(fConst277, kStruct))))
	StoreVarInst(Address(fConst282, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst280, kStruct))), LoadVarInst(Address(fConst277, kStruct)))))
	StoreVarInst(Address(fConst283, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst284, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst285, kStruct), BinopInst("+", LoadVarInst(Address(fConst283, kStruct)), LoadVarInst(Address(fConst284, kStruct))))
	StoreVarInst(Address(fConst286, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst285, kStruct)))))
	StoreVarInst(Address(fConst287, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst284, kStruct)), LoadVarInst(Address(fConst283, kStruct))), LoadVarInst(Address(fConst285, kStruct))))
	StoreVarInst(Address(fConst288, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst289, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst288, kStruct))), LoadVarInst(Address(fConst285, kStruct))))
	StoreVarInst(Address(fConst290, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst288, kStruct))), LoadVarInst(Address(fConst285, kStruct)))))
	StoreVarInst(Address(fConst291, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst292, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst293, kStruct), BinopInst("+", LoadVarInst(Address(fConst291, kStruct)), LoadVarInst(Address(fConst292, kStruct))))
	StoreVarInst(Address(fConst294, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst293, kStruct)))))
	StoreVarInst(Address(fConst295, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst292, kStruct)), LoadVarInst(Address(fConst291, kStruct))), LoadVarInst(Address(fConst293, kStruct))))
	StoreVarInst(Address(fConst296, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst297, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst296, kStruct))), LoadVarInst(Address(fConst293, kStruct))))
	StoreVarInst(Address(fConst298, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst296, kStruct))), LoadVarInst(Address(fConst293, kStruct)))))
	StoreVarInst(Address(fConst299, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst300, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst301, kStruct), BinopInst("+", LoadVarInst(Address(fConst299, kStruct)), LoadVarInst(Address(fConst300, kStruct))))
	StoreVarInst(Address(fConst302, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst301, kStruct)))))
	StoreVarInst(Address(fConst303, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst300, kStruct)), LoadVarInst(Address(fConst299, kStruct))), LoadVarInst(Address(fConst301, kStruct))))
	StoreVarInst(Address(fConst304, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst273, kStruct))))
	StoreVarInst(Address(fConst305, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst304, kStruct))), LoadVarInst(Address(fConst301, kStruct))))
	StoreVarInst(Address(fConst306, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst304, kStruct))), LoadVarInst(Address(fConst301, kStruct)))))
	StoreVarInst(Address(fConst307, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst308, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst309, kStruct), BinopInst("+", LoadVarInst(Address(fConst307, kStruct)), LoadVarInst(Address(fConst308, kStruct))))
	StoreVarInst(Address(fConst310, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst309, kStruct)))))
	StoreVarInst(Address(fConst311, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst308, kStruct)), LoadVarInst(Address(fConst307, kStruct))), LoadVarInst(Address(fConst309, kStruct))))
	StoreVarInst(Address(fConst312, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst309, kStruct))))
	StoreVarInst(Address(fConst313, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst309, kStruct)))))
	StoreVarInst(Address(fConst314, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst272, kStruct))))
	StoreVarInst(Address(fConst315, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst274, kStruct))))
	StoreVarInst(Address(fConst316, kStruct), BinopInst("+", LoadVarInst(Address(fConst314, kStruct)), LoadVarInst(Address(fConst315, kStruct))))
	StoreVarInst(Address(fConst317, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst316, kStruct)))))
	StoreVarInst(Address(fConst318, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst315, kStruct)), LoadVarInst(Address(fConst314, kStruct))), LoadVarInst(Address(fConst316, kStruct))))
	StoreVarInst(Address(fConst319, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst316, kStruct))))
	StoreVarInst(Address(fConst320, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst274, kStruct))), LoadVarInst(Address(fConst316, kStruct)))))
	StoreVarInst(Address(fConst321, kStruct), FunCallInst("tanf", BinopInst("/", Float(785.3982f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst322, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst323, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst324, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst325, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst326, kStruct), BinopInst("+", LoadVarInst(Address(fConst324, kStruct)), LoadVarInst(Address(fConst325, kStruct))))
	StoreVarInst(Address(fConst327, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst326, kStruct)))))
	StoreVarInst(Address(fConst328, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst325, kStruct)), LoadVarInst(Address(fConst324, kStruct))), LoadVarInst(Address(fConst326, kStruct))))
	StoreVarInst(Address(fConst329, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst330, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst329, kStruct))), LoadVarInst(Address(fConst326, kStruct))))
	StoreVarInst(Address(fConst331, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst329, kStruct))), LoadVarInst(Address(fConst326, kStruct)))))
	StoreVarInst(Address(fConst332, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst333, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst334, kStruct), BinopInst("+", LoadVarInst(Address(fConst332, kStruct)), LoadVarInst(Address(fConst333, kStruct))))
	StoreVarInst(Address(fConst335, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst334, kStruct)))))
	StoreVarInst(Address(fConst336, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst333, kStruct)), LoadVarInst(Address(fConst332, kStruct))), LoadVarInst(Address(fConst334, kStruct))))
	StoreVarInst(Address(fConst337, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst334, kStruct))))
	StoreVarInst(Address(fConst338, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst334, kStruct)))))
	StoreVarInst(Address(fConst339, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst340, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst341, kStruct), BinopInst("+", LoadVarInst(Address(fConst339, kStruct)), LoadVarInst(Address(fConst340, kStruct))))
	StoreVarInst(Address(fConst342, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst341, kStruct)))))
	StoreVarInst(Address(fConst343, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst340, kStruct)), LoadVarInst(Address(fConst339, kStruct))), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst344, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst341, kStruct))))
	StoreVarInst(Address(fConst345, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst341, kStruct)))))
	StoreVarInst(Address(fConst346, kStruct), FunCallInst("tanf", BinopInst("/", Float(494.76984f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst347, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst348, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst349, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst350, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst351, kStruct), BinopInst("+", LoadVarInst(Address(fConst349, kStruct)), LoadVarInst(Address(fConst350, kStruct))))
	StoreVarInst(Address(fConst352, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst351, kStruct)))))
	StoreVarInst(Address(fConst353, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst350, kStruct)), LoadVarInst(Address(fConst349, kStruct))), LoadVarInst(Address(fConst351, kStruct))))
	StoreVarInst(Address(fConst354, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst355, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst354, kStruct))), LoadVarInst(Address(fConst351, kStruct))))
	StoreVarInst(Address(fConst356, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst354, kStruct))), LoadVarInst(Address(fConst351, kStruct)))))
	StoreVarInst(Address(fConst357, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst358, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst359, kStruct), BinopInst("+", LoadVarInst(Address(fConst357, kStruct)), LoadVarInst(Address(fConst358, kStruct))))
	StoreVarInst(Address(fConst360, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst359, kStruct)))))
	StoreVarInst(Address(fConst361, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst358, kStruct)), LoadVarInst(Address(fConst357, kStruct))), LoadVarInst(Address(fConst359, kStruct))))
	StoreVarInst(Address(fConst362, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst359, kStruct))))
	StoreVarInst(Address(fConst363, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst359, kStruct)))))
	StoreVarInst(Address(fConst364, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst365, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst366, kStruct), BinopInst("+", LoadVarInst(Address(fConst364, kStruct)), LoadVarInst(Address(fConst365, kStruct))))
	StoreVarInst(Address(fConst367, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst366, kStruct)))))
	StoreVarInst(Address(fConst368, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst365, kStruct)), LoadVarInst(Address(fConst364, kStruct))), LoadVarInst(Address(fConst366, kStruct))))
	StoreVarInst(Address(fConst369, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst366, kStruct))))
	StoreVarInst(Address(fConst370, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst366, kStruct)))))
	StoreVarInst(Address(fConst371, kStruct), FunCallInst("tanf", BinopInst("/", Float(311.68546f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst372, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst373, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst374, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst375, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst376, kStruct), BinopInst("+", LoadVarInst(Address(fConst374, kStruct)), LoadVarInst(Address(fConst375, kStruct))))
	StoreVarInst(Address(fConst377, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst376, kStruct)))))
	StoreVarInst(Address(fConst378, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst375, kStruct)), LoadVarInst(Address(fConst374, kStruct))), LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst379, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst380, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst379, kStruct))), LoadVarInst(Address(fConst376, kStruct))))
	StoreVarInst(Address(fConst381, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst379, kStruct))), LoadVarInst(Address(fConst376, kStruct)))))
	StoreVarInst(Address(fConst382, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst383, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst384, kStruct), BinopInst("+", LoadVarInst(Address(fConst382, kStruct)), LoadVarInst(Address(fConst383, kStruct))))
	StoreVarInst(Address(fConst385, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst384, kStruct)))))
	StoreVarInst(Address(fConst386, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst383, kStruct)), LoadVarInst(Address(fConst382, kStruct))), LoadVarInst(Address(fConst384, kStruct))))
	StoreVarInst(Address(fConst387, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst384, kStruct))))
	StoreVarInst(Address(fConst388, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst384, kStruct)))))
	StoreVarInst(Address(fConst389, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst390, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst391, kStruct), BinopInst("+", LoadVarInst(Address(fConst389, kStruct)), LoadVarInst(Address(fConst390, kStruct))))
	StoreVarInst(Address(fConst392, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst391, kStruct)))))
	StoreVarInst(Address(fConst393, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst390, kStruct)), LoadVarInst(Address(fConst389, kStruct))), LoadVarInst(Address(fConst391, kStruct))))
	StoreVarInst(Address(fConst394, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst391, kStruct))))
	StoreVarInst(Address(fConst395, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst391, kStruct)))))
	StoreVarInst(Address(fConst396, kStruct), FunCallInst("tanf", BinopInst("/", Float(196.34955f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst397, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst398, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst399, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst400, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst401, kStruct), BinopInst("+", LoadVarInst(Address(fConst399, kStruct)), LoadVarInst(Address(fConst400, kStruct))))
	StoreVarInst(Address(fConst402, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst401, kStruct)))))
	StoreVarInst(Address(fConst403, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst400, kStruct)), LoadVarInst(Address(fConst399, kStruct))), LoadVarInst(Address(fConst401, kStruct))))
	StoreVarInst(Address(fConst404, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst405, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst404, kStruct))), LoadVarInst(Address(fConst401, kStruct))))
	StoreVarInst(Address(fConst406, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst404, kStruct))), LoadVarInst(Address(fConst401, kStruct)))))
	StoreVarInst(Address(fConst407, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst408, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst409, kStruct), BinopInst("+", LoadVarInst(Address(fConst407, kStruct)), LoadVarInst(Address(fConst408, kStruct))))
	StoreVarInst(Address(fConst410, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst409, kStruct)))))
	StoreVarInst(Address(fConst411, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst408, kStruct)), LoadVarInst(Address(fConst407, kStruct))), LoadVarInst(Address(fConst409, kStruct))))
	StoreVarInst(Address(fConst412, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst413, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst412, kStruct))), LoadVarInst(Address(fConst409, kStruct))))
	StoreVarInst(Address(fConst414, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst412, kStruct))), LoadVarInst(Address(fConst409, kStruct)))))
	StoreVarInst(Address(fConst415, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst416, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst417, kStruct), BinopInst("+", LoadVarInst(Address(fConst415, kStruct)), LoadVarInst(Address(fConst416, kStruct))))
	StoreVarInst(Address(fConst418, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst417, kStruct)))))
	StoreVarInst(Address(fConst419, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst416, kStruct)), LoadVarInst(Address(fConst415, kStruct))), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst420, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst421, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst420, kStruct))), LoadVarInst(Address(fConst417, kStruct))))
	StoreVarInst(Address(fConst422, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst420, kStruct))), LoadVarInst(Address(fConst417, kStruct)))))
	StoreVarInst(Address(fConst423, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst424, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst425, kStruct), BinopInst("+", LoadVarInst(Address(fConst423, kStruct)), LoadVarInst(Address(fConst424, kStruct))))
	StoreVarInst(Address(fConst426, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst425, kStruct)))))
	StoreVarInst(Address(fConst427, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst424, kStruct)), LoadVarInst(Address(fConst423, kStruct))), LoadVarInst(Address(fConst425, kStruct))))
	StoreVarInst(Address(fConst428, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst429, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst428, kStruct))), LoadVarInst(Address(fConst425, kStruct))))
	StoreVarInst(Address(fConst430, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst428, kStruct))), LoadVarInst(Address(fConst425, kStruct)))))
	StoreVarInst(Address(fConst431, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst432, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst433, kStruct), BinopInst("+", LoadVarInst(Address(fConst431, kStruct)), LoadVarInst(Address(fConst432, kStruct))))
	StoreVarInst(Address(fConst434, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst433, kStruct)))))
	StoreVarInst(Address(fConst435, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst432, kStruct)), LoadVarInst(Address(fConst431, kStruct))), LoadVarInst(Address(fConst433, kStruct))))
	StoreVarInst(Address(fConst436, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst437, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst436, kStruct))), LoadVarInst(Address(fConst433, kStruct))))
	StoreVarInst(Address(fConst438, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst436, kStruct))), LoadVarInst(Address(fConst433, kStruct)))))
	StoreVarInst(Address(fConst439, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst73, kStruct))))
	StoreVarInst(Address(fConst440, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst75, kStruct))))
	StoreVarInst(Address(fConst441, kStruct), BinopInst("+", LoadVarInst(Address(fConst439, kStruct)), LoadVarInst(Address(fConst440, kStruct))))
	StoreVarInst(Address(fConst442, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst75, kStruct))), LoadVarInst(Address(fConst441, kStruct)))))
	StoreVarInst(Address(fConst443, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst440, kStruct)), LoadVarInst(Address(fConst439, kStruct))), LoadVarInst(Address(fConst441, kStruct))))
	StoreVarInst(Address(fConst444, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst74, kStruct))))
	StoreVarInst(Address(fConst445, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst444, kStruct))), LoadVarInst(Address(fConst441, kStruct))))
	StoreVarInst(Address(fConst446, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst444, kStruct))), LoadVarInst(Address(fConst441, kStruct)))))
	StoreVarInst(Address(fConst447, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst448, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst449, kStruct), BinopInst("+", LoadVarInst(Address(fConst447, kStruct)), LoadVarInst(Address(fConst448, kStruct))))
	StoreVarInst(Address(fConst450, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst449, kStruct)))))
	StoreVarInst(Address(fConst451, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst448, kStruct)), LoadVarInst(Address(fConst447, kStruct))), LoadVarInst(Address(fConst449, kStruct))))
	StoreVarInst(Address(fConst452, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst453, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst452, kStruct))), LoadVarInst(Address(fConst449, kStruct))))
	StoreVarInst(Address(fConst454, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst452, kStruct))), LoadVarInst(Address(fConst449, kStruct)))))
	StoreVarInst(Address(fConst455, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst456, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst457, kStruct), BinopInst("+", LoadVarInst(Address(fConst455, kStruct)), LoadVarInst(Address(fConst456, kStruct))))
	StoreVarInst(Address(fConst458, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst457, kStruct)))))
	StoreVarInst(Address(fConst459, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst456, kStruct)), LoadVarInst(Address(fConst455, kStruct))), LoadVarInst(Address(fConst457, kStruct))))
	StoreVarInst(Address(fConst460, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst461, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst460, kStruct))), LoadVarInst(Address(fConst457, kStruct))))
	StoreVarInst(Address(fConst462, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst460, kStruct))), LoadVarInst(Address(fConst457, kStruct)))))
	StoreVarInst(Address(fConst463, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst197, kStruct))))
	StoreVarInst(Address(fConst464, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst199, kStruct))))
	StoreVarInst(Address(fConst465, kStruct), BinopInst("+", LoadVarInst(Address(fConst463, kStruct)), LoadVarInst(Address(fConst464, kStruct))))
	StoreVarInst(Address(fConst466, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst199, kStruct))), LoadVarInst(Address(fConst465, kStruct)))))
	StoreVarInst(Address(fConst467, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst464, kStruct)), LoadVarInst(Address(fConst463, kStruct))), LoadVarInst(Address(fConst465, kStruct))))
	StoreVarInst(Address(fConst468, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst198, kStruct))))
	StoreVarInst(Address(fConst469, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst468, kStruct))), LoadVarInst(Address(fConst465, kStruct))))
	StoreVarInst(Address(fConst470, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst468, kStruct))), LoadVarInst(Address(fConst465, kStruct)))))
	StoreVarInst(Address(fConst471, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst472, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst473, kStruct), BinopInst("+", LoadVarInst(Address(fConst471, kStruct)), LoadVarInst(Address(fConst472, kStruct))))
	StoreVarInst(Address(fConst474, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst473, kStruct)))))
	StoreVarInst(Address(fConst475, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst472, kStruct)), LoadVarInst(Address(fConst471, kStruct))), LoadVarInst(Address(fConst473, kStruct))))
	StoreVarInst(Address(fConst476, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst477, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst476, kStruct))), LoadVarInst(Address(fConst473, kStruct))))
	StoreVarInst(Address(fConst478, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst476, kStruct))), LoadVarInst(Address(fConst473, kStruct)))))
	StoreVarInst(Address(fConst479, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst480, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst481, kStruct), BinopInst("+", LoadVarInst(Address(fConst479, kStruct)), LoadVarInst(Address(fConst480, kStruct))))
	StoreVarInst(Address(fConst482, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst483, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst480, kStruct)), LoadVarInst(Address(fConst479, kStruct))), LoadVarInst(Address(fConst481, kStruct))))
	StoreVarInst(Address(fConst484, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst485, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst484, kStruct))), LoadVarInst(Address(fConst481, kStruct))))
	StoreVarInst(Address(fConst486, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst484, kStruct))), LoadVarInst(Address(fConst481, kStruct)))))
	StoreVarInst(Address(fConst487, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst321, kStruct))))
	StoreVarInst(Address(fConst488, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst323, kStruct))))
	StoreVarInst(Address(fConst489, kStruct), BinopInst("+", LoadVarInst(Address(fConst487, kStruct)), LoadVarInst(Address(fConst488, kStruct))))
	StoreVarInst(Address(fConst490, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst323, kStruct))), LoadVarInst(Address(fConst489, kStruct)))))
	StoreVarInst(Address(fConst491, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst488, kStruct)), LoadVarInst(Address(fConst487, kStruct))), LoadVarInst(Address(fConst489, kStruct))))
	StoreVarInst(Address(fConst492, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst322, kStruct))))
	StoreVarInst(Address(fConst493, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst492, kStruct))), LoadVarInst(Address(fConst489, kStruct))))
	StoreVarInst(Address(fConst494, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst492, kStruct))), LoadVarInst(Address(fConst489, kStruct)))))
	StoreVarInst(Address(fConst495, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst496, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst497, kStruct), BinopInst("+", LoadVarInst(Address(fConst495, kStruct)), LoadVarInst(Address(fConst496, kStruct))))
	StoreVarInst(Address(fConst498, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst497, kStruct)))))
	StoreVarInst(Address(fConst499, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst496, kStruct)), LoadVarInst(Address(fConst495, kStruct))), LoadVarInst(Address(fConst497, kStruct))))
	StoreVarInst(Address(fConst500, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst397, kStruct))))
	StoreVarInst(Address(fConst501, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst500, kStruct))), LoadVarInst(Address(fConst497, kStruct))))
	StoreVarInst(Address(fConst502, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst500, kStruct))), LoadVarInst(Address(fConst497, kStruct)))))
	StoreVarInst(Address(fConst503, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst504, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst505, kStruct), BinopInst("+", LoadVarInst(Address(fConst503, kStruct)), LoadVarInst(Address(fConst504, kStruct))))
	StoreVarInst(Address(fConst506, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst505, kStruct)))))
	StoreVarInst(Address(fConst507, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst504, kStruct)), LoadVarInst(Address(fConst503, kStruct))), LoadVarInst(Address(fConst505, kStruct))))
	StoreVarInst(Address(fConst508, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst505, kStruct))))
	StoreVarInst(Address(fConst509, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst505, kStruct)))))
	StoreVarInst(Address(fConst510, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst396, kStruct))))
	StoreVarInst(Address(fConst511, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst398, kStruct))))
	StoreVarInst(Address(fConst512, kStruct), BinopInst("+", LoadVarInst(Address(fConst510, kStruct)), LoadVarInst(Address(fConst511, kStruct))))
	StoreVarInst(Address(fConst513, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst512, kStruct)))))
	StoreVarInst(Address(fConst514, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst511, kStruct)), LoadVarInst(Address(fConst510, kStruct))), LoadVarInst(Address(fConst512, kStruct))))
	StoreVarInst(Address(fConst515, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst512, kStruct))))
	StoreVarInst(Address(fConst516, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst398, kStruct))), LoadVarInst(Address(fConst512, kStruct)))))
	StoreVarInst(Address(fConst517, kStruct), FunCallInst("tanf", BinopInst("/", Float(123.69246f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst518, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst519, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst520, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst521, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst522, kStruct), BinopInst("+", LoadVarInst(Address(fConst520, kStruct)), LoadVarInst(Address(fConst521, kStruct))))
	StoreVarInst(Address(fConst523, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst522, kStruct)))))
	StoreVarInst(Address(fConst524, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst521, kStruct)), LoadVarInst(Address(fConst520, kStruct))), LoadVarInst(Address(fConst522, kStruct))))
	StoreVarInst(Address(fConst525, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst526, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst525, kStruct))), LoadVarInst(Address(fConst522, kStruct))))
	StoreVarInst(Address(fConst527, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst525, kStruct))), LoadVarInst(Address(fConst522, kStruct)))))
	StoreVarInst(Address(fConst528, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst529, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst530, kStruct), BinopInst("+", LoadVarInst(Address(fConst528, kStruct)), LoadVarInst(Address(fConst529, kStruct))))
	StoreVarInst(Address(fConst531, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst530, kStruct)))))
	StoreVarInst(Address(fConst532, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst529, kStruct)), LoadVarInst(Address(fConst528, kStruct))), LoadVarInst(Address(fConst530, kStruct))))
	StoreVarInst(Address(fConst533, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst534, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst533, kStruct))), LoadVarInst(Address(fConst530, kStruct))))
	StoreVarInst(Address(fConst535, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst533, kStruct))), LoadVarInst(Address(fConst530, kStruct)))))
	StoreVarInst(Address(fConst536, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst537, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst538, kStruct), BinopInst("+", LoadVarInst(Address(fConst536, kStruct)), LoadVarInst(Address(fConst537, kStruct))))
	StoreVarInst(Address(fConst539, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst538, kStruct)))))
	StoreVarInst(Address(fConst540, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst537, kStruct)), LoadVarInst(Address(fConst536, kStruct))), LoadVarInst(Address(fConst538, kStruct))))
	StoreVarInst(Address(fConst541, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst542, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst541, kStruct))), LoadVarInst(Address(fConst538, kStruct))))
	StoreVarInst(Address(fConst543, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst541, kStruct))), LoadVarInst(Address(fConst538, kStruct)))))
	StoreVarInst(Address(fConst544, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst545, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst546, kStruct), BinopInst("+", LoadVarInst(Address(fConst544, kStruct)), LoadVarInst(Address(fConst545, kStruct))))
	StoreVarInst(Address(fConst547, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst546, kStruct)))))
	StoreVarInst(Address(fConst548, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst545, kStruct)), LoadVarInst(Address(fConst544, kStruct))), LoadVarInst(Address(fConst546, kStruct))))
	StoreVarInst(Address(fConst549, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst550, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst549, kStruct))), LoadVarInst(Address(fConst546, kStruct))))
	StoreVarInst(Address(fConst551, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst549, kStruct))), LoadVarInst(Address(fConst546, kStruct)))))
	StoreVarInst(Address(fConst552, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst553, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst554, kStruct), BinopInst("+", LoadVarInst(Address(fConst552, kStruct)), LoadVarInst(Address(fConst553, kStruct))))
	StoreVarInst(Address(fConst555, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst554, kStruct)))))
	StoreVarInst(Address(fConst556, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst553, kStruct)), LoadVarInst(Address(fConst552, kStruct))), LoadVarInst(Address(fConst554, kStruct))))
	StoreVarInst(Address(fConst557, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst558, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst557, kStruct))), LoadVarInst(Address(fConst554, kStruct))))
	StoreVarInst(Address(fConst559, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst557, kStruct))), LoadVarInst(Address(fConst554, kStruct)))))
	StoreVarInst(Address(fConst560, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst98, kStruct))))
	StoreVarInst(Address(fConst561, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst100, kStruct))))
	StoreVarInst(Address(fConst562, kStruct), BinopInst("+", LoadVarInst(Address(fConst560, kStruct)), LoadVarInst(Address(fConst561, kStruct))))
	StoreVarInst(Address(fConst563, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst100, kStruct))), LoadVarInst(Address(fConst562, kStruct)))))
	StoreVarInst(Address(fConst564, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst561, kStruct)), LoadVarInst(Address(fConst560, kStruct))), LoadVarInst(Address(fConst562, kStruct))))
	StoreVarInst(Address(fConst565, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst99, kStruct))))
	StoreVarInst(Address(fConst566, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst565, kStruct))), LoadVarInst(Address(fConst562, kStruct))))
	StoreVarInst(Address(fConst567, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst565, kStruct))), LoadVarInst(Address(fConst562, kStruct)))))
	StoreVarInst(Address(fConst568, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst569, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst570, kStruct), BinopInst("+", LoadVarInst(Address(fConst568, kStruct)), LoadVarInst(Address(fConst569, kStruct))))
	StoreVarInst(Address(fConst571, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst570, kStruct)))))
	StoreVarInst(Address(fConst572, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst569, kStruct)), LoadVarInst(Address(fConst568, kStruct))), LoadVarInst(Address(fConst570, kStruct))))
	StoreVarInst(Address(fConst573, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst574, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst573, kStruct))), LoadVarInst(Address(fConst570, kStruct))))
	StoreVarInst(Address(fConst575, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst573, kStruct))), LoadVarInst(Address(fConst570, kStruct)))))
	StoreVarInst(Address(fConst576, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst577, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst578, kStruct), BinopInst("+", LoadVarInst(Address(fConst576, kStruct)), LoadVarInst(Address(fConst577, kStruct))))
	StoreVarInst(Address(fConst579, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst578, kStruct)))))
	StoreVarInst(Address(fConst580, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst577, kStruct)), LoadVarInst(Address(fConst576, kStruct))), LoadVarInst(Address(fConst578, kStruct))))
	StoreVarInst(Address(fConst581, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst582, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst581, kStruct))), LoadVarInst(Address(fConst578, kStruct))))
	StoreVarInst(Address(fConst583, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst581, kStruct))), LoadVarInst(Address(fConst578, kStruct)))))
	StoreVarInst(Address(fConst584, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst222, kStruct))))
	StoreVarInst(Address(fConst585, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst224, kStruct))))
	StoreVarInst(Address(fConst586, kStruct), BinopInst("+", LoadVarInst(Address(fConst584, kStruct)), LoadVarInst(Address(fConst585, kStruct))))
	StoreVarInst(Address(fConst587, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst224, kStruct))), LoadVarInst(Address(fConst586, kStruct)))))
	StoreVarInst(Address(fConst588, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst585, kStruct)), LoadVarInst(Address(fConst584, kStruct))), LoadVarInst(Address(fConst586, kStruct))))
	StoreVarInst(Address(fConst589, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst223, kStruct))))
	StoreVarInst(Address(fConst590, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst589, kStruct))), LoadVarInst(Address(fConst586, kStruct))))
	StoreVarInst(Address(fConst591, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst589, kStruct))), LoadVarInst(Address(fConst586, kStruct)))))
	StoreVarInst(Address(fConst592, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst593, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst594, kStruct), BinopInst("+", LoadVarInst(Address(fConst592, kStruct)), LoadVarInst(Address(fConst593, kStruct))))
	StoreVarInst(Address(fConst595, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst594, kStruct)))))
	StoreVarInst(Address(fConst596, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst593, kStruct)), LoadVarInst(Address(fConst592, kStruct))), LoadVarInst(Address(fConst594, kStruct))))
	StoreVarInst(Address(fConst597, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst598, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst597, kStruct))), LoadVarInst(Address(fConst594, kStruct))))
	StoreVarInst(Address(fConst599, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst597, kStruct))), LoadVarInst(Address(fConst594, kStruct)))))
	StoreVarInst(Address(fConst600, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst601, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst602, kStruct), BinopInst("+", LoadVarInst(Address(fConst600, kStruct)), LoadVarInst(Address(fConst601, kStruct))))
	StoreVarInst(Address(fConst603, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst602, kStruct)))))
	StoreVarInst(Address(fConst604, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst601, kStruct)), LoadVarInst(Address(fConst600, kStruct))), LoadVarInst(Address(fConst602, kStruct))))
	StoreVarInst(Address(fConst605, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst606, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst605, kStruct))), LoadVarInst(Address(fConst602, kStruct))))
	StoreVarInst(Address(fConst607, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst605, kStruct))), LoadVarInst(Address(fConst602, kStruct)))))
	StoreVarInst(Address(fConst608, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst346, kStruct))))
	StoreVarInst(Address(fConst609, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst348, kStruct))))
	StoreVarInst(Address(fConst610, kStruct), BinopInst("+", LoadVarInst(Address(fConst608, kStruct)), LoadVarInst(Address(fConst609, kStruct))))
	StoreVarInst(Address(fConst611, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst348, kStruct))), LoadVarInst(Address(fConst610, kStruct)))))
	StoreVarInst(Address(fConst612, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst609, kStruct)), LoadVarInst(Address(fConst608, kStruct))), LoadVarInst(Address(fConst610, kStruct))))
	StoreVarInst(Address(fConst613, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst347, kStruct))))
	StoreVarInst(Address(fConst614, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst613, kStruct))), LoadVarInst(Address(fConst610, kStruct))))
	StoreVarInst(Address(fConst615, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst613, kStruct))), LoadVarInst(Address(fConst610, kStruct)))))
	StoreVarInst(Address(fConst616, kStruct), BinopInst("/", Float(0.78241307f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst617, kStruct), BinopInst("+", Float(0.2452915f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst618, kStruct), BinopInst("+", LoadVarInst(Address(fConst616, kStruct)), LoadVarInst(Address(fConst617, kStruct))))
	StoreVarInst(Address(fConst619, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.2452915f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst618, kStruct)))))
	StoreVarInst(Address(fConst620, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst617, kStruct)), LoadVarInst(Address(fConst616, kStruct))), LoadVarInst(Address(fConst618, kStruct))))
	StoreVarInst(Address(fConst621, kStruct), BinopInst("/", Float(0.0001f), LoadVarInst(Address(fConst518, kStruct))))
	StoreVarInst(Address(fConst622, kStruct), BinopInst("/", BinopInst("+", Float(0.0004332272f), LoadVarInst(Address(fConst621, kStruct))), LoadVarInst(Address(fConst618, kStruct))))
	StoreVarInst(Address(fConst623, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004332272f), LoadVarInst(Address(fConst621, kStruct))), LoadVarInst(Address(fConst618, kStruct)))))
	StoreVarInst(Address(fConst624, kStruct), BinopInst("/", Float(0.51247865f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst625, kStruct), BinopInst("+", Float(0.6896214f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst626, kStruct), BinopInst("+", LoadVarInst(Address(fConst624, kStruct)), LoadVarInst(Address(fConst625, kStruct))))
	StoreVarInst(Address(fConst627, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.6896214f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst626, kStruct)))))
	StoreVarInst(Address(fConst628, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst625, kStruct)), LoadVarInst(Address(fConst624, kStruct))), LoadVarInst(Address(fConst626, kStruct))))
	StoreVarInst(Address(fConst629, kStruct), BinopInst("/", BinopInst("+", Float(7.6217313f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst626, kStruct))))
	StoreVarInst(Address(fConst630, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(7.6217313f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst626, kStruct)))))
	StoreVarInst(Address(fConst631, kStruct), BinopInst("/", Float(0.16840488f), LoadVarInst(Address(fConst517, kStruct))))
	StoreVarInst(Address(fConst632, kStruct), BinopInst("+", Float(1.0693583f), LoadVarInst(Address(fConst519, kStruct))))
	StoreVarInst(Address(fConst633, kStruct), BinopInst("+", LoadVarInst(Address(fConst631, kStruct)), LoadVarInst(Address(fConst632, kStruct))))
	StoreVarInst(Address(fConst634, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0693583f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst633, kStruct)))))
	StoreVarInst(Address(fConst635, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst632, kStruct)), LoadVarInst(Address(fConst631, kStruct))), LoadVarInst(Address(fConst633, kStruct))))
	StoreVarInst(Address(fConst636, kStruct), BinopInst("/", BinopInst("+", Float(53.53615f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst633, kStruct))))
	StoreVarInst(Address(fConst637, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(53.53615f), LoadVarInst(Address(fConst519, kStruct))), LoadVarInst(Address(fConst633, kStruct)))))
	StoreVarInst(Address(fConst638, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst639, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst640, kStruct), BinopInst("+", LoadVarInst(Address(fConst638, kStruct)), LoadVarInst(Address(fConst639, kStruct))))
	StoreVarInst(Address(fConst641, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst640, kStruct)))))
	StoreVarInst(Address(fConst642, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst639, kStruct)), LoadVarInst(Address(fConst638, kStruct))), LoadVarInst(Address(fConst640, kStruct))))
	StoreVarInst(Address(fConst643, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst644, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst643, kStruct))), LoadVarInst(Address(fConst640, kStruct))))
	StoreVarInst(Address(fConst645, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst643, kStruct))), LoadVarInst(Address(fConst640, kStruct)))))
	StoreVarInst(Address(fConst646, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst647, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst648, kStruct), BinopInst("+", LoadVarInst(Address(fConst646, kStruct)), LoadVarInst(Address(fConst647, kStruct))))
	StoreVarInst(Address(fConst649, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst648, kStruct)))))
	StoreVarInst(Address(fConst650, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst647, kStruct)), LoadVarInst(Address(fConst646, kStruct))), LoadVarInst(Address(fConst648, kStruct))))
	StoreVarInst(Address(fConst651, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst652, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst651, kStruct))), LoadVarInst(Address(fConst648, kStruct))))
	StoreVarInst(Address(fConst653, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst651, kStruct))), LoadVarInst(Address(fConst648, kStruct)))))
	StoreVarInst(Address(fConst654, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst123, kStruct))))
	StoreVarInst(Address(fConst655, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst125, kStruct))))
	StoreVarInst(Address(fConst656, kStruct), BinopInst("+", LoadVarInst(Address(fConst654, kStruct)), LoadVarInst(Address(fConst655, kStruct))))
	StoreVarInst(Address(fConst657, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst125, kStruct))), LoadVarInst(Address(fConst656, kStruct)))))
	StoreVarInst(Address(fConst658, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst655, kStruct)), LoadVarInst(Address(fConst654, kStruct))), LoadVarInst(Address(fConst656, kStruct))))
	StoreVarInst(Address(fConst659, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst124, kStruct))))
	StoreVarInst(Address(fConst660, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst659, kStruct))), LoadVarInst(Address(fConst656, kStruct))))
	StoreVarInst(Address(fConst661, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst659, kStruct))), LoadVarInst(Address(fConst656, kStruct)))))
	StoreVarInst(Address(fConst662, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst663, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst664, kStruct), BinopInst("+", LoadVarInst(Address(fConst662, kStruct)), LoadVarInst(Address(fConst663, kStruct))))
	StoreVarInst(Address(fConst665, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst664, kStruct)))))
	StoreVarInst(Address(fConst666, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst663, kStruct)), LoadVarInst(Address(fConst662, kStruct))), LoadVarInst(Address(fConst664, kStruct))))
	StoreVarInst(Address(fConst667, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst668, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst667, kStruct))), LoadVarInst(Address(fConst664, kStruct))))
	StoreVarInst(Address(fConst669, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst667, kStruct))), LoadVarInst(Address(fConst664, kStruct)))))
	StoreVarInst(Address(fConst670, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst671, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst672, kStruct), BinopInst("+", LoadVarInst(Address(fConst670, kStruct)), LoadVarInst(Address(fConst671, kStruct))))
	StoreVarInst(Address(fConst673, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst672, kStruct)))))
	StoreVarInst(Address(fConst674, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst671, kStruct)), LoadVarInst(Address(fConst670, kStruct))), LoadVarInst(Address(fConst672, kStruct))))
	StoreVarInst(Address(fConst675, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst676, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst675, kStruct))), LoadVarInst(Address(fConst672, kStruct))))
	StoreVarInst(Address(fConst677, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst675, kStruct))), LoadVarInst(Address(fConst672, kStruct)))))
	StoreVarInst(Address(fConst678, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst247, kStruct))))
	StoreVarInst(Address(fConst679, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst249, kStruct))))
	StoreVarInst(Address(fConst680, kStruct), BinopInst("+", LoadVarInst(Address(fConst678, kStruct)), LoadVarInst(Address(fConst679, kStruct))))
	StoreVarInst(Address(fConst681, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst249, kStruct))), LoadVarInst(Address(fConst680, kStruct)))))
	StoreVarInst(Address(fConst682, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst679, kStruct)), LoadVarInst(Address(fConst678, kStruct))), LoadVarInst(Address(fConst680, kStruct))))
	StoreVarInst(Address(fConst683, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst248, kStruct))))
	StoreVarInst(Address(fConst684, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst683, kStruct))), LoadVarInst(Address(fConst680, kStruct))))
	StoreVarInst(Address(fConst685, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst683, kStruct))), LoadVarInst(Address(fConst680, kStruct)))))
	StoreVarInst(Address(fConst686, kStruct), BinopInst("/", Float(3.1897273f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst687, kStruct), BinopInst("+", Float(4.0767817f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst688, kStruct), BinopInst("+", LoadVarInst(Address(fConst686, kStruct)), LoadVarInst(Address(fConst687, kStruct))))
	StoreVarInst(Address(fConst689, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(4.0767817f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst688, kStruct)))))
	StoreVarInst(Address(fConst690, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst687, kStruct)), LoadVarInst(Address(fConst686, kStruct))), LoadVarInst(Address(fConst688, kStruct))))
	StoreVarInst(Address(fConst691, kStruct), BinopInst("/", Float(0.0017661728f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst692, kStruct), BinopInst("/", BinopInst("+", Float(0.0004076782f), LoadVarInst(Address(fConst691, kStruct))), LoadVarInst(Address(fConst688, kStruct))))
	StoreVarInst(Address(fConst693, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.0004076782f), LoadVarInst(Address(fConst691, kStruct))), LoadVarInst(Address(fConst688, kStruct)))))
	StoreVarInst(Address(fConst694, kStruct), BinopInst("/", Float(0.74313045f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst695, kStruct), BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst696, kStruct), BinopInst("+", LoadVarInst(Address(fConst694, kStruct)), LoadVarInst(Address(fConst695, kStruct))))
	StoreVarInst(Address(fConst697, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst696, kStruct)))))
	StoreVarInst(Address(fConst698, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst695, kStruct)), LoadVarInst(Address(fConst694, kStruct))), LoadVarInst(Address(fConst696, kStruct))))
	StoreVarInst(Address(fConst699, kStruct), BinopInst("/", Float(11.0520525f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst700, kStruct), BinopInst("/", BinopInst("+", Float(1.4500711f), LoadVarInst(Address(fConst699, kStruct))), LoadVarInst(Address(fConst696, kStruct))))
	StoreVarInst(Address(fConst701, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.4500711f), LoadVarInst(Address(fConst699, kStruct))), LoadVarInst(Address(fConst696, kStruct)))))
	StoreVarInst(Address(fConst702, kStruct), BinopInst("/", Float(0.15748216f), LoadVarInst(Address(fConst371, kStruct))))
	StoreVarInst(Address(fConst703, kStruct), BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst373, kStruct))))
	StoreVarInst(Address(fConst704, kStruct), BinopInst("+", LoadVarInst(Address(fConst702, kStruct)), LoadVarInst(Address(fConst703, kStruct))))
	StoreVarInst(Address(fConst705, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst373, kStruct))), LoadVarInst(Address(fConst704, kStruct)))))
	StoreVarInst(Address(fConst706, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst703, kStruct)), LoadVarInst(Address(fConst702, kStruct))), LoadVarInst(Address(fConst704, kStruct))))
	StoreVarInst(Address(fConst707, kStruct), BinopInst("/", Float(50.06381f), LoadVarInst(Address(fConst372, kStruct))))
	StoreVarInst(Address(fConst708, kStruct), BinopInst("/", BinopInst("+", Float(0.9351402f), LoadVarInst(Address(fConst707, kStruct))), LoadVarInst(Address(fConst704, kStruct))))
	StoreVarInst(Address(fConst709, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(0.9351402f), LoadVarInst(Address(fConst707, kStruct))), LoadVarInst(Address(fConst704, kStruct)))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(5e+01f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.9f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(25.0f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(-2e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(1.0f)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(2.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Float(49.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.1f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(-0.1f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(0.1f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox2, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fCheckbox3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Float(5.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Float(1e+02f)))
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
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4096))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(4096))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(4096))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fVec28, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(4096))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(4096))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR10, kStruct)[LoadVarInst(Address(l47, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(4))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(3))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR11, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(3))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(3))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(3))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM0, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(3))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR26, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(3))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR25, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(3))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR24, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(3))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR23, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(3))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR22, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(3))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR21, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(3))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR20, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(3))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR19, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(3))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR18, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(3))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR17, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(3))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR16, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(3))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR15, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(3))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR14, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(3))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR13, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(3))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR12, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(2))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM2, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(3))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR41, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(3))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR40, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(3))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR39, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(3))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR38, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(3))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR37, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(3))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR36, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(3))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR35, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(3))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR34, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(3))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR33, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(3))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR32, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(3))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR31, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(3))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR30, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(3))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR29, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(3))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR28, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(3))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR27, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(2))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM3, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(3))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR56, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l99, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l99, kLoop)), Int32(3))
		StoreVarInst(Address(l99, kLoop), BinopInst("+", LoadVarInst(Address(l99, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR55, kStruct)[LoadVarInst(Address(l99, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l100, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l100, kLoop)), Int32(3))
		StoreVarInst(Address(l100, kLoop), BinopInst("+", LoadVarInst(Address(l100, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR54, kStruct)[LoadVarInst(Address(l100, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l101, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l101, kLoop)), Int32(3))
		StoreVarInst(Address(l101, kLoop), BinopInst("+", LoadVarInst(Address(l101, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR53, kStruct)[LoadVarInst(Address(l101, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l102, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l102, kLoop)), Int32(3))
		StoreVarInst(Address(l102, kLoop), BinopInst("+", LoadVarInst(Address(l102, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR52, kStruct)[LoadVarInst(Address(l102, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l103, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l103, kLoop)), Int32(3))
		StoreVarInst(Address(l103, kLoop), BinopInst("+", LoadVarInst(Address(l103, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR51, kStruct)[LoadVarInst(Address(l103, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l104, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l104, kLoop)), Int32(3))
		StoreVarInst(Address(l104, kLoop), BinopInst("+", LoadVarInst(Address(l104, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR50, kStruct)[LoadVarInst(Address(l104, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l105, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l105, kLoop)), Int32(3))
		StoreVarInst(Address(l105, kLoop), BinopInst("+", LoadVarInst(Address(l105, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR49, kStruct)[LoadVarInst(Address(l105, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l106, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l106, kLoop)), Int32(3))
		StoreVarInst(Address(l106, kLoop), BinopInst("+", LoadVarInst(Address(l106, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR48, kStruct)[LoadVarInst(Address(l106, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l107, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l107, kLoop)), Int32(3))
		StoreVarInst(Address(l107, kLoop), BinopInst("+", LoadVarInst(Address(l107, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR47, kStruct)[LoadVarInst(Address(l107, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l108, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l108, kLoop)), Int32(3))
		StoreVarInst(Address(l108, kLoop), BinopInst("+", LoadVarInst(Address(l108, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR46, kStruct)[LoadVarInst(Address(l108, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l109, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l109, kLoop)), Int32(3))
		StoreVarInst(Address(l109, kLoop), BinopInst("+", LoadVarInst(Address(l109, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR45, kStruct)[LoadVarInst(Address(l109, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l110, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l110, kLoop)), Int32(3))
		StoreVarInst(Address(l110, kLoop), BinopInst("+", LoadVarInst(Address(l110, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR44, kStruct)[LoadVarInst(Address(l110, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l111, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l111, kLoop)), Int32(3))
		StoreVarInst(Address(l111, kLoop), BinopInst("+", LoadVarInst(Address(l111, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR43, kStruct)[LoadVarInst(Address(l111, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l112, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l112, kLoop)), Int32(3))
		StoreVarInst(Address(l112, kLoop), BinopInst("+", LoadVarInst(Address(l112, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR42, kStruct)[LoadVarInst(Address(l112, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l113, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l113, kLoop)), Int32(2))
		StoreVarInst(Address(l113, kLoop), BinopInst("+", LoadVarInst(Address(l113, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM4, kStruct)[LoadVarInst(Address(l113, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l114, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l114, kLoop)), Int32(3))
		StoreVarInst(Address(l114, kLoop), BinopInst("+", LoadVarInst(Address(l114, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR59, kStruct)[LoadVarInst(Address(l114, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l115, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l115, kLoop)), Int32(3))
		StoreVarInst(Address(l115, kLoop), BinopInst("+", LoadVarInst(Address(l115, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR58, kStruct)[LoadVarInst(Address(l115, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l116, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l116, kLoop)), Int32(3))
		StoreVarInst(Address(l116, kLoop), BinopInst("+", LoadVarInst(Address(l116, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR57, kStruct)[LoadVarInst(Address(l116, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l117, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l117, kLoop)), Int32(2))
		StoreVarInst(Address(l117, kLoop), BinopInst("+", LoadVarInst(Address(l117, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM5, kStruct)[LoadVarInst(Address(l117, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l118, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l118, kLoop)), Int32(3))
		StoreVarInst(Address(l118, kLoop), BinopInst("+", LoadVarInst(Address(l118, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR62, kStruct)[LoadVarInst(Address(l118, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l119, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l119, kLoop)), Int32(3))
		StoreVarInst(Address(l119, kLoop), BinopInst("+", LoadVarInst(Address(l119, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR61, kStruct)[LoadVarInst(Address(l119, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l120, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l120, kLoop)), Int32(3))
		StoreVarInst(Address(l120, kLoop), BinopInst("+", LoadVarInst(Address(l120, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR60, kStruct)[LoadVarInst(Address(l120, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l121, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l121, kLoop)), Int32(2))
		StoreVarInst(Address(l121, kLoop), BinopInst("+", LoadVarInst(Address(l121, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM6, kStruct)[LoadVarInst(Address(l121, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l122, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l122, kLoop)), Int32(3))
		StoreVarInst(Address(l122, kLoop), BinopInst("+", LoadVarInst(Address(l122, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR65, kStruct)[LoadVarInst(Address(l122, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l123, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l123, kLoop)), Int32(3))
		StoreVarInst(Address(l123, kLoop), BinopInst("+", LoadVarInst(Address(l123, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR64, kStruct)[LoadVarInst(Address(l123, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l124, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l124, kLoop)), Int32(3))
		StoreVarInst(Address(l124, kLoop), BinopInst("+", LoadVarInst(Address(l124, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR63, kStruct)[LoadVarInst(Address(l124, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l125, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l125, kLoop)), Int32(2))
		StoreVarInst(Address(l125, kLoop), BinopInst("+", LoadVarInst(Address(l125, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM7, kStruct)[LoadVarInst(Address(l125, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l126, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l126, kLoop)), Int32(3))
		StoreVarInst(Address(l126, kLoop), BinopInst("+", LoadVarInst(Address(l126, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR71, kStruct)[LoadVarInst(Address(l126, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l127, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l127, kLoop)), Int32(3))
		StoreVarInst(Address(l127, kLoop), BinopInst("+", LoadVarInst(Address(l127, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR70, kStruct)[LoadVarInst(Address(l127, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l128, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l128, kLoop)), Int32(3))
		StoreVarInst(Address(l128, kLoop), BinopInst("+", LoadVarInst(Address(l128, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR69, kStruct)[LoadVarInst(Address(l128, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l129, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l129, kLoop)), Int32(3))
		StoreVarInst(Address(l129, kLoop), BinopInst("+", LoadVarInst(Address(l129, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR68, kStruct)[LoadVarInst(Address(l129, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l130, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l130, kLoop)), Int32(3))
		StoreVarInst(Address(l130, kLoop), BinopInst("+", LoadVarInst(Address(l130, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR67, kStruct)[LoadVarInst(Address(l130, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l131, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l131, kLoop)), Int32(3))
		StoreVarInst(Address(l131, kLoop), BinopInst("+", LoadVarInst(Address(l131, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR66, kStruct)[LoadVarInst(Address(l131, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l132, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l132, kLoop)), Int32(2))
		StoreVarInst(Address(l132, kLoop), BinopInst("+", LoadVarInst(Address(l132, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM8, kStruct)[LoadVarInst(Address(l132, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l133, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l133, kLoop)), Int32(3))
		StoreVarInst(Address(l133, kLoop), BinopInst("+", LoadVarInst(Address(l133, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR74, kStruct)[LoadVarInst(Address(l133, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l134, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l134, kLoop)), Int32(3))
		StoreVarInst(Address(l134, kLoop), BinopInst("+", LoadVarInst(Address(l134, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR73, kStruct)[LoadVarInst(Address(l134, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l135, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l135, kLoop)), Int32(3))
		StoreVarInst(Address(l135, kLoop), BinopInst("+", LoadVarInst(Address(l135, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR72, kStruct)[LoadVarInst(Address(l135, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l136, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l136, kLoop)), Int32(2))
		StoreVarInst(Address(l136, kLoop), BinopInst("+", LoadVarInst(Address(l136, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM9, kStruct)[LoadVarInst(Address(l136, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l137, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l137, kLoop)), Int32(3))
		StoreVarInst(Address(l137, kLoop), BinopInst("+", LoadVarInst(Address(l137, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR77, kStruct)[LoadVarInst(Address(l137, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l138, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l138, kLoop)), Int32(3))
		StoreVarInst(Address(l138, kLoop), BinopInst("+", LoadVarInst(Address(l138, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR76, kStruct)[LoadVarInst(Address(l138, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l139, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l139, kLoop)), Int32(3))
		StoreVarInst(Address(l139, kLoop), BinopInst("+", LoadVarInst(Address(l139, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR75, kStruct)[LoadVarInst(Address(l139, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l140, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l140, kLoop)), Int32(2))
		StoreVarInst(Address(l140, kLoop), BinopInst("+", LoadVarInst(Address(l140, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM10, kStruct)[LoadVarInst(Address(l140, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l141, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l141, kLoop)), Int32(3))
		StoreVarInst(Address(l141, kLoop), BinopInst("+", LoadVarInst(Address(l141, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR80, kStruct)[LoadVarInst(Address(l141, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l142, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l142, kLoop)), Int32(3))
		StoreVarInst(Address(l142, kLoop), BinopInst("+", LoadVarInst(Address(l142, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR79, kStruct)[LoadVarInst(Address(l142, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l143, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l143, kLoop)), Int32(3))
		StoreVarInst(Address(l143, kLoop), BinopInst("+", LoadVarInst(Address(l143, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR78, kStruct)[LoadVarInst(Address(l143, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l144, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l144, kLoop)), Int32(2))
		StoreVarInst(Address(l144, kLoop), BinopInst("+", LoadVarInst(Address(l144, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM11, kStruct)[LoadVarInst(Address(l144, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l145, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l145, kLoop)), Int32(3))
		StoreVarInst(Address(l145, kLoop), BinopInst("+", LoadVarInst(Address(l145, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR83, kStruct)[LoadVarInst(Address(l145, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l146, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l146, kLoop)), Int32(3))
		StoreVarInst(Address(l146, kLoop), BinopInst("+", LoadVarInst(Address(l146, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR82, kStruct)[LoadVarInst(Address(l146, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l147, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l147, kLoop)), Int32(3))
		StoreVarInst(Address(l147, kLoop), BinopInst("+", LoadVarInst(Address(l147, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR81, kStruct)[LoadVarInst(Address(l147, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l148, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l148, kLoop)), Int32(2))
		StoreVarInst(Address(l148, kLoop), BinopInst("+", LoadVarInst(Address(l148, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM12, kStruct)[LoadVarInst(Address(l148, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l149, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l149, kLoop)), Int32(3))
		StoreVarInst(Address(l149, kLoop), BinopInst("+", LoadVarInst(Address(l149, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR86, kStruct)[LoadVarInst(Address(l149, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l150, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l150, kLoop)), Int32(3))
		StoreVarInst(Address(l150, kLoop), BinopInst("+", LoadVarInst(Address(l150, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR85, kStruct)[LoadVarInst(Address(l150, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l151, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l151, kLoop)), Int32(3))
		StoreVarInst(Address(l151, kLoop), BinopInst("+", LoadVarInst(Address(l151, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR84, kStruct)[LoadVarInst(Address(l151, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l152, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l152, kLoop)), Int32(2))
		StoreVarInst(Address(l152, kLoop), BinopInst("+", LoadVarInst(Address(l152, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM13, kStruct)[LoadVarInst(Address(l152, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l153, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l153, kLoop)), Int32(3))
		StoreVarInst(Address(l153, kLoop), BinopInst("+", LoadVarInst(Address(l153, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR89, kStruct)[LoadVarInst(Address(l153, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l154, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l154, kLoop)), Int32(3))
		StoreVarInst(Address(l154, kLoop), BinopInst("+", LoadVarInst(Address(l154, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR88, kStruct)[LoadVarInst(Address(l154, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l155, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l155, kLoop)), Int32(3))
		StoreVarInst(Address(l155, kLoop), BinopInst("+", LoadVarInst(Address(l155, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR87, kStruct)[LoadVarInst(Address(l155, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l156, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l156, kLoop)), Int32(2))
		StoreVarInst(Address(l156, kLoop), BinopInst("+", LoadVarInst(Address(l156, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM14, kStruct)[LoadVarInst(Address(l156, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l157, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l157, kLoop)), Int32(3))
		StoreVarInst(Address(l157, kLoop), BinopInst("+", LoadVarInst(Address(l157, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR92, kStruct)[LoadVarInst(Address(l157, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l158, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l158, kLoop)), Int32(3))
		StoreVarInst(Address(l158, kLoop), BinopInst("+", LoadVarInst(Address(l158, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR91, kStruct)[LoadVarInst(Address(l158, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l159, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l159, kLoop)), Int32(3))
		StoreVarInst(Address(l159, kLoop), BinopInst("+", LoadVarInst(Address(l159, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR90, kStruct)[LoadVarInst(Address(l159, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l160, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l160, kLoop)), Int32(2))
		StoreVarInst(Address(l160, kLoop), BinopInst("+", LoadVarInst(Address(l160, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM15, kStruct)[LoadVarInst(Address(l160, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("int", iSlow1, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f)))))
	DeclareVarInst("int", iSlow2, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct))), Float(0.0f)))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fSlow3, kStack))), Float(0.999999f))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(4.0f), LoadVarInst(Address(fSlow4, kStack))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", Float(-49.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(88.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-1.2e+02f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))))))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(0.33333334f), LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("int", iSlow11, kStack, CastInst("int", BinopInst("+", Float(-1.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(4.0f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))))
	DeclareVarInst("int", iSlow12, kStack, BinopInst(">=", LoadVarInst(Address(iSlow11, kStack)), Int32(2)))
	DeclareVarInst("int", iSlow13, kStack, BinopInst(">=", LoadVarInst(Address(iSlow11, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), BinopInst("+", Float(-49.0f), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(88.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), FunCallInst("max_f", Float(0.001f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct)))))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow15, kStack))), LoadVarInst(Address(fSlow14, kStack))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst(">=", LoadVarInst(Address(iSlow11, kStack)), Int32(3)))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", Float(0.01f), FunCallInst("max_f", Float(-1e+01f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow18, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("+", Float(1.0f), BinopInst("*", Float(0.01f), FunCallInst("max_f", Float(-1e+01f), FunCallInst("min_f", Float(1e+01f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox2, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))
	DeclareVarInst("int", iSlow32, kStack, CastInst("int", CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox3, kStruct))), Float(0.0f)))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("min_f", Float(1.4127994f), BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow3, kStack)))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("*", Float(1.4142135f), LoadVarInst(Address(fSlow33, kStack))))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow33, kStack)))))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow34, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("+", Float(2.0f), LoadVarInst(Address(fSlow34, kStack))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("*", Float(1.998f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("+", Float(2.0f), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.4127994f), LoadVarInst(Address(fSlow3, kStack))))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(2.0f), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow42, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-6e+01f), FunCallInst("min_f", Float(2e+01f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst50, kStruct)), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("*", Float(0.44f), LoadVarInst(Address(fTemp0, kStack))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp1, kStack))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp2, kStack))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fIRM1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIRM1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(4.4e+02f), LoadVarInst(Address(fTemp5, kStack))))
			DeclareVarInst("float", fTemp7, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp6, kStack)))))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp7, kStack)))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp8, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp8, kStack)))))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp9, kStack))))
			DeclareVarInst("float", fTemp11, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp12, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp10, kStack))))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
			DeclareVarInst("float", fTemp13, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(2)])))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("-", LoadVarInst(Address(fTemp9, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp10, kStack))))))
			DeclareVarInst("float", fTemp15, kStack, NegInst(LoadVarInst(Address(fTemp14, kStack))))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp15, kStack)))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec2, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp14, kStack)))), LoadVarInst(Address(fTemp7, kStack))))
			StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp16, kStack)))
			DeclareVarInst("float", fTemp17, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(3)])))
			DeclareVarInst("float", fTemp18, kStack, BinopInst("*", LoadVarInst(Address(fTemp12, kStack)), BinopInst("+", Float(-2.0f), LoadVarInst(Address(fTemp12, kStack)))))
			StoreVarInst(Address(fVec4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp18, kStack)))
			DeclareVarInst("float", fTemp19, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp7, kStack))))
			StoreVarInst(Address(fVec5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp19, kStack)))
			DeclareVarInst("float", fTemp20, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fVec5, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp7, kStack))))
			StoreVarInst(Address(fVec6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp20, kStack)))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fTemp6, kStack))))
			DeclareVarInst("float", fTemp22, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp21, kStack)))))
			DeclareVarInst("float", fTemp23, kStack, BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp22, kStack)))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp23, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp23, kStack)))))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp24, kStack))))
			DeclareVarInst("float", fTemp26, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp25, kStack))))
			StoreVarInst(Address(fVec7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp26, kStack)))
			DeclareVarInst("float", fTemp27, kStack, BinopInst("-", LoadVarInst(Address(fTemp24, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp25, kStack))))))
			DeclareVarInst("float", fTemp28, kStack, NegInst(LoadVarInst(Address(fTemp27, kStack))))
			StoreVarInst(Address(fVec8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp28, kStack)))
			DeclareVarInst("float", fTemp29, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec8, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp27, kStack)))), LoadVarInst(Address(fTemp22, kStack))))
			StoreVarInst(Address(fVec9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp29, kStack)))
			DeclareVarInst("float", fTemp30, kStack, BinopInst("*", LoadVarInst(Address(fTemp26, kStack)), BinopInst("+", Float(-2.0f), LoadVarInst(Address(fTemp26, kStack)))))
			StoreVarInst(Address(fVec10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp30, kStack)))
			DeclareVarInst("float", fTemp31, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fVec10, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp22, kStack))))
			StoreVarInst(Address(fVec11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp31, kStack)))
			DeclareVarInst("float", fTemp32, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fVec11, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp22, kStack))))
			StoreVarInst(Address(fVec12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp32, kStack)))
			DeclareVarInst("float", fTemp33, kStack, BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fTemp6, kStack))))
			DeclareVarInst("float", fTemp34, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp33, kStack)))))
			DeclareVarInst("float", fTemp35, kStack, BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp34, kStack)))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp35, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp35, kStack)))))
			DeclareVarInst("float", fTemp36, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp37, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp36, kStack))))
			DeclareVarInst("float", fTemp38, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp37, kStack))))
			StoreVarInst(Address(fVec13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp38, kStack)))
			DeclareVarInst("float", fTemp39, kStack, BinopInst("-", LoadVarInst(Address(fTemp36, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp37, kStack))))))
			DeclareVarInst("float", fTemp40, kStack, NegInst(LoadVarInst(Address(fTemp39, kStack))))
			StoreVarInst(Address(fVec14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp40, kStack)))
			DeclareVarInst("float", fTemp41, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp39, kStack)))), LoadVarInst(Address(fTemp34, kStack))))
			StoreVarInst(Address(fVec15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp41, kStack)))
			DeclareVarInst("float", fTemp42, kStack, BinopInst("*", LoadVarInst(Address(fTemp38, kStack)), BinopInst("+", Float(-2.0f), LoadVarInst(Address(fTemp38, kStack)))))
			StoreVarInst(Address(fVec16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp42, kStack)))
			DeclareVarInst("float", fTemp43, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fVec16, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp34, kStack))))
			StoreVarInst(Address(fVec17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp43, kStack)))
			DeclareVarInst("float", fTemp44, kStack, BinopInst("/", BinopInst("-", LoadVarInst(Address(fTemp43, kStack)), LoadVarInst(Address(fVec17, kStruct)[Int32(1)])), LoadVarInst(Address(fTemp34, kStack))))
			StoreVarInst(Address(fVec18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp44, kStack)))
			DeclareVarInst("float", fTemp45, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp6, kStack)), Float(23.44895f)))
			DeclareVarInst("float", fTemp46, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp45, kStack))))))
			DeclareVarInst("int", iTemp47, kStack, CastInst("int", LoadVarInst(Address(fTemp46, kStack))))
			DeclareVarInst("float", fTemp48, kStack, CastInst("float", LoadVarInst(Address(iTemp47, kStack))))
			DeclareVarInst("float", fTemp49, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp45, kStack)))))
			DeclareVarInst("float", fTemp50, kStack, BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp49, kStack)))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp50, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp50, kStack)))))
			DeclareVarInst("float", fTemp51, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp52, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp51, kStack))))
			DeclareVarInst("float", fTemp53, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp52, kStack))))
			StoreVarInst(Address(fVec19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp53, kStack)))
			DeclareVarInst("float", fTemp54, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
			StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp54, kStack)))
			DeclareVarInst("float", fTemp55, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp47, kStack))), Int32(4095))]), BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp46, kStack))), LoadVarInst(Address(fTemp48, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fTemp48, kStack))), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp47, kStack)))), Int32(4095))]))))
			DeclareVarInst("float", fTemp56, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp21, kStack)), Float(23.44895f)))
			DeclareVarInst("float", fTemp57, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp56, kStack))))))
			DeclareVarInst("int", iTemp58, kStack, CastInst("int", LoadVarInst(Address(fTemp57, kStack))))
			DeclareVarInst("float", fTemp59, kStack, CastInst("float", LoadVarInst(Address(iTemp58, kStack))))
			DeclareVarInst("float", fTemp60, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp56, kStack)))))
			DeclareVarInst("float", fTemp61, kStack, BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp60, kStack)))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp61, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp61, kStack)))))
			DeclareVarInst("float", fTemp62, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp63, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp62, kStack))))
			DeclareVarInst("float", fTemp64, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp63, kStack))))
			StoreVarInst(Address(fVec21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp64, kStack)))
			DeclareVarInst("float", fTemp65, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp64, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
			StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp65, kStack)))
			DeclareVarInst("float", fTemp66, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp58, kStack))), Int32(4095))]), BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp57, kStack))), LoadVarInst(Address(fTemp59, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp57, kStack)), LoadVarInst(Address(fTemp59, kStack))), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp58, kStack)))), Int32(4095))]))))
			DeclareVarInst("float", fTemp67, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp33, kStack)), Float(23.44895f)))
			DeclareVarInst("float", fTemp68, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fTemp67, kStack))))))
			DeclareVarInst("int", iTemp69, kStack, CastInst("int", LoadVarInst(Address(fTemp68, kStack))))
			DeclareVarInst("float", fTemp70, kStack, CastInst("float", LoadVarInst(Address(iTemp69, kStack))))
			DeclareVarInst("float", fTemp71, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fTemp67, kStack)))))
			DeclareVarInst("float", fTemp72, kStack, BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fTemp71, kStack)))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp72, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp72, kStack)))))
			DeclareVarInst("float", fTemp73, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp74, kStack, BinopInst("+", Float(-1.0f), LoadVarInst(Address(fTemp73, kStack))))
			DeclareVarInst("float", fTemp75, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp74, kStack))))
			StoreVarInst(Address(fVec23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp75, kStack)))
			DeclareVarInst("float", fTemp76, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp75, kStack)), LoadVarInst(Address(fVec23, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp71, kStack))))
			StoreVarInst(Address(fVec24, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp76, kStack)))
			DeclareVarInst("float", fTemp77, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp76, kStack)), BinopInst("*", LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp69, kStack))), Int32(4095))]), BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp68, kStack))), LoadVarInst(Address(fTemp70, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp68, kStack)), LoadVarInst(Address(fTemp70, kStack))), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp69, kStack)))), Int32(4095))]))))
			DeclareVarInst("float", fTemp78, kStack, BinopInst("+", LoadVarInst(Address(fTemp55, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp78, kStack)))
			DeclareVarInst("float", fTemp79, kStack, BinopInst("+", LoadVarInst(Address(fTemp66, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp79, kStack)))
			DeclareVarInst("float", fTemp80, kStack, BinopInst("+", LoadVarInst(Address(fTemp77, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp80, kStack)))
			DeclareVarInst("float", fTemp81, kStack, BinopInst("+", LoadVarInst(Address(fSlow28, kStack)), BinopInst("*", Float(0.99f), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp81, kStack)))
			DeclareVarInst("float", fTemp82, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fTemp81, kStack))))
			DeclareVarInst("float", fTemp83, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp45, kStack)))))))
			DeclareVarInst("int", iTemp84, kStack, CastInst("int", LoadVarInst(Address(fTemp83, kStack))))
			DeclareVarInst("float", fTemp85, kStack, CastInst("float", LoadVarInst(Address(iTemp84, kStack))))
			DeclareVarInst("float", fTemp86, kStack, BinopInst("-", LoadVarInst(Address(fTemp83, kStack)), LoadVarInst(Address(fTemp85, kStack))))
			DeclareVarInst("float", fTemp87, kStack, BinopInst("-", LoadVarInst(Address(fTemp51, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp52, kStack))))))
			DeclareVarInst("float", fTemp88, kStack, NegInst(LoadVarInst(Address(fTemp87, kStack))))
			StoreVarInst(Address(fVec25, kStruct)[Int32(0)], LoadVarInst(Address(fTemp88, kStack)))
			DeclareVarInst("float", fTemp89, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec25, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp87, kStack)))), LoadVarInst(Address(fTemp49, kStack))))
			StoreVarInst(Address(fVec26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp89, kStack)))
			DeclareVarInst("float", fTemp90, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp89, kStack)), LoadVarInst(Address(fVec26, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp49, kStack))))
			StoreVarInst(Address(fVec27, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp90, kStack)))
			DeclareVarInst("int", iTemp91, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iTemp84, kStack))))
			DeclareVarInst("float", fTemp92, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp83, kStack))), LoadVarInst(Address(fTemp85, kStack))))
			DeclareVarInst("float", fTemp93, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp56, kStack)))))))
			DeclareVarInst("int", iTemp94, kStack, CastInst("int", LoadVarInst(Address(fTemp93, kStack))))
			DeclareVarInst("float", fTemp95, kStack, CastInst("float", LoadVarInst(Address(iTemp94, kStack))))
			DeclareVarInst("float", fTemp96, kStack, BinopInst("-", LoadVarInst(Address(fTemp93, kStack)), LoadVarInst(Address(fTemp95, kStack))))
			DeclareVarInst("float", fTemp97, kStack, BinopInst("-", LoadVarInst(Address(fTemp62, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp63, kStack))))))
			DeclareVarInst("float", fTemp98, kStack, NegInst(LoadVarInst(Address(fTemp97, kStack))))
			StoreVarInst(Address(fVec28, kStruct)[Int32(0)], LoadVarInst(Address(fTemp98, kStack)))
			DeclareVarInst("float", fTemp99, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec28, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp97, kStack)))), LoadVarInst(Address(fTemp60, kStack))))
			StoreVarInst(Address(fVec29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp99, kStack)))
			DeclareVarInst("float", fTemp100, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp99, kStack)), LoadVarInst(Address(fVec29, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp60, kStack))))
			StoreVarInst(Address(fVec30, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp100, kStack)))
			DeclareVarInst("int", iTemp101, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iTemp94, kStack))))
			DeclareVarInst("float", fTemp102, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp93, kStack))), LoadVarInst(Address(fTemp95, kStack))))
			DeclareVarInst("float", fTemp103, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), BinopInst("/", LoadVarInst(Address(fTemp82, kStack)), LoadVarInst(Address(fTemp67, kStack)))))))
			DeclareVarInst("int", iTemp104, kStack, CastInst("int", LoadVarInst(Address(fTemp103, kStack))))
			DeclareVarInst("float", fTemp105, kStack, CastInst("float", LoadVarInst(Address(iTemp104, kStack))))
			DeclareVarInst("float", fTemp106, kStack, BinopInst("-", LoadVarInst(Address(fTemp103, kStack)), LoadVarInst(Address(fTemp105, kStack))))
			DeclareVarInst("float", fTemp107, kStack, BinopInst("-", LoadVarInst(Address(fTemp73, kStack)), BinopInst("+", Float(1.0f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp74, kStack))))))
			DeclareVarInst("float", fTemp108, kStack, NegInst(LoadVarInst(Address(fTemp107, kStack))))
			StoreVarInst(Address(fVec31, kStruct)[Int32(0)], LoadVarInst(Address(fTemp108, kStack)))
			DeclareVarInst("float", fTemp109, kStack, BinopInst("/", NegInst(BinopInst("+", LoadVarInst(Address(fVec31, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp107, kStack)))), LoadVarInst(Address(fTemp71, kStack))))
			StoreVarInst(Address(fVec32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp109, kStack)))
			DeclareVarInst("float", fTemp110, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp109, kStack)), LoadVarInst(Address(fVec32, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp71, kStack))))
			StoreVarInst(Address(fVec33, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp110, kStack)))
			DeclareVarInst("int", iTemp111, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iTemp104, kStack))))
			DeclareVarInst("float", fTemp112, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp103, kStack))), LoadVarInst(Address(fTemp105, kStack))))
			DeclareVarInst("int", iTemp113, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR10, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR10, kStruct)[Int32(0)], LoadVarInst(Address(iTemp113, kStack)))
			DeclareVarInst("float", fTemp114, kStack, BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(iTemp113, kStack))), BinopInst("*", Float(2.494956f), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))), BinopInst("*", Float(-2.0172658f), LoadVarInst(Address(fIIR9, kStruct)[Int32(2)]))), BinopInst("*", Float(0.5221894f), LoadVarInst(Address(fIIR9, kStruct)[Int32(3)]))))
			StoreVarInst(Address(fIIR9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp114, kStack)))
			StoreVarInst(Address(fVec34, kStruct)[Int32(0)], BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp114, kStack))))
			DeclareVarInst("float", fTemp115, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp4, kStack))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(Address(iSlow12, kStack)) Select2Inst(LoadVarInst(Address(iSlow17, kStack)) BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fVec6, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp7, kStack)))) BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp16, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp7, kStack))))) Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp7, kStack)))) LoadVarInst(Address(fTemp10, kStack)))), Select2Inst(LoadVarInst(Address(iSlow12, kStack)) Select2Inst(LoadVarInst(Address(iSlow17, kStack)) BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp32, kStack)), LoadVarInst(Address(fVec12, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp22, kStack)))) BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fVec9, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp22, kStack))))) Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), LoadVarInst(Address(fVec7, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp22, kStack)))) LoadVarInst(Address(fTemp25, kStack))))), Select2Inst(LoadVarInst(Address(iSlow12, kStack)) Select2Inst(LoadVarInst(Address(iSlow17, kStack)) BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp44, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp34, kStack)))) BinopInst("*", LoadVarInst(Address(fConst12, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp13, kStack)), BinopInst("-", LoadVarInst(Address(fTemp41, kStack)), LoadVarInst(Address(fVec15, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp34, kStack))))) Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), BinopInst("/", BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("-", LoadVarInst(Address(fTemp38, kStack)), LoadVarInst(Address(fVec13, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp34, kStack)))) LoadVarInst(Address(fTemp37, kStack)))))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp55, kStack)), LoadVarInst(Address(fTemp66, kStack))), LoadVarInst(Address(fTemp77, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fTemp78, kStack))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fTemp79, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fTemp80, kStack)))))))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp90, kStack)), BinopInst("*", LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp84, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp92, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp91, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp100, kStack)), BinopInst("*", LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp94, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp102, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp96, kStack)), LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp101, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp110, kStack)), BinopInst("*", LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp104, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp112, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp106, kStack)), LoadVarInst(Address(fVec33, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp111, kStack))), Int32(4095))]))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp54, kStack)), BinopInst("*", LoadVarInst(Address(fTemp92, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp84, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp86, kStack)), LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp91, kStack))), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp65, kStack)), BinopInst("*", LoadVarInst(Address(fTemp102, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp94, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp96, kStack)), LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp101, kStack))), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp76, kStack)), BinopInst("*", LoadVarInst(Address(fTemp112, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp104, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fTemp106, kStack)), LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp111, kStack))), Int32(4095))])))))))), BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.049922034f), LoadVarInst(Address(fVec34, kStruct)[Int32(0)])), BinopInst("*", Float(-0.095993534f), LoadVarInst(Address(fVec34, kStruct)[Int32(1)]))), BinopInst("*", Float(0.0506127f), LoadVarInst(Address(fVec34, kStruct)[Int32(2)]))), BinopInst("*", Float(-0.004408786f), LoadVarInst(Address(fVec34, kStruct)[Int32(3)]))))))))
			DeclareVarInst("float", fTemp116, kStack, Select2Inst(LoadVarInst(Address(iSlow1, kStack)) Float(0.0f) LoadVarInst(Address(fTemp115, kStack))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp3, kStack))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), LoadVarInst(Address(fTemp116, kStack))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("*", FunCallInst("mydsp_faustpower4_f", LoadVarInst(Address(fTemp2, kStack))), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp117, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1e+04f), LoadVarInst(Address(fTemp1, kStack)))))))
			DeclareVarInst("float", fTemp118, kStack, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp117, kStack)))))
			DeclareVarInst("float", fTemp119, kStack, BinopInst("-", LoadVarInst(Address(fTemp118, kStack)), LoadVarInst(Address(fSlow35, kStack))))
			DeclareVarInst("float", fTemp120, kStack, BinopInst("/", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp117, kStack))))
			DeclareVarInst("float", fTemp121, kStack, BinopInst("+", LoadVarInst(Address(fTemp118, kStack)), LoadVarInst(Address(fSlow35, kStack))))
			DeclareVarInst("float", fTemp122, kStack, BinopInst("-", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp121, kStack))))
			DeclareVarInst("float", fTemp123, kStack, BinopInst("-", LoadVarInst(Address(fTemp120, kStack)), LoadVarInst(Address(fTemp122, kStack))))
			DeclareVarInst("float", fTemp124, kStack, BinopInst("/", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fTemp117, kStack))))
			DeclareVarInst("float", fTemp125, kStack, BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp121, kStack))))
			DeclareVarInst("float", fTemp126, kStack, BinopInst("+", LoadVarInst(Address(fTemp124, kStack)), LoadVarInst(Address(fTemp125, kStack))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp116, kStack)), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("-", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp119, kStack))))), BinopInst("*", LoadVarInst(Address(fRec12, kStruct)[Int32(2)]), BinopInst("-", LoadVarInst(Address(fTemp125, kStack)), LoadVarInst(Address(fTemp124, kStack))))), LoadVarInst(Address(fTemp126, kStack)))))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("-", BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))), LoadVarInst(Address(fRec12, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp126, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), NegInst(BinopInst("+", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp119, kStack)))))), BinopInst("*", LoadVarInst(Address(fRec11, kStruct)[Int32(2)]), NegInst(BinopInst("+", LoadVarInst(Address(fTemp120, kStack)), LoadVarInst(Address(fTemp122, kStack)))))), LoadVarInst(Address(fTemp123, kStack)))))
			DeclareVarInst("float", fTemp127, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), FunCallInst("max_f", LoadVarInst(Address(fTemp1, kStack)), Float(2e+01f)))))
			DeclareVarInst("float", fTemp128, kStack, BinopInst("/", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp127, kStack))))
			DeclareVarInst("float", fTemp129, kStack, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp127, kStack)))))
			DeclareVarInst("float", fTemp130, kStack, BinopInst("+", LoadVarInst(Address(fTemp129, kStack)), LoadVarInst(Address(fSlow40, kStack))))
			DeclareVarInst("float", fTemp131, kStack, BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp130, kStack))))
			DeclareVarInst("float", fTemp132, kStack, BinopInst("-", LoadVarInst(Address(fTemp131, kStack)), LoadVarInst(Address(fTemp128, kStack))))
			DeclareVarInst("float", fTemp133, kStack, BinopInst("+", LoadVarInst(Address(fTemp128, kStack)), LoadVarInst(Address(fTemp131, kStack))))
			DeclareVarInst("float", fTemp134, kStack, BinopInst("/", LoadVarInst(Address(fTemp132, kStack)), LoadVarInst(Address(fTemp133, kStack))))
			DeclareVarInst("float", fTemp135, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp134, kStack)))))
			DeclareVarInst("float", fTemp136, kStack, BinopInst("-", LoadVarInst(Address(fTemp129, kStack)), LoadVarInst(Address(fSlow40, kStack))))
			DeclareVarInst("float", fTemp137, kStack, BinopInst("-", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp136, kStack))))
			DeclareVarInst("float", fTemp138, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp137, kStack)), BinopInst("*", LoadVarInst(Address(fTemp133, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp134, kStack)))))))))
			DeclareVarInst("float", fTemp139, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp135, kStack)))))
			DeclareVarInst("float", fTemp140, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp139, kStack)))))
			DeclareVarInst("float", fTemp141, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp116, kStack)), LoadVarInst(Address(fTemp140, kStack))), BinopInst("*", LoadVarInst(Address(fTemp135, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp142, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp138, kStack)))))
			DeclareVarInst("float", fTemp143, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp142, kStack)))))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp141, kStack)), LoadVarInst(Address(fTemp143, kStack))), BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp138, kStack)))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp138, kStack)), LoadVarInst(Address(fTemp141, kStack))), BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp143, kStack)))))
			DeclareVarInst("float", fTemp144, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp133, kStack))))
			DeclareVarInst("float", fTemp145, kStack, BinopInst("/", LoadVarInst(Address(fTemp137, kStack)), LoadVarInst(Address(fTemp144, kStack))))
			DeclareVarInst("float", fTemp146, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp133, kStack))))
			DeclareVarInst("float", fTemp147, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fTemp138, kStack))))
			DeclareVarInst("float", fTemp148, kStack, BinopInst("+", BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp116, kStack)), LoadVarInst(Address(fTemp135, kStack))), BinopInst("*", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp140, kStack)))), LoadVarInst(Address(fTemp133, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec14, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fTemp146, kStack)), LoadVarInst(Address(fTemp145, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp146, kStack)), BinopInst("*", LoadVarInst(Address(fTemp147, kStack)), BinopInst("-", LoadVarInst(Address(fTemp145, kStack)), LoadVarInst(Address(fTemp146, kStack))))), BinopInst("/", LoadVarInst(Address(fTemp132, kStack)), LoadVarInst(Address(fTemp144, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp142, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp139, kStack))))))
			DeclareVarInst("float", fTemp149, kStack, BinopInst("/", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fTemp127, kStack))))
			DeclareVarInst("float", fTemp150, kStack, BinopInst("-", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp130, kStack))))
			DeclareVarInst("float", fTemp151, kStack, NegInst(BinopInst("+", LoadVarInst(Address(fTemp149, kStack)), LoadVarInst(Address(fTemp150, kStack)))))
			DeclareVarInst("float", fTemp152, kStack, BinopInst("-", LoadVarInst(Address(fTemp149, kStack)), LoadVarInst(Address(fTemp150, kStack))))
			DeclareVarInst("float", fTemp153, kStack, BinopInst("/", LoadVarInst(Address(fTemp151, kStack)), LoadVarInst(Address(fTemp152, kStack))))
			DeclareVarInst("float", fTemp154, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), LoadVarInst(Address(fTemp153, kStack)))))
			DeclareVarInst("float", fTemp155, kStack, NegInst(BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp136, kStack)))))
			DeclareVarInst("float", fTemp156, kStack, FunCallInst("max_f", Float(-0.9999f), FunCallInst("min_f", Float(0.9999f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(Address(fTemp155, kStack)), BinopInst("*", LoadVarInst(Address(fTemp152, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp153, kStack)))))))))
			DeclareVarInst("float", fTemp157, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp154, kStack)))))
			DeclareVarInst("float", fTemp158, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp157, kStack)))))
			DeclareVarInst("float", fTemp159, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp148, kStack)), LoadVarInst(Address(fTemp158, kStack))), BinopInst("*", LoadVarInst(Address(fTemp154, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp160, kStack, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp156, kStack)))))
			DeclareVarInst("float", fTemp161, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fTemp160, kStack)))))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp159, kStack)), LoadVarInst(Address(fTemp161, kStack))), BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp156, kStack)))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp156, kStack)), LoadVarInst(Address(fTemp159, kStack))), BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp161, kStack)))))
			DeclareVarInst("float", fTemp162, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp152, kStack))))
			DeclareVarInst("float", fTemp163, kStack, BinopInst("/", LoadVarInst(Address(fTemp155, kStack)), LoadVarInst(Address(fTemp162, kStack))))
			DeclareVarInst("float", fTemp164, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fTemp152, kStack))))
			DeclareVarInst("float", fTemp165, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fTemp156, kStack))))
			DeclareVarInst("float", fTemp166, kStack, BinopInst("+", LoadVarInst(Address(fSlow42, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR11, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp166, kStack)))
			DeclareVarInst("float", fTemp167, kStack, Select2Inst(LoadVarInst(Address(iSlow1, kStack)) LoadVarInst(Address(fTemp115, kStack)) BinopInst("*", Select2Inst(LoadVarInst(Address(iSlow2, kStack)) Select2Inst(LoadVarInst(Address(iSlow32, kStack)) BinopInst("+", BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp148, kStack)), LoadVarInst(Address(fTemp154, kStack))), BinopInst("*", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp158, kStack)))), LoadVarInst(Address(fTemp152, kStack))), BinopInst("/", BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(Address(fRec16, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fTemp164, kStack)), LoadVarInst(Address(fTemp163, kStack))))), BinopInst("/", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp164, kStack)), BinopInst("*", LoadVarInst(Address(fTemp165, kStack)), BinopInst("-", LoadVarInst(Address(fTemp163, kStack)), LoadVarInst(Address(fTemp164, kStack))))), BinopInst("/", LoadVarInst(Address(fTemp151, kStack)), LoadVarInst(Address(fTemp162, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp160, kStack))))), FunCallInst("sqrtf", LoadVarInst(Address(fTemp157, kStack))))) BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))), LoadVarInst(Address(fRec11, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp123, kStack)))) LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp166, kStack))))))
			DeclareVarInst("float", fTemp168, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp167, kStack)), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp168, kStack)))
			DeclareVarInst("float", fTemp169, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst33, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst37, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst38, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp169, kStack)))
			DeclareVarInst("float", fTemp170, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst41, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst46, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp170, kStack)))
			DeclareVarInst("float", fTemp171, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst48, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp172, kStack, BinopInst("+", LoadVarInst(Address(fTemp171, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM0, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp171, kStack))))))
			StoreVarInst(Address(fIRM0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp172, kStack)))
			StoreVarInst(Address(fVbargraph0, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp172, kStack)))))))
			DeclareVarInst("float", fTemp173, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp167, kStack)), BinopInst("*", LoadVarInst(Address(fConst54, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst55, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp173, kStack)))
			DeclareVarInst("float", fTemp174, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst57, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst58, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst57, kStruct)), LoadVarInst(Address(fIIR26, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst62, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst63, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR25, kStruct)[Int32(0)], LoadVarInst(Address(fTemp174, kStack)))
			DeclareVarInst("float", fTemp175, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst64, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst65, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst64, kStruct)), LoadVarInst(Address(fIIR25, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst69, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst70, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR24, kStruct)[Int32(0)], LoadVarInst(Address(fTemp175, kStack)))
			DeclareVarInst("float", fTemp176, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst71, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst72, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst71, kStruct)), LoadVarInst(Address(fIIR24, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp177, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp176, kStack)), BinopInst("*", LoadVarInst(Address(fConst79, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst80, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp177, kStack)))
			DeclareVarInst("float", fTemp178, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst82, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst83, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst82, kStruct)), LoadVarInst(Address(fIIR23, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst87, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst88, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR22, kStruct)[Int32(0)], LoadVarInst(Address(fTemp178, kStack)))
			DeclareVarInst("float", fTemp179, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst89, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst90, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst89, kStruct)), LoadVarInst(Address(fIIR22, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst94, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst95, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp179, kStack)))
			DeclareVarInst("float", fTemp180, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst96, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst97, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst96, kStruct)), LoadVarInst(Address(fIIR21, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp181, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp180, kStack)), BinopInst("*", LoadVarInst(Address(fConst104, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst105, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR20, kStruct)[Int32(0)], LoadVarInst(Address(fTemp181, kStack)))
			DeclareVarInst("float", fTemp182, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst107, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst108, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst107, kStruct)), LoadVarInst(Address(fIIR20, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst112, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst113, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp182, kStack)))
			DeclareVarInst("float", fTemp183, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst114, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst115, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst114, kStruct)), LoadVarInst(Address(fIIR19, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst119, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst120, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp183, kStack)))
			DeclareVarInst("float", fTemp184, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst122, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst121, kStruct)), LoadVarInst(Address(fIIR18, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp185, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp184, kStack)), BinopInst("*", LoadVarInst(Address(fConst129, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst130, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp185, kStack)))
			DeclareVarInst("float", fTemp186, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst132, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst133, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst132, kStruct)), LoadVarInst(Address(fIIR17, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst137, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst138, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp186, kStack)))
			DeclareVarInst("float", fTemp187, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst139, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst140, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst139, kStruct)), LoadVarInst(Address(fIIR16, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst144, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst145, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp187, kStack)))
			DeclareVarInst("float", fTemp188, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst146, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst147, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst146, kStruct)), LoadVarInst(Address(fIIR15, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp189, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp188, kStack)), BinopInst("*", LoadVarInst(Address(fConst154, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst155, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp189, kStack)))
			DeclareVarInst("float", fTemp190, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst158, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst157, kStruct)), LoadVarInst(Address(fIIR14, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst162, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst163, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp190, kStack)))
			DeclareVarInst("float", fTemp191, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst165, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst166, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst165, kStruct)), LoadVarInst(Address(fIIR13, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst170, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst171, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp191, kStack)))
			DeclareVarInst("float", fTemp192, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst173, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst174, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst173, kStruct)), LoadVarInst(Address(fIIR12, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp193, kStack, BinopInst("+", LoadVarInst(Address(fTemp192, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM2, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp192, kStack))))))
			StoreVarInst(Address(fIRM2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp193, kStack)))
			StoreVarInst(Address(fVbargraph1, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp193, kStack)))))))
			DeclareVarInst("float", fTemp194, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp188, kStack)), BinopInst("*", LoadVarInst(Address(fConst178, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst179, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR41, kStruct)[Int32(0)], LoadVarInst(Address(fTemp194, kStack)))
			DeclareVarInst("float", fTemp195, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst181, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst182, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst181, kStruct)), LoadVarInst(Address(fIIR41, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst186, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst187, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR40, kStruct)[Int32(0)], LoadVarInst(Address(fTemp195, kStack)))
			DeclareVarInst("float", fTemp196, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst189, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst188, kStruct)), LoadVarInst(Address(fIIR40, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst193, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst194, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR39, kStruct)[Int32(0)], LoadVarInst(Address(fTemp196, kStack)))
			DeclareVarInst("float", fTemp197, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst196, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst195, kStruct)), LoadVarInst(Address(fIIR39, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp198, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp197, kStack)), BinopInst("*", LoadVarInst(Address(fConst203, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst204, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR38, kStruct)[Int32(0)], LoadVarInst(Address(fTemp198, kStack)))
			DeclareVarInst("float", fTemp199, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst206, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst207, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst206, kStruct)), LoadVarInst(Address(fIIR38, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst211, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst212, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR37, kStruct)[Int32(0)], LoadVarInst(Address(fTemp199, kStack)))
			DeclareVarInst("float", fTemp200, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst213, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst214, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst213, kStruct)), LoadVarInst(Address(fIIR37, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst218, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst219, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR36, kStruct)[Int32(0)], LoadVarInst(Address(fTemp200, kStack)))
			DeclareVarInst("float", fTemp201, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst220, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst221, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst220, kStruct)), LoadVarInst(Address(fIIR36, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp202, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp201, kStack)), BinopInst("*", LoadVarInst(Address(fConst228, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst229, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR35, kStruct)[Int32(0)], LoadVarInst(Address(fTemp202, kStack)))
			DeclareVarInst("float", fTemp203, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst231, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst232, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst231, kStruct)), LoadVarInst(Address(fIIR35, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst236, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst237, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR34, kStruct)[Int32(0)], LoadVarInst(Address(fTemp203, kStack)))
			DeclareVarInst("float", fTemp204, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst239, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst238, kStruct)), LoadVarInst(Address(fIIR34, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst243, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst244, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR33, kStruct)[Int32(0)], LoadVarInst(Address(fTemp204, kStack)))
			DeclareVarInst("float", fTemp205, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst245, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst246, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst245, kStruct)), LoadVarInst(Address(fIIR33, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp206, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp205, kStack)), BinopInst("*", LoadVarInst(Address(fConst253, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst254, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp206, kStack)))
			DeclareVarInst("float", fTemp207, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst256, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst257, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst256, kStruct)), LoadVarInst(Address(fIIR32, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst261, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst262, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR31, kStruct)[Int32(0)], LoadVarInst(Address(fTemp207, kStack)))
			DeclareVarInst("float", fTemp208, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst263, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst264, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst263, kStruct)), LoadVarInst(Address(fIIR31, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst268, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst269, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR30, kStruct)[Int32(0)], LoadVarInst(Address(fTemp208, kStack)))
			DeclareVarInst("float", fTemp209, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst271, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst270, kStruct)), LoadVarInst(Address(fIIR30, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp210, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp209, kStack)), BinopInst("*", LoadVarInst(Address(fConst278, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst279, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp210, kStack)))
			DeclareVarInst("float", fTemp211, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst281, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst282, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst281, kStruct)), LoadVarInst(Address(fIIR29, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst286, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst287, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR28, kStruct)[Int32(0)], LoadVarInst(Address(fTemp211, kStack)))
			DeclareVarInst("float", fTemp212, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst289, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst290, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst289, kStruct)), LoadVarInst(Address(fIIR28, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst294, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst295, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR27, kStruct)[Int32(0)], LoadVarInst(Address(fTemp212, kStack)))
			DeclareVarInst("float", fTemp213, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst297, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst298, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst297, kStruct)), LoadVarInst(Address(fIIR27, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp214, kStack, BinopInst("+", LoadVarInst(Address(fTemp213, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM3, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp213, kStack))))))
			StoreVarInst(Address(fIRM3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp214, kStack)))
			StoreVarInst(Address(fVbargraph2, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp214, kStack)))))))
			DeclareVarInst("float", fTemp215, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp209, kStack)), BinopInst("*", LoadVarInst(Address(fConst302, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst303, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR56, kStruct)[Int32(0)], LoadVarInst(Address(fTemp215, kStack)))
			DeclareVarInst("float", fTemp216, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst306, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst305, kStruct)), LoadVarInst(Address(fIIR56, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst310, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst311, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR55, kStruct)[Int32(0)], LoadVarInst(Address(fTemp216, kStack)))
			DeclareVarInst("float", fTemp217, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst313, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst312, kStruct)), LoadVarInst(Address(fIIR55, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst317, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst318, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR54, kStruct)[Int32(0)], LoadVarInst(Address(fTemp217, kStack)))
			DeclareVarInst("float", fTemp218, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst319, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst320, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst319, kStruct)), LoadVarInst(Address(fIIR54, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp219, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp218, kStack)), BinopInst("*", LoadVarInst(Address(fConst327, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst328, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR53, kStruct)[Int32(0)], LoadVarInst(Address(fTemp219, kStack)))
			DeclareVarInst("float", fTemp220, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst330, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst331, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst330, kStruct)), LoadVarInst(Address(fIIR53, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst335, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst336, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR52, kStruct)[Int32(0)], LoadVarInst(Address(fTemp220, kStack)))
			DeclareVarInst("float", fTemp221, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst337, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst338, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst337, kStruct)), LoadVarInst(Address(fIIR52, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst342, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst343, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR51, kStruct)[Int32(0)], LoadVarInst(Address(fTemp221, kStack)))
			DeclareVarInst("float", fTemp222, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst345, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst344, kStruct)), LoadVarInst(Address(fIIR51, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp223, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp222, kStack)), BinopInst("*", LoadVarInst(Address(fConst352, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst353, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR50, kStruct)[Int32(0)], LoadVarInst(Address(fTemp223, kStack)))
			DeclareVarInst("float", fTemp224, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst355, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst356, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst355, kStruct)), LoadVarInst(Address(fIIR50, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst360, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst361, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR49, kStruct)[Int32(0)], LoadVarInst(Address(fTemp224, kStack)))
			DeclareVarInst("float", fTemp225, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst362, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst363, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst362, kStruct)), LoadVarInst(Address(fIIR49, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst367, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst368, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR48, kStruct)[Int32(0)], LoadVarInst(Address(fTemp225, kStack)))
			DeclareVarInst("float", fTemp226, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst369, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst370, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst369, kStruct)), LoadVarInst(Address(fIIR48, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp227, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp226, kStack)), BinopInst("*", LoadVarInst(Address(fConst377, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst378, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR47, kStruct)[Int32(0)], LoadVarInst(Address(fTemp227, kStack)))
			DeclareVarInst("float", fTemp228, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst380, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst381, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst380, kStruct)), LoadVarInst(Address(fIIR47, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst385, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst386, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR46, kStruct)[Int32(0)], LoadVarInst(Address(fTemp228, kStack)))
			DeclareVarInst("float", fTemp229, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst388, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst387, kStruct)), LoadVarInst(Address(fIIR46, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst392, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst393, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR45, kStruct)[Int32(0)], LoadVarInst(Address(fTemp229, kStack)))
			DeclareVarInst("float", fTemp230, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst395, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst394, kStruct)), LoadVarInst(Address(fIIR45, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp231, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp230, kStack)), BinopInst("*", LoadVarInst(Address(fConst402, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst403, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR44, kStruct)[Int32(0)], LoadVarInst(Address(fTemp231, kStack)))
			DeclareVarInst("float", fTemp232, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst405, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst406, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst405, kStruct)), LoadVarInst(Address(fIIR44, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst410, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst411, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR43, kStruct)[Int32(0)], LoadVarInst(Address(fTemp232, kStack)))
			DeclareVarInst("float", fTemp233, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst413, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst414, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst413, kStruct)), LoadVarInst(Address(fIIR43, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst418, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst419, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR42, kStruct)[Int32(0)], LoadVarInst(Address(fTemp233, kStack)))
			DeclareVarInst("float", fTemp234, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst421, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst422, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst421, kStruct)), LoadVarInst(Address(fIIR42, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp235, kStack, BinopInst("+", LoadVarInst(Address(fTemp234, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM4, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp234, kStack))))))
			StoreVarInst(Address(fIRM4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp235, kStack)))
			StoreVarInst(Address(fVbargraph3, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp235, kStack)))))))
			DeclareVarInst("float", fTemp236, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp176, kStack)), BinopInst("*", LoadVarInst(Address(fConst426, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst427, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR59, kStruct)[Int32(0)], LoadVarInst(Address(fTemp236, kStack)))
			DeclareVarInst("float", fTemp237, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst430, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst429, kStruct)), LoadVarInst(Address(fIIR59, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst434, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst435, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR58, kStruct)[Int32(0)], LoadVarInst(Address(fTemp237, kStack)))
			DeclareVarInst("float", fTemp238, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst437, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst438, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst437, kStruct)), LoadVarInst(Address(fIIR58, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst442, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst443, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR57, kStruct)[Int32(0)], LoadVarInst(Address(fTemp238, kStack)))
			DeclareVarInst("float", fTemp239, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst445, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst446, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst445, kStruct)), LoadVarInst(Address(fIIR57, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp240, kStack, BinopInst("+", LoadVarInst(Address(fTemp239, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM5, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp239, kStack))))))
			StoreVarInst(Address(fIRM5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp240, kStack)))
			StoreVarInst(Address(fVbargraph4, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp240, kStack)))))))
			DeclareVarInst("float", fTemp241, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp197, kStack)), BinopInst("*", LoadVarInst(Address(fConst450, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst451, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR62, kStruct)[Int32(0)], LoadVarInst(Address(fTemp241, kStack)))
			DeclareVarInst("float", fTemp242, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst453, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst454, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst453, kStruct)), LoadVarInst(Address(fIIR62, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst458, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst459, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR61, kStruct)[Int32(0)], LoadVarInst(Address(fTemp242, kStack)))
			DeclareVarInst("float", fTemp243, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst462, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst461, kStruct)), LoadVarInst(Address(fIIR61, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst466, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst467, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR60, kStruct)[Int32(0)], LoadVarInst(Address(fTemp243, kStack)))
			DeclareVarInst("float", fTemp244, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst469, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst470, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst469, kStruct)), LoadVarInst(Address(fIIR60, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp245, kStack, BinopInst("+", LoadVarInst(Address(fTemp244, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM6, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp244, kStack))))))
			StoreVarInst(Address(fIRM6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp245, kStack)))
			StoreVarInst(Address(fVbargraph5, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp245, kStack)))))))
			DeclareVarInst("float", fTemp246, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp218, kStack)), BinopInst("*", LoadVarInst(Address(fConst474, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst475, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR65, kStruct)[Int32(0)], LoadVarInst(Address(fTemp246, kStack)))
			DeclareVarInst("float", fTemp247, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst477, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst478, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst477, kStruct)), LoadVarInst(Address(fIIR65, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst482, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst483, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR64, kStruct)[Int32(0)], LoadVarInst(Address(fTemp247, kStack)))
			DeclareVarInst("float", fTemp248, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst485, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst486, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst485, kStruct)), LoadVarInst(Address(fIIR64, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst490, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst491, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR63, kStruct)[Int32(0)], LoadVarInst(Address(fTemp248, kStack)))
			DeclareVarInst("float", fTemp249, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst493, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst494, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst493, kStruct)), LoadVarInst(Address(fIIR63, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp250, kStack, BinopInst("+", LoadVarInst(Address(fTemp249, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM7, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp249, kStack))))))
			StoreVarInst(Address(fIRM7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp250, kStack)))
			StoreVarInst(Address(fVbargraph6, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp250, kStack)))))))
			DeclareVarInst("float", fTemp251, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp230, kStack)), BinopInst("*", LoadVarInst(Address(fConst498, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst499, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR71, kStruct)[Int32(0)], LoadVarInst(Address(fTemp251, kStack)))
			DeclareVarInst("float", fTemp252, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst502, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst501, kStruct)), LoadVarInst(Address(fIIR71, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst506, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst507, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR70, kStruct)[Int32(0)], LoadVarInst(Address(fTemp252, kStack)))
			DeclareVarInst("float", fTemp253, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst509, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst508, kStruct)), LoadVarInst(Address(fIIR70, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst513, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst514, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR69, kStruct)[Int32(0)], LoadVarInst(Address(fTemp253, kStack)))
			DeclareVarInst("float", fTemp254, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst515, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst516, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst515, kStruct)), LoadVarInst(Address(fIIR69, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp255, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp254, kStack)), BinopInst("*", LoadVarInst(Address(fConst523, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst524, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR68, kStruct)[Int32(0)], LoadVarInst(Address(fTemp255, kStack)))
			DeclareVarInst("float", fTemp256, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst526, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst527, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst526, kStruct)), LoadVarInst(Address(fIIR68, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst531, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst532, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR67, kStruct)[Int32(0)], LoadVarInst(Address(fTemp256, kStack)))
			DeclareVarInst("float", fTemp257, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst535, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst534, kStruct)), LoadVarInst(Address(fIIR67, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst539, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst540, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR66, kStruct)[Int32(0)], LoadVarInst(Address(fTemp257, kStack)))
			DeclareVarInst("float", fTemp258, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst542, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst543, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst542, kStruct)), LoadVarInst(Address(fIIR66, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp259, kStack, BinopInst("+", LoadVarInst(Address(fTemp258, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM8, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp258, kStack))))))
			StoreVarInst(Address(fIRM8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp259, kStack)))
			StoreVarInst(Address(fVbargraph7, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp259, kStack)))))))
			DeclareVarInst("float", fTemp260, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp180, kStack)), BinopInst("*", LoadVarInst(Address(fConst547, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst548, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR74, kStruct)[Int32(0)], LoadVarInst(Address(fTemp260, kStack)))
			DeclareVarInst("float", fTemp261, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst550, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst551, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst550, kStruct)), LoadVarInst(Address(fIIR74, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst555, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst556, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR73, kStruct)[Int32(0)], LoadVarInst(Address(fTemp261, kStack)))
			DeclareVarInst("float", fTemp262, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst558, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst559, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst558, kStruct)), LoadVarInst(Address(fIIR73, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst563, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst564, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR72, kStruct)[Int32(0)], LoadVarInst(Address(fTemp262, kStack)))
			DeclareVarInst("float", fTemp263, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst566, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst567, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst566, kStruct)), LoadVarInst(Address(fIIR72, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp264, kStack, BinopInst("+", LoadVarInst(Address(fTemp263, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM9, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp263, kStack))))))
			StoreVarInst(Address(fIRM9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp264, kStack)))
			StoreVarInst(Address(fVbargraph8, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp264, kStack)))))))
			DeclareVarInst("float", fTemp265, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp201, kStack)), BinopInst("*", LoadVarInst(Address(fConst571, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst572, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR77, kStruct)[Int32(0)], LoadVarInst(Address(fTemp265, kStack)))
			DeclareVarInst("float", fTemp266, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst574, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst575, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst574, kStruct)), LoadVarInst(Address(fIIR77, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst579, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst580, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR76, kStruct)[Int32(0)], LoadVarInst(Address(fTemp266, kStack)))
			DeclareVarInst("float", fTemp267, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst582, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst583, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst582, kStruct)), LoadVarInst(Address(fIIR76, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst587, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst588, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR75, kStruct)[Int32(0)], LoadVarInst(Address(fTemp267, kStack)))
			DeclareVarInst("float", fTemp268, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst590, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst591, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst590, kStruct)), LoadVarInst(Address(fIIR75, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp269, kStack, BinopInst("+", LoadVarInst(Address(fTemp268, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM10, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp268, kStack))))))
			StoreVarInst(Address(fIRM10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp269, kStack)))
			StoreVarInst(Address(fVbargraph9, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp269, kStack)))))))
			DeclareVarInst("float", fTemp270, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp222, kStack)), BinopInst("*", LoadVarInst(Address(fConst595, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst596, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR80, kStruct)[Int32(0)], LoadVarInst(Address(fTemp270, kStack)))
			DeclareVarInst("float", fTemp271, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst598, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst599, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst598, kStruct)), LoadVarInst(Address(fIIR80, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst603, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst604, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR79, kStruct)[Int32(0)], LoadVarInst(Address(fTemp271, kStack)))
			DeclareVarInst("float", fTemp272, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst606, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst607, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst606, kStruct)), LoadVarInst(Address(fIIR79, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst611, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst612, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR78, kStruct)[Int32(0)], LoadVarInst(Address(fTemp272, kStack)))
			DeclareVarInst("float", fTemp273, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst614, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst615, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst614, kStruct)), LoadVarInst(Address(fIIR78, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp274, kStack, BinopInst("+", LoadVarInst(Address(fTemp273, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM11, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp273, kStack))))))
			StoreVarInst(Address(fIRM11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp274, kStack)))
			StoreVarInst(Address(fVbargraph10, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp274, kStack)))))))
			DeclareVarInst("float", fTemp275, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp254, kStack)), BinopInst("*", LoadVarInst(Address(fConst619, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst620, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR83, kStruct)[Int32(0)], LoadVarInst(Address(fTemp275, kStack)))
			DeclareVarInst("float", fTemp276, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst622, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst623, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst622, kStruct)), LoadVarInst(Address(fIIR83, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst627, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst628, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR82, kStruct)[Int32(0)], LoadVarInst(Address(fTemp276, kStack)))
			DeclareVarInst("float", fTemp277, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst629, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst630, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst629, kStruct)), LoadVarInst(Address(fIIR82, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst634, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst635, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR81, kStruct)[Int32(0)], LoadVarInst(Address(fTemp277, kStack)))
			DeclareVarInst("float", fTemp278, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst636, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst637, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst636, kStruct)), LoadVarInst(Address(fIIR81, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp279, kStack, BinopInst("+", LoadVarInst(Address(fTemp278, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM12, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp278, kStack))))))
			StoreVarInst(Address(fIRM12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp279, kStack)))
			StoreVarInst(Address(fVbargraph11, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp279, kStack)))))))
			DeclareVarInst("float", fTemp280, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp184, kStack)), BinopInst("*", LoadVarInst(Address(fConst641, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst642, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR86, kStruct)[Int32(0)], LoadVarInst(Address(fTemp280, kStack)))
			DeclareVarInst("float", fTemp281, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst644, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst645, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst644, kStruct)), LoadVarInst(Address(fIIR86, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst649, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst650, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR85, kStruct)[Int32(0)], LoadVarInst(Address(fTemp281, kStack)))
			DeclareVarInst("float", fTemp282, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst652, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst653, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst652, kStruct)), LoadVarInst(Address(fIIR85, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst657, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst658, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR84, kStruct)[Int32(0)], LoadVarInst(Address(fTemp282, kStack)))
			DeclareVarInst("float", fTemp283, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst660, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst661, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst660, kStruct)), LoadVarInst(Address(fIIR84, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp284, kStack, BinopInst("+", LoadVarInst(Address(fTemp283, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM13, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp283, kStack))))))
			StoreVarInst(Address(fIRM13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp284, kStack)))
			StoreVarInst(Address(fVbargraph12, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp284, kStack)))))))
			DeclareVarInst("float", fTemp285, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp205, kStack)), BinopInst("*", LoadVarInst(Address(fConst665, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst666, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR89, kStruct)[Int32(0)], LoadVarInst(Address(fTemp285, kStack)))
			DeclareVarInst("float", fTemp286, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst668, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst669, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst668, kStruct)), LoadVarInst(Address(fIIR89, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst673, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst674, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR88, kStruct)[Int32(0)], LoadVarInst(Address(fTemp286, kStack)))
			DeclareVarInst("float", fTemp287, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst676, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst677, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst676, kStruct)), LoadVarInst(Address(fIIR88, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst681, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst682, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR87, kStruct)[Int32(0)], LoadVarInst(Address(fTemp287, kStack)))
			DeclareVarInst("float", fTemp288, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst684, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst685, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst684, kStruct)), LoadVarInst(Address(fIIR87, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp289, kStack, BinopInst("+", LoadVarInst(Address(fTemp288, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp288, kStack))))))
			StoreVarInst(Address(fIRM14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp289, kStack)))
			StoreVarInst(Address(fVbargraph13, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp289, kStack)))))))
			DeclareVarInst("float", fTemp290, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp226, kStack)), BinopInst("*", LoadVarInst(Address(fConst689, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst690, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR92, kStruct)[Int32(0)], LoadVarInst(Address(fTemp290, kStack)))
			DeclareVarInst("float", fTemp291, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst692, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst693, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst692, kStruct)), LoadVarInst(Address(fIIR92, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst697, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst698, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR91, kStruct)[Int32(0)], LoadVarInst(Address(fTemp291, kStack)))
			DeclareVarInst("float", fTemp292, kStack, BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst700, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst701, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst700, kStruct)), LoadVarInst(Address(fIIR91, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fConst705, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst706, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR90, kStruct)[Int32(0)], LoadVarInst(Address(fTemp292, kStack)))
			DeclareVarInst("float", fTemp293, kStack, FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst708, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst709, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst708, kStruct)), LoadVarInst(Address(fIIR90, kStruct)[Int32(2)])))))
			DeclareVarInst("float", fTemp294, kStack, BinopInst("+", LoadVarInst(Address(fTemp293, kStack)), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), BinopInst("-", LoadVarInst(Address(fIRM15, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp293, kStack))))))
			StoreVarInst(Address(fIRM15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp294, kStack)))
			StoreVarInst(Address(fVbargraph14, kStruct), CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(2e+01f), FunCallInst("log10f", LoadVarInst(Address(fTemp294, kStack)))))))
			DeclareVarInst("float", fTemp295, kStack, LoadVarInst(Address(fTemp167, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp295, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp295, kStack))))
			ForLoopInst 
				DeclareVarInst("int", j0, kLoop, Int32(3))
				BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
				StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(iVec0, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM1, kStruct)[Int32(1)], LoadVarInst(Address(fIRM1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec4, kStruct)[Int32(1)], LoadVarInst(Address(fVec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec5, kStruct)[Int32(1)], LoadVarInst(Address(fVec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec6, kStruct)[Int32(1)], LoadVarInst(Address(fVec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec7, kStruct)[Int32(1)], LoadVarInst(Address(fVec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec8, kStruct)[Int32(1)], LoadVarInst(Address(fVec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec9, kStruct)[Int32(1)], LoadVarInst(Address(fVec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec10, kStruct)[Int32(1)], LoadVarInst(Address(fVec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec11, kStruct)[Int32(1)], LoadVarInst(Address(fVec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec12, kStruct)[Int32(1)], LoadVarInst(Address(fVec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec13, kStruct)[Int32(1)], LoadVarInst(Address(fVec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec14, kStruct)[Int32(1)], LoadVarInst(Address(fVec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec15, kStruct)[Int32(1)], LoadVarInst(Address(fVec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec16, kStruct)[Int32(1)], LoadVarInst(Address(fVec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec17, kStruct)[Int32(1)], LoadVarInst(Address(fVec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec18, kStruct)[Int32(1)], LoadVarInst(Address(fVec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec19, kStruct)[Int32(1)], LoadVarInst(Address(fVec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec21, kStruct)[Int32(1)], LoadVarInst(Address(fVec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec23, kStruct)[Int32(1)], LoadVarInst(Address(fVec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec25, kStruct)[Int32(1)], LoadVarInst(Address(fVec25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec26, kStruct)[Int32(1)], LoadVarInst(Address(fVec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec28, kStruct)[Int32(1)], LoadVarInst(Address(fVec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec29, kStruct)[Int32(1)], LoadVarInst(Address(fVec29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec31, kStruct)[Int32(1)], LoadVarInst(Address(fVec31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec32, kStruct)[Int32(1)], LoadVarInst(Address(fVec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(iIIR10, kStruct)[Int32(1)], LoadVarInst(Address(iIIR10, kStruct)[Int32(0)]))
			ForLoopInst 
				DeclareVarInst("int", j1, kLoop, Int32(3))
				BinopInst(">", LoadVarInst(Address(j1, kLoop)), Int32(0))
				StoreVarInst(Address(j1, kLoop), BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(j1, kLoop))], LoadVarInst(Address(fIIR9, kStruct)[BinopInst("-", LoadVarInst(Address(j1, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
			ForLoopInst 
				DeclareVarInst("int", j2, kLoop, Int32(3))
				BinopInst(">", LoadVarInst(Address(j2, kLoop)), Int32(0))
				StoreVarInst(Address(j2, kLoop), BinopInst("-", LoadVarInst(Address(j2, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(fVec34, kStruct)[LoadVarInst(Address(j2, kLoop))], LoadVarInst(Address(fVec34, kStruct)[BinopInst("-", LoadVarInst(Address(j2, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(2)], LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR11, kStruct)[Int32(1)], LoadVarInst(Address(fIIR11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(2)], LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(2)], LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM0, kStruct)[Int32(1)], LoadVarInst(Address(fIRM0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR26, kStruct)[Int32(2)], LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR26, kStruct)[Int32(1)], LoadVarInst(Address(fIIR26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR25, kStruct)[Int32(2)], LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR25, kStruct)[Int32(1)], LoadVarInst(Address(fIIR25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR24, kStruct)[Int32(2)], LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR24, kStruct)[Int32(1)], LoadVarInst(Address(fIIR24, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR23, kStruct)[Int32(2)], LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR23, kStruct)[Int32(1)], LoadVarInst(Address(fIIR23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR22, kStruct)[Int32(2)], LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR22, kStruct)[Int32(1)], LoadVarInst(Address(fIIR22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR21, kStruct)[Int32(2)], LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR21, kStruct)[Int32(1)], LoadVarInst(Address(fIIR21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR20, kStruct)[Int32(2)], LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR20, kStruct)[Int32(1)], LoadVarInst(Address(fIIR20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR19, kStruct)[Int32(2)], LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR19, kStruct)[Int32(1)], LoadVarInst(Address(fIIR19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR18, kStruct)[Int32(2)], LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR18, kStruct)[Int32(1)], LoadVarInst(Address(fIIR18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR17, kStruct)[Int32(2)], LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR17, kStruct)[Int32(1)], LoadVarInst(Address(fIIR17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR16, kStruct)[Int32(2)], LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR16, kStruct)[Int32(1)], LoadVarInst(Address(fIIR16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR15, kStruct)[Int32(2)], LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR15, kStruct)[Int32(1)], LoadVarInst(Address(fIIR15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR14, kStruct)[Int32(2)], LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR14, kStruct)[Int32(1)], LoadVarInst(Address(fIIR14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR13, kStruct)[Int32(2)], LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR13, kStruct)[Int32(1)], LoadVarInst(Address(fIIR13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR12, kStruct)[Int32(2)], LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR12, kStruct)[Int32(1)], LoadVarInst(Address(fIIR12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM2, kStruct)[Int32(1)], LoadVarInst(Address(fIRM2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR41, kStruct)[Int32(2)], LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR41, kStruct)[Int32(1)], LoadVarInst(Address(fIIR41, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR40, kStruct)[Int32(2)], LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR40, kStruct)[Int32(1)], LoadVarInst(Address(fIIR40, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR39, kStruct)[Int32(2)], LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR39, kStruct)[Int32(1)], LoadVarInst(Address(fIIR39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR38, kStruct)[Int32(2)], LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR38, kStruct)[Int32(1)], LoadVarInst(Address(fIIR38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR37, kStruct)[Int32(2)], LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR37, kStruct)[Int32(1)], LoadVarInst(Address(fIIR37, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR36, kStruct)[Int32(2)], LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR36, kStruct)[Int32(1)], LoadVarInst(Address(fIIR36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR35, kStruct)[Int32(2)], LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR35, kStruct)[Int32(1)], LoadVarInst(Address(fIIR35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR34, kStruct)[Int32(2)], LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR34, kStruct)[Int32(1)], LoadVarInst(Address(fIIR34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR33, kStruct)[Int32(2)], LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR33, kStruct)[Int32(1)], LoadVarInst(Address(fIIR33, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR32, kStruct)[Int32(2)], LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR32, kStruct)[Int32(1)], LoadVarInst(Address(fIIR32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR31, kStruct)[Int32(2)], LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR31, kStruct)[Int32(1)], LoadVarInst(Address(fIIR31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR30, kStruct)[Int32(2)], LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR30, kStruct)[Int32(1)], LoadVarInst(Address(fIIR30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR29, kStruct)[Int32(2)], LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR29, kStruct)[Int32(1)], LoadVarInst(Address(fIIR29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR28, kStruct)[Int32(2)], LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR28, kStruct)[Int32(1)], LoadVarInst(Address(fIIR28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR27, kStruct)[Int32(2)], LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR27, kStruct)[Int32(1)], LoadVarInst(Address(fIIR27, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM3, kStruct)[Int32(1)], LoadVarInst(Address(fIRM3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR56, kStruct)[Int32(2)], LoadVarInst(Address(fIIR56, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR56, kStruct)[Int32(1)], LoadVarInst(Address(fIIR56, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR55, kStruct)[Int32(2)], LoadVarInst(Address(fIIR55, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR55, kStruct)[Int32(1)], LoadVarInst(Address(fIIR55, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR54, kStruct)[Int32(2)], LoadVarInst(Address(fIIR54, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR54, kStruct)[Int32(1)], LoadVarInst(Address(fIIR54, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR53, kStruct)[Int32(2)], LoadVarInst(Address(fIIR53, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR53, kStruct)[Int32(1)], LoadVarInst(Address(fIIR53, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR52, kStruct)[Int32(2)], LoadVarInst(Address(fIIR52, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR52, kStruct)[Int32(1)], LoadVarInst(Address(fIIR52, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR51, kStruct)[Int32(2)], LoadVarInst(Address(fIIR51, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR51, kStruct)[Int32(1)], LoadVarInst(Address(fIIR51, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR50, kStruct)[Int32(2)], LoadVarInst(Address(fIIR50, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR50, kStruct)[Int32(1)], LoadVarInst(Address(fIIR50, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR49, kStruct)[Int32(2)], LoadVarInst(Address(fIIR49, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR49, kStruct)[Int32(1)], LoadVarInst(Address(fIIR49, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR48, kStruct)[Int32(2)], LoadVarInst(Address(fIIR48, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR48, kStruct)[Int32(1)], LoadVarInst(Address(fIIR48, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR47, kStruct)[Int32(2)], LoadVarInst(Address(fIIR47, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR47, kStruct)[Int32(1)], LoadVarInst(Address(fIIR47, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR46, kStruct)[Int32(2)], LoadVarInst(Address(fIIR46, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR46, kStruct)[Int32(1)], LoadVarInst(Address(fIIR46, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR45, kStruct)[Int32(2)], LoadVarInst(Address(fIIR45, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR45, kStruct)[Int32(1)], LoadVarInst(Address(fIIR45, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR44, kStruct)[Int32(2)], LoadVarInst(Address(fIIR44, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR44, kStruct)[Int32(1)], LoadVarInst(Address(fIIR44, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR43, kStruct)[Int32(2)], LoadVarInst(Address(fIIR43, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR43, kStruct)[Int32(1)], LoadVarInst(Address(fIIR43, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR42, kStruct)[Int32(2)], LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR42, kStruct)[Int32(1)], LoadVarInst(Address(fIIR42, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM4, kStruct)[Int32(1)], LoadVarInst(Address(fIRM4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR59, kStruct)[Int32(2)], LoadVarInst(Address(fIIR59, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR59, kStruct)[Int32(1)], LoadVarInst(Address(fIIR59, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR58, kStruct)[Int32(2)], LoadVarInst(Address(fIIR58, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR58, kStruct)[Int32(1)], LoadVarInst(Address(fIIR58, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR57, kStruct)[Int32(2)], LoadVarInst(Address(fIIR57, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR57, kStruct)[Int32(1)], LoadVarInst(Address(fIIR57, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM5, kStruct)[Int32(1)], LoadVarInst(Address(fIRM5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR62, kStruct)[Int32(2)], LoadVarInst(Address(fIIR62, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR62, kStruct)[Int32(1)], LoadVarInst(Address(fIIR62, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR61, kStruct)[Int32(2)], LoadVarInst(Address(fIIR61, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR61, kStruct)[Int32(1)], LoadVarInst(Address(fIIR61, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR60, kStruct)[Int32(2)], LoadVarInst(Address(fIIR60, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR60, kStruct)[Int32(1)], LoadVarInst(Address(fIIR60, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM6, kStruct)[Int32(1)], LoadVarInst(Address(fIRM6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR65, kStruct)[Int32(2)], LoadVarInst(Address(fIIR65, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR65, kStruct)[Int32(1)], LoadVarInst(Address(fIIR65, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR64, kStruct)[Int32(2)], LoadVarInst(Address(fIIR64, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR64, kStruct)[Int32(1)], LoadVarInst(Address(fIIR64, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR63, kStruct)[Int32(2)], LoadVarInst(Address(fIIR63, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR63, kStruct)[Int32(1)], LoadVarInst(Address(fIIR63, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM7, kStruct)[Int32(1)], LoadVarInst(Address(fIRM7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR71, kStruct)[Int32(2)], LoadVarInst(Address(fIIR71, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR71, kStruct)[Int32(1)], LoadVarInst(Address(fIIR71, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR70, kStruct)[Int32(2)], LoadVarInst(Address(fIIR70, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR70, kStruct)[Int32(1)], LoadVarInst(Address(fIIR70, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR69, kStruct)[Int32(2)], LoadVarInst(Address(fIIR69, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR69, kStruct)[Int32(1)], LoadVarInst(Address(fIIR69, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR68, kStruct)[Int32(2)], LoadVarInst(Address(fIIR68, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR68, kStruct)[Int32(1)], LoadVarInst(Address(fIIR68, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR67, kStruct)[Int32(2)], LoadVarInst(Address(fIIR67, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR67, kStruct)[Int32(1)], LoadVarInst(Address(fIIR67, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR66, kStruct)[Int32(2)], LoadVarInst(Address(fIIR66, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR66, kStruct)[Int32(1)], LoadVarInst(Address(fIIR66, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM8, kStruct)[Int32(1)], LoadVarInst(Address(fIRM8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR74, kStruct)[Int32(2)], LoadVarInst(Address(fIIR74, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR74, kStruct)[Int32(1)], LoadVarInst(Address(fIIR74, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR73, kStruct)[Int32(2)], LoadVarInst(Address(fIIR73, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR73, kStruct)[Int32(1)], LoadVarInst(Address(fIIR73, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR72, kStruct)[Int32(2)], LoadVarInst(Address(fIIR72, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR72, kStruct)[Int32(1)], LoadVarInst(Address(fIIR72, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM9, kStruct)[Int32(1)], LoadVarInst(Address(fIRM9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR77, kStruct)[Int32(2)], LoadVarInst(Address(fIIR77, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR77, kStruct)[Int32(1)], LoadVarInst(Address(fIIR77, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR76, kStruct)[Int32(2)], LoadVarInst(Address(fIIR76, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR76, kStruct)[Int32(1)], LoadVarInst(Address(fIIR76, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR75, kStruct)[Int32(2)], LoadVarInst(Address(fIIR75, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR75, kStruct)[Int32(1)], LoadVarInst(Address(fIIR75, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM10, kStruct)[Int32(1)], LoadVarInst(Address(fIRM10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR80, kStruct)[Int32(2)], LoadVarInst(Address(fIIR80, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR80, kStruct)[Int32(1)], LoadVarInst(Address(fIIR80, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR79, kStruct)[Int32(2)], LoadVarInst(Address(fIIR79, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR79, kStruct)[Int32(1)], LoadVarInst(Address(fIIR79, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR78, kStruct)[Int32(2)], LoadVarInst(Address(fIIR78, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR78, kStruct)[Int32(1)], LoadVarInst(Address(fIIR78, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM11, kStruct)[Int32(1)], LoadVarInst(Address(fIRM11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR83, kStruct)[Int32(2)], LoadVarInst(Address(fIIR83, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR83, kStruct)[Int32(1)], LoadVarInst(Address(fIIR83, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR82, kStruct)[Int32(2)], LoadVarInst(Address(fIIR82, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR82, kStruct)[Int32(1)], LoadVarInst(Address(fIIR82, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR81, kStruct)[Int32(2)], LoadVarInst(Address(fIIR81, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR81, kStruct)[Int32(1)], LoadVarInst(Address(fIIR81, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM12, kStruct)[Int32(1)], LoadVarInst(Address(fIRM12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR86, kStruct)[Int32(2)], LoadVarInst(Address(fIIR86, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR86, kStruct)[Int32(1)], LoadVarInst(Address(fIIR86, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR85, kStruct)[Int32(2)], LoadVarInst(Address(fIIR85, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR85, kStruct)[Int32(1)], LoadVarInst(Address(fIIR85, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR84, kStruct)[Int32(2)], LoadVarInst(Address(fIIR84, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR84, kStruct)[Int32(1)], LoadVarInst(Address(fIIR84, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM13, kStruct)[Int32(1)], LoadVarInst(Address(fIRM13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR89, kStruct)[Int32(2)], LoadVarInst(Address(fIIR89, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR89, kStruct)[Int32(1)], LoadVarInst(Address(fIIR89, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR88, kStruct)[Int32(2)], LoadVarInst(Address(fIIR88, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR88, kStruct)[Int32(1)], LoadVarInst(Address(fIIR88, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR87, kStruct)[Int32(2)], LoadVarInst(Address(fIIR87, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR87, kStruct)[Int32(1)], LoadVarInst(Address(fIIR87, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM14, kStruct)[Int32(1)], LoadVarInst(Address(fIRM14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR92, kStruct)[Int32(2)], LoadVarInst(Address(fIIR92, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR92, kStruct)[Int32(1)], LoadVarInst(Address(fIIR92, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR91, kStruct)[Int32(2)], LoadVarInst(Address(fIIR91, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR91, kStruct)[Int32(1)], LoadVarInst(Address(fIIR91, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR90, kStruct)[Int32(2)], LoadVarInst(Address(fIIR90, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR90, kStruct)[Int32(1)], LoadVarInst(Address(fIIR90, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIRM15, kStruct)[Int32(1)], LoadVarInst(Address(fIRM15, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 24 bytes
Heap size real = 102876 bytes
Total heap size = 102908 bytes
Stack size in compute = 200 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec20 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR9 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec34 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR26 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR25 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst70 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR24 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst71 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst78 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst79 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst80 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR23 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst81 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst82 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst83 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst84 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst85 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst86 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst87 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst88 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR22 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst89 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst90 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst91 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst92 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst93 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst94 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst95 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst96 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst97 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst98 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst99 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst100 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst101 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst102 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst103 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst104 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst105 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst106 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst107 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst108 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst109 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst110 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst111 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst112 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst113 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst114 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst115 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst116 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst117 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst118 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst119 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst120 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR17 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst131 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst132 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst133 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst134 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst135 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst136 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst137 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst138 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR16 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst139 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst140 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst141 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst142 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst143 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst144 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst145 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR15 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst146 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst147 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst148 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst149 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst150 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst151 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst152 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst153 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst154 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst155 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR14 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst156 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst157 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst158 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst159 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst160 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst161 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst162 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst163 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR13 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst164 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst165 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst166 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst167 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst168 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst169 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst170 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst171 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst172 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst173 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst174 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst175 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst176 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst177 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst178 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst179 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR41 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst180 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst181 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst182 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst183 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst184 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst185 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst186 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst187 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR40 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst188 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst189 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst190 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst191 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst192 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst193 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst194 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR39 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR38 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst205 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst206 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst207 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst208 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst209 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst210 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst211 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst212 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR37 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst213 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst214 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst215 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst216 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst217 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst218 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst219 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR36 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst220 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst221 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst222 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst223 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst224 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst225 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst226 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst227 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst228 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst229 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR35 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst230 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst231 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst232 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst233 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst234 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst235 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst236 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst237 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR34 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst238 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst239 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst240 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst241 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst242 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst243 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst244 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR33 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst245 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst246 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst247 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst248 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst249 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst250 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst251 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst252 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst253 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst254 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR32 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst255 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst256 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst257 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst258 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst259 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst260 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst261 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst262 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR31 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst263 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst264 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst265 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst266 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst267 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst268 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst269 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR30 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR29 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst280 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst281 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst282 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst283 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst284 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst285 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst286 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst287 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR28 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst288 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst289 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst290 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst291 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst292 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst293 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst294 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst295 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR27 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst296 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst297 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst298 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst299 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst300 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst301 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst302 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst303 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR56 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst304 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst305 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst306 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst307 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst308 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst309 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst310 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst311 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR55 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst312 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst313 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst314 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst315 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst316 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst317 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst318 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR54 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst319 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst320 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst321 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst322 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst323 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst324 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst325 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst326 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst327 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst328 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR53 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst329 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst330 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst331 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst332 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst333 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst334 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst335 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst336 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR52 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst337 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst338 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst339 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst340 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst341 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst342 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst343 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR51 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR50 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst354 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst355 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst356 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst357 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst358 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst359 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst360 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst361 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR49 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst362 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst363 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst364 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst365 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst366 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst367 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst368 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR48 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst369 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst370 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst371 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst372 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst373 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst374 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst375 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst376 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst377 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst378 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR47 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst379 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst380 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst381 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst382 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst383 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst384 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst385 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst386 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR46 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst387 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst388 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst389 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst390 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst391 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst392 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst393 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR45 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst394 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst395 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst396 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst397 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst398 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst399 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst400 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst401 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst402 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst403 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR44 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst404 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst405 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst406 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst407 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst408 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst409 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst410 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst411 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR43 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst412 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst413 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst414 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst415 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst416 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst417 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst418 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst419 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR42 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst420 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst421 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst422 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst423 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst424 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst425 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst426 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst427 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR59 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst428 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst429 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst430 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst431 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst432 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst433 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst434 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst435 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR58 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst436 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst437 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst438 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst439 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst440 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst441 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst442 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst443 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR57 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst444 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst445 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst446 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst447 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst448 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst449 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst450 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst451 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR62 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst452 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst453 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst454 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst455 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst456 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst457 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst458 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst459 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR61 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst460 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst461 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst462 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst463 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst464 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst465 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst466 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst467 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR60 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst468 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst469 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst470 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst471 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst472 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst473 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst474 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst475 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR65 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst476 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst477 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst478 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst479 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst480 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst481 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst482 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst483 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR64 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst484 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst485 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst486 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst487 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst488 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst489 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst490 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst491 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR63 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst492 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst493 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst494 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst495 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst496 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst497 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst498 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst499 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR71 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst500 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst501 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst502 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst503 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst504 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst505 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst506 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst507 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR70 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst508 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst509 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst510 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst511 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst512 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst513 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst514 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR69 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst515 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst516 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst517 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst518 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst519 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst520 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst521 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst522 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst523 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst524 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR68 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst525 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst526 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst527 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst528 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst529 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst530 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst531 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst532 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR67 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst533 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst534 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst535 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst536 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst537 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst538 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst539 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst540 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR66 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst541 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst542 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst543 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst544 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst545 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst546 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst547 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst548 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR74 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst549 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst550 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst551 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst552 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst553 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst554 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst555 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst556 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR73 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst557 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst558 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst559 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst560 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst561 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst562 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst563 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst564 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR72 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst565 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst566 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst567 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst568 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst569 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst570 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst571 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst572 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR77 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst573 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst574 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst575 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst576 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst577 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst578 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst579 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst580 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR76 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst581 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst582 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst583 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst584 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst585 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst586 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst587 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst588 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR75 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst589 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst590 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst591 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst592 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst593 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst594 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst595 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst596 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR80 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst597 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst598 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst599 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst600 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst601 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst602 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst603 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst604 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR79 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst605 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst606 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst607 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst608 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst609 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst610 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst611 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst612 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR78 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst613 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst614 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst615 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst616 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst617 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst618 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst619 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst620 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR83 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst621 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst622 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst623 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst624 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst625 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst626 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst627 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst628 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR82 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst629 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst630 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst631 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst632 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst633 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst634 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst635 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR81 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst636 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst637 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst638 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst639 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst640 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst641 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst642 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR86 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst643 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst644 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst645 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst646 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst647 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst648 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst649 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst650 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR85 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst651 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst652 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst653 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst654 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst655 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst656 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst657 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst658 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR84 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst659 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst660 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst661 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst662 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst663 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst664 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst665 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst666 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR89 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst667 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst668 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst669 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst670 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst671 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst672 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst673 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst674 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR88 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst675 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst676 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst677 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst678 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst679 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst680 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst681 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst682 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR87 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst683 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst684 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst685 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst686 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst687 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst688 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst689 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst690 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR92 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst691 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst692 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst693 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst694 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst695 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst696 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst697 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst698 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR91 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst699 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst700 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst701 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst702 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst703 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst704 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst705 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst706 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR90 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst707 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst708 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst709 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec0 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec20 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst20 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iIIR10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR9 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec34 size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR26 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR25 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst70 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR24 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst71 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst78 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst79 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst80 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR23 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst81 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst82 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst83 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst84 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst85 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst86 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst87 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst88 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR22 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst89 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst90 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst91 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst92 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst93 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst94 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst95 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst96 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst97 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst98 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst99 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst100 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst101 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst102 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst103 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst104 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst105 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst106 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst107 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst108 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst109 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst110 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst111 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst112 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst113 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst114 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst115 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst116 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst117 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst118 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst119 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst120 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR17 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst131 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst132 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst133 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst134 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst135 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst136 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst137 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst138 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR16 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst139 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst140 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst141 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst142 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst143 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst144 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst145 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR15 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst146 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst147 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst148 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst149 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst150 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst151 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst152 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst153 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst154 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst155 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR14 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst156 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst157 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst158 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst159 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst160 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst161 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst162 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst163 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR13 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst164 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst165 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst166 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst167 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst168 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst169 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst170 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst171 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst172 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst173 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst174 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst175 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst176 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst177 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst178 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst179 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR41 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst180 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst181 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst182 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst183 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst184 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst185 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst186 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst187 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR40 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst188 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst189 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst190 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst191 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst192 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst193 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst194 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR39 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR38 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst205 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst206 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst207 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst208 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst209 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst210 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst211 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst212 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR37 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst213 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst214 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst215 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst216 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst217 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst218 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst219 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR36 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst220 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst221 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst222 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst223 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst224 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst225 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst226 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst227 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst228 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst229 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR35 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst230 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst231 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst232 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst233 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst234 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst235 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst236 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst237 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR34 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst238 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst239 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst240 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst241 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst242 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst243 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst244 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR33 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst245 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst246 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst247 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst248 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst249 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst250 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst251 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst252 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst253 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst254 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR32 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst255 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst256 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst257 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst258 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst259 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst260 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst261 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst262 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR31 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst263 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst264 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst265 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst266 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst267 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst268 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst269 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR30 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR29 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst280 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst281 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst282 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst283 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst284 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst285 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst286 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst287 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR28 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst288 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst289 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst290 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst291 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst292 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst293 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst294 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst295 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR27 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst296 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst297 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst298 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst299 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst300 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst301 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst302 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst303 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR56 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst304 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst305 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst306 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst307 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst308 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst309 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst310 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst311 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR55 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst312 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst313 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst314 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst315 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst316 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst317 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst318 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR54 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst319 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst320 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst321 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst322 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst323 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst324 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst325 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst326 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst327 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst328 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR53 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst329 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst330 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst331 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst332 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst333 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst334 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst335 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst336 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR52 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst337 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst338 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst339 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst340 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst341 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst342 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst343 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR51 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
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
Field = fIIR50 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst354 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst355 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst356 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst357 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst358 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst359 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst360 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst361 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR49 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst362 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst363 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst364 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst365 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst366 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst367 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst368 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR48 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst369 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst370 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst371 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst372 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst373 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst374 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst375 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst376 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst377 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst378 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR47 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst379 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst380 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst381 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst382 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst383 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst384 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst385 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst386 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR46 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst387 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst388 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst389 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst390 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst391 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst392 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst393 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR45 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst394 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst395 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst396 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst397 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst398 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst399 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst400 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst401 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst402 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst403 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR44 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst404 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst405 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst406 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst407 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst408 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst409 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst410 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst411 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR43 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst412 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst413 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst414 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst415 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst416 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst417 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst418 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst419 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR42 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst420 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst421 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst422 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst423 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst424 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst425 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst426 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst427 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR59 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst428 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst429 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst430 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst431 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst432 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst433 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst434 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst435 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR58 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst436 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst437 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst438 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst439 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst440 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst441 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst442 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst443 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR57 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst444 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst445 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst446 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst447 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst448 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst449 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst450 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst451 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR62 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst452 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst453 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst454 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst455 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst456 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst457 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst458 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst459 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR61 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst460 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst461 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst462 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst463 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst464 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst465 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst466 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst467 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR60 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst468 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst469 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst470 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst471 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst472 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst473 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst474 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst475 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR65 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst476 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst477 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst478 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst479 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst480 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst481 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst482 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst483 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR64 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst484 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst485 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst486 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst487 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst488 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst489 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst490 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst491 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR63 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst492 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst493 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst494 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst495 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst496 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst497 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst498 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst499 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR71 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst500 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst501 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst502 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst503 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst504 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst505 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst506 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst507 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR70 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst508 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst509 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst510 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst511 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst512 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst513 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst514 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR69 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst515 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst516 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst517 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst518 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst519 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst520 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst521 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst522 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst523 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst524 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR68 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst525 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst526 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst527 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst528 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst529 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst530 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst531 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst532 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR67 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst533 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst534 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst535 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst536 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst537 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst538 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst539 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst540 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR66 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst541 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst542 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst543 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst544 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst545 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst546 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst547 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst548 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR74 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst549 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst550 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst551 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst552 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst553 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst554 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst555 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst556 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR73 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst557 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst558 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst559 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst560 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst561 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst562 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst563 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst564 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR72 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst565 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst566 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst567 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst568 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst569 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst570 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst571 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst572 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR77 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst573 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst574 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst575 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst576 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst577 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst578 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst579 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst580 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR76 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst581 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst582 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst583 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst584 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst585 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst586 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst587 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst588 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR75 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst589 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst590 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst591 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst592 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst593 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst594 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst595 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst596 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR80 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst597 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst598 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst599 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst600 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst601 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst602 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst603 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst604 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR79 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst605 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst606 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst607 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst608 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst609 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst610 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst611 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst612 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR78 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst613 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst614 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst615 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst616 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst617 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst618 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst619 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst620 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR83 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst621 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst622 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst623 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst624 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst625 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst626 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst627 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst628 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR82 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst629 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst630 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst631 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst632 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst633 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst634 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst635 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR81 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst636 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst637 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst638 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst639 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst640 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst641 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst642 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR86 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst643 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst644 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst645 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst646 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst647 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst648 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst649 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst650 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR85 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst651 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst652 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst653 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst654 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst655 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst656 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst657 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst658 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR84 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst659 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst660 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst661 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst662 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst663 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst664 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst665 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst666 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR89 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst667 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst668 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst669 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst670 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst671 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst672 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst673 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst674 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR88 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst675 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst676 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst677 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst678 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst679 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst680 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst681 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst682 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR87 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst683 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst684 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst685 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst686 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst687 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst688 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst689 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst690 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR92 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst691 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst692 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst693 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst694 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst695 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst696 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst697 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst698 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR91 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst699 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst700 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst701 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst702 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst703 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst704 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst705 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst706 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR90 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst707 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst708 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst709 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVbargraph14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 4 size_bytes = 16 read = 4 write = 2 ratio = 1.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 6 write = 0 ratio = 6
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec8 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec9 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec10 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec11 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec12 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec13 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec14 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec15 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec16 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec17 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec18 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec19 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = IOTA0 size = 1 size_bytes = 4 read = 25 write = 1 ratio = 26
Field = fVec20 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec21 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec22 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fRec10 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec23 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec24 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec25 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec26 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec27 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVec28 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec29 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec30 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVec31 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec32 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec33 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR10 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR9 size = 4 size_bytes = 16 read = 4 write = 2 ratio = 1.5
Field = fVec34 size = 4 size_bytes = 16 read = 5 write = 2 ratio = 1.75
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec3 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fCheckbox3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec12 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec11 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec13 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec14 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec15 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec16 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR11 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst30 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR2 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst38 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR1 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst41 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst46 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst48 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst49 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph0 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst54 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst55 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR26 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst58 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst62 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst63 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR25 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst64 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst65 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst69 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst70 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR24 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst71 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst72 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst78 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst79 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst80 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR23 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst81 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst82 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst83 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst84 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst85 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst86 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst87 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst88 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR22 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst89 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst90 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst91 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst92 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst93 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst94 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst95 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR21 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst96 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst97 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst98 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst99 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst100 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst101 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst102 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst103 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst104 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst105 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR20 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst106 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst107 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst108 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst109 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst110 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst111 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst112 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst113 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR19 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst114 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst115 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst116 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst117 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst118 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst119 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst120 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR18 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst121 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst122 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst123 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst124 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst125 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst126 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst127 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst128 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst129 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst130 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR17 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst131 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst132 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst133 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst134 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst135 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst136 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst137 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst138 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR16 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst139 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst140 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst141 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst142 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst143 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst144 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst145 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR15 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst146 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst147 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst148 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst149 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst150 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst151 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst152 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst153 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst154 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst155 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR14 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst156 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst157 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst158 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst159 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst160 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst161 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst162 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst163 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR13 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst164 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst165 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst166 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst167 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst168 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst169 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst170 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst171 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR12 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst172 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst173 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst174 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph1 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst175 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst176 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst177 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst178 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst179 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR41 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst180 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst181 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst182 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst183 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst184 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst185 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst186 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst187 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR40 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst188 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst189 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst190 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst191 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst192 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst193 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst194 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR39 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst195 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst196 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst197 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst198 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst199 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst200 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst201 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst202 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst203 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst204 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR38 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst205 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst206 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst207 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst208 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst209 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst210 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst211 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst212 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR37 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst213 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst214 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst215 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst216 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst217 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst218 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst219 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR36 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst220 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst221 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst222 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst223 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst224 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst225 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst226 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst227 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst228 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst229 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR35 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst230 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst231 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst232 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst233 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst234 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst235 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst236 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst237 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR34 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst238 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst239 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst240 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst241 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst242 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst243 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst244 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR33 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst245 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst246 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst247 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst248 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst249 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst250 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst251 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst252 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst253 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst254 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR32 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst255 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst256 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst257 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst258 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst259 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst260 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst261 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst262 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR31 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst263 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst264 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst265 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst266 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst267 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst268 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst269 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR30 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst270 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst271 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst272 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst273 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst274 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst275 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst276 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst277 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst278 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst279 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR29 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst280 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst281 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst282 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst283 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst284 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst285 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst286 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst287 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR28 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst288 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst289 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst290 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst291 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst292 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst293 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst294 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst295 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR27 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst296 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst297 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst298 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph2 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst299 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst300 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst301 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst302 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst303 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR56 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst304 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst305 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst306 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst307 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst308 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst309 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst310 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst311 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR55 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst312 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst313 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst314 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst315 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst316 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst317 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst318 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR54 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst319 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst320 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst321 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst322 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst323 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst324 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst325 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst326 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst327 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst328 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR53 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst329 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst330 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst331 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst332 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst333 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst334 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst335 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst336 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR52 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst337 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst338 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst339 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst340 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst341 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst342 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst343 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR51 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst344 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst345 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst346 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst347 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst348 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst349 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst350 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst351 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst352 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst353 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR50 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst354 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst355 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst356 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst357 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst358 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst359 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst360 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst361 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR49 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst362 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst363 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst364 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst365 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst366 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst367 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst368 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR48 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst369 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst370 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst371 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst372 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst373 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst374 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst375 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst376 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst377 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst378 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR47 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst379 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst380 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst381 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst382 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst383 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst384 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst385 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst386 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR46 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst387 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst388 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst389 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst390 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst391 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst392 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst393 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR45 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst394 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst395 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst396 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst397 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst398 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst399 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst400 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst401 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst402 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst403 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR44 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst404 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst405 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst406 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst407 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst408 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst409 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst410 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst411 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR43 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst412 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst413 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst414 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst415 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst416 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst417 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst418 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst419 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR42 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst420 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst421 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst422 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph3 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst423 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst424 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst425 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst426 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst427 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR59 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst428 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst429 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst430 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst431 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst432 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst433 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst434 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst435 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR58 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst436 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst437 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst438 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst439 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst440 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst441 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst442 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst443 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR57 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst444 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst445 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst446 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph4 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst447 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst448 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst449 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst450 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst451 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR62 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst452 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst453 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst454 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst455 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst456 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst457 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst458 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst459 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR61 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst460 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst461 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst462 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst463 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst464 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst465 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst466 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst467 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR60 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst468 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst469 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst470 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph5 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst471 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst472 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst473 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst474 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst475 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR65 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst476 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst477 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst478 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst479 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst480 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst481 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst482 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst483 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR64 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst484 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst485 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst486 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst487 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst488 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst489 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst490 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst491 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR63 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst492 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst493 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst494 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph6 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst495 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst496 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst497 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst498 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst499 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR71 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst500 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst501 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst502 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst503 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst504 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst505 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst506 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst507 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR70 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst508 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst509 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst510 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst511 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst512 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst513 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst514 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR69 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst515 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst516 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst517 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst518 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst519 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst520 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst521 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst522 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst523 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst524 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR68 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst525 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst526 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst527 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst528 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst529 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst530 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst531 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst532 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR67 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst533 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst534 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst535 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst536 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst537 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst538 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst539 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst540 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR66 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst541 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst542 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst543 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM8 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph7 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst544 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst545 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst546 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst547 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst548 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR74 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst549 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst550 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst551 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst552 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst553 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst554 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst555 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst556 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR73 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst557 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst558 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst559 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst560 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst561 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst562 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst563 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst564 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR72 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst565 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst566 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst567 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM9 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph8 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst568 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst569 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst570 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst571 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst572 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR77 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst573 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst574 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst575 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst576 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst577 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst578 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst579 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst580 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR76 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst581 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst582 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst583 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst584 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst585 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst586 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst587 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst588 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR75 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst589 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst590 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst591 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM10 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph9 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst592 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst593 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst594 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst595 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst596 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR80 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst597 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst598 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst599 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst600 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst601 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst602 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst603 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst604 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR79 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst605 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst606 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst607 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst608 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst609 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst610 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst611 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst612 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR78 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst613 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst614 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst615 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM11 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph10 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst616 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst617 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst618 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst619 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst620 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR83 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst621 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst622 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst623 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst624 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst625 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst626 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst627 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst628 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR82 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst629 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst630 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst631 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst632 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst633 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst634 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst635 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR81 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst636 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst637 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM12 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph11 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst638 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst639 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst640 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst641 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst642 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR86 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst643 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst644 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst645 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst646 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst647 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst648 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst649 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst650 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR85 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst651 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst652 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst653 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst654 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst655 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst656 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst657 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst658 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR84 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst659 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst660 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst661 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM13 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph12 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst662 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst663 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst664 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst665 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst666 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR89 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst667 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst668 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst669 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst670 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst671 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst672 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst673 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst674 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR88 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst675 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst676 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst677 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst678 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst679 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst680 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst681 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst682 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR87 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst683 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst684 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst685 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM14 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph13 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1
Field = fConst686 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst687 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst688 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst689 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst690 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR92 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst691 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst692 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst693 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst694 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst695 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst696 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst697 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst698 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR91 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst699 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst700 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst701 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst702 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst703 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst704 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst705 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst706 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR90 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst707 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst708 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst709 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM15 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVbargraph14 size = 1 size_bytes = 4 read = 0 write = 1 ratio = 1

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            86785
  eval() cache hits:       25739 (29.6584%)
  eval() cache misses:     61046
  Loop detector calls:     61046
  Stack detector calls:    61046

--- Phase 3: Propagation ---
  propagate() calls:       34263
  propagate() cache hits:  8812 (25.7187%)
  propagate() cache misses:25451

--- Box Type Computation ---
  getBoxType() calls:      60910
  getBoxType() cache hits: 47915 (78.6652%)
  getBoxType() computed:   12995

--- Environment Operations ---
  Environment lookups:     3329
  Average lookup depth:    0.500751
  Env layers pushed:       5460

--- Pattern Matching ---
  build automaton calls:        236
  build total time (ms):        1.54654
  build avg time (ms):          0.00655316
  apply calls:                  1896
  apply total time (ms):        1.91701
  apply avg time (ms):          0.00101108

--- Tree Operations ---
  Trees created:           218722
  Trees reused (hash):     455837 (67.5756% reuse rate)
  Property set ops:        78405
  Property get ops:        240520

--- Iteration Constructs ---
  par() iterations:        27
  seq() iterations:        25
  sum() iterations:        6
  prod() iterations:       0

==========================================
