======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("graphicEqLab")
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "See Faust's oscillators.lib   for documentation and references")
	OpenVerticalBox("SAWTOOTH OSCILLATOR")
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider0, "1", "")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddMetaDeclareInst(fVslider0, "tooltip", "Sawtooth   waveform amplitude")
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("Amplitude", fVslider0, -20.0f, -120.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider1, "2", "")
	AddMetaDeclareInst(fVslider1, "style", "knob")
	AddMetaDeclareInst(fVslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)")
	AddMetaDeclareInst(fVslider1, "unit", "PK")
	AddVerticalSlider("Frequency", fVslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider3, "3", "")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Percentange frequency-shift  up or down for second oscillator")
	AddMetaDeclareInst(fVslider3, "unit", "%%")
	AddVerticalSlider("Detuning 1", fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider4, "4", "")
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddMetaDeclareInst(fVslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator")
	AddMetaDeclareInst(fVslider4, "unit", "%%")
	AddVerticalSlider("Detuning 2", fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider2, "5", "")
	AddMetaDeclareInst(fVslider2, "scale", "log")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds")
	AddMetaDeclareInst(fVslider2, "unit", "sec")
	AddVerticalSlider("Portamento", fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f)
	AddMetaDeclareInst(fEntry0, "6", "")
	AddMetaDeclareInst(fEntry0, "tooltip", "Order of sawtootn aliasing   suppression")
	AddNumEntry"Saw Order", fEntry0, 2.0f, 1.0f, 4.0f, 1.0f)
	AddMetaDeclareInst(0, "7", "")
	OpenVerticalBox("Alternate Signals")
	AddMetaDeclareInst(fCheckbox2, "0", "")
	AddCheckButtonInst("Noise (White or Pink - uses only Amplitude control on   the left)"fCheckbox2)
	AddMetaDeclareInst(fCheckbox3, "1", "")
	AddMetaDeclareInst(fCheckbox3, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the   same total power in every octave")
	AddCheckButtonInst("Pink instead of White Noise (also called 1/f Noise)"fCheckbox3)
	AddMetaDeclareInst(fCheckbox1, "2", "")
	AddCheckButtonInst("External Signal Input (overrides Sawtooth/Noise   selection above)"fCheckbox1)
	CloseboxInst
	CloseboxInst
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(0, "tooltip", "See Faust's filters.lib for documentation and references")
	OpenVerticalBox("CONSTANT-Q FILTER BANK (Butterworth dyadic tree)")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the filter-bank has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider7, "1", "")
	AddMetaDeclareInst(fVslider7, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider7, "unit", "dB")
	AddVerticalSlider("0x00", fVslider7, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider6, "2", "")
	AddMetaDeclareInst(fVslider6, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider6, "unit", "dB")
	AddVerticalSlider("0x00", fVslider6, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider5, "3", "")
	AddMetaDeclareInst(fVslider5, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider5, "unit", "dB")
	AddVerticalSlider("0x00", fVslider5, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider14, "4", "")
	AddMetaDeclareInst(fVslider14, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider14, "unit", "dB")
	AddVerticalSlider("0x00", fVslider14, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider13, "5", "")
	AddMetaDeclareInst(fVslider13, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider13, "unit", "dB")
	AddVerticalSlider("0x00", fVslider13, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider12, "6", "")
	AddMetaDeclareInst(fVslider12, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider12, "unit", "dB")
	AddVerticalSlider("0x00", fVslider12, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider11, "7", "")
	AddMetaDeclareInst(fVslider11, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider11, "unit", "dB")
	AddVerticalSlider("0x00", fVslider11, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider10, "8", "")
	AddMetaDeclareInst(fVslider10, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider10, "unit", "dB")
	AddVerticalSlider("0x00", fVslider10, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider9, "9", "")
	AddMetaDeclareInst(fVslider9, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider9, "unit", "dB")
	AddVerticalSlider("0x00", fVslider9, -10.0f, -70.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fVslider8, "10", "")
	AddMetaDeclareInst(fVslider8, "tooltip", "Bandpass filter   gain in dB")
	AddMetaDeclareInst(fVslider8, "unit", "dB")
	AddVerticalSlider("0x00", fVslider8, -10.0f, -70.0f, 10.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "See Faust's filters.lib for documentation and references")
	OpenHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP")
	AddMetaDeclareInst(fVbargraph14, "0", "")
	AddMetaDeclareInst(fVbargraph14, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph14, "unit", "dB")
	AddVerticalBargraph("0x7f8f093ef8f0", fVbargraph14, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph13, "1", "")
	AddMetaDeclareInst(fVbargraph13, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph13, "unit", "dB")
	AddVerticalBargraph("0x7f8f093ddf90", fVbargraph13, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph12, "2", "")
	AddMetaDeclareInst(fVbargraph12, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph12, "unit", "dB")
	AddVerticalBargraph("0x7f8f093bbe40", fVbargraph12, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph11, "3", "")
	AddMetaDeclareInst(fVbargraph11, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph11, "unit", "dB")
	AddVerticalBargraph("0x7f8f09399cf0", fVbargraph11, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph10, "4", "")
	AddMetaDeclareInst(fVbargraph10, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph10, "unit", "dB")
	AddVerticalBargraph("0x7f8f09377ba0", fVbargraph10, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph9, "5", "")
	AddMetaDeclareInst(fVbargraph9, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph9, "unit", "dB")
	AddVerticalBargraph("0x7f8f09355a50", fVbargraph9, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph8, "6", "")
	AddMetaDeclareInst(fVbargraph8, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph8, "unit", "dB")
	AddVerticalBargraph("0x7f8f09932e90", fVbargraph8, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph7, "7", "")
	AddMetaDeclareInst(fVbargraph7, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph7, "unit", "dB")
	AddVerticalBargraph("0x7f8f09910d40", fVbargraph7, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph6, "8", "")
	AddMetaDeclareInst(fVbargraph6, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("0x7f8f098eac70", fVbargraph6, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph5, "9", "")
	AddMetaDeclareInst(fVbargraph5, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("0x7f8f098c8b20", fVbargraph5, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph4, "10", "")
	AddMetaDeclareInst(fVbargraph4, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("0x7f8f098a69d0", fVbargraph4, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph3, "11", "")
	AddMetaDeclareInst(fVbargraph3, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("0x7f8f09884880", fVbargraph3, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph2, "12", "")
	AddMetaDeclareInst(fVbargraph2, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("0x7f8f09862730", fVbargraph2, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph1, "13", "")
	AddMetaDeclareInst(fVbargraph1, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("0x7f8f098405e0", fVbargraph1, -50.0f, 10.0f)
	AddMetaDeclareInst(fVbargraph0, "14", "")
	AddMetaDeclareInst(fVbargraph0, "tooltip", "Spectral Band Level in dB")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("0x7f8f0981d400", fVbargraph0, -50.0f, 10.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("SPECTRUM ANALYZER CONTROLS")
	AddMetaDeclareInst(fHslider1, "0", "")
	AddMetaDeclareInst(fHslider1, "scale", "log")
	AddMetaDeclareInst(fHslider1, "tooltip", "band-level averaging time in milliseconds")
	AddMetaDeclareInst(fHslider1, "unit", "ms")
	AddHorizontalSlider("Level Averaging Time", fHslider1, 100.0f, 1.0f, 10000.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "1", "")
	AddMetaDeclareInst(fHslider0, "tooltip", "Level offset in decibels")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Level dB Offset", fHslider0, 50.0f, -50.0f, 100.0f, 1.0f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "log10f", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[4])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, "float", fConst66)
	DeclareVarInst(struct, "float", fConst67)
	DeclareVarInst(struct, "float", fConst68)
	DeclareVarInst(struct, "float", fConst69)
	DeclareVarInst(struct, "float", fConst70)
	DeclareVarInst(struct, "float", fConst71)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "float", fConst72)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, "float", fConst73)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "float", fConst74)
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, "float", fConst75)
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fVec8[2])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec9[2])
	DeclareVarInst(struct, float, fVec10[2])
	DeclareVarInst(struct, float, fVec11[2])
	DeclareVarInst(struct, float, fVec12[2])
	DeclareVarInst(struct, float, fVec13[2])
	DeclareVarInst(struct, float, fVec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fVec15[2])
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, float, fVec16[2])
	DeclareVarInst(struct, float, fVec17[2])
	DeclareVarInst(struct, float, fVec18[2])
	DeclareVarInst(struct, float, fVec19[2])
	DeclareVarInst(struct, float, fVec20[2])
	DeclareVarInst(struct, float, fVec21[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox3)
	DeclareVarInst(struct, int, iRec34[2])
	DeclareVarInst(struct, float, fRec35[4])
	DeclareVarInst(struct, float, fVec22[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "float", fConst76)
	DeclareVarInst(struct, "float", fConst77)
	DeclareVarInst(struct, "float", fConst78)
	DeclareVarInst(struct, float, fRec27[3])
	DeclareVarInst(struct, "float", fConst79)
	DeclareVarInst(struct, "float", fConst80)
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, float, fVec23[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst81)
	DeclareVarInst(struct, "float", fConst82)
	DeclareVarInst(struct, "float", fConst83)
	DeclareVarInst(struct, float, fRec24[3])
	DeclareVarInst(struct, "float", fConst84)
	DeclareVarInst(struct, "float", fConst85)
	DeclareVarInst(struct, float, fRec23[3])
	DeclareVarInst(struct, float, fVec24[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "float", fConst86)
	DeclareVarInst(struct, "float", fConst87)
	DeclareVarInst(struct, "float", fConst88)
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, "float", fConst89)
	DeclareVarInst(struct, "float", fConst90)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, float, fVec25[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "float", fConst91)
	DeclareVarInst(struct, "float", fConst92)
	DeclareVarInst(struct, "float", fConst93)
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, "float", fConst94)
	DeclareVarInst(struct, "float", fConst95)
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, float, fVec26[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "float", fConst96)
	DeclareVarInst(struct, "float", fConst97)
	DeclareVarInst(struct, "float", fConst98)
	DeclareVarInst(struct, float, fRec15[3])
	DeclareVarInst(struct, "float", fConst99)
	DeclareVarInst(struct, "float", fConst100)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, float, fVec27[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "float", fConst101)
	DeclareVarInst(struct, "float", fConst102)
	DeclareVarInst(struct, "float", fConst103)
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "float", fConst104)
	DeclareVarInst(struct, "float", fConst105)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, float, fVec28[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "float", fConst106)
	DeclareVarInst(struct, "float", fConst107)
	DeclareVarInst(struct, "float", fConst108)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, "float", fConst109)
	DeclareVarInst(struct, "float", fConst110)
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fVec29[2])
	DeclareVarInst(struct, "float", fConst111)
	DeclareVarInst(struct, "float", fConst112)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "float", fConst113)
	DeclareVarInst(struct, "float", fConst114)
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, "float", fConst115)
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst116)
	DeclareVarInst(struct, "float", fConst117)
	DeclareVarInst(struct, "float", fConst118)
	DeclareVarInst(struct, "float", fConst119)
	DeclareVarInst(struct, "float", fConst120)
	DeclareVarInst(struct, "float", fConst121)
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, "float", fConst122)
	DeclareVarInst(struct, "float", fConst123)
	DeclareVarInst(struct, "float", fConst124)
	DeclareVarInst(struct, "float", fConst125)
	DeclareVarInst(struct, "float", fConst126)
	DeclareVarInst(struct, "float", fConst127)
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, float, fRec40[3])
	DeclareVarInst(struct, float, fVec30[2])
	DeclareVarInst(struct, "float", fConst128)
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, "float", fConst129)
	DeclareVarInst(struct, float, fRec38[3])
	DeclareVarInst(struct, "float", fConst130)
	DeclareVarInst(struct, float, fRec37[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, float, fRec44[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, float, fRec47[2])
	DeclareVarInst(struct, "float", fConst131)
	DeclareVarInst(struct, "float", fConst132)
	DeclareVarInst(struct, float, fRec58[2])
	DeclareVarInst(struct, float, fRec57[3])
	DeclareVarInst(struct, float, fRec56[3])
	DeclareVarInst(struct, float, fRec55[3])
	DeclareVarInst(struct, "float", fConst133)
	DeclareVarInst(struct, "float", fConst134)
	DeclareVarInst(struct, float, fRec54[3])
	DeclareVarInst(struct, "float", fConst135)
	DeclareVarInst(struct, "float", fConst136)
	DeclareVarInst(struct, float, fRec53[3])
	DeclareVarInst(struct, "float", fConst137)
	DeclareVarInst(struct, "float", fConst138)
	DeclareVarInst(struct, float, fRec52[3])
	DeclareVarInst(struct, "float", fConst139)
	DeclareVarInst(struct, "float", fConst140)
	DeclareVarInst(struct, float, fRec51[3])
	DeclareVarInst(struct, "float", fConst141)
	DeclareVarInst(struct, "float", fConst142)
	DeclareVarInst(struct, float, fRec50[3])
	DeclareVarInst(struct, "float", fConst143)
	DeclareVarInst(struct, "float", fConst144)
	DeclareVarInst(struct, float, fRec49[3])
	DeclareVarInst(struct, "float", fConst145)
	DeclareVarInst(struct, "float", fConst146)
	DeclareVarInst(struct, float, fRec48[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec59[2])
	DeclareVarInst(struct, "float", fConst147)
	DeclareVarInst(struct, "float", fConst148)
	DeclareVarInst(struct, float, fRec69[2])
	DeclareVarInst(struct, float, fRec68[3])
	DeclareVarInst(struct, float, fRec67[3])
	DeclareVarInst(struct, float, fRec66[3])
	DeclareVarInst(struct, float, fRec65[3])
	DeclareVarInst(struct, float, fRec64[3])
	DeclareVarInst(struct, float, fRec63[3])
	DeclareVarInst(struct, float, fRec62[3])
	DeclareVarInst(struct, float, fRec61[3])
	DeclareVarInst(struct, float, fRec60[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, float, fRec70[2])
	DeclareVarInst(struct, "float", fConst149)
	DeclareVarInst(struct, "float", fConst150)
	DeclareVarInst(struct, float, fRec79[2])
	DeclareVarInst(struct, float, fRec78[3])
	DeclareVarInst(struct, float, fRec77[3])
	DeclareVarInst(struct, float, fRec76[3])
	DeclareVarInst(struct, float, fRec75[3])
	DeclareVarInst(struct, float, fRec74[3])
	DeclareVarInst(struct, float, fRec73[3])
	DeclareVarInst(struct, float, fRec72[3])
	DeclareVarInst(struct, float, fRec71[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider10)
	DeclareVarInst(struct, float, fRec80[2])
	DeclareVarInst(struct, "float", fConst151)
	DeclareVarInst(struct, "float", fConst152)
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, float, fRec87[3])
	DeclareVarInst(struct, float, fRec86[3])
	DeclareVarInst(struct, float, fRec85[3])
	DeclareVarInst(struct, float, fRec84[3])
	DeclareVarInst(struct, float, fRec83[3])
	DeclareVarInst(struct, float, fRec82[3])
	DeclareVarInst(struct, float, fRec81[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider11)
	DeclareVarInst(struct, float, fRec89[2])
	DeclareVarInst(struct, "float", fConst153)
	DeclareVarInst(struct, "float", fConst154)
	DeclareVarInst(struct, float, fRec96[2])
	DeclareVarInst(struct, float, fRec95[3])
	DeclareVarInst(struct, float, fRec94[3])
	DeclareVarInst(struct, float, fRec93[3])
	DeclareVarInst(struct, float, fRec92[3])
	DeclareVarInst(struct, float, fRec91[3])
	DeclareVarInst(struct, float, fRec90[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider12)
	DeclareVarInst(struct, float, fRec97[2])
	DeclareVarInst(struct, "float", fConst155)
	DeclareVarInst(struct, "float", fConst156)
	DeclareVarInst(struct, float, fRec103[2])
	DeclareVarInst(struct, float, fRec102[3])
	DeclareVarInst(struct, float, fRec101[3])
	DeclareVarInst(struct, float, fRec100[3])
	DeclareVarInst(struct, float, fRec99[3])
	DeclareVarInst(struct, float, fRec98[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider13)
	DeclareVarInst(struct, float, fRec104[2])
	DeclareVarInst(struct, "float", fConst157)
	DeclareVarInst(struct, "float", fConst158)
	DeclareVarInst(struct, float, fRec109[2])
	DeclareVarInst(struct, float, fRec108[3])
	DeclareVarInst(struct, float, fRec107[3])
	DeclareVarInst(struct, float, fRec106[3])
	DeclareVarInst(struct, float, fRec105[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider14)
	DeclareVarInst(struct, float, fRec110[2])
	DeclareVarInst(struct, "float", fConst159)
	DeclareVarInst(struct, "float", fConst160)
	DeclareVarInst(struct, "float", fConst161)
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "float", fConst162)
	DeclareVarInst(struct, "float", fConst163)
	DeclareVarInst(struct, "float", fConst164)
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, "float", fConst165)
	DeclareVarInst(struct, "float", fConst166)
	DeclareVarInst(struct, "float", fConst167)
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "float", fConst168)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "float", fConst169)
	DeclareVarInst(struct, "float", fConst170)
	DeclareVarInst(struct, "float", fConst171)
	DeclareVarInst(struct, "float", fConst172)
	DeclareVarInst(struct, "float", fConst173)
	DeclareVarInst(struct, "float", fConst174)
	DeclareVarInst(struct, "float", fConst175)
	DeclareVarInst(struct, "float", fConst176)
	DeclareVarInst(struct, "float", fConst177)
	DeclareVarInst(struct, "float", fConst178)
	DeclareVarInst(struct, "float", fConst179)
	DeclareVarInst(struct, "float", fConst180)
	DeclareVarInst(struct, "float", fConst181)
	DeclareVarInst(struct, "float", fConst182)
	DeclareVarInst(struct, "float", fConst183)
	DeclareVarInst(struct, "float", fConst184)
	DeclareVarInst(struct, "float", fConst185)
	DeclareVarInst(struct, "float", fConst186)
	DeclareVarInst(struct, "float", fConst187)
	DeclareVarInst(struct, "float", fConst188)
	DeclareVarInst(struct, "float", fConst189)
	DeclareVarInst(struct, float, fRec117[3])
	DeclareVarInst(struct, "float", fConst190)
	DeclareVarInst(struct, "float", fConst191)
	DeclareVarInst(struct, "float", fConst192)
	DeclareVarInst(struct, float, fRec116[3])
	DeclareVarInst(struct, "float", fConst193)
	DeclareVarInst(struct, "float", fConst194)
	DeclareVarInst(struct, "float", fConst195)
	DeclareVarInst(struct, float, fRec115[3])
	DeclareVarInst(struct, "float", fConst196)
	DeclareVarInst(struct, "float", fConst197)
	DeclareVarInst(struct, "float", fConst198)
	DeclareVarInst(struct, "float", fConst199)
	DeclareVarInst(struct, float, fRec114[3])
	DeclareVarInst(struct, "float", fConst200)
	DeclareVarInst(struct, "float", fConst201)
	DeclareVarInst(struct, "float", fConst202)
	DeclareVarInst(struct, float, fRec113[3])
	DeclareVarInst(struct, "float", fConst203)
	DeclareVarInst(struct, "float", fConst204)
	DeclareVarInst(struct, "float", fConst205)
	DeclareVarInst(struct, float, fRec112[3])
	DeclareVarInst(struct, "float", fConst206)
	DeclareVarInst(struct, float, fRec111[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "float", fConst207)
	DeclareVarInst(struct, "float", fConst208)
	DeclareVarInst(struct, "float", fConst209)
	DeclareVarInst(struct, "float", fConst210)
	DeclareVarInst(struct, "float", fConst211)
	DeclareVarInst(struct, "float", fConst212)
	DeclareVarInst(struct, "float", fConst213)
	DeclareVarInst(struct, "float", fConst214)
	DeclareVarInst(struct, "float", fConst215)
	DeclareVarInst(struct, "float", fConst216)
	DeclareVarInst(struct, "float", fConst217)
	DeclareVarInst(struct, "float", fConst218)
	DeclareVarInst(struct, "float", fConst219)
	DeclareVarInst(struct, "float", fConst220)
	DeclareVarInst(struct, "float", fConst221)
	DeclareVarInst(struct, "float", fConst222)
	DeclareVarInst(struct, "float", fConst223)
	DeclareVarInst(struct, "float", fConst224)
	DeclareVarInst(struct, "float", fConst225)
	DeclareVarInst(struct, "float", fConst226)
	DeclareVarInst(struct, "float", fConst227)
	DeclareVarInst(struct, float, fRec124[3])
	DeclareVarInst(struct, "float", fConst228)
	DeclareVarInst(struct, "float", fConst229)
	DeclareVarInst(struct, "float", fConst230)
	DeclareVarInst(struct, float, fRec123[3])
	DeclareVarInst(struct, "float", fConst231)
	DeclareVarInst(struct, "float", fConst232)
	DeclareVarInst(struct, "float", fConst233)
	DeclareVarInst(struct, float, fRec122[3])
	DeclareVarInst(struct, "float", fConst234)
	DeclareVarInst(struct, "float", fConst235)
	DeclareVarInst(struct, "float", fConst236)
	DeclareVarInst(struct, "float", fConst237)
	DeclareVarInst(struct, float, fRec121[3])
	DeclareVarInst(struct, "float", fConst238)
	DeclareVarInst(struct, "float", fConst239)
	DeclareVarInst(struct, "float", fConst240)
	DeclareVarInst(struct, float, fRec120[3])
	DeclareVarInst(struct, "float", fConst241)
	DeclareVarInst(struct, "float", fConst242)
	DeclareVarInst(struct, "float", fConst243)
	DeclareVarInst(struct, float, fRec119[3])
	DeclareVarInst(struct, "float", fConst244)
	DeclareVarInst(struct, float, fRec118[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "float", fConst245)
	DeclareVarInst(struct, "float", fConst246)
	DeclareVarInst(struct, "float", fConst247)
	DeclareVarInst(struct, "float", fConst248)
	DeclareVarInst(struct, "float", fConst249)
	DeclareVarInst(struct, "float", fConst250)
	DeclareVarInst(struct, "float", fConst251)
	DeclareVarInst(struct, "float", fConst252)
	DeclareVarInst(struct, "float", fConst253)
	DeclareVarInst(struct, "float", fConst254)
	DeclareVarInst(struct, "float", fConst255)
	DeclareVarInst(struct, "float", fConst256)
	DeclareVarInst(struct, "float", fConst257)
	DeclareVarInst(struct, "float", fConst258)
	DeclareVarInst(struct, "float", fConst259)
	DeclareVarInst(struct, "float", fConst260)
	DeclareVarInst(struct, "float", fConst261)
	DeclareVarInst(struct, "float", fConst262)
	DeclareVarInst(struct, "float", fConst263)
	DeclareVarInst(struct, "float", fConst264)
	DeclareVarInst(struct, "float", fConst265)
	DeclareVarInst(struct, float, fRec131[3])
	DeclareVarInst(struct, "float", fConst266)
	DeclareVarInst(struct, "float", fConst267)
	DeclareVarInst(struct, "float", fConst268)
	DeclareVarInst(struct, float, fRec130[3])
	DeclareVarInst(struct, "float", fConst269)
	DeclareVarInst(struct, "float", fConst270)
	DeclareVarInst(struct, "float", fConst271)
	DeclareVarInst(struct, float, fRec129[3])
	DeclareVarInst(struct, "float", fConst272)
	DeclareVarInst(struct, "float", fConst273)
	DeclareVarInst(struct, "float", fConst274)
	DeclareVarInst(struct, "float", fConst275)
	DeclareVarInst(struct, float, fRec128[3])
	DeclareVarInst(struct, "float", fConst276)
	DeclareVarInst(struct, "float", fConst277)
	DeclareVarInst(struct, "float", fConst278)
	DeclareVarInst(struct, float, fRec127[3])
	DeclareVarInst(struct, "float", fConst279)
	DeclareVarInst(struct, "float", fConst280)
	DeclareVarInst(struct, "float", fConst281)
	DeclareVarInst(struct, float, fRec126[3])
	DeclareVarInst(struct, "float", fConst282)
	DeclareVarInst(struct, float, fRec125[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "float", fConst283)
	DeclareVarInst(struct, "float", fConst284)
	DeclareVarInst(struct, "float", fConst285)
	DeclareVarInst(struct, "float", fConst286)
	DeclareVarInst(struct, "float", fConst287)
	DeclareVarInst(struct, "float", fConst288)
	DeclareVarInst(struct, "float", fConst289)
	DeclareVarInst(struct, "float", fConst290)
	DeclareVarInst(struct, "float", fConst291)
	DeclareVarInst(struct, "float", fConst292)
	DeclareVarInst(struct, "float", fConst293)
	DeclareVarInst(struct, "float", fConst294)
	DeclareVarInst(struct, "float", fConst295)
	DeclareVarInst(struct, "float", fConst296)
	DeclareVarInst(struct, "float", fConst297)
	DeclareVarInst(struct, "float", fConst298)
	DeclareVarInst(struct, "float", fConst299)
	DeclareVarInst(struct, "float", fConst300)
	DeclareVarInst(struct, "float", fConst301)
	DeclareVarInst(struct, "float", fConst302)
	DeclareVarInst(struct, "float", fConst303)
	DeclareVarInst(struct, float, fRec138[3])
	DeclareVarInst(struct, "float", fConst304)
	DeclareVarInst(struct, "float", fConst305)
	DeclareVarInst(struct, "float", fConst306)
	DeclareVarInst(struct, float, fRec137[3])
	DeclareVarInst(struct, "float", fConst307)
	DeclareVarInst(struct, "float", fConst308)
	DeclareVarInst(struct, "float", fConst309)
	DeclareVarInst(struct, float, fRec136[3])
	DeclareVarInst(struct, "float", fConst310)
	DeclareVarInst(struct, "float", fConst311)
	DeclareVarInst(struct, "float", fConst312)
	DeclareVarInst(struct, "float", fConst313)
	DeclareVarInst(struct, float, fRec135[3])
	DeclareVarInst(struct, "float", fConst314)
	DeclareVarInst(struct, "float", fConst315)
	DeclareVarInst(struct, "float", fConst316)
	DeclareVarInst(struct, float, fRec134[3])
	DeclareVarInst(struct, "float", fConst317)
	DeclareVarInst(struct, "float", fConst318)
	DeclareVarInst(struct, "float", fConst319)
	DeclareVarInst(struct, float, fRec133[3])
	DeclareVarInst(struct, "float", fConst320)
	DeclareVarInst(struct, float, fRec132[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, "float", fConst321)
	DeclareVarInst(struct, "float", fConst322)
	DeclareVarInst(struct, "float", fConst323)
	DeclareVarInst(struct, "float", fConst324)
	DeclareVarInst(struct, "float", fConst325)
	DeclareVarInst(struct, "float", fConst326)
	DeclareVarInst(struct, "float", fConst327)
	DeclareVarInst(struct, "float", fConst328)
	DeclareVarInst(struct, "float", fConst329)
	DeclareVarInst(struct, "float", fConst330)
	DeclareVarInst(struct, "float", fConst331)
	DeclareVarInst(struct, "float", fConst332)
	DeclareVarInst(struct, "float", fConst333)
	DeclareVarInst(struct, "float", fConst334)
	DeclareVarInst(struct, "float", fConst335)
	DeclareVarInst(struct, "float", fConst336)
	DeclareVarInst(struct, "float", fConst337)
	DeclareVarInst(struct, "float", fConst338)
	DeclareVarInst(struct, "float", fConst339)
	DeclareVarInst(struct, "float", fConst340)
	DeclareVarInst(struct, "float", fConst341)
	DeclareVarInst(struct, float, fRec145[3])
	DeclareVarInst(struct, "float", fConst342)
	DeclareVarInst(struct, "float", fConst343)
	DeclareVarInst(struct, "float", fConst344)
	DeclareVarInst(struct, float, fRec144[3])
	DeclareVarInst(struct, "float", fConst345)
	DeclareVarInst(struct, "float", fConst346)
	DeclareVarInst(struct, "float", fConst347)
	DeclareVarInst(struct, float, fRec143[3])
	DeclareVarInst(struct, "float", fConst348)
	DeclareVarInst(struct, "float", fConst349)
	DeclareVarInst(struct, "float", fConst350)
	DeclareVarInst(struct, "float", fConst351)
	DeclareVarInst(struct, float, fRec142[3])
	DeclareVarInst(struct, "float", fConst352)
	DeclareVarInst(struct, "float", fConst353)
	DeclareVarInst(struct, "float", fConst354)
	DeclareVarInst(struct, float, fRec141[3])
	DeclareVarInst(struct, "float", fConst355)
	DeclareVarInst(struct, "float", fConst356)
	DeclareVarInst(struct, "float", fConst357)
	DeclareVarInst(struct, float, fRec140[3])
	DeclareVarInst(struct, "float", fConst358)
	DeclareVarInst(struct, float, fRec139[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, "float", fConst359)
	DeclareVarInst(struct, "float", fConst360)
	DeclareVarInst(struct, "float", fConst361)
	DeclareVarInst(struct, "float", fConst362)
	DeclareVarInst(struct, "float", fConst363)
	DeclareVarInst(struct, "float", fConst364)
	DeclareVarInst(struct, "float", fConst365)
	DeclareVarInst(struct, "float", fConst366)
	DeclareVarInst(struct, "float", fConst367)
	DeclareVarInst(struct, "float", fConst368)
	DeclareVarInst(struct, "float", fConst369)
	DeclareVarInst(struct, "float", fConst370)
	DeclareVarInst(struct, "float", fConst371)
	DeclareVarInst(struct, "float", fConst372)
	DeclareVarInst(struct, "float", fConst373)
	DeclareVarInst(struct, "float", fConst374)
	DeclareVarInst(struct, "float", fConst375)
	DeclareVarInst(struct, "float", fConst376)
	DeclareVarInst(struct, "float", fConst377)
	DeclareVarInst(struct, "float", fConst378)
	DeclareVarInst(struct, "float", fConst379)
	DeclareVarInst(struct, float, fRec152[3])
	DeclareVarInst(struct, "float", fConst380)
	DeclareVarInst(struct, "float", fConst381)
	DeclareVarInst(struct, "float", fConst382)
	DeclareVarInst(struct, float, fRec151[3])
	DeclareVarInst(struct, "float", fConst383)
	DeclareVarInst(struct, "float", fConst384)
	DeclareVarInst(struct, "float", fConst385)
	DeclareVarInst(struct, float, fRec150[3])
	DeclareVarInst(struct, "float", fConst386)
	DeclareVarInst(struct, "float", fConst387)
	DeclareVarInst(struct, "float", fConst388)
	DeclareVarInst(struct, "float", fConst389)
	DeclareVarInst(struct, float, fRec149[3])
	DeclareVarInst(struct, "float", fConst390)
	DeclareVarInst(struct, "float", fConst391)
	DeclareVarInst(struct, "float", fConst392)
	DeclareVarInst(struct, float, fRec148[3])
	DeclareVarInst(struct, "float", fConst393)
	DeclareVarInst(struct, "float", fConst394)
	DeclareVarInst(struct, "float", fConst395)
	DeclareVarInst(struct, float, fRec147[3])
	DeclareVarInst(struct, "float", fConst396)
	DeclareVarInst(struct, float, fRec146[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, "float", fConst397)
	DeclareVarInst(struct, "float", fConst398)
	DeclareVarInst(struct, "float", fConst399)
	DeclareVarInst(struct, "float", fConst400)
	DeclareVarInst(struct, "float", fConst401)
	DeclareVarInst(struct, "float", fConst402)
	DeclareVarInst(struct, "float", fConst403)
	DeclareVarInst(struct, "float", fConst404)
	DeclareVarInst(struct, "float", fConst405)
	DeclareVarInst(struct, "float", fConst406)
	DeclareVarInst(struct, "float", fConst407)
	DeclareVarInst(struct, "float", fConst408)
	DeclareVarInst(struct, "float", fConst409)
	DeclareVarInst(struct, "float", fConst410)
	DeclareVarInst(struct, "float", fConst411)
	DeclareVarInst(struct, "float", fConst412)
	DeclareVarInst(struct, "float", fConst413)
	DeclareVarInst(struct, "float", fConst414)
	DeclareVarInst(struct, "float", fConst415)
	DeclareVarInst(struct, "float", fConst416)
	DeclareVarInst(struct, "float", fConst417)
	DeclareVarInst(struct, float, fRec159[3])
	DeclareVarInst(struct, "float", fConst418)
	DeclareVarInst(struct, "float", fConst419)
	DeclareVarInst(struct, "float", fConst420)
	DeclareVarInst(struct, float, fRec158[3])
	DeclareVarInst(struct, "float", fConst421)
	DeclareVarInst(struct, "float", fConst422)
	DeclareVarInst(struct, "float", fConst423)
	DeclareVarInst(struct, float, fRec157[3])
	DeclareVarInst(struct, "float", fConst424)
	DeclareVarInst(struct, "float", fConst425)
	DeclareVarInst(struct, "float", fConst426)
	DeclareVarInst(struct, "float", fConst427)
	DeclareVarInst(struct, float, fRec156[3])
	DeclareVarInst(struct, "float", fConst428)
	DeclareVarInst(struct, "float", fConst429)
	DeclareVarInst(struct, "float", fConst430)
	DeclareVarInst(struct, float, fRec155[3])
	DeclareVarInst(struct, "float", fConst431)
	DeclareVarInst(struct, "float", fConst432)
	DeclareVarInst(struct, "float", fConst433)
	DeclareVarInst(struct, float, fRec154[3])
	DeclareVarInst(struct, "float", fConst434)
	DeclareVarInst(struct, float, fRec153[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, "float", fConst435)
	DeclareVarInst(struct, "float", fConst436)
	DeclareVarInst(struct, "float", fConst437)
	DeclareVarInst(struct, "float", fConst438)
	DeclareVarInst(struct, "float", fConst439)
	DeclareVarInst(struct, "float", fConst440)
	DeclareVarInst(struct, "float", fConst441)
	DeclareVarInst(struct, "float", fConst442)
	DeclareVarInst(struct, "float", fConst443)
	DeclareVarInst(struct, "float", fConst444)
	DeclareVarInst(struct, "float", fConst445)
	DeclareVarInst(struct, "float", fConst446)
	DeclareVarInst(struct, "float", fConst447)
	DeclareVarInst(struct, "float", fConst448)
	DeclareVarInst(struct, "float", fConst449)
	DeclareVarInst(struct, "float", fConst450)
	DeclareVarInst(struct, "float", fConst451)
	DeclareVarInst(struct, "float", fConst452)
	DeclareVarInst(struct, "float", fConst453)
	DeclareVarInst(struct, "float", fConst454)
	DeclareVarInst(struct, "float", fConst455)
	DeclareVarInst(struct, float, fRec166[3])
	DeclareVarInst(struct, "float", fConst456)
	DeclareVarInst(struct, "float", fConst457)
	DeclareVarInst(struct, "float", fConst458)
	DeclareVarInst(struct, float, fRec165[3])
	DeclareVarInst(struct, "float", fConst459)
	DeclareVarInst(struct, "float", fConst460)
	DeclareVarInst(struct, "float", fConst461)
	DeclareVarInst(struct, float, fRec164[3])
	DeclareVarInst(struct, "float", fConst462)
	DeclareVarInst(struct, "float", fConst463)
	DeclareVarInst(struct, "float", fConst464)
	DeclareVarInst(struct, "float", fConst465)
	DeclareVarInst(struct, float, fRec163[3])
	DeclareVarInst(struct, "float", fConst466)
	DeclareVarInst(struct, "float", fConst467)
	DeclareVarInst(struct, "float", fConst468)
	DeclareVarInst(struct, float, fRec162[3])
	DeclareVarInst(struct, "float", fConst469)
	DeclareVarInst(struct, "float", fConst470)
	DeclareVarInst(struct, "float", fConst471)
	DeclareVarInst(struct, float, fRec161[3])
	DeclareVarInst(struct, "float", fConst472)
	DeclareVarInst(struct, float, fRec160[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph8)
	DeclareVarInst(struct, "float", fConst473)
	DeclareVarInst(struct, "float", fConst474)
	DeclareVarInst(struct, "float", fConst475)
	DeclareVarInst(struct, "float", fConst476)
	DeclareVarInst(struct, "float", fConst477)
	DeclareVarInst(struct, "float", fConst478)
	DeclareVarInst(struct, "float", fConst479)
	DeclareVarInst(struct, "float", fConst480)
	DeclareVarInst(struct, "float", fConst481)
	DeclareVarInst(struct, "float", fConst482)
	DeclareVarInst(struct, "float", fConst483)
	DeclareVarInst(struct, "float", fConst484)
	DeclareVarInst(struct, "float", fConst485)
	DeclareVarInst(struct, "float", fConst486)
	DeclareVarInst(struct, "float", fConst487)
	DeclareVarInst(struct, "float", fConst488)
	DeclareVarInst(struct, "float", fConst489)
	DeclareVarInst(struct, "float", fConst490)
	DeclareVarInst(struct, "float", fConst491)
	DeclareVarInst(struct, "float", fConst492)
	DeclareVarInst(struct, "float", fConst493)
	DeclareVarInst(struct, float, fRec173[3])
	DeclareVarInst(struct, "float", fConst494)
	DeclareVarInst(struct, "float", fConst495)
	DeclareVarInst(struct, "float", fConst496)
	DeclareVarInst(struct, float, fRec172[3])
	DeclareVarInst(struct, "float", fConst497)
	DeclareVarInst(struct, "float", fConst498)
	DeclareVarInst(struct, "float", fConst499)
	DeclareVarInst(struct, float, fRec171[3])
	DeclareVarInst(struct, "float", fConst500)
	DeclareVarInst(struct, "float", fConst501)
	DeclareVarInst(struct, "float", fConst502)
	DeclareVarInst(struct, "float", fConst503)
	DeclareVarInst(struct, float, fRec170[3])
	DeclareVarInst(struct, "float", fConst504)
	DeclareVarInst(struct, "float", fConst505)
	DeclareVarInst(struct, "float", fConst506)
	DeclareVarInst(struct, float, fRec169[3])
	DeclareVarInst(struct, "float", fConst507)
	DeclareVarInst(struct, "float", fConst508)
	DeclareVarInst(struct, "float", fConst509)
	DeclareVarInst(struct, float, fRec168[3])
	DeclareVarInst(struct, "float", fConst510)
	DeclareVarInst(struct, float, fRec167[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph9)
	DeclareVarInst(struct, "float", fConst511)
	DeclareVarInst(struct, "float", fConst512)
	DeclareVarInst(struct, "float", fConst513)
	DeclareVarInst(struct, "float", fConst514)
	DeclareVarInst(struct, "float", fConst515)
	DeclareVarInst(struct, "float", fConst516)
	DeclareVarInst(struct, "float", fConst517)
	DeclareVarInst(struct, "float", fConst518)
	DeclareVarInst(struct, "float", fConst519)
	DeclareVarInst(struct, "float", fConst520)
	DeclareVarInst(struct, "float", fConst521)
	DeclareVarInst(struct, "float", fConst522)
	DeclareVarInst(struct, "float", fConst523)
	DeclareVarInst(struct, "float", fConst524)
	DeclareVarInst(struct, "float", fConst525)
	DeclareVarInst(struct, "float", fConst526)
	DeclareVarInst(struct, "float", fConst527)
	DeclareVarInst(struct, "float", fConst528)
	DeclareVarInst(struct, "float", fConst529)
	DeclareVarInst(struct, "float", fConst530)
	DeclareVarInst(struct, "float", fConst531)
	DeclareVarInst(struct, float, fRec180[3])
	DeclareVarInst(struct, "float", fConst532)
	DeclareVarInst(struct, "float", fConst533)
	DeclareVarInst(struct, "float", fConst534)
	DeclareVarInst(struct, float, fRec179[3])
	DeclareVarInst(struct, "float", fConst535)
	DeclareVarInst(struct, "float", fConst536)
	DeclareVarInst(struct, "float", fConst537)
	DeclareVarInst(struct, float, fRec178[3])
	DeclareVarInst(struct, "float", fConst538)
	DeclareVarInst(struct, "float", fConst539)
	DeclareVarInst(struct, "float", fConst540)
	DeclareVarInst(struct, "float", fConst541)
	DeclareVarInst(struct, float, fRec177[3])
	DeclareVarInst(struct, "float", fConst542)
	DeclareVarInst(struct, "float", fConst543)
	DeclareVarInst(struct, "float", fConst544)
	DeclareVarInst(struct, float, fRec176[3])
	DeclareVarInst(struct, "float", fConst545)
	DeclareVarInst(struct, "float", fConst546)
	DeclareVarInst(struct, "float", fConst547)
	DeclareVarInst(struct, float, fRec175[3])
	DeclareVarInst(struct, "float", fConst548)
	DeclareVarInst(struct, float, fRec174[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph10)
	DeclareVarInst(struct, "float", fConst549)
	DeclareVarInst(struct, "float", fConst550)
	DeclareVarInst(struct, "float", fConst551)
	DeclareVarInst(struct, "float", fConst552)
	DeclareVarInst(struct, "float", fConst553)
	DeclareVarInst(struct, "float", fConst554)
	DeclareVarInst(struct, "float", fConst555)
	DeclareVarInst(struct, "float", fConst556)
	DeclareVarInst(struct, "float", fConst557)
	DeclareVarInst(struct, "float", fConst558)
	DeclareVarInst(struct, "float", fConst559)
	DeclareVarInst(struct, "float", fConst560)
	DeclareVarInst(struct, "float", fConst561)
	DeclareVarInst(struct, "float", fConst562)
	DeclareVarInst(struct, "float", fConst563)
	DeclareVarInst(struct, "float", fConst564)
	DeclareVarInst(struct, "float", fConst565)
	DeclareVarInst(struct, "float", fConst566)
	DeclareVarInst(struct, "float", fConst567)
	DeclareVarInst(struct, "float", fConst568)
	DeclareVarInst(struct, "float", fConst569)
	DeclareVarInst(struct, float, fRec187[3])
	DeclareVarInst(struct, "float", fConst570)
	DeclareVarInst(struct, "float", fConst571)
	DeclareVarInst(struct, "float", fConst572)
	DeclareVarInst(struct, float, fRec186[3])
	DeclareVarInst(struct, "float", fConst573)
	DeclareVarInst(struct, "float", fConst574)
	DeclareVarInst(struct, "float", fConst575)
	DeclareVarInst(struct, float, fRec185[3])
	DeclareVarInst(struct, "float", fConst576)
	DeclareVarInst(struct, "float", fConst577)
	DeclareVarInst(struct, "float", fConst578)
	DeclareVarInst(struct, "float", fConst579)
	DeclareVarInst(struct, float, fRec184[3])
	DeclareVarInst(struct, "float", fConst580)
	DeclareVarInst(struct, "float", fConst581)
	DeclareVarInst(struct, "float", fConst582)
	DeclareVarInst(struct, float, fRec183[3])
	DeclareVarInst(struct, "float", fConst583)
	DeclareVarInst(struct, "float", fConst584)
	DeclareVarInst(struct, "float", fConst585)
	DeclareVarInst(struct, float, fRec182[3])
	DeclareVarInst(struct, "float", fConst586)
	DeclareVarInst(struct, float, fRec181[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph11)
	DeclareVarInst(struct, "float", fConst587)
	DeclareVarInst(struct, "float", fConst588)
	DeclareVarInst(struct, "float", fConst589)
	DeclareVarInst(struct, "float", fConst590)
	DeclareVarInst(struct, "float", fConst591)
	DeclareVarInst(struct, "float", fConst592)
	DeclareVarInst(struct, "float", fConst593)
	DeclareVarInst(struct, "float", fConst594)
	DeclareVarInst(struct, "float", fConst595)
	DeclareVarInst(struct, "float", fConst596)
	DeclareVarInst(struct, "float", fConst597)
	DeclareVarInst(struct, "float", fConst598)
	DeclareVarInst(struct, "float", fConst599)
	DeclareVarInst(struct, "float", fConst600)
	DeclareVarInst(struct, "float", fConst601)
	DeclareVarInst(struct, "float", fConst602)
	DeclareVarInst(struct, "float", fConst603)
	DeclareVarInst(struct, "float", fConst604)
	DeclareVarInst(struct, "float", fConst605)
	DeclareVarInst(struct, "float", fConst606)
	DeclareVarInst(struct, "float", fConst607)
	DeclareVarInst(struct, float, fRec194[3])
	DeclareVarInst(struct, "float", fConst608)
	DeclareVarInst(struct, "float", fConst609)
	DeclareVarInst(struct, "float", fConst610)
	DeclareVarInst(struct, float, fRec193[3])
	DeclareVarInst(struct, "float", fConst611)
	DeclareVarInst(struct, "float", fConst612)
	DeclareVarInst(struct, "float", fConst613)
	DeclareVarInst(struct, float, fRec192[3])
	DeclareVarInst(struct, "float", fConst614)
	DeclareVarInst(struct, "float", fConst615)
	DeclareVarInst(struct, "float", fConst616)
	DeclareVarInst(struct, "float", fConst617)
	DeclareVarInst(struct, float, fRec191[3])
	DeclareVarInst(struct, "float", fConst618)
	DeclareVarInst(struct, "float", fConst619)
	DeclareVarInst(struct, "float", fConst620)
	DeclareVarInst(struct, float, fRec190[3])
	DeclareVarInst(struct, "float", fConst621)
	DeclareVarInst(struct, "float", fConst622)
	DeclareVarInst(struct, "float", fConst623)
	DeclareVarInst(struct, float, fRec189[3])
	DeclareVarInst(struct, "float", fConst624)
	DeclareVarInst(struct, float, fRec188[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph12)
	DeclareVarInst(struct, "float", fConst625)
	DeclareVarInst(struct, "float", fConst626)
	DeclareVarInst(struct, "float", fConst627)
	DeclareVarInst(struct, "float", fConst628)
	DeclareVarInst(struct, "float", fConst629)
	DeclareVarInst(struct, "float", fConst630)
	DeclareVarInst(struct, "float", fConst631)
	DeclareVarInst(struct, "float", fConst632)
	DeclareVarInst(struct, "float", fConst633)
	DeclareVarInst(struct, "float", fConst634)
	DeclareVarInst(struct, "float", fConst635)
	DeclareVarInst(struct, "float", fConst636)
	DeclareVarInst(struct, "float", fConst637)
	DeclareVarInst(struct, "float", fConst638)
	DeclareVarInst(struct, "float", fConst639)
	DeclareVarInst(struct, "float", fConst640)
	DeclareVarInst(struct, "float", fConst641)
	DeclareVarInst(struct, "float", fConst642)
	DeclareVarInst(struct, "float", fConst643)
	DeclareVarInst(struct, "float", fConst644)
	DeclareVarInst(struct, "float", fConst645)
	DeclareVarInst(struct, float, fRec201[3])
	DeclareVarInst(struct, "float", fConst646)
	DeclareVarInst(struct, "float", fConst647)
	DeclareVarInst(struct, "float", fConst648)
	DeclareVarInst(struct, float, fRec200[3])
	DeclareVarInst(struct, "float", fConst649)
	DeclareVarInst(struct, "float", fConst650)
	DeclareVarInst(struct, "float", fConst651)
	DeclareVarInst(struct, float, fRec199[3])
	DeclareVarInst(struct, "float", fConst652)
	DeclareVarInst(struct, "float", fConst653)
	DeclareVarInst(struct, "float", fConst654)
	DeclareVarInst(struct, "float", fConst655)
	DeclareVarInst(struct, float, fRec198[3])
	DeclareVarInst(struct, "float", fConst656)
	DeclareVarInst(struct, "float", fConst657)
	DeclareVarInst(struct, "float", fConst658)
	DeclareVarInst(struct, float, fRec197[3])
	DeclareVarInst(struct, "float", fConst659)
	DeclareVarInst(struct, "float", fConst660)
	DeclareVarInst(struct, "float", fConst661)
	DeclareVarInst(struct, float, fRec196[3])
	DeclareVarInst(struct, "float", fConst662)
	DeclareVarInst(struct, float, fRec195[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph13)
	DeclareVarInst(struct, "float", fConst663)
	DeclareVarInst(struct, "float", fConst664)
	DeclareVarInst(struct, "float", fConst665)
	DeclareVarInst(struct, "float", fConst666)
	DeclareVarInst(struct, "float", fConst667)
	DeclareVarInst(struct, "float", fConst668)
	DeclareVarInst(struct, "float", fConst669)
	DeclareVarInst(struct, "float", fConst670)
	DeclareVarInst(struct, "float", fConst671)
	DeclareVarInst(struct, float, fRec205[3])
	DeclareVarInst(struct, "float", fConst672)
	DeclareVarInst(struct, "float", fConst673)
	DeclareVarInst(struct, "float", fConst674)
	DeclareVarInst(struct, float, fRec204[3])
	DeclareVarInst(struct, "float", fConst675)
	DeclareVarInst(struct, "float", fConst676)
	DeclareVarInst(struct, "float", fConst677)
	DeclareVarInst(struct, float, fRec203[3])
	DeclareVarInst(struct, "float", fConst678)
	DeclareVarInst(struct, float, fRec202[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph14)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getInputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getOutputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, FunCallInst("tanf", BinopInst("/", Float(50265.4844f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.157482162f)), LoadVarInst(struct, fConst2)), Float(0.935140193f))))
	StoreVarInst(struct, fConst5, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst6))))
	StoreVarInst(struct, fConst8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.743130445f)), LoadVarInst(struct, fConst2)), Float(1.4500711f))))
	StoreVarInst(struct, fConst9, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst10, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst9))))
	StoreVarInst(struct, fConst11, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(3.18972731f)), LoadVarInst(struct, fConst2)), Float(4.07678175f))))
	StoreVarInst(struct, fConst12, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst13, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst12))))
	StoreVarInst(struct, fConst14, FunCallInst("tanf", BinopInst("/", Float(245.43692f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst15, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst14)))
	StoreVarInst(struct, fConst16, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(0.618034005f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst17, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst16)))
	StoreVarInst(struct, fConst18, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst14))))
	StoreVarInst(struct, fConst19, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst18))))
	StoreVarInst(struct, fConst20, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f))))
	StoreVarInst(struct, fConst21, FunCallInst("tanf", BinopInst("/", Float(490.87384f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst22, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst21)))
	StoreVarInst(struct, fConst23, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst24, BinopInst("+", LoadVarInst(struct, fConst15), Float(1.0f)))
	StoreVarInst(struct, fConst25, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst23), LoadVarInst(struct, fConst24))))
	StoreVarInst(struct, fConst26, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst27, BinopInst("+", LoadVarInst(struct, fConst22), Float(1.0f)))
	StoreVarInst(struct, fConst28, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst22)), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst29, FunCallInst("tanf", BinopInst("/", Float(981.747681f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst30, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst29)))
	StoreVarInst(struct, fConst31, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(0.618034005f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst32, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst33, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f))))
	StoreVarInst(struct, fConst34, BinopInst("+", LoadVarInst(struct, fConst30), Float(1.0f)))
	StoreVarInst(struct, fConst35, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst30)), LoadVarInst(struct, fConst34))))
	StoreVarInst(struct, fConst36, FunCallInst("tanf", BinopInst("/", Float(1963.49536f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst37, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst36)))
	StoreVarInst(struct, fConst38, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(0.618034005f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst39, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fConst34))))
	StoreVarInst(struct, fConst40, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f))))
	StoreVarInst(struct, fConst41, BinopInst("+", LoadVarInst(struct, fConst37), Float(1.0f)))
	StoreVarInst(struct, fConst42, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst37)), LoadVarInst(struct, fConst41))))
	StoreVarInst(struct, fConst43, FunCallInst("tanf", BinopInst("/", Float(3926.99072f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst44, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst43)))
	StoreVarInst(struct, fConst45, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(0.618034005f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst46, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst45), LoadVarInst(struct, fConst41))))
	StoreVarInst(struct, fConst47, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f))))
	StoreVarInst(struct, fConst48, BinopInst("+", LoadVarInst(struct, fConst44), Float(1.0f)))
	StoreVarInst(struct, fConst49, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst44)), LoadVarInst(struct, fConst48))))
	StoreVarInst(struct, fConst50, FunCallInst("tanf", BinopInst("/", Float(7853.98145f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst51, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst50)))
	StoreVarInst(struct, fConst52, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(0.618034005f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst53, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst52), LoadVarInst(struct, fConst48))))
	StoreVarInst(struct, fConst54, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f))))
	StoreVarInst(struct, fConst55, BinopInst("+", LoadVarInst(struct, fConst51), Float(1.0f)))
	StoreVarInst(struct, fConst56, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst51)), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst57, FunCallInst("tanf", BinopInst("/", Float(15707.9629f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst58, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst57)))
	StoreVarInst(struct, fConst59, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst60, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst59), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst61, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst62, BinopInst("+", LoadVarInst(struct, fConst58), Float(1.0f)))
	StoreVarInst(struct, fConst63, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst58)), LoadVarInst(struct, fConst62))))
	StoreVarInst(struct, fConst64, FunCallInst("tanf", BinopInst("/", Float(31415.9258f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst65, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst64)))
	StoreVarInst(struct, fConst66, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(0.618034005f)), LoadVarInst(struct, fConst64)), Float(1.0f)))
	StoreVarInst(struct, fConst67, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst66), LoadVarInst(struct, fConst62))))
	StoreVarInst(struct, fConst68, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(1.61803401f)), LoadVarInst(struct, fConst64)), Float(1.0f))))
	StoreVarInst(struct, fConst69, BinopInst("+", LoadVarInst(struct, fConst65), Float(1.0f)))
	StoreVarInst(struct, fConst70, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst65)), LoadVarInst(struct, fConst69))))
	StoreVarInst(struct, fConst71, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst69)))
	StoreVarInst(struct, fConst72, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst73, BinopInst("*", Float(0.25f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst74, BinopInst("*", Float(0.0416666679f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst75, BinopInst("*", Float(0.00520833349f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst76, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst64))))
	StoreVarInst(struct, fConst77, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst76))))
	StoreVarInst(struct, fConst78, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(-1.61803401f)), LoadVarInst(struct, fConst64)), Float(1.0f)))
	StoreVarInst(struct, fConst79, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst66)))
	StoreVarInst(struct, fConst80, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(-0.618034005f)), LoadVarInst(struct, fConst64)), Float(1.0f)))
	StoreVarInst(struct, fConst81, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst57))))
	StoreVarInst(struct, fConst82, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst81))))
	StoreVarInst(struct, fConst83, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst84, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst59)))
	StoreVarInst(struct, fConst85, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst86, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst50))))
	StoreVarInst(struct, fConst87, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst86))))
	StoreVarInst(struct, fConst88, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(-1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst89, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst52)))
	StoreVarInst(struct, fConst90, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(-0.618034005f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst91, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst92, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst91))))
	StoreVarInst(struct, fConst93, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(-1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst94, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst45)))
	StoreVarInst(struct, fConst95, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(-0.618034005f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst96, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst36))))
	StoreVarInst(struct, fConst97, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst96))))
	StoreVarInst(struct, fConst98, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(-1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst99, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst38)))
	StoreVarInst(struct, fConst100, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(-0.618034005f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst101, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst29))))
	StoreVarInst(struct, fConst102, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst101))))
	StoreVarInst(struct, fConst103, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(-1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst104, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst31)))
	StoreVarInst(struct, fConst105, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(-0.618034005f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst106, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst21))))
	StoreVarInst(struct, fConst107, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst106))))
	StoreVarInst(struct, fConst108, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst109, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst23)))
	StoreVarInst(struct, fConst110, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst111, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst112, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst15)), LoadVarInst(struct, fConst24))))
	StoreVarInst(struct, fConst113, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst18))))
	StoreVarInst(struct, fConst114, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(-1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst115, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(-0.618034005f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst116, FunCallInst("tanf", BinopInst("/", Float(122.71846f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst117, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst116)))
	StoreVarInst(struct, fConst118, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f))))
	StoreVarInst(struct, fConst119, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst116))))
	StoreVarInst(struct, fConst120, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst119))))
	StoreVarInst(struct, fConst121, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(-1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f)))
	StoreVarInst(struct, fConst122, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(0.618034005f)), LoadVarInst(struct, fConst116)), Float(1.0f))))
	StoreVarInst(struct, fConst123, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst119))))
	StoreVarInst(struct, fConst124, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f))))
	StoreVarInst(struct, fConst125, BinopInst("+", LoadVarInst(struct, fConst117), Float(1.0f)))
	StoreVarInst(struct, fConst126, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst117)), LoadVarInst(struct, fConst125))))
	StoreVarInst(struct, fConst127, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst16), LoadVarInst(struct, fConst125))))
	StoreVarInst(struct, fConst128, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst117)))
	StoreVarInst(struct, fConst129, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(-1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f)))
	StoreVarInst(struct, fConst130, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(-0.618034005f)), LoadVarInst(struct, fConst116)), Float(1.0f)))
	StoreVarInst(struct, fConst131, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst76))))
	StoreVarInst(struct, fConst132, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst65)))
	StoreVarInst(struct, fConst133, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f))))
	StoreVarInst(struct, fConst134, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(-1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst135, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst136, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst137, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f))))
	StoreVarInst(struct, fConst138, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(-1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst139, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f))))
	StoreVarInst(struct, fConst140, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(-1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst141, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f))))
	StoreVarInst(struct, fConst142, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(-1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst143, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f))))
	StoreVarInst(struct, fConst144, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(-1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst145, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst146, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst147, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst81))))
	StoreVarInst(struct, fConst148, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst58)))
	StoreVarInst(struct, fConst149, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst86))))
	StoreVarInst(struct, fConst150, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst151, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst91))))
	StoreVarInst(struct, fConst152, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst44)))
	StoreVarInst(struct, fConst153, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst96))))
	StoreVarInst(struct, fConst154, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst37)))
	StoreVarInst(struct, fConst155, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst101))))
	StoreVarInst(struct, fConst156, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst30)))
	StoreVarInst(struct, fConst157, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst106))))
	StoreVarInst(struct, fConst158, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst22)))
	StoreVarInst(struct, fConst159, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-3.18972731f)), LoadVarInst(struct, fConst2)), Float(4.07678175f)))
	StoreVarInst(struct, fConst160, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst161, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst162, BinopInst("+", LoadVarInst(struct, fConst12), Float(0.000407678192f)))
	StoreVarInst(struct, fConst163, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.743130445f)), LoadVarInst(struct, fConst2)), Float(1.4500711f)))
	StoreVarInst(struct, fConst164, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst165, BinopInst("+", LoadVarInst(struct, fConst9), Float(1.4500711f)))
	StoreVarInst(struct, fConst166, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.157482162f)), LoadVarInst(struct, fConst2)), Float(0.935140193f)))
	StoreVarInst(struct, fConst167, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst168, BinopInst("+", LoadVarInst(struct, fConst6), Float(0.935140193f)))
	StoreVarInst(struct, fConst169, FunCallInst("tanf", BinopInst("/", Float(31665.2695f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst170, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst169)))
	StoreVarInst(struct, fConst171, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.157482162f)), LoadVarInst(struct, fConst169)), Float(0.935140193f))))
	StoreVarInst(struct, fConst172, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst169)))
	StoreVarInst(struct, fConst173, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst174, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst173))))
	StoreVarInst(struct, fConst175, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.743130445f)), LoadVarInst(struct, fConst169)), Float(1.4500711f))))
	StoreVarInst(struct, fConst176, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst177, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst176))))
	StoreVarInst(struct, fConst178, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(3.18972731f)), LoadVarInst(struct, fConst169)), Float(4.07678175f))))
	StoreVarInst(struct, fConst179, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst180, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst179))))
	StoreVarInst(struct, fConst181, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.168404877f)), LoadVarInst(struct, fConst2)), Float(1.06935835f))))
	StoreVarInst(struct, fConst182, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst183, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.51247865f)), LoadVarInst(struct, fConst2)), Float(0.689621389f))))
	StoreVarInst(struct, fConst184, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst185, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.782413065f)), LoadVarInst(struct, fConst2)), Float(0.245291501f))))
	StoreVarInst(struct, fConst186, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst187, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst186))))
	StoreVarInst(struct, fConst188, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.782413065f)), LoadVarInst(struct, fConst2)), Float(0.245291501f)))
	StoreVarInst(struct, fConst189, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst190, BinopInst("+", LoadVarInst(struct, fConst186), Float(0.000433227193f)))
	StoreVarInst(struct, fConst191, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.51247865f)), LoadVarInst(struct, fConst2)), Float(0.689621389f)))
	StoreVarInst(struct, fConst192, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst193, BinopInst("+", LoadVarInst(struct, fConst160), Float(7.62173128f)))
	StoreVarInst(struct, fConst194, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.168404877f)), LoadVarInst(struct, fConst2)), Float(1.06935835f)))
	StoreVarInst(struct, fConst195, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst196, BinopInst("+", LoadVarInst(struct, fConst160), Float(53.5361519f)))
	StoreVarInst(struct, fConst197, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-3.18972731f)), LoadVarInst(struct, fConst169)), Float(4.07678175f)))
	StoreVarInst(struct, fConst198, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst199, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst200, BinopInst("+", LoadVarInst(struct, fConst179), Float(0.000407678192f)))
	StoreVarInst(struct, fConst201, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.743130445f)), LoadVarInst(struct, fConst169)), Float(1.4500711f)))
	StoreVarInst(struct, fConst202, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst203, BinopInst("+", LoadVarInst(struct, fConst176), Float(1.4500711f)))
	StoreVarInst(struct, fConst204, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.157482162f)), LoadVarInst(struct, fConst169)), Float(0.935140193f)))
	StoreVarInst(struct, fConst205, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst206, BinopInst("+", LoadVarInst(struct, fConst173), Float(0.935140193f)))
	StoreVarInst(struct, fConst207, FunCallInst("tanf", BinopInst("/", Float(19947.8691f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst208, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst207)))
	StoreVarInst(struct, fConst209, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.157482162f)), LoadVarInst(struct, fConst207)), Float(0.935140193f))))
	StoreVarInst(struct, fConst210, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst207)))
	StoreVarInst(struct, fConst211, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst212, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst211))))
	StoreVarInst(struct, fConst213, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.743130445f)), LoadVarInst(struct, fConst207)), Float(1.4500711f))))
	StoreVarInst(struct, fConst214, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst215, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst214))))
	StoreVarInst(struct, fConst216, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(3.18972731f)), LoadVarInst(struct, fConst207)), Float(4.07678175f))))
	StoreVarInst(struct, fConst217, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst218, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst217))))
	StoreVarInst(struct, fConst219, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.168404877f)), LoadVarInst(struct, fConst169)), Float(1.06935835f))))
	StoreVarInst(struct, fConst220, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst221, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.51247865f)), LoadVarInst(struct, fConst169)), Float(0.689621389f))))
	StoreVarInst(struct, fConst222, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst223, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.782413065f)), LoadVarInst(struct, fConst169)), Float(0.245291501f))))
	StoreVarInst(struct, fConst224, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst225, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst224))))
	StoreVarInst(struct, fConst226, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.782413065f)), LoadVarInst(struct, fConst169)), Float(0.245291501f)))
	StoreVarInst(struct, fConst227, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst228, BinopInst("+", LoadVarInst(struct, fConst224), Float(0.000433227193f)))
	StoreVarInst(struct, fConst229, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.51247865f)), LoadVarInst(struct, fConst169)), Float(0.689621389f)))
	StoreVarInst(struct, fConst230, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst231, BinopInst("+", LoadVarInst(struct, fConst198), Float(7.62173128f)))
	StoreVarInst(struct, fConst232, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.168404877f)), LoadVarInst(struct, fConst169)), Float(1.06935835f)))
	StoreVarInst(struct, fConst233, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst234, BinopInst("+", LoadVarInst(struct, fConst198), Float(53.5361519f)))
	StoreVarInst(struct, fConst235, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-3.18972731f)), LoadVarInst(struct, fConst207)), Float(4.07678175f)))
	StoreVarInst(struct, fConst236, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst237, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst238, BinopInst("+", LoadVarInst(struct, fConst217), Float(0.000407678192f)))
	StoreVarInst(struct, fConst239, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.743130445f)), LoadVarInst(struct, fConst207)), Float(1.4500711f)))
	StoreVarInst(struct, fConst240, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst241, BinopInst("+", LoadVarInst(struct, fConst214), Float(1.4500711f)))
	StoreVarInst(struct, fConst242, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.157482162f)), LoadVarInst(struct, fConst207)), Float(0.935140193f)))
	StoreVarInst(struct, fConst243, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst244, BinopInst("+", LoadVarInst(struct, fConst211), Float(0.935140193f)))
	StoreVarInst(struct, fConst245, FunCallInst("tanf", BinopInst("/", Float(12566.3711f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst246, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst245)))
	StoreVarInst(struct, fConst247, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.157482162f)), LoadVarInst(struct, fConst245)), Float(0.935140193f))))
	StoreVarInst(struct, fConst248, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst245)))
	StoreVarInst(struct, fConst249, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst250, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst249))))
	StoreVarInst(struct, fConst251, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.743130445f)), LoadVarInst(struct, fConst245)), Float(1.4500711f))))
	StoreVarInst(struct, fConst252, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst253, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst252))))
	StoreVarInst(struct, fConst254, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(3.18972731f)), LoadVarInst(struct, fConst245)), Float(4.07678175f))))
	StoreVarInst(struct, fConst255, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst256, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst255))))
	StoreVarInst(struct, fConst257, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.168404877f)), LoadVarInst(struct, fConst207)), Float(1.06935835f))))
	StoreVarInst(struct, fConst258, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst259, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.51247865f)), LoadVarInst(struct, fConst207)), Float(0.689621389f))))
	StoreVarInst(struct, fConst260, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst261, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.782413065f)), LoadVarInst(struct, fConst207)), Float(0.245291501f))))
	StoreVarInst(struct, fConst262, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst263, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst262))))
	StoreVarInst(struct, fConst264, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.782413065f)), LoadVarInst(struct, fConst207)), Float(0.245291501f)))
	StoreVarInst(struct, fConst265, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst266, BinopInst("+", LoadVarInst(struct, fConst262), Float(0.000433227193f)))
	StoreVarInst(struct, fConst267, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.51247865f)), LoadVarInst(struct, fConst207)), Float(0.689621389f)))
	StoreVarInst(struct, fConst268, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst269, BinopInst("+", LoadVarInst(struct, fConst236), Float(7.62173128f)))
	StoreVarInst(struct, fConst270, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.168404877f)), LoadVarInst(struct, fConst207)), Float(1.06935835f)))
	StoreVarInst(struct, fConst271, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst272, BinopInst("+", LoadVarInst(struct, fConst236), Float(53.5361519f)))
	StoreVarInst(struct, fConst273, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-3.18972731f)), LoadVarInst(struct, fConst245)), Float(4.07678175f)))
	StoreVarInst(struct, fConst274, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst275, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst276, BinopInst("+", LoadVarInst(struct, fConst255), Float(0.000407678192f)))
	StoreVarInst(struct, fConst277, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.743130445f)), LoadVarInst(struct, fConst245)), Float(1.4500711f)))
	StoreVarInst(struct, fConst278, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst279, BinopInst("+", LoadVarInst(struct, fConst252), Float(1.4500711f)))
	StoreVarInst(struct, fConst280, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.157482162f)), LoadVarInst(struct, fConst245)), Float(0.935140193f)))
	StoreVarInst(struct, fConst281, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst282, BinopInst("+", LoadVarInst(struct, fConst249), Float(0.935140193f)))
	StoreVarInst(struct, fConst283, FunCallInst("tanf", BinopInst("/", Float(7916.31738f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst284, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst283)))
	StoreVarInst(struct, fConst285, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.157482162f)), LoadVarInst(struct, fConst283)), Float(0.935140193f))))
	StoreVarInst(struct, fConst286, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst283)))
	StoreVarInst(struct, fConst287, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst288, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst287))))
	StoreVarInst(struct, fConst289, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.743130445f)), LoadVarInst(struct, fConst283)), Float(1.4500711f))))
	StoreVarInst(struct, fConst290, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst291, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst290))))
	StoreVarInst(struct, fConst292, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(3.18972731f)), LoadVarInst(struct, fConst283)), Float(4.07678175f))))
	StoreVarInst(struct, fConst293, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst294, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst293))))
	StoreVarInst(struct, fConst295, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.168404877f)), LoadVarInst(struct, fConst245)), Float(1.06935835f))))
	StoreVarInst(struct, fConst296, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst297, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.51247865f)), LoadVarInst(struct, fConst245)), Float(0.689621389f))))
	StoreVarInst(struct, fConst298, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst299, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.782413065f)), LoadVarInst(struct, fConst245)), Float(0.245291501f))))
	StoreVarInst(struct, fConst300, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst301, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst300))))
	StoreVarInst(struct, fConst302, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.782413065f)), LoadVarInst(struct, fConst245)), Float(0.245291501f)))
	StoreVarInst(struct, fConst303, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst304, BinopInst("+", LoadVarInst(struct, fConst300), Float(0.000433227193f)))
	StoreVarInst(struct, fConst305, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.51247865f)), LoadVarInst(struct, fConst245)), Float(0.689621389f)))
	StoreVarInst(struct, fConst306, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst307, BinopInst("+", LoadVarInst(struct, fConst274), Float(7.62173128f)))
	StoreVarInst(struct, fConst308, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.168404877f)), LoadVarInst(struct, fConst245)), Float(1.06935835f)))
	StoreVarInst(struct, fConst309, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst310, BinopInst("+", LoadVarInst(struct, fConst274), Float(53.5361519f)))
	StoreVarInst(struct, fConst311, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-3.18972731f)), LoadVarInst(struct, fConst283)), Float(4.07678175f)))
	StoreVarInst(struct, fConst312, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst313, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst314, BinopInst("+", LoadVarInst(struct, fConst293), Float(0.000407678192f)))
	StoreVarInst(struct, fConst315, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.743130445f)), LoadVarInst(struct, fConst283)), Float(1.4500711f)))
	StoreVarInst(struct, fConst316, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst317, BinopInst("+", LoadVarInst(struct, fConst290), Float(1.4500711f)))
	StoreVarInst(struct, fConst318, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.157482162f)), LoadVarInst(struct, fConst283)), Float(0.935140193f)))
	StoreVarInst(struct, fConst319, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst320, BinopInst("+", LoadVarInst(struct, fConst287), Float(0.935140193f)))
	StoreVarInst(struct, fConst321, FunCallInst("tanf", BinopInst("/", Float(4986.96729f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst322, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst321)))
	StoreVarInst(struct, fConst323, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.157482162f)), LoadVarInst(struct, fConst321)), Float(0.935140193f))))
	StoreVarInst(struct, fConst324, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst321)))
	StoreVarInst(struct, fConst325, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst326, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst325))))
	StoreVarInst(struct, fConst327, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.743130445f)), LoadVarInst(struct, fConst321)), Float(1.4500711f))))
	StoreVarInst(struct, fConst328, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst329, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst328))))
	StoreVarInst(struct, fConst330, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(3.18972731f)), LoadVarInst(struct, fConst321)), Float(4.07678175f))))
	StoreVarInst(struct, fConst331, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst332, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst331))))
	StoreVarInst(struct, fConst333, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.168404877f)), LoadVarInst(struct, fConst283)), Float(1.06935835f))))
	StoreVarInst(struct, fConst334, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst335, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.51247865f)), LoadVarInst(struct, fConst283)), Float(0.689621389f))))
	StoreVarInst(struct, fConst336, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst337, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.782413065f)), LoadVarInst(struct, fConst283)), Float(0.245291501f))))
	StoreVarInst(struct, fConst338, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst339, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst338))))
	StoreVarInst(struct, fConst340, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.782413065f)), LoadVarInst(struct, fConst283)), Float(0.245291501f)))
	StoreVarInst(struct, fConst341, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst342, BinopInst("+", LoadVarInst(struct, fConst338), Float(0.000433227193f)))
	StoreVarInst(struct, fConst343, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.51247865f)), LoadVarInst(struct, fConst283)), Float(0.689621389f)))
	StoreVarInst(struct, fConst344, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst345, BinopInst("+", LoadVarInst(struct, fConst312), Float(7.62173128f)))
	StoreVarInst(struct, fConst346, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.168404877f)), LoadVarInst(struct, fConst283)), Float(1.06935835f)))
	StoreVarInst(struct, fConst347, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst348, BinopInst("+", LoadVarInst(struct, fConst312), Float(53.5361519f)))
	StoreVarInst(struct, fConst349, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-3.18972731f)), LoadVarInst(struct, fConst321)), Float(4.07678175f)))
	StoreVarInst(struct, fConst350, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst351, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst352, BinopInst("+", LoadVarInst(struct, fConst331), Float(0.000407678192f)))
	StoreVarInst(struct, fConst353, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.743130445f)), LoadVarInst(struct, fConst321)), Float(1.4500711f)))
	StoreVarInst(struct, fConst354, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst355, BinopInst("+", LoadVarInst(struct, fConst328), Float(1.4500711f)))
	StoreVarInst(struct, fConst356, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.157482162f)), LoadVarInst(struct, fConst321)), Float(0.935140193f)))
	StoreVarInst(struct, fConst357, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst358, BinopInst("+", LoadVarInst(struct, fConst325), Float(0.935140193f)))
	StoreVarInst(struct, fConst359, FunCallInst("tanf", BinopInst("/", Float(3141.59277f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst360, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst359)))
	StoreVarInst(struct, fConst361, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.157482162f)), LoadVarInst(struct, fConst359)), Float(0.935140193f))))
	StoreVarInst(struct, fConst362, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst359)))
	StoreVarInst(struct, fConst363, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst364, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst363))))
	StoreVarInst(struct, fConst365, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.743130445f)), LoadVarInst(struct, fConst359)), Float(1.4500711f))))
	StoreVarInst(struct, fConst366, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst367, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst366))))
	StoreVarInst(struct, fConst368, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(3.18972731f)), LoadVarInst(struct, fConst359)), Float(4.07678175f))))
	StoreVarInst(struct, fConst369, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst370, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst369))))
	StoreVarInst(struct, fConst371, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.168404877f)), LoadVarInst(struct, fConst321)), Float(1.06935835f))))
	StoreVarInst(struct, fConst372, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst373, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.51247865f)), LoadVarInst(struct, fConst321)), Float(0.689621389f))))
	StoreVarInst(struct, fConst374, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst375, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.782413065f)), LoadVarInst(struct, fConst321)), Float(0.245291501f))))
	StoreVarInst(struct, fConst376, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst377, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst376))))
	StoreVarInst(struct, fConst378, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.782413065f)), LoadVarInst(struct, fConst321)), Float(0.245291501f)))
	StoreVarInst(struct, fConst379, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst380, BinopInst("+", LoadVarInst(struct, fConst376), Float(0.000433227193f)))
	StoreVarInst(struct, fConst381, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.51247865f)), LoadVarInst(struct, fConst321)), Float(0.689621389f)))
	StoreVarInst(struct, fConst382, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst383, BinopInst("+", LoadVarInst(struct, fConst350), Float(7.62173128f)))
	StoreVarInst(struct, fConst384, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.168404877f)), LoadVarInst(struct, fConst321)), Float(1.06935835f)))
	StoreVarInst(struct, fConst385, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst386, BinopInst("+", LoadVarInst(struct, fConst350), Float(53.5361519f)))
	StoreVarInst(struct, fConst387, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-3.18972731f)), LoadVarInst(struct, fConst359)), Float(4.07678175f)))
	StoreVarInst(struct, fConst388, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst389, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst390, BinopInst("+", LoadVarInst(struct, fConst369), Float(0.000407678192f)))
	StoreVarInst(struct, fConst391, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.743130445f)), LoadVarInst(struct, fConst359)), Float(1.4500711f)))
	StoreVarInst(struct, fConst392, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst393, BinopInst("+", LoadVarInst(struct, fConst366), Float(1.4500711f)))
	StoreVarInst(struct, fConst394, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.157482162f)), LoadVarInst(struct, fConst359)), Float(0.935140193f)))
	StoreVarInst(struct, fConst395, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst396, BinopInst("+", LoadVarInst(struct, fConst363), Float(0.935140193f)))
	StoreVarInst(struct, fConst397, FunCallInst("tanf", BinopInst("/", Float(1979.07935f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst398, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst397)))
	StoreVarInst(struct, fConst399, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.157482162f)), LoadVarInst(struct, fConst397)), Float(0.935140193f))))
	StoreVarInst(struct, fConst400, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst397)))
	StoreVarInst(struct, fConst401, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst402, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst401))))
	StoreVarInst(struct, fConst403, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.743130445f)), LoadVarInst(struct, fConst397)), Float(1.4500711f))))
	StoreVarInst(struct, fConst404, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst405, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst404))))
	StoreVarInst(struct, fConst406, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(3.18972731f)), LoadVarInst(struct, fConst397)), Float(4.07678175f))))
	StoreVarInst(struct, fConst407, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst408, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst407))))
	StoreVarInst(struct, fConst409, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.168404877f)), LoadVarInst(struct, fConst359)), Float(1.06935835f))))
	StoreVarInst(struct, fConst410, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst411, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.51247865f)), LoadVarInst(struct, fConst359)), Float(0.689621389f))))
	StoreVarInst(struct, fConst412, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst413, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.782413065f)), LoadVarInst(struct, fConst359)), Float(0.245291501f))))
	StoreVarInst(struct, fConst414, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst415, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst414))))
	StoreVarInst(struct, fConst416, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.782413065f)), LoadVarInst(struct, fConst359)), Float(0.245291501f)))
	StoreVarInst(struct, fConst417, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst418, BinopInst("+", LoadVarInst(struct, fConst414), Float(0.000433227193f)))
	StoreVarInst(struct, fConst419, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.51247865f)), LoadVarInst(struct, fConst359)), Float(0.689621389f)))
	StoreVarInst(struct, fConst420, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst421, BinopInst("+", LoadVarInst(struct, fConst388), Float(7.62173128f)))
	StoreVarInst(struct, fConst422, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.168404877f)), LoadVarInst(struct, fConst359)), Float(1.06935835f)))
	StoreVarInst(struct, fConst423, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst424, BinopInst("+", LoadVarInst(struct, fConst388), Float(53.5361519f)))
	StoreVarInst(struct, fConst425, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-3.18972731f)), LoadVarInst(struct, fConst397)), Float(4.07678175f)))
	StoreVarInst(struct, fConst426, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst427, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst428, BinopInst("+", LoadVarInst(struct, fConst407), Float(0.000407678192f)))
	StoreVarInst(struct, fConst429, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.743130445f)), LoadVarInst(struct, fConst397)), Float(1.4500711f)))
	StoreVarInst(struct, fConst430, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst431, BinopInst("+", LoadVarInst(struct, fConst404), Float(1.4500711f)))
	StoreVarInst(struct, fConst432, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.157482162f)), LoadVarInst(struct, fConst397)), Float(0.935140193f)))
	StoreVarInst(struct, fConst433, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst434, BinopInst("+", LoadVarInst(struct, fConst401), Float(0.935140193f)))
	StoreVarInst(struct, fConst435, FunCallInst("tanf", BinopInst("/", Float(1246.74182f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst436, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst435)))
	StoreVarInst(struct, fConst437, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.157482162f)), LoadVarInst(struct, fConst435)), Float(0.935140193f))))
	StoreVarInst(struct, fConst438, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst435)))
	StoreVarInst(struct, fConst439, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst440, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst439))))
	StoreVarInst(struct, fConst441, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.743130445f)), LoadVarInst(struct, fConst435)), Float(1.4500711f))))
	StoreVarInst(struct, fConst442, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst443, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst442))))
	StoreVarInst(struct, fConst444, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(3.18972731f)), LoadVarInst(struct, fConst435)), Float(4.07678175f))))
	StoreVarInst(struct, fConst445, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst446, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst445))))
	StoreVarInst(struct, fConst447, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.168404877f)), LoadVarInst(struct, fConst397)), Float(1.06935835f))))
	StoreVarInst(struct, fConst448, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst449, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.51247865f)), LoadVarInst(struct, fConst397)), Float(0.689621389f))))
	StoreVarInst(struct, fConst450, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst451, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.782413065f)), LoadVarInst(struct, fConst397)), Float(0.245291501f))))
	StoreVarInst(struct, fConst452, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst453, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst452))))
	StoreVarInst(struct, fConst454, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.782413065f)), LoadVarInst(struct, fConst397)), Float(0.245291501f)))
	StoreVarInst(struct, fConst455, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst456, BinopInst("+", LoadVarInst(struct, fConst452), Float(0.000433227193f)))
	StoreVarInst(struct, fConst457, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.51247865f)), LoadVarInst(struct, fConst397)), Float(0.689621389f)))
	StoreVarInst(struct, fConst458, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst459, BinopInst("+", LoadVarInst(struct, fConst426), Float(7.62173128f)))
	StoreVarInst(struct, fConst460, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.168404877f)), LoadVarInst(struct, fConst397)), Float(1.06935835f)))
	StoreVarInst(struct, fConst461, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst462, BinopInst("+", LoadVarInst(struct, fConst426), Float(53.5361519f)))
	StoreVarInst(struct, fConst463, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-3.18972731f)), LoadVarInst(struct, fConst435)), Float(4.07678175f)))
	StoreVarInst(struct, fConst464, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst465, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst466, BinopInst("+", LoadVarInst(struct, fConst445), Float(0.000407678192f)))
	StoreVarInst(struct, fConst467, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.743130445f)), LoadVarInst(struct, fConst435)), Float(1.4500711f)))
	StoreVarInst(struct, fConst468, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst469, BinopInst("+", LoadVarInst(struct, fConst442), Float(1.4500711f)))
	StoreVarInst(struct, fConst470, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.157482162f)), LoadVarInst(struct, fConst435)), Float(0.935140193f)))
	StoreVarInst(struct, fConst471, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst472, BinopInst("+", LoadVarInst(struct, fConst439), Float(0.935140193f)))
	StoreVarInst(struct, fConst473, FunCallInst("tanf", BinopInst("/", Float(785.398193f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst474, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst473)))
	StoreVarInst(struct, fConst475, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.157482162f)), LoadVarInst(struct, fConst473)), Float(0.935140193f))))
	StoreVarInst(struct, fConst476, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst473)))
	StoreVarInst(struct, fConst477, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst478, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst477))))
	StoreVarInst(struct, fConst479, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.743130445f)), LoadVarInst(struct, fConst473)), Float(1.4500711f))))
	StoreVarInst(struct, fConst480, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst481, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst480))))
	StoreVarInst(struct, fConst482, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(3.18972731f)), LoadVarInst(struct, fConst473)), Float(4.07678175f))))
	StoreVarInst(struct, fConst483, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst484, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst483))))
	StoreVarInst(struct, fConst485, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.168404877f)), LoadVarInst(struct, fConst435)), Float(1.06935835f))))
	StoreVarInst(struct, fConst486, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst487, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.51247865f)), LoadVarInst(struct, fConst435)), Float(0.689621389f))))
	StoreVarInst(struct, fConst488, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst489, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.782413065f)), LoadVarInst(struct, fConst435)), Float(0.245291501f))))
	StoreVarInst(struct, fConst490, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst491, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst490))))
	StoreVarInst(struct, fConst492, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.782413065f)), LoadVarInst(struct, fConst435)), Float(0.245291501f)))
	StoreVarInst(struct, fConst493, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst494, BinopInst("+", LoadVarInst(struct, fConst490), Float(0.000433227193f)))
	StoreVarInst(struct, fConst495, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.51247865f)), LoadVarInst(struct, fConst435)), Float(0.689621389f)))
	StoreVarInst(struct, fConst496, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst497, BinopInst("+", LoadVarInst(struct, fConst464), Float(7.62173128f)))
	StoreVarInst(struct, fConst498, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.168404877f)), LoadVarInst(struct, fConst435)), Float(1.06935835f)))
	StoreVarInst(struct, fConst499, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst500, BinopInst("+", LoadVarInst(struct, fConst464), Float(53.5361519f)))
	StoreVarInst(struct, fConst501, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-3.18972731f)), LoadVarInst(struct, fConst473)), Float(4.07678175f)))
	StoreVarInst(struct, fConst502, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst503, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst504, BinopInst("+", LoadVarInst(struct, fConst483), Float(0.000407678192f)))
	StoreVarInst(struct, fConst505, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.743130445f)), LoadVarInst(struct, fConst473)), Float(1.4500711f)))
	StoreVarInst(struct, fConst506, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst507, BinopInst("+", LoadVarInst(struct, fConst480), Float(1.4500711f)))
	StoreVarInst(struct, fConst508, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.157482162f)), LoadVarInst(struct, fConst473)), Float(0.935140193f)))
	StoreVarInst(struct, fConst509, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst510, BinopInst("+", LoadVarInst(struct, fConst477), Float(0.935140193f)))
	StoreVarInst(struct, fConst511, FunCallInst("tanf", BinopInst("/", Float(494.769836f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst512, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst511)))
	StoreVarInst(struct, fConst513, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.157482162f)), LoadVarInst(struct, fConst511)), Float(0.935140193f))))
	StoreVarInst(struct, fConst514, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst511)))
	StoreVarInst(struct, fConst515, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst516, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst515))))
	StoreVarInst(struct, fConst517, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.743130445f)), LoadVarInst(struct, fConst511)), Float(1.4500711f))))
	StoreVarInst(struct, fConst518, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst519, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst518))))
	StoreVarInst(struct, fConst520, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(3.18972731f)), LoadVarInst(struct, fConst511)), Float(4.07678175f))))
	StoreVarInst(struct, fConst521, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst522, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst521))))
	StoreVarInst(struct, fConst523, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.168404877f)), LoadVarInst(struct, fConst473)), Float(1.06935835f))))
	StoreVarInst(struct, fConst524, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst525, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.51247865f)), LoadVarInst(struct, fConst473)), Float(0.689621389f))))
	StoreVarInst(struct, fConst526, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst527, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.782413065f)), LoadVarInst(struct, fConst473)), Float(0.245291501f))))
	StoreVarInst(struct, fConst528, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst529, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst528))))
	StoreVarInst(struct, fConst530, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.782413065f)), LoadVarInst(struct, fConst473)), Float(0.245291501f)))
	StoreVarInst(struct, fConst531, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst532, BinopInst("+", LoadVarInst(struct, fConst528), Float(0.000433227193f)))
	StoreVarInst(struct, fConst533, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.51247865f)), LoadVarInst(struct, fConst473)), Float(0.689621389f)))
	StoreVarInst(struct, fConst534, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst535, BinopInst("+", LoadVarInst(struct, fConst502), Float(7.62173128f)))
	StoreVarInst(struct, fConst536, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.168404877f)), LoadVarInst(struct, fConst473)), Float(1.06935835f)))
	StoreVarInst(struct, fConst537, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst538, BinopInst("+", LoadVarInst(struct, fConst502), Float(53.5361519f)))
	StoreVarInst(struct, fConst539, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-3.18972731f)), LoadVarInst(struct, fConst511)), Float(4.07678175f)))
	StoreVarInst(struct, fConst540, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst541, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst542, BinopInst("+", LoadVarInst(struct, fConst521), Float(0.000407678192f)))
	StoreVarInst(struct, fConst543, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.743130445f)), LoadVarInst(struct, fConst511)), Float(1.4500711f)))
	StoreVarInst(struct, fConst544, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst545, BinopInst("+", LoadVarInst(struct, fConst518), Float(1.4500711f)))
	StoreVarInst(struct, fConst546, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.157482162f)), LoadVarInst(struct, fConst511)), Float(0.935140193f)))
	StoreVarInst(struct, fConst547, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst548, BinopInst("+", LoadVarInst(struct, fConst515), Float(0.935140193f)))
	StoreVarInst(struct, fConst549, FunCallInst("tanf", BinopInst("/", Float(311.685455f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst550, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst549)))
	StoreVarInst(struct, fConst551, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.157482162f)), LoadVarInst(struct, fConst549)), Float(0.935140193f))))
	StoreVarInst(struct, fConst552, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst549)))
	StoreVarInst(struct, fConst553, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst554, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst553))))
	StoreVarInst(struct, fConst555, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.743130445f)), LoadVarInst(struct, fConst549)), Float(1.4500711f))))
	StoreVarInst(struct, fConst556, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst557, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst556))))
	StoreVarInst(struct, fConst558, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(3.18972731f)), LoadVarInst(struct, fConst549)), Float(4.07678175f))))
	StoreVarInst(struct, fConst559, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst560, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst559))))
	StoreVarInst(struct, fConst561, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.168404877f)), LoadVarInst(struct, fConst511)), Float(1.06935835f))))
	StoreVarInst(struct, fConst562, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst563, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.51247865f)), LoadVarInst(struct, fConst511)), Float(0.689621389f))))
	StoreVarInst(struct, fConst564, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst565, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.782413065f)), LoadVarInst(struct, fConst511)), Float(0.245291501f))))
	StoreVarInst(struct, fConst566, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst567, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst566))))
	StoreVarInst(struct, fConst568, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.782413065f)), LoadVarInst(struct, fConst511)), Float(0.245291501f)))
	StoreVarInst(struct, fConst569, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst570, BinopInst("+", LoadVarInst(struct, fConst566), Float(0.000433227193f)))
	StoreVarInst(struct, fConst571, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.51247865f)), LoadVarInst(struct, fConst511)), Float(0.689621389f)))
	StoreVarInst(struct, fConst572, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst573, BinopInst("+", LoadVarInst(struct, fConst540), Float(7.62173128f)))
	StoreVarInst(struct, fConst574, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.168404877f)), LoadVarInst(struct, fConst511)), Float(1.06935835f)))
	StoreVarInst(struct, fConst575, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst576, BinopInst("+", LoadVarInst(struct, fConst540), Float(53.5361519f)))
	StoreVarInst(struct, fConst577, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-3.18972731f)), LoadVarInst(struct, fConst549)), Float(4.07678175f)))
	StoreVarInst(struct, fConst578, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst579, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst580, BinopInst("+", LoadVarInst(struct, fConst559), Float(0.000407678192f)))
	StoreVarInst(struct, fConst581, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.743130445f)), LoadVarInst(struct, fConst549)), Float(1.4500711f)))
	StoreVarInst(struct, fConst582, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst583, BinopInst("+", LoadVarInst(struct, fConst556), Float(1.4500711f)))
	StoreVarInst(struct, fConst584, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.157482162f)), LoadVarInst(struct, fConst549)), Float(0.935140193f)))
	StoreVarInst(struct, fConst585, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst586, BinopInst("+", LoadVarInst(struct, fConst553), Float(0.935140193f)))
	StoreVarInst(struct, fConst587, FunCallInst("tanf", BinopInst("/", Float(196.349548f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst588, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst587)))
	StoreVarInst(struct, fConst589, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.157482162f)), LoadVarInst(struct, fConst587)), Float(0.935140193f))))
	StoreVarInst(struct, fConst590, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst587)))
	StoreVarInst(struct, fConst591, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst592, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst591))))
	StoreVarInst(struct, fConst593, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.743130445f)), LoadVarInst(struct, fConst587)), Float(1.4500711f))))
	StoreVarInst(struct, fConst594, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst595, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst594))))
	StoreVarInst(struct, fConst596, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(3.18972731f)), LoadVarInst(struct, fConst587)), Float(4.07678175f))))
	StoreVarInst(struct, fConst597, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst598, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst597))))
	StoreVarInst(struct, fConst599, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.168404877f)), LoadVarInst(struct, fConst549)), Float(1.06935835f))))
	StoreVarInst(struct, fConst600, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst601, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.51247865f)), LoadVarInst(struct, fConst549)), Float(0.689621389f))))
	StoreVarInst(struct, fConst602, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst603, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.782413065f)), LoadVarInst(struct, fConst549)), Float(0.245291501f))))
	StoreVarInst(struct, fConst604, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst605, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst604))))
	StoreVarInst(struct, fConst606, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.782413065f)), LoadVarInst(struct, fConst549)), Float(0.245291501f)))
	StoreVarInst(struct, fConst607, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst608, BinopInst("+", LoadVarInst(struct, fConst604), Float(0.000433227193f)))
	StoreVarInst(struct, fConst609, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.51247865f)), LoadVarInst(struct, fConst549)), Float(0.689621389f)))
	StoreVarInst(struct, fConst610, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst611, BinopInst("+", LoadVarInst(struct, fConst578), Float(7.62173128f)))
	StoreVarInst(struct, fConst612, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.168404877f)), LoadVarInst(struct, fConst549)), Float(1.06935835f)))
	StoreVarInst(struct, fConst613, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst614, BinopInst("+", LoadVarInst(struct, fConst578), Float(53.5361519f)))
	StoreVarInst(struct, fConst615, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-3.18972731f)), LoadVarInst(struct, fConst587)), Float(4.07678175f)))
	StoreVarInst(struct, fConst616, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst617, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst618, BinopInst("+", LoadVarInst(struct, fConst597), Float(0.000407678192f)))
	StoreVarInst(struct, fConst619, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.743130445f)), LoadVarInst(struct, fConst587)), Float(1.4500711f)))
	StoreVarInst(struct, fConst620, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst621, BinopInst("+", LoadVarInst(struct, fConst594), Float(1.4500711f)))
	StoreVarInst(struct, fConst622, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.157482162f)), LoadVarInst(struct, fConst587)), Float(0.935140193f)))
	StoreVarInst(struct, fConst623, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst624, BinopInst("+", LoadVarInst(struct, fConst591), Float(0.935140193f)))
	StoreVarInst(struct, fConst625, FunCallInst("tanf", BinopInst("/", Float(123.692459f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst626, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst625)))
	StoreVarInst(struct, fConst627, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.157482162f)), LoadVarInst(struct, fConst625)), Float(0.935140193f))))
	StoreVarInst(struct, fConst628, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst625)))
	StoreVarInst(struct, fConst629, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst630, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst629))))
	StoreVarInst(struct, fConst631, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.743130445f)), LoadVarInst(struct, fConst625)), Float(1.4500711f))))
	StoreVarInst(struct, fConst632, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst633, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst632))))
	StoreVarInst(struct, fConst634, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(3.18972731f)), LoadVarInst(struct, fConst625)), Float(4.07678175f))))
	StoreVarInst(struct, fConst635, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst636, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst635))))
	StoreVarInst(struct, fConst637, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.168404877f)), LoadVarInst(struct, fConst587)), Float(1.06935835f))))
	StoreVarInst(struct, fConst638, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst639, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.51247865f)), LoadVarInst(struct, fConst587)), Float(0.689621389f))))
	StoreVarInst(struct, fConst640, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst641, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.782413065f)), LoadVarInst(struct, fConst587)), Float(0.245291501f))))
	StoreVarInst(struct, fConst642, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst643, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst642))))
	StoreVarInst(struct, fConst644, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.782413065f)), LoadVarInst(struct, fConst587)), Float(0.245291501f)))
	StoreVarInst(struct, fConst645, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst646, BinopInst("+", LoadVarInst(struct, fConst642), Float(0.000433227193f)))
	StoreVarInst(struct, fConst647, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.51247865f)), LoadVarInst(struct, fConst587)), Float(0.689621389f)))
	StoreVarInst(struct, fConst648, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst649, BinopInst("+", LoadVarInst(struct, fConst616), Float(7.62173128f)))
	StoreVarInst(struct, fConst650, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.168404877f)), LoadVarInst(struct, fConst587)), Float(1.06935835f)))
	StoreVarInst(struct, fConst651, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst652, BinopInst("+", LoadVarInst(struct, fConst616), Float(53.5361519f)))
	StoreVarInst(struct, fConst653, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-3.18972731f)), LoadVarInst(struct, fConst625)), Float(4.07678175f)))
	StoreVarInst(struct, fConst654, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst655, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst656, BinopInst("+", LoadVarInst(struct, fConst635), Float(0.000407678192f)))
	StoreVarInst(struct, fConst657, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.743130445f)), LoadVarInst(struct, fConst625)), Float(1.4500711f)))
	StoreVarInst(struct, fConst658, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst659, BinopInst("+", LoadVarInst(struct, fConst632), Float(1.4500711f)))
	StoreVarInst(struct, fConst660, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.157482162f)), LoadVarInst(struct, fConst625)), Float(0.935140193f)))
	StoreVarInst(struct, fConst661, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst662, BinopInst("+", LoadVarInst(struct, fConst629), Float(0.935140193f)))
	StoreVarInst(struct, fConst663, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.168404877f)), LoadVarInst(struct, fConst625)), Float(1.06935835f))))
	StoreVarInst(struct, fConst664, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst665, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.51247865f)), LoadVarInst(struct, fConst625)), Float(0.689621389f))))
	StoreVarInst(struct, fConst666, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst667, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.782413065f)), LoadVarInst(struct, fConst625)), Float(0.245291501f))))
	StoreVarInst(struct, fConst668, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst669, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst668))))
	StoreVarInst(struct, fConst670, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.782413065f)), LoadVarInst(struct, fConst625)), Float(0.245291501f)))
	StoreVarInst(struct, fConst671, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst672, BinopInst("+", LoadVarInst(struct, fConst668), Float(0.000433227193f)))
	StoreVarInst(struct, fConst673, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.51247865f)), LoadVarInst(struct, fConst625)), Float(0.689621389f)))
	StoreVarInst(struct, fConst674, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst675, BinopInst("+", LoadVarInst(struct, fConst654), Float(7.62173128f)))
	StoreVarInst(struct, fConst676, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.168404877f)), LoadVarInst(struct, fConst625)), Float(1.06935835f)))
	StoreVarInst(struct, fConst677, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst678, BinopInst("+", LoadVarInst(struct, fConst654), Float(53.5361519f)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(-20.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(-0.10000000000000001f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fCheckbox3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider10, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider11, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider12, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider13, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider14, CastInst("FAUSTFLOAT", Double(-10.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(4))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec18[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec19[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec21[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec34[LoadVarInst(loop, l27)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(4))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec22[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(3))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(3))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec23[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(3))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(3))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec24[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(3))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec25[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec26[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec27[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(3))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec28[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(2))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(3))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec29[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(3))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(3))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(3))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(3))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(3))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec30[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(3))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l68)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(3))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l70, Int32(0))
		BinopInst("<", LoadVarInst(loop, l70), Int32(2))
		StoreVarInst(loop, l70, BinopInst("+", LoadVarInst(loop, l70), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l70)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l71, Int32(0))
		BinopInst("<", LoadVarInst(loop, l71), Int32(2))
		StoreVarInst(loop, l71, BinopInst("+", LoadVarInst(loop, l71), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l71)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l72, Int32(0))
		BinopInst("<", LoadVarInst(loop, l72), Int32(3))
		StoreVarInst(loop, l72, BinopInst("+", LoadVarInst(loop, l72), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l72)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l73, Int32(0))
		BinopInst("<", LoadVarInst(loop, l73), Int32(3))
		StoreVarInst(loop, l73, BinopInst("+", LoadVarInst(loop, l73), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l73)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l74, Int32(0))
		BinopInst("<", LoadVarInst(loop, l74), Int32(2))
		StoreVarInst(loop, l74, BinopInst("+", LoadVarInst(loop, l74), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l74)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l75, Int32(0))
		BinopInst("<", LoadVarInst(loop, l75), Int32(2))
		StoreVarInst(loop, l75, BinopInst("+", LoadVarInst(loop, l75), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l75)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l76, Int32(0))
		BinopInst("<", LoadVarInst(loop, l76), Int32(3))
		StoreVarInst(loop, l76, BinopInst("+", LoadVarInst(loop, l76), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l76)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l77, Int32(0))
		BinopInst("<", LoadVarInst(loop, l77), Int32(3))
		StoreVarInst(loop, l77, BinopInst("+", LoadVarInst(loop, l77), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l77)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l78, Int32(0))
		BinopInst("<", LoadVarInst(loop, l78), Int32(3))
		StoreVarInst(loop, l78, BinopInst("+", LoadVarInst(loop, l78), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l78)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l79, Int32(0))
		BinopInst("<", LoadVarInst(loop, l79), Int32(3))
		StoreVarInst(loop, l79, BinopInst("+", LoadVarInst(loop, l79), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l79)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l80, Int32(0))
		BinopInst("<", LoadVarInst(loop, l80), Int32(3))
		StoreVarInst(loop, l80, BinopInst("+", LoadVarInst(loop, l80), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l80)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l81, Int32(0))
		BinopInst("<", LoadVarInst(loop, l81), Int32(3))
		StoreVarInst(loop, l81, BinopInst("+", LoadVarInst(loop, l81), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l81)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l82, Int32(0))
		BinopInst("<", LoadVarInst(loop, l82), Int32(3))
		StoreVarInst(loop, l82, BinopInst("+", LoadVarInst(loop, l82), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l82)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l83, Int32(0))
		BinopInst("<", LoadVarInst(loop, l83), Int32(3))
		StoreVarInst(loop, l83, BinopInst("+", LoadVarInst(loop, l83), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l83)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l84, Int32(0))
		BinopInst("<", LoadVarInst(loop, l84), Int32(3))
		StoreVarInst(loop, l84, BinopInst("+", LoadVarInst(loop, l84), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l84)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l85, Int32(0))
		BinopInst("<", LoadVarInst(loop, l85), Int32(3))
		StoreVarInst(loop, l85, BinopInst("+", LoadVarInst(loop, l85), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l85)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l86, Int32(0))
		BinopInst("<", LoadVarInst(loop, l86), Int32(2))
		StoreVarInst(loop, l86, BinopInst("+", LoadVarInst(loop, l86), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l86)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l87, Int32(0))
		BinopInst("<", LoadVarInst(loop, l87), Int32(2))
		StoreVarInst(loop, l87, BinopInst("+", LoadVarInst(loop, l87), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec69[LoadVarInst(loop, l87)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l88, Int32(0))
		BinopInst("<", LoadVarInst(loop, l88), Int32(3))
		StoreVarInst(loop, l88, BinopInst("+", LoadVarInst(loop, l88), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec68[LoadVarInst(loop, l88)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l89, Int32(0))
		BinopInst("<", LoadVarInst(loop, l89), Int32(3))
		StoreVarInst(loop, l89, BinopInst("+", LoadVarInst(loop, l89), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec67[LoadVarInst(loop, l89)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l90, Int32(0))
		BinopInst("<", LoadVarInst(loop, l90), Int32(3))
		StoreVarInst(loop, l90, BinopInst("+", LoadVarInst(loop, l90), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec66[LoadVarInst(loop, l90)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l91, Int32(0))
		BinopInst("<", LoadVarInst(loop, l91), Int32(3))
		StoreVarInst(loop, l91, BinopInst("+", LoadVarInst(loop, l91), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l91)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l92, Int32(0))
		BinopInst("<", LoadVarInst(loop, l92), Int32(3))
		StoreVarInst(loop, l92, BinopInst("+", LoadVarInst(loop, l92), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l92)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l93, Int32(0))
		BinopInst("<", LoadVarInst(loop, l93), Int32(3))
		StoreVarInst(loop, l93, BinopInst("+", LoadVarInst(loop, l93), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l93)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l94, Int32(0))
		BinopInst("<", LoadVarInst(loop, l94), Int32(3))
		StoreVarInst(loop, l94, BinopInst("+", LoadVarInst(loop, l94), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l94)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l95, Int32(0))
		BinopInst("<", LoadVarInst(loop, l95), Int32(3))
		StoreVarInst(loop, l95, BinopInst("+", LoadVarInst(loop, l95), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l95)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l96, Int32(0))
		BinopInst("<", LoadVarInst(loop, l96), Int32(3))
		StoreVarInst(loop, l96, BinopInst("+", LoadVarInst(loop, l96), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l96)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l97, Int32(0))
		BinopInst("<", LoadVarInst(loop, l97), Int32(2))
		StoreVarInst(loop, l97, BinopInst("+", LoadVarInst(loop, l97), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec70[LoadVarInst(loop, l97)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l98, Int32(0))
		BinopInst("<", LoadVarInst(loop, l98), Int32(2))
		StoreVarInst(loop, l98, BinopInst("+", LoadVarInst(loop, l98), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l98)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l99, Int32(0))
		BinopInst("<", LoadVarInst(loop, l99), Int32(3))
		StoreVarInst(loop, l99, BinopInst("+", LoadVarInst(loop, l99), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l99)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l100, Int32(0))
		BinopInst("<", LoadVarInst(loop, l100), Int32(3))
		StoreVarInst(loop, l100, BinopInst("+", LoadVarInst(loop, l100), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l100)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l101, Int32(0))
		BinopInst("<", LoadVarInst(loop, l101), Int32(3))
		StoreVarInst(loop, l101, BinopInst("+", LoadVarInst(loop, l101), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l101)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l102, Int32(0))
		BinopInst("<", LoadVarInst(loop, l102), Int32(3))
		StoreVarInst(loop, l102, BinopInst("+", LoadVarInst(loop, l102), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec75[LoadVarInst(loop, l102)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l103, Int32(0))
		BinopInst("<", LoadVarInst(loop, l103), Int32(3))
		StoreVarInst(loop, l103, BinopInst("+", LoadVarInst(loop, l103), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec74[LoadVarInst(loop, l103)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l104, Int32(0))
		BinopInst("<", LoadVarInst(loop, l104), Int32(3))
		StoreVarInst(loop, l104, BinopInst("+", LoadVarInst(loop, l104), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec73[LoadVarInst(loop, l104)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l105, Int32(0))
		BinopInst("<", LoadVarInst(loop, l105), Int32(3))
		StoreVarInst(loop, l105, BinopInst("+", LoadVarInst(loop, l105), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec72[LoadVarInst(loop, l105)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l106, Int32(0))
		BinopInst("<", LoadVarInst(loop, l106), Int32(3))
		StoreVarInst(loop, l106, BinopInst("+", LoadVarInst(loop, l106), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec71[LoadVarInst(loop, l106)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l107, Int32(0))
		BinopInst("<", LoadVarInst(loop, l107), Int32(2))
		StoreVarInst(loop, l107, BinopInst("+", LoadVarInst(loop, l107), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l107)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l108, Int32(0))
		BinopInst("<", LoadVarInst(loop, l108), Int32(2))
		StoreVarInst(loop, l108, BinopInst("+", LoadVarInst(loop, l108), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l108)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l109, Int32(0))
		BinopInst("<", LoadVarInst(loop, l109), Int32(3))
		StoreVarInst(loop, l109, BinopInst("+", LoadVarInst(loop, l109), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec87[LoadVarInst(loop, l109)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l110, Int32(0))
		BinopInst("<", LoadVarInst(loop, l110), Int32(3))
		StoreVarInst(loop, l110, BinopInst("+", LoadVarInst(loop, l110), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec86[LoadVarInst(loop, l110)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l111, Int32(0))
		BinopInst("<", LoadVarInst(loop, l111), Int32(3))
		StoreVarInst(loop, l111, BinopInst("+", LoadVarInst(loop, l111), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l111)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l112, Int32(0))
		BinopInst("<", LoadVarInst(loop, l112), Int32(3))
		StoreVarInst(loop, l112, BinopInst("+", LoadVarInst(loop, l112), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l112)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l113, Int32(0))
		BinopInst("<", LoadVarInst(loop, l113), Int32(3))
		StoreVarInst(loop, l113, BinopInst("+", LoadVarInst(loop, l113), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l113)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l114, Int32(0))
		BinopInst("<", LoadVarInst(loop, l114), Int32(3))
		StoreVarInst(loop, l114, BinopInst("+", LoadVarInst(loop, l114), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l114)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l115, Int32(0))
		BinopInst("<", LoadVarInst(loop, l115), Int32(3))
		StoreVarInst(loop, l115, BinopInst("+", LoadVarInst(loop, l115), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l115)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l116, Int32(0))
		BinopInst("<", LoadVarInst(loop, l116), Int32(2))
		StoreVarInst(loop, l116, BinopInst("+", LoadVarInst(loop, l116), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l116)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l117, Int32(0))
		BinopInst("<", LoadVarInst(loop, l117), Int32(2))
		StoreVarInst(loop, l117, BinopInst("+", LoadVarInst(loop, l117), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec96[LoadVarInst(loop, l117)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l118, Int32(0))
		BinopInst("<", LoadVarInst(loop, l118), Int32(3))
		StoreVarInst(loop, l118, BinopInst("+", LoadVarInst(loop, l118), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l118)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l119, Int32(0))
		BinopInst("<", LoadVarInst(loop, l119), Int32(3))
		StoreVarInst(loop, l119, BinopInst("+", LoadVarInst(loop, l119), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l119)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l120, Int32(0))
		BinopInst("<", LoadVarInst(loop, l120), Int32(3))
		StoreVarInst(loop, l120, BinopInst("+", LoadVarInst(loop, l120), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l120)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l121, Int32(0))
		BinopInst("<", LoadVarInst(loop, l121), Int32(3))
		StoreVarInst(loop, l121, BinopInst("+", LoadVarInst(loop, l121), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l121)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l122, Int32(0))
		BinopInst("<", LoadVarInst(loop, l122), Int32(3))
		StoreVarInst(loop, l122, BinopInst("+", LoadVarInst(loop, l122), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l122)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l123, Int32(0))
		BinopInst("<", LoadVarInst(loop, l123), Int32(3))
		StoreVarInst(loop, l123, BinopInst("+", LoadVarInst(loop, l123), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l123)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l124, Int32(0))
		BinopInst("<", LoadVarInst(loop, l124), Int32(2))
		StoreVarInst(loop, l124, BinopInst("+", LoadVarInst(loop, l124), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec97[LoadVarInst(loop, l124)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l125, Int32(0))
		BinopInst("<", LoadVarInst(loop, l125), Int32(2))
		StoreVarInst(loop, l125, BinopInst("+", LoadVarInst(loop, l125), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec103[LoadVarInst(loop, l125)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l126, Int32(0))
		BinopInst("<", LoadVarInst(loop, l126), Int32(3))
		StoreVarInst(loop, l126, BinopInst("+", LoadVarInst(loop, l126), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec102[LoadVarInst(loop, l126)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l127, Int32(0))
		BinopInst("<", LoadVarInst(loop, l127), Int32(3))
		StoreVarInst(loop, l127, BinopInst("+", LoadVarInst(loop, l127), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec101[LoadVarInst(loop, l127)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l128, Int32(0))
		BinopInst("<", LoadVarInst(loop, l128), Int32(3))
		StoreVarInst(loop, l128, BinopInst("+", LoadVarInst(loop, l128), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec100[LoadVarInst(loop, l128)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l129, Int32(0))
		BinopInst("<", LoadVarInst(loop, l129), Int32(3))
		StoreVarInst(loop, l129, BinopInst("+", LoadVarInst(loop, l129), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec99[LoadVarInst(loop, l129)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l130, Int32(0))
		BinopInst("<", LoadVarInst(loop, l130), Int32(3))
		StoreVarInst(loop, l130, BinopInst("+", LoadVarInst(loop, l130), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec98[LoadVarInst(loop, l130)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l131, Int32(0))
		BinopInst("<", LoadVarInst(loop, l131), Int32(2))
		StoreVarInst(loop, l131, BinopInst("+", LoadVarInst(loop, l131), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec104[LoadVarInst(loop, l131)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l132, Int32(0))
		BinopInst("<", LoadVarInst(loop, l132), Int32(2))
		StoreVarInst(loop, l132, BinopInst("+", LoadVarInst(loop, l132), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec109[LoadVarInst(loop, l132)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l133, Int32(0))
		BinopInst("<", LoadVarInst(loop, l133), Int32(3))
		StoreVarInst(loop, l133, BinopInst("+", LoadVarInst(loop, l133), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec108[LoadVarInst(loop, l133)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l134, Int32(0))
		BinopInst("<", LoadVarInst(loop, l134), Int32(3))
		StoreVarInst(loop, l134, BinopInst("+", LoadVarInst(loop, l134), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec107[LoadVarInst(loop, l134)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l135, Int32(0))
		BinopInst("<", LoadVarInst(loop, l135), Int32(3))
		StoreVarInst(loop, l135, BinopInst("+", LoadVarInst(loop, l135), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec106[LoadVarInst(loop, l135)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l136, Int32(0))
		BinopInst("<", LoadVarInst(loop, l136), Int32(3))
		StoreVarInst(loop, l136, BinopInst("+", LoadVarInst(loop, l136), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec105[LoadVarInst(loop, l136)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l137, Int32(0))
		BinopInst("<", LoadVarInst(loop, l137), Int32(2))
		StoreVarInst(loop, l137, BinopInst("+", LoadVarInst(loop, l137), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec110[LoadVarInst(loop, l137)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l138, Int32(0))
		BinopInst("<", LoadVarInst(loop, l138), Int32(3))
		StoreVarInst(loop, l138, BinopInst("+", LoadVarInst(loop, l138), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l138)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l139, Int32(0))
		BinopInst("<", LoadVarInst(loop, l139), Int32(3))
		StoreVarInst(loop, l139, BinopInst("+", LoadVarInst(loop, l139), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l139)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l140, Int32(0))
		BinopInst("<", LoadVarInst(loop, l140), Int32(3))
		StoreVarInst(loop, l140, BinopInst("+", LoadVarInst(loop, l140), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l140)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l141, Int32(0))
		BinopInst("<", LoadVarInst(loop, l141), Int32(2))
		StoreVarInst(loop, l141, BinopInst("+", LoadVarInst(loop, l141), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l141)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l142, Int32(0))
		BinopInst("<", LoadVarInst(loop, l142), Int32(3))
		StoreVarInst(loop, l142, BinopInst("+", LoadVarInst(loop, l142), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec117[LoadVarInst(loop, l142)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l143, Int32(0))
		BinopInst("<", LoadVarInst(loop, l143), Int32(3))
		StoreVarInst(loop, l143, BinopInst("+", LoadVarInst(loop, l143), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec116[LoadVarInst(loop, l143)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l144, Int32(0))
		BinopInst("<", LoadVarInst(loop, l144), Int32(3))
		StoreVarInst(loop, l144, BinopInst("+", LoadVarInst(loop, l144), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec115[LoadVarInst(loop, l144)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l145, Int32(0))
		BinopInst("<", LoadVarInst(loop, l145), Int32(3))
		StoreVarInst(loop, l145, BinopInst("+", LoadVarInst(loop, l145), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec114[LoadVarInst(loop, l145)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l146, Int32(0))
		BinopInst("<", LoadVarInst(loop, l146), Int32(3))
		StoreVarInst(loop, l146, BinopInst("+", LoadVarInst(loop, l146), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec113[LoadVarInst(loop, l146)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l147, Int32(0))
		BinopInst("<", LoadVarInst(loop, l147), Int32(3))
		StoreVarInst(loop, l147, BinopInst("+", LoadVarInst(loop, l147), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec112[LoadVarInst(loop, l147)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l148, Int32(0))
		BinopInst("<", LoadVarInst(loop, l148), Int32(2))
		StoreVarInst(loop, l148, BinopInst("+", LoadVarInst(loop, l148), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec111[LoadVarInst(loop, l148)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l149, Int32(0))
		BinopInst("<", LoadVarInst(loop, l149), Int32(3))
		StoreVarInst(loop, l149, BinopInst("+", LoadVarInst(loop, l149), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec124[LoadVarInst(loop, l149)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l150, Int32(0))
		BinopInst("<", LoadVarInst(loop, l150), Int32(3))
		StoreVarInst(loop, l150, BinopInst("+", LoadVarInst(loop, l150), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec123[LoadVarInst(loop, l150)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l151, Int32(0))
		BinopInst("<", LoadVarInst(loop, l151), Int32(3))
		StoreVarInst(loop, l151, BinopInst("+", LoadVarInst(loop, l151), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec122[LoadVarInst(loop, l151)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l152, Int32(0))
		BinopInst("<", LoadVarInst(loop, l152), Int32(3))
		StoreVarInst(loop, l152, BinopInst("+", LoadVarInst(loop, l152), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec121[LoadVarInst(loop, l152)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l153, Int32(0))
		BinopInst("<", LoadVarInst(loop, l153), Int32(3))
		StoreVarInst(loop, l153, BinopInst("+", LoadVarInst(loop, l153), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec120[LoadVarInst(loop, l153)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l154, Int32(0))
		BinopInst("<", LoadVarInst(loop, l154), Int32(3))
		StoreVarInst(loop, l154, BinopInst("+", LoadVarInst(loop, l154), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec119[LoadVarInst(loop, l154)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l155, Int32(0))
		BinopInst("<", LoadVarInst(loop, l155), Int32(2))
		StoreVarInst(loop, l155, BinopInst("+", LoadVarInst(loop, l155), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec118[LoadVarInst(loop, l155)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l156, Int32(0))
		BinopInst("<", LoadVarInst(loop, l156), Int32(3))
		StoreVarInst(loop, l156, BinopInst("+", LoadVarInst(loop, l156), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec131[LoadVarInst(loop, l156)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l157, Int32(0))
		BinopInst("<", LoadVarInst(loop, l157), Int32(3))
		StoreVarInst(loop, l157, BinopInst("+", LoadVarInst(loop, l157), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec130[LoadVarInst(loop, l157)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l158, Int32(0))
		BinopInst("<", LoadVarInst(loop, l158), Int32(3))
		StoreVarInst(loop, l158, BinopInst("+", LoadVarInst(loop, l158), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec129[LoadVarInst(loop, l158)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l159, Int32(0))
		BinopInst("<", LoadVarInst(loop, l159), Int32(3))
		StoreVarInst(loop, l159, BinopInst("+", LoadVarInst(loop, l159), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec128[LoadVarInst(loop, l159)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l160, Int32(0))
		BinopInst("<", LoadVarInst(loop, l160), Int32(3))
		StoreVarInst(loop, l160, BinopInst("+", LoadVarInst(loop, l160), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec127[LoadVarInst(loop, l160)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l161, Int32(0))
		BinopInst("<", LoadVarInst(loop, l161), Int32(3))
		StoreVarInst(loop, l161, BinopInst("+", LoadVarInst(loop, l161), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec126[LoadVarInst(loop, l161)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l162, Int32(0))
		BinopInst("<", LoadVarInst(loop, l162), Int32(2))
		StoreVarInst(loop, l162, BinopInst("+", LoadVarInst(loop, l162), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec125[LoadVarInst(loop, l162)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l163, Int32(0))
		BinopInst("<", LoadVarInst(loop, l163), Int32(3))
		StoreVarInst(loop, l163, BinopInst("+", LoadVarInst(loop, l163), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec138[LoadVarInst(loop, l163)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l164, Int32(0))
		BinopInst("<", LoadVarInst(loop, l164), Int32(3))
		StoreVarInst(loop, l164, BinopInst("+", LoadVarInst(loop, l164), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec137[LoadVarInst(loop, l164)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l165, Int32(0))
		BinopInst("<", LoadVarInst(loop, l165), Int32(3))
		StoreVarInst(loop, l165, BinopInst("+", LoadVarInst(loop, l165), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec136[LoadVarInst(loop, l165)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l166, Int32(0))
		BinopInst("<", LoadVarInst(loop, l166), Int32(3))
		StoreVarInst(loop, l166, BinopInst("+", LoadVarInst(loop, l166), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec135[LoadVarInst(loop, l166)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l167, Int32(0))
		BinopInst("<", LoadVarInst(loop, l167), Int32(3))
		StoreVarInst(loop, l167, BinopInst("+", LoadVarInst(loop, l167), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec134[LoadVarInst(loop, l167)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l168, Int32(0))
		BinopInst("<", LoadVarInst(loop, l168), Int32(3))
		StoreVarInst(loop, l168, BinopInst("+", LoadVarInst(loop, l168), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec133[LoadVarInst(loop, l168)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l169, Int32(0))
		BinopInst("<", LoadVarInst(loop, l169), Int32(2))
		StoreVarInst(loop, l169, BinopInst("+", LoadVarInst(loop, l169), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec132[LoadVarInst(loop, l169)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l170, Int32(0))
		BinopInst("<", LoadVarInst(loop, l170), Int32(3))
		StoreVarInst(loop, l170, BinopInst("+", LoadVarInst(loop, l170), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec145[LoadVarInst(loop, l170)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l171, Int32(0))
		BinopInst("<", LoadVarInst(loop, l171), Int32(3))
		StoreVarInst(loop, l171, BinopInst("+", LoadVarInst(loop, l171), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec144[LoadVarInst(loop, l171)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l172, Int32(0))
		BinopInst("<", LoadVarInst(loop, l172), Int32(3))
		StoreVarInst(loop, l172, BinopInst("+", LoadVarInst(loop, l172), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec143[LoadVarInst(loop, l172)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l173, Int32(0))
		BinopInst("<", LoadVarInst(loop, l173), Int32(3))
		StoreVarInst(loop, l173, BinopInst("+", LoadVarInst(loop, l173), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec142[LoadVarInst(loop, l173)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l174, Int32(0))
		BinopInst("<", LoadVarInst(loop, l174), Int32(3))
		StoreVarInst(loop, l174, BinopInst("+", LoadVarInst(loop, l174), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec141[LoadVarInst(loop, l174)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l175, Int32(0))
		BinopInst("<", LoadVarInst(loop, l175), Int32(3))
		StoreVarInst(loop, l175, BinopInst("+", LoadVarInst(loop, l175), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec140[LoadVarInst(loop, l175)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l176, Int32(0))
		BinopInst("<", LoadVarInst(loop, l176), Int32(2))
		StoreVarInst(loop, l176, BinopInst("+", LoadVarInst(loop, l176), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec139[LoadVarInst(loop, l176)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l177, Int32(0))
		BinopInst("<", LoadVarInst(loop, l177), Int32(3))
		StoreVarInst(loop, l177, BinopInst("+", LoadVarInst(loop, l177), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec152[LoadVarInst(loop, l177)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l178, Int32(0))
		BinopInst("<", LoadVarInst(loop, l178), Int32(3))
		StoreVarInst(loop, l178, BinopInst("+", LoadVarInst(loop, l178), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec151[LoadVarInst(loop, l178)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l179, Int32(0))
		BinopInst("<", LoadVarInst(loop, l179), Int32(3))
		StoreVarInst(loop, l179, BinopInst("+", LoadVarInst(loop, l179), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec150[LoadVarInst(loop, l179)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l180, Int32(0))
		BinopInst("<", LoadVarInst(loop, l180), Int32(3))
		StoreVarInst(loop, l180, BinopInst("+", LoadVarInst(loop, l180), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec149[LoadVarInst(loop, l180)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l181, Int32(0))
		BinopInst("<", LoadVarInst(loop, l181), Int32(3))
		StoreVarInst(loop, l181, BinopInst("+", LoadVarInst(loop, l181), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec148[LoadVarInst(loop, l181)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l182, Int32(0))
		BinopInst("<", LoadVarInst(loop, l182), Int32(3))
		StoreVarInst(loop, l182, BinopInst("+", LoadVarInst(loop, l182), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec147[LoadVarInst(loop, l182)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l183, Int32(0))
		BinopInst("<", LoadVarInst(loop, l183), Int32(2))
		StoreVarInst(loop, l183, BinopInst("+", LoadVarInst(loop, l183), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec146[LoadVarInst(loop, l183)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l184, Int32(0))
		BinopInst("<", LoadVarInst(loop, l184), Int32(3))
		StoreVarInst(loop, l184, BinopInst("+", LoadVarInst(loop, l184), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec159[LoadVarInst(loop, l184)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l185, Int32(0))
		BinopInst("<", LoadVarInst(loop, l185), Int32(3))
		StoreVarInst(loop, l185, BinopInst("+", LoadVarInst(loop, l185), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec158[LoadVarInst(loop, l185)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l186, Int32(0))
		BinopInst("<", LoadVarInst(loop, l186), Int32(3))
		StoreVarInst(loop, l186, BinopInst("+", LoadVarInst(loop, l186), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec157[LoadVarInst(loop, l186)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l187, Int32(0))
		BinopInst("<", LoadVarInst(loop, l187), Int32(3))
		StoreVarInst(loop, l187, BinopInst("+", LoadVarInst(loop, l187), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec156[LoadVarInst(loop, l187)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l188, Int32(0))
		BinopInst("<", LoadVarInst(loop, l188), Int32(3))
		StoreVarInst(loop, l188, BinopInst("+", LoadVarInst(loop, l188), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec155[LoadVarInst(loop, l188)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l189, Int32(0))
		BinopInst("<", LoadVarInst(loop, l189), Int32(3))
		StoreVarInst(loop, l189, BinopInst("+", LoadVarInst(loop, l189), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec154[LoadVarInst(loop, l189)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l190, Int32(0))
		BinopInst("<", LoadVarInst(loop, l190), Int32(2))
		StoreVarInst(loop, l190, BinopInst("+", LoadVarInst(loop, l190), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec153[LoadVarInst(loop, l190)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l191, Int32(0))
		BinopInst("<", LoadVarInst(loop, l191), Int32(3))
		StoreVarInst(loop, l191, BinopInst("+", LoadVarInst(loop, l191), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec166[LoadVarInst(loop, l191)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l192, Int32(0))
		BinopInst("<", LoadVarInst(loop, l192), Int32(3))
		StoreVarInst(loop, l192, BinopInst("+", LoadVarInst(loop, l192), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec165[LoadVarInst(loop, l192)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l193, Int32(0))
		BinopInst("<", LoadVarInst(loop, l193), Int32(3))
		StoreVarInst(loop, l193, BinopInst("+", LoadVarInst(loop, l193), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec164[LoadVarInst(loop, l193)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l194, Int32(0))
		BinopInst("<", LoadVarInst(loop, l194), Int32(3))
		StoreVarInst(loop, l194, BinopInst("+", LoadVarInst(loop, l194), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec163[LoadVarInst(loop, l194)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l195, Int32(0))
		BinopInst("<", LoadVarInst(loop, l195), Int32(3))
		StoreVarInst(loop, l195, BinopInst("+", LoadVarInst(loop, l195), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec162[LoadVarInst(loop, l195)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l196, Int32(0))
		BinopInst("<", LoadVarInst(loop, l196), Int32(3))
		StoreVarInst(loop, l196, BinopInst("+", LoadVarInst(loop, l196), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec161[LoadVarInst(loop, l196)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l197, Int32(0))
		BinopInst("<", LoadVarInst(loop, l197), Int32(2))
		StoreVarInst(loop, l197, BinopInst("+", LoadVarInst(loop, l197), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec160[LoadVarInst(loop, l197)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l198, Int32(0))
		BinopInst("<", LoadVarInst(loop, l198), Int32(3))
		StoreVarInst(loop, l198, BinopInst("+", LoadVarInst(loop, l198), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec173[LoadVarInst(loop, l198)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l199, Int32(0))
		BinopInst("<", LoadVarInst(loop, l199), Int32(3))
		StoreVarInst(loop, l199, BinopInst("+", LoadVarInst(loop, l199), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec172[LoadVarInst(loop, l199)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l200, Int32(0))
		BinopInst("<", LoadVarInst(loop, l200), Int32(3))
		StoreVarInst(loop, l200, BinopInst("+", LoadVarInst(loop, l200), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec171[LoadVarInst(loop, l200)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l201, Int32(0))
		BinopInst("<", LoadVarInst(loop, l201), Int32(3))
		StoreVarInst(loop, l201, BinopInst("+", LoadVarInst(loop, l201), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec170[LoadVarInst(loop, l201)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l202, Int32(0))
		BinopInst("<", LoadVarInst(loop, l202), Int32(3))
		StoreVarInst(loop, l202, BinopInst("+", LoadVarInst(loop, l202), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec169[LoadVarInst(loop, l202)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l203, Int32(0))
		BinopInst("<", LoadVarInst(loop, l203), Int32(3))
		StoreVarInst(loop, l203, BinopInst("+", LoadVarInst(loop, l203), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec168[LoadVarInst(loop, l203)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l204, Int32(0))
		BinopInst("<", LoadVarInst(loop, l204), Int32(2))
		StoreVarInst(loop, l204, BinopInst("+", LoadVarInst(loop, l204), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec167[LoadVarInst(loop, l204)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l205, Int32(0))
		BinopInst("<", LoadVarInst(loop, l205), Int32(3))
		StoreVarInst(loop, l205, BinopInst("+", LoadVarInst(loop, l205), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec180[LoadVarInst(loop, l205)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l206, Int32(0))
		BinopInst("<", LoadVarInst(loop, l206), Int32(3))
		StoreVarInst(loop, l206, BinopInst("+", LoadVarInst(loop, l206), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec179[LoadVarInst(loop, l206)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l207, Int32(0))
		BinopInst("<", LoadVarInst(loop, l207), Int32(3))
		StoreVarInst(loop, l207, BinopInst("+", LoadVarInst(loop, l207), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec178[LoadVarInst(loop, l207)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l208, Int32(0))
		BinopInst("<", LoadVarInst(loop, l208), Int32(3))
		StoreVarInst(loop, l208, BinopInst("+", LoadVarInst(loop, l208), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec177[LoadVarInst(loop, l208)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l209, Int32(0))
		BinopInst("<", LoadVarInst(loop, l209), Int32(3))
		StoreVarInst(loop, l209, BinopInst("+", LoadVarInst(loop, l209), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec176[LoadVarInst(loop, l209)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l210, Int32(0))
		BinopInst("<", LoadVarInst(loop, l210), Int32(3))
		StoreVarInst(loop, l210, BinopInst("+", LoadVarInst(loop, l210), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec175[LoadVarInst(loop, l210)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l211, Int32(0))
		BinopInst("<", LoadVarInst(loop, l211), Int32(2))
		StoreVarInst(loop, l211, BinopInst("+", LoadVarInst(loop, l211), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec174[LoadVarInst(loop, l211)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l212, Int32(0))
		BinopInst("<", LoadVarInst(loop, l212), Int32(3))
		StoreVarInst(loop, l212, BinopInst("+", LoadVarInst(loop, l212), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec187[LoadVarInst(loop, l212)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l213, Int32(0))
		BinopInst("<", LoadVarInst(loop, l213), Int32(3))
		StoreVarInst(loop, l213, BinopInst("+", LoadVarInst(loop, l213), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec186[LoadVarInst(loop, l213)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l214, Int32(0))
		BinopInst("<", LoadVarInst(loop, l214), Int32(3))
		StoreVarInst(loop, l214, BinopInst("+", LoadVarInst(loop, l214), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec185[LoadVarInst(loop, l214)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l215, Int32(0))
		BinopInst("<", LoadVarInst(loop, l215), Int32(3))
		StoreVarInst(loop, l215, BinopInst("+", LoadVarInst(loop, l215), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec184[LoadVarInst(loop, l215)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l216, Int32(0))
		BinopInst("<", LoadVarInst(loop, l216), Int32(3))
		StoreVarInst(loop, l216, BinopInst("+", LoadVarInst(loop, l216), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec183[LoadVarInst(loop, l216)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l217, Int32(0))
		BinopInst("<", LoadVarInst(loop, l217), Int32(3))
		StoreVarInst(loop, l217, BinopInst("+", LoadVarInst(loop, l217), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec182[LoadVarInst(loop, l217)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l218, Int32(0))
		BinopInst("<", LoadVarInst(loop, l218), Int32(2))
		StoreVarInst(loop, l218, BinopInst("+", LoadVarInst(loop, l218), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec181[LoadVarInst(loop, l218)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l219, Int32(0))
		BinopInst("<", LoadVarInst(loop, l219), Int32(3))
		StoreVarInst(loop, l219, BinopInst("+", LoadVarInst(loop, l219), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec194[LoadVarInst(loop, l219)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l220, Int32(0))
		BinopInst("<", LoadVarInst(loop, l220), Int32(3))
		StoreVarInst(loop, l220, BinopInst("+", LoadVarInst(loop, l220), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec193[LoadVarInst(loop, l220)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l221, Int32(0))
		BinopInst("<", LoadVarInst(loop, l221), Int32(3))
		StoreVarInst(loop, l221, BinopInst("+", LoadVarInst(loop, l221), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec192[LoadVarInst(loop, l221)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l222, Int32(0))
		BinopInst("<", LoadVarInst(loop, l222), Int32(3))
		StoreVarInst(loop, l222, BinopInst("+", LoadVarInst(loop, l222), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec191[LoadVarInst(loop, l222)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l223, Int32(0))
		BinopInst("<", LoadVarInst(loop, l223), Int32(3))
		StoreVarInst(loop, l223, BinopInst("+", LoadVarInst(loop, l223), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec190[LoadVarInst(loop, l223)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l224, Int32(0))
		BinopInst("<", LoadVarInst(loop, l224), Int32(3))
		StoreVarInst(loop, l224, BinopInst("+", LoadVarInst(loop, l224), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec189[LoadVarInst(loop, l224)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l225, Int32(0))
		BinopInst("<", LoadVarInst(loop, l225), Int32(2))
		StoreVarInst(loop, l225, BinopInst("+", LoadVarInst(loop, l225), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec188[LoadVarInst(loop, l225)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l226, Int32(0))
		BinopInst("<", LoadVarInst(loop, l226), Int32(3))
		StoreVarInst(loop, l226, BinopInst("+", LoadVarInst(loop, l226), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec201[LoadVarInst(loop, l226)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l227, Int32(0))
		BinopInst("<", LoadVarInst(loop, l227), Int32(3))
		StoreVarInst(loop, l227, BinopInst("+", LoadVarInst(loop, l227), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec200[LoadVarInst(loop, l227)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l228, Int32(0))
		BinopInst("<", LoadVarInst(loop, l228), Int32(3))
		StoreVarInst(loop, l228, BinopInst("+", LoadVarInst(loop, l228), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec199[LoadVarInst(loop, l228)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l229, Int32(0))
		BinopInst("<", LoadVarInst(loop, l229), Int32(3))
		StoreVarInst(loop, l229, BinopInst("+", LoadVarInst(loop, l229), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec198[LoadVarInst(loop, l229)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l230, Int32(0))
		BinopInst("<", LoadVarInst(loop, l230), Int32(3))
		StoreVarInst(loop, l230, BinopInst("+", LoadVarInst(loop, l230), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec197[LoadVarInst(loop, l230)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l231, Int32(0))
		BinopInst("<", LoadVarInst(loop, l231), Int32(3))
		StoreVarInst(loop, l231, BinopInst("+", LoadVarInst(loop, l231), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec196[LoadVarInst(loop, l231)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l232, Int32(0))
		BinopInst("<", LoadVarInst(loop, l232), Int32(2))
		StoreVarInst(loop, l232, BinopInst("+", LoadVarInst(loop, l232), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec195[LoadVarInst(loop, l232)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l233, Int32(0))
		BinopInst("<", LoadVarInst(loop, l233), Int32(3))
		StoreVarInst(loop, l233, BinopInst("+", LoadVarInst(loop, l233), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec205[LoadVarInst(loop, l233)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l234, Int32(0))
		BinopInst("<", LoadVarInst(loop, l234), Int32(3))
		StoreVarInst(loop, l234, BinopInst("+", LoadVarInst(loop, l234), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec204[LoadVarInst(loop, l234)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l235, Int32(0))
		BinopInst("<", LoadVarInst(loop, l235), Int32(3))
		StoreVarInst(loop, l235, BinopInst("+", LoadVarInst(loop, l235), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec203[LoadVarInst(loop, l235)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l236, Int32(0))
		BinopInst("<", LoadVarInst(loop, l236), Int32(2))
		StoreVarInst(loop, l236, BinopInst("+", LoadVarInst(loop, l236), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec202[LoadVarInst(loop, l236)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 32
Store = 0
Binop = 30
Numbers = 29
Declare = 29
Cast = 27
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider0))))))
	DeclareVarInst(stack, "int", iSlow5, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "int", iSlow7, CastInst("int", BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry0)), Float(-1.0f))))
	DeclareVarInst(stack, "int", iSlow8, BinopInst(">=", LoadVarInst(stack, iSlow7), Int32(2)))
	DeclareVarInst(stack, "int", iSlow9, BinopInst(">=", LoadVarInst(stack, iSlow7), Int32(1)))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst72), CastInst("float", LoadVarInst(struct, fVslider2))))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(440.0f), BinopInst("*", FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fVslider1)), Float(-49.0f)))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow10)))))
	DeclareVarInst(stack, "int", iSlow12, BinopInst(">=", LoadVarInst(stack, iSlow7), Int32(3)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("+", BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider3))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("+", BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider4))), Float(1.0f)))
	DeclareVarInst(stack, "int", iSlow15, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox3))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider5))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider6))))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider7))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider8))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider9))))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider10))))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider11))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider12))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider13))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider14))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 2622
Store = 650
Binop = 1933
Numbers = 746
Declare = 94
Cast = 28
Select = 0
Loop = 3
Funcall = 70

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec29[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec29[Int32(1)]))))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec31[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(struct, fRec31[Int32(0)]))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp0))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("+", LoadVarInst(struct, fRec30[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fVec1[Int32(1)]))))
		StoreVarInst(struct, fRec30[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), FunCallInst("floorf", LoadVarInst(stack, fTemp1))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec30[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp4))
		DeclareVarInst(stack, "float", fTemp5, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fVec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(struct, fVec3[Int32(1)])))), LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp6))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("+", LoadVarInst(stack, fTemp4), Float(-2.0f))))
		StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp7))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec5[Int32(1)])), LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp8))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec6[Int32(1)])), LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp9))
		DeclareVarInst(stack, "float", fTemp10, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec31[Int32(0)])))))
		StoreVarInst(struct, fVec8[Int32(0)], LoadVarInst(stack, fTemp10))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fVec8[Int32(1)]))))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp11), FunCallInst("floorf", LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec32[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fTemp12), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp14, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp13)))
		StoreVarInst(struct, fVec9[Int32(0)], LoadVarInst(stack, fTemp14))
		DeclareVarInst(stack, "float", fTemp15, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp13)))
		StoreVarInst(struct, fVec10[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec10[Int32(1)])))), LoadVarInst(stack, fTemp10)))
		StoreVarInst(struct, fVec11[Int32(0)], LoadVarInst(stack, fTemp16))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", LoadVarInst(stack, fTemp14), Float(-2.0f))))
		StoreVarInst(struct, fVec12[Int32(0)], LoadVarInst(stack, fTemp17))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp17), LoadVarInst(struct, fVec12[Int32(1)])), LoadVarInst(stack, fTemp10)))
		StoreVarInst(struct, fVec13[Int32(0)], LoadVarInst(stack, fTemp18))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fVec13[Int32(1)])), LoadVarInst(stack, fTemp10)))
		StoreVarInst(struct, fVec14[Int32(0)], LoadVarInst(stack, fTemp19))
		DeclareVarInst(stack, "float", fTemp20, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec31[Int32(0)])))))
		StoreVarInst(struct, fVec15[Int32(0)], LoadVarInst(stack, fTemp20))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("+", LoadVarInst(struct, fRec33[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fVec15[Int32(1)]))))
		StoreVarInst(struct, fRec33[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp21), FunCallInst("floorf", LoadVarInst(stack, fTemp21))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec33[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("+", LoadVarInst(stack, fTemp22), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp24, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp23)))
		StoreVarInst(struct, fVec16[Int32(0)], LoadVarInst(stack, fTemp24))
		DeclareVarInst(stack, "float", fTemp25, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp23)))
		StoreVarInst(struct, fVec17[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp25), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp22))))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp25), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp22), LoadVarInst(struct, fVec17[Int32(1)])))), LoadVarInst(stack, fTemp20)))
		StoreVarInst(struct, fVec18[Int32(0)], LoadVarInst(stack, fTemp26))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(stack, fTemp24), BinopInst("+", LoadVarInst(stack, fTemp24), Float(-2.0f))))
		StoreVarInst(struct, fVec19[Int32(0)], LoadVarInst(stack, fTemp27))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fVec19[Int32(1)])), LoadVarInst(stack, fTemp20)))
		StoreVarInst(struct, fVec20[Int32(0)], LoadVarInst(stack, fTemp28))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fVec20[Int32(1)])), LoadVarInst(stack, fTemp20)))
		StoreVarInst(struct, fVec21[Int32(0)], LoadVarInst(stack, fTemp29))
		StoreVarInst(struct, iRec34[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec34[Int32(1)])), Int32(12345)))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec34[Int32(0)]))))
		StoreVarInst(struct, fRec35[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.522189379f), LoadVarInst(struct, fRec35[Int32(3)])), BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("*", Float(2.49495602f), LoadVarInst(struct, fRec35[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(struct, fRec35[Int32(2)]))))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("*", LoadVarInst(struct, fRec29[Int32(0)]), Select2Inst(LoadVarInst(stack, iSlow5) CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])) Select2Inst(LoadVarInst(stack, iSlow6) Select2Inst(LoadVarInst(stack, iSlow15) BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0499220341f), LoadVarInst(struct, fRec35[Int32(0)])), BinopInst("*", Float(0.0506126992f), LoadVarInst(struct, fRec35[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.0959935337f), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", Float(0.00440878607f), LoadVarInst(struct, fRec35[Int32(3)])))) LoadVarInst(stack, fTemp30)) BinopInst("*", Float(0.333333343f), BinopInst("*", LoadVarInst(struct, fRec29[Int32(0)]), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow8) Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("*", LoadVarInst(struct, fConst75), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec7[Int32(1)]))), LoadVarInst(stack, fTemp0))) BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec4[Int32(1)]))), LoadVarInst(stack, fTemp0)))) Select2Inst(LoadVarInst(stack, iSlow9) BinopInst("*", LoadVarInst(struct, fConst73), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(struct, fVec2[Int32(1)]))), LoadVarInst(stack, fTemp0))) LoadVarInst(stack, fTemp3))), Select2Inst(LoadVarInst(stack, iSlow8) Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("*", LoadVarInst(struct, fConst75), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp19), LoadVarInst(struct, fVec14[Int32(1)]))), LoadVarInst(stack, fTemp10))) BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp16), LoadVarInst(struct, fVec11[Int32(1)]))), LoadVarInst(stack, fTemp10)))) Select2Inst(LoadVarInst(stack, iSlow9) BinopInst("*", LoadVarInst(struct, fConst73), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp14), LoadVarInst(struct, fVec9[Int32(1)]))), LoadVarInst(stack, fTemp10))) LoadVarInst(stack, fTemp13)))), Select2Inst(LoadVarInst(stack, iSlow8) Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("*", LoadVarInst(struct, fConst75), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp29), LoadVarInst(struct, fVec21[Int32(1)]))), LoadVarInst(stack, fTemp20))) BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec18[Int32(1)]))), LoadVarInst(stack, fTemp20)))) Select2Inst(LoadVarInst(stack, iSlow9) BinopInst("*", LoadVarInst(struct, fConst73), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fVec16[Int32(1)]))), LoadVarInst(stack, fTemp20))) LoadVarInst(stack, fTemp23))))))))))
		DeclareVarInst(stack, "float", fTemp32, Select2Inst(LoadVarInst(stack, iSlow3) Float(0.0f) LoadVarInst(stack, fTemp31)))
		StoreVarInst(struct, fVec22[Int32(0)], LoadVarInst(stack, fTemp32))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), BinopInst("+", LoadVarInst(stack, fTemp32), LoadVarInst(struct, fVec22[Int32(1)])))))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec27[Int32(2)]))))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", LoadVarInst(struct, fRec27[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec27[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec27[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst80), LoadVarInst(struct, fRec26[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec26[Int32(1)])))))
		StoreVarInst(struct, fVec23[Int32(0)], LoadVarInst(stack, fTemp33))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst63), LoadVarInst(struct, fRec25[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst67), BinopInst("+", LoadVarInst(stack, fTemp33), LoadVarInst(struct, fVec23[Int32(1)])))))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec25[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst83), LoadVarInst(struct, fRec24[Int32(2)]))))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", LoadVarInst(struct, fRec24[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec24[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec23[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("+", LoadVarInst(struct, fRec23[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec23[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec23[Int32(1)])))))
		StoreVarInst(struct, fVec24[Int32(0)], LoadVarInst(stack, fTemp34))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst60), BinopInst("+", LoadVarInst(stack, fTemp34), LoadVarInst(struct, fVec24[Int32(1)])))))
		StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec22[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec21[Int32(2)]))))))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", LoadVarInst(struct, fRec21[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec21[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec21[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fRec20[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(struct, fRec20[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec20[Int32(1)])))))
		StoreVarInst(struct, fVec25[Int32(0)], LoadVarInst(stack, fTemp35))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fVec25[Int32(1)])))))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec19[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(struct, fRec18[Int32(2)]))))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(struct, fRec18[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec18[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec18[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec17[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(struct, fRec17[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec17[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec17[Int32(1)])))))
		StoreVarInst(struct, fVec26[Int32(0)], LoadVarInst(stack, fTemp36))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst46), BinopInst("+", LoadVarInst(stack, fTemp36), LoadVarInst(struct, fVec26[Int32(1)])))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec15[Int32(2)]))))))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec15[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec15[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst100), LoadVarInst(struct, fRec14[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec14[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec14[Int32(1)])))))
		StoreVarInst(struct, fVec27[Int32(0)], LoadVarInst(stack, fTemp37))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst35), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst39), BinopInst("+", LoadVarInst(stack, fTemp37), LoadVarInst(struct, fVec27[Int32(1)])))))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec13[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst103), LoadVarInst(struct, fRec12[Int32(2)]))))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec12[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec11[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("+", LoadVarInst(struct, fRec11[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec11[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec11[Int32(1)])))))
		StoreVarInst(struct, fVec28[Int32(0)], LoadVarInst(stack, fTemp38))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst28), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst32), BinopInst("+", LoadVarInst(stack, fTemp38), LoadVarInst(struct, fVec28[Int32(1)])))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec9[Int32(2)]))))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", LoadVarInst(struct, fRec9[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec9[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fRec8[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("+", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec8[Int32(1)])), LoadVarInst(struct, fRec8[Int32(0)])), LoadVarInst(struct, fRec8[Int32(2)])))
		StoreVarInst(struct, fVec29[Int32(0)], LoadVarInst(stack, fTemp39))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst25), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst15), LoadVarInst(stack, fTemp39)), BinopInst("*", LoadVarInst(struct, fConst111), LoadVarInst(struct, fVec29[Int32(1)])))), BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec7[Int32(1)]))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec7[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst114), LoadVarInst(struct, fRec6[Int32(2)]))))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec6[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec6[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec6[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec5[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec4[Int32(1)])))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec5[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec5[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec4[Int32(2)]))))))
		StoreVarInst(struct, fRec36[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow16), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec36[Int32(1)]))))
		StoreVarInst(struct, fRec42[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec42[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst25), BinopInst("+", LoadVarInst(stack, fTemp39), LoadVarInst(struct, fVec29[Int32(1)])))))
		StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec42[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec41[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst114), LoadVarInst(struct, fRec41[Int32(2)]))))))
		StoreVarInst(struct, fRec40[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", LoadVarInst(struct, fRec41[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec41[Int32(1)])), LoadVarInst(struct, fRec41[Int32(0)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec40[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec40[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(struct, fRec40[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec40[Int32(1)])), LoadVarInst(struct, fRec40[Int32(0)]))))
		StoreVarInst(struct, fVec30[Int32(0)], LoadVarInst(stack, fTemp41))
		StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst126), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst127), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst117), LoadVarInst(stack, fTemp41)), BinopInst("*", LoadVarInst(struct, fConst128), LoadVarInst(struct, fVec30[Int32(1)]))))))
		StoreVarInst(struct, fRec38[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec39[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec38[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), LoadVarInst(struct, fRec38[Int32(2)]))))))
		StoreVarInst(struct, fRec37[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec38[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst123), LoadVarInst(struct, fRec38[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec38[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst122), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fRec37[Int32(2)]))))))
		StoreVarInst(struct, fRec43[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow17), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec43[Int32(1)]))))
		StoreVarInst(struct, fRec46[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst126), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst127), BinopInst("+", LoadVarInst(stack, fTemp41), LoadVarInst(struct, fVec30[Int32(1)])))))
		StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec46[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), LoadVarInst(struct, fRec45[Int32(2)]))))))
		StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", LoadVarInst(struct, fRec45[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec45[Int32(1)])), LoadVarInst(struct, fRec45[Int32(0)])))), BinopInst("*", LoadVarInst(struct, fConst122), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fRec44[Int32(2)]))))))
		StoreVarInst(struct, fRec47[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow18), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec47[Int32(1)]))))
		StoreVarInst(struct, fRec58[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fRec58[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(stack, fTemp32)), BinopInst("*", LoadVarInst(struct, fConst132), LoadVarInst(struct, fVec22[Int32(1)]))))))
		StoreVarInst(struct, fRec57[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec58[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec57[Int32(2)]))))))
		StoreVarInst(struct, fRec56[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec57[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec57[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst80), LoadVarInst(struct, fRec56[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec55[Int32(1)])))
		StoreVarInst(struct, fRec55[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec56[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec56[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec55[Int32(2)])), LoadVarInst(stack, fTemp42)))))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec54[Int32(1)])))
		StoreVarInst(struct, fRec54[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec55[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp42), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec55[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec54[Int32(2)])), LoadVarInst(stack, fTemp43)))))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec53[Int32(1)])))
		StoreVarInst(struct, fRec53[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec54[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp43), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec54[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec53[Int32(2)])), LoadVarInst(stack, fTemp44)))))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec52[Int32(1)])))
		StoreVarInst(struct, fRec52[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec53[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp44), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec53[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec52[Int32(2)])), LoadVarInst(stack, fTemp45)))))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec51[Int32(1)])))
		StoreVarInst(struct, fRec51[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec52[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp45), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec52[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec51[Int32(2)])), LoadVarInst(stack, fTemp46)))))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec50[Int32(1)])))
		StoreVarInst(struct, fRec50[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec51[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp46), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec51[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec50[Int32(2)])), LoadVarInst(stack, fTemp47)))))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec49[Int32(1)])))
		StoreVarInst(struct, fRec49[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec50[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp47), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec50[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec49[Int32(2)])), LoadVarInst(stack, fTemp48)))))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec48[Int32(1)])))
		StoreVarInst(struct, fRec48[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec49[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", LoadVarInst(stack, fTemp48), BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec49[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst145), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst146), LoadVarInst(struct, fRec48[Int32(2)])), LoadVarInst(stack, fTemp49)))))
		StoreVarInst(struct, fRec59[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow19), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec59[Int32(1)]))))
		StoreVarInst(struct, fRec69[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst63), LoadVarInst(struct, fRec69[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst67), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst58), LoadVarInst(stack, fTemp33)), BinopInst("*", LoadVarInst(struct, fConst148), LoadVarInst(struct, fVec23[Int32(1)]))))))
		StoreVarInst(struct, fRec68[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec69[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec68[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst83), LoadVarInst(struct, fRec68[Int32(2)]))))))
		StoreVarInst(struct, fRec67[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec68[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst147), LoadVarInst(struct, fRec68[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec68[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec67[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec67[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec66[Int32(1)])))
		StoreVarInst(struct, fRec66[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst147), LoadVarInst(struct, fRec67[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec67[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec67[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp50), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec66[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec65[Int32(1)])))
		StoreVarInst(struct, fRec65[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec66[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp50), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec66[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp51), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec65[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp52, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec64[Int32(1)])))
		StoreVarInst(struct, fRec64[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec65[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp51), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec65[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp52), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec64[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec63[Int32(1)])))
		StoreVarInst(struct, fRec63[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec64[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp52), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec64[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp53), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec63[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec62[Int32(1)])))
		StoreVarInst(struct, fRec62[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec63[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp53), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec63[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp54), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec62[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec61[Int32(1)])))
		StoreVarInst(struct, fRec61[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec62[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp54), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec62[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp55), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec61[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec60[Int32(1)])))
		StoreVarInst(struct, fRec60[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec61[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp55), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec61[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec60[Int32(2)]))))))
		StoreVarInst(struct, fRec70[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec70[Int32(1)]))))
		StoreVarInst(struct, fRec79[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec79[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst60), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst51), LoadVarInst(stack, fTemp34)), BinopInst("*", LoadVarInst(struct, fConst150), LoadVarInst(struct, fVec24[Int32(1)]))))))
		StoreVarInst(struct, fRec78[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec79[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec78[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec78[Int32(2)]))))))
		StoreVarInst(struct, fRec77[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec78[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst149), LoadVarInst(struct, fRec78[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec78[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fRec77[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec76[Int32(1)])))
		StoreVarInst(struct, fRec76[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst149), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec77[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec77[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp57), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec76[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec75[Int32(1)])))
		StoreVarInst(struct, fRec75[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec76[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp57), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec76[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec75[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp59, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec74[Int32(1)])))
		StoreVarInst(struct, fRec74[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec75[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec75[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec74[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec73[Int32(1)])))
		StoreVarInst(struct, fRec73[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec74[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec74[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec73[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp61, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec72[Int32(1)])))
		StoreVarInst(struct, fRec72[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec73[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec73[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp61), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec72[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp62, BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec71[Int32(1)])))
		StoreVarInst(struct, fRec71[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec72[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp61), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec72[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp62), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec71[Int32(2)]))))))
		StoreVarInst(struct, fRec80[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow21), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec80[Int32(1)]))))
		StoreVarInst(struct, fRec88[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec88[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(stack, fTemp35)), BinopInst("*", LoadVarInst(struct, fConst152), LoadVarInst(struct, fVec25[Int32(1)]))))))
		StoreVarInst(struct, fRec87[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec88[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec87[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(struct, fRec87[Int32(2)]))))))
		StoreVarInst(struct, fRec86[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec87[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst151), LoadVarInst(struct, fRec87[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec87[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec86[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec86[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp63, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec85[Int32(1)])))
		StoreVarInst(struct, fRec85[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst151), LoadVarInst(struct, fRec86[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec86[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec86[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec85[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec84[Int32(1)])))
		StoreVarInst(struct, fRec84[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec85[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec85[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp64), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec84[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp65, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec83[Int32(1)])))
		StoreVarInst(struct, fRec83[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec84[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp64), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec84[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp65), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec83[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp66, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec82[Int32(1)])))
		StoreVarInst(struct, fRec82[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec83[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp65), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec83[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp66), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec82[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp67, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec81[Int32(1)])))
		StoreVarInst(struct, fRec81[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec82[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp66), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec82[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp67), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec81[Int32(2)]))))))
		StoreVarInst(struct, fRec89[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow22), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec89[Int32(1)]))))
		StoreVarInst(struct, fRec96[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec96[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst46), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(stack, fTemp36)), BinopInst("*", LoadVarInst(struct, fConst154), LoadVarInst(struct, fVec26[Int32(1)]))))))
		StoreVarInst(struct, fRec95[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec96[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec95[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec95[Int32(2)]))))))
		StoreVarInst(struct, fRec94[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec95[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst153), LoadVarInst(struct, fRec95[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec95[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec94[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst100), LoadVarInst(struct, fRec94[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp68, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec93[Int32(1)])))
		StoreVarInst(struct, fRec93[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst153), LoadVarInst(struct, fRec94[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec94[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec94[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp68), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec93[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp69, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec92[Int32(1)])))
		StoreVarInst(struct, fRec92[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec93[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp68), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec93[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp69), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec92[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp70, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec91[Int32(1)])))
		StoreVarInst(struct, fRec91[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec92[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp69), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec92[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp70), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec91[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp71, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec90[Int32(1)])))
		StoreVarInst(struct, fRec90[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec91[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp70), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec91[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp71), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec90[Int32(2)]))))))
		StoreVarInst(struct, fRec97[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow23), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec97[Int32(1)]))))
		StoreVarInst(struct, fRec103[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst35), LoadVarInst(struct, fRec103[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst39), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(stack, fTemp37)), BinopInst("*", LoadVarInst(struct, fConst156), LoadVarInst(struct, fVec27[Int32(1)]))))))
		StoreVarInst(struct, fRec102[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec103[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec102[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst103), LoadVarInst(struct, fRec102[Int32(2)]))))))
		StoreVarInst(struct, fRec101[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec102[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst155), LoadVarInst(struct, fRec102[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec102[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec101[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec101[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp72, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec100[Int32(1)])))
		StoreVarInst(struct, fRec100[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst155), LoadVarInst(struct, fRec101[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec101[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec101[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp72), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec100[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp73, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec99[Int32(1)])))
		StoreVarInst(struct, fRec99[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec100[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp72), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec100[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp73), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec99[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp74, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec98[Int32(1)])))
		StoreVarInst(struct, fRec98[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec99[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp73), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec99[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp74), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec98[Int32(2)]))))))
		StoreVarInst(struct, fRec104[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow24), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec104[Int32(1)]))))
		StoreVarInst(struct, fRec109[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst28), LoadVarInst(struct, fRec109[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst32), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst22), LoadVarInst(stack, fTemp38)), BinopInst("*", LoadVarInst(struct, fConst158), LoadVarInst(struct, fVec28[Int32(1)]))))))
		StoreVarInst(struct, fRec108[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec109[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec108[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec108[Int32(2)]))))))
		StoreVarInst(struct, fRec107[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec108[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst157), LoadVarInst(struct, fRec108[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec108[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec107[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fRec107[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp75, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec106[Int32(1)])))
		StoreVarInst(struct, fRec106[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst157), LoadVarInst(struct, fRec107[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec107[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec107[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp75), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec106[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp76, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec105[Int32(1)])))
		StoreVarInst(struct, fRec105[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec106[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp75), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec106[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp76), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec105[Int32(2)]))))))
		StoreVarInst(struct, fRec110[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow25), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec110[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp77, Select2Inst(LoadVarInst(stack, iSlow3) LoadVarInst(stack, fTemp31) BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec4[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec4[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec36[Int32(0)])))), BinopInst("*", LoadVarInst(struct, fConst122), BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst123), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec37[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec37[Int32(2)]))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec43[Int32(0)])))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec44[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec44[Int32(1)])), LoadVarInst(struct, fRec44[Int32(0)]))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec47[Int32(0)]))))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec48[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst145), BinopInst("+", LoadVarInst(stack, fTemp49), BinopInst("*", LoadVarInst(struct, fConst146), LoadVarInst(struct, fRec48[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec59[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec60[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec60[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec70[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec71[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp62), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec71[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec80[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec81[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp67), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec81[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec89[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec90[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp71), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec90[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec97[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec98[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp74), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec98[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec104[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec105[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp76), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec105[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec110[Int32(0)])))))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp77), BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst159), LoadVarInst(struct, fRec3[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst161), LoadVarInst(struct, fRec3[Int32(1)]))))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst162), LoadVarInst(struct, fRec3[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst162), LoadVarInst(struct, fRec3[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst8), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst163), LoadVarInst(struct, fRec2[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst164), LoadVarInst(struct, fRec2[Int32(1)]))))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst8), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst10), LoadVarInst(struct, fRec2[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst165), LoadVarInst(struct, fRec2[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst165), LoadVarInst(struct, fRec2[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst166), LoadVarInst(struct, fRec1[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst167), LoadVarInst(struct, fRec1[Int32(1)]))))))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst168), LoadVarInst(struct, fRec1[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst168), LoadVarInst(struct, fRec1[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec0[Int32(0)])))))))
		StoreVarInst(struct, fRec117[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp77), BinopInst("*", LoadVarInst(struct, fConst185), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst188), LoadVarInst(struct, fRec117[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst189), LoadVarInst(struct, fRec117[Int32(1)]))))))
		StoreVarInst(struct, fRec116[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst185), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst187), LoadVarInst(struct, fRec117[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst190), LoadVarInst(struct, fRec117[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst190), LoadVarInst(struct, fRec117[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst183), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst191), LoadVarInst(struct, fRec116[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst192), LoadVarInst(struct, fRec116[Int32(1)]))))))
		StoreVarInst(struct, fRec115[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst183), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst184), LoadVarInst(struct, fRec116[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst193), LoadVarInst(struct, fRec116[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst193), LoadVarInst(struct, fRec116[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst181), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst194), LoadVarInst(struct, fRec115[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst195), LoadVarInst(struct, fRec115[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp78, BinopInst("*", LoadVarInst(struct, fConst181), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst182), LoadVarInst(struct, fRec115[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst196), LoadVarInst(struct, fRec115[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst196), LoadVarInst(struct, fRec115[Int32(2)])))))
		StoreVarInst(struct, fRec114[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp78), BinopInst("*", LoadVarInst(struct, fConst178), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst197), LoadVarInst(struct, fRec114[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst199), LoadVarInst(struct, fRec114[Int32(1)]))))))
		StoreVarInst(struct, fRec113[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst178), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst180), LoadVarInst(struct, fRec114[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst200), LoadVarInst(struct, fRec114[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst200), LoadVarInst(struct, fRec114[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst175), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst201), LoadVarInst(struct, fRec113[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst202), LoadVarInst(struct, fRec113[Int32(1)]))))))
		StoreVarInst(struct, fRec112[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst175), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst177), LoadVarInst(struct, fRec113[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst203), LoadVarInst(struct, fRec113[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst203), LoadVarInst(struct, fRec113[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst171), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst204), LoadVarInst(struct, fRec112[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst205), LoadVarInst(struct, fRec112[Int32(1)]))))))
		StoreVarInst(struct, fRec111[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec111[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst171), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst174), LoadVarInst(struct, fRec112[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst206), LoadVarInst(struct, fRec112[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst206), LoadVarInst(struct, fRec112[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec111[Int32(0)])))))))
		StoreVarInst(struct, fRec124[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp78), BinopInst("*", LoadVarInst(struct, fConst223), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst226), LoadVarInst(struct, fRec124[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst227), LoadVarInst(struct, fRec124[Int32(1)]))))))
		StoreVarInst(struct, fRec123[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst223), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst225), LoadVarInst(struct, fRec124[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst228), LoadVarInst(struct, fRec124[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst228), LoadVarInst(struct, fRec124[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst221), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst229), LoadVarInst(struct, fRec123[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst230), LoadVarInst(struct, fRec123[Int32(1)]))))))
		StoreVarInst(struct, fRec122[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst221), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst222), LoadVarInst(struct, fRec123[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst231), LoadVarInst(struct, fRec123[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst231), LoadVarInst(struct, fRec123[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst219), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst232), LoadVarInst(struct, fRec122[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst233), LoadVarInst(struct, fRec122[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp79, BinopInst("*", LoadVarInst(struct, fConst219), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst220), LoadVarInst(struct, fRec122[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst234), LoadVarInst(struct, fRec122[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst234), LoadVarInst(struct, fRec122[Int32(2)])))))
		StoreVarInst(struct, fRec121[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp79), BinopInst("*", LoadVarInst(struct, fConst216), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst235), LoadVarInst(struct, fRec121[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst237), LoadVarInst(struct, fRec121[Int32(1)]))))))
		StoreVarInst(struct, fRec120[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst216), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst218), LoadVarInst(struct, fRec121[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst238), LoadVarInst(struct, fRec121[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst238), LoadVarInst(struct, fRec121[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst213), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst239), LoadVarInst(struct, fRec120[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst240), LoadVarInst(struct, fRec120[Int32(1)]))))))
		StoreVarInst(struct, fRec119[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst213), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst215), LoadVarInst(struct, fRec120[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst241), LoadVarInst(struct, fRec120[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst241), LoadVarInst(struct, fRec120[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst209), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst242), LoadVarInst(struct, fRec119[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst243), LoadVarInst(struct, fRec119[Int32(1)]))))))
		StoreVarInst(struct, fRec118[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec118[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst209), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst212), LoadVarInst(struct, fRec119[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst244), LoadVarInst(struct, fRec119[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst244), LoadVarInst(struct, fRec119[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec118[Int32(0)])))))))
		StoreVarInst(struct, fRec131[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp79), BinopInst("*", LoadVarInst(struct, fConst261), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst264), LoadVarInst(struct, fRec131[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst265), LoadVarInst(struct, fRec131[Int32(1)]))))))
		StoreVarInst(struct, fRec130[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst261), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst263), LoadVarInst(struct, fRec131[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst266), LoadVarInst(struct, fRec131[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst266), LoadVarInst(struct, fRec131[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst259), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst267), LoadVarInst(struct, fRec130[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst268), LoadVarInst(struct, fRec130[Int32(1)]))))))
		StoreVarInst(struct, fRec129[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst259), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst260), LoadVarInst(struct, fRec130[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst269), LoadVarInst(struct, fRec130[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst269), LoadVarInst(struct, fRec130[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst257), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst270), LoadVarInst(struct, fRec129[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst271), LoadVarInst(struct, fRec129[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp80, BinopInst("*", LoadVarInst(struct, fConst257), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst258), LoadVarInst(struct, fRec129[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst272), LoadVarInst(struct, fRec129[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst272), LoadVarInst(struct, fRec129[Int32(2)])))))
		StoreVarInst(struct, fRec128[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp80), BinopInst("*", LoadVarInst(struct, fConst254), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst273), LoadVarInst(struct, fRec128[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst275), LoadVarInst(struct, fRec128[Int32(1)]))))))
		StoreVarInst(struct, fRec127[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst254), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst256), LoadVarInst(struct, fRec128[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst276), LoadVarInst(struct, fRec128[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst276), LoadVarInst(struct, fRec128[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst251), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst277), LoadVarInst(struct, fRec127[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst278), LoadVarInst(struct, fRec127[Int32(1)]))))))
		StoreVarInst(struct, fRec126[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst251), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst253), LoadVarInst(struct, fRec127[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst279), LoadVarInst(struct, fRec127[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst279), LoadVarInst(struct, fRec127[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst247), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst280), LoadVarInst(struct, fRec126[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst281), LoadVarInst(struct, fRec126[Int32(1)]))))))
		StoreVarInst(struct, fRec125[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec125[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst247), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst250), LoadVarInst(struct, fRec126[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst282), LoadVarInst(struct, fRec126[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst282), LoadVarInst(struct, fRec126[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec125[Int32(0)])))))))
		StoreVarInst(struct, fRec138[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp80), BinopInst("*", LoadVarInst(struct, fConst299), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst302), LoadVarInst(struct, fRec138[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst303), LoadVarInst(struct, fRec138[Int32(1)]))))))
		StoreVarInst(struct, fRec137[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst299), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst301), LoadVarInst(struct, fRec138[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst304), LoadVarInst(struct, fRec138[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst304), LoadVarInst(struct, fRec138[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst297), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst305), LoadVarInst(struct, fRec137[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst306), LoadVarInst(struct, fRec137[Int32(1)]))))))
		StoreVarInst(struct, fRec136[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst297), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst298), LoadVarInst(struct, fRec137[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst307), LoadVarInst(struct, fRec137[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst307), LoadVarInst(struct, fRec137[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst295), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst308), LoadVarInst(struct, fRec136[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst309), LoadVarInst(struct, fRec136[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp81, BinopInst("*", LoadVarInst(struct, fConst295), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst296), LoadVarInst(struct, fRec136[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst310), LoadVarInst(struct, fRec136[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst310), LoadVarInst(struct, fRec136[Int32(2)])))))
		StoreVarInst(struct, fRec135[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp81), BinopInst("*", LoadVarInst(struct, fConst292), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst311), LoadVarInst(struct, fRec135[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst313), LoadVarInst(struct, fRec135[Int32(1)]))))))
		StoreVarInst(struct, fRec134[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst292), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst294), LoadVarInst(struct, fRec135[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst314), LoadVarInst(struct, fRec135[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst314), LoadVarInst(struct, fRec135[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst289), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst315), LoadVarInst(struct, fRec134[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst316), LoadVarInst(struct, fRec134[Int32(1)]))))))
		StoreVarInst(struct, fRec133[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst289), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst291), LoadVarInst(struct, fRec134[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst317), LoadVarInst(struct, fRec134[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst317), LoadVarInst(struct, fRec134[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst285), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst318), LoadVarInst(struct, fRec133[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst319), LoadVarInst(struct, fRec133[Int32(1)]))))))
		StoreVarInst(struct, fRec132[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec132[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst285), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst288), LoadVarInst(struct, fRec133[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst320), LoadVarInst(struct, fRec133[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst320), LoadVarInst(struct, fRec133[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec132[Int32(0)])))))))
		StoreVarInst(struct, fRec145[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp81), BinopInst("*", LoadVarInst(struct, fConst337), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst340), LoadVarInst(struct, fRec145[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst341), LoadVarInst(struct, fRec145[Int32(1)]))))))
		StoreVarInst(struct, fRec144[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst337), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst339), LoadVarInst(struct, fRec145[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst342), LoadVarInst(struct, fRec145[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst342), LoadVarInst(struct, fRec145[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst335), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst343), LoadVarInst(struct, fRec144[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst344), LoadVarInst(struct, fRec144[Int32(1)]))))))
		StoreVarInst(struct, fRec143[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst335), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst336), LoadVarInst(struct, fRec144[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst345), LoadVarInst(struct, fRec144[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst345), LoadVarInst(struct, fRec144[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst333), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst346), LoadVarInst(struct, fRec143[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst347), LoadVarInst(struct, fRec143[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp82, BinopInst("*", LoadVarInst(struct, fConst333), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst334), LoadVarInst(struct, fRec143[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst348), LoadVarInst(struct, fRec143[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst348), LoadVarInst(struct, fRec143[Int32(2)])))))
		StoreVarInst(struct, fRec142[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp82), BinopInst("*", LoadVarInst(struct, fConst330), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst349), LoadVarInst(struct, fRec142[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst351), LoadVarInst(struct, fRec142[Int32(1)]))))))
		StoreVarInst(struct, fRec141[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst330), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst332), LoadVarInst(struct, fRec142[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst352), LoadVarInst(struct, fRec142[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst352), LoadVarInst(struct, fRec142[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst327), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst353), LoadVarInst(struct, fRec141[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst354), LoadVarInst(struct, fRec141[Int32(1)]))))))
		StoreVarInst(struct, fRec140[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst327), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst329), LoadVarInst(struct, fRec141[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst355), LoadVarInst(struct, fRec141[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst355), LoadVarInst(struct, fRec141[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst323), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst356), LoadVarInst(struct, fRec140[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst357), LoadVarInst(struct, fRec140[Int32(1)]))))))
		StoreVarInst(struct, fRec139[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec139[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst323), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst326), LoadVarInst(struct, fRec140[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst358), LoadVarInst(struct, fRec140[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst358), LoadVarInst(struct, fRec140[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec139[Int32(0)])))))))
		StoreVarInst(struct, fRec152[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp82), BinopInst("*", LoadVarInst(struct, fConst375), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst378), LoadVarInst(struct, fRec152[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst379), LoadVarInst(struct, fRec152[Int32(1)]))))))
		StoreVarInst(struct, fRec151[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst375), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst377), LoadVarInst(struct, fRec152[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst380), LoadVarInst(struct, fRec152[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst380), LoadVarInst(struct, fRec152[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst373), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst381), LoadVarInst(struct, fRec151[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst382), LoadVarInst(struct, fRec151[Int32(1)]))))))
		StoreVarInst(struct, fRec150[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst373), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst374), LoadVarInst(struct, fRec151[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst383), LoadVarInst(struct, fRec151[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst383), LoadVarInst(struct, fRec151[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst371), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst384), LoadVarInst(struct, fRec150[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst385), LoadVarInst(struct, fRec150[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp83, BinopInst("*", LoadVarInst(struct, fConst371), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst372), LoadVarInst(struct, fRec150[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst386), LoadVarInst(struct, fRec150[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst386), LoadVarInst(struct, fRec150[Int32(2)])))))
		StoreVarInst(struct, fRec149[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp83), BinopInst("*", LoadVarInst(struct, fConst368), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst387), LoadVarInst(struct, fRec149[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst389), LoadVarInst(struct, fRec149[Int32(1)]))))))
		StoreVarInst(struct, fRec148[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst368), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst370), LoadVarInst(struct, fRec149[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst390), LoadVarInst(struct, fRec149[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst390), LoadVarInst(struct, fRec149[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst365), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst391), LoadVarInst(struct, fRec148[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst392), LoadVarInst(struct, fRec148[Int32(1)]))))))
		StoreVarInst(struct, fRec147[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst365), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst367), LoadVarInst(struct, fRec148[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst393), LoadVarInst(struct, fRec148[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst393), LoadVarInst(struct, fRec148[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst361), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst394), LoadVarInst(struct, fRec147[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst395), LoadVarInst(struct, fRec147[Int32(1)]))))))
		StoreVarInst(struct, fRec146[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec146[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst361), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst364), LoadVarInst(struct, fRec147[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst396), LoadVarInst(struct, fRec147[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst396), LoadVarInst(struct, fRec147[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec146[Int32(0)])))))))
		StoreVarInst(struct, fRec159[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp83), BinopInst("*", LoadVarInst(struct, fConst413), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst416), LoadVarInst(struct, fRec159[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst417), LoadVarInst(struct, fRec159[Int32(1)]))))))
		StoreVarInst(struct, fRec158[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst413), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst415), LoadVarInst(struct, fRec159[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst418), LoadVarInst(struct, fRec159[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst418), LoadVarInst(struct, fRec159[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst411), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst419), LoadVarInst(struct, fRec158[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst420), LoadVarInst(struct, fRec158[Int32(1)]))))))
		StoreVarInst(struct, fRec157[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst411), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst412), LoadVarInst(struct, fRec158[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst421), LoadVarInst(struct, fRec158[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst421), LoadVarInst(struct, fRec158[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst409), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst422), LoadVarInst(struct, fRec157[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst423), LoadVarInst(struct, fRec157[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp84, BinopInst("*", LoadVarInst(struct, fConst409), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst410), LoadVarInst(struct, fRec157[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst424), LoadVarInst(struct, fRec157[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst424), LoadVarInst(struct, fRec157[Int32(2)])))))
		StoreVarInst(struct, fRec156[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp84), BinopInst("*", LoadVarInst(struct, fConst406), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst425), LoadVarInst(struct, fRec156[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst427), LoadVarInst(struct, fRec156[Int32(1)]))))))
		StoreVarInst(struct, fRec155[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst406), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst408), LoadVarInst(struct, fRec156[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst428), LoadVarInst(struct, fRec156[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst428), LoadVarInst(struct, fRec156[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst403), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst429), LoadVarInst(struct, fRec155[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst430), LoadVarInst(struct, fRec155[Int32(1)]))))))
		StoreVarInst(struct, fRec154[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst403), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst405), LoadVarInst(struct, fRec155[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst431), LoadVarInst(struct, fRec155[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst431), LoadVarInst(struct, fRec155[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst399), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst432), LoadVarInst(struct, fRec154[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst433), LoadVarInst(struct, fRec154[Int32(1)]))))))
		StoreVarInst(struct, fRec153[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec153[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst399), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst402), LoadVarInst(struct, fRec154[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst434), LoadVarInst(struct, fRec154[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst434), LoadVarInst(struct, fRec154[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec153[Int32(0)])))))))
		StoreVarInst(struct, fRec166[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp84), BinopInst("*", LoadVarInst(struct, fConst451), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst454), LoadVarInst(struct, fRec166[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst455), LoadVarInst(struct, fRec166[Int32(1)]))))))
		StoreVarInst(struct, fRec165[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst451), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst453), LoadVarInst(struct, fRec166[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst456), LoadVarInst(struct, fRec166[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst456), LoadVarInst(struct, fRec166[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst449), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst457), LoadVarInst(struct, fRec165[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst458), LoadVarInst(struct, fRec165[Int32(1)]))))))
		StoreVarInst(struct, fRec164[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst449), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst450), LoadVarInst(struct, fRec165[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst459), LoadVarInst(struct, fRec165[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst459), LoadVarInst(struct, fRec165[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst447), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst460), LoadVarInst(struct, fRec164[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst461), LoadVarInst(struct, fRec164[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp85, BinopInst("*", LoadVarInst(struct, fConst447), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst448), LoadVarInst(struct, fRec164[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst462), LoadVarInst(struct, fRec164[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst462), LoadVarInst(struct, fRec164[Int32(2)])))))
		StoreVarInst(struct, fRec163[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp85), BinopInst("*", LoadVarInst(struct, fConst444), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst463), LoadVarInst(struct, fRec163[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst465), LoadVarInst(struct, fRec163[Int32(1)]))))))
		StoreVarInst(struct, fRec162[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst444), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst446), LoadVarInst(struct, fRec163[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst466), LoadVarInst(struct, fRec163[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst466), LoadVarInst(struct, fRec163[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst441), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst467), LoadVarInst(struct, fRec162[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst468), LoadVarInst(struct, fRec162[Int32(1)]))))))
		StoreVarInst(struct, fRec161[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst441), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst443), LoadVarInst(struct, fRec162[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst469), LoadVarInst(struct, fRec162[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst469), LoadVarInst(struct, fRec162[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst437), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst470), LoadVarInst(struct, fRec161[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst471), LoadVarInst(struct, fRec161[Int32(1)]))))))
		StoreVarInst(struct, fRec160[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec160[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst437), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst440), LoadVarInst(struct, fRec161[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst472), LoadVarInst(struct, fRec161[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst472), LoadVarInst(struct, fRec161[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph8, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec160[Int32(0)])))))))
		StoreVarInst(struct, fRec173[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp85), BinopInst("*", LoadVarInst(struct, fConst489), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst492), LoadVarInst(struct, fRec173[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst493), LoadVarInst(struct, fRec173[Int32(1)]))))))
		StoreVarInst(struct, fRec172[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst489), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst491), LoadVarInst(struct, fRec173[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst494), LoadVarInst(struct, fRec173[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst494), LoadVarInst(struct, fRec173[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst487), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst495), LoadVarInst(struct, fRec172[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst496), LoadVarInst(struct, fRec172[Int32(1)]))))))
		StoreVarInst(struct, fRec171[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst487), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst488), LoadVarInst(struct, fRec172[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst497), LoadVarInst(struct, fRec172[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst497), LoadVarInst(struct, fRec172[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst485), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst498), LoadVarInst(struct, fRec171[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst499), LoadVarInst(struct, fRec171[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp86, BinopInst("*", LoadVarInst(struct, fConst485), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst486), LoadVarInst(struct, fRec171[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst500), LoadVarInst(struct, fRec171[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst500), LoadVarInst(struct, fRec171[Int32(2)])))))
		StoreVarInst(struct, fRec170[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp86), BinopInst("*", LoadVarInst(struct, fConst482), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst501), LoadVarInst(struct, fRec170[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst503), LoadVarInst(struct, fRec170[Int32(1)]))))))
		StoreVarInst(struct, fRec169[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst482), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst484), LoadVarInst(struct, fRec170[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst504), LoadVarInst(struct, fRec170[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst504), LoadVarInst(struct, fRec170[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst479), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst505), LoadVarInst(struct, fRec169[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst506), LoadVarInst(struct, fRec169[Int32(1)]))))))
		StoreVarInst(struct, fRec168[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst479), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst481), LoadVarInst(struct, fRec169[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst507), LoadVarInst(struct, fRec169[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst507), LoadVarInst(struct, fRec169[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst475), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst508), LoadVarInst(struct, fRec168[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst509), LoadVarInst(struct, fRec168[Int32(1)]))))))
		StoreVarInst(struct, fRec167[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec167[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst475), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst478), LoadVarInst(struct, fRec168[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst510), LoadVarInst(struct, fRec168[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst510), LoadVarInst(struct, fRec168[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph9, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec167[Int32(0)])))))))
		StoreVarInst(struct, fRec180[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp86), BinopInst("*", LoadVarInst(struct, fConst527), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst530), LoadVarInst(struct, fRec180[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst531), LoadVarInst(struct, fRec180[Int32(1)]))))))
		StoreVarInst(struct, fRec179[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst527), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst529), LoadVarInst(struct, fRec180[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst532), LoadVarInst(struct, fRec180[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst532), LoadVarInst(struct, fRec180[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst525), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst533), LoadVarInst(struct, fRec179[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst534), LoadVarInst(struct, fRec179[Int32(1)]))))))
		StoreVarInst(struct, fRec178[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst525), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst526), LoadVarInst(struct, fRec179[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst535), LoadVarInst(struct, fRec179[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst535), LoadVarInst(struct, fRec179[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst523), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst536), LoadVarInst(struct, fRec178[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst537), LoadVarInst(struct, fRec178[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp87, BinopInst("*", LoadVarInst(struct, fConst523), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst524), LoadVarInst(struct, fRec178[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst538), LoadVarInst(struct, fRec178[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst538), LoadVarInst(struct, fRec178[Int32(2)])))))
		StoreVarInst(struct, fRec177[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp87), BinopInst("*", LoadVarInst(struct, fConst520), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst539), LoadVarInst(struct, fRec177[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst541), LoadVarInst(struct, fRec177[Int32(1)]))))))
		StoreVarInst(struct, fRec176[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst520), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst522), LoadVarInst(struct, fRec177[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst542), LoadVarInst(struct, fRec177[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst542), LoadVarInst(struct, fRec177[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst517), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst543), LoadVarInst(struct, fRec176[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst544), LoadVarInst(struct, fRec176[Int32(1)]))))))
		StoreVarInst(struct, fRec175[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst517), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst519), LoadVarInst(struct, fRec176[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst545), LoadVarInst(struct, fRec176[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst545), LoadVarInst(struct, fRec176[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst513), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst546), LoadVarInst(struct, fRec175[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst547), LoadVarInst(struct, fRec175[Int32(1)]))))))
		StoreVarInst(struct, fRec174[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec174[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst513), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst516), LoadVarInst(struct, fRec175[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst548), LoadVarInst(struct, fRec175[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst548), LoadVarInst(struct, fRec175[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph10, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec174[Int32(0)])))))))
		StoreVarInst(struct, fRec187[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp87), BinopInst("*", LoadVarInst(struct, fConst565), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst568), LoadVarInst(struct, fRec187[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst569), LoadVarInst(struct, fRec187[Int32(1)]))))))
		StoreVarInst(struct, fRec186[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst565), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst567), LoadVarInst(struct, fRec187[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst570), LoadVarInst(struct, fRec187[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst570), LoadVarInst(struct, fRec187[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst563), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst571), LoadVarInst(struct, fRec186[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst572), LoadVarInst(struct, fRec186[Int32(1)]))))))
		StoreVarInst(struct, fRec185[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst563), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst564), LoadVarInst(struct, fRec186[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst573), LoadVarInst(struct, fRec186[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst573), LoadVarInst(struct, fRec186[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst561), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst574), LoadVarInst(struct, fRec185[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst575), LoadVarInst(struct, fRec185[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp88, BinopInst("*", LoadVarInst(struct, fConst561), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst562), LoadVarInst(struct, fRec185[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst576), LoadVarInst(struct, fRec185[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst576), LoadVarInst(struct, fRec185[Int32(2)])))))
		StoreVarInst(struct, fRec184[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp88), BinopInst("*", LoadVarInst(struct, fConst558), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst577), LoadVarInst(struct, fRec184[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst579), LoadVarInst(struct, fRec184[Int32(1)]))))))
		StoreVarInst(struct, fRec183[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst558), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst560), LoadVarInst(struct, fRec184[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst580), LoadVarInst(struct, fRec184[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst580), LoadVarInst(struct, fRec184[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst555), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst581), LoadVarInst(struct, fRec183[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst582), LoadVarInst(struct, fRec183[Int32(1)]))))))
		StoreVarInst(struct, fRec182[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst555), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst557), LoadVarInst(struct, fRec183[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst583), LoadVarInst(struct, fRec183[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst583), LoadVarInst(struct, fRec183[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst551), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst584), LoadVarInst(struct, fRec182[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst585), LoadVarInst(struct, fRec182[Int32(1)]))))))
		StoreVarInst(struct, fRec181[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec181[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst551), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst554), LoadVarInst(struct, fRec182[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst586), LoadVarInst(struct, fRec182[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst586), LoadVarInst(struct, fRec182[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph11, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec181[Int32(0)])))))))
		StoreVarInst(struct, fRec194[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp88), BinopInst("*", LoadVarInst(struct, fConst603), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst606), LoadVarInst(struct, fRec194[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst607), LoadVarInst(struct, fRec194[Int32(1)]))))))
		StoreVarInst(struct, fRec193[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst603), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst605), LoadVarInst(struct, fRec194[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst608), LoadVarInst(struct, fRec194[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst608), LoadVarInst(struct, fRec194[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst601), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst609), LoadVarInst(struct, fRec193[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst610), LoadVarInst(struct, fRec193[Int32(1)]))))))
		StoreVarInst(struct, fRec192[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst601), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst602), LoadVarInst(struct, fRec193[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst611), LoadVarInst(struct, fRec193[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst611), LoadVarInst(struct, fRec193[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst599), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst612), LoadVarInst(struct, fRec192[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst613), LoadVarInst(struct, fRec192[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp89, BinopInst("*", LoadVarInst(struct, fConst599), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst600), LoadVarInst(struct, fRec192[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst614), LoadVarInst(struct, fRec192[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst614), LoadVarInst(struct, fRec192[Int32(2)])))))
		StoreVarInst(struct, fRec191[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp89), BinopInst("*", LoadVarInst(struct, fConst596), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst615), LoadVarInst(struct, fRec191[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst617), LoadVarInst(struct, fRec191[Int32(1)]))))))
		StoreVarInst(struct, fRec190[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst596), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst598), LoadVarInst(struct, fRec191[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst618), LoadVarInst(struct, fRec191[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst618), LoadVarInst(struct, fRec191[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst593), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst619), LoadVarInst(struct, fRec190[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst620), LoadVarInst(struct, fRec190[Int32(1)]))))))
		StoreVarInst(struct, fRec189[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst593), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst595), LoadVarInst(struct, fRec190[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst621), LoadVarInst(struct, fRec190[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst621), LoadVarInst(struct, fRec190[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst589), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst622), LoadVarInst(struct, fRec189[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst623), LoadVarInst(struct, fRec189[Int32(1)]))))))
		StoreVarInst(struct, fRec188[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec188[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst589), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst592), LoadVarInst(struct, fRec189[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst624), LoadVarInst(struct, fRec189[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst624), LoadVarInst(struct, fRec189[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph12, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec188[Int32(0)])))))))
		StoreVarInst(struct, fRec201[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp89), BinopInst("*", LoadVarInst(struct, fConst641), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst644), LoadVarInst(struct, fRec201[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst645), LoadVarInst(struct, fRec201[Int32(1)]))))))
		StoreVarInst(struct, fRec200[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst641), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst643), LoadVarInst(struct, fRec201[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst646), LoadVarInst(struct, fRec201[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst646), LoadVarInst(struct, fRec201[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst639), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst647), LoadVarInst(struct, fRec200[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst648), LoadVarInst(struct, fRec200[Int32(1)]))))))
		StoreVarInst(struct, fRec199[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst639), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst640), LoadVarInst(struct, fRec200[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst649), LoadVarInst(struct, fRec200[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst649), LoadVarInst(struct, fRec200[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst637), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst650), LoadVarInst(struct, fRec199[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst651), LoadVarInst(struct, fRec199[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp90, BinopInst("*", LoadVarInst(struct, fConst637), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst638), LoadVarInst(struct, fRec199[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst652), LoadVarInst(struct, fRec199[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst652), LoadVarInst(struct, fRec199[Int32(2)])))))
		StoreVarInst(struct, fRec198[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp90), BinopInst("*", LoadVarInst(struct, fConst634), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst653), LoadVarInst(struct, fRec198[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst655), LoadVarInst(struct, fRec198[Int32(1)]))))))
		StoreVarInst(struct, fRec197[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst634), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst636), LoadVarInst(struct, fRec198[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst656), LoadVarInst(struct, fRec198[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst656), LoadVarInst(struct, fRec198[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst631), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst657), LoadVarInst(struct, fRec197[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst658), LoadVarInst(struct, fRec197[Int32(1)]))))))
		StoreVarInst(struct, fRec196[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst631), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst633), LoadVarInst(struct, fRec197[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst659), LoadVarInst(struct, fRec197[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst659), LoadVarInst(struct, fRec197[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst627), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst660), LoadVarInst(struct, fRec196[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst661), LoadVarInst(struct, fRec196[Int32(1)]))))))
		StoreVarInst(struct, fRec195[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec195[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst627), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst630), LoadVarInst(struct, fRec196[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst662), LoadVarInst(struct, fRec196[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst662), LoadVarInst(struct, fRec196[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph13, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec195[Int32(0)])))))))
		StoreVarInst(struct, fRec205[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp90), BinopInst("*", LoadVarInst(struct, fConst667), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst670), LoadVarInst(struct, fRec205[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst671), LoadVarInst(struct, fRec205[Int32(1)]))))))
		StoreVarInst(struct, fRec204[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst667), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst669), LoadVarInst(struct, fRec205[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst672), LoadVarInst(struct, fRec205[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst672), LoadVarInst(struct, fRec205[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst665), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst673), LoadVarInst(struct, fRec204[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst674), LoadVarInst(struct, fRec204[Int32(1)]))))))
		StoreVarInst(struct, fRec203[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst665), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst666), LoadVarInst(struct, fRec204[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst675), LoadVarInst(struct, fRec204[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst675), LoadVarInst(struct, fRec204[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst663), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst676), LoadVarInst(struct, fRec203[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst677), LoadVarInst(struct, fRec203[Int32(1)]))))))
		StoreVarInst(struct, fRec202[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec202[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst663), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst664), LoadVarInst(struct, fRec203[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst678), LoadVarInst(struct, fRec203[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst678), LoadVarInst(struct, fRec203[Int32(2)]))))))))
		StoreVarInst(struct, fVbargraph14, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec202[Int32(0)])))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp77)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp77)))
		ForLoopInst 
			DeclareVarInst(loop, "int", j0, Int32(3))
			BinopInst(">", LoadVarInst(loop, j0), Int32(0))
			StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
			BlockInst 
				StoreVarInst(struct, iVec0[LoadVarInst(loop, j0)], LoadVarInst(struct, iVec0[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
		StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
		StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
		StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
		StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
		StoreVarInst(struct, fVec8[Int32(1)], LoadVarInst(struct, fVec8[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fVec9[Int32(1)], LoadVarInst(struct, fVec9[Int32(0)]))
		StoreVarInst(struct, fVec10[Int32(1)], LoadVarInst(struct, fVec10[Int32(0)]))
		StoreVarInst(struct, fVec11[Int32(1)], LoadVarInst(struct, fVec11[Int32(0)]))
		StoreVarInst(struct, fVec12[Int32(1)], LoadVarInst(struct, fVec12[Int32(0)]))
		StoreVarInst(struct, fVec13[Int32(1)], LoadVarInst(struct, fVec13[Int32(0)]))
		StoreVarInst(struct, fVec14[Int32(1)], LoadVarInst(struct, fVec14[Int32(0)]))
		StoreVarInst(struct, fVec15[Int32(1)], LoadVarInst(struct, fVec15[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
		StoreVarInst(struct, fVec16[Int32(1)], LoadVarInst(struct, fVec16[Int32(0)]))
		StoreVarInst(struct, fVec17[Int32(1)], LoadVarInst(struct, fVec17[Int32(0)]))
		StoreVarInst(struct, fVec18[Int32(1)], LoadVarInst(struct, fVec18[Int32(0)]))
		StoreVarInst(struct, fVec19[Int32(1)], LoadVarInst(struct, fVec19[Int32(0)]))
		StoreVarInst(struct, fVec20[Int32(1)], LoadVarInst(struct, fVec20[Int32(0)]))
		StoreVarInst(struct, fVec21[Int32(1)], LoadVarInst(struct, fVec21[Int32(0)]))
		StoreVarInst(struct, iRec34[Int32(1)], LoadVarInst(struct, iRec34[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j1, Int32(3))
			BinopInst(">", LoadVarInst(loop, j1), Int32(0))
			StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec35[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec35[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec22[Int32(1)], LoadVarInst(struct, fVec22[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(2)], LoadVarInst(struct, fRec27[Int32(1)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fVec23[Int32(1)], LoadVarInst(struct, fVec23[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(2)], LoadVarInst(struct, fRec24[Int32(1)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(2)], LoadVarInst(struct, fRec23[Int32(1)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fVec24[Int32(1)], LoadVarInst(struct, fVec24[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(2)], LoadVarInst(struct, fRec21[Int32(1)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fVec25[Int32(1)], LoadVarInst(struct, fVec25[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(2)], LoadVarInst(struct, fRec18[Int32(1)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fVec26[Int32(1)], LoadVarInst(struct, fVec26[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fVec27[Int32(1)], LoadVarInst(struct, fVec27[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fVec28[Int32(1)], LoadVarInst(struct, fVec28[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fVec29[Int32(1)], LoadVarInst(struct, fVec29[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
		StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
		StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
		StoreVarInst(struct, fRec40[Int32(2)], LoadVarInst(struct, fRec40[Int32(1)]))
		StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
		StoreVarInst(struct, fVec30[Int32(1)], LoadVarInst(struct, fVec30[Int32(0)]))
		StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
		StoreVarInst(struct, fRec38[Int32(2)], LoadVarInst(struct, fRec38[Int32(1)]))
		StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
		StoreVarInst(struct, fRec37[Int32(2)], LoadVarInst(struct, fRec37[Int32(1)]))
		StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
		StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
		StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
		StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
		StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
		StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
		StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
		StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
		StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
		StoreVarInst(struct, fRec57[Int32(2)], LoadVarInst(struct, fRec57[Int32(1)]))
		StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
		StoreVarInst(struct, fRec56[Int32(2)], LoadVarInst(struct, fRec56[Int32(1)]))
		StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
		StoreVarInst(struct, fRec55[Int32(2)], LoadVarInst(struct, fRec55[Int32(1)]))
		StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
		StoreVarInst(struct, fRec54[Int32(2)], LoadVarInst(struct, fRec54[Int32(1)]))
		StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
		StoreVarInst(struct, fRec53[Int32(2)], LoadVarInst(struct, fRec53[Int32(1)]))
		StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
		StoreVarInst(struct, fRec52[Int32(2)], LoadVarInst(struct, fRec52[Int32(1)]))
		StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
		StoreVarInst(struct, fRec51[Int32(2)], LoadVarInst(struct, fRec51[Int32(1)]))
		StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
		StoreVarInst(struct, fRec50[Int32(2)], LoadVarInst(struct, fRec50[Int32(1)]))
		StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
		StoreVarInst(struct, fRec49[Int32(2)], LoadVarInst(struct, fRec49[Int32(1)]))
		StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
		StoreVarInst(struct, fRec48[Int32(2)], LoadVarInst(struct, fRec48[Int32(1)]))
		StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
		StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
		StoreVarInst(struct, fRec69[Int32(1)], LoadVarInst(struct, fRec69[Int32(0)]))
		StoreVarInst(struct, fRec68[Int32(2)], LoadVarInst(struct, fRec68[Int32(1)]))
		StoreVarInst(struct, fRec68[Int32(1)], LoadVarInst(struct, fRec68[Int32(0)]))
		StoreVarInst(struct, fRec67[Int32(2)], LoadVarInst(struct, fRec67[Int32(1)]))
		StoreVarInst(struct, fRec67[Int32(1)], LoadVarInst(struct, fRec67[Int32(0)]))
		StoreVarInst(struct, fRec66[Int32(2)], LoadVarInst(struct, fRec66[Int32(1)]))
		StoreVarInst(struct, fRec66[Int32(1)], LoadVarInst(struct, fRec66[Int32(0)]))
		StoreVarInst(struct, fRec65[Int32(2)], LoadVarInst(struct, fRec65[Int32(1)]))
		StoreVarInst(struct, fRec65[Int32(1)], LoadVarInst(struct, fRec65[Int32(0)]))
		StoreVarInst(struct, fRec64[Int32(2)], LoadVarInst(struct, fRec64[Int32(1)]))
		StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
		StoreVarInst(struct, fRec63[Int32(2)], LoadVarInst(struct, fRec63[Int32(1)]))
		StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
		StoreVarInst(struct, fRec62[Int32(2)], LoadVarInst(struct, fRec62[Int32(1)]))
		StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
		StoreVarInst(struct, fRec61[Int32(2)], LoadVarInst(struct, fRec61[Int32(1)]))
		StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
		StoreVarInst(struct, fRec60[Int32(2)], LoadVarInst(struct, fRec60[Int32(1)]))
		StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
		StoreVarInst(struct, fRec70[Int32(1)], LoadVarInst(struct, fRec70[Int32(0)]))
		StoreVarInst(struct, fRec79[Int32(1)], LoadVarInst(struct, fRec79[Int32(0)]))
		StoreVarInst(struct, fRec78[Int32(2)], LoadVarInst(struct, fRec78[Int32(1)]))
		StoreVarInst(struct, fRec78[Int32(1)], LoadVarInst(struct, fRec78[Int32(0)]))
		StoreVarInst(struct, fRec77[Int32(2)], LoadVarInst(struct, fRec77[Int32(1)]))
		StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
		StoreVarInst(struct, fRec76[Int32(2)], LoadVarInst(struct, fRec76[Int32(1)]))
		StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
		StoreVarInst(struct, fRec75[Int32(2)], LoadVarInst(struct, fRec75[Int32(1)]))
		StoreVarInst(struct, fRec75[Int32(1)], LoadVarInst(struct, fRec75[Int32(0)]))
		StoreVarInst(struct, fRec74[Int32(2)], LoadVarInst(struct, fRec74[Int32(1)]))
		StoreVarInst(struct, fRec74[Int32(1)], LoadVarInst(struct, fRec74[Int32(0)]))
		StoreVarInst(struct, fRec73[Int32(2)], LoadVarInst(struct, fRec73[Int32(1)]))
		StoreVarInst(struct, fRec73[Int32(1)], LoadVarInst(struct, fRec73[Int32(0)]))
		StoreVarInst(struct, fRec72[Int32(2)], LoadVarInst(struct, fRec72[Int32(1)]))
		StoreVarInst(struct, fRec72[Int32(1)], LoadVarInst(struct, fRec72[Int32(0)]))
		StoreVarInst(struct, fRec71[Int32(2)], LoadVarInst(struct, fRec71[Int32(1)]))
		StoreVarInst(struct, fRec71[Int32(1)], LoadVarInst(struct, fRec71[Int32(0)]))
		StoreVarInst(struct, fRec80[Int32(1)], LoadVarInst(struct, fRec80[Int32(0)]))
		StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
		StoreVarInst(struct, fRec87[Int32(2)], LoadVarInst(struct, fRec87[Int32(1)]))
		StoreVarInst(struct, fRec87[Int32(1)], LoadVarInst(struct, fRec87[Int32(0)]))
		StoreVarInst(struct, fRec86[Int32(2)], LoadVarInst(struct, fRec86[Int32(1)]))
		StoreVarInst(struct, fRec86[Int32(1)], LoadVarInst(struct, fRec86[Int32(0)]))
		StoreVarInst(struct, fRec85[Int32(2)], LoadVarInst(struct, fRec85[Int32(1)]))
		StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
		StoreVarInst(struct, fRec84[Int32(2)], LoadVarInst(struct, fRec84[Int32(1)]))
		StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
		StoreVarInst(struct, fRec83[Int32(2)], LoadVarInst(struct, fRec83[Int32(1)]))
		StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
		StoreVarInst(struct, fRec82[Int32(2)], LoadVarInst(struct, fRec82[Int32(1)]))
		StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
		StoreVarInst(struct, fRec81[Int32(2)], LoadVarInst(struct, fRec81[Int32(1)]))
		StoreVarInst(struct, fRec81[Int32(1)], LoadVarInst(struct, fRec81[Int32(0)]))
		StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
		StoreVarInst(struct, fRec96[Int32(1)], LoadVarInst(struct, fRec96[Int32(0)]))
		StoreVarInst(struct, fRec95[Int32(2)], LoadVarInst(struct, fRec95[Int32(1)]))
		StoreVarInst(struct, fRec95[Int32(1)], LoadVarInst(struct, fRec95[Int32(0)]))
		StoreVarInst(struct, fRec94[Int32(2)], LoadVarInst(struct, fRec94[Int32(1)]))
		StoreVarInst(struct, fRec94[Int32(1)], LoadVarInst(struct, fRec94[Int32(0)]))
		StoreVarInst(struct, fRec93[Int32(2)], LoadVarInst(struct, fRec93[Int32(1)]))
		StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
		StoreVarInst(struct, fRec92[Int32(2)], LoadVarInst(struct, fRec92[Int32(1)]))
		StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
		StoreVarInst(struct, fRec91[Int32(2)], LoadVarInst(struct, fRec91[Int32(1)]))
		StoreVarInst(struct, fRec91[Int32(1)], LoadVarInst(struct, fRec91[Int32(0)]))
		StoreVarInst(struct, fRec90[Int32(2)], LoadVarInst(struct, fRec90[Int32(1)]))
		StoreVarInst(struct, fRec90[Int32(1)], LoadVarInst(struct, fRec90[Int32(0)]))
		StoreVarInst(struct, fRec97[Int32(1)], LoadVarInst(struct, fRec97[Int32(0)]))
		StoreVarInst(struct, fRec103[Int32(1)], LoadVarInst(struct, fRec103[Int32(0)]))
		StoreVarInst(struct, fRec102[Int32(2)], LoadVarInst(struct, fRec102[Int32(1)]))
		StoreVarInst(struct, fRec102[Int32(1)], LoadVarInst(struct, fRec102[Int32(0)]))
		StoreVarInst(struct, fRec101[Int32(2)], LoadVarInst(struct, fRec101[Int32(1)]))
		StoreVarInst(struct, fRec101[Int32(1)], LoadVarInst(struct, fRec101[Int32(0)]))
		StoreVarInst(struct, fRec100[Int32(2)], LoadVarInst(struct, fRec100[Int32(1)]))
		StoreVarInst(struct, fRec100[Int32(1)], LoadVarInst(struct, fRec100[Int32(0)]))
		StoreVarInst(struct, fRec99[Int32(2)], LoadVarInst(struct, fRec99[Int32(1)]))
		StoreVarInst(struct, fRec99[Int32(1)], LoadVarInst(struct, fRec99[Int32(0)]))
		StoreVarInst(struct, fRec98[Int32(2)], LoadVarInst(struct, fRec98[Int32(1)]))
		StoreVarInst(struct, fRec98[Int32(1)], LoadVarInst(struct, fRec98[Int32(0)]))
		StoreVarInst(struct, fRec104[Int32(1)], LoadVarInst(struct, fRec104[Int32(0)]))
		StoreVarInst(struct, fRec109[Int32(1)], LoadVarInst(struct, fRec109[Int32(0)]))
		StoreVarInst(struct, fRec108[Int32(2)], LoadVarInst(struct, fRec108[Int32(1)]))
		StoreVarInst(struct, fRec108[Int32(1)], LoadVarInst(struct, fRec108[Int32(0)]))
		StoreVarInst(struct, fRec107[Int32(2)], LoadVarInst(struct, fRec107[Int32(1)]))
		StoreVarInst(struct, fRec107[Int32(1)], LoadVarInst(struct, fRec107[Int32(0)]))
		StoreVarInst(struct, fRec106[Int32(2)], LoadVarInst(struct, fRec106[Int32(1)]))
		StoreVarInst(struct, fRec106[Int32(1)], LoadVarInst(struct, fRec106[Int32(0)]))
		StoreVarInst(struct, fRec105[Int32(2)], LoadVarInst(struct, fRec105[Int32(1)]))
		StoreVarInst(struct, fRec105[Int32(1)], LoadVarInst(struct, fRec105[Int32(0)]))
		StoreVarInst(struct, fRec110[Int32(1)], LoadVarInst(struct, fRec110[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec117[Int32(2)], LoadVarInst(struct, fRec117[Int32(1)]))
		StoreVarInst(struct, fRec117[Int32(1)], LoadVarInst(struct, fRec117[Int32(0)]))
		StoreVarInst(struct, fRec116[Int32(2)], LoadVarInst(struct, fRec116[Int32(1)]))
		StoreVarInst(struct, fRec116[Int32(1)], LoadVarInst(struct, fRec116[Int32(0)]))
		StoreVarInst(struct, fRec115[Int32(2)], LoadVarInst(struct, fRec115[Int32(1)]))
		StoreVarInst(struct, fRec115[Int32(1)], LoadVarInst(struct, fRec115[Int32(0)]))
		StoreVarInst(struct, fRec114[Int32(2)], LoadVarInst(struct, fRec114[Int32(1)]))
		StoreVarInst(struct, fRec114[Int32(1)], LoadVarInst(struct, fRec114[Int32(0)]))
		StoreVarInst(struct, fRec113[Int32(2)], LoadVarInst(struct, fRec113[Int32(1)]))
		StoreVarInst(struct, fRec113[Int32(1)], LoadVarInst(struct, fRec113[Int32(0)]))
		StoreVarInst(struct, fRec112[Int32(2)], LoadVarInst(struct, fRec112[Int32(1)]))
		StoreVarInst(struct, fRec112[Int32(1)], LoadVarInst(struct, fRec112[Int32(0)]))
		StoreVarInst(struct, fRec111[Int32(1)], LoadVarInst(struct, fRec111[Int32(0)]))
		StoreVarInst(struct, fRec124[Int32(2)], LoadVarInst(struct, fRec124[Int32(1)]))
		StoreVarInst(struct, fRec124[Int32(1)], LoadVarInst(struct, fRec124[Int32(0)]))
		StoreVarInst(struct, fRec123[Int32(2)], LoadVarInst(struct, fRec123[Int32(1)]))
		StoreVarInst(struct, fRec123[Int32(1)], LoadVarInst(struct, fRec123[Int32(0)]))
		StoreVarInst(struct, fRec122[Int32(2)], LoadVarInst(struct, fRec122[Int32(1)]))
		StoreVarInst(struct, fRec122[Int32(1)], LoadVarInst(struct, fRec122[Int32(0)]))
		StoreVarInst(struct, fRec121[Int32(2)], LoadVarInst(struct, fRec121[Int32(1)]))
		StoreVarInst(struct, fRec121[Int32(1)], LoadVarInst(struct, fRec121[Int32(0)]))
		StoreVarInst(struct, fRec120[Int32(2)], LoadVarInst(struct, fRec120[Int32(1)]))
		StoreVarInst(struct, fRec120[Int32(1)], LoadVarInst(struct, fRec120[Int32(0)]))
		StoreVarInst(struct, fRec119[Int32(2)], LoadVarInst(struct, fRec119[Int32(1)]))
		StoreVarInst(struct, fRec119[Int32(1)], LoadVarInst(struct, fRec119[Int32(0)]))
		StoreVarInst(struct, fRec118[Int32(1)], LoadVarInst(struct, fRec118[Int32(0)]))
		StoreVarInst(struct, fRec131[Int32(2)], LoadVarInst(struct, fRec131[Int32(1)]))
		StoreVarInst(struct, fRec131[Int32(1)], LoadVarInst(struct, fRec131[Int32(0)]))
		StoreVarInst(struct, fRec130[Int32(2)], LoadVarInst(struct, fRec130[Int32(1)]))
		StoreVarInst(struct, fRec130[Int32(1)], LoadVarInst(struct, fRec130[Int32(0)]))
		StoreVarInst(struct, fRec129[Int32(2)], LoadVarInst(struct, fRec129[Int32(1)]))
		StoreVarInst(struct, fRec129[Int32(1)], LoadVarInst(struct, fRec129[Int32(0)]))
		StoreVarInst(struct, fRec128[Int32(2)], LoadVarInst(struct, fRec128[Int32(1)]))
		StoreVarInst(struct, fRec128[Int32(1)], LoadVarInst(struct, fRec128[Int32(0)]))
		StoreVarInst(struct, fRec127[Int32(2)], LoadVarInst(struct, fRec127[Int32(1)]))
		StoreVarInst(struct, fRec127[Int32(1)], LoadVarInst(struct, fRec127[Int32(0)]))
		StoreVarInst(struct, fRec126[Int32(2)], LoadVarInst(struct, fRec126[Int32(1)]))
		StoreVarInst(struct, fRec126[Int32(1)], LoadVarInst(struct, fRec126[Int32(0)]))
		StoreVarInst(struct, fRec125[Int32(1)], LoadVarInst(struct, fRec125[Int32(0)]))
		StoreVarInst(struct, fRec138[Int32(2)], LoadVarInst(struct, fRec138[Int32(1)]))
		StoreVarInst(struct, fRec138[Int32(1)], LoadVarInst(struct, fRec138[Int32(0)]))
		StoreVarInst(struct, fRec137[Int32(2)], LoadVarInst(struct, fRec137[Int32(1)]))
		StoreVarInst(struct, fRec137[Int32(1)], LoadVarInst(struct, fRec137[Int32(0)]))
		StoreVarInst(struct, fRec136[Int32(2)], LoadVarInst(struct, fRec136[Int32(1)]))
		StoreVarInst(struct, fRec136[Int32(1)], LoadVarInst(struct, fRec136[Int32(0)]))
		StoreVarInst(struct, fRec135[Int32(2)], LoadVarInst(struct, fRec135[Int32(1)]))
		StoreVarInst(struct, fRec135[Int32(1)], LoadVarInst(struct, fRec135[Int32(0)]))
		StoreVarInst(struct, fRec134[Int32(2)], LoadVarInst(struct, fRec134[Int32(1)]))
		StoreVarInst(struct, fRec134[Int32(1)], LoadVarInst(struct, fRec134[Int32(0)]))
		StoreVarInst(struct, fRec133[Int32(2)], LoadVarInst(struct, fRec133[Int32(1)]))
		StoreVarInst(struct, fRec133[Int32(1)], LoadVarInst(struct, fRec133[Int32(0)]))
		StoreVarInst(struct, fRec132[Int32(1)], LoadVarInst(struct, fRec132[Int32(0)]))
		StoreVarInst(struct, fRec145[Int32(2)], LoadVarInst(struct, fRec145[Int32(1)]))
		StoreVarInst(struct, fRec145[Int32(1)], LoadVarInst(struct, fRec145[Int32(0)]))
		StoreVarInst(struct, fRec144[Int32(2)], LoadVarInst(struct, fRec144[Int32(1)]))
		StoreVarInst(struct, fRec144[Int32(1)], LoadVarInst(struct, fRec144[Int32(0)]))
		StoreVarInst(struct, fRec143[Int32(2)], LoadVarInst(struct, fRec143[Int32(1)]))
		StoreVarInst(struct, fRec143[Int32(1)], LoadVarInst(struct, fRec143[Int32(0)]))
		StoreVarInst(struct, fRec142[Int32(2)], LoadVarInst(struct, fRec142[Int32(1)]))
		StoreVarInst(struct, fRec142[Int32(1)], LoadVarInst(struct, fRec142[Int32(0)]))
		StoreVarInst(struct, fRec141[Int32(2)], LoadVarInst(struct, fRec141[Int32(1)]))
		StoreVarInst(struct, fRec141[Int32(1)], LoadVarInst(struct, fRec141[Int32(0)]))
		StoreVarInst(struct, fRec140[Int32(2)], LoadVarInst(struct, fRec140[Int32(1)]))
		StoreVarInst(struct, fRec140[Int32(1)], LoadVarInst(struct, fRec140[Int32(0)]))
		StoreVarInst(struct, fRec139[Int32(1)], LoadVarInst(struct, fRec139[Int32(0)]))
		StoreVarInst(struct, fRec152[Int32(2)], LoadVarInst(struct, fRec152[Int32(1)]))
		StoreVarInst(struct, fRec152[Int32(1)], LoadVarInst(struct, fRec152[Int32(0)]))
		StoreVarInst(struct, fRec151[Int32(2)], LoadVarInst(struct, fRec151[Int32(1)]))
		StoreVarInst(struct, fRec151[Int32(1)], LoadVarInst(struct, fRec151[Int32(0)]))
		StoreVarInst(struct, fRec150[Int32(2)], LoadVarInst(struct, fRec150[Int32(1)]))
		StoreVarInst(struct, fRec150[Int32(1)], LoadVarInst(struct, fRec150[Int32(0)]))
		StoreVarInst(struct, fRec149[Int32(2)], LoadVarInst(struct, fRec149[Int32(1)]))
		StoreVarInst(struct, fRec149[Int32(1)], LoadVarInst(struct, fRec149[Int32(0)]))
		StoreVarInst(struct, fRec148[Int32(2)], LoadVarInst(struct, fRec148[Int32(1)]))
		StoreVarInst(struct, fRec148[Int32(1)], LoadVarInst(struct, fRec148[Int32(0)]))
		StoreVarInst(struct, fRec147[Int32(2)], LoadVarInst(struct, fRec147[Int32(1)]))
		StoreVarInst(struct, fRec147[Int32(1)], LoadVarInst(struct, fRec147[Int32(0)]))
		StoreVarInst(struct, fRec146[Int32(1)], LoadVarInst(struct, fRec146[Int32(0)]))
		StoreVarInst(struct, fRec159[Int32(2)], LoadVarInst(struct, fRec159[Int32(1)]))
		StoreVarInst(struct, fRec159[Int32(1)], LoadVarInst(struct, fRec159[Int32(0)]))
		StoreVarInst(struct, fRec158[Int32(2)], LoadVarInst(struct, fRec158[Int32(1)]))
		StoreVarInst(struct, fRec158[Int32(1)], LoadVarInst(struct, fRec158[Int32(0)]))
		StoreVarInst(struct, fRec157[Int32(2)], LoadVarInst(struct, fRec157[Int32(1)]))
		StoreVarInst(struct, fRec157[Int32(1)], LoadVarInst(struct, fRec157[Int32(0)]))
		StoreVarInst(struct, fRec156[Int32(2)], LoadVarInst(struct, fRec156[Int32(1)]))
		StoreVarInst(struct, fRec156[Int32(1)], LoadVarInst(struct, fRec156[Int32(0)]))
		StoreVarInst(struct, fRec155[Int32(2)], LoadVarInst(struct, fRec155[Int32(1)]))
		StoreVarInst(struct, fRec155[Int32(1)], LoadVarInst(struct, fRec155[Int32(0)]))
		StoreVarInst(struct, fRec154[Int32(2)], LoadVarInst(struct, fRec154[Int32(1)]))
		StoreVarInst(struct, fRec154[Int32(1)], LoadVarInst(struct, fRec154[Int32(0)]))
		StoreVarInst(struct, fRec153[Int32(1)], LoadVarInst(struct, fRec153[Int32(0)]))
		StoreVarInst(struct, fRec166[Int32(2)], LoadVarInst(struct, fRec166[Int32(1)]))
		StoreVarInst(struct, fRec166[Int32(1)], LoadVarInst(struct, fRec166[Int32(0)]))
		StoreVarInst(struct, fRec165[Int32(2)], LoadVarInst(struct, fRec165[Int32(1)]))
		StoreVarInst(struct, fRec165[Int32(1)], LoadVarInst(struct, fRec165[Int32(0)]))
		StoreVarInst(struct, fRec164[Int32(2)], LoadVarInst(struct, fRec164[Int32(1)]))
		StoreVarInst(struct, fRec164[Int32(1)], LoadVarInst(struct, fRec164[Int32(0)]))
		StoreVarInst(struct, fRec163[Int32(2)], LoadVarInst(struct, fRec163[Int32(1)]))
		StoreVarInst(struct, fRec163[Int32(1)], LoadVarInst(struct, fRec163[Int32(0)]))
		StoreVarInst(struct, fRec162[Int32(2)], LoadVarInst(struct, fRec162[Int32(1)]))
		StoreVarInst(struct, fRec162[Int32(1)], LoadVarInst(struct, fRec162[Int32(0)]))
		StoreVarInst(struct, fRec161[Int32(2)], LoadVarInst(struct, fRec161[Int32(1)]))
		StoreVarInst(struct, fRec161[Int32(1)], LoadVarInst(struct, fRec161[Int32(0)]))
		StoreVarInst(struct, fRec160[Int32(1)], LoadVarInst(struct, fRec160[Int32(0)]))
		StoreVarInst(struct, fRec173[Int32(2)], LoadVarInst(struct, fRec173[Int32(1)]))
		StoreVarInst(struct, fRec173[Int32(1)], LoadVarInst(struct, fRec173[Int32(0)]))
		StoreVarInst(struct, fRec172[Int32(2)], LoadVarInst(struct, fRec172[Int32(1)]))
		StoreVarInst(struct, fRec172[Int32(1)], LoadVarInst(struct, fRec172[Int32(0)]))
		StoreVarInst(struct, fRec171[Int32(2)], LoadVarInst(struct, fRec171[Int32(1)]))
		StoreVarInst(struct, fRec171[Int32(1)], LoadVarInst(struct, fRec171[Int32(0)]))
		StoreVarInst(struct, fRec170[Int32(2)], LoadVarInst(struct, fRec170[Int32(1)]))
		StoreVarInst(struct, fRec170[Int32(1)], LoadVarInst(struct, fRec170[Int32(0)]))
		StoreVarInst(struct, fRec169[Int32(2)], LoadVarInst(struct, fRec169[Int32(1)]))
		StoreVarInst(struct, fRec169[Int32(1)], LoadVarInst(struct, fRec169[Int32(0)]))
		StoreVarInst(struct, fRec168[Int32(2)], LoadVarInst(struct, fRec168[Int32(1)]))
		StoreVarInst(struct, fRec168[Int32(1)], LoadVarInst(struct, fRec168[Int32(0)]))
		StoreVarInst(struct, fRec167[Int32(1)], LoadVarInst(struct, fRec167[Int32(0)]))
		StoreVarInst(struct, fRec180[Int32(2)], LoadVarInst(struct, fRec180[Int32(1)]))
		StoreVarInst(struct, fRec180[Int32(1)], LoadVarInst(struct, fRec180[Int32(0)]))
		StoreVarInst(struct, fRec179[Int32(2)], LoadVarInst(struct, fRec179[Int32(1)]))
		StoreVarInst(struct, fRec179[Int32(1)], LoadVarInst(struct, fRec179[Int32(0)]))
		StoreVarInst(struct, fRec178[Int32(2)], LoadVarInst(struct, fRec178[Int32(1)]))
		StoreVarInst(struct, fRec178[Int32(1)], LoadVarInst(struct, fRec178[Int32(0)]))
		StoreVarInst(struct, fRec177[Int32(2)], LoadVarInst(struct, fRec177[Int32(1)]))
		StoreVarInst(struct, fRec177[Int32(1)], LoadVarInst(struct, fRec177[Int32(0)]))
		StoreVarInst(struct, fRec176[Int32(2)], LoadVarInst(struct, fRec176[Int32(1)]))
		StoreVarInst(struct, fRec176[Int32(1)], LoadVarInst(struct, fRec176[Int32(0)]))
		StoreVarInst(struct, fRec175[Int32(2)], LoadVarInst(struct, fRec175[Int32(1)]))
		StoreVarInst(struct, fRec175[Int32(1)], LoadVarInst(struct, fRec175[Int32(0)]))
		StoreVarInst(struct, fRec174[Int32(1)], LoadVarInst(struct, fRec174[Int32(0)]))
		StoreVarInst(struct, fRec187[Int32(2)], LoadVarInst(struct, fRec187[Int32(1)]))
		StoreVarInst(struct, fRec187[Int32(1)], LoadVarInst(struct, fRec187[Int32(0)]))
		StoreVarInst(struct, fRec186[Int32(2)], LoadVarInst(struct, fRec186[Int32(1)]))
		StoreVarInst(struct, fRec186[Int32(1)], LoadVarInst(struct, fRec186[Int32(0)]))
		StoreVarInst(struct, fRec185[Int32(2)], LoadVarInst(struct, fRec185[Int32(1)]))
		StoreVarInst(struct, fRec185[Int32(1)], LoadVarInst(struct, fRec185[Int32(0)]))
		StoreVarInst(struct, fRec184[Int32(2)], LoadVarInst(struct, fRec184[Int32(1)]))
		StoreVarInst(struct, fRec184[Int32(1)], LoadVarInst(struct, fRec184[Int32(0)]))
		StoreVarInst(struct, fRec183[Int32(2)], LoadVarInst(struct, fRec183[Int32(1)]))
		StoreVarInst(struct, fRec183[Int32(1)], LoadVarInst(struct, fRec183[Int32(0)]))
		StoreVarInst(struct, fRec182[Int32(2)], LoadVarInst(struct, fRec182[Int32(1)]))
		StoreVarInst(struct, fRec182[Int32(1)], LoadVarInst(struct, fRec182[Int32(0)]))
		StoreVarInst(struct, fRec181[Int32(1)], LoadVarInst(struct, fRec181[Int32(0)]))
		StoreVarInst(struct, fRec194[Int32(2)], LoadVarInst(struct, fRec194[Int32(1)]))
		StoreVarInst(struct, fRec194[Int32(1)], LoadVarInst(struct, fRec194[Int32(0)]))
		StoreVarInst(struct, fRec193[Int32(2)], LoadVarInst(struct, fRec193[Int32(1)]))
		StoreVarInst(struct, fRec193[Int32(1)], LoadVarInst(struct, fRec193[Int32(0)]))
		StoreVarInst(struct, fRec192[Int32(2)], LoadVarInst(struct, fRec192[Int32(1)]))
		StoreVarInst(struct, fRec192[Int32(1)], LoadVarInst(struct, fRec192[Int32(0)]))
		StoreVarInst(struct, fRec191[Int32(2)], LoadVarInst(struct, fRec191[Int32(1)]))
		StoreVarInst(struct, fRec191[Int32(1)], LoadVarInst(struct, fRec191[Int32(0)]))
		StoreVarInst(struct, fRec190[Int32(2)], LoadVarInst(struct, fRec190[Int32(1)]))
		StoreVarInst(struct, fRec190[Int32(1)], LoadVarInst(struct, fRec190[Int32(0)]))
		StoreVarInst(struct, fRec189[Int32(2)], LoadVarInst(struct, fRec189[Int32(1)]))
		StoreVarInst(struct, fRec189[Int32(1)], LoadVarInst(struct, fRec189[Int32(0)]))
		StoreVarInst(struct, fRec188[Int32(1)], LoadVarInst(struct, fRec188[Int32(0)]))
		StoreVarInst(struct, fRec201[Int32(2)], LoadVarInst(struct, fRec201[Int32(1)]))
		StoreVarInst(struct, fRec201[Int32(1)], LoadVarInst(struct, fRec201[Int32(0)]))
		StoreVarInst(struct, fRec200[Int32(2)], LoadVarInst(struct, fRec200[Int32(1)]))
		StoreVarInst(struct, fRec200[Int32(1)], LoadVarInst(struct, fRec200[Int32(0)]))
		StoreVarInst(struct, fRec199[Int32(2)], LoadVarInst(struct, fRec199[Int32(1)]))
		StoreVarInst(struct, fRec199[Int32(1)], LoadVarInst(struct, fRec199[Int32(0)]))
		StoreVarInst(struct, fRec198[Int32(2)], LoadVarInst(struct, fRec198[Int32(1)]))
		StoreVarInst(struct, fRec198[Int32(1)], LoadVarInst(struct, fRec198[Int32(0)]))
		StoreVarInst(struct, fRec197[Int32(2)], LoadVarInst(struct, fRec197[Int32(1)]))
		StoreVarInst(struct, fRec197[Int32(1)], LoadVarInst(struct, fRec197[Int32(0)]))
		StoreVarInst(struct, fRec196[Int32(2)], LoadVarInst(struct, fRec196[Int32(1)]))
		StoreVarInst(struct, fRec196[Int32(1)], LoadVarInst(struct, fRec196[Int32(0)]))
		StoreVarInst(struct, fRec195[Int32(1)], LoadVarInst(struct, fRec195[Int32(0)]))
		StoreVarInst(struct, fRec205[Int32(2)], LoadVarInst(struct, fRec205[Int32(1)]))
		StoreVarInst(struct, fRec205[Int32(1)], LoadVarInst(struct, fRec205[Int32(0)]))
		StoreVarInst(struct, fRec204[Int32(2)], LoadVarInst(struct, fRec204[Int32(1)]))
		StoreVarInst(struct, fRec204[Int32(1)], LoadVarInst(struct, fRec204[Int32(0)]))
		StoreVarInst(struct, fRec203[Int32(2)], LoadVarInst(struct, fRec203[Int32(1)]))
		StoreVarInst(struct, fRec203[Int32(1)], LoadVarInst(struct, fRec203[Int32(0)]))
		StoreVarInst(struct, fRec202[Int32(1)], LoadVarInst(struct, fRec202[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[4])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, "float", fConst12)
	DeclareVarInst(struct, "float", fConst13)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "float", fConst14)
	DeclareVarInst(struct, "float", fConst15)
	DeclareVarInst(struct, "float", fConst16)
	DeclareVarInst(struct, "float", fConst17)
	DeclareVarInst(struct, "float", fConst18)
	DeclareVarInst(struct, "float", fConst19)
	DeclareVarInst(struct, "float", fConst20)
	DeclareVarInst(struct, "float", fConst21)
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "float", fConst23)
	DeclareVarInst(struct, "float", fConst24)
	DeclareVarInst(struct, "float", fConst25)
	DeclareVarInst(struct, "float", fConst26)
	DeclareVarInst(struct, "float", fConst27)
	DeclareVarInst(struct, "float", fConst28)
	DeclareVarInst(struct, "float", fConst29)
	DeclareVarInst(struct, "float", fConst30)
	DeclareVarInst(struct, "float", fConst31)
	DeclareVarInst(struct, "float", fConst32)
	DeclareVarInst(struct, "float", fConst33)
	DeclareVarInst(struct, "float", fConst34)
	DeclareVarInst(struct, "float", fConst35)
	DeclareVarInst(struct, "float", fConst36)
	DeclareVarInst(struct, "float", fConst37)
	DeclareVarInst(struct, "float", fConst38)
	DeclareVarInst(struct, "float", fConst39)
	DeclareVarInst(struct, "float", fConst40)
	DeclareVarInst(struct, "float", fConst41)
	DeclareVarInst(struct, "float", fConst42)
	DeclareVarInst(struct, "float", fConst43)
	DeclareVarInst(struct, "float", fConst44)
	DeclareVarInst(struct, "float", fConst45)
	DeclareVarInst(struct, "float", fConst46)
	DeclareVarInst(struct, "float", fConst47)
	DeclareVarInst(struct, "float", fConst48)
	DeclareVarInst(struct, "float", fConst49)
	DeclareVarInst(struct, "float", fConst50)
	DeclareVarInst(struct, "float", fConst51)
	DeclareVarInst(struct, "float", fConst52)
	DeclareVarInst(struct, "float", fConst53)
	DeclareVarInst(struct, "float", fConst54)
	DeclareVarInst(struct, "float", fConst55)
	DeclareVarInst(struct, "float", fConst56)
	DeclareVarInst(struct, "float", fConst57)
	DeclareVarInst(struct, "float", fConst58)
	DeclareVarInst(struct, "float", fConst59)
	DeclareVarInst(struct, "float", fConst60)
	DeclareVarInst(struct, "float", fConst61)
	DeclareVarInst(struct, "float", fConst62)
	DeclareVarInst(struct, "float", fConst63)
	DeclareVarInst(struct, "float", fConst64)
	DeclareVarInst(struct, "float", fConst65)
	DeclareVarInst(struct, "float", fConst66)
	DeclareVarInst(struct, "float", fConst67)
	DeclareVarInst(struct, "float", fConst68)
	DeclareVarInst(struct, "float", fConst69)
	DeclareVarInst(struct, "float", fConst70)
	DeclareVarInst(struct, "float", fConst71)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "float", fConst72)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, "float", fConst73)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "float", fConst74)
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, "float", fConst75)
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fVec8[2])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec9[2])
	DeclareVarInst(struct, float, fVec10[2])
	DeclareVarInst(struct, float, fVec11[2])
	DeclareVarInst(struct, float, fVec12[2])
	DeclareVarInst(struct, float, fVec13[2])
	DeclareVarInst(struct, float, fVec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fVec15[2])
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, float, fVec16[2])
	DeclareVarInst(struct, float, fVec17[2])
	DeclareVarInst(struct, float, fVec18[2])
	DeclareVarInst(struct, float, fVec19[2])
	DeclareVarInst(struct, float, fVec20[2])
	DeclareVarInst(struct, float, fVec21[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox3)
	DeclareVarInst(struct, int, iRec34[2])
	DeclareVarInst(struct, float, fRec35[4])
	DeclareVarInst(struct, float, fVec22[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "float", fConst76)
	DeclareVarInst(struct, "float", fConst77)
	DeclareVarInst(struct, "float", fConst78)
	DeclareVarInst(struct, float, fRec27[3])
	DeclareVarInst(struct, "float", fConst79)
	DeclareVarInst(struct, "float", fConst80)
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, float, fVec23[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst81)
	DeclareVarInst(struct, "float", fConst82)
	DeclareVarInst(struct, "float", fConst83)
	DeclareVarInst(struct, float, fRec24[3])
	DeclareVarInst(struct, "float", fConst84)
	DeclareVarInst(struct, "float", fConst85)
	DeclareVarInst(struct, float, fRec23[3])
	DeclareVarInst(struct, float, fVec24[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "float", fConst86)
	DeclareVarInst(struct, "float", fConst87)
	DeclareVarInst(struct, "float", fConst88)
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, "float", fConst89)
	DeclareVarInst(struct, "float", fConst90)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, float, fVec25[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "float", fConst91)
	DeclareVarInst(struct, "float", fConst92)
	DeclareVarInst(struct, "float", fConst93)
	DeclareVarInst(struct, float, fRec18[3])
	DeclareVarInst(struct, "float", fConst94)
	DeclareVarInst(struct, "float", fConst95)
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, float, fVec26[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "float", fConst96)
	DeclareVarInst(struct, "float", fConst97)
	DeclareVarInst(struct, "float", fConst98)
	DeclareVarInst(struct, float, fRec15[3])
	DeclareVarInst(struct, "float", fConst99)
	DeclareVarInst(struct, "float", fConst100)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, float, fVec27[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "float", fConst101)
	DeclareVarInst(struct, "float", fConst102)
	DeclareVarInst(struct, "float", fConst103)
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, "float", fConst104)
	DeclareVarInst(struct, "float", fConst105)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, float, fVec28[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "float", fConst106)
	DeclareVarInst(struct, "float", fConst107)
	DeclareVarInst(struct, "float", fConst108)
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, "float", fConst109)
	DeclareVarInst(struct, "float", fConst110)
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fVec29[2])
	DeclareVarInst(struct, "float", fConst111)
	DeclareVarInst(struct, "float", fConst112)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "float", fConst113)
	DeclareVarInst(struct, "float", fConst114)
	DeclareVarInst(struct, float, fRec6[3])
	DeclareVarInst(struct, "float", fConst115)
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst116)
	DeclareVarInst(struct, "float", fConst117)
	DeclareVarInst(struct, "float", fConst118)
	DeclareVarInst(struct, "float", fConst119)
	DeclareVarInst(struct, "float", fConst120)
	DeclareVarInst(struct, "float", fConst121)
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, "float", fConst122)
	DeclareVarInst(struct, "float", fConst123)
	DeclareVarInst(struct, "float", fConst124)
	DeclareVarInst(struct, "float", fConst125)
	DeclareVarInst(struct, "float", fConst126)
	DeclareVarInst(struct, "float", fConst127)
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, float, fRec41[3])
	DeclareVarInst(struct, float, fRec40[3])
	DeclareVarInst(struct, float, fVec30[2])
	DeclareVarInst(struct, "float", fConst128)
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, "float", fConst129)
	DeclareVarInst(struct, float, fRec38[3])
	DeclareVarInst(struct, "float", fConst130)
	DeclareVarInst(struct, float, fRec37[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, float, fRec45[3])
	DeclareVarInst(struct, float, fRec44[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, float, fRec47[2])
	DeclareVarInst(struct, "float", fConst131)
	DeclareVarInst(struct, "float", fConst132)
	DeclareVarInst(struct, float, fRec58[2])
	DeclareVarInst(struct, float, fRec57[3])
	DeclareVarInst(struct, float, fRec56[3])
	DeclareVarInst(struct, float, fRec55[3])
	DeclareVarInst(struct, "float", fConst133)
	DeclareVarInst(struct, "float", fConst134)
	DeclareVarInst(struct, float, fRec54[3])
	DeclareVarInst(struct, "float", fConst135)
	DeclareVarInst(struct, "float", fConst136)
	DeclareVarInst(struct, float, fRec53[3])
	DeclareVarInst(struct, "float", fConst137)
	DeclareVarInst(struct, "float", fConst138)
	DeclareVarInst(struct, float, fRec52[3])
	DeclareVarInst(struct, "float", fConst139)
	DeclareVarInst(struct, "float", fConst140)
	DeclareVarInst(struct, float, fRec51[3])
	DeclareVarInst(struct, "float", fConst141)
	DeclareVarInst(struct, "float", fConst142)
	DeclareVarInst(struct, float, fRec50[3])
	DeclareVarInst(struct, "float", fConst143)
	DeclareVarInst(struct, "float", fConst144)
	DeclareVarInst(struct, float, fRec49[3])
	DeclareVarInst(struct, "float", fConst145)
	DeclareVarInst(struct, "float", fConst146)
	DeclareVarInst(struct, float, fRec48[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec59[2])
	DeclareVarInst(struct, "float", fConst147)
	DeclareVarInst(struct, "float", fConst148)
	DeclareVarInst(struct, float, fRec69[2])
	DeclareVarInst(struct, float, fRec68[3])
	DeclareVarInst(struct, float, fRec67[3])
	DeclareVarInst(struct, float, fRec66[3])
	DeclareVarInst(struct, float, fRec65[3])
	DeclareVarInst(struct, float, fRec64[3])
	DeclareVarInst(struct, float, fRec63[3])
	DeclareVarInst(struct, float, fRec62[3])
	DeclareVarInst(struct, float, fRec61[3])
	DeclareVarInst(struct, float, fRec60[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, float, fRec70[2])
	DeclareVarInst(struct, "float", fConst149)
	DeclareVarInst(struct, "float", fConst150)
	DeclareVarInst(struct, float, fRec79[2])
	DeclareVarInst(struct, float, fRec78[3])
	DeclareVarInst(struct, float, fRec77[3])
	DeclareVarInst(struct, float, fRec76[3])
	DeclareVarInst(struct, float, fRec75[3])
	DeclareVarInst(struct, float, fRec74[3])
	DeclareVarInst(struct, float, fRec73[3])
	DeclareVarInst(struct, float, fRec72[3])
	DeclareVarInst(struct, float, fRec71[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider10)
	DeclareVarInst(struct, float, fRec80[2])
	DeclareVarInst(struct, "float", fConst151)
	DeclareVarInst(struct, "float", fConst152)
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, float, fRec87[3])
	DeclareVarInst(struct, float, fRec86[3])
	DeclareVarInst(struct, float, fRec85[3])
	DeclareVarInst(struct, float, fRec84[3])
	DeclareVarInst(struct, float, fRec83[3])
	DeclareVarInst(struct, float, fRec82[3])
	DeclareVarInst(struct, float, fRec81[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider11)
	DeclareVarInst(struct, float, fRec89[2])
	DeclareVarInst(struct, "float", fConst153)
	DeclareVarInst(struct, "float", fConst154)
	DeclareVarInst(struct, float, fRec96[2])
	DeclareVarInst(struct, float, fRec95[3])
	DeclareVarInst(struct, float, fRec94[3])
	DeclareVarInst(struct, float, fRec93[3])
	DeclareVarInst(struct, float, fRec92[3])
	DeclareVarInst(struct, float, fRec91[3])
	DeclareVarInst(struct, float, fRec90[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider12)
	DeclareVarInst(struct, float, fRec97[2])
	DeclareVarInst(struct, "float", fConst155)
	DeclareVarInst(struct, "float", fConst156)
	DeclareVarInst(struct, float, fRec103[2])
	DeclareVarInst(struct, float, fRec102[3])
	DeclareVarInst(struct, float, fRec101[3])
	DeclareVarInst(struct, float, fRec100[3])
	DeclareVarInst(struct, float, fRec99[3])
	DeclareVarInst(struct, float, fRec98[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider13)
	DeclareVarInst(struct, float, fRec104[2])
	DeclareVarInst(struct, "float", fConst157)
	DeclareVarInst(struct, "float", fConst158)
	DeclareVarInst(struct, float, fRec109[2])
	DeclareVarInst(struct, float, fRec108[3])
	DeclareVarInst(struct, float, fRec107[3])
	DeclareVarInst(struct, float, fRec106[3])
	DeclareVarInst(struct, float, fRec105[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider14)
	DeclareVarInst(struct, float, fRec110[2])
	DeclareVarInst(struct, "float", fConst159)
	DeclareVarInst(struct, "float", fConst160)
	DeclareVarInst(struct, "float", fConst161)
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "float", fConst162)
	DeclareVarInst(struct, "float", fConst163)
	DeclareVarInst(struct, "float", fConst164)
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, "float", fConst165)
	DeclareVarInst(struct, "float", fConst166)
	DeclareVarInst(struct, "float", fConst167)
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "float", fConst168)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "float", fConst169)
	DeclareVarInst(struct, "float", fConst170)
	DeclareVarInst(struct, "float", fConst171)
	DeclareVarInst(struct, "float", fConst172)
	DeclareVarInst(struct, "float", fConst173)
	DeclareVarInst(struct, "float", fConst174)
	DeclareVarInst(struct, "float", fConst175)
	DeclareVarInst(struct, "float", fConst176)
	DeclareVarInst(struct, "float", fConst177)
	DeclareVarInst(struct, "float", fConst178)
	DeclareVarInst(struct, "float", fConst179)
	DeclareVarInst(struct, "float", fConst180)
	DeclareVarInst(struct, "float", fConst181)
	DeclareVarInst(struct, "float", fConst182)
	DeclareVarInst(struct, "float", fConst183)
	DeclareVarInst(struct, "float", fConst184)
	DeclareVarInst(struct, "float", fConst185)
	DeclareVarInst(struct, "float", fConst186)
	DeclareVarInst(struct, "float", fConst187)
	DeclareVarInst(struct, "float", fConst188)
	DeclareVarInst(struct, "float", fConst189)
	DeclareVarInst(struct, float, fRec117[3])
	DeclareVarInst(struct, "float", fConst190)
	DeclareVarInst(struct, "float", fConst191)
	DeclareVarInst(struct, "float", fConst192)
	DeclareVarInst(struct, float, fRec116[3])
	DeclareVarInst(struct, "float", fConst193)
	DeclareVarInst(struct, "float", fConst194)
	DeclareVarInst(struct, "float", fConst195)
	DeclareVarInst(struct, float, fRec115[3])
	DeclareVarInst(struct, "float", fConst196)
	DeclareVarInst(struct, "float", fConst197)
	DeclareVarInst(struct, "float", fConst198)
	DeclareVarInst(struct, "float", fConst199)
	DeclareVarInst(struct, float, fRec114[3])
	DeclareVarInst(struct, "float", fConst200)
	DeclareVarInst(struct, "float", fConst201)
	DeclareVarInst(struct, "float", fConst202)
	DeclareVarInst(struct, float, fRec113[3])
	DeclareVarInst(struct, "float", fConst203)
	DeclareVarInst(struct, "float", fConst204)
	DeclareVarInst(struct, "float", fConst205)
	DeclareVarInst(struct, float, fRec112[3])
	DeclareVarInst(struct, "float", fConst206)
	DeclareVarInst(struct, float, fRec111[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "float", fConst207)
	DeclareVarInst(struct, "float", fConst208)
	DeclareVarInst(struct, "float", fConst209)
	DeclareVarInst(struct, "float", fConst210)
	DeclareVarInst(struct, "float", fConst211)
	DeclareVarInst(struct, "float", fConst212)
	DeclareVarInst(struct, "float", fConst213)
	DeclareVarInst(struct, "float", fConst214)
	DeclareVarInst(struct, "float", fConst215)
	DeclareVarInst(struct, "float", fConst216)
	DeclareVarInst(struct, "float", fConst217)
	DeclareVarInst(struct, "float", fConst218)
	DeclareVarInst(struct, "float", fConst219)
	DeclareVarInst(struct, "float", fConst220)
	DeclareVarInst(struct, "float", fConst221)
	DeclareVarInst(struct, "float", fConst222)
	DeclareVarInst(struct, "float", fConst223)
	DeclareVarInst(struct, "float", fConst224)
	DeclareVarInst(struct, "float", fConst225)
	DeclareVarInst(struct, "float", fConst226)
	DeclareVarInst(struct, "float", fConst227)
	DeclareVarInst(struct, float, fRec124[3])
	DeclareVarInst(struct, "float", fConst228)
	DeclareVarInst(struct, "float", fConst229)
	DeclareVarInst(struct, "float", fConst230)
	DeclareVarInst(struct, float, fRec123[3])
	DeclareVarInst(struct, "float", fConst231)
	DeclareVarInst(struct, "float", fConst232)
	DeclareVarInst(struct, "float", fConst233)
	DeclareVarInst(struct, float, fRec122[3])
	DeclareVarInst(struct, "float", fConst234)
	DeclareVarInst(struct, "float", fConst235)
	DeclareVarInst(struct, "float", fConst236)
	DeclareVarInst(struct, "float", fConst237)
	DeclareVarInst(struct, float, fRec121[3])
	DeclareVarInst(struct, "float", fConst238)
	DeclareVarInst(struct, "float", fConst239)
	DeclareVarInst(struct, "float", fConst240)
	DeclareVarInst(struct, float, fRec120[3])
	DeclareVarInst(struct, "float", fConst241)
	DeclareVarInst(struct, "float", fConst242)
	DeclareVarInst(struct, "float", fConst243)
	DeclareVarInst(struct, float, fRec119[3])
	DeclareVarInst(struct, "float", fConst244)
	DeclareVarInst(struct, float, fRec118[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "float", fConst245)
	DeclareVarInst(struct, "float", fConst246)
	DeclareVarInst(struct, "float", fConst247)
	DeclareVarInst(struct, "float", fConst248)
	DeclareVarInst(struct, "float", fConst249)
	DeclareVarInst(struct, "float", fConst250)
	DeclareVarInst(struct, "float", fConst251)
	DeclareVarInst(struct, "float", fConst252)
	DeclareVarInst(struct, "float", fConst253)
	DeclareVarInst(struct, "float", fConst254)
	DeclareVarInst(struct, "float", fConst255)
	DeclareVarInst(struct, "float", fConst256)
	DeclareVarInst(struct, "float", fConst257)
	DeclareVarInst(struct, "float", fConst258)
	DeclareVarInst(struct, "float", fConst259)
	DeclareVarInst(struct, "float", fConst260)
	DeclareVarInst(struct, "float", fConst261)
	DeclareVarInst(struct, "float", fConst262)
	DeclareVarInst(struct, "float", fConst263)
	DeclareVarInst(struct, "float", fConst264)
	DeclareVarInst(struct, "float", fConst265)
	DeclareVarInst(struct, float, fRec131[3])
	DeclareVarInst(struct, "float", fConst266)
	DeclareVarInst(struct, "float", fConst267)
	DeclareVarInst(struct, "float", fConst268)
	DeclareVarInst(struct, float, fRec130[3])
	DeclareVarInst(struct, "float", fConst269)
	DeclareVarInst(struct, "float", fConst270)
	DeclareVarInst(struct, "float", fConst271)
	DeclareVarInst(struct, float, fRec129[3])
	DeclareVarInst(struct, "float", fConst272)
	DeclareVarInst(struct, "float", fConst273)
	DeclareVarInst(struct, "float", fConst274)
	DeclareVarInst(struct, "float", fConst275)
	DeclareVarInst(struct, float, fRec128[3])
	DeclareVarInst(struct, "float", fConst276)
	DeclareVarInst(struct, "float", fConst277)
	DeclareVarInst(struct, "float", fConst278)
	DeclareVarInst(struct, float, fRec127[3])
	DeclareVarInst(struct, "float", fConst279)
	DeclareVarInst(struct, "float", fConst280)
	DeclareVarInst(struct, "float", fConst281)
	DeclareVarInst(struct, float, fRec126[3])
	DeclareVarInst(struct, "float", fConst282)
	DeclareVarInst(struct, float, fRec125[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "float", fConst283)
	DeclareVarInst(struct, "float", fConst284)
	DeclareVarInst(struct, "float", fConst285)
	DeclareVarInst(struct, "float", fConst286)
	DeclareVarInst(struct, "float", fConst287)
	DeclareVarInst(struct, "float", fConst288)
	DeclareVarInst(struct, "float", fConst289)
	DeclareVarInst(struct, "float", fConst290)
	DeclareVarInst(struct, "float", fConst291)
	DeclareVarInst(struct, "float", fConst292)
	DeclareVarInst(struct, "float", fConst293)
	DeclareVarInst(struct, "float", fConst294)
	DeclareVarInst(struct, "float", fConst295)
	DeclareVarInst(struct, "float", fConst296)
	DeclareVarInst(struct, "float", fConst297)
	DeclareVarInst(struct, "float", fConst298)
	DeclareVarInst(struct, "float", fConst299)
	DeclareVarInst(struct, "float", fConst300)
	DeclareVarInst(struct, "float", fConst301)
	DeclareVarInst(struct, "float", fConst302)
	DeclareVarInst(struct, "float", fConst303)
	DeclareVarInst(struct, float, fRec138[3])
	DeclareVarInst(struct, "float", fConst304)
	DeclareVarInst(struct, "float", fConst305)
	DeclareVarInst(struct, "float", fConst306)
	DeclareVarInst(struct, float, fRec137[3])
	DeclareVarInst(struct, "float", fConst307)
	DeclareVarInst(struct, "float", fConst308)
	DeclareVarInst(struct, "float", fConst309)
	DeclareVarInst(struct, float, fRec136[3])
	DeclareVarInst(struct, "float", fConst310)
	DeclareVarInst(struct, "float", fConst311)
	DeclareVarInst(struct, "float", fConst312)
	DeclareVarInst(struct, "float", fConst313)
	DeclareVarInst(struct, float, fRec135[3])
	DeclareVarInst(struct, "float", fConst314)
	DeclareVarInst(struct, "float", fConst315)
	DeclareVarInst(struct, "float", fConst316)
	DeclareVarInst(struct, float, fRec134[3])
	DeclareVarInst(struct, "float", fConst317)
	DeclareVarInst(struct, "float", fConst318)
	DeclareVarInst(struct, "float", fConst319)
	DeclareVarInst(struct, float, fRec133[3])
	DeclareVarInst(struct, "float", fConst320)
	DeclareVarInst(struct, float, fRec132[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, "float", fConst321)
	DeclareVarInst(struct, "float", fConst322)
	DeclareVarInst(struct, "float", fConst323)
	DeclareVarInst(struct, "float", fConst324)
	DeclareVarInst(struct, "float", fConst325)
	DeclareVarInst(struct, "float", fConst326)
	DeclareVarInst(struct, "float", fConst327)
	DeclareVarInst(struct, "float", fConst328)
	DeclareVarInst(struct, "float", fConst329)
	DeclareVarInst(struct, "float", fConst330)
	DeclareVarInst(struct, "float", fConst331)
	DeclareVarInst(struct, "float", fConst332)
	DeclareVarInst(struct, "float", fConst333)
	DeclareVarInst(struct, "float", fConst334)
	DeclareVarInst(struct, "float", fConst335)
	DeclareVarInst(struct, "float", fConst336)
	DeclareVarInst(struct, "float", fConst337)
	DeclareVarInst(struct, "float", fConst338)
	DeclareVarInst(struct, "float", fConst339)
	DeclareVarInst(struct, "float", fConst340)
	DeclareVarInst(struct, "float", fConst341)
	DeclareVarInst(struct, float, fRec145[3])
	DeclareVarInst(struct, "float", fConst342)
	DeclareVarInst(struct, "float", fConst343)
	DeclareVarInst(struct, "float", fConst344)
	DeclareVarInst(struct, float, fRec144[3])
	DeclareVarInst(struct, "float", fConst345)
	DeclareVarInst(struct, "float", fConst346)
	DeclareVarInst(struct, "float", fConst347)
	DeclareVarInst(struct, float, fRec143[3])
	DeclareVarInst(struct, "float", fConst348)
	DeclareVarInst(struct, "float", fConst349)
	DeclareVarInst(struct, "float", fConst350)
	DeclareVarInst(struct, "float", fConst351)
	DeclareVarInst(struct, float, fRec142[3])
	DeclareVarInst(struct, "float", fConst352)
	DeclareVarInst(struct, "float", fConst353)
	DeclareVarInst(struct, "float", fConst354)
	DeclareVarInst(struct, float, fRec141[3])
	DeclareVarInst(struct, "float", fConst355)
	DeclareVarInst(struct, "float", fConst356)
	DeclareVarInst(struct, "float", fConst357)
	DeclareVarInst(struct, float, fRec140[3])
	DeclareVarInst(struct, "float", fConst358)
	DeclareVarInst(struct, float, fRec139[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, "float", fConst359)
	DeclareVarInst(struct, "float", fConst360)
	DeclareVarInst(struct, "float", fConst361)
	DeclareVarInst(struct, "float", fConst362)
	DeclareVarInst(struct, "float", fConst363)
	DeclareVarInst(struct, "float", fConst364)
	DeclareVarInst(struct, "float", fConst365)
	DeclareVarInst(struct, "float", fConst366)
	DeclareVarInst(struct, "float", fConst367)
	DeclareVarInst(struct, "float", fConst368)
	DeclareVarInst(struct, "float", fConst369)
	DeclareVarInst(struct, "float", fConst370)
	DeclareVarInst(struct, "float", fConst371)
	DeclareVarInst(struct, "float", fConst372)
	DeclareVarInst(struct, "float", fConst373)
	DeclareVarInst(struct, "float", fConst374)
	DeclareVarInst(struct, "float", fConst375)
	DeclareVarInst(struct, "float", fConst376)
	DeclareVarInst(struct, "float", fConst377)
	DeclareVarInst(struct, "float", fConst378)
	DeclareVarInst(struct, "float", fConst379)
	DeclareVarInst(struct, float, fRec152[3])
	DeclareVarInst(struct, "float", fConst380)
	DeclareVarInst(struct, "float", fConst381)
	DeclareVarInst(struct, "float", fConst382)
	DeclareVarInst(struct, float, fRec151[3])
	DeclareVarInst(struct, "float", fConst383)
	DeclareVarInst(struct, "float", fConst384)
	DeclareVarInst(struct, "float", fConst385)
	DeclareVarInst(struct, float, fRec150[3])
	DeclareVarInst(struct, "float", fConst386)
	DeclareVarInst(struct, "float", fConst387)
	DeclareVarInst(struct, "float", fConst388)
	DeclareVarInst(struct, "float", fConst389)
	DeclareVarInst(struct, float, fRec149[3])
	DeclareVarInst(struct, "float", fConst390)
	DeclareVarInst(struct, "float", fConst391)
	DeclareVarInst(struct, "float", fConst392)
	DeclareVarInst(struct, float, fRec148[3])
	DeclareVarInst(struct, "float", fConst393)
	DeclareVarInst(struct, "float", fConst394)
	DeclareVarInst(struct, "float", fConst395)
	DeclareVarInst(struct, float, fRec147[3])
	DeclareVarInst(struct, "float", fConst396)
	DeclareVarInst(struct, float, fRec146[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, "float", fConst397)
	DeclareVarInst(struct, "float", fConst398)
	DeclareVarInst(struct, "float", fConst399)
	DeclareVarInst(struct, "float", fConst400)
	DeclareVarInst(struct, "float", fConst401)
	DeclareVarInst(struct, "float", fConst402)
	DeclareVarInst(struct, "float", fConst403)
	DeclareVarInst(struct, "float", fConst404)
	DeclareVarInst(struct, "float", fConst405)
	DeclareVarInst(struct, "float", fConst406)
	DeclareVarInst(struct, "float", fConst407)
	DeclareVarInst(struct, "float", fConst408)
	DeclareVarInst(struct, "float", fConst409)
	DeclareVarInst(struct, "float", fConst410)
	DeclareVarInst(struct, "float", fConst411)
	DeclareVarInst(struct, "float", fConst412)
	DeclareVarInst(struct, "float", fConst413)
	DeclareVarInst(struct, "float", fConst414)
	DeclareVarInst(struct, "float", fConst415)
	DeclareVarInst(struct, "float", fConst416)
	DeclareVarInst(struct, "float", fConst417)
	DeclareVarInst(struct, float, fRec159[3])
	DeclareVarInst(struct, "float", fConst418)
	DeclareVarInst(struct, "float", fConst419)
	DeclareVarInst(struct, "float", fConst420)
	DeclareVarInst(struct, float, fRec158[3])
	DeclareVarInst(struct, "float", fConst421)
	DeclareVarInst(struct, "float", fConst422)
	DeclareVarInst(struct, "float", fConst423)
	DeclareVarInst(struct, float, fRec157[3])
	DeclareVarInst(struct, "float", fConst424)
	DeclareVarInst(struct, "float", fConst425)
	DeclareVarInst(struct, "float", fConst426)
	DeclareVarInst(struct, "float", fConst427)
	DeclareVarInst(struct, float, fRec156[3])
	DeclareVarInst(struct, "float", fConst428)
	DeclareVarInst(struct, "float", fConst429)
	DeclareVarInst(struct, "float", fConst430)
	DeclareVarInst(struct, float, fRec155[3])
	DeclareVarInst(struct, "float", fConst431)
	DeclareVarInst(struct, "float", fConst432)
	DeclareVarInst(struct, "float", fConst433)
	DeclareVarInst(struct, float, fRec154[3])
	DeclareVarInst(struct, "float", fConst434)
	DeclareVarInst(struct, float, fRec153[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, "float", fConst435)
	DeclareVarInst(struct, "float", fConst436)
	DeclareVarInst(struct, "float", fConst437)
	DeclareVarInst(struct, "float", fConst438)
	DeclareVarInst(struct, "float", fConst439)
	DeclareVarInst(struct, "float", fConst440)
	DeclareVarInst(struct, "float", fConst441)
	DeclareVarInst(struct, "float", fConst442)
	DeclareVarInst(struct, "float", fConst443)
	DeclareVarInst(struct, "float", fConst444)
	DeclareVarInst(struct, "float", fConst445)
	DeclareVarInst(struct, "float", fConst446)
	DeclareVarInst(struct, "float", fConst447)
	DeclareVarInst(struct, "float", fConst448)
	DeclareVarInst(struct, "float", fConst449)
	DeclareVarInst(struct, "float", fConst450)
	DeclareVarInst(struct, "float", fConst451)
	DeclareVarInst(struct, "float", fConst452)
	DeclareVarInst(struct, "float", fConst453)
	DeclareVarInst(struct, "float", fConst454)
	DeclareVarInst(struct, "float", fConst455)
	DeclareVarInst(struct, float, fRec166[3])
	DeclareVarInst(struct, "float", fConst456)
	DeclareVarInst(struct, "float", fConst457)
	DeclareVarInst(struct, "float", fConst458)
	DeclareVarInst(struct, float, fRec165[3])
	DeclareVarInst(struct, "float", fConst459)
	DeclareVarInst(struct, "float", fConst460)
	DeclareVarInst(struct, "float", fConst461)
	DeclareVarInst(struct, float, fRec164[3])
	DeclareVarInst(struct, "float", fConst462)
	DeclareVarInst(struct, "float", fConst463)
	DeclareVarInst(struct, "float", fConst464)
	DeclareVarInst(struct, "float", fConst465)
	DeclareVarInst(struct, float, fRec163[3])
	DeclareVarInst(struct, "float", fConst466)
	DeclareVarInst(struct, "float", fConst467)
	DeclareVarInst(struct, "float", fConst468)
	DeclareVarInst(struct, float, fRec162[3])
	DeclareVarInst(struct, "float", fConst469)
	DeclareVarInst(struct, "float", fConst470)
	DeclareVarInst(struct, "float", fConst471)
	DeclareVarInst(struct, float, fRec161[3])
	DeclareVarInst(struct, "float", fConst472)
	DeclareVarInst(struct, float, fRec160[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph8)
	DeclareVarInst(struct, "float", fConst473)
	DeclareVarInst(struct, "float", fConst474)
	DeclareVarInst(struct, "float", fConst475)
	DeclareVarInst(struct, "float", fConst476)
	DeclareVarInst(struct, "float", fConst477)
	DeclareVarInst(struct, "float", fConst478)
	DeclareVarInst(struct, "float", fConst479)
	DeclareVarInst(struct, "float", fConst480)
	DeclareVarInst(struct, "float", fConst481)
	DeclareVarInst(struct, "float", fConst482)
	DeclareVarInst(struct, "float", fConst483)
	DeclareVarInst(struct, "float", fConst484)
	DeclareVarInst(struct, "float", fConst485)
	DeclareVarInst(struct, "float", fConst486)
	DeclareVarInst(struct, "float", fConst487)
	DeclareVarInst(struct, "float", fConst488)
	DeclareVarInst(struct, "float", fConst489)
	DeclareVarInst(struct, "float", fConst490)
	DeclareVarInst(struct, "float", fConst491)
	DeclareVarInst(struct, "float", fConst492)
	DeclareVarInst(struct, "float", fConst493)
	DeclareVarInst(struct, float, fRec173[3])
	DeclareVarInst(struct, "float", fConst494)
	DeclareVarInst(struct, "float", fConst495)
	DeclareVarInst(struct, "float", fConst496)
	DeclareVarInst(struct, float, fRec172[3])
	DeclareVarInst(struct, "float", fConst497)
	DeclareVarInst(struct, "float", fConst498)
	DeclareVarInst(struct, "float", fConst499)
	DeclareVarInst(struct, float, fRec171[3])
	DeclareVarInst(struct, "float", fConst500)
	DeclareVarInst(struct, "float", fConst501)
	DeclareVarInst(struct, "float", fConst502)
	DeclareVarInst(struct, "float", fConst503)
	DeclareVarInst(struct, float, fRec170[3])
	DeclareVarInst(struct, "float", fConst504)
	DeclareVarInst(struct, "float", fConst505)
	DeclareVarInst(struct, "float", fConst506)
	DeclareVarInst(struct, float, fRec169[3])
	DeclareVarInst(struct, "float", fConst507)
	DeclareVarInst(struct, "float", fConst508)
	DeclareVarInst(struct, "float", fConst509)
	DeclareVarInst(struct, float, fRec168[3])
	DeclareVarInst(struct, "float", fConst510)
	DeclareVarInst(struct, float, fRec167[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph9)
	DeclareVarInst(struct, "float", fConst511)
	DeclareVarInst(struct, "float", fConst512)
	DeclareVarInst(struct, "float", fConst513)
	DeclareVarInst(struct, "float", fConst514)
	DeclareVarInst(struct, "float", fConst515)
	DeclareVarInst(struct, "float", fConst516)
	DeclareVarInst(struct, "float", fConst517)
	DeclareVarInst(struct, "float", fConst518)
	DeclareVarInst(struct, "float", fConst519)
	DeclareVarInst(struct, "float", fConst520)
	DeclareVarInst(struct, "float", fConst521)
	DeclareVarInst(struct, "float", fConst522)
	DeclareVarInst(struct, "float", fConst523)
	DeclareVarInst(struct, "float", fConst524)
	DeclareVarInst(struct, "float", fConst525)
	DeclareVarInst(struct, "float", fConst526)
	DeclareVarInst(struct, "float", fConst527)
	DeclareVarInst(struct, "float", fConst528)
	DeclareVarInst(struct, "float", fConst529)
	DeclareVarInst(struct, "float", fConst530)
	DeclareVarInst(struct, "float", fConst531)
	DeclareVarInst(struct, float, fRec180[3])
	DeclareVarInst(struct, "float", fConst532)
	DeclareVarInst(struct, "float", fConst533)
	DeclareVarInst(struct, "float", fConst534)
	DeclareVarInst(struct, float, fRec179[3])
	DeclareVarInst(struct, "float", fConst535)
	DeclareVarInst(struct, "float", fConst536)
	DeclareVarInst(struct, "float", fConst537)
	DeclareVarInst(struct, float, fRec178[3])
	DeclareVarInst(struct, "float", fConst538)
	DeclareVarInst(struct, "float", fConst539)
	DeclareVarInst(struct, "float", fConst540)
	DeclareVarInst(struct, "float", fConst541)
	DeclareVarInst(struct, float, fRec177[3])
	DeclareVarInst(struct, "float", fConst542)
	DeclareVarInst(struct, "float", fConst543)
	DeclareVarInst(struct, "float", fConst544)
	DeclareVarInst(struct, float, fRec176[3])
	DeclareVarInst(struct, "float", fConst545)
	DeclareVarInst(struct, "float", fConst546)
	DeclareVarInst(struct, "float", fConst547)
	DeclareVarInst(struct, float, fRec175[3])
	DeclareVarInst(struct, "float", fConst548)
	DeclareVarInst(struct, float, fRec174[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph10)
	DeclareVarInst(struct, "float", fConst549)
	DeclareVarInst(struct, "float", fConst550)
	DeclareVarInst(struct, "float", fConst551)
	DeclareVarInst(struct, "float", fConst552)
	DeclareVarInst(struct, "float", fConst553)
	DeclareVarInst(struct, "float", fConst554)
	DeclareVarInst(struct, "float", fConst555)
	DeclareVarInst(struct, "float", fConst556)
	DeclareVarInst(struct, "float", fConst557)
	DeclareVarInst(struct, "float", fConst558)
	DeclareVarInst(struct, "float", fConst559)
	DeclareVarInst(struct, "float", fConst560)
	DeclareVarInst(struct, "float", fConst561)
	DeclareVarInst(struct, "float", fConst562)
	DeclareVarInst(struct, "float", fConst563)
	DeclareVarInst(struct, "float", fConst564)
	DeclareVarInst(struct, "float", fConst565)
	DeclareVarInst(struct, "float", fConst566)
	DeclareVarInst(struct, "float", fConst567)
	DeclareVarInst(struct, "float", fConst568)
	DeclareVarInst(struct, "float", fConst569)
	DeclareVarInst(struct, float, fRec187[3])
	DeclareVarInst(struct, "float", fConst570)
	DeclareVarInst(struct, "float", fConst571)
	DeclareVarInst(struct, "float", fConst572)
	DeclareVarInst(struct, float, fRec186[3])
	DeclareVarInst(struct, "float", fConst573)
	DeclareVarInst(struct, "float", fConst574)
	DeclareVarInst(struct, "float", fConst575)
	DeclareVarInst(struct, float, fRec185[3])
	DeclareVarInst(struct, "float", fConst576)
	DeclareVarInst(struct, "float", fConst577)
	DeclareVarInst(struct, "float", fConst578)
	DeclareVarInst(struct, "float", fConst579)
	DeclareVarInst(struct, float, fRec184[3])
	DeclareVarInst(struct, "float", fConst580)
	DeclareVarInst(struct, "float", fConst581)
	DeclareVarInst(struct, "float", fConst582)
	DeclareVarInst(struct, float, fRec183[3])
	DeclareVarInst(struct, "float", fConst583)
	DeclareVarInst(struct, "float", fConst584)
	DeclareVarInst(struct, "float", fConst585)
	DeclareVarInst(struct, float, fRec182[3])
	DeclareVarInst(struct, "float", fConst586)
	DeclareVarInst(struct, float, fRec181[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph11)
	DeclareVarInst(struct, "float", fConst587)
	DeclareVarInst(struct, "float", fConst588)
	DeclareVarInst(struct, "float", fConst589)
	DeclareVarInst(struct, "float", fConst590)
	DeclareVarInst(struct, "float", fConst591)
	DeclareVarInst(struct, "float", fConst592)
	DeclareVarInst(struct, "float", fConst593)
	DeclareVarInst(struct, "float", fConst594)
	DeclareVarInst(struct, "float", fConst595)
	DeclareVarInst(struct, "float", fConst596)
	DeclareVarInst(struct, "float", fConst597)
	DeclareVarInst(struct, "float", fConst598)
	DeclareVarInst(struct, "float", fConst599)
	DeclareVarInst(struct, "float", fConst600)
	DeclareVarInst(struct, "float", fConst601)
	DeclareVarInst(struct, "float", fConst602)
	DeclareVarInst(struct, "float", fConst603)
	DeclareVarInst(struct, "float", fConst604)
	DeclareVarInst(struct, "float", fConst605)
	DeclareVarInst(struct, "float", fConst606)
	DeclareVarInst(struct, "float", fConst607)
	DeclareVarInst(struct, float, fRec194[3])
	DeclareVarInst(struct, "float", fConst608)
	DeclareVarInst(struct, "float", fConst609)
	DeclareVarInst(struct, "float", fConst610)
	DeclareVarInst(struct, float, fRec193[3])
	DeclareVarInst(struct, "float", fConst611)
	DeclareVarInst(struct, "float", fConst612)
	DeclareVarInst(struct, "float", fConst613)
	DeclareVarInst(struct, float, fRec192[3])
	DeclareVarInst(struct, "float", fConst614)
	DeclareVarInst(struct, "float", fConst615)
	DeclareVarInst(struct, "float", fConst616)
	DeclareVarInst(struct, "float", fConst617)
	DeclareVarInst(struct, float, fRec191[3])
	DeclareVarInst(struct, "float", fConst618)
	DeclareVarInst(struct, "float", fConst619)
	DeclareVarInst(struct, "float", fConst620)
	DeclareVarInst(struct, float, fRec190[3])
	DeclareVarInst(struct, "float", fConst621)
	DeclareVarInst(struct, "float", fConst622)
	DeclareVarInst(struct, "float", fConst623)
	DeclareVarInst(struct, float, fRec189[3])
	DeclareVarInst(struct, "float", fConst624)
	DeclareVarInst(struct, float, fRec188[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph12)
	DeclareVarInst(struct, "float", fConst625)
	DeclareVarInst(struct, "float", fConst626)
	DeclareVarInst(struct, "float", fConst627)
	DeclareVarInst(struct, "float", fConst628)
	DeclareVarInst(struct, "float", fConst629)
	DeclareVarInst(struct, "float", fConst630)
	DeclareVarInst(struct, "float", fConst631)
	DeclareVarInst(struct, "float", fConst632)
	DeclareVarInst(struct, "float", fConst633)
	DeclareVarInst(struct, "float", fConst634)
	DeclareVarInst(struct, "float", fConst635)
	DeclareVarInst(struct, "float", fConst636)
	DeclareVarInst(struct, "float", fConst637)
	DeclareVarInst(struct, "float", fConst638)
	DeclareVarInst(struct, "float", fConst639)
	DeclareVarInst(struct, "float", fConst640)
	DeclareVarInst(struct, "float", fConst641)
	DeclareVarInst(struct, "float", fConst642)
	DeclareVarInst(struct, "float", fConst643)
	DeclareVarInst(struct, "float", fConst644)
	DeclareVarInst(struct, "float", fConst645)
	DeclareVarInst(struct, float, fRec201[3])
	DeclareVarInst(struct, "float", fConst646)
	DeclareVarInst(struct, "float", fConst647)
	DeclareVarInst(struct, "float", fConst648)
	DeclareVarInst(struct, float, fRec200[3])
	DeclareVarInst(struct, "float", fConst649)
	DeclareVarInst(struct, "float", fConst650)
	DeclareVarInst(struct, "float", fConst651)
	DeclareVarInst(struct, float, fRec199[3])
	DeclareVarInst(struct, "float", fConst652)
	DeclareVarInst(struct, "float", fConst653)
	DeclareVarInst(struct, "float", fConst654)
	DeclareVarInst(struct, "float", fConst655)
	DeclareVarInst(struct, float, fRec198[3])
	DeclareVarInst(struct, "float", fConst656)
	DeclareVarInst(struct, "float", fConst657)
	DeclareVarInst(struct, "float", fConst658)
	DeclareVarInst(struct, float, fRec197[3])
	DeclareVarInst(struct, "float", fConst659)
	DeclareVarInst(struct, "float", fConst660)
	DeclareVarInst(struct, "float", fConst661)
	DeclareVarInst(struct, float, fRec196[3])
	DeclareVarInst(struct, "float", fConst662)
	DeclareVarInst(struct, float, fRec195[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph13)
	DeclareVarInst(struct, "float", fConst663)
	DeclareVarInst(struct, "float", fConst664)
	DeclareVarInst(struct, "float", fConst665)
	DeclareVarInst(struct, "float", fConst666)
	DeclareVarInst(struct, "float", fConst667)
	DeclareVarInst(struct, "float", fConst668)
	DeclareVarInst(struct, "float", fConst669)
	DeclareVarInst(struct, "float", fConst670)
	DeclareVarInst(struct, "float", fConst671)
	DeclareVarInst(struct, float, fRec205[3])
	DeclareVarInst(struct, "float", fConst672)
	DeclareVarInst(struct, "float", fConst673)
	DeclareVarInst(struct, "float", fConst674)
	DeclareVarInst(struct, float, fRec204[3])
	DeclareVarInst(struct, "float", fConst675)
	DeclareVarInst(struct, "float", fConst676)
	DeclareVarInst(struct, "float", fConst677)
	DeclareVarInst(struct, float, fRec203[3])
	DeclareVarInst(struct, "float", fConst678)
	DeclareVarInst(struct, float, fRec202[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph14)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, FunCallInst("tanf", BinopInst("/", Float(50265.4844f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.157482162f)), LoadVarInst(struct, fConst2)), Float(0.935140193f))))
	StoreVarInst(struct, fConst5, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst6))))
	StoreVarInst(struct, fConst8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.743130445f)), LoadVarInst(struct, fConst2)), Float(1.4500711f))))
	StoreVarInst(struct, fConst9, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst10, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst9))))
	StoreVarInst(struct, fConst11, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(3.18972731f)), LoadVarInst(struct, fConst2)), Float(4.07678175f))))
	StoreVarInst(struct, fConst12, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst13, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst12))))
	StoreVarInst(struct, fConst14, FunCallInst("tanf", BinopInst("/", Float(245.43692f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst15, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst14)))
	StoreVarInst(struct, fConst16, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(0.618034005f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst17, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst16)))
	StoreVarInst(struct, fConst18, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst14))))
	StoreVarInst(struct, fConst19, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst18))))
	StoreVarInst(struct, fConst20, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f))))
	StoreVarInst(struct, fConst21, FunCallInst("tanf", BinopInst("/", Float(490.87384f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst22, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst21)))
	StoreVarInst(struct, fConst23, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst24, BinopInst("+", LoadVarInst(struct, fConst15), Float(1.0f)))
	StoreVarInst(struct, fConst25, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst23), LoadVarInst(struct, fConst24))))
	StoreVarInst(struct, fConst26, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst27, BinopInst("+", LoadVarInst(struct, fConst22), Float(1.0f)))
	StoreVarInst(struct, fConst28, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst22)), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst29, FunCallInst("tanf", BinopInst("/", Float(981.747681f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst30, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst29)))
	StoreVarInst(struct, fConst31, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(0.618034005f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst32, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst31), LoadVarInst(struct, fConst27))))
	StoreVarInst(struct, fConst33, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f))))
	StoreVarInst(struct, fConst34, BinopInst("+", LoadVarInst(struct, fConst30), Float(1.0f)))
	StoreVarInst(struct, fConst35, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst30)), LoadVarInst(struct, fConst34))))
	StoreVarInst(struct, fConst36, FunCallInst("tanf", BinopInst("/", Float(1963.49536f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst37, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst36)))
	StoreVarInst(struct, fConst38, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(0.618034005f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst39, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst38), LoadVarInst(struct, fConst34))))
	StoreVarInst(struct, fConst40, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f))))
	StoreVarInst(struct, fConst41, BinopInst("+", LoadVarInst(struct, fConst37), Float(1.0f)))
	StoreVarInst(struct, fConst42, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst37)), LoadVarInst(struct, fConst41))))
	StoreVarInst(struct, fConst43, FunCallInst("tanf", BinopInst("/", Float(3926.99072f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst44, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst43)))
	StoreVarInst(struct, fConst45, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(0.618034005f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst46, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst45), LoadVarInst(struct, fConst41))))
	StoreVarInst(struct, fConst47, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f))))
	StoreVarInst(struct, fConst48, BinopInst("+", LoadVarInst(struct, fConst44), Float(1.0f)))
	StoreVarInst(struct, fConst49, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst44)), LoadVarInst(struct, fConst48))))
	StoreVarInst(struct, fConst50, FunCallInst("tanf", BinopInst("/", Float(7853.98145f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst51, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst50)))
	StoreVarInst(struct, fConst52, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(0.618034005f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst53, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst52), LoadVarInst(struct, fConst48))))
	StoreVarInst(struct, fConst54, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f))))
	StoreVarInst(struct, fConst55, BinopInst("+", LoadVarInst(struct, fConst51), Float(1.0f)))
	StoreVarInst(struct, fConst56, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst51)), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst57, FunCallInst("tanf", BinopInst("/", Float(15707.9629f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst58, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst57)))
	StoreVarInst(struct, fConst59, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst60, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst59), LoadVarInst(struct, fConst55))))
	StoreVarInst(struct, fConst61, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst62, BinopInst("+", LoadVarInst(struct, fConst58), Float(1.0f)))
	StoreVarInst(struct, fConst63, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst58)), LoadVarInst(struct, fConst62))))
	StoreVarInst(struct, fConst64, FunCallInst("tanf", BinopInst("/", Float(31415.9258f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst65, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst64)))
	StoreVarInst(struct, fConst66, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(0.618034005f)), LoadVarInst(struct, fConst64)), Float(1.0f)))
	StoreVarInst(struct, fConst67, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst66), LoadVarInst(struct, fConst62))))
	StoreVarInst(struct, fConst68, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(1.61803401f)), LoadVarInst(struct, fConst64)), Float(1.0f))))
	StoreVarInst(struct, fConst69, BinopInst("+", LoadVarInst(struct, fConst65), Float(1.0f)))
	StoreVarInst(struct, fConst70, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst65)), LoadVarInst(struct, fConst69))))
	StoreVarInst(struct, fConst71, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst69)))
	StoreVarInst(struct, fConst72, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst73, BinopInst("*", Float(0.25f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst74, BinopInst("*", Float(0.0416666679f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst75, BinopInst("*", Float(0.00520833349f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst76, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst64))))
	StoreVarInst(struct, fConst77, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst76))))
	StoreVarInst(struct, fConst78, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(-1.61803401f)), LoadVarInst(struct, fConst64)), Float(1.0f)))
	StoreVarInst(struct, fConst79, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst66)))
	StoreVarInst(struct, fConst80, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst65), Float(-0.618034005f)), LoadVarInst(struct, fConst64)), Float(1.0f)))
	StoreVarInst(struct, fConst81, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst57))))
	StoreVarInst(struct, fConst82, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst81))))
	StoreVarInst(struct, fConst83, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst84, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst59)))
	StoreVarInst(struct, fConst85, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-0.618034005f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst86, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst50))))
	StoreVarInst(struct, fConst87, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst86))))
	StoreVarInst(struct, fConst88, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(-1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst89, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst52)))
	StoreVarInst(struct, fConst90, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(-0.618034005f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst91, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst43))))
	StoreVarInst(struct, fConst92, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst91))))
	StoreVarInst(struct, fConst93, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(-1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst94, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst45)))
	StoreVarInst(struct, fConst95, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(-0.618034005f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst96, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst36))))
	StoreVarInst(struct, fConst97, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst96))))
	StoreVarInst(struct, fConst98, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(-1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst99, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst38)))
	StoreVarInst(struct, fConst100, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(-0.618034005f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst101, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst29))))
	StoreVarInst(struct, fConst102, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst101))))
	StoreVarInst(struct, fConst103, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(-1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst104, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst31)))
	StoreVarInst(struct, fConst105, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(-0.618034005f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst106, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst21))))
	StoreVarInst(struct, fConst107, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst106))))
	StoreVarInst(struct, fConst108, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst109, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst23)))
	StoreVarInst(struct, fConst110, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-0.618034005f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst111, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst15)))
	StoreVarInst(struct, fConst112, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst15)), LoadVarInst(struct, fConst24))))
	StoreVarInst(struct, fConst113, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst18))))
	StoreVarInst(struct, fConst114, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(-1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst115, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(-0.618034005f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst116, FunCallInst("tanf", BinopInst("/", Float(122.71846f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst117, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst116)))
	StoreVarInst(struct, fConst118, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f))))
	StoreVarInst(struct, fConst119, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst116))))
	StoreVarInst(struct, fConst120, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst119))))
	StoreVarInst(struct, fConst121, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(-1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f)))
	StoreVarInst(struct, fConst122, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(0.618034005f)), LoadVarInst(struct, fConst116)), Float(1.0f))))
	StoreVarInst(struct, fConst123, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst119))))
	StoreVarInst(struct, fConst124, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f))))
	StoreVarInst(struct, fConst125, BinopInst("+", LoadVarInst(struct, fConst117), Float(1.0f)))
	StoreVarInst(struct, fConst126, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst117)), LoadVarInst(struct, fConst125))))
	StoreVarInst(struct, fConst127, BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst16), LoadVarInst(struct, fConst125))))
	StoreVarInst(struct, fConst128, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst117)))
	StoreVarInst(struct, fConst129, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(-1.61803401f)), LoadVarInst(struct, fConst116)), Float(1.0f)))
	StoreVarInst(struct, fConst130, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst117), Float(-0.618034005f)), LoadVarInst(struct, fConst116)), Float(1.0f)))
	StoreVarInst(struct, fConst131, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst76))))
	StoreVarInst(struct, fConst132, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst65)))
	StoreVarInst(struct, fConst133, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f))))
	StoreVarInst(struct, fConst134, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst15), Float(-1.61803401f)), LoadVarInst(struct, fConst14)), Float(1.0f)))
	StoreVarInst(struct, fConst135, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f))))
	StoreVarInst(struct, fConst136, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst22), Float(-1.61803401f)), LoadVarInst(struct, fConst21)), Float(1.0f)))
	StoreVarInst(struct, fConst137, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f))))
	StoreVarInst(struct, fConst138, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst30), Float(-1.61803401f)), LoadVarInst(struct, fConst29)), Float(1.0f)))
	StoreVarInst(struct, fConst139, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f))))
	StoreVarInst(struct, fConst140, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst37), Float(-1.61803401f)), LoadVarInst(struct, fConst36)), Float(1.0f)))
	StoreVarInst(struct, fConst141, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f))))
	StoreVarInst(struct, fConst142, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst44), Float(-1.61803401f)), LoadVarInst(struct, fConst43)), Float(1.0f)))
	StoreVarInst(struct, fConst143, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f))))
	StoreVarInst(struct, fConst144, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst51), Float(-1.61803401f)), LoadVarInst(struct, fConst50)), Float(1.0f)))
	StoreVarInst(struct, fConst145, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f))))
	StoreVarInst(struct, fConst146, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst58), Float(-1.61803401f)), LoadVarInst(struct, fConst57)), Float(1.0f)))
	StoreVarInst(struct, fConst147, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst81))))
	StoreVarInst(struct, fConst148, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst58)))
	StoreVarInst(struct, fConst149, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst86))))
	StoreVarInst(struct, fConst150, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst51)))
	StoreVarInst(struct, fConst151, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst91))))
	StoreVarInst(struct, fConst152, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst44)))
	StoreVarInst(struct, fConst153, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst96))))
	StoreVarInst(struct, fConst154, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst37)))
	StoreVarInst(struct, fConst155, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst101))))
	StoreVarInst(struct, fConst156, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst30)))
	StoreVarInst(struct, fConst157, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst106))))
	StoreVarInst(struct, fConst158, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst22)))
	StoreVarInst(struct, fConst159, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-3.18972731f)), LoadVarInst(struct, fConst2)), Float(4.07678175f)))
	StoreVarInst(struct, fConst160, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst161, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst162, BinopInst("+", LoadVarInst(struct, fConst12), Float(0.000407678192f)))
	StoreVarInst(struct, fConst163, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.743130445f)), LoadVarInst(struct, fConst2)), Float(1.4500711f)))
	StoreVarInst(struct, fConst164, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst165, BinopInst("+", LoadVarInst(struct, fConst9), Float(1.4500711f)))
	StoreVarInst(struct, fConst166, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.157482162f)), LoadVarInst(struct, fConst2)), Float(0.935140193f)))
	StoreVarInst(struct, fConst167, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst168, BinopInst("+", LoadVarInst(struct, fConst6), Float(0.935140193f)))
	StoreVarInst(struct, fConst169, FunCallInst("tanf", BinopInst("/", Float(31665.2695f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst170, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst169)))
	StoreVarInst(struct, fConst171, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.157482162f)), LoadVarInst(struct, fConst169)), Float(0.935140193f))))
	StoreVarInst(struct, fConst172, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst169)))
	StoreVarInst(struct, fConst173, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst174, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst173))))
	StoreVarInst(struct, fConst175, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.743130445f)), LoadVarInst(struct, fConst169)), Float(1.4500711f))))
	StoreVarInst(struct, fConst176, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst177, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst176))))
	StoreVarInst(struct, fConst178, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(3.18972731f)), LoadVarInst(struct, fConst169)), Float(4.07678175f))))
	StoreVarInst(struct, fConst179, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst180, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst179))))
	StoreVarInst(struct, fConst181, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.168404877f)), LoadVarInst(struct, fConst2)), Float(1.06935835f))))
	StoreVarInst(struct, fConst182, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst183, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.51247865f)), LoadVarInst(struct, fConst2)), Float(0.689621389f))))
	StoreVarInst(struct, fConst184, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst185, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(0.782413065f)), LoadVarInst(struct, fConst2)), Float(0.245291501f))))
	StoreVarInst(struct, fConst186, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst187, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst186))))
	StoreVarInst(struct, fConst188, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.782413065f)), LoadVarInst(struct, fConst2)), Float(0.245291501f)))
	StoreVarInst(struct, fConst189, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst190, BinopInst("+", LoadVarInst(struct, fConst186), Float(0.000433227193f)))
	StoreVarInst(struct, fConst191, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.51247865f)), LoadVarInst(struct, fConst2)), Float(0.689621389f)))
	StoreVarInst(struct, fConst192, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst193, BinopInst("+", LoadVarInst(struct, fConst160), Float(7.62173128f)))
	StoreVarInst(struct, fConst194, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst3), Float(-0.168404877f)), LoadVarInst(struct, fConst2)), Float(1.06935835f)))
	StoreVarInst(struct, fConst195, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst160))))
	StoreVarInst(struct, fConst196, BinopInst("+", LoadVarInst(struct, fConst160), Float(53.5361519f)))
	StoreVarInst(struct, fConst197, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-3.18972731f)), LoadVarInst(struct, fConst169)), Float(4.07678175f)))
	StoreVarInst(struct, fConst198, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst199, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst200, BinopInst("+", LoadVarInst(struct, fConst179), Float(0.000407678192f)))
	StoreVarInst(struct, fConst201, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.743130445f)), LoadVarInst(struct, fConst169)), Float(1.4500711f)))
	StoreVarInst(struct, fConst202, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst203, BinopInst("+", LoadVarInst(struct, fConst176), Float(1.4500711f)))
	StoreVarInst(struct, fConst204, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.157482162f)), LoadVarInst(struct, fConst169)), Float(0.935140193f)))
	StoreVarInst(struct, fConst205, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst206, BinopInst("+", LoadVarInst(struct, fConst173), Float(0.935140193f)))
	StoreVarInst(struct, fConst207, FunCallInst("tanf", BinopInst("/", Float(19947.8691f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst208, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst207)))
	StoreVarInst(struct, fConst209, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.157482162f)), LoadVarInst(struct, fConst207)), Float(0.935140193f))))
	StoreVarInst(struct, fConst210, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst207)))
	StoreVarInst(struct, fConst211, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst212, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst211))))
	StoreVarInst(struct, fConst213, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.743130445f)), LoadVarInst(struct, fConst207)), Float(1.4500711f))))
	StoreVarInst(struct, fConst214, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst215, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst214))))
	StoreVarInst(struct, fConst216, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(3.18972731f)), LoadVarInst(struct, fConst207)), Float(4.07678175f))))
	StoreVarInst(struct, fConst217, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst218, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst217))))
	StoreVarInst(struct, fConst219, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.168404877f)), LoadVarInst(struct, fConst169)), Float(1.06935835f))))
	StoreVarInst(struct, fConst220, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst221, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.51247865f)), LoadVarInst(struct, fConst169)), Float(0.689621389f))))
	StoreVarInst(struct, fConst222, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst223, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(0.782413065f)), LoadVarInst(struct, fConst169)), Float(0.245291501f))))
	StoreVarInst(struct, fConst224, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst172)))
	StoreVarInst(struct, fConst225, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst224))))
	StoreVarInst(struct, fConst226, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.782413065f)), LoadVarInst(struct, fConst169)), Float(0.245291501f)))
	StoreVarInst(struct, fConst227, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst228, BinopInst("+", LoadVarInst(struct, fConst224), Float(0.000433227193f)))
	StoreVarInst(struct, fConst229, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.51247865f)), LoadVarInst(struct, fConst169)), Float(0.689621389f)))
	StoreVarInst(struct, fConst230, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst231, BinopInst("+", LoadVarInst(struct, fConst198), Float(7.62173128f)))
	StoreVarInst(struct, fConst232, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst170), Float(-0.168404877f)), LoadVarInst(struct, fConst169)), Float(1.06935835f)))
	StoreVarInst(struct, fConst233, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst198))))
	StoreVarInst(struct, fConst234, BinopInst("+", LoadVarInst(struct, fConst198), Float(53.5361519f)))
	StoreVarInst(struct, fConst235, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-3.18972731f)), LoadVarInst(struct, fConst207)), Float(4.07678175f)))
	StoreVarInst(struct, fConst236, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst237, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst238, BinopInst("+", LoadVarInst(struct, fConst217), Float(0.000407678192f)))
	StoreVarInst(struct, fConst239, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.743130445f)), LoadVarInst(struct, fConst207)), Float(1.4500711f)))
	StoreVarInst(struct, fConst240, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst241, BinopInst("+", LoadVarInst(struct, fConst214), Float(1.4500711f)))
	StoreVarInst(struct, fConst242, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.157482162f)), LoadVarInst(struct, fConst207)), Float(0.935140193f)))
	StoreVarInst(struct, fConst243, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst244, BinopInst("+", LoadVarInst(struct, fConst211), Float(0.935140193f)))
	StoreVarInst(struct, fConst245, FunCallInst("tanf", BinopInst("/", Float(12566.3711f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst246, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst245)))
	StoreVarInst(struct, fConst247, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.157482162f)), LoadVarInst(struct, fConst245)), Float(0.935140193f))))
	StoreVarInst(struct, fConst248, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst245)))
	StoreVarInst(struct, fConst249, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst250, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst249))))
	StoreVarInst(struct, fConst251, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.743130445f)), LoadVarInst(struct, fConst245)), Float(1.4500711f))))
	StoreVarInst(struct, fConst252, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst253, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst252))))
	StoreVarInst(struct, fConst254, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(3.18972731f)), LoadVarInst(struct, fConst245)), Float(4.07678175f))))
	StoreVarInst(struct, fConst255, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst256, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst255))))
	StoreVarInst(struct, fConst257, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.168404877f)), LoadVarInst(struct, fConst207)), Float(1.06935835f))))
	StoreVarInst(struct, fConst258, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst259, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.51247865f)), LoadVarInst(struct, fConst207)), Float(0.689621389f))))
	StoreVarInst(struct, fConst260, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst261, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(0.782413065f)), LoadVarInst(struct, fConst207)), Float(0.245291501f))))
	StoreVarInst(struct, fConst262, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst210)))
	StoreVarInst(struct, fConst263, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst262))))
	StoreVarInst(struct, fConst264, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.782413065f)), LoadVarInst(struct, fConst207)), Float(0.245291501f)))
	StoreVarInst(struct, fConst265, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst266, BinopInst("+", LoadVarInst(struct, fConst262), Float(0.000433227193f)))
	StoreVarInst(struct, fConst267, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.51247865f)), LoadVarInst(struct, fConst207)), Float(0.689621389f)))
	StoreVarInst(struct, fConst268, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst269, BinopInst("+", LoadVarInst(struct, fConst236), Float(7.62173128f)))
	StoreVarInst(struct, fConst270, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst208), Float(-0.168404877f)), LoadVarInst(struct, fConst207)), Float(1.06935835f)))
	StoreVarInst(struct, fConst271, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst236))))
	StoreVarInst(struct, fConst272, BinopInst("+", LoadVarInst(struct, fConst236), Float(53.5361519f)))
	StoreVarInst(struct, fConst273, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-3.18972731f)), LoadVarInst(struct, fConst245)), Float(4.07678175f)))
	StoreVarInst(struct, fConst274, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst275, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst276, BinopInst("+", LoadVarInst(struct, fConst255), Float(0.000407678192f)))
	StoreVarInst(struct, fConst277, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.743130445f)), LoadVarInst(struct, fConst245)), Float(1.4500711f)))
	StoreVarInst(struct, fConst278, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst279, BinopInst("+", LoadVarInst(struct, fConst252), Float(1.4500711f)))
	StoreVarInst(struct, fConst280, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.157482162f)), LoadVarInst(struct, fConst245)), Float(0.935140193f)))
	StoreVarInst(struct, fConst281, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst282, BinopInst("+", LoadVarInst(struct, fConst249), Float(0.935140193f)))
	StoreVarInst(struct, fConst283, FunCallInst("tanf", BinopInst("/", Float(7916.31738f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst284, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst283)))
	StoreVarInst(struct, fConst285, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.157482162f)), LoadVarInst(struct, fConst283)), Float(0.935140193f))))
	StoreVarInst(struct, fConst286, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst283)))
	StoreVarInst(struct, fConst287, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst288, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst287))))
	StoreVarInst(struct, fConst289, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.743130445f)), LoadVarInst(struct, fConst283)), Float(1.4500711f))))
	StoreVarInst(struct, fConst290, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst291, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst290))))
	StoreVarInst(struct, fConst292, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(3.18972731f)), LoadVarInst(struct, fConst283)), Float(4.07678175f))))
	StoreVarInst(struct, fConst293, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst294, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst293))))
	StoreVarInst(struct, fConst295, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.168404877f)), LoadVarInst(struct, fConst245)), Float(1.06935835f))))
	StoreVarInst(struct, fConst296, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst297, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.51247865f)), LoadVarInst(struct, fConst245)), Float(0.689621389f))))
	StoreVarInst(struct, fConst298, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst299, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(0.782413065f)), LoadVarInst(struct, fConst245)), Float(0.245291501f))))
	StoreVarInst(struct, fConst300, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst248)))
	StoreVarInst(struct, fConst301, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst300))))
	StoreVarInst(struct, fConst302, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.782413065f)), LoadVarInst(struct, fConst245)), Float(0.245291501f)))
	StoreVarInst(struct, fConst303, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst304, BinopInst("+", LoadVarInst(struct, fConst300), Float(0.000433227193f)))
	StoreVarInst(struct, fConst305, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.51247865f)), LoadVarInst(struct, fConst245)), Float(0.689621389f)))
	StoreVarInst(struct, fConst306, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst307, BinopInst("+", LoadVarInst(struct, fConst274), Float(7.62173128f)))
	StoreVarInst(struct, fConst308, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst246), Float(-0.168404877f)), LoadVarInst(struct, fConst245)), Float(1.06935835f)))
	StoreVarInst(struct, fConst309, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst274))))
	StoreVarInst(struct, fConst310, BinopInst("+", LoadVarInst(struct, fConst274), Float(53.5361519f)))
	StoreVarInst(struct, fConst311, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-3.18972731f)), LoadVarInst(struct, fConst283)), Float(4.07678175f)))
	StoreVarInst(struct, fConst312, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst313, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst314, BinopInst("+", LoadVarInst(struct, fConst293), Float(0.000407678192f)))
	StoreVarInst(struct, fConst315, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.743130445f)), LoadVarInst(struct, fConst283)), Float(1.4500711f)))
	StoreVarInst(struct, fConst316, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst317, BinopInst("+", LoadVarInst(struct, fConst290), Float(1.4500711f)))
	StoreVarInst(struct, fConst318, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.157482162f)), LoadVarInst(struct, fConst283)), Float(0.935140193f)))
	StoreVarInst(struct, fConst319, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst320, BinopInst("+", LoadVarInst(struct, fConst287), Float(0.935140193f)))
	StoreVarInst(struct, fConst321, FunCallInst("tanf", BinopInst("/", Float(4986.96729f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst322, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst321)))
	StoreVarInst(struct, fConst323, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.157482162f)), LoadVarInst(struct, fConst321)), Float(0.935140193f))))
	StoreVarInst(struct, fConst324, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst321)))
	StoreVarInst(struct, fConst325, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst326, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst325))))
	StoreVarInst(struct, fConst327, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.743130445f)), LoadVarInst(struct, fConst321)), Float(1.4500711f))))
	StoreVarInst(struct, fConst328, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst329, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst328))))
	StoreVarInst(struct, fConst330, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(3.18972731f)), LoadVarInst(struct, fConst321)), Float(4.07678175f))))
	StoreVarInst(struct, fConst331, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst332, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst331))))
	StoreVarInst(struct, fConst333, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.168404877f)), LoadVarInst(struct, fConst283)), Float(1.06935835f))))
	StoreVarInst(struct, fConst334, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst335, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.51247865f)), LoadVarInst(struct, fConst283)), Float(0.689621389f))))
	StoreVarInst(struct, fConst336, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst337, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(0.782413065f)), LoadVarInst(struct, fConst283)), Float(0.245291501f))))
	StoreVarInst(struct, fConst338, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst286)))
	StoreVarInst(struct, fConst339, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst338))))
	StoreVarInst(struct, fConst340, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.782413065f)), LoadVarInst(struct, fConst283)), Float(0.245291501f)))
	StoreVarInst(struct, fConst341, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst342, BinopInst("+", LoadVarInst(struct, fConst338), Float(0.000433227193f)))
	StoreVarInst(struct, fConst343, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.51247865f)), LoadVarInst(struct, fConst283)), Float(0.689621389f)))
	StoreVarInst(struct, fConst344, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst345, BinopInst("+", LoadVarInst(struct, fConst312), Float(7.62173128f)))
	StoreVarInst(struct, fConst346, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst284), Float(-0.168404877f)), LoadVarInst(struct, fConst283)), Float(1.06935835f)))
	StoreVarInst(struct, fConst347, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst312))))
	StoreVarInst(struct, fConst348, BinopInst("+", LoadVarInst(struct, fConst312), Float(53.5361519f)))
	StoreVarInst(struct, fConst349, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-3.18972731f)), LoadVarInst(struct, fConst321)), Float(4.07678175f)))
	StoreVarInst(struct, fConst350, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst351, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst352, BinopInst("+", LoadVarInst(struct, fConst331), Float(0.000407678192f)))
	StoreVarInst(struct, fConst353, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.743130445f)), LoadVarInst(struct, fConst321)), Float(1.4500711f)))
	StoreVarInst(struct, fConst354, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst355, BinopInst("+", LoadVarInst(struct, fConst328), Float(1.4500711f)))
	StoreVarInst(struct, fConst356, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.157482162f)), LoadVarInst(struct, fConst321)), Float(0.935140193f)))
	StoreVarInst(struct, fConst357, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst358, BinopInst("+", LoadVarInst(struct, fConst325), Float(0.935140193f)))
	StoreVarInst(struct, fConst359, FunCallInst("tanf", BinopInst("/", Float(3141.59277f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst360, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst359)))
	StoreVarInst(struct, fConst361, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.157482162f)), LoadVarInst(struct, fConst359)), Float(0.935140193f))))
	StoreVarInst(struct, fConst362, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst359)))
	StoreVarInst(struct, fConst363, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst364, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst363))))
	StoreVarInst(struct, fConst365, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.743130445f)), LoadVarInst(struct, fConst359)), Float(1.4500711f))))
	StoreVarInst(struct, fConst366, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst367, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst366))))
	StoreVarInst(struct, fConst368, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(3.18972731f)), LoadVarInst(struct, fConst359)), Float(4.07678175f))))
	StoreVarInst(struct, fConst369, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst370, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst369))))
	StoreVarInst(struct, fConst371, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.168404877f)), LoadVarInst(struct, fConst321)), Float(1.06935835f))))
	StoreVarInst(struct, fConst372, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst373, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.51247865f)), LoadVarInst(struct, fConst321)), Float(0.689621389f))))
	StoreVarInst(struct, fConst374, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst375, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(0.782413065f)), LoadVarInst(struct, fConst321)), Float(0.245291501f))))
	StoreVarInst(struct, fConst376, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst324)))
	StoreVarInst(struct, fConst377, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst376))))
	StoreVarInst(struct, fConst378, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.782413065f)), LoadVarInst(struct, fConst321)), Float(0.245291501f)))
	StoreVarInst(struct, fConst379, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst380, BinopInst("+", LoadVarInst(struct, fConst376), Float(0.000433227193f)))
	StoreVarInst(struct, fConst381, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.51247865f)), LoadVarInst(struct, fConst321)), Float(0.689621389f)))
	StoreVarInst(struct, fConst382, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst383, BinopInst("+", LoadVarInst(struct, fConst350), Float(7.62173128f)))
	StoreVarInst(struct, fConst384, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst322), Float(-0.168404877f)), LoadVarInst(struct, fConst321)), Float(1.06935835f)))
	StoreVarInst(struct, fConst385, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst350))))
	StoreVarInst(struct, fConst386, BinopInst("+", LoadVarInst(struct, fConst350), Float(53.5361519f)))
	StoreVarInst(struct, fConst387, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-3.18972731f)), LoadVarInst(struct, fConst359)), Float(4.07678175f)))
	StoreVarInst(struct, fConst388, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst389, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst390, BinopInst("+", LoadVarInst(struct, fConst369), Float(0.000407678192f)))
	StoreVarInst(struct, fConst391, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.743130445f)), LoadVarInst(struct, fConst359)), Float(1.4500711f)))
	StoreVarInst(struct, fConst392, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst393, BinopInst("+", LoadVarInst(struct, fConst366), Float(1.4500711f)))
	StoreVarInst(struct, fConst394, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.157482162f)), LoadVarInst(struct, fConst359)), Float(0.935140193f)))
	StoreVarInst(struct, fConst395, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst396, BinopInst("+", LoadVarInst(struct, fConst363), Float(0.935140193f)))
	StoreVarInst(struct, fConst397, FunCallInst("tanf", BinopInst("/", Float(1979.07935f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst398, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst397)))
	StoreVarInst(struct, fConst399, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.157482162f)), LoadVarInst(struct, fConst397)), Float(0.935140193f))))
	StoreVarInst(struct, fConst400, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst397)))
	StoreVarInst(struct, fConst401, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst402, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst401))))
	StoreVarInst(struct, fConst403, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.743130445f)), LoadVarInst(struct, fConst397)), Float(1.4500711f))))
	StoreVarInst(struct, fConst404, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst405, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst404))))
	StoreVarInst(struct, fConst406, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(3.18972731f)), LoadVarInst(struct, fConst397)), Float(4.07678175f))))
	StoreVarInst(struct, fConst407, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst408, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst407))))
	StoreVarInst(struct, fConst409, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.168404877f)), LoadVarInst(struct, fConst359)), Float(1.06935835f))))
	StoreVarInst(struct, fConst410, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst411, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.51247865f)), LoadVarInst(struct, fConst359)), Float(0.689621389f))))
	StoreVarInst(struct, fConst412, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst413, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(0.782413065f)), LoadVarInst(struct, fConst359)), Float(0.245291501f))))
	StoreVarInst(struct, fConst414, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst362)))
	StoreVarInst(struct, fConst415, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst414))))
	StoreVarInst(struct, fConst416, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.782413065f)), LoadVarInst(struct, fConst359)), Float(0.245291501f)))
	StoreVarInst(struct, fConst417, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst418, BinopInst("+", LoadVarInst(struct, fConst414), Float(0.000433227193f)))
	StoreVarInst(struct, fConst419, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.51247865f)), LoadVarInst(struct, fConst359)), Float(0.689621389f)))
	StoreVarInst(struct, fConst420, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst421, BinopInst("+", LoadVarInst(struct, fConst388), Float(7.62173128f)))
	StoreVarInst(struct, fConst422, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst360), Float(-0.168404877f)), LoadVarInst(struct, fConst359)), Float(1.06935835f)))
	StoreVarInst(struct, fConst423, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst388))))
	StoreVarInst(struct, fConst424, BinopInst("+", LoadVarInst(struct, fConst388), Float(53.5361519f)))
	StoreVarInst(struct, fConst425, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-3.18972731f)), LoadVarInst(struct, fConst397)), Float(4.07678175f)))
	StoreVarInst(struct, fConst426, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst427, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst428, BinopInst("+", LoadVarInst(struct, fConst407), Float(0.000407678192f)))
	StoreVarInst(struct, fConst429, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.743130445f)), LoadVarInst(struct, fConst397)), Float(1.4500711f)))
	StoreVarInst(struct, fConst430, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst431, BinopInst("+", LoadVarInst(struct, fConst404), Float(1.4500711f)))
	StoreVarInst(struct, fConst432, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.157482162f)), LoadVarInst(struct, fConst397)), Float(0.935140193f)))
	StoreVarInst(struct, fConst433, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst434, BinopInst("+", LoadVarInst(struct, fConst401), Float(0.935140193f)))
	StoreVarInst(struct, fConst435, FunCallInst("tanf", BinopInst("/", Float(1246.74182f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst436, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst435)))
	StoreVarInst(struct, fConst437, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.157482162f)), LoadVarInst(struct, fConst435)), Float(0.935140193f))))
	StoreVarInst(struct, fConst438, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst435)))
	StoreVarInst(struct, fConst439, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst440, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst439))))
	StoreVarInst(struct, fConst441, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.743130445f)), LoadVarInst(struct, fConst435)), Float(1.4500711f))))
	StoreVarInst(struct, fConst442, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst443, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst442))))
	StoreVarInst(struct, fConst444, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(3.18972731f)), LoadVarInst(struct, fConst435)), Float(4.07678175f))))
	StoreVarInst(struct, fConst445, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst446, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst445))))
	StoreVarInst(struct, fConst447, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.168404877f)), LoadVarInst(struct, fConst397)), Float(1.06935835f))))
	StoreVarInst(struct, fConst448, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst449, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.51247865f)), LoadVarInst(struct, fConst397)), Float(0.689621389f))))
	StoreVarInst(struct, fConst450, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst451, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(0.782413065f)), LoadVarInst(struct, fConst397)), Float(0.245291501f))))
	StoreVarInst(struct, fConst452, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst400)))
	StoreVarInst(struct, fConst453, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst452))))
	StoreVarInst(struct, fConst454, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.782413065f)), LoadVarInst(struct, fConst397)), Float(0.245291501f)))
	StoreVarInst(struct, fConst455, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst456, BinopInst("+", LoadVarInst(struct, fConst452), Float(0.000433227193f)))
	StoreVarInst(struct, fConst457, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.51247865f)), LoadVarInst(struct, fConst397)), Float(0.689621389f)))
	StoreVarInst(struct, fConst458, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst459, BinopInst("+", LoadVarInst(struct, fConst426), Float(7.62173128f)))
	StoreVarInst(struct, fConst460, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst398), Float(-0.168404877f)), LoadVarInst(struct, fConst397)), Float(1.06935835f)))
	StoreVarInst(struct, fConst461, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst426))))
	StoreVarInst(struct, fConst462, BinopInst("+", LoadVarInst(struct, fConst426), Float(53.5361519f)))
	StoreVarInst(struct, fConst463, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-3.18972731f)), LoadVarInst(struct, fConst435)), Float(4.07678175f)))
	StoreVarInst(struct, fConst464, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst465, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst466, BinopInst("+", LoadVarInst(struct, fConst445), Float(0.000407678192f)))
	StoreVarInst(struct, fConst467, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.743130445f)), LoadVarInst(struct, fConst435)), Float(1.4500711f)))
	StoreVarInst(struct, fConst468, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst469, BinopInst("+", LoadVarInst(struct, fConst442), Float(1.4500711f)))
	StoreVarInst(struct, fConst470, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.157482162f)), LoadVarInst(struct, fConst435)), Float(0.935140193f)))
	StoreVarInst(struct, fConst471, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst472, BinopInst("+", LoadVarInst(struct, fConst439), Float(0.935140193f)))
	StoreVarInst(struct, fConst473, FunCallInst("tanf", BinopInst("/", Float(785.398193f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst474, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst473)))
	StoreVarInst(struct, fConst475, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.157482162f)), LoadVarInst(struct, fConst473)), Float(0.935140193f))))
	StoreVarInst(struct, fConst476, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst473)))
	StoreVarInst(struct, fConst477, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst478, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst477))))
	StoreVarInst(struct, fConst479, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.743130445f)), LoadVarInst(struct, fConst473)), Float(1.4500711f))))
	StoreVarInst(struct, fConst480, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst481, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst480))))
	StoreVarInst(struct, fConst482, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(3.18972731f)), LoadVarInst(struct, fConst473)), Float(4.07678175f))))
	StoreVarInst(struct, fConst483, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst484, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst483))))
	StoreVarInst(struct, fConst485, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.168404877f)), LoadVarInst(struct, fConst435)), Float(1.06935835f))))
	StoreVarInst(struct, fConst486, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst487, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.51247865f)), LoadVarInst(struct, fConst435)), Float(0.689621389f))))
	StoreVarInst(struct, fConst488, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst489, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(0.782413065f)), LoadVarInst(struct, fConst435)), Float(0.245291501f))))
	StoreVarInst(struct, fConst490, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst438)))
	StoreVarInst(struct, fConst491, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst490))))
	StoreVarInst(struct, fConst492, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.782413065f)), LoadVarInst(struct, fConst435)), Float(0.245291501f)))
	StoreVarInst(struct, fConst493, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst494, BinopInst("+", LoadVarInst(struct, fConst490), Float(0.000433227193f)))
	StoreVarInst(struct, fConst495, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.51247865f)), LoadVarInst(struct, fConst435)), Float(0.689621389f)))
	StoreVarInst(struct, fConst496, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst497, BinopInst("+", LoadVarInst(struct, fConst464), Float(7.62173128f)))
	StoreVarInst(struct, fConst498, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst436), Float(-0.168404877f)), LoadVarInst(struct, fConst435)), Float(1.06935835f)))
	StoreVarInst(struct, fConst499, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst464))))
	StoreVarInst(struct, fConst500, BinopInst("+", LoadVarInst(struct, fConst464), Float(53.5361519f)))
	StoreVarInst(struct, fConst501, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-3.18972731f)), LoadVarInst(struct, fConst473)), Float(4.07678175f)))
	StoreVarInst(struct, fConst502, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst503, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst504, BinopInst("+", LoadVarInst(struct, fConst483), Float(0.000407678192f)))
	StoreVarInst(struct, fConst505, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.743130445f)), LoadVarInst(struct, fConst473)), Float(1.4500711f)))
	StoreVarInst(struct, fConst506, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst507, BinopInst("+", LoadVarInst(struct, fConst480), Float(1.4500711f)))
	StoreVarInst(struct, fConst508, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.157482162f)), LoadVarInst(struct, fConst473)), Float(0.935140193f)))
	StoreVarInst(struct, fConst509, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst510, BinopInst("+", LoadVarInst(struct, fConst477), Float(0.935140193f)))
	StoreVarInst(struct, fConst511, FunCallInst("tanf", BinopInst("/", Float(494.769836f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst512, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst511)))
	StoreVarInst(struct, fConst513, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.157482162f)), LoadVarInst(struct, fConst511)), Float(0.935140193f))))
	StoreVarInst(struct, fConst514, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst511)))
	StoreVarInst(struct, fConst515, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst516, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst515))))
	StoreVarInst(struct, fConst517, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.743130445f)), LoadVarInst(struct, fConst511)), Float(1.4500711f))))
	StoreVarInst(struct, fConst518, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst519, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst518))))
	StoreVarInst(struct, fConst520, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(3.18972731f)), LoadVarInst(struct, fConst511)), Float(4.07678175f))))
	StoreVarInst(struct, fConst521, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst522, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst521))))
	StoreVarInst(struct, fConst523, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.168404877f)), LoadVarInst(struct, fConst473)), Float(1.06935835f))))
	StoreVarInst(struct, fConst524, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst525, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.51247865f)), LoadVarInst(struct, fConst473)), Float(0.689621389f))))
	StoreVarInst(struct, fConst526, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst527, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(0.782413065f)), LoadVarInst(struct, fConst473)), Float(0.245291501f))))
	StoreVarInst(struct, fConst528, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst476)))
	StoreVarInst(struct, fConst529, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst528))))
	StoreVarInst(struct, fConst530, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.782413065f)), LoadVarInst(struct, fConst473)), Float(0.245291501f)))
	StoreVarInst(struct, fConst531, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst532, BinopInst("+", LoadVarInst(struct, fConst528), Float(0.000433227193f)))
	StoreVarInst(struct, fConst533, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.51247865f)), LoadVarInst(struct, fConst473)), Float(0.689621389f)))
	StoreVarInst(struct, fConst534, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst535, BinopInst("+", LoadVarInst(struct, fConst502), Float(7.62173128f)))
	StoreVarInst(struct, fConst536, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst474), Float(-0.168404877f)), LoadVarInst(struct, fConst473)), Float(1.06935835f)))
	StoreVarInst(struct, fConst537, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst502))))
	StoreVarInst(struct, fConst538, BinopInst("+", LoadVarInst(struct, fConst502), Float(53.5361519f)))
	StoreVarInst(struct, fConst539, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-3.18972731f)), LoadVarInst(struct, fConst511)), Float(4.07678175f)))
	StoreVarInst(struct, fConst540, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst541, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst542, BinopInst("+", LoadVarInst(struct, fConst521), Float(0.000407678192f)))
	StoreVarInst(struct, fConst543, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.743130445f)), LoadVarInst(struct, fConst511)), Float(1.4500711f)))
	StoreVarInst(struct, fConst544, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst545, BinopInst("+", LoadVarInst(struct, fConst518), Float(1.4500711f)))
	StoreVarInst(struct, fConst546, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.157482162f)), LoadVarInst(struct, fConst511)), Float(0.935140193f)))
	StoreVarInst(struct, fConst547, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst548, BinopInst("+", LoadVarInst(struct, fConst515), Float(0.935140193f)))
	StoreVarInst(struct, fConst549, FunCallInst("tanf", BinopInst("/", Float(311.685455f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst550, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst549)))
	StoreVarInst(struct, fConst551, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.157482162f)), LoadVarInst(struct, fConst549)), Float(0.935140193f))))
	StoreVarInst(struct, fConst552, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst549)))
	StoreVarInst(struct, fConst553, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst554, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst553))))
	StoreVarInst(struct, fConst555, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.743130445f)), LoadVarInst(struct, fConst549)), Float(1.4500711f))))
	StoreVarInst(struct, fConst556, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst557, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst556))))
	StoreVarInst(struct, fConst558, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(3.18972731f)), LoadVarInst(struct, fConst549)), Float(4.07678175f))))
	StoreVarInst(struct, fConst559, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst560, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst559))))
	StoreVarInst(struct, fConst561, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.168404877f)), LoadVarInst(struct, fConst511)), Float(1.06935835f))))
	StoreVarInst(struct, fConst562, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst563, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.51247865f)), LoadVarInst(struct, fConst511)), Float(0.689621389f))))
	StoreVarInst(struct, fConst564, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst565, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(0.782413065f)), LoadVarInst(struct, fConst511)), Float(0.245291501f))))
	StoreVarInst(struct, fConst566, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst514)))
	StoreVarInst(struct, fConst567, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst566))))
	StoreVarInst(struct, fConst568, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.782413065f)), LoadVarInst(struct, fConst511)), Float(0.245291501f)))
	StoreVarInst(struct, fConst569, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst570, BinopInst("+", LoadVarInst(struct, fConst566), Float(0.000433227193f)))
	StoreVarInst(struct, fConst571, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.51247865f)), LoadVarInst(struct, fConst511)), Float(0.689621389f)))
	StoreVarInst(struct, fConst572, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst573, BinopInst("+", LoadVarInst(struct, fConst540), Float(7.62173128f)))
	StoreVarInst(struct, fConst574, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst512), Float(-0.168404877f)), LoadVarInst(struct, fConst511)), Float(1.06935835f)))
	StoreVarInst(struct, fConst575, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst540))))
	StoreVarInst(struct, fConst576, BinopInst("+", LoadVarInst(struct, fConst540), Float(53.5361519f)))
	StoreVarInst(struct, fConst577, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-3.18972731f)), LoadVarInst(struct, fConst549)), Float(4.07678175f)))
	StoreVarInst(struct, fConst578, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst579, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst580, BinopInst("+", LoadVarInst(struct, fConst559), Float(0.000407678192f)))
	StoreVarInst(struct, fConst581, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.743130445f)), LoadVarInst(struct, fConst549)), Float(1.4500711f)))
	StoreVarInst(struct, fConst582, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst583, BinopInst("+", LoadVarInst(struct, fConst556), Float(1.4500711f)))
	StoreVarInst(struct, fConst584, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.157482162f)), LoadVarInst(struct, fConst549)), Float(0.935140193f)))
	StoreVarInst(struct, fConst585, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst586, BinopInst("+", LoadVarInst(struct, fConst553), Float(0.935140193f)))
	StoreVarInst(struct, fConst587, FunCallInst("tanf", BinopInst("/", Float(196.349548f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst588, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst587)))
	StoreVarInst(struct, fConst589, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.157482162f)), LoadVarInst(struct, fConst587)), Float(0.935140193f))))
	StoreVarInst(struct, fConst590, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst587)))
	StoreVarInst(struct, fConst591, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst592, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst591))))
	StoreVarInst(struct, fConst593, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.743130445f)), LoadVarInst(struct, fConst587)), Float(1.4500711f))))
	StoreVarInst(struct, fConst594, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst595, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst594))))
	StoreVarInst(struct, fConst596, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(3.18972731f)), LoadVarInst(struct, fConst587)), Float(4.07678175f))))
	StoreVarInst(struct, fConst597, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst598, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst597))))
	StoreVarInst(struct, fConst599, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.168404877f)), LoadVarInst(struct, fConst549)), Float(1.06935835f))))
	StoreVarInst(struct, fConst600, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst601, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.51247865f)), LoadVarInst(struct, fConst549)), Float(0.689621389f))))
	StoreVarInst(struct, fConst602, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst603, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(0.782413065f)), LoadVarInst(struct, fConst549)), Float(0.245291501f))))
	StoreVarInst(struct, fConst604, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst552)))
	StoreVarInst(struct, fConst605, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst604))))
	StoreVarInst(struct, fConst606, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.782413065f)), LoadVarInst(struct, fConst549)), Float(0.245291501f)))
	StoreVarInst(struct, fConst607, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst608, BinopInst("+", LoadVarInst(struct, fConst604), Float(0.000433227193f)))
	StoreVarInst(struct, fConst609, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.51247865f)), LoadVarInst(struct, fConst549)), Float(0.689621389f)))
	StoreVarInst(struct, fConst610, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst611, BinopInst("+", LoadVarInst(struct, fConst578), Float(7.62173128f)))
	StoreVarInst(struct, fConst612, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst550), Float(-0.168404877f)), LoadVarInst(struct, fConst549)), Float(1.06935835f)))
	StoreVarInst(struct, fConst613, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst578))))
	StoreVarInst(struct, fConst614, BinopInst("+", LoadVarInst(struct, fConst578), Float(53.5361519f)))
	StoreVarInst(struct, fConst615, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-3.18972731f)), LoadVarInst(struct, fConst587)), Float(4.07678175f)))
	StoreVarInst(struct, fConst616, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst617, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst618, BinopInst("+", LoadVarInst(struct, fConst597), Float(0.000407678192f)))
	StoreVarInst(struct, fConst619, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.743130445f)), LoadVarInst(struct, fConst587)), Float(1.4500711f)))
	StoreVarInst(struct, fConst620, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst621, BinopInst("+", LoadVarInst(struct, fConst594), Float(1.4500711f)))
	StoreVarInst(struct, fConst622, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.157482162f)), LoadVarInst(struct, fConst587)), Float(0.935140193f)))
	StoreVarInst(struct, fConst623, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst624, BinopInst("+", LoadVarInst(struct, fConst591), Float(0.935140193f)))
	StoreVarInst(struct, fConst625, FunCallInst("tanf", BinopInst("/", Float(123.692459f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst626, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst625)))
	StoreVarInst(struct, fConst627, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.157482162f)), LoadVarInst(struct, fConst625)), Float(0.935140193f))))
	StoreVarInst(struct, fConst628, FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst625)))
	StoreVarInst(struct, fConst629, BinopInst("/", Float(50.0638084f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst630, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst629))))
	StoreVarInst(struct, fConst631, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.743130445f)), LoadVarInst(struct, fConst625)), Float(1.4500711f))))
	StoreVarInst(struct, fConst632, BinopInst("/", Float(11.0520525f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst633, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst632))))
	StoreVarInst(struct, fConst634, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(3.18972731f)), LoadVarInst(struct, fConst625)), Float(4.07678175f))))
	StoreVarInst(struct, fConst635, BinopInst("/", Float(0.00176617282f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst636, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000407678192f), LoadVarInst(struct, fConst635))))
	StoreVarInst(struct, fConst637, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.168404877f)), LoadVarInst(struct, fConst587)), Float(1.06935835f))))
	StoreVarInst(struct, fConst638, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst639, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.51247865f)), LoadVarInst(struct, fConst587)), Float(0.689621389f))))
	StoreVarInst(struct, fConst640, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst641, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(0.782413065f)), LoadVarInst(struct, fConst587)), Float(0.245291501f))))
	StoreVarInst(struct, fConst642, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst590)))
	StoreVarInst(struct, fConst643, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst642))))
	StoreVarInst(struct, fConst644, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.782413065f)), LoadVarInst(struct, fConst587)), Float(0.245291501f)))
	StoreVarInst(struct, fConst645, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst646, BinopInst("+", LoadVarInst(struct, fConst642), Float(0.000433227193f)))
	StoreVarInst(struct, fConst647, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.51247865f)), LoadVarInst(struct, fConst587)), Float(0.689621389f)))
	StoreVarInst(struct, fConst648, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst649, BinopInst("+", LoadVarInst(struct, fConst616), Float(7.62173128f)))
	StoreVarInst(struct, fConst650, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst588), Float(-0.168404877f)), LoadVarInst(struct, fConst587)), Float(1.06935835f)))
	StoreVarInst(struct, fConst651, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst616))))
	StoreVarInst(struct, fConst652, BinopInst("+", LoadVarInst(struct, fConst616), Float(53.5361519f)))
	StoreVarInst(struct, fConst653, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-3.18972731f)), LoadVarInst(struct, fConst625)), Float(4.07678175f)))
	StoreVarInst(struct, fConst654, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst655, BinopInst("*", Float(2.0f), BinopInst("-", Float(4.07678175f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst656, BinopInst("+", LoadVarInst(struct, fConst635), Float(0.000407678192f)))
	StoreVarInst(struct, fConst657, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.743130445f)), LoadVarInst(struct, fConst625)), Float(1.4500711f)))
	StoreVarInst(struct, fConst658, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.4500711f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst659, BinopInst("+", LoadVarInst(struct, fConst632), Float(1.4500711f)))
	StoreVarInst(struct, fConst660, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.157482162f)), LoadVarInst(struct, fConst625)), Float(0.935140193f)))
	StoreVarInst(struct, fConst661, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.935140193f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst662, BinopInst("+", LoadVarInst(struct, fConst629), Float(0.935140193f)))
	StoreVarInst(struct, fConst663, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.168404877f)), LoadVarInst(struct, fConst625)), Float(1.06935835f))))
	StoreVarInst(struct, fConst664, BinopInst("*", Float(2.0f), BinopInst("-", Float(53.5361519f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst665, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.51247865f)), LoadVarInst(struct, fConst625)), Float(0.689621389f))))
	StoreVarInst(struct, fConst666, BinopInst("*", Float(2.0f), BinopInst("-", Float(7.62173128f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst667, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(0.782413065f)), LoadVarInst(struct, fConst625)), Float(0.245291501f))))
	StoreVarInst(struct, fConst668, BinopInst("/", Float(9.99999975e-05f), LoadVarInst(struct, fConst628)))
	StoreVarInst(struct, fConst669, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.000433227193f), LoadVarInst(struct, fConst668))))
	StoreVarInst(struct, fConst670, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.782413065f)), LoadVarInst(struct, fConst625)), Float(0.245291501f)))
	StoreVarInst(struct, fConst671, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.245291501f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst672, BinopInst("+", LoadVarInst(struct, fConst668), Float(0.000433227193f)))
	StoreVarInst(struct, fConst673, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.51247865f)), LoadVarInst(struct, fConst625)), Float(0.689621389f)))
	StoreVarInst(struct, fConst674, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.689621389f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst675, BinopInst("+", LoadVarInst(struct, fConst654), Float(7.62173128f)))
	StoreVarInst(struct, fConst676, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst626), Float(-0.168404877f)), LoadVarInst(struct, fConst625)), Float(1.06935835f)))
	StoreVarInst(struct, fConst677, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.06935835f), LoadVarInst(struct, fConst654))))
	StoreVarInst(struct, fConst678, BinopInst("+", LoadVarInst(struct, fConst654), Float(53.5361519f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(50.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(-20.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(-0.10000000000000001f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fCheckbox3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider10, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider11, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider12, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider13, CastInst("FAUSTFLOAT", Double(-10.0f)))
	StoreVarInst(struct, fVslider14, CastInst("FAUSTFLOAT", Double(-10.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(4))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec18[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec19[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec21[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec34[LoadVarInst(loop, l27)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(4))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec22[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(3))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(3))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec23[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(3))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(3))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec24[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(3))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec25[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(3))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(3))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec26[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(3))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(3))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec27[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(3))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(3))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec28[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(2))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(3))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec29[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(3))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(3))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(3))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(3))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(3))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec30[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(3))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l68)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(3))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l70, Int32(0))
		BinopInst("<", LoadVarInst(loop, l70), Int32(2))
		StoreVarInst(loop, l70, BinopInst("+", LoadVarInst(loop, l70), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l70)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l71, Int32(0))
		BinopInst("<", LoadVarInst(loop, l71), Int32(2))
		StoreVarInst(loop, l71, BinopInst("+", LoadVarInst(loop, l71), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l71)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l72, Int32(0))
		BinopInst("<", LoadVarInst(loop, l72), Int32(3))
		StoreVarInst(loop, l72, BinopInst("+", LoadVarInst(loop, l72), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l72)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l73, Int32(0))
		BinopInst("<", LoadVarInst(loop, l73), Int32(3))
		StoreVarInst(loop, l73, BinopInst("+", LoadVarInst(loop, l73), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l73)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l74, Int32(0))
		BinopInst("<", LoadVarInst(loop, l74), Int32(2))
		StoreVarInst(loop, l74, BinopInst("+", LoadVarInst(loop, l74), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l74)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l75, Int32(0))
		BinopInst("<", LoadVarInst(loop, l75), Int32(2))
		StoreVarInst(loop, l75, BinopInst("+", LoadVarInst(loop, l75), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l75)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l76, Int32(0))
		BinopInst("<", LoadVarInst(loop, l76), Int32(3))
		StoreVarInst(loop, l76, BinopInst("+", LoadVarInst(loop, l76), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l76)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l77, Int32(0))
		BinopInst("<", LoadVarInst(loop, l77), Int32(3))
		StoreVarInst(loop, l77, BinopInst("+", LoadVarInst(loop, l77), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l77)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l78, Int32(0))
		BinopInst("<", LoadVarInst(loop, l78), Int32(3))
		StoreVarInst(loop, l78, BinopInst("+", LoadVarInst(loop, l78), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l78)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l79, Int32(0))
		BinopInst("<", LoadVarInst(loop, l79), Int32(3))
		StoreVarInst(loop, l79, BinopInst("+", LoadVarInst(loop, l79), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l79)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l80, Int32(0))
		BinopInst("<", LoadVarInst(loop, l80), Int32(3))
		StoreVarInst(loop, l80, BinopInst("+", LoadVarInst(loop, l80), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l80)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l81, Int32(0))
		BinopInst("<", LoadVarInst(loop, l81), Int32(3))
		StoreVarInst(loop, l81, BinopInst("+", LoadVarInst(loop, l81), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l81)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l82, Int32(0))
		BinopInst("<", LoadVarInst(loop, l82), Int32(3))
		StoreVarInst(loop, l82, BinopInst("+", LoadVarInst(loop, l82), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l82)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l83, Int32(0))
		BinopInst("<", LoadVarInst(loop, l83), Int32(3))
		StoreVarInst(loop, l83, BinopInst("+", LoadVarInst(loop, l83), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l83)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l84, Int32(0))
		BinopInst("<", LoadVarInst(loop, l84), Int32(3))
		StoreVarInst(loop, l84, BinopInst("+", LoadVarInst(loop, l84), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l84)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l85, Int32(0))
		BinopInst("<", LoadVarInst(loop, l85), Int32(3))
		StoreVarInst(loop, l85, BinopInst("+", LoadVarInst(loop, l85), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l85)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l86, Int32(0))
		BinopInst("<", LoadVarInst(loop, l86), Int32(2))
		StoreVarInst(loop, l86, BinopInst("+", LoadVarInst(loop, l86), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l86)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l87, Int32(0))
		BinopInst("<", LoadVarInst(loop, l87), Int32(2))
		StoreVarInst(loop, l87, BinopInst("+", LoadVarInst(loop, l87), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec69[LoadVarInst(loop, l87)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l88, Int32(0))
		BinopInst("<", LoadVarInst(loop, l88), Int32(3))
		StoreVarInst(loop, l88, BinopInst("+", LoadVarInst(loop, l88), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec68[LoadVarInst(loop, l88)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l89, Int32(0))
		BinopInst("<", LoadVarInst(loop, l89), Int32(3))
		StoreVarInst(loop, l89, BinopInst("+", LoadVarInst(loop, l89), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec67[LoadVarInst(loop, l89)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l90, Int32(0))
		BinopInst("<", LoadVarInst(loop, l90), Int32(3))
		StoreVarInst(loop, l90, BinopInst("+", LoadVarInst(loop, l90), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec66[LoadVarInst(loop, l90)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l91, Int32(0))
		BinopInst("<", LoadVarInst(loop, l91), Int32(3))
		StoreVarInst(loop, l91, BinopInst("+", LoadVarInst(loop, l91), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l91)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l92, Int32(0))
		BinopInst("<", LoadVarInst(loop, l92), Int32(3))
		StoreVarInst(loop, l92, BinopInst("+", LoadVarInst(loop, l92), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l92)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l93, Int32(0))
		BinopInst("<", LoadVarInst(loop, l93), Int32(3))
		StoreVarInst(loop, l93, BinopInst("+", LoadVarInst(loop, l93), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l93)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l94, Int32(0))
		BinopInst("<", LoadVarInst(loop, l94), Int32(3))
		StoreVarInst(loop, l94, BinopInst("+", LoadVarInst(loop, l94), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l94)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l95, Int32(0))
		BinopInst("<", LoadVarInst(loop, l95), Int32(3))
		StoreVarInst(loop, l95, BinopInst("+", LoadVarInst(loop, l95), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l95)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l96, Int32(0))
		BinopInst("<", LoadVarInst(loop, l96), Int32(3))
		StoreVarInst(loop, l96, BinopInst("+", LoadVarInst(loop, l96), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l96)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l97, Int32(0))
		BinopInst("<", LoadVarInst(loop, l97), Int32(2))
		StoreVarInst(loop, l97, BinopInst("+", LoadVarInst(loop, l97), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec70[LoadVarInst(loop, l97)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l98, Int32(0))
		BinopInst("<", LoadVarInst(loop, l98), Int32(2))
		StoreVarInst(loop, l98, BinopInst("+", LoadVarInst(loop, l98), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l98)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l99, Int32(0))
		BinopInst("<", LoadVarInst(loop, l99), Int32(3))
		StoreVarInst(loop, l99, BinopInst("+", LoadVarInst(loop, l99), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l99)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l100, Int32(0))
		BinopInst("<", LoadVarInst(loop, l100), Int32(3))
		StoreVarInst(loop, l100, BinopInst("+", LoadVarInst(loop, l100), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l100)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l101, Int32(0))
		BinopInst("<", LoadVarInst(loop, l101), Int32(3))
		StoreVarInst(loop, l101, BinopInst("+", LoadVarInst(loop, l101), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l101)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l102, Int32(0))
		BinopInst("<", LoadVarInst(loop, l102), Int32(3))
		StoreVarInst(loop, l102, BinopInst("+", LoadVarInst(loop, l102), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec75[LoadVarInst(loop, l102)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l103, Int32(0))
		BinopInst("<", LoadVarInst(loop, l103), Int32(3))
		StoreVarInst(loop, l103, BinopInst("+", LoadVarInst(loop, l103), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec74[LoadVarInst(loop, l103)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l104, Int32(0))
		BinopInst("<", LoadVarInst(loop, l104), Int32(3))
		StoreVarInst(loop, l104, BinopInst("+", LoadVarInst(loop, l104), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec73[LoadVarInst(loop, l104)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l105, Int32(0))
		BinopInst("<", LoadVarInst(loop, l105), Int32(3))
		StoreVarInst(loop, l105, BinopInst("+", LoadVarInst(loop, l105), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec72[LoadVarInst(loop, l105)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l106, Int32(0))
		BinopInst("<", LoadVarInst(loop, l106), Int32(3))
		StoreVarInst(loop, l106, BinopInst("+", LoadVarInst(loop, l106), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec71[LoadVarInst(loop, l106)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l107, Int32(0))
		BinopInst("<", LoadVarInst(loop, l107), Int32(2))
		StoreVarInst(loop, l107, BinopInst("+", LoadVarInst(loop, l107), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l107)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l108, Int32(0))
		BinopInst("<", LoadVarInst(loop, l108), Int32(2))
		StoreVarInst(loop, l108, BinopInst("+", LoadVarInst(loop, l108), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l108)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l109, Int32(0))
		BinopInst("<", LoadVarInst(loop, l109), Int32(3))
		StoreVarInst(loop, l109, BinopInst("+", LoadVarInst(loop, l109), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec87[LoadVarInst(loop, l109)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l110, Int32(0))
		BinopInst("<", LoadVarInst(loop, l110), Int32(3))
		StoreVarInst(loop, l110, BinopInst("+", LoadVarInst(loop, l110), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec86[LoadVarInst(loop, l110)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l111, Int32(0))
		BinopInst("<", LoadVarInst(loop, l111), Int32(3))
		StoreVarInst(loop, l111, BinopInst("+", LoadVarInst(loop, l111), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l111)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l112, Int32(0))
		BinopInst("<", LoadVarInst(loop, l112), Int32(3))
		StoreVarInst(loop, l112, BinopInst("+", LoadVarInst(loop, l112), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l112)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l113, Int32(0))
		BinopInst("<", LoadVarInst(loop, l113), Int32(3))
		StoreVarInst(loop, l113, BinopInst("+", LoadVarInst(loop, l113), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l113)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l114, Int32(0))
		BinopInst("<", LoadVarInst(loop, l114), Int32(3))
		StoreVarInst(loop, l114, BinopInst("+", LoadVarInst(loop, l114), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l114)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l115, Int32(0))
		BinopInst("<", LoadVarInst(loop, l115), Int32(3))
		StoreVarInst(loop, l115, BinopInst("+", LoadVarInst(loop, l115), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l115)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l116, Int32(0))
		BinopInst("<", LoadVarInst(loop, l116), Int32(2))
		StoreVarInst(loop, l116, BinopInst("+", LoadVarInst(loop, l116), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l116)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l117, Int32(0))
		BinopInst("<", LoadVarInst(loop, l117), Int32(2))
		StoreVarInst(loop, l117, BinopInst("+", LoadVarInst(loop, l117), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec96[LoadVarInst(loop, l117)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l118, Int32(0))
		BinopInst("<", LoadVarInst(loop, l118), Int32(3))
		StoreVarInst(loop, l118, BinopInst("+", LoadVarInst(loop, l118), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l118)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l119, Int32(0))
		BinopInst("<", LoadVarInst(loop, l119), Int32(3))
		StoreVarInst(loop, l119, BinopInst("+", LoadVarInst(loop, l119), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l119)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l120, Int32(0))
		BinopInst("<", LoadVarInst(loop, l120), Int32(3))
		StoreVarInst(loop, l120, BinopInst("+", LoadVarInst(loop, l120), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l120)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l121, Int32(0))
		BinopInst("<", LoadVarInst(loop, l121), Int32(3))
		StoreVarInst(loop, l121, BinopInst("+", LoadVarInst(loop, l121), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l121)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l122, Int32(0))
		BinopInst("<", LoadVarInst(loop, l122), Int32(3))
		StoreVarInst(loop, l122, BinopInst("+", LoadVarInst(loop, l122), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l122)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l123, Int32(0))
		BinopInst("<", LoadVarInst(loop, l123), Int32(3))
		StoreVarInst(loop, l123, BinopInst("+", LoadVarInst(loop, l123), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l123)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l124, Int32(0))
		BinopInst("<", LoadVarInst(loop, l124), Int32(2))
		StoreVarInst(loop, l124, BinopInst("+", LoadVarInst(loop, l124), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec97[LoadVarInst(loop, l124)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l125, Int32(0))
		BinopInst("<", LoadVarInst(loop, l125), Int32(2))
		StoreVarInst(loop, l125, BinopInst("+", LoadVarInst(loop, l125), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec103[LoadVarInst(loop, l125)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l126, Int32(0))
		BinopInst("<", LoadVarInst(loop, l126), Int32(3))
		StoreVarInst(loop, l126, BinopInst("+", LoadVarInst(loop, l126), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec102[LoadVarInst(loop, l126)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l127, Int32(0))
		BinopInst("<", LoadVarInst(loop, l127), Int32(3))
		StoreVarInst(loop, l127, BinopInst("+", LoadVarInst(loop, l127), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec101[LoadVarInst(loop, l127)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l128, Int32(0))
		BinopInst("<", LoadVarInst(loop, l128), Int32(3))
		StoreVarInst(loop, l128, BinopInst("+", LoadVarInst(loop, l128), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec100[LoadVarInst(loop, l128)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l129, Int32(0))
		BinopInst("<", LoadVarInst(loop, l129), Int32(3))
		StoreVarInst(loop, l129, BinopInst("+", LoadVarInst(loop, l129), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec99[LoadVarInst(loop, l129)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l130, Int32(0))
		BinopInst("<", LoadVarInst(loop, l130), Int32(3))
		StoreVarInst(loop, l130, BinopInst("+", LoadVarInst(loop, l130), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec98[LoadVarInst(loop, l130)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l131, Int32(0))
		BinopInst("<", LoadVarInst(loop, l131), Int32(2))
		StoreVarInst(loop, l131, BinopInst("+", LoadVarInst(loop, l131), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec104[LoadVarInst(loop, l131)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l132, Int32(0))
		BinopInst("<", LoadVarInst(loop, l132), Int32(2))
		StoreVarInst(loop, l132, BinopInst("+", LoadVarInst(loop, l132), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec109[LoadVarInst(loop, l132)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l133, Int32(0))
		BinopInst("<", LoadVarInst(loop, l133), Int32(3))
		StoreVarInst(loop, l133, BinopInst("+", LoadVarInst(loop, l133), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec108[LoadVarInst(loop, l133)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l134, Int32(0))
		BinopInst("<", LoadVarInst(loop, l134), Int32(3))
		StoreVarInst(loop, l134, BinopInst("+", LoadVarInst(loop, l134), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec107[LoadVarInst(loop, l134)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l135, Int32(0))
		BinopInst("<", LoadVarInst(loop, l135), Int32(3))
		StoreVarInst(loop, l135, BinopInst("+", LoadVarInst(loop, l135), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec106[LoadVarInst(loop, l135)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l136, Int32(0))
		BinopInst("<", LoadVarInst(loop, l136), Int32(3))
		StoreVarInst(loop, l136, BinopInst("+", LoadVarInst(loop, l136), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec105[LoadVarInst(loop, l136)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l137, Int32(0))
		BinopInst("<", LoadVarInst(loop, l137), Int32(2))
		StoreVarInst(loop, l137, BinopInst("+", LoadVarInst(loop, l137), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec110[LoadVarInst(loop, l137)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l138, Int32(0))
		BinopInst("<", LoadVarInst(loop, l138), Int32(3))
		StoreVarInst(loop, l138, BinopInst("+", LoadVarInst(loop, l138), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l138)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l139, Int32(0))
		BinopInst("<", LoadVarInst(loop, l139), Int32(3))
		StoreVarInst(loop, l139, BinopInst("+", LoadVarInst(loop, l139), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l139)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l140, Int32(0))
		BinopInst("<", LoadVarInst(loop, l140), Int32(3))
		StoreVarInst(loop, l140, BinopInst("+", LoadVarInst(loop, l140), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l140)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l141, Int32(0))
		BinopInst("<", LoadVarInst(loop, l141), Int32(2))
		StoreVarInst(loop, l141, BinopInst("+", LoadVarInst(loop, l141), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l141)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l142, Int32(0))
		BinopInst("<", LoadVarInst(loop, l142), Int32(3))
		StoreVarInst(loop, l142, BinopInst("+", LoadVarInst(loop, l142), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec117[LoadVarInst(loop, l142)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l143, Int32(0))
		BinopInst("<", LoadVarInst(loop, l143), Int32(3))
		StoreVarInst(loop, l143, BinopInst("+", LoadVarInst(loop, l143), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec116[LoadVarInst(loop, l143)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l144, Int32(0))
		BinopInst("<", LoadVarInst(loop, l144), Int32(3))
		StoreVarInst(loop, l144, BinopInst("+", LoadVarInst(loop, l144), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec115[LoadVarInst(loop, l144)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l145, Int32(0))
		BinopInst("<", LoadVarInst(loop, l145), Int32(3))
		StoreVarInst(loop, l145, BinopInst("+", LoadVarInst(loop, l145), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec114[LoadVarInst(loop, l145)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l146, Int32(0))
		BinopInst("<", LoadVarInst(loop, l146), Int32(3))
		StoreVarInst(loop, l146, BinopInst("+", LoadVarInst(loop, l146), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec113[LoadVarInst(loop, l146)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l147, Int32(0))
		BinopInst("<", LoadVarInst(loop, l147), Int32(3))
		StoreVarInst(loop, l147, BinopInst("+", LoadVarInst(loop, l147), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec112[LoadVarInst(loop, l147)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l148, Int32(0))
		BinopInst("<", LoadVarInst(loop, l148), Int32(2))
		StoreVarInst(loop, l148, BinopInst("+", LoadVarInst(loop, l148), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec111[LoadVarInst(loop, l148)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l149, Int32(0))
		BinopInst("<", LoadVarInst(loop, l149), Int32(3))
		StoreVarInst(loop, l149, BinopInst("+", LoadVarInst(loop, l149), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec124[LoadVarInst(loop, l149)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l150, Int32(0))
		BinopInst("<", LoadVarInst(loop, l150), Int32(3))
		StoreVarInst(loop, l150, BinopInst("+", LoadVarInst(loop, l150), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec123[LoadVarInst(loop, l150)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l151, Int32(0))
		BinopInst("<", LoadVarInst(loop, l151), Int32(3))
		StoreVarInst(loop, l151, BinopInst("+", LoadVarInst(loop, l151), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec122[LoadVarInst(loop, l151)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l152, Int32(0))
		BinopInst("<", LoadVarInst(loop, l152), Int32(3))
		StoreVarInst(loop, l152, BinopInst("+", LoadVarInst(loop, l152), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec121[LoadVarInst(loop, l152)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l153, Int32(0))
		BinopInst("<", LoadVarInst(loop, l153), Int32(3))
		StoreVarInst(loop, l153, BinopInst("+", LoadVarInst(loop, l153), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec120[LoadVarInst(loop, l153)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l154, Int32(0))
		BinopInst("<", LoadVarInst(loop, l154), Int32(3))
		StoreVarInst(loop, l154, BinopInst("+", LoadVarInst(loop, l154), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec119[LoadVarInst(loop, l154)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l155, Int32(0))
		BinopInst("<", LoadVarInst(loop, l155), Int32(2))
		StoreVarInst(loop, l155, BinopInst("+", LoadVarInst(loop, l155), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec118[LoadVarInst(loop, l155)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l156, Int32(0))
		BinopInst("<", LoadVarInst(loop, l156), Int32(3))
		StoreVarInst(loop, l156, BinopInst("+", LoadVarInst(loop, l156), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec131[LoadVarInst(loop, l156)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l157, Int32(0))
		BinopInst("<", LoadVarInst(loop, l157), Int32(3))
		StoreVarInst(loop, l157, BinopInst("+", LoadVarInst(loop, l157), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec130[LoadVarInst(loop, l157)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l158, Int32(0))
		BinopInst("<", LoadVarInst(loop, l158), Int32(3))
		StoreVarInst(loop, l158, BinopInst("+", LoadVarInst(loop, l158), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec129[LoadVarInst(loop, l158)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l159, Int32(0))
		BinopInst("<", LoadVarInst(loop, l159), Int32(3))
		StoreVarInst(loop, l159, BinopInst("+", LoadVarInst(loop, l159), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec128[LoadVarInst(loop, l159)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l160, Int32(0))
		BinopInst("<", LoadVarInst(loop, l160), Int32(3))
		StoreVarInst(loop, l160, BinopInst("+", LoadVarInst(loop, l160), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec127[LoadVarInst(loop, l160)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l161, Int32(0))
		BinopInst("<", LoadVarInst(loop, l161), Int32(3))
		StoreVarInst(loop, l161, BinopInst("+", LoadVarInst(loop, l161), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec126[LoadVarInst(loop, l161)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l162, Int32(0))
		BinopInst("<", LoadVarInst(loop, l162), Int32(2))
		StoreVarInst(loop, l162, BinopInst("+", LoadVarInst(loop, l162), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec125[LoadVarInst(loop, l162)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l163, Int32(0))
		BinopInst("<", LoadVarInst(loop, l163), Int32(3))
		StoreVarInst(loop, l163, BinopInst("+", LoadVarInst(loop, l163), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec138[LoadVarInst(loop, l163)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l164, Int32(0))
		BinopInst("<", LoadVarInst(loop, l164), Int32(3))
		StoreVarInst(loop, l164, BinopInst("+", LoadVarInst(loop, l164), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec137[LoadVarInst(loop, l164)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l165, Int32(0))
		BinopInst("<", LoadVarInst(loop, l165), Int32(3))
		StoreVarInst(loop, l165, BinopInst("+", LoadVarInst(loop, l165), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec136[LoadVarInst(loop, l165)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l166, Int32(0))
		BinopInst("<", LoadVarInst(loop, l166), Int32(3))
		StoreVarInst(loop, l166, BinopInst("+", LoadVarInst(loop, l166), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec135[LoadVarInst(loop, l166)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l167, Int32(0))
		BinopInst("<", LoadVarInst(loop, l167), Int32(3))
		StoreVarInst(loop, l167, BinopInst("+", LoadVarInst(loop, l167), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec134[LoadVarInst(loop, l167)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l168, Int32(0))
		BinopInst("<", LoadVarInst(loop, l168), Int32(3))
		StoreVarInst(loop, l168, BinopInst("+", LoadVarInst(loop, l168), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec133[LoadVarInst(loop, l168)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l169, Int32(0))
		BinopInst("<", LoadVarInst(loop, l169), Int32(2))
		StoreVarInst(loop, l169, BinopInst("+", LoadVarInst(loop, l169), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec132[LoadVarInst(loop, l169)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l170, Int32(0))
		BinopInst("<", LoadVarInst(loop, l170), Int32(3))
		StoreVarInst(loop, l170, BinopInst("+", LoadVarInst(loop, l170), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec145[LoadVarInst(loop, l170)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l171, Int32(0))
		BinopInst("<", LoadVarInst(loop, l171), Int32(3))
		StoreVarInst(loop, l171, BinopInst("+", LoadVarInst(loop, l171), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec144[LoadVarInst(loop, l171)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l172, Int32(0))
		BinopInst("<", LoadVarInst(loop, l172), Int32(3))
		StoreVarInst(loop, l172, BinopInst("+", LoadVarInst(loop, l172), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec143[LoadVarInst(loop, l172)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l173, Int32(0))
		BinopInst("<", LoadVarInst(loop, l173), Int32(3))
		StoreVarInst(loop, l173, BinopInst("+", LoadVarInst(loop, l173), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec142[LoadVarInst(loop, l173)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l174, Int32(0))
		BinopInst("<", LoadVarInst(loop, l174), Int32(3))
		StoreVarInst(loop, l174, BinopInst("+", LoadVarInst(loop, l174), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec141[LoadVarInst(loop, l174)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l175, Int32(0))
		BinopInst("<", LoadVarInst(loop, l175), Int32(3))
		StoreVarInst(loop, l175, BinopInst("+", LoadVarInst(loop, l175), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec140[LoadVarInst(loop, l175)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l176, Int32(0))
		BinopInst("<", LoadVarInst(loop, l176), Int32(2))
		StoreVarInst(loop, l176, BinopInst("+", LoadVarInst(loop, l176), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec139[LoadVarInst(loop, l176)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l177, Int32(0))
		BinopInst("<", LoadVarInst(loop, l177), Int32(3))
		StoreVarInst(loop, l177, BinopInst("+", LoadVarInst(loop, l177), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec152[LoadVarInst(loop, l177)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l178, Int32(0))
		BinopInst("<", LoadVarInst(loop, l178), Int32(3))
		StoreVarInst(loop, l178, BinopInst("+", LoadVarInst(loop, l178), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec151[LoadVarInst(loop, l178)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l179, Int32(0))
		BinopInst("<", LoadVarInst(loop, l179), Int32(3))
		StoreVarInst(loop, l179, BinopInst("+", LoadVarInst(loop, l179), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec150[LoadVarInst(loop, l179)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l180, Int32(0))
		BinopInst("<", LoadVarInst(loop, l180), Int32(3))
		StoreVarInst(loop, l180, BinopInst("+", LoadVarInst(loop, l180), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec149[LoadVarInst(loop, l180)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l181, Int32(0))
		BinopInst("<", LoadVarInst(loop, l181), Int32(3))
		StoreVarInst(loop, l181, BinopInst("+", LoadVarInst(loop, l181), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec148[LoadVarInst(loop, l181)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l182, Int32(0))
		BinopInst("<", LoadVarInst(loop, l182), Int32(3))
		StoreVarInst(loop, l182, BinopInst("+", LoadVarInst(loop, l182), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec147[LoadVarInst(loop, l182)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l183, Int32(0))
		BinopInst("<", LoadVarInst(loop, l183), Int32(2))
		StoreVarInst(loop, l183, BinopInst("+", LoadVarInst(loop, l183), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec146[LoadVarInst(loop, l183)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l184, Int32(0))
		BinopInst("<", LoadVarInst(loop, l184), Int32(3))
		StoreVarInst(loop, l184, BinopInst("+", LoadVarInst(loop, l184), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec159[LoadVarInst(loop, l184)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l185, Int32(0))
		BinopInst("<", LoadVarInst(loop, l185), Int32(3))
		StoreVarInst(loop, l185, BinopInst("+", LoadVarInst(loop, l185), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec158[LoadVarInst(loop, l185)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l186, Int32(0))
		BinopInst("<", LoadVarInst(loop, l186), Int32(3))
		StoreVarInst(loop, l186, BinopInst("+", LoadVarInst(loop, l186), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec157[LoadVarInst(loop, l186)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l187, Int32(0))
		BinopInst("<", LoadVarInst(loop, l187), Int32(3))
		StoreVarInst(loop, l187, BinopInst("+", LoadVarInst(loop, l187), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec156[LoadVarInst(loop, l187)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l188, Int32(0))
		BinopInst("<", LoadVarInst(loop, l188), Int32(3))
		StoreVarInst(loop, l188, BinopInst("+", LoadVarInst(loop, l188), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec155[LoadVarInst(loop, l188)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l189, Int32(0))
		BinopInst("<", LoadVarInst(loop, l189), Int32(3))
		StoreVarInst(loop, l189, BinopInst("+", LoadVarInst(loop, l189), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec154[LoadVarInst(loop, l189)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l190, Int32(0))
		BinopInst("<", LoadVarInst(loop, l190), Int32(2))
		StoreVarInst(loop, l190, BinopInst("+", LoadVarInst(loop, l190), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec153[LoadVarInst(loop, l190)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l191, Int32(0))
		BinopInst("<", LoadVarInst(loop, l191), Int32(3))
		StoreVarInst(loop, l191, BinopInst("+", LoadVarInst(loop, l191), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec166[LoadVarInst(loop, l191)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l192, Int32(0))
		BinopInst("<", LoadVarInst(loop, l192), Int32(3))
		StoreVarInst(loop, l192, BinopInst("+", LoadVarInst(loop, l192), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec165[LoadVarInst(loop, l192)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l193, Int32(0))
		BinopInst("<", LoadVarInst(loop, l193), Int32(3))
		StoreVarInst(loop, l193, BinopInst("+", LoadVarInst(loop, l193), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec164[LoadVarInst(loop, l193)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l194, Int32(0))
		BinopInst("<", LoadVarInst(loop, l194), Int32(3))
		StoreVarInst(loop, l194, BinopInst("+", LoadVarInst(loop, l194), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec163[LoadVarInst(loop, l194)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l195, Int32(0))
		BinopInst("<", LoadVarInst(loop, l195), Int32(3))
		StoreVarInst(loop, l195, BinopInst("+", LoadVarInst(loop, l195), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec162[LoadVarInst(loop, l195)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l196, Int32(0))
		BinopInst("<", LoadVarInst(loop, l196), Int32(3))
		StoreVarInst(loop, l196, BinopInst("+", LoadVarInst(loop, l196), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec161[LoadVarInst(loop, l196)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l197, Int32(0))
		BinopInst("<", LoadVarInst(loop, l197), Int32(2))
		StoreVarInst(loop, l197, BinopInst("+", LoadVarInst(loop, l197), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec160[LoadVarInst(loop, l197)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l198, Int32(0))
		BinopInst("<", LoadVarInst(loop, l198), Int32(3))
		StoreVarInst(loop, l198, BinopInst("+", LoadVarInst(loop, l198), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec173[LoadVarInst(loop, l198)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l199, Int32(0))
		BinopInst("<", LoadVarInst(loop, l199), Int32(3))
		StoreVarInst(loop, l199, BinopInst("+", LoadVarInst(loop, l199), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec172[LoadVarInst(loop, l199)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l200, Int32(0))
		BinopInst("<", LoadVarInst(loop, l200), Int32(3))
		StoreVarInst(loop, l200, BinopInst("+", LoadVarInst(loop, l200), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec171[LoadVarInst(loop, l200)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l201, Int32(0))
		BinopInst("<", LoadVarInst(loop, l201), Int32(3))
		StoreVarInst(loop, l201, BinopInst("+", LoadVarInst(loop, l201), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec170[LoadVarInst(loop, l201)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l202, Int32(0))
		BinopInst("<", LoadVarInst(loop, l202), Int32(3))
		StoreVarInst(loop, l202, BinopInst("+", LoadVarInst(loop, l202), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec169[LoadVarInst(loop, l202)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l203, Int32(0))
		BinopInst("<", LoadVarInst(loop, l203), Int32(3))
		StoreVarInst(loop, l203, BinopInst("+", LoadVarInst(loop, l203), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec168[LoadVarInst(loop, l203)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l204, Int32(0))
		BinopInst("<", LoadVarInst(loop, l204), Int32(2))
		StoreVarInst(loop, l204, BinopInst("+", LoadVarInst(loop, l204), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec167[LoadVarInst(loop, l204)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l205, Int32(0))
		BinopInst("<", LoadVarInst(loop, l205), Int32(3))
		StoreVarInst(loop, l205, BinopInst("+", LoadVarInst(loop, l205), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec180[LoadVarInst(loop, l205)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l206, Int32(0))
		BinopInst("<", LoadVarInst(loop, l206), Int32(3))
		StoreVarInst(loop, l206, BinopInst("+", LoadVarInst(loop, l206), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec179[LoadVarInst(loop, l206)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l207, Int32(0))
		BinopInst("<", LoadVarInst(loop, l207), Int32(3))
		StoreVarInst(loop, l207, BinopInst("+", LoadVarInst(loop, l207), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec178[LoadVarInst(loop, l207)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l208, Int32(0))
		BinopInst("<", LoadVarInst(loop, l208), Int32(3))
		StoreVarInst(loop, l208, BinopInst("+", LoadVarInst(loop, l208), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec177[LoadVarInst(loop, l208)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l209, Int32(0))
		BinopInst("<", LoadVarInst(loop, l209), Int32(3))
		StoreVarInst(loop, l209, BinopInst("+", LoadVarInst(loop, l209), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec176[LoadVarInst(loop, l209)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l210, Int32(0))
		BinopInst("<", LoadVarInst(loop, l210), Int32(3))
		StoreVarInst(loop, l210, BinopInst("+", LoadVarInst(loop, l210), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec175[LoadVarInst(loop, l210)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l211, Int32(0))
		BinopInst("<", LoadVarInst(loop, l211), Int32(2))
		StoreVarInst(loop, l211, BinopInst("+", LoadVarInst(loop, l211), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec174[LoadVarInst(loop, l211)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l212, Int32(0))
		BinopInst("<", LoadVarInst(loop, l212), Int32(3))
		StoreVarInst(loop, l212, BinopInst("+", LoadVarInst(loop, l212), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec187[LoadVarInst(loop, l212)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l213, Int32(0))
		BinopInst("<", LoadVarInst(loop, l213), Int32(3))
		StoreVarInst(loop, l213, BinopInst("+", LoadVarInst(loop, l213), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec186[LoadVarInst(loop, l213)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l214, Int32(0))
		BinopInst("<", LoadVarInst(loop, l214), Int32(3))
		StoreVarInst(loop, l214, BinopInst("+", LoadVarInst(loop, l214), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec185[LoadVarInst(loop, l214)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l215, Int32(0))
		BinopInst("<", LoadVarInst(loop, l215), Int32(3))
		StoreVarInst(loop, l215, BinopInst("+", LoadVarInst(loop, l215), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec184[LoadVarInst(loop, l215)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l216, Int32(0))
		BinopInst("<", LoadVarInst(loop, l216), Int32(3))
		StoreVarInst(loop, l216, BinopInst("+", LoadVarInst(loop, l216), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec183[LoadVarInst(loop, l216)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l217, Int32(0))
		BinopInst("<", LoadVarInst(loop, l217), Int32(3))
		StoreVarInst(loop, l217, BinopInst("+", LoadVarInst(loop, l217), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec182[LoadVarInst(loop, l217)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l218, Int32(0))
		BinopInst("<", LoadVarInst(loop, l218), Int32(2))
		StoreVarInst(loop, l218, BinopInst("+", LoadVarInst(loop, l218), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec181[LoadVarInst(loop, l218)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l219, Int32(0))
		BinopInst("<", LoadVarInst(loop, l219), Int32(3))
		StoreVarInst(loop, l219, BinopInst("+", LoadVarInst(loop, l219), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec194[LoadVarInst(loop, l219)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l220, Int32(0))
		BinopInst("<", LoadVarInst(loop, l220), Int32(3))
		StoreVarInst(loop, l220, BinopInst("+", LoadVarInst(loop, l220), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec193[LoadVarInst(loop, l220)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l221, Int32(0))
		BinopInst("<", LoadVarInst(loop, l221), Int32(3))
		StoreVarInst(loop, l221, BinopInst("+", LoadVarInst(loop, l221), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec192[LoadVarInst(loop, l221)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l222, Int32(0))
		BinopInst("<", LoadVarInst(loop, l222), Int32(3))
		StoreVarInst(loop, l222, BinopInst("+", LoadVarInst(loop, l222), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec191[LoadVarInst(loop, l222)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l223, Int32(0))
		BinopInst("<", LoadVarInst(loop, l223), Int32(3))
		StoreVarInst(loop, l223, BinopInst("+", LoadVarInst(loop, l223), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec190[LoadVarInst(loop, l223)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l224, Int32(0))
		BinopInst("<", LoadVarInst(loop, l224), Int32(3))
		StoreVarInst(loop, l224, BinopInst("+", LoadVarInst(loop, l224), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec189[LoadVarInst(loop, l224)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l225, Int32(0))
		BinopInst("<", LoadVarInst(loop, l225), Int32(2))
		StoreVarInst(loop, l225, BinopInst("+", LoadVarInst(loop, l225), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec188[LoadVarInst(loop, l225)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l226, Int32(0))
		BinopInst("<", LoadVarInst(loop, l226), Int32(3))
		StoreVarInst(loop, l226, BinopInst("+", LoadVarInst(loop, l226), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec201[LoadVarInst(loop, l226)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l227, Int32(0))
		BinopInst("<", LoadVarInst(loop, l227), Int32(3))
		StoreVarInst(loop, l227, BinopInst("+", LoadVarInst(loop, l227), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec200[LoadVarInst(loop, l227)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l228, Int32(0))
		BinopInst("<", LoadVarInst(loop, l228), Int32(3))
		StoreVarInst(loop, l228, BinopInst("+", LoadVarInst(loop, l228), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec199[LoadVarInst(loop, l228)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l229, Int32(0))
		BinopInst("<", LoadVarInst(loop, l229), Int32(3))
		StoreVarInst(loop, l229, BinopInst("+", LoadVarInst(loop, l229), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec198[LoadVarInst(loop, l229)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l230, Int32(0))
		BinopInst("<", LoadVarInst(loop, l230), Int32(3))
		StoreVarInst(loop, l230, BinopInst("+", LoadVarInst(loop, l230), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec197[LoadVarInst(loop, l230)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l231, Int32(0))
		BinopInst("<", LoadVarInst(loop, l231), Int32(3))
		StoreVarInst(loop, l231, BinopInst("+", LoadVarInst(loop, l231), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec196[LoadVarInst(loop, l231)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l232, Int32(0))
		BinopInst("<", LoadVarInst(loop, l232), Int32(2))
		StoreVarInst(loop, l232, BinopInst("+", LoadVarInst(loop, l232), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec195[LoadVarInst(loop, l232)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l233, Int32(0))
		BinopInst("<", LoadVarInst(loop, l233), Int32(3))
		StoreVarInst(loop, l233, BinopInst("+", LoadVarInst(loop, l233), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec205[LoadVarInst(loop, l233)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l234, Int32(0))
		BinopInst("<", LoadVarInst(loop, l234), Int32(3))
		StoreVarInst(loop, l234, BinopInst("+", LoadVarInst(loop, l234), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec204[LoadVarInst(loop, l234)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l235, Int32(0))
		BinopInst("<", LoadVarInst(loop, l235), Int32(3))
		StoreVarInst(loop, l235, BinopInst("+", LoadVarInst(loop, l235), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec203[LoadVarInst(loop, l235)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l236, Int32(0))
		BinopInst("<", LoadVarInst(loop, l236), Int32(2))
		StoreVarInst(loop, l236, BinopInst("+", LoadVarInst(loop, l236), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec202[LoadVarInst(loop, l236)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider0))))))
	DeclareVarInst(stack, "int", iSlow5, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "int", iSlow7, CastInst("int", BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry0)), Float(-1.0f))))
	DeclareVarInst(stack, "int", iSlow8, BinopInst(">=", LoadVarInst(stack, iSlow7), Int32(2)))
	DeclareVarInst(stack, "int", iSlow9, BinopInst(">=", LoadVarInst(stack, iSlow7), Int32(1)))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst72), CastInst("float", LoadVarInst(struct, fVslider2))))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(440.0f), BinopInst("*", FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fVslider1)), Float(-49.0f)))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow10)))))
	DeclareVarInst(stack, "int", iSlow12, BinopInst(">=", LoadVarInst(stack, iSlow7), Int32(3)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("+", BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider3))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("+", BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider4))), Float(1.0f)))
	DeclareVarInst(stack, "int", iSlow15, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox3))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider5))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider6))))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider7))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider8))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider9))))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider10))))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider11))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider12))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider13))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fVslider14))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec29[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec29[Int32(1)]))))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec31[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(struct, fRec31[Int32(0)]))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp0))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("+", LoadVarInst(struct, fRec30[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fVec1[Int32(1)]))))
			StoreVarInst(struct, fRec30[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), FunCallInst("floorf", LoadVarInst(stack, fTemp1))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec30[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp4))
			DeclareVarInst(stack, "float", fTemp5, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fVec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(struct, fVec3[Int32(1)])))), LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp6))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("+", LoadVarInst(stack, fTemp4), Float(-2.0f))))
			StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp7))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec5[Int32(1)])), LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp8))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec6[Int32(1)])), LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp9))
			DeclareVarInst(stack, "float", fTemp10, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec31[Int32(0)])))))
			StoreVarInst(struct, fVec8[Int32(0)], LoadVarInst(stack, fTemp10))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fVec8[Int32(1)]))))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp11), FunCallInst("floorf", LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec32[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fTemp12), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp14, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp13)))
			StoreVarInst(struct, fVec9[Int32(0)], LoadVarInst(stack, fTemp14))
			DeclareVarInst(stack, "float", fTemp15, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp13)))
			StoreVarInst(struct, fVec10[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec10[Int32(1)])))), LoadVarInst(stack, fTemp10)))
			StoreVarInst(struct, fVec11[Int32(0)], LoadVarInst(stack, fTemp16))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", LoadVarInst(stack, fTemp14), Float(-2.0f))))
			StoreVarInst(struct, fVec12[Int32(0)], LoadVarInst(stack, fTemp17))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp17), LoadVarInst(struct, fVec12[Int32(1)])), LoadVarInst(stack, fTemp10)))
			StoreVarInst(struct, fVec13[Int32(0)], LoadVarInst(stack, fTemp18))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fVec13[Int32(1)])), LoadVarInst(stack, fTemp10)))
			StoreVarInst(struct, fVec14[Int32(0)], LoadVarInst(stack, fTemp19))
			DeclareVarInst(stack, "float", fTemp20, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec31[Int32(0)])))))
			StoreVarInst(struct, fVec15[Int32(0)], LoadVarInst(stack, fTemp20))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("+", LoadVarInst(struct, fRec33[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst72), LoadVarInst(struct, fVec15[Int32(1)]))))
			StoreVarInst(struct, fRec33[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp21), FunCallInst("floorf", LoadVarInst(stack, fTemp21))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec33[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("+", LoadVarInst(stack, fTemp22), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp24, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp23)))
			StoreVarInst(struct, fVec16[Int32(0)], LoadVarInst(stack, fTemp24))
			DeclareVarInst(stack, "float", fTemp25, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp23)))
			StoreVarInst(struct, fVec17[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp25), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp22))))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp25), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp22), LoadVarInst(struct, fVec17[Int32(1)])))), LoadVarInst(stack, fTemp20)))
			StoreVarInst(struct, fVec18[Int32(0)], LoadVarInst(stack, fTemp26))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(stack, fTemp24), BinopInst("+", LoadVarInst(stack, fTemp24), Float(-2.0f))))
			StoreVarInst(struct, fVec19[Int32(0)], LoadVarInst(stack, fTemp27))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fVec19[Int32(1)])), LoadVarInst(stack, fTemp20)))
			StoreVarInst(struct, fVec20[Int32(0)], LoadVarInst(stack, fTemp28))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fVec20[Int32(1)])), LoadVarInst(stack, fTemp20)))
			StoreVarInst(struct, fVec21[Int32(0)], LoadVarInst(stack, fTemp29))
			StoreVarInst(struct, iRec34[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec34[Int32(1)])), Int32(12345)))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec34[Int32(0)]))))
			StoreVarInst(struct, fRec35[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.522189379f), LoadVarInst(struct, fRec35[Int32(3)])), BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("*", Float(2.49495602f), LoadVarInst(struct, fRec35[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(struct, fRec35[Int32(2)]))))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("*", LoadVarInst(struct, fRec29[Int32(0)]), Select2Inst(LoadVarInst(stack, iSlow5) CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])) Select2Inst(LoadVarInst(stack, iSlow6) Select2Inst(LoadVarInst(stack, iSlow15) BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0499220341f), LoadVarInst(struct, fRec35[Int32(0)])), BinopInst("*", Float(0.0506126992f), LoadVarInst(struct, fRec35[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.0959935337f), LoadVarInst(struct, fRec35[Int32(1)])), BinopInst("*", Float(0.00440878607f), LoadVarInst(struct, fRec35[Int32(3)])))) LoadVarInst(stack, fTemp30)) BinopInst("*", Float(0.333333343f), BinopInst("*", LoadVarInst(struct, fRec29[Int32(0)]), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow8) Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("*", LoadVarInst(struct, fConst75), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec7[Int32(1)]))), LoadVarInst(stack, fTemp0))) BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec4[Int32(1)]))), LoadVarInst(stack, fTemp0)))) Select2Inst(LoadVarInst(stack, iSlow9) BinopInst("*", LoadVarInst(struct, fConst73), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(struct, fVec2[Int32(1)]))), LoadVarInst(stack, fTemp0))) LoadVarInst(stack, fTemp3))), Select2Inst(LoadVarInst(stack, iSlow8) Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("*", LoadVarInst(struct, fConst75), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp19), LoadVarInst(struct, fVec14[Int32(1)]))), LoadVarInst(stack, fTemp10))) BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp16), LoadVarInst(struct, fVec11[Int32(1)]))), LoadVarInst(stack, fTemp10)))) Select2Inst(LoadVarInst(stack, iSlow9) BinopInst("*", LoadVarInst(struct, fConst73), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp14), LoadVarInst(struct, fVec9[Int32(1)]))), LoadVarInst(stack, fTemp10))) LoadVarInst(stack, fTemp13)))), Select2Inst(LoadVarInst(stack, iSlow8) Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("*", LoadVarInst(struct, fConst75), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp29), LoadVarInst(struct, fVec21[Int32(1)]))), LoadVarInst(stack, fTemp20))) BinopInst("*", LoadVarInst(struct, fConst74), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec18[Int32(1)]))), LoadVarInst(stack, fTemp20)))) Select2Inst(LoadVarInst(stack, iSlow9) BinopInst("*", LoadVarInst(struct, fConst73), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fVec16[Int32(1)]))), LoadVarInst(stack, fTemp20))) LoadVarInst(stack, fTemp23))))))))))
			DeclareVarInst(stack, "float", fTemp32, Select2Inst(LoadVarInst(stack, iSlow3) Float(0.0f) LoadVarInst(stack, fTemp31)))
			StoreVarInst(struct, fVec22[Int32(0)], LoadVarInst(stack, fTemp32))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), BinopInst("+", LoadVarInst(stack, fTemp32), LoadVarInst(struct, fVec22[Int32(1)])))))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec27[Int32(2)]))))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", LoadVarInst(struct, fRec27[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec27[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec27[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst80), LoadVarInst(struct, fRec26[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec26[Int32(1)])))))
			StoreVarInst(struct, fVec23[Int32(0)], LoadVarInst(stack, fTemp33))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst63), LoadVarInst(struct, fRec25[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst67), BinopInst("+", LoadVarInst(stack, fTemp33), LoadVarInst(struct, fVec23[Int32(1)])))))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec25[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst83), LoadVarInst(struct, fRec24[Int32(2)]))))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", LoadVarInst(struct, fRec24[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec24[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec24[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec23[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("+", LoadVarInst(struct, fRec23[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec23[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec23[Int32(1)])))))
			StoreVarInst(struct, fVec24[Int32(0)], LoadVarInst(stack, fTemp34))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst60), BinopInst("+", LoadVarInst(stack, fTemp34), LoadVarInst(struct, fVec24[Int32(1)])))))
			StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec22[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec21[Int32(2)]))))))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", LoadVarInst(struct, fRec21[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec21[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec21[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fRec20[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(struct, fRec20[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec20[Int32(1)])))))
			StoreVarInst(struct, fVec25[Int32(0)], LoadVarInst(stack, fTemp35))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fVec25[Int32(1)])))))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec19[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(struct, fRec18[Int32(2)]))))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", LoadVarInst(struct, fRec18[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec18[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec18[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec17[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(struct, fRec17[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec17[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec17[Int32(1)])))))
			StoreVarInst(struct, fVec26[Int32(0)], LoadVarInst(stack, fTemp36))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst46), BinopInst("+", LoadVarInst(stack, fTemp36), LoadVarInst(struct, fVec26[Int32(1)])))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec15[Int32(2)]))))))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec15[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec15[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst100), LoadVarInst(struct, fRec14[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec14[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec14[Int32(1)])))))
			StoreVarInst(struct, fVec27[Int32(0)], LoadVarInst(stack, fTemp37))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst35), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst39), BinopInst("+", LoadVarInst(stack, fTemp37), LoadVarInst(struct, fVec27[Int32(1)])))))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec13[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst103), LoadVarInst(struct, fRec12[Int32(2)]))))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec12[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec12[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec11[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("+", LoadVarInst(struct, fRec11[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec11[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec11[Int32(1)])))))
			StoreVarInst(struct, fVec28[Int32(0)], LoadVarInst(stack, fTemp38))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst28), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst32), BinopInst("+", LoadVarInst(stack, fTemp38), LoadVarInst(struct, fVec28[Int32(1)])))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec9[Int32(2)]))))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", LoadVarInst(struct, fRec9[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec9[Int32(1)]))))), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fRec8[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("+", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec8[Int32(1)])), LoadVarInst(struct, fRec8[Int32(0)])), LoadVarInst(struct, fRec8[Int32(2)])))
			StoreVarInst(struct, fVec29[Int32(0)], LoadVarInst(stack, fTemp39))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst25), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst15), LoadVarInst(stack, fTemp39)), BinopInst("*", LoadVarInst(struct, fConst111), LoadVarInst(struct, fVec29[Int32(1)])))), BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec7[Int32(1)]))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec7[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst114), LoadVarInst(struct, fRec6[Int32(2)]))))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec6[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec6[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec6[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec5[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec4[Int32(1)])))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst19), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec5[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst18), LoadVarInst(struct, fRec5[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec4[Int32(2)]))))))
			StoreVarInst(struct, fRec36[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow16), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec36[Int32(1)]))))
			StoreVarInst(struct, fRec42[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst112), LoadVarInst(struct, fRec42[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst25), BinopInst("+", LoadVarInst(stack, fTemp39), LoadVarInst(struct, fVec29[Int32(1)])))))
			StoreVarInst(struct, fRec41[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec42[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec41[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst114), LoadVarInst(struct, fRec41[Int32(2)]))))))
			StoreVarInst(struct, fRec40[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst20), BinopInst("+", LoadVarInst(struct, fRec41[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec41[Int32(1)])), LoadVarInst(struct, fRec41[Int32(0)])))), BinopInst("*", LoadVarInst(struct, fConst17), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec40[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst115), LoadVarInst(struct, fRec40[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(struct, fRec40[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec40[Int32(1)])), LoadVarInst(struct, fRec40[Int32(0)]))))
			StoreVarInst(struct, fVec30[Int32(0)], LoadVarInst(stack, fTemp41))
			StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst126), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst127), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst117), LoadVarInst(stack, fTemp41)), BinopInst("*", LoadVarInst(struct, fConst128), LoadVarInst(struct, fVec30[Int32(1)]))))))
			StoreVarInst(struct, fRec38[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec39[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec38[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), LoadVarInst(struct, fRec38[Int32(2)]))))))
			StoreVarInst(struct, fRec37[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec38[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst123), LoadVarInst(struct, fRec38[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec38[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst122), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fRec37[Int32(2)]))))))
			StoreVarInst(struct, fRec43[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow17), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec43[Int32(1)]))))
			StoreVarInst(struct, fRec46[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst126), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst127), BinopInst("+", LoadVarInst(stack, fTemp41), LoadVarInst(struct, fVec30[Int32(1)])))))
			StoreVarInst(struct, fRec45[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec46[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst129), LoadVarInst(struct, fRec45[Int32(2)]))))))
			StoreVarInst(struct, fRec44[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst124), BinopInst("+", LoadVarInst(struct, fRec45[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec45[Int32(1)])), LoadVarInst(struct, fRec45[Int32(0)])))), BinopInst("*", LoadVarInst(struct, fConst122), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec44[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst130), LoadVarInst(struct, fRec44[Int32(2)]))))))
			StoreVarInst(struct, fRec47[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow18), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec47[Int32(1)]))))
			StoreVarInst(struct, fRec58[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst70), LoadVarInst(struct, fRec58[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst71), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst65), LoadVarInst(stack, fTemp32)), BinopInst("*", LoadVarInst(struct, fConst132), LoadVarInst(struct, fVec22[Int32(1)]))))))
			StoreVarInst(struct, fRec57[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec58[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst78), LoadVarInst(struct, fRec57[Int32(2)]))))))
			StoreVarInst(struct, fRec56[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst68), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec57[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec57[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec57[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst77), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst80), LoadVarInst(struct, fRec56[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec55[Int32(1)])))
			StoreVarInst(struct, fRec55[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst79), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst131), LoadVarInst(struct, fRec56[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec56[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst76), LoadVarInst(struct, fRec56[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec55[Int32(2)])), LoadVarInst(stack, fTemp42)))))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec54[Int32(1)])))
			StoreVarInst(struct, fRec54[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec55[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp42), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec55[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec54[Int32(2)])), LoadVarInst(stack, fTemp43)))))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec53[Int32(1)])))
			StoreVarInst(struct, fRec53[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec54[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp43), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec54[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec53[Int32(2)])), LoadVarInst(stack, fTemp44)))))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec52[Int32(1)])))
			StoreVarInst(struct, fRec52[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec53[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp44), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec53[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec52[Int32(2)])), LoadVarInst(stack, fTemp45)))))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec51[Int32(1)])))
			StoreVarInst(struct, fRec51[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec52[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp45), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec52[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec51[Int32(2)])), LoadVarInst(stack, fTemp46)))))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec50[Int32(1)])))
			StoreVarInst(struct, fRec50[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec51[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp46), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec51[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec50[Int32(2)])), LoadVarInst(stack, fTemp47)))))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec49[Int32(1)])))
			StoreVarInst(struct, fRec49[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec50[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp47), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec50[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec49[Int32(2)])), LoadVarInst(stack, fTemp48)))))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec48[Int32(1)])))
			StoreVarInst(struct, fRec48[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec49[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", LoadVarInst(stack, fTemp48), BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec49[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst145), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst146), LoadVarInst(struct, fRec48[Int32(2)])), LoadVarInst(stack, fTemp49)))))
			StoreVarInst(struct, fRec59[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow19), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec59[Int32(1)]))))
			StoreVarInst(struct, fRec69[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst63), LoadVarInst(struct, fRec69[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst67), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst58), LoadVarInst(stack, fTemp33)), BinopInst("*", LoadVarInst(struct, fConst148), LoadVarInst(struct, fVec23[Int32(1)]))))))
			StoreVarInst(struct, fRec68[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec69[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec68[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst83), LoadVarInst(struct, fRec68[Int32(2)]))))))
			StoreVarInst(struct, fRec67[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst61), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec68[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst147), LoadVarInst(struct, fRec68[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec68[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst82), LoadVarInst(struct, fRec67[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst85), LoadVarInst(struct, fRec67[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec66[Int32(1)])))
			StoreVarInst(struct, fRec66[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst84), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst147), LoadVarInst(struct, fRec67[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec67[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst81), LoadVarInst(struct, fRec67[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp50), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec66[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec65[Int32(1)])))
			StoreVarInst(struct, fRec65[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec66[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp50), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec66[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp51), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec65[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp52, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec64[Int32(1)])))
			StoreVarInst(struct, fRec64[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec65[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp51), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec65[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp52), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec64[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec63[Int32(1)])))
			StoreVarInst(struct, fRec63[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec64[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp52), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec64[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp53), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec63[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec62[Int32(1)])))
			StoreVarInst(struct, fRec62[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec63[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp53), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec63[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp54), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec62[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec61[Int32(1)])))
			StoreVarInst(struct, fRec61[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec62[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp54), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec62[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp55), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec61[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec60[Int32(1)])))
			StoreVarInst(struct, fRec60[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec61[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp55), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec61[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec60[Int32(2)]))))))
			StoreVarInst(struct, fRec70[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec70[Int32(1)]))))
			StoreVarInst(struct, fRec79[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst56), LoadVarInst(struct, fRec79[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst60), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst51), LoadVarInst(stack, fTemp34)), BinopInst("*", LoadVarInst(struct, fConst150), LoadVarInst(struct, fVec24[Int32(1)]))))))
			StoreVarInst(struct, fRec78[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec79[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec78[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst88), LoadVarInst(struct, fRec78[Int32(2)]))))))
			StoreVarInst(struct, fRec77[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst54), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec78[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst149), LoadVarInst(struct, fRec78[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec78[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst87), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst90), LoadVarInst(struct, fRec77[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec76[Int32(1)])))
			StoreVarInst(struct, fRec76[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst89), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst149), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec77[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst86), LoadVarInst(struct, fRec77[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp57), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec76[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec75[Int32(1)])))
			StoreVarInst(struct, fRec75[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec76[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp57), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec76[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec75[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp59, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec74[Int32(1)])))
			StoreVarInst(struct, fRec74[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec75[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec75[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec74[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec73[Int32(1)])))
			StoreVarInst(struct, fRec73[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec74[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec74[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec73[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp61, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec72[Int32(1)])))
			StoreVarInst(struct, fRec72[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec73[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec73[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp61), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec72[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp62, BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec71[Int32(1)])))
			StoreVarInst(struct, fRec71[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec72[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp61), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec72[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp62), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec71[Int32(2)]))))))
			StoreVarInst(struct, fRec80[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow21), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec80[Int32(1)]))))
			StoreVarInst(struct, fRec88[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst49), LoadVarInst(struct, fRec88[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst53), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst44), LoadVarInst(stack, fTemp35)), BinopInst("*", LoadVarInst(struct, fConst152), LoadVarInst(struct, fVec25[Int32(1)]))))))
			StoreVarInst(struct, fRec87[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec88[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec87[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst93), LoadVarInst(struct, fRec87[Int32(2)]))))))
			StoreVarInst(struct, fRec86[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst47), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec87[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst151), LoadVarInst(struct, fRec87[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec87[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst92), LoadVarInst(struct, fRec86[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst95), LoadVarInst(struct, fRec86[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp63, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec85[Int32(1)])))
			StoreVarInst(struct, fRec85[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst94), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst151), LoadVarInst(struct, fRec86[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec86[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst91), LoadVarInst(struct, fRec86[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec85[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec84[Int32(1)])))
			StoreVarInst(struct, fRec84[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec85[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec85[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp64), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec84[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp65, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec83[Int32(1)])))
			StoreVarInst(struct, fRec83[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec84[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp64), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec84[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp65), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec83[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp66, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec82[Int32(1)])))
			StoreVarInst(struct, fRec82[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec83[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp65), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec83[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp66), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec82[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp67, BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec81[Int32(1)])))
			StoreVarInst(struct, fRec81[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec82[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp66), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec82[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp67), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec81[Int32(2)]))))))
			StoreVarInst(struct, fRec89[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow22), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec89[Int32(1)]))))
			StoreVarInst(struct, fRec96[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst42), LoadVarInst(struct, fRec96[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst46), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst37), LoadVarInst(stack, fTemp36)), BinopInst("*", LoadVarInst(struct, fConst154), LoadVarInst(struct, fVec26[Int32(1)]))))))
			StoreVarInst(struct, fRec95[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec96[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec95[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst98), LoadVarInst(struct, fRec95[Int32(2)]))))))
			StoreVarInst(struct, fRec94[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst40), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec95[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst153), LoadVarInst(struct, fRec95[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec95[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst97), LoadVarInst(struct, fRec94[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst100), LoadVarInst(struct, fRec94[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp68, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec93[Int32(1)])))
			StoreVarInst(struct, fRec93[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst99), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst153), LoadVarInst(struct, fRec94[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec94[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst96), LoadVarInst(struct, fRec94[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp68), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec93[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp69, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec92[Int32(1)])))
			StoreVarInst(struct, fRec92[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec93[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp68), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec93[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp69), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec92[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp70, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec91[Int32(1)])))
			StoreVarInst(struct, fRec91[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec92[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp69), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec92[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp70), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec91[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp71, BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec90[Int32(1)])))
			StoreVarInst(struct, fRec90[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec91[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp70), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec91[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp71), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec90[Int32(2)]))))))
			StoreVarInst(struct, fRec97[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow23), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec97[Int32(1)]))))
			StoreVarInst(struct, fRec103[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst35), LoadVarInst(struct, fRec103[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst39), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst30), LoadVarInst(stack, fTemp37)), BinopInst("*", LoadVarInst(struct, fConst156), LoadVarInst(struct, fVec27[Int32(1)]))))))
			StoreVarInst(struct, fRec102[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec103[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec102[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst103), LoadVarInst(struct, fRec102[Int32(2)]))))))
			StoreVarInst(struct, fRec101[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst33), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec102[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst155), LoadVarInst(struct, fRec102[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec102[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst102), LoadVarInst(struct, fRec101[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst105), LoadVarInst(struct, fRec101[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp72, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec100[Int32(1)])))
			StoreVarInst(struct, fRec100[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst104), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst155), LoadVarInst(struct, fRec101[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec101[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst101), LoadVarInst(struct, fRec101[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp72), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec100[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp73, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec99[Int32(1)])))
			StoreVarInst(struct, fRec99[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec100[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp72), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec100[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp73), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec99[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp74, BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec98[Int32(1)])))
			StoreVarInst(struct, fRec98[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec99[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp73), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec99[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp74), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec98[Int32(2)]))))))
			StoreVarInst(struct, fRec104[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow24), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec104[Int32(1)]))))
			StoreVarInst(struct, fRec109[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst28), LoadVarInst(struct, fRec109[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst32), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst22), LoadVarInst(stack, fTemp38)), BinopInst("*", LoadVarInst(struct, fConst158), LoadVarInst(struct, fVec28[Int32(1)]))))))
			StoreVarInst(struct, fRec108[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec109[Int32(0)]), BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec108[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst108), LoadVarInst(struct, fRec108[Int32(2)]))))))
			StoreVarInst(struct, fRec107[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst26), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec108[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst157), LoadVarInst(struct, fRec108[Int32(1)]))), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec108[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst107), LoadVarInst(struct, fRec107[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst110), LoadVarInst(struct, fRec107[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp75, BinopInst("*", LoadVarInst(struct, fConst120), LoadVarInst(struct, fRec106[Int32(1)])))
			StoreVarInst(struct, fRec106[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst109), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst157), LoadVarInst(struct, fRec107[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec107[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst106), LoadVarInst(struct, fRec107[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp75), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec106[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp76, BinopInst("*", LoadVarInst(struct, fConst113), LoadVarInst(struct, fRec105[Int32(1)])))
			StoreVarInst(struct, fRec105[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec106[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp75), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec106[Int32(0)]))))), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp76), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec105[Int32(2)]))))))
			StoreVarInst(struct, fRec110[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow25), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec110[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp77, Select2Inst(LoadVarInst(stack, iSlow3) LoadVarInst(stack, fTemp31) BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec4[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst118), BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", LoadVarInst(struct, fConst121), LoadVarInst(struct, fRec4[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec36[Int32(0)])))), BinopInst("*", LoadVarInst(struct, fConst122), BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst123), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec37[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst119), LoadVarInst(struct, fRec37[Int32(2)]))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec43[Int32(0)])))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec44[Int32(2)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec44[Int32(1)])), LoadVarInst(struct, fRec44[Int32(0)]))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec47[Int32(0)]))))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec48[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst145), BinopInst("+", LoadVarInst(stack, fTemp49), BinopInst("*", LoadVarInst(struct, fConst146), LoadVarInst(struct, fRec48[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec59[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec60[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst143), BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("*", LoadVarInst(struct, fConst144), LoadVarInst(struct, fRec60[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec70[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec71[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst141), BinopInst("+", LoadVarInst(stack, fTemp62), BinopInst("*", LoadVarInst(struct, fConst142), LoadVarInst(struct, fRec71[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec80[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec81[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst139), BinopInst("+", LoadVarInst(stack, fTemp67), BinopInst("*", LoadVarInst(struct, fConst140), LoadVarInst(struct, fRec81[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec89[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec90[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst137), BinopInst("+", LoadVarInst(stack, fTemp71), BinopInst("*", LoadVarInst(struct, fConst138), LoadVarInst(struct, fRec90[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec97[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec98[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst135), BinopInst("+", LoadVarInst(stack, fTemp74), BinopInst("*", LoadVarInst(struct, fConst136), LoadVarInst(struct, fRec98[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec104[Int32(0)]))))), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec105[Int32(2)]), BinopInst("*", LoadVarInst(struct, fConst133), BinopInst("+", LoadVarInst(stack, fTemp76), BinopInst("*", LoadVarInst(struct, fConst134), LoadVarInst(struct, fRec105[Int32(0)]))))), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec110[Int32(0)])))))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp77), BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst159), LoadVarInst(struct, fRec3[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst161), LoadVarInst(struct, fRec3[Int32(1)]))))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst13), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst162), LoadVarInst(struct, fRec3[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst162), LoadVarInst(struct, fRec3[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst8), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst163), LoadVarInst(struct, fRec2[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst164), LoadVarInst(struct, fRec2[Int32(1)]))))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst8), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst10), LoadVarInst(struct, fRec2[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst165), LoadVarInst(struct, fRec2[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst165), LoadVarInst(struct, fRec2[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst166), LoadVarInst(struct, fRec1[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst167), LoadVarInst(struct, fRec1[Int32(1)]))))))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst168), LoadVarInst(struct, fRec1[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst168), LoadVarInst(struct, fRec1[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec0[Int32(0)])))))))
			StoreVarInst(struct, fRec117[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp77), BinopInst("*", LoadVarInst(struct, fConst185), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst188), LoadVarInst(struct, fRec117[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst189), LoadVarInst(struct, fRec117[Int32(1)]))))))
			StoreVarInst(struct, fRec116[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst185), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst187), LoadVarInst(struct, fRec117[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst190), LoadVarInst(struct, fRec117[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst190), LoadVarInst(struct, fRec117[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst183), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst191), LoadVarInst(struct, fRec116[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst192), LoadVarInst(struct, fRec116[Int32(1)]))))))
			StoreVarInst(struct, fRec115[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst183), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst184), LoadVarInst(struct, fRec116[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst193), LoadVarInst(struct, fRec116[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst193), LoadVarInst(struct, fRec116[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst181), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst194), LoadVarInst(struct, fRec115[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst195), LoadVarInst(struct, fRec115[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp78, BinopInst("*", LoadVarInst(struct, fConst181), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst182), LoadVarInst(struct, fRec115[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst196), LoadVarInst(struct, fRec115[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst196), LoadVarInst(struct, fRec115[Int32(2)])))))
			StoreVarInst(struct, fRec114[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp78), BinopInst("*", LoadVarInst(struct, fConst178), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst197), LoadVarInst(struct, fRec114[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst199), LoadVarInst(struct, fRec114[Int32(1)]))))))
			StoreVarInst(struct, fRec113[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst178), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst180), LoadVarInst(struct, fRec114[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst200), LoadVarInst(struct, fRec114[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst200), LoadVarInst(struct, fRec114[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst175), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst201), LoadVarInst(struct, fRec113[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst202), LoadVarInst(struct, fRec113[Int32(1)]))))))
			StoreVarInst(struct, fRec112[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst175), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst177), LoadVarInst(struct, fRec113[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst203), LoadVarInst(struct, fRec113[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst203), LoadVarInst(struct, fRec113[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst171), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst204), LoadVarInst(struct, fRec112[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst205), LoadVarInst(struct, fRec112[Int32(1)]))))))
			StoreVarInst(struct, fRec111[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec111[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst171), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst174), LoadVarInst(struct, fRec112[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst206), LoadVarInst(struct, fRec112[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst206), LoadVarInst(struct, fRec112[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec111[Int32(0)])))))))
			StoreVarInst(struct, fRec124[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp78), BinopInst("*", LoadVarInst(struct, fConst223), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst226), LoadVarInst(struct, fRec124[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst227), LoadVarInst(struct, fRec124[Int32(1)]))))))
			StoreVarInst(struct, fRec123[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst223), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst225), LoadVarInst(struct, fRec124[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst228), LoadVarInst(struct, fRec124[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst228), LoadVarInst(struct, fRec124[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst221), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst229), LoadVarInst(struct, fRec123[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst230), LoadVarInst(struct, fRec123[Int32(1)]))))))
			StoreVarInst(struct, fRec122[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst221), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst222), LoadVarInst(struct, fRec123[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst231), LoadVarInst(struct, fRec123[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst231), LoadVarInst(struct, fRec123[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst219), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst232), LoadVarInst(struct, fRec122[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst233), LoadVarInst(struct, fRec122[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp79, BinopInst("*", LoadVarInst(struct, fConst219), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst220), LoadVarInst(struct, fRec122[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst234), LoadVarInst(struct, fRec122[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst234), LoadVarInst(struct, fRec122[Int32(2)])))))
			StoreVarInst(struct, fRec121[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp79), BinopInst("*", LoadVarInst(struct, fConst216), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst235), LoadVarInst(struct, fRec121[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst237), LoadVarInst(struct, fRec121[Int32(1)]))))))
			StoreVarInst(struct, fRec120[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst216), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst218), LoadVarInst(struct, fRec121[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst238), LoadVarInst(struct, fRec121[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst238), LoadVarInst(struct, fRec121[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst213), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst239), LoadVarInst(struct, fRec120[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst240), LoadVarInst(struct, fRec120[Int32(1)]))))))
			StoreVarInst(struct, fRec119[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst213), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst215), LoadVarInst(struct, fRec120[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst241), LoadVarInst(struct, fRec120[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst241), LoadVarInst(struct, fRec120[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst209), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst242), LoadVarInst(struct, fRec119[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst243), LoadVarInst(struct, fRec119[Int32(1)]))))))
			StoreVarInst(struct, fRec118[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec118[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst209), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst212), LoadVarInst(struct, fRec119[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst244), LoadVarInst(struct, fRec119[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst244), LoadVarInst(struct, fRec119[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec118[Int32(0)])))))))
			StoreVarInst(struct, fRec131[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp79), BinopInst("*", LoadVarInst(struct, fConst261), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst264), LoadVarInst(struct, fRec131[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst265), LoadVarInst(struct, fRec131[Int32(1)]))))))
			StoreVarInst(struct, fRec130[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst261), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst263), LoadVarInst(struct, fRec131[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst266), LoadVarInst(struct, fRec131[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst266), LoadVarInst(struct, fRec131[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst259), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst267), LoadVarInst(struct, fRec130[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst268), LoadVarInst(struct, fRec130[Int32(1)]))))))
			StoreVarInst(struct, fRec129[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst259), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst260), LoadVarInst(struct, fRec130[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst269), LoadVarInst(struct, fRec130[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst269), LoadVarInst(struct, fRec130[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst257), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst270), LoadVarInst(struct, fRec129[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst271), LoadVarInst(struct, fRec129[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp80, BinopInst("*", LoadVarInst(struct, fConst257), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst258), LoadVarInst(struct, fRec129[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst272), LoadVarInst(struct, fRec129[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst272), LoadVarInst(struct, fRec129[Int32(2)])))))
			StoreVarInst(struct, fRec128[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp80), BinopInst("*", LoadVarInst(struct, fConst254), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst273), LoadVarInst(struct, fRec128[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst275), LoadVarInst(struct, fRec128[Int32(1)]))))))
			StoreVarInst(struct, fRec127[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst254), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst256), LoadVarInst(struct, fRec128[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst276), LoadVarInst(struct, fRec128[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst276), LoadVarInst(struct, fRec128[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst251), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst277), LoadVarInst(struct, fRec127[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst278), LoadVarInst(struct, fRec127[Int32(1)]))))))
			StoreVarInst(struct, fRec126[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst251), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst253), LoadVarInst(struct, fRec127[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst279), LoadVarInst(struct, fRec127[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst279), LoadVarInst(struct, fRec127[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst247), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst280), LoadVarInst(struct, fRec126[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst281), LoadVarInst(struct, fRec126[Int32(1)]))))))
			StoreVarInst(struct, fRec125[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec125[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst247), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst250), LoadVarInst(struct, fRec126[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst282), LoadVarInst(struct, fRec126[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst282), LoadVarInst(struct, fRec126[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec125[Int32(0)])))))))
			StoreVarInst(struct, fRec138[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp80), BinopInst("*", LoadVarInst(struct, fConst299), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst302), LoadVarInst(struct, fRec138[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst303), LoadVarInst(struct, fRec138[Int32(1)]))))))
			StoreVarInst(struct, fRec137[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst299), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst301), LoadVarInst(struct, fRec138[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst304), LoadVarInst(struct, fRec138[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst304), LoadVarInst(struct, fRec138[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst297), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst305), LoadVarInst(struct, fRec137[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst306), LoadVarInst(struct, fRec137[Int32(1)]))))))
			StoreVarInst(struct, fRec136[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst297), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst298), LoadVarInst(struct, fRec137[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst307), LoadVarInst(struct, fRec137[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst307), LoadVarInst(struct, fRec137[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst295), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst308), LoadVarInst(struct, fRec136[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst309), LoadVarInst(struct, fRec136[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp81, BinopInst("*", LoadVarInst(struct, fConst295), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst296), LoadVarInst(struct, fRec136[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst310), LoadVarInst(struct, fRec136[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst310), LoadVarInst(struct, fRec136[Int32(2)])))))
			StoreVarInst(struct, fRec135[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp81), BinopInst("*", LoadVarInst(struct, fConst292), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst311), LoadVarInst(struct, fRec135[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst313), LoadVarInst(struct, fRec135[Int32(1)]))))))
			StoreVarInst(struct, fRec134[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst292), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst294), LoadVarInst(struct, fRec135[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst314), LoadVarInst(struct, fRec135[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst314), LoadVarInst(struct, fRec135[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst289), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst315), LoadVarInst(struct, fRec134[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst316), LoadVarInst(struct, fRec134[Int32(1)]))))))
			StoreVarInst(struct, fRec133[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst289), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst291), LoadVarInst(struct, fRec134[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst317), LoadVarInst(struct, fRec134[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst317), LoadVarInst(struct, fRec134[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst285), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst318), LoadVarInst(struct, fRec133[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst319), LoadVarInst(struct, fRec133[Int32(1)]))))))
			StoreVarInst(struct, fRec132[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec132[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst285), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst288), LoadVarInst(struct, fRec133[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst320), LoadVarInst(struct, fRec133[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst320), LoadVarInst(struct, fRec133[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec132[Int32(0)])))))))
			StoreVarInst(struct, fRec145[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp81), BinopInst("*", LoadVarInst(struct, fConst337), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst340), LoadVarInst(struct, fRec145[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst341), LoadVarInst(struct, fRec145[Int32(1)]))))))
			StoreVarInst(struct, fRec144[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst337), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst339), LoadVarInst(struct, fRec145[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst342), LoadVarInst(struct, fRec145[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst342), LoadVarInst(struct, fRec145[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst335), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst343), LoadVarInst(struct, fRec144[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst344), LoadVarInst(struct, fRec144[Int32(1)]))))))
			StoreVarInst(struct, fRec143[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst335), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst336), LoadVarInst(struct, fRec144[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst345), LoadVarInst(struct, fRec144[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst345), LoadVarInst(struct, fRec144[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst333), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst346), LoadVarInst(struct, fRec143[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst347), LoadVarInst(struct, fRec143[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp82, BinopInst("*", LoadVarInst(struct, fConst333), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst334), LoadVarInst(struct, fRec143[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst348), LoadVarInst(struct, fRec143[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst348), LoadVarInst(struct, fRec143[Int32(2)])))))
			StoreVarInst(struct, fRec142[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp82), BinopInst("*", LoadVarInst(struct, fConst330), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst349), LoadVarInst(struct, fRec142[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst351), LoadVarInst(struct, fRec142[Int32(1)]))))))
			StoreVarInst(struct, fRec141[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst330), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst332), LoadVarInst(struct, fRec142[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst352), LoadVarInst(struct, fRec142[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst352), LoadVarInst(struct, fRec142[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst327), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst353), LoadVarInst(struct, fRec141[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst354), LoadVarInst(struct, fRec141[Int32(1)]))))))
			StoreVarInst(struct, fRec140[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst327), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst329), LoadVarInst(struct, fRec141[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst355), LoadVarInst(struct, fRec141[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst355), LoadVarInst(struct, fRec141[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst323), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst356), LoadVarInst(struct, fRec140[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst357), LoadVarInst(struct, fRec140[Int32(1)]))))))
			StoreVarInst(struct, fRec139[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec139[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst323), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst326), LoadVarInst(struct, fRec140[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst358), LoadVarInst(struct, fRec140[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst358), LoadVarInst(struct, fRec140[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec139[Int32(0)])))))))
			StoreVarInst(struct, fRec152[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp82), BinopInst("*", LoadVarInst(struct, fConst375), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst378), LoadVarInst(struct, fRec152[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst379), LoadVarInst(struct, fRec152[Int32(1)]))))))
			StoreVarInst(struct, fRec151[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst375), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst377), LoadVarInst(struct, fRec152[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst380), LoadVarInst(struct, fRec152[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst380), LoadVarInst(struct, fRec152[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst373), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst381), LoadVarInst(struct, fRec151[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst382), LoadVarInst(struct, fRec151[Int32(1)]))))))
			StoreVarInst(struct, fRec150[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst373), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst374), LoadVarInst(struct, fRec151[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst383), LoadVarInst(struct, fRec151[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst383), LoadVarInst(struct, fRec151[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst371), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst384), LoadVarInst(struct, fRec150[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst385), LoadVarInst(struct, fRec150[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp83, BinopInst("*", LoadVarInst(struct, fConst371), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst372), LoadVarInst(struct, fRec150[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst386), LoadVarInst(struct, fRec150[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst386), LoadVarInst(struct, fRec150[Int32(2)])))))
			StoreVarInst(struct, fRec149[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp83), BinopInst("*", LoadVarInst(struct, fConst368), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst387), LoadVarInst(struct, fRec149[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst389), LoadVarInst(struct, fRec149[Int32(1)]))))))
			StoreVarInst(struct, fRec148[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst368), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst370), LoadVarInst(struct, fRec149[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst390), LoadVarInst(struct, fRec149[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst390), LoadVarInst(struct, fRec149[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst365), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst391), LoadVarInst(struct, fRec148[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst392), LoadVarInst(struct, fRec148[Int32(1)]))))))
			StoreVarInst(struct, fRec147[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst365), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst367), LoadVarInst(struct, fRec148[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst393), LoadVarInst(struct, fRec148[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst393), LoadVarInst(struct, fRec148[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst361), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst394), LoadVarInst(struct, fRec147[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst395), LoadVarInst(struct, fRec147[Int32(1)]))))))
			StoreVarInst(struct, fRec146[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec146[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst361), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst364), LoadVarInst(struct, fRec147[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst396), LoadVarInst(struct, fRec147[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst396), LoadVarInst(struct, fRec147[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec146[Int32(0)])))))))
			StoreVarInst(struct, fRec159[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp83), BinopInst("*", LoadVarInst(struct, fConst413), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst416), LoadVarInst(struct, fRec159[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst417), LoadVarInst(struct, fRec159[Int32(1)]))))))
			StoreVarInst(struct, fRec158[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst413), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst415), LoadVarInst(struct, fRec159[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst418), LoadVarInst(struct, fRec159[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst418), LoadVarInst(struct, fRec159[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst411), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst419), LoadVarInst(struct, fRec158[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst420), LoadVarInst(struct, fRec158[Int32(1)]))))))
			StoreVarInst(struct, fRec157[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst411), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst412), LoadVarInst(struct, fRec158[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst421), LoadVarInst(struct, fRec158[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst421), LoadVarInst(struct, fRec158[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst409), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst422), LoadVarInst(struct, fRec157[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst423), LoadVarInst(struct, fRec157[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp84, BinopInst("*", LoadVarInst(struct, fConst409), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst410), LoadVarInst(struct, fRec157[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst424), LoadVarInst(struct, fRec157[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst424), LoadVarInst(struct, fRec157[Int32(2)])))))
			StoreVarInst(struct, fRec156[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp84), BinopInst("*", LoadVarInst(struct, fConst406), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst425), LoadVarInst(struct, fRec156[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst427), LoadVarInst(struct, fRec156[Int32(1)]))))))
			StoreVarInst(struct, fRec155[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst406), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst408), LoadVarInst(struct, fRec156[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst428), LoadVarInst(struct, fRec156[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst428), LoadVarInst(struct, fRec156[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst403), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst429), LoadVarInst(struct, fRec155[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst430), LoadVarInst(struct, fRec155[Int32(1)]))))))
			StoreVarInst(struct, fRec154[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst403), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst405), LoadVarInst(struct, fRec155[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst431), LoadVarInst(struct, fRec155[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst431), LoadVarInst(struct, fRec155[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst399), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst432), LoadVarInst(struct, fRec154[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst433), LoadVarInst(struct, fRec154[Int32(1)]))))))
			StoreVarInst(struct, fRec153[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec153[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst399), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst402), LoadVarInst(struct, fRec154[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst434), LoadVarInst(struct, fRec154[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst434), LoadVarInst(struct, fRec154[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec153[Int32(0)])))))))
			StoreVarInst(struct, fRec166[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp84), BinopInst("*", LoadVarInst(struct, fConst451), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst454), LoadVarInst(struct, fRec166[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst455), LoadVarInst(struct, fRec166[Int32(1)]))))))
			StoreVarInst(struct, fRec165[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst451), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst453), LoadVarInst(struct, fRec166[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst456), LoadVarInst(struct, fRec166[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst456), LoadVarInst(struct, fRec166[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst449), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst457), LoadVarInst(struct, fRec165[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst458), LoadVarInst(struct, fRec165[Int32(1)]))))))
			StoreVarInst(struct, fRec164[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst449), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst450), LoadVarInst(struct, fRec165[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst459), LoadVarInst(struct, fRec165[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst459), LoadVarInst(struct, fRec165[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst447), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst460), LoadVarInst(struct, fRec164[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst461), LoadVarInst(struct, fRec164[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp85, BinopInst("*", LoadVarInst(struct, fConst447), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst448), LoadVarInst(struct, fRec164[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst462), LoadVarInst(struct, fRec164[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst462), LoadVarInst(struct, fRec164[Int32(2)])))))
			StoreVarInst(struct, fRec163[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp85), BinopInst("*", LoadVarInst(struct, fConst444), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst463), LoadVarInst(struct, fRec163[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst465), LoadVarInst(struct, fRec163[Int32(1)]))))))
			StoreVarInst(struct, fRec162[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst444), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst446), LoadVarInst(struct, fRec163[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst466), LoadVarInst(struct, fRec163[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst466), LoadVarInst(struct, fRec163[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst441), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst467), LoadVarInst(struct, fRec162[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst468), LoadVarInst(struct, fRec162[Int32(1)]))))))
			StoreVarInst(struct, fRec161[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst441), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst443), LoadVarInst(struct, fRec162[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst469), LoadVarInst(struct, fRec162[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst469), LoadVarInst(struct, fRec162[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst437), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst470), LoadVarInst(struct, fRec161[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst471), LoadVarInst(struct, fRec161[Int32(1)]))))))
			StoreVarInst(struct, fRec160[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec160[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst437), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst440), LoadVarInst(struct, fRec161[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst472), LoadVarInst(struct, fRec161[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst472), LoadVarInst(struct, fRec161[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph8, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec160[Int32(0)])))))))
			StoreVarInst(struct, fRec173[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp85), BinopInst("*", LoadVarInst(struct, fConst489), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst492), LoadVarInst(struct, fRec173[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst493), LoadVarInst(struct, fRec173[Int32(1)]))))))
			StoreVarInst(struct, fRec172[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst489), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst491), LoadVarInst(struct, fRec173[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst494), LoadVarInst(struct, fRec173[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst494), LoadVarInst(struct, fRec173[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst487), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst495), LoadVarInst(struct, fRec172[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst496), LoadVarInst(struct, fRec172[Int32(1)]))))))
			StoreVarInst(struct, fRec171[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst487), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst488), LoadVarInst(struct, fRec172[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst497), LoadVarInst(struct, fRec172[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst497), LoadVarInst(struct, fRec172[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst485), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst498), LoadVarInst(struct, fRec171[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst499), LoadVarInst(struct, fRec171[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp86, BinopInst("*", LoadVarInst(struct, fConst485), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst486), LoadVarInst(struct, fRec171[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst500), LoadVarInst(struct, fRec171[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst500), LoadVarInst(struct, fRec171[Int32(2)])))))
			StoreVarInst(struct, fRec170[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp86), BinopInst("*", LoadVarInst(struct, fConst482), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst501), LoadVarInst(struct, fRec170[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst503), LoadVarInst(struct, fRec170[Int32(1)]))))))
			StoreVarInst(struct, fRec169[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst482), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst484), LoadVarInst(struct, fRec170[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst504), LoadVarInst(struct, fRec170[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst504), LoadVarInst(struct, fRec170[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst479), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst505), LoadVarInst(struct, fRec169[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst506), LoadVarInst(struct, fRec169[Int32(1)]))))))
			StoreVarInst(struct, fRec168[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst479), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst481), LoadVarInst(struct, fRec169[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst507), LoadVarInst(struct, fRec169[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst507), LoadVarInst(struct, fRec169[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst475), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst508), LoadVarInst(struct, fRec168[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst509), LoadVarInst(struct, fRec168[Int32(1)]))))))
			StoreVarInst(struct, fRec167[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec167[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst475), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst478), LoadVarInst(struct, fRec168[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst510), LoadVarInst(struct, fRec168[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst510), LoadVarInst(struct, fRec168[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph9, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec167[Int32(0)])))))))
			StoreVarInst(struct, fRec180[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp86), BinopInst("*", LoadVarInst(struct, fConst527), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst530), LoadVarInst(struct, fRec180[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst531), LoadVarInst(struct, fRec180[Int32(1)]))))))
			StoreVarInst(struct, fRec179[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst527), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst529), LoadVarInst(struct, fRec180[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst532), LoadVarInst(struct, fRec180[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst532), LoadVarInst(struct, fRec180[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst525), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst533), LoadVarInst(struct, fRec179[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst534), LoadVarInst(struct, fRec179[Int32(1)]))))))
			StoreVarInst(struct, fRec178[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst525), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst526), LoadVarInst(struct, fRec179[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst535), LoadVarInst(struct, fRec179[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst535), LoadVarInst(struct, fRec179[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst523), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst536), LoadVarInst(struct, fRec178[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst537), LoadVarInst(struct, fRec178[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp87, BinopInst("*", LoadVarInst(struct, fConst523), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst524), LoadVarInst(struct, fRec178[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst538), LoadVarInst(struct, fRec178[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst538), LoadVarInst(struct, fRec178[Int32(2)])))))
			StoreVarInst(struct, fRec177[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp87), BinopInst("*", LoadVarInst(struct, fConst520), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst539), LoadVarInst(struct, fRec177[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst541), LoadVarInst(struct, fRec177[Int32(1)]))))))
			StoreVarInst(struct, fRec176[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst520), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst522), LoadVarInst(struct, fRec177[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst542), LoadVarInst(struct, fRec177[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst542), LoadVarInst(struct, fRec177[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst517), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst543), LoadVarInst(struct, fRec176[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst544), LoadVarInst(struct, fRec176[Int32(1)]))))))
			StoreVarInst(struct, fRec175[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst517), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst519), LoadVarInst(struct, fRec176[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst545), LoadVarInst(struct, fRec176[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst545), LoadVarInst(struct, fRec176[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst513), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst546), LoadVarInst(struct, fRec175[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst547), LoadVarInst(struct, fRec175[Int32(1)]))))))
			StoreVarInst(struct, fRec174[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec174[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst513), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst516), LoadVarInst(struct, fRec175[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst548), LoadVarInst(struct, fRec175[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst548), LoadVarInst(struct, fRec175[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph10, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec174[Int32(0)])))))))
			StoreVarInst(struct, fRec187[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp87), BinopInst("*", LoadVarInst(struct, fConst565), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst568), LoadVarInst(struct, fRec187[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst569), LoadVarInst(struct, fRec187[Int32(1)]))))))
			StoreVarInst(struct, fRec186[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst565), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst567), LoadVarInst(struct, fRec187[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst570), LoadVarInst(struct, fRec187[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst570), LoadVarInst(struct, fRec187[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst563), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst571), LoadVarInst(struct, fRec186[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst572), LoadVarInst(struct, fRec186[Int32(1)]))))))
			StoreVarInst(struct, fRec185[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst563), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst564), LoadVarInst(struct, fRec186[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst573), LoadVarInst(struct, fRec186[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst573), LoadVarInst(struct, fRec186[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst561), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst574), LoadVarInst(struct, fRec185[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst575), LoadVarInst(struct, fRec185[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp88, BinopInst("*", LoadVarInst(struct, fConst561), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst562), LoadVarInst(struct, fRec185[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst576), LoadVarInst(struct, fRec185[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst576), LoadVarInst(struct, fRec185[Int32(2)])))))
			StoreVarInst(struct, fRec184[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp88), BinopInst("*", LoadVarInst(struct, fConst558), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst577), LoadVarInst(struct, fRec184[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst579), LoadVarInst(struct, fRec184[Int32(1)]))))))
			StoreVarInst(struct, fRec183[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst558), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst560), LoadVarInst(struct, fRec184[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst580), LoadVarInst(struct, fRec184[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst580), LoadVarInst(struct, fRec184[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst555), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst581), LoadVarInst(struct, fRec183[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst582), LoadVarInst(struct, fRec183[Int32(1)]))))))
			StoreVarInst(struct, fRec182[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst555), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst557), LoadVarInst(struct, fRec183[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst583), LoadVarInst(struct, fRec183[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst583), LoadVarInst(struct, fRec183[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst551), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst584), LoadVarInst(struct, fRec182[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst585), LoadVarInst(struct, fRec182[Int32(1)]))))))
			StoreVarInst(struct, fRec181[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec181[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst551), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst554), LoadVarInst(struct, fRec182[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst586), LoadVarInst(struct, fRec182[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst586), LoadVarInst(struct, fRec182[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph11, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec181[Int32(0)])))))))
			StoreVarInst(struct, fRec194[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp88), BinopInst("*", LoadVarInst(struct, fConst603), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst606), LoadVarInst(struct, fRec194[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst607), LoadVarInst(struct, fRec194[Int32(1)]))))))
			StoreVarInst(struct, fRec193[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst603), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst605), LoadVarInst(struct, fRec194[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst608), LoadVarInst(struct, fRec194[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst608), LoadVarInst(struct, fRec194[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst601), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst609), LoadVarInst(struct, fRec193[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst610), LoadVarInst(struct, fRec193[Int32(1)]))))))
			StoreVarInst(struct, fRec192[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst601), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst602), LoadVarInst(struct, fRec193[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst611), LoadVarInst(struct, fRec193[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst611), LoadVarInst(struct, fRec193[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst599), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst612), LoadVarInst(struct, fRec192[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst613), LoadVarInst(struct, fRec192[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp89, BinopInst("*", LoadVarInst(struct, fConst599), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst600), LoadVarInst(struct, fRec192[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst614), LoadVarInst(struct, fRec192[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst614), LoadVarInst(struct, fRec192[Int32(2)])))))
			StoreVarInst(struct, fRec191[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp89), BinopInst("*", LoadVarInst(struct, fConst596), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst615), LoadVarInst(struct, fRec191[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst617), LoadVarInst(struct, fRec191[Int32(1)]))))))
			StoreVarInst(struct, fRec190[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst596), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst598), LoadVarInst(struct, fRec191[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst618), LoadVarInst(struct, fRec191[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst618), LoadVarInst(struct, fRec191[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst593), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst619), LoadVarInst(struct, fRec190[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst620), LoadVarInst(struct, fRec190[Int32(1)]))))))
			StoreVarInst(struct, fRec189[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst593), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst595), LoadVarInst(struct, fRec190[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst621), LoadVarInst(struct, fRec190[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst621), LoadVarInst(struct, fRec190[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst589), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst622), LoadVarInst(struct, fRec189[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst623), LoadVarInst(struct, fRec189[Int32(1)]))))))
			StoreVarInst(struct, fRec188[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec188[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst589), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst592), LoadVarInst(struct, fRec189[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst624), LoadVarInst(struct, fRec189[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst624), LoadVarInst(struct, fRec189[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph12, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec188[Int32(0)])))))))
			StoreVarInst(struct, fRec201[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp89), BinopInst("*", LoadVarInst(struct, fConst641), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst644), LoadVarInst(struct, fRec201[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst645), LoadVarInst(struct, fRec201[Int32(1)]))))))
			StoreVarInst(struct, fRec200[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst641), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst643), LoadVarInst(struct, fRec201[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst646), LoadVarInst(struct, fRec201[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst646), LoadVarInst(struct, fRec201[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst639), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst647), LoadVarInst(struct, fRec200[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst648), LoadVarInst(struct, fRec200[Int32(1)]))))))
			StoreVarInst(struct, fRec199[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst639), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst640), LoadVarInst(struct, fRec200[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst649), LoadVarInst(struct, fRec200[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst649), LoadVarInst(struct, fRec200[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst637), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst650), LoadVarInst(struct, fRec199[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst651), LoadVarInst(struct, fRec199[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp90, BinopInst("*", LoadVarInst(struct, fConst637), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst638), LoadVarInst(struct, fRec199[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst652), LoadVarInst(struct, fRec199[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst652), LoadVarInst(struct, fRec199[Int32(2)])))))
			StoreVarInst(struct, fRec198[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp90), BinopInst("*", LoadVarInst(struct, fConst634), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst653), LoadVarInst(struct, fRec198[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst655), LoadVarInst(struct, fRec198[Int32(1)]))))))
			StoreVarInst(struct, fRec197[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst634), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst636), LoadVarInst(struct, fRec198[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst656), LoadVarInst(struct, fRec198[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst656), LoadVarInst(struct, fRec198[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst631), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst657), LoadVarInst(struct, fRec197[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst658), LoadVarInst(struct, fRec197[Int32(1)]))))))
			StoreVarInst(struct, fRec196[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst631), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst633), LoadVarInst(struct, fRec197[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst659), LoadVarInst(struct, fRec197[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst659), LoadVarInst(struct, fRec197[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst627), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst660), LoadVarInst(struct, fRec196[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst661), LoadVarInst(struct, fRec196[Int32(1)]))))))
			StoreVarInst(struct, fRec195[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec195[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst627), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst630), LoadVarInst(struct, fRec196[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst662), LoadVarInst(struct, fRec196[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst662), LoadVarInst(struct, fRec196[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph13, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec195[Int32(0)])))))))
			StoreVarInst(struct, fRec205[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp90), BinopInst("*", LoadVarInst(struct, fConst667), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst670), LoadVarInst(struct, fRec205[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst671), LoadVarInst(struct, fRec205[Int32(1)]))))))
			StoreVarInst(struct, fRec204[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst667), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst669), LoadVarInst(struct, fRec205[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst672), LoadVarInst(struct, fRec205[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst672), LoadVarInst(struct, fRec205[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst665), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst673), LoadVarInst(struct, fRec204[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst674), LoadVarInst(struct, fRec204[Int32(1)]))))))
			StoreVarInst(struct, fRec203[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(struct, fConst665), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst666), LoadVarInst(struct, fRec204[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst675), LoadVarInst(struct, fRec204[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst675), LoadVarInst(struct, fRec204[Int32(2)])))), BinopInst("*", LoadVarInst(struct, fConst663), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst676), LoadVarInst(struct, fRec203[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst677), LoadVarInst(struct, fRec203[Int32(1)]))))))
			StoreVarInst(struct, fRec202[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec202[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), FunCallInst("fabsf", BinopInst("*", LoadVarInst(struct, fConst663), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst664), LoadVarInst(struct, fRec203[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst678), LoadVarInst(struct, fRec203[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst678), LoadVarInst(struct, fRec203[Int32(2)]))))))))
			StoreVarInst(struct, fVbargraph14, CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(1.00000001e-07f), LoadVarInst(struct, fRec202[Int32(0)])))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp77)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp77)))
			ForLoopInst 
				DeclareVarInst(loop, "int", j0, Int32(3))
				BinopInst(">", LoadVarInst(loop, j0), Int32(0))
				StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
				BlockInst 
					StoreVarInst(struct, iVec0[LoadVarInst(loop, j0)], LoadVarInst(struct, iVec0[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
			StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
			StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
			StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
			StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
			StoreVarInst(struct, fVec8[Int32(1)], LoadVarInst(struct, fVec8[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fVec9[Int32(1)], LoadVarInst(struct, fVec9[Int32(0)]))
			StoreVarInst(struct, fVec10[Int32(1)], LoadVarInst(struct, fVec10[Int32(0)]))
			StoreVarInst(struct, fVec11[Int32(1)], LoadVarInst(struct, fVec11[Int32(0)]))
			StoreVarInst(struct, fVec12[Int32(1)], LoadVarInst(struct, fVec12[Int32(0)]))
			StoreVarInst(struct, fVec13[Int32(1)], LoadVarInst(struct, fVec13[Int32(0)]))
			StoreVarInst(struct, fVec14[Int32(1)], LoadVarInst(struct, fVec14[Int32(0)]))
			StoreVarInst(struct, fVec15[Int32(1)], LoadVarInst(struct, fVec15[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
			StoreVarInst(struct, fVec16[Int32(1)], LoadVarInst(struct, fVec16[Int32(0)]))
			StoreVarInst(struct, fVec17[Int32(1)], LoadVarInst(struct, fVec17[Int32(0)]))
			StoreVarInst(struct, fVec18[Int32(1)], LoadVarInst(struct, fVec18[Int32(0)]))
			StoreVarInst(struct, fVec19[Int32(1)], LoadVarInst(struct, fVec19[Int32(0)]))
			StoreVarInst(struct, fVec20[Int32(1)], LoadVarInst(struct, fVec20[Int32(0)]))
			StoreVarInst(struct, fVec21[Int32(1)], LoadVarInst(struct, fVec21[Int32(0)]))
			StoreVarInst(struct, iRec34[Int32(1)], LoadVarInst(struct, iRec34[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j1, Int32(3))
				BinopInst(">", LoadVarInst(loop, j1), Int32(0))
				StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec35[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec35[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec22[Int32(1)], LoadVarInst(struct, fVec22[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(2)], LoadVarInst(struct, fRec27[Int32(1)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fVec23[Int32(1)], LoadVarInst(struct, fVec23[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(2)], LoadVarInst(struct, fRec24[Int32(1)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(2)], LoadVarInst(struct, fRec23[Int32(1)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fVec24[Int32(1)], LoadVarInst(struct, fVec24[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(2)], LoadVarInst(struct, fRec21[Int32(1)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fVec25[Int32(1)], LoadVarInst(struct, fVec25[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(2)], LoadVarInst(struct, fRec18[Int32(1)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fVec26[Int32(1)], LoadVarInst(struct, fVec26[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fVec27[Int32(1)], LoadVarInst(struct, fVec27[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fVec28[Int32(1)], LoadVarInst(struct, fVec28[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fVec29[Int32(1)], LoadVarInst(struct, fVec29[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(2)], LoadVarInst(struct, fRec6[Int32(1)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
			StoreVarInst(struct, fRec41[Int32(2)], LoadVarInst(struct, fRec41[Int32(1)]))
			StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
			StoreVarInst(struct, fRec40[Int32(2)], LoadVarInst(struct, fRec40[Int32(1)]))
			StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
			StoreVarInst(struct, fVec30[Int32(1)], LoadVarInst(struct, fVec30[Int32(0)]))
			StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
			StoreVarInst(struct, fRec38[Int32(2)], LoadVarInst(struct, fRec38[Int32(1)]))
			StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
			StoreVarInst(struct, fRec37[Int32(2)], LoadVarInst(struct, fRec37[Int32(1)]))
			StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
			StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
			StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
			StoreVarInst(struct, fRec45[Int32(2)], LoadVarInst(struct, fRec45[Int32(1)]))
			StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
			StoreVarInst(struct, fRec44[Int32(2)], LoadVarInst(struct, fRec44[Int32(1)]))
			StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
			StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
			StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
			StoreVarInst(struct, fRec57[Int32(2)], LoadVarInst(struct, fRec57[Int32(1)]))
			StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
			StoreVarInst(struct, fRec56[Int32(2)], LoadVarInst(struct, fRec56[Int32(1)]))
			StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
			StoreVarInst(struct, fRec55[Int32(2)], LoadVarInst(struct, fRec55[Int32(1)]))
			StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
			StoreVarInst(struct, fRec54[Int32(2)], LoadVarInst(struct, fRec54[Int32(1)]))
			StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
			StoreVarInst(struct, fRec53[Int32(2)], LoadVarInst(struct, fRec53[Int32(1)]))
			StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
			StoreVarInst(struct, fRec52[Int32(2)], LoadVarInst(struct, fRec52[Int32(1)]))
			StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
			StoreVarInst(struct, fRec51[Int32(2)], LoadVarInst(struct, fRec51[Int32(1)]))
			StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
			StoreVarInst(struct, fRec50[Int32(2)], LoadVarInst(struct, fRec50[Int32(1)]))
			StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
			StoreVarInst(struct, fRec49[Int32(2)], LoadVarInst(struct, fRec49[Int32(1)]))
			StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
			StoreVarInst(struct, fRec48[Int32(2)], LoadVarInst(struct, fRec48[Int32(1)]))
			StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
			StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
			StoreVarInst(struct, fRec69[Int32(1)], LoadVarInst(struct, fRec69[Int32(0)]))
			StoreVarInst(struct, fRec68[Int32(2)], LoadVarInst(struct, fRec68[Int32(1)]))
			StoreVarInst(struct, fRec68[Int32(1)], LoadVarInst(struct, fRec68[Int32(0)]))
			StoreVarInst(struct, fRec67[Int32(2)], LoadVarInst(struct, fRec67[Int32(1)]))
			StoreVarInst(struct, fRec67[Int32(1)], LoadVarInst(struct, fRec67[Int32(0)]))
			StoreVarInst(struct, fRec66[Int32(2)], LoadVarInst(struct, fRec66[Int32(1)]))
			StoreVarInst(struct, fRec66[Int32(1)], LoadVarInst(struct, fRec66[Int32(0)]))
			StoreVarInst(struct, fRec65[Int32(2)], LoadVarInst(struct, fRec65[Int32(1)]))
			StoreVarInst(struct, fRec65[Int32(1)], LoadVarInst(struct, fRec65[Int32(0)]))
			StoreVarInst(struct, fRec64[Int32(2)], LoadVarInst(struct, fRec64[Int32(1)]))
			StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
			StoreVarInst(struct, fRec63[Int32(2)], LoadVarInst(struct, fRec63[Int32(1)]))
			StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
			StoreVarInst(struct, fRec62[Int32(2)], LoadVarInst(struct, fRec62[Int32(1)]))
			StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
			StoreVarInst(struct, fRec61[Int32(2)], LoadVarInst(struct, fRec61[Int32(1)]))
			StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
			StoreVarInst(struct, fRec60[Int32(2)], LoadVarInst(struct, fRec60[Int32(1)]))
			StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
			StoreVarInst(struct, fRec70[Int32(1)], LoadVarInst(struct, fRec70[Int32(0)]))
			StoreVarInst(struct, fRec79[Int32(1)], LoadVarInst(struct, fRec79[Int32(0)]))
			StoreVarInst(struct, fRec78[Int32(2)], LoadVarInst(struct, fRec78[Int32(1)]))
			StoreVarInst(struct, fRec78[Int32(1)], LoadVarInst(struct, fRec78[Int32(0)]))
			StoreVarInst(struct, fRec77[Int32(2)], LoadVarInst(struct, fRec77[Int32(1)]))
			StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
			StoreVarInst(struct, fRec76[Int32(2)], LoadVarInst(struct, fRec76[Int32(1)]))
			StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
			StoreVarInst(struct, fRec75[Int32(2)], LoadVarInst(struct, fRec75[Int32(1)]))
			StoreVarInst(struct, fRec75[Int32(1)], LoadVarInst(struct, fRec75[Int32(0)]))
			StoreVarInst(struct, fRec74[Int32(2)], LoadVarInst(struct, fRec74[Int32(1)]))
			StoreVarInst(struct, fRec74[Int32(1)], LoadVarInst(struct, fRec74[Int32(0)]))
			StoreVarInst(struct, fRec73[Int32(2)], LoadVarInst(struct, fRec73[Int32(1)]))
			StoreVarInst(struct, fRec73[Int32(1)], LoadVarInst(struct, fRec73[Int32(0)]))
			StoreVarInst(struct, fRec72[Int32(2)], LoadVarInst(struct, fRec72[Int32(1)]))
			StoreVarInst(struct, fRec72[Int32(1)], LoadVarInst(struct, fRec72[Int32(0)]))
			StoreVarInst(struct, fRec71[Int32(2)], LoadVarInst(struct, fRec71[Int32(1)]))
			StoreVarInst(struct, fRec71[Int32(1)], LoadVarInst(struct, fRec71[Int32(0)]))
			StoreVarInst(struct, fRec80[Int32(1)], LoadVarInst(struct, fRec80[Int32(0)]))
			StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
			StoreVarInst(struct, fRec87[Int32(2)], LoadVarInst(struct, fRec87[Int32(1)]))
			StoreVarInst(struct, fRec87[Int32(1)], LoadVarInst(struct, fRec87[Int32(0)]))
			StoreVarInst(struct, fRec86[Int32(2)], LoadVarInst(struct, fRec86[Int32(1)]))
			StoreVarInst(struct, fRec86[Int32(1)], LoadVarInst(struct, fRec86[Int32(0)]))
			StoreVarInst(struct, fRec85[Int32(2)], LoadVarInst(struct, fRec85[Int32(1)]))
			StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
			StoreVarInst(struct, fRec84[Int32(2)], LoadVarInst(struct, fRec84[Int32(1)]))
			StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
			StoreVarInst(struct, fRec83[Int32(2)], LoadVarInst(struct, fRec83[Int32(1)]))
			StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
			StoreVarInst(struct, fRec82[Int32(2)], LoadVarInst(struct, fRec82[Int32(1)]))
			StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
			StoreVarInst(struct, fRec81[Int32(2)], LoadVarInst(struct, fRec81[Int32(1)]))
			StoreVarInst(struct, fRec81[Int32(1)], LoadVarInst(struct, fRec81[Int32(0)]))
			StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
			StoreVarInst(struct, fRec96[Int32(1)], LoadVarInst(struct, fRec96[Int32(0)]))
			StoreVarInst(struct, fRec95[Int32(2)], LoadVarInst(struct, fRec95[Int32(1)]))
			StoreVarInst(struct, fRec95[Int32(1)], LoadVarInst(struct, fRec95[Int32(0)]))
			StoreVarInst(struct, fRec94[Int32(2)], LoadVarInst(struct, fRec94[Int32(1)]))
			StoreVarInst(struct, fRec94[Int32(1)], LoadVarInst(struct, fRec94[Int32(0)]))
			StoreVarInst(struct, fRec93[Int32(2)], LoadVarInst(struct, fRec93[Int32(1)]))
			StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
			StoreVarInst(struct, fRec92[Int32(2)], LoadVarInst(struct, fRec92[Int32(1)]))
			StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
			StoreVarInst(struct, fRec91[Int32(2)], LoadVarInst(struct, fRec91[Int32(1)]))
			StoreVarInst(struct, fRec91[Int32(1)], LoadVarInst(struct, fRec91[Int32(0)]))
			StoreVarInst(struct, fRec90[Int32(2)], LoadVarInst(struct, fRec90[Int32(1)]))
			StoreVarInst(struct, fRec90[Int32(1)], LoadVarInst(struct, fRec90[Int32(0)]))
			StoreVarInst(struct, fRec97[Int32(1)], LoadVarInst(struct, fRec97[Int32(0)]))
			StoreVarInst(struct, fRec103[Int32(1)], LoadVarInst(struct, fRec103[Int32(0)]))
			StoreVarInst(struct, fRec102[Int32(2)], LoadVarInst(struct, fRec102[Int32(1)]))
			StoreVarInst(struct, fRec102[Int32(1)], LoadVarInst(struct, fRec102[Int32(0)]))
			StoreVarInst(struct, fRec101[Int32(2)], LoadVarInst(struct, fRec101[Int32(1)]))
			StoreVarInst(struct, fRec101[Int32(1)], LoadVarInst(struct, fRec101[Int32(0)]))
			StoreVarInst(struct, fRec100[Int32(2)], LoadVarInst(struct, fRec100[Int32(1)]))
			StoreVarInst(struct, fRec100[Int32(1)], LoadVarInst(struct, fRec100[Int32(0)]))
			StoreVarInst(struct, fRec99[Int32(2)], LoadVarInst(struct, fRec99[Int32(1)]))
			StoreVarInst(struct, fRec99[Int32(1)], LoadVarInst(struct, fRec99[Int32(0)]))
			StoreVarInst(struct, fRec98[Int32(2)], LoadVarInst(struct, fRec98[Int32(1)]))
			StoreVarInst(struct, fRec98[Int32(1)], LoadVarInst(struct, fRec98[Int32(0)]))
			StoreVarInst(struct, fRec104[Int32(1)], LoadVarInst(struct, fRec104[Int32(0)]))
			StoreVarInst(struct, fRec109[Int32(1)], LoadVarInst(struct, fRec109[Int32(0)]))
			StoreVarInst(struct, fRec108[Int32(2)], LoadVarInst(struct, fRec108[Int32(1)]))
			StoreVarInst(struct, fRec108[Int32(1)], LoadVarInst(struct, fRec108[Int32(0)]))
			StoreVarInst(struct, fRec107[Int32(2)], LoadVarInst(struct, fRec107[Int32(1)]))
			StoreVarInst(struct, fRec107[Int32(1)], LoadVarInst(struct, fRec107[Int32(0)]))
			StoreVarInst(struct, fRec106[Int32(2)], LoadVarInst(struct, fRec106[Int32(1)]))
			StoreVarInst(struct, fRec106[Int32(1)], LoadVarInst(struct, fRec106[Int32(0)]))
			StoreVarInst(struct, fRec105[Int32(2)], LoadVarInst(struct, fRec105[Int32(1)]))
			StoreVarInst(struct, fRec105[Int32(1)], LoadVarInst(struct, fRec105[Int32(0)]))
			StoreVarInst(struct, fRec110[Int32(1)], LoadVarInst(struct, fRec110[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec117[Int32(2)], LoadVarInst(struct, fRec117[Int32(1)]))
			StoreVarInst(struct, fRec117[Int32(1)], LoadVarInst(struct, fRec117[Int32(0)]))
			StoreVarInst(struct, fRec116[Int32(2)], LoadVarInst(struct, fRec116[Int32(1)]))
			StoreVarInst(struct, fRec116[Int32(1)], LoadVarInst(struct, fRec116[Int32(0)]))
			StoreVarInst(struct, fRec115[Int32(2)], LoadVarInst(struct, fRec115[Int32(1)]))
			StoreVarInst(struct, fRec115[Int32(1)], LoadVarInst(struct, fRec115[Int32(0)]))
			StoreVarInst(struct, fRec114[Int32(2)], LoadVarInst(struct, fRec114[Int32(1)]))
			StoreVarInst(struct, fRec114[Int32(1)], LoadVarInst(struct, fRec114[Int32(0)]))
			StoreVarInst(struct, fRec113[Int32(2)], LoadVarInst(struct, fRec113[Int32(1)]))
			StoreVarInst(struct, fRec113[Int32(1)], LoadVarInst(struct, fRec113[Int32(0)]))
			StoreVarInst(struct, fRec112[Int32(2)], LoadVarInst(struct, fRec112[Int32(1)]))
			StoreVarInst(struct, fRec112[Int32(1)], LoadVarInst(struct, fRec112[Int32(0)]))
			StoreVarInst(struct, fRec111[Int32(1)], LoadVarInst(struct, fRec111[Int32(0)]))
			StoreVarInst(struct, fRec124[Int32(2)], LoadVarInst(struct, fRec124[Int32(1)]))
			StoreVarInst(struct, fRec124[Int32(1)], LoadVarInst(struct, fRec124[Int32(0)]))
			StoreVarInst(struct, fRec123[Int32(2)], LoadVarInst(struct, fRec123[Int32(1)]))
			StoreVarInst(struct, fRec123[Int32(1)], LoadVarInst(struct, fRec123[Int32(0)]))
			StoreVarInst(struct, fRec122[Int32(2)], LoadVarInst(struct, fRec122[Int32(1)]))
			StoreVarInst(struct, fRec122[Int32(1)], LoadVarInst(struct, fRec122[Int32(0)]))
			StoreVarInst(struct, fRec121[Int32(2)], LoadVarInst(struct, fRec121[Int32(1)]))
			StoreVarInst(struct, fRec121[Int32(1)], LoadVarInst(struct, fRec121[Int32(0)]))
			StoreVarInst(struct, fRec120[Int32(2)], LoadVarInst(struct, fRec120[Int32(1)]))
			StoreVarInst(struct, fRec120[Int32(1)], LoadVarInst(struct, fRec120[Int32(0)]))
			StoreVarInst(struct, fRec119[Int32(2)], LoadVarInst(struct, fRec119[Int32(1)]))
			StoreVarInst(struct, fRec119[Int32(1)], LoadVarInst(struct, fRec119[Int32(0)]))
			StoreVarInst(struct, fRec118[Int32(1)], LoadVarInst(struct, fRec118[Int32(0)]))
			StoreVarInst(struct, fRec131[Int32(2)], LoadVarInst(struct, fRec131[Int32(1)]))
			StoreVarInst(struct, fRec131[Int32(1)], LoadVarInst(struct, fRec131[Int32(0)]))
			StoreVarInst(struct, fRec130[Int32(2)], LoadVarInst(struct, fRec130[Int32(1)]))
			StoreVarInst(struct, fRec130[Int32(1)], LoadVarInst(struct, fRec130[Int32(0)]))
			StoreVarInst(struct, fRec129[Int32(2)], LoadVarInst(struct, fRec129[Int32(1)]))
			StoreVarInst(struct, fRec129[Int32(1)], LoadVarInst(struct, fRec129[Int32(0)]))
			StoreVarInst(struct, fRec128[Int32(2)], LoadVarInst(struct, fRec128[Int32(1)]))
			StoreVarInst(struct, fRec128[Int32(1)], LoadVarInst(struct, fRec128[Int32(0)]))
			StoreVarInst(struct, fRec127[Int32(2)], LoadVarInst(struct, fRec127[Int32(1)]))
			StoreVarInst(struct, fRec127[Int32(1)], LoadVarInst(struct, fRec127[Int32(0)]))
			StoreVarInst(struct, fRec126[Int32(2)], LoadVarInst(struct, fRec126[Int32(1)]))
			StoreVarInst(struct, fRec126[Int32(1)], LoadVarInst(struct, fRec126[Int32(0)]))
			StoreVarInst(struct, fRec125[Int32(1)], LoadVarInst(struct, fRec125[Int32(0)]))
			StoreVarInst(struct, fRec138[Int32(2)], LoadVarInst(struct, fRec138[Int32(1)]))
			StoreVarInst(struct, fRec138[Int32(1)], LoadVarInst(struct, fRec138[Int32(0)]))
			StoreVarInst(struct, fRec137[Int32(2)], LoadVarInst(struct, fRec137[Int32(1)]))
			StoreVarInst(struct, fRec137[Int32(1)], LoadVarInst(struct, fRec137[Int32(0)]))
			StoreVarInst(struct, fRec136[Int32(2)], LoadVarInst(struct, fRec136[Int32(1)]))
			StoreVarInst(struct, fRec136[Int32(1)], LoadVarInst(struct, fRec136[Int32(0)]))
			StoreVarInst(struct, fRec135[Int32(2)], LoadVarInst(struct, fRec135[Int32(1)]))
			StoreVarInst(struct, fRec135[Int32(1)], LoadVarInst(struct, fRec135[Int32(0)]))
			StoreVarInst(struct, fRec134[Int32(2)], LoadVarInst(struct, fRec134[Int32(1)]))
			StoreVarInst(struct, fRec134[Int32(1)], LoadVarInst(struct, fRec134[Int32(0)]))
			StoreVarInst(struct, fRec133[Int32(2)], LoadVarInst(struct, fRec133[Int32(1)]))
			StoreVarInst(struct, fRec133[Int32(1)], LoadVarInst(struct, fRec133[Int32(0)]))
			StoreVarInst(struct, fRec132[Int32(1)], LoadVarInst(struct, fRec132[Int32(0)]))
			StoreVarInst(struct, fRec145[Int32(2)], LoadVarInst(struct, fRec145[Int32(1)]))
			StoreVarInst(struct, fRec145[Int32(1)], LoadVarInst(struct, fRec145[Int32(0)]))
			StoreVarInst(struct, fRec144[Int32(2)], LoadVarInst(struct, fRec144[Int32(1)]))
			StoreVarInst(struct, fRec144[Int32(1)], LoadVarInst(struct, fRec144[Int32(0)]))
			StoreVarInst(struct, fRec143[Int32(2)], LoadVarInst(struct, fRec143[Int32(1)]))
			StoreVarInst(struct, fRec143[Int32(1)], LoadVarInst(struct, fRec143[Int32(0)]))
			StoreVarInst(struct, fRec142[Int32(2)], LoadVarInst(struct, fRec142[Int32(1)]))
			StoreVarInst(struct, fRec142[Int32(1)], LoadVarInst(struct, fRec142[Int32(0)]))
			StoreVarInst(struct, fRec141[Int32(2)], LoadVarInst(struct, fRec141[Int32(1)]))
			StoreVarInst(struct, fRec141[Int32(1)], LoadVarInst(struct, fRec141[Int32(0)]))
			StoreVarInst(struct, fRec140[Int32(2)], LoadVarInst(struct, fRec140[Int32(1)]))
			StoreVarInst(struct, fRec140[Int32(1)], LoadVarInst(struct, fRec140[Int32(0)]))
			StoreVarInst(struct, fRec139[Int32(1)], LoadVarInst(struct, fRec139[Int32(0)]))
			StoreVarInst(struct, fRec152[Int32(2)], LoadVarInst(struct, fRec152[Int32(1)]))
			StoreVarInst(struct, fRec152[Int32(1)], LoadVarInst(struct, fRec152[Int32(0)]))
			StoreVarInst(struct, fRec151[Int32(2)], LoadVarInst(struct, fRec151[Int32(1)]))
			StoreVarInst(struct, fRec151[Int32(1)], LoadVarInst(struct, fRec151[Int32(0)]))
			StoreVarInst(struct, fRec150[Int32(2)], LoadVarInst(struct, fRec150[Int32(1)]))
			StoreVarInst(struct, fRec150[Int32(1)], LoadVarInst(struct, fRec150[Int32(0)]))
			StoreVarInst(struct, fRec149[Int32(2)], LoadVarInst(struct, fRec149[Int32(1)]))
			StoreVarInst(struct, fRec149[Int32(1)], LoadVarInst(struct, fRec149[Int32(0)]))
			StoreVarInst(struct, fRec148[Int32(2)], LoadVarInst(struct, fRec148[Int32(1)]))
			StoreVarInst(struct, fRec148[Int32(1)], LoadVarInst(struct, fRec148[Int32(0)]))
			StoreVarInst(struct, fRec147[Int32(2)], LoadVarInst(struct, fRec147[Int32(1)]))
			StoreVarInst(struct, fRec147[Int32(1)], LoadVarInst(struct, fRec147[Int32(0)]))
			StoreVarInst(struct, fRec146[Int32(1)], LoadVarInst(struct, fRec146[Int32(0)]))
			StoreVarInst(struct, fRec159[Int32(2)], LoadVarInst(struct, fRec159[Int32(1)]))
			StoreVarInst(struct, fRec159[Int32(1)], LoadVarInst(struct, fRec159[Int32(0)]))
			StoreVarInst(struct, fRec158[Int32(2)], LoadVarInst(struct, fRec158[Int32(1)]))
			StoreVarInst(struct, fRec158[Int32(1)], LoadVarInst(struct, fRec158[Int32(0)]))
			StoreVarInst(struct, fRec157[Int32(2)], LoadVarInst(struct, fRec157[Int32(1)]))
			StoreVarInst(struct, fRec157[Int32(1)], LoadVarInst(struct, fRec157[Int32(0)]))
			StoreVarInst(struct, fRec156[Int32(2)], LoadVarInst(struct, fRec156[Int32(1)]))
			StoreVarInst(struct, fRec156[Int32(1)], LoadVarInst(struct, fRec156[Int32(0)]))
			StoreVarInst(struct, fRec155[Int32(2)], LoadVarInst(struct, fRec155[Int32(1)]))
			StoreVarInst(struct, fRec155[Int32(1)], LoadVarInst(struct, fRec155[Int32(0)]))
			StoreVarInst(struct, fRec154[Int32(2)], LoadVarInst(struct, fRec154[Int32(1)]))
			StoreVarInst(struct, fRec154[Int32(1)], LoadVarInst(struct, fRec154[Int32(0)]))
			StoreVarInst(struct, fRec153[Int32(1)], LoadVarInst(struct, fRec153[Int32(0)]))
			StoreVarInst(struct, fRec166[Int32(2)], LoadVarInst(struct, fRec166[Int32(1)]))
			StoreVarInst(struct, fRec166[Int32(1)], LoadVarInst(struct, fRec166[Int32(0)]))
			StoreVarInst(struct, fRec165[Int32(2)], LoadVarInst(struct, fRec165[Int32(1)]))
			StoreVarInst(struct, fRec165[Int32(1)], LoadVarInst(struct, fRec165[Int32(0)]))
			StoreVarInst(struct, fRec164[Int32(2)], LoadVarInst(struct, fRec164[Int32(1)]))
			StoreVarInst(struct, fRec164[Int32(1)], LoadVarInst(struct, fRec164[Int32(0)]))
			StoreVarInst(struct, fRec163[Int32(2)], LoadVarInst(struct, fRec163[Int32(1)]))
			StoreVarInst(struct, fRec163[Int32(1)], LoadVarInst(struct, fRec163[Int32(0)]))
			StoreVarInst(struct, fRec162[Int32(2)], LoadVarInst(struct, fRec162[Int32(1)]))
			StoreVarInst(struct, fRec162[Int32(1)], LoadVarInst(struct, fRec162[Int32(0)]))
			StoreVarInst(struct, fRec161[Int32(2)], LoadVarInst(struct, fRec161[Int32(1)]))
			StoreVarInst(struct, fRec161[Int32(1)], LoadVarInst(struct, fRec161[Int32(0)]))
			StoreVarInst(struct, fRec160[Int32(1)], LoadVarInst(struct, fRec160[Int32(0)]))
			StoreVarInst(struct, fRec173[Int32(2)], LoadVarInst(struct, fRec173[Int32(1)]))
			StoreVarInst(struct, fRec173[Int32(1)], LoadVarInst(struct, fRec173[Int32(0)]))
			StoreVarInst(struct, fRec172[Int32(2)], LoadVarInst(struct, fRec172[Int32(1)]))
			StoreVarInst(struct, fRec172[Int32(1)], LoadVarInst(struct, fRec172[Int32(0)]))
			StoreVarInst(struct, fRec171[Int32(2)], LoadVarInst(struct, fRec171[Int32(1)]))
			StoreVarInst(struct, fRec171[Int32(1)], LoadVarInst(struct, fRec171[Int32(0)]))
			StoreVarInst(struct, fRec170[Int32(2)], LoadVarInst(struct, fRec170[Int32(1)]))
			StoreVarInst(struct, fRec170[Int32(1)], LoadVarInst(struct, fRec170[Int32(0)]))
			StoreVarInst(struct, fRec169[Int32(2)], LoadVarInst(struct, fRec169[Int32(1)]))
			StoreVarInst(struct, fRec169[Int32(1)], LoadVarInst(struct, fRec169[Int32(0)]))
			StoreVarInst(struct, fRec168[Int32(2)], LoadVarInst(struct, fRec168[Int32(1)]))
			StoreVarInst(struct, fRec168[Int32(1)], LoadVarInst(struct, fRec168[Int32(0)]))
			StoreVarInst(struct, fRec167[Int32(1)], LoadVarInst(struct, fRec167[Int32(0)]))
			StoreVarInst(struct, fRec180[Int32(2)], LoadVarInst(struct, fRec180[Int32(1)]))
			StoreVarInst(struct, fRec180[Int32(1)], LoadVarInst(struct, fRec180[Int32(0)]))
			StoreVarInst(struct, fRec179[Int32(2)], LoadVarInst(struct, fRec179[Int32(1)]))
			StoreVarInst(struct, fRec179[Int32(1)], LoadVarInst(struct, fRec179[Int32(0)]))
			StoreVarInst(struct, fRec178[Int32(2)], LoadVarInst(struct, fRec178[Int32(1)]))
			StoreVarInst(struct, fRec178[Int32(1)], LoadVarInst(struct, fRec178[Int32(0)]))
			StoreVarInst(struct, fRec177[Int32(2)], LoadVarInst(struct, fRec177[Int32(1)]))
			StoreVarInst(struct, fRec177[Int32(1)], LoadVarInst(struct, fRec177[Int32(0)]))
			StoreVarInst(struct, fRec176[Int32(2)], LoadVarInst(struct, fRec176[Int32(1)]))
			StoreVarInst(struct, fRec176[Int32(1)], LoadVarInst(struct, fRec176[Int32(0)]))
			StoreVarInst(struct, fRec175[Int32(2)], LoadVarInst(struct, fRec175[Int32(1)]))
			StoreVarInst(struct, fRec175[Int32(1)], LoadVarInst(struct, fRec175[Int32(0)]))
			StoreVarInst(struct, fRec174[Int32(1)], LoadVarInst(struct, fRec174[Int32(0)]))
			StoreVarInst(struct, fRec187[Int32(2)], LoadVarInst(struct, fRec187[Int32(1)]))
			StoreVarInst(struct, fRec187[Int32(1)], LoadVarInst(struct, fRec187[Int32(0)]))
			StoreVarInst(struct, fRec186[Int32(2)], LoadVarInst(struct, fRec186[Int32(1)]))
			StoreVarInst(struct, fRec186[Int32(1)], LoadVarInst(struct, fRec186[Int32(0)]))
			StoreVarInst(struct, fRec185[Int32(2)], LoadVarInst(struct, fRec185[Int32(1)]))
			StoreVarInst(struct, fRec185[Int32(1)], LoadVarInst(struct, fRec185[Int32(0)]))
			StoreVarInst(struct, fRec184[Int32(2)], LoadVarInst(struct, fRec184[Int32(1)]))
			StoreVarInst(struct, fRec184[Int32(1)], LoadVarInst(struct, fRec184[Int32(0)]))
			StoreVarInst(struct, fRec183[Int32(2)], LoadVarInst(struct, fRec183[Int32(1)]))
			StoreVarInst(struct, fRec183[Int32(1)], LoadVarInst(struct, fRec183[Int32(0)]))
			StoreVarInst(struct, fRec182[Int32(2)], LoadVarInst(struct, fRec182[Int32(1)]))
			StoreVarInst(struct, fRec182[Int32(1)], LoadVarInst(struct, fRec182[Int32(0)]))
			StoreVarInst(struct, fRec181[Int32(1)], LoadVarInst(struct, fRec181[Int32(0)]))
			StoreVarInst(struct, fRec194[Int32(2)], LoadVarInst(struct, fRec194[Int32(1)]))
			StoreVarInst(struct, fRec194[Int32(1)], LoadVarInst(struct, fRec194[Int32(0)]))
			StoreVarInst(struct, fRec193[Int32(2)], LoadVarInst(struct, fRec193[Int32(1)]))
			StoreVarInst(struct, fRec193[Int32(1)], LoadVarInst(struct, fRec193[Int32(0)]))
			StoreVarInst(struct, fRec192[Int32(2)], LoadVarInst(struct, fRec192[Int32(1)]))
			StoreVarInst(struct, fRec192[Int32(1)], LoadVarInst(struct, fRec192[Int32(0)]))
			StoreVarInst(struct, fRec191[Int32(2)], LoadVarInst(struct, fRec191[Int32(1)]))
			StoreVarInst(struct, fRec191[Int32(1)], LoadVarInst(struct, fRec191[Int32(0)]))
			StoreVarInst(struct, fRec190[Int32(2)], LoadVarInst(struct, fRec190[Int32(1)]))
			StoreVarInst(struct, fRec190[Int32(1)], LoadVarInst(struct, fRec190[Int32(0)]))
			StoreVarInst(struct, fRec189[Int32(2)], LoadVarInst(struct, fRec189[Int32(1)]))
			StoreVarInst(struct, fRec189[Int32(1)], LoadVarInst(struct, fRec189[Int32(0)]))
			StoreVarInst(struct, fRec188[Int32(1)], LoadVarInst(struct, fRec188[Int32(0)]))
			StoreVarInst(struct, fRec201[Int32(2)], LoadVarInst(struct, fRec201[Int32(1)]))
			StoreVarInst(struct, fRec201[Int32(1)], LoadVarInst(struct, fRec201[Int32(0)]))
			StoreVarInst(struct, fRec200[Int32(2)], LoadVarInst(struct, fRec200[Int32(1)]))
			StoreVarInst(struct, fRec200[Int32(1)], LoadVarInst(struct, fRec200[Int32(0)]))
			StoreVarInst(struct, fRec199[Int32(2)], LoadVarInst(struct, fRec199[Int32(1)]))
			StoreVarInst(struct, fRec199[Int32(1)], LoadVarInst(struct, fRec199[Int32(0)]))
			StoreVarInst(struct, fRec198[Int32(2)], LoadVarInst(struct, fRec198[Int32(1)]))
			StoreVarInst(struct, fRec198[Int32(1)], LoadVarInst(struct, fRec198[Int32(0)]))
			StoreVarInst(struct, fRec197[Int32(2)], LoadVarInst(struct, fRec197[Int32(1)]))
			StoreVarInst(struct, fRec197[Int32(1)], LoadVarInst(struct, fRec197[Int32(0)]))
			StoreVarInst(struct, fRec196[Int32(2)], LoadVarInst(struct, fRec196[Int32(1)]))
			StoreVarInst(struct, fRec196[Int32(1)], LoadVarInst(struct, fRec196[Int32(0)]))
			StoreVarInst(struct, fRec195[Int32(1)], LoadVarInst(struct, fRec195[Int32(0)]))
			StoreVarInst(struct, fRec205[Int32(2)], LoadVarInst(struct, fRec205[Int32(1)]))
			StoreVarInst(struct, fRec205[Int32(1)], LoadVarInst(struct, fRec205[Int32(0)]))
			StoreVarInst(struct, fRec204[Int32(2)], LoadVarInst(struct, fRec204[Int32(1)]))
			StoreVarInst(struct, fRec204[Int32(1)], LoadVarInst(struct, fRec204[Int32(0)]))
			StoreVarInst(struct, fRec203[Int32(2)], LoadVarInst(struct, fRec203[Int32(1)]))
			StoreVarInst(struct, fRec203[Int32(1)], LoadVarInst(struct, fRec203[Int32(0)]))
			StoreVarInst(struct, fRec202[Int32(1)], LoadVarInst(struct, fRec202[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 24 bytes
Heap size real = 5376 bytes
Heap size = 5404 bytes
Stack size in compute = 128 bytes

