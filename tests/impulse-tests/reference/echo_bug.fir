======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("echo_bug")
	AddMetaDeclareInst(fHslider0, "0", "")
	AddHorizontalSlider("EchoWarp", fHslider0, 0.0f, -1.0f, 1.0f, 0.001f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[2048]", fRec1)("FAUSTFLOAT", fHslider0)("int", fSampleRate)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2048))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 2 Store = 0 Binop = 0 Mathop = 0 Numbers = 2 Declare = 2 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 27 Store = 4 Binop = 23 [ { Int(&) = 4 } { Int(+) = 3 } { Int(-) = 3 } { Int(<) = 1 } { Real(*) = 5 } { Real(+) = 5 } { Real(-) = 2 } ] Mathop = 5 [ { floorf = 1 } { max_i = 2 } { min_i = 2 } ] Numbers = 18 Declare = 7 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("*", Float(0.995f), LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(2047))])), BinopInst("*", Float(0.005f), LoadVarInst(Address(fTemp0, kStack)))))
		DeclareVarInst("float", fRec3, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
		DeclareVarInst("float", fRec2, kStack, BinopInst("*", Float(1e+02f), BinopInst("+", LoadVarInst(Address(fRec3, kStack)), Float(1.0f))))
		DeclareVarInst("int", iTemp1, kStack, CastInst("int", LoadVarInst(Address(fRec2, kStack))))
		DeclareVarInst("float", fTemp2, kStack, FunCallInst("floorf", LoadVarInst(Address(fRec2, kStack))))
		DeclareVarInst("float", fRec0, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp1, kStack))))), Int32(2047))]), BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec2, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fRec2, kStack)), LoadVarInst(Address(fTemp2, kStack))), LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp1, kStack)), Int32(1))))), Int32(2047))]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec0, kStack)))))
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
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fRec1[2048], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2048))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("*", Float(0.995f), LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(2047))])), BinopInst("*", Float(0.005f), LoadVarInst(Address(fTemp0, kStack)))))
			DeclareVarInst("float", fRec3, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
			DeclareVarInst("float", fRec2, kStack, BinopInst("*", Float(1e+02f), BinopInst("+", LoadVarInst(Address(fRec3, kStack)), Float(1.0f))))
			DeclareVarInst("int", iTemp1, kStack, CastInst("int", LoadVarInst(Address(fRec2, kStack))))
			DeclareVarInst("float", fTemp2, kStack, FunCallInst("floorf", LoadVarInst(Address(fRec2, kStack))))
			DeclareVarInst("float", fRec0, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp1, kStack))))), Int32(2047))]), BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec2, kStack))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fRec2, kStack)), LoadVarInst(Address(fTemp2, kStack))), LoadVarInst(Address(fRec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp1, kStack)), Int32(1))))), Int32(2047))]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec0, kStack)))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 8196 bytes
Total heap size = 8204 bytes
Stack size in compute = 16 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 5 write = 1 ratio = 6
Field = fRec1 size = 2048 size_bytes = 8192 read = 3 write = 1 ratio = 0.00195312
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
