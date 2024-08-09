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

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("float", fConst1)("int", iConst2)("int", iConst3)("float[2]", fVec0)("int", iConst4)("float[3]", fVec1)("int", iConst5)("float[5]", fVec2)("int", iConst6)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst2, kStruct), BinopInst("==", LoadVarInst(Address(fConst0, kStruct)), Float(0.0f)))
	StoreVarInst(Address(iConst3, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", LoadVarInst(Address(fConst0, kStruct)))), Int32(2)))
	StoreVarInst(Address(iConst4, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst5, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst6, kStruct), BinopInst("+", LoadVarInst(Address(iConst3, kStruct)), BinopInst("*", Int32(2), LoadVarInst(Address(iConst4, kStruct)))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(3))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(5))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 31 Store = 10 Binop = 10 [ { Int(+) = 1 } { Int(-) = 2 } { Int(<) = 1 } { Int(>) = 1 } { Real(*) = 1 } { Real(+) = 4 } ] Mathop = 0 Numbers = 20 Declare = 4 Cast = 2 Select = 4 Loop = 2

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(2)])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(Address(iConst2, kStruct)) LoadVarInst(Address(fTemp0, kStack)) Select2Inst(LoadVarInst(Address(iConst3, kStruct)) LoadVarInst(Address(fTemp0, kStack)) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst4, kStruct)) LoadVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(iConst3, kStruct))]) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst5, kStruct)) LoadVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(iConst6, kStruct))]) Float(0.0f))))))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(2)], LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		ForLoopInst 
			DeclareVarInst("int", j0, kLoop, Int32(4))
			BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
			StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
			BlockInst 
				StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(fVec2, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
			EndBlockInst
		EndForLoopInst
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
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("int", iConst2, kStruct)
	DeclareVarInst("int", iConst3, kStruct)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("int", iConst4, kStruct)
	DeclareVarInst("float", fVec1[3], kStruct)
	DeclareVarInst("int", iConst5, kStruct)
	DeclareVarInst("float", fVec2[5], kStruct)
	DeclareVarInst("int", iConst6, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst2, kStruct), BinopInst("==", LoadVarInst(Address(fConst0, kStruct)), Float(0.0f)))
	StoreVarInst(Address(iConst3, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", LoadVarInst(Address(fConst0, kStruct)))), Int32(2)))
	StoreVarInst(Address(iConst4, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst5, kStruct), BinopInst("%", CastInst("int", FunCallInst("floorf", BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))), Int32(2)))
	StoreVarInst(Address(iConst6, kStruct), BinopInst("+", LoadVarInst(Address(iConst3, kStruct)), BinopInst("*", Int32(2), LoadVarInst(Address(iConst4, kStruct)))))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(3))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(5))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(2)])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(Address(iConst2, kStruct)) LoadVarInst(Address(fTemp0, kStack)) Select2Inst(LoadVarInst(Address(iConst3, kStruct)) LoadVarInst(Address(fTemp0, kStack)) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst4, kStruct)) LoadVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(iConst3, kStruct))]) Float(0.0f))), Select2Inst(LoadVarInst(Address(iConst5, kStruct)) LoadVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(iConst6, kStruct))]) Float(0.0f))))))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(2)], LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			ForLoopInst 
				DeclareVarInst("int", j0, kLoop, Int32(4))
				BinopInst(">", LoadVarInst(Address(j0, kLoop)), Int32(0))
				StoreVarInst(Address(j0, kLoop), BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1)))
				BlockInst 
					StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(j0, kLoop))], LoadVarInst(Address(fVec2, kStruct)[BinopInst("-", LoadVarInst(Address(j0, kLoop)), Int32(1))]))
				EndBlockInst
			EndForLoopInst
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 24 bytes
Heap size int* = 0 bytes
Heap size real = 48 bytes
Total heap size = 72 bytes
Stack size in compute = 16 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 5 size_bytes = 20 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 5 size_bytes = 20 read = 0 write = 0 ratio = 0
Field = iConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iConst3 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = iConst4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = iConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2 size = 5 size_bytes = 20 read = 2 write = 2 ratio = 0.8
Field = iConst6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
