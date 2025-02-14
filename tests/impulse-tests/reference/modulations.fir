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

DeclareStructTypeInst(StructType<"mydspSIG0",("int", IOTA1)("int[2]", iVec12SI)>)

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
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 10 Store = 4 Binop = 10 [ { Int(&) = 3 } { Int(+) = 4 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))))
		StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Modulations")
	OpenHorizontalBox("Instrument")
	AddMetaDeclareInst(fHslider2, "acc", "1 1 -10 0 15")
	AddMetaDeclareInst(fHslider2, "unit", "Hz")
	AddHorizontalSlider("Frequency", fHslider2, 3.3e+02f, 1e+02f, 1.2e+03f, 0.1f)
	AddMetaDeclareInst(fHslider9, "acc", "1 1 -10 0 10")
	AddMetaDeclareInst(fHslider9, "style", "knob")
	AddHorizontalSlider("General Volume", fHslider9, 1.0f, 0.75f, 4.0f, 0.01f)
	AddMetaDeclareInst(fHslider6, "acc", "1 0 -10 0 10")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddHorizontalSlider("Oscillator Volume", fHslider6, 0.5f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fHslider0, "acc", "0 0 -10 0 10")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("Modulating Frequency", fHslider0, 1.2e+03f, 9e+02f, 1.7e+03f, 0.1f)
	CloseboxInst
	OpenVerticalBox("Modulations")
	AddMetaDeclareInst(fHslider3, "acc", "0 0 -30 0 10")
	AddMetaDeclareInst(fHslider3, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 0 (ASR Envelope)", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider4, "acc", "0 0 -30 0 5")
	AddMetaDeclareInst(fHslider4, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 1 (ASR Envelope)", fHslider4, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider5, "acc", "2 1 -30 0 10")
	AddMetaDeclareInst(fHslider5, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 2 (ASR Envelope)", fHslider5, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "acc", "1 0 -10 0 10")
	AddMetaDeclareInst(fHslider1, "tooltip", "noteOn = 1, noteOff = 0")
	AddHorizontalSlider("Play Modulation 3 (ASR Envelope)", fHslider1, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	OpenVerticalBox("Reverb")
	AddMetaDeclareInst(fHslider8, "acc", "1 1 -10 0 10")
	AddHorizontalSlider("Reverberation Room Size(InstrReverb)", fHslider8, 0.5f, 0.05f, 2.0f, 0.01f)
	AddMetaDeclareInst(fHslider7, "acc", "1 1 -10 0 10")
	AddHorizontalSlider("Reverberation Volume(InstrReverb)", fHslider7, 0.25f, 0.05f, 1.0f, 0.01f)
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
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst("float", ftbl1SImydspSIG0[65537], kStaticStruct)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("int", fSampleRate)("float", fConst0KI)("int", iConst1KI)("float", fConst2KI)("float", fConst3KI)("float", fConst4KI)("float[2]", fVec6SI)("float", fConst5KI)("FAUSTFLOAT", fHslider0)("float[2]", fVec9SE)("float[2]", fVec8SE)("float", fConst6KI)("FAUSTFLOAT", fHslider1)("float[2]", fVec14SE)("float", fConst7KI)("float[2]", fVec17SE)("float", fConst8KI)("float[2]", fVec16SE)("float", fConst9KI)("FAUSTFLOAT", fHslider2)("float[2]", fVec21SE)("float[2]", fVec20SE)("FAUSTFLOAT", fHslider3)("float[2]", fVec24SE)("float[2]", fVec27SE)("float[2]", fVec26SE)("FAUSTFLOAT", fHslider4)("float[2]", fVec31SE)("float[2]", fVec34SE)("float[2]", fVec33SE)("FAUSTFLOAT", fHslider5)("float[2]", fVec39SE)("float[2]", fVec42SE)("float[2]", fVec41SE)("float[2]", fVec4SE)("FAUSTFLOAT", fHslider6)("float[2]", fVec48SE)("FAUSTFLOAT", fHslider7)("float[2]", fVec50SE)("float[4096]", fVec52SE)("float", fConst10KI)("FAUSTFLOAT", fHslider8)("float", fConst11KI)("float", fConst12KI)("float", fConst13KI)("float", fConst14KI)("float", fConst15KI)("float", fConst16KI)("float[2]", fVec57SE)("float", fConst17KI)("float[2]", fVec55SE)("float[32768]", fVec61SE)("float", fConst18KI)("int", iConst19KI)("float", fConst20KI)("float", fConst21KI)("float", fConst22KI)("float[2]", fVec66SE)("float", fConst23KI)("float[2]", fVec64SE)("float[16384]", fVec70SE)("float", fConst24KI)("int", iConst25KI)("float", fConst26KI)("float", fConst27KI)("float", fConst28KI)("float", fConst29KI)("float[2]", fVec76SE)("float[2]", fVec74SE)("float[16384]", fVec80SE)("float", fConst30KI)("int", iConst31KI)("float", fConst32KI)("float", fConst33KI)("float", fConst34KI)("float", fConst35KI)("float[2]", fVec86SE)("float[2]", fVec84SE)("float[16384]", fVec90SE)("float", fConst36KI)("int", iConst37KI)("float", fConst38KI)("float", fConst39KI)("float", fConst40KI)("float[2]", fVec99SE)("float", fConst41KI)("float[2]", fVec97SE)("float[32768]", fVec103SE)("float", fConst42KI)("int", iConst43KI)("float", fConst44KI)("float", fConst45KI)("float", fConst46KI)("float[2]", fVec108SE)("float", fConst47KI)("float[2]", fVec106SE)("float[32768]", fVec112SE)("float", fConst48KI)("int", iConst49KI)("float", fConst50KI)("float", fConst51KI)("float", fConst52KI)("float", fConst53KI)("float[2]", fVec119SE)("float[2]", fVec117SE)("float[16384]", fVec123SE)("float", fConst54KI)("int", iConst55KI)("float", fConst56KI)("float", fConst57KI)("float", fConst58KI)("float", fConst59KI)("float[2]", fVec130SE)("float[2]", fVec128SE)("float[16384]", fVec134SE)("float", fConst60KI)("int", iConst61KI)("float[2]", fVec98SE)("float[4]", fVec100SE)("float[2]", fVec144SE)("float[2]", fVec145SE)("float[2]", fVec143SE)("float[2]", fVec147SE)("float[2]", fVec142SE)("float[2]", fVec149SE)("float[2]", fVec141SE)("float[2]", fVec151SE)("float[2]", fVec140SE)("float[2]", fVec153SE)("float[2]", fVec139SE)("float[2]", fVec5SE)("float[2]", fVec161SE)("float[2]", fVec162SE)("float[2]", fVec160SE)("float[2]", fVec164SE)("float[2]", fVec159SE)("float[2]", fVec166SE)("float[2]", fVec158SE)("float[2]", fVec168SE)("float[2]", fVec157SE)("float[2]", fVec170SE)("float[2]", fVec156SE)("float[2]", fVec30SE)("float[2]", fVec173SE)("float[2]", fVec37SE)("float[2]", fVec181SE)("float[2]", fVec182SE)("float[2]", fVec180SE)("float[2]", fVec184SE)("float[2]", fVec179SE)("float[2]", fVec186SE)("float[2]", fVec178SE)("float[2]", fVec188SE)("float[2]", fVec177SE)("float[2]", fVec190SE)("float[2]", fVec176SE)("float[2]", fVec38SE)("float[2]", fVec198SE)("float[2]", fVec199SE)("float[2]", fVec197SE)("float[2]", fVec201SE)("float[2]", fVec196SE)("float[2]", fVec203SE)("float[2]", fVec195SE)("float[2]", fVec205SE)("float[2]", fVec194SE)("float[2]", fVec207SE)("float[2]", fVec193SE)("float[2]", fVec45SE)("float[2]", fVec46SE)("float[2048]", fVec211SE)("int", iConst62KI)("float[2]", fVec96SE)("float[2]", fVec94SE)("float[2]", fVec56SE)("float[4]", fVec58SE)("float[4096]", fVec215SE)("int", iConst63KI)("float[2]", fVec54SE)("float[2]", fVec0SE)("float[2]", fVec65SE)("float[4]", fVec67SE)("float[4096]", fVec219SE)("int", iConst64KI)("float[2]", fVec72SE)("float[2]", fVec1SE)("float[2]", fVec107SE)("float[4]", fVec109SE)("float[4096]", fVec223SE)("int", iConst65KI)("float[2]", fVec114SE)("float[2]", fVec95SE)("float[2]", fVec75SE)("float[4]", fVec77SE)("float[2048]", fVec227SE)("int", iConst66KI)("float[2]", fVec82SE)("float[2]", fVec2SE)("float[2]", fVec118SE)("float[4]", fVec120SE)("float[4096]", fVec231SE)("int", iConst67KI)("float[2]", fVec125SE)("float[2]", fVec116SE)("float[2]", fVec129SE)("float[4]", fVec131SE)("float[4096]", fVec235SE)("int", iConst68KI)("float[2]", fVec136SE)("float[2]", fVec127SE)("float[2]", fVec85SE)("float[4]", fVec87SE)("float[2048]", fVec239SE)("int", iConst69KI)("float[2]", fVec92SE)("float[2]", fVec3SE)("FAUSTFLOAT", fHslider9)("float[2]", fVec242SE)>)

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
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl1SImydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(iConst1KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("*", Float(0.02f), LoadVarInst(Address(fConst0KI, kStruct)))))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(6283.1855f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst2KI, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst2KI, kStruct)))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst7KI, kStruct), BinopInst("*", Float(3.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst8KI, kStruct), BinopInst("/", Float(0.33333334f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst9KI, kStruct), BinopInst("/", Float(0.5f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst10KI, kStruct), FunCallInst("cosf", BinopInst("/", Float(37699.113f), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst11KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst12KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst11KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst13KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst12KI, kStruct))))
	StoreVarInst(Address(fConst14KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(628.31854f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst15KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst14KI, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst16KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst14KI, kStruct)))))
	StoreVarInst(Address(fConst17KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst12KI, kStruct))))
	StoreVarInst(Address(fConst18KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst19KI, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst11KI, kStruct)), MinusInst(LoadVarInst(Address(fConst18KI, kStruct))))))))
	StoreVarInst(Address(fConst20KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst21KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst20KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst22KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst21KI, kStruct))))
	StoreVarInst(Address(fConst23KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst21KI, kStruct))))
	StoreVarInst(Address(fConst24KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst25KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst20KI, kStruct)), MinusInst(LoadVarInst(Address(fConst24KI, kStruct))))))))
	StoreVarInst(Address(fConst26KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst27KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst26KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst28KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst27KI, kStruct))))
	StoreVarInst(Address(fConst29KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst27KI, kStruct))))
	StoreVarInst(Address(fConst30KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst31KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst26KI, kStruct)), MinusInst(LoadVarInst(Address(fConst30KI, kStruct))))))))
	StoreVarInst(Address(fConst32KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst33KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst32KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst34KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst33KI, kStruct))))
	StoreVarInst(Address(fConst35KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst33KI, kStruct))))
	StoreVarInst(Address(fConst36KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst37KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst32KI, kStruct)), MinusInst(LoadVarInst(Address(fConst36KI, kStruct))))))))
	StoreVarInst(Address(fConst38KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst39KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst38KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst40KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst39KI, kStruct))))
	StoreVarInst(Address(fConst41KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst39KI, kStruct))))
	StoreVarInst(Address(fConst42KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst43KI, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst38KI, kStruct)), MinusInst(LoadVarInst(Address(fConst42KI, kStruct))))))))
	StoreVarInst(Address(fConst44KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst45KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst44KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst46KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst45KI, kStruct))))
	StoreVarInst(Address(fConst47KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst45KI, kStruct))))
	StoreVarInst(Address(fConst48KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst49KI, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst44KI, kStruct)), MinusInst(LoadVarInst(Address(fConst48KI, kStruct))))))))
	StoreVarInst(Address(fConst50KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst51KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst50KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst52KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst51KI, kStruct))))
	StoreVarInst(Address(fConst53KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst51KI, kStruct))))
	StoreVarInst(Address(fConst54KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst55KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst50KI, kStruct)), MinusInst(LoadVarInst(Address(fConst54KI, kStruct))))))))
	StoreVarInst(Address(fConst56KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst57KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst56KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst58KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst57KI, kStruct))))
	StoreVarInst(Address(fConst59KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst57KI, kStruct))))
	StoreVarInst(Address(fConst60KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst61KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst56KI, kStruct)), MinusInst(LoadVarInst(Address(fConst60KI, kStruct))))))))
	StoreVarInst(Address(iConst62KI, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst42KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst63KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst18KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst64KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst24KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst65KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst48KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst66KI, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst30KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst67KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst54KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst68KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst60KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst69KI, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst36KI, kStruct)), Float(-1.0f))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.2e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(3.3e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.25f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider9, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec39SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec50SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(4096))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec57SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec55SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(32768))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec66SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec64SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(16384))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec76SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(16384))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec80SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec86SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec84SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(16384))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec90SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec99SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec97SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(32768))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec103SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec108SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec106SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(32768))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec112SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec119SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec117SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(16384))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec123SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec130SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec128SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(16384))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec134SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec98SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec100SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec144SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec145SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec143SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec147SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec142SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec149SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec141SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec151SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec140SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec153SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec139SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec161SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec162SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(2))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec160SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(2))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec164SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec159SE, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec166SE, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(2))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec158SE, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(2))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec168SE, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(2))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec157SE, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(2))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec170SE, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec156SE, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(2))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(2))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec173SE, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(2))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec37SE, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(2))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec181SE, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(2))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec182SE, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(2))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec180SE, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(2))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec184SE, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(2))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec179SE, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(2))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec186SE, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(2))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec178SE, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(2))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec188SE, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(2))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec177SE, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(2))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec190SE, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(2))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec176SE, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(2))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec198SE, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(2))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec199SE, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(2))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec197SE, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(2))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec201SE, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(2))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec196SE, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(2))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec203SE, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(2))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec195SE, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(2))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec205SE, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(2))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec194SE, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(2))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec207SE, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(2))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec193SE, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(2))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec45SE, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(2))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l99, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l99, kLoop)), Int32(2048))
		StoreVarInst(Address(l99, kLoop), BinopInst("+", LoadVarInst(Address(l99, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec211SE, kStruct)[LoadVarInst(Address(l99, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l100, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l100, kLoop)), Int32(2))
		StoreVarInst(Address(l100, kLoop), BinopInst("+", LoadVarInst(Address(l100, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec96SE, kStruct)[LoadVarInst(Address(l100, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l101, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l101, kLoop)), Int32(2))
		StoreVarInst(Address(l101, kLoop), BinopInst("+", LoadVarInst(Address(l101, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec94SE, kStruct)[LoadVarInst(Address(l101, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l102, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l102, kLoop)), Int32(2))
		StoreVarInst(Address(l102, kLoop), BinopInst("+", LoadVarInst(Address(l102, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SE, kStruct)[LoadVarInst(Address(l102, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l103, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l103, kLoop)), Int32(4))
		StoreVarInst(Address(l103, kLoop), BinopInst("+", LoadVarInst(Address(l103, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec58SE, kStruct)[LoadVarInst(Address(l103, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l104, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l104, kLoop)), Int32(4096))
		StoreVarInst(Address(l104, kLoop), BinopInst("+", LoadVarInst(Address(l104, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec215SE, kStruct)[LoadVarInst(Address(l104, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l105, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l105, kLoop)), Int32(2))
		StoreVarInst(Address(l105, kLoop), BinopInst("+", LoadVarInst(Address(l105, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec54SE, kStruct)[LoadVarInst(Address(l105, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l106, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l106, kLoop)), Int32(2))
		StoreVarInst(Address(l106, kLoop), BinopInst("+", LoadVarInst(Address(l106, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l106, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l107, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l107, kLoop)), Int32(2))
		StoreVarInst(Address(l107, kLoop), BinopInst("+", LoadVarInst(Address(l107, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec65SE, kStruct)[LoadVarInst(Address(l107, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l108, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l108, kLoop)), Int32(4))
		StoreVarInst(Address(l108, kLoop), BinopInst("+", LoadVarInst(Address(l108, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l108, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l109, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l109, kLoop)), Int32(4096))
		StoreVarInst(Address(l109, kLoop), BinopInst("+", LoadVarInst(Address(l109, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec219SE, kStruct)[LoadVarInst(Address(l109, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l110, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l110, kLoop)), Int32(2))
		StoreVarInst(Address(l110, kLoop), BinopInst("+", LoadVarInst(Address(l110, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l110, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l111, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l111, kLoop)), Int32(2))
		StoreVarInst(Address(l111, kLoop), BinopInst("+", LoadVarInst(Address(l111, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l111, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l112, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l112, kLoop)), Int32(2))
		StoreVarInst(Address(l112, kLoop), BinopInst("+", LoadVarInst(Address(l112, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec107SE, kStruct)[LoadVarInst(Address(l112, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l113, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l113, kLoop)), Int32(4))
		StoreVarInst(Address(l113, kLoop), BinopInst("+", LoadVarInst(Address(l113, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec109SE, kStruct)[LoadVarInst(Address(l113, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l114, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l114, kLoop)), Int32(4096))
		StoreVarInst(Address(l114, kLoop), BinopInst("+", LoadVarInst(Address(l114, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec223SE, kStruct)[LoadVarInst(Address(l114, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l115, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l115, kLoop)), Int32(2))
		StoreVarInst(Address(l115, kLoop), BinopInst("+", LoadVarInst(Address(l115, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec114SE, kStruct)[LoadVarInst(Address(l115, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l116, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l116, kLoop)), Int32(2))
		StoreVarInst(Address(l116, kLoop), BinopInst("+", LoadVarInst(Address(l116, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec95SE, kStruct)[LoadVarInst(Address(l116, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l117, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l117, kLoop)), Int32(2))
		StoreVarInst(Address(l117, kLoop), BinopInst("+", LoadVarInst(Address(l117, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec75SE, kStruct)[LoadVarInst(Address(l117, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l118, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l118, kLoop)), Int32(4))
		StoreVarInst(Address(l118, kLoop), BinopInst("+", LoadVarInst(Address(l118, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l118, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l119, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l119, kLoop)), Int32(2048))
		StoreVarInst(Address(l119, kLoop), BinopInst("+", LoadVarInst(Address(l119, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec227SE, kStruct)[LoadVarInst(Address(l119, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l120, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l120, kLoop)), Int32(2))
		StoreVarInst(Address(l120, kLoop), BinopInst("+", LoadVarInst(Address(l120, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l120, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l121, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l121, kLoop)), Int32(2))
		StoreVarInst(Address(l121, kLoop), BinopInst("+", LoadVarInst(Address(l121, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l121, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l122, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l122, kLoop)), Int32(2))
		StoreVarInst(Address(l122, kLoop), BinopInst("+", LoadVarInst(Address(l122, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec118SE, kStruct)[LoadVarInst(Address(l122, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l123, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l123, kLoop)), Int32(4))
		StoreVarInst(Address(l123, kLoop), BinopInst("+", LoadVarInst(Address(l123, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec120SE, kStruct)[LoadVarInst(Address(l123, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l124, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l124, kLoop)), Int32(4096))
		StoreVarInst(Address(l124, kLoop), BinopInst("+", LoadVarInst(Address(l124, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec231SE, kStruct)[LoadVarInst(Address(l124, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l125, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l125, kLoop)), Int32(2))
		StoreVarInst(Address(l125, kLoop), BinopInst("+", LoadVarInst(Address(l125, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec125SE, kStruct)[LoadVarInst(Address(l125, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l126, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l126, kLoop)), Int32(2))
		StoreVarInst(Address(l126, kLoop), BinopInst("+", LoadVarInst(Address(l126, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec116SE, kStruct)[LoadVarInst(Address(l126, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l127, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l127, kLoop)), Int32(2))
		StoreVarInst(Address(l127, kLoop), BinopInst("+", LoadVarInst(Address(l127, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec129SE, kStruct)[LoadVarInst(Address(l127, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l128, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l128, kLoop)), Int32(4))
		StoreVarInst(Address(l128, kLoop), BinopInst("+", LoadVarInst(Address(l128, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec131SE, kStruct)[LoadVarInst(Address(l128, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l129, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l129, kLoop)), Int32(4096))
		StoreVarInst(Address(l129, kLoop), BinopInst("+", LoadVarInst(Address(l129, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec235SE, kStruct)[LoadVarInst(Address(l129, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l130, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l130, kLoop)), Int32(2))
		StoreVarInst(Address(l130, kLoop), BinopInst("+", LoadVarInst(Address(l130, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec136SE, kStruct)[LoadVarInst(Address(l130, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l131, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l131, kLoop)), Int32(2))
		StoreVarInst(Address(l131, kLoop), BinopInst("+", LoadVarInst(Address(l131, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec127SE, kStruct)[LoadVarInst(Address(l131, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l132, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l132, kLoop)), Int32(2))
		StoreVarInst(Address(l132, kLoop), BinopInst("+", LoadVarInst(Address(l132, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec85SE, kStruct)[LoadVarInst(Address(l132, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l133, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l133, kLoop)), Int32(4))
		StoreVarInst(Address(l133, kLoop), BinopInst("+", LoadVarInst(Address(l133, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec87SE, kStruct)[LoadVarInst(Address(l133, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l134, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l134, kLoop)), Int32(2048))
		StoreVarInst(Address(l134, kLoop), BinopInst("+", LoadVarInst(Address(l134, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec239SE, kStruct)[LoadVarInst(Address(l134, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l135, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l135, kLoop)), Int32(2))
		StoreVarInst(Address(l135, kLoop), BinopInst("+", LoadVarInst(Address(l135, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec92SE, kStruct)[LoadVarInst(Address(l135, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l136, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l136, kLoop)), Int32(2))
		StoreVarInst(Address(l136, kLoop), BinopInst("+", LoadVarInst(Address(l136, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l136, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l137, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l137, kLoop)), Int32(2))
		StoreVarInst(Address(l137, kLoop), BinopInst("+", LoadVarInst(Address(l137, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec242SE, kStruct)[LoadVarInst(Address(l137, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 184 Store = 0 Binop = 137 [ { Int(>) = 8 } { Real(*) = 25 } { Real(+) = 56 } { Real(/) = 40 } { Real(==) = 4 } { Real(>) = 4 } ] Mathop = 63 [ { expf = 20 } { max_f = 9 } { min_f = 1 } { mydsp_faustpower2_f = 25 } { sqrtf = 8 } ] Numbers = 73 Declare = 108 Cast = 14 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("int", iSlow2BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow1BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow3BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow2BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow4BE, kStack, CastInst("float", LoadVarInst(Address(iSlow2BE, kStack))))
	DeclareVarInst("int", iSlow5BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow1BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow1BE, kStack))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow8BE, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("int", iSlow9BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow8BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow10BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow9BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow11BE, kStack, CastInst("float", LoadVarInst(Address(iSlow9BE, kStack))))
	DeclareVarInst("int", iSlow12BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow8BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow8BE, kStack))))
	DeclareVarInst("float", fSlow14BE, kStack, CastInst("float", LoadVarInst(Address(fHslider4, kStruct))))
	DeclareVarInst("int", iSlow15BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow14BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow16BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow15BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow17BE, kStack, CastInst("float", LoadVarInst(Address(iSlow15BE, kStack))))
	DeclareVarInst("int", iSlow18BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow14BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))
	DeclareVarInst("float", fSlow20BE, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("int", iSlow21BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow20BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow22BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow21BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(iSlow21BE, kStack))))
	DeclareVarInst("int", iSlow24BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow20BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow20BE, kStack))))
	DeclareVarInst("float", fSlow26BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider7, kStruct)))))
	DeclareVarInst("float", fSlow28BE, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider8, kStruct))))))
	DeclareVarInst("float", fSlow29BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst13KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow30BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow29BE, kStack))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow30BE, kStack))))))
	DeclareVarInst("float", fSlow32BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow30BE, kStack)))))
	DeclareVarInst("float", fSlow33BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fSlow32BE, kStack))))
	DeclareVarInst("float", fSlow34BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow31BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow32BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow35BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), MinusInst(LoadVarInst(Address(fSlow34BE, kStack)))))
	DeclareVarInst("float", fSlow36BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow34BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow33BE, kStack))))))
	DeclareVarInst("float", fSlow37BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow29BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow38BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst22KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow39BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38BE, kStack))))
	DeclareVarInst("float", fSlow40BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow39BE, kStack))))))
	DeclareVarInst("float", fSlow41BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow39BE, kStack)))))
	DeclareVarInst("float", fSlow42BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fSlow41BE, kStack))))
	DeclareVarInst("float", fSlow43BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow40BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow41BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow44BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow42BE, kStack)), MinusInst(LoadVarInst(Address(fSlow43BE, kStack)))))
	DeclareVarInst("float", fSlow45BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow43BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow42BE, kStack))))))
	DeclareVarInst("float", fSlow46BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst23KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow38BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow47BE, kStack, BinopInst("/", LoadVarInst(Address(fConst28KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow48BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow47BE, kStack))))))
	DeclareVarInst("float", fSlow49BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow48BE, kStack))))))
	DeclareVarInst("float", fSlow50BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow48BE, kStack)))))
	DeclareVarInst("float", fSlow51BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow49BE, kStack)), LoadVarInst(Address(fSlow50BE, kStack))))
	DeclareVarInst("float", fSlow52BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow49BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow50BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow53BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow51BE, kStack)), MinusInst(LoadVarInst(Address(fSlow52BE, kStack)))))
	DeclareVarInst("float", fSlow54BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow47BE, kStack)))))
	DeclareVarInst("float", fSlow55BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow52BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow51BE, kStack))))))
	DeclareVarInst("float", fSlow56BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst29KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow54BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow57BE, kStack, BinopInst("/", LoadVarInst(Address(fConst34KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow58BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow57BE, kStack))))))
	DeclareVarInst("float", fSlow59BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow58BE, kStack))))))
	DeclareVarInst("float", fSlow60BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow58BE, kStack)))))
	DeclareVarInst("float", fSlow61BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fSlow60BE, kStack))))
	DeclareVarInst("float", fSlow62BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow59BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow60BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow63BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow61BE, kStack)), MinusInst(LoadVarInst(Address(fSlow62BE, kStack)))))
	DeclareVarInst("float", fSlow64BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow57BE, kStack)))))
	DeclareVarInst("float", fSlow65BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow62BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow61BE, kStack))))))
	DeclareVarInst("float", fSlow66BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst35KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow64BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow67BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst40KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow68BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow67BE, kStack))))
	DeclareVarInst("float", fSlow69BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow68BE, kStack))))))
	DeclareVarInst("float", fSlow70BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow68BE, kStack)))))
	DeclareVarInst("float", fSlow71BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow69BE, kStack)), LoadVarInst(Address(fSlow70BE, kStack))))
	DeclareVarInst("float", fSlow72BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow69BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow70BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow73BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow71BE, kStack)), MinusInst(LoadVarInst(Address(fSlow72BE, kStack)))))
	DeclareVarInst("float", fSlow74BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow67BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow72BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow71BE, kStack))))))
	DeclareVarInst("float", fSlow75BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst41KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow67BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow76BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst46KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow77BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow76BE, kStack))))
	DeclareVarInst("float", fSlow78BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow77BE, kStack))))))
	DeclareVarInst("float", fSlow79BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow77BE, kStack)))))
	DeclareVarInst("float", fSlow80BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow78BE, kStack)), LoadVarInst(Address(fSlow79BE, kStack))))
	DeclareVarInst("float", fSlow81BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow78BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow79BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow82BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow80BE, kStack)), MinusInst(LoadVarInst(Address(fSlow81BE, kStack)))))
	DeclareVarInst("float", fSlow83BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow76BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow81BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow80BE, kStack))))))
	DeclareVarInst("float", fSlow84BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst47KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow76BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow85BE, kStack, BinopInst("/", LoadVarInst(Address(fConst52KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow86BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow85BE, kStack))))))
	DeclareVarInst("float", fSlow87BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow86BE, kStack))))))
	DeclareVarInst("float", fSlow88BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow86BE, kStack)))))
	DeclareVarInst("float", fSlow89BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fSlow88BE, kStack))))
	DeclareVarInst("float", fSlow90BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow87BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow88BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow91BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow89BE, kStack)), MinusInst(LoadVarInst(Address(fSlow90BE, kStack)))))
	DeclareVarInst("float", fSlow92BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow85BE, kStack)))))
	DeclareVarInst("float", fSlow93BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow90BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow89BE, kStack))))))
	DeclareVarInst("float", fSlow94BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst53KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow92BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow95BE, kStack, BinopInst("/", LoadVarInst(Address(fConst58KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow96BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow95BE, kStack))))))
	DeclareVarInst("float", fSlow97BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow96BE, kStack))))))
	DeclareVarInst("float", fSlow98BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow96BE, kStack)))))
	DeclareVarInst("float", fSlow99BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow97BE, kStack)), LoadVarInst(Address(fSlow98BE, kStack))))
	DeclareVarInst("float", fSlow100BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow97BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow98BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow101BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), MinusInst(LoadVarInst(Address(fSlow100BE, kStack)))))
	DeclareVarInst("float", fSlow102BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow95BE, kStack)))))
	DeclareVarInst("float", fSlow103BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow102BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow100BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow99BE, kStack))))))
	DeclareVarInst("float", fSlow104BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst59KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow102BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow105BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider9, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 1144 Store = 141 Binop = 1017 [ { Int(&) = 353 } { Int(+) = 3 } { Int(-) = 137 } { Int(<) = 1 } { Real(*) = 237 } { Real(+) = 278 } { Real(<) = 8 } ] Mathop = 39 [ { cosf = 8 } { floorf = 3 } { max_f = 2 } { max_i = 3 } { min_f = 10 } { min_i = 3 } { mydsp_faustpower2_f = 2 } { sinf = 8 } ] Numbers = 573 Declare = 134 Cast = 4 Select = 24 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Float(0.0008f)))
		DeclareVarInst("float", fTemp4SI, kStack, LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp6SE, kStack, BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fTemp6SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))))
		DeclareVarInst("float", fTemp7SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), Int32(65535)))])))
		StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow3BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow5BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow2BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp9SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack))) LoadVarInst(Address(fSlow1BE, kStack)))) LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp11SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp8SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp10SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp8SE, kStack)))))) Float(0.0f)))
		DeclareVarInst("float", fTemp12SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), LoadVarInst(Address(fTemp11SE, kStack)))))
		DeclareVarInst("float", fTemp13SE, kStack, BinopInst("*", LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), FunCallInst("cosf", LoadVarInst(Address(fTemp12SE, kStack)))))
		DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow7BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp15SE, kStack, BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), LoadVarInst(Address(fTemp15SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), LoadVarInst(Address(fTemp15SE, kStack)))))))
		DeclareVarInst("float", fTemp16SE, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("int", iTemp17SE, kStack, CastInst("int", LoadVarInst(Address(fTemp16SE, kStack))))
		DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(ftbl1SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp17SE, kStack)), Int32(65536)))]))
		DeclareVarInst("float", fTemp19SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp16SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp16SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl1SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp17SE, kStack)), Int32(1)), Int32(65536)))]), MinusInst(LoadVarInst(Address(fTemp18SE, kStack)))))))
		DeclareVarInst("float", fTemp20SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(fTemp19SE, kStack))))
		StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow10BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp21SE, kStack, LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow12BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp22SE, kStack, LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow9BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp22SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp22SE, kStack))) LoadVarInst(Address(fSlow8BE, kStack)))) LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		DeclareVarInst("float", fTemp23SE, kStack, LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp24SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp21SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp23SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp21SE, kStack)))))) Float(0.0f)))
		DeclareVarInst("float", fTemp25SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp20SE, kStack)), LoadVarInst(Address(fTemp24SE, kStack)))))
		DeclareVarInst("float", fTemp26SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp25SE, kStack))))
		DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp28SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp26SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27SE, kStack)), FunCallInst("cosf", LoadVarInst(Address(fTemp25SE, kStack)))))))
		DeclareVarInst("float", fTemp29SI, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp4SI, kStack)))))
		DeclareVarInst("float", fTemp30SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp29SI, kStack))))
		DeclareVarInst("float", fTemp31SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp28SE, kStack)), LoadVarInst(Address(fTemp30SE, kStack))))
		StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow16BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp32SE, kStack, LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow18BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp33SE, kStack, LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow15BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp33SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow19BE, kStack)), LoadVarInst(Address(fTemp33SE, kStack))) LoadVarInst(Address(fSlow14BE, kStack)))) LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		DeclareVarInst("float", fTemp34SE, kStack, LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp35SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp32SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp34SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp32SE, kStack)))))) Float(0.0f)))
		DeclareVarInst("float", fTemp36SE, kStack, BinopInst("*", Float(1.5707964f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(fTemp35SE, kStack))), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp28SE, kStack)), LoadVarInst(Address(fTemp30SE, kStack))), LoadVarInst(Address(fVec37SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp37SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp36SE, kStack))))
		DeclareVarInst("float", fTemp38SE, kStack, LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp39SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp31SE, kStack)), LoadVarInst(Address(fTemp37SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp38SE, kStack)), FunCallInst("cosf", LoadVarInst(Address(fTemp36SE, kStack)))))), BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp31SE, kStack)))))
		StoreVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow22BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp40SE, kStack, LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow24BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
		DeclareVarInst("float", fTemp41SE, kStack, LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow21BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp41SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), LoadVarInst(Address(fTemp41SE, kStack))) LoadVarInst(Address(fSlow20BE, kStack)))) LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		DeclareVarInst("float", fTemp42SE, kStack, LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp43SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp40SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp42SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp40SE, kStack)))))) Float(0.0f)))
		DeclareVarInst("float", fTemp44SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(fTemp43SE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp39SE, kStack))))))
		DeclareVarInst("float", fTemp45SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp44SE, kStack))))
		DeclareVarInst("float", fTemp46SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp39SE, kStack)), LoadVarInst(Address(fTemp45SE, kStack))), BinopInst("*", LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), FunCallInst("cosf", LoadVarInst(Address(fTemp44SE, kStack)))))))
		DeclareVarInst("float", fTemp47SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp39SE, kStack))))
		DeclareVarInst("float", fTemp48SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp12SE, kStack))))
		DeclareVarInst("float", fTemp49SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp48SE, kStack))))
		StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp46SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp47SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))), MinusInst(LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))))
		StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow26BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp50SE, kStack, BinopInst("*", LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp51SE, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(1.0f), LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("*", LoadVarInst(Address(fTemp50SE, kStack)), LoadVarInst(Address(fTemp51SE, kStack))))
		DeclareVarInst("float", fTemp52SE, kStack, LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst1KI, kStruct))), Int32(4095))]))
		DeclareVarInst("float", fTemp53SE, kStack, BinopInst("*", Float(0.18f), LoadVarInst(Address(fTemp52SE, kStack))))
		DeclareVarInst("float", fTemp54SE, kStack, LoadVarInst(Address(fVec54SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp55SE, kStack, LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp55SE, kStack)))), MinusInst(LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec55SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fVec55SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp55SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec55SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp56SE, kStack, LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst19KI, kStruct))), Int32(32767))]))
		DeclareVarInst("float", fRec23SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp54SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp56SE, kStack))))))
		DeclareVarInst("float", fTemp57SE, kStack, LoadVarInst(Address(fRec23SE, kStack)))
		DeclareVarInst("float", fTemp58SE, kStack, LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp58SE, kStack)))), MinusInst(LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow45BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp58SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow46BE, kStack)), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp59SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst25KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp53SE, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec26SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp59SE, kStack))))
		DeclareVarInst("float", fTemp60SE, kStack, LoadVarInst(Address(fRec26SE, kStack)))
		DeclareVarInst("float", fTemp61SE, kStack, BinopInst("*", Float(-0.18f), LoadVarInst(Address(fTemp52SE, kStack))))
		DeclareVarInst("float", fTemp62SE, kStack, LoadVarInst(Address(fVec75SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp62SE, kStack)))), MinusInst(LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp62SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow56BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp63SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst31KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp61SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec29SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp63SE, kStack))))
		DeclareVarInst("float", fTemp64SE, kStack, LoadVarInst(Address(fRec29SE, kStack)))
		DeclareVarInst("float", fTemp65SE, kStack, LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec86SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec86SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp65SE, kStack)))), MinusInst(LoadVarInst(Address(fVec87SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow63BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp65SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fVec86SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec90SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp66SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec90SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp53SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec32SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp66SE, kStack))))
		DeclareVarInst("float", fTemp67SE, kStack, LoadVarInst(Address(fRec32SE, kStack)))
		DeclareVarInst("float", fTemp68SE, kStack, LoadVarInst(Address(fVec94SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp69SE, kStack, LoadVarInst(Address(fVec95SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp70SE, kStack, LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp71SE, kStack, LoadVarInst(Address(fVec98SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec99SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec99SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp71SE, kStack)))), MinusInst(LoadVarInst(Address(fVec100SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow73BE, kStack)), LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow74BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp71SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fVec99SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec103SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp72SE, kStack, LoadVarInst(Address(fVec103SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43KI, kStruct))), Int32(32767))]))
		DeclareVarInst("float", fRec35SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp70SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp72SE, kStack))))))
		DeclareVarInst("float", fTemp73SE, kStack, LoadVarInst(Address(fRec35SE, kStack)))
		DeclareVarInst("float", fTemp74SE, kStack, LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec108SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec108SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp74SE, kStack)))), MinusInst(LoadVarInst(Address(fVec109SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec106SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow82BE, kStack)), LoadVarInst(Address(fVec106SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow83BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp74SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), LoadVarInst(Address(fVec108SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec106SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp75SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst49KI, kStruct))), Int32(32767))]), LoadVarInst(Address(fTemp53SE, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec114SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec38SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp75SE, kStack))))
		DeclareVarInst("float", fTemp76SE, kStack, LoadVarInst(Address(fRec38SE, kStack)))
		DeclareVarInst("float", fTemp77SE, kStack, LoadVarInst(Address(fVec116SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp78SE, kStack, LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp78SE, kStack)))), MinusInst(LoadVarInst(Address(fVec120SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow93BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp78SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow94BE, kStack)), LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec123SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp79SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec123SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst55KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp61SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec125SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec41SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp79SE, kStack))))
		DeclareVarInst("float", fTemp80SE, kStack, LoadVarInst(Address(fRec41SE, kStack)))
		DeclareVarInst("float", fTemp81SE, kStack, LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp82SE, kStack, LoadVarInst(Address(fVec129SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec130SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec130SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp82SE, kStack)))), MinusInst(LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
		StoreVarInst(Address(fVec128SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow101BE, kStack)), LoadVarInst(Address(fVec128SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow103BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp82SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow104BE, kStack)), LoadVarInst(Address(fVec130SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec128SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
		DeclareVarInst("float", fTemp83SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53SE, kStack)), LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst61KI, kStruct))), Int32(16383))])), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fRec44SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp83SE, kStack))))
		DeclareVarInst("float", fTemp84SE, kStack, LoadVarInst(Address(fRec44SE, kStack)))
		StoreVarInst(Address(fVec98SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))))
		StoreVarInst(Address(fVec100SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec98SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp85SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), Select2Inst(Int32(0) LoadVarInst(Address(fTemp10SE, kStack)) LoadVarInst(Address(fTemp11SE, kStack))))))
		DeclareVarInst("float", fTemp86SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp85SE, kStack))))
		DeclareVarInst("float", fTemp87SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp86SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec139SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp48SE, kStack))))))
		DeclareVarInst("float", fTemp88SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp87SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp89SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp88SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp90SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp89SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp91SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp90SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec143SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec144SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp91SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec144SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec144SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp92SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp85SE, kStack))))
		StoreVarInst(Address(fVec143SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp91SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec143SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp90SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec149SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec141SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp89SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec149SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec151SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp88SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec151SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec153SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec139SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp87SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec153SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec139SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp93SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp20SE, kStack)), Select2Inst(Int32(0) LoadVarInst(Address(fTemp23SE, kStack)) LoadVarInst(Address(fTemp24SE, kStack))))))
		DeclareVarInst("float", fTemp94SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp93SE, kStack))))
		DeclareVarInst("float", fTemp95SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp94SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec156SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp26SE, kStack))))))
		DeclareVarInst("float", fTemp96SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp95SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp97SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp96SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec158SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp98SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp97SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec159SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp99SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp98SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec160SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec161SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp99SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec161SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec161SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp100SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp93SE, kStack))))
		StoreVarInst(Address(fVec160SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp99SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec164SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec160SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec159SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp98SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec164SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec166SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec159SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec158SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp97SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec166SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec168SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec158SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp96SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec168SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec170SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec156SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp95SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec170SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec156SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp101SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp100SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp27SE, kStack))))))
		DeclareVarInst("float", fTemp102SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp19SE, kStack))))
		DeclareVarInst("float", fTemp103SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp101SE, kStack)), LoadVarInst(Address(fTemp102SE, kStack))))
		StoreVarInst(Address(fVec173SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp103SE, kStack)))
		StoreVarInst(Address(fVec37SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp31SE, kStack)))
		DeclareVarInst("float", fTemp104SE, kStack, BinopInst("*", Float(1.5707964f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), Select2Inst(Int32(0) LoadVarInst(Address(fTemp34SE, kStack)) LoadVarInst(Address(fTemp35SE, kStack)))), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp101SE, kStack)), LoadVarInst(Address(fTemp102SE, kStack))), LoadVarInst(Address(fVec173SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp105SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp104SE, kStack))))
		DeclareVarInst("float", fTemp106SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp103SE, kStack)), LoadVarInst(Address(fTemp105SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec176SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp37SE, kStack))))))
		DeclareVarInst("float", fTemp107SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp106SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp108SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp107SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec178SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp109SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp108SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec179SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp110SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp109SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec180SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec181SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp110SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec181SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec182SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec181SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp111SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp104SE, kStack))))
		StoreVarInst(Address(fVec180SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp110SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec182SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec184SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec180SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec179SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp109SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec184SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec186SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec179SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec178SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp108SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec186SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec188SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec178SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp107SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec188SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec190SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec176SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp106SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec190SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec176SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp112SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp103SE, kStack)), LoadVarInst(Address(fTemp111SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp38SE, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp103SE, kStack)))))
		DeclareVarInst("float", fTemp113SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp112SE, kStack)))), Select2Inst(Int32(0) LoadVarInst(Address(fTemp42SE, kStack)) LoadVarInst(Address(fTemp43SE, kStack))))))
		DeclareVarInst("float", fTemp114SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp113SE, kStack))))
		DeclareVarInst("float", fTemp115SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp112SE, kStack)), LoadVarInst(Address(fTemp114SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec193SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp45SE, kStack))))))
		DeclareVarInst("float", fTemp116SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp115SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec194SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp117SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp116SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec195SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp118SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp117SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec196SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		DeclareVarInst("float", fTemp119SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp118SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec197SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec198SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp119SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec198SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec199SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec198SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp120SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp113SE, kStack))))
		StoreVarInst(Address(fVec197SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp119SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec199SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec201SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec197SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec196SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp118SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec201SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec203SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec196SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec195SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp117SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec203SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec205SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec195SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec194SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp116SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec205SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec207SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec194SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec193SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp115SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec207SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec193SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp13SE, kStack)), LoadVarInst(Address(fTemp46SE, kStack))), LoadVarInst(Address(fTemp47SE, kStack))), LoadVarInst(Address(fTemp49SE, kStack))))
		StoreVarInst(Address(fVec211SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp70SE, kStack))), LoadVarInst(Address(fTemp72SE, kStack))), LoadVarInst(Address(fTemp61SE, kStack))))
		StoreVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec211SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst62KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec94SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
		StoreVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec215SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp54SE, kStack))), LoadVarInst(Address(fTemp56SE, kStack))), LoadVarInst(Address(fTemp61SE, kStack))))
		StoreVarInst(Address(fVec54SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec215SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst63KI, kStruct))), Int32(4095))]))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec54SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
		StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec219SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp59SE, kStack)))
		StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec219SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst64KI, kStruct))), Int32(4095))]))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))))
		StoreVarInst(Address(fVec109SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec223SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp75SE, kStack)))
		StoreVarInst(Address(fVec114SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec223SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst65KI, kStruct))), Int32(4095))]))
		StoreVarInst(Address(fVec95SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec114SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec75SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))))
		StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec75SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec227SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp63SE, kStack)))
		StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec227SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst66KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
		StoreVarInst(Address(fVec120SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec231SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp79SE, kStack)))
		StoreVarInst(Address(fVec125SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec231SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst67KI, kStruct))), Int32(4095))]))
		StoreVarInst(Address(fVec116SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec125SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec129SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
		StoreVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec129SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec235SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp83SE, kStack)))
		StoreVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec235SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst68KI, kStruct))), Int32(4095))]))
		StoreVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))))
		StoreVarInst(Address(fVec87SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec239SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp66SE, kStack)))
		StoreVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec239SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst69KI, kStruct))), Int32(2047))]))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec242SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow105BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec242SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp121SE, kStack, FunCallInst("max_f", Float(0.75f), FunCallInst("min_f", Float(4.0f), LoadVarInst(Address(fVec242SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		DeclareVarInst("float", fTemp122SE, kStack, LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp123SE, kStack, LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp124SE, kStack, BinopInst("*", Float(0.6f), BinopInst("*", LoadVarInst(Address(fTemp50SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp51SE, kStack)))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp121SE, kStack)), BinopInst("+", BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fTemp122SE, kStack)), LoadVarInst(Address(fTemp123SE, kStack)))), LoadVarInst(Address(fTemp124SE, kStack))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp121SE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp124SE, kStack)), BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fTemp122SE, kStack)), MinusInst(LoadVarInst(Address(fTemp123SE, kStack)))))))))
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
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst("float", ftbl1SImydspSIG0[65537], kStaticStruct)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("int", iConst1KI, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	DeclareVarInst("float", fConst3KI, kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	// Recursion delay fVec6SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec6SI[2], kStruct)
	DeclareVarInst("float", fConst5KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	// Recursion delay fVec9SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec9SE[2], kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	DeclareVarInst("float", fConst6KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	// Recursion delay fVec14SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec14SE[2], kStruct)
	DeclareVarInst("float", fConst7KI, kStruct)
	// Recursion delay fVec17SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec17SE[2], kStruct)
	DeclareVarInst("float", fConst8KI, kStruct)
	// Recursion delay fVec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec16SE[2], kStruct)
	DeclareVarInst("float", fConst9KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	// Recursion delay fVec21SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec21SE[2], kStruct)
	// Recursion delay fVec20SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec20SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	// Recursion delay fVec24SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec24SE[2], kStruct)
	// Recursion delay fVec27SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec27SE[2], kStruct)
	// Recursion delay fVec26SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec26SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	// Recursion delay fVec31SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec31SE[2], kStruct)
	// Recursion delay fVec34SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec34SE[2], kStruct)
	// Recursion delay fVec33SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec33SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	// Recursion delay fVec39SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec39SE[2], kStruct)
	// Recursion delay fVec42SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec42SE[2], kStruct)
	// Recursion delay fVec41SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec41SE[2], kStruct)
	// Recursion delay fVec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	// Recursion delay fVec48SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec48SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider7, kStruct)
	// Recursion delay fVec50SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec50SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec52SE[4096], kStruct)
	DeclareVarInst("float", fConst10KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider8, kStruct)
	DeclareVarInst("float", fConst11KI, kStruct)
	DeclareVarInst("float", fConst12KI, kStruct)
	DeclareVarInst("float", fConst13KI, kStruct)
	DeclareVarInst("float", fConst14KI, kStruct)
	DeclareVarInst("float", fConst15KI, kStruct)
	DeclareVarInst("float", fConst16KI, kStruct)
	// Recursion delay fVec57SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec57SE[2], kStruct)
	DeclareVarInst("float", fConst17KI, kStruct)
	// Recursion delay fVec55SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec55SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec61SE[32768], kStruct)
	DeclareVarInst("float", fConst18KI, kStruct)
	DeclareVarInst("int", iConst19KI, kStruct)
	// Recursion delay fRec23SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst20KI, kStruct)
	DeclareVarInst("float", fConst21KI, kStruct)
	DeclareVarInst("float", fConst22KI, kStruct)
	// Recursion delay fVec66SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec66SE[2], kStruct)
	DeclareVarInst("float", fConst23KI, kStruct)
	// Recursion delay fVec64SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec64SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec70SE[16384], kStruct)
	DeclareVarInst("float", fConst24KI, kStruct)
	DeclareVarInst("int", iConst25KI, kStruct)
	// Recursion delay fRec26SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst26KI, kStruct)
	DeclareVarInst("float", fConst27KI, kStruct)
	DeclareVarInst("float", fConst28KI, kStruct)
	DeclareVarInst("float", fConst29KI, kStruct)
	// Recursion delay fVec76SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec76SE[2], kStruct)
	// Recursion delay fVec74SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec74SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec80SE[16384], kStruct)
	DeclareVarInst("float", fConst30KI, kStruct)
	DeclareVarInst("int", iConst31KI, kStruct)
	// Recursion delay fRec29SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst32KI, kStruct)
	DeclareVarInst("float", fConst33KI, kStruct)
	DeclareVarInst("float", fConst34KI, kStruct)
	DeclareVarInst("float", fConst35KI, kStruct)
	// Recursion delay fVec86SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec86SE[2], kStruct)
	// Recursion delay fVec84SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec84SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec90SE[16384], kStruct)
	DeclareVarInst("float", fConst36KI, kStruct)
	DeclareVarInst("int", iConst37KI, kStruct)
	// Recursion delay fRec32SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst38KI, kStruct)
	DeclareVarInst("float", fConst39KI, kStruct)
	DeclareVarInst("float", fConst40KI, kStruct)
	// Recursion delay fVec99SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec99SE[2], kStruct)
	DeclareVarInst("float", fConst41KI, kStruct)
	// Recursion delay fVec97SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec97SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec103SE[32768], kStruct)
	DeclareVarInst("float", fConst42KI, kStruct)
	DeclareVarInst("int", iConst43KI, kStruct)
	// Recursion delay fRec35SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst44KI, kStruct)
	DeclareVarInst("float", fConst45KI, kStruct)
	DeclareVarInst("float", fConst46KI, kStruct)
	// Recursion delay fVec108SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec108SE[2], kStruct)
	DeclareVarInst("float", fConst47KI, kStruct)
	// Recursion delay fVec106SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec106SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec112SE[32768], kStruct)
	DeclareVarInst("float", fConst48KI, kStruct)
	DeclareVarInst("int", iConst49KI, kStruct)
	// Recursion delay fRec38SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst50KI, kStruct)
	DeclareVarInst("float", fConst51KI, kStruct)
	DeclareVarInst("float", fConst52KI, kStruct)
	DeclareVarInst("float", fConst53KI, kStruct)
	// Recursion delay fVec119SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec119SE[2], kStruct)
	// Recursion delay fVec117SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec117SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec123SE[16384], kStruct)
	DeclareVarInst("float", fConst54KI, kStruct)
	DeclareVarInst("int", iConst55KI, kStruct)
	// Recursion delay fRec41SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("float", fConst56KI, kStruct)
	DeclareVarInst("float", fConst57KI, kStruct)
	DeclareVarInst("float", fConst58KI, kStruct)
	DeclareVarInst("float", fConst59KI, kStruct)
	// Recursion delay fVec130SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec130SE[2], kStruct)
	// Recursion delay fVec128SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec128SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec134SE[16384], kStruct)
	DeclareVarInst("float", fConst60KI, kStruct)
	DeclareVarInst("int", iConst61KI, kStruct)
	// Recursion delay fRec44SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Recursion delay fVec98SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec98SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec100SE[4], kStruct)
	// Recursion delay fVec144SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec144SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec145SE[2], kStruct)
	// Recursion delay fVec143SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec143SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec147SE[2], kStruct)
	// Recursion delay fVec142SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec142SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec149SE[2], kStruct)
	// Recursion delay fVec141SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec141SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec151SE[2], kStruct)
	// Recursion delay fVec140SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec140SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec153SE[2], kStruct)
	// Recursion delay fVec139SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec139SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec5SE[2], kStruct)
	// Recursion delay fVec161SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec161SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec162SE[2], kStruct)
	// Recursion delay fVec160SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec160SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec164SE[2], kStruct)
	// Recursion delay fVec159SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec159SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec166SE[2], kStruct)
	// Recursion delay fVec158SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec158SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec168SE[2], kStruct)
	// Recursion delay fVec157SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec157SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec170SE[2], kStruct)
	// Recursion delay fVec156SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec156SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec30SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec173SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec37SE[2], kStruct)
	// Recursion delay fVec181SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec181SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec182SE[2], kStruct)
	// Recursion delay fVec180SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec180SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec184SE[2], kStruct)
	// Recursion delay fVec179SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec179SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec186SE[2], kStruct)
	// Recursion delay fVec178SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec178SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec188SE[2], kStruct)
	// Recursion delay fVec177SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec177SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec190SE[2], kStruct)
	// Recursion delay fVec176SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec176SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec38SE[2], kStruct)
	// Recursion delay fVec198SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec198SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec199SE[2], kStruct)
	// Recursion delay fVec197SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec197SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec201SE[2], kStruct)
	// Recursion delay fVec196SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec196SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec203SE[2], kStruct)
	// Recursion delay fVec195SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec195SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec205SE[2], kStruct)
	// Recursion delay fVec194SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec194SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec207SE[2], kStruct)
	// Recursion delay fVec193SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec193SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec45SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec46SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec211SE[2048], kStruct)
	DeclareVarInst("int", iConst62KI, kStruct)
	// Recursion delay fVec96SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec96SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec94SE[2], kStruct)
	// Recursion delay fVec56SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec56SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec58SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec215SE[4096], kStruct)
	DeclareVarInst("int", iConst63KI, kStruct)
	// Recursion delay fVec54SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec54SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	// Recursion delay fVec65SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec65SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec67SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec219SE[4096], kStruct)
	DeclareVarInst("int", iConst64KI, kStruct)
	// Recursion delay fVec72SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec72SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Recursion delay fVec107SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec107SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec109SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec223SE[4096], kStruct)
	DeclareVarInst("int", iConst65KI, kStruct)
	// Recursion delay fVec114SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec114SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec95SE[2], kStruct)
	// Recursion delay fVec75SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec75SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec77SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec227SE[2048], kStruct)
	DeclareVarInst("int", iConst66KI, kStruct)
	// Recursion delay fVec82SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec82SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
	// Recursion delay fVec118SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec118SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec120SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec231SE[4096], kStruct)
	DeclareVarInst("int", iConst67KI, kStruct)
	// Recursion delay fVec125SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec125SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec116SE[2], kStruct)
	// Recursion delay fVec129SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec129SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec131SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec235SE[4096], kStruct)
	DeclareVarInst("int", iConst68KI, kStruct)
	// Recursion delay fVec136SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec136SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec127SE[2], kStruct)
	// Recursion delay fVec85SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec85SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec87SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec239SE[2048], kStruct)
	DeclareVarInst("int", iConst69KI, kStruct)
	// Recursion delay fVec92SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec92SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider9, kStruct)
	// Recursion delay fVec242SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec242SE[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(iConst1KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("*", Float(0.02f), LoadVarInst(Address(fConst0KI, kStruct)))))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(6283.1855f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst2KI, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst2KI, kStruct)))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst7KI, kStruct), BinopInst("*", Float(3.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst8KI, kStruct), BinopInst("/", Float(0.33333334f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst9KI, kStruct), BinopInst("/", Float(0.5f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst10KI, kStruct), FunCallInst("cosf", BinopInst("/", Float(37699.113f), LoadVarInst(Address(fConst0KI, kStruct)))))
	StoreVarInst(Address(fConst11KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.256891f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst12KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst11KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst13KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst12KI, kStruct))))
	StoreVarInst(Address(fConst14KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("tanf", BinopInst("/", Float(628.31854f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst15KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst14KI, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst16KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst14KI, kStruct)))))
	StoreVarInst(Address(fConst17KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst12KI, kStruct))))
	StoreVarInst(Address(fConst18KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.027333f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst19KI, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst11KI, kStruct)), MinusInst(LoadVarInst(Address(fConst18KI, kStruct))))))))
	StoreVarInst(Address(fConst20KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.192303f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst21KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst20KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst22KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst21KI, kStruct))))
	StoreVarInst(Address(fConst23KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst21KI, kStruct))))
	StoreVarInst(Address(fConst24KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.029291f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst25KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst20KI, kStruct)), MinusInst(LoadVarInst(Address(fConst24KI, kStruct))))))))
	StoreVarInst(Address(fConst26KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.125f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst27KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst26KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst28KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst27KI, kStruct))))
	StoreVarInst(Address(fConst29KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst27KI, kStruct))))
	StoreVarInst(Address(fConst30KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.013458f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst31KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst26KI, kStruct)), MinusInst(LoadVarInst(Address(fConst30KI, kStruct))))))))
	StoreVarInst(Address(fConst32KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.153129f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst33KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst32KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst34KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst33KI, kStruct))))
	StoreVarInst(Address(fConst35KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst33KI, kStruct))))
	StoreVarInst(Address(fConst36KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.020346f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst37KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst32KI, kStruct)), MinusInst(LoadVarInst(Address(fConst36KI, kStruct))))))))
	StoreVarInst(Address(fConst38KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.219991f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst39KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst38KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst40KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst39KI, kStruct))))
	StoreVarInst(Address(fConst41KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst39KI, kStruct))))
	StoreVarInst(Address(fConst42KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.019123f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst43KI, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst38KI, kStruct)), MinusInst(LoadVarInst(Address(fConst42KI, kStruct))))))))
	StoreVarInst(Address(fConst44KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.210389f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst45KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst44KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst46KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst45KI, kStruct))))
	StoreVarInst(Address(fConst47KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst45KI, kStruct))))
	StoreVarInst(Address(fConst48KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.024421f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst49KI, kStruct), CastInst("int", FunCallInst("min_f", Float(16384.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst44KI, kStruct)), MinusInst(LoadVarInst(Address(fConst48KI, kStruct))))))))
	StoreVarInst(Address(fConst50KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.127837f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst51KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst50KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst52KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst51KI, kStruct))))
	StoreVarInst(Address(fConst53KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst51KI, kStruct))))
	StoreVarInst(Address(fConst54KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.031604f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst55KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst50KI, kStruct)), MinusInst(LoadVarInst(Address(fConst54KI, kStruct))))))))
	StoreVarInst(Address(fConst56KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.174713f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(fConst57KI, kStruct), BinopInst("/", LoadVarInst(Address(fConst56KI, kStruct)), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst58KI, kStruct), BinopInst("*", Float(3.4538777f), LoadVarInst(Address(fConst57KI, kStruct))))
	StoreVarInst(Address(fConst59KI, kStruct), BinopInst("*", Float(2.3025851f), LoadVarInst(Address(fConst57KI, kStruct))))
	StoreVarInst(Address(fConst60KI, kStruct), FunCallInst("floorf", BinopInst("+", BinopInst("*", Float(0.022904f), LoadVarInst(Address(fConst0KI, kStruct))), Float(0.5f))))
	StoreVarInst(Address(iConst61KI, kStruct), CastInst("int", FunCallInst("min_f", Float(8192.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst56KI, kStruct)), MinusInst(LoadVarInst(Address(fConst60KI, kStruct))))))))
	StoreVarInst(Address(iConst62KI, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst42KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst63KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst18KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst64KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst24KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst65KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst48KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst66KI, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst30KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst67KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst54KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst68KI, kStruct), CastInst("int", FunCallInst("min_f", Float(2048.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst60KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(iConst69KI, kStruct), CastInst("int", FunCallInst("min_f", Float(1024.0f), FunCallInst("max_f", Float(0.0f), BinopInst("+", LoadVarInst(Address(fConst36KI, kStruct)), Float(-1.0f))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.2e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(3.3e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.25f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider9, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec39SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec50SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(4096))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec57SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec55SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(32768))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec66SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec64SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(16384))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec76SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(16384))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec80SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec86SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec84SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(16384))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec90SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec99SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec97SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(32768))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec103SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec108SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec106SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(32768))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec112SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec119SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec117SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(16384))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec123SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec130SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec128SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(16384))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec134SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec98SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec100SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec144SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec145SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec143SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec147SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec142SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec149SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec141SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec151SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec140SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec153SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec139SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec161SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec162SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(2))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec160SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(2))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec164SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec159SE, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(2))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec166SE, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(2))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec158SE, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(2))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec168SE, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(2))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec157SE, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(2))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec170SE, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec156SE, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(2))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(2))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec173SE, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(2))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec37SE, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(2))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec181SE, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(2))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec182SE, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(2))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec180SE, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(2))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec184SE, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(2))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec179SE, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(2))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec186SE, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(2))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec178SE, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(2))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec188SE, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(2))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec177SE, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(2))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec190SE, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(2))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec176SE, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(2))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec198SE, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(2))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec199SE, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(2))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec197SE, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(2))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec201SE, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(2))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec196SE, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(2))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec203SE, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(2))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec195SE, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(2))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec205SE, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(2))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec194SE, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(2))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec207SE, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(2))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec193SE, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(2))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec45SE, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(2))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l99, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l99, kLoop)), Int32(2048))
		StoreVarInst(Address(l99, kLoop), BinopInst("+", LoadVarInst(Address(l99, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec211SE, kStruct)[LoadVarInst(Address(l99, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l100, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l100, kLoop)), Int32(2))
		StoreVarInst(Address(l100, kLoop), BinopInst("+", LoadVarInst(Address(l100, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec96SE, kStruct)[LoadVarInst(Address(l100, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l101, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l101, kLoop)), Int32(2))
		StoreVarInst(Address(l101, kLoop), BinopInst("+", LoadVarInst(Address(l101, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec94SE, kStruct)[LoadVarInst(Address(l101, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l102, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l102, kLoop)), Int32(2))
		StoreVarInst(Address(l102, kLoop), BinopInst("+", LoadVarInst(Address(l102, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SE, kStruct)[LoadVarInst(Address(l102, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l103, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l103, kLoop)), Int32(4))
		StoreVarInst(Address(l103, kLoop), BinopInst("+", LoadVarInst(Address(l103, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec58SE, kStruct)[LoadVarInst(Address(l103, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l104, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l104, kLoop)), Int32(4096))
		StoreVarInst(Address(l104, kLoop), BinopInst("+", LoadVarInst(Address(l104, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec215SE, kStruct)[LoadVarInst(Address(l104, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l105, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l105, kLoop)), Int32(2))
		StoreVarInst(Address(l105, kLoop), BinopInst("+", LoadVarInst(Address(l105, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec54SE, kStruct)[LoadVarInst(Address(l105, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l106, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l106, kLoop)), Int32(2))
		StoreVarInst(Address(l106, kLoop), BinopInst("+", LoadVarInst(Address(l106, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l106, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l107, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l107, kLoop)), Int32(2))
		StoreVarInst(Address(l107, kLoop), BinopInst("+", LoadVarInst(Address(l107, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec65SE, kStruct)[LoadVarInst(Address(l107, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l108, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l108, kLoop)), Int32(4))
		StoreVarInst(Address(l108, kLoop), BinopInst("+", LoadVarInst(Address(l108, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l108, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l109, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l109, kLoop)), Int32(4096))
		StoreVarInst(Address(l109, kLoop), BinopInst("+", LoadVarInst(Address(l109, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec219SE, kStruct)[LoadVarInst(Address(l109, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l110, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l110, kLoop)), Int32(2))
		StoreVarInst(Address(l110, kLoop), BinopInst("+", LoadVarInst(Address(l110, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l110, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l111, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l111, kLoop)), Int32(2))
		StoreVarInst(Address(l111, kLoop), BinopInst("+", LoadVarInst(Address(l111, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l111, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l112, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l112, kLoop)), Int32(2))
		StoreVarInst(Address(l112, kLoop), BinopInst("+", LoadVarInst(Address(l112, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec107SE, kStruct)[LoadVarInst(Address(l112, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l113, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l113, kLoop)), Int32(4))
		StoreVarInst(Address(l113, kLoop), BinopInst("+", LoadVarInst(Address(l113, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec109SE, kStruct)[LoadVarInst(Address(l113, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l114, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l114, kLoop)), Int32(4096))
		StoreVarInst(Address(l114, kLoop), BinopInst("+", LoadVarInst(Address(l114, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec223SE, kStruct)[LoadVarInst(Address(l114, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l115, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l115, kLoop)), Int32(2))
		StoreVarInst(Address(l115, kLoop), BinopInst("+", LoadVarInst(Address(l115, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec114SE, kStruct)[LoadVarInst(Address(l115, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l116, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l116, kLoop)), Int32(2))
		StoreVarInst(Address(l116, kLoop), BinopInst("+", LoadVarInst(Address(l116, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec95SE, kStruct)[LoadVarInst(Address(l116, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l117, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l117, kLoop)), Int32(2))
		StoreVarInst(Address(l117, kLoop), BinopInst("+", LoadVarInst(Address(l117, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec75SE, kStruct)[LoadVarInst(Address(l117, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l118, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l118, kLoop)), Int32(4))
		StoreVarInst(Address(l118, kLoop), BinopInst("+", LoadVarInst(Address(l118, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l118, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l119, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l119, kLoop)), Int32(2048))
		StoreVarInst(Address(l119, kLoop), BinopInst("+", LoadVarInst(Address(l119, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec227SE, kStruct)[LoadVarInst(Address(l119, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l120, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l120, kLoop)), Int32(2))
		StoreVarInst(Address(l120, kLoop), BinopInst("+", LoadVarInst(Address(l120, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l120, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l121, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l121, kLoop)), Int32(2))
		StoreVarInst(Address(l121, kLoop), BinopInst("+", LoadVarInst(Address(l121, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l121, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l122, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l122, kLoop)), Int32(2))
		StoreVarInst(Address(l122, kLoop), BinopInst("+", LoadVarInst(Address(l122, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec118SE, kStruct)[LoadVarInst(Address(l122, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l123, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l123, kLoop)), Int32(4))
		StoreVarInst(Address(l123, kLoop), BinopInst("+", LoadVarInst(Address(l123, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec120SE, kStruct)[LoadVarInst(Address(l123, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l124, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l124, kLoop)), Int32(4096))
		StoreVarInst(Address(l124, kLoop), BinopInst("+", LoadVarInst(Address(l124, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec231SE, kStruct)[LoadVarInst(Address(l124, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l125, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l125, kLoop)), Int32(2))
		StoreVarInst(Address(l125, kLoop), BinopInst("+", LoadVarInst(Address(l125, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec125SE, kStruct)[LoadVarInst(Address(l125, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l126, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l126, kLoop)), Int32(2))
		StoreVarInst(Address(l126, kLoop), BinopInst("+", LoadVarInst(Address(l126, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec116SE, kStruct)[LoadVarInst(Address(l126, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l127, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l127, kLoop)), Int32(2))
		StoreVarInst(Address(l127, kLoop), BinopInst("+", LoadVarInst(Address(l127, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec129SE, kStruct)[LoadVarInst(Address(l127, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l128, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l128, kLoop)), Int32(4))
		StoreVarInst(Address(l128, kLoop), BinopInst("+", LoadVarInst(Address(l128, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec131SE, kStruct)[LoadVarInst(Address(l128, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l129, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l129, kLoop)), Int32(4096))
		StoreVarInst(Address(l129, kLoop), BinopInst("+", LoadVarInst(Address(l129, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec235SE, kStruct)[LoadVarInst(Address(l129, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l130, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l130, kLoop)), Int32(2))
		StoreVarInst(Address(l130, kLoop), BinopInst("+", LoadVarInst(Address(l130, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec136SE, kStruct)[LoadVarInst(Address(l130, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l131, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l131, kLoop)), Int32(2))
		StoreVarInst(Address(l131, kLoop), BinopInst("+", LoadVarInst(Address(l131, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec127SE, kStruct)[LoadVarInst(Address(l131, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l132, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l132, kLoop)), Int32(2))
		StoreVarInst(Address(l132, kLoop), BinopInst("+", LoadVarInst(Address(l132, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec85SE, kStruct)[LoadVarInst(Address(l132, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l133, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l133, kLoop)), Int32(4))
		StoreVarInst(Address(l133, kLoop), BinopInst("+", LoadVarInst(Address(l133, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec87SE, kStruct)[LoadVarInst(Address(l133, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l134, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l134, kLoop)), Int32(2048))
		StoreVarInst(Address(l134, kLoop), BinopInst("+", LoadVarInst(Address(l134, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec239SE, kStruct)[LoadVarInst(Address(l134, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l135, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l135, kLoop)), Int32(2))
		StoreVarInst(Address(l135, kLoop), BinopInst("+", LoadVarInst(Address(l135, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec92SE, kStruct)[LoadVarInst(Address(l135, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l136, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l136, kLoop)), Int32(2))
		StoreVarInst(Address(l136, kLoop), BinopInst("+", LoadVarInst(Address(l136, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l136, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l137, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l137, kLoop)), Int32(2))
		StoreVarInst(Address(l137, kLoop), BinopInst("+", LoadVarInst(Address(l137, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec242SE, kStruct)[LoadVarInst(Address(l137, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl1SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", IOTA1, kStruct)
	// Recursion delay iVec12SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec12SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
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
			StoreVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))))
			StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("int", iSlow2BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow1BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow3BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow2BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow4BE, kStack, CastInst("float", LoadVarInst(Address(iSlow2BE, kStack))))
	DeclareVarInst("int", iSlow5BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow1BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow1BE, kStack))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow8BE, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("int", iSlow9BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow8BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow10BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow9BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow11BE, kStack, CastInst("float", LoadVarInst(Address(iSlow9BE, kStack))))
	DeclareVarInst("int", iSlow12BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow8BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow8BE, kStack))))
	DeclareVarInst("float", fSlow14BE, kStack, CastInst("float", LoadVarInst(Address(fHslider4, kStruct))))
	DeclareVarInst("int", iSlow15BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow14BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow16BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow15BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow17BE, kStack, CastInst("float", LoadVarInst(Address(iSlow15BE, kStack))))
	DeclareVarInst("int", iSlow18BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow14BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow19BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow14BE, kStack))))
	DeclareVarInst("float", fSlow20BE, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("int", iSlow21BE, kStack, BinopInst(">", LoadVarInst(Address(fSlow20BE, kStack)), Float(0.0f)))
	DeclareVarInst("int", iSlow22BE, kStack, BinopInst(">", LoadVarInst(Address(iSlow21BE, kStack)), Int32(0)))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(iSlow21BE, kStack))))
	DeclareVarInst("int", iSlow24BE, kStack, BinopInst(">", BinopInst("==", LoadVarInst(Address(fSlow20BE, kStack)), Float(0.0f)), Int32(0)))
	DeclareVarInst("float", fSlow25BE, kStack, BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fSlow20BE, kStack))))
	DeclareVarInst("float", fSlow26BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider7, kStruct)))))
	DeclareVarInst("float", fSlow28BE, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider8, kStruct))))))
	DeclareVarInst("float", fSlow29BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst13KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow30BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow29BE, kStack))))
	DeclareVarInst("float", fSlow31BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow30BE, kStack))))))
	DeclareVarInst("float", fSlow32BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow30BE, kStack)))))
	DeclareVarInst("float", fSlow33BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fSlow32BE, kStack))))
	DeclareVarInst("float", fSlow34BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow31BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow32BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow35BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow33BE, kStack)), MinusInst(LoadVarInst(Address(fSlow34BE, kStack)))))
	DeclareVarInst("float", fSlow36BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow34BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow33BE, kStack))))))
	DeclareVarInst("float", fSlow37BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow29BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow38BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst22KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow39BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow38BE, kStack))))
	DeclareVarInst("float", fSlow40BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow39BE, kStack))))))
	DeclareVarInst("float", fSlow41BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow39BE, kStack)))))
	DeclareVarInst("float", fSlow42BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fSlow41BE, kStack))))
	DeclareVarInst("float", fSlow43BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow40BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow41BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow44BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow42BE, kStack)), MinusInst(LoadVarInst(Address(fSlow43BE, kStack)))))
	DeclareVarInst("float", fSlow45BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow43BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow42BE, kStack))))))
	DeclareVarInst("float", fSlow46BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst23KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow38BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow47BE, kStack, BinopInst("/", LoadVarInst(Address(fConst28KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow48BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow47BE, kStack))))))
	DeclareVarInst("float", fSlow49BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow48BE, kStack))))))
	DeclareVarInst("float", fSlow50BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow48BE, kStack)))))
	DeclareVarInst("float", fSlow51BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow49BE, kStack)), LoadVarInst(Address(fSlow50BE, kStack))))
	DeclareVarInst("float", fSlow52BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow49BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow50BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow53BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow51BE, kStack)), MinusInst(LoadVarInst(Address(fSlow52BE, kStack)))))
	DeclareVarInst("float", fSlow54BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow47BE, kStack)))))
	DeclareVarInst("float", fSlow55BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow52BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow51BE, kStack))))))
	DeclareVarInst("float", fSlow56BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst29KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow54BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow57BE, kStack, BinopInst("/", LoadVarInst(Address(fConst34KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow58BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow57BE, kStack))))))
	DeclareVarInst("float", fSlow59BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow58BE, kStack))))))
	DeclareVarInst("float", fSlow60BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow58BE, kStack)))))
	DeclareVarInst("float", fSlow61BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fSlow60BE, kStack))))
	DeclareVarInst("float", fSlow62BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow59BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow60BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow63BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow61BE, kStack)), MinusInst(LoadVarInst(Address(fSlow62BE, kStack)))))
	DeclareVarInst("float", fSlow64BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow57BE, kStack)))))
	DeclareVarInst("float", fSlow65BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow62BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow61BE, kStack))))))
	DeclareVarInst("float", fSlow66BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst35KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow64BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow67BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst40KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow68BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow67BE, kStack))))
	DeclareVarInst("float", fSlow69BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow68BE, kStack))))))
	DeclareVarInst("float", fSlow70BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow68BE, kStack)))))
	DeclareVarInst("float", fSlow71BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow69BE, kStack)), LoadVarInst(Address(fSlow70BE, kStack))))
	DeclareVarInst("float", fSlow72BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow69BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow70BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow73BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow71BE, kStack)), MinusInst(LoadVarInst(Address(fSlow72BE, kStack)))))
	DeclareVarInst("float", fSlow74BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow67BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow72BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow71BE, kStack))))))
	DeclareVarInst("float", fSlow75BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst41KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow67BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow76BE, kStack, FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst46KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))))
	DeclareVarInst("float", fSlow77BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow76BE, kStack))))
	DeclareVarInst("float", fSlow78BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow77BE, kStack))))))
	DeclareVarInst("float", fSlow79BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow77BE, kStack)))))
	DeclareVarInst("float", fSlow80BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow78BE, kStack)), LoadVarInst(Address(fSlow79BE, kStack))))
	DeclareVarInst("float", fSlow81BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow78BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow79BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow82BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow80BE, kStack)), MinusInst(LoadVarInst(Address(fSlow81BE, kStack)))))
	DeclareVarInst("float", fSlow83BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow76BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow81BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow80BE, kStack))))))
	DeclareVarInst("float", fSlow84BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst47KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow76BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow85BE, kStack, BinopInst("/", LoadVarInst(Address(fConst52KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow86BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow85BE, kStack))))))
	DeclareVarInst("float", fSlow87BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow86BE, kStack))))))
	DeclareVarInst("float", fSlow88BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow86BE, kStack)))))
	DeclareVarInst("float", fSlow89BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow87BE, kStack)), LoadVarInst(Address(fSlow88BE, kStack))))
	DeclareVarInst("float", fSlow90BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow87BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow88BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow91BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow89BE, kStack)), MinusInst(LoadVarInst(Address(fSlow90BE, kStack)))))
	DeclareVarInst("float", fSlow92BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow85BE, kStack)))))
	DeclareVarInst("float", fSlow93BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow92BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow90BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow89BE, kStack))))))
	DeclareVarInst("float", fSlow94BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst53KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow92BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow95BE, kStack, BinopInst("/", LoadVarInst(Address(fConst58KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))
	DeclareVarInst("float", fSlow96BE, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow95BE, kStack))))))
	DeclareVarInst("float", fSlow97BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fSlow96BE, kStack))))))
	DeclareVarInst("float", fSlow98BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow96BE, kStack)))))
	DeclareVarInst("float", fSlow99BE, kStack, BinopInst("/", LoadVarInst(Address(fSlow97BE, kStack)), LoadVarInst(Address(fSlow98BE, kStack))))
	DeclareVarInst("float", fSlow100BE, kStack, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("+", BinopInst("/", FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow97BE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow98BE, kStack)))), Float(-1.0f)))))
	DeclareVarInst("float", fSlow101BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow99BE, kStack)), MinusInst(LoadVarInst(Address(fSlow100BE, kStack)))))
	DeclareVarInst("float", fSlow102BE, kStack, FunCallInst("expf", MinusInst(LoadVarInst(Address(fSlow95BE, kStack)))))
	DeclareVarInst("float", fSlow103BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow102BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow100BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow99BE, kStack))))))
	DeclareVarInst("float", fSlow104BE, kStack, BinopInst("+", BinopInst("/", FunCallInst("expf", MinusInst(BinopInst("/", LoadVarInst(Address(fConst59KI, kStruct)), LoadVarInst(Address(fSlow28BE, kStack))))), LoadVarInst(Address(fSlow102BE, kStack))), Float(-1.0f)))
	DeclareVarInst("float", fSlow105BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider9, kStruct)))))
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
			StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Float(0.0008f)))
			DeclareVarInst("float", fTemp4SI, kStack, LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp6SE, kStack, BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fTemp6SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))))
			DeclareVarInst("float", fTemp7SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), Int32(65535)))])))
			StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow3BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow5BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow2BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp9SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack))) LoadVarInst(Address(fSlow1BE, kStack)))) LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp11SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp8SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp10SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp8SE, kStack)))))) Float(0.0f)))
			DeclareVarInst("float", fTemp12SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), LoadVarInst(Address(fTemp11SE, kStack)))))
			DeclareVarInst("float", fTemp13SE, kStack, BinopInst("*", LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), FunCallInst("cosf", LoadVarInst(Address(fTemp12SE, kStack)))))
			DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow7BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp15SE, kStack, BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), LoadVarInst(Address(fTemp15SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), LoadVarInst(Address(fTemp15SE, kStack)))))))
			DeclareVarInst("float", fTemp16SE, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("int", iTemp17SE, kStack, CastInst("int", LoadVarInst(Address(fTemp16SE, kStack))))
			DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(ftbl1SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp17SE, kStack)), Int32(65536)))]))
			DeclareVarInst("float", fTemp19SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp16SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp16SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl1SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp17SE, kStack)), Int32(1)), Int32(65536)))]), MinusInst(LoadVarInst(Address(fTemp18SE, kStack)))))))
			DeclareVarInst("float", fTemp20SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(fTemp19SE, kStack))))
			StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow10BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp21SE, kStack, LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow12BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp22SE, kStack, LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow9BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp22SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp22SE, kStack))) LoadVarInst(Address(fSlow8BE, kStack)))) LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			DeclareVarInst("float", fTemp23SE, kStack, LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp24SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp21SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp23SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp21SE, kStack)))))) Float(0.0f)))
			DeclareVarInst("float", fTemp25SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp20SE, kStack)), LoadVarInst(Address(fTemp24SE, kStack)))))
			DeclareVarInst("float", fTemp26SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp25SE, kStack))))
			DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp28SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp26SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp27SE, kStack)), FunCallInst("cosf", LoadVarInst(Address(fTemp25SE, kStack)))))))
			DeclareVarInst("float", fTemp29SI, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp4SI, kStack)))))
			DeclareVarInst("float", fTemp30SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp29SI, kStack))))
			DeclareVarInst("float", fTemp31SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp28SE, kStack)), LoadVarInst(Address(fTemp30SE, kStack))))
			StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow16BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp32SE, kStack, LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow18BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp33SE, kStack, LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow15BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp33SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow19BE, kStack)), LoadVarInst(Address(fTemp33SE, kStack))) LoadVarInst(Address(fSlow14BE, kStack)))) LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			DeclareVarInst("float", fTemp34SE, kStack, LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp35SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp32SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp34SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp32SE, kStack)))))) Float(0.0f)))
			DeclareVarInst("float", fTemp36SE, kStack, BinopInst("*", Float(1.5707964f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(fTemp35SE, kStack))), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp28SE, kStack)), LoadVarInst(Address(fTemp30SE, kStack))), LoadVarInst(Address(fVec37SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp37SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp36SE, kStack))))
			DeclareVarInst("float", fTemp38SE, kStack, LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp39SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp31SE, kStack)), LoadVarInst(Address(fTemp37SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp38SE, kStack)), FunCallInst("cosf", LoadVarInst(Address(fTemp36SE, kStack)))))), BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp31SE, kStack)))))
			StoreVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow22BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst6KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp40SE, kStack, LoadVarInst(Address(fVec39SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow24BE, kStack)) Float(0.0f) FunCallInst("min_f", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(1.0f)))))
			DeclareVarInst("float", fTemp41SE, kStack, LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iSlow21BE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp41SE, kStack)), LoadVarInst(Address(fConst7KI, kStruct))) BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), LoadVarInst(Address(fTemp41SE, kStack))) LoadVarInst(Address(fSlow20BE, kStack)))) LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			DeclareVarInst("float", fTemp42SE, kStack, LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp43SE, kStack, Select2Inst(BinopInst("<", LoadVarInst(Address(fTemp40SE, kStack)), LoadVarInst(Address(fConst6KI, kStruct))) BinopInst("*", LoadVarInst(Address(fTemp42SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fTemp40SE, kStack)))))) Float(0.0f)))
			DeclareVarInst("float", fTemp44SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), LoadVarInst(Address(fTemp43SE, kStack))), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp39SE, kStack))))))
			DeclareVarInst("float", fTemp45SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp44SE, kStack))))
			DeclareVarInst("float", fTemp46SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp39SE, kStack)), LoadVarInst(Address(fTemp45SE, kStack))), BinopInst("*", LoadVarInst(Address(fVec45SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), FunCallInst("cosf", LoadVarInst(Address(fTemp44SE, kStack)))))))
			DeclareVarInst("float", fTemp47SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp39SE, kStack))))
			DeclareVarInst("float", fTemp48SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp12SE, kStack))))
			DeclareVarInst("float", fTemp49SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp48SE, kStack))))
			StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp13SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp46SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp47SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp49SE, kStack)))), MinusInst(LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))))
			StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow26BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp50SE, kStack, BinopInst("*", LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp51SE, kStack, FunCallInst("max_f", Float(0.05f), FunCallInst("min_f", Float(1.0f), LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("*", LoadVarInst(Address(fTemp50SE, kStack)), LoadVarInst(Address(fTemp51SE, kStack))))
			DeclareVarInst("float", fTemp52SE, kStack, LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst1KI, kStruct))), Int32(4095))]))
			DeclareVarInst("float", fTemp53SE, kStack, BinopInst("*", Float(0.18f), LoadVarInst(Address(fTemp52SE, kStack))))
			DeclareVarInst("float", fTemp54SE, kStack, LoadVarInst(Address(fVec54SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp55SE, kStack, LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp55SE, kStack)))), MinusInst(LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec55SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fVec55SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp55SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec55SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp56SE, kStack, LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst19KI, kStruct))), Int32(32767))]))
			DeclareVarInst("float", fRec23SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp54SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp56SE, kStack))))))
			DeclareVarInst("float", fTemp57SE, kStack, LoadVarInst(Address(fRec23SE, kStack)))
			DeclareVarInst("float", fTemp58SE, kStack, LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp58SE, kStack)))), MinusInst(LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow45BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp58SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow46BE, kStack)), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp59SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst25KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp53SE, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec26SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp59SE, kStack))))
			DeclareVarInst("float", fTemp60SE, kStack, LoadVarInst(Address(fRec26SE, kStack)))
			DeclareVarInst("float", fTemp61SE, kStack, BinopInst("*", Float(-0.18f), LoadVarInst(Address(fTemp52SE, kStack))))
			DeclareVarInst("float", fTemp62SE, kStack, LoadVarInst(Address(fVec75SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp62SE, kStack)))), MinusInst(LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp62SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow56BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp63SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst31KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp61SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec29SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp63SE, kStack))))
			DeclareVarInst("float", fTemp64SE, kStack, LoadVarInst(Address(fRec29SE, kStack)))
			DeclareVarInst("float", fTemp65SE, kStack, LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec86SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec86SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp65SE, kStack)))), MinusInst(LoadVarInst(Address(fVec87SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow63BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp65SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fVec86SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec90SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp66SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec90SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst37KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp53SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec32SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp66SE, kStack))))
			DeclareVarInst("float", fTemp67SE, kStack, LoadVarInst(Address(fRec32SE, kStack)))
			DeclareVarInst("float", fTemp68SE, kStack, LoadVarInst(Address(fVec94SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp69SE, kStack, LoadVarInst(Address(fVec95SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp70SE, kStack, LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp71SE, kStack, LoadVarInst(Address(fVec98SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec99SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec99SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp71SE, kStack)))), MinusInst(LoadVarInst(Address(fVec100SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow73BE, kStack)), LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow74BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp71SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fVec99SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec103SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp72SE, kStack, LoadVarInst(Address(fVec103SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst43KI, kStruct))), Int32(32767))]))
			DeclareVarInst("float", fRec35SE, kStack, BinopInst("*", Float(0.6f), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53SE, kStack)), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp70SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp72SE, kStack))))))
			DeclareVarInst("float", fTemp73SE, kStack, LoadVarInst(Address(fRec35SE, kStack)))
			DeclareVarInst("float", fTemp74SE, kStack, LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec108SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec108SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp74SE, kStack)))), MinusInst(LoadVarInst(Address(fVec109SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec106SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow82BE, kStack)), LoadVarInst(Address(fVec106SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow83BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp74SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow84BE, kStack)), LoadVarInst(Address(fVec108SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(32767))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec106SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp75SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst49KI, kStruct))), Int32(32767))]), LoadVarInst(Address(fTemp53SE, kStack))), BinopInst("*", Float(0.6f), LoadVarInst(Address(fVec114SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec38SE, kStack, BinopInst("*", Float(-0.6f), LoadVarInst(Address(fTemp75SE, kStack))))
			DeclareVarInst("float", fTemp76SE, kStack, LoadVarInst(Address(fRec38SE, kStack)))
			DeclareVarInst("float", fTemp77SE, kStack, LoadVarInst(Address(fVec116SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp78SE, kStack, LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp78SE, kStack)))), MinusInst(LoadVarInst(Address(fVec120SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow91BE, kStack)), LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow93BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp78SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow94BE, kStack)), LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec123SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp79SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec123SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst55KI, kStruct))), Int32(16383))]), LoadVarInst(Address(fTemp61SE, kStack))), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec125SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec41SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp79SE, kStack))))
			DeclareVarInst("float", fTemp80SE, kStack, LoadVarInst(Address(fRec41SE, kStack)))
			DeclareVarInst("float", fTemp81SE, kStack, LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp82SE, kStack, LoadVarInst(Address(fVec129SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec130SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec130SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp82SE, kStack)))), MinusInst(LoadVarInst(Address(fVec131SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))))))
			StoreVarInst(Address(fVec128SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow101BE, kStack)), LoadVarInst(Address(fVec128SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow103BE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp82SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow104BE, kStack)), LoadVarInst(Address(fVec130SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(16383))], BinopInst("+", BinopInst("*", Float(0.35355338f), LoadVarInst(Address(fVec128SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1e-20f)))
			DeclareVarInst("float", fTemp83SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp53SE, kStack)), LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst61KI, kStruct))), Int32(16383))])), BinopInst("*", Float(-0.6f), LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fRec44SE, kStack, BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp83SE, kStack))))
			DeclareVarInst("float", fTemp84SE, kStack, LoadVarInst(Address(fRec44SE, kStack)))
			StoreVarInst(Address(fVec98SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))))
			StoreVarInst(Address(fVec100SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec98SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp85SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), Select2Inst(Int32(0) LoadVarInst(Address(fTemp10SE, kStack)) LoadVarInst(Address(fTemp11SE, kStack))))))
			DeclareVarInst("float", fTemp86SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp85SE, kStack))))
			DeclareVarInst("float", fTemp87SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp86SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec139SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp48SE, kStack))))))
			DeclareVarInst("float", fTemp88SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp87SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp89SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp88SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp90SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp89SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp91SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp90SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec143SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec144SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fTemp91SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp48SE, kStack)), LoadVarInst(Address(fVec144SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec145SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec144SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp92SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp85SE, kStack))))
			StoreVarInst(Address(fVec143SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp91SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec145SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec143SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp90SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec149SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec141SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp89SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec149SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec151SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec141SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp88SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec151SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec153SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec140SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec139SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp92SE, kStack)), LoadVarInst(Address(fTemp87SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp86SE, kStack)), LoadVarInst(Address(fVec153SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec139SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp93SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", LoadVarInst(Address(fTemp20SE, kStack)), Select2Inst(Int32(0) LoadVarInst(Address(fTemp23SE, kStack)) LoadVarInst(Address(fTemp24SE, kStack))))))
			DeclareVarInst("float", fTemp94SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp93SE, kStack))))
			DeclareVarInst("float", fTemp95SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp94SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec156SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp26SE, kStack))))))
			DeclareVarInst("float", fTemp96SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp95SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp97SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp96SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec158SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp98SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp97SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec159SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp99SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp98SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec160SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec161SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp99SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp26SE, kStack)), LoadVarInst(Address(fVec161SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec161SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp100SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp93SE, kStack))))
			StoreVarInst(Address(fVec160SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp99SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec164SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec160SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec159SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp98SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec164SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec166SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec159SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec158SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp97SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec166SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec168SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec158SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp96SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec168SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec170SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec156SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp100SE, kStack)), LoadVarInst(Address(fTemp95SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fVec170SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec156SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp101SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp19SE, kStack)), LoadVarInst(Address(fTemp100SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp94SE, kStack)), LoadVarInst(Address(fTemp27SE, kStack))))))
			DeclareVarInst("float", fTemp102SE, kStack, BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp19SE, kStack))))
			DeclareVarInst("float", fTemp103SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp101SE, kStack)), LoadVarInst(Address(fTemp102SE, kStack))))
			StoreVarInst(Address(fVec173SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp103SE, kStack)))
			StoreVarInst(Address(fVec37SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp31SE, kStack)))
			DeclareVarInst("float", fTemp104SE, kStack, BinopInst("*", Float(1.5707964f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), Select2Inst(Int32(0) LoadVarInst(Address(fTemp34SE, kStack)) LoadVarInst(Address(fTemp35SE, kStack)))), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp101SE, kStack)), LoadVarInst(Address(fTemp102SE, kStack))), LoadVarInst(Address(fVec173SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp105SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp104SE, kStack))))
			DeclareVarInst("float", fTemp106SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp103SE, kStack)), LoadVarInst(Address(fTemp105SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec176SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp37SE, kStack))))))
			DeclareVarInst("float", fTemp107SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp106SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp108SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp107SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec178SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp109SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp108SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec179SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp110SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp109SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec180SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec181SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp110SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp37SE, kStack)), LoadVarInst(Address(fVec181SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec182SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec181SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp111SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp104SE, kStack))))
			StoreVarInst(Address(fVec180SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp110SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec182SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec184SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec180SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec179SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp109SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec184SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec186SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec179SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec178SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp108SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec186SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec188SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec178SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp107SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec188SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec190SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec176SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp111SE, kStack)), LoadVarInst(Address(fTemp106SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fVec190SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec176SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp112SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp103SE, kStack)), LoadVarInst(Address(fTemp111SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp105SE, kStack)), LoadVarInst(Address(fTemp38SE, kStack))))), BinopInst("*", LoadVarInst(Address(fTemp29SI, kStack)), LoadVarInst(Address(fTemp103SE, kStack)))))
			DeclareVarInst("float", fTemp113SE, kStack, BinopInst("*", Float(3.1415927f), BinopInst("*", BinopInst("*", LoadVarInst(Address(fTemp4SI, kStack)), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fTemp112SE, kStack)))), Select2Inst(Int32(0) LoadVarInst(Address(fTemp42SE, kStack)) LoadVarInst(Address(fTemp43SE, kStack))))))
			DeclareVarInst("float", fTemp114SE, kStack, FunCallInst("cosf", LoadVarInst(Address(fTemp113SE, kStack))))
			DeclareVarInst("float", fTemp115SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp112SE, kStack)), LoadVarInst(Address(fTemp114SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec193SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fTemp45SE, kStack))))))
			DeclareVarInst("float", fTemp116SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp115SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec194SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp117SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp116SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec195SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp118SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp117SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec196SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			DeclareVarInst("float", fTemp119SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp118SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec197SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec198SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fTemp119SE, kStack))), MinusInst(BinopInst("*", LoadVarInst(Address(fTemp45SE, kStack)), LoadVarInst(Address(fVec198SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec199SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec198SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp120SE, kStack, FunCallInst("sinf", LoadVarInst(Address(fTemp113SE, kStack))))
			StoreVarInst(Address(fVec197SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp119SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec199SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec201SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec197SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec196SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp118SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec201SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec203SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec196SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec195SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp117SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec203SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec205SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec195SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec194SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp116SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec205SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec207SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec194SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec193SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp120SE, kStack)), LoadVarInst(Address(fTemp115SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp114SE, kStack)), LoadVarInst(Address(fVec207SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec193SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp13SE, kStack)), LoadVarInst(Address(fTemp46SE, kStack))), LoadVarInst(Address(fTemp47SE, kStack))), LoadVarInst(Address(fTemp49SE, kStack))))
			StoreVarInst(Address(fVec211SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp70SE, kStack))), LoadVarInst(Address(fTemp72SE, kStack))), LoadVarInst(Address(fTemp61SE, kStack))))
			StoreVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec211SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst62KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec94SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
			StoreVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec215SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", BinopInst("+", BinopInst("*", Float(0.6f), LoadVarInst(Address(fTemp54SE, kStack))), LoadVarInst(Address(fTemp56SE, kStack))), LoadVarInst(Address(fTemp61SE, kStack))))
			StoreVarInst(Address(fVec54SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec215SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst63KI, kStruct))), Int32(4095))]))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec54SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
			StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec219SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp59SE, kStack)))
			StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec219SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst64KI, kStruct))), Int32(4095))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp69SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp76SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))))
			StoreVarInst(Address(fVec109SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec223SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp75SE, kStack)))
			StoreVarInst(Address(fVec114SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec223SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst65KI, kStruct))), Int32(4095))]))
			StoreVarInst(Address(fVec95SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec114SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec75SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))))
			StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec75SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec227SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp63SE, kStack)))
			StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec227SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst66KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp0SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp77SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp57SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp80SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
			StoreVarInst(Address(fVec120SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec231SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp79SE, kStack)))
			StoreVarInst(Address(fVec125SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec231SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst67KI, kStruct))), Int32(4095))]))
			StoreVarInst(Address(fVec116SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec125SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec129SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), MinusInst(LoadVarInst(Address(fTemp68SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp81SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp73SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp60SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp84SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp64SE, kStack)))))
			StoreVarInst(Address(fVec131SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec129SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec235SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp83SE, kStack)))
			StoreVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec235SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst68KI, kStruct))), Int32(4095))]))
			StoreVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec136SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp68SE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fTemp69SE, kStack))), LoadVarInst(Address(fTemp2SE, kStack))), LoadVarInst(Address(fTemp77SE, kStack))), LoadVarInst(Address(fTemp81SE, kStack))), LoadVarInst(Address(fTemp3SE, kStack))), LoadVarInst(Address(fTemp73SE, kStack))), LoadVarInst(Address(fTemp57SE, kStack))), LoadVarInst(Address(fTemp60SE, kStack))), LoadVarInst(Address(fTemp76SE, kStack))), LoadVarInst(Address(fTemp64SE, kStack))), LoadVarInst(Address(fTemp80SE, kStack))), LoadVarInst(Address(fTemp67SE, kStack))), LoadVarInst(Address(fTemp84SE, kStack))))
			StoreVarInst(Address(fVec87SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec239SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp66SE, kStack)))
			StoreVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec239SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst69KI, kStruct))), Int32(2047))]))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec242SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow105BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec242SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp121SE, kStack, FunCallInst("max_f", Float(0.75f), FunCallInst("min_f", Float(4.0f), LoadVarInst(Address(fVec242SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			DeclareVarInst("float", fTemp122SE, kStack, LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp123SE, kStack, LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp124SE, kStack, BinopInst("*", Float(0.6f), BinopInst("*", LoadVarInst(Address(fTemp50SE, kStack)), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp51SE, kStack)))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp121SE, kStack)), BinopInst("+", BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fTemp122SE, kStack)), LoadVarInst(Address(fTemp123SE, kStack)))), LoadVarInst(Address(fTemp124SE, kStack))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp121SE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp124SE, kStack)), BinopInst("*", Float(0.37f), BinopInst("+", LoadVarInst(Address(fTemp122SE, kStack)), MinusInst(LoadVarInst(Address(fTemp123SE, kStack)))))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 76 bytes
Heap size int* = 0 bytes
Heap size real = 845052 bytes
Total heap size = 845140 bytes
Stack size in compute = 440 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst7KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst8KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec39SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec50SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst10KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec57SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst17KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec55SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst19KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec66SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst23KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst24KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst25KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst27KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec80SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst30KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst31KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec86SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec90SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst36KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst39KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec99SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst41KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec97SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec103SE size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst42KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst43KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst46KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec108SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst47KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec106SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec112SE size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst48KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst49KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst53KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec119SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec117SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec123SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst54KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst55KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst56KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec130SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec128SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec134SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst60KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst61KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec98SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec100SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec144SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec145SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec143SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec147SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec142SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec149SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec141SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec151SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec140SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec153SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec139SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec161SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec162SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec160SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec164SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec159SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec166SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec158SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec168SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec157SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec170SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec156SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec173SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec37SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec181SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec182SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec180SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec184SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec179SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec186SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec178SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec188SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec177SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec190SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec176SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec198SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec199SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec197SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec201SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec196SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec203SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec195SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec205SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec194SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec207SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec193SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec45SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec211SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst62KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec96SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec94SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec56SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec58SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec215SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst63KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec54SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec65SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec219SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst64KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec107SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec109SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec223SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst65KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec114SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec95SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec75SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec227SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst66KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec118SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec120SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec231SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst67KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec125SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec116SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec129SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec131SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec235SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst68KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec136SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec127SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec85SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec87SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec239SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst69KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec92SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec242SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst7KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst8KI size = 1 size_bytes = 4 read = 4 write = 0 ratio = 4
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec31SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec39SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec48SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec50SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst10KI size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fHslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst11KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec57SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst17KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec55SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst19KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec66SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst23KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec64SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst24KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst25KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst27KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst29KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec80SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst30KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst31KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst35KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec86SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec90SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst36KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst38KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst39KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec99SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst41KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec97SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec103SE size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst42KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst43KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst44KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst46KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec108SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst47KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec106SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec112SE size = 32768 size_bytes = 131072 read = 0 write = 0 ratio = 0
Field = fConst48KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst49KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst50KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst53KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec119SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec117SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec123SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst54KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst55KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst56KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst59KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec130SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec128SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec134SE size = 16384 size_bytes = 65536 read = 0 write = 0 ratio = 0
Field = fConst60KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst61KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec98SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec100SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec144SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec145SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec143SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec147SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec142SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec149SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec141SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec151SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec140SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec153SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec139SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec161SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec162SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec160SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec164SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec159SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec166SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec158SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec168SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec157SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec170SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec156SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec173SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec37SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec181SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec182SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec180SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec184SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec179SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec186SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec178SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec188SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec177SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec190SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec176SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec198SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec199SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec197SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec201SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec196SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec203SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec195SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec205SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec194SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec207SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec193SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec45SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec211SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst62KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec96SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec94SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec56SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec58SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec215SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst63KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec54SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec65SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec219SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst64KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec107SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec109SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec223SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst65KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec114SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec95SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec75SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec227SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst66KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec118SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec120SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec231SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst67KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec125SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec116SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec129SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec131SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec235SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = iConst68KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec136SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec127SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec85SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec87SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec239SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = iConst69KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec92SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec242SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 354 write = 1 ratio = 355
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst1KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst5KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst6KI size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst7KI size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fVec17SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst8KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst9KI size = 1 size_bytes = 4 read = 4 write = 0 ratio = 4
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec20SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec27SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec26SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec34SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec33SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec39SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec42SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec41SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec4SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec50SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec52SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fConst10KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15KI size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fConst16KI size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fVec57SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst17KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec55SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec61SE size = 32768 size_bytes = 131072 read = 1 write = 1 ratio = 6.10352e-05
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst19KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec66SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst23KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec70SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst24KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst25KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst26KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst27KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst29KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec74SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec80SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst30KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst31KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst32KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst35KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec86SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec84SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec90SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst36KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst37KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst38KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst39KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst40KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec99SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst41KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec97SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec103SE size = 32768 size_bytes = 131072 read = 1 write = 1 ratio = 6.10352e-05
Field = fConst42KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst43KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst44KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst45KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst46KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec108SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst47KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec106SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec112SE size = 32768 size_bytes = 131072 read = 1 write = 1 ratio = 6.10352e-05
Field = fConst48KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst49KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst50KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst51KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst52KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst53KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec119SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec117SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec123SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst54KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst55KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst56KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst57KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst58KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst59KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec130SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec128SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec134SE size = 16384 size_bytes = 65536 read = 1 write = 1 ratio = 0.00012207
Field = fConst60KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst61KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec98SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec100SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec144SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec145SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec143SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec147SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec142SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec149SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec141SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec151SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec140SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec153SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec139SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec5SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec161SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec162SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec160SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec164SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec159SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec166SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec158SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec168SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec157SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec170SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec156SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec30SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec173SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec37SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec181SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec182SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec180SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec184SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec179SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec186SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec178SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec188SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec177SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec190SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec176SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec38SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec198SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec199SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec197SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec201SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec196SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec203SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec195SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec205SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec194SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec207SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec193SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec45SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec46SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec211SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst62KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec96SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec94SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec56SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec58SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec215SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst63KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec54SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec0SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec65SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec67SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec219SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst64KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec72SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec1SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec107SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec109SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec223SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst65KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec114SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec95SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec75SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec77SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec227SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst66KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec82SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec2SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec118SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec120SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec231SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst67KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec125SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec116SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec129SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec131SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec235SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = iConst68KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec136SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec127SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec85SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec87SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec239SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = iConst69KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec92SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec3SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec242SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
