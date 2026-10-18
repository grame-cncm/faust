======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("delays")
	AddNumEntry"d1", fEntry0, 2e+02f, 0.0f, 1e+03f, 1.0f)
	AddNumEntry"d2", fEntry1, 2e+02f, 0.0f, 2e+03f, 1.0f)
	AddNumEntry"d3", fEntry2, 4e+02f, 2e+02f, 3e+03f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[1024]", fVec0)("FAUSTFLOAT", fEntry0)("float[2]", fIIR0)("float[2048]", fVec1)("FAUSTFLOAT", fEntry1)("float[2]", fIIR1)("float[4096]", fVec2)("FAUSTFLOAT", fEntry2)("float[2]", fIIR2)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(3))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(3))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Float(4e+02f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(1024))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2048))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(4096))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 9 Store = 0 Binop = 0 Mathop = 6 [ { max_f = 3 } { min_f = 3 } ] Numbers = 12 Declare = 9 Cast = 6 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("int", iSlow0, kStack, CastInst("int", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+03f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct)))))))
	DeclareVarInst("int", iSlow1, kStack, CastInst("int", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2e+03f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct)))))))
	DeclareVarInst("int", iSlow2, kStack, CastInst("int", FunCallInst("max_f", Float(2e+02f), FunCallInst("min_f", Float(3e+03f), CastInst("float", LoadVarInst(Address(fEntry2, kStruct)))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 37 Store = 14 Binop = 21 [ { Int(&) = 6 } { Int(+) = 2 } { Int(-) = 3 } { Int(<) = 1 } { Real(*) = 6 } { Real(+) = 3 } ] Mathop = 0 Numbers = 27 Declare = 4 Cast = 6 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow0, kStack))), Int32(1023))]), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp0, kStack)))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow1, kStack))), Int32(2047))]), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp1, kStack)))))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(4095))]), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
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
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[1024], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry0, kStruct)
	DeclareVarInst("float", fIIR0[2], kStruct)
	DeclareVarInst("float", fVec1[2048], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry1, kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fVec2[4096], kStruct)
	DeclareVarInst("FAUSTFLOAT", fEntry2, kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fEntry0, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fEntry1, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fEntry2, kStruct), CastInst("FAUSTFLOAT", Float(4e+02f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(1024))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2048))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(4096))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("int", iSlow0, kStack, CastInst("int", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+03f), CastInst("float", LoadVarInst(Address(fEntry0, kStruct)))))))
	DeclareVarInst("int", iSlow1, kStack, CastInst("int", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2e+03f), CastInst("float", LoadVarInst(Address(fEntry1, kStruct)))))))
	DeclareVarInst("int", iSlow2, kStack, CastInst("int", FunCallInst("max_f", Float(2e+02f), FunCallInst("min_f", Float(3e+03f), CastInst("float", LoadVarInst(Address(fEntry2, kStruct)))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow0, kStack))), Int32(1023))]), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp0, kStack)))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow1, kStack))), Int32(2047))]), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp1, kStack)))))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow2, kStack))), Int32(4095))]), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 28708 bytes
Total heap size = 28716 bytes
Stack size in compute = 60 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fEntry0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fEntry1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fEntry2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 7 write = 1 ratio = 8
Field = fVec0 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = fEntry0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec1 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fEntry1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec2 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fEntry2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            49
  eval() cache hits:       12 (24.4898%)
  eval() cache misses:     37
  Loop detector calls:     37
  Stack detector calls:    37

--- Phase 3: Propagation ---
  propagate() calls:       64
  propagate() cache hits:  9 (14.0625%)
  propagate() cache misses:55

--- Box Type Computation ---
  getBoxType() calls:      112
  getBoxType() cache hits: 76 (67.8571%)
  getBoxType() computed:   36

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       2

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           4368
  Trees reused (hash):     9638 (68.8134% reuse rate)
  Property set ops:        2288
  Property get ops:        949

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
