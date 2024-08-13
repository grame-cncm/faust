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
	DeclareVarInst("float", fmydspWave0[11], kStaticStruct|kConst, FloatArrayNumInst{0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f})
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("float", fmydspWave1[4], kStaticStruct|kConst, FloatArrayNumInst{0.1f,0.8f,0.9f,0.2f})
	DeclareFunInst("float", "floorf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", pfPerm0)("int", fmydspWave0_idx)("int[2]", iVec0)("int", fSampleRate)("float", fConst0)("int", fmydspWave1_idx)("float[2]", fRec0)>)

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
	StoreVarInst(Address(pfPerm0, kStruct), Int32(1))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(7e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fmydspWave1_idx, kStruct), Int32(0))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 26 Store = 11 Binop = 10 [ { Int(%) = 2 } { Int(+) = 3 } { Int(<) = 1 } { Real(+) = 1 } { Real(-) = 1 } { Real(>) = 2 } ] Mathop = 1 [ { floorf = 1 } ] Numbers = 16 Declare = 5 Cast = 3 Select = 1 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", pfTemp0, kStack, LoadVarInst(Address(pfPerm0, kStruct)))
		DeclareVarInst("float", fTemp0, kStack, LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], BinopInst(">", LoadVarInst(Address(fTemp0, kStack)), Float(0.0f)))
		StoreVarInst(Address(pfPerm0, kStruct), BinopInst(">", LoadVarInst(Address(fTemp0, kStack)), Float(0.0f)))
		DeclareVarInst("float", fTemp1, kStack, LoadVarInst(Address(fmydspWave1, kStaticStruct)[LoadVarInst(Address(fmydspWave1_idx, kStruct))]))
		DeclareVarInst("float", fTemp2, kStack, Select2Inst(LoadVarInst(Address(pfTemp0, kStack)) LoadVarInst(Address(fTemp1, kStack)) BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp1, kStack))))
		StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(11)))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fmydspWave1_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1_idx, kStruct))), Int32(4)))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", fmydspWave0[11], kStaticStruct|kConst, FloatArrayNumInst{0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f})
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("float", fmydspWave1[4], kStaticStruct|kConst, FloatArrayNumInst{0.1f,0.8f,0.9f,0.2f})
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst("int", pfPerm0, kStruct)
	DeclareVarInst("int", fmydspWave0_idx, kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("int", fmydspWave1_idx, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(pfPerm0, kStruct), Int32(1))
	StoreVarInst(Address(fmydspWave0_idx, kStruct), Int32(0))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(7e+02f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fmydspWave1_idx, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
			DeclareVarInst("int", pfTemp0, kStack, LoadVarInst(Address(pfPerm0, kStruct)))
			DeclareVarInst("float", fTemp0, kStack, LoadVarInst(Address(fmydspWave0, kStaticStruct)[LoadVarInst(Address(fmydspWave0_idx, kStruct))]))
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], BinopInst(">", LoadVarInst(Address(fTemp0, kStack)), Float(0.0f)))
			StoreVarInst(Address(pfPerm0, kStruct), BinopInst(">", LoadVarInst(Address(fTemp0, kStack)), Float(0.0f)))
			DeclareVarInst("float", fTemp1, kStack, LoadVarInst(Address(fmydspWave1, kStaticStruct)[LoadVarInst(Address(fmydspWave1_idx, kStruct))]))
			DeclareVarInst("float", fTemp2, kStack, Select2Inst(LoadVarInst(Address(pfTemp0, kStack)) LoadVarInst(Address(fTemp1, kStack)) BinopInst("+", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp0, kStack))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp1, kStack))))
			StoreVarInst(Address(fmydspWave0_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave0_idx, kStruct))), Int32(11)))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fmydspWave1_idx, kStruct), BinopInst("%", BinopInst("+", Int32(1), LoadVarInst(Address(fmydspWave1_idx, kStruct))), Int32(4)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 16 bytes
Heap size int* = 8 bytes
Heap size real = 12 bytes
Total heap size = 36 bytes
Stack size in compute = 24 bytes

======= Variable access in Control ==========

Field = pfPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = pfPerm0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fmydspWave1_idx size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = pfPerm0 size = 1 size_bytes = 4 read = 1 write = 1 ratio = 2
Field = fmydspWave0_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = iVec0 size = 2 size_bytes = 8 read = 1 write = 2 ratio = 1.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fmydspWave1_idx size = 1 size_bytes = 4 read = 2 write = 1 ratio = 3
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
