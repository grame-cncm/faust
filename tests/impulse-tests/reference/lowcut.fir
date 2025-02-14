======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("low-freq shelving cut")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "unit", "dB")
	AddHorizontalSlider("attenuation", fHslider1, 0.0f, -96.0f, 1e+01f, 0.1f)
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider0, 1e+02f, 2e+01f, 5e+03f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("int", fSampleRate)("float", fConst0KI)("FAUSTFLOAT", fHslider1)("int", IOTA0)("float[2]", fVec1SE)("float[4]", fVec0SE)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 28 Store = 0 Binop = 30 [ { Real(*) = 16 } { Real(+) = 12 } { Real(/) = 2 } ] Mathop = 8 [ { mydsp_faustpower2_f = 1 } { powf = 3 } { sqrtf = 3 } { tanf = 1 } ] Numbers = 23 Declare = 16 Cast = 2 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow2BE, kStack)))), LoadVarInst(Address(fSlow3BE, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow1BE, kStack))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))))), MinusInst(LoadVarInst(Address(fSlow3BE, kStack))))))))
	DeclareVarInst("float", fSlow7BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), LoadVarInst(Address(fSlow2BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow9BE, kStack, FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow9BE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fSlow9BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(1.4142135f))), Float(1.0f)))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow7BE, kStack)), Float(-1.0f))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(-1.4142135f))), Float(1.0f)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 29 Store = 5 Binop = 24 [ { Int(&) = 7 } { Int(+) = 2 } { Int(-) = 3 } { Int(<) = 1 } { Real(*) = 7 } { Real(+) = 4 } ] Mathop = 0 Numbers = 13 Declare = 3 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SE, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[4], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(-0.05f), LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow2BE, kStack)))), LoadVarInst(Address(fSlow3BE, kStack)))), Float(1.0f))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(0.05f), LoadVarInst(Address(fSlow1BE, kStack))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))))), MinusInst(LoadVarInst(Address(fSlow3BE, kStack))))))))
	DeclareVarInst("float", fSlow7BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), LoadVarInst(Address(fSlow2BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow9BE, kStack, FunCallInst("powf", Float(1e+01f), MinusInst(LoadVarInst(Address(fSlow5BE, kStack)))))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow9BE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fSlow9BE, kStack))))), Float(1.0f))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(1.4142135f))), Float(1.0f)))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow7BE, kStack)), Float(-1.0f))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(-1.4142135f))), Float(1.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SE, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 36 bytes
Total heap size = 44 bytes
Stack size in compute = 72 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 8 write = 1 ratio = 9
Field = fVec1SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec0SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
