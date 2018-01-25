======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("frog")
	AddMetaDeclareInst(fHslider1, "acc", "0 0 -10 0 10")
	AddHorizontalSlider("cutoff", fHslider1, 2500.0f, 50.0f, 5000.0f, 0.00999999978f)
	AddButtonInst("gate"fButton0)
	AddHorizontalSlider("x", fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddHorizontalSlider("y", fHslider2, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec0[3])
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
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(100.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst2, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(2500.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 9
Store = 0
Binop = 9
Numbers = 8
Declare = 8
Cast = 4
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("+", BinopInst("*", Float(99.0f), CastInst("float", LoadVarInst(struct, fHslider0))), Float(1.0f)))
	DeclareVarInst(stack, "int", iSlow3, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), BinopInst("+", BinopInst("*", Float(39.0f), BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2)))), Float(1.0f))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 65
Store = 18
Binop = 49
Numbers = 37
Declare = 12
Cast = 4
Select = 0
Loop = 1
Funcall = 4

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow0))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec1[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow3)))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec4[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp1, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", LoadVarInst(struct, fRec4[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fTemp1))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.0f)))
		DeclareVarInst(stack, "int", iTemp4, BinopInst("<", LoadVarInst(stack, fTemp3), Float(0.0f)))
		StoreVarInst(struct, fRec2[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp4) LoadVarInst(stack, fTemp2) LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fRec3, Select2Inst(LoadVarInst(stack, iTemp4) LoadVarInst(stack, fTemp2) BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp1))), LoadVarInst(stack, fTemp3)))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp5, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec5[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp5)))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fRec6[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp5)), Float(1.0f)))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("*", Float(0.5f), BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec3)), Float(-1.0f)))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp5)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp5))))))), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec0[Int32(1)])))), LoadVarInst(stack, fTemp8)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp9)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp9)))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec0[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(100.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst2, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(2500.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("+", BinopInst("*", Float(99.0f), CastInst("float", LoadVarInst(struct, fHslider0))), Float(1.0f)))
	DeclareVarInst(stack, "int", iSlow3, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), BinopInst("+", BinopInst("*", Float(39.0f), BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2)))), Float(1.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow0))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec1[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow3)))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec4[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp1, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", LoadVarInst(struct, fRec4[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fTemp1))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.0f)))
			DeclareVarInst(stack, "int", iTemp4, BinopInst("<", LoadVarInst(stack, fTemp3), Float(0.0f)))
			StoreVarInst(struct, fRec2[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp4) LoadVarInst(stack, fTemp2) LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fRec3, Select2Inst(LoadVarInst(stack, iTemp4) LoadVarInst(stack, fTemp2) BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp1))), LoadVarInst(stack, fTemp3)))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp5, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec5[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp5)))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fRec6[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp5)), Float(1.0f)))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("*", Float(0.5f), BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec3)), Float(-1.0f)))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp5)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp5))))))), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec0[Int32(1)])))), LoadVarInst(stack, fTemp8)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp9)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp9)))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 96 bytes
Heap size = 100 bytes
Stack size in compute = 40 bytes

