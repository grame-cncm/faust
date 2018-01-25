======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("felix1")
	CloseboxInst
	EndBlock

======= Global external declarations ==========

BlockInst 
	DeclareFunInst("float", "hypotf", "float", dummy0, "float", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[512])
	DeclareVarInst(struct, "int", iConst0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getInputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getOutputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, iConst0, BinopInst("&", CastInst("int", CastInst("float", FunCallInst("hypotf", Float(2.0f), Float(4.0f)))), Int32(511)))
	EndBlock

======= Clear ==========

BlockInst 
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(512))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 2
Store = 0
Binop = 0
Numbers = 0
Declare = 2
Cast = 0
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 8
Store = 4
Binop = 4
Numbers = 4
Declare = 1
Cast = 2
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst0)), Int32(511))])))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "hypotf", "float", dummy0, "float", dummy1)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[512])
	DeclareVarInst(struct, "int", iConst0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, iConst0, BinopInst("&", CastInst("int", CastInst("float", FunCallInst("hypotf", Float(2.0f), Float(4.0f)))), Int32(511)))
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(512))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst0)), Int32(511))])))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 12 bytes
Heap size int* = 0 bytes
Heap size real = 2048 bytes
Heap size = 2060 bytes
Stack size in compute = 16 bytes

