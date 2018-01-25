======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("rain")
	AddHorizontalSlider("density", fHslider1, 300.0f, 0.0f, 1000.0f, 1.0f)
	AddHorizontalSlider("volume", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "fabsf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iRec0[2])
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
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
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 1
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

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(300.0f)))
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
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 4
Store = 0
Binop = 1
Numbers = 1
Declare = 4
Cast = 2
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 23
Store = 9
Binop = 14
Numbers = 14
Declare = 5
Cast = 6
Select = 0
Loop = 1
Funcall = 2

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "int", iTemp0, BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(struct, iRec0[Int32(1)]), Int32(12345))))
		StoreVarInst(struct, iRec0[Int32(0)], BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(stack, iTemp0), Int32(12345))))
		DeclareVarInst(stack, "int", iRec1, LoadVarInst(stack, iTemp0))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec0[Int32(0)]))))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp1))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fVec0[Int32(1)]), CastInst("float", BinopInst("<", FunCallInst("fabsf", LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fSlow1)))))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(stack, iRec1))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp2))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fVec1[Int32(1)]), CastInst("float", BinopInst("<", FunCallInst("fabsf", LoadVarInst(stack, fTemp2)), LoadVarInst(stack, fSlow1)))))))
		StoreVarInst(struct, iRec0[Int32(1)], LoadVarInst(struct, iRec0[Int32(0)]))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iRec0[2])
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(300.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "int", iTemp0, BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(struct, iRec0[Int32(1)]), Int32(12345))))
			StoreVarInst(struct, iRec0[Int32(0)], BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(stack, iTemp0), Int32(12345))))
			DeclareVarInst(stack, "int", iRec1, LoadVarInst(stack, iTemp0))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec0[Int32(0)]))))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp1))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fVec0[Int32(1)]), CastInst("float", BinopInst("<", FunCallInst("fabsf", LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fSlow1)))))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(stack, iRec1))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp2))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fVec1[Int32(1)]), CastInst("float", BinopInst("<", FunCallInst("fabsf", LoadVarInst(stack, fTemp2)), LoadVarInst(stack, fSlow1)))))))
			StoreVarInst(struct, iRec0[Int32(1)], LoadVarInst(struct, iRec0[Int32(0)]))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 24 bytes
Heap size = 36 bytes
Stack size in compute = 24 bytes

