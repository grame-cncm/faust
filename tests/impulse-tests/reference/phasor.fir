======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("phasor")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", fmydspWave0SC[4], kStaticStruct|kConst, FloatArrayNumInst{0.1f,0.8f,0.9f,0.2f})
	DeclareVarInst("float", fmydspWave1SC[11], kStaticStruct|kConst, FloatArrayNumInst{0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f})
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("float", fConst0KC)("int", fmydspWave0SC_idx)("float", fConst1KC)("int", fmydspWave1SC_idx)("int", IOTA0)("int[2]", iVec0SC)("int", pfPerm0)("int", fSampleRate)("float", fConst2KI)("float[2]", fVec1SI)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
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
	StoreVarInst(Address(fConst0KC, kStruct), Float(0.1f))
	StoreVarInst(Address(fmydspWave0SC_idx, kStruct), Int32(0))
	StoreVarInst(Address(fConst1KC, kStruct), Float(0.0f))
	StoreVarInst(Address(fmydspWave1SC_idx, kStruct), Int32(0))
	StoreVarInst(Address(pfPerm0, kStruct), Int32(1))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(7e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
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
			StoreVarInst(Address(iVec0SC, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 3 Store = 0 Binop = 0 Mathop = 0 Numbers = 3 Declare = 3 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 30 Store = 10 Binop = 16 [ { Int(%) = 2 } { Int(&) = 5 } { Int(+) = 4 } { Int(-) = 1 } { Int(<) = 1 } { Real(+) = 2 } { Real(>) = 1 } ] Mathop = 1 [ { floorf = 1 } ] Numbers = 14 Declare = 5 Cast = 3 Select = 1 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SC, kStack, LoadVarInst(Address(fmydspWave0SC, kStaticStruct)[LoadVarInst(Address(fmydspWave0SC_idx, kStruct))]))
		DeclareVarInst("float", fTemp1SC, kStack, LoadVarInst(Address(fmydspWave1SC, kStaticStruct)[LoadVarInst(Address(fmydspWave1SC_idx, kStruct))]))
		StoreVarInst(Address(iVec0SC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst(">", LoadVarInst(Address(fTemp1SC, kStack)), Float(0.0f)))
		DeclareVarInst("int", pfTemp0, kStack, LoadVarInst(Address(pfPerm0, kStruct)))
		StoreVarInst(Address(pfPerm0, kStruct), LoadVarInst(Address(iVec0SC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp2SI, kStack, Select2Inst(LoadVarInst(Address(pfTemp0, kStack)) LoadVarInst(Address(fTemp0SC, kStack)) BinopInst("+", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec1SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec1SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fTemp2SI, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp2SI, kStack))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec1SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp1SC, kStack))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0SC, kStack))))
		StoreVarInst(Address(fmydspWave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0SC_idx, kStruct))), Int32(4)))
		StoreVarInst(Address(fmydspWave1SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1SC_idx, kStruct))), Int32(11)))
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
	DeclareVarInst("float", fmydspWave0SC[4], kStaticStruct|kConst, FloatArrayNumInst{0.1f,0.8f,0.9f,0.2f})
	DeclareVarInst("float", fmydspWave1SC[11], kStaticStruct|kConst, FloatArrayNumInst{0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f})
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst("float", fConst0KC, kStruct)
	DeclareVarInst("int", fmydspWave0SC_idx, kStruct)
	DeclareVarInst("float", fConst1KC, kStruct)
	DeclareVarInst("int", fmydspWave1SC_idx, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec0SC[2], kStruct)
	DeclareVarInst("int", pfPerm0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	// Recursion delay fVec1SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KC, kStruct), Float(0.1f))
	StoreVarInst(Address(fmydspWave0SC_idx, kStruct), Int32(0))
	StoreVarInst(Address(fConst1KC, kStruct), Float(0.0f))
	StoreVarInst(Address(fmydspWave1SC_idx, kStruct), Int32(0))
	StoreVarInst(Address(pfPerm0, kStruct), Int32(1))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(7e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SC, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SC, kStack, LoadVarInst(Address(fmydspWave0SC, kStaticStruct)[LoadVarInst(Address(fmydspWave0SC_idx, kStruct))]))
			DeclareVarInst("float", fTemp1SC, kStack, LoadVarInst(Address(fmydspWave1SC, kStaticStruct)[LoadVarInst(Address(fmydspWave1SC_idx, kStruct))]))
			StoreVarInst(Address(iVec0SC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst(">", LoadVarInst(Address(fTemp1SC, kStack)), Float(0.0f)))
			DeclareVarInst("int", pfTemp0, kStack, LoadVarInst(Address(pfPerm0, kStruct)))
			StoreVarInst(Address(pfPerm0, kStruct), LoadVarInst(Address(iVec0SC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp2SI, kStack, Select2Inst(LoadVarInst(Address(pfTemp0, kStack)) LoadVarInst(Address(fTemp0SC, kStack)) BinopInst("+", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec1SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec1SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fTemp2SI, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp2SI, kStack))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec1SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp1SC, kStack))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0SC, kStack))))
			StoreVarInst(Address(fmydspWave0SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0SC_idx, kStruct))), Int32(4)))
			StoreVarInst(Address(fmydspWave1SC_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1SC_idx, kStruct))), Int32(11)))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 20 bytes
Heap size int* = 8 bytes
Heap size real = 20 bytes
Total heap size = 48 bytes
Stack size in compute = 24 bytes

======= Variable access in Control ==========

Field = fConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave0SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave0SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1SC_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = pfPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave0SC_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = fConst1KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1SC_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = IOTA0 size = 1 size_bytes = 4 read = 6 write = 1 ratio = 7
Field = iVec0SC size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = pfPerm0 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
