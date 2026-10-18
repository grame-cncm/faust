======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER ALLPASS-COMB REVERBERATOR (8x8). See Faust's effect.lib for documentation and references")
	OpenHorizontalBox("Zita_Rev1")
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("Input")
	AddMetaDeclareInst(fVslider4, "1", "")
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddMetaDeclareInst(fVslider4, "tooltip", "Delay in ms before reverberation begins")
	AddMetaDeclareInst(fVslider4, "unit", "ms")
	AddVerticalSlider("In Delay", fVslider4, 6e+01f, 2e+01f, 1e+02f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("Decay Times in Bands (see tooltips)")
	AddMetaDeclareInst(fVslider0, "1", "")
	AddMetaDeclareInst(fVslider0, "scale", "log")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddMetaDeclareInst(fVslider0, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies")
	AddMetaDeclareInst(fVslider0, "unit", "Hz")
	AddVerticalSlider("LF X", fVslider0, 2e+02f, 5e+01f, 1e+03f, 1.0f)
	AddMetaDeclareInst(fVslider3, "2", "")
	AddMetaDeclareInst(fVslider3, "scale", "log")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band")
	AddMetaDeclareInst(fVslider3, "unit", "s")
	AddVerticalSlider("Low RT60", fVslider3, 3.0f, 1.0f, 8.0f, 0.1f)
	AddMetaDeclareInst(fVslider1, "3", "")
	AddMetaDeclareInst(fVslider1, "scale", "log")
	AddMetaDeclareInst(fVslider1, "style", "knob")
	AddMetaDeclareInst(fVslider1, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band")
	AddMetaDeclareInst(fVslider1, "unit", "s")
	AddVerticalSlider("Mid RT60", fVslider1, 2.0f, 1.0f, 8.0f, 0.1f)
	AddMetaDeclareInst(fVslider2, "4", "")
	AddMetaDeclareInst(fVslider2, "scale", "log")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60")
	AddMetaDeclareInst(fVslider2, "unit", "Hz")
	AddVerticalSlider("HF Damping", fVslider2, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenHorizontalBox("RM Peaking Equalizer 1")
	AddMetaDeclareInst(fVslider5, "1", "")
	AddMetaDeclareInst(fVslider5, "scale", "log")
	AddMetaDeclareInst(fVslider5, "style", "knob")
	AddMetaDeclareInst(fVslider5, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1")
	AddMetaDeclareInst(fVslider5, "unit", "Hz")
	AddVerticalSlider("Eq1 Freq", fVslider5, 315.0f, 4e+01f, 2.5e+03f, 1.0f)
	AddMetaDeclareInst(fVslider6, "2", "")
	AddMetaDeclareInst(fVslider6, "style", "knob")
	AddMetaDeclareInst(fVslider6, "tooltip", "Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1")
	AddMetaDeclareInst(fVslider6, "unit", "dB")
	AddVerticalSlider("Eq1 Level", fVslider6, 0.0f, -15.0f, 15.0f, 0.1f)
	CloseboxInst
	AddMetaDeclareInst(0, "4", "")
	OpenHorizontalBox("RM Peaking Equalizer 2")
	AddMetaDeclareInst(fVslider7, "1", "")
	AddMetaDeclareInst(fVslider7, "scale", "log")
	AddMetaDeclareInst(fVslider7, "style", "knob")
	AddMetaDeclareInst(fVslider7, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2")
	AddMetaDeclareInst(fVslider7, "unit", "Hz")
	AddVerticalSlider("Eq2 Freq", fVslider7, 1.5e+03f, 1.6e+02f, 1e+04f, 1.0f)
	AddMetaDeclareInst(fVslider8, "2", "")
	AddMetaDeclareInst(fVslider8, "style", "knob")
	AddMetaDeclareInst(fVslider8, "tooltip", "Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2")
	AddMetaDeclareInst(fVslider8, "unit", "dB")
	AddVerticalSlider("Eq2 Level", fVslider8, 0.0f, -15.0f, 15.0f, 0.1f)
	CloseboxInst
	AddMetaDeclareInst(0, "5", "")
	OpenHorizontalBox("Output")
	AddMetaDeclareInst(fVslider9, "1", "")
	AddMetaDeclareInst(fVslider9, "style", "knob")
	AddMetaDeclareInst(fVslider9, "tooltip", "-1 = dry, 1 = wet")
	AddVerticalSlider("Dry/Wet Mix", fVslider9, 0.4492f, -1.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fVslider10, "2", "")
	AddMetaDeclareInst(fVslider10, "style", "knob")
	AddMetaDeclareInst(fVslider10, "tooltip", "Output scale factor")
	AddMetaDeclareInst(fVslider10, "unit", "dB")
	AddVerticalSlider("Level", fVslider10, 16.79f, -7e+01f, 4e+01f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fVslider0)("float[2]", fRec0)("float", fConst2)("float", fConst3)("FAUSTFLOAT", fVslider1)("float", fConst4)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fVslider3)("float[2]", fRec1)("int", IOTA0)("float[8192]", fVec0)("float", fConst5)("int", iConst6)("float[8192]", fVec1)("float", fConst7)("FAUSTFLOAT", fVslider4)("float[1024]", fVec2)("int", iConst8)("float[2]", fRec2)("float[2]", fRec4)("float", fConst9)("float", fConst10)("float[2]", fRec5)("float[8192]", fVec3)("float", fConst11)("int", iConst12)("float[2048]", fVec4)("int", iConst13)("float[2]", fRec6)("float[2]", fRec8)("float", fConst14)("float", fConst15)("float[2]", fRec9)("float[8192]", fVec5)("float", fConst16)("int", iConst17)("float[2048]", fVec6)("int", iConst18)("float[2]", fRec10)("float[2]", fRec12)("float", fConst19)("float", fConst20)("float[2]", fRec13)("float[8192]", fVec7)("float", fConst21)("int", iConst22)("float[1024]", fVec8)("int", iConst23)("float[2]", fRec14)("float[2]", fRec16)("float", fConst24)("float", fConst25)("float[2]", fRec17)("float[16384]", fVec9)("float", fConst26)("int", iConst27)("float[8192]", fVec10)("float[2048]", fVec11)("int", iConst28)("float[2]", fRec18)("float[2]", fRec20)("float", fConst29)("float", fConst30)("float[2]", fRec21)("float[8192]", fVec12)("float", fConst31)("int", iConst32)("float[2048]", fVec13)("int", iConst33)("float[2]", fRec22)("float[2]", fRec24)("float", fConst34)("float", fConst35)("float[2]", fRec25)("float[16384]", fVec14)("float", fConst36)("int", iConst37)("float[2048]", fVec15)("int", iConst38)("float[2]", fRec26)("float[2]", fRec28)("float", fConst39)("float", fConst40)("float[2]", fRec29)("float[16384]", fVec16)("float", fConst41)("int", iConst42)("float[1024]", fVec17)("int", iConst43)("float[2]", fRec30)("float[3]", fRec32)("float[3]", fRec33)("float[3]", fRec34)("float[3]", fRec35)("float[3]", fRec36)("float[3]", fRec37)("float[3]", fRec38)("float[3]", fRec39)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fVslider6)("float[3]", fIIR1)("float[3]", fVec18)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fVslider8)("float[3]", fIIR0)("float[3]", fVec19)("FAUSTFLOAT", fVslider9)("float[2]", fIIR2)("float", fConst44)("FAUSTFLOAT", fVslider10)("float[2]", fIIR3)("float[3]", fIIR5)("float[3]", fVec20)("float[3]", fIIR4)("float[3]", fVec21)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
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
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst6, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst5, kStruct)))), Int32(8191)))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst8, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst5, kStruct)))), Int32(1023)))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst11, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst12, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst11, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst13, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst11, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst14, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst16, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst17, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst16, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst18, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst16, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst19, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst21, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst22, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst21, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst23, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst21, kStruct)))), Int32(1023)))
	StoreVarInst(Address(fConst24, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst26, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst27, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst26, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst28, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst26, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst29, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst32, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst31, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst33, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst31, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst34, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst36, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst37, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst36, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst38, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst36, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst39, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst41, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst42, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst41, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst43, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst41, kStruct)))), Int32(1023)))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("-", Float(1.0f), Float(0.5f)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(2.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(6e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(3.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(315.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(1.5e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Float(0.4492f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Float(16.79f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(8192))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(8192))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(1024))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(8192))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2048))
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
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(8192))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2048))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(8192))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(1024))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(16384))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(8192))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2048))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(8192))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2048))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(16384))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2048))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(16384))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(1024))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(3))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(3))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(3))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(3))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(3))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(3))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(3))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(3))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(3))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(3))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(3))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(3))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(3))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(3))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 206 Store = 0 Binop = 172 [ { Int(&) = 1 } { Real(*) = 36 } { Real(+) = 37 } { Real(-) = 43 } { Real(/) = 55 } ] Mathop = 89 [ { cosf = 3 } { expf = 16 } { max_f = 21 } { min_f = 11 } { mydsp_faustpower2_f = 24 } { powf = 3 } { sqrtf = 10 } { tanf = 1 } ] Numbers = 109 Declare = 104 Cast = 12 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), FunCallInst("max_f", Float(5e+01f), FunCallInst("min_f", Float(1e+03f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(8.0f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), FunCallInst("max_f", Float(1.5e+03f), FunCallInst("min_f", Float(2.352e+04f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow8, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow6, kStack))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow9, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow10, kStack))))))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fSlow10, kStack))), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow10, kStack))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11, kStack)), BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow13, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow8, kStack))))))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(8.0f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))), Int32(8191)))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow18, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow20, kStack))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow21, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow22, kStack))))))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fSlow22, kStack))), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("+", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow25, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow20, kStack))))))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow18, kStack)))))
	DeclareVarInst("float", fSlow28, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow29, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow28, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow30, kStack))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow31, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow32, kStack))))))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fSlow32, kStack))), LoadVarInst(Address(fSlow33, kStack))))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow32, kStack))))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow35, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow30, kStack))))))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow28, kStack)))))
	DeclareVarInst("float", fSlow38, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow39, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow40, kStack))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow39, kStack))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow41, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow42, kStack))))))))
	DeclareVarInst("float", fSlow44, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fSlow42, kStack))), LoadVarInst(Address(fSlow43, kStack))))
	DeclareVarInst("float", fSlow45, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow42, kStack))))
	DeclareVarInst("float", fSlow46, kStack, BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", LoadVarInst(Address(fSlow43, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow45, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow40, kStack))))))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow38, kStack)))))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow48, kStack))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow50, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow51, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow52, kStack))))))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fSlow52, kStack))), LoadVarInst(Address(fSlow53, kStack))))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow52, kStack))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", LoadVarInst(Address(fSlow53, kStack)), BinopInst("+", LoadVarInst(Address(fSlow50, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow55, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow50, kStack))))))))
	DeclareVarInst("float", fSlow57, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow48, kStack)))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow59, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow58, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow59, kStack))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow62, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow59, kStack))))
	DeclareVarInst("float", fSlow63, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow61, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow62, kStack))))))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fSlow62, kStack))), LoadVarInst(Address(fSlow63, kStack))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow62, kStack))))
	DeclareVarInst("float", fSlow66, kStack, BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), BinopInst("+", LoadVarInst(Address(fSlow63, kStack)), BinopInst("+", LoadVarInst(Address(fSlow60, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow65, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow60, kStack))))))))
	DeclareVarInst("float", fSlow67, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow58, kStack)))))
	DeclareVarInst("float", fSlow68, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow69, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow68, kStack))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow69, kStack))))
	DeclareVarInst("float", fSlow71, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow70, kStack))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow69, kStack))))
	DeclareVarInst("float", fSlow73, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow71, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow72, kStack))))))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow71, kStack)), LoadVarInst(Address(fSlow72, kStack))), LoadVarInst(Address(fSlow73, kStack))))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow72, kStack))))
	DeclareVarInst("float", fSlow76, kStack, BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), BinopInst("+", LoadVarInst(Address(fSlow73, kStack)), BinopInst("+", LoadVarInst(Address(fSlow70, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow75, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow70, kStack))))))))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow68, kStack)))))
	DeclareVarInst("float", fSlow78, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow79, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow78, kStack))))
	DeclareVarInst("float", fSlow80, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow80, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow83, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow81, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow82, kStack))))))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow82, kStack))), LoadVarInst(Address(fSlow83, kStack))))
	DeclareVarInst("float", fSlow85, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("*", LoadVarInst(Address(fSlow78, kStack)), BinopInst("+", LoadVarInst(Address(fSlow83, kStack)), BinopInst("+", LoadVarInst(Address(fSlow80, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow85, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow80, kStack))))))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow78, kStack)))))
	DeclareVarInst("float", fSlow88, kStack, FunCallInst("max_f", Float(4e+01f), FunCallInst("min_f", Float(2.5e+03f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow89, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-15.0f), FunCallInst("min_f", Float(15.0f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))))
	DeclareVarInst("float", fSlow90, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow88, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow89, kStack)))))))
	DeclareVarInst("float", fSlow91, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow90, kStack))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow90, kStack)))))
	DeclareVarInst("float", fSlow92, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow88, kStack)))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow91, kStack)))))
	DeclareVarInst("float", fSlow93, kStack, FunCallInst("max_f", Float(1.6e+02f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))
	DeclareVarInst("float", fSlow94, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-15.0f), FunCallInst("min_f", Float(15.0f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))))
	DeclareVarInst("float", fSlow95, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow93, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow94, kStack)))))))
	DeclareVarInst("float", fSlow96, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow95, kStack))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow95, kStack)))))
	DeclareVarInst("float", fSlow97, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow93, kStack)))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow96, kStack)))))
	DeclareVarInst("float", fSlow98, kStack, FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))
	DeclareVarInst("float", fSlow99, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4e+01f), CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 439 Store = 122 Binop = 297 [ { Int(&) = 36 } { Int(+) = 2 } { Int(-) = 18 } { Int(<) = 1 } { Real(*) = 115 } { Real(+) = 83 } { Real(-) = 42 } ] Mathop = 0 Numbers = 345 Declare = 68 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(8191))])))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst6, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst8, kStruct))), Int32(1023))]))
		DeclareVarInst("float", fRec3, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp2, kStack))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst12, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp3, kStack)))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst13, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec7, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), BinopInst("+", LoadVarInst(Address(fRec34, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst17, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp4, kStack)))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst18, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec11, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp4, kStack))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), BinopInst("+", LoadVarInst(Address(fRec38, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst22, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp5, kStack)))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst23, kStruct))), Int32(1023))]))
		DeclareVarInst("float", fRec15, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp5, kStack))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), BinopInst("+", LoadVarInst(Address(fRec33, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp6, kStack)))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(8191))])))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp7, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp8, kStack)))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst28, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec19, kStack, NegInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp8, kStack)))))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), BinopInst("+", LoadVarInst(Address(fRec37, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow67, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst32, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp7, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp9, kStack)))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst33, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec23, kStack, NegInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp9, kStack)))))
		StoreVarInst(Address(fRec24, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), BinopInst("+", LoadVarInst(Address(fRec35, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)])), BinopInst("-", LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp7, kStack)))))
		StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp10, kStack)))
		StoreVarInst(Address(fRec26, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst38, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec27, kStack, BinopInst("*", Float(0.6f), NegInst(LoadVarInst(Address(fTemp10, kStack)))))
		StoreVarInst(Address(fRec28, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec29, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fRec29, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), BinopInst("+", LoadVarInst(Address(fRec39, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow87, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec30, kStruct)[Int32(1)])), BinopInst("-", LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst42, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp7, kStack)))))
		StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp11, kStack)))
		StoreVarInst(Address(fRec30, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43, kStruct))), Int32(1023))]))
		DeclareVarInst("float", fRec31, kStack, BinopInst("*", Float(0.6f), NegInst(LoadVarInst(Address(fTemp11, kStack)))))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStack))))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStack))))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("+", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fTemp13, kStack))))
		DeclareVarInst("float", fTemp15, kStack, BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStack))))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fRec15, kStack))))
		DeclareVarInst("float", fTemp17, kStack, BinopInst("+", LoadVarInst(Address(fTemp15, kStack)), LoadVarInst(Address(fTemp16, kStack))))
		DeclareVarInst("float", fTemp18, kStack, BinopInst("+", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fTemp17, kStack))))
		DeclareVarInst("float", fTemp19, kStack, BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fRec19, kStack))))
		DeclareVarInst("float", fTemp20, kStack, BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), LoadVarInst(Address(fRec23, kStack))))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("+", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fTemp20, kStack))))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), LoadVarInst(Address(fRec27, kStack))))
		DeclareVarInst("float", fTemp23, kStack, BinopInst("+", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fRec31, kStack))))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("+", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fTemp23, kStack))))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("+", LoadVarInst(Address(fTemp21, kStack)), LoadVarInst(Address(fTemp24, kStack))))
		StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp25, kStack))))
		StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp25, kStack))))
		DeclareVarInst("float", fTemp26, kStack, BinopInst("-", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fTemp17, kStack))))
		DeclareVarInst("float", fTemp27, kStack, BinopInst("-", LoadVarInst(Address(fTemp21, kStack)), LoadVarInst(Address(fTemp24, kStack))))
		StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp26, kStack)), LoadVarInst(Address(fTemp27, kStack))))
		StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), LoadVarInst(Address(fTemp27, kStack))))
		DeclareVarInst("float", fTemp28, kStack, BinopInst("-", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fTemp13, kStack))))
		DeclareVarInst("float", fTemp29, kStack, BinopInst("-", LoadVarInst(Address(fTemp15, kStack)), LoadVarInst(Address(fTemp16, kStack))))
		DeclareVarInst("float", fTemp30, kStack, BinopInst("+", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp29, kStack))))
		DeclareVarInst("float", fTemp31, kStack, BinopInst("-", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fTemp20, kStack))))
		DeclareVarInst("float", fTemp32, kStack, BinopInst("-", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fTemp23, kStack))))
		DeclareVarInst("float", fTemp33, kStack, BinopInst("+", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fTemp32, kStack))))
		StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fTemp33, kStack))))
		StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fTemp33, kStack))))
		DeclareVarInst("float", fTemp34, kStack, BinopInst("-", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp29, kStack))))
		DeclareVarInst("float", fTemp35, kStack, BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fTemp32, kStack))))
		StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp35, kStack))))
		StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp35, kStack))))
		DeclareVarInst("float", fTemp36, kStack, BinopInst("+", LoadVarInst(Address(fRec33, kStruct)[Int32(0)]), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp37, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp36, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp37, kStack)))
		StoreVarInst(Address(fVec18, kStruct)[Int32(0)], BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp37, kStack))))
		DeclareVarInst("float", fTemp38, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec18, kStruct)[Int32(2)])))
		DeclareVarInst("float", fTemp39, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp36, kStack))))
		DeclareVarInst("float", fTemp40, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp38, kStack)), LoadVarInst(Address(fTemp39, kStack))), BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), BinopInst("-", LoadVarInst(Address(fTemp38, kStack)), LoadVarInst(Address(fTemp39, kStack))))))
		DeclareVarInst("float", fTemp41, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp40, kStack)), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp41, kStack)))
		StoreVarInst(Address(fVec19, kStruct)[Int32(0)], BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp41, kStack))))
		DeclareVarInst("float", fTemp42, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec19, kStruct)[Int32(2)])))
		DeclareVarInst("float", fTemp43, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp40, kStack))))
		DeclareVarInst("float", fTemp44, kStack, BinopInst("+", LoadVarInst(Address(fSlow98, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp44, kStack)))
		DeclareVarInst("float", fTemp45, kStack, BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp44, kStack))))
		DeclareVarInst("float", fTemp46, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp45, kStack))))
		DeclareVarInst("float", fTemp47, kStack, NegInst(LoadVarInst(Address(fTemp45, kStack))))
		DeclareVarInst("float", fTemp48, kStack, BinopInst("+", LoadVarInst(Address(fTemp47, kStack)), BinopInst("*", LoadVarInst(Address(fConst44, kStruct)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp47, kStack))))))
		DeclareVarInst("float", fTemp49, kStack, BinopInst("+", LoadVarInst(Address(fSlow99, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp49, kStack)))
		DeclareVarInst("float", fTemp50, kStack, BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp49, kStack))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fTemp43, kStack))), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), BinopInst("-", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fTemp43, kStack))))), LoadVarInst(Address(fTemp46, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp48, kStack)))), LoadVarInst(Address(fTemp50, kStack)))))
		DeclareVarInst("float", fTemp51, kStack, BinopInst("-", LoadVarInst(Address(fRec33, kStruct)[Int32(0)]), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp52, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp51, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp52, kStack)))
		StoreVarInst(Address(fVec20, kStruct)[Int32(0)], BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp52, kStack))))
		DeclareVarInst("float", fTemp53, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fVec20, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fVec20, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec20, kStruct)[Int32(2)])))
		DeclareVarInst("float", fTemp54, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp51, kStack))))
		DeclareVarInst("float", fTemp55, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fTemp54, kStack))), BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), BinopInst("-", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fTemp54, kStack))))))
		DeclareVarInst("float", fTemp56, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp55, kStack)), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp56, kStack)))
		StoreVarInst(Address(fVec21, kStruct)[Int32(0)], BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp56, kStack))))
		DeclareVarInst("float", fTemp57, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec21, kStruct)[Int32(2)])))
		DeclareVarInst("float", fTemp58, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp55, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp50, kStack)), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp46, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp57, kStack)), LoadVarInst(Address(fTemp58, kStack))), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), BinopInst("-", LoadVarInst(Address(fTemp57, kStack)), LoadVarInst(Address(fTemp58, kStack))))))), BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), LoadVarInst(Address(fTemp48, kStack)))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(2)], LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(2)], LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(2)], LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(2)], LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(2)], LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(2)], LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(2)], LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(2)], LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(2)], LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec18, kStruct)[Int32(2)], LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec18, kStruct)[Int32(1)], LoadVarInst(Address(fVec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec19, kStruct)[Int32(2)], LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec19, kStruct)[Int32(1)], LoadVarInst(Address(fVec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(2)], LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec20, kStruct)[Int32(2)], LoadVarInst(Address(fVec20, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec20, kStruct)[Int32(1)], LoadVarInst(Address(fVec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(2)], LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec21, kStruct)[Int32(2)], LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec21, kStruct)[Int32(1)], LoadVarInst(Address(fVec21, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[8192], kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("int", iConst6, kStruct)
	DeclareVarInst("float", fVec1[8192], kStruct)
	DeclareVarInst("float", fConst7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("float", fVec2[1024], kStruct)
	DeclareVarInst("int", iConst8, kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fConst9, kStruct)
	DeclareVarInst("float", fConst10, kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("float", fVec3[8192], kStruct)
	DeclareVarInst("float", fConst11, kStruct)
	DeclareVarInst("int", iConst12, kStruct)
	DeclareVarInst("float", fVec4[2048], kStruct)
	DeclareVarInst("int", iConst13, kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fConst14, kStruct)
	DeclareVarInst("float", fConst15, kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fVec5[8192], kStruct)
	DeclareVarInst("float", fConst16, kStruct)
	DeclareVarInst("int", iConst17, kStruct)
	DeclareVarInst("float", fVec6[2048], kStruct)
	DeclareVarInst("int", iConst18, kStruct)
	DeclareVarInst("float", fRec10[2], kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("float", fConst19, kStruct)
	DeclareVarInst("float", fConst20, kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("float", fVec7[8192], kStruct)
	DeclareVarInst("float", fConst21, kStruct)
	DeclareVarInst("int", iConst22, kStruct)
	DeclareVarInst("float", fVec8[1024], kStruct)
	DeclareVarInst("int", iConst23, kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("float", fConst24, kStruct)
	DeclareVarInst("float", fConst25, kStruct)
	DeclareVarInst("float", fRec17[2], kStruct)
	DeclareVarInst("float", fVec9[16384], kStruct)
	DeclareVarInst("float", fConst26, kStruct)
	DeclareVarInst("int", iConst27, kStruct)
	DeclareVarInst("float", fVec10[8192], kStruct)
	DeclareVarInst("float", fVec11[2048], kStruct)
	DeclareVarInst("int", iConst28, kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("float", fRec20[2], kStruct)
	DeclareVarInst("float", fConst29, kStruct)
	DeclareVarInst("float", fConst30, kStruct)
	DeclareVarInst("float", fRec21[2], kStruct)
	DeclareVarInst("float", fVec12[8192], kStruct)
	DeclareVarInst("float", fConst31, kStruct)
	DeclareVarInst("int", iConst32, kStruct)
	DeclareVarInst("float", fVec13[2048], kStruct)
	DeclareVarInst("int", iConst33, kStruct)
	DeclareVarInst("float", fRec22[2], kStruct)
	DeclareVarInst("float", fRec24[2], kStruct)
	DeclareVarInst("float", fConst34, kStruct)
	DeclareVarInst("float", fConst35, kStruct)
	DeclareVarInst("float", fRec25[2], kStruct)
	DeclareVarInst("float", fVec14[16384], kStruct)
	DeclareVarInst("float", fConst36, kStruct)
	DeclareVarInst("int", iConst37, kStruct)
	DeclareVarInst("float", fVec15[2048], kStruct)
	DeclareVarInst("int", iConst38, kStruct)
	DeclareVarInst("float", fRec26[2], kStruct)
	DeclareVarInst("float", fRec28[2], kStruct)
	DeclareVarInst("float", fConst39, kStruct)
	DeclareVarInst("float", fConst40, kStruct)
	DeclareVarInst("float", fRec29[2], kStruct)
	DeclareVarInst("float", fVec16[16384], kStruct)
	DeclareVarInst("float", fConst41, kStruct)
	DeclareVarInst("int", iConst42, kStruct)
	DeclareVarInst("float", fVec17[1024], kStruct)
	DeclareVarInst("int", iConst43, kStruct)
	DeclareVarInst("float", fRec30[2], kStruct)
	DeclareVarInst("float", fRec32[3], kStruct)
	DeclareVarInst("float", fRec33[3], kStruct)
	DeclareVarInst("float", fRec34[3], kStruct)
	DeclareVarInst("float", fRec35[3], kStruct)
	DeclareVarInst("float", fRec36[3], kStruct)
	DeclareVarInst("float", fRec37[3], kStruct)
	DeclareVarInst("float", fRec38[3], kStruct)
	DeclareVarInst("float", fRec39[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("float", fIIR1[3], kStruct)
	DeclareVarInst("float", fVec18[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("float", fIIR0[3], kStruct)
	DeclareVarInst("float", fVec19[3], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	DeclareVarInst("float", fConst44, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider10, kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("float", fIIR5[3], kStruct)
	DeclareVarInst("float", fVec20[3], kStruct)
	DeclareVarInst("float", fIIR4[3], kStruct)
	DeclareVarInst("float", fVec21[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst6, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst5, kStruct)))), Int32(8191)))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst8, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst5, kStruct)))), Int32(1023)))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst11, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst12, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst11, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst13, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst11, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst14, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst16, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst17, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst16, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst18, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst16, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst19, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst21, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst22, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst21, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst23, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst21, kStruct)))), Int32(1023)))
	StoreVarInst(Address(fConst24, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst26, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst27, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst26, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst28, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst26, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst29, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst32, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst31, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst33, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst31, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst34, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst36, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst37, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst36, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst38, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst36, kStruct)))), Int32(2047)))
	StoreVarInst(Address(fConst39, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst41, kStruct), FunCallInst("floorf", BinopInst("+", Float(0.5f), BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(iConst42, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst41, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst43, kStruct), BinopInst("&", CastInst("int", BinopInst("+", Float(-1.0f), LoadVarInst(Address(fConst41, kStruct)))), Int32(1023)))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("-", Float(1.0f), Float(0.5f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Float(2.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Float(6e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Float(3.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Float(6e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Float(315.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Float(1.5e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Float(0.4492f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Float(16.79f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(8192))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(8192))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(1024))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(8192))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2048))
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
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(8192))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2048))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(8192))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(1024))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(16384))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(8192))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2048))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(8192))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2048))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(16384))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2048))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(16384))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(1024))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(3))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(3))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(3))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(3))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(3))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(3))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(3))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(3))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(3))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(3))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(3))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(3))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(3))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(3))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), FunCallInst("max_f", Float(5e+01f), FunCallInst("min_f", Float(1e+03f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(8.0f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), FunCallInst("max_f", Float(1.5e+03f), FunCallInst("min_f", Float(2.352e+04f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow8, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow6, kStack))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow9, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow10, kStack))))))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fSlow10, kStack))), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow10, kStack))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("+", LoadVarInst(Address(fSlow11, kStack)), BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow13, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow8, kStack))))))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(8.0f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow5, kStack)))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))), Int32(8191)))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow18, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow20, kStack))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow21, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow22, kStack))))))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fSlow22, kStack))), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("+", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow25, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow20, kStack))))))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow18, kStack)))))
	DeclareVarInst("float", fSlow28, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow29, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow28, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow30, kStack))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow31, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow32, kStack))))))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fSlow32, kStack))), LoadVarInst(Address(fSlow33, kStack))))
	DeclareVarInst("float", fSlow35, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow32, kStack))))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), BinopInst("+", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", LoadVarInst(Address(fSlow30, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow35, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow30, kStack))))))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow28, kStack)))))
	DeclareVarInst("float", fSlow38, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow40, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow39, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow40, kStack))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow39, kStack))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow41, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow42, kStack))))))))
	DeclareVarInst("float", fSlow44, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fSlow42, kStack))), LoadVarInst(Address(fSlow43, kStack))))
	DeclareVarInst("float", fSlow45, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow42, kStack))))
	DeclareVarInst("float", fSlow46, kStack, BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), BinopInst("+", LoadVarInst(Address(fSlow43, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow45, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow40, kStack))))))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow38, kStack)))))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow48, kStack))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow50, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow51, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow52, kStack))))))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fSlow52, kStack))), LoadVarInst(Address(fSlow53, kStack))))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow52, kStack))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", LoadVarInst(Address(fSlow53, kStack)), BinopInst("+", LoadVarInst(Address(fSlow50, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow55, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow50, kStack))))))))
	DeclareVarInst("float", fSlow57, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow48, kStack)))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow59, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow58, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow59, kStack))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow62, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow59, kStack))))
	DeclareVarInst("float", fSlow63, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow61, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow62, kStack))))))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fSlow62, kStack))), LoadVarInst(Address(fSlow63, kStack))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow62, kStack))))
	DeclareVarInst("float", fSlow66, kStack, BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), BinopInst("+", LoadVarInst(Address(fSlow63, kStack)), BinopInst("+", LoadVarInst(Address(fSlow60, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow65, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow60, kStack))))))))
	DeclareVarInst("float", fSlow67, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow58, kStack)))))
	DeclareVarInst("float", fSlow68, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow69, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow68, kStack))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow69, kStack))))
	DeclareVarInst("float", fSlow71, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow70, kStack))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow69, kStack))))
	DeclareVarInst("float", fSlow73, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow71, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow72, kStack))))))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow71, kStack)), LoadVarInst(Address(fSlow72, kStack))), LoadVarInst(Address(fSlow73, kStack))))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow72, kStack))))
	DeclareVarInst("float", fSlow76, kStack, BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), BinopInst("+", LoadVarInst(Address(fSlow73, kStack)), BinopInst("+", LoadVarInst(Address(fSlow70, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow75, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow70, kStack))))))))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow68, kStack)))))
	DeclareVarInst("float", fSlow78, kStack, FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow4, kStack))))))
	DeclareVarInst("float", fSlow79, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow78, kStack))))
	DeclareVarInst("float", fSlow80, kStack, BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow80, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow79, kStack))))
	DeclareVarInst("float", fSlow83, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow81, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow82, kStack))))))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("-", BinopInst("/", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow82, kStack))), LoadVarInst(Address(fSlow83, kStack))))
	DeclareVarInst("float", fSlow85, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow82, kStack))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("*", LoadVarInst(Address(fSlow78, kStack)), BinopInst("+", LoadVarInst(Address(fSlow83, kStack)), BinopInst("+", LoadVarInst(Address(fSlow80, kStack)), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow85, kStack))), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow80, kStack))))))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("+", Float(-1.0f), BinopInst("/", FunCallInst("expf", NegInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow15, kStack))))), LoadVarInst(Address(fSlow78, kStack)))))
	DeclareVarInst("float", fSlow88, kStack, FunCallInst("max_f", Float(4e+01f), FunCallInst("min_f", Float(2.5e+03f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow89, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-15.0f), FunCallInst("min_f", Float(15.0f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))))
	DeclareVarInst("float", fSlow90, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow88, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow89, kStack)))))))
	DeclareVarInst("float", fSlow91, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow90, kStack))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow90, kStack)))))
	DeclareVarInst("float", fSlow92, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow88, kStack)))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow91, kStack)))))
	DeclareVarInst("float", fSlow93, kStack, FunCallInst("max_f", Float(1.6e+02f), FunCallInst("min_f", Float(1e+04f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))
	DeclareVarInst("float", fSlow94, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-15.0f), FunCallInst("min_f", Float(15.0f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))))
	DeclareVarInst("float", fSlow95, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow93, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow94, kStack)))))))
	DeclareVarInst("float", fSlow96, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow95, kStack))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow95, kStack)))))
	DeclareVarInst("float", fSlow97, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow93, kStack)))), BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow96, kStack)))))
	DeclareVarInst("float", fSlow98, kStack, FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))
	DeclareVarInst("float", fSlow99, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), FunCallInst("max_f", Float(-7e+01f), FunCallInst("min_f", Float(4e+01f), CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(8191))])))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst6, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst8, kStruct))), Int32(1023))]))
			DeclareVarInst("float", fRec3, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp2, kStack))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst12, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp3, kStack)))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst13, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec7, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), BinopInst("+", LoadVarInst(Address(fRec34, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst17, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp4, kStack)))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst18, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec11, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp4, kStack))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), BinopInst("+", LoadVarInst(Address(fRec38, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst22, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp1, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp5, kStack)))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst23, kStruct))), Int32(1023))]))
			DeclareVarInst("float", fRec15, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp5, kStack))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), BinopInst("+", LoadVarInst(Address(fRec33, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp6, kStack)))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(8191))])))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp7, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp8, kStack)))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst28, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec19, kStack, NegInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp8, kStack)))))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), BinopInst("+", LoadVarInst(Address(fRec37, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow67, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst32, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp7, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp9, kStack)))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst33, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec23, kStack, NegInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp9, kStack)))))
			StoreVarInst(Address(fRec24, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), BinopInst("+", LoadVarInst(Address(fRec35, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)])), BinopInst("-", LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp7, kStack)))))
			StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp10, kStack)))
			StoreVarInst(Address(fRec26, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst38, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec27, kStack, BinopInst("*", Float(0.6f), NegInst(LoadVarInst(Address(fTemp10, kStack)))))
			StoreVarInst(Address(fRec28, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec29, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fRec29, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), BinopInst("+", LoadVarInst(Address(fRec39, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow87, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", Float(1e-20f), BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec30, kStruct)[Int32(1)])), BinopInst("-", LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst42, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp7, kStack)))))
			StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp11, kStack)))
			StoreVarInst(Address(fRec30, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43, kStruct))), Int32(1023))]))
			DeclareVarInst("float", fRec31, kStack, BinopInst("*", Float(0.6f), NegInst(LoadVarInst(Address(fTemp11, kStack)))))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStack))))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStack))))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("+", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fTemp13, kStack))))
			DeclareVarInst("float", fTemp15, kStack, BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStack))))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fRec15, kStack))))
			DeclareVarInst("float", fTemp17, kStack, BinopInst("+", LoadVarInst(Address(fTemp15, kStack)), LoadVarInst(Address(fTemp16, kStack))))
			DeclareVarInst("float", fTemp18, kStack, BinopInst("+", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fTemp17, kStack))))
			DeclareVarInst("float", fTemp19, kStack, BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fRec19, kStack))))
			DeclareVarInst("float", fTemp20, kStack, BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), LoadVarInst(Address(fRec23, kStack))))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("+", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fTemp20, kStack))))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), LoadVarInst(Address(fRec27, kStack))))
			DeclareVarInst("float", fTemp23, kStack, BinopInst("+", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fRec31, kStack))))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("+", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fTemp23, kStack))))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("+", LoadVarInst(Address(fTemp21, kStack)), LoadVarInst(Address(fTemp24, kStack))))
			StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp25, kStack))))
			StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp25, kStack))))
			DeclareVarInst("float", fTemp26, kStack, BinopInst("-", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fTemp17, kStack))))
			DeclareVarInst("float", fTemp27, kStack, BinopInst("-", LoadVarInst(Address(fTemp21, kStack)), LoadVarInst(Address(fTemp24, kStack))))
			StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp26, kStack)), LoadVarInst(Address(fTemp27, kStack))))
			StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), LoadVarInst(Address(fTemp27, kStack))))
			DeclareVarInst("float", fTemp28, kStack, BinopInst("-", LoadVarInst(Address(fTemp12, kStack)), LoadVarInst(Address(fTemp13, kStack))))
			DeclareVarInst("float", fTemp29, kStack, BinopInst("-", LoadVarInst(Address(fTemp15, kStack)), LoadVarInst(Address(fTemp16, kStack))))
			DeclareVarInst("float", fTemp30, kStack, BinopInst("+", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp29, kStack))))
			DeclareVarInst("float", fTemp31, kStack, BinopInst("-", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fTemp20, kStack))))
			DeclareVarInst("float", fTemp32, kStack, BinopInst("-", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fTemp23, kStack))))
			DeclareVarInst("float", fTemp33, kStack, BinopInst("+", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fTemp32, kStack))))
			StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fTemp33, kStack))))
			StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fTemp33, kStack))))
			DeclareVarInst("float", fTemp34, kStack, BinopInst("-", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp29, kStack))))
			DeclareVarInst("float", fTemp35, kStack, BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), LoadVarInst(Address(fTemp32, kStack))))
			StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp35, kStack))))
			StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp35, kStack))))
			DeclareVarInst("float", fTemp36, kStack, BinopInst("+", LoadVarInst(Address(fRec33, kStruct)[Int32(0)]), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp37, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp36, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp37, kStack)))
			StoreVarInst(Address(fVec18, kStruct)[Int32(0)], BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp37, kStack))))
			DeclareVarInst("float", fTemp38, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec18, kStruct)[Int32(2)])))
			DeclareVarInst("float", fTemp39, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp36, kStack))))
			DeclareVarInst("float", fTemp40, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp38, kStack)), LoadVarInst(Address(fTemp39, kStack))), BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), BinopInst("-", LoadVarInst(Address(fTemp38, kStack)), LoadVarInst(Address(fTemp39, kStack))))))
			DeclareVarInst("float", fTemp41, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp40, kStack)), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp41, kStack)))
			StoreVarInst(Address(fVec19, kStruct)[Int32(0)], BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp41, kStack))))
			DeclareVarInst("float", fTemp42, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec19, kStruct)[Int32(2)])))
			DeclareVarInst("float", fTemp43, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp40, kStack))))
			DeclareVarInst("float", fTemp44, kStack, BinopInst("+", LoadVarInst(Address(fSlow98, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp44, kStack)))
			DeclareVarInst("float", fTemp45, kStack, BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp44, kStack))))
			DeclareVarInst("float", fTemp46, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp45, kStack))))
			DeclareVarInst("float", fTemp47, kStack, NegInst(LoadVarInst(Address(fTemp45, kStack))))
			DeclareVarInst("float", fTemp48, kStack, BinopInst("+", LoadVarInst(Address(fTemp47, kStack)), BinopInst("*", LoadVarInst(Address(fConst44, kStruct)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp47, kStack))))))
			DeclareVarInst("float", fTemp49, kStack, BinopInst("+", LoadVarInst(Address(fSlow99, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp49, kStack)))
			DeclareVarInst("float", fTemp50, kStack, BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp49, kStack))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fTemp43, kStack))), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), BinopInst("-", LoadVarInst(Address(fTemp42, kStack)), LoadVarInst(Address(fTemp43, kStack))))), LoadVarInst(Address(fTemp46, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp48, kStack)))), LoadVarInst(Address(fTemp50, kStack)))))
			DeclareVarInst("float", fTemp51, kStack, BinopInst("-", LoadVarInst(Address(fRec33, kStruct)[Int32(0)]), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp52, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp51, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp52, kStack)))
			StoreVarInst(Address(fVec20, kStruct)[Int32(0)], BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp52, kStack))))
			DeclareVarInst("float", fTemp53, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), LoadVarInst(Address(fVec20, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fVec20, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec20, kStruct)[Int32(2)])))
			DeclareVarInst("float", fTemp54, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp51, kStack))))
			DeclareVarInst("float", fTemp55, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fTemp54, kStack))), BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), BinopInst("-", LoadVarInst(Address(fTemp53, kStack)), LoadVarInst(Address(fTemp54, kStack))))))
			DeclareVarInst("float", fTemp56, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp55, kStack)), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp56, kStack)))
			StoreVarInst(Address(fVec21, kStruct)[Int32(0)], BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp56, kStack))))
			DeclareVarInst("float", fTemp57, kStack, BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow96, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))), LoadVarInst(Address(fVec21, kStruct)[Int32(2)])))
			DeclareVarInst("float", fTemp58, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp55, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp50, kStack)), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp46, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp57, kStack)), LoadVarInst(Address(fTemp58, kStack))), BinopInst("*", LoadVarInst(Address(fSlow94, kStack)), BinopInst("-", LoadVarInst(Address(fTemp57, kStack)), LoadVarInst(Address(fTemp58, kStack))))))), BinopInst("*", LoadVarInst(Address(fTemp6, kStack)), LoadVarInst(Address(fTemp48, kStack)))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(2)], LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(2)], LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(2)], LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(2)], LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(2)], LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(2)], LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(2)], LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(2)], LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(2)], LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec18, kStruct)[Int32(2)], LoadVarInst(Address(fVec18, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec18, kStruct)[Int32(1)], LoadVarInst(Address(fVec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec19, kStruct)[Int32(2)], LoadVarInst(Address(fVec19, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec19, kStruct)[Int32(1)], LoadVarInst(Address(fVec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(2)], LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec20, kStruct)[Int32(2)], LoadVarInst(Address(fVec20, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec20, kStruct)[Int32(1)], LoadVarInst(Address(fVec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(2)], LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec21, kStruct)[Int32(2)], LoadVarInst(Address(fVec21, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec21, kStruct)[Int32(1)], LoadVarInst(Address(fVec21, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 72 bytes
Heap size int* = 0 bytes
Heap size real = 479792 bytes
Total heap size = 479864 bytes
Stack size in compute = 432 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fVec11 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec33 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec34 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec35 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec36 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec37 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec38 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec39 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4 size = 1 size_bytes = 4 read = 5 write = 0 ratio = 5
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fVec11 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec33 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec34 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec35 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec36 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec37 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec38 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec39 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = IOTA0 size = 1 size_bytes = 4 read = 37 write = 1 ratio = 38
Field = fVec0 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec3 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec5 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec10 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec12 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec7 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst22 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec8 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst23 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec16 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec9 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec10 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fVec11 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst28 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec20 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec12 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst32 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec13 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec22 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec24 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec25 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec14 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec15 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst38 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec26 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec28 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec16 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst42 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec17 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst43 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec30 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec32 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec33 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec34 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec35 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec36 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec37 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec38 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec39 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec18 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec19 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst44 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR5 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec20 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fIIR4 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec21 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            12995
  eval() cache hits:       3457 (26.6025%)
  eval() cache misses:     9538
  Loop detector calls:     9538
  Stack detector calls:    9538

--- Phase 3: Propagation ---
  propagate() calls:       6129
  propagate() cache hits:  1652 (26.9538%)
  propagate() cache misses:4477

--- Box Type Computation ---
  getBoxType() calls:      9520
  getBoxType() cache hits: 7741 (81.313%)
  getBoxType() computed:   1779

--- Environment Operations ---
  Environment lookups:     856
  Average lookup depth:    0.498832
  Env layers pushed:       1436

--- Pattern Matching ---
  build automaton calls:        25
  build total time (ms):        0.130126
  build avg time (ms):          0.00520504
  apply calls:                  455
  apply total time (ms):        0.585868
  apply avg time (ms):          0.00128762

--- Tree Operations ---
  Trees created:           55700
  Trees reused (hash):     129128 (69.8639% reuse rate)
  Property set ops:        24700
  Property get ops:        51305

--- Iteration Constructs ---
  par() iterations:        175
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
