======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("harp")
	AddHorizontalSlider("freq", fHslider0, 400.0f, 50.0f, 2000.0f, 0.00999999978f)
	AddButtonInst("gate"fButton0)
	AddMetaDeclareInst(fHslider1, "acc", "0 0 -10 0 10")
	AddHorizontalSlider("res", fHslider1, 2.0f, 0.100000001f, 4.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
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

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(400.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l1)], Int32(0))
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
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2048))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 15
Store = 0
Binop = 9
Numbers = 9
Declare = 11
Cast = 4
Select = 0
Loop = 0
Funcall = 6

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("/", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("+", LoadVarInst(stack, fSlow0), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("floorf", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(2.0f), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "int", iSlow7, FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iSlow6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fSlow2))))
	DeclareVarInst(stack, "int", iSlow9, FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow6), Int32(1)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 43
Store = 16
Binop = 28
Numbers = 30
Declare = 3
Cast = 2
Select = 0
Loop = 1
Funcall = 1

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(struct, fConst0))
		StoreVarInst(struct, iRec2[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec2[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow5))
		StoreVarInst(struct, fRec3[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(struct, fConst2), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", Float(0.00200000009f), BinopInst("-", LoadVarInst(struct, fConst0), LoadVarInst(struct, fVec0[Int32(1)])))), Float(1.0f)))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fConst3)))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", Float(4.65661287e-10f), BinopInst("*", CastInst("float", LoadVarInst(struct, iRec2[Int32(0)])), Select2Inst(LoadVarInst(stack, iTemp0) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp0) BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec3[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fConst2)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fConst3)))), Float(1.0f)) Float(0.0f)))))))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp1))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow7)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow9)), Int32(2047))]))))
		StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fTemp1))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(1)])))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(400.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l1)], Int32(0))
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
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2048))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("/", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("+", LoadVarInst(stack, fSlow0), Float(-1.0f)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("floorf", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("-", Float(2.0f), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "int", iSlow7, FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(stack, iSlow6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fSlow2))))
	DeclareVarInst(stack, "int", iSlow9, FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iSlow6), Int32(1)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(struct, fConst0))
			StoreVarInst(struct, iRec2[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec2[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow5))
			StoreVarInst(struct, fRec3[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(struct, fConst2), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", Float(0.00200000009f), BinopInst("-", LoadVarInst(struct, fConst0), LoadVarInst(struct, fVec0[Int32(1)])))), Float(1.0f)))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fConst3)))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", Float(4.65661287e-10f), BinopInst("*", CastInst("float", LoadVarInst(struct, iRec2[Int32(0)])), Select2Inst(LoadVarInst(stack, iTemp0) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp0) BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec3[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fConst2)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fConst3)))), Float(1.0f)) Float(0.0f)))))))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp1))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow7)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow9)), Int32(2047))]))))
			StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fTemp1))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(1)])))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 8260 bytes
Heap size = 8276 bytes
Stack size in compute = 48 bytes

