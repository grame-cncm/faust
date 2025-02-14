======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("lowboost")
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddMetaDeclareInst(fEntry0, "unit", "Hz")
	AddNumEntry"freq", fEntry0, 1e+02f, 2e+01f, 1.5e+02f, 1.0f)
	AddMetaDeclareInst(fVslider0, "unit", "dB")
	AddVerticalSlider("gain", fVslider0, 0.0f, -2e+01f, 2e+01f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fEntry0)("int", fSampleRate)("float", fConst0KI)("int", IOTA0)("float[2]", fVec1SE)("float[4]", fVec0SE)("FAUSTFLOAT", fVslider0)>)

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
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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

Instructions complexity : Load = 22 Store = 0 Binop = 22 [ { Real(*) = 11 } { Real(+) = 10 } { Real(/) = 1 } ] Mathop = 4 [ { mydsp_faustpower2_f = 1 } { powf = 1 } { sqrtf = 1 } { tanf = 1 } ] Numbers = 16 Declare = 13 Cast = 2 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(1.4142135f))), Float(1.0f))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(-1.4142135f))), Float(1.0f)))
	DeclareVarInst("float", fSlow3BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), Float(-1.0f))))
	DeclareVarInst("float", fSlow5BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow6BE, kStack, FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow5BE, kStack)))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fSlow7BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow3BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), MinusInst(LoadVarInst(Address(fSlow7BE, kStack))))))))
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
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SE, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(3.1415927f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
	DeclareVarInst("float", fSlow0BE, kStack, FunCallInst("tanf", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fEntry0, kStruct))))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(1.4142135f))), Float(1.0f))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), Float(-1.4142135f))), Float(1.0f)))
	DeclareVarInst("float", fSlow3BE, kStack, FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), Float(-1.0f))))
	DeclareVarInst("float", fSlow5BE, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow6BE, kStack, FunCallInst("sqrtf", BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow5BE, kStack)))))
	DeclareVarInst("float", fSlow7BE, kStack, BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fSlow7BE, kStack)))), Float(1.0f)))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow3BE, kStack))), Float(-1.0f))))
	DeclareVarInst("float", fSlow10BE, kStack, BinopInst("+", Float(1.0f), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), MinusInst(LoadVarInst(Address(fSlow7BE, kStack))))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SE, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
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
Stack size in compute = 60 bytes

======= Variable access in Control ==========

Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1

======= Variable access in compute DSP ==========

Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 8 write = 1 ratio = 9
Field = fVec1SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec0SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
