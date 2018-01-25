======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec1[2])
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
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 7
Store = 4
Binop = 5
Numbers = 7
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
		StoreVarInst(struct, iRec1[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec1[Int32(1)]), Int32(1)))
		StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec1[Int32(0)]), Int32(-1))))))
		StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
		EndBlock
	EndForLoop

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("Oscillator")
	AddMetaDeclareInst(fHslider1, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider1, 1000.0f, 20.0f, 24000.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("volume", fHslider0, 0.0f, -96.0f, 0.0f, 0.100000001f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65537])
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec2[2])
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
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(65537), LoadVarInst(static, ftbl0mydspSIG0)))
	EndBlock
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	EndBlock

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1000.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 4
Store = 0
Binop = 3
Numbers = 3
Declare = 3
Cast = 2
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider1))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 20
Store = 6
Binop = 13
Numbers = 8
Declare = 3
Cast = 2
Select = 0
Loop = 1
Funcall = 2

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec2[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec2[Int32(0)])))
		DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(stack, fTemp0)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp0), FunCallInst("floorf", LoadVarInst(stack, fTemp0))), BinopInst("-", LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))]), LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)])))))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65537])
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec2[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1000.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(65537), LoadVarInst(static, ftbl0mydspSIG0)))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst(struct, int, iRec1[2])
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l1)], Int32(0))
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
			StoreVarInst(struct, iRec1[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec1[Int32(1)]), Int32(1)))
			StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec1[Int32(0)]), Int32(-1))))))
			StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
			EndBlock
		EndForLoop
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider1))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec2[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec2[Int32(0)])))
			DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(stack, fTemp0)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp0), FunCallInst("floorf", LoadVarInst(stack, fTemp0))), BinopInst("-", LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))]), LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)])))))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 28 bytes
Heap size = 40 bytes
Stack size in compute = 16 bytes

