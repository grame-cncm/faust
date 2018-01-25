======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("fm")
	AddButtonInst("gate"fButton0)
	AddMetaDeclareInst(fHslider1, "acc", "0 0 -10 0 10")
	AddHorizontalSlider("res", fHslider1, 1.0f, 0.0f, 2.0f, 0.00999999978f)
	AddHorizontalSlider("x", fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddHorizontalSlider("y", fHslider2, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec7[2])
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
	StoreVarInst(struct, fConst0, BinopInst("/", Float(6.28318548f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l1)], Float(0.0f))
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
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 7
Store = 0
Binop = 6
Numbers = 6
Declare = 7
Cast = 4
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("+", BinopInst("*", Float(420.0f), CastInst("float", LoadVarInst(struct, fHslider0))), Float(80.0f)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), LoadVarInst(stack, fSlow1)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 60
Store = 22
Binop = 40
Numbers = 33
Declare = 9
Cast = 5
Select = 0
Loop = 1
Funcall = 4

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow1))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow2)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec2[Int32(1)])))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec5[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("sinf", LoadVarInst(stack, fTemp1)))
		DeclareVarInst(stack, "float", fTemp3, FunCallInst("cosf", LoadVarInst(stack, fTemp1)))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp2)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(stack, fTemp3))))
		DeclareVarInst(stack, "int", iTemp4, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp3)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp2)))), CastInst("float", LoadVarInst(stack, iTemp4))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fRec6[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp6, FunCallInst("sinf", LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "float", fTemp7, FunCallInst("cosf", LoadVarInst(stack, fTemp5)))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp6)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp7))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp7)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp6)))), CastInst("float", LoadVarInst(stack, iTemp4))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.5f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec7[Int32(0)])))))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec7[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(6.28318548f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l1)], Float(0.0f))
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
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("+", BinopInst("*", Float(420.0f), CastInst("float", LoadVarInst(struct, fHslider0))), Float(80.0f)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00100000005f), LoadVarInst(stack, fSlow1)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow1))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow2)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec2[Int32(1)])))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec5[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("sinf", LoadVarInst(stack, fTemp1)))
			DeclareVarInst(stack, "float", fTemp3, FunCallInst("cosf", LoadVarInst(stack, fTemp1)))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp2)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(stack, fTemp3))))
			DeclareVarInst(stack, "int", iTemp4, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp3)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp2)))), CastInst("float", LoadVarInst(stack, iTemp4))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fRec6[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp6, FunCallInst("sinf", LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "float", fTemp7, FunCallInst("cosf", LoadVarInst(stack, fTemp5)))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp6)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp7))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp7)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp6)))), CastInst("float", LoadVarInst(stack, iTemp4))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.5f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec7[Int32(0)])))))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 92 bytes
Heap size = 104 bytes
Stack size in compute = 32 bytes

