======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Pitch Shifter")
	AddHorizontalSlider("shift (semitones)", fHslider1, 0.0f, -12.0f, 12.0f, 0.1f)
	AddHorizontalSlider("window (samples)", fHslider0, 1e+03f, 5e+01f, 1e+04f, 1.0f)
	AddHorizontalSlider("xfade (samples)", fHslider2, 1e+01f, 1.0f, 1e+04f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[65536]", fVec0SE)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float[2]", fVec1SE)("FAUSTFLOAT", fHslider2)("int", fSampleRate)>)

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
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+01f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(65536))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 4 Store = 0 Binop = 1 [ { Real(/) = 1 } ] Mathop = 0 Numbers = 3 Declare = 4 Cast = 2 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 48 Store = 5 Binop = 46 [ { Int(&) = 12 } { Int(+) = 4 } { Int(-) = 5 } { Int(<) = 1 } { Real(*) = 8 } { Real(+) = 16 } ] Mathop = 3 [ { fmodf = 1 } { min_f = 1 } { powf = 1 } ] Numbers = 25 Declare = 8 Cast = 7 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(65535))], LoadVarInst(Address(fTemp0SE, kStack)))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("fmodf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Float(1.0f)), MinusInst(FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))), LoadVarInst(Address(fSlow0BE, kStack))))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp2SE, kStack, CastInst("int", LoadVarInst(Address(fTemp1SE, kStack))))
		DeclareVarInst("float", fTemp3SE, kStack, CastInst("float", LoadVarInst(Address(iTemp2SE, kStack))))
		DeclareVarInst("float", fTemp4SE, kStack, FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), Float(1.0f)))
		DeclareVarInst("int", iTemp5SE, kStack, CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))
		DeclareVarInst("float", fTemp6SE, kStack, CastInst("float", LoadVarInst(Address(iTemp5SE, kStack))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp2SE, kStack)), Int32(65535))), Int32(65535))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp1SE, kStack))))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), MinusInst(LoadVarInst(Address(fTemp3SE, kStack)))), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp2SE, kStack)), Int32(1)), Int32(65535))), Int32(65535))]))), LoadVarInst(Address(fTemp4SE, kStack))), BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp5SE, kStack)), Int32(65535))), Int32(65535))]), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fSlow0BE, kStack))))), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), MinusInst(LoadVarInst(Address(fTemp6SE, kStack)))), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp5SE, kStack)), Int32(1)), Int32(65535))), Int32(65535))]))), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp4SE, kStack))))))))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[65536], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+01f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(65536))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(65535))], LoadVarInst(Address(fTemp0SE, kStack)))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("fmodf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Float(1.0f)), MinusInst(FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.083333336f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))), LoadVarInst(Address(fSlow0BE, kStack))))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp2SE, kStack, CastInst("int", LoadVarInst(Address(fTemp1SE, kStack))))
			DeclareVarInst("float", fTemp3SE, kStack, CastInst("float", LoadVarInst(Address(iTemp2SE, kStack))))
			DeclareVarInst("float", fTemp4SE, kStack, FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), Float(1.0f)))
			DeclareVarInst("int", iTemp5SE, kStack, CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))
			DeclareVarInst("float", fTemp6SE, kStack, CastInst("float", LoadVarInst(Address(iTemp5SE, kStack))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp2SE, kStack)), Int32(65535))), Int32(65535))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp1SE, kStack))))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), MinusInst(LoadVarInst(Address(fTemp3SE, kStack)))), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp2SE, kStack)), Int32(1)), Int32(65535))), Int32(65535))]))), LoadVarInst(Address(fTemp4SE, kStack))), BinopInst("*", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp5SE, kStack)), Int32(65535))), Int32(65535))]), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp1SE, kStack)))), MinusInst(LoadVarInst(Address(fSlow0BE, kStack))))), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))), MinusInst(LoadVarInst(Address(fTemp6SE, kStack)))), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp5SE, kStack)), Int32(1)), Int32(65535))), Int32(65535))]))), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp4SE, kStack))))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 262164 bytes
Total heap size = 262172 bytes
Stack size in compute = 24 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 65536 size_bytes = 262144 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 65536 size_bytes = 262144 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 9 write = 1 ratio = 10
Field = fVec0SE size = 65536 size_bytes = 262144 read = 4 write = 1 ratio = 7.62939e-05
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
