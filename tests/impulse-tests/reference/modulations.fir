======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iRec16)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec16, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 4 Binop = 5 [ { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec16, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec16, kStruct)[Int32(1)]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec16, kStruct)[Int32(0)]), Int32(-1))))))
		StoreVarInst(Address(iRec16, kStruct)[Int32(1)], LoadVarInst(Address(iRec16, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Modulations")
	OpenHorizontalBox("Instrument")
	AddMetaDeclareInst(fHslider4, "acc", "1 1 -10 0 15")
	AddMetaDeclareInst(fHslider4, "unit", "Hz")
	AddHorizontalSlider("Frequency", fHslider4, 3.3e+02f, 1e+02f, 1.2e+03f, 0.1f)
	AddMetaDeclareInst(fHslider0, "acc", "1 1 -10 0 10")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("General Volume", fHslider0, 1.0f, 0.75f, 4.0f, 0.01f)
	AddMetaDeclareInst(fHslider8, "acc", "1 0 -10 0 10")
	AddMetaDeclareInst(fHslider8, "style", "knob")
	AddHorizontalSlider("Oscillator Volume", fHslider8, 0.5f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fHslider2, "acc", "0 0 -10 0 10")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "unit", "Hz")
	AddHorizontalSlider("Modulating Frequency", fHslider2, 1.2e+03f, 9e+02f, 1.7e+03f, 0.1f)
	CloseboxInst
	OpenVerticalBox("Modulations")
	AddMetaDeclareInst(fHslider5, "acc", "0 0 -30 0 10")
	AddMetaDeclareInst(fHslider5, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 0 (ASR Envelope)", fHslider5, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider6, "acc", "0 0 -30 0 5")
	AddMetaDeclareInst(fHslider6, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 1 (ASR Envelope)", fHslider6, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider7, "acc", "2 1 -30 0 10")
	AddMetaDeclareInst(fHslider7, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 2 (ASR Envelope)", fHslider7, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider3, "acc", "1 0 -10 0 10")
	AddMetaDeclareInst(fHslider3, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 3 (ASR Envelope)", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	OpenVerticalBox("Reverb")
	AddMetaDeclareInst(fHslider1, "acc", "1 1 -10 0 10")
	AddHorizontalSlider("Reverberation Room Size(InstrReverb)", fHslider1, 0.5f, 0.05f, 2.0f, 0.01f)
	AddMetaDeclareInst(fHslider9, "acc", "1 1 -10 0 10")
	AddHorizontalSlider("Reverberation Volume(InstrReverb)", fHslider9, 0.25f, 0.05f, 1.0f, 0.01f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
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
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("float", ftbl1mydspSIG0[65537], kStaticStruct)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("float[2]", fRec0)("int", fSampleRate)("float", fConst0)("float", fConst1)("float", fConst2)("float", fConst3)("float", fConst4)("FAUSTFLOAT", fHslider1)("float", fConst5)("float", fConst6)("float", fConst7)("float", fConst8)("float[2]", fRec12)("float[2]", fRec11)("int", IOTA0)("float[32768]", fVec0)("float", fConst9)("int", iConst10)("float", fConst11)("float", fConst12)("float", fConst13)("float[2]", fRec15)("float", fConst14)("FAUSTFLOAT", fHslider2)("float[2]", fRec18)("float[2]", fRec17)("FAUSTFLOAT", fHslider3)("float", fConst15)("float[2]", fRec19)("float", fConst16)("float[2]", fRec21)("float", fConst17)("float[2]", fRec20)("float", fConst18)("FAUSTFLOAT", fHslider4)("float[2]", fRec23)("float[2]", fRec22)("float[2]", fRec28)("float[2]", fRec27)("float[2]", fRec26)("float[2]", fRec25)("float[2]", fRec24)("float[2]", fRec14)("FAUSTFLOAT", fHslider5)("float[2]", fRec29)("float[2]", fRec31)("float[2]", fRec30)("float[2]", fRec37)("float[2]", fRec36)("float[2]", fRec35)("float[2]", fRec34)("float[2]", fRec33)("float[2]", fRec32)("float[2]", fVec1)("FAUSTFLOAT", fHslider6)("float[2]", fRec38)("float[2]", fRec40)("float[2]", fRec39)("float[2]", fRec46)("float[2]", fRec45)("float[2]", fRec44)("float[2]", fRec43)("float[2]", fRec42)("float[2]", fRec41)("FAUSTFLOAT", fHslider7)("float[2]", fRec47)("float[2]", fRec49)("float[2]", fRec48)("float[2]", fRec55)("float[2]", fRec54)("float[2]", fRec53)("float[2]", fRec52)("float[2]", fRec51)("float[2]", fRec50)("float[2]", fVec2)("float[2]", fRec13)("FAUSTFLOAT", fHslider8)("float[2]", fRec56)("FAUSTFLOAT", fHslider9)("float[2]", fRec57)("float[4096]", fVec3)("int", iConst19)("float[2048]", fVec4)("int", iConst20)("float[2]", fRec9)("float", fConst21)("float", fConst22)("float", fConst23)("float", fConst24)("float[2]", fRec61)("float[2]", fRec60)("float[32768]", fVec5)("float", fConst25)("int", iConst26)("float[4096]", fVec6)("int", iConst27)("float[2]", fRec58)("float", fConst28)("float", fConst29)("float", fConst30)("float", fConst31)("float[2]", fRec65)("float[2]", fRec64)("float[16384]", fVec7)("float", fConst32)("int", iConst33)("float[4096]", fVec8)("int", iConst34)("float[2]", fRec62)("float", fConst35)("float", fConst36)("float", fConst37)("float", fConst38)("float[2]", fRec69)("float[2]", fRec68)("float[32768]", fVec9)("float", fConst39)("int", iConst40)("float[4096]", fVec10)("int", iConst41)("float[2]", fRec66)("float", fConst42)("float", fConst43)("float", fConst44)("float", fConst45)("float[2]", fRec73)("float[2]", fRec72)("float[16384]", fVec11)("float", fConst46)("int", iConst47)("float[2048]", fVec12)("int", iConst48)("float[2]", fRec70)("float", fConst49)("float", fConst50)("float", fConst51)("float", fConst52)("float[2]", fRec77)("float[2]", fRec76)("float[16384]", fVec13)("float", fConst53)("int", iConst54)("float[4096]", fVec14)("int", iConst55)("float[2]", fRec74)("float", fConst56)("float", fConst57)("float", fConst58)("float", fConst59)("float[2]", fRec81)("float[2]", fRec80)("float[16384]", fVec15)("float", fConst60)("int", iConst61)("float[4096]", fVec16)("int", iConst62)("float[2]", fRec78)("float", fConst63)("float", fConst64)("float", fConst65)("float", fConst66)("float[2]", fRec85)("float[2]", fRec84)("float[16384]", fVec17)("float", fConst67)("int", iConst68)("float[2048]", fVec18)("int", iConst69)("float[2]", fRec82)("float[3]", fRec1)("float[3]", fRec2)("float[3]", fRec3)("float[3]", fRec4)("float[3]", fRec5)("float[3]", fRec6)("float[3]", fRec7)("float[3]", fRec8)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl1mydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), FunCallInst("cosf", BinopInst("/", Float(37699.113f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(628.31854f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst6, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst10, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst9, kStruct)))))))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(6283.1855f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst11, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("*", Float(3.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("/", Float(0.33333334f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("/", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst19, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("*", Float(0.02f), LoadVarInst(Address(fConst0, kStruct)))))))
	StoreVarInst(Address(iConst20, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst9, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst21, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst22, kStruct))))
	StoreVarInst(Address(fConst24, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst22, kStruct))))
	StoreVarInst(Address(fConst25, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst26, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fConst25, kStruct)))))))
	StoreVarInst(Address(iConst27, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst28, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("/", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst29, kStruct))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst29, kStruct))))
	StoreVarInst(Address(fConst32, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst33, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fConst32, kStruct)))))))
	StoreVarInst(Address(iConst34, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst32, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst35, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst37, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst38, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst39, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst40, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fConst39, kStruct)))))))
	StoreVarInst(Address(iConst41, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst39, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst42, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst43, kStruct), BinopInst("/", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst43, kStruct))))
	StoreVarInst(Address(fConst45, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst43, kStruct))))
	StoreVarInst(Address(fConst46, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst47, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fConst46, kStruct)))))))
	StoreVarInst(Address(iConst48, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst46, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst49, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst50, kStruct), BinopInst("/", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst51, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst50, kStruct))))
	StoreVarInst(Address(fConst52, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst50, kStruct))))
	StoreVarInst(Address(fConst53, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst54, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fConst53, kStruct)))))))
	StoreVarInst(Address(iConst55, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst53, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst56, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst57, kStruct), BinopInst("/", LoadVarInst(Address(fConst56, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst58, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst57, kStruct))))
	StoreVarInst(Address(fConst59, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst57, kStruct))))
	StoreVarInst(Address(fConst60, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst61, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst56, kStruct)), LoadVarInst(Address(fConst60, kStruct)))))))
	StoreVarInst(Address(iConst62, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst60, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst63, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst64, kStruct), BinopInst("/", LoadVarInst(Address(fConst63, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst65, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst64, kStruct))))
	StoreVarInst(Address(fConst66, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst64, kStruct))))
	StoreVarInst(Address(fConst67, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst68, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst63, kStruct)), LoadVarInst(Address(fConst67, kStruct)))))))
	StoreVarInst(Address(iConst69, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst67, kStruct)), Float(-1.0f))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.2e+03f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(3.3e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.25f)))
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
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(32768))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec46, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec47, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec49, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec48, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec55, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec54, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec53, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec52, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec51, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec50, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec56, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec57, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(4096))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2048))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec61, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec60, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(32768))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4096))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec58, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec65, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec64, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(16384))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(4096))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(2))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec62, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec69, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec68, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(32768))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(4096))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(2))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec66, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(2))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec73, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec72, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(16384))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(2048))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(2))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec70, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(2))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec77, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(2))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec76, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(16384))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(4096))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(2))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec74, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(2))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec81, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(2))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec80, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(16384))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(4096))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(2))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec78, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(2))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec85, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec84, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(16384))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(2048))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(2))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec82, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(3))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(3))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(3))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(3))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(3))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(3))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(3))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(3))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 180 Store = 0 Binop = 137 [ { Int(>) = 8 } { Real(*) = 25 } { Real(+) = 24 } { Real(-) = 32 } { Real(/) = 40 } { Real(==) = 4 } { Real(>) = 4 } ] Mathop = 59 [ { expf = 16 } { max_f = 9 } { min_f = 1 } { mydsp_faustpower2_f = 25 } { sqrtf = 8 } ] Numbers = 73 Declare = 104 Cast = 14 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow3, kStack)))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow4, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("-", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow6, kStack))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow2, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("int", iSlow13, kStack, BinopInst(">", LoadVarInst(Address(fSlow12, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow14, kStack, BinopInst(">", LoadVarInst(Address(iSlow13, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow15, kStack, CastInst("float", LoadVarInst(Address(iSlow13, kStack))))
	DeclareVarInst("int", iSlow16, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow12, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow19, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("int", iSlow20, kStack, BinopInst(">", LoadVarInst(Address(fSlow19, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow21, kStack, BinopInst(">", LoadVarInst(Address(iSlow20, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(iSlow20, kStack))))
	DeclareVarInst("int", iSlow23, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow19, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow25, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("int", iSlow26, kStack, BinopInst(">", LoadVarInst(Address(fSlow25, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow27, kStack, BinopInst(">", LoadVarInst(Address(iSlow26, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow28, kStack, CastInst("float", LoadVarInst(Address(iSlow26, kStack))))
	DeclareVarInst("int", iSlow29, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow25, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow25, kStack))))
	DeclareVarInst("float", fSlow31, kStack, CastInst("float", LoadVarInst(Address(fHslider7, kStruct))))
	DeclareVarInst("int", iSlow32, kStack, BinopInst(">", LoadVarInst(Address(fSlow31, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow33, kStack, BinopInst(">", LoadVarInst(Address(iSlow32, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow34, kStack, CastInst("float", LoadVarInst(Address(iSlow32, kStack))))
	DeclareVarInst("int", iSlow35, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow31, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("*", Float(0.001f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider8, kStruct))))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider9, kStruct)))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst23, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow39, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow40, kStack)))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow40, kStack))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("/", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fSlow42, kStack))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow41, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow42, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow45, kStack, BinopInst("-", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fSlow44, kStack))))
	DeclareVarInst("float", fSlow46, kStack, BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow43, kStack))))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow39, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow48, kStack))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow49, kStack)))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("/", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fSlow51, kStack))))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow50, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow51, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("-", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fSlow53, kStack))))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", LoadVarInst(Address(fSlow53, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow52, kStack))))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst31, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow48, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow57, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst37, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow57, kStack))))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow58, kStack)))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow58, kStack))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("/", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow62, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow59, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow60, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow63, kStack, BinopInst("-", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fSlow62, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), BinopInst("+", LoadVarInst(Address(fSlow62, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow61, kStack))))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst38, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow57, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow66, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst44, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow67, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66, kStack))))
	DeclareVarInst("float", fSlow68, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow67, kStack)))))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow67, kStack))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("/", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fSlow69, kStack))))
	DeclareVarInst("float", fSlow71, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow68, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow69, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("-", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), BinopInst("+", LoadVarInst(Address(fSlow71, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow70, kStack))))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow66, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow75, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst51, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow76, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow75, kStack))))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow76, kStack)))))
	DeclareVarInst("float", fSlow78, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow76, kStack))))
	DeclareVarInst("float", fSlow79, kStack, BinopInst("/", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fSlow78, kStack))))
	DeclareVarInst("float", fSlow80, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow77, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow78, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("-", LoadVarInst(Address(fSlow79, kStack)), LoadVarInst(Address(fSlow80, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("*", LoadVarInst(Address(fSlow75, kStack)), BinopInst("+", LoadVarInst(Address(fSlow80, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow79, kStack))))))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow75, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow84, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst58, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow85, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow84, kStack))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow85, kStack)))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow85, kStack))))
	DeclareVarInst("float", fSlow88, kStack, BinopInst("/", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fSlow87, kStack))))
	DeclareVarInst("float", fSlow89, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow86, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow87, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow90, kStack, BinopInst("-", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fSlow89, kStack))))
	DeclareVarInst("float", fSlow91, kStack, BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), BinopInst("+", LoadVarInst(Address(fSlow89, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow88, kStack))))))
	DeclareVarInst("float", fSlow92, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst59, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow84, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow93, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst65, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow94, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow95, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow94, kStack)))))
	DeclareVarInst("float", fSlow96, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow94, kStack))))
	DeclareVarInst("float", fSlow97, kStack, BinopInst("/", LoadVarInst(Address(fSlow95, kStack)), LoadVarInst(Address(fSlow96, kStack))))
	DeclareVarInst("float", fSlow98, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow95, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow96, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow99, kStack, BinopInst("-", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fSlow98, kStack))))
	DeclareVarInst("float", fSlow100, kStack, BinopInst("*", LoadVarInst(Address(fSlow93, kStack)), BinopInst("+", LoadVarInst(Address(fSlow98, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow97, kStack))))))
	DeclareVarInst("float", fSlow101, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst66, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow93, kStack))), Float(-1.0f)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 778 Store = 187 Binop = 541 [ { Int(&) = 34 } { Int(+) = 3 } { Int(-) = 17 } { Int(<) = 1 } { Real(*) = 216 } { Real(+) = 195 } { Real(-) = 59 } { Real(<) = 16 } ] Mathop = 30 [ { cosf = 4 } { floorf = 3 } { max_f = 2 } { max_i = 3 } { min_f = 10 } { min_i = 3 } { mydsp_faustpower2_f = 1 } { sinf = 4 } ] Numbers = 639 Declare = 71 Cast = 4 Select = 28 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp0, kStack, FunCallInst("max_f", Float(0.75f), FunCallInst("min_f", Float(4.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec12, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec11, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst10, kStruct))), Int32(32767))])))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec15, kStruct)[Int32(1)])), Float(0.0008f)))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow11, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow14, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow16, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec21, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec21, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow12, kStack))))) LoadVarInst(Address(fRec20, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))), Int32(65535)))])), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec20, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec20, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)])))) Float(0.0f))))))
		DeclareVarInst("float", fTemp4, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack)))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))
		DeclareVarInst("int", iTemp7, kStack, CastInst("int", LoadVarInst(Address(fTemp6, kStack))))
		DeclareVarInst("float", fTemp8, kStack, LoadVarInst(Address(ftbl1mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp7, kStack)), Int32(65536)))]))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp6, kStack)))), BinopInst("-", LoadVarInst(Address(ftbl1mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp7, kStack)), Int32(1)), Int32(65536)))]), LoadVarInst(Address(fTemp8, kStack))))))
		DeclareVarInst("float", fTemp10, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp3, kStack))))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp10, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp11, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp12, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp13, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp15, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec28, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp15, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec27, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp15, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp13, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec24, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp12, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp11, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec29, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow21, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec29, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec31, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow23, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec31, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec30, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow20, kStack)) BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec31, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec31, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow19, kStack))))) LoadVarInst(Address(fRec30, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp9, kStack))), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec29, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec30, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec29, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec30, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec29, kStruct)[Int32(0)])))) Float(0.0f))))))
		DeclareVarInst("float", fTemp17, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp16, kStack))))
		DeclareVarInst("float", fTemp18, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp16, kStack))))
		DeclareVarInst("float", fTemp19, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp18, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp20, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp19, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp21, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp23, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp22, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp23, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp23, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp22, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp21, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp19, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp17, kStack))), BinopInst("*", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp18, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp9, kStack)))))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
		StoreVarInst(Address(fRec38, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow27, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec38, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec40, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow29, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec39, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow26, kStack)) BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec40, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec40, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fRec40, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow25, kStack))))) LoadVarInst(Address(fRec39, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp26, kStack, BinopInst("*", Float(1.5707964f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec38, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec39, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec38, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec39, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])))) Float(0.0f)))), BinopInst("+", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))))
		DeclareVarInst("float", fTemp27, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp26, kStack))))
		DeclareVarInst("float", fTemp28, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp26, kStack))))
		DeclareVarInst("float", fTemp29, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fTemp28, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp30, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp29, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp31, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp30, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp32, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp31, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp33, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp32, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec46, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp33, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp33, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec44, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp32, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec43, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp31, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp30, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp29, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp34, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fTemp27, kStack))), BinopInst("*", LoadVarInst(Address(fRec41, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp28, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp25, kStack)))))
		StoreVarInst(Address(fRec47, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow33, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec47, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec49, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow35, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec49, kStruct)[Int32(1)]), Float(1.0f)))))
		StoreVarInst(Address(fRec48, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow32, kStack)) BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec49, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec49, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fRec49, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow31, kStack))))) LoadVarInst(Address(fRec48, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp35, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp34, kStack)))), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec47, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec48, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec47, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec48, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec47, kStruct)[Int32(0)])))) Float(0.0f))))))
		DeclareVarInst("float", fTemp36, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp35, kStack))))
		DeclareVarInst("float", fTemp37, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp35, kStack))))
		DeclareVarInst("float", fTemp38, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp37, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp39, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp38, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp40, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp39, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp41, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp40, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp42, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp41, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec54, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec55, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp42, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec54, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp42, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec53, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp41, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec54, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec52, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp40, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec51, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp39, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec50, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp38, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp43, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp10, kStack))), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp36, kStack))), BinopInst("*", LoadVarInst(Address(fRec50, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp37, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp34, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp4, kStack))))))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp43, kStack)))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst12, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fRec13, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fTemp43, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec56, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow37, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp44, kStack, BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), LoadVarInst(Address(fRec56, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec57, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp45, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(1.0f), LoadVarInst(Address(fRec57, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("*", LoadVarInst(Address(fTemp44, kStack)), LoadVarInst(Address(fTemp45, kStack))))
		DeclareVarInst("float", fTemp46, kStack, BinopInst("*", Float(0.18f), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst19, kStruct))), Int32(4095))])))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fTemp46, kStack))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst20, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec10, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fTemp1, kStack)))))
		StoreVarInst(Address(fRec61, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec61, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec60, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fRec60, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec60, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp47, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec58, kStruct)[Int32(1)])), LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst26, kStruct))), Int32(32767))])))
		StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("-", LoadVarInst(Address(fTemp47, kStack)), LoadVarInst(Address(fTemp46, kStack))))
		StoreVarInst(Address(fRec58, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27, kStruct))), Int32(4095))]))
		DeclareVarInst("float", fRec59, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fTemp47, kStack)))))
		StoreVarInst(Address(fRec65, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec64, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec64, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec65, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec64, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp48, kStack, BinopInst("+", LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst33, kStruct))), Int32(16383))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec62, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp48, kStack)))
		StoreVarInst(Address(fRec62, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst34, kStruct))), Int32(4095))]))
		DeclareVarInst("float", fRec63, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp48, kStack)))))
		StoreVarInst(Address(fRec69, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fRec2, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec68, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fRec68, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fRec69, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec68, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp49, kStack, BinopInst("+", LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst40, kStruct))), Int32(32767))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec66, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp49, kStack)))
		StoreVarInst(Address(fRec66, kStruct)[Int32(0)], LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst41, kStruct))), Int32(4095))]))
		DeclareVarInst("float", fRec67, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp49, kStack)))))
		StoreVarInst(Address(fRec73, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec72, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fRec72, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec73, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec72, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp50, kStack, BinopInst("-", LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst47, kStruct))), Int32(16383))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec70, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp50, kStack)))
		StoreVarInst(Address(fRec70, kStruct)[Int32(0)], LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst48, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec71, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp50, kStack))))
		StoreVarInst(Address(fRec77, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec76, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fRec76, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow82, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fRec77, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec76, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp51, kStack, BinopInst("-", LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst54, kStruct))), Int32(16383))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec74, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp51, kStack)))
		StoreVarInst(Address(fRec74, kStruct)[Int32(0)], LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst55, kStruct))), Int32(4095))]))
		DeclareVarInst("float", fRec75, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp51, kStack))))
		StoreVarInst(Address(fRec81, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec80, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow90, kStack)), LoadVarInst(Address(fRec80, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fRec81, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec80, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp52, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst61, kStruct))), Int32(16383))])), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp52, kStack)))
		StoreVarInst(Address(fRec78, kStruct)[Int32(0)], LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst62, kStruct))), Int32(4095))]))
		DeclareVarInst("float", fRec79, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp52, kStack))))
		StoreVarInst(Address(fRec85, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fRec1, kStruct)[Int32(2)]))))))
		StoreVarInst(Address(fRec84, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99, kStack)), LoadVarInst(Address(fRec84, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow100, kStack)), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow101, kStack)), LoadVarInst(Address(fRec85, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec84, kStruct)[Int32(0)])), Float(1e-20f)))
		DeclareVarInst("float", fTemp53, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst68, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp46, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec82, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec18, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp53, kStack)))
		StoreVarInst(Address(fRec82, kStruct)[Int32(0)], LoadVarInst(Address(fVec18, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst69, kStruct))), Int32(2047))]))
		DeclareVarInst("float", fRec83, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp53, kStack))))
		DeclareVarInst("float", fTemp54, kStack, BinopInst("+", LoadVarInst(Address(fRec83, kStack)), LoadVarInst(Address(fRec79, kStack))))
		DeclareVarInst("float", fTemp55, kStack, BinopInst("+", LoadVarInst(Address(fRec71, kStack)), BinopInst("+", LoadVarInst(Address(fRec75, kStack)), LoadVarInst(Address(fTemp54, kStack)))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp55, kStack)))))))))))))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp55, kStack)))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fRec63, kStack)))))))))))
		DeclareVarInst("float", fTemp56, kStack, BinopInst("+", LoadVarInst(Address(fRec75, kStack)), LoadVarInst(Address(fRec71, kStack))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp54, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), LoadVarInst(Address(fTemp56, kStack))))))))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), LoadVarInst(Address(fTemp54, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp56, kStack))))))))))
		DeclareVarInst("float", fTemp57, kStack, BinopInst("+", LoadVarInst(Address(fRec83, kStack)), LoadVarInst(Address(fRec75, kStack))))
		DeclareVarInst("float", fTemp58, kStack, BinopInst("+", LoadVarInst(Address(fRec79, kStack)), LoadVarInst(Address(fRec71, kStack))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp57, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp58, kStack))))))))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp57, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp58, kStack))))))))))
		DeclareVarInst("float", fTemp59, kStack, BinopInst("+", LoadVarInst(Address(fRec83, kStack)), LoadVarInst(Address(fRec71, kStack))))
		DeclareVarInst("float", fTemp60, kStack, BinopInst("+", LoadVarInst(Address(fRec79, kStack)), LoadVarInst(Address(fRec75, kStack))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp59, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp60, kStack))))))))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp59, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp60, kStack))))))))))
		DeclareVarInst("float", fTemp61, kStack, BinopInst("*", Float(0.6f), BinopInst("*", LoadVarInst(Address(fTemp44, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp45, kStack))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), LoadVarInst(Address(fTemp61, kStack))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", LoadVarInst(Address(fTemp61, kStack)), BinopInst("*", Float(0.37f), BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec46, kStruct)[Int32(1)], LoadVarInst(Address(fRec46, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec47, kStruct)[Int32(1)], LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec49, kStruct)[Int32(1)], LoadVarInst(Address(fRec49, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec48, kStruct)[Int32(1)], LoadVarInst(Address(fRec48, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec55, kStruct)[Int32(1)], LoadVarInst(Address(fRec55, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec54, kStruct)[Int32(1)], LoadVarInst(Address(fRec54, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec53, kStruct)[Int32(1)], LoadVarInst(Address(fRec53, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec52, kStruct)[Int32(1)], LoadVarInst(Address(fRec52, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec51, kStruct)[Int32(1)], LoadVarInst(Address(fRec51, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec50, kStruct)[Int32(1)], LoadVarInst(Address(fRec50, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec56, kStruct)[Int32(1)], LoadVarInst(Address(fRec56, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec57, kStruct)[Int32(1)], LoadVarInst(Address(fRec57, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec61, kStruct)[Int32(1)], LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec60, kStruct)[Int32(1)], LoadVarInst(Address(fRec60, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec58, kStruct)[Int32(1)], LoadVarInst(Address(fRec58, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec65, kStruct)[Int32(1)], LoadVarInst(Address(fRec65, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec64, kStruct)[Int32(1)], LoadVarInst(Address(fRec64, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec62, kStruct)[Int32(1)], LoadVarInst(Address(fRec62, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec69, kStruct)[Int32(1)], LoadVarInst(Address(fRec69, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec68, kStruct)[Int32(1)], LoadVarInst(Address(fRec68, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec66, kStruct)[Int32(1)], LoadVarInst(Address(fRec66, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec73, kStruct)[Int32(1)], LoadVarInst(Address(fRec73, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec72, kStruct)[Int32(1)], LoadVarInst(Address(fRec72, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec70, kStruct)[Int32(1)], LoadVarInst(Address(fRec70, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec77, kStruct)[Int32(1)], LoadVarInst(Address(fRec77, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec76, kStruct)[Int32(1)], LoadVarInst(Address(fRec76, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec74, kStruct)[Int32(1)], LoadVarInst(Address(fRec74, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec81, kStruct)[Int32(1)], LoadVarInst(Address(fRec81, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec80, kStruct)[Int32(1)], LoadVarInst(Address(fRec80, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec78, kStruct)[Int32(1)], LoadVarInst(Address(fRec78, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec85, kStruct)[Int32(1)], LoadVarInst(Address(fRec85, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec84, kStruct)[Int32(1)], LoadVarInst(Address(fRec84, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec82, kStruct)[Int32(1)], LoadVarInst(Address(fRec82, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("float", ftbl1mydspSIG0[65537], kStaticStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("float", fConst6, kStruct)
	DeclareVarInst("float", fConst7, kStruct)
	DeclareVarInst("float", fConst8, kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("float", fRec11[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[32768], kStruct)
	DeclareVarInst("float", fConst9, kStruct)
	DeclareVarInst("int", iConst10, kStruct)
	DeclareVarInst("float", fConst11, kStruct)
	DeclareVarInst("float", fConst12, kStruct)
	DeclareVarInst("float", fConst13, kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fConst14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("float", fRec17[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fConst15, kStruct)
	DeclareVarInst("float", fRec19[2], kStruct)
	DeclareVarInst("float", fConst16, kStruct)
	DeclareVarInst("float", fRec21[2], kStruct)
	DeclareVarInst("float", fConst17, kStruct)
	DeclareVarInst("float", fRec20[2], kStruct)
	DeclareVarInst("float", fConst18, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("float", fRec23[2], kStruct)
	DeclareVarInst("float", fRec22[2], kStruct)
	DeclareVarInst("float", fRec28[2], kStruct)
	DeclareVarInst("float", fRec27[2], kStruct)
	DeclareVarInst("float", fRec26[2], kStruct)
	DeclareVarInst("float", fRec25[2], kStruct)
	DeclareVarInst("float", fRec24[2], kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("float", fRec29[2], kStruct)
	DeclareVarInst("float", fRec31[2], kStruct)
	DeclareVarInst("float", fRec30[2], kStruct)
	DeclareVarInst("float", fRec37[2], kStruct)
	DeclareVarInst("float", fRec36[2], kStruct)
	DeclareVarInst("float", fRec35[2], kStruct)
	DeclareVarInst("float", fRec34[2], kStruct)
	DeclareVarInst("float", fRec33[2], kStruct)
	DeclareVarInst("float", fRec32[2], kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("float", fRec38[2], kStruct)
	DeclareVarInst("float", fRec40[2], kStruct)
	DeclareVarInst("float", fRec39[2], kStruct)
	DeclareVarInst("float", fRec46[2], kStruct)
	DeclareVarInst("float", fRec45[2], kStruct)
	DeclareVarInst("float", fRec44[2], kStruct)
	DeclareVarInst("float", fRec43[2], kStruct)
	DeclareVarInst("float", fRec42[2], kStruct)
	DeclareVarInst("float", fRec41[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider7, kStruct)
	DeclareVarInst("float", fRec47[2], kStruct)
	DeclareVarInst("float", fRec49[2], kStruct)
	DeclareVarInst("float", fRec48[2], kStruct)
	DeclareVarInst("float", fRec55[2], kStruct)
	DeclareVarInst("float", fRec54[2], kStruct)
	DeclareVarInst("float", fRec53[2], kStruct)
	DeclareVarInst("float", fRec52[2], kStruct)
	DeclareVarInst("float", fRec51[2], kStruct)
	DeclareVarInst("float", fRec50[2], kStruct)
	DeclareVarInst("float", fVec2[2], kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider8, kStruct)
	DeclareVarInst("float", fRec56[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider9, kStruct)
	DeclareVarInst("float", fRec57[2], kStruct)
	DeclareVarInst("float", fVec3[4096], kStruct)
	DeclareVarInst("int", iConst19, kStruct)
	DeclareVarInst("float", fVec4[2048], kStruct)
	DeclareVarInst("int", iConst20, kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fConst21, kStruct)
	DeclareVarInst("float", fConst22, kStruct)
	DeclareVarInst("float", fConst23, kStruct)
	DeclareVarInst("float", fConst24, kStruct)
	DeclareVarInst("float", fRec61[2], kStruct)
	DeclareVarInst("float", fRec60[2], kStruct)
	DeclareVarInst("float", fVec5[32768], kStruct)
	DeclareVarInst("float", fConst25, kStruct)
	DeclareVarInst("int", iConst26, kStruct)
	DeclareVarInst("float", fVec6[4096], kStruct)
	DeclareVarInst("int", iConst27, kStruct)
	DeclareVarInst("float", fRec58[2], kStruct)
	DeclareVarInst("float", fConst28, kStruct)
	DeclareVarInst("float", fConst29, kStruct)
	DeclareVarInst("float", fConst30, kStruct)
	DeclareVarInst("float", fConst31, kStruct)
	DeclareVarInst("float", fRec65[2], kStruct)
	DeclareVarInst("float", fRec64[2], kStruct)
	DeclareVarInst("float", fVec7[16384], kStruct)
	DeclareVarInst("float", fConst32, kStruct)
	DeclareVarInst("int", iConst33, kStruct)
	DeclareVarInst("float", fVec8[4096], kStruct)
	DeclareVarInst("int", iConst34, kStruct)
	DeclareVarInst("float", fRec62[2], kStruct)
	DeclareVarInst("float", fConst35, kStruct)
	DeclareVarInst("float", fConst36, kStruct)
	DeclareVarInst("float", fConst37, kStruct)
	DeclareVarInst("float", fConst38, kStruct)
	DeclareVarInst("float", fRec69[2], kStruct)
	DeclareVarInst("float", fRec68[2], kStruct)
	DeclareVarInst("float", fVec9[32768], kStruct)
	DeclareVarInst("float", fConst39, kStruct)
	DeclareVarInst("int", iConst40, kStruct)
	DeclareVarInst("float", fVec10[4096], kStruct)
	DeclareVarInst("int", iConst41, kStruct)
	DeclareVarInst("float", fRec66[2], kStruct)
	DeclareVarInst("float", fConst42, kStruct)
	DeclareVarInst("float", fConst43, kStruct)
	DeclareVarInst("float", fConst44, kStruct)
	DeclareVarInst("float", fConst45, kStruct)
	DeclareVarInst("float", fRec73[2], kStruct)
	DeclareVarInst("float", fRec72[2], kStruct)
	DeclareVarInst("float", fVec11[16384], kStruct)
	DeclareVarInst("float", fConst46, kStruct)
	DeclareVarInst("int", iConst47, kStruct)
	DeclareVarInst("float", fVec12[2048], kStruct)
	DeclareVarInst("int", iConst48, kStruct)
	DeclareVarInst("float", fRec70[2], kStruct)
	DeclareVarInst("float", fConst49, kStruct)
	DeclareVarInst("float", fConst50, kStruct)
	DeclareVarInst("float", fConst51, kStruct)
	DeclareVarInst("float", fConst52, kStruct)
	DeclareVarInst("float", fRec77[2], kStruct)
	DeclareVarInst("float", fRec76[2], kStruct)
	DeclareVarInst("float", fVec13[16384], kStruct)
	DeclareVarInst("float", fConst53, kStruct)
	DeclareVarInst("int", iConst54, kStruct)
	DeclareVarInst("float", fVec14[4096], kStruct)
	DeclareVarInst("int", iConst55, kStruct)
	DeclareVarInst("float", fRec74[2], kStruct)
	DeclareVarInst("float", fConst56, kStruct)
	DeclareVarInst("float", fConst57, kStruct)
	DeclareVarInst("float", fConst58, kStruct)
	DeclareVarInst("float", fConst59, kStruct)
	DeclareVarInst("float", fRec81[2], kStruct)
	DeclareVarInst("float", fRec80[2], kStruct)
	DeclareVarInst("float", fVec15[16384], kStruct)
	DeclareVarInst("float", fConst60, kStruct)
	DeclareVarInst("int", iConst61, kStruct)
	DeclareVarInst("float", fVec16[4096], kStruct)
	DeclareVarInst("int", iConst62, kStruct)
	DeclareVarInst("float", fRec78[2], kStruct)
	DeclareVarInst("float", fConst63, kStruct)
	DeclareVarInst("float", fConst64, kStruct)
	DeclareVarInst("float", fConst65, kStruct)
	DeclareVarInst("float", fConst66, kStruct)
	DeclareVarInst("float", fRec85[2], kStruct)
	DeclareVarInst("float", fRec84[2], kStruct)
	DeclareVarInst("float", fVec17[16384], kStruct)
	DeclareVarInst("float", fConst67, kStruct)
	DeclareVarInst("int", iConst68, kStruct)
	DeclareVarInst("float", fVec18[2048], kStruct)
	DeclareVarInst("int", iConst69, kStruct)
	DeclareVarInst("float", fRec82[2], kStruct)
	DeclareVarInst("float", fRec1[3], kStruct)
	DeclareVarInst("float", fRec2[3], kStruct)
	DeclareVarInst("float", fRec3[3], kStruct)
	DeclareVarInst("float", fRec4[3], kStruct)
	DeclareVarInst("float", fRec5[3], kStruct)
	DeclareVarInst("float", fRec6[3], kStruct)
	DeclareVarInst("float", fRec7[3], kStruct)
	DeclareVarInst("float", fRec8[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), FunCallInst("cosf", BinopInst("/", Float(37699.113f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(628.31854f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst6, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst10, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst9, kStruct)))))))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(6283.1855f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst11, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("*", Float(3.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("/", Float(0.33333334f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("/", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst19, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("*", Float(0.02f), LoadVarInst(Address(fConst0, kStruct)))))))
	StoreVarInst(Address(iConst20, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst9, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst21, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst22, kStruct))))
	StoreVarInst(Address(fConst24, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst22, kStruct))))
	StoreVarInst(Address(fConst25, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst26, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fConst25, kStruct)))))))
	StoreVarInst(Address(iConst27, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst25, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst28, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("/", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst29, kStruct))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst29, kStruct))))
	StoreVarInst(Address(fConst32, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst33, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fConst32, kStruct)))))))
	StoreVarInst(Address(iConst34, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst32, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst35, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("/", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst37, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst38, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst36, kStruct))))
	StoreVarInst(Address(fConst39, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst40, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fConst39, kStruct)))))))
	StoreVarInst(Address(iConst41, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst39, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst42, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst43, kStruct), BinopInst("/", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst44, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst43, kStruct))))
	StoreVarInst(Address(fConst45, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst43, kStruct))))
	StoreVarInst(Address(fConst46, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst47, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst42, kStruct)), LoadVarInst(Address(fConst46, kStruct)))))))
	StoreVarInst(Address(iConst48, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst46, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst49, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst50, kStruct), BinopInst("/", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst51, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst50, kStruct))))
	StoreVarInst(Address(fConst52, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst50, kStruct))))
	StoreVarInst(Address(fConst53, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst54, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst49, kStruct)), LoadVarInst(Address(fConst53, kStruct)))))))
	StoreVarInst(Address(iConst55, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst53, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst56, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst57, kStruct), BinopInst("/", LoadVarInst(Address(fConst56, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst58, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst57, kStruct))))
	StoreVarInst(Address(fConst59, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst57, kStruct))))
	StoreVarInst(Address(fConst60, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst61, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst56, kStruct)), LoadVarInst(Address(fConst60, kStruct)))))))
	StoreVarInst(Address(iConst62, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst60, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fConst63, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst64, kStruct), BinopInst("/", LoadVarInst(Address(fConst63, kStruct)), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst65, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst64, kStruct))))
	StoreVarInst(Address(fConst66, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst64, kStruct))))
	StoreVarInst(Address(fConst67, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst68, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("-", LoadVarInst(Address(fConst63, kStruct)), LoadVarInst(Address(fConst67, kStruct)))))))
	StoreVarInst(Address(iConst69, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst67, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.2e+03f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(3.3e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.25f)))
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
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(32768))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec46, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec47, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec49, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec48, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec55, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec54, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec53, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec52, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec51, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec50, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec56, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec57, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(4096))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2048))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec61, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec60, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(32768))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4096))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec58, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec65, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec64, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(16384))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(4096))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(2))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec62, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec69, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec68, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(32768))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(4096))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(2))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec66, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(2))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec73, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec72, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(16384))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(2048))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(2))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec70, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(2))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec77, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(2))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec76, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(16384))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(4096))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(2))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec74, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(2))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec81, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(2))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec80, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(16384))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(4096))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(2))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec78, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(2))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec85, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec84, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(16384))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(2048))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(2))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec82, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(3))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(3))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(3))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(3))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(3))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(3))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(3))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(3))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl1mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", iRec16[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec16, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec16, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec16, kStruct)[Int32(1)]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec16, kStruct)[Int32(0)]), Int32(-1))))))
			StoreVarInst(Address(iRec16, kStruct)[Int32(1)], LoadVarInst(Address(iRec16, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow3, kStack)))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow4, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow5, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("-", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow6, kStack))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow2, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("int", iSlow13, kStack, BinopInst(">", LoadVarInst(Address(fSlow12, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow14, kStack, BinopInst(">", LoadVarInst(Address(iSlow13, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow15, kStack, CastInst("float", LoadVarInst(Address(iSlow13, kStack))))
	DeclareVarInst("int", iSlow16, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow12, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow12, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow19, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("int", iSlow20, kStack, BinopInst(">", LoadVarInst(Address(fSlow19, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow21, kStack, BinopInst(">", LoadVarInst(Address(iSlow20, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(iSlow20, kStack))))
	DeclareVarInst("int", iSlow23, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow19, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow25, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("int", iSlow26, kStack, BinopInst(">", LoadVarInst(Address(fSlow25, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow27, kStack, BinopInst(">", LoadVarInst(Address(iSlow26, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow28, kStack, CastInst("float", LoadVarInst(Address(iSlow26, kStack))))
	DeclareVarInst("int", iSlow29, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow25, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow25, kStack))))
	DeclareVarInst("float", fSlow31, kStack, CastInst("float", LoadVarInst(Address(fHslider7, kStruct))))
	DeclareVarInst("int", iSlow32, kStack, BinopInst(">", LoadVarInst(Address(fSlow31, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow33, kStack, BinopInst(">", LoadVarInst(Address(iSlow32, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow34, kStack, CastInst("float", LoadVarInst(Address(iSlow32, kStack))))
	DeclareVarInst("int", iSlow35, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow31, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow36, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fSlow31, kStack))))
	DeclareVarInst("float", fSlow37, kStack, BinopInst("*", Float(0.001f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider8, kStruct))))))
	DeclareVarInst("float", fSlow38, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider9, kStruct)))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst23, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow39, kStack))))
	DeclareVarInst("float", fSlow41, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow40, kStack)))))
	DeclareVarInst("float", fSlow42, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow40, kStack))))
	DeclareVarInst("float", fSlow43, kStack, BinopInst("/", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fSlow42, kStack))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow41, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow42, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow45, kStack, BinopInst("-", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fSlow44, kStack))))
	DeclareVarInst("float", fSlow46, kStack, BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), BinopInst("+", LoadVarInst(Address(fSlow44, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow43, kStack))))))
	DeclareVarInst("float", fSlow47, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst24, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow39, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow48, kStack))))
	DeclareVarInst("float", fSlow50, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow49, kStack)))))
	DeclareVarInst("float", fSlow51, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow49, kStack))))
	DeclareVarInst("float", fSlow52, kStack, BinopInst("/", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fSlow51, kStack))))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow50, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow51, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow54, kStack, BinopInst("-", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fSlow53, kStack))))
	DeclareVarInst("float", fSlow55, kStack, BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), BinopInst("+", LoadVarInst(Address(fSlow53, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow52, kStack))))))
	DeclareVarInst("float", fSlow56, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst31, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow48, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow57, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst37, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow57, kStack))))
	DeclareVarInst("float", fSlow59, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow58, kStack)))))
	DeclareVarInst("float", fSlow60, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow58, kStack))))
	DeclareVarInst("float", fSlow61, kStack, BinopInst("/", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fSlow60, kStack))))
	DeclareVarInst("float", fSlow62, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow59, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow60, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow63, kStack, BinopInst("-", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fSlow62, kStack))))
	DeclareVarInst("float", fSlow64, kStack, BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), BinopInst("+", LoadVarInst(Address(fSlow62, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow61, kStack))))))
	DeclareVarInst("float", fSlow65, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst38, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow57, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow66, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst44, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow67, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow66, kStack))))
	DeclareVarInst("float", fSlow68, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow67, kStack)))))
	DeclareVarInst("float", fSlow69, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow67, kStack))))
	DeclareVarInst("float", fSlow70, kStack, BinopInst("/", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fSlow69, kStack))))
	DeclareVarInst("float", fSlow71, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow68, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow69, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow72, kStack, BinopInst("-", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fSlow71, kStack))))
	DeclareVarInst("float", fSlow73, kStack, BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), BinopInst("+", LoadVarInst(Address(fSlow71, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow70, kStack))))))
	DeclareVarInst("float", fSlow74, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst45, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow66, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow75, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst51, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow76, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow75, kStack))))
	DeclareVarInst("float", fSlow77, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow76, kStack)))))
	DeclareVarInst("float", fSlow78, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow76, kStack))))
	DeclareVarInst("float", fSlow79, kStack, BinopInst("/", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fSlow78, kStack))))
	DeclareVarInst("float", fSlow80, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow77, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow78, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow81, kStack, BinopInst("-", LoadVarInst(Address(fSlow79, kStack)), LoadVarInst(Address(fSlow80, kStack))))
	DeclareVarInst("float", fSlow82, kStack, BinopInst("*", LoadVarInst(Address(fSlow75, kStack)), BinopInst("+", LoadVarInst(Address(fSlow80, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow79, kStack))))))
	DeclareVarInst("float", fSlow83, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst52, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow75, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow84, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst58, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow85, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow84, kStack))))
	DeclareVarInst("float", fSlow86, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow85, kStack)))))
	DeclareVarInst("float", fSlow87, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow85, kStack))))
	DeclareVarInst("float", fSlow88, kStack, BinopInst("/", LoadVarInst(Address(fSlow86, kStack)), LoadVarInst(Address(fSlow87, kStack))))
	DeclareVarInst("float", fSlow89, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow86, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow87, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow90, kStack, BinopInst("-", LoadVarInst(Address(fSlow88, kStack)), LoadVarInst(Address(fSlow89, kStack))))
	DeclareVarInst("float", fSlow91, kStack, BinopInst("*", LoadVarInst(Address(fSlow84, kStack)), BinopInst("+", LoadVarInst(Address(fSlow89, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow88, kStack))))))
	DeclareVarInst("float", fSlow92, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst59, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow84, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow93, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst65, kStruct)), LoadVarInst(Address(fSlow1, kStack))))))
	DeclareVarInst("float", fSlow94, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow93, kStack))))
	DeclareVarInst("float", fSlow95, kStack, BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow94, kStack)))))
	DeclareVarInst("float", fSlow96, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow94, kStack))))
	DeclareVarInst("float", fSlow97, kStack, BinopInst("/", LoadVarInst(Address(fSlow95, kStack)), LoadVarInst(Address(fSlow96, kStack))))
	DeclareVarInst("float", fSlow98, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow95, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow96, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow99, kStack, BinopInst("-", LoadVarInst(Address(fSlow97, kStack)), LoadVarInst(Address(fSlow98, kStack))))
	DeclareVarInst("float", fSlow100, kStack, BinopInst("*", LoadVarInst(Address(fSlow93, kStack)), BinopInst("+", LoadVarInst(Address(fSlow98, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow97, kStack))))))
	DeclareVarInst("float", fSlow101, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst66, kStruct)), LoadVarInst(Address(fSlow1, kStack))))), LoadVarInst(Address(fSlow93, kStack))), Float(-1.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp0, kStack, FunCallInst("max_f", Float(0.75f), FunCallInst("min_f", Float(4.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec12, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec11, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst10, kStruct))), Int32(32767))])))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec15, kStruct)[Int32(1)])), Float(0.0008f)))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow11, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow14, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow16, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow13, kStack)) BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec21, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec21, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow12, kStack))))) LoadVarInst(Address(fRec20, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))), Int32(65535)))])), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec20, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec20, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)])))) Float(0.0f))))))
			DeclareVarInst("float", fTemp4, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack)))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))
			DeclareVarInst("int", iTemp7, kStack, CastInst("int", LoadVarInst(Address(fTemp6, kStack))))
			DeclareVarInst("float", fTemp8, kStack, LoadVarInst(Address(ftbl1mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp7, kStack)), Int32(65536)))]))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp6, kStack)))), BinopInst("-", LoadVarInst(Address(ftbl1mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp7, kStack)), Int32(1)), Int32(65536)))]), LoadVarInst(Address(fTemp8, kStack))))))
			DeclareVarInst("float", fTemp10, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp3, kStack))))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp10, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp11, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp12, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp13, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp15, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec28, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fTemp15, kStack))), BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec27, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp15, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp14, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp13, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec24, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp12, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4, kStack)), LoadVarInst(Address(fTemp11, kStack))), BinopInst("*", LoadVarInst(Address(fTemp10, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec29, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow21, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec29, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec31, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow23, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec31, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec30, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow20, kStack)) BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec31, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec31, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow19, kStack))))) LoadVarInst(Address(fRec30, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp9, kStack))), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec29, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec30, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec29, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec30, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec29, kStruct)[Int32(0)])))) Float(0.0f))))))
			DeclareVarInst("float", fTemp17, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp16, kStack))))
			DeclareVarInst("float", fTemp18, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp16, kStack))))
			DeclareVarInst("float", fTemp19, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp18, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp20, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp19, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp21, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp23, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp22, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fTemp23, kStack))), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp23, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp22, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp21, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp20, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp19, kStack))), BinopInst("*", LoadVarInst(Address(fTemp18, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp17, kStack))), BinopInst("*", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp18, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp9, kStack)))))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
			StoreVarInst(Address(fRec38, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow27, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec38, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec40, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow29, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec40, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec39, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow26, kStack)) BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec40, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec40, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fRec40, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow25, kStack))))) LoadVarInst(Address(fRec39, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp26, kStack, BinopInst("*", Float(1.5707964f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec38, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec39, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec38, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec39, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])))) Float(0.0f)))), BinopInst("+", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))))
			DeclareVarInst("float", fTemp27, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp26, kStack))))
			DeclareVarInst("float", fTemp28, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp26, kStack))))
			DeclareVarInst("float", fTemp29, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fTemp28, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp30, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp29, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp31, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp30, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp32, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp31, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp33, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp32, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec46, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fTemp33, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp33, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec44, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp32, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec43, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp31, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp30, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp27, kStack)), LoadVarInst(Address(fTemp29, kStack))), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp34, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp25, kStack)), LoadVarInst(Address(fTemp27, kStack))), BinopInst("*", LoadVarInst(Address(fRec41, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp28, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp25, kStack)))))
			StoreVarInst(Address(fRec47, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow33, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst15, kStruct)), BinopInst("+", LoadVarInst(Address(fRec47, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec49, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow35, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst16, kStruct)), BinopInst("+", LoadVarInst(Address(fRec49, kStruct)[Int32(1)]), Float(1.0f)))))
			StoreVarInst(Address(fRec48, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iSlow32, kStack)) BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec49, kStruct)[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec49, kStruct)[Int32(0)]), LoadVarInst(Address(fConst16, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fRec49, kStruct)[Int32(0)])) LoadVarInst(Address(fSlow31, kStack))))) LoadVarInst(Address(fRec48, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp35, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp34, kStack)))), Select2Inst(BinopInst("<", LoadVarInst(Address(fRec47, kStruct)[Int32(0)]), Float(0.0f)) LoadVarInst(Address(fRec48, kStruct)[Int32(0)]) Select2Inst(BinopInst("<", LoadVarInst(Address(fRec47, kStruct)[Int32(0)]), LoadVarInst(Address(fConst15, kStruct))) BinopInst("*", LoadVarInst(Address(fRec48, kStruct)[Int32(0)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec47, kStruct)[Int32(0)])))) Float(0.0f))))))
			DeclareVarInst("float", fTemp36, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp35, kStack))))
			DeclareVarInst("float", fTemp37, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp35, kStack))))
			DeclareVarInst("float", fTemp38, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp37, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec50, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp39, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp38, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp40, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp39, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp41, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp40, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp42, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp41, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec54, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec55, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fTemp42, kStack))), BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec54, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp42, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec55, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec53, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp41, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec54, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec52, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp40, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec53, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec51, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp39, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec52, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec50, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp36, kStack)), LoadVarInst(Address(fTemp38, kStack))), BinopInst("*", LoadVarInst(Address(fTemp37, kStack)), LoadVarInst(Address(fRec51, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp43, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp10, kStack))), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp34, kStack)), LoadVarInst(Address(fTemp36, kStack))), BinopInst("*", LoadVarInst(Address(fRec50, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp37, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp24, kStack)), LoadVarInst(Address(fTemp34, kStack)))), BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), LoadVarInst(Address(fTemp4, kStack))))))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp43, kStack)))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst12, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fRec13, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fTemp43, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec56, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow37, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec56, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp44, kStack, BinopInst("*", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), LoadVarInst(Address(fRec56, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec57, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow38, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec57, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp45, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(1.0f), LoadVarInst(Address(fRec57, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("*", LoadVarInst(Address(fTemp44, kStack)), LoadVarInst(Address(fTemp45, kStack))))
			DeclareVarInst("float", fTemp46, kStack, BinopInst("*", Float(0.18f), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst19, kStruct))), Int32(4095))])))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fTemp46, kStack))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst20, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec10, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fTemp1, kStack)))))
			StoreVarInst(Address(fRec61, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec61, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec60, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fRec60, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec60, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp47, kStack, BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec58, kStruct)[Int32(1)])), LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst26, kStruct))), Int32(32767))])))
			StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("-", LoadVarInst(Address(fTemp47, kStack)), LoadVarInst(Address(fTemp46, kStack))))
			StoreVarInst(Address(fRec58, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst27, kStruct))), Int32(4095))]))
			DeclareVarInst("float", fRec59, kStack, BinopInst("*", Float(0.6f), BinopInst("-", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fTemp47, kStack)))))
			StoreVarInst(Address(fRec65, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec65, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec64, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec64, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec65, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec64, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp48, kStack, BinopInst("+", LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst33, kStruct))), Int32(16383))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec62, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp48, kStack)))
			StoreVarInst(Address(fRec62, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst34, kStruct))), Int32(4095))]))
			DeclareVarInst("float", fRec63, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp48, kStack)))))
			StoreVarInst(Address(fRec69, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec69, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fRec2, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec68, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fRec68, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fRec69, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec68, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp49, kStack, BinopInst("+", LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst40, kStruct))), Int32(32767))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec66, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp49, kStack)))
			StoreVarInst(Address(fRec66, kStruct)[Int32(0)], LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst41, kStruct))), Int32(4095))]))
			DeclareVarInst("float", fRec67, kStack, MinusInst(BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp49, kStack)))))
			StoreVarInst(Address(fRec73, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec73, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec72, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fRec72, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec73, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec72, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp50, kStack, BinopInst("-", LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst47, kStruct))), Int32(16383))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec70, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp50, kStack)))
			StoreVarInst(Address(fRec70, kStruct)[Int32(0)], LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst48, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec71, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp50, kStack))))
			StoreVarInst(Address(fRec77, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec77, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec76, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow81, kStack)), LoadVarInst(Address(fRec76, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow82, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow83, kStack)), LoadVarInst(Address(fRec77, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec76, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp51, kStack, BinopInst("-", LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst54, kStruct))), Int32(16383))]), BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec74, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp51, kStack)))
			StoreVarInst(Address(fRec74, kStruct)[Int32(0)], LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst55, kStruct))), Int32(4095))]))
			DeclareVarInst("float", fRec75, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp51, kStack))))
			StoreVarInst(Address(fRec81, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec81, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec80, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow90, kStack)), LoadVarInst(Address(fRec80, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow91, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow92, kStack)), LoadVarInst(Address(fRec81, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec80, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp52, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp46, kStack)), LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst61, kStruct))), Int32(16383))])), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec78, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp52, kStack)))
			StoreVarInst(Address(fRec78, kStruct)[Int32(0)], LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst62, kStruct))), Int32(4095))]))
			DeclareVarInst("float", fRec79, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp52, kStack))))
			StoreVarInst(Address(fRec85, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec85, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fRec1, kStruct)[Int32(2)]))))))
			StoreVarInst(Address(fRec84, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow99, kStack)), LoadVarInst(Address(fRec84, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow100, kStack)), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow101, kStack)), LoadVarInst(Address(fRec85, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fRec84, kStruct)[Int32(0)])), Float(1e-20f)))
			DeclareVarInst("float", fTemp53, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst68, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp46, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fRec82, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec18, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp53, kStack)))
			StoreVarInst(Address(fRec82, kStruct)[Int32(0)], LoadVarInst(Address(fVec18, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst69, kStruct))), Int32(2047))]))
			DeclareVarInst("float", fRec83, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp53, kStack))))
			DeclareVarInst("float", fTemp54, kStack, BinopInst("+", LoadVarInst(Address(fRec83, kStack)), LoadVarInst(Address(fRec79, kStack))))
			DeclareVarInst("float", fTemp55, kStack, BinopInst("+", LoadVarInst(Address(fRec71, kStack)), BinopInst("+", LoadVarInst(Address(fRec75, kStack)), LoadVarInst(Address(fTemp54, kStack)))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp55, kStack)))))))))))))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp55, kStack)))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fRec63, kStack)))))))))))
			DeclareVarInst("float", fTemp56, kStack, BinopInst("+", LoadVarInst(Address(fRec75, kStack)), LoadVarInst(Address(fRec71, kStack))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp54, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), LoadVarInst(Address(fTemp56, kStack))))))))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), LoadVarInst(Address(fTemp54, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp56, kStack))))))))))
			DeclareVarInst("float", fTemp57, kStack, BinopInst("+", LoadVarInst(Address(fRec83, kStack)), LoadVarInst(Address(fRec75, kStack))))
			DeclareVarInst("float", fTemp58, kStack, BinopInst("+", LoadVarInst(Address(fRec79, kStack)), LoadVarInst(Address(fRec71, kStack))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp57, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp58, kStack))))))))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp57, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp58, kStack))))))))))
			DeclareVarInst("float", fTemp59, kStack, BinopInst("+", LoadVarInst(Address(fRec83, kStack)), LoadVarInst(Address(fRec71, kStack))))
			DeclareVarInst("float", fTemp60, kStack, BinopInst("+", LoadVarInst(Address(fRec79, kStack)), LoadVarInst(Address(fRec75, kStack))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp59, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp60, kStack))))))))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec58, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec62, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec70, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec82, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec59, kStack)), BinopInst("+", LoadVarInst(Address(fRec63, kStack)), LoadVarInst(Address(fTemp59, kStack)))))))), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec66, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec74, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec78, kStruct)[Int32(1)]), BinopInst("+", LoadVarInst(Address(fRec10, kStack)), BinopInst("+", LoadVarInst(Address(fRec67, kStack)), LoadVarInst(Address(fTemp60, kStack))))))))))
			DeclareVarInst("float", fTemp61, kStack, BinopInst("*", Float(0.6f), BinopInst("*", LoadVarInst(Address(fTemp44, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp45, kStack))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), LoadVarInst(Address(fTemp61, kStack))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", LoadVarInst(Address(fTemp61, kStack)), BinopInst("*", Float(0.37f), BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec46, kStruct)[Int32(1)], LoadVarInst(Address(fRec46, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec47, kStruct)[Int32(1)], LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec49, kStruct)[Int32(1)], LoadVarInst(Address(fRec49, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec48, kStruct)[Int32(1)], LoadVarInst(Address(fRec48, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec55, kStruct)[Int32(1)], LoadVarInst(Address(fRec55, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec54, kStruct)[Int32(1)], LoadVarInst(Address(fRec54, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec53, kStruct)[Int32(1)], LoadVarInst(Address(fRec53, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec52, kStruct)[Int32(1)], LoadVarInst(Address(fRec52, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec51, kStruct)[Int32(1)], LoadVarInst(Address(fRec51, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec50, kStruct)[Int32(1)], LoadVarInst(Address(fRec50, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec56, kStruct)[Int32(1)], LoadVarInst(Address(fRec56, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec57, kStruct)[Int32(1)], LoadVarInst(Address(fRec57, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec61, kStruct)[Int32(1)], LoadVarInst(Address(fRec61, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec60, kStruct)[Int32(1)], LoadVarInst(Address(fRec60, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec58, kStruct)[Int32(1)], LoadVarInst(Address(fRec58, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec65, kStruct)[Int32(1)], LoadVarInst(Address(fRec65, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec64, kStruct)[Int32(1)], LoadVarInst(Address(fRec64, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec62, kStruct)[Int32(1)], LoadVarInst(Address(fRec62, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec69, kStruct)[Int32(1)], LoadVarInst(Address(fRec69, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec68, kStruct)[Int32(1)], LoadVarInst(Address(fRec68, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec66, kStruct)[Int32(1)], LoadVarInst(Address(fRec66, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec73, kStruct)[Int32(1)], LoadVarInst(Address(fRec73, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec72, kStruct)[Int32(1)], LoadVarInst(Address(fRec72, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec70, kStruct)[Int32(1)], LoadVarInst(Address(fRec70, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec77, kStruct)[Int32(1)], LoadVarInst(Address(fRec77, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec76, kStruct)[Int32(1)], LoadVarInst(Address(fRec76, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec74, kStruct)[Int32(1)], LoadVarInst(Address(fRec74, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec81, kStruct)[Int32(1)], LoadVarInst(Address(fRec81, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec80, kStruct)[Int32(1)], LoadVarInst(Address(fRec80, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec78, kStruct)[Int32(1)], LoadVarInst(Address(fRec78, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec85, kStruct)[Int32(1)], LoadVarInst(Address(fRec85, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec84, kStruct)[Int32(1)], LoadVarInst(Address(fRec84, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec82, kStruct)[Int32(1)], LoadVarInst(Address(fRec82, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(2)], LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
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
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 76 bytes
Heap size int* = 0 bytes
Heap size real = 844692 bytes
Total heap size = 844776 bytes
Stack size in compute = 424 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec46 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec45 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec44 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec43 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec47 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec49 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec48 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec55 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec54 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec53 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec52 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec51 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec50 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec56 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec57 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec61 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec60 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec58 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec65 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec64 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec62 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec69 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec68 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec66 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec73 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec72 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec70 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec77 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec76 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec74 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec81 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec80 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec78 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec85 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec84 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec82 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 4 write = 0 ratio = 4
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec46 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec45 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec44 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec43 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec47 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec49 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec48 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec55 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec54 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec53 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec52 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec51 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec50 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec56 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec57 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst24 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec61 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec60 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec58 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst31 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec65 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec64 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec62 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst38 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec69 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec68 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec66 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst45 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec73 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec72 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec70 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst52 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec77 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec76 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec74 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst59 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec81 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec80 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec78 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst65 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst66 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec85 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec84 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec82 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fConst8 size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fRec12 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec11 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = IOTA0 size = 1 size_bytes = 4 read = 35 write = 1 ratio = 36
Field = fVec0 size = 32768 size_bytes = 131072 read = 1 write = 1 ratio = 6.10352e-05
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec15 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst14 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec17 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fRec19 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fConst16 size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fRec21 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fConst18 size = 1 size_bytes = 4 read = 4 write = 0 ratio = 4
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec22 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec28 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec27 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec26 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec25 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec24 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec31 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec30 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec37 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec36 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec35 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec34 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec33 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec32 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec40 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec39 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec46 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec45 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec44 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec43 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec42 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec41 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec47 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec49 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec48 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec55 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec54 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec53 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec52 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec51 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec50 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec13 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec56 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec57 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec3 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst20 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec9 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec61 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec60 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec5 size = 32768 size_bytes = 131072 read = 1 write = 1 ratio = 6.10352e-05
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst26 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst27 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec58 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec65 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec64 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec7 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec8 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst34 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec62 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec69 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec68 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec9 size = 32768 size_bytes = 131072 read = 1 write = 1 ratio = 6.10352e-05
Field = fConst39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst40 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec10 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst41 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec66 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec73 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec72 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec11 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst47 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec12 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst48 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec70 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec77 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec76 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec13 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst54 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec14 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst55 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec74 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec81 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec80 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec15 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst61 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec16 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst62 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec78 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fConst63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec85 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec84 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec17 size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst68 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec18 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst69 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec82 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fRec1 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec2 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec3 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fRec4 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec5 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec6 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec7 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec8 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
