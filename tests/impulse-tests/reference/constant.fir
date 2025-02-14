======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("constant")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0KI)("float", fConst1KI)("int", IOTA0)("float[2]", fVec0SE)("int", iConst2KI)("int", iConst3KI)("float[4]", fVec2SE)("int", iConst4KI)("float[8]", fVec5SE)("int", iConst5KI)>)

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
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(iConst2KI, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", LoadVarInst(Address(fConst0KI, kStruct)))), Int32(2)))
	StoreVarInst(Address(iConst3KI, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0KI, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst4KI, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0KI, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst5KI, kStruct), BinopInst("+", LoadVarInst(Address(iConst2KI, kStruct)), BinopInst("*", Int32(2), LoadVarInst(Address(iConst3KI, kStruct)))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(8))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 36 Store = 6 Binop = 24 [ { Int(&) = 11 } { Int(+) = 2 } { Int(-) = 4 } { Int(<) = 1 } { Real(*) = 1 } { Real(+) = 5 } ] Mathop = 0 Numbers = 20 Declare = 4 Cast = 2 Select = 4 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp0SE, kStack)))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp2SE, kStack, BinopInst("+", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp1SE, kStack))))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp2SE, kStack)))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(7))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), BinopInst("+", BinopInst("+", Select2Inst(Int32(0) LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]) Select2Inst(LoadVarInst(Address(iConst2KI, kStruct)) LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst3KI, kStruct)) LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst2KI, kStruct))), Int32(3))]) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst4KI, kStruct)) LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst5KI, kStruct))), Int32(7))]) Float(0.0f))))))
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
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	DeclareVarInst("int", iConst2KI, kStruct)
	DeclareVarInst("int", iConst3KI, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SE[4], kStruct)
	DeclareVarInst("int", iConst4KI, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec5SE[8], kStruct)
	DeclareVarInst("int", iConst5KI, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(iConst2KI, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", LoadVarInst(Address(fConst0KI, kStruct)))), Int32(2)))
	StoreVarInst(Address(iConst3KI, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0KI, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst4KI, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0KI, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst5KI, kStruct), BinopInst("+", LoadVarInst(Address(iConst2KI, kStruct)), BinopInst("*", Int32(2), LoadVarInst(Address(iConst3KI, kStruct)))))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(8))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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
			DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp0SE, kStack)))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp2SE, kStack, BinopInst("+", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp1SE, kStack))))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp2SE, kStack)))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(7))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp1SE, kStack))), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), BinopInst("+", BinopInst("+", Select2Inst(Int32(0) LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]) Select2Inst(LoadVarInst(Address(iConst2KI, kStruct)) LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst3KI, kStruct)) LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst2KI, kStruct))), Int32(3))]) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst4KI, kStruct)) LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iConst5KI, kStruct))), Int32(7))]) Float(0.0f))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 24 bytes
Heap size int* = 0 bytes
Heap size real = 64 bytes
Total heap size = 88 bytes
Stack size in compute = 16 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 8 size_bytes = 32 read = 0 write = 0 ratio = 0
Field = iConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 8 size_bytes = 32 read = 0 write = 0 ratio = 0
Field = iConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 12 write = 1 ratio = 13
Field = fVec0SE size = 2 size_bytes = 8 read = 5 write = 1 ratio = 3
Field = iConst2KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = iConst3KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2SE size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = iConst4KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec5SE size = 8 size_bytes = 32 read = 1 write = 1 ratio = 0.25
Field = iConst5KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
