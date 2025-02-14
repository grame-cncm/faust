======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Audio Capture")
	AddButtonInst("Capture"fButton0)
	AddHorizontalSlider("level (db)", fHslider0, 0.0f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fButton0)("int", IOTA0)("int[2]", iVec0BE)("float[524288]", fVec2SE)("int[2]", iVec3SE)("float[2]", fVec1SE)("FAUSTFLOAT", fHslider0)("float[2]", fVec8SE)("int", fSampleRate)>)

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
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(Address(iVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(524288))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec3SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 7 Store = 0 Binop = 3 [ { Real(*) = 2 } { Real(+) = 1 } ] Mathop = 1 [ { powf = 1 } ] Numbers = 6 Declare = 7 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("int", iSlow1BE, kStack, CastInst("int", LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("int", iSlow2BE, kStack, LoadVarInst(Address(iSlow1BE, kStack)))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow0BE, kStack)))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 34 Store = 8 Binop = 33 [ { Int(&) = 14 } { Int(*) = 1 } { Int(+) = 5 } { Int(-) = 5 } { Int(<) = 1 } { Int(<=) = 1 } { Real(*) = 4 } { Real(+) = 2 } ] Mathop = 0 Numbers = 24 Declare = 1 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iSlow2BE, kStack)))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))))
		StoreVarInst(Address(iVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", BinopInst("+", LoadVarInst(Address(iSlow1BE, kStack)), LoadVarInst(Address(iVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("<=", BinopInst("+", LoadVarInst(Address(iSlow1BE, kStack)), MinusInst(LoadVarInst(Address(iVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Int32(0))))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Int32(-1)), Int32(524287))), Int32(524287))]))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
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
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec0BE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SE[524288], kStruct)
	// Recursion delay iVec3SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec3SE[2], kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(524288))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec3SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("int", iSlow1BE, kStack, CastInst("int", LoadVarInst(Address(fSlow0BE, kStack))))
	DeclareVarInst("int", iSlow2BE, kStack, LoadVarInst(Address(iSlow1BE, kStack)))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow0BE, kStack)))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iSlow2BE, kStack)))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))))
			StoreVarInst(Address(iVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", BinopInst("+", LoadVarInst(Address(iSlow1BE, kStack)), LoadVarInst(Address(iVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("<=", BinopInst("+", LoadVarInst(Address(iSlow1BE, kStack)), MinusInst(LoadVarInst(Address(iVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Int32(0))))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Int32(-1)), Int32(524287))), Int32(524287))]))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 16 bytes
Heap size real = 2097176 bytes
Total heap size = 2097200 bytes
Stack size in compute = 36 bytes

======= Variable access in Control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = iVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = iVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 14 write = 1 ratio = 15
Field = iVec0BE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec2SE size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = iVec3SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec1SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
