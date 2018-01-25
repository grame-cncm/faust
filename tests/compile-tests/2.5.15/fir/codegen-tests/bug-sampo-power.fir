======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations ==========

BlockInst 
	DeclareFunInst("int", "mydspSIG0_faustpower2_i", "int", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec0[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
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
					StoreVarInst(stack, rate, Int32(0))
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

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 7
Store = 4
Binop = 3
Numbers = 5
Declare = 1
Cast = 0
Select = 0
Loop = 1
Funcall = 1

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec0[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec0[Int32(1)]), Int32(1)))
		StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("mydspSIG0_faustpower2_i", LoadVarInst(struct, iRec0[Int32(0)])))
		StoreVarInst(struct, iRec0[Int32(1)], LoadVarInst(struct, iRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("bug-sampo-power")
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareVarInst(static, int, itbl0mydspSIG0[128])
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("int", "mydsp_faustpower2_i", "int", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
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

======= Static Init ==========

BlockInst 
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(128), LoadVarInst(static, itbl0mydspSIG0)))
	EndBlock
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	EndBlock

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
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
Load = 5
Store = 2
Binop = 2
Numbers = 2
Declare = 1
Cast = 1
Select = 0
Loop = 1
Funcall = 1

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_i", LoadVarInst(static, itbl0mydspSIG0[CastInst("int", BinopInst("*", Float(127.0f), FunCallInst("fabsf", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))))]))))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareVarInst(static, int, itbl0mydspSIG0[128])
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("int", "mydsp_faustpower2_i", "int", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	========== Static init method ==========
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(128), LoadVarInst(static, itbl0mydspSIG0)))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("int", "mydspSIG0_faustpower2_i", "int", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, int, iRec0[2])
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec0[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec0[Int32(1)]), Int32(1)))
			StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("mydspSIG0_faustpower2_i", LoadVarInst(struct, iRec0[Int32(0)])))
			StoreVarInst(struct, iRec0[Int32(1)], LoadVarInst(struct, iRec0[Int32(0)]))
			EndBlock
		EndForLoop
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", FunCallInst("mydsp_faustpower2_i", LoadVarInst(static, itbl0mydspSIG0[CastInst("int", BinopInst("*", Float(127.0f), FunCallInst("fabsf", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))))]))))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 0 bytes
Heap size = 12 bytes
Stack size in compute = 16 bytes

