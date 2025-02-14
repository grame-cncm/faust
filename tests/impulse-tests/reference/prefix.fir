======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("prefix")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("float", fConst0KC)("int", IOTA0)("float[2]", fVec0KC)("float", pfPerm0)("float[2]", fVec1SE)("float", pfPerm1)("float[2]", fVec2SE)("float", pfPerm2)("float[2]", fVec3SE)("float", pfPerm3)("float", fConst1KC)("float[2]", fVec4KC)("float", pfPerm4)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(5))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KC, kStruct), Float(0.8f))
	StoreVarInst(Address(pfPerm0, kStruct), Float(0.5f))
	StoreVarInst(Address(pfPerm1, kStruct), Float(0.31f))
	StoreVarInst(Address(pfPerm2, kStruct), Float(0.32f))
	StoreVarInst(Address(pfPerm3, kStruct), Float(0.7f))
	StoreVarInst(Address(fConst1KC, kStruct), Float(0.9f))
	StoreVarInst(Address(pfPerm4, kStruct), Float(0.35f))
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
			StoreVarInst(Address(fVec0KC, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4KC, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 7 Store = 0 Binop = 0 Mathop = 0 Numbers = 7 Declare = 7 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 39 Store = 17 Binop = 11 [ { Int(&) = 8 } { Int(+) = 2 } { Int(<) = 1 } ] Mathop = 0 Numbers = 11 Declare = 6 Cast = 7 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fConst0KC, kStruct)))
		DeclareVarInst("float", pfTemp0, kStack, LoadVarInst(Address(pfPerm0, kStruct)))
		StoreVarInst(Address(pfPerm0, kStruct), LoadVarInst(Address(fConst0KC, kStruct)))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", pfTemp1, kStack, LoadVarInst(Address(pfPerm1, kStruct)))
		StoreVarInst(Address(pfPerm1, kStruct), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", pfTemp2, kStack, LoadVarInst(Address(pfPerm2, kStruct)))
		StoreVarInst(Address(pfPerm2, kStruct), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(pfTemp2, kStack)))
		DeclareVarInst("float", pfTemp3, kStack, LoadVarInst(Address(pfPerm3, kStruct)))
		StoreVarInst(Address(pfPerm3, kStruct), LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec4KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fConst1KC, kStruct)))
		DeclareVarInst("float", pfTemp4, kStack, LoadVarInst(Address(pfPerm4, kStruct)))
		StoreVarInst(Address(pfPerm4, kStruct), LoadVarInst(Address(fConst1KC, kStruct)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp0, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp1, kStack))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp3, kStack))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp4, kStack))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp4, kStack))))
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
	DeclareVarInst("float", fConst0KC, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0KC[2], kStruct)
	DeclareVarInst("float", pfPerm0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	DeclareVarInst("float", pfPerm1, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
	DeclareVarInst("float", pfPerm2, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2], kStruct)
	DeclareVarInst("float", pfPerm3, kStruct)
	DeclareVarInst("float", fConst1KC, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec4KC[2], kStruct)
	DeclareVarInst("float", pfPerm4, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KC, kStruct), Float(0.8f))
	StoreVarInst(Address(pfPerm0, kStruct), Float(0.5f))
	StoreVarInst(Address(pfPerm1, kStruct), Float(0.31f))
	StoreVarInst(Address(pfPerm2, kStruct), Float(0.32f))
	StoreVarInst(Address(pfPerm3, kStruct), Float(0.7f))
	StoreVarInst(Address(fConst1KC, kStruct), Float(0.9f))
	StoreVarInst(Address(pfPerm4, kStruct), Float(0.35f))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0KC, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4KC, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
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
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fConst0KC, kStruct)))
			DeclareVarInst("float", pfTemp0, kStack, LoadVarInst(Address(pfPerm0, kStruct)))
			StoreVarInst(Address(pfPerm0, kStruct), LoadVarInst(Address(fConst0KC, kStruct)))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", pfTemp1, kStack, LoadVarInst(Address(pfPerm1, kStruct)))
			StoreVarInst(Address(pfPerm1, kStruct), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", pfTemp2, kStack, LoadVarInst(Address(pfPerm2, kStruct)))
			StoreVarInst(Address(pfPerm2, kStruct), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(pfTemp2, kStack)))
			DeclareVarInst("float", pfTemp3, kStack, LoadVarInst(Address(pfPerm3, kStruct)))
			StoreVarInst(Address(pfPerm3, kStruct), LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec4KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fConst1KC, kStruct)))
			DeclareVarInst("float", pfTemp4, kStack, LoadVarInst(Address(pfPerm4, kStruct)))
			StoreVarInst(Address(pfPerm4, kStruct), LoadVarInst(Address(fConst1KC, kStruct)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp0, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp1, kStack))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp3, kStack))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp4, kStack))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(pfTemp4, kStack))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 68 bytes
Total heap size = 76 bytes
Stack size in compute = 56 bytes

======= Variable access in Control ==========

Field = fConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fConst0KC size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = IOTA0 size = 1 size_bytes = 4 read = 9 write = 1 ratio = 10
Field = fVec0KC size = 2 size_bytes = 8 read = 0 write = 1 ratio = 0.5
Field = pfPerm0 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVec1SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = pfPerm1 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVec2SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = pfPerm2 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fVec3SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = pfPerm3 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fConst1KC size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec4KC size = 2 size_bytes = 8 read = 0 write = 1 ratio = 0.5
Field = pfPerm4 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
