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
	AddMetaDeclareInst(fVslider0, "1", "")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddMetaDeclareInst(fVslider0, "tooltip", "Delay in ms before reverberation begins")
	AddMetaDeclareInst(fVslider0, "unit", "ms")
	AddVerticalSlider("In Delay", fVslider0, 6e+01f, 2e+01f, 1e+02f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("Decay Times in Bands (see tooltips)")
	AddMetaDeclareInst(fVslider3, "1", "")
	AddMetaDeclareInst(fVslider3, "scale", "log")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies")
	AddMetaDeclareInst(fVslider3, "unit", "Hz")
	AddVerticalSlider("LF X", fVslider3, 2e+02f, 5e+01f, 1e+03f, 1.0f)
	AddMetaDeclareInst(fVslider4, "2", "")
	AddMetaDeclareInst(fVslider4, "scale", "log")
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddMetaDeclareInst(fVslider4, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band")
	AddMetaDeclareInst(fVslider4, "unit", "s")
	AddVerticalSlider("Low RT60", fVslider4, 3.0f, 1.0f, 8.0f, 0.1f)
	AddMetaDeclareInst(fVslider2, "3", "")
	AddMetaDeclareInst(fVslider2, "scale", "log")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band")
	AddMetaDeclareInst(fVslider2, "unit", "s")
	AddVerticalSlider("Mid RT60", fVslider2, 2.0f, 1.0f, 8.0f, 0.1f)
	AddMetaDeclareInst(fVslider1, "4", "")
	AddMetaDeclareInst(fVslider1, "scale", "log")
	AddMetaDeclareInst(fVslider1, "style", "knob")
	AddMetaDeclareInst(fVslider1, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60")
	AddMetaDeclareInst(fVslider1, "unit", "Hz")
	AddVerticalSlider("HF Damping", fVslider1, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f)
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
	AddMetaDeclareInst(fVslider10, "1", "")
	AddMetaDeclareInst(fVslider10, "style", "knob")
	AddMetaDeclareInst(fVslider10, "tooltip", "-1 = dry, 1 = wet")
	AddVerticalSlider("Dry/Wet Mix", fVslider10, 0.4492f, -1.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fVslider9, "2", "")
	AddMetaDeclareInst(fVslider9, "style", "knob")
	AddMetaDeclareInst(fVslider9, "tooltip", "Output scale factor")
	AddMetaDeclareInst(fVslider9, "unit", "dB")
	AddVerticalSlider("Level", fVslider9, 16.79f, -7e+01f, 4e+01f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[8192]", fVec4SE)("FAUSTFLOAT", fVslider0)("int", fSampleRate)("float", fConst0KI)("float", fConst1KI)("FAUSTFLOAT", fVslider1)("float", fConst2KI)("FAUSTFLOAT", fVslider2)("float", fConst3KI)("float", fConst4KI)("FAUSTFLOAT", fVslider3)("float", fConst5KI)("float[2]", fVec9SE)("FAUSTFLOAT", fVslider4)("float[2]", fVec7SE)("float[16384]", fVec13SE)("float", fConst6KI)("int", iConst7KI)("float", fConst8KI)("float", fConst9KI)("float[2]", fVec18SE)("float[2]", fVec16SE)("float[8192]", fVec22SE)("float", fConst10KI)("int", iConst11KI)("float", fConst12KI)("float", fConst13KI)("float[2]", fVec28SE)("float[2]", fVec26SE)("float[8192]", fVec32SE)("float", fConst14KI)("int", iConst15KI)("float[8192]", fVec34SE)("float", fConst16KI)("float", fConst17KI)("float[2]", fVec40SE)("float[2]", fVec38SE)("float[8192]", fVec44SE)("float", fConst18KI)("int", iConst19KI)("float", fConst20KI)("float", fConst21KI)("float[2]", fVec53SE)("float[2]", fVec51SE)("float[16384]", fVec57SE)("float", fConst22KI)("int", iConst23KI)("float", fConst24KI)("float", fConst25KI)("float[2]", fVec63SE)("float[2]", fVec61SE)("float[16384]", fVec67SE)("float", fConst26KI)("int", iConst27KI)("float", fConst28KI)("float", fConst29KI)("float[2]", fVec73SE)("float[2]", fVec71SE)("float[8192]", fVec77SE)("float", fConst30KI)("int", iConst31KI)("float", fConst32KI)("float", fConst33KI)("float[2]", fVec84SE)("float[2]", fVec82SE)("float[8192]", fVec88SE)("float", fConst34KI)("int", iConst35KI)("float[2]", fVec52SE)("float[4]", fVec54SE)("float[1024]", fVec93SE)("int", iConst36KI)("float[2]", fVec50SE)("float[2]", fVec48SE)("float[2]", fVec8SE)("float[4]", fVec10SE)("float[2048]", fVec97SE)("int", iConst37KI)("float[2]", fVec6SE)("float[2]", fVec0SE)("float[2]", fVec17SE)("float[4]", fVec19SE)("float[2048]", fVec101SE)("int", iConst38KI)("float[2]", fVec24SE)("float[2]", fVec1SE)("float[2]", fVec62SE)("float[4]", fVec64SE)("float[2048]", fVec105SE)("int", iConst39KI)("float[2]", fVec60SE)("float[2]", fVec49SE)("float[2]", fVec27SE)("float[4]", fVec29SE)("float[1024]", fVec109SE)("int", iConst40KI)("float[2]", fVec36SE)("float[2]", fVec2SE)("float[2]", fVec72SE)("float[4]", fVec74SE)("float[2048]", fVec113SE)("int", iConst41KI)("float[2]", fVec79SE)("float[2]", fVec70SE)("float[2]", fVec83SE)("float[4]", fVec85SE)("float[2048]", fVec117SE)("int", iConst42KI)("float[2]", fVec90SE)("float[2]", fVec81SE)("float[2]", fVec39SE)("float[4]", fVec41SE)("float[1024]", fVec121SE)("int", iConst43KI)("float[2]", fVec46SE)("float[2]", fVec3SE)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fVslider6)("float[2]", fVec126SE)("float[4]", fVec127SE)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fVslider8)("float[2]", fVec131SE)("float[4]", fVec132SE)("FAUSTFLOAT", fVslider9)("float[2]", fVec134SE)("FAUSTFLOAT", fVslider10)("float[2]", fVec136SE)("float[2]", fVec140SE)("float[4]", fVec141SE)("float[2]", fVec145SE)("float[4]", fVec146SE)>)

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
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst3KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst3KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst7KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), MinusInst(LoadVarInst(Address(fConst6KI, kStruct))))), Int32(16383)))
	StoreVarInst(Address(fConst8KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst9KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst10KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst11KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst8KI, kStruct)), MinusInst(LoadVarInst(Address(fConst10KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst12KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst13KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst12KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst14KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst15KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst12KI, kStruct)), MinusInst(LoadVarInst(Address(fConst14KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst16KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst17KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst18KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst19KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst16KI, kStruct)), MinusInst(LoadVarInst(Address(fConst18KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst20KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst21KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst20KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst22KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst23KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst20KI, kStruct)), MinusInst(LoadVarInst(Address(fConst22KI, kStruct))))), Int32(16383)))
	StoreVarInst(Address(fConst24KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst25KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst24KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst26KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst27KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst24KI, kStruct)), MinusInst(LoadVarInst(Address(fConst26KI, kStruct))))), Int32(16383)))
	StoreVarInst(Address(fConst28KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst29KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst28KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst30KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst31KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst28KI, kStruct)), MinusInst(LoadVarInst(Address(fConst30KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst32KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst33KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst32KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst34KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst35KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst32KI, kStruct)), MinusInst(LoadVarInst(Address(fConst34KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(iConst36KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst22KI, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(iConst37KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst6KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst38KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst10KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst39KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst26KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst40KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst14KI, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(iConst41KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst30KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst42KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst34KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst43KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst18KI, kStruct)), Float(-1.0f))), Int32(1023)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(315.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(1.5e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(16.79f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(0.4492f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(8192))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(16384))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(8192))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(8192))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(8192))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec40SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(8192))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec44SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec53SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(16384))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec57SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec63SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(16384))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec73SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec71SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(8192))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec84SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(8192))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec88SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec54SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(1024))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec93SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec50SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(4))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2048))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec97SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(4))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2048))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec101SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec62SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(4))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec64SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2048))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec105SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec60SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec49SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(1024))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec109SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(4))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2048))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec113SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec79SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec85SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2048))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec117SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec90SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec81SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec39SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(4))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(1024))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec121SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(2))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec126SE, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(4))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec127SE, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(2))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec131SE, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(4))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec132SE, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec134SE, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(2))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec136SE, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(2))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec140SE, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(4))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec141SE, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(2))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec145SE, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(4))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec146SE, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 184 Store = 0 Binop = 141 [ { Int(&) = 1 } { Real(*) = 30 } { Real(+) = 64 } { Real(/) = 46 } ] Mathop = 71 [ { cosf = 3 } { expf = 20 } { max_f = 10 } { mydsp_faustpower2_f = 24 } { powf = 3 } { sqrtf = 10 } { tanf = 1 } ] Numbers = 73 Declare = 99 Cast = 12 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("int", iSlow0BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))), Int32(8191)))
	DeclareVarInst("float", fSlow1BE, kStack, FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow4BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow3BE, kStack))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow4BE, kStack))))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow4BE, kStack)))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow6BE, kStack))))
	DeclareVarInst("float", fSlow8BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow6BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow7BE, kStack)), MinusInst(LoadVarInst(Address(fSlow8BE, kStack)))))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow7BE, kStack))))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow11BE, kStack)))))
	DeclareVarInst("float", fSlow14BE, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow15BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow3BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow16BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow17BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow16BE, kStack))))
	DeclareVarInst("float", fSlow18BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow17BE, kStack))))))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow17BE, kStack)))))
	DeclareVarInst("float", fSlow20BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow18BE, kStack)), LoadVarInst(Address(fSlow19BE, kStack))))
	DeclareVarInst("float", fSlow21BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow18BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow19BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow22BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow20BE, kStack)), MinusInst(LoadVarInst(Address(fSlow21BE, kStack)))))
	DeclareVarInst("float", fSlow23BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow16BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow21BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow20BE, kStack))))))
	DeclareVarInst("float", fSlow24BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow16BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("/", LoadVarInst(Address(fConst13KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow26BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow25BE, kStack))))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow26BE, kStack))))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow26BE, kStack)))))
	DeclareVarInst("float", fSlow29BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow27BE, kStack)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow30BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow27BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow28BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow29BE, kStack)), MinusInst(LoadVarInst(Address(fSlow30BE, kStack)))))
	DeclareVarInst("float", fSlow32BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow25BE, kStack)))))
	DeclareVarInst("float", fSlow33BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow30BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow29BE, kStack))))))
	DeclareVarInst("float", fSlow34BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst13KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow32BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow35BE, kStack, BinopInst("/", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow36BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow35BE, kStack))))))
	DeclareVarInst("float", fSlow37BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow36BE, kStack))))))
	DeclareVarInst("float", fSlow38BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow36BE, kStack)))))
	DeclareVarInst("float", fSlow39BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fSlow38BE, kStack))))
	DeclareVarInst("float", fSlow40BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow37BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow41BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow39BE, kStack)), MinusInst(LoadVarInst(Address(fSlow40BE, kStack)))))
	DeclareVarInst("float", fSlow42BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow35BE, kStack)))))
	DeclareVarInst("float", fSlow43BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow42BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow40BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow39BE, kStack))))))
	DeclareVarInst("float", fSlow44BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow42BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow45BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst21KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow46BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow45BE, kStack))))
	DeclareVarInst("float", fSlow47BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow46BE, kStack))))))
	DeclareVarInst("float", fSlow48BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow46BE, kStack)))))
	DeclareVarInst("float", fSlow49BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow47BE, kStack)), LoadVarInst(Address(fSlow48BE, kStack))))
	DeclareVarInst("float", fSlow50BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow47BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow48BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow51BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow49BE, kStack)), MinusInst(LoadVarInst(Address(fSlow50BE, kStack)))))
	DeclareVarInst("float", fSlow52BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow45BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow50BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow49BE, kStack))))))
	DeclareVarInst("float", fSlow53BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst21KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow45BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow54BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow55BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow54BE, kStack))))
	DeclareVarInst("float", fSlow56BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow55BE, kStack))))))
	DeclareVarInst("float", fSlow57BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow55BE, kStack)))))
	DeclareVarInst("float", fSlow58BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow56BE, kStack)), LoadVarInst(Address(fSlow57BE, kStack))))
	DeclareVarInst("float", fSlow59BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow56BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow57BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow60BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow58BE, kStack)), MinusInst(LoadVarInst(Address(fSlow59BE, kStack)))))
	DeclareVarInst("float", fSlow61BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow59BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow58BE, kStack))))))
	DeclareVarInst("float", fSlow62BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow54BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow63BE, kStack, BinopInst("/", LoadVarInst(Address(fConst29KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow64BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow63BE, kStack))))))
	DeclareVarInst("float", fSlow65BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow64BE, kStack))))))
	DeclareVarInst("float", fSlow66BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow64BE, kStack)))))
	DeclareVarInst("float", fSlow67BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fSlow66BE, kStack))))
	DeclareVarInst("float", fSlow68BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow65BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow69BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow67BE, kStack)), MinusInst(LoadVarInst(Address(fSlow68BE, kStack)))))
	DeclareVarInst("float", fSlow70BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow63BE, kStack)))))
	DeclareVarInst("float", fSlow71BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow68BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow67BE, kStack))))))
	DeclareVarInst("float", fSlow72BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst29KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow70BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow73BE, kStack, BinopInst("/", LoadVarInst(Address(fConst33KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow74BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow73BE, kStack))))))
	DeclareVarInst("float", fSlow75BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow74BE, kStack))))))
	DeclareVarInst("float", fSlow76BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow74BE, kStack)))))
	DeclareVarInst("float", fSlow77BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fSlow76BE, kStack))))
	DeclareVarInst("float", fSlow78BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow75BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow76BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow79BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), MinusInst(LoadVarInst(Address(fSlow78BE, kStack)))))
	DeclareVarInst("float", fSlow80BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow73BE, kStack)))))
	DeclareVarInst("float", fSlow81BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow80BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow78BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow77BE, kStack))))))
	DeclareVarInst("float", fSlow82BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst33KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow80BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow83BE, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow84BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow85BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow83BE, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow84BE, kStack)))))))
	DeclareVarInst("float", fSlow86BE, kStack, BinopInst("/", BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow85BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow85BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow87BE, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow83BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow86BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow88BE, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow89BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))
	DeclareVarInst("float", fSlow90BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow88BE, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow89BE, kStack)))))))
	DeclareVarInst("float", fSlow91BE, kStack, BinopInst("/", BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow90BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow90BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow92BE, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow88BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow91BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow93BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct)))))))
	DeclareVarInst("float", fSlow94BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fVslider10, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 679 Store = 80 Binop = 634 [ { Int(&) = 202 } { Int(+) = 2 } { Int(-) = 80 } { Int(<) = 1 } { Real(*) = 111 } { Real(+) = 238 } ] Mathop = 0 Numbers = 320 Declare = 78 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp4SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp4SE, kStack)))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow0BE, kStack))), Int32(8191))]))
		DeclareVarInst("float", fTemp6SE, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fTemp5SE, kStack))))
		DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp8SE, kStack)))), MinusInst(LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst7KI, kStruct))), Int32(16383))]))
		DeclareVarInst("float", fRec2SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp7SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp9SE, kStack))))))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fRec2SE, kStack)))
		DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp11SE, kStack)))), MinusInst(LoadVarInst(Address(fVec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow24BE, kStack)), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp12SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst11KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp6SE, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec5SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp12SE, kStack))))
		DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fRec5SE, kStack)))
		DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp14SE, kStack)))), MinusInst(LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp15SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp15SE, kStack)))
		DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow0BE, kStack))), Int32(8191))]))
		DeclareVarInst("float", fTemp17SE, kStack, BinopInst("*", Float(-0.3f), LoadVarInst(Address(fTemp16SE, kStack))))
		DeclareVarInst("float", fTemp18SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst15KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp17SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec8SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp18SE, kStack))))
		DeclareVarInst("float", fTemp19SE, kStack, LoadVarInst(Address(fRec8SE, kStack)))
		DeclareVarInst("float", fTemp20SE, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fTemp16SE, kStack))))
		DeclareVarInst("float", fTemp21SE, kStack, LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp21SE, kStack)))), MinusInst(LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41BE, kStack)), LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow43BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp21SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp22SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec44SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst19KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp20SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec11SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp22SE, kStack))))
		DeclareVarInst("float", fTemp23SE, kStack, LoadVarInst(Address(fRec11SE, kStack)))
		DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp25SE, kStack, LoadVarInst(Address(fVec49SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp26SE, kStack, LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec53SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp27SE, kStack)))), MinusInst(LoadVarInst(Address(fVec54SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow51BE, kStack)), LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow52BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp27SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp28SE, kStack, LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst23KI, kStruct))), Int32(16383))]))
		DeclareVarInst("float", fRec14SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp26SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp28SE, kStack))))))
		DeclareVarInst("float", fTemp29SE, kStack, LoadVarInst(Address(fRec14SE, kStack)))
		DeclareVarInst("float", fTemp30SE, kStack, LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec63SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec63SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp30SE, kStack)))), MinusInst(LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow60BE, kStack)), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp30SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), LoadVarInst(Address(fVec63SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp31SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec60SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27KI, kStruct))), Int32(16383))])))
		DeclareVarInst("float", fRec17SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp31SE, kStack))))
		DeclareVarInst("float", fTemp32SE, kStack, LoadVarInst(Address(fRec17SE, kStack)))
		DeclareVarInst("float", fTemp33SE, kStack, LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp34SE, kStack, LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp34SE, kStack)))), MinusInst(LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow71BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp34SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp35SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst31KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp17SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec20SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp35SE, kStack))))
		DeclareVarInst("float", fTemp36SE, kStack, LoadVarInst(Address(fRec20SE, kStack)))
		DeclareVarInst("float", fTemp37SE, kStack, LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp38SE, kStack, LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp38SE, kStack)))), MinusInst(LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow79BE, kStack)), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow81BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp38SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow82BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp39SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp20SE, kStack)), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst35KI, kStruct))), Int32(8191))])), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec90SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec23SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp39SE, kStack))))
		DeclareVarInst("float", fTemp40SE, kStack, LoadVarInst(Address(fRec23SE, kStack)))
		StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))))
		StoreVarInst(Address(fVec54SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp41SE, kStack, BinopInst("*", Float(-0.3f), LoadVarInst(Address(fTemp5SE, kStack))))
		StoreVarInst(Address(fVec93SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp26SE, kStack))), LoadVarInst(Address(fTemp28SE, kStack))), LoadVarInst(Address(fTemp41SE, kStack))))
		StoreVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec93SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst36KI, kStruct))), Int32(1023))]))
		StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
		StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp7SE, kStack))), LoadVarInst(Address(fTemp9SE, kStack))), LoadVarInst(Address(fTemp41SE, kStack))))
		StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
		StoreVarInst(Address(fVec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec101SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp12SE, kStack)))
		StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec101SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst38KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))))
		StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec105SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp31SE, kStack)))
		StoreVarInst(Address(fVec60SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec105SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst39KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec49SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec60SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))))
		StoreVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec109SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp18SE, kStack)))
		StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec109SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst40KI, kStruct))), Int32(1023))]))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
		StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec113SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp35SE, kStack)))
		StoreVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec113SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst41KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
		StoreVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp39SE, kStack)))
		StoreVarInst(Address(fVec90SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst42KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec90SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))))
		StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec121SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp22SE, kStack)))
		StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec121SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43KI, kStruct))), Int32(1023))]))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp42SE, kStack, LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp43SE, kStack, LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp44SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp42SE, kStack)), LoadVarInst(Address(fTemp43SE, kStack))))
		DeclareVarInst("float", fTemp45SE, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp44SE, kStack))))
		DeclareVarInst("float", fTemp46SE, kStack, LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec126SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp45SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec126SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fTemp46SE, kStack))))))
		DeclareVarInst("float", fTemp47SE, kStack, LoadVarInst(Address(fVec126SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp47SE, kStack)))
		DeclareVarInst("float", fTemp48SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fVec126SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp49SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
		DeclareVarInst("float", fTemp50SE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fTemp45SE, kStack))), LoadVarInst(Address(fTemp46SE, kStack))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp46SE, kStack)), LoadVarInst(Address(fTemp48SE, kStack))), BinopInst("*", Float(-0.37f), LoadVarInst(Address(fTemp44SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack))))))))
		DeclareVarInst("float", fTemp51SE, kStack, LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp50SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fTemp51SE, kStack))))))
		DeclareVarInst("float", fTemp52SE, kStack, LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp52SE, kStack)))
		StoreVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow93BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp53SE, kStack, LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow94BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp54SE, kStack, BinopInst("+", LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(1.0f)))
		DeclareVarInst("float", fTemp55SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp56SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
		DeclareVarInst("float", fTemp57SE, kStack, BinopInst("+", Float(1.0f), BinopInst("*", Float(-0.5f), LoadVarInst(Address(fTemp54SE, kStack)))))
		DeclareVarInst("float", fTemp58SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp42SE, kStack)), MinusInst(LoadVarInst(Address(fTemp43SE, kStack)))))
		DeclareVarInst("float", fTemp59SE, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp58SE, kStack))))
		DeclareVarInst("float", fTemp60SE, kStack, LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp59SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fTemp60SE, kStack))))))
		DeclareVarInst("float", fTemp61SE, kStack, LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec141SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp61SE, kStack)))
		DeclareVarInst("float", fTemp62SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp63SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
		DeclareVarInst("float", fTemp64SE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp62SE, kStack)), LoadVarInst(Address(fTemp59SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp60SE, kStack)), LoadVarInst(Address(fTemp62SE, kStack))), BinopInst("*", Float(-0.37f), LoadVarInst(Address(fTemp58SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack))))))))
		DeclareVarInst("float", fTemp65SE, kStack, LoadVarInst(Address(fVec146SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp64SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fTemp65SE, kStack))))))
		DeclareVarInst("float", fTemp66SE, kStack, LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec146SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp66SE, kStack)))
		DeclareVarInst("float", fTemp67SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp68SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec146SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp54SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp55SE, kStack)), LoadVarInst(Address(fTemp50SE, kStack))), LoadVarInst(Address(fTemp51SE, kStack))), MinusInst(LoadVarInst(Address(fTemp56SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow89BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp51SE, kStack)), LoadVarInst(Address(fTemp55SE, kStack))), BinopInst("*", Float(-0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fTemp45SE, kStack))), LoadVarInst(Address(fTemp46SE, kStack))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp46SE, kStack)), LoadVarInst(Address(fTemp48SE, kStack))), MinusInst(LoadVarInst(Address(fTemp45SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))))))), MinusInst(LoadVarInst(Address(fTemp56SE, kStack)))))))), BinopInst("*", LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))]), LoadVarInst(Address(fTemp57SE, kStack)))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp54SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp67SE, kStack)), LoadVarInst(Address(fTemp64SE, kStack))), LoadVarInst(Address(fTemp65SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow89BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp65SE, kStack)), LoadVarInst(Address(fTemp67SE, kStack))), BinopInst("*", Float(-0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp62SE, kStack)), LoadVarInst(Address(fTemp59SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp60SE, kStack)), LoadVarInst(Address(fTemp62SE, kStack))), MinusInst(LoadVarInst(Address(fTemp59SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack)))))))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))))))), BinopInst("*", LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))]), LoadVarInst(Address(fTemp57SE, kStack)))))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec4SE[8192], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("float", fConst3KI, kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("float", fConst5KI, kStruct)
	// Recursion delay fVec9SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec9SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	// Recursion delay fVec7SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec7SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec13SE[16384], kStruct)
	DeclareVarInst("float", fConst6KI, kStruct)
	DeclareVarInst("int", iConst7KI, kStruct)
	// Recursion delay fRec2SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst8KI, kStruct)
	DeclareVarInst("float", fConst9KI, kStruct)
	// Recursion delay fVec18SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec18SE[2], kStruct)
	// Recursion delay fVec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec16SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec22SE[8192], kStruct)
	DeclareVarInst("float", fConst10KI, kStruct)
	DeclareVarInst("int", iConst11KI, kStruct)
	// Recursion delay fRec5SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst12KI, kStruct)
	DeclareVarInst("float", fConst13KI, kStruct)
	// Recursion delay fVec28SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec28SE[2], kStruct)
	// Recursion delay fVec26SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec26SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec32SE[8192], kStruct)
	DeclareVarInst("float", fConst14KI, kStruct)
	DeclareVarInst("int", iConst15KI, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec34SE[8192], kStruct)
	// Recursion delay fRec8SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst16KI, kStruct)
	DeclareVarInst("float", fConst17KI, kStruct)
	// Recursion delay fVec40SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec40SE[2], kStruct)
	// Recursion delay fVec38SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec38SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec44SE[8192], kStruct)
	DeclareVarInst("float", fConst18KI, kStruct)
	DeclareVarInst("int", iConst19KI, kStruct)
	// Recursion delay fRec11SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst20KI, kStruct)
	DeclareVarInst("float", fConst21KI, kStruct)
	// Recursion delay fVec53SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec53SE[2], kStruct)
	// Recursion delay fVec51SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec51SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec57SE[16384], kStruct)
	DeclareVarInst("float", fConst22KI, kStruct)
	DeclareVarInst("int", iConst23KI, kStruct)
	// Recursion delay fRec14SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst24KI, kStruct)
	DeclareVarInst("float", fConst25KI, kStruct)
	// Recursion delay fVec63SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec63SE[2], kStruct)
	// Recursion delay fVec61SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec61SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec67SE[16384], kStruct)
	DeclareVarInst("float", fConst26KI, kStruct)
	DeclareVarInst("int", iConst27KI, kStruct)
	// Recursion delay fRec17SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst28KI, kStruct)
	DeclareVarInst("float", fConst29KI, kStruct)
	// Recursion delay fVec73SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec73SE[2], kStruct)
	// Recursion delay fVec71SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec71SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec77SE[8192], kStruct)
	DeclareVarInst("float", fConst30KI, kStruct)
	DeclareVarInst("int", iConst31KI, kStruct)
	// Recursion delay fRec20SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst32KI, kStruct)
	DeclareVarInst("float", fConst33KI, kStruct)
	// Recursion delay fVec84SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec84SE[2], kStruct)
	// Recursion delay fVec82SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec82SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec88SE[8192], kStruct)
	DeclareVarInst("float", fConst34KI, kStruct)
	DeclareVarInst("int", iConst35KI, kStruct)
	// Recursion delay fRec23SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Recursion delay fVec52SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec52SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec54SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec93SE[1024], kStruct)
	DeclareVarInst("int", iConst36KI, kStruct)
	// Recursion delay fVec50SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec50SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec48SE[2], kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec10SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec97SE[2048], kStruct)
	DeclareVarInst("int", iConst37KI, kStruct)
	// Recursion delay fVec6SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec6SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	// Recursion delay fVec17SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec17SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec19SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec101SE[2048], kStruct)
	DeclareVarInst("int", iConst38KI, kStruct)
	// Recursion delay fVec24SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec24SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Recursion delay fVec62SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec62SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec64SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec105SE[2048], kStruct)
	DeclareVarInst("int", iConst39KI, kStruct)
	// Recursion delay fVec60SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec60SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec49SE[2], kStruct)
	// Recursion delay fVec27SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec27SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec29SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec109SE[1024], kStruct)
	DeclareVarInst("int", iConst40KI, kStruct)
	// Recursion delay fVec36SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec36SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
	// Recursion delay fVec72SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec72SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec74SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec113SE[2048], kStruct)
	DeclareVarInst("int", iConst41KI, kStruct)
	// Recursion delay fVec79SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec79SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec70SE[2], kStruct)
	// Recursion delay fVec83SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec83SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec85SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec117SE[2048], kStruct)
	DeclareVarInst("int", iConst42KI, kStruct)
	// Recursion delay fVec90SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec90SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec81SE[2], kStruct)
	// Recursion delay fVec39SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec39SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec41SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec121SE[1024], kStruct)
	DeclareVarInst("int", iConst43KI, kStruct)
	// Recursion delay fVec46SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec46SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	// Recursion delay fVec126SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec126SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec127SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	// Recursion delay fVec131SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec131SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec132SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	// Recursion delay fVec134SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec134SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider10, kStruct)
	// Recursion delay fVec136SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec136SE[2], kStruct)
	// Recursion delay fVec140SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec140SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec141SE[4], kStruct)
	// Recursion delay fVec145SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec145SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec146SE[4], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst3KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst3KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("/", Float(3.1415927f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst7KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), MinusInst(LoadVarInst(Address(fConst6KI, kStruct))))), Int32(16383)))
	StoreVarInst(Address(fConst8KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst9KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst10KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst11KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst8KI, kStruct)), MinusInst(LoadVarInst(Address(fConst10KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst12KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst13KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst12KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst14KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst15KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst12KI, kStruct)), MinusInst(LoadVarInst(Address(fConst14KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst16KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst17KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst18KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst19KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst16KI, kStruct)), MinusInst(LoadVarInst(Address(fConst18KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst20KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst21KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst20KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst22KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst23KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst20KI, kStruct)), MinusInst(LoadVarInst(Address(fConst22KI, kStruct))))), Int32(16383)))
	StoreVarInst(Address(fConst24KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst25KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst24KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst26KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst27KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst24KI, kStruct)), MinusInst(LoadVarInst(Address(fConst26KI, kStruct))))), Int32(16383)))
	StoreVarInst(Address(fConst28KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst29KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst28KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst30KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst31KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst28KI, kStruct)), MinusInst(LoadVarInst(Address(fConst30KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(fConst32KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst33KI, kStruct), BinopInst("*", Float(6.9077554f), BinopInst("/", LoadVarInst(Address(fConst32KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst34KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst35KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst32KI, kStruct)), MinusInst(LoadVarInst(Address(fConst34KI, kStruct))))), Int32(8191)))
	StoreVarInst(Address(iConst36KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst22KI, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(iConst37KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst6KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst38KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst10KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst39KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst26KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst40KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst14KI, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(iConst41KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst30KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst42KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst34KI, kStruct)), Float(-1.0f))), Int32(2047)))
	StoreVarInst(Address(iConst43KI, kStruct), BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fConst18KI, kStruct)), Float(-1.0f))), Int32(1023)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(6e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(6e+03f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(3.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(315.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(1.5e+03f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(16.79f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(0.4492f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(8192))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(16384))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(8192))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(8192))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(8192))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec40SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(8192))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec44SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec53SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(16384))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec57SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec63SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(16384))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec73SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec71SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(8192))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec84SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(8192))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec88SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec54SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(1024))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec93SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec50SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(4))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2048))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec97SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(4))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2048))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec101SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec62SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(4))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec64SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2048))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec105SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec60SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec49SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(1024))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec109SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(4))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2048))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec113SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec79SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec85SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2048))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec117SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec90SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec81SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec39SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(4))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(1024))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec121SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(2))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec126SE, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(4))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec127SE, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(2))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec131SE, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(4))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec132SE, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec134SE, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(2))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec136SE, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(2))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec140SE, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(4))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec141SE, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(2))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec145SE, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(4))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec146SE, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
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
	DeclareVarInst("int", iSlow0BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))), Int32(8191)))
	DeclareVarInst("float", fSlow1BE, kStack, FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow4BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow3BE, kStack))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow4BE, kStack))))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow4BE, kStack)))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow6BE, kStack))))
	DeclareVarInst("float", fSlow8BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow6BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow7BE, kStack)), MinusInst(LoadVarInst(Address(fSlow8BE, kStack)))))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow7BE, kStack))))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider3, kStruct)))))))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow11BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow11BE, kStack)))))
	DeclareVarInst("float", fSlow14BE, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow15BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow3BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow16BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow17BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow16BE, kStack))))
	DeclareVarInst("float", fSlow18BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow17BE, kStack))))))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow17BE, kStack)))))
	DeclareVarInst("float", fSlow20BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow18BE, kStack)), LoadVarInst(Address(fSlow19BE, kStack))))
	DeclareVarInst("float", fSlow21BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow18BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow19BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow22BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow20BE, kStack)), MinusInst(LoadVarInst(Address(fSlow21BE, kStack)))))
	DeclareVarInst("float", fSlow23BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow16BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow21BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow20BE, kStack))))))
	DeclareVarInst("float", fSlow24BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow16BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("/", LoadVarInst(Address(fConst13KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow26BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow25BE, kStack))))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow26BE, kStack))))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow26BE, kStack)))))
	DeclareVarInst("float", fSlow29BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow27BE, kStack)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow30BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow27BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow28BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow29BE, kStack)), MinusInst(LoadVarInst(Address(fSlow30BE, kStack)))))
	DeclareVarInst("float", fSlow32BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow25BE, kStack)))))
	DeclareVarInst("float", fSlow33BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow30BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow29BE, kStack))))))
	DeclareVarInst("float", fSlow34BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst13KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow32BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow35BE, kStack, BinopInst("/", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow36BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow35BE, kStack))))))
	DeclareVarInst("float", fSlow37BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow36BE, kStack))))))
	DeclareVarInst("float", fSlow38BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow36BE, kStack)))))
	DeclareVarInst("float", fSlow39BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fSlow38BE, kStack))))
	DeclareVarInst("float", fSlow40BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow37BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow41BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow39BE, kStack)), MinusInst(LoadVarInst(Address(fSlow40BE, kStack)))))
	DeclareVarInst("float", fSlow42BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow35BE, kStack)))))
	DeclareVarInst("float", fSlow43BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow42BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow40BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow39BE, kStack))))))
	DeclareVarInst("float", fSlow44BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow42BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow45BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst21KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow46BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow45BE, kStack))))
	DeclareVarInst("float", fSlow47BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow46BE, kStack))))))
	DeclareVarInst("float", fSlow48BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow46BE, kStack)))))
	DeclareVarInst("float", fSlow49BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow47BE, kStack)), LoadVarInst(Address(fSlow48BE, kStack))))
	DeclareVarInst("float", fSlow50BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow47BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow48BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow51BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow49BE, kStack)), MinusInst(LoadVarInst(Address(fSlow50BE, kStack)))))
	DeclareVarInst("float", fSlow52BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow45BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow50BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow49BE, kStack))))))
	DeclareVarInst("float", fSlow53BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst21KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow45BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow54BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))))
	DeclareVarInst("float", fSlow55BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow54BE, kStack))))
	DeclareVarInst("float", fSlow56BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow55BE, kStack))))))
	DeclareVarInst("float", fSlow57BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow55BE, kStack)))))
	DeclareVarInst("float", fSlow58BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow56BE, kStack)), LoadVarInst(Address(fSlow57BE, kStack))))
	DeclareVarInst("float", fSlow59BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow56BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow57BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow60BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow58BE, kStack)), MinusInst(LoadVarInst(Address(fSlow59BE, kStack)))))
	DeclareVarInst("float", fSlow61BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow59BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow58BE, kStack))))))
	DeclareVarInst("float", fSlow62BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst25KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow54BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow63BE, kStack, BinopInst("/", LoadVarInst(Address(fConst29KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow64BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow63BE, kStack))))))
	DeclareVarInst("float", fSlow65BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow64BE, kStack))))))
	DeclareVarInst("float", fSlow66BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow64BE, kStack)))))
	DeclareVarInst("float", fSlow67BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fSlow66BE, kStack))))
	DeclareVarInst("float", fSlow68BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow65BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow69BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow67BE, kStack)), MinusInst(LoadVarInst(Address(fSlow68BE, kStack)))))
	DeclareVarInst("float", fSlow70BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow63BE, kStack)))))
	DeclareVarInst("float", fSlow71BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow68BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow67BE, kStack))))))
	DeclareVarInst("float", fSlow72BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst29KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow70BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow73BE, kStack, BinopInst("/", LoadVarInst(Address(fConst33KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow74BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow73BE, kStack))))))
	DeclareVarInst("float", fSlow75BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fSlow74BE, kStack))))))
	DeclareVarInst("float", fSlow76BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow74BE, kStack)))))
	DeclareVarInst("float", fSlow77BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fSlow76BE, kStack))))
	DeclareVarInst("float", fSlow78BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow75BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow76BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow79BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow77BE, kStack)), MinusInst(LoadVarInst(Address(fSlow78BE, kStack)))))
	DeclareVarInst("float", fSlow80BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow73BE, kStack)))))
	DeclareVarInst("float", fSlow81BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow80BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow78BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow77BE, kStack))))))
	DeclareVarInst("float", fSlow82BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst33KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))), LoadVarInst(Address(fSlow80BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow83BE, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow84BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow85BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow83BE, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow84BE, kStack)))))))
	DeclareVarInst("float", fSlow86BE, kStack, BinopInst("/", BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow85BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow85BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow87BE, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow83BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow86BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow88BE, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow89BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))
	DeclareVarInst("float", fSlow90BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), BinopInst("/", LoadVarInst(Address(fSlow88BE, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(Address(fSlow89BE, kStack)))))))
	DeclareVarInst("float", fSlow91BE, kStack, BinopInst("/", BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow90BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow90BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow92BE, kStack, BinopInst("*", FunCallInst("cosf", BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow88BE, kStack)))), BinopInst("+", LoadVarInst(Address(fSlow91BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow93BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct)))))))
	DeclareVarInst("float", fSlow94BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fVslider10, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp4SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp4SE, kStack)))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow0BE, kStack))), Int32(8191))]))
			DeclareVarInst("float", fTemp6SE, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fTemp5SE, kStack))))
			DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp8SE, kStack)))), MinusInst(LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow15BE, kStack)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst7KI, kStruct))), Int32(16383))]))
			DeclareVarInst("float", fRec2SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp7SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp9SE, kStack))))))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fRec2SE, kStack)))
			DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp11SE, kStack)))), MinusInst(LoadVarInst(Address(fVec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow24BE, kStack)), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp12SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst11KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp6SE, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec5SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp12SE, kStack))))
			DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fRec5SE, kStack)))
			DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp14SE, kStack)))), MinusInst(LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp15SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], LoadVarInst(Address(fTemp15SE, kStack)))
			DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow0BE, kStack))), Int32(8191))]))
			DeclareVarInst("float", fTemp17SE, kStack, BinopInst("*", Float(-0.3f), LoadVarInst(Address(fTemp16SE, kStack))))
			DeclareVarInst("float", fTemp18SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst15KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp17SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec8SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp18SE, kStack))))
			DeclareVarInst("float", fTemp19SE, kStack, LoadVarInst(Address(fRec8SE, kStack)))
			DeclareVarInst("float", fTemp20SE, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fTemp16SE, kStack))))
			DeclareVarInst("float", fTemp21SE, kStack, LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp21SE, kStack)))), MinusInst(LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41BE, kStack)), LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow43BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp21SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp22SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec44SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst19KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp20SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec11SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp22SE, kStack))))
			DeclareVarInst("float", fTemp23SE, kStack, LoadVarInst(Address(fRec11SE, kStack)))
			DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp25SE, kStack, LoadVarInst(Address(fVec49SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp26SE, kStack, LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec53SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp27SE, kStack)))), MinusInst(LoadVarInst(Address(fVec54SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow51BE, kStack)), LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow52BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp27SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp28SE, kStack, LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst23KI, kStruct))), Int32(16383))]))
			DeclareVarInst("float", fRec14SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp26SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp28SE, kStack))))))
			DeclareVarInst("float", fTemp29SE, kStack, LoadVarInst(Address(fRec14SE, kStack)))
			DeclareVarInst("float", fTemp30SE, kStack, LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec63SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec63SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp30SE, kStack)))), MinusInst(LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow60BE, kStack)), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp30SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), LoadVarInst(Address(fVec63SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp31SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec60SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27KI, kStruct))), Int32(16383))])))
			DeclareVarInst("float", fRec17SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp31SE, kStack))))
			DeclareVarInst("float", fTemp32SE, kStack, LoadVarInst(Address(fRec17SE, kStack)))
			DeclareVarInst("float", fTemp33SE, kStack, LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp34SE, kStack, LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp34SE, kStack)))), MinusInst(LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow71BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp34SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp35SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst31KI, kStruct))), Int32(8191))]), LoadVarInst(Address(fTemp17SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec20SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp35SE, kStack))))
			DeclareVarInst("float", fTemp36SE, kStack, LoadVarInst(Address(fRec20SE, kStack)))
			DeclareVarInst("float", fTemp37SE, kStack, LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp38SE, kStack, LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp38SE, kStack)))), MinusInst(LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow79BE, kStack)), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow81BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp38SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow82BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp39SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp20SE, kStack)), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst35KI, kStruct))), Int32(8191))])), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec90SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec23SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp39SE, kStack))))
			DeclareVarInst("float", fTemp40SE, kStack, LoadVarInst(Address(fRec23SE, kStack)))
			StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))))
			StoreVarInst(Address(fVec54SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp41SE, kStack, BinopInst("*", Float(-0.3f), LoadVarInst(Address(fTemp5SE, kStack))))
			StoreVarInst(Address(fVec93SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp26SE, kStack))), LoadVarInst(Address(fTemp28SE, kStack))), LoadVarInst(Address(fTemp41SE, kStack))))
			StoreVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec93SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst36KI, kStruct))), Int32(1023))]))
			StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
			StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp7SE, kStack))), LoadVarInst(Address(fTemp9SE, kStack))), LoadVarInst(Address(fTemp41SE, kStack))))
			StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
			StoreVarInst(Address(fVec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec101SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp12SE, kStack)))
			StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec101SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst38KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp32SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))))
			StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec105SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp31SE, kStack)))
			StoreVarInst(Address(fVec60SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec105SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst39KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec49SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec60SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))))
			StoreVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec109SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp18SE, kStack)))
			StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec109SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst40KI, kStruct))), Int32(1023))]))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp33SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp36SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
			StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec113SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp35SE, kStack)))
			StoreVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec113SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst41KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp37SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp40SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))))
			StoreVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp39SE, kStack)))
			StoreVarInst(Address(fVec90SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst42KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec90SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp25SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp33SE, kStack))), LoadVarInst(Address(fTemp37SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp29SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), LoadVarInst(Address(fTemp13SE, kStack))), LoadVarInst(Address(fTemp32SE, kStack))), LoadVarInst(Address(fTemp19SE, kStack))), LoadVarInst(Address(fTemp36SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp40SE, kStack))))
			StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec121SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], LoadVarInst(Address(fTemp22SE, kStack)))
			StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec121SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43KI, kStruct))), Int32(1023))]))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp42SE, kStack, LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp43SE, kStack, LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp44SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp42SE, kStack)), LoadVarInst(Address(fTemp43SE, kStack))))
			DeclareVarInst("float", fTemp45SE, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp44SE, kStack))))
			DeclareVarInst("float", fTemp46SE, kStack, LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec126SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp45SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec126SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fTemp46SE, kStack))))))
			DeclareVarInst("float", fTemp47SE, kStack, LoadVarInst(Address(fVec126SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp47SE, kStack)))
			DeclareVarInst("float", fTemp48SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fVec126SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp49SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
			DeclareVarInst("float", fTemp50SE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fTemp45SE, kStack))), LoadVarInst(Address(fTemp46SE, kStack))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp46SE, kStack)), LoadVarInst(Address(fTemp48SE, kStack))), BinopInst("*", Float(-0.37f), LoadVarInst(Address(fTemp44SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack))))))))
			DeclareVarInst("float", fTemp51SE, kStack, LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp50SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fTemp51SE, kStack))))))
			DeclareVarInst("float", fTemp52SE, kStack, LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp52SE, kStack)))
			StoreVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow93BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp53SE, kStack, LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow94BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp54SE, kStack, BinopInst("+", LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(1.0f)))
			DeclareVarInst("float", fTemp55SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp56SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
			DeclareVarInst("float", fTemp57SE, kStack, BinopInst("+", Float(1.0f), BinopInst("*", Float(-0.5f), LoadVarInst(Address(fTemp54SE, kStack)))))
			DeclareVarInst("float", fTemp58SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp42SE, kStack)), MinusInst(LoadVarInst(Address(fTemp43SE, kStack)))))
			DeclareVarInst("float", fTemp59SE, kStack, BinopInst("*", Float(0.37f), LoadVarInst(Address(fTemp58SE, kStack))))
			DeclareVarInst("float", fTemp60SE, kStack, LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp59SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fTemp60SE, kStack))))))
			DeclareVarInst("float", fTemp61SE, kStack, LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec141SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp61SE, kStack)))
			DeclareVarInst("float", fTemp62SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow86BE, kStack)), LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp63SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
			DeclareVarInst("float", fTemp64SE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp62SE, kStack)), LoadVarInst(Address(fTemp59SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp60SE, kStack)), LoadVarInst(Address(fTemp62SE, kStack))), BinopInst("*", Float(-0.37f), LoadVarInst(Address(fTemp58SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack))))))))
			DeclareVarInst("float", fTemp65SE, kStack, LoadVarInst(Address(fVec146SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp64SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fTemp65SE, kStack))))))
			DeclareVarInst("float", fTemp66SE, kStack, LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec146SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp66SE, kStack)))
			DeclareVarInst("float", fTemp67SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp68SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), LoadVarInst(Address(fVec146SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp54SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp55SE, kStack)), LoadVarInst(Address(fTemp50SE, kStack))), LoadVarInst(Address(fTemp51SE, kStack))), MinusInst(LoadVarInst(Address(fTemp56SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow89BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp51SE, kStack)), LoadVarInst(Address(fTemp55SE, kStack))), BinopInst("*", Float(-0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fTemp45SE, kStack))), LoadVarInst(Address(fTemp46SE, kStack))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp46SE, kStack)), LoadVarInst(Address(fTemp48SE, kStack))), MinusInst(LoadVarInst(Address(fTemp45SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))))))), MinusInst(LoadVarInst(Address(fTemp56SE, kStack)))))))), BinopInst("*", LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))]), LoadVarInst(Address(fTemp57SE, kStack)))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("+", BinopInst("*", Float(0.25f), BinopInst("*", LoadVarInst(Address(fTemp54SE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp67SE, kStack)), LoadVarInst(Address(fTemp64SE, kStack))), LoadVarInst(Address(fTemp65SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow89BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp65SE, kStack)), LoadVarInst(Address(fTemp67SE, kStack))), BinopInst("*", Float(-0.5f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp62SE, kStack)), LoadVarInst(Address(fTemp59SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp60SE, kStack)), LoadVarInst(Address(fTemp62SE, kStack))), MinusInst(LoadVarInst(Address(fTemp59SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp63SE, kStack)))))))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))))))), BinopInst("*", LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(8191))]), LoadVarInst(Address(fTemp57SE, kStack)))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 72 bytes
Heap size int* = 0 bytes
Heap size real = 479948 bytes
Total heap size = 480020 bytes
Stack size in compute = 412 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst7KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst10KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst11KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst15KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst16KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec40SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec44SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst19KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec53SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec57SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst22KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst23KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst24KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec63SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst26KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec73SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec71SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst30KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst31KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec88SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst34KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst35KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec54SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec93SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst36KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec50SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec97SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst37KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec101SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst38KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec62SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec105SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst39KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec60SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec49SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec109SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst40KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec113SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst41KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec79SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec85SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec117SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst42KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec90SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec81SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec39SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec121SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst43KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec126SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec127SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec131SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec132SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec134SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec136SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec140SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec141SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec145SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec146SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2KI size = 1 size_bytes = 4 read = 5 write = 0 ratio = 5
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst5KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst7KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst10KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst11KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst15KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst16KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec40SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec44SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst19KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec53SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec57SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst22KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst23KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst24KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec63SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst26KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec73SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec71SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst30KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst31KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec88SE size = 8192 size_bytes = 32768 read = 0 write = 0 ratio = 0
Field = fConst34KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst35KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec54SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec93SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst36KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec50SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec97SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst37KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec101SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst38KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec62SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec105SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst39KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec60SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec49SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec109SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst40KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec113SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst41KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec79SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec85SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec117SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst42KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec90SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec81SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec39SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec121SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = iConst43KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec126SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec127SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec131SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec132SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec134SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec136SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec140SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec141SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec145SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec146SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 203 write = 1 ratio = 204
Field = fVec4SE size = 8192 size_bytes = 32768 read = 2 write = 1 ratio = 0.000366211
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec13SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst7KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst8KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec16SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec22SE size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst10KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst11KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec26SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec32SE size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst15KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec34SE size = 8192 size_bytes = 32768 read = 2 write = 1 ratio = 0.000366211
Field = fConst16KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec40SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec38SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec44SE size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst19KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec53SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec51SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec57SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst22KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst23KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst24KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec63SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec61SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec67SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst26KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst27KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst28KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec73SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec71SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec77SE size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst30KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst31KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst32KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec82SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec88SE size = 8192 size_bytes = 32768 read = 1 write = 1 ratio = 0.000244141
Field = fConst34KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst35KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec52SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec54SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec93SE size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst36KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec50SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec48SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec10SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec97SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst37KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec0SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec17SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec19SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec101SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst38KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec24SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec1SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec62SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec64SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec105SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst39KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec60SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec49SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec27SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec29SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec109SE size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst40KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec36SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec2SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec72SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec74SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec113SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst41KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec79SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec70SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec83SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec85SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec117SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst42KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec90SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec81SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec39SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec41SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec121SE size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = iConst43KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec46SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec3SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec126SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec127SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec131SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec132SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec134SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec136SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec140SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec141SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fVec145SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec146SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
