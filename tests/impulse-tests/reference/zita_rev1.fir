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
	AddMetaDeclareInst(fVslider10, "1", "")
	AddMetaDeclareInst(fVslider10, "style", "knob")
	AddMetaDeclareInst(fVslider10, "tooltip", "Delay in ms before reverberation begins")
	AddMetaDeclareInst(fVslider10, "unit", "ms")
	AddVerticalSlider("In Delay", fVslider10, 6e+01f, 2e+01f, 1e+02f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("Decay Times in Bands (see tooltips)")
	AddMetaDeclareInst(fVslider9, "1", "")
	AddMetaDeclareInst(fVslider9, "scale", "log")
	AddMetaDeclareInst(fVslider9, "style", "knob")
	AddMetaDeclareInst(fVslider9, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies")
	AddMetaDeclareInst(fVslider9, "unit", "Hz")
	AddVerticalSlider("LF X", fVslider9, 2e+02f, 5e+01f, 1e+03f, 1.0f)
	AddMetaDeclareInst(fVslider8, "2", "")
	AddMetaDeclareInst(fVslider8, "scale", "log")
	AddMetaDeclareInst(fVslider8, "style", "knob")
	AddMetaDeclareInst(fVslider8, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band")
	AddMetaDeclareInst(fVslider8, "unit", "s")
	AddVerticalSlider("Low RT60", fVslider8, 3.0f, 1.0f, 8.0f, 0.1f)
	AddMetaDeclareInst(fVslider7, "3", "")
	AddMetaDeclareInst(fVslider7, "scale", "log")
	AddMetaDeclareInst(fVslider7, "style", "knob")
	AddMetaDeclareInst(fVslider7, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band")
	AddMetaDeclareInst(fVslider7, "unit", "s")
	AddVerticalSlider("Mid RT60", fVslider7, 2.0f, 1.0f, 8.0f, 0.1f)
	AddMetaDeclareInst(fVslider6, "4", "")
	AddMetaDeclareInst(fVslider6, "scale", "log")
	AddMetaDeclareInst(fVslider6, "style", "knob")
	AddMetaDeclareInst(fVslider6, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60")
	AddMetaDeclareInst(fVslider6, "unit", "Hz")
	AddVerticalSlider("HF Damping", fVslider6, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenHorizontalBox("RM Peaking Equalizer 1")
	AddMetaDeclareInst(fVslider4, "1", "")
	AddMetaDeclareInst(fVslider4, "scale", "log")
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddMetaDeclareInst(fVslider4, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1")
	AddMetaDeclareInst(fVslider4, "unit", "Hz")
	AddVerticalSlider("Eq1 Freq", fVslider4, 315.0f, 4e+01f, 2.5e+03f, 1.0f)
	AddMetaDeclareInst(fVslider5, "2", "")
	AddMetaDeclareInst(fVslider5, "style", "knob")
	AddMetaDeclareInst(fVslider5, "tooltip", "Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1")
	AddMetaDeclareInst(fVslider5, "unit", "dB")
	AddVerticalSlider("Eq1 Level", fVslider5, 0.0f, -15.0f, 15.0f, 0.1f)
	CloseboxInst
	AddMetaDeclareInst(0, "4", "")
	OpenHorizontalBox("RM Peaking Equalizer 2")
	AddMetaDeclareInst(fVslider2, "1", "")
	AddMetaDeclareInst(fVslider2, "scale", "log")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2")
	AddMetaDeclareInst(fVslider2, "unit", "Hz")
	AddVerticalSlider("Eq2 Freq", fVslider2, 1.5e+03f, 1.6e+02f, 1e+04f, 1.0f)
	AddMetaDeclareInst(fVslider3, "2", "")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2")
	AddMetaDeclareInst(fVslider3, "unit", "dB")
	AddVerticalSlider("Eq2 Level", fVslider3, 0.0f, -15.0f, 15.0f, 0.1f)
	CloseboxInst
	AddMetaDeclareInst(0, "5", "")
	OpenHorizontalBox("Output")
	AddMetaDeclareInst(fVslider1, "1", "")
	AddMetaDeclareInst(fVslider1, "style", "knob")
	AddMetaDeclareInst(fVslider1, "tooltip", "-1 = dry, 1 = wet")
	AddVerticalSlider("Dry/Wet Mix", fVslider1, 0.4492f, -1.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fVslider0, "2", "")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddMetaDeclareInst(fVslider0, "tooltip", "Output scale factor")
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("Level", fVslider0, 16.79f, -7e+01f, 4e+01f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "tanf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fVslider0)("float[2]", fRec0)("FAUSTFLOAT", fVslider1)("float[2]", fRec1)("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fVslider3)("FAUSTFLOAT", fVslider4)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fVslider6)("float", fConst2)("float", fConst3)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fVslider8)("float", fConst4)("FAUSTFLOAT", fVslider9)("float[2]", fRec15)("float[2]", fRec14)("int", IOTA0)("float[16384]", fVec0)("float", fConst5)("int", iConst6)("float[8192]", fVec1)("float", fConst7)("FAUSTFLOAT", fVslider10)("float[1024]", fVec2)("int", iConst8)("float[2]", fRec12)("float", fConst9)("float", fConst10)("float[2]", fRec19)("float[2]", fRec18)("float[16384]", fVec3)("float", fConst11)("int", iConst12)("float[2048]", fVec4)("int", iConst13)("float[2]", fRec16)("float", fConst14)("float", fConst15)("float[2]", fRec23)("float[2]", fRec22)("float[8192]", fVec5)("float", fConst16)("int", iConst17)("float[2048]", fVec6)("int", iConst18)("float[2]", fRec20)("float", fConst19)("float", fConst20)("float[2]", fRec27)("float[2]", fRec26)("float[16384]", fVec7)("float", fConst21)("int", iConst22)("float[2048]", fVec8)("int", iConst23)("float[2]", fRec24)("float", fConst24)("float", fConst25)("float[2]", fRec31)("float[2]", fRec30)("float[8192]", fVec9)("float", fConst26)("int", iConst27)("float[8192]", fVec10)("float[1024]", fVec11)("int", iConst28)("float[2]", fRec28)("float", fConst29)("float", fConst30)("float[2]", fRec35)("float[2]", fRec34)("float[8192]", fVec12)("float", fConst31)("int", iConst32)("float[2048]", fVec13)("int", iConst33)("float[2]", fRec32)("float", fConst34)("float", fConst35)("float[2]", fRec39)("float[2]", fRec38)("float[8192]", fVec14)("float", fConst36)("int", iConst37)("float[2048]", fVec15)("int", iConst38)("float[2]", fRec36)("float", fConst39)("float", fConst40)("float[2]", fRec43)("float[2]", fRec42)("float[8192]", fVec16)("float", fConst41)("int", iConst42)("float[1024]", fVec17)("int", iConst43)("float[2]", fRec40)("float[3]", fRec4)("float[3]", fRec5)("float[3]", fRec6)("float[3]", fRec7)("float[3]", fRec8)("float[3]", fRec9)("float[3]", fRec10)("float[3]", fRec11)("float[3]", fRec3)("float[3]", fRec2)("float[3]", fRec45)("float[3]", fRec44)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst6, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst5, kStruct)))), Int32(16383)))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst8, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst5, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst11, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst12, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst11, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst13, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst11, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst14, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst16, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst17, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst16, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst18, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst16, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst19, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst21, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst22, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst21, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst23, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst21, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst24, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst26, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst27, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst26, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst28, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst26, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(fConst29, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst32, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst31, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst33, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst31, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst34, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst36, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst37, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst36, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst38, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst36, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst39, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst41, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst42, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst41, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst43, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst41, kStruct)), Float(-1.0f))), Int32(1023)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(16.79f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.4492f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.5e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(315.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
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
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(16384))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(8192))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(1024))
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
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(16384))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2048))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(8192))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2048))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(16384))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2048))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(8192))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(8192))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(1024))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(8192))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2048))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(8192))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2048))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(8192))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(1024))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(3))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(3))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(3))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(3))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(3))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(3))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(3))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(3))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(3))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(3))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(3))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 180 Store = 0 Binop = 141 [ { Int(&) = 1 } { Real(*) = 30 } { Real(+) = 29 } { Real(-) = 35 } { Real(/) = 46 } ] Mathop = 67 [ { cosf = 3 } { expf = 16 } { max_f = 10 } { mydsp_faustpower2_f = 24 } { powf = 3 } { sqrtf = 10 } { tanf = 1 } ] Numbers = 73 Declare = 95 Cast = 12 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow3, kStack)))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow4, kStack))), BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow6, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow7, kStack)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow8, kStack))), BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow13, kStack)))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("/", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fSlow15, kStack))))
	DeclareVarInst("float", fSlow17, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow14, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow15, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("-", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fSlow17, kStack))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), BinopInst("+", LoadVarInst(Address(fSlow17, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow16, kStack))))))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow12, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), CastInst("float", LoadVarInst(Address(fVslider9, kStruct)))))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow22, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("int", iSlow25, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))), Int32(8191)))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow27, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("/", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow28, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow29, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("-", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("+", LoadVarInst(Address(fSlow31, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow30, kStack))))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow26, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow35, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow36, kStack)))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow36, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("/", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow37, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fSlow40, kStack))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow39, kStack))))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow35, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow44, kStack))))
	DeclareVarInst("float", fSlow46, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow45, kStack)))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow45, kStack))))
	DeclareVarInst("float", fSlow48, kStack, BinopInst("/", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fSlow47, kStack))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow46, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow47, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("-", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), BinopInst("+", LoadVarInst(Address(fSlow49, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow48, kStack))))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow44, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow54, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow53, kStack))))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow54, kStack)))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow54, kStack))))
	DeclareVarInst("float", fSlow57, kStack, BinopInst("/", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fSlow56, kStack))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow55, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow56, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("-", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fSlow58, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), BinopInst("+", LoadVarInst(Address(fSlow58, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow57, kStack))))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow53, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow62, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow63, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow62, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow63, kStack)))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow63, kStack))))
	DeclareVarInst("float", fSlow66, kStack, BinopInst("/", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fSlow65, kStack))))
	DeclareVarInst("float", fSlow67, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow64, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow65, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow68, kStack, BinopInst("-", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fSlow67, kStack))))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), BinopInst("+", LoadVarInst(Address(fSlow67, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow66, kStack))))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow62, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow71, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow72, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow72, kStack)))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow72, kStack))))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fSlow74, kStack))))
	DeclareVarInst("float", fSlow76, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow73, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow74, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("-", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fSlow76, kStack))))
	DeclareVarInst("float", fSlow78, kStack, BinopInst("*", LoadVarInst(Address(fSlow71, kStack)), BinopInst("+", LoadVarInst(Address(fSlow76, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow75, kStack))))))
	DeclareVarInst("float", fSlow79, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow71, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow80, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow81, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow80, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow81, kStack))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("/", LoadVarInst(Address(fSlow82, kStack)), LoadVarInst(Address(fSlow83, kStack))))
	DeclareVarInst("float", fSlow85, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow82, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow83, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("-", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fSlow85, kStack))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("*", LoadVarInst(Address(fSlow80, kStack)), BinopInst("+", LoadVarInst(Address(fSlow85, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow84, kStack))))))
	DeclareVarInst("float", fSlow88, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow80, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow89, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow6, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow90, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow2, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), Float(1.0f))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 475 Store = 110 Binop = 362 [ { Int(&) = 36 } { Int(+) = 2 } { Int(-) = 18 } { Int(<) = 1 } { Real(*) = 97 } { Real(+) = 171 } { Real(-) = 37 } ] Mathop = 0 Numbers = 379 Declare = 46 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(1.0f)))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec12, kStruct)[Int32(1)])), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst6, kStruct))), Int32(16383))])))
		DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp2, kStack)))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25, kStack))), Int32(8191))])))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst8, kStruct))), Int32(1023))]))
		DeclareVarInst("float", fRec13, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fTemp1, kStack)))))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fRec18, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec16, kStruct)[Int32(1)])), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst12, kStruct))), Int32(16383))])))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("-", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst13, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec17, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fTemp4, kStack)))))
		StoreVarInst(Address(fRec23, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fRec9, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fRec22, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst17, kStruct))), Int32(8191))]), BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec20, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp5, kStack)))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst18, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec21, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec27, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow51, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec26, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec24, kStruct)[Int32(1)])), LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst22, kStruct))), Int32(16383))]))))
		StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp6, kStack)))
		StoreVarInst(Address(fRec24, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst23, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec25, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp6, kStack)))))
		StoreVarInst(Address(fRec31, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec10, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec30, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fRec30, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec30, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp7, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp7, kStack)))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25, kStack))), Int32(8191))])))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("-", LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27, kStruct))), Int32(8191))]), BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec28, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp9, kStack)))
		StoreVarInst(Address(fRec28, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst28, kStruct))), Int32(1023))]))
		DeclareVarInst("float", fRec29, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp9, kStack))))
		StoreVarInst(Address(fRec35, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow69, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("-", LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst32, kStruct))), Int32(8191))]), BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec32, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp10, kStack)))
		StoreVarInst(Address(fRec32, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst33, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec33, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp10, kStack))))
		StoreVarInst(Address(fRec39, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow78, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow79, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37, kStruct))), Int32(8191))])), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp11, kStack)))
		StoreVarInst(Address(fRec36, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst38, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec37, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp11, kStack))))
		StoreVarInst(Address(fRec43, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow87, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec42, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst42, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp8, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec40, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp12, kStack)))
		StoreVarInst(Address(fRec40, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43, kStruct))), Int32(1023))]))
		DeclareVarInst("float", fRec41, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp12, kStack))))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("+", LoadVarInst(Address(fRec41, kStack)), LoadVarInst(Address(fRec37, kStack))))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("+", LoadVarInst(Address(fRec29, kStack)), BinopInst("+", LoadVarInst(Address(fRec33, kStack)), LoadVarInst(Address(fTemp13, kStack)))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp14, kStack)))))))))))))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp14, kStack)))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fRec21, kStack)))))))))))
		DeclareVarInst("float", fTemp15, kStack, BinopInst("+", LoadVarInst(Address(fRec33, kStack)), LoadVarInst(Address(fRec29, kStack))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp13, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), LoadVarInst(Address(fTemp15, kStack))))))))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), LoadVarInst(Address(fTemp13, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp15, kStack))))))))))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("+", LoadVarInst(Address(fRec41, kStack)), LoadVarInst(Address(fRec33, kStack))))
		DeclareVarInst("float", fTemp17, kStack, BinopInst("+", LoadVarInst(Address(fRec37, kStack)), LoadVarInst(Address(fRec29, kStack))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp16, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp17, kStack))))))))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp16, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp17, kStack))))))))))
		DeclareVarInst("float", fTemp18, kStack, BinopInst("+", LoadVarInst(Address(fRec41, kStack)), LoadVarInst(Address(fRec29, kStack))))
		DeclareVarInst("float", fTemp19, kStack, BinopInst("+", LoadVarInst(Address(fRec37, kStack)), LoadVarInst(Address(fRec33, kStack))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp18, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp19, kStack))))))))))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp18, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp19, kStack))))))))))
		DeclareVarInst("float", fTemp20, kStack, BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("+", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fTemp21, kStack))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp22, kStack)), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp23, kStack, BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp23, kStack)), BinopInst("+", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp21, kStack))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp23, kStack))), LoadVarInst(Address(fTemp22, kStack)))))))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("*", LoadVarInst(Address(fSlow90, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp26, kStack, BinopInst("+", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp25, kStack))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp27, kStack, BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp28, kStack, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp27, kStack)), BinopInst("+", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp25, kStack))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp27, kStack))), LoadVarInst(Address(fTemp26, kStack))))))), BinopInst("*", LoadVarInst(Address(fTemp7, kStack)), LoadVarInst(Address(fTemp28, kStack)))))))
		DeclareVarInst("float", fTemp29, kStack, BinopInst("*", Float(0.37f), BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp30, kStack, BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp31, kStack, BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fTemp30, kStack))))
		StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp32, kStack, BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp33, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp30, kStack))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec45, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp32, kStack))), LoadVarInst(Address(fTemp31, kStack)))))))
		DeclareVarInst("float", fTemp34, kStack, BinopInst("*", LoadVarInst(Address(fSlow90, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp35, kStack, BinopInst("+", LoadVarInst(Address(fTemp33, kStack)), LoadVarInst(Address(fTemp34, kStack))))
		StoreVarInst(Address(fRec44, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp35, kStack)), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)]))))
		DeclareVarInst("float", fTemp36, kStack, BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(0)])))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp36, kStack)), BinopInst("+", LoadVarInst(Address(fTemp33, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp34, kStack))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec44, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp36, kStack))), LoadVarInst(Address(fTemp35, kStack))))))), BinopInst("*", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fTemp28, kStack)))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(2)], LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec45, kStruct)[Int32(2)], LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec44, kStruct)[Int32(2)], LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[16384], kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("int", iConst6, kStruct)
	DeclareVarInst("float", fVec1[8192], kStruct)
	DeclareVarInst("float", fConst7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider10, kStruct)
	DeclareVarInst("float", fVec2[1024], kStruct)
	DeclareVarInst("int", iConst8, kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("float", fConst9, kStruct)
	DeclareVarInst("float", fConst10, kStruct)
	DeclareVarInst("float", fRec19[2], kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("float", fVec3[16384], kStruct)
	DeclareVarInst("float", fConst11, kStruct)
	DeclareVarInst("int", iConst12, kStruct)
	DeclareVarInst("float", fVec4[2048], kStruct)
	DeclareVarInst("int", iConst13, kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("float", fConst14, kStruct)
	DeclareVarInst("float", fConst15, kStruct)
	DeclareVarInst("float", fRec23[2], kStruct)
	DeclareVarInst("float", fRec22[2], kStruct)
	DeclareVarInst("float", fVec5[8192], kStruct)
	DeclareVarInst("float", fConst16, kStruct)
	DeclareVarInst("int", iConst17, kStruct)
	DeclareVarInst("float", fVec6[2048], kStruct)
	DeclareVarInst("int", iConst18, kStruct)
	DeclareVarInst("float", fRec20[2], kStruct)
	DeclareVarInst("float", fConst19, kStruct)
	DeclareVarInst("float", fConst20, kStruct)
	DeclareVarInst("float", fRec27[2], kStruct)
	DeclareVarInst("float", fRec26[2], kStruct)
	DeclareVarInst("float", fVec7[16384], kStruct)
	DeclareVarInst("float", fConst21, kStruct)
	DeclareVarInst("int", iConst22, kStruct)
	DeclareVarInst("float", fVec8[2048], kStruct)
	DeclareVarInst("int", iConst23, kStruct)
	DeclareVarInst("float", fRec24[2], kStruct)
	DeclareVarInst("float", fConst24, kStruct)
	DeclareVarInst("float", fConst25, kStruct)
	DeclareVarInst("float", fRec31[2], kStruct)
	DeclareVarInst("float", fRec30[2], kStruct)
	DeclareVarInst("float", fVec9[8192], kStruct)
	DeclareVarInst("float", fConst26, kStruct)
	DeclareVarInst("int", iConst27, kStruct)
	DeclareVarInst("float", fVec10[8192], kStruct)
	DeclareVarInst("float", fVec11[1024], kStruct)
	DeclareVarInst("int", iConst28, kStruct)
	DeclareVarInst("float", fRec28[2], kStruct)
	DeclareVarInst("float", fConst29, kStruct)
	DeclareVarInst("float", fConst30, kStruct)
	DeclareVarInst("float", fRec35[2], kStruct)
	DeclareVarInst("float", fRec34[2], kStruct)
	DeclareVarInst("float", fVec12[8192], kStruct)
	DeclareVarInst("float", fConst31, kStruct)
	DeclareVarInst("int", iConst32, kStruct)
	DeclareVarInst("float", fVec13[2048], kStruct)
	DeclareVarInst("int", iConst33, kStruct)
	DeclareVarInst("float", fRec32[2], kStruct)
	DeclareVarInst("float", fConst34, kStruct)
	DeclareVarInst("float", fConst35, kStruct)
	DeclareVarInst("float", fRec39[2], kStruct)
	DeclareVarInst("float", fRec38[2], kStruct)
	DeclareVarInst("float", fVec14[8192], kStruct)
	DeclareVarInst("float", fConst36, kStruct)
	DeclareVarInst("int", iConst37, kStruct)
	DeclareVarInst("float", fVec15[2048], kStruct)
	DeclareVarInst("int", iConst38, kStruct)
	DeclareVarInst("float", fRec36[2], kStruct)
	DeclareVarInst("float", fConst39, kStruct)
	DeclareVarInst("float", fConst40, kStruct)
	DeclareVarInst("float", fRec43[2], kStruct)
	DeclareVarInst("float", fRec42[2], kStruct)
	DeclareVarInst("float", fVec16[8192], kStruct)
	DeclareVarInst("float", fConst41, kStruct)
	DeclareVarInst("int", iConst42, kStruct)
	DeclareVarInst("float", fVec17[1024], kStruct)
	DeclareVarInst("int", iConst43, kStruct)
	DeclareVarInst("float", fRec40[2], kStruct)
	DeclareVarInst("float", fRec4[3], kStruct)
	DeclareVarInst("float", fRec5[3], kStruct)
	DeclareVarInst("float", fRec6[3], kStruct)
	DeclareVarInst("float", fRec7[3], kStruct)
	DeclareVarInst("float", fRec8[3], kStruct)
	DeclareVarInst("float", fRec9[3], kStruct)
	DeclareVarInst("float", fRec10[3], kStruct)
	DeclareVarInst("float", fRec11[3], kStruct)
	DeclareVarInst("float", fRec3[3], kStruct)
	DeclareVarInst("float", fRec2[3], kStruct)
	DeclareVarInst("float", fRec45[3], kStruct)
	DeclareVarInst("float", fRec44[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst6, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst5, kStruct)))), Int32(16383)))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst8, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst5, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst11, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst12, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst11, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst13, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst11, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst14, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst16, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst17, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fConst16, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst18, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst16, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst19, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst21, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst22, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fConst21, kStruct)))), Int32(16383)))
	StoreVarInst(Address(iConst23, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst21, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst24, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst26, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst27, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fConst26, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst28, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst26, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(fConst29, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst32, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fConst31, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst33, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst31, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst34, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst36, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst37, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fConst36, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst38, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst36, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(fConst39, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst40, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst41, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst42, kStruct), BinopInst("&", CastInst("int", BinopInst("-", LoadVarInst(Address(fConst39, kStruct)), LoadVarInst(Address(fConst41, kStruct)))), Int32(8191)))
	StoreVarInst(Address(iConst43, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst41, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(16.79f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.4492f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.5e+03f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(315.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
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
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(16384))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(8192))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(1024))
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
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(16384))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2048))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(8192))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2048))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(16384))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2048))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(8192))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(8192))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(1024))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(8192))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2048))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(8192))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2048))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(8192))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(1024))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(3))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(3))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(3))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(3))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(3))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(3))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(3))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(3))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(3))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(3))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(3))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct)))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow3, kStack)))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow4, kStack))), BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow6, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow7, kStack)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow8, kStack))), BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow13, kStack)))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("/", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fSlow15, kStack))))
	DeclareVarInst("float", fSlow17, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow14, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow15, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("-", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fSlow17, kStack))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), BinopInst("+", LoadVarInst(Address(fSlow17, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow16, kStack))))))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow12, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), CastInst("float", LoadVarInst(Address(fVslider9, kStruct)))))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow22, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("int", iSlow25, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))), Int32(8191)))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow27, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow26, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow27, kStack)))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow27, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("/", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fSlow29, kStack))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow28, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow29, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow32, kStack, BinopInst("-", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("+", LoadVarInst(Address(fSlow31, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow30, kStack))))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow26, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow35, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow36, kStack)))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow36, kStack))))
	DeclareVarInst("float", fSlow39, kStack, BinopInst("/", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fSlow38, kStack))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow37, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fSlow40, kStack))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), BinopInst("+", LoadVarInst(Address(fSlow40, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow39, kStack))))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow35, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow44, kStack))))
	DeclareVarInst("float", fSlow46, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow45, kStack)))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow45, kStack))))
	DeclareVarInst("float", fSlow48, kStack, BinopInst("/", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fSlow47, kStack))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow46, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow47, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("-", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), BinopInst("+", LoadVarInst(Address(fSlow49, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow48, kStack))))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow44, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow54, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow53, kStack))))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow54, kStack)))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow54, kStack))))
	DeclareVarInst("float", fSlow57, kStack, BinopInst("/", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fSlow56, kStack))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow55, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow56, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("-", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fSlow58, kStack))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), BinopInst("+", LoadVarInst(Address(fSlow58, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow57, kStack))))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow53, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow62, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow63, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow62, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow63, kStack)))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow63, kStack))))
	DeclareVarInst("float", fSlow66, kStack, BinopInst("/", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fSlow65, kStack))))
	DeclareVarInst("float", fSlow67, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow64, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow65, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow68, kStack, BinopInst("-", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fSlow67, kStack))))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), BinopInst("+", LoadVarInst(Address(fSlow67, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow66, kStack))))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow62, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow71, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow72, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fSlow72, kStack)))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow72, kStack))))
	DeclareVarInst("float", fSlow75, kStack, BinopInst("/", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fSlow74, kStack))))
	DeclareVarInst("float", fSlow76, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow73, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow74, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("-", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fSlow76, kStack))))
	DeclareVarInst("float", fSlow78, kStack, BinopInst("*", LoadVarInst(Address(fSlow71, kStack)), BinopInst("+", LoadVarInst(Address(fSlow76, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow75, kStack))))))
	DeclareVarInst("float", fSlow79, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow71, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow80, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow11, kStack))))))
	DeclareVarInst("float", fSlow81, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow80, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow81, kStack))))
	DeclareVarInst("float", fSlow84, kStack, BinopInst("/", LoadVarInst(Address(fSlow82, kStack)), LoadVarInst(Address(fSlow83, kStack))))
	DeclareVarInst("float", fSlow85, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow82, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow83, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("-", LoadVarInst(Address(fSlow84, kStack)), LoadVarInst(Address(fSlow85, kStack))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("*", LoadVarInst(Address(fSlow80, kStack)), BinopInst("+", LoadVarInst(Address(fSlow85, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow84, kStack))))))
	DeclareVarInst("float", fSlow88, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst40, kStruct)), LoadVarInst(Address(fSlow20, kStack))))), LoadVarInst(Address(fSlow80, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow89, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow6, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow90, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow2, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), Float(1.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(1.0f)))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec12, kStruct)[Int32(1)])), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst6, kStruct))), Int32(16383))])))
			DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp2, kStack)))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25, kStack))), Int32(8191))])))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst8, kStruct))), Int32(1023))]))
			DeclareVarInst("float", fRec13, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fTemp1, kStack)))))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fRec18, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec16, kStruct)[Int32(1)])), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst12, kStruct))), Int32(16383))])))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("-", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst13, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec17, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fTemp4, kStack)))))
			StoreVarInst(Address(fRec23, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fRec9, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fRec22, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst17, kStruct))), Int32(8191))]), BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec20, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp5, kStack)))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst18, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec21, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec27, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow51, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec26, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec24, kStruct)[Int32(1)])), LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst22, kStruct))), Int32(16383))]))))
			StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp6, kStack)))
			StoreVarInst(Address(fRec24, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst23, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec25, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp6, kStack)))))
			StoreVarInst(Address(fRec31, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec10, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec30, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fRec30, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec30, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp7, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp7, kStack)))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25, kStack))), Int32(8191))])))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("-", LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27, kStruct))), Int32(8191))]), BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec28, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp9, kStack)))
			StoreVarInst(Address(fRec28, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst28, kStruct))), Int32(1023))]))
			DeclareVarInst("float", fRec29, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp9, kStack))))
			StoreVarInst(Address(fRec35, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow69, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("-", LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst32, kStruct))), Int32(8191))]), BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec32, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp10, kStack)))
			StoreVarInst(Address(fRec32, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst33, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec33, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp10, kStack))))
			StoreVarInst(Address(fRec39, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow78, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow79, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37, kStruct))), Int32(8191))])), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp11, kStack)))
			StoreVarInst(Address(fRec36, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst38, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec37, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp11, kStack))))
			StoreVarInst(Address(fRec43, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow87, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec42, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst42, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp8, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec40, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp12, kStack)))
			StoreVarInst(Address(fRec40, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43, kStruct))), Int32(1023))]))
			DeclareVarInst("float", fRec41, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp12, kStack))))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("+", LoadVarInst(Address(fRec41, kStack)), LoadVarInst(Address(fRec37, kStack))))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("+", LoadVarInst(Address(fRec29, kStack)), BinopInst("+", LoadVarInst(Address(fRec33, kStack)), LoadVarInst(Address(fTemp13, kStack)))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp14, kStack)))))))))))))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp14, kStack)))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fRec21, kStack)))))))))))
			DeclareVarInst("float", fTemp15, kStack, BinopInst("+", LoadVarInst(Address(fRec33, kStack)), LoadVarInst(Address(fRec29, kStack))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp13, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), LoadVarInst(Address(fTemp15, kStack))))))))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), LoadVarInst(Address(fTemp13, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp15, kStack))))))))))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("+", LoadVarInst(Address(fRec41, kStack)), LoadVarInst(Address(fRec33, kStack))))
			DeclareVarInst("float", fTemp17, kStack, BinopInst("+", LoadVarInst(Address(fRec37, kStack)), LoadVarInst(Address(fRec29, kStack))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp16, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp17, kStack))))))))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp16, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp17, kStack))))))))))
			DeclareVarInst("float", fTemp18, kStack, BinopInst("+", LoadVarInst(Address(fRec41, kStack)), LoadVarInst(Address(fRec29, kStack))))
			DeclareVarInst("float", fTemp19, kStack, BinopInst("+", LoadVarInst(Address(fRec37, kStack)), LoadVarInst(Address(fRec33, kStack))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp18, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp19, kStack))))))))))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec17, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStack)), LoadVarInst(Address(fTemp18, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec36, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec13, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStack)), LoadVarInst(Address(fTemp19, kStack))))))))))
			DeclareVarInst("float", fTemp20, kStack, BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("+", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fTemp21, kStack))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp22, kStack)), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp23, kStack, BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp23, kStack)), BinopInst("+", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp21, kStack))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp23, kStack))), LoadVarInst(Address(fTemp22, kStack)))))))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("*", LoadVarInst(Address(fSlow90, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp26, kStack, BinopInst("+", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp25, kStack))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp27, kStack, BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp28, kStack, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp27, kStack)), BinopInst("+", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp25, kStack))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp27, kStack))), LoadVarInst(Address(fTemp26, kStack))))))), BinopInst("*", LoadVarInst(Address(fTemp7, kStack)), LoadVarInst(Address(fTemp28, kStack)))))))
			DeclareVarInst("float", fTemp29, kStack, BinopInst("*", Float(0.37f), BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp30, kStack, BinopInst("*", LoadVarInst(Address(fSlow89, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp31, kStack, BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fTemp30, kStack))))
			StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp31, kStack)), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp32, kStack, BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp33, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("+", LoadVarInst(Address(fTemp29, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp30, kStack))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec45, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp32, kStack))), LoadVarInst(Address(fTemp31, kStack)))))))
			DeclareVarInst("float", fTemp34, kStack, BinopInst("*", LoadVarInst(Address(fSlow90, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp35, kStack, BinopInst("+", LoadVarInst(Address(fTemp33, kStack)), LoadVarInst(Address(fTemp34, kStack))))
			StoreVarInst(Address(fRec44, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp35, kStack)), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)]))))
			DeclareVarInst("float", fTemp36, kStack, BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(0)])))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp36, kStack)), BinopInst("+", LoadVarInst(Address(fTemp33, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp34, kStack))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec44, kStruct)[Int32(2)]), LoadVarInst(Address(fTemp36, kStack))), LoadVarInst(Address(fTemp35, kStack))))))), BinopInst("*", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fTemp28, kStack)))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(2)], LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec45, kStruct)[Int32(2)], LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec44, kStruct)[Int32(2)], LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 72 bytes
Heap size int* = 0 bytes
Heap size real = 479740 bytes
Total heap size = 479812 bytes
Stack size in compute = 396 bytes

======= Variable access in Control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fVec11 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec43 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec10 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec45 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec44 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 5 write = 0 ratio = 5
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fVec11 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec43 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec10 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec45 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec44 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = IOTA0 size = 1 size_bytes = 4 read = 37 write = 1 ratio = 38
Field = fVec0 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec12 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec3 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec16 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec22 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec5 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec20 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec26 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec7 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst22 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec8 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst23 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec24 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec31 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec30 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec9 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec10 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fVec11 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst28 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec28 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec34 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec12 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst32 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec13 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec32 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec38 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec14 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec15 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst38 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec36 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec43 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec42 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec16 size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst42 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec17 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst43 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec40 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fRec4 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec5 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec6 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec7 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec8 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec9 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec10 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec11 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec3 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec2 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec45 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec44 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
