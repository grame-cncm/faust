======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("math")
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "rintf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "remainderf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "logf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareFunInst("int", "abs", "int", dummy0)
	DeclareFunInst("float", "asinf", "float", dummy0)
	DeclareFunInst("float", "atan2f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "atanf", "float", dummy0)
	DeclareFunInst("float", "ceilf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(6))
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
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 3
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 4
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 5
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
	EndBlock

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

======= Compute control ==========

Instructions complexity
Load = 7
Store = 0
Binop = 0
Numbers = 0
Declare = 7
Cast = 0
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 32
Store = 4
Binop = 22
Numbers = 6
Declare = 2
Cast = 26
Select = 0
Loop = 1
Funcall = 19

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec0[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec0[Int32(1)]), Int32(1)))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("+", LoadVarInst(struct, iRec0[Int32(0)]), Int32(-1)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", FunCallInst("sqrtf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("tanf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("rintf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("sinf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("remainderf", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)]))), BinopInst("+", FunCallInst("powf", CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])), CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("min_f", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))), BinopInst("+", FunCallInst("logf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("log10f", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", FunCallInst("abs", LoadVarInst(stack, iTemp0))), FunCallInst("asinf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("atan2f", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))), FunCallInst("atanf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("ceilf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("cosf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("expf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("floorf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("fmodf", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))), FunCallInst("max_f", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))))))))))))))
		StoreVarInst(struct, iRec0[Int32(1)], LoadVarInst(struct, iRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "rintf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "remainderf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "logf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareFunInst("int", "abs", "int", dummy0)
	DeclareFunInst("float", "asinf", "float", dummy0)
	DeclareFunInst("float", "atan2f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "atanf", "float", dummy0)
	DeclareFunInst("float", "ceilf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareVarInst(struct, int, iRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
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
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec0[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec0[Int32(1)]), Int32(1)))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("+", LoadVarInst(struct, iRec0[Int32(0)]), Int32(-1)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", FunCallInst("sqrtf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("tanf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("rintf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("sinf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("remainderf", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)]))), BinopInst("+", FunCallInst("powf", CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])), CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("min_f", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)]))), BinopInst("+", FunCallInst("logf", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", FunCallInst("log10f", CastInst("float", LoadVarInst(stack, iTemp0))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", CastInst("float", FunCallInst("abs", LoadVarInst(stack, iTemp0))), FunCallInst("asinf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("atan2f", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))), FunCallInst("atanf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("ceilf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("cosf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("expf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("floorf", CastInst("float", LoadVarInst(stack, iTemp0)))), FunCallInst("fmodf", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))), FunCallInst("max_f", CastInst("float", LoadVarInst(stack, iTemp0)), CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))))))))))))))
			StoreVarInst(struct, iRec0[Int32(1)], LoadVarInst(struct, iRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 0 bytes
Heap size = 12 bytes
Stack size in compute = 56 bytes

